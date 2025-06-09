import { execSync } from "child_process"
import { dirname } from "path"
import { fileURLToPath } from "url"

import fs from "fs"
import path from "path"
import process from "process"
import minimist from "minimist"

var args = minimist(process.argv.slice(2))

const _dirname = dirname(fileURLToPath(import.meta.url))

const CWD = process.cwd()
const BUNDLE_PATH = path.join(CWD, "arkoala-har-bundle")
const HAR_PATH = path.join(CWD, "app/arkoala")

function execCmdSync(cmd, options) {
    return execSync(cmd, options).toString().trim().replace("\n", " ")
}

function rollupLaunch(loaderArch, vmkind) {
    console.log(`> Run rollup`)
    execCmdSync(`npx rollup -c --arch ${loaderArch} --vmkind ${vmkind}`)
}

function copyFileToHar(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })
}

function copySoLibs(from, to) {
    fs.readdirSync(from, {withFileTypes: true})
    .filter(file => file.name.endsWith(".so"))
    .forEach(file => {
        console.log(`> Copy from: ${from}/${file.name} to ${to}/${file.name}`)
        fs.cpSync(`${from}/${file.name}`, `${to}/${file.name}`, { recursive: true, force: true })
    })
}

function main(targetLibDir, loaderArch, vmkind) {

    process.chdir(BUNDLE_PATH)

    rollupLaunch(loaderArch, vmkind)
    /* we don't yet know which files should be in har */
    copyFileToHar(path.join(_dirname, `../../../arkoala/framework/build/libc++.so`), path.join(HAR_PATH, `libs/${targetLibDir}/libc++.so`))
    copyFileToHar(path.join(_dirname, `../../../arkoala/framework/build/libArkoalaLoader.so`), path.join(HAR_PATH, `libs/${targetLibDir}/libArkoalaLoader.so`))
    copyFileToHar(path.join(_dirname, `../../../arkoala/framework/build/libvmloader.so`), path.join(HAR_PATH, `libs/${targetLibDir}/libvmloader.so`))
    copyFileToHar(path.join(_dirname, `../../../arkoala/framework/build/libArkoalaNative_${vmkind}.so`), path.join(HAR_PATH, `libs/${targetLibDir}/libArkoalaNative_${vmkind}.so`))
    copyFileToHar(path.join(_dirname, `../../build/arkoala.abc`), path.join(HAR_PATH, `libs/${targetLibDir}/arkoala.abc.so`))
}

const vmkind = args["vmkind"]
if (vmkind !== "ani" && vmkind !== "ets") {
    console.log("Unsupported vmkind: ", vmkind)
    process.exit(1)
}
const arch = args["arch"]
if (arch == "arm32") {
    main("armeabi-v7a", "arm", vmkind)
} else if (arch == "arm64") {
    main("arm64-v8a", arch, vmkind)
} else {
    console.log("Unsupported architecture: ", arch)
    process.exit(1)
}
