#ifndef _SPIFFS_FS_h
#define _SPIFFS_FS_h

#include "IFilesystem.h"

#include <esp_log.h>

extern "C" {
#include <esp_vfs.h>
//#include "esp_vfs_fat.h"
	#include "spiffs/spiffs_vfs.h"
}

#include <esp_partition.h>

static const char *TAGSPIFF = "vfs_spiffs";

class SPIFFilesystem : public IFilesystem {
	virtual int init() {
		const char * partition_label = "spiffs";

		esp_partition_t *data_partition = (esp_partition_t *)esp_partition_find_first(ESP_PARTITION_TYPE_DATA, esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_ANY, partition_label);
		if (data_partition == NULL) {
			ESP_LOGE(TAGSPIFF, "Failed to find SPIFFS partition (type='data', subtype='any', partition_label='%s'). Check the partition table.", partition_label);
			return ESP_ERR_NOT_FOUND;
		}

		vfs_spiffs_register( data_partition->address, data_partition->size /*256 * 1024*/, 256, 4096, 4096);
		return 0;
	}
	virtual int format() {
		init();
		spiffs_format();
		deinit();
	}

	virtual int deinit() {
		spiffs_unmount(1);
		return 0;
	}

	virtual long get_size() {
		uint32_t total;
		uint32_t used;
		spiffs_fs_stat(&total, &used);
		return total;
	}
	virtual long get_available() {
		uint32_t total;
		uint32_t used;
		spiffs_fs_stat(&total, &used);
		return total- used;
	}

};

#endif

