# edb_user_login

edb_user_login is an extension which allows to users to include after logon procedures/functions for EDB Postgres Advanced Server Version 9.6

# Installation

1. Download the the module using git command as given below:
```cmd
git clone https://github.com/vibhorkum/edb_user_login
```
2. Make sure path variable set correctly and has included EDB AS 9.6 bin location as given below:
```cmd
export PATH=/usr/edb/as9.6/bin:$PATH
```
3. Use make and make install to install the module as given below:
```cmd
make
gcc -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -Wmissing-format-attribute -Wformat-security -fno-strict-aliasing -fwrapv -fexcess-precision=standard -I/usr/libexec/icu-edb53.1/include -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -I/usr/include/et -fPIC -I. -I./ -I/usr/edb/as9.6/include/server -I/usr/edb/as9.6/include/internal -I/usr/include/et -D_GNU_SOURCE -I/usr/include/libxml2 -I/usr/libexec/icu-edb53.1/include   -I/usr/include  -c -o edb_user_login.o edb_user_login.c
gcc -Wall -Wmissing-prototypes -Wpointer-arith -Wdeclaration-after-statement -Wendif-labels -Wmissing-format-attribute -Wformat-security -fno-strict-aliasing -fwrapv -fexcess-precision=standard -I/usr/libexec/icu-edb53.1/include -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -m64 -mtune=generic -I/usr/include/et -fPIC -shared -o edb_user_login.so edb_user_login.o  -L/usr/edb/as9.6/lib -Wl,-rpath,/usr/libexec/icu-edb53.1/lib -L/usr/libexec/icu-edb53.1/lib   -L/usr/lib64 -L/usr/libexec/icu-edb53.1/lib  -Wl,--as-needed -Wl,-rpath,'/usr/edb/as9.6/lib',--enable-new-dtags  
```
```cmd
make install 
/bin/mkdir -p '/usr/edb/as9.6/lib'
/bin/install -c -m 755  edb_user_login.so '/usr/edb/as9.6/lib/edb_user_login.so'
```

4. After installing the module, set the following parameters:
```cmd
edb_user_login.enabled = true
edb_user_login.login_procedure_name = 'public.login_procedure'
```

Where *edb_user_login.enabled* is enable to execution of all roles inside the database and *edb_user_login.login_procedure_name* is for procedure/function which DBAs/Developers want to execute after each successful login. 

Please note: Procedure/function should not include any (). Also, this module ignores the output of function/procedures.
