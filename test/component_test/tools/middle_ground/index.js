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

const {readCSVFile, promiseRun} = require('./util/index');
const path = require('path');
const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const PORT = process.env.PORT || 4000;
let executeStatus = -1;
let message = '';

app.use(express.static(path.join(__dirname, 'public')));

app.use(bodyParser.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + path.join('/pages/index.html'));
});

app.get('/api/getCsv', (req, res) => {
    readCSVFile().then((resolve, reject) => {
        res.json(resolve);
    })
});

app.get('/api/getExecuteStatus', (req, res) => {
    res.json({execResult: executeStatus, mes: message});
    if (executeStatus === 0 || executeStatus === 1) {
        executeStatus = -1;
    }
});

app.post('/api/runCase', (req, res) => {
    const {list, pr} = req.body;
    executeStatus = 2;
    promiseRun(list, pr)
        .then((result) => {
            if (result.code === 0) {
                executeStatus = 0;
            } else if (result.code === 1) {
                executeStatus = 1;
                message = result.errorMes;
            }
        })
    res.json({execResult: executeStatus, mes: message});
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});