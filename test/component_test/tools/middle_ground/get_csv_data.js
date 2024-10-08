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

const fs = require("fs").promises;
const path = require("path");
const {createObjectCsvWriter} = require('csv-writer');
const {parseJson} = require('../previewer_host/utils/json');

let jsonData = parseJson('param.json');
let casePath = jsonData.casePath;

async function getFolders(filePath) {
    try {
        return await fs.readdir(filePath);
    } catch (err) {
        throw err;
    }
}

async function createCsvData(casePath) {
    const csvContext = [];
    let index = 1;
    const projectPath = path.join(casePath, "test", "component_test", "test_cases", "components");

    try {
        const projectNames = await getFolders(projectPath);
        for (let i = 0; i < projectNames.length; i++) {
            const componentName = await getFolders(path.join(projectPath,
                projectNames[i], "entry", "src", "main", "ets", "pages"));

            for (let j = 0; j < componentName.length; j++) {
                if (!componentName[j].includes(".") && componentName[j] !== "MyTest") {
                    const fileNames = await getFolders(path.join(projectPath, projectNames[i],
                        "entry", "src", "main", "ets", "pages", componentName[j]));
                    for (let k = 0; k < fileNames.length; k++) {
                        if (fileNames[k].includes(".ets")) {
                            if (!fileNames[k].includes("Home")) {
                                csvContext.push({
                                    projectName: projectNames[i],
                                    componentName: componentName[j],
                                    fileName: fileNames[k],
                                    id: index
                                });
                                index++;
                            }
                        }
                    }
                }
            }
        }

        const csvWriter = createObjectCsvWriter({
            path: path.join(__dirname, '..', 'data.csv'),
            header: [
                {id: 'projectName', title: 'Project Name'},
                {id: 'componentName', title: 'Component Name'},
                {id: 'fileName', title: 'File Name'},
                {id: 'id', title: 'id'}
            ]
        });

        await csvWriter.writeRecords(csvContext)
            .then(() => console.log("CSV文件已生成"))
            .catch(err => console.error("生成CSV文件时出错:", err));
    } catch (err) {
        console.error(err);
    }
}

createCsvData(casePath);