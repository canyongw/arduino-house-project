# My FIRST Arduino Project

## parts on Arduino house

- button
- another button
- RFID tag reader
- LCD
- montion sensor
- servo (door)
- another servo (window)
- gas sensor
- temp sensor
- moister sensor
- LED
- fan
- music buzzer

- [ ] My check box empty
- [x] My check box checked

## steps to update repo

1. local changes 
2. create branch `git checkout -b experiment/readme2`
3. Add files to staging `git add .`
4. Create commit `git commit -m` "My commit message <what is changing>"
5. Make more changes, and stage commit additional changes. (commit often, push when ready)
6. Push new branch to origin `git push origin experiment/readme2`
7. Go to website and review code and merge when ready.
8. If new branch is not needed online, then delete branch online.
9. Local - move back to main branch `git checkout main`
10. Ask origin for new HEAD hash `git fetch`
11. Sync main with origin `git pull origin`

You are now up to date with your remote repository
If the local new branch is no longer needed, then delete.  You are already in main, so you will be able to delete
`git branch -d experiment/readme2`
If error during delete, use force `git branch -D experiment/readme2`