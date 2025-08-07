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

import * as util from "../../../test-util"
import * as ts from "../../../../src/ts-api"
import { factory } from "../../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    test("empty-function", function() {
        // function test_func() {
        //     // empty
        // }

        const sample_in = ``

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = ts.factory.createFunctionDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("test_func"),
            undefined,
            [],
            undefined,
            ts.factory.createBlock(
                [],
                true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test_func() {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test("empty-function-with-param", function() {
        const sample_in = ``

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcParams = [
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier("x"),
                undefined,
                ts.factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                undefined
            )
        ]
        const funcDecl = ts.factory.createFunctionDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("test_func"),
            undefined,
            funcParams,
            undefined,
            ts.factory.createBlock(
                [],
                true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test_func(x: number) {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test("empty-function-with-string-param", function() {
        // function test_func(x: string) {
        //     // empty
        // }

        const sample_in = ``

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcParams = [
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier("x"),
                undefined,
                ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                undefined
            )
        ]
        const funcDecl = ts.factory.createFunctionDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("test_func"),
            undefined,
            funcParams,
            undefined,
            ts.factory.createBlock(
                [],
                true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test_func(x: string) {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test("async-empty-function", function() {
        // async function test_func() {}

        const sample_in = ``

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = ts.factory.createFunctionDeclaration(
            [
                ts.factory.createToken(ts.SyntaxKind.AsyncKeyword)
            ],
            undefined,
            ts.factory.createIdentifier("test_func"),
            undefined,
            [],
            undefined,
            ts.factory.createBlock(
              [],
              true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            async function test_func() {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test.skip("empty-method-with-public-static-modifiers", function() {
        const sample_in =
        `
        class A {
        }
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let classDecl = sourceFile.statements[0]
        util.assert(ts.isClassDeclaration(classDecl))

        classDecl = factory.updateClassDeclaration(
            classDecl,
            undefined,
            factory.createIdentifier("A"),
            undefined,
            undefined,
            [
                factory.createMethodDeclaration(
                    [
                        factory.createToken(ts.SyntaxKind.PublicKeyword),
                        factory.createToken(ts.SyntaxKind.StaticKeyword)
                    ],
                    undefined,
                    factory.createIdentifier("test_func"),
                    undefined,
                    undefined,
                    [],
                    undefined,
                    factory.createBlock(
                        [],
                        false
                    )
                ),
                factory.createConstructorDeclaration(
                    [
                        factory.createToken(ts.SyntaxKind.PublicKeyword)
                    ],
                    [],
                    factory.createBlock(
                        [],
                        false
                    )
                )
            ]
        )

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                classDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            class A {
                public static test_func() {}

                public constructor() {}

            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    test("function-with-type-parameters", function() {
        // function test_func<T, K>(): void {}

        const sample_in =
        `
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = ts.factory.createFunctionDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("test_func"),
            [
                ts.factory.createTSTypeParameterDeclaration(
                    undefined,
                    ts.factory.createIdentifier("T"),
                    undefined,
                    undefined
                ),
                ts.factory.createTSTypeParameterDeclaration(
                    undefined,
                    ts.factory.createIdentifier("K"),
                    undefined,
                    undefined
                )
            ],
            [],
            ts.factory.createKeywordTypeNode(ts.SyntaxKind.VoidKeyword),
            ts.factory.createBlock(
                [],
                true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test_func<T, K>(): void {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    // TODO: change 0 -> 777 (waiting fix)
    test("sample-1", function() {
        const sample_in =
        `
        console.log("OK")
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = factory.createFunctionDeclaration(
            undefined,
            undefined,
            factory.createIdentifier("foo"),
            undefined,
            [
                factory.createParameterDeclaration(
                    undefined,
                    undefined,
                    factory.createIdentifier("x"),
                    undefined,
                    factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                    factory.createNumericLiteral(0)
                ),
                factory.createParameterDeclaration(
                    undefined,
                    undefined,
                    factory.createIdentifier("y"),
                    undefined,
                    factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                    factory.createStringLiteral("abc")
                )
            ],
            factory.createETSUnionTypeNode([
                factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword)
            ]),
            factory.createBlock(
                [factory.createReturnStatement(factory.createBinaryExpression(
                    factory.createIdentifier("x"),
                    factory.createToken(ts.SyntaxKind.PlusToken),
                    factory.createIdentifier("y")
                ))],
                true
            )
        )

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                funcDecl,
                sourceFile.statements[0]
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function foo(x: number = 0, y: string = "abc"): number | string {
                return x + y
            }
            console.log("OK")
            `
        )
    })

    // TODO: change 0 -> 777 (waiting fix)
    test("sample-2", function() {
        const sample_in =
        `
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        const funcDecl = ts.factory.createFunctionDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("foo"),
            undefined,
            [
                ts.factory.createParameterDeclaration(
                    undefined,
                    undefined,
                    ts.factory.createIdentifier("x"),
                    undefined,
                    ts.factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                    ts.factory.createNumericLiteral(0)
                ),
                ts.factory.createParameterDeclaration(
                    undefined,
                    undefined,
                    ts.factory.createIdentifier("y"),
                    undefined,
                    ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                    ts.factory.createStringLiteral("abc")
                )
            ],
            ts.factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
            ts.factory.createBlock(
                [
                    ts.factory.createReturnStatement(
                        ts.factory.createIdentifier("x")
                    )
                ],
                true
            )
        )

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                funcDecl,
                // sourceFile.statements[0]
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function foo(x: number = 0, y: string = "abc"): number {
                return x
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })
})
