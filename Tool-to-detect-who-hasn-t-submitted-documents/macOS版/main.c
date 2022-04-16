//
// Created by hao_g on 2020/3/30.
//

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include <unistd.h>


int str_cmp_name(char *,char*);


//int str_partition(char *name,char *d_nameo)

int str_partition(char *f_buf)

{
    char * tmp;//字符指针用于标记字符开始位置
    char seps1[]=",";//英文分隔符(建议用英文分隔符，不然会出现分割错误，如"开"字会被分解)
    char seps2[]="，";//中文分隔符

    //char f_buf[] = "李小明李大明";

    char name[30] = "";

    //-----------------------------目录IO
    DIR *dp,*dpn;//目录指针
    struct dirent *sp,*spn=NULL;//目录结构体指针
    int n=0;//存放文件个数
    int no_pay=0;//存放未提交人数
    int list=0;//存放人员名单人数

    dpn=opendir("./提交文件夹");//打开目录的地址给dp
    if(dpn!=NULL)
    {
        while (1)//判断里面有几个正常的普通文件
        {
            spn = readdir(dpn);//把读到目录结构体地址给sp；readdir每读一次会移动到下一个目录的结构体地址
            if (spn == NULL) {
                break;
            }

            if (spn->d_name[0] == '.' || spn->d_type == 4)//忽略开头是.的文件和文件夹
            {
                continue;
            }
            n++;
        }
        printf("已交文件：%d个\n", n);
    }
    else
    {
        printf("打开目录失败，请在程序同级目录下新建\"提交文件夹\"目录放检测文件\n");
    }




    printf("未交名单：");

    for(int i=0;i<strlen(f_buf)&&i<3000;i++)//检测分隔符是seps1还是seps2。
    {
        if (strncmp(&f_buf[i], seps1, 1) == 0||strncmp(&f_buf[i], seps2, 1) == 0)
        {
            if (strncmp(&f_buf[i], seps1, 1) == 0)
            {

                tmp = strtok(f_buf, seps1);
                if(tmp!=0)
                {
                    list++;
                    strcpy(name, tmp);
                }
                dp=opendir("./提交文件夹");//--------------tmp分割头部开始的部分
                while (1)
                {
                    if(dp!=NULL)
                    {
                        sp=readdir(dp);
                        if(sp==NULL)
                        {
                            printf("%s、",name);
                            no_pay++;
                            break;
                        }
                        if(sp->d_name[0]=='.'||sp->d_type==4)//忽略开头是.的文件和文件夹
                            continue;
                        if(str_cmp_name(name,sp->d_name)==0)
                        {
                            break;
                        }


                    }
                }

                while(1)
                {
                    list++;
                    tmp = strtok(NULL, seps1);
                    if(tmp!=0)
                    {
                        strcpy(name, tmp);
                        dp=opendir("./提交文件夹");//--------------tmp分割剩下的部分
                        while (1)
                        {
                            if(dp!=NULL)
                            {
                                sp=readdir(dp);
                                if(sp==NULL)
                                {
                                    printf("%s、",name);
                                    no_pay++;
                                    break;
                                }
                                if(sp->d_name[0]=='.'||sp->d_type==4)//忽略开头是.的文件和文件夹
                                    continue;
                                if(str_cmp_name(name,sp->d_name)==0)
                               {
                                   break;
                               }


                            }
                        }
                      //  printf("name=%s\n",name);
                    }
                    else
                    {
                        printf("\n未交人数：%d\n",no_pay);
                        printf("人员名单：%d人\n",list-1);
                        return 0;
                    }
                }
            }

            if (strncmp(&f_buf[i], seps2, 2) == 0)
            {

                tmp = strtok(f_buf, seps2);
                if(tmp!=0)
                {
                    list++;
                    strcpy(name, tmp);
                }
                dp=opendir("./提交文件夹");//--------------tmp分割头部开始的部分
                while (1)
                {
                    if(dp!=NULL)
                    {
                        sp=readdir(dp);
                        if(sp==NULL)
                        {
                            printf("%s、",name);
                            no_pay++;
                            break;
                        }
                        if(sp->d_name[0]=='.'||sp->d_type==4)//忽略开头是.的文件和文件夹
                            continue;
                        if(str_cmp_name(name,sp->d_name)==0)
                        {
                            break;
                        }


                    }
                }


                while(1)
                {
                    tmp = strtok(NULL, seps1);
                    if(tmp!=0)
                    {
                        list++;
                        strcpy(name, tmp);
                        dp=opendir("./提交文件夹");//--------------tmp分割剩下的部分
                        while (1)
                        {
                            if(dp!=NULL)
                            {
                                sp=readdir(dp);
                                if(sp==NULL)
                                {
                                    printf("%s、",name);
                                    no_pay++;
                                    break;
                                }
                                if(sp->d_name[0]=='.'||sp->d_type==4)//忽略开头是.的文件和文件夹
                                    continue;
                                if(str_cmp_name(name,sp->d_name)==0)
                                {
                                    break;
                                }


                            }
                        }
                        //  printf("name=%s\n",name);
                    }
                    else
                    {
                        printf("\n未交人数：%d\n",no_pay);
                        printf("人员名单：%d人\n",list-1);
                        return 0;
                    }
                }
            }
        }
    }

    printf("未找到分隔符：\"，\"或\",\"\n");
    return -1;


}



int str_cmp_name(char *st,char *st2)//st短名字（人员名单） st2长名字（提交的作业名字）return_0:表示名字匹配 return_-1:表示名字不匹配
{
    for(int i=0;i<strlen(st2)-(strlen(st)-1);i++)
    {
        if(strlen(st2)<strlen(st))
            break;
        if(strncmp(st,&st2[i],strlen(st))==0)
            return 0;
    }
    return -1;
}



int main(int argc,char * argv[])
{
    //----------------------------------------------------
    //printf("本程序路径：%s\n",argv[0]);
    //本程序路径其实保存在argv[0]中，而chdir只需要目录，下面是去掉程序名，留目录。
    char buf[500]={0};
    int i;
    strcpy(buf,argv[0]);
    for(i=strlen(buf);buf[i]!='/';i--)
    {
        continue;
    }
    buf[i]='\0';
    chdir(buf);
    printf("本程序路径：%s\n",buf);
    //----------------------------------------------------


    char f_buf[5000];
    bzero(f_buf, sizeof(f_buf));
    FILE *fp=fopen("./人员名单.txt","r");
    if(fp!=NULL)
    {
        fread(f_buf,1, sizeof(f_buf),fp);
        str_partition(f_buf);
        printf("\n");
    }

    else
    {
     printf("程序目录没有\"人员名单.txt\"");
    }

    return 0;
}