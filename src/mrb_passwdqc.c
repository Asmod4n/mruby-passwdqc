#include "mruby/passwdqc.h"
#include "mrb_passwdqc.h"

static mrb_value
mrb_passwdqc_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value pathname_val = mrb_nil_value();

  mrb_get_args(mrb, "|S!", &pathname_val);

  passwdqc_params_t *params = (passwdqc_params_t *) mrb_realloc(mrb, DATA_PTR(self), sizeof(passwdqc_params_t));
  mrb_data_init(self, params, &mrb_passwdqc_params_type);
  passwdqc_params_reset(params);

  if (mrb_string_p(pathname_val)) {
    mrb_funcall(mrb, self, "params_load", 1, pathname_val);
  }

  return self;
}

static mrb_value
mrb_passwdqc_check(mrb_state *mrb, mrb_value self)
{
  char *newpass, *oldpass = NULL;
  mrb_value login_val = mrb_nil_value();

  mrb_get_args(mrb, "z|z!S!", &newpass, &oldpass, &login_val);

  struct passwd *pwd = NULL;
  if (mrb_string_p(login_val)) {
    const char *login = mrb_string_value_cstr(mrb, &login_val);
    errno = 0;
    pwd = getpwnam(login);
    if (pwd == NULL) {
      if (errno == 0) {
        return mrb_format(mrb, "login '%S' not found", login_val);
      } else {
        mrb_sys_fail(mrb, "getpwnam");
      }
    }
  }

  const char *reason = passwdqc_check(&((passwdqc_params_t *) DATA_PTR(self))->qc, newpass, oldpass, pwd);
  if (reason) {
    return mrb_str_new_static(mrb, reason, strlen(reason));
  } else {
    return mrb_nil_value();
  }
}

static mrb_value
mrb_passwdqc_random(mrb_state *mrb, mrb_value self)
{
  errno = 0;
  char *retval = passwdqc_random(&((passwdqc_params_t *) DATA_PTR(self))->qc);
  if (retval) {
    mrb_value retval_str = self;
    struct mrb_jmpbuf* prev_jmp = mrb->jmp;
    struct mrb_jmpbuf c_jmp;

    MRB_TRY(&c_jmp)
    {
        mrb->jmp = &c_jmp;
        retval_str = mrb_str_new_cstr(mrb, retval);
        free(retval);
        mrb->jmp = prev_jmp;
    }
    MRB_CATCH(&c_jmp)
    {
        mrb->jmp = prev_jmp;
        free(retval);
        MRB_THROW(mrb->jmp);
    }
    MRB_END_EXC(&c_jmp);

    return retval_str;
  } else {
    mrb_sys_fail(mrb, "passwdqc_random");
  }

  return self;
}

static mrb_value
mrb_passwdqc_params_parse(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv_val;
  mrb_int argc;

  mrb_get_args(mrb, "*", &argv_val, &argc);

  const char *argv[argc];
  for (mrb_int argv_counter = 0; argv_counter < argc; ++argv_counter) {
    argv[argv_counter] = mrb_string_value_cstr(mrb, &argv_val[argv_counter]);
  }

  char *reason = NULL;
  errno = 0;
  int rc = passwdqc_params_parse((passwdqc_params_t *) DATA_PTR(self), &reason, argc, argv);
  if (rc == -1) {
    if (reason) {
      struct mrb_jmpbuf* prev_jmp = mrb->jmp;
      struct mrb_jmpbuf c_jmp;

      MRB_TRY(&c_jmp)
      {
          mrb->jmp = &c_jmp;
          mrb_value reason_str = mrb_str_new_cstr(mrb, reason);
          mrb_raisef(mrb, E_PASSWDQC_ERROR, "passwdqc_params_parse: %S", reason_str);
          mrb->jmp = prev_jmp;
      }
      MRB_CATCH(&c_jmp)
      {
          mrb->jmp = prev_jmp;
          free(reason);
          MRB_THROW(mrb->jmp);
      }
      MRB_END_EXC(&c_jmp);
    } else {
      mrb_sys_fail(mrb, "passwdqc_params_parse");
    }
  }

  return self;
}

static mrb_value
mrb_passwdqc_params_load(mrb_state *mrb, mrb_value self)
{
  char *pathname;

  mrb_get_args(mrb, "z", &pathname);

  char *reason = NULL;
  errno = 0;
  int rc = passwdqc_params_load((passwdqc_params_t *) DATA_PTR(self), &reason, pathname);
  if (rc == -1) {
    if (reason) {
      struct mrb_jmpbuf* prev_jmp = mrb->jmp;
      struct mrb_jmpbuf c_jmp;

      MRB_TRY(&c_jmp)
      {
          mrb->jmp = &c_jmp;
          mrb_value reason_str = mrb_str_new_cstr(mrb, reason);
          mrb_raisef(mrb, E_PASSWDQC_ERROR, "passwdqc_params_load: %S", reason_str);
          mrb->jmp = prev_jmp;
      }
      MRB_CATCH(&c_jmp)
      {
          mrb->jmp = prev_jmp;
          free(reason);
          MRB_THROW(mrb->jmp);
      }
      MRB_END_EXC(&c_jmp);
    } else {
      mrb_sys_fail(mrb, "passwdqc_params_load");
    }
  }

  return self;
}

static mrb_value
mrb_passwdqc_params_reset(mrb_state *mrb, mrb_value self)
{
  passwdqc_params_reset((passwdqc_params_t *) DATA_PTR(self));

  return self;
}

void mrb_mruby_passwdqc_gem_init(mrb_state* mrb)
{
  struct RClass *passwdqc_class = mrb_define_class(mrb, "Passwdqc", mrb->object_class);
  MRB_SET_INSTANCE_TT(passwdqc_class, MRB_TT_DATA);
  mrb_define_class_under(mrb, passwdqc_class, "Error", E_RUNTIME_ERROR);
  mrb_define_method(mrb, passwdqc_class, "initialize", mrb_passwdqc_initialize, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, passwdqc_class, "check", mrb_passwdqc_check, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, passwdqc_class, "random", mrb_passwdqc_random, MRB_ARGS_NONE());
  mrb_define_method(mrb, passwdqc_class, "params_parse", mrb_passwdqc_params_parse, MRB_ARGS_ANY());
  mrb_define_method(mrb, passwdqc_class, "params_load", mrb_passwdqc_params_load, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, passwdqc_class, "params_reset", mrb_passwdqc_params_reset, MRB_ARGS_NONE());

}

void mrb_mruby_passwdqc_gem_final(mrb_state* mrb) {}
