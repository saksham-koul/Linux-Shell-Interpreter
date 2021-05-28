# Linux-Shell-Interpreter
Created a mini Linux shell interpreter in C.

-> This page contains the list of all valid commands that can be executed on this shell.
-> This shell can implement a total of 11 commands: 6 internal commands/shell builtins, and 5 external commands as listed here - 

# Internal commands/Shell builtins
----------------------------------
	- chd [relative_path] (cd) (no flags)
	- hisstory [-clear, -write] (history)
        *flags handled = -clear: to clear the command history; -write: to write something from stdin into the history
	- cwd (pwd) (no flags)
	- hellp (help) (no flags)
	- ecko [-n, -e] ["..."] (echo)
        *flags handled = -n: to omit the newline character ('\n') after echoing; -e: to identify some escape sequences which it otherwise would have treated as any other characters (\t & \n handled)
	- quit (exit) (no flags)

# External commands
-------------------
	- datetime [-g, -u] (date)
        *flags handled = -g: to display GMT date, day and time; -u to display UTC date, day and time.
	- makedir [-v, -m] [dir_name] (mkdir)
        *flags handled = -v: verbose - prints a msg after creating the directory; -m: mode - takes a 4 digit mode as input to custom specify read, write and execute permissions for the newly created directory.
	- list [-a, -l] (ls)
        *flags handled = -a: to display all files in the current working dir, including the hidden files; -l: to display all files in long listing format (excluding hidden ones).
	- kat [>] [file1, file2, ...] [>] [file1, file2, ...] (cat) (no flags)
	- remove [-v, -d] [file_name, dir_name] (rm)
        *flags handled = -v: verbose - prints a msg after removing the file passed as argument; -d: to remove directory

-> The things mentioned inside square brackets refer to the flags and arguments that are applicable on some of the commands.
-> Some of these commands can also run without any flags or arguments.
