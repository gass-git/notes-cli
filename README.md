# Notes CLI

Keep track of your notes in the CLI

<img width="706" height="293" alt="notes" src="https://github.com/user-attachments/assets/f1956c5f-a985-460a-84b6-e3a72ccd428f" />

## Install with Scoop

```sh
scoop install https://raw.githubusercontent.com/gass-git/notes-cli/refs/heads/main/notes-cli.json
```

## Commands

View all your notes:
```sh
notes-cli show
```

Add a new note:
```sh
notes-cli add "Your note here"
```

Delete note number n:
```sh
notes-cli delete n
```

## Dev Notes

Run unit-tests:
```sh
gcc -o tests tests.c unity/unity.c notes.c -DNO_MAIN
```