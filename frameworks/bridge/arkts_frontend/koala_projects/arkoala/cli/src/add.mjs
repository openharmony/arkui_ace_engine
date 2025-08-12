import path from "path"
import fs from "fs"
import { fileURLToPath } from 'url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

const configFile = JSON.parse(fs.readFileSync(path.join(__dirname, "config.json")))

export async function add(options) {
    if (options.arkoalaPlugin) {
        if (fs.existsSync(options.arkoalaPlugin)) {
            fs.cpSync(options.arkoalaPlugin, path.join(configFile.OHOS_SDK_PATH, "ets/build-tools/ets-loader/lib/fast_build/ets_ui/arkoala-plugin.js"), { recursive: true })
        } else {
            if (fs.existsSync(configFile.ARKOALA_PLUGIN)) {
                fs.cpSync(configFile.ARKOALA_PLUGIN, path.join(configFile.OHOS_SDK_PATH, "ets/build-tools/ets-loader/lib/fast_build/ets_ui/arkoala-plugin.js"), { recursive: true })
            } else {
                throw new Error("arkoala plugin path not valid")
            }
        }
    }
}