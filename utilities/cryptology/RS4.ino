// runRC4()
// Port of the classic RC4 stream cipher (ported from a VBA "RunRC4" routine).
// RC4 is symmetric: the same call both encrypts and decrypts, so pass ciphertext
// back through with the same key to recover the plaintext. This variant discards
// the first 3072 keystream bytes before producing output.
String runRC4(const String &message, const String &key) {
  // Guard against an empty key to avoid a divide-by-zero in the (i mod keyLen).
  int keyLen = key.length();
  if (keyLen == 0) {
    return String("");
  }

  int s[256];
  int k[256];

  // Init the S array (identity permutation) and the repeating key stream.
  for (int i = 0; i < 256; i++) {
    s[i] = i;
    k[i] = (uint8_t)key[i % keyLen];
  }

  // Key-scheduling algorithm: build the initial permutation of S.
  int j = 0;
  for (int i = 0; i < 256; i++) {
    j = (j + k[i] + s[i]) & 0xFF;
    int temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }

  int x = 0;
  int y = 0;

  // Drop the first 3072 bytes of the keystream (matches the VBA 1 To 3072 loop).
  for (int i = 0; i < 3072; i++) {
    x = (x + 1) & 0xFF;
    y = (y + s[x]) & 0xFF;
    int temp = s[x];
    s[x] = s[y];
    s[y] = temp;
  }

  // Encode/decode: XOR each message byte with the next keystream byte.
  // NOTE: RC4 output can contain arbitrary bytes, including a 0x00 (null) byte.
  // Bytes are appended as (char) so they are preserved in order; however, Arduino
  // String is backed by a null-terminated C-string, so callers should be aware
  // that an embedded 0x00 in the ciphertext/plaintext can truncate String-based
  // reads (e.g. c_str()/length() may stop early). The return type stays String.
  String result = "";
  for (int i = 0; i < (int)message.length(); i++) {
    x = (x + 1) & 0xFF;
    y = (y + s[x]) & 0xFF;
    int temp = s[x];
    s[x] = s[y];
    s[y] = temp;

    int keyByte = s[(s[x] + s[y]) & 0xFF];
    int value = keyByte ^ (uint8_t)message[i];
    result += (char)value;
  }

  return result;
}
