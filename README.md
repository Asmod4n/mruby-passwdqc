# mruby-passwdqc

A Password quality checker for mruby, wrapping http://www.openwall.com/passwdqc/

Examples
========
```ruby
passwdqc = Passwdqc.new

passwdqc.check "newpass" # just checks the password
passwdqc.check "newpass", "oldpass" # also checks if the new one is too similar
passwdqc.check "newpass", "oldpass", "unix_login" # takes into account informations from the unix account
```

if returns nil when the password is okay, or else a reason why it is not good enough or when it cannot find a unix account
