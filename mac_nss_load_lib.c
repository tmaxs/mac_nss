#include "mac_nss_int.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <sys/types.h>

#define PRIOR_CONFIG "mac_nss.conf"

extern int mac_load_lib_user_info (const char *uname, uid_t uid, struct usersec *out)
{
	
	FILE *file = fopen(PRIOR_CONFIG,"r+t");
	
	if (file != NULL)
	{
             	char *str, *libname;
		char *libn, *type;
		
		str = malloc(SIZE_INCREMENT*sizeof(char));

            	while (fgets(str,SIZE_INCREMENT,file)!= NULL)
         	{	
			int j;
			char *saveptr, *str1;
			

			if ( strchr(str, '#') != NULL)
				continue;
			if ( str[0] == '\n' )
				continue;
			
			libname = malloc(SIZE_INCREMENT*sizeof(char));
			type = malloc(SIZE_INCREMENT*sizeof(char));
				
			mac_string_parser_file(str, &type, &libname);
			
			
			if (strcmp(type, "mac") != 0)
				continue;	
			
        		for ( j = 0, str1 = libname; ; j++, str1 = NULL)
       			{
				char *lib;
				char n[56] = "mac_lib_";
				
				lib = malloc(SIZE_INCREMENT*sizeof(char));               		
				lib = strtok_r(str1, " ", &saveptr);
                		if (lib == NULL)
                      			break;		 
        		
				strcat(n, lib);
				strcat(n,".so");		
				
				void *h = dlopen(n, RTLD_LAZY);

					if (!h)
					{
						fprintf(stderr, "%s\n", dlerror());
						exit(EXIT_FAILURE);
						
					}
					
					printf("Opened library |%s|.\n", lib);
						
				typedef int (*get_func)(const char *, uid_t , struct usersec *);
		
				get_func lib_func = dlsym(h, "mac_get_user_info");		
			
					if (lib_func != NULL)
                        		{
						printf("Function loaded.\n");

						if( lib_func (uname, uid, out) == 0 ) 
						{	
							printf("In the given library of the information on the user it is not found.\n");
							continue;
						}
						else
						{
							dlclose(h);
							fclose(file);
							return 0;
						}

					}
				free(lib);
		

			}		
			free(libname);
			free(type);		
		}
		free(str);
	}      
	fclose(file);
	return 1;             
}   

