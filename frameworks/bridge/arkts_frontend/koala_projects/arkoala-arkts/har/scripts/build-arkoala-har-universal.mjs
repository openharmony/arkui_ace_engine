import { execSync } from "child_process"
import { dirname } from "path"
import { fileURLToPath } from "url"

import fs from "fs"
import path from "path"
import process from "process"
import minimist from "minimist"

var args = minimist(process.argv.slice(2))

const _dirname = dirname(fileURLToPath(import.meta.url))

function getHostMachine() {

    var platform = process.platform; 
    switch(platform) { 
        case 'darwin':  
            platform = 'macos'
            break; 
        case 'linux':  
            platform = 'linux'
            break; 
        case 'win32': 
            platform = 'windows'
            break;     
        default:  
            platform = undefined
    } 

    return {
        machine: platform,
        arch: process.arch
    }
}

const CWD = process.cwd()
const BUNDLE_PATH = path.join(CWD, "arkoala-har-bundle")
const HAR_PATH = path.join(CWD, "app/arkoala")

function execCmdSync(cmd, options) {
    return execSync(cmd, options).toString().trim().replace("\n", " ")
}

function rollupLaunch() {
    console.log(`> Run rollup`)
    execCmdSync(`npx rollup -c`)
}

function copyFile(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })
}

function main() {

    process.chdir(BUNDLE_PATH)

    rollupLaunch()

    const { machine, arch } = getHostMachine()

    // arm32
    copyFile(path.join(_dirname, `../../../arkoala/framework/build/libc++.so`), path.join(HAR_PATH, `libs/armeabi-v7a/libc++.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-hzvm-ohos-arm32-vmloader/libArkoalaLoader.so`), path.join(HAR_PATH, `libs/armeabi-v7a/libArkoalaLoader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-hzvm-ohos-arm32-vmloader/libvmloader.so`), path.join(HAR_PATH, `libs/armeabi-v7a/libvmloader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-panda-ohos-arm32/libArkoalaNative_ark.so`), path.join(HAR_PATH, `libs/armeabi-v7a/libArkoalaNative_ark.so`))
    copyFile(path.join(_dirname, `../../build/arkoala.abc`), path.join(HAR_PATH, `libs/armeabi-v7a/arkoala.abc.so`))

    // arm64
    copyFile(path.join(_dirname, `../../../arkoala/framework/build/libc++.so`), path.join(HAR_PATH, `libs/arm64-v8a/libc++.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-hzvm-ohos-arm64-vmloader/libArkoalaLoader.so`), path.join(HAR_PATH, `libs/arm64-v8a/libArkoalaLoader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-hzvm-ohos-arm64-vmloader/libvmloader.so`), path.join(HAR_PATH, `libs/arm64-v8a/libvmloader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-panda-ohos-arm64/libArkoalaNative_ark.so`), path.join(HAR_PATH, `libs/arm64-v8a/libArkoalaNative_ark.so`))
    copyFile(path.join(_dirname, `../../build/arkoala.abc`), path.join(HAR_PATH, `libs/arm64-v8a/arkoala.abc.so`))

    // x64
    copyFile(path.join(_dirname, `../../../arkoala/framework/build/libc++.so`), path.join(HAR_PATH, `libs/x86-64/libc++.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/build/ArkoalaLoader.node`), path.join(HAR_PATH, `libs/x86-64/libarkoalaloader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-node-host-vmloader/libvmloader.so`), path.join(HAR_PATH, `libs/x86-64/libvmloader.so`))
    copyFile(path.join(_dirname, `../../../arkoala/framework/native/build-panda-host/libArkoalaNative_${machine}_${arch}_ark.so`), path.join(HAR_PATH, `libs/x86-64/libArkoalaNative_ark.so`))
    copyFile(path.join(_dirname, `../../build/arkoala.abc`), path.join(HAR_PATH, `libs/x86-64/arkoala.abc.so`))
}

main()
