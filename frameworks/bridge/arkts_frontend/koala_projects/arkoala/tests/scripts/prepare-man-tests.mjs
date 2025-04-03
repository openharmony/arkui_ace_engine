/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import fs from "fs"
import path from "path"
import { fileURLToPath } from "url"

const SCRIPT_ROOT = path.dirname(fileURLToPath(import.meta.url))
const TESTS_SRC_ROOT = path.join(SCRIPT_ROOT, "../src/ets-tests/pages")
const PAGES_ROOT = path.join(SCRIPT_ROOT, "../app/entry/src/main/ets/pages")
const TESTS_DST_ROOT = path.join(PAGES_ROOT, "tests")
const TESTS_DESCRIPTOR_FILE = path.join(SCRIPT_ROOT, "../../tools/peer-generator/package.json")
const INDEX_FILE = path.join(PAGES_ROOT, "Index.ets")
const MAIN_PAGES_FILE = path.join(SCRIPT_ROOT, "../app/entry/src/main/resources/base/profile/main_pages.json")
const INDEX_FILE_PATCH_POINT = "const TESTS: Map<number, string> = new Map(["

const TESTS_NAMES = parseTestsNames()
const TEST_FILE_POSTFIX = ".test.ets"

function adoptAndCopyTests() {
    const files = fs.readdirSync(TESTS_SRC_ROOT)

    for (let file of files) {
        const name = file.replace(/\.test\.ets/g, "")
        if (specifiedTestNamed()) {
            let match = false
            for (let n of TESTS_NAMES) {
                if (n === name) {
                    match = true
                    break
                }
            }
            if (!match) {
                continue
            }
        }
        else if (!test2ComponentName(file)) {
            continue
        }
        console.log(`${file}`)
        const content = fs.readFileSync(path.join(TESTS_SRC_ROOT, file)) + ""
        let modifiedContent = ""
        let braces = -1
        content.split(/\r?\n/).forEach(line => {
            modifiedContent += line + "\n"
            if (line.includes("build() {")) {
                modifiedContent += "    Column() {\n"
                braces = 0
            }
            if (braces >= 0) {
                braces += numChars("{", line)
                braces -= numChars("}", line)
            }
            if (braces === 0) {
                modifiedContent +=
                    '    .width("100%")\n' +
                    '    .height("100%")\n' +
                    '    }\n'
                braces = -1
            }
        })
        fs.mkdirSync(TESTS_DST_ROOT, {recursive: true})
        fs.writeFileSync(path.join(TESTS_DST_ROOT, file), modifiedContent)
    }
}

function patchTestsNames() {
    const content = fs.readFileSync(INDEX_FILE) + ""
    let modifiedContent = ""
    let brackets = -1
    content.split(/\r?\n/).forEach(line => {
        if (line.includes(INDEX_FILE_PATCH_POINT)) {
            modifiedContent += `${INDEX_FILE_PATCH_POINT}\n`
            brackets = 1
        }
        if (brackets > 0 && line.includes("])")) {
            brackets = 0
        }
        if (brackets < 0) {
            modifiedContent += line + "\n"
        }
        if (brackets === 0) {
            const updateModifiedContent = name => {
                if (!name) {
                    return
                }
                if (ensureTestExists(name)) {
                    modifiedContent += `    [${index++}, "${name}"],\n`
                } else {
                    modifiedContent += `    // no matching test for "${name}"\n`
                    console.error(`WARNING: No matching test for "${name}"`)
                }
            }
            let index = 0
            if (specifiedTestNamed()) {
                TESTS_NAMES.forEach(name => updateModifiedContent(name))
            }
            else {
                fs.readdirSync(TESTS_SRC_ROOT).forEach(file => updateModifiedContent(test2ComponentName(file)))
            }
            modifiedContent = cutTrailingComma(modifiedContent)
            modifiedContent += "])\n"
            brackets = -1
        }
    })
    modifiedContent = cutTrailingNL(modifiedContent)
    fs.writeFileSync(INDEX_FILE, modifiedContent)
}

function patchMainPages() {
    let content =
        '{\n' +
        '    "src": [\n' +
        '        "pages/Index",\n'

    const updateContent = name => {
        if (ensureTestExists(name)) {
            content += `        "pages/tests/${name}.test",\n`
        }
    }

    if (specifiedTestNamed()) {
        TESTS_NAMES.forEach(name => updateContent(name))
    }
    else {
        fs.readdirSync(TESTS_SRC_ROOT).forEach(file => updateContent(test2ComponentName(file)))
    }
    content = cutTrailingComma(content)
    content +=
        '    ]\n' +
        '}\n'
    fs.writeFileSync(MAIN_PAGES_FILE, content)
}

function parseTestsNames() {
    const content = JSON.parse(fs.readFileSync(TESTS_DESCRIPTOR_FILE, 'utf8') + "")
    const command = content["scripts"]["generate:ts"]


    const pattern = /^.*\s*--generate-interface\s+([a-zA-Z0-9,\s]+)\s+.*$/
    const match = command.match(pattern)
    if (match) {
        const tests = match.splice(1)[0]
        return tests.split(",")
    }
    return []
}

function specifiedTestNamed() {
    return TESTS_NAMES.length > 0
}

function ensureTestExists(testName) {
    const testFile = path.join(TESTS_SRC_ROOT, `${testName}.test.ets`)
    return fs.existsSync(testFile)
}

function test2ComponentName(file) {
    if (file.endsWith(TEST_FILE_POSTFIX))
        return file.slice(0, -(TEST_FILE_POSTFIX.length))
    return undefined
}

function cutTrailingComma(line) {
    return line.slice(0, -2) + '\n'
}

function cutTrailingNL(line) {
    return line.slice(0, -1)
}

function numChars(char, str) {
    let result = 0
    for (let i = 0; i < str.length; i++) {
        if (str[i] === char) result++
    }
    return result
}

adoptAndCopyTests()
patchTestsNames()
patchMainPages()
