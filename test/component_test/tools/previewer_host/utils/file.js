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
const fs = require('fs').promises

module.exports = {
    existDir,
    mkdir,
    readDir,
    clearDir,
    deleteDir,
    delFile,
    renameDir,
    moveDir,
    moveSourceToTarget,
    writeJsonFile,
    isExistFile,
    recursiveCreateFolders,
    copyFile,
    writeFile
}

async function existDir(folderPath) {
    try {
        const stats = await fs.stat(folderPath);
        return stats.isDirectory();
    } catch (err) {
        if (err.code === 'ENOENT') {
            return false;
        } else {
            throw err;
        }
    }
}

async function mkdir(folderPath) {
    try {
        await fs.mkdir(folderPath, { recursive: true });
    } catch (error) {
        throw error;
    }
}

async function readDir(folderPath) {
    try {
        const fileNames = await fs.readdir(folderPath);
        return fileNames.map(fileName => {
            return path.join(folderPath, fileName);
        });
    } catch (err) {
        return Promise.reject(err);
    }
}

async function clearDir(folderPath) {
    let folder = await readDir(folderPath);
    try {
        for (let i = 0; i < folder.length; i++) {
            await fs.rm(folder[i], { recursive: true });
        }
    } catch (error) {
        console.error(error);
        throw error;
    }
}

async function deleteDir(folderPath) {
    try {
        let files = await fs.readdir(folderPath);
        if (files.length > 0) {
            for (const file of files) {
                const filePath = path.join(folderPath, file);
                await fs.rm(filePath, { recursive: true });
            }
        }
        await fs.rmdir(folderPath);
    } catch (err) {
        if (err.code !== 'ENOENT') throw err;
    }
}

async function delFile(filePath) {
    try {
        await fs.rm(filePath, { recursive: true });
    } catch (err) {
        if (err.code !== 'ENOENT') throw err;
    }
}

async function renameDir(oldName, newName) {
    try {
        await fs.rename(oldName, newName);
    } catch (error) {
        throw error;
    }
}

async function moveDir(src, dest) {
    try {
        let fileName = src.split(path.sep)[src.split(path.sep).length - 1];
        const target = path.join(dest, fileName);
        await moveSourceToTarget(src, target);
    } catch (err) {
        if (err.code !== 'ENOENT') throw err;
    }
}

async function moveSourceToTarget(src, dest) {
    try {
        await fs.rename(src, dest);
    } catch (err) {
        throw err;
    }
}

async function ensureDirectoryExists(filePath) {
    const dirname = path.dirname(filePath);
    try {
        await fs.mkdir(dirname, { recursive: true });
    } catch (err) {
        if (err.code !== 'EEXIST') {
            throw err;
        }
    }
}

async function writeJsonFile(jsonData, jsonFilePath) {
    try {
        await ensureDirectoryExists(jsonFilePath);
        await fs.writeFile(jsonFilePath, jsonData, 'utf8');
    } catch (err) {
        throw err;
    }
}

async function isExistFile(filePath) {
    try {
        await fs.access(filePath);
        return true;
    } catch (error) {
        return false;
    }
}

async function recursiveCreateFolders(folderPath) {
    try {
        await fs.mkdir(folderPath, { recursive: true });
    } catch (err) {
        if (err.code !== 'EEXIST') {
            throw err;
        }
    }
}

async function copyFile(source, target) {
    try {
        const data = await fs.readFile(source);
        await fs.writeFile(target, data);
    } catch (error) {
        throw error;
    }
}

async function writeFile(filePath, fileContext) {
    try {
        await fs.writeFile(filePath, fileContext);
    } catch (error) {
        throw error;
    }
}