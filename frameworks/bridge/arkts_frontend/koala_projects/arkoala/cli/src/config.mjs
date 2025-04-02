import path from "path"
import fs from "fs"
import { fileURLToPath } from 'url'
import chalk from "chalk"

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const configFile = JSON.parse(fs.readFileSync(path.join(__dirname, "config.json")))

export async function show() {
    console.log("ArkoalaHar:", chalk.green(configFile.ARKOALA_HAR))
    console.log("ArkoalaPlugin:", chalk.green(configFile.ARKOALA_PLUGIN))
    console.log("OhosSDK:", chalk.green(configFile.OHOS_SDK_PATH))
}

export async function config(options) {

    if (options.arkoalaHar) {
        if (!fs.existsSync(options.arkoalaHar)) throw(new Error(`not valid path ${options.arkoalaHar}`))
        configFile.ARKOALA_HAR = options.arkoalaHar       
    }
    if (options.arkoalaPlugin) {
        if (!fs.existsSync(options.arkoalaPlugin)) throw(new Error(`not valid path ${options.arkoalaPlugin}`))
        configFile.ARKOALA_PLUGIN = options.arkoalaPlugin
    }
    if (options.ohosSdk) {
        if (!fs.existsSync(options.ohosSdk)) throw(new Error(`not valid path ${options.ohosSdk}`))
        configFile.OHOS_SDK_PATH = options.ohosSdk
    }

    fs.writeFileSync(path.join(__dirname, "config.json"), JSON.stringify(configFile, null, 4), 'utf-8')
}