- For pinc --version
    - cli.h
    - function name `pinc_cli_run`
    - Arguments `argc` that is number of arguments and `argv` this is pointer array that has pointers to terminal arguments
- Implementation is:
    - header files:
        - `cli.h`,  the content is the definition of `pinc_cli_run`
        - `stdio.h`, for printf message to terminal 
        - `string.h` for comparing the argument and string `--version` 
    - if statement for checking if there is more thatn one arguments coming from
    - if more than one then print the version 
    - if not then print the help for pinc --version usage.


