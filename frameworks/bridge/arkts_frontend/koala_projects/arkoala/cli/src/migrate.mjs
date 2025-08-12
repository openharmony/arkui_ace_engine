import path from "path"
import fs from "fs"
import { fileURLToPath } from 'url'
import { Project } from "./project.mjs"

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const config = JSON.parse(fs.readFileSync(path.join(__dirname, "config.json")))

const arkoalaPlugin = {
    name: "ArkoalaPlugin",
    value: true
}

const tsCheckApi11 = {
    name: 'Api11ArkTSCheck',
    value: 'SkipArkTSCheckInApi11'
}

const tsCheck = {
    name: 'ArkTSCheck',
    value: 'SkipArkTSCheck',
}

export async function migrate() {
    const project = new Project()

    const metadata = [arkoalaPlugin, tsCheck, tsCheckApi11]
    project.addMetadata(metadata)

    if (!fs.existsSync(config.ARKOALA_HAR)) throw new Error(`not valid arkoala har path ${config.ARKOALA_HAR}`)
    project.addDependency({"@koalaui/arkoala-arkui": `file://${config.ARKOALA_HAR}`})
}
