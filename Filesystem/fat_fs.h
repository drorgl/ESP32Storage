#ifndef _FAT_FILESYSTEM_H_
#define _FAT_FILESYSTEM_H_

#include "IFilesystem.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "esp_vfs.h"
#include "custom_vfs_fat.h"
//extern "C" {
//
//}
static const char *TAG = "fat_fs";

class FATFilesystem : public IFilesystem {
private:
	const char *base_path = "/spiffs";

	//FATFS *_fs;

	// Handle of the wear levelling library instance
	wl_handle_t s_wl_handle = WL_INVALID_HANDLE;
public:
	virtual int init() {
		ESP_LOGI(TAG, "Mounting FAT filesystem");
		// To mount device we need name of device partition, define base_path
		// and allow format partition in case if it is new one and was not formated before
		esp_vfs_fat_mount_config_t mount_config;
		mount_config.max_files = 4;
		mount_config.format_if_mount_failed = true;

		esp_err_t err = custom_esp_vfs_fat_spiflash_mount(base_path, "spiffs", &mount_config, &s_wl_handle);
		if (err != ESP_OK) {
			ESP_LOGE(TAG, "Failed to mount FATFS (0x%x)", err);
			return -1;
		}

		return 0;
	}

	virtual int format() {
		esp_vfs_fat_mount_config_t mount_config;
		mount_config.max_files = 4;
		mount_config.format_if_mount_failed = true;

		esp_err_t err = custom_esp_vfs_fat_spiflash_format(base_path, "spiffs", &mount_config, &s_wl_handle);
		if (err != ESP_OK) {
			ESP_LOGE(TAG, "Failed to format FATFS (0x%x)", err);
			return -1;
		}

		return 0;

		//init();

		//ESP_LOGI(TAG, "Formatting FATFS partition");
		//BYTE pdrv = 0xFF;
		//if (ff_diskio_get_drive(&pdrv) != ESP_OK) {
		//	ESP_LOGD(TAG, "the maximum count of volumes is already mounted");
		//	return ESP_ERR_NO_MEM;
		//}
		//ESP_LOGD(TAG, "using pdrv=%i", pdrv);
		//char drv[3] = { (char)('0' + pdrv), ':', 0 };

		//auto result = ff_diskio_register_wl_partition(pdrv, s_wl_handle);
		//if (result != ESP_OK) {
		//	ESP_LOGE(TAG, "ff_diskio_register_wl_partition failed pdrv=%i, error - 0x(%x)", pdrv, result);
		//	return -2;
		//}

		//const size_t workbuf_size = 4096;
		//auto workbuf = malloc(workbuf_size);

		//auto fresult = f_mkfs(drv, FM_ANY | FM_SFD, workbuf_size, workbuf, workbuf_size);
		//if (fresult != FR_OK) {
		//	//result = ESP_FAIL;
		//	ESP_LOGE(TAG, "f_mkfs failed (%d)", fresult);

		//	ff_diskio_unregister(pdrv);
		//	//// release partition driver
		//	//esp_err_t err_drv = wl_unmount(s_wl_handle);
		//	free(workbuf);
		//	return -1;
		//}

		//ff_diskio_unregister(pdrv);
		////// release partition driver
		////esp_err_t err_drv = wl_unmount(s_wl_handle);
		//free(workbuf);
		//deinit();
		//return 0;
	}

	virtual int deinit() {
		// Unmount FATFS
		ESP_LOGI(TAG, "Unmounting FAT filesystem");
		ESP_ERROR_CHECK(custom_esp_vfs_fat_spiflash_unmount(base_path, &s_wl_handle));

		ESP_LOGI(TAG, "Done");
	}

	virtual long get_size() {
		FATFS *fs;
		DWORD nclast;

		f_getfree(base_path, &nclast, &fs);

		/*printf("fs %d\r\n", nclast);
		printf("FS: %d, %d, %d, %d, %d \r\n",
			fs->csize,
			fs->ssize,
			fs->free_clst,
			fs->fsize,
			fs->n_fatent
		);*/

		return fs->ssize * (fs->n_fatent - 2);
	}
	virtual long get_available() {
		FATFS *fs;
		DWORD nclast;

		f_getfree(base_path, &nclast, &fs);

		/*printf("fs %d\r\n", nclast);
		printf("FS: %d, %d, %d, %d, %d \r\n",
			fs->csize,
			fs->ssize,
			fs->free_clst,
			fs->fsize,
			fs->n_fatent
		);*/

		return fs->ssize * fs->free_clst;
	}

	
	// Mount path for the partition
	//

	//void append_data() {
	//	ESP_LOGD(TAG, "Appending data");
	//	FILE *f = fopen("/spiffs/test.txt", "a");
	//	if (f == NULL) {
	//		ESP_LOGE(TAG, "Failed to open file for writing");
	//		return;
	//	}
	//	fprintf(f, "message\r\n");
	//	fclose(f);
	//}



};

#endif