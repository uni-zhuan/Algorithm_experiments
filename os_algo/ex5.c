#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define TIME_STRING_LEN 50
//获取时间
char *time2String(time_t tm, char *buf)
{
    struct tm *local;
    local = localtime(&tm);                      //获取时间
    strftime(buf, TIME_STRING_LEN, "%c", local); //格式化时间
    return buf;
}
//显示文件信息
int ShowFileInfo(char *file)
{
    struct stat buf;
    char timeBuf[TIME_STRING_LEN];
    if (lstat(file, &buf)) // lstat执行失败
    {
        perror("lstat() error");
        return 1;
    }
    printf("\nFile:%s\n", file); //文件名
    printf("On device(major/minor):%d %d,inode number:%ld\n",
           major(buf.st_dev), minor(buf.st_dev), buf.st_ino);
    printf("Size:%ld\t Type: %07o\t Permission:%05o\n", buf.st_size, buf.st_mode & S_IFMT, buf.st_mode & ~(S_IFMT));
    printf("Ower id:%d\t Group id:%d\t Number of hard links:%d\n", buf.st_uid, buf.st_gid, buf.st_nlink);
    printf("Last access:%s\n", time2String(buf.st_atime, timeBuf));
    printf("Last modify inode:%s\n\n", time2String(buf.st_atime, timeBuf));
    return 0;
}
int main(int argc, char *argv[])
{
    int i, ret;
    for (i = 1; i < argc; i++)
    {
        ret = ShowFileInfo(argv[i]);
        if (argc - i > 1)
            printf("\n");
    }
    return ret;
}

/*系统保持每一个用户进程的相关的虚拟地址,这些地址可以通过引用外部变量 etext,edata,end 来获得*/
// 在链接过程中，链接器ld和ld86会使用变量记录下执行程序中每个段的逻辑地址。因此在程序中可以通过访问这几个外部变量来获得程序中段的位置。链接器预定义的外部变量通常至少有etext、_etext、edata、_edata、end和_end。
// 变量名_etext和etext的地址是程序正文段结束后的第1个地址；_edata和edata的地址是初始化数据区后面的第1个地址；end和end的地址是未初始化数据区（bss）后的第1个地址位置。
#include <stdio.h>
extern int etext, edata, end; /*对应文本的第一有效地址、初始化的数据*/
main()
{
    printf("etext:%6x \t edata:%6x \t end:%6x \n", &etext, &edata, &end);
}
/*Print the address of program text, the adderess of data area, etc*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define SHW_ADR(ID, I) printf("The id %s \t is at adr:%8X\n", ID, &I);
extern int etext, edata, end;
char *cptr = "Hello World.\n";
char buffer1[25];
main()
{
    void showit(char *);
    int i = 0;
    printf("Adr etext:%8x\t Adr edata:%8x Adr end:%8x\n\n", &etext, &edata, &end);
    SHW_ADR("main", main);
    SHW_ADR("showit", showit);
    SHW_ADR("cptr", cptr);
    SHW_ADR("buffer1", buffer1);
    SHW_ADR("i", i);
    strcpy(buffer1, "A demonstration\n");
    write(1, buffer1, strlen(buffer1) + 1);
    for (; i < 1; ++i)
        showit(cptr);
}
Void showit(char *p)
{
    char *buffer2;
    SHW_ADR("buffer2", buffer2);
    if ((buffer2 = (char *)malloc((unsigned)(strlen(p) + 1))) != NULL)
    {
        strcpy(buffer2, p);
        printf("%s", buffer2);
        free(buffer2);
    }
    else
    {
        printf("Allocation error.\n");
        exit(1);
    }
}

/*Open the file and put the line into screen*/
/*Command format: ./command filename */
#include <sys/types.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    char s[1024];
    FILE *fp;
    if ((fp = fopen(argv[1], "r")) != (FILE *)0) /*打开参数 1 指定的文件*/
    {
        while ((fgets(s, 1024, fp)) != (char *)0)
            puts(s); /*显示缓冲区*/
    }
    else
    {
        fprintf(stderr, "file open error.\n");
        exit(1);
    }
    exit(0);
}

clude<string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

    int main(int argc, char *argv[])
{
    char s[1024];
    FILE *fp1, *fp2, *fp3;
    if (((fp1 = fopen(argv[1], "r")) != (FILE *)0) && ((fp2 = fopen(argv[2], "r")) != (FILE *)0) && ((fp3 = fopen(argv[3], "w")) != (FILE *)0))
        if (((fp1 = fopen(argv[1], "r")) != (FILE *)0) && ((fp2 = fopen(argv[2], "r")) != (FILE *)0) && ((fp3 = fopen(argv[3], "w")) != (FILE *)0)) /*打开参数指定的文件*/
        {
            while ((fgets(s, 1024, fp1)) != (char *)0)
                write(argv[3], s, 1024);
            while ((fgets(s, 1024, fp2)) != (char *)0)
                write(argv[3], s, 1024);
            fchmod(fd3, 0777);
            while ((fgets(s, 1024, fp3)) != (char *)0)
                puts(s);
        }
        else
        {
            fprintf(stderr, "file open error.\n");
            exit(1);
        }
    exit(0);
}

#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    char s[1024];
    FILE *fp1, *fp2, *fp3;
    if (((fp1 = fopen(argv[1], "r")) != (FILE *)0) && ((fp2 = fopen(argv[2], "r")) != (FILE *)0) && ((fp3 = fopen(argv[3], "w")) != (FILE *)0)) /*打开参数指定的文件*/
    {
        fprintf(stderr, "ok");
        while ((fgets(s, 1024, fp1)) != (char *)0)
            fwrite(s, 1024, 1, fp3);
        while ((fgets(s, 1024, fp2)) != (char *)0)
            fwrite(s, 1024, 1, fp3);
        fchmod(fp3, 0711);
        while ((fgets(s, 1024, fp3)) != (char *)0)
            puts(s);
    }
    else
    {
        fprintf(stderr, "file open error.\n");
        exit(1);
    }
    exit(0);
}