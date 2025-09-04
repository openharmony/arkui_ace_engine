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

suite(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        function _() {};
        `

        const sample_out =
        `
        function _() {};
        function foo() {
            console.log("AAA")
        }
        foo()
        `

        let script = arkts.createETSModuleFromSource(sample_in)

        const scriptFunc =
            arkts.factory.createScriptFunction(
                arkts.factory.createBlockStatement(
                    [
                        arkts.factory.createExpressionStatement(
                            arkts.factory.createCallExpression(
                                arkts.factory.createMemberExpression(
                                    arkts.factory.createIdentifier(
                                        'console'
                                    ),
                                    arkts.factory.createIdentifier(
                                        'log'
                                    ),
                                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                                    false,
                                    false
                                ),

                                [
                                    arkts.factory.createStringLiteral(
                                        'AAA'
                                    )
                                ],
                                        undefined,
                            )
                        )
                    ]
                ),
                undefined,
                [],
                undefined,
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                arkts.factory.createIdentifier("foo"),
                undefined,
            )

        const funcDecl =
            arkts.factory.createFunctionDeclaration(
                scriptFunc,
                [],
                false
            )
        funcDecl.updateModifiers(scriptFunc.modifierFlags)

        script = arkts.factory.updateETSModule(
            script,
            [
                script.statements[0],
                funcDecl,
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        [],
                        undefined,
                    )
                )
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            sample_out
        )
    })

    test("sample-2", function() {
        const sample_in =
        `
        function _() {};
        `

        const sample_out =
        `
        function _() {};
        function foo(x: int, y: string = "bbb") {
            console.log(x)
            console.log(y)
        }
        foo(0)
        `

        let script = arkts.createETSModuleFromSource(sample_in)

        const scriptFunc =
            arkts.factory.createScriptFunction(
                arkts.factory.createBlockStatement(
                    [
                        arkts.factory.createExpressionStatement(
                            arkts.factory.createCallExpression(
                                arkts.factory.createMemberExpression(
                                    arkts.factory.createIdentifier(
                                        'console'
                                    ),
                                    arkts.factory.createIdentifier(
                                        'log'
                                    ),
                                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                                    false,
                                    false
                                ),

                                [
                                    arkts.factory.createIdentifier(
                                        'x'
                                    )
                                ],
                                        undefined,
                            )
                        ),
                        arkts.factory.createExpressionStatement(
                            arkts.factory.createCallExpression(
                                arkts.factory.createMemberExpression(
                                    arkts.factory.createIdentifier(
                                        'console'
                                    ),
                                    arkts.factory.createIdentifier(
                                        'log'
                                    ),
                                    arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                                    false,
                                    false
                                ),

                                [
                                    arkts.factory.createIdentifier(
                                        'y'
                                    )
                                ],
                                        undefined,
                            )
                        )
                    ]
                ),
                undefined,
                [
                    arkts.factory.createETSParameterExpression(
                        arkts.factory.createIdentifier(
                            'x',
                            arkts.factory.createETSPrimitiveType(
                                arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_INT
                            )
                        ),
                        false
                    ),
                    arkts.factory.createETSParameterExpression(
                        arkts.factory.createIdentifier(
                            'y',
                            arkts.factory.createETSTypeReference(
                                arkts.factory.createETSTypeReferencePart(
                                    arkts.factory.createIdentifier(
                                        'string'
                                    )
                                )
                            )
                        ),
                        false,
                        arkts.factory.createStringLiteral(
                            'bbb'
                        )
                    )
                ],
                undefined,
                false,
                arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE,
                arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                arkts.factory.createIdentifier("foo"),
                undefined,
            )

        const funcDecl =
            arkts.factory.createFunctionDeclaration(
                scriptFunc,
                [],
                false
            )
        funcDecl.updateModifiers(scriptFunc.modifierFlags)

        script = arkts.factory.updateETSModule(
            script,
            [
                script.statements[0],
                funcDecl,
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        [
                            arkts.factory.createNumberLiteral(
                                0
                            )
                        ],
                        undefined,
                    )
                )
            ],
            script.ident,
            script.getNamespaceFlag(),
            script.program,
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            sample_out
        )
    })
})
