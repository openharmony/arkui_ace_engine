/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import * as fs from "node:fs"
import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"
import { constructorWithOverload } from "./constructor"
import { updateTopLevelClass } from "./simple"
import { renameClass } from "./simple/rename-class"
import { addClassMethod } from "./simple/add-class-method"
import { addVariableDeclaration } from "./simple/add-variable"
import { addThisReference } from "./this"
import { insertParameterToType } from "./overloads/getter-setter"
import { insertParameter } from "./imports/recursive"
import { addImportSameFile } from "./imports/add-same-file"
import { addUseImportSameFile } from "./imports/add-use-same-file"
import { addImportNewFile } from "./imports/add-new-file"
import { addOptionalChain } from "./optional/add-chain"
import { addUseImportClassSameFile } from "./exports/basic"
import { addUseImportClassSameFileAndExportClass } from "./exports/add-export"
import { addUseImportClassSameFileAndCreateClass } from "./exports/create-class"

const DIR = './test/arkts-api/recheck/'
const PANDA_SDK_PATH = process.env.PANDA_SDK_PATH ?? '../../incremental/tools/panda/node_modules/@panda/sdk'

function createConfig(file: string) {
    fs.mkdirSync(`${DIR}/build/abc/${file}`, { recursive: true })
    arkts.arktsGlobal.filePath = `${DIR}/${file}/main.ets`
    arkts.arktsGlobal.config = arkts.Config.create([
        '_',
        '--arktsconfig',
        `${DIR}/arktsconfig.json`,
        `${DIR}/${file}/main.ets`,
        '--extension',
        'ets',
        '--stdlib',
        `${PANDA_SDK_PATH}/ets/stdlib`,
        '--output',
        `${DIR}/build/abc/${file}/main.abc`
    ]).peer
}

function createContext(file: string) {
    const code = fs.readFileSync(`${DIR}/${file}/main.ets`, 'utf-8')
    arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)
}

function proceedToParsed() {
    arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED)
}

function proceedToChecked() {
    arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)
}

function applyTransform(transform?: arkts.ProgramTransformer, onlyModifyMain?: boolean) {
    arkts.arktsGlobal.compilerContext.program.externalSources.forEach(it => {
        if (it.getName().startsWith("std.")) return
        if (it.getName().startsWith("escompat")) return
        it.programs.forEach(program => {
            const ast = program.astNode
            const importStorage = new arkts.ImportStorage(program, false)
            if (!onlyModifyMain) {
                transform?.(program, { isMainProgram: false, name: "", stage: arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED }, new arkts.PluginContextImpl())
            }
            arkts.setBaseOverloads(ast)
            importStorage.update()
            arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, ast.peer)
        })
    })

    const script = arkts.createETSModuleFromContext()
    const importStorage = new arkts.ImportStorage(arkts.arktsGlobal.compilerContext.program, false)
    transform?.(arkts.arktsGlobal.compilerContext.program, { isMainProgram: true, name: "", stage: arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED }, new arkts.PluginContextImpl())
    arkts.setBaseOverloads(script)
    importStorage.update()
    arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, script.peer)
}

function recheck() {
    arkts.recheckSubtree(arkts.createETSModuleFromContext())
}

function dumpSrc(file: string) {
    const src = arkts.createETSModuleFromContext().dumpSrc()
    fs.mkdirSync(`${DIR}/${file}/dump-src`, { recursive: true })
    fs.writeFileSync(`${DIR}/${file}/dump-src/main.ets`, src)
}

function dumpJson(file: string) {
    const json = arkts.createETSModuleFromContext().dumpJson()
    fs.mkdirSync(`${DIR}/${file}/dump-json`, { recursive: true })
    fs.writeFileSync(`${DIR}/${file}/dump-json/main.json`, json)
}

function assertSrc(file: string) {
    const src = arkts.createETSModuleFromContext().dumpSrc()
    const expected = fs.readFileSync(`${DIR}/${file}/dump-src/main.ets`, 'utf-8')
    util.assert.equal(src, expected)
}

