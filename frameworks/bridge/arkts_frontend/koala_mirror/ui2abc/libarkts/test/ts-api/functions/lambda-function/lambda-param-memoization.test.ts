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

suite.skip(util.basename(__filename), () => {
    // full memo rewrite
    test("memo-function-with-lambda-memo-param", function() {
        // function foo(
        //     __memo_context: __memo_context_type,
        //     __memo_id: __memo_id_type,
        //     content: (__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void
        // ) {
        //     if (__memo_scope.unchanged)
        //         return __memo_scope.cached
        //     content(__memo_context, __memo_id + "key_id_main.ts")
        //     return __memo_scope.recache()
        // }

        const sample_in =
        `
        function foo(
            content: () => void
        ) {
            content()
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))

        let body_statements = [
            ts.factory.createIfStatement(
                ts.factory.createPropertyAccessExpression(
                    ts.factory.createIdentifier("__memo_scope"),
                    ts.factory.createIdentifier("unchanged")
                ),
                ts.factory.createBlock([
                    ts.factory.createReturnStatement(
                        ts.factory.createPropertyAccessExpression(
                            ts.factory.createIdentifier("__memo_scope"),
                            ts.factory.createIdentifier("cached")
                        )
                    )
                ]),
                undefined
            ),
            ts.factory.createExpressionStatement(
                ts.factory.createCallExpression(
                    ts.factory.createIdentifier("content"),
                    undefined,
                    [
                    ts.factory.createIdentifier("__memo_context"),
                    ts.factory.createBinaryExpression(
                        ts.factory.createIdentifier("__memo_id"),
                        ts.factory.createToken(ts.SyntaxKind.PlusToken),
                        ts.factory.createStringLiteral("key_id_main.ts")
                    )
                    ]
            )),
            ts.factory.createReturnStatement(
                ts.factory.createCallExpression(
                    ts.factory.createPropertyAccessExpression(
                        ts.factory.createIdentifier("__memo_scope"),
                        ts.factory.createIdentifier("recache")
                    ),
                    undefined,
                    undefined
                )
            )
        ]

        testFunc = util.addMemoParamsToFunctionDeclaration(testFunc)
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

        const newLambdaParams = [
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier("__memo_context"),
                undefined,
                ts.factory.createETSTypeReferenceNode(
                    ts.factory.createIdentifier("__memo_context_type"),
                    undefined
                )
            ),
            ts.factory.createParameterDeclaration(
                undefined,
                undefined,
                ts.factory.createIdentifier("__memo_id"),
                undefined,
                ts.factory.createETSTypeReferenceNode(
                    ts.factory.createIdentifier("__memo_id_type"),
                    undefined
                ),
            )
        ]

        const newLambdaParam = ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("content"),
            undefined,
            ts.factory.createFunctionTypeNode(
                undefined,
                newLambdaParams,
                ts.factory.createKeywordTypeNode(ts.SyntaxKind.VoidKeyword)
            ),
            undefined
        )

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            [
                testFunc.parameters[0],
                testFunc.parameters[1],
                newLambdaParam
            ],
            undefined,
            ts.factory.updateBlock(
                testFunc.body,
                body_statements
            )
        )
        util.assert(ts.isFunctionDeclaration(testFunc))

        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                testFunc
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type, content: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)) {
            if (__memo_scope.unchanged) {
                return __memo_scope.cached;
            }
            content(__memo_context, ((__memo_id) + ("key_id_main.ts")));
            return __memo_scope.recache();
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })
})
