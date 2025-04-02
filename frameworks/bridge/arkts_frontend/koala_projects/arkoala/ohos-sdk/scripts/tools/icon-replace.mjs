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
const PE_HEADER_LEN = 0x112; // for 64-bit
const PE_HEADER_MAGIC = 0x00004550;

const COFF_HEADER_SIZE =  24;
const PE_NUMBER_OF_SECTIONS_OFFSET = 6;
const PE_MAGIC_OFFSET = COFF_HEADER_SIZE + 0;
const PE_SIZE_OF_HEADERS_OFFSET = COFF_HEADER_SIZE + 60;
const PE_NUMBER_OF_RVA_AND_SIZES_OFFSET_32 = COFF_HEADER_SIZE + 92;
const PE_NUMBER_OF_RVA_AND_SIZES_OFFSET_64 = COFF_HEADER_SIZE + 108;
const PE_RESOURCE_SECTION_INFO_OFFSET_32 = COFF_HEADER_SIZE + 112;
const PE_RESOURCE_SECTION_INFO_OFFSET_64 = COFF_HEADER_SIZE + 128;
const PE_SECTION_HEADER_SIZE = 40

const RT_ICON = 3
const RT_GROUP_ICON = RT_ICON + 11

export function setIcon(filePath, iconPath) {
    
    process.on("uncaughtException", err => {
        console.error("" + err);
        process.exit(1);
    })

    if (!filePath || !iconPath) printUsageAndExit()

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

    let sections = readSections(fd, peHeader, peOffset);

    let rsrc = sections.find(s => s.name === ".rsrc");
    if (!rsrc) {
        console.error("no resource section")
        process.exit(1);
    }

    let resources = readResourceSection(fd, rsrc.size, rsrc.offset);

    const iconDirResource = resources.items.find(r => r.id === RT_ICON);
    const iconResources = iconDirResource.items
        .map(res => ({ name: "icon-" + res.id, id: res.id, size: res.items[0].size, offset: rsrc.offset + res.items[0].offset - rsrc.virtualAddr, tableOffset: res.items[0].fileOffset }))
    const groupIconResources = resources.items.find(r => r.id === RT_GROUP_ICON)?.items
        .map(res => ({ name: "groupicon-" + res.id, size: res.items[0].size, offset: rsrc.offset + res.items[0].offset - rsrc.virtualAddr, tableOffset: res.items[0].fileOffset }))

    if (!checkResourcesAreSequential(iconResources)) {
        console.error("Icons must be placed sequentially, WIP")
        process.exit(1)
    }

    const newIcon = fs.readFileSync(iconPath)
    const lastResource = iconResources[iconResources.length - 1]
    const imageResource = iconResources[0]
    const icoHeaderResource = groupIconResources[0]
    writeImage(fd, newIcon, imageResource.offset, lastResource.offset + lastResource.size);
    fixImageDirectoryResource(fd, icoHeaderResource.tableOffset,icoHeaderResource.offset, icoHeaderResource.size, imageResource.id, newIcon.length);
    fixImageDataEntry(fd, imageResource.tableOffset, newIcon.length);
    fixImageDirectoryEntry(fd, iconDirResource.fileOffset, imageResource.id, iconResources.length);

    fs.closeSync(fd);
}

function readSections(fd, peHeader, peOffset) {

    let is64 = peHeader.readUint16LE(PE_MAGIC_OFFSET) === 0x20b;

    let numRVAAndSizesOffset = is64 ? PE_NUMBER_OF_RVA_AND_SIZES_OFFSET_64 : PE_NUMBER_OF_RVA_AND_SIZES_OFFSET_32;
    let numRVAAndSizes = peHeader.readUInt32LE(numRVAAndSizesOffset);

    let sectionsOffset = peOffset + numRVAAndSizesOffset + 4 + 8 * numRVAAndSizes;
    let numSections = peHeader.readUInt16LE(PE_NUMBER_OF_SECTIONS_OFFSET);
    let sectionsHeaders = Buffer.alloc(numSections * PE_SECTION_HEADER_SIZE);
    let _bytesRead = fs.readSync(fd, sectionsHeaders, 0, numSections * PE_SECTION_HEADER_SIZE, sectionsOffset);
    let sections = [];
    for (let i = 0; i < numSections; i++) {
        let sectionHeader = sectionsHeaders.subarray(i * PE_SECTION_HEADER_SIZE, (i + 1) * PE_SECTION_HEADER_SIZE);
        let sectionName = sectionHeader.toString("utf8", 0, cstrlen(sectionHeader, 0, 8));
        let sectionOffset = sectionHeader.readUInt32LE(20);
        let sectionSize = sectionHeader.readUInt32LE(16);
        let sectionVirtAddr = sectionHeader.readUint32LE(12);
        sections.push({ name: sectionName, size: sectionSize, offset: sectionOffset, virtualAddr: sectionVirtAddr });
    }
    return sections;
}

