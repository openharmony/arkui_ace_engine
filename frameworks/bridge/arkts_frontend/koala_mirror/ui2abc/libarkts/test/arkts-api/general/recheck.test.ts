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

import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

const PANDA_SDK_PATH = process.env.PANDA_SDK_PATH ?? '../../incremental/tools/panda/node_modules/@panda/sdk'

function createConfig() {
    arkts.arktsGlobal.config = arkts.Config.create([
        '_',
        '--arktsconfig',
        'arktsconfig.json',
        './plugins/input/main.ets',
        '--extension',
        'ets',
        '--stdlib',
        `${PANDA_SDK_PATH}/ets/stdlib`,
        '--output',
        './build/main.abc'
    ]).peer
}

class RenameTestFunction extends arkts.AbstractVisitor {
    visitor(node: arkts.BlockStatement): arkts.BlockStatement
    visitor(beforeChildren: arkts.AstNode): arkts.AstNode {
        const node = this.visitEachChild(beforeChildren)
        // Don't change name at checked stage, add another import
        if (arkts.isImportDeclaration(node)) return node
        if (arkts.isIdentifier(node) && node.name == "testFunction") {
            return arkts.factory.createIdentifier("testFunctionChanged")
        }
        return node
    }
}


suite(util.basename(__filename), () => {


    test("add import at parsed stage and proceed to checked", function() {
        createConfig()

        const code =
        `
        console.log("test")
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED)

        const program = arkts.arktsGlobal.compilerContext.program
        const importStorage = new arkts.ImportStorage(program, true)
        const module = program.ast as arkts.ETSModule

        program.setAst(
            arkts.factory.updateETSModule(
                module,
                [
                    arkts.factory.createETSImportDeclaration(
                        arkts.factory.createStringLiteral(
                            './library'
                        ),
                        [
                            arkts.factory.createImportSpecifier(
                                arkts.factory.createIdentifier(
                                    'testFunction'
                                ),
                                arkts.factory.createIdentifier(
                                    'testFunction'
                                )
                            )
                        ],
                        arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
                    ),
                    ...module.statements,
                ],
                module.ident,
                module.getNamespaceFlag(),
                module.program,
            )
        )
        importStorage.update()

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        arkts.recheckContext()

        util.assert.equal(
            program.ast.dumpSrc(), `
import { testFunction as testFunction } from "./library";

function main() {}

console.log("test");

`,
        `invalid result: ${program.ast.dumpSrc()}`)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })

    test("change function name in main program and in dependency", function() {
        createConfig()

        const code =
        `
        import { testFunction } from "./library"
        testFunction()
        `

        arkts.arktsGlobal.compilerContext = arkts.Context.createFromString(code)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        const program = arkts.arktsGlobal.compilerContext.program
        const importStorage = new arkts.ImportStorage(program, true)
        const module = program.ast as arkts.ETSModule

        arkts.programGetExternalSources(arkts.arktsGlobal.compilerContext.program).forEach(it => {
            if (!it.getName().includes("library")) return
            it.programs.forEach(program => {
                program.setAst(new RenameTestFunction().visitor(program.ast))
            })
        })

        program.setAst(
            arkts.factory.updateETSModule(
                module,
                [
                    arkts.factory.updateETSImportDeclaration(
                        module.statements[0] as arkts.ETSImportDeclaration,
                        arkts.factory.createStringLiteral(
                            './library'
                        ),
                        [
                            arkts.factory.createImportSpecifier(
                                arkts.factory.createIdentifier(
                                    'testFunctionChanged'
                                ),
                                arkts.factory.createIdentifier(
                                    'testFunctionChanged'
                                )
                            )
                        ],
                        arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
                    ),
                    ...module.statements.slice(1),
                ],
                module.ident,
                module.getNamespaceFlag(),
                module.program,
            )
        )

        program.setAst(new RenameTestFunction().visitor(program.ast))

        importStorage.update()
        arkts.recheckContext()

        util.assert.equal(
            program.ast.dumpSrc(), `
import { testFunctionChanged as testFunctionChanged } from "./library";

function main() {}

testFunctionChanged();

`,
        `invalid result: ${program.ast.dumpSrc()}`)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })
})
