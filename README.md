# shell_proj
Repo for Shell project

## How to use

1. build using gcc

    ```
    gcc -o myShell *.c -Wall -Werror
    ```
2. start the shell

    ```
    ./myshell
    ```

## Files and usage
- `myShell`
    - this is main function with actually just call shell_loop


- `shell_loop`
    - this the loop that keeps:
        - printing "myShell>"
        - taking input
        - phasing command
    - Constants set:
        - `CMD_MAX_LEN` for command max size
        - `ARGU_MAX_NUM` for arguments (which acctually also counts command itself and NULL at the end )


- `buildin_exec`
    - execute the build-in function
