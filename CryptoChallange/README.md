MY SOLUTIONS TO THE MATASANO CRYPTO CHALLENGES
==============================================

My solutions so far to the crypto challenges posted at [Cryptopals](http://cryptopals.org)
Solutions in plain C. This project is a learning project, hence full of stupid s**t,
but I'm learning heaps, so that's ok..

The point of this reference document is to clarify the project structure for my
own part, but it will also be useful to anyone else who stumbles upon it.
I am very happy if my solutions serve to help or hint others struggling with the 
challenges in C (or any other language).

##Program strucure

There are almost 50 challenges in all, grouped by similarity and type into 8 sets.
I am using XCode as IDE, where each exercise has its own __target__ (challenge($x), and 
it's own __main file__ (challenge($x).c) within which is a `main` function that 
sets up and tests the solution code.

Most of the _solution code_ lies in the files __CryptoChallenges.h/c__. Functions
that should be publicly available in various `main`-functions are declared in the
header, helper functions and private stuff has their declerations and implementations
hidden away in the .c-file.

Some of the solutions are dependent upon the __OpenSSL__ library. This means
the static libraries __libcrypto.a__ and __libssl.a__, and also the headers
__<openssl/*.h>__ must be available to the computer. In order to run the programs
on a Mac, the OpenSSL library must be downloaded and installed afresh, as the
built in version is deprecated to bits. To avoid over-linking when the libraries
aren't necessary, the solutions that require OpenSSL are found in __OpenSSLFunctions.c/h__

In addition, the files __Crypto_Utils.h/c__ contain declarations, typedefs
and constants of a more general nature, useful throughout the project. These are
not _per se_ related to any of the challenges, but perform tasks like hex/base64
en/decoding &c.

All files neccessary for testing the programs are included as __$(chal#.txt)__.