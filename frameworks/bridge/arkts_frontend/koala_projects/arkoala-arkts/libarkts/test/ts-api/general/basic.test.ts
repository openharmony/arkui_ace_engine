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
                        factory.createTypeParameterDeclaration(
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
                            factory.createTypeReferenceNode(
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
