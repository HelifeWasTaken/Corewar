/*
** EPITECH PROJECT, 2021
** my
** File description:
** getopt
*/

#include <erty/getopt.h>

static bool chose_fun(struct my_getopt_args *args, usize_t i,
    struct my_getopt_parser *parser)
{
    switch (args[i].opt_type) {
    case OPT_NO_ARG:
        return (opt_load_none(args, i, parser));
    case OPT_STR:
        return (opt_load_string(args, i, parser));
    case OPT_INT:
        return (opt_load_integer(args, i, parser));
    default:
        efprintf(stderr, "WTF it should impossible to come here\n");
        return (false);
    }
}

static bool load_arg(struct my_getopt_args *args,
    struct my_getopt_parser *parser, char ***not_opt)
{
    char *arg = parser->argv[parser->argv_idx];

    if (*arg != '-') {
        eappend_tab(not_opt, arg);
        parser->argv_idx++;
        if (not_opt == NULL)
            efprintf(stderr, "Allocation error\n");
        return (not_opt != NULL);
    }
    for (usize_t i = 0; args[i].arg || args[i].long_arg; i++) {
        if (!estrcmp(args[i].arg, arg) || !estrcmp(args[i].long_arg, arg)) {
            return (chose_fun(args, i, parser));
        }
    }
    efprintf(stderr, "%s: argument is not recognized\n", arg);
    return (false);
}

bool my_getopt(struct my_getopt *args, char **argv)
{
    struct my_getopt_parser parser = {0};

    parser.argv = argv;
    parser.argv_idx = 0;
    while (parser.argv[parser.argv_idx]) {
        if (load_arg(args->arg, &parser, &args->reg) == false)
            return (false);
    }
    return (true);
}

void destroy_opts(struct my_getopt *args)
{
    if (args->reg) {
        free_esplit(args->reg);
        args->reg = NULL;
    }
    for (usize_t i = 0; args->arg[i].arg || args->arg[i].long_arg; i++) {
        if (args->arg[i].opt_type == OPT_STR) {
            FREE(args->arg[i].u.s);
        }
    }
}

void display_opts(struct my_getopt *args)
{
    eprintf("args reg: [ ");
    if (args->reg == NULL)
        eprintf("(null)");
    else
        for (usize_t i = 0; args->reg[i]; i++)
            eprintf(" [ %s ] ", args->reg[i]);
    eprintf(" ]\nargs opt: [ \n");
    for (usize_t i = 0; args->arg[i].arg || args->arg[i].long_arg; i++) {
        eprintf("\t[%s|%s]: [is_used: %s][multiple_allowed: %s][value: ",
                args->arg[i].arg ? args->arg[i].arg : "(null)",
                args->arg[i].long_arg ? args->arg[i].long_arg : "(null)",
                args->arg[i].is_used ? "true" : "false",
                args->arg[i].multiple_allowed ? "true" : "false");
        if (args->arg[i].opt_type == OPT_NO_ARG) eprintf("(none)");
        else if (args->arg[i].opt_type == OPT_INT)
            eprintf("%lld", args->arg[i].u.i);
        else eprintf("%s", args->arg[i].u.s ? args->arg[i].u.s : "(null)");
        eprintf("]\n");
    }
    eprintf("]\n");
}
