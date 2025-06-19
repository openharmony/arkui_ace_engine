import fs from "fs"
import path from "path"

var args = process.argv.slice(2);
const compiler = args[0]

const CWD = process.cwd()

const prebuilt = path.join(CWD, "prebuilt")
const typescriptPath = path.join(CWD, "node_modules/typescript")
const ohosTypescriptPath = path.join(CWD, "node_modules/ohos-typescript")

console.log(compiler)

function copy(from, to) {
    fs.cpSync(from, to, { recursive: true })
}

function rename(oldName, newName) {
    fs.renameSync(path.join(prebuilt, oldName, "bin/tsc"), path.join(prebuilt, oldName, `bin/${newName}`))

    const packageJson = JSON.parse(fs.readFileSync(path.join(prebuilt, oldName, "package.json")))
    packageJson.name = `@koalaui/${newName}`
    packageJson.bin = {[`${newName}`]: `./bin/${newName}`}
    fs.writeFileSync(path.join(prebuilt, oldName, "package.json"), JSON.stringify(packageJson, null, 4), 'utf-8')
}

function main() {

    if (compiler === "memo-tsc") {
        copy(typescriptPath, path.join(prebuilt, "typescript"))
        rename("typescript", "memo-tsc")
    }

    if (compiler === "ets-tsc") {
        copy(ohosTypescriptPath, path.join(prebuilt, "ohos-typescript"))
        rename("ohos-typescript", "ets-tsc")
    }

}

main()
