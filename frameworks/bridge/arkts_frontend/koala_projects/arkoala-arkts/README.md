# Setup env
```
Export these env variables:
- `OPENLAB_USERNAME`
- `OPENLAB_PASSWORD`
```
Add registry to the `.npmrc` file in the `$HOME` directory (`~/.npmrc`):
```text
@koalaui:registry=https://nexus.bz-openlab.ru:10443/repository/koala-npm/
//nexus.bz-openlab.ru:10443/repository/koala-npm/:_auth=a29hbGEtcHViOnkzdCFuMHRoZXJQ
```
# Run on desktop

```
$ npm install
$ cd arkoala-arkts
$ npm run trivial:all:node
```
# Run on device
1. Building arkoala-arkts.har

```
$ npm install
$ cd arkoala-arkts
$ KOALA_BZ=1 npm run trivial:all:har-arm32
$ file ./arkoala-arkts/har/app/arkoala/build/default/outputs/default/arkoala.har
```
2. Сreate an application in DevEco and set the arkoala-arkts.har depending on the oh-package.json5
```
"dependencies": {
    "@koalaui/arkoala-arkui": "file:<arkoala-har-path>"
}
```
3. Add metadata to entry/src/main/module.json5
```
{
    "module": {
        ...
        "metadata": [
            {
                "name": "ArkoalaPlugin",
                "value": "true"
            }
        ]
    }
}
```
4. Run your application

# Some problems
1. If you can’t load libraries, you can put them in the system/lib
```
hdc file send <some-libs.so> /system/lib
```
2. Currently a working version of panda in the blue zone is 1.5.0-dev.5226
```
cd incremental/tools/panda
npm i @panda/sdk@1.5.0-dev.5226
```