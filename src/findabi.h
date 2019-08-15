/*This header is used for to for find abi apllication */

// for debugging purpose.
#define dbg_printf(gdbg,fmt,...) do{ if(gdbg) printf(" %s %d\t " #fmt "\n",\
									__FILE__,__LINE__,##__VA_ARGS__);\
									}while(0);

#define MAX 256
#define TOTAL_BYTE_READ 64

typedef struct elf_library_list{
	char library_name[MAX];
	char library_arch_type[25];
	char library_file_count;
	struct elf_library_list * next;
}elf_library_list;

void add_to_list(elf_library_list * data);
void file_processing_abi( char * path,const char *_name);
 
