import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"

suite(util.basename(__filename), () => {
    test.skip("sample-1", function() {
        const sample_in =
        `
        function foo() {}
        `

        let script = arkts.EtsScript.createFromSource(
            sample_in,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        const expr = arkts.factory.createExpressionStatement(
            arkts.factory.createIdentifier(
                'abc'
            )
        )

        script = arkts.EtsScript.updateByStatements(
            script,
            [
                expr
            ]
        )

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_CHECKED)

        arkts.recheckSubtree(expr)

        arkts.proceedToState(arkts.Es2pandaContextState.ES2PANDA_STATE_BIN_GENERATED)
    })
})
