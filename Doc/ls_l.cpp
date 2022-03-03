#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<pwd.h>	//struct passwd * getpwuid()
#include<grp.h>	//getgrgid()
#include<time.h> //ctime()
#include<string.h>
using namespace std;
//模拟实现 ls -l
int main(int argc, char * argv[]){
	
	//判断输入参数是否正确
	if(argc < 2){
		printf("%s filename\n",argv[0]);
		return -1;
	}
	
	//通过stat获取文件信息
	struct stat st;
	int ret = stat(argv[1],&st);
	if(ret==-1){
		perror("stat");
		return -1;
	}

	char perms[11] = {0};//存储文件信息
	
	//获取文件类型和文件权限
	switch(st.st_mode & S_IFMT){
		case S_IFLINK : //linkage
			perms[0] = 'l';
			break;
		case S_IFDIR : //dictionary
			perms[0] = 'd';
			break;
		case S_IFREG : //regular
			perms[0] = '-';
			break;
		case S_IFBLK : //block
			perms[0] = 'b';
			break;
		case S_IFCHR : //char 
			perms[0] = 'c';
			break;
		case S_IFSOCK : 
			perms[0] = 's';
			break;
		case S_IFIFO : //pipe
			perms[0] = 'p';
			break;
		default:
			perms[0] = '?';
	}
	
	//文件所有者
	perms[1] = st.st_mode & S_IRUSR ? 'r':'-';
	perms[2] = st.st_mode & S_IWUSR ? 'w':'-';
	perms[3] = st.st_mode & S_IXUSR ? 'x':'-';
	//文件所在组
	perms[4] = st.st_mode & S_IRGRP ? 'r':'-';
	perms[5] = st.st_mode & S_IWGRP ? 'w':'-';
	perms[6] = st.st_mode & S_IXGRP ? 'x':'-';
	//other
	perms[7] = st.st_mode & S_IROTH ? 'r':'-';
	perms[8] = st.st_mode & S_IWOTH ? 'w':'-';
	perms[9] = st.st_mode & S_IXOTH ? 'x':'-';
	
	//硬链接树
	int linkNum = st.st_nlink;
	
	//文件所有者
	char * fileUser = getpwuid(st.st_uid) -> pw_name;
	
	//文件所在组
	char * fileGroup = getgrgid(st.st_gid)->gr_name;
	
	//文件大小
	long int fileSize = st.st_size;
	
	//获取修改时间
	char * time = ctime(&st.st_mtime);//自带回车
	//去掉回车
	char mtime[512] = {0};
	strncpy(mtime, time,strlen(time)-1);
	
	char buf[1024];
	sprintf(buf,"%s %d %s %s %d %s %s",perms,linkNum,fileUser,fileGroup,fileSize,time,argv[1]);
	printf("%s\n",buf);
	
	return 0;	
}
