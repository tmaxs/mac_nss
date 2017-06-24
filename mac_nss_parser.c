#include "mac_nss_int.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

extern void mac_string_parser(char *str, struct usersec *temp)
{	 
        char *token, *str1;
        char *saveptr;
        int j;

        for ( j = 0, str1 = str; ;j++, str1 = NULL)
        {
              	token = strtok_r(str1, "|", &saveptr);
				
                if (token == NULL)
                        break;	

                switch(j)
                {
                case 0: 
			temp->uname = strdup(token);
			break;
              	case 1: temp->uid = atoi(token);
                        break;
            	case 2:
			temp->sec_level = strdup(token);
                        break;
                case 3: 
			temp->sec_cat = atoi(token);
                        break;
                }
	
        }
	
}

extern void mac_string_subparser(char *str, int *min, int *max)
{
        char *str2;
        char *token;
        char *saveptr;
        int j;

        for ( j = 0, str2 = str; ; j++, str2 = NULL)
        {
                token = strtok_r(str2, "[;]", &saveptr);
                if (token == NULL)
                      break;

                switch(j)
                {
                case 0: *min = atoi(token);
                        break;
                case 1: *max = atoi(token);
                        break;  
		}

        }

}

extern void mac_string_parser_file (char *str, char **type, char **libname)
{
        char *str1;
        char *token;
        char *saveptr;
        int j;

        for ( j = 0, str1 = str; ; j++, str1 = NULL)
        {
                token = strtok_r(str1, ":", &saveptr);
                if (token == NULL)
                      break;
                switch(j)
                {
                case 0: *type = token;
                        break;
                case 1: *libname = token;
                        break;  
		}

        }

}

