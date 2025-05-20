```bash
# 1. prepare dependencies
cd ../..
npm run prepare
npm run compile
npm run panda:sdk:install --prefix incremental/tools/panda
npm run build:incremental:components --prefix incremental/runtime
npm run compile:all --prefix incremental/harness
npm run build:harness --prefix incremental/harness
npm run compile --prefix incremental/compiler-plugin

npm run compile --prefix ui2abc/libarkts # npm run clean --prefix ui2abc/libarkts
npm run compile --prefix ui2abc/annotate
npm run compile --prefix ui2abc/memo-plugin
npm run build:incremental:inc:ui2abc --prefix incremental/runtime

# 1.1 OR you could use this command
npm run compile:deps --prefix ui2abc/tests-memo

# 2. run tests
cd ui2abc/tests-memo
npm i
npm run test:ts # 1.
npm run test:arkts:compiler-plugin # 2.
npm run test:arkts:memo-plugin # 3.
```