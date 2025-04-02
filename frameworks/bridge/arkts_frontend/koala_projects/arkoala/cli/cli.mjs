#!/usr/bin/env node

import { Command } from 'commander'
import fs from "fs"
import path from "path"
import { fileURLToPath } from 'url'

const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

function init() {
    if (!fs.existsSync(path.join(__dirname, "src/config.json"))) fs.writeFileSync(path.join(__dirname, "src/config.json"), JSON.stringify({}, null, 4), 'utf-8')
}

init()

const app = new Command("arkoala")
    .action(() => {
        console.log("Welcome to Arkoala CLI")
    })

app.command("migrate")
    .description("Migrate from ArkUI project to Arkoala project")
    .action(async (options) => {
        const { migrate } = await import("./src/migrate.mjs")
        await migrate()
    })

app.command("add")
    .description("Adding tools")
    .option("-p, --arkoala-plugin <arkoala-plugin>", "Arkoala plugin path")
    .action(async (options) => {
        const { add } = await import("./src/add.mjs")
        await add(options)
    })

app.command("config")
    .description("Configure for Arkoala project")
    .option("-p, --arkoala-plugin <arkoala-plugin>", "Arkoala plugin path")
    .option("-h, --arkoala-har <arkoala-har>", "Arkoala HAR path")
    .option("--ohos-sdk <ohos-sdk-path>", "OpenHarmony SDK path")
    .action(async (options) => {
        const { config } = await import("./src/config.mjs")
        await config(options)
})

app.command("check")
    .description("Show config")
    .action(async () => {
        const { show } = await import("./src/config.mjs")
        await show()
})

app.parse()