/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

const fs = require('fs');
var peg = require('pegjs');

function usageAndExit() {
    console.error(`
State Management Library
================

Comments out stateMgmtProfiler.[start, stop] calls.

Usage:
Disable all stateMgmtProfiler.[start, stop] from a file.
node disableProfiler.js <filePath>

WARNING:
Original file is overwritten.
`);
    process.exit(-1);
}

// load parser sources and compile them
// returns the parser object
function makeParser() {
    let pegjsSources = '';
    try {
        pegjsSources = fs.readFileSync('disableProfiler.pegjs') + '\n';
    } catch (err) {
        console.error("While trying to read: 'disableProfiler.pegjs': " + err);
        process.exit(-1);
    }
    console.log(`  Read parser sources 'disableProfiler.pegjs': ${pegjsSources.length} Bytes.`)

    // generate the parser from parser.pegjs source file:
    var parser;
    try {
        parser = peg.generate(pegjsSources,
            {
                'allowedStartRules': [
                    'program'
                ]
            });
    } catch (err) {
        console.error('Failed to compile parser. Error: ' + err);
        process.exit(-1);
    }
    return parser;
}

// load the specified source file and return the buffer
function loadFile(fileName) {
    let content = '';
    try {
        content = fs.readFileSync(fileName) + '\n';
    } catch (err) {
        console.error(`While trying to read source file ${fileName}: ${err}`);
        process.exit(-1);
    }
    console.log(`  Read source file ${fileName}: ${content.length} Bytes.`)
    return content;
}

function saveFile(fileName, content) {
    fs.writeFileSync(fileName, content);
    console.log(`Calls for stateMgmtProfiler disabled. '${fileName}': ${content.length} Bytes. OK.`);
}


function main() {

    if (process.argv.length < 3) {
        usageAndExit();
    }

    let fileName = process.argv[2];

    console.log(`Loading file to disable stateMgmtProfiler calls. File: ${fileName}`);

    let parser = makeParser();
    let content = loadFile(fileName);

    let newContent;
    try {
        newContent = parser.parse(content);
    } catch (err) {
        console.error(`Failed disabling stateMgmtProfiler calls. Error: ${err}`);
        process.exit(-1);
    }

    saveFile(fileName, newContent);
}

main();