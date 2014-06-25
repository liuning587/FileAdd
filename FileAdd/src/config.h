/**
 ******************************************************************************
 * @file       config.h
 * @brief      配置文件
 * @details    This file including all API functions's declare of config.h.
 * @copyright
 *
 ******************************************************************************
 */
#ifndef CONFIG_H_
#define CONFIG_H_ 

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
#define DEFAULT_MAX_FILE        (5u)                /**< 最大文件合并数量 */
#define DEFAULT_INI_FILE        "./FileAdd.ini"     /**< 默认配置文件 */
#define DEFAULT_OUT_FILE        "./out.bin"         /**< 处理后文件 */
#define DEFAULT_IN_FILE         "./in.bin"          /**< app文件 */

#define DEFAULT_LOG_ON          (1u)                /**< 默认打开日志记录 */
#define DEFAULT_LOG_FILE_NAME   "./FileAdd.log"     /**< 默认日志文件 */

#endif /* CONFIG_H_ */
/*-----------------------------End of config.h-------------------------------*/
