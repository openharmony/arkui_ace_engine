/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

const fs = require('fs');
const path = require('path');
const { JSDOM } = require('jsdom');
const os = require('os');
const unzipper = require('unzipper');
const { clearDir, deleteDir, existDir, mkdir, moveDir, readDir, renameDir } = require('../utils/file.js');
const http = require("http");

module.exports = { prepareHostEnv };

async function getPullsNumberComments(url) {
    const response = await fetch(url);
    if (response.ok) {
        const data = await response.json();
        for (let i = 0; i < data.length; i++) {
            const date = new Date(data[i].updated_at);
            if (data[i].body.includes("代码门禁通过")) {
                const dom = new JSDOM(data[i].body);
                const document = dom.window.document;
                const anchors = document.getElementsByTagName('a');
                for (let j = 0; j < anchors.length; j++) {
                    const anchor = anchors[j];
                    const hrefValue = anchor.href;
                    if (hrefValue.includes("ohos-sdk") && hrefValue.includes(".zip")) {
                        return { status: response.status, data, hrefValue };
                    }
                }
            }
        }
    } else {
        throw new Error(`HTTP状态码${response.status},请求URL为${url}`);
    }
    return null;
}

async function downloadFile(url, destinationPath) {
    return new Promise((resolve, reject) => {
        const fileStream = fs.createWriteStream(destinationPath);
        const request = http.get(url, (response) => {
            if (response.statusCode !== 200) {
                reject(false);
            } else {
                console.log("开始下载");
                response.pipe(fileStream);
                fileStream.on('finish', () => {
                    fileStream.close();
                    resolve(true);
                });
            }
        });
        request.on('error', (error) => {
            reject(false);
        });
    });
}

async function extractLargeZip(zipFilePath, outputDir) {
    return new Promise((resolve, reject) => {
        const readStream = fs.createReadStream(zipFilePath);
        readStream.pipe(unzipper.Parse())
            .on('entry', (entry) => {
                const fileName = entry.path;
                const type = entry.type;

                if (type === 'File') {
                    const outputPath = path.join(outputDir, fileName);
                    entry.pipe(fs.createWriteStream(outputPath));
                } else if (type === 'Directory') {
                    fs.mkdirSync(path.join(outputDir, fileName), { recursive: true });
                    entry.autodrain();
                }
            })
            .on('error', (error) => {
                throw error;
            })
            .on('close', () => {
                console.log('解压完成');
                resolve();
            });
    });
}

function judgePlatform() {
    return os.platform() === 'win32';
}

async function extractZipFile(zipFilePath, outputDirectory) {
    console.log('zip 文件路径:', zipFilePath);
    console.log('输出目录:', outputDirectory);
    try {
        await new Promise((resolve, reject) => {
            fs.createReadStream(zipFilePath)
                .pipe(unzipper.Extract({ path: outputDirectory }))
                .on('error', reject)
                .on('finish', () => {
                    console.log('解压完成');
                    resolve();
                });
        });
    } catch (err) {
        throw err;
    }
    if (!fs.existsSync(outputDirectory)) {
        fs.mkdirSync(outputDirectory, { recursive: true });
    }
}

async function downloadSdk(url, downloadPath) {
    return new Promise(async (resolve, reject) => {
        try {
            const pullsNumberCommentsResponse = await getPullsNumberComments(url);
            if (pullsNumberCommentsResponse !== null && pullsNumberCommentsResponse.hrefValue !== "") {
                const downloadResult = await downloadFile(
                    pullsNumberCommentsResponse.hrefValue, path.join(downloadPath, "ohos-sdk.zip"));
                resolve(downloadResult);
            } else {
                console.warn("暂时没有ohos-sdk");
            }
        } catch (error) {
            throw error;
        }
    });
}

async function prepareHostEnv(url, downloadPath, sdkPath) {
    try {
        const existSdk = await existDir(downloadPath);
        if (existSdk) {
            console.log(`清空${downloadPath}文件夹`);
            await clearDir(downloadPath);
        } else {
            console.log(`创建${downloadPath}文件夹`);
            await mkdir(downloadPath);
        }

        const existSdkPath = await existDir(sdkPath);
        if (existSdkPath) {
            console.log(`备份${sdkPath}文件夹`);
            await renameDir(sdkPath, `${sdkPath}-backup`);
            await mkdir(sdkPath);
        } else {
            console.log(`创建${sdkPath}文件夹`);
            await mkdir(sdkPath);
        }

        const downloadResult = await downloadSdk(url, downloadPath);
        console.log("SDK下载成功:", downloadResult);
        console.log("解压下载的文件");

        await extractLargeZip(path.join(downloadPath, "ohos-sdk.zip"), downloadPath);

        let ohosSdkPath;
        if (judgePlatform) {
            ohosSdkPath = path.join(downloadPath, 'ohos-sdk\\windows');
        } else {
            ohosSdkPath = path.join(downloadPath, 'ohos-sdk\\linux');
        }
        console.log(`当前操作系统是${os.platform()}`);

        let zipFiles = await readDir(ohosSdkPath);
        for (let i = 0; i < zipFiles.length; i++) {
            await extractZipFile(zipFiles[i], ohosSdkPath);
        }

        let sdks = await readDir(ohosSdkPath);
        for (let i = 0; i < sdks.length; i++) {
            if (sdks[i].includes(".zip") !== true) {
                await moveDir(sdks[i], sdkPath);
            }
        }
        await deleteDir(downloadPath);
    } catch (error) {
        throw error;
    }
}