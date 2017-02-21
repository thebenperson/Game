#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.hpp"
#include "Util/File/file.hpp"

void Config::add(char *name, void *val) {

	Setting* setting = new Setting();
	setting->name = name;
	setting->val = val;

	setting->freeName = false;
	setting->freeVal = false;

	settings.add(setting);

}

Config::Setting* Config::get(char* name) {

	for (size_t i = 0; i < settings.len; i++) {

		Setting *setting = (Setting*) settings.get(i);
		if (!strcmp(setting->name, name)) return setting;

	}

	return NULL;

}

bool Config::load(char *path) {

	char *file = NULL;
	size_t size = loadFile(path, &file);

	Config *config = NULL;

	if (size != -1) {

		char *start = file; //initialize name pointer
		bool lineStart = true;

		for (size_t i = 0; i < size; i++) {

			for (;;) { //cycle until next char != #

				if (file[i] == '#') {

					char* end = strchr((file + i) + 1, '\n');
					if (!end) {

						fprintf(stderr, "Error parsing %s: no data\n", path);
						return false;

					}

					i = (end - file) + 1;
					start = file + i; //skip to next line

				} else break;

			}

			char c = file[i];

			if ((lineStart) && (c == ' ' || c == '\t' || c == '\n')) { //ignore spaces, tabs, and newlines at the beginning of a line

				start++;

			} else { //use '=', ':', ' ', and '\t' as field seperators

				bool sep = false;
				bool pad = false;

				if (c == '=' || c == ':' || c == '\t') sep = true;
				else if (c == ' ') {

					sep = true;
					if (file[i + 1] == '=' || file[i + 1] == ':') pad = true;

				}

				if (sep) {

					size_t len = (file + i) - start;

					char *name = (char*) malloc(len + 1);
					strncpy(name, start, len);
					name[len] = '\0'; //get val name

					start = (file + i) + 1;

					if (pad) start++;
					if (*start == ' ') start++;

					char* end = strchr(start, '\n');
					if (!end) {

						fprintf(stderr, "Error parsing %s: no data\n", path);
						return false;

					}

					len = (end - start);

					char* val = (char*) malloc(len + 1);
					strncpy(val, start, len);
					val[len] = '\0'; //get val string

					bool isNew;

					Setting *setting = get(name);
					if (setting) {

						free(name);
						if (setting->freeVal) free(setting->val);

						isNew = false;

					} else {

						setting = new Setting();
						setting->name = name;
						setting->freeName = true;

						isNew = true;

					}

					setting->isString = false;

					char* flag;
					long int nVal = strtol(val, &flag, 10);

					if ((*flag)) {

						if (!strcasecmp(val, "true")) nVal = true;
						else if (!strcasecmp(val, "false")) nVal = false;
						else {

							setting->isString = true;

						}

					}

					if (setting->isString) {

						setting->val = val;
						setting->freeVal = true;

					} else {

						setting->val = (void*) nVal;
						free(val);

						setting->freeVal = false;

					}

					if (isNew) settings.add(setting);

					i = (end - file);
					start = end + 1; //skip to next line

					lineStart = true;

				} else {

					lineStart = false;

				}

			}

		}

		free(file);

	}

	return true;

}

void Config::save(char *path) {



}

void Config::set(char *name, void *val) {

	get(name)->val = val;

}

Config::~Config() {

	Setting* setting;

	for (size_t i = 0; i < settings.len; i++) {

		setting = (Setting*) settings.get(i);
		if (setting->freeName) free(setting->name);
		if (setting->freeVal) free(setting->val);

		delete setting;

	}

}