**Umbrella repo of `incremental engine` and `ArkUI` refactoring project**

# Setup env

Export these env variables:
- `OPENLAB_USERNAME`
- `OPENLAB_PASSWORD`

Install:
- `node.js` `18.20.4 LTS`
- `meson` no older than `0.61`

Make sure the workspace does not contain outdated artifacts of older builds.

# How to build `arkoala.har`

```
$ npm install
$ KOALA_BZ=1 npm run arkoala:har-arm32
$ file ./arkoala/har/app/arkoala/build/default/outputs/default/arkoala.har
```
# How to build `arkoala-arkts.har`

```
$ npm install
$ cd arkoala-arkts
$ KOALA_BZ=1 npm run trivial:all:har-arm32
$ file ./arkoala-arkts/har/app/arkoala/build/default/outputs/default/arkoala.har
```

# How to build `arkoala plugin` and patch `OHOS SDK`

```
$ npm install
$ KOALA_BZ=1 npm run ohos-sdk
$ export HOS_SDK_HOME=`pwd`/arkoala/ohos-sdk/ohos-sdk
$ KOALA_BZ=1 npm run arkoala:plugin
$ file ${HOS_SDK_HOME}/HarmonyOS-NEXT-DB1/openharmony/ets/build-tools/ets-loader/lib/fast_build/ets_ui/arkoala-plugin.js
```
