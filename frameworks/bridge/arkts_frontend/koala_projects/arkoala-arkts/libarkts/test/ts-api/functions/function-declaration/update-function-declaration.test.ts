import * as util from "../../../test-util"
import * as ts from "../../../../src/ts-api"

suite.skip(util.basename(__filename), () => {
    // adding y: string to signature
    test("update-name-and-add-param-to-function", function() {
        // function new_test_func(x: number, y: string) {
        //     // empty
        // }

        const sample_in =
        `
        function test_func(x: number) {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))

        const newParam = ts.factory.createParameterDeclaration(
            undefined,
            undefined,
            ts.factory.createIdentifier("y"),
            undefined,
            ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
            undefined
        )
        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            ts.factory.createIdentifier("new_test_func"),
            undefined,
            [
                ...testFunc.parameters,
                newParam
            ],
            undefined,
            testFunc.body
        )
        sourceFile = ts.factory.updateSourceFile(
            sourceFile,
            [
                testFunc
            ]
        )

        util.TS_TEST_ASSERTION(
            sourceFile,
            `
            function new_test_func(x: number, y: string) {}
            `
        )
    })

    // adding memo params to signature
    test("add-params-to-memo-function", function() {
        // function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number) {
        //     // empty
        // }

        const sample_in =
        `
        function foo(x: number) {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))

        testFunc = util.addMemoParamsToFunctionDeclaration(testFunc)
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
            function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type, x: number) {}
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    // adding identifier x
    test("add-identifier-to-function-body", function() {
        // function foo() {
        //     x
        // }

        const sample_in =
        `
        function foo(x: string) {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

        let body_statements = [
            ...testFunc.body.statements,
            ts.factory.createExpressionStatement(ts.factory.createIdentifier("x"))
        ]

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            testFunc.parameters,
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
            function foo(x: string) {
                x
            }
            `
        )
    })

    // adding __memo_scope.recache
    test("add-property-access-expression-to-function-body", function() {
        // function foo() {
        //     __memo_scope.recache
        // }

        const sample_in =
        `
        function foo() {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

        let body_statements = [
            ...testFunc.body.statements,
            ts.factory.createExpressionStatement(
                ts.factory.createPropertyAccessExpression(
                    ts.factory.createIdentifier("__memo_scope"),
                    ts.factory.createIdentifier("recache")
                )
            )
        ]

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            testFunc.parameters,
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
            function foo() {
                __memo_scope.recache;
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    // body memo rewrite (adding return statement)
    test("add-return-statement-to-function-body", function() {
        // function foo() {
        //     return __memo_scope.recache()
        // }

        const sample_in =
        `
        function foo() {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

        let body_statements = [
            ...testFunc.body.statements,
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

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            testFunc.parameters,
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
            function foo() {
                return __memo_scope.recache();
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    // body memo rewrite (adding if statement)
    test("add-if-statement-to-function-body", function() {
        // function foo() {
        //     if (__memo_scope.unchanged)
        //         return __memo_scope.cached
        // }

        const sample_in =
        `
        function foo() {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

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
            ...testFunc.body.statements
        ]

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            testFunc.parameters,
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
            function foo() {
                if (__memo_scope.unchanged) {
                    return __memo_scope.cached;
                }
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })

    // body memo rewrite
    test("function-declaration-memo-rewrite", function() {
        // function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
        //     if (__memo_scope.unchanged)
        //         return __memo_scope.cached
        //     content(__memo_context, __memo_id + "key_id_main.ts")
        //     return __memo_scope.recache()
        // }

        const sample_in =
        `
        function foo() {
            // empty
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

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
            ),
            ...testFunc.body.statements
        ]

        testFunc = util.addMemoParamsToFunctionDeclaration(testFunc)
        util.assert(ts.isFunctionDeclaration(testFunc))
        util.assert(testFunc.body !== undefined)

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
            undefined,
            undefined,
            testFunc.name,
            undefined,
            testFunc.parameters,
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
            function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
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

    test("return-lambda", function() {
        const sample_in =
        `
        function foo() {}
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        let testFunc = sourceFile.statements[0]
        util.assert(ts.isFunctionDeclaration(testFunc))

        testFunc = ts.factory.updateFunctionDeclaration(
            testFunc,
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
                    ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                    undefined
                )
            ],
            undefined,
            ts.factory.createBlock(
                [
                    ts.factory.createReturnStatement(
                        ts.factory.createCallExpression(
                            ts.factory.createParenthesizedExpression(
                                ts.factory.createArrowFunction(
                                    undefined,
                                    undefined,
                                    [
                                        ts.factory.createParameterDeclaration(
                                            undefined,
                                            undefined,
                                            ts.factory.createIdentifier("val"),
                                            undefined,
                                            ts.factory.createKeywordTypeNode(ts.SyntaxKind.StringKeyword),
                                            ts.factory.createIdentifier("x")
                                        )
                                    ],
                                    undefined,
                                    ts.factory.createToken(ts.SyntaxKind.EqualsGreaterThanToken),
                                    ts.factory.createBlock(
                                        [
                                            ts.factory.createExpressionStatement(
                                                ts.factory.createIdentifier("val")
                                            )
                                        ],
                                        false
                                    )
                                )
                            ),
                            undefined,
                            []
                        )
                    )
                ],
                true
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
            function foo(x: string) {
                return ((val: string = x) => { val })()
            }
            `,
            ts.ContextState.ES2PANDA_STATE_PARSED,
        )
    })
})
