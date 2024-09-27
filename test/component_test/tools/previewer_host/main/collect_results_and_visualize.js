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
const { readDir } = require("../utils/file.js");
const { parseJson } = require("../utils/json.js");
const { getRunTime } = require("../utils/date.js");
const path = require("path");

module.exports = { generateHTML };

function getJsonData(filePaths) {
    let jsonData = parseJson(filePaths);
    if (jsonData === 3) {
        return 3;
    }
    return jsonData.result;
}

async function getNotPassJson(filePaths) {
    let notPassArr = [];
    for (let i = 0; i < filePaths.length; i++) {
        if (!filePaths[i].includes(".")) {
            const testComponentNameFolder = await readDir(filePaths[i]);
            for (let j = 0; j < testComponentNameFolder.length; j++) {
                const testTypeNameFolder = await readDir(testComponentNameFolder[j]);
                for (let k = 0; k < testTypeNameFolder.length; k++) {
                    let jsonData = parseJson(testTypeNameFolder[k]);
                    if (jsonData.result !== 0) {
                        let componentNames = testComponentNameFolder[j].split("\\");
                        let componentName = componentNames[componentNames.length - 1];
                        let testResult = {
                            ComponentName: componentName,
                            CaseName: "",
                            CodeLine: "",
                            Message: "",
                            Result: "",
                        };
                        if (jsonData === 3) {
                            testResult.CaseName = testTypeNameFolder[k];
                            testResult.CodeLine = "not run";
                            testResult.Message = "not run";
                            testResult.Result = "not run";
                        } else {
                            testResult.CaseName = jsonData.test_case_name;
                            testResult.CodeLine = jsonData.error_position;
                            testResult.Message = jsonData.message;
                            testResult.Result = jsonData.result === 1 ? "Fail" : "Error";
                        }
                        notPassArr.push(testResult);
                    }
                }
            }
        }
    }
    return notPassArr;
}

async function createStackedBarChartData(filePaths) {
    const yAxisData = [];
    const passCounts = [];
    const failCounts = [];
    const errorCounts = [];
    const notRunCounts = [];
    let passData = 0;
    let failData = 0;
    let errorData = 0;
    let notRunData = 0;
    let caseCount;

    const dataCollection = new Map();
    const testTypeNameFolder = await readDir(filePaths);
    for (let i = 0; i < testTypeNameFolder.length; i++) {
        if (!testTypeNameFolder[i].includes(".")) {
            let folderContext = testTypeNameFolder[i].split("\\");
            let yName = folderContext[folderContext.length - 1];
            let passCount = 0;
            let failCount = 0;
            let errorCount = 0;
            let notRunCount = 0;
            yAxisData.push(yName);
            const TypeFiles = await readDir(testTypeNameFolder[i]);
            for (let k = 0; k < TypeFiles.length; k++) {
                const jsonFiles = await readDir(TypeFiles[k]);
                for (let j = 0; j < jsonFiles.length; j++) {
                    let result = getJsonData(jsonFiles[j]);
                    switch (result) {
                        case 0:
                            passCount++;
                            break;
                        case 1:
                            failCount++;
                            break;
                        case 2:
                            errorCount++;
                            break;
                        case 3:
                            notRunCount++;
                            break;
                    }
                }
            }
            passCounts.push(passCount);
            failCounts.push(failCount);
            errorCounts.push(errorCount);
            notRunCounts.push(notRunCount);
        }
    }
    const seriesData = [
        {
            name: 'Pass',
            type: 'bar',
            stack: 'stack',
            data: passCounts,
            color: '#5cb85c',
        },
        {
            name: 'Fail',
            type: 'bar',
            stack: 'stack',
            data: failCounts,
            color: '#d9534f',
        },
        {
            name: 'Error',
            type: 'bar',
            stack: 'stack',
            data: errorCounts,
            color: '#f0ad4e',
        },
        {
            name: 'not run',
            type: 'bar',
            stack: 'stack',
            data: notRunCounts,
            color: '#808080',
        }
    ];
    passCounts.forEach(element => {
        passData = passData + element;
    });
    dataCollection.set("passCounts", passData);

    failCounts.forEach(element => {
        failData = failData + element;
    });
    dataCollection.set("failCounts", failData);

    errorCounts.forEach(element => {
        errorData = errorData + element;
    });
    dataCollection.set("errorCounts", errorData);

    notRunCounts.forEach(element => {
        notRunData = notRunData + element;
    });
    dataCollection.set("notRunCounts", notRunData);

    caseCount = dataCollection.get('passCounts') + dataCollection.get('failCounts') + dataCollection.get('errorCounts')
        + dataCollection.get('notRunCounts');
    dataCollection.set("caseCount", caseCount);

    return {
        yAxisData: yAxisData,
        seriesData: seriesData,
        dataCollection: dataCollection,
    };
}


