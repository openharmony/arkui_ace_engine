#!/usr/bin/env node
//!/usr/bin/env python
// -*- coding: utf-8 -*-
// Copyright (c) 2025 Huawei Device Co., Ltd.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

const fs = require('fs');
const JSON5 = require('json5');

function main(argv) {
    console.log('Generating files_to_watch.gni from tsconfig.json');

    const uniqueLines = new Set();
    const duplicates = [];

    // Load JSON5 config
    let config;
    try {
        const fileContent = fs.readFileSync('tsconfig.json', 'utf-8');
        config = JSON5.parse(fileContent); // JSON5 allows comments and trailing commas
    } catch (error) {
        const errorMessage = `
        +-----------------------------------------------------------------------------+
        |                                   ERROR                                     |
        | Failed to parse 'tsconfig.json                                         |
        | Ensure the file is valid JSON5 format                                       |
        +-----------------------------------------------------------------------------+
        `;
        console.error(errorMessage);
        process.exit(1);
    }

    const configFileNameBase = './ark_breakpoint/tsconfig.json';
    // Modify file paths
    const files = config.files || [];
    const modifiedFiles = files.map(file =>
        file.replace('src/', './ark_breakpoint/src/')
    );

    let newContent = `# Copyright (c) 2024 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License")
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ark_breakpoint_files_to_watch = [
  "${configFileNameBase}",
`;
    newContent += modifiedFiles.map(file => `  "${file}",`).join('\n');
    newContent += `
]
`;

    // Check if files_to_watch.gni already exists and matches the new content
    // Its important not to write the file again with the same content.
    // If file has new timestamp then --fast-rebuild canot be done because .gni gile get updated.
    try {
        const currentContent = fs.readFileSync('files_to_watch.gni', 'utf-8');
        if (currentContent === newContent) {
            console.log('No changes detected in files_to_watch.gni. Skipping update.');
            return;
        }
    } catch (error) {
        console.log('files_to_watch.gni not found. It will be created.');
    }

    // Write to files_to_watch.gni
    try {
        fs.writeFileSync('files_to_watch.gni', newContent);
        console.log('StateMgmt: File list generation done.');
    } catch (error) {
        console.error('Error writing to files_to_watch.gni:');
        console.error(error.message);
        process.exit(1);
    }

    // Check for duplicates in the input file list.
    modifiedFiles.forEach(line => {
        if (uniqueLines.has(line)) {
            duplicates.push(line);
        } else {
            uniqueLines.add(line);
        }
    });

    if (duplicates.length > 0) {
        console.error('ERROR: Duplicates found in tsconfig.json:');
        duplicates.forEach(duplicate => console.error(duplicate));
    }
}

main(process.argv);
