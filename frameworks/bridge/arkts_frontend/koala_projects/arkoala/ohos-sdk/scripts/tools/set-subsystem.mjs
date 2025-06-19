#!/usr/bin/env node

/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import fs from "node:fs"
import path from "node:path";

const { O_RDWR } = fs.constants

const DOS_HEADER_LEN = 0x40;
const DOS_HEADER_MAGIC = 0x5A4D;
const PE_HEADER_POS_OFFSET = 0x3c;
const PE_HEADER_LEN = 0x78; // Partially
const PE_HEADER_MAGIC = 0x00004550
const PE_SUBSYSTEM_OFFSET = 0x5C;

const SUBSYSTEM_WINDOWS = 2;
const SUBSYSTEM_CONSOLE = 3;

export function setSubsystem(filePath, platform) {

    process.on("uncaughtException", err => {
        console.error("" + err);
        process.exit(1);
    })

    if (!filePath) printUsageAndExit()

    let fd = fs.openSync(filePath, O_RDWR);
    let dosHeader = Buffer.alloc(DOS_HEADER_LEN);
    let bytesRead = fs.readSync(fd, dosHeader, 0, DOS_HEADER_LEN);

    if (bytesRead !== DOS_HEADER_LEN || dosHeader.readUInt16LE(0) !== DOS_HEADER_MAGIC) {
        throw new Error("Not a PE file")
    }

    let peOffset = dosHeader.readUInt32LE(PE_HEADER_POS_OFFSET);
    let peHeader = Buffer.alloc(PE_HEADER_LEN);
    bytesRead = fs.readSync(fd, peHeader, 0, PE_HEADER_LEN, peOffset);
    if (bytesRead !== PE_HEADER_LEN || peHeader.readUInt32LE(0) !== PE_HEADER_MAGIC) {
        throw new Error("Not a PE file")
    }

    if (platform) {
        const subsystem = parseSubsystem(platform);
        let newSubsystem = Buffer.alloc(2);
        newSubsystem.writeUInt16LE(subsystem);
        fs.writeSync(fd, newSubsystem, 0, newSubsystem.length, peOffset + PE_SUBSYSTEM_OFFSET);
    } else {
        console.log("Current subsystem: " + subsystemStr(peHeader.readUint16LE(PE_SUBSYSTEM_OFFSET)));
    }

    fs.closeSync(fd);
}

function subsystemStr(subsystem) {

    switch (subsystem) {
        case SUBSYSTEM_CONSOLE: return "console";
        case SUBSYSTEM_WINDOWS: return "windows";
        default: return `unknown<${subsystem}>`;
    }
}

function parseSubsystem(subsystemStr) {

    let subsystem = subsystemStr.toLowerCase()
    switch (subsystem) {
        case "console": return SUBSYSTEM_CONSOLE;
        case "windows": return SUBSYSTEM_WINDOWS;
        default: throw new RangeError(`illegal subsystem ${subsystem}`)
    }
}
function printUsageAndExit() {
    let exe = path.basename(process.argv[0])
    let script = path.basename(process.argv[1])
    console.log(`USAGE: ${exe} ${script} <file> [windows|console]`)
    process.exit(1);
}
