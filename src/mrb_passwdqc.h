#ifndef MRB_PASSWDQC_H
#define MRB_PASSWDQC_H

#include "passwdqc.h"
#include <mruby/data.h>
#include <errno.h>
#include <mruby/throw.h>
#include <stdlib.h>
#include <mruby/error.h>
#include <mruby/class.h>

static const struct mrb_data_type mrb_passwdqc_params_type = {
  "$i_mrb_passwdqc_params_type", mrb_free
};

#endif
