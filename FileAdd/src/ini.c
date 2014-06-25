/**
 ******************************************************************************
 * @file      ini.c
 * @brief     C Source file of ini.c.
 * @details   This file including all API functions's 
 *            implement of ini.c.	
 *
 * @copyright
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "iniparser.h"
#include "ini.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   创建默认配置文件
 * @param[in]  None
 * @param[out] None
 * @retval     None
 ******************************************************************************
 */
static void
create_example_ini_file(void)
{
    FILE    *   ini ;

    ini = fopen(DEFAULT_INI_FILE, "w");
    fprintf(ini,
            "#文件数据修改配置By LiuNing\n"
            "[cfg]\n"
            "#是否记录日志(0:不记录1:记录)\n"
            "IsLog = 0\n"
            "#日志文件名\n"
            "LogFile = ./FileAdd.log\n"
            "#文件中每个字节增加的值(减运算可以转换为加运算)\n"
            "AddValue = 0x33\n"
            "#输入文件名\n"
            "InFile = ./in.bin\n"
            "#输出文件名\n"
            "OutFile = ./out.bin\n");
    fclose(ini);
}

/**
 ******************************************************************************
 * @brief   从配置文件中获取文件合并信息
 * @param[out] *pinfo   : 返回info
 *
 * @retval     -1 失败
 * @retval      0 成功
 ******************************************************************************
 */
int
ini_get_info(fileadd_ini_t *pinfo)
{
    dictionary  *   ini ;
    char *pstr = NULL;

    memset(pinfo, 0x00, sizeof(*pinfo));

    ini = iniparser_load(DEFAULT_INI_FILE);
    if (NULL == ini)
    {
        create_example_ini_file();
        ini = iniparser_load(DEFAULT_INI_FILE);
        if (ini == NULL)
        {
            return -1;
        }
    }

    iniparser_dump(ini, NULL);//stderr

    pinfo->islog = iniparser_getint(ini, "cfg:IsLog", -1);
    if (pinfo->islog == -1)
    {
        iniparser_freedict(ini);
        return -1;
    }
    pstr = iniparser_getstring(ini, "cfg:LogFile", NULL);
    if (pstr == NULL)
    {
        iniparser_freedict(ini);
        return -1;
    }
    strncpy(pinfo->logfile, pstr, sizeof(pinfo->logfile));

    pinfo->addValue = iniparser_getint(ini, "cfg:AddValue", -1);
    if (pinfo->addValue == -1)
    {
        iniparser_freedict(ini);
        return -1;
    }
    pinfo->addValue &= 0xff;

    pstr = iniparser_getstring(ini, "cfg:InFile", NULL);
    if (pstr == NULL)
    {
        strncpy(pinfo->infile, DEFAULT_IN_FILE, sizeof(pinfo->infile));
    }
    else
    {
        strncpy(pinfo->infile, pstr, sizeof(pinfo->infile));
    }

    pstr = iniparser_getstring(ini, "cfg:OutFile", NULL);
    if (pstr == NULL)
    {
        strncpy(pinfo->outfile, DEFAULT_OUT_FILE, sizeof(pinfo->outfile));
    }
    else
    {
        strncpy(pinfo->outfile, pstr, sizeof(pinfo->outfile));
    }

    iniparser_freedict(ini);

    return 0;
}
/*----------------------------ini.c--------------------------------*/
