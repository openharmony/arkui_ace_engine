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

        let script = arkts.EtsScript.createFromSource(sample_in)

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                script.statements[0],
                arkts.factory.createFunctionDeclaration(
                    arkts.factory.createScriptFunction(
                        arkts.factory.createBlock(
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
                                        undefined,
                                        [
                                            arkts.factory.createStringLiteral(
                                                'AAA'
                                            )
                                        ]
                                    )
                                )
                            ]
                        ),
                        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE,
                        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                        false,
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        [],
                        undefined,
                        undefined
                    ),
                    false
                ),
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        undefined,
                        []
                    )
                )
            ]
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

        let script = arkts.EtsScript.createFromSource(sample_in)

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                script.statements[0],
                arkts.factory.createFunctionDeclaration(
                    arkts.factory.createScriptFunction(
                        arkts.factory.createBlock(
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
                                        undefined,
                                        [
                                            arkts.factory.createIdentifier(
                                                'x'
                                            )
                                        ]
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
                                        undefined,
                                        [
                                            arkts.factory.createIdentifier(
                                                'y'
                                            )
                                        ]
                                    )
                                )
                            ]
                        ),

                        arkts.Es2pandaScriptFunctionFlags.SCRIPT_FUNCTION_FLAGS_NONE,
                        arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_PUBLIC | arkts.Es2pandaModifierFlags.MODIFIER_FLAGS_STATIC,
                        false,
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        [
                            arkts.factory.createParameterDeclaration(
                                arkts.factory.createIdentifier(
                                    'x',
                                    arkts.factory.createPrimitiveType(
                                        arkts.Es2pandaPrimitiveType.PRIMITIVE_TYPE_INT
                                    )
                                ),
                                undefined
                            ),
                            arkts.factory.createParameterDeclaration(
                                arkts.factory.createIdentifier(
                                    'y',
                                    arkts.factory.createTypeReference(
                                        arkts.factory.createTypeReferencePart(
                                            arkts.factory.createIdentifier(
                                                'string'
                                            )
                                        )
                                    )
                                ),
                                arkts.factory.createStringLiteral(
                                    'bbb'
                                )
                            )
                        ],
                        undefined,
                        undefined
                    ),
                    false
                ),
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createIdentifier(
                            'foo'
                        ),
                        undefined,
                        [
                            arkts.factory.createNumericLiteral(
                                0
                            )
                        ]
                    )
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            sample_out
        )
    })
})
