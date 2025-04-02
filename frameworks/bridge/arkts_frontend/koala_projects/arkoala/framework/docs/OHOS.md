
As for now we can run DevEco app on OHOS. The app imports Arkoala and successfully loads libArkoalaNative-ohos-arm64.so
In order to build the ohos lib, first build Arkoala as usual, then:
$ cd arkoala
$ npm run configure:native-arkjs-ohos
$ npm run compile:arkjs-ohos
$ cd ../arkoala-loader
$ npm run compile:arkjs-ohos

Then, in the DevEco project, put arkoala-loader/lib/js/index-ark.js somewhere into the "entry" folder (I wasn't able to import it from the outside so far, if you known how - good).
Then in Index.ets:
import { startArkoala } from path/to/index-ark.js

Think you know that, but just for any case: in the "entry" folder create "libs/arm64-v8a" and put libArkoalaNative-ohos-arm64.so (from akoala/build) inside the folder. The lib will be built-in into the hap file.
