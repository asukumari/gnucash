/********************************************************************\
 * dialog-account.h -- window for creating and editing accounts for *
 *                     GnuCash                                      *
 * Copyright (C) 2000 Dave Peticolas <petcola@cs.ucdavis.edu>       *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 51 Franklin Street, Fifth Floor    Fax:    +1-617-542-2652       *
 * Boston, MA  02110-1301,  USA       gnu@gnu.org                   *
\********************************************************************/

#ifndef DIALOG_ACCOUNT_H
#define DIALOG_ACCOUNT_H

#include "Account.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Note: make sure to update the help text for this in prefs.scm if these
 * change!  These macros define the account types for which an auto interest
 * xfer dialog could pop up, if the user's preferences allow it.
 */
#define account_type_has_auto_interest_charge(type)  (((type) == ACCT_TYPE_CREDIT) || \
((type) == ACCT_TYPE_LIABILITY) ||\
((type) == ACCT_TYPE_PAYABLE))

#define account_type_has_auto_interest_payment(type) (((type) == ACCT_TYPE_BANK)  || \
((type) == ACCT_TYPE_ASSET) || \
((type) == ACCT_TYPE_MUTUAL) || \
((type) == ACCT_TYPE_RECEIVABLE))

#define account_type_has_auto_interest_xfer(type) \
(  account_type_has_auto_interest_charge(type) || \
account_type_has_auto_interest_payment(type) )

/** @addtogroup GUI
    @{ */
/** @addtogroup GuiAccount Creating and editing accounts in the GUI
    @{ */
/** @file dialog-account.h
 *
 *  This file contains the functions to present a gui to the user for
 *  creating a new account or editing an existing account.
 *
 *  @brief Dialog for create/edit an account.
 *  @author Copyright (C) 1997 Robin D. Clark
 *  @author Copyright (C) 2000 Dave Peticolas
 */

/** @name Non-Modal
 @{ */

/** Display a window for editing the attributes of an existing account.
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param account This parameter specifies the account whose data
 *  will be edited.
 */
void gnc_ui_edit_account_window (GtkWindow *parent, Account *account);


/** Display a window for creating a new account.  This function will
 *  also initially set the parent account of the new account to what
 *  the caller specified.  The user is free, however, to choose any
 *  parent account they wish.
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param book The book in which the new account should be created.
 *  This is a required argument.
 *
 *  @param parent_acct The initially selected parent account.  This
 *  argument is optional, but if supplied must be an account contained
 *  in the specified book.
 */
void gnc_ui_new_account_window (GtkWindow *parent,
                                QofBook *book, Account *parent_acct);


/** Display a window for creating a new account.  This function will
 *  restrict the available account type values to the list specified
 *  by the caller.
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param book The book in which the new account should be created.
 *  This is a required argument.
 *
 *  @param valid_types A GList of GNCAccountType gints [as pointers]
 *  which are allowed to be created.  The calling function is
 *  responsible for freeing this list.
 */
void gnc_ui_new_account_with_types (GtkWindow *parent, QofBook *book,
                                    GList *valid_types);
/** @} */



/** @name Modal
 @{ */

/** Display a modal window for creating a new account
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param name The account name/path to be created.  This parameter
 *  is not used for determining the initially selected parent account.
 */
Account * gnc_ui_new_accounts_from_name_window (GtkWindow *parent,
                                                const char *name);

/** Display a modal window for creating a new account.  This function
 *  will restrict the available account type values to the list
 *  specified by the caller.
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param name The account name/path to be created.  This parameter
 *  is not used for determining the initially selected parent account.
 *
 *  @param valid_types A GList of GNCAccountType gints [as pointers]
 *  which are allowed to be created.  The calling function is
 *  responsible for freeing this list.
 *
 *  @return A pointer to the newly created account.
 */
/* Note that the caller owns the valid_types list */
Account * gnc_ui_new_accounts_from_name_window_with_types (GtkWindow *parent,
                                                           const char *name,
                                                           GList *valid_types);


/** Display a modal window for creating a new account.  This function
 *  will restrict the available account type values to the list
 *  specified by the caller.
 *
 *  @param parent The widget on which to parent the dialog.
 *
 *  @param name The account name/path to be created.  This parameter
 *  is not used for determining the initially selected parent account.
 *
 *  @param valid_types A GList of GNCAccountType gints [as pointers]
 *  which are allowed to be created.  The calling function is
 *  responsible for freeing this list.
 *
 *  @param default_commodity The commodity to initially select when
 *  the dialog is presented.
 *
 *  @param parent_acct The initially selected parent account.
 *
 *  @return A pointer to the newly created account.
 */
Account * gnc_ui_new_accounts_from_name_with_defaults (GtkWindow *parent,
                                                       const char *name,
                                                       GList *valid_types,
                                                       const gnc_commodity *default_commodity,
                                                       Account *parent_acct);

/*
 * register a callback that gets called when the account has changed
 * so significantly that you need to destroy yourself.  In particular
 * this is used by the ledger display to destroy ledgers when the
 * account type has changed.
 */
void gnc_ui_register_account_destroy_callback (void (*cb)(Account *));
/** @} */

void gnc_account_renumber_create_dialog (GtkWidget *window, Account *account);

void gnc_account_cascade_properties_dialog (GtkWidget *window, Account *account);

#ifdef __cplusplus
}
#endif

/** @} */
/** @} */

#endif
