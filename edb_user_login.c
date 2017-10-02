/*------------------------------------------------------------------------
 *
 * edb_user_login.c
 *
 *
 * Copyright (c) 2017, Vibhor Kumar, vibhor.aim@gmail.com
 *
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"
#include "fmgr.h"
#include "access/xact.h"
#include "catalog/namespace.h"
#include "storage/ipc.h"
#include "utils/builtins.h"
#include "utils/guc.h"
#include "catalog/pg_proc.h"

PG_MODULE_MAGIC;

void		_PG_init(void);

char *edb_login_function = NULL;
bool user_login_enable = true;

/*
 * Execute function named funcname. This function
 * can not have any parameters. This module will
 * be used for execution login/logout procedure.
 */
static void
exec_function(char *funcname)
{
	FuncCandidateList clist;
	List *names;

	names = stringToQualifiedNameList(funcname);
	clist = FuncnameGetCandidatesEx(names, -1, NIL, false, false, true, T_PROC, false, false, NIL, false);

	if (clist == NULL)
		elog(WARNING, "function \"%s()\" does not exist", funcname);
	else
	{
		/* execute function */
		OidFunctionCall0(clist->oid);
	}
}

void
_PG_init(void)
{
	DefineCustomStringVariable("edb_user_login.login_procedure_name",
					 "Define procedure/function that will be executed on login",
					 "It is undefined by default",
					 &edb_login_function,
					 NULL,
					 PGC_SUSET,
					 0, NULL, NULL, NULL);

	DefineCustomBoolVariable("edb_user_login.enable",
					 "Enable to usage login function",
					 NULL,
					 &user_login_enable,
					 true,
					 PGC_SUSET,
					 0, NULL, NULL, NULL);

	if (user_login_enable && edb_login_function != NULL && *edb_login_function != '\0')
	{
		MemoryContext	oldCtx = CurrentMemoryContext;

		PG_TRY();
		{
			SetCurrentStatementStartTimestamp();
			StartTransactionCommand();

			exec_function(edb_login_function);

			CommitTransactionCommand();
		}
		PG_CATCH();
		{
			ErrorData	*edata;

			MemoryContextSwitchTo(oldCtx);
			edata = CopyErrorData();
			FlushErrorState();

			ereport(FATAL,
					(errcode(ERRCODE_CONNECTION_FAILURE),
					 errmsg("unhandled exception in login procedure \"%s\"",
						    edb_login_function),
					 errdetail("%s", edata->message),
					 errcontext("edb_user_login: execute login procedure/function \"%s\"",
						    edb_login_function),
					 errcontext("%s", edata->context)));
		}
		PG_END_TRY();
	}
}
