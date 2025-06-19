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

import path from "path"
import fs from "fs"
import { testOhConf } from "./common.mjs"
import { ensureExists, ohConf } from "../ohconf.mjs"
import { lazy } from "../utils.mjs"

const LZ_OHCONF = lazy(ohConfPath => ohConf(ohConfPath))

export function generate(options) {
    const tests = LZ_OHCONF(options.ohConf).value('test', true)

    let testRoots = []
    tests.forEach(test => {
        console.log("\n> Test folder " + ensureExists(test))

        const conf = testOhConf(test)
        const testRoot = ensureExists(conf.value("test_root", true))
        console.log("> Test root: " + testRoot)
        testRoots = [...testRoots, testRoot]

        const index = path.join(testRoot, 'ohos-index.ts')
        const include = conf.value('include', false, false)
        const exclude = conf.value('exclude', false, false)

        generateTestsIndex(testRoot, index, include, exclude)
    })
    generateTestsImports(testRoots)
}

function writeCaption(file) {
    fs.appendFileSync(file, "// *******************************\n")
    fs.appendFileSync(file, "// GENERATED: tests to run on OHOS\n")
    fs.appendFileSync(file, "// *******************************\n\n")
}

function isExcluded(test, exclude) {
    return exclude !== undefined ? exclude.includes(test) : false
}

function isIncluded(test, include) {
    return include !== undefined ? include.includes(test) : true
}

function writeTests(prefix, curDir, file, include, exclude) {
    fs.readdirSync(curDir).forEach(item => {
        const itemPath = path.join(curDir, item)
        const stat = fs.statSync(itemPath)
        if (!stat.isFile()) {
            writeTests(prefix + '/' + item, itemPath, file, include, exclude)
        }
        else if (item.endsWith(".test.ts") &&
            isIncluded(`${prefix}/${item}`, include) &&
            !isExcluded(`${prefix}/${item}`, exclude))
        {
            fs.appendFileSync(file, `import "${prefix}/${item}"\n`)
        }
    })
}

function generateTestsIndex(testRoot, index, include, exclude) {
    if (fs.existsSync(index))
        fs.rmSync(index)

    writeCaption(index)
    writeTests(".", testRoot, index, include, exclude)
}

function generateTestsImports(testRoots) {
    const testsImports = path.join(path.dirname(LZ_OHCONF().config), "src/tests.ts")

    if (fs.existsSync(testsImports))
        fs.rmSync(testsImports)

    writeCaption(testsImports)

    testRoots.forEach(testRoot => {
        let test = path.join(testRoot, "ohos-index.ts")
        test = path.relative(path.dirname(testsImports), test)
        test = test.replaceAll("\\", "/")
        fs.appendFileSync(testsImports, `import "${test}"\n`)
    })
}
