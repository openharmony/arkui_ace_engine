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
        console.log('out')
        `

        let script = arkts.EtsScript.createFromSource(sample_in)

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                script.statements[0],
                arkts.factory.createExpressionStatement(
                    arkts.factory.createCallExpression(
                        arkts.factory.createMemberExpression(
                            arkts.factory.createIdentifier(
                                'console'
                            ),
                            arkts.Identifier.create2Identifier(
                                'log'
                            ),
                            arkts.Es2pandaMemberExpressionKind.MEMBER_EXPRESSION_KIND_PROPERTY_ACCESS,
                            false,
                            false
                        ),
                        undefined,
                        [
                            arkts.factory.createStringLiteral(
                                'out'
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
