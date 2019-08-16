# elf_info
This project gives the arch information about given elf file for which it is compiled for.
To run this code base one need to compile it on linux/unix based system.
 
Steps are as follows :
	1. Download this repo from github.
	2. Goto the repo place home.
	3. run command 
		 $ make all
	   this will give you finabi.out as executable file.
	4. Run the ececutable file with path.
		 $ ./findabi  <directory path of your input>
	
Limitations:
	1. Code is tested on x86 & x84_64 linux machine only.
	2. It find arch type on one level depth of given input i.e it's not gona
	   work for subdirectories of given input.
	3. code is using system elf header & their apis.

