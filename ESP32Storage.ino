#define LOG_LOCAL_LEVEL  ESP_LOG_VERBOSE


#include "Filesystem/fat_fs.h"
#include "Filesystem/spiffs_fs.h"

#include "FilesystemTests.h"

#include "esp_log.h"

IFilesystem *_fs;

void runTest(void *) {
	printf("start memory: %d \r\n", system_get_free_heap_size());

	

	_fs = new FATFilesystem();
	//_fs = new SPIFFilesystem();

	_fs->format();
	printf("format memory: %d \r\n", system_get_free_heap_size());
	_fs->init();
	printf("init memory: %d \r\n", system_get_free_heap_size());

	printf("total: %d, available: %d\r\n", _fs->get_size(), _fs->get_available());

	//xTaskCreate(&test_fs, "test_fs", 4096, NULL, NULL, NULL);
	//xTaskCreatePinnedToCore(&test_fs, "test_fs", 8192, NULL, NULL, NULL, NULL);
	FSTest test1(_fs);
	test1.test(NULL);
	printf("test memory: %d \r\n", system_get_free_heap_size());

	printf("total: %d, available: %d\r\n", _fs->get_size(), _fs->get_available());
	_fs->deinit();
	printf("deinit memory: %d \r\n", system_get_free_heap_size());
	free(_fs);
	taskYIELD();
	printf("free memory: %d \r\n", system_get_free_heap_size());

	//_fs = new FATFilesystem();
	_fs = new SPIFFilesystem();

	_fs->format();
	printf("format memory: %d \r\n", system_get_free_heap_size());
	_fs->init();
	printf("init memory: %d \r\n", system_get_free_heap_size());

	printf("total: %d, available: %d\r\n", _fs->get_size(), _fs->get_available());

	//xTaskCreatePinnedToCore(&test_fs, "test_fs", 8192, NULL, NULL, NULL, NULL);
	FSTest test(_fs);
	test.test(NULL);
	printf("test memory: %d \r\n", system_get_free_heap_size());

	printf("total: %d, available: %d\r\n", _fs->get_size(), _fs->get_available());
	_fs->deinit();
	printf("deinit memory: %d \r\n", system_get_free_heap_size());
	free(_fs);
	taskYIELD();
	printf("free memory: %d \r\n", system_get_free_heap_size());


	while (1) {
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

//================
void setup()
{
	esp_log_level_set("*", esp_log_level_t::ESP_LOG_VERBOSE);
	xTaskCreate(&runTest, "runTest", 16384, NULL, NULL, NULL);
	//xTaskCreatePinnedToCore(&runTest, "runTest", 16384, NULL, NULL, NULL, 1);
	//runTest(NULL);
}

void loop() {
	vTaskDelay(1000 / portTICK_RATE_MS);
}

