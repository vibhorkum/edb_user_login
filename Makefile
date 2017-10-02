# contrib/edb_user_login/Makefile

MODULE_big = edb_user_login
OBJS = edb_user_login.o $(WIN32RES)
PGFILEDESC = "edb_user_login - login function executer"

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
