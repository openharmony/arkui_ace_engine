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

import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"
import { factory } from "../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    test("const-number", function() {
        const sample_in =
        `
        function f() {}
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const varDecl = factory.createVariableStatement(
            undefined,
            factory.createVariableDeclarationList(
                [
                    factory.createVariableDeclaration(
                        factory.createIdentifier("x"),
                        undefined,
                        factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                        factory.createNumericLiteral(0)
                    )
                ],
                ts.NodeFlags.Const
            )
        )

        const f = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(f))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.updateFunctionDeclaration(
                    f,
                    f.modifiers,
                    undefined,
                    f.name,
                    f.typeParameters,
                    f.parameters,
                    f.type,
                    factory.createBlock([
                        varDecl
                    ])
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function f() {
                const x: number = 0
            }
            `
        )
    })

    test("declaration-list", function() {
        // const x: number = 0, y: string = "a", z = 0

        const sample_in = `const x = 1`

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const varStatement = sourceFile.statements[0]
        util.assert(ts.isVariableStatement(varStatement))

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                factory.updateVariableStatement(
                    varStatement,
                    [
                        // Improve: not ok maybe (problem with ModifierFlags)
                        factory.createToken(ts.SyntaxKind.PublicKeyword),
                        factory.createToken(ts.SyntaxKind.StaticKeyword),
                        factory.createToken(ts.SyntaxKind.ConstKeyword),
                    ],
                    factory.createVariableDeclarationList(
                        [
                            factory.createVariableDeclaration(
                                factory.createIdentifier("x"),
                                undefined,
                                factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                                factory.createNumericLiteral(0)
                            ),
                            factory.createVariableDeclaration(
                                factory.createIdentifier("y"),
                                undefined,
                                factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                                factory.createStringLiteral("a")
                            ),
                            factory.createVariableDeclaration(
                                factory.createIdentifier("z"),
                                undefined,
                                undefined,
                                factory.createNumericLiteral(0)
                            )
                        ],
                        ts.NodeFlags.Const
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            const x: number = 0, y: string = "a", z = 0
            `
        )
    })

    test.skip("let-vars", function() {
        const sample_in =
        `
        const x = 0
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const varStatement = sourceFile.statements[0]
        util.assert(ts.isVariableStatement(varStatement))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.updateVariableStatement(
                    varStatement,
                    [
                        // Improve: not ok maybe (problem with ModifierFlags)
                        factory.createToken(ts.SyntaxKind.PublicKeyword),
                        factory.createToken(ts.SyntaxKind.StaticKeyword),
                    ],
                    factory.createVariableDeclarationList(
                        [
                            factory.createVariableDeclaration(
                                factory.createIdentifier("x"),
                                undefined,
                                factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                                factory.createNumericLiteral(0)
                            ),
                            factory.createVariableDeclaration(
                                factory.createIdentifier("y"),
                                undefined,
                                factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                                factory.createStringLiteral("a")
                            ),
                            factory.createVariableDeclaration(
                                factory.createIdentifier("z"),
                                undefined,
                                undefined,
                                factory.createNumericLiteral(0)
                            )
                        ],
                        ts.NodeFlags.Let
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            let x: number = 0, y: string = "a", z = 0
            `
        )
    })

    test("parenthesized-expression", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.createVariableStatement(
                    [
                        // Improve: not ok maybe (problem with ModifierFlags)
                        factory.createToken(ts.SyntaxKind.PublicKeyword),
                        factory.createToken(ts.SyntaxKind.StaticKeyword),
                        factory.createToken(ts.SyntaxKind.ConstKeyword),
                    ],
                    factory.createVariableDeclarationList(
                        [
                            factory.createVariableDeclaration(
                                factory.createIdentifier("x"),
                                undefined,
                                factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                                factory.createBinaryExpression(
                                    factory.createParenthesizedExpression(
                                        factory.createBinaryExpression(
                                            factory.createNumericLiteral(0),
                                            factory.createToken(ts.SyntaxKind.PlusToken),
                                            factory.createNumericLiteral(0)
                                        )
                                    ),
                                    factory.createToken(ts.SyntaxKind.AsteriskToken),
                                    factory.createNumericLiteral(0)
                                )
                            )
                        ],
                        ts.NodeFlags.Const
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            const x: number = (0 + 0) * 0
            `
        )
    })

    test.skip("question-mark", function() {
        const sample_in =
        `
        function foo(x?: number | undefined) {
            console.log(x);
        }
        foo()
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function foo(x?: number | undefined) {
                console.log(x);
            }
            foo()
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })
})
