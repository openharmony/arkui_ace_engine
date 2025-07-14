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
    test("sample-1", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.createExpressionStatement(
                    factory.createIdentifier("abc")
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            abc
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("sample-2", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.createFunctionDeclaration(
                    undefined,
                    undefined,
                    factory.createIdentifier("test"),
                    undefined,
                    [],
                    undefined,
                    factory.createBlock(
                        [],
                        true
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test() {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("sample-3", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.createFunctionDeclaration(
                    undefined,
                    undefined,
                    factory.createIdentifier("test"),
                    undefined,
                    [
                        factory.createParameterDeclaration(
                            undefined,
                            undefined,
                            factory.createIdentifier("x"),
                            undefined,
                            factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                            undefined
                        )
                    ],
                    factory.createKeywordTypeNode(ts.SyntaxKind.NumberKeyword),
                    factory.createBlock(
                        [
                            factory.createReturnStatement(
                                factory.createNumericLiteral(0)
                            )
                        ],
                        true
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test(x: string): number {
                return 0;
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })

    test("sample-4", function() {
        const sample_in =
        `
        `

        let sourceFile = factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        sourceFile = factory.updateSourceFile(
            sourceFile,
            [
                factory.createFunctionDeclaration(
                    undefined,
                    undefined,
                    factory.createIdentifier("test"),
                    [
                        factory.createTSTypeParameterDeclaration(
                            undefined,
                            factory.createIdentifier("T"),
                            factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                            undefined
                        )
                    ],
                    [
                        factory.createParameterDeclaration(
                            undefined,
                            undefined,
                            factory.createIdentifier("x"),
                            undefined,
                            factory.createETSTypeReferenceNode(
                                factory.createIdentifier("T"),
                                undefined
                            ),
                            undefined
                        )
                    ],
                    factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                    factory.createBlock(
                        [
                            factory.createReturnStatement(
                                factory.createStringLiteral("aaa")
                            )
                        ],
                        true
                    )
                )
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function test<T extends string>(x: T): string {
                return "aaa"
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED
        )
    })
})
