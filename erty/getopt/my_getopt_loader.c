/*
** EPITECH PROJECT, 2021
** getopt
** File description:
** loader
*/

#include <erty/getopt.h>

static bool opt_arg_valid(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser)
{
    if (args[i].multiple_allowed == false && args[i].is_used == true) {
        efprintf(stderr, "%s: has been used twice!\n",
                parser->argv[parser->argv_idx]);
        return (false);
    }
    if (args[i].opt_type != OPT_NO_ARG &&
        (parser->argv[parser->argv_idx + 1] == NULL ||
        parser->argv[parser->argv_idx + 1][0] == '-')) {
        efprintf(stderr, "%s: requires an argument\n",
                parser->argv[parser->argv_idx]);
        return (false);
    }
    return (true);
}

bool opt_load_string(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser)
{
    if (opt_arg_valid(args, i, parser) == false)
        return (false);
    args[i].u.s = estrdup(parser->argv[parser->argv_idx + 1]);
    if (args[i].u.s == NULL) {
        efprintf(stderr, "Allocation error in my_getopt\n");
        return (false);
    }
    args[i].is_used = true;
    parser->argv_idx += 2;
    return (true);
}

bool opt_load_integer(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser)
{
    usize_t i_argv = 0;

    if (opt_arg_valid(args, i, parser) == false)
        return (false);
    if (parser->argv[parser->argv_idx + 1][0] == '-')
        i_argv++;
    for (; parser->argv[parser->argv_idx + 1][i_argv]; i_argv++) {
        if (eis_num(parser->argv[parser->argv_idx + 1][i_argv]) == false) {
            efprintf(stderr, "%s: Is not a valid number\n",
                    parser->argv[parser->argv_idx + 1]);
            return (false);
        }
    }
    args[i].u.i = eatol(parser->argv[parser->argv_idx + 1]).value;
    args[i].is_used = true;
    parser->argv_idx += 2;
    return (true);
}

bool opt_load_none(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser)
{
    if (opt_arg_valid(args, i, parser) == false)
        return (false);
    parser->argv_idx++;
    args[i].is_used = true;
    return (true);
}
