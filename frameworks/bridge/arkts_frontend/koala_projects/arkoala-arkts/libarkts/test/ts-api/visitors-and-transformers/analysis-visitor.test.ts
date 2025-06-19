// import * as util from "../../test-util"
// import * as ts from "../../../src/ts-api"
// import { AnalysisVisitor } from "../../../plugins/src/analysis-visitor"
// import { Tracer } from "../../../plugins/src/util"
// import { Rewrite } from "../../../plugins/src/transformation-context"
//
// suite(util.getSuiteTitle(__filename), () => {
//     test("sample-1", function() {
//         const sample_in =
//         `
//         const _memo_x: string = "A"
//
//         function _memo_foo() {}
//
//         _memo_foo()
//         `
//
//         let sourceFile = ts.factory.createSourceFile(sample_in)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         // ts.proceedToState(ts.ContextState.ES2PANDA_STATE_CHECKED)
//
//         const options = {}
//
//         const tracer = new Tracer(options)
//         const rewrite = new Rewrite(sourceFile, options)
//
//         const result = new AnalysisVisitor(tracer, rewrite).visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.assert(rewrite.functionTable.size === 1)
//         util.assert(rewrite.callTable.size === 1)
//         util.assert(rewrite.variableTable.size === 1)
//     })
// })
