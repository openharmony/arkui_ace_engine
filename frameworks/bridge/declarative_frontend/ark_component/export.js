/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
const fs = require("fs");

function addOtherContentToDistFile(fileName, otherContent) {
    let content = fs.readFileSync(fileName);
    if (content.includes('globalThis.__getArkUINode__')) {
        return;
    }
    fs.writeFileSync(fileName, content + otherContent);
}


function main() {
    if (process.argv.length < 3) {
        console.log('Usage: node export.js <dist-file>');
        process.exit(1);
    }

    let distFileName = process.argv[2];
    const otherContent = fs.readFileSync('./src/arkComponent.js');
    addOtherContentToDistFile(distFileName, otherContent);
    console.log(`Updated export file: ${distFileName}`);
}

main();