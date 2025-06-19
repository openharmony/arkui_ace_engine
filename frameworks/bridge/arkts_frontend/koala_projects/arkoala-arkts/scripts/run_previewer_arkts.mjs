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

import { execSync } from 'child_process'
import path from 'path'
import fs from 'fs'
import { fileURLToPath } from 'url'
import { Command } from 'commander'

// Get current directory
const __filename = fileURLToPath(import.meta.url)
const __dirname = path.dirname(__filename)

// Path to the previewer executable
const PREVIEWER_PATH = path.join(__dirname, '../previewer/previewer/common/bin/Previewer')

// Function to validate and convert the HAP file path provided via --hap flag
function validateHapFilePath(hapFilePath) {
    if (!hapFilePath) {
        throw new Error('HAP file path must be provided using the --hap flag.')
    }
    // If the path is relative, make it absolute based on current working directory
    return path.isAbsolute(hapFilePath) ? hapFilePath : path.join(process.cwd(), hapFilePath)
}

// Function to run the previewer with the specified HAP file
function runPreviewer(hapFilePath) {
    // Check if previewer exists
    if (!fs.existsSync(PREVIEWER_PATH)) {
        console.error(`Error: Previewer not found at ${PREVIEWER_PATH}`)
        console.error('Please run "npm run download-previewer" first to download the previewer.')
        process.exit(1)
    }

    // Check if HAP file exists
    if (!fs.existsSync(hapFilePath)) {
        console.error(`Error: HAP file not found at ${hapFilePath}`)
        console.error('Please specify a valid path to a HAP file.')
        process.exit(1)
    }

    try {
        console.log(`Running previewer with HAP file: ${hapFilePath}`)
        const command = `${PREVIEWER_PATH} -s previewer_serg -gui -hap ${hapFilePath} -refresh region -cpm false -device phone -shape rect -sd 160 -or 432 936 -cr 432 936 -n "entry" -av "ACE_2_0" -url "pages/Index" -pages "main_pages" -d -pm "Stage" -l zh_CN -cm light -o portrait`
        console.log(`Executing command: ${command}`)
        execSync(command, { stdio: 'inherit' })
    } catch (error) {
        console.error(`Error running previewer: ${error.message}`)
        process.exit(1)
    }
}

// Set up command-line options using Commander
const program = new Command()
program
  .option('--hap <hapFilePath>', 'Path to the HAP file')
  .parse(process.argv)

const options = program.opts()

// validate the HAP file path from the --hap flag
const hapFilePath = validateHapFilePath(options.hap)

// Run the previewer with the specified HAP file
runPreviewer(hapFilePath)
