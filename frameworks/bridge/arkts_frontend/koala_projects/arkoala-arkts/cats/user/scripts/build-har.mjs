import { execSync } from "child_process"
import { dirname } from "path"
import { fileURLToPath } from "url"

import fs from "fs"
import path from "path"
import process from "process"
import minimist from "minimist"

var args = minimist(process.argv.slice(2))
const arch = args["arch"]
const name = args["name"]

const _dirname = dirname(fileURLToPath(import.meta.url))

const CWD = process.cwd()
const HAR_PATH = path.join(CWD, `app/${name}`)

function execCmdSync(cmd, options) {
    return execSync(cmd, options).toString().trim().replace("\n", " ")
}

function rollupLaunch() {
    console.log(`> Run rollup`)
    execCmdSync("npx rollup -c")
}

function copyFilesToHar(from, to) {
    if (!fs.existsSync(from)) {
        throw new Error(`file ${from} does not exist`)
    }

    console.log(`> Copy from: ${from} to ${to}`)
    fs.cpSync(from, to, { recursive: true, force: true })
}


function main(targetLibDir, name) {
    copyFilesToHar(path.join(_dirname, `../build/${name}.abc`), path.join(HAR_PATH, `libs/${targetLibDir}/${name}.abc.so`))
}

if (arch == "arm32") {
    main("armeabi-v7a", name)
} else if (arch == "arm64") {
    main("arm64-v8a", name)
} else {
    console.log("Unsupported architecture: ", arch)
    exit(1)
}
