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

import path from "path"
import fs from "fs"
import { generic_package_archive_gitlab, generic_package_upload_gitlab } from "./gitlab.mjs"
import { moveDirSync } from "./utils.mjs"
import { Command } from "commander"

const command = new Command("gitlab")

command.command("upload")
    .description("Uploads package to gitlab")
    .option("-p --package-name <name>", "package name")
    .option("-a --archive <path>", "path to the archive to upload")
    .option("-v --package-version <version>", "package version", "1.0.0")
    .action(async (options) => {
        await upload(options)
    })

command.command("download")
    .description("Downloads package from gitlab")
    .option("-p --package-name <name>", "package name")
    .option("-f --file-name <name>", "name (with extension) of the file to download")
    .option("-d --destination <path>", "path to the folder to download")
    .option("-v --package-version <version>", "package version", "1.0.0")
    .action(async (options) => {
        await download(options)
    })

command.command("chmod")
    .description("Sets mod bits")
    .requiredOption("-p --path <path>", "path to the file or folder")
    .requiredOption("-b --bits <bits>", "chmod bits")
    .action(async (options) => {
        await chmod(options)
    })

command.parse()

async function download(options) {
    const fileName = path.basename(options.fileName)
    const fileNameNoEx = fileName.split(".")[0]
    await generic_package_archive_gitlab(options.packageName, options.packageVersion, fileName, options.destination, null, true)
    moveDirSync(path.join(options.destination, fileNameNoEx), options.destination)
}

async function upload(options) {
    await generic_package_upload_gitlab(options.packageName, options.packageVersion, options.archive)
}

async function chmod(options) {
    if (fs.lstatSync(options.path).isDirectory()) {
        for (let entry of fs.readdirSync(options.path)) {
            await chmod({
                ...options,
                path: path.join(options.path, entry)
            })
        }
    }
    else {
        fs.chmodSync(options.path, options.bits)
    }
}
