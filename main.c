#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "mac_nss_int.h"
#include <inttypes.h>

int main()
{
	char *uname;
	char *opt;
	uid_t uid;
      
        uname = malloc( sizeof(char));
	opt = malloc( sizeof(char));

        printf("If search by username, enter the word 'uname'. If serch by userID, enter the word 'uid'.\n");
        scanf("%s", opt);
	char *opt1 = "uname";
	char *opt2 = "uid";
	if (strcmp(opt, opt1) == 0 )
	{
        	printf("Enter username:\n");
		scanf("%s", uname);
        	struct usersec temp;
		mac_get_uname(&temp, uname);
  //    	temp = get_user_mac(uname);
        	printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:% "PRIu64" \n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);
        	return 0;
	}
	free(uname);
	if (strcmp(opt, opt2) == 0)
        {
		printf("Enter userID:\n");		
		scanf("%d", &uid);
		printf("Uid:%d\n", uid);
		struct usersec temp;
		mac_get_uid(&temp, uid);
  //            temp = get_user_mac(uname);
		printf("Uname:%s\n Uid:%d\n Min:%d, Max:%d\n Seccat:% "PRIu64" \n",temp.uname, temp.uid, temp.min, temp.max, temp.sec_cat);
		return 0;
	} 
	free(opt);
	printf("Error!\n");
	return 1;                      
	
}