function readResourceSection(fd, size, offset) {
    let section = Buffer.alloc(size)
    let _ = fs.readSync(fd, section, 0, size, offset)
    const fileOffset = offset

    const TABLE_HEADER_SIZE = 16
    const DIRECTORY_ENTRY_SIZE = 8
    
    function readDirectoryTable(offset, id) {
        let entry = { type: "directory", id: id, items: [], fileOffset: fileOffset + offset }
        let numNamed = section.readUint16LE(offset + 12)
        let numIds = section.readUint16LE(offset + 14)

        let off = offset + TABLE_HEADER_SIZE
        for (let i = 0; i < numNamed; i++) {
            entry.items.push(readDirectoryEntry(off, true))
            off += DIRECTORY_ENTRY_SIZE
        }
        for (let i = 0; i < numIds; i++) {
            entry.items.push(readDirectoryEntry(off, false))
            off += DIRECTORY_ENTRY_SIZE
        }

        return entry;
    }

    function readDataEntry(offset, id) {
        let entry = { type: "data", id: id, offset: 0, size: 0, fileOffset: fileOffset + offset }
        entry.offset = section.readUInt32LE(offset)
        entry.size = section.readUInt32LE(offset + 4)
        return entry;
    }

    function readStringEntry(offset) {
        let length = section.readUint16LE(offset);
        let value = section.toString("utf16le", offset + 2, offset + 2 + length)
        if (value.endsWith("\0")) value = value.slice(0, -1)
        return value
    }

    function readDirectoryEntry(offset, named) {
        let id = section.readUInt32LE(offset);
        let itemOffset = section.readUInt32LE(offset + 4)
        if (named) {
            id = readStringEntry(id)
        }
        if (itemOffset & 0x80000000) {
            itemOffset &= 0x0FFFFFFF
            return readDirectoryTable(itemOffset, id)
        } else {
            return readDataEntry(itemOffset, id)
        }
    }

    return readDirectoryTable(0, 0)
}

function printUsageAndExit() {
    let exe = path.basename(process.argv[0])
    let script = path.basename(process.argv[1])
    console.log(`USAGE: ${exe} ${script} <file> <icon path>`)
    process.exit(1);
}

function cstrlen(buf, start, end) {
    for (let i = start; i < end; i++) {
        if (buf[i] === 0) return i;
    }

    return end - start;
}

function checkResourcesAreSequential(items) {
    if (!items.length) return true
    let offset = items[0].offset
    for (const item of items) {
        if (offset !== item.offset) {
            return false
        }
        offset += item.size
    }

    return true
}

function writeImage(fd, data, start, end) {
    writeWithTrailingZeroes(fd, data, start, end)
}

function writeWithTrailingZeroes(fd, data, start, end) {
    if (end - start < data.length) {
        throw new Error("Image too large")
    }

    fs.writeSync(fd, data, 0, data.length, start);
    let offset = start + data.length
    let zeros = Buffer.alloc(4096);
    while (offset < end) {
        let delta = Math.min(zeros.length, end - offset);
        offset += fs.writeSync(fd, zeros, 0, delta, offset);
    }
}

function fixImageDirectoryResource(fd, tableOffset, dataOffset, dataSize, iconId, iconSize) {
    let newIcoDirectory = Buffer.alloc(6 + 14);
    newIcoDirectory.writeUInt16LE(0, 0); // Must be zero
    newIcoDirectory.writeUInt16LE(1, 2); // 1 for ICON
    newIcoDirectory.writeUInt16LE(1, 4); // num images, only one is supported by this script
    newIcoDirectory.writeUInt8(0, 6); // width, icon must 256x256
    newIcoDirectory.writeUInt8(0, 7); // height
    newIcoDirectory.writeUInt8(0, 8); // no palette
    newIcoDirectory.writeUInt8(0, 9); // reserved
    newIcoDirectory.writeUInt16LE(1, 10); // 1 plane
    newIcoDirectory.writeUInt16LE(32, 12); // bpp
    newIcoDirectory.writeUInt32LE(iconSize, 14); // size
    newIcoDirectory.writeUInt16LE(iconId, 18); // id

    writeWithTrailingZeroes(fd, newIcoDirectory, dataOffset, dataOffset + dataSize);

    let buffer = Buffer.alloc(4)
    buffer.writeUInt32LE(newIcoDirectory.length)
    fs.writeSync(fd, buffer, 0, 4, tableOffset + 4);
}

function fixImageDataEntry(fd, tableOffset, iconSize) {
    let buffer = Buffer.alloc(4)
    buffer.writeUInt32LE(iconSize)
    fs.writeSync(fd, buffer, 0, 4, tableOffset + 4);
}

function fixImageDirectoryEntry(fd, tableOffset, iconId, numIcons) {
    const DIRECTORY_ENTRY_SIZE = 8
    const TABLE_HEADER_SIZE = 16

    let buffer = Buffer.alloc(8)
    buffer.writeUInt16LE(0, 0)      // No entries with string names
    buffer.writeUInt16LE(1, 2)      // 1 entry with id
    buffer.writeUInt32LE(iconId, 4) // point to current icon ID
    fs.writeSync(fd, buffer, 0, 8, tableOffset + 12);
    let zerosStart = tableOffset + TABLE_HEADER_SIZE + DIRECTORY_ENTRY_SIZE
    let zerosEnd = zerosStart + (numIcons - 1) * DIRECTORY_ENTRY_SIZE
    writeWithTrailingZeroes(fd, Buffer.alloc(0), zerosStart, zerosEnd)
}
