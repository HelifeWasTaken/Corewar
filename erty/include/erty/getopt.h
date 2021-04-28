/*
** EPITECH PROJECT, 2021
** getopt
** File description:
** erty
*/

#ifndef __LIBERTY__GETOPT__H__
    #define __LIBERTY__GETOPT__H__

    #include <erty/string/ecstring.h>
    #include <erty/eprintf.h>
    #include <erty/estdlib.h>

    enum arg_type {
        OPT_NO_ARG,
        OPT_STR,
        OPT_INT
    };

    union opt_arg {
        char *s;
        long long i;
    };

    #define EMPTY_OPT_ARG (union opt_arg){.s = NULL}

    #define OPT_ARG(arg, long_arg, multiple, type) \
        (struct my_getopt_args){arg, long_arg, EMPTY_OPT_ARG, \
                                multiple, false, type}
    #define MAX_ARG_COUNT 20

    struct my_getopt_parser {
        char **argv;
        usize_t argv_idx;
    };

    struct my_getopt_args {
        char *arg;
        char *long_arg;
        union opt_arg u;
        bool is_used;
        bool multiple_allowed;
        enum arg_type opt_type;
    };

    typedef struct my_getopt {
        struct my_getopt_args arg[MAX_ARG_COUNT];
        char **reg;
    } my_getopt_t;

    bool my_getopt(struct my_getopt *args, char **argv);
    void destroy_opts(struct my_getopt *args);
    void display_opts(struct my_getopt *args);

    bool opt_load_none(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser);
    bool opt_load_integer(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser);
    bool opt_load_string(struct my_getopt_args *args, usize_t i,
        struct my_getopt_parser *parser);

#endif
