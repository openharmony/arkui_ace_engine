import * as util from "../../test-util"
import * as arkts from "../../../src/arkts-api"
import { assert } from "chai"

suite(util.basename(__filename), () => {
    test("annotated-function-1", function() {
        const sample_in =
        `
        @annotation1
        @annotation2
        function foo() {}
        `

        let script = arkts.EtsScript.createFromSource(
            sample_in,
            arkts.Es2pandaContextState.ES2PANDA_STATE_PARSED
        )

        const annotations = arkts.getAnnotations(script.statements[0])

        const names = annotations.map((annot) => {
            if (annot.expr === undefined) {
                throw new Error('annotation expression is undefined')
            }
            if (!arkts.isIdentifier(annot.expr)) {
                throw new Error('annotation expected to be Identifier')
            }
            return annot.expr.name
        })

        assert.equal(names.join(', '), 'annotation1, annotation2')
    })
})
