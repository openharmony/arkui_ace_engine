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
import { global } from "../../../src/arkts-api/static/global"


suite(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        `

        let script = arkts.createETSModuleFromSource(sample_in)

        script = arkts.factory.updateETSModule(
            script,
            [
                arkts.factory.createETSImportDeclaration(
                    arkts.factory.createStringLiteral(
                        './variable'
                    ),
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
                )
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("sample-2-rewrite", function() {
        const sample_in =
        `
        import { Y } from "./variable"
        `

        let script = arkts.createETSModuleFromSource(sample_in)
        const importDeclaration = script.statements[0] as arkts.ETSImportDeclaration

        script = arkts.factory.updateETSModule(
            script,
            [
                arkts.factory.createETSImportDeclaration(
                    arkts.factory.createStringLiteral(
                        './variable'
                    ),
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
                ),
                ...script.statements,
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"
            import { Y } from "./variable"
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("rewrite-imported-variable", function() {
        const sample_in =
        `
        import { Y } from "./variable"

        function main() {
            console.log(X)
        }
        `

        let script = arkts.createETSModuleFromSource(sample_in)
        const importDeclaration = script.statements[0] as arkts.ETSImportDeclaration

        script = arkts.factory.updateETSModule(
            script,
            [
                arkts.factory.createETSImportDeclaration(
                    arkts.factory.createStringLiteral(
                        './variable'
                    ),
                    [
                        arkts.factory.createImportSpecifier(
                            arkts.factory.createIdentifier(
                                'X'
                            ),
                            arkts.factory.createIdentifier(
                                'X'
                            )
                        )
                    ],
                    arkts.Es2pandaImportKinds.IMPORT_KINDS_ALL,
                ),
                ...script.statements,
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { X } from "./variable"
            import { Y } from "./variable"

            function main() {
                console.log(X)
            }
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        // util.cleanGenerated()
        // util.fileToAbc(`./input/variable.sts`, true)
        // util.contextToAbc()
        // util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })

    test("rewrite-imported-function", function() {
        const sample_in =
        `
        import { f } from "./f"
        function main() {}
        `

        let script = arkts.createETSModuleFromSource(sample_in)
        const functionDeclaration: arkts.FunctionDeclaration = script.statements[1] as arkts.FunctionDeclaration
        const scriptFunction: arkts.ScriptFunction = functionDeclaration.function!

        const newScriptFunc =
            arkts.factory.updateScriptFunction(
                scriptFunction,
                arkts.factory.createBlockStatement(
                    [
                        arkts.factory.createExpressionStatement(
                            arkts.factory.createCallExpression(
                                arkts.factory.createIdentifier(
                                    'f'
                                ),
                                [],undefined,

                            )
                        )
                    ]
                ),
                undefined,
                [],
                undefined,
                false,
                scriptFunction.flags,
                scriptFunction.modifierFlags,
                scriptFunction.id!,
                undefined,
            )

        const newFuncDecl =
            arkts.factory.updateFunctionDeclaration(
                functionDeclaration,
                newScriptFunc,
                [],
                false
            )
        newFuncDecl.updateModifiers(newScriptFunc.modifierFlags)

        script = arkts.factory.updateETSModule(
            script,
            [
                script.statements[0],
                newFuncDecl
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            import { f } from "./f"
            function main() {
                f()
            }
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        // util.cleanGenerated()
        // util.fileToAbc(`./input/f.sts`, true)
        // util.contextToAbc()
        // util.runAbc(`./generated/main.abc`, ['./generated/f.abc'])
    })
})
