# mruby-passwdqc

A Password quality checker for mruby, wrapping http://www.openwall.com/passwdqc/

Examples
========
```ruby
passwdqc = Passwdqc.new

passwdqc.check "newpass"
passwdqc.check "newpass", "oldpass"
passwdqc.check "newpass", "oldpass", "unix_login"
```

if returns nil when the password is okay, or else a reason why it is not good enough
