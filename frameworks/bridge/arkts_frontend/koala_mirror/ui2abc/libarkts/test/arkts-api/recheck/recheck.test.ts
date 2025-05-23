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

const DIR = './test/arkts-api/recheck/'

function createConfig(file: string) {
    fs.mkdirSync(`${DIR}/build/abc/${file}`, { recursive: true })
    arkts.arktsGlobal.filePath = `${DIR}/${file}/main.ts`
    arkts.arktsGlobal.config = arkts.Config.create([
        '_',
        '--arktsconfig',
        `${DIR}/arktsconfig.json`,
        `${DIR}/${file}/main.ts`,
        '--extension',
        'ets',
        '--stdlib',
        '../build/sdk/ets/stdlib',
        '--output',
        `${DIR}/build/abc/${file}/main.abc`
    ]).peer
}

function createContext(file: string) {
    const code = fs.readFileSync(`${DIR}/${file}/main.ts`, 'utf-8')
    arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)
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
            if (!onlyModifyMain) {
                transform?.(program, { isMainProgram: false, name: "", stage: arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED })
            }
            arkts.setBaseOverloads(ast)
            arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, ast.peer)
        })
    })

    const script = arkts.createETSModuleFromContext()
    transform?.(arkts.arktsGlobal.compilerContext.program, { isMainProgram: true, name: "", stage: arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED })
    arkts.setBaseOverloads(script)
    arkts.arktsGlobal.es2panda._AstNodeUpdateAll(arkts.arktsGlobal.context, script.peer)
}

function recheck() {
    arkts.recheckSubtree(arkts.createETSModuleFromContext())
}

function dumpSrc(file: string) {
    const src = arkts.createETSModuleFromContext().dumpSrc()
    fs.mkdirSync(`${DIR}/${file}/dump-src`, { recursive: true })
    fs.writeFileSync(`${DIR}/${file}/dump-src/main.ts`, src)
}

function dumpJson(file: string) {
    const json = arkts.createETSModuleFromContext().dumpJson()
    fs.mkdirSync(`${DIR}/${file}/dump-json`, { recursive: true })
    fs.writeFileSync(`${DIR}/${file}/dump-json/main.json`, json)
}

function assertSrc(file: string) {
    const src = arkts.createETSModuleFromContext().dumpSrc()
    const expected = fs.readFileSync(`${DIR}/${file}/dump-src/main.ts`, 'utf-8')
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

function runTest(
    file: string,
    transform?: arkts.ProgramTransformer,
    skipSrc?: boolean,
    skipJson?: boolean,
    onlyModifyMain?: boolean,
) {
    createConfig(file)
    createContext(file)
    proceedToChecked()
    applyTransform(transform, onlyModifyMain)
    recheck()
    if (process.env.TEST_GOLDEN == "1") {
        if (!skipSrc) dumpSrc(file)
        if (!skipJson) dumpJson(file)
    } else {
        if (!skipSrc) assertSrc(file)
        if (!skipJson) assertJson(file)
    }
    proceedToBin()
}

suite(util.basename(__filename), () => {
    suite('static', () => {
        test("function", () => {
            runTest('static/function', undefined, false, true)
        })

        test("public setter", () => {
            runTest('static/public-setter', undefined, false, true)
        })

        test("constructor with overload", () => {
            runTest('static/constructor', undefined, false, true)
        })

        // es2panda issue 24821
        test.skip("property", () => {
            runTest('static/property', undefined, false, true)
        })

        test("typed property", () => {
            runTest('static/typed-property', undefined, false, true)
        })

        test("trailing block", () => {
            runTest('static/trailing-block', undefined, false, true)
        })

        test("import type", () => {
            runTest('static/import-type', undefined, false, true)
        })
    })

    suite('simple', () => {
        test('rename class', () => {
            runTest('simple/rename-class', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, renameClass)
            }, false, true)
        })

        test('add class method', () => {
            runTest('simple/add-class-method', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, addClassMethod)
            }, false, true)
        })

        test('add variable declaration', () => {
            runTest('simple/add-variable', (program: arkts.Program) => {
                return updateTopLevelClass(program.astNode, addVariableDeclaration)
            }, false, true)
        })
    })

    test.skip('constructor', () => {
        runTest('constructor', constructorWithOverload, false, true)
    })

    test('add this reference', () => {
        runTest('this', addThisReference, false, true)
    })

    suite('imports', () => {
        test('add another import from the same file with dedicated API', () => {
            runTest('imports/add-same-file', addImportSameFile, false, true)
        })

        test('add another import from the same file with dedicated API and use it', () => {
            runTest('imports/add-use-same-file', addUseImportSameFile, false, true, true)
        })

        test.skip('add import from the new file with dedicated API', () => {
            runTest('imports/add-new-file', addImportNewFile, false, true, true)
        })

        test('recursive', () => {
            runTest('imports/recursive', insertParameter, false, true)
        })
    })

    suite('overloads', () => {
        test('getter and setter both modified simultaneously', () => {
            runTest('overloads/getter-setter', insertParameterToType, false, true)
        })
    })    
})
