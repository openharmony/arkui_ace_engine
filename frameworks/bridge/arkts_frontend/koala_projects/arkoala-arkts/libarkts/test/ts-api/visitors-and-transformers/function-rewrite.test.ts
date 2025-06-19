// import * as util from "../../test-util"
// import * as ts from "../../../src/ts-api"
// import global from "src/arkts-api/static/global"
// import { FunctionTransformer } from "../../../plugins/src/function-transformer"
// import { PrintVisitor } from "../../../plugins/src/print-visitor"
//
// suite.skip(util.getSuiteTitle(__filename), () => {
//     test("function-transformer-sample-1", function() {
//         const sample_in =
//         `
//         const x: string = "A"
//
//         function _REWRITE_foo() {
//             console.log("FUNC CALLED: " + x)
//         }
//
//         _REWRITE_foo()
//         `
//
//         const sourceFile = ts.factory.createSourceFile(sample_in, ts.ContextState.ES2PANDA_STATE_CHECKED)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         // util.nativeModule._VarBinderSetContext(global.context)
//         // util.nativeModule._VarBinderSetProgram(global.context)
//         // util.nativeModule._VarBinderSetGenStdLib(global.context, false)
//         // util.nativeModule._VarBinderInitTopScope(global.context)
//         // util.nativeModule._VarBinderIdentifierAnalysis(global.context)
//
//         const result = (new FunctionTransformer()).visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.TS_TEST_ASSERTION(
//             sourceFile,
//             `
//             const x: string = "A"
//
//             function foo(x: string) {
//                 console.log("FUNC CALLED: " + x)
//             }
//
//             foo("SAMPLE")
//            `,
//             ts.ContextState.ES2PANDA_STATE_CHECKED,
//         )
//
//         // TODO:
//         util.nativeModule._VarBinderInitTopScope(global.context)
//         util.nativeModule._VarBinderIdentifierAnalysis(global.context)
//         ts.proceedToState(ts.ContextState.ES2PANDA_STATE_BIN_GENERATED)
//     })
// })
