#include "mac_nss_int.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>

extern int mac_get_uname(struct usersec *out, const char *uname)
{	
	uid_t uid;
	if (uname == NULL)
	{
		printf("Error! Wrong uname\n");
		return 1;

        }
	if (mac_load_lib_user_info(uname, uid, out) != 0)                          
	{
		printf("Error!\n");
		return 1;	
	
	}
	return 0;
}
extern int mac_get_uid(struct usersec *out, uid_t uid)
{
	char *uname;
	uname = malloc(SIZE_INCREMENT*(sizeof(char)));
	if(!uid)
	{
		printf("Error! Wrong uid\n");
		return 1;
	
	}
	
        if (mac_load_lib_user_info(uname, uid, out) != 0)
        {
                printf("Error!\n");
                return 1;

        }
	free(uname);
	return 0;
}
