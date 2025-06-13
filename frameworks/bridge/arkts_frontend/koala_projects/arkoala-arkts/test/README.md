# This is a small testsuite on arkoala/arkts state management

the test cases are in src/ets

## Initial setup


See https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/blob/master/arkoala-arkts/README.md

for the initial setup

## How to see the rewrites

At the moment you can take a look at the rewrite:

```
$ npm run compile:ets
```

Now check out the `build/generated` folder


## How to see compilation errors

```
$ npm run build:test
```

will try to compile the test cases up to .abc and will demonstrate the errors

```
$ npm run build:test:passed
```

should be able to run es2panda on the cases
TODO: at the moment the test cases should be adapter to ArkTS capabilities of es2panda

