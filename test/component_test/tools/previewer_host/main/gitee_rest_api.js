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
const {
    clearDir, deleteDir, existDir, mkdir, moveDir, readDir, renameDir, isExistFile, copyFile
} = require('../utils/file.js');
const http = require("http");

module.exports = { prepareHostEnv };

async function getPullsNumberComments(url) {
    const response = await fetch(url);
    if (response.ok) {
        const data = await response.json();
        for (let i = 0; i < data.length; i++) {
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
    return new Promise(async (resolve, reject) => {
        const fileStream = fs.createWriteStream(destinationPath);
        const request = await http.get(url, (response) => {
            if (response.statusCode === 404) {
                console.error("当前PR地址已失效，请更换可用的PR地址后重试");
                reject(false);
                return;
            }
            if (response.statusCode !== 200) {
                console.error("下载失败");
                reject(false);
                return;
            }
            response.pipe(fileStream);
            fileStream.on('finish', () => {
                fileStream.close(() => resolve(true));
            });
            fileStream.on('error', (error) => {
                console.error("下载文件错误", error);
                reject(false);
            });
        });
        request.on('error', (error) => {
            console.error("请求出错", error);
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
                resolve();
            });
    });
}

function judgePlatform() {
    return os.platform() === 'win32';
}

async function extractZipFile(zipFilePath, outputDirectory) {
    try {
        await new Promise((resolve, reject) => {
            fs.createReadStream(zipFilePath)
                .pipe(unzipper.Extract({ path: outputDirectory }))
                .on('error', reject)
                .on('finish', () => {
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
                await downloadFile(pullsNumberCommentsResponse.hrefValue,
                    path.join(downloadPath, "ohos-sdk.zip")).then((res, rej) => {
                        if (res) {
                            resolve(true);
                        } else {
                            reject(false);
                        }
                    })
            } else {
                console.error("暂无可用sdk");
                reject(false);
            }
        } catch (error) {
            console.error("下载过程中发生错误");
            reject(false);
        }
    });
}

async function prepareHostEnv(url, downloadPath, sdkPath) {
    try {
        let ohosSdkPath;
        let etsPath = path.join(sdkPath, "ets\\api");
        const existSdk = await existDir(downloadPath);
        if (existSdk) {
            await clearDir(downloadPath);
        } else {
            await mkdir(downloadPath);
        }

        const existSdkPath = await existDir(sdkPath);
        const existBackUpSdkPath = await existDir(`${sdkPath}-backup`);
        if (existBackUpSdkPath) {
            await deleteDir(`${sdkPath}-backup`);
        }
        if (existSdkPath) {
            await renameDir(sdkPath, `${sdkPath}-backup`);
            await mkdir(sdkPath);
        } else {
            await mkdir(sdkPath);
        }
        await downloadSdk(url, downloadPath);
        await extractLargeZip(path.join(downloadPath, "ohos-sdk.zip"), downloadPath);

        if (judgePlatform) {
            ohosSdkPath = path.join(downloadPath, 'windows');
        } else {
            ohosSdkPath = path.join(downloadPath, 'linux');
        }

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
        let etsFile = path.join(etsPath, "@ohos.arkui.componentTest.d.ts");
        if (await isExistFile(etsFile)) {
            await copyFile("previewer_host\\resource\\componentTest.ts", etsFile)
        }
    } catch (error) {
        console.log("准备环境过程出错,恢复初始状态");

        if (await isExistFile(downloadPath)) {
            await clearDir(downloadPath);
        }

        if (await isExistFile(sdkPath)) {
            await deleteDir(sdkPath);
        }

        if (await isExistFile(`${sdkPath}-backup`)) {
            await renameDir(`${sdkPath}-backup`, sdkPath);
        }
        console.log("环境清理完成");
        throw error;
    }
}