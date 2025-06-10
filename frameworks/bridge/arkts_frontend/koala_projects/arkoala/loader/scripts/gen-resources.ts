/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import * as fs from "fs"
import * as path from "path"
import { spawnSync } from "child_process"

process.on("uncaughtException", e => {
    console.error(e.message || e)
    process.exit(1)
})

const ohosSdkPath = findOhosSdk()
const srcPath = path.resolve("src")
const buildDir = path.resolve("build")
const generatedDir = path.resolve("generated/ets")
const generatedFile = "__resources.generated.ts"
const buildResourceDir = path.join(buildDir, "resources")

if (process.env.CI) {
    const generatedFileTemplatePath = path.join(__dirname, "ci-templates", generatedFile)
    // restool is not currently runnable on CI due to arch mismatch
    console.warn("warning: use predefined template", generatedFileTemplatePath)
    fs.mkdirSync(generatedDir, { recursive: true })
    fs.copyFileSync(generatedFileTemplatePath, path.join(generatedDir, generatedFile))
    process.exit(0)
}

console.log("OHOS SDK at ", ohosSdkPath)

const PACKAGE_NAME = "ohos.arkoala"

runRestool(srcPath, buildResourceDir, PACKAGE_NAME) // TODO remove hardcoded values

let moduleInfo = readModuleManifest(path.join(buildResourceDir, "module.json")) // TODO generated module.json differs from DevEco, run generator
let entries = readResourceTable(path.join(buildResourceDir, "ResourceTable.txt"))

writeTypescriptSource(path.join(generatedDir, generatedFile), moduleInfo, entries);

interface ResourceTableEntry {
    type: string
    name: string
    id: number
}

interface ModuleInfo {
    bundleName: string
    moduleName: string
}

function readResourceTable(filepath: string): ResourceTableEntry[] {
    let content = fs.readFileSync(filepath, "utf-8").trim()
    let lines = content.split(/(\r?\n)+/gm)

    let entries: ResourceTableEntry[] = []
    for (const line of lines) {
        let items = line.trim().split(/\s+/g);
        if (items.length === 0 || items[0] === "") continue;

        if (items.length !== 3) {
            throw new Error(`Illegal resource table format (at line '${items}')`)
        }

        const [type, name, idStr] = items
        if (!/^0x[0-9A-Fa-f]{8}$/i.test(idStr)) { // int32 in hex, 0xFFFFFFFF
            throw new Error(`Illegal resource id: ${idStr}`)
        }

        const id = parseInt(idStr, 16)

        entries.push({ type, name, id })
    }

    return entries
}

function readModuleManifest(filepath: string): ModuleInfo {
    let json = fs.readFileSync(filepath, "utf-8").trim()
    let manifest = JSON.parse(json)
    let moduleName = manifest.module.name
    let bundleName = manifest.app?.bundleName ?? PACKAGE_NAME // TODO remove hardcoded constant

    return { moduleName, bundleName }
}

function makeResourceMap(resources: ResourceTableEntry[]): Record<string, number> {
    let output = {};
    for (const {type, name, id} of resources) {
        let key = type + "." + name
        if (key in output) {
            throw new Error(`Duplicated resource key: ${key}`)
        }
        output[key] = id
    }

    return output
}

interface CodegenOptions {
    arkoalaImport?: string
}

function writeTypescriptSource(filepath: string, module: ModuleInfo, resources: ResourceTableEntry[], options: CodegenOptions = {}) {
    const importString = options.arkoalaImport ?? "@koalaui/arkoala-arkui"
    const resourceMap = makeResourceMap(resources)

    fs.mkdirSync(path.dirname(filepath), { recursive: true })
    let out = fs.createWriteStream(filepath, "utf-8")

    out.write(`// THIS CODE WAS AUTOMATICALLY GENERATED, DO NOT MODIFY\n\n`)
    out.write(`import { __registerResources, _r, _rawfile } from ${JSON.stringify(importString)};\n\n`)
    out.write(`const bundleName: string = ${JSON.stringify(module.bundleName)};\n`)
    out.write(`const moduleName: string = ${JSON.stringify(module.moduleName)};\n`)
    out.write(`const resources: Record<string, number> = ${JSON.stringify(resourceMap, null, 4)};\n\n`)
    out.write(`__registerResources(bundleName, moduleName, resources);\n`);
    out.write(`export function $r(name: string, ...args: any[]) { return _r(name, ...args) };\n`);
    out.write(`export function $rawfile(name: string) { return _rawfile(name) };\n`);

    out.end()
}

function runRestool(srcDir: string, destDir: string, packageName: string, startIdMask = 0x01000000) {
    let restoolExe = path.join(ohosSdkPath, "toolchains/restool" + (process.platform === "win32" ? ".exe" : ""));
    let src = process.env["ETS_RESOURCES_SRC"] ?? path.resolve(srcDir)
    let dst = path.resolve(destDir)
    fs.mkdirSync(dst, { recursive: true })
    let headerPath = path.join(dst, "ResourceTable.h")
    let startId = "0x" + startIdMask.toString(16).toUpperCase().padStart(8, "0")

    const restoolArgs = ["-i", src, "-o", dst, "-p", packageName, "-r", headerPath, "-e", startId, "-f"]
    console.log("-------------- restool -------------------")
    console.log(restoolExe, restoolArgs.join(" "))
    let result = spawnSync(restoolExe, restoolArgs, {
        stdio: "inherit"
    })
    console.log("-------------- restool -------------------")
}
function findOhosSdk() {
    const API_VERSION = "11"

    if (process.env["HOS_SDK_HOME"]) {
        return path.resolve(process.env["HOS_SDK_HOME"])
    }

    let repositoryPath = path.resolve("../ohos-sdk/ohos-sdk/HarmonyOS-NEXT-DB1/openharmony")
    if (fs.existsSync(repositoryPath)) {
        return repositoryPath
    }

    if (process.env["LOCALAPPDATA"]) {
        let osDefaultPath = path.join(process.env["LOCALAPPDATA"]!, "OpenHarmony/Sdk/" + API_VERSION)
        if (fs.existsSync(osDefaultPath)) {
            return osDefaultPath
        }
    }

    throw new Error("No OHOS SDK found, please provide HOS_SDK_HOME variable set to OpenHarmony SDK 10 directory path")
}