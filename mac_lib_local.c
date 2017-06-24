#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> 
#include <sys/types.h>
#include "mac_nss_int.h"

#define FILE_DB "mac_local_db.db"

extern int mac_get_user_info (const char *uname, uid_t uid, struct usersec *out)
{    
	
   
      FILE *file = fopen(FILE_DB, "r+t");
 	
	if (file != NULL)
	{
		char *str; 

		str = malloc(SIZE_INCREMENT *sizeof(char));

		while (fgets(str, SIZE_INCREMENT, file) != NULL)
		{
			
			int min, max;
			char *str1;
			str1 = malloc(strlen(str) * sizeof(char));
                     	size_t i=0;
                        while (i < strlen(str))
                        {
                                if (str[i]!='\n')
                                        str1[i] = str[i];
                                else
                                        str1[i] = '\0';
                        i++;
                        }
                     	strcpy(str, str1);
			
			struct usersec temp;
			mac_string_parser(str, &temp);
			mac_string_subparser(temp.sec_level, &min, &max);

			if (strcmp(temp.uname, uname) == 0 || temp.uid == uid )
			{	
	  			out->uname = strdup(temp.uname);
				out->uid = temp.uid;
				out->min = min;
				out->max = max;
				out->sec_cat = temp.sec_cat;
				//free(out->uname);
				
				fclose(file);
				return 1;
			}
			free(str1); 
		}
		free(str);
	}
	
	fclose(file);
	return 0;
}

