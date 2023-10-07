#include "ecsviz/ecsviz_fs.h"
#include "ecsviz/ecsviz_assert.h"
#include "ecsviz/ecsviz_log.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COLOR_RST "\033[0m"
#define COLOR_CWD "\033[38;2;100;100;255m"
#define COLOR_PATH "\033[38;2;160;160;255m"
#define COLOR_ERROR "\033[38;2;255;120;120m"

char * fs_getcwd(char cwd[], int n)
{
	char *rc = getcwd(cwd, n);
	if (rc == NULL) {
		ecsviz_log("getcwd error: %s\n", strerror(errno));
		return NULL;
	}
	return rc;
}

void fs_pwd()
{
	char cwd[1024] = {0};
	fs_getcwd(cwd, 1024);
	printf("Current working directory: %s%s%s\n", COLOR_CWD, cwd, COLOR_RST);
}

char *fs_readfile(char const *path)
{
	ecsviz_assert_notnull(path);
	char *content = NULL;

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		char cwd[1024] = {0};
		char *rc = getcwd(cwd, sizeof(cwd));
		ecsviz_log(COLOR_CWD"%s/"COLOR_PATH"%s "COLOR_ERROR"%s"COLOR_RST"\n", cwd, path, strerror(errno));
		goto error;
	}

	fseek(file, 0, SEEK_END);
	int32_t size = (int32_t)ftell(file);

	if (size == -1) {
		goto error;
	}
	rewind(file);

	content = malloc(size + 1);
	content[size] = '\0';
	size_t n = fread(content, size, 1, file);
	if (n != 1) {
		ecsviz_log("%s: could not read wholef file %d bytes\n", path, size);
		goto error;
	}
	ecsviz_assert(content[size] == '\0', "Expected null terminator");
	fclose(file);
	return content;
error:
	if (content) {
		free(content);
	}
	return NULL;
}