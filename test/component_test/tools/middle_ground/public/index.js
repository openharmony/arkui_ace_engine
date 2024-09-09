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

function readCsv() {
    return new Promise(async (resolve) => {
        await fetch('/api/getCsv')
            .then(response => response.json())
            .then(testCases => {
                resolve(testCases);
            })
            .catch((error) => {
                throw error;
            });
    });
}

function createCheckboxCell(name, value, caseTree, id) {
    let result;
    const tdEle = document.createElement('td');
    const newElement = document.createElement('input');
    const buttonEle = document.createElement('button');
    const textEle = document.createTextNode(value);
    newElement.type = 'checkbox';
    if ("Project Name" === name) {
        newElement.id = id;
        result = findPathByName(caseTree, id);
    } else if ("Component Name" === name) {
        newElement.id = id;
        result = findPathByName(caseTree, id);
    } else {
        newElement.id = value;
        result = findPathByName(caseTree, id);
    }
    newElement.value = JSON.stringify([value, name, result]);

    newElement.addEventListener('change', changeHandler.bind(null, caseTree, newElement));
    buttonEle.innerHTML = '-';
    buttonEle.style.width = '18px';
    buttonEle.style.height = '18px';
    if (name === 'Project Name') {
        buttonEle.className = 'checkBoxButton';
    }
    if (name === 'Project Name') {
        buttonEle.addEventListener('click', foldTr.bind(null, value, name));
        tdEle.appendChild(buttonEle);
    } else if (name === 'Component Name') {
        buttonEle.addEventListener('click', foldTr.bind(null, id, name));
        tdEle.appendChild(buttonEle);
    }
    tdEle.appendChild(newElement);
    tdEle.appendChild(textEle);
    return tdEle;
}

function run(list, pr) {
    let data = JSON.stringify({list, pr});
    return new Promise(async (resolve, reject) => {
        const options = {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: data
        };
        await fetch('/api/runCase', options)
            .then(response => response.json())
            .then(mes => {
                resolve(mes);
            })
            .catch((error) => {
                throw error;
            });
    });
}

function getIdByName(nameList) {
    let idList = [];
    nameList[2].forEach((val) => {
        if (nameList[1] === "Project Name") {
            idList.push(componentMap.get(`${val[0]}_${val[1]}`), val[2]);
        } else if (nameList[1] === "Component Name") {
            idList.push(val[2]);
        }
    });
    return uniqueArray(idList);
}

function findPathByName(data, targetName) {
    let values = [];
    for (let item of data) {
        if (item.id === targetName) {
            if (item.type === "Project Name") {
                for (let subItem of item.value) {
                    values = values.concat(findPathByName(item.value, subItem.id));
                }
                return values;
            } else if (Array.isArray(item.value)) {
                for (let subItem of item.value) {
                    values.push(subItem.path);
                }
                return values;
            } else if (!('type' in item)) {
                return [item.path];
            }
        } else if (Array.isArray(item.value)) {
            let result = findPathByName(item.value, targetName);
            if (result !== undefined) {
                return result;
            }
        }
    }
    return undefined;
}

function listToTree(data) {
    const result = [];
    const projectMap = {};
    data.forEach(item => {
        const projectName = item["Project Name"];
        const componentName = item["Component Name"];
        const fileName = item["File Name"];
        const id = item["id"];
        if (!projectMap[projectName]) {
            projectMap[projectName] = {
                type: "Project Name",
                name: projectName,
                path: [projectName],
                value: [],
                id: `${projectName}${id}`
            };
            result.push(projectMap[projectName]);
        }
        let componentEntry = projectMap[projectName].value.find(component => component.name === componentName);
        if (!componentEntry) {
            componentEntry = {
                type: "Component Name",
                name: componentName,
                path: [projectName, componentName],
                value: [],
                id: `${projectName}_${componentName}_${id}`
            };
            projectMap[projectName].value.push(componentEntry);
        }
        componentEntry.value.push({
            path: [projectName, componentName, fileName],
            name: fileName,
            id: fileName
        });
    });
    return result;
}

function changeHandler(componentMap, checkbox, event) {
    const value = checkbox.id;
    let checkboxData = JSON.parse(checkbox.value);
    if ("Component Name" === JSON.parse(checkbox.value)[1]) {
        let array = JSON.parse(checkbox.value)[2];
        let arrayData = [];
        array.forEach(e => {
            if (e[1] === checkboxData[0]) {
                arrayData.push(e);
            }
        })
        checkboxData[2] = arrayData;
    }
    const selectList = getIdByName(checkboxData);
    let list = [];
    selectList.forEach((val) => {
        list.push(val);
    })

    list.forEach((val) => {
        const otherCheckbox = document.getElementById(val);
        if (otherCheckbox) {
            otherCheckbox.checked = event.target.checked;
        }
    });
    let data = document.getElementById(value + 2) ? document.getElementById(value + 2) : document.getElementById(value);

    let valueList = JSON.parse(data.value)[2];
    if (event.target.checked) {
        checkboxLst = checkboxLst.concat(valueList);
    } else {
        valueList.forEach((val) => {
            let index = checkboxLst.findIndex(subArray => JSON.stringify(subArray) === JSON.stringify(val));
            checkboxLst.splice(index, 1);
        })
    }
}

function foldTr(value, name, event) {
    let elementList = document.querySelectorAll(`tr[${value}]`);
    const componentButton = elementList[0].getElementsByTagName('td')[1].querySelector('button');
    let isFoldStatus = false;
    for (let i = 1; i < elementList.length; i++) {
        if (name === 'Project Name') {
            if (event.target.textContent === '-') {
                componentButton.disabled = true;
                if (!elementList[i].classList.contains('hidden')) {
                    elementList[i].classList.add('hidden');
                }
                isFoldStatus = true;
            } else {
                elementList[i].classList.remove('hidden');
                componentButton.disabled = false;
                componentButton.textContent = '-';
                isFoldStatus = false;
            }
        } else {
            if (elementList[i].classList.contains('hidden')) {
                elementList[i].classList.remove('hidden');
                isFoldStatus = false;
            } else {
                elementList[i].classList.add('hidden');
                isFoldStatus = true;
            }
        }
    }
    isFoldStatus ? event.target.textContent = '+' : event.target.textContent = '-';
}

function uniqueArray(arr) {
    return [...new Set(arr.map(JSON.stringify))].map(JSON.parse);
}