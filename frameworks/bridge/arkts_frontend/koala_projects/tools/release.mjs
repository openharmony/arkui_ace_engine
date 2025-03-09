import fs from "fs"
import path from "path"
import { fileURLToPath } from 'url'
import { execSync } from "child_process"

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)
const EXTERNAL_HOME = path.resolve(path.join(__dirname, ".."))

class Package {
    constructor(path) {
        this.path = path
    }

    name() {
        return this.read("name")
    }

    package() {
        return path.join(this.path, "package.json")
    }

    write(key, value, updater) {
        const json = JSON.parse(fs.readFileSync(this.package(), "utf-8"))
        json[key] = value
        if (updater) updater(json)
        fs.writeFileSync(this.package(), JSON.stringify(json, null, 4), "utf-8")
    }

    read(key) {
        const json = JSON.parse(fs.readFileSync(this.package(), "utf-8"))
        return json[key]
    }

    compile() {
        process.chdir(this.path)
        try {
            execSync(`npm run compile`)
        } catch(e) {
            console.log(`cannot compile package: ${this.name()}`, e)
        }
    }

    publish() {
        process.chdir(this.path)
        publish("next")
    }

    externalDependencies = [
        "@koalaui/build-common",
        "@koalaui/compat",
        "@koalaui/common",
        "@koalaui/harness",
        "@koalaui/runtime",
        "@koalaui/compiler-plugin",
        "@koalaui/ets-plugin",
        "@koalaui/arkui-common",
        "@koalaui/arkoala-arkui",
        "@koalaui/arkui",
        "@koalaui/interop",
    ]
}

const all_packages = [
    new Package(path.join(EXTERNAL_HOME, "incremental/build-common")),
    new Package(path.join(EXTERNAL_HOME, "incremental/compat")),
    new Package(path.join(EXTERNAL_HOME, "incremental/common")),
    new Package(path.join(EXTERNAL_HOME, "incremental/harness")),
    new Package(path.join(EXTERNAL_HOME, "incremental/runtime")),
    new Package(path.join(EXTERNAL_HOME, "incremental/compiler-plugin")),
    // new Package(path.join(EXTERNAL_HOME, "arkoala-arkts/ets-harness")),
    new Package(path.join(EXTERNAL_HOME, "arkoala/ets-plugin")),
    new Package(path.join(EXTERNAL_HOME, "arkoala/arkui-common")),
    new Package(path.join(EXTERNAL_HOME, "arkoala/arkui")),
    new Package(path.join(EXTERNAL_HOME, "interop"))
]

const exclude_packages = [
    "@koalaui/arkui-common",
    "@koalaui/arkoala-arkui",
]

class Version {
    constructor(version) {
        let [major, minor, patch] = version.split(/\./).map(x => +x);
        this.major = major;
        this.minor = minor;
        this.patch = patch;
    }

    up() {
        ++this.patch
        return new Version(`${this.major}.${this.minor}.${this.patch}`)
    }

    down() {
        --this.patch
        return new Version(`${this.major}.${this.minor}.${this.patch}`)
    }

    toString() {
        return `${this.major}.${this.minor}.${this.patch}`
    }
}

const CURRENT_VERSION = readVersion()

function writeVersion(version) {
    fs.writeFileSync(path.join(EXTERNAL_HOME, "VERSION"), version.toString(), "utf-8")
}

function readVersion() {
    const version = fs.readFileSync(path.join(EXTERNAL_HOME, "VERSION"), "utf-8")
    return new Version(version)
}

function publish(tag, dryRun = false) {
    if (dryRun) {
        execSync(`npm publish --dry-run --tag ${tag}`)
    } else {
        execSync(`npm publish --tag ${tag} --access public`)
    }
}

function main() {

    all_packages.forEach(module => module.compile())
    
    const version = CURRENT_VERSION.toString()

    console.log(`> Updating idlize version to ${version}`)

    all_packages.forEach(module => {
        module.write(`version`, `${version}`, (json) => {
            module.externalDependencies.forEach(dep => {
                if (json.dependencies && json.dependencies[dep]) {
                    json.dependencies[dep] = `${version}`
                }
            })
        })
    })

    try {

        all_packages.filter(module => !exclude_packages.includes(module.name()))
                    .map(module => module.publish())
    
        all_packages.forEach(module => {
            module.write(`version`, `${version}+devel`, (json) => {
                module.externalDependencies.forEach(dep => {
                    if (json.dependencies && json.dependencies[dep]) {
                        json.dependencies[dep] = `${version}+devel`
                    }
                })
            })
        })       
    } catch (e) {

        console.log("Error:", e)
        all_packages.forEach(module => {
            module.write(`version`, `${version}+devel`, (json) => {
                module.externalDependencies.forEach(dep => {
                    if (json.dependencies && json.dependencies[dep]) {
                        json.dependencies[dep] = `${version}+devel`
                    }
                })
            })
        })    

    }

}

main()
