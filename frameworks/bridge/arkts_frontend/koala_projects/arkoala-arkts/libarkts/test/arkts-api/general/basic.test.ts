import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

suite(util.basename(__filename), () => {
    test("sample-1", function() {
        const sample_in =
        `
        `

        let script = arkts.EtsScript.createFromSource(sample_in)

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                arkts.factory.createExpressionStatement(
                    arkts.factory.createIdentifier(
                        'abc'
                    )
                )
            ]
        )

        util.ARKTS_TEST_ASSERTION(
            script,
            `
            abc
            `,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )
    })
})
