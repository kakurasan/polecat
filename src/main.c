#include <stdio.h>
#include <string.h>
#include <linux/limits.h>

#include "main.h"
#include "wine.h"
#include "dxvk.h"
#include "lutris.h"
#include "common.h"
#include "config.h"

const static struct Command main_commands[] = {
    { .name = "wine",   .func = wine,      .description = "manage wine versions" },
#ifdef DEBUG
    { .name = "dxvk",   .func = dxvk,      .description = "manage dxvk versions" },
#endif
    { .name = "lutris", .func = lutris,    .description = "run lutris instraller"},
    { .name = "info",   .func = main_info, .description = "show some information about polecat" },
};


int main(int argc, char** argv)
{
    if (argc > 1)
    {
        for (int i = 0; i < ARRAY_LEN(main_commands); ++i)
        {
            if (!strcmp(main_commands[i].name, argv[1])) return main_commands[i].func(argc-1, argv+1);
        }
    } 

    return main_help(argc, argv);
}

int main_info(int argc, char** argv)
{
    char cfgdir[PATH_MAX], datadir[PATH_MAX], cachedir[PATH_MAX];

    getConfigDir(cfgdir, sizeof(cfgdir));
    getDataDir(datadir, sizeof(datadir));
    getCacheDir(cachedir, sizeof(cachedir));

    printf("version:\t\t%s\n"
           "user-Agent:\t\t%s/%s\n"
           "config dir\t\t%s\n"
           "data dir\t\t%s\n"
           "cache dir\t\t%s\n",
           VERSION,
           NAME, VERSION,
           cfgdir, datadir, cachedir);

    return 0;
}

int main_help(int argc, char** argv)
{
    puts(USAGE_STR " <command>\n\nList of commands:");

    print_help(main_commands, ARRAY_LEN(main_commands));

    return 0;
}