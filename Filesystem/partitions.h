#pragma once

#include <esp_log.h>
#include <esp_partition.h>

void patch_partition() {
	esp_log_level_set("*", esp_log_level_t::ESP_LOG_DEBUG);
	printf("starting...\r\n");
	ESP_LOGI(TAGSPIFF, "Patching partition table");
	{
		auto it = esp_partition_find(esp_partition_type_t::ESP_PARTITION_TYPE_APP, esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_ANY, NULL);
		while (it != NULL) {
			const esp_partition_t *p = esp_partition_get(it);
			printf("- %s %d/%d %08x:%08x %d  \r\n", p->label, p->type, p->subtype, p->address, p->size, p->encrypted);

			it = esp_partition_next(it);
		}
		esp_partition_iterator_release(it);
	}
	{
		auto it = esp_partition_find(esp_partition_type_t::ESP_PARTITION_TYPE_DATA, esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_ANY, NULL);
		while (it != NULL) {
			esp_partition_t *p = const_cast<esp_partition_t*>(esp_partition_get(it));
			if (p->type == esp_partition_type_t::ESP_PARTITION_TYPE_DATA && p->subtype == esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_DATA_SPIFFS) {
				p->subtype = esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_DATA_FAT;
			}
			printf("- %s 0x%02x/0x%02x 0x%08x:0x%08x %d  \r\n", p->label, p->type, p->subtype, p->address, p->size, p->encrypted);

			it = esp_partition_next(it);
		}
		esp_partition_iterator_release(it);
	}

	{
		auto it = esp_partition_find(esp_partition_type_t::ESP_PARTITION_TYPE_DATA, esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_ANY, NULL);
		while (it != NULL) {
			const esp_partition_t *p = esp_partition_get(it);
			if (p->type == esp_partition_type_t::ESP_PARTITION_TYPE_DATA && p->subtype == esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_DATA_SPIFFS) {
				p->subtype == esp_partition_subtype_t::ESP_PARTITION_SUBTYPE_DATA_FAT;
			}
			printf("- %s 0x%02x/0x%02x 0x%08x:0x%08x %d  \r\n", p->label, p->type, p->subtype, p->address, p->size, p->encrypted);

			it = esp_partition_next(it);
		}
		esp_partition_iterator_release(it);
	}
}