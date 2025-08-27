import { execSync } from "child_process"
import { dirname } from "path"
import { fileURLToPath } from "url"

import fs from "fs"
import path from "path"
import process from "process"
import minimist from "minimist"

var args = minimist(process.argv.slice(2))
const name = args["name"]

const _dirname = dirname(fileURLToPath(import.meta.url))

const CWD = process.cwd()
const HAR_PATH = path.join(CWD, `app/${name}`)


function copyFile(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })
}


function main() {
    // arm32
    copyFile(path.join(_dirname, `../build/${name}.abc`), path.join(HAR_PATH, `libs/armeabi-v7a/${name}.abc.so`))

    // arm64
    copyFile(path.join(_dirname, `../build/${name}.abc`), path.join(HAR_PATH, `libs/arm64-v8a/${name}.abc.so`))

    //x64
    copyFile(path.join(_dirname, `../build/${name}.abc`), path.join(HAR_PATH, `libs/x86-64/${name}.abc.so`))
}

main()
