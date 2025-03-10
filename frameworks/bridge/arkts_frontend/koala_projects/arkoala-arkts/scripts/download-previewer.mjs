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

import fs from "fs"
import path from "path"
import https from "https"
import http from "http"
import { execSync } from "child_process"
import os from "os"
import { Command } from "commander"

let PREVIEWER_URL
const BASE_URL = "https://nexus.bz-openlab.ru:10443/repository/koala-raw/"

// Function to get authentication headers
function getAuth() {
    const NEXUS_NPM_PASS = process.env.NEXUS_NPM_PASS
    const OPENLAB_USERNAME = process.env.OPENLAB_USERNAME
    const OPENLAB_PASSWORD = process.env.OPENLAB_PASSWORD

    if (NEXUS_NPM_PASS)
        return `Basic ${NEXUS_NPM_PASS}`

    if (OPENLAB_USERNAME === undefined) throw new Error(`Environment variable OPENLAB_USERNAME is not specified`)
    if (OPENLAB_PASSWORD === undefined) throw new Error(`Environment variable OPENLAB_PASSWORD is not specified`)
    const authStr = `${OPENLAB_USERNAME}:${OPENLAB_PASSWORD}`
    return `Basic ${Buffer.from(authStr).toString('base64')}`
}

function getHeaders() {
    return {
        'Authorization': getAuth(),
    }
}

// Function to download file
async function download(url, filePath, headers) {
    const protocol = url.startsWith("https") ? https : http

    return new Promise((resolve, reject) => {
        const file = fs.createWriteStream(filePath)
        let fileInfo = null

        let options = {
            headers: headers,
            rejectUnauthorized: false, // TODO: add cert
        }

        file.on('error', err => reject(err))
        file.on('open', () => {
            const request = protocol.request(url, options, response => {
                if (response.statusCode > 300) {
                    fs.unlink(filePath, () => {
                        reject(new Error(`Failed to get '${url}' (${response.statusCode})`))
                    })
                    return
                }
                fileInfo = {
                    mime: response.headers['content-type'],
                    size: parseInt(response.headers['content-length'], 10),
                }
                response.pipe(file)
            })
            request.on('error', err => fs.unlink(filePath, () => reject(err)))
            request.end()
        })
        file.on('finish', () => resolve(fileInfo))
    })
}

// Function to extract archive using system commands
async function extractArchive(inPath, outPath) {
    const ext = path.parse(inPath).ext
    
    // Create output directory if it doesn't exist
    try {
        fs.mkdirSync(outPath, { recursive: true })
    } catch (error) {
        if (error.code === 'EACCES') {
            console.error(`Error: Permission denied to create directory '${outPath}'`)
            console.error('Please choose a directory where you have write permissions.')
            process.exit(1)
        }
        throw error
    }
    
    console.log(`Extracting ${inPath} to ${outPath}`)
    
    if (ext === '.zip') {
        try {
            // Try to use unzip command
            execSync(`unzip -o "${inPath}" -d "${outPath}"`, { stdio: 'inherit' })
        } catch (error) {
            console.error(`Error using unzip command: ${error.message}`)
            console.log("Falling back to Node.js decompression...")
            
            try {
                // Fallback to Node.js decompress
                const decompress = (await import('decompress')).default
                await decompress(inPath, outPath)
            } catch (decompressError) {
                console.error(`Error using Node.js decompression: ${decompressError.message}`)
                console.error('Please install the decompress package with: npm install --save-dev decompress')
                process.exit(1)
            }
        }
    } else if (ext === '.tar' || ext === '.gz') {
        try {
            // Try to use tar command
            execSync(`tar -xf "${inPath}" -C "${outPath}"`, { stdio: 'inherit' })
        } catch (error) {
            console.error(`Error using tar command: ${error.message}`)
            console.log("Falling back to Node.js decompression...")
            
            try {
                // Fallback to Node.js tar
                const tar = await import('tar')
                await tar.x({
                    file: inPath,
                    cwd: outPath
                })
            } catch (tarError) {
                console.error(`Error using Node.js tar decompression: ${tarError.message}`)
                console.error('Please install the tar package with: npm install --save-dev tar')
                process.exit(1)
            }
        }
    } else {
        console.log(`Unknown archive format: ${ext}`)
        process.exit(1)
    }
}

