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
import chalk from "chalk"
import path from "path"
import url from "url"
import os from "os"
import https from "https"
import http from "http"
import decompress from "decompress"
import * as tar from "tar"

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

export async function extractArchive(inPath, outPath, stripPrefix) {
    console.log(chalk.green(`Extracting ${inPath} to ${outPath}...`))

    const ext = path.parse(inPath).ext
    let result
    switch(ext) {
        case ".zip":
            result = extractZip(inPath, outPath, stripPrefix)
            break
        case ".tar":
            result = extractTar(inPath, outPath, stripPrefix)
            break
        case ".gz":
            result = extractTar(inPath, outPath, stripPrefix)
            break
        default:
            result = Promise.resolve()
    }
    return result.catch(error => {
        console.log(chalk.red(error.message ?? error))
        throw error
    })
}

async function extractZip(inPath, outPath, stripPrefix) {
    return new Promise((resolve, reject) => {
        let options = {}
        if (stripPrefix) {
            if (!stripPrefix.endsWith("/")) stripPrefix += "/"
            options.map = file => {
                if (file.path.startsWith(stripPrefix)) file.path = file.path.slice(stripPrefix.length)
                return file
            }
        }

        decompress(inPath, outPath, options).then(() => resolve()).catch(err => reject(err))
    })
}

async function extractTar(inPath, outPath, stripPrefix) {
    var strip = 0
    if (stripPrefix) {
        if (!stripPrefix.endsWith("/")) stripPrefix += "/"
        strip = stripPrefix.split("/").length - 1
    }
    return tar.x({
        file: inPath,
        strip: strip,
        C: outPath
    })
}

export async function http_file(httpUrl, outDir, fileName = null, headers = null) {
    console.log(chalk.green(`Downloading ${httpUrl} -> ${outDir}`))

    fs.mkdirSync(outDir, {overwrite: true, recursive: true})
    await download(httpUrl, `${outDir}/${fileName}`, headers)
}

function sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms))
}

function basename(fileName) {
    if (fileName.endsWith(".zip") || fileName.endsWith(".tgz")) return fileName.substring(0, fileName.length - 4)
    else if (fileName.endsWith(".tar.gz")) return fileName.substring(0, fileName.length - 7)
    else throw new Error("Unsupported file type for: " + fileName)
}

export async function http_archive(httpUrl, outDir, stripPrefix = null, headers = null, copy = false) {
    let fileName = path.basename(url.parse(httpUrl).pathname)
    fileName = fileName.replaceAll(":", "_") // todo: validate the file name is correct
    fs.mkdirSync(outDir, {overwrite: true, recursive: true})

    if (process.env.HTTP_CACHE_DIR) {
        let cachedFilePath = path.join(process.env.HTTP_CACHE_DIR, fileName)
        let cachedDir = path.join(process.env.HTTP_CACHE_DIR, "unzip", basename(fileName))
        let lockFile = cachedFilePath + ".lock"

        while(true) {
            if (fs.existsSync(cachedDir) && !fs.existsSync(lockFile)) {
                if (copy) { // Make a copy
                    console.log(chalk.green(`Make copy to ${outDir} from ${cachedDir}`))
                    fs.cpSync(cachedDir, outDir, {recursive: true})
                } else { // Make symlinks
                    fs.readdirSync(cachedDir).forEach(file => {
                        let src = path.join(cachedDir, file)
                        let dest = path.join(outDir, file)
                        console.log(chalk.green(`Make symlink to ${src} from ${dest}`))
                        try {
                            fs.symlinkSync(src, dest)
                        } catch (err) {
                            console.log(err)
                        }
                    })
                }
                break
            } else {
                try {
                    fs.mkdirSync(lockFile)

                    console.log(chalk.green(`Downloading ${httpUrl} to ${cachedFilePath}`))
                    await download(httpUrl, cachedFilePath, headers).catch(err => {
                        console.error("Download error: " + err + ", remove cachedFile:" + cachedFilePath)
                        fs.rmdirSync(lockFile)
                        fs.unlinkSync(cachedFilePath)
                    })

                    console.log(chalk.green(`Unzipping ${cachedFilePath} to ${cachedDir}`))
                    await extractArchive(cachedFilePath, cachedDir, stripPrefix).then(() => {
                        console.log("Remove lock file: " + lockFile)
                        fs.rmdirSync(lockFile)
                    })

                } catch (err) {
                    if (err.code == "EEXIST") {
                        let counter = 0
                        while (fs.existsSync(lockFile)) {
                            await sleep(1000)
                            if (++counter % 5 == 0)
                                console.log("Waiting for " + lockFile + " to be deleted: " + counter + " secs.")
                        }
                        console.log(lockFile + " deleted in " + counter + " secs.")
                    } else {
                        throw err
                    }
                }
            }
        }
    } else {
        /* download in tmp */
        let tmp = (!process.env.BUILD_DIR) ?
            path.resolve(path.join(os.tmpdir(), fileName)) :
            path.resolve(path.join(process.env.BUILD_DIR, fileName))

        console.log(chalk.green(`Downloading ${httpUrl} to ${outDir} (${tmp})`))

        if (fs.existsSync(tmp)) {
            console.log(`Already downloaded, reuse ${tmp}`)
        } else {
            await download(httpUrl, tmp, headers)
        }
        await extractArchive(tmp, outDir, stripPrefix).catch(async () => {
            console.log(chalk.green(`Downloading ${httpUrl} anew...`))
            // update the cached archive
            await download(httpUrl, tmp, headers)
            // and make another attempt
            await extractArchive(tmp, outDir, stripPrefix).catch(() => process.exit(1))
        })
    }
}