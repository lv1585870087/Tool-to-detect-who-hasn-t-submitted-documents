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
    char * tmp;//�ַ�ָ�����ڱ���ַ���ʼλ��
    char seps1[]=",";//Ӣ�ķָ���(������Ӣ�ķָ�������Ȼ����ַָ������"��"�ֻᱻ�ֽ�)
    char seps2[]="��";//���ķָ���

    //char f_buf[] = "��С�������";

    char name[30] = "";

    //-----------------------------Ŀ¼IO
    DIR *dp,*dpn;//Ŀ¼ָ��
    struct dirent *sp,*spn=NULL;//Ŀ¼�ṹ��ָ��
    int n=0;//����ļ�����
    int no_pay=0;//���δ�ύ����
    int list=0;//�����Ա��������

    dpn=opendir("./�ύ�ļ���");//��Ŀ¼�ĵ�ַ��dp
    if(dpn!=NULL)
    {
        while (1)//�ж������м�����������ͨ�ļ�
        {
            spn = readdir(dpn);//�Ѷ���Ŀ¼�ṹ���ַ��sp��readdirÿ��һ�λ��ƶ�����һ��Ŀ¼�Ľṹ���ַ
            if (spn == NULL) {
                break;
            }

            if (spn->d_name[0] == '.' || spn->d_type == 4)//���Կ�ͷ��.���ļ����ļ���
            {
                continue;
            }
            n++;
        }
        printf("�ѽ��ļ���%d��\n", n);
    }
    else
    {
        printf("��Ŀ¼ʧ�ܣ����ڳ���ͬ��Ŀ¼���½�\"�ύ�ļ���\"Ŀ¼�ż���ļ�\n");
    }




    printf("δ��������");

    for(int i=0;i<strlen(f_buf)&&i<3000;i++)//���ָ�����seps1����seps2��
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
                dp=opendir("./�ύ�ļ���");//--------------tmp�ָ�ͷ����ʼ�Ĳ���
                while (1)
                {
                    if(dp!=NULL)
                    {
                        sp=readdir(dp);
                        if(sp==NULL)
                        {
                            printf("%s��",name);
                            no_pay++;
                            break;
                        }
                        if(sp->d_name[0]=='.'||sp->d_type==4)//���Կ�ͷ��.���ļ����ļ���
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
                        dp=opendir("./�ύ�ļ���");//--------------tmp�ָ�ʣ�µĲ���
                        while (1)
                        {
                            if(dp!=NULL)
                            {
                                sp=readdir(dp);
                                if(sp==NULL)
                                {
                                    printf("%s��",name);
                                    no_pay++;
                                    break;
                                }
                                if(sp->d_name[0]=='.'||sp->d_type==4)//���Կ�ͷ��.���ļ����ļ���
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
                        printf("\nδ��������%d\n",no_pay);
                        printf("��Ա������%d��\n",list-1);
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
                dp=opendir("./�ύ�ļ���");//--------------tmp�ָ�ͷ����ʼ�Ĳ���
                while (1)
                {
                    if(dp!=NULL)
                    {
                        sp=readdir(dp);
                        if(sp==NULL)
                        {
                            printf("%s��",name);
                            no_pay++;
                            break;
                        }
                        if(sp->d_name[0]=='.'||sp->d_type==4)//���Կ�ͷ��.���ļ����ļ���
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
                        dp=opendir("./�ύ�ļ���");//--------------tmp�ָ�ʣ�µĲ���
                        while (1)
                        {
                            if(dp!=NULL)
                            {
                                sp=readdir(dp);
                                if(sp==NULL)
                                {
                                    printf("%s��",name);
                                    no_pay++;
                                    break;
                                }
                                if(sp->d_name[0]=='.'||sp->d_type==4)//���Կ�ͷ��.���ļ����ļ���
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
                        printf("\nδ��������%d\n",no_pay);
                        printf("��Ա������%d��\n",list-1);
                        return 0;
                    }
                }
            }
        }
    }

    printf("δ�ҵ��ָ�����\"��\"��\",\"\n");
    return -1;


}



int str_cmp_name(char *st,char *st2)//st�����֣���Ա������ st2�����֣��ύ����ҵ���֣�return_0:��ʾ����ƥ�� return_-1:��ʾ���ֲ�ƥ��
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
    //printf("������·����%s\n",argv[0]);
    //������·����ʵ������argv[0]�У���chdirֻ��ҪĿ¼��������ȥ������������Ŀ¼��
    char buf[500]={0};
    int i;
    strcpy(buf,argv[0]);
    for(i=strlen(buf);buf[i]!='/';i--)
    {
        continue;
    }
    buf[i]='\0';
    chdir(buf);
    printf("������·����%s\n",buf);
    //----------------------------------------------------


    char f_buf[5000];
    bzero(f_buf, sizeof(f_buf));
    FILE *fp=fopen("./��Ա����.txt","r");
    if(fp!=NULL)
    {
        fread(f_buf,1, sizeof(f_buf),fp);
        str_partition(f_buf);
        printf("\n");
    }

    else
    {
     printf("����Ŀ¼û��\"��Ա����.txt\"");
    }
	scanf("%d",buf);

    return 0;
}