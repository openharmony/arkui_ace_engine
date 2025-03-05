import fs from "fs"
import path from "path"
import url from "url"

const __dirname = path.dirname(url.fileURLToPath(import.meta.url))

function replaceEts(src, dst) {

    const srcEts = path.join(src, 'ets')
    const dstEts = path.join(dst, 'ets')

    if(!fs.existsSync(srcEts)) console.log(`> ${srcEts} is empty. You need download ohos-sdk-prebuilt`)
    if(!fs.existsSync(dstEts)) console.log(`> ${dstEts} is empty. You need download ohos-sdk`)

    fs.renameSync(dstEts, path.join(dst, 'ets.orig'))
    fs.cpSync(srcEts, dstEts, { recursive: true, force: true })
    console.log(`> Copy from ${srcEts} to ${dstEts}`)

    fs.renameSync(`${dstEts}/oh-uni-package.json`, `${dstEts}/oh-uni-package.orig.json`)
    fs.cpSync(`${dst}/ets.orig/oh-uni-package.json`, `${dstEts}/oh-uni-package.json`, {recursive: true, force: true})
    console.log(`> Copy from ${dst}/ets.orig/oh-uni-package.json to ${dstEts}/oh-uni-package.json`)
}


function main() {
    const ohosSdkPath = path.join(__dirname, '../ohos-sdk/HarmonyOS-NEXT-DB1/openharmony')
    const ohosSdkPrebuiltPath = path.join(__dirname, '../ohos-sdk-prebuilt')

    replaceEts(ohosSdkPrebuiltPath, ohosSdkPath)
}

main()