async function generateHTML(resultPath, htmlName, startTime) {
    let files = await readDir(resultPath);
    let barChart = await createStackedBarChartData(resultPath);
    let list = await getNotPassJson(files);
    let formattedTime = getRunTime(startTime);
    const htmlContent = `
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>测试结果</title>
            <style>
                #table {
                    min-width: 98%;
                    max-width: 99%;
                    border-collapse: collapse;
                }
                #table tr {
                    border-bottom: 1px solid #ddd;
                }
                #table th, #table td {
                    padding: 10px;
                    text-align: left;
                    border: 1px solid #ddd;
                    word-break: break-all;
                }
                #table th {
                    background-color: #f2f2f2;
                    font-weight: bold;
                }
                #table tr:nth-child(even) {
                    background-color: #f2f2f2;
                }
                #res{
                    width:70px;
                }
                #cn{
                    width:150px;
                }
            </style>
        </head>
        <body id="body" style="width: 100%;">
            <div id="chart" style="width: 80%; height: 80%;"></div>
            <script src="https://cdn.staticfile.org/echarts/4.3.0/echarts.min.js"></script>
            <script>
                var bodyElement = document.getElementById('body');
                bodyElement.style.height = ${JSON.stringify(barChart.yAxisData)}.length*110 + 'px';
                var chart = echarts.init(document.getElementById('chart'));
                var option = {
                    title:{
                        text: '测试结果'
                    },
                    legend: {},
                    tooltip: {},
                    xAxis: {
                        minInterval: 1,
                        axisLine: {
                            show: true,
                        },
                        axisTick: {  
                            show: false,
                            inside: true,
                        },
                        splitLine: { 
                            show: true,
                        },
                    },
                    yAxis: {
                        data: ${JSON.stringify(barChart.yAxisData)},
                    },
                    series: ${JSON.stringify(barChart.seriesData)}
                    };
                chart.setOption(option); 
            </script>
            <div id='summary' style= 'font-size: 20px;'></div>
            <script>
            var id = document.getElementById('summary');
            id.innerHTML = '本次共执行了'+ ${JSON.stringify(barChart.dataCollection.get('caseCount'))} +
            'case,pass:'+ ${JSON.stringify(barChart.dataCollection.get('passCounts'))} +
            ',fail:'+ ${JSON.stringify(barChart.dataCollection.get('failCounts'))} +
            ',error:'+ ${JSON.stringify(barChart.dataCollection.get('errorCounts'))} +
            ',not run:'+ ${JSON.stringify(barChart.dataCollection.get('notRunCounts'))} +
            ',执行时间:'+ ${JSON.stringify(formattedTime)} +'.';
            </script>
            <table id="table">
                    <thead>
                        <tr>
                            <th id="cn">ComponentName</th>
                            <th>CaseName</th>
                            <th>CodeLine</th>
                            <th>Message</th>
                            <th id="res">Result</th>
                        </tr>
                    </thead>
                    <tbody>
                    </tbody>
            </table>
            <script>  
                var tableData = ${JSON.stringify(list)};
                var tableBody = document.querySelector('#table');
                tableData.forEach(function(item){
                    var row = document.createElement('tr');

                    var componentNameCell = document.createElement('td');
                    componentNameCell.textContent = item.ComponentName;
                    row.appendChild(componentNameCell);

                    var caseNameCell = document.createElement('td');
                    caseNameCell.textContent = item.CaseName;
                    row.appendChild(caseNameCell);
        
                    var codeLineCell = document.createElement('td');
                    codeLineCell.textContent = item.CodeLine;
                    row.appendChild(codeLineCell);
                    
                    var messageCell = document.createElement('td');
                    messageCell.textContent = item.Message;
                    row.appendChild(messageCell);
                    
                    var resultCell = document.createElement('td');
                    resultCell.textContent = item.Result;
                    row.appendChild(resultCell);
        
                    tableBody.appendChild(row); 
                });
            </script>            
        </body>
        </html>
    `;
    fs.writeFileSync(path.join(resultPath, htmlName), htmlContent);
    console.info(`HTML file with stacked bar chart generated: ${htmlName}`);
}