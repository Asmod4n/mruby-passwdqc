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

LICENSE
=======
include/* and src/mrb_* fall under the Apache-2 license, the rest from passwdqc:
Two manual pages (pam_passwdqc.8 and passwdqc.conf.5) are under the
3-clause BSD-style license as specified within the files themselves.

concat.c, wordset_4k.c, wordset_4k.h, pam_macros.h, and pwqcheck.php
are in the public domain, but at your option they may also be used under
this package's license below.

The rest of the files in this package fall under the following terms
(heavily cut-down "BSD license"):

Redistribution and use in source and binary forms, with or without
modification, are permitted.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

$Owl: Owl/packages/passwdqc/passwdqc/LICENSE,v 1.8 2013/04/24 02:01:43 solar Exp $
