/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { Assert as assert, test } from "@koalaui/harness"
import * as path from "path"
import * as fs from "fs"

let logText: string = ""

export function log(msg: string) {
    logText = logText.concat(msg, "\n")
}

export function getLog(): string {
    return logText
}

export function filterDirname(text: string): string {
    // tsc AST on windows uses C:/foo/bar representation, but
    // __dirname on windows returns C:\foo\bar.
    const platformDirname = __dirname.replaceAll(path.sep, "/")
    return text.replaceAll(platformDirname, "DIRNAME")
}

export function getLogFiltered(): string {
    return filterDirname(logText)
}

export function resetLog() {
    logText = ""
}

export function cleanDumpDirectory() {
    fs.rmSync(`${__dirname}/dump}`, {recursive: true, force: true})
}

export function loadDump(name: string, kind: string, module: string): string|undefined {
    const dirname = __dirname
    const dumpFile = `${dirname}/${kind}/${name}_${module}.test.ts_dump`
    const dump = fs.readFileSync(dumpFile, 'utf8')
    return (dump && dump.includes('\r'))
        ? dump.replace(/[\r]/g, '')
        : dump
}

export function checkDump(name: string, module: string) {
    test(`Transformed ${name} dump matches the golden dump`, () => {
        const test = loadDump(name, "dump", module)
        const testFiltered = test ? filterDirname(test) : undefined
        const golden = loadDump(name, "golden", module)
        assert.equal(golden, testFiltered)
    })
}
