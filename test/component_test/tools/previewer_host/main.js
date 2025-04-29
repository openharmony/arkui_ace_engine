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

const path = require('path');
const async = require('async');
const { test, runHvigor } = require('./main/cmd.js');
const { prepareHostEnv } = require("./main/gitee_rest_api.js");
const { readDir, deleteDir, renameDir } = require("./utils/file.js");
const { generateHTML } = require("./main/collect_results_and_visualize.js");
const { getDateTime } = require("./utils/date.js");
const { getNodePIDs, deleteNodePIDs } = require("./utils/sys.js");
const { parseJson } = require('./utils/json.js');
const { readJson } = require("./utils/json");

module.exports = { main };

const args = process.argv.slice(2);
const originUrl = args[0];
const testFilePath = args[1];

function Parameters(sdkPath, access_token, downloadPath, resultPath, casePath, devEcoPath, concurrentQuantity) {
    this.sdkPath = sdkPath;
    this.access_token = access_token;
    this.downloadPath = downloadPath;
    this.resultPath = resultPath;
    this.casePath = casePath;
    this.devEcoPath = devEcoPath;
    this.concurrentQuantity = concurrentQuantity;
}

const createQueueWithHvigor = () => {
    return async.queue(async (param, callback) => {
        await runHvigor(param.sdkPath, param.testFile, param.resultPath, param.casePath, param.ohpmBat, param.nodePath
            , param.hvigorPath);
        callback();
    }, 1);
};

const createQueueWithConcurrency = (concurrencyLimit) => {
    return async.queue(async (param, callback) => {
        await test(param.sdkPath, param.testFile, param.resultPath, param.casePath, param.ohpmBat, param.nodePath
            , param.hvigorPath);
        callback();
    }, concurrencyLimit);
};

function TestParam(sdkPath, testFile, resultPath, casePath, ohpmBat, nodePath, hvigorPath) {
    this.sdkPath = sdkPath;
    this.testFile = testFile;
    this.resultPath = resultPath;
    this.casePath = casePath;
    this.ohpmBat = ohpmBat;
    this.nodePath = nodePath;
    this.hvigorPath = hvigorPath;
}

async function run(url, htmlName, testFiles, downloadPath, resultFolder, sdkPath, casePath,
    concurrentQuantity, datetime, ohpmBat, nodePath, hvigorPath) {
    let startTime = new Date().getTime();
    let downloadResultPath = path.join(downloadPath, "downloadResult");
    await prepareHostEnv(url, downloadResultPath, sdkPath)
        .catch(error => {
            throw error;
        });
    let originPIDs = await getNodePIDs();
    let projectName = "";
    const queueHvigor = createQueueWithHvigor();
    for (let i = 0; i < testFiles.length; i++) {
        const resultPath = path.join(resultFolder, datetime, testFiles[i][0]);
        let testFile = testFiles[i];
        if (projectName !== testFile[0]) {
            queueHvigor.push(new TestParam(sdkPath, testFile, resultPath, casePath, ohpmBat, nodePath, hvigorPath));
            projectName = testFile[0];
        }
    }
    queueHvigor.drain(() => {
        const queue = createQueueWithConcurrency(concurrentQuantity);
        for (let i = 0; i < testFiles.length; i++) {
            const resultPath = path.join(resultFolder, datetime, testFiles[i][0]);
            let testFile = testFiles[i];
            queue.push(new TestParam(sdkPath, testFile, resultPath, casePath, ohpmBat, nodePath, hvigorPath));
        }
        queue.drain(async () => {
            const htmlPath = path.join(resultFolder, datetime);
            readDir(htmlPath)
                .then((file, err) => {
                    if (err) {
                        console.error(err);
                    }
                    if (file.length > 0) {
                        generateHTML(htmlPath, htmlName, startTime);
                    } else {
                        console.error('resultPath directory is empty.');
                    }
                });
            getNodePIDs()
                .then((pIds, err) => {
                    if (err) {
                        console.error(err);
                    }
                    let runOverPIDs = [...pIds];
                    for (let i = 0; i < originPIDs.length; i++) {
                        for (let j = 0; j < runOverPIDs.length; j++) {
                            if (originPIDs[i] === runOverPIDs[j]) {
                                runOverPIDs.splice(j, 1);
                            }
                        }
                    }
                    deleteNodePIDs(runOverPIDs)
                        .then((code, err) => {
                            if (err) {
                                console.error(err);
                            }
                        }).catch((error) => {
                            console.error(error);
                        });
                });
            await deleteDir(sdkPath);
            await renameDir(`${sdkPath}-backup`, sdkPath);
        })
    });
}

async function main() {
    const testFiles = await parseJson(testFilePath);
    const datetime = getDateTime();
    let prNumber = originUrl.split("/")[originUrl.split("/").length - 1];
    const htmlName = `${datetime}_${prNumber}.html`;
    let jsonData = parseJson('param.json');
    let param = new Parameters(jsonData.sdkPath, jsonData.access_token, jsonData.downloadPath, jsonData.resultPath,
        jsonData.casePath, jsonData.devEcoPath, jsonData.concurrentQuantity);
    let ohpmBat = `${param.devEcoPath}\\tools\\ohpm\\bin\\ohpm.bat`;
    let nodePath = `${param.devEcoPath}\\tools\\node\\node.exe`;
    let hvigorPath = `${param.devEcoPath}\\tools\\hvigor\\bin\\hvigorw.js`;
    try {
        const evolveUrl = originUrl.slice(18);
        let requestUrl =
            `https://gitee.com/api/v5/repos/${evolveUrl}/comments?access_token=${param.access_token}` +
            `&page=1&per_page=50&direction=desc`;
        await run(requestUrl, htmlName, testFiles, param.downloadPath, param.resultPath, param.sdkPath,
            param.casePath, jsonData.concurrentQuantity, datetime, ohpmBat, nodePath, hvigorPath)
            .catch(err => {
                throw err;
            });
    } catch (err) {
        process.exit(1);
        throw err;
    }
}

main();