import * as util from "../../test-util"
import * as ts from "../../../src/ts-api"
import { MemoTransformer } from "../../../plugins/src/memo-transformer"

suite.skip(util.basename(__filename), () => {
    test("memo-transformer-sample-1", function() {
        const sample_in =
        `
        function _MEMO_foo() {
            console.log("MEMO FUNC CALLED!")
        }

        _MEMO_foo()
        `

        // util.getDefaultSetup(sample_in)

        // arkts.proceedToState(arkts.ContextState.ES2PANDA_STATE_CHECKED)

        // const sourceFile = arkts.makeView(util.AstProvider.provideAst())

        // const memoTransformer = new MemoTransformer()
        // const transformed = memoTransformer.visitor(sourceFile)

        // console.log(arkts.dumpSrcNode(sourceFile))
    })
})
