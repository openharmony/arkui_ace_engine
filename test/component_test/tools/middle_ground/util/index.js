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
const spawn = require('child_process').spawn;
const csvParser = require('csv-parser');
const { parseJson } = require("../../previewer_host/utils/json.js");
function readCSVFile() {
    const filePath = 'data.csv';
    const readStream = fs.createReadStream(filePath);
    const rows = [];
    return new Promise((resolve, reject) => {
        readStream.pipe(csvParser())
            .on('data', (row) => {
                rows.push(row);
            })
            .on('end', () => {
                resolve(rows);
            })
            .on('error', (error) => {
                throw error;
            });
    })
}

function promiseRun(list, pr) {
    const hostPath = path.join('./previewer_host/main.js');
    let errorMes;
    return new Promise((resolve, reject) => {
        let path = setFile(JSON.stringify(list));
        let workerProcess = spawn('node', [hostPath, pr, path], { encoding: 'utf-8', stdio: 'pipe' });
        try {
            workerProcess.stdout.on('data', function (data) {
                console.log("stdout:", `${new Date().toTimeString()}-${data.toString()}\n`);
            });
            workerProcess.stderr.on('data', function (data) {
                console.log("stderr:", `${new Date().toTimeString()}-${data.toString()}\n`);
                errorMes += `${formatDate(new Date())}-错误:${data.toString()}\n`;
            });
            workerProcess.on('exit', (code) => {
                if (code === 0) {
                    console.log('执行成功');
                    resolve({ code: 0 });
                } else {
                    console.log('执行失败，退出码：', code);
                    resolve({ code: 1, errorMes: errorMes });
                }
            });
        } catch (error) {
            throw error;
        } finally {
            errorMes = '';
        }
    })
}
function setFile(flieData) {
    const fs = require('fs');
    const data = flieData;
    let jsonData = parseJson('./param.json');
    const filePathData = jsonData.filePathData;


    fs.writeFile(filePathData, data, (err) => {
        if (err) throw err;
    });
    try {
        fs.writeFileSync(filePathData, data);
        return filePathData;
    } catch (err) {
        throw err;
    }
}

function formatDate(date) {
    const year = date.getFullYear();
    const month = date.getMonth() + 1;
    const day = date.getDate();
    const hours = date.getHours();
    const minutes = date.getMinutes();
    const seconds = date.getSeconds();
    let format_date = `${year}-${month}-${day}` +
        `${hours.toString().padStart(2, '0')}` +
        `:${minutes.toString().padStart(2, '0')}` +
        `:${seconds.toString().padStart(2, '0')}`;
    return format_date;
}

module.exports = {
    readCSVFile,
    promiseRun
}