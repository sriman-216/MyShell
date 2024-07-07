#MYSHELL    

## Requirements

The requirements to execute this MYSHELL are :
1.A Linux Ubuntu machine.

2.GCC should be installed in the machine:
	If GCC is not installed in your machine, do the following:
	Open the terminal on your machine and run the following commands:
		1. "sudo apt update"
		2. "sudo apt install build-essential"
		OR
		."sudo apt install gcc"
	To check if install then run the following command:
	    ."gcc --version"

3.libreadline :
    Install libreadline in your machine:
    For that run the following command on your terminal:
		 ."sudo apt-get install libreadline8 libreadline-dev"
    Now you are ready to run this MYSHELL!

##Installation

1. Change the directory to the directory where the files are located.
2. Now compile the following commands: 
    -> "make" (To compile the executable files.)

## Usage
 Now run the following commands:
    -> "./myshell" (To execute the MYSHELL.)

This MYSHELL can execute :
1)ls:
	ls [OPTION]
	This can be executed with following options:
	1) -l 2) -s 3) -g 4) -u 5) -S 6) -a
2)ps:
	ps [OPTION]
	This works as original command ps.
	This can be executed with following options:
	1) -a 2) -j 3) - 4) -e 5) -eF
3)cp:
	cp [OPTION] [SOURCE] [TARGET]
	cp [SOURCE] [SOURCE]..... [DIRECTORY]
	This works as original command cp.
	This can be executed with following options:
	1) -i 2) -n 3) -u 4) -v
4)mv:
	mv [OPTION] [SOURCE] [TARGET]
	mv [SOURCE] [SOURCE]..... [DIRECTORY]
	This works as original command mv.
	This can be executed with following options:
	1) -i 2) -n 3) -u 4) -v
5)grep:
	grep [OPTION] PATTERN [FILE] [FILE]...
	This works as original command grep.
	This can be executed with following options:
	1) -s 2) -n 3) -c 4) -m

Type 'help' and ENTER for detailed usage of options for every command.
Type '[COMMAND] --help' and ENTER for detailed usage of options for a particular command.
	

Now you can run whichever command you want to run from the above mentioned commands.

Use quit command to stop MYSHELL

