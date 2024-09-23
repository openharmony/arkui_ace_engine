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
const iconv = require('iconv-lite');

module.exports = {
    getNodePIDs,
    deleteNodePIDs
};

async function getNodePIDs() {
    return new Promise((resolve, reject) => {
        const tasklist = spawn('tasklist', [
            '/nh',
            '/fo',
            'csv',
            '/fi',
            'imagename eq node.exe'
        ]);
        let output = '';

        tasklist.stdout.on('data', (data) => {
            output += iconv.decode(data, 'cp936');
        });

        tasklist.on('close', () => {
            try {
                const lines = output.trim().split('\r\n');
                const pids = lines.filter(line => line.trim())
                    .map(line => {
                        const parts = line.split(/","/);
                        return parts[1].replace(/^"|"$/g, '');
                    });
                resolve(pids);
            } catch (error) {
                reject(error);
            }
        });

        tasklist.stderr.on('data', (data) => {
            reject(new Error(`Error getting PIDs: ${data}`));
        });
    });
}

async function deleteNodePIDs(PIDs) {
    return new Promise((resolve, reject) => {
        PIDs.forEach(item => {
            const deleteProcess = spawn('taskkill', [
                '/f',
                '/pid',
                item,
            ], { shell: true });

            if (!deleteProcess) {
                console.error(new Error("Failed to delete child process"));
            }

            let stdout;
            let stderr;

            deleteProcess.stdout.on('data', data => {
                stdout += data.toString();
            });

            deleteProcess.stderr.on('data', data => {
                stderr += data.toString();
                console.error(data.toString());
            });

            deleteProcess.on('close', code => {
                if (code !== 0) {
                    console.error(`delete process error exited with code ${code}`);
                    reject(code);
                } else {
                    resolve(code);
                }
            });
        });
    });
}