#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include "security.h"

/*! \brief Checks is the current user root. If he is not, kills the program.
 *
 *  \return Nothing
 */
void rootCheck()
{
    if (geteuid() != ROOT_ID)
    {
        puts("You are not authorized as a root to run this program!");
        exit(EXIT_FAILURE);
    }
}

/*! \brief Invites user for authentication . If the password is wrong, kills the program.
 *
 *  \return Nothing
 */
void auth()
{
    pam_handle_t* pamh;
    struct pam_conv pamc;
    pamc.conv = &misc_conv;
    pamc.appdata_ptr = NULL;
    pam_start("su", getenv("USER"), &pamc, &pamh);
    if (pam_authenticate(pamh, 0) != PAM_SUCCESS)
    {
        puts("Password is incorrect!\n");
        exit(EXIT_FAILURE);
    }
    pam_end(pamh, 0);
}
