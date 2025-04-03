## libarkts

Wrapper library which provides tsc-like __ArkTS__ compiler API 

Implemented with koala interop technology 

### Prerequisites

node >= 18
meson >= 0.62

Having following .npmrc: https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/wikis/npmrc

```
cd ~/arkcompiler_ets_frontend 
npm i
cd ./arkoala-arkts/libarkts/
npm i
npm run compile
```

### Structure

- ```compatible``` - __ArkTS__ / __typescript__ plugins
- ```input``` - code samples to be compiled with __ArkTS__ / __typescript__
- ```native``` - node module wrapper for __es2panda.so__
- ```src``` - plugin API sources
- ```test``` - plugin API tests

### How to run
```
npm run run
node build/api/es2panda.js --help
```

Runs __ArkTS__ compiler for __./input/main.sts__ invoking plugins specified in __arktsconfig.json__
