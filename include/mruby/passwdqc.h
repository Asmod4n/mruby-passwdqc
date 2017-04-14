#ifndef MRUBY_PASSWDQC_H
#define MRUBY_PASSWDQC_H

#include <mruby.h>

MRB_BEGIN_DECL

#define E_PASSWDQC_ERROR (mrb_class_get_under(mrb, mrb_class_get(mrb, "Passwdqc"), "Error"))

MRB_END_DECL

#endif
