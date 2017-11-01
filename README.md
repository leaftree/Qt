**vsftpd代表非常安全的文件传输守护进程，是轻量、稳定、最安全、最快的FTP服务器，是大多数Linux和Unix操作系统的默认FTP服务。不同的vsftpd版本及远行在不同版本的操作系统上时，其配置选项可能是不一样的。**

下面将详细记录vsftpd的常用配置项，简单记录vsftpd所支持的绝大部分特性

> vsftpd默认配置文件位/etc/vsftpd/下，配置文件名为vsftpd.conf  
>> vsftpd.conf文件的配置格式为k-v格式：***字符'#'到行末尾的内容为注释***
```
# = 前后无空格，否则vsftpd启动失败
ConfKey=ConfValue
```
* [基础配置选项](#基础配置选项)
案例
案例一：允许匿名用户上传文件
案例二：本地用户配置
案例三：配置虚拟用户
前奏
步骤 1 ：增加用户ftpuser
步骤 2：配置vsftpd.conf选项
步骤 3：配置虚拟用户信息
步骤 4：配置PAM验证
步骤 5：配置chroot_list
步骤 6：配置user_list
步骤 7：配置用户个性化属性
步骤 8：重启vsftpd服务
vsftpd支持的特性
一、 用户选项
二、用户权限控制
三、超时设置
四、服务器功能选项
五、服务器性能选项
六、信息类设置
七、文件定义
八、目录定义
九、用户连接选项
十、数据传输选项

# 默认配置

> \# 是否允许匿名登录FTP服务器  
>> \# 匿名用户可使用用户名ftp/anonymous进行ftp登录，口令为用户Email地址  
```ini
anonymous_enable=YES
```

> \# 是否允许本地用户(Linux系统中的用户账号)登录FTP服务器  
>> \# 本地用户登录后会进入用户HOME目录，而匿名用户登录后会进入目录/var/ftp/pub下  
```ini
local_enable=YES
```

> \# 是否允许本地用户对FTP服务器文件肯有写权限
```ini
write_enable=YES
```

> \# 本地用户默认掩码为077，一般设置为022
```ini
local_umask=022
```

> \# 是否允许匿名用户上传文件，必须将write_enable设置为YES才有效
```ini
#anon_upload_enable=YES
```

> \# 是否允许匿名用户创建新文件夹
```ini
#anon_mkdir_write_enable=YES
```

> \# 是否允许为目录配置显示信息，使用CMD首次访问某个目录时显示欢迎信息，欢迎信息由所在目录下的.message文件设置
```ini
dirmessage_enable=YES
```

> \# 是否开启文件上传/下载的日志记录功能，默认日志文件为/var/log/vsftpd.log，也可以通过xferlog_file配置自定义日志文件名
```ini
xferlog_enable=YES
```

> \# 是否使用标准的20端口来连接FTP，21为控制连接端口
```ini
connect_from_port_20=YES
```

> \# 是否允许改变上传文件的属主，与chown_username配合使用  
>> \# 警告，不推荐使用root用户上传文件
```ini
#chown_uploads=YES
```

> \# 设置要改变文件的属主(本地用户名)，whoever:任何人
```ini
#chown_username=whoever
```

> \# 记录文件上传/下载日志的文件名，默认日志文件为/var/log/vsftpd.log
```ini
#xferlog_file=/var/log/xferlog
```

> \# 是否使用xferlog的格式书写传输日志文件
```ini
xferlog_std_format=YES
```

> \# 空闲用户会话中断时间，当数据传输结束后，用户连接FTP服务器的时间不应超过600秒
```ini
#idle_session_timeout=600
```

> \# 数据连接超时时间
```ini
#data_connection_timeout=120
```

> \# 运行vsftpd需要的非特权系统用户，缺省是nobody
```ini
#nopriv_user=ftpsecure
```

> \# 是否识别异步ABOR请求，客户端下达"async ABOR"指令时这个设置才需要启用
> \# 不安全设置，通常取消
```ini
#async_abor_enable=YES
```

> \# 是否以ASCII方式传输数据，默认情况下，服务器会忽略ASCII方式的请求  
>> \# 设备ASCII方式选项将允许服务器以ASCII方式传输数据，可能会导致由"SIZE /big/file"方式引起的Dos攻击
```ini
#ascii_upload_enable=YES
#ascii_download_enable=YES
```

> \# 登录FTP服务器时显示欢迎信息
```ini
#ftpd_banner=Welcome to blah FTP service.
```

> \# 拒绝特殊的EmailAddress登录
```ini
#deny_email_enable=YES
```

> \# 当启用deny_email_enable配置后，由banned_email_file指定的邮件地址不可登录FTP服务器  
>> \# 此文件需要用户自己配置，一行一个邮件地址
```ini
#banned_email_file=/etc/vsftpd/banned_emails
```

> \# 是否将所有用户限制在主目录,YES为启用 NO禁用，默认是NO
```ini
#chroot_local_user=YES
```

> \# 是否允许用户登录FTP服务器后有访问自己目录以外的文件的权限  
>> \# 设置为YES，则用户被锁定在自己的HOME目录中；vsftpd将根据chroot_list_file寻找chroot_list文件
```ini
#chroot_list_enable=YES
```

> \# 被列入此文件的用户，登录FTP服务器后不能切换到自己目录以外的其他目录  
>> \# 此项设置有利于FTP服务器的安全；此文件一行一个用户名
```ini
#chroot_list_file=/etc/vsftpd/chroot_list
```

> \# 是否允许递归查询，默认为关闭，以防止远程用户造成过量的IO
```ini
#ls_recurse_enable=YES
```

> \# 是否允许监听，YES表示vsftpd以独立模式运行，由vsftpd自己监听和处理IPv4端口的连接请求
```ini
listen=YES
```

> \# 是否支持IPv6，需要同时监听IPv4和IPv6端口
```ini
#listen_ipv6=YES
```

> \# 设置PAM外挂模块提供的认证服务所使用的配置文件名，即/etc/pam.d/vsftpd文件  
>> \# /etc/pam.d/vsftpd文件中file=/etc/vsftpd/ftpusers字段，表示PAM模块能抵挡的账号内容来自文件/etc/vsftpd/ftpusers
```ini
pam_service_name=vsftpd
```

> \# 是否允许ftpusers文件中的用户登录FTP服务器，默认为NO  
>> \# 此值设置为YES，则user_list文件中的用户允许登录FTP服务器  
>> \# 启用此选项，userlist_deny选项才被启动  
>> \# 如果同时设备了userlist_deny=YES，则user_list文件中的用户将不被允许登录FTP服务器  
```ini
userlist_enable=YES
```

> \# 是否阻止user_list文件中用户登录FTP服务器，默认值为YES
```ini
#userlist_deny=YES
```

> \# 是否使用tcp_wrappers作为主机访问控制方式  
> \# tcp_wrappers可以实现Linux系统网络服务基于主机地址的访问控制  
>> \# 在/etc目录中hosts.allow(允许)和hosts.deny(不允许)两个文件用于设置tcp_wrappers的访问控制  
>> \# 例如要限制10.15.10.10主机访问FTP服务器，则在/etc/hosts.allow中添加***vsftpd:10.15.10.10:DENY***或者在/etc/hosts.deny中添加***vsftpd:10.15.10.10***即可
```ini
tcp_wrappers=YES
```
---
---

# 案例
vsftpd的用户分三类：匿名用户(anonymous user)、本地用户(local user)和虚拟用户(guest user)，下面将详述如何为这三类用户配置FTP服务

## 案例一：允许匿名用户上传文件
```
write_enable=YES
anon_world_readable_only=NO
anon_upload_enable=YES
anon_mkdir_write_enable=YES
```
同时需要确保匿名用户登录到服务器上的目录其他rw-权限，通常情况下anon_root目录为root用户所有，
因此ftp匿名用户则为other用户，所以需要确保其他用户拥有anon_root目录读、写权限

---

## 案例二：本地用户配置
决定vsftpd所在系统的本地用户是否可以登录vsftpd的选项为local_enable，默认值为YES允许  
```
local_enable=YES
```

本地用户登录FTP服务器后的根目录，默认情况是是每个用户的HOME目录，可以由选项local_root指定用户登录的后根目录
```
local_root=app
```
local_root可以选择绝对路径，也可以使用相对路径  
当local_root为相对路径时，则它是相对于HOME目录而言的  
比如local_root=app，当则用户user登录FTP服务器时，它的根目录为/home/user/app

如果想指定某些用户有个性化的设置，则可以设置user_config_dir选项
user_config_dir指定个性化配置文件所在的目录，并且user_config_dir下每个文件的文件名对应着其用户名
```
user_config_dir=/etc/vsftpd/userconf
```

比如，有三个用户SC、LCC、ACC，user_config_dir的值设置为/etc/vsftpd/userconf，则/etc/vsftpd/userconf目录下有三个名字为SC、LCC、ACC的文件

它们对应着本地用户SC、LCC、ACC的个性化配置，其配置格式与vsftpd.conf一样  
当用户登录FTP服务器时，服务器会使用其个性化配置。

## 案例三：配置虚拟用户

#### 前奏
确保系统安装db4-utils程序包，需要使用其db_load命令创建Berkeley数据库文件

#### 步骤 1 ：增加用户ftpuser
```bash
useradd -d $dir_for_ftpuser ftpuser -s /bin/false
```

#### 步骤 2：配置vsftpd.conf选项
```
# 禁止匿名用户登录
anonymous_enable=NO

# 虚拟用户要映射为本地用户，因此要启用本地用户
local_enable=YES

# 是否将所有用户限制在主目录,YES为启用 NO禁用（默认值）
chroot_local_user=YES

# YES：将chroot_list中列出来的用户转到其在user_config_dir下面定义的文件中指定的目录
# NO：就是系统用户的HOME目录
chroot_list_enable=YES

# 指定存储chroot用户名单的文件
chroot_list_file=/etc/vsftpd/chroot_list

# 是否允许chroot_list用户名单的用户登录
userlist_enable=YES

# 是否禁止user_list用户名单的用户登录
#user_list_deny=NO

# 虚拟用户的配置文件的主目录，目录下的配置文件名为虚拟用户名
user_config_dir=/etc/vsftpd/vsftpd_user_dir

# 所有非匿名用户登录都视为guest  
guest_enable=YES

# 设置guest用户在系统中的用户名，默认值为ftp
guest_username=ftpuser

# 指定PAM模块验证文件，文件需要存在于/etc/pam.d目录下
pam_service_name=vsftpd
```

#### 步骤 3：配置虚拟用户信息
创建临时文件login_user.txt，在文件中写入虚拟用户的用户名及登录密码，用户名与用户密码分别在不同行中，奇数行为用户名，偶数行为用户密码

比如：
```
user1
passwd1
user2
passwd2
```

编辑完成后，使用db_load生成数据库文件，供PAM验证使用
```shell
db_load -T -thash -f /etc/vsftpd/login_user.txt /etc/vsftpd/vsftpd_login.db 
```

#### 步骤 4：配置PAM验证

vsftpd默认的PAM验证文件是/etc/pam.d/vsftpd，也可以设置为其他文件名，需要与vsftpd.conf配置中pam_service_name选项指定的文件名一致。

```
# vsftpd_login是通过db_load命令创建的验证文件，配置时把后缀.db去掉
auth sufficient pam_userdb.so db=/etc/vsftpd/vsftpd_login

account sufficient pam_userdb.so db=/etc/vsftpd/vsftpd_login
```

> 如果找不到pam_userdb.so动态库，可以使用locate pam_userdb.so来检测

#### 步骤 5：配置chroot_list
该文件名由vsftpd.conf的chroot_list_file指定，文件用于存储需要设置个性化配置的用户名称，可以在user_config_dir目录下为用户创建根目录local_root，如果没有配置local_root或者没有在chroot_list_file文件名配置用户名，则默认的根目录是虚拟用户映射的真实用户的HOME目录。

该文件中，每个用户单独一行。

#### 步骤 6：配置user_list
如果禁止某些用户登录ftp，则可以在user_list文件下写入指定的用户名称，并且把vsftpd.conf中userlist_deny配置为YES。

#### 步骤 7：配置用户个性化属性
该目录由vsftpd.conf中user_config_dir指定，目录下的文件名称为要配置的用户的名称。

```
# 虚拟用户的根目录，需要预先建立并赋予相应权限
local_root=/tmp

# 开放虚拟用户的写权限
write_enable=YES

# 开放虚拟用户的下载权限
anon_world_readable_only=NO

#开放虚拟用户的上传权限
anon_upload_enable=YES

# 开放虚拟用户创建目录的权限
anon_mkdir_write_enable=YES

# 禁止虚拟用户删除、重命名目录和文件
anon_other_write_enable=NO

```

#### 步骤 8：重启vsftpd服务
```shell
service vsftpd restart
```

> 权限配置 virtual_use_local_privs参数

```
当virtual_use_local_privs参数为YES时，虚拟用户和本地用户有相同权限；

当virtual_use_local_privs参数为NO时，虚拟用户和匿名用户有相同权限；

当virtual_use_local_privs=YES, write_enable=YES时，虚拟用户的权限：上传、下载、删除、重命名；

当virtual_use_local_privs=NO, write_enable=YES，anon_world_readable_only=YES，anon_upload_enable=YES时，虚拟用户的权限：只能上传文件，不能浏览目录；

当virtual_use_local_privs=NO, write_enable=YES，anon_world_readable_only=NO，anon_upload_enable=YES时，虚拟用户的权限：只能上传、下载文件；

当virtual_use_local_privs=NO, write_enable=YES，anon_world_readable_only=NO，anon_upload_enable=NO时，虚拟用户的权限：只能下载文件；

当virtual_use_local_privs=NO, write_enable=YES，anon_world_readable_only=NO，anon_mkdir_write_enable=YES时，虚拟用户的权限：只能下载文件和创建目录；

当virtual_use_local_privs=NO, write_enable=YES，anon_world_readable_only=NO，anon_other_write_ebable=YES时，虚拟用户的权限：只能下载、删除、重命名文件；
```

---
---

# vsftpd支持的特性

### 一、 用户选项

1. 接受匿名用户  
__**anonymous_enable=YES**__

2. 匿名用户login时不询问口令  
__**no_anon_password=YES**__

3. 匿名用户主目录  
__**anon_root=(none)**__

4. 接受本地用户  
__**local_enable=YES**__

5. 本地用户主目录  
__**local_root=(none)**__

6. 如果匿名用户需要密码,那么使用banned_email_file里面的电子邮件地址的用户不能登录  
__**deny_email_enable=YES**__

7. 仅在没有pam验证版本时有用,是否检查用户有一个有效的shell来登录  
__**check_shell=YES**__

8. 若启用此选项,userlist_deny选项才被启动  
__**userlist_enable=YES**__

9. 若为YES,则userlist_file中的用户将不能登录,为NO则只有userlist_file的用户可以登录  
__**userlist_deny=NO**__

10. 如果和chroot_local_user一起开启,那么用户锁定的目录来自/etc/passwd每个用户指定的目录  
__**passwd_chroot_enable=NO**__

11. 定义匿名登入的使用者名称。默认值为ftp  
__**ftp_username=ftp**__

---

### 二、用户权限控制

1. 可以上传(全局控制)  
__**write_enable=YES**__

2. 本地用户上传文件的umask  
__**local_umask=022**__

3. 上传文件的权限配合umask使用  
__**file_open_mode=0666**__

4. 匿名用户可以上传  
__**anon_upload_enable=YES**__

5. 匿名用户可以建目录  
__**anon_mkdir_write_enable=YES**__

6. 匿名用户其它的写权利  
__**anon_other_write_enable=YES**__

7. 如果设为YES，匿名登入者会被允许下载可阅读的档案  
__**anon_world_readable_only=YES**__

8. 如果开启,那么所有非匿名登陆的用户名都会被切换成guest_username指定的用户名  
__**guest_enable=NO**__

9. 所有匿名上传的文件的所属用户将会被更改成chown_username  
__**chown_uploads=YES**__

10. 匿名上传文件所属用户名  
__**chown_username=lightwiter**__

11. 如果启动这项功能，则所有列在chroot_list_file之中的使用者不能更改根目录  
__**chroot_list_enable=YES**__

12. 允许使用"async ABOR"命令,一般不用,容易出问题  
__**async_abor_enable=NO**__

13. 管控是否可用ASCII模式上传。默认值为NO  
__**ascii_upload_enable=NO**__

14. 管控是否可用ASCII 模式下载。默认值为NO  
__**ascii_download_enable=NO**__

15. 这个选项必须指定一个空的数据夹且任何登入者都不能有写入的权限，当vsftpd 不需要file system 的权限时，就会将使用者限制在此数据夹中  
__**secure_chroot_dir=/usr/share/empty **__

---

### 三、超时设置

1. 空闲连接超时  
__**idle_session_timeout=600**__

2. 数据传输超时  
__**data_connection_timeout=120**__

3. PAVS请求超时  
__**ACCEPT_TIMEOUT=60**__

4. PROT模式连接超时  
__**connect_timeout=60**__

---

### 四、服务器功能选项

1. 开启日记功能  
__**xferlog_enable=YES**__

2. 使用标准格式  
__**xferlog_std_format=YES**__

3. 当xferlog_std_format关闭且本选项开启时,记录所有ftp请求和回复,当调试比较有用  
__**log_ftp_protocol=NO**__

4. 允许使用pasv模式  
__**pasv_enable=YES**__

5. 关闭安全检查  
__**pasv_promiscuous=YES**__

6. 允许使用port模式  
__**port_enable=YES**__

7. 关闭安全检查  
__**prot_promiscuous=YES**__

8. 开启tcp_wrappers支持  
__**tcp_wrappers=YES**__

9. 定义PAM 所使用的名称，预设为vsftpd  
__**pam_service_name=vsftpd**__

10. 当服务器运行于最底层时使用的用户名  
__**nopriv_user=nobody**__

11. 使vsftpd在pasv命令回复时跳转到指定的IP地址  
__**pasv_address=(none)**__

---

### 五、服务器性能选项

1. 是否能使用ls -R命令以防止浪费大量的服务器IO资源  
__**ls_recurse_enable=YES**__

2. 是否使用单进程模式  
__**one_process_model=YES**__

3. 绑定到listen_port指定的端口  
__**listen=YES**__

4. 当使用者登入后使用ls -al之类的指令查询该档案的管理权时，预设会出现拥有者的UID，而不是该档案拥有者的名称。若是希望出现拥有者的名称，则将此功能开启  
__**text_userdb_names=NO**__

5. 显示目录清单时是用本地时间还是GMT时间,可以通过mdtm命令来达到一样的效果  
__**use_localtime=NO**__

6. 测试平台优化  
__**use_sendfile=YES**__

---

### 六、信息类设置

1. login时显示欢迎信息.如果设置了banner_file则此设置无效  
__**ftpd_banner=Welcome to blah FTP service.**__

2. 允许为目录配置显示信息,显示每个目录下面的message_file文件的内容  
__**dirmessage_enable=YES**__

3. 显示会话状态信息  
__**setproctitle_enable=YES**__

---

### 七、文件定义

1. 定义不能更改用户主目录的文件  
__**chroot_list_file=/etc/vsftpd/vsftpd/chroot_list**__

2. 定义限制/允许用户登录的文件  
__**userlist_file=/etc/vsftpd/vsftpd/user_list**__

3. 定义登录信息文件的位置  
__**banner_file=/etc/vsftpd/banner**__

4. 禁止使用的匿名用户登陆时作为密码的电子邮件地址  
__**banned_email_file=/etc/vsftpd/banned_emails**__

5. 日志文件位置  
__**xferlog_file=/var/log/vsftpd.log**__

6. 目录信息文件  
__**message_file=.message**__

---

### 八、目录定义

1. 定义用户配置文件的目录  
__**user_config_dir=/etc/vsftpd/userconf**__

2. 定义本地用户登陆的根目录,注意定义根目录可以是相对路径也可以是绝对路径.相对路径是针对用户家目录来说的  
__**local_root=webdisk**__

3. 此项设置每个用户登陆后其根目录  
__**/home/username/webdisk**__

4. 匿名用户登陆后的根目录  
__**anon_root=/var/ftp**__

---

### 九、用户连接选项

1. 可接受的客户端的最大连接数目  
__**max_clients=100**__

2. 每个IP的客户端最大连接数目  
__**max_per_ip=5**__

3. 使用标准的20端口来连接ftp  
__**connect_from_port_20=YES**__

4. 绑定到某个IP,其它IP不能访问  
__**listen_address=192.168.0.2**__

5. 指定连接请求控制端口  
__**listen_port=2121**__

6. 指定数据传输端口  
__**ftp_data_port=2020**__

7. pasv连接模式时可以使用port范围的上界，0 表示任意  
__**pasv_max_port=0**__

8. pasv连接模式时可以使用port 范围的下界，0 表示任意  
__**pasv_min_port=0**__

---

###  十、数据传输选项

1. 匿名用户的传输比率(b/s)  
__**anon_max_rate=51200**__

2. 本地用户的传输比率(b/s)  
__**local_max_rate=512000**__

---