// Function to recursively set executable permissions using Node's API
function setExecutablePermissionsSync(directory) {
    const items = fs.readdirSync(directory)
    for (const item of items) {
        const fullPath = path.join(directory, item)
        const stats = fs.statSync(fullPath)
        if (stats.isDirectory()) {
            setExecutablePermissionsSync(fullPath)
        } else {
            // If file name ends with .sh, set to 755 (rwxr-xr-x)
            if (item.endsWith('.sh')) {
                try {
                    fs.chmodSync(fullPath, 0o755)
                    console.log(`Set executable permissions for ${fullPath}`)
                } catch (err) {
                    console.error(`Failed to chmod ${fullPath}:`, err)
                }
            }
            // Also, if the file already has any execute bit, ensure all execute bits are set.
            else if (stats.mode & 0o111) {
                const newMode = stats.mode | 0o111
                try {
                    fs.chmodSync(fullPath, newMode)
                    console.log(`Updated execute bits for ${fullPath}`)
                } catch (err) {
                    console.error(`Failed to update permissions for ${fullPath}:`, err)
                }
            }
        }
    }
}

// Main function to download and extract previewer
async function downloadPreviewer(destinationPath) {
    // Create destination directory if it doesn't exist
    try {
        fs.mkdirSync(destinationPath, { recursive: true })
    } catch (error) {
        if (error.code === 'EACCES') {
            console.error(`Error: Permission denied to create directory '${destinationPath}'`)
            console.error('Please choose a directory where you have write permissions.')
            process.exit(1)
        }
        throw error
    }
    
    // Get the filename from the URL
    const fileName = path.basename(PREVIEWER_URL)
    const tempFilePath = path.join(fs.mkdtempSync(path.join(os.tmpdir(), 'previewer-')), fileName)
    
    console.log(`Downloading Previewer tools from ${PREVIEWER_URL} to ${destinationPath}`)
    
    try {
        // Download the file
        await download(PREVIEWER_URL, tempFilePath, getHeaders())
        console.log(`Download completed: ${tempFilePath}`)
        
        // Extract the archive
        await extractArchive(tempFilePath, destinationPath)
        console.log(`Extraction completed to ${destinationPath}`)
        
        // Set permissions for executable files using Node's API
        console.log("Setting permissions for executable files...")
        setExecutablePermissionsSync(destinationPath)
        
        console.log(`Previewer tools successfully downloaded and extracted to ${destinationPath}`)
    } catch (error) {
        console.error(`Error downloading or extracting Previewer tools: ${error}`)
        // Clean up temp file if download failed
        if (fs.existsSync(tempFilePath)) {
            fs.unlinkSync(tempFilePath)
        }
        process.exit(1)
    } finally {
        // Clean up temp file
        if (fs.existsSync(tempFilePath)) {
            try {
                fs.unlinkSync(tempFilePath)
            } catch (e) {
                console.warn(`Error cleaning up temporary file ${tempFilePath}: ${e}`)
            }
        }
    }
}

// Set up command line interface
const program = new Command()

program
  .name("download-previewer")
  .description("Download OHOS Previewer tools from Nexus repository")
  .option("-d, --destination <path>", "destination path", path.join(process.cwd(), "previewer"))
  .option("-u, --url <url>", "previewer URL (either a full URL or a relative path)")
  .action(async (options) => {
      if (!options.url) {
          PREVIEWER_URL = "https://nexus.bz-openlab.ru:10443/repository/koala-raw/Previewer/latest/previewer-linux-latest.zip"
      } else {
          // If the provided URL does not start with http, consider it relative
          if (!options.url.startsWith("http")) {
              PREVIEWER_URL = BASE_URL + options.url
          } else {
              PREVIEWER_URL = options.url
          }
      }
      console.log(`Using URL: ${PREVIEWER_URL}`)
      await downloadPreviewer(options.destination)
  })

program.parse(process.argv)
