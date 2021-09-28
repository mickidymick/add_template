#include <yed/plugin.h>

void set_template(int nargs, char** args);

int set_template_completion(char *name, struct yed_completion_results_t *comp_res) {
    int ret = 0;
    array_t list;
    list = array_make(char *);
    char *tmp;
    char loc[256];

    tmp = get_config_item_path("templates");
    if(tmp == NULL) {
        LOG_FN_ENTER();
        yed_cerr("templates dir not found");
        LOG_EXIT();
        return 0;
    }

    DIR *d;
    struct dirent *dir;
    d = opendir(tmp);
    if(d) {
        while((dir = readdir(d)) != NULL) {
            tmp = strdup(dir->d_name);
            if((strcmp(tmp, ".")) && (strcmp(tmp, ".."))) {
                array_push(list, tmp);
            }
        }
        closedir(d);
    }

    FN_BODY_FOR_COMPLETE_FROM_ARRAY(name, array_len(list), (char **)array_data(list), comp_res, ret);
    array_free(list);
    return ret;
}

int yed_plugin_boot(yed_plugin *self) {

    YED_PLUG_VERSION_CHECK();

    yed_plugin_set_command(self, "set-template", set_template);
    yed_plugin_set_completion(self, "set-template-compl-arg-0", set_template_completion);

    return 0;
}

void set_template(int nargs, char** args) {
    char line[512];
    char str[512];
    char app[512];
    char *path;
    yed_frame *frame;

    frame = ys->active_frame;

    if (!frame
    ||  !frame->buffer
    ||  frame->buffer->kind != BUFF_KIND_FILE) {
        return;
    }

    if(nargs != 1) {
        yed_cerr("Must have the template name as an argument you gave %d args\n", nargs);
        return;
    }

    strcpy(app, "templates/");
    strcat(app, args[0]);

    FILE *fp;
    if (!ys->options.no_init) {
        path = get_config_item_path(app);
        fp = fopen (path, "r");
	    free(path);
    }

    if (fp == NULL) {
        return;
    }

    int start_row = frame->cursor_line;
    while( fgets( line, 512, fp ) != NULL ) {
        start_row++;
        yed_buff_insert_string(frame->buffer, line, start_row, 1);
        yed_merge_undo_records(frame->buffer);
    }
    fclose(fp);
}
