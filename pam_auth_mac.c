#include <sys/types.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "mac_nss_int.h"
#include <security/pam_appl.h>
#include <security/pam_modules.h>

#define PAM_SM_AUTH
struct usersec *temp;	

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	int rv;
	//uint64_t sec_cat;
	const char *user;
	/*struct pam_conv *conv; 
	struct pam_message msg;
	struct pam_message *(msgp[1]);
	struct pam_response *resp;*/
	
	rv=pam_get_user(pamh, &user, "Uname: ");

	if (rv!=PAM_SUCCESS)
	{
		pam_syslog(pamh, LOG_ERR, "pam_get_user() failed %s", pam_strerror(pamh, rv));
		rv=PAM_USER_UNKNOWN;
		goto out;
	} 
	if (mac_get_uname(temp, user) != 0)
	{
		pam_syslog(pamh, LOG_ERR, "User not found in privileges database %s", user);
		rv=PAM_USER_UNKNOWN;
		goto out;
	}
	{
        
            struct pam_conv *conv;
            struct pam_message *pmsg[3],msg[3];
            struct pam_response *response;


        	rv = pam_get_item( pamh, PAM_CONV, (const void **) &conv ) ;

	// Сами мы не знаем как будет осущестляться диалог, это забота программы
//(в нашем случае этим займется login). Мы
// лишь только  укажем параметры, вид приглашения и более того, можем
  // задать сразу несколько приглашений, если надо
// получить сразу несколько ответов

        pmsg[0] = &msg[0];
        msg[0].msg_style = PAM_PROMPT_ECHO_OFF;
        msg[0].msg=malloc(100);
        //snprintf(msg[0].msg,60,"Diap sec_level:[%d;%d]\n", temp->min, temp->max);

        rv = conv->conv(1, ( const struct pam_message ** ) pmsg
                            , &response, conv->appdata_ptr);
 // Нам дали указатель на диалоговую функцию. ╢е и запускаем.
        
 // Сравним с ответом пользователя. Ответ формируется диалоговой функцией в специальном формате.
        if (temp->min <= atoi(response->resp) && atoi(response->resp) <= temp->max)
	{
		return PAM_SUCCESS;
		goto out;
	
	}

	else 
	{
		return PAM_AUTH_ERR;
	}
      /*диалог*/

	}

	printf("User auth.\n");
	rv=PAM_SUCCESS;
	goto out;
out:
	free(temp);
	return rv;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t * pamh, int flags,int argc, const char **argv)
{
        int rv;
        rv = PAM_SUCCESS;
        return rv;
}

int pam_acct_mgmt(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}
int pam_open_session(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}

int pam_close_session(pam_handle_t *pamh, int flags)
{
	return PAM_SUCCESS ;
}
#ifdef PAM_STATIC
struct pam_module _pam_unix_auth_modstruct = {
    "pam_test",
    pam_sm_authenticate,
    pam_sm_setcred,
    NULL,
    NULL,
    NULL,
    NULL,
};
#endif

