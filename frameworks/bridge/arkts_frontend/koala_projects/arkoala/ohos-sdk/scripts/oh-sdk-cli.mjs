import { Command, Option } from "commander"
import path from "path"
import url from "url"
import { ohConf } from "./ohconf.mjs"
import {
    downloadOhSdk,
    downloadOhSdkPrebuiltEts,
    downloadCliTools,
    OH_SDK_COMPONENT
} from "./oh-sdk-utils.mjs"

const __dirname = path.dirname(url.fileURLToPath(import.meta.url))
const OHCONF = ohConf(path.join(__dirname, "../.ohconf.json"))

const cmd = new Command("oh-sdk-cli")

cmd.command("download")
    .description("Download OpenHarmony SDK from openlab or gitlab")
    .option("-d, --destination <path>", "destination path", OHCONF.value("ohos_sdk_path", true))
    .addOption(new Option("-s, --sdk-component <type>", "download the specified SDK component only")
        .choices(Object.values(OH_SDK_COMPONENT)))
    .option("-v, --version <version>", "SDK version", OHCONF.sdkVersion())
    .action(async (options) => {
        await downloadOhSdk(options.destination, options.version, options.sdkComponent)
    })

cmd.command("download:prebuilt")
    .description("Download OpenHarmony SDK prebuilt from openlab or gitlab")
    .option("-d, --destination <path>", "destination path", OHCONF.value("ohos_sdk_prebuilt_path", true))
    .option("-v, --version <version>", "SDK version", "5.0.0.17")
    .action(async (options) => {
        await downloadOhSdkPrebuiltEts(options.destination, options.version)
    })

cmd.command("cli-tools")
    .description("Download command-line-tools from openlab or gitlab")
    .option("-d, --destination <path>", "destination path", ".")
    .action(async (options) => {
        await downloadCliTools(options.destination)
    })

cmd.parse()