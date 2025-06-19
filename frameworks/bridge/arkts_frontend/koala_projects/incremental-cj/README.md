# CjKoala

Koala infrastructure for [Cangjie] language.

## cd runtime

This is a port of the Koala incremental engine to CJ.
Due to Cangjie restrictions, the callsite key is calculated using via C language.
So, you have to call `CallsiteKey.sh`, which compiles the required source code with `clang`.
You can do this only once after downloading the repository.
Unfortunately, this approach works correctly on Linux, but not on Windows.

`cjpm test` compiles and executes all tests in this module

## cd original-test

This is the original test for the incremental engine, which shows the recomputation of the changed parts only.

`cjpm run` compiles and executes the application from `main.cj`

## cd demo-playground

This is a port of the Koala demo, that allows to play with the incremental runtime and memo functions.

`cjpm run` compiles and executes the application from `main.cj`.