function assertJson(file: string) {
    const json = arkts.createETSModuleFromContext().dumpJson()
    const expected = fs.readFileSync(`${DIR}/${file}/dump-json/main.json`, 'utf-8')
    util.assert.equal(json, expected)
}

function proceedToBin() {
    arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
}

interface TestOptions {
    skipSrc?: boolean,
    skipJson?: boolean,
    onlyModifyMain?: boolean,
}

const defaultTestOptions: TestOptions = {
    skipSrc: false,
    skipJson: true,
    onlyModifyMain: false
}

function runTest(
    file: string,
    transform?: arkts.ProgramTransformer,
    userOptions: TestOptions = defaultTestOptions
) {
    const options = {
        skipSrc: userOptions.skipSrc ?? defaultTestOptions.skipSrc,
        skipJson: userOptions.skipJson ?? defaultTestOptions.skipJson,
        onlyModifyMain: userOptions.onlyModifyMain ?? defaultTestOptions.onlyModifyMain
    }
    createConfig(file)
    createContext(file)
    proceedToChecked()
    applyTransform(transform, options.onlyModifyMain)
    recheck()
    if (process.env.TEST_GOLDEN == "1") {
        if (!options.skipSrc) dumpSrc(file)
        if (!options.skipJson) dumpJson(file)
    } else {
        if (!options.skipSrc) assertSrc(file)
        if (!options.skipJson) assertJson(file)
    }
    proceedToBin()
}

suite(util.basename(__filename), () => {
    suite('static', () => {
        test("function", () => {
            runTest('static/function', undefined)
        })

        test("public setter", () => {
            runTest('static/public-setter', undefined)
        })

        test("constructor with overload", () => {
            runTest('static/constructor', undefined)
        })

        // es2panda issue 24821
        test.skip("property", () => {
            runTest('static/property', undefined)
        })

        test("typed property", () => {
            runTest('static/typed-property', undefined)
        })

        test("trailing block", () => {
            runTest('static/trailing-block', undefined)
        })

        test("import type", () => {
            runTest('static/import-type', undefined)
        })
    })

    suite('simple', () => {
        test('rename class', () => {
            runTest('simple/rename-class', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, renameClass)
            })
        })

        test('add class method', () => {
            runTest('simple/add-class-method', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, addClassMethod)
            })
        })

        test('add variable declaration', () => {
            runTest('simple/add-variable', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, addVariableDeclaration)
            })
        })
    })

    test.skip('constructor', () => {
        runTest('constructor', constructorWithOverload)
    })

    test('add this reference', () => {
        runTest('this', addThisReference)
    })

    suite('optional', () => {
        test('pass optional unchanged', () => {
            runTest('optional/unchanged', undefined)
        })
        test('add optional chain', () => {
            runTest('optional/add-chain', addOptionalChain)
        })
    })

    suite('imports', () => {
        test('add another import from the same file with dedicated API', () => {
            runTest('imports/add-same-file', addImportSameFile)
        })

        test('add another import from the same file with dedicated API and use it', () => {
            runTest('imports/add-use-same-file', addUseImportSameFile, {onlyModifyMain: true})
        })

        test.skip('add import from the new file with dedicated API', () => {
            runTest('imports/add-new-file', addImportNewFile, {onlyModifyMain: true})
        })

        test('recursive', () => {
            runTest('imports/recursive', insertParameter)
        })
    })

    suite('overloads', () => {
        test('getter and setter both modified simultaneously', () => {
            runTest('overloads/getter-setter', insertParameterToType)
        })
    })

    suite('exports', () => {
        test('import existing exported class', () => {
            runTest('exports/basic', addUseImportClassSameFile)
        })

        test('import existing not exported class', () => {
            runTest('exports/add-export', addUseImportClassSameFileAndExportClass)
        })

        test('import created class', () => {
            runTest('exports/create-class', addUseImportClassSameFileAndCreateClass)
        })
    })
})
