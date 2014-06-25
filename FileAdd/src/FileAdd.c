/*
 ============================================================================
 Name        : FileAdd.c
 Author      : liuning
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log.h"
#include "ini.h"

#define BUF_SIZE            (1024)

int main(void) {
    fileadd_ini_t fai;
    char buf[BUF_SIZE];
    FILE* fdest = NULL;
    FILE* fcur = NULL;
    int file_size = 0;
    int write_size = 0;
    int len = 0;
    int i;

    puts("!!! FileAdd by LiuNing !!!");

    /* 0. ��ʼ������ */
    if (0 != ini_get_info(&fai))
    {
        printf("ini get info err!\n");
        goto mainend;
    }

    /* 1. �������ļ� */
    fcur = fopen(fai.infile, "rb");
    if (fcur == NULL)
    {
        printf("%s������!\n", fai.infile);
        goto mainend;
    }

    /* 2. ��������ļ� */
    fdest = fopen(fai.outfile, "w+b");
    if (fdest == NULL)
    {
        printf("�����ļ�%sʧ��!\n", fai.outfile);
        goto mainend;
    }

    /* 3. ת���ļ� */
    fseek(fcur, 0, SEEK_END);
    file_size = ftell(fcur);
    write_size = 0;
    fseek(fcur, 0, SEEK_SET);
    while (write_size < file_size)
    {
        len = fread(buf, 1, BUF_SIZE, fcur);

        /* ��ÿһ�ֽ�������ֵ */
        for (i = 0; i < len; i++)
        {
            buf[i] = (char)((unsigned char)buf[i] + fai.addValue);
        }

        if ((len <= 0) || (len != fwrite(buf, 1, len, fdest)))
        {
           printf("д�ļ�����[L%d]!\n", __LINE__);
           goto mainend;
        }
        write_size += len;
    }
    printf("ת���ɹ���\n");

mainend:
    if (fdest != NULL)
    {
        fclose(fdest);
    }
    if (fcur != NULL)
    {
        fclose(fcur);
    }

    printf("��������˳�������\n");
    getch();
    return EXIT_SUCCESS;
}
