#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	DIR *dirp;
	struct dirent *direntp;
	struct stat stat_buf;
	char *str;
	
	if (argc != 2) {
		// fprintf() : prints to the given output stream
		// stderr : stream for printing diagnostic or error messages.
		// is referred to as 'standard error'
		fprintf(stderr, "usage : %s dir_name\n", argv[0]);
		exit(1);
	}

	// DIR *opendir(const char *name)
	// opens a directory stream corresponding to the directory name and returs a pointer to the directory stream
	if ((dirp = opendir(argv[1])) == NULL) {
		perror(argv[1]);
		exit(2);
	}

	// #include <dirent.h>
	// struct dirent *readdir(DIR *dirp)
	// readdir() : returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp
	// it returns NULL on reaching the end of the directory stream or if an error ocurred
	// on Linux the dirent structure is defined as follows :
	// struct dirent {
	//     ino_t d_ino : inode number
	//     off_t d_off : not an offset
	//     unsigned short d_reclen : length of this record
	//     unsigned char d_type : type of file; not supported by all filesystem types
	//     char d_name[256] : filename
	// };
	while ((direntp = readdir(dirp)) != NULL) {
		// int lstat(const char *path, struct stat *buf)
		// stat() : stats the file pointed to by path and fills in buff
		// lstat() : is identical to stat() expect that if path is a symbolic link, then the link itself is stat-ed, not the file that it refers to
		// returns a stat structure :
		// struct stat {
		//     dev_t st_dev : ID of device containing file
		//     ino_t st_ino : inode number
		//	   mode_t st_mode : protection
		//     nlink_t st_nlink : number of hard links
		//     uid_t st_uid : user ID of owner
		// 	   gid_t st_gid : group ID of owner
		//     dev_t st_rdev : devide ID (if special file)
		// 	   off_t st_size : total size, in bytes
		//     blksize_t st_blksize : blocksize for filesystem I/O
		//     blkcnt_t st_blocks : number of 512B blocks allocated
		//     time_t st_atime : time of last access
		//     time_t st_mtime : time of last modification
		// 	   time_t st_ctime : time of last status change
		// };
		if ((lstat(direntp->d_name, &stat_buf)) == -1) {
			perror("lstat ");
			exit(3);
		}
		// S_ISREG() : returns true if regular file
		// S_ISDIR() : returns true if directory
		if (S_ISREG(stat_buf.st_mode)) str = "regular";
		else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
		else str = "other";
		printf("%-25s - %s\n", direntp->d_name, str);
	}

	// int closedir(DIR *dirp)
	// closedir() : closes the directory stream associated with dirp
	closedir(dirp);
	exit(0);
}
