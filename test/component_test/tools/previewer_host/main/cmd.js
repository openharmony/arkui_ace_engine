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

const { spawn } = require('child_process');
const path = require('path');
const {
    recursiveCreateFolders,
    copyFile,
    isExistFile,
    writeFile,
    readDir
} = require("../utils/file.js");


const { writeJsonFile } = require("../utils/file");


module.exports = { test, runHvigor };
let origin = 40001;

async function test(sdkPath, testFile, resultPath, casePath, ohpmBat, nodePath, hvigorPath) {
    return new Promise(async (resolve, reject) => {
        const testCasePath = `${casePath}\\test\\component_test\\test_cases\\components\\${testFile[0]}`;
        const previewerExePath = `${sdkPath}\\previewer\\common\\bin`;
        const jParam = `${testCasePath}\\entry\\.preview\\default\\intermediates\\loader_out\\default\\ets`;
        const ljPathParam = `${testCasePath}\\entry\\.preview\\default\\intermediates\\loader\\default\\loader.json`;
        const fParam = `${testCasePath}\\.idea\\previewer\\default\\defaultSettingConfig_Default.json`;
        const arpParam = `${testCasePath}\\entry\\.preview\\default\\intermediates\\res\\default`;
        const urlWithets = `"pages/${testFile[1]}/${testFile[2]}"`;
        const urlParam = urlWithets.split(".ets")[0] + "\"";
        let lwsParam = ++origin;
        const page = `${testFile[0]}\\${testFile[1]}`.replaceAll("\\", "\\\\");
        const out = `${resultPath}\\${testFile[1]}\\${testFile[2]}.json`.replaceAll("\\", "\\\\");
        const componentTestParam = `{\\\"page\\\":\\\"${page}\\\",\\\"out\\\":\\\"${out}\\\"}`;
        runPreviewer(previewerExePath, jParam, ljPathParam, fParam, urlParam, arpParam,
            lwsParam, componentTestParam)
            .then((isOver, error) => {
                if (error) {
                    reject(error);
                } else {
                    resolve(testFile);
                }
            }).catch((err) => {
                if (err) {
                    throw err;
                }
            });
    });
}

const runCommand = (command, args, options) => {
    return new Promise((resolve, reject) => {
        const child = spawn(command, args, { shell: true, ...options });
        if (!child) {
            reject(new Error("Failed to create child process"));
            return;
        }
        let stdoutData = "";
        let stderrData = "";
        child.stdout.on('data', data => {
            stdoutData += data.toString();
        });
        child.stderr.on('data', (data) => {
            stderrData += data.toString();
            if (data.toString().includes("ERROR")) {
                resolve(false)
            }
        });
        child.on('close', code => {
            if (code === 0) {
                resolve(true);
            } else {
                resolve(false);
            }
        });
    });
};

async function runHvigor(sdkPath, testFile, resultPath, casePath, ohpmBat, nodePath, hvigorPath) {
    const testCasePath = `${casePath}\\test\\component_test\\test_cases\\components\\${testFile[0]}`;
    const fParam = `${testCasePath}\\.idea\\previewer\\default\\defaultSettingConfig_Default.json`;
    const caseResultPath = `${resultPath}\\${testFile[2]}.json`.replaceAll("\\", "\\\\");
    runCommand(`"${ohpmBat}"`, [
        'install',
        '--all',
        '--registry',
        'https://ohpm.openharmony.cn/ohpm/',
        '--strict_ssl',
        'true'
    ], { cwd: testCasePath })
        .then(async (isOk, err) => {
            if (err) {
                console.error(err);
            }
            if (!isOk) {
                writeJsonFile("", caseResultPath)
                    .catch(err => {
                        reject(err);
                    });
                resolve(true);
            }
        });

    const localProperties = path.join(testCasePath, "local.properties");
    if (!await isExistFile(localProperties)) {
        let sdkDir = sdkPath.replaceAll("\\", "/");
        let removeLast = sdkDir.replace(/\/\d+$/, '');
        let fileContext = `sdk.dir=${removeLast}`;
        await writeFile(path.join(testCasePath, "local.properties"), fileContext);
    }

    await runCommand(`"${nodePath}"`, [
        `"${hvigorPath}"`,
        '--sync',
        '-p', 'product=default',
        '--analyze=normal',
        '--parallel',
        '--incremental',
        '--daemon'
    ], { cwd: testCasePath })
        .then((isOk, err) => {
            if (err) {
                reject(err);
            }
            if (!isOk) {
                writeJsonFile("", caseResultPath)
                    .catch(err => {
                        reject(err);
                    });
                resolve(true);
            }
        });

    await runCommand(`"${nodePath}"`, [
        `"${hvigorPath}"`,
        '--mode', 'module',
        '-p', 'module=entry@default',
        '-p', 'product=default',
        '-p', 'pageType=page',
        '-p', 'compileResInc=true',
        '-p', 'requiredDeviceType=default',
        '-p', 'previewMode=true',
        '-p', 'buildRoot=.preview',
        'PreviewBuild',
        '--watch',
        '--analyze=normal',
        '--parallel',
        '--incremental',
        '--daemon'
    ], { cwd: testCasePath, shell: true })
        .then((isOk, err) => {
            if (err) {
                reject(err);
            }
            if (!isOk) {
                writeJsonFile("", caseResultPath)
                    .catch(err => {
                        reject(err);
                    });
                resolve(true);
            }
        });

    await recursiveCreateFolders(fParam.split("\\defaultSettingConfig_Default.json")[0]);
    const configFileExists = await isExistFile(fParam);
    if (!configFileExists) {
        await copyFile("previewer_host\\resource\\defaultSettingConfig_Default.json", fParam);
    }
}
async function runPreviewer(
    previewerExePath, jParam, ljPathParam, fParam, urlParam, arpParam, lwsParam, componentTestParam) {
    return new Promise(async (resolve, reject) => {
        const previewerProcess = spawn("Previewer.exe", [
            '-refresh', 'region',
            '-projectID', '908375455',
            '-ts', 'trace_48336_commandPipe',
            '-j', jParam,
            '-s', 'default_1713408574374_1',
            '-cpm', 'false',
            '-device', 'phone',
            '-shape', 'rect',
            '-sd', '480',
            '-ljPath', `"${ljPathParam}"`,
            '-or', '1080', '2340',
            '-cr', '1080', '2340',
            '-f', `"${fParam}"`,
            '-n', '"entry"',
            '-av', '"ACE_2_0"',
            '-url', `${urlParam}`,
            '-pages', '"main_pages"',
            '-arp', `"${arpParam}"`,
            '-pm', '"Stage"',
            '-l', 'zh_CN',
            '-cm', 'light',
            '-o', 'portrait',
            '-lws', lwsParam,
            '-componentTest', `"${componentTestParam}"`
        ], { detached: true, cwd: previewerExePath, shell: true });
        previewerProcess.on('close', (code) => {
            resolve(true);
        });
        previewerProcess.on('error', (err) => {
            reject(err);
        });
    });
}