#!/usr/bin/env node

/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { Command } from "commander"
import path from "path"
import { fileURLToPath } from 'url'
import { ensureEnvVarSet, assertExists } from "./utils.mjs"

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

ensureEnvVarSet("DEVECO_TOOLS_HOME", path.join(__dirname, "../../har/command-line-tools"), true)
assertExists(process.env.DEVECO_TOOLS_HOME)
ensureEnvVarSet("DEVECO_SDK_HOME", path.join(__dirname, "../ohos-sdk"), true)
assertExists(process.env.DEVECO_SDK_HOME)

const app = new Command("arkoala")

app.command("oh-sign")
    .description("Sign the OpenHarmony project hap file")
    .option("-m, --mod <mod>", "project mode: app, test", "app")
    // .option("-c, --oh-conf <path>", "path to .ohconf.json", "./.ohconf.json")
    .action(async (options) => {
        const { sign } = await import("./ohos-app/sign.mjs")
        await sign(options)
    })

app.command("oh-build")
    .description("Build the OpenHarmony project")
    .option("-m, --mod <mod>", "project mode: app, test", "app")
    // .option("-c, --oh-conf <path>", "path to .ohconf.json", "./.ohconf.json")
    // .option("-s, --sync", "sync the project config ws well")
    // .option("--sync-only", "sync the project config only")
    .option("-i, --install-ohpm-deps", "install ohpm dependencies as well")
    .option("--install-ohpm-deps-only", "install ohpm dependencies only")
    .option("-s, --sign", "sign the project as well")
    .option("-r, --run", "install and run the app on device as well")
    .option("-a, --all", "equivalent of -i -s -r")
    .option("-e, --extra-options <opts>", "comma-separated pass extra options")
    .option("-V, --verbose", "log commands")
    .action(async (options) => {
        const { build } = await import("./ohos-app/build.mjs")
        if (options.all) {
            options.installOhpmDeps = true
            options.sign = true
            options.run = true
        }
        await build(options)
        if (options.sign) {
            const { sign } = await import("./ohos-app/sign.mjs")
            await sign(options)
        }
        if (options.run) {
            const { install, run } = await import("./ohos-app/exec-on-device.mjs")
            await install(options)
            await run(options)
        }
    })

app.command("oh-log")
    .description("Log the OpenHarmony project")
    .option("-a, --all", "show all log")
    .option("-b, --bundle-name <name>", "show log by application bundle name")
    .action(async (options) => {
        const { log } = await import("./ohos-app/log.mjs")
        await log(options)
    })

app.command("oh-exec")
    .description("Execute an instruction on an OpenHarmony device")
    .option("-i, --install", "install the project hap file on a device")
    .option("-u, --uninstall", "uninstall the project hap file from a device")
    .option("-r, --run", "run the project app on a device")
    .option("-t, --run-timeout <timeout>", "run the project app on a device with timeout in ms")
    .option("-m, --mod <mod>", "project mode: app, test", "app")
    // .option("-c, --oh-conf <path>", "path to .ohconf.json", "./.ohconf.json")
    .option("-l, --list-devices", "list connected devices")
    .option("-o, --hdc-extra-opts <opts>", "extra options to pass to the HDC tool")
    .option("-V, --verbose", "log commands")
    .option("-e, --extra <opts>", "extra options which will be added to hdc command if supported", "")
    .action(async (options) => {
        const { install, uninstall, run } = await import("./ohos-app/exec-on-device.mjs")

        if (options.install)
            await install(options)
        if (options.uninstall)
            await uninstall(options)
        if (options.run || options.runTimeout)
            await run(options)
    })

app.parse()