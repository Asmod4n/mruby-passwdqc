#ifndef MRUBY_PASSWDQC_H
#define MRUBY_PASSWDQC_H

#include <mruby.h>

#ifdef __cplusplus
extern "C" {
#endif

#define E_PASSWDQC_ERROR (mrb_class_get_under(mrb, mrb_class_get(mrb, "Passwdqc"), "Error"))

#ifdef __cplusplus
}
#endif

#endif
