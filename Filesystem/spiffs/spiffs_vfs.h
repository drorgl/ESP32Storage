/*
 * spiffs VFS public function
 *
 * Author: LoBo (loboris@gmail.com / https://github.com/loboris)
 *
 * Part of this code is copied from or inspired by LUA-RTOS_ESP32 project:
 *
 * https://github.com/whitecatboard/Lua-RTOS-ESP32
 * IBEROXARXA SERVICIOS INTEGRALES, S.L. & CSS IBÉRICA, S.L.
 * Jaume Olivé (jolive@iberoxarxa.com / jolive@whitecatboard.org)
 *
 */
#define LOG_LOCAL_LEVEL  ESP_LOG_VERBOSE

#define SPIFFS_BASE_PATH "/spiffs"

//
//#define CONFIG_SPIFFS_BASE_ADDR 0x290000
//#define CONFIG_SPIFFS_SIZE 131072
//#define CONFIG_SPIFFS_LOG_BLOCK_SIZE 8192
//#define CONFIG_SPIFFS_LOG_PAGE_SIZE 256

extern int spiffs_is_registered;
extern int spiffs_is_mounted;

void vfs_spiffs_register(uint32_t phys_addr, uint32_t phys_size, uint32_t log_page_size, uint32_t log_block_size, uint32_t erase_size);
int spiffs_format();
int spiffs_mount();
int spiffs_unmount(int unreg);
void spiffs_fs_stat(uint32_t *total, uint32_t *used);
