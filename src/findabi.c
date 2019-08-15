#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "findabi.h"

int dbg_print = 0;    // to enable:1 & disable:0 the debug logs on console.

elf_library_list * info_elf_data = NULL; 

/* This is to chck the gien argument path is vaild or not 
 * @return 1: path is vaild.		0: path is invaild.
 */
int check_vaild_path ( const char * path){
	struct stat buf;
	int ret = stat(path,&buf);
	if (-1 == ret){
		return 0;
	}
	return S_ISDIR(buf.st_mode);
}
void add_to_list(elf_library_list * data){

	if (NULL == data) return;

	if (NULL == info_elf_data){
		data->next = NULL;
		info_elf_data = data;
		return;
	}
// add to end 
	elf_library_list * head =  info_elf_data;
	while (head->next != NULL){

		head = head->next;
	}
	data->next = NULL;
	head->next = data;
	return;
}
void diplay_list(){
	elf_library_list * head = info_elf_data;
	printf("File \t\t\t\t\t\t Archtype\n");
	printf("=====\t\t\t\t\t\t ========\n");
	while( head != NULL ){
		printf(" %s\t\t%s\n",head->library_name,head->library_arch_type);
		head = head->next;
	}
}
void clean_up(){
	free(info_elf_data);
}
void process_dir(const char * path){
	dbg_printf(dbg_print,"path: %s",path);
	if (NULL == path){
		printf("Error: path is NULL\n");
		return;
	}
	DIR * dir = NULL;
	struct dirent * dir_read;
	struct stat buf;
	int i = 0;

	if ( NULL ==(dir = opendir(path))){
		printf("directory not opening\n");
	}

	while((dir_read = readdir(dir)) != NULL) {
		
		if ((strcmp(dir_read->d_name,"." ) == 0) ||
			 (strcmp(dir_read->d_name,".." ) == 0) 
			){
			continue;
		}

	//printf("%d File name: %s type: %d \n",i++,dir_read->d_name,dir_read->d_type);
		if ( dir_read->d_type == DT_REG){
			dbg_printf(dbg_print,"File name:%s\n",dir_read->d_name);
			file_processing_abi((char *)path,dir_read->d_name);
		}
	}

	closedir(dir);
	return;
}

int main(int argc, char *argv[]){

	char path_buf[MAX] = {0};
	dbg_printf(dbg_print," Hello to arch/abi world!!!\n");
	if (argc < 2){
		printf(" Need at least one argument to run this application. i.e path\n");
		exit(0);
	}
	else if (argc == 2){
		dbg_printf(dbg_print,"Given path : %s",argv[1]);
		if (1 == check_vaild_path(argv[1])){
			strcpy(path_buf,argv[1]);
		}else{
			printf(" Path:%s is not directory path.\n",argv[1]);
			printf(" Try with correct path (without file name).\n");
			exit(0);
		}

	}
	else {
		printf(" Too many arguments!!!! Application needs only one argument.\n");
		exit(0);
	}

	process_dir(path_buf);
	diplay_list();
	clean_up();
	return 0;
}
