# pipex
Why use your Shell's pipe '|' if you can write your own?

## Goal and Usage
Pipex should behave such as the following shell command structure:
```
$ < infile command -flag | command -flag > outfile 
```
In Pipex, it receives files and commands in the following format:
```
$ ./pipex infile "command -flag" "command -flag" outfile
```
Both output and behaviour should be the same. 

To install, run:
```
$ git clone https://github.com/leorapini/42_pipex.git pipex
$ cd pipex
$ make
```

## Examples
```
$ ./pipex infile "ls -l" "wc -l" outfile
```
```
$ ./pipex infile "grep a1" "wc -w" outfile```
