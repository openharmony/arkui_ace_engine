import { execSync } from "child_process"
import fs from "fs"
import path from "path"
import process from "process"

import { dirname } from "path"
import { fileURLToPath } from "url"

const _dirname = dirname(fileURLToPath(import.meta.url))

const CWD = process.cwd()
const BUNDLE_PATH = path.join(CWD, "arkoala-har-bundle")
const HAR_PATH = path.join(CWD, "app/arkoala")
const DTS_PATH = path.join(CWD, "../arkui/build/lib/src/shared")
const DTS = [
    [DTS_PATH, "system.router.d.ts"],
    [DTS_PATH, "ohos.router.d.ts"],
    [DTS_PATH, "ohos.matrix4.d.ts"],
    [DTS_PATH, "ohos.arkui.testing.d.ts"],
    [path.join(CWD, "../arkui-types"), "index-full.d.ts"]
]

function rollupLaunch() {
    console.log(`> Run rollup`)
    execCmdSync(`npx rollup -c`)
}

function apiExtractorLaunch() {
    console.log(`> Run ApiExtractor`)
    execCmdSync("npx api-extractor run --local --verbose --diagnostics -c api-extractor.json --typescript-compiler-folder ../../node_modules/typescript")

    let file = fs.readFileSync(path.join(BUNDLE_PATH, "dist", "arkoala.d.ts"), "utf-8").trim()
    file = file.replace(/\/{3}\s*<reference.*/g, '')
    fs.writeFileSync(path.join(BUNDLE_PATH, "dist", "arkoala.d.ts"), file, 'utf-8')
}

function copyDts(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })

    /* Replace import path from "@koalaui/" to "." */
    let file = fs.readFileSync(to, "utf-8").trim()
    file = file.replace(/['"]@.+?['"]/g, '"."')
    fs.writeFileSync(to, file, 'utf-8')
}

function copyFileToHar(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })
}

function main() {

    process.chdir(BUNDLE_PATH)

    rollupLaunch()
    apiExtractorLaunch()
    
    DTS.forEach((entry) => {
        const base = entry[0]
        const file = entry[1]
        copyDts(path.join(base, file), path.join(BUNDLE_PATH, "dist", file))
    })

    const files = fs.readdirSync(path.join(BUNDLE_PATH, "dist"))
    files.forEach((file) => {
        copyFileToHar(path.join(BUNDLE_PATH, "dist", file), path.join(HAR_PATH, file))
    })


    // arm32
    copyFileToHar(path.join(_dirname, `../../framework/native/build-hzvm-ohos-arm32/libArkoalaNative.so`), path.join(HAR_PATH, `libs/armeabi-v7a/libArkoalaNative.so`))
    
    // arm64
    copyFileToHar(path.join(_dirname, `../../framework/native/build-hzvm-ohos-arm64/libArkoalaNative.so`), path.join(HAR_PATH, `libs/arm64-v8a/libArkoalaNative.so`))
    
    // x86-64
    copyFileToHar(path.join(_dirname, `../../framework/build/libArkoalaNative.so`), path.join(HAR_PATH, `libs/x86-64/libarkoalanative.so`))


}

function execCmdSync(cmd, options) {
    return execSync(cmd, options).toString().trim().replace("\n", " ")
}

main()