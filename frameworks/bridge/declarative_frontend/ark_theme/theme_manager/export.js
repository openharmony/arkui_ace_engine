/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

function main() {
    if (process.argv.length < 3) {
        console.log('Usage: node build_postprocess.js <file>');
        process.exit(1);
    }
    const fileName = process.argv[2];
    if (!fs.existsSync(fileName)) {
        console.log('Error: File not found: ' + fileName);
        process.exit(1);
    }
    let content = fs.readFileSync(fileName, 'utf-8');
    // Remove console.log lines for release build
    content = content.replace(/console\.log\([^)]*\);?\n?/g, '');
    const exportStatement = `export default { ArkThemeScopeManager };`;
    content += exportStatement;
    fs.writeFileSync(fileName, content);
    console.log('Post-processed: ' + fileName);
}

main();