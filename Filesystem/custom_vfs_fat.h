// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "esp_log.h"
extern "C" {
#include "esp_vfs_fat.h"
}
#include "wear_levelling.h"

static const char *TAG = "vfs_fat_spiflash";

esp_err_t custom_esp_vfs_fat_spiflash_mount(const char* base_path,
	const char* partition_label,
	const esp_vfs_fat_mount_config_t* mount_config,
	wl_handle_t* wl_handle);

esp_err_t custom_esp_vfs_fat_spiflash_format(const char* base_path,
	const char* partition_label,
	const esp_vfs_fat_mount_config_t* mount_config,
	wl_handle_t* wl_handle);

esp_err_t custom_esp_vfs_fat_spiflash_unmount(const char *base_path, wl_handle_t *wl_handle);