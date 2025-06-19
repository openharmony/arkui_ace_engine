// import * as util from "../../test-util"
// import * as ts from "../../../src/ts-api"
// import { MemoTransformer } from "../../../plugins/src/memo-transformer"
//
// suite(util.getSuiteTitle(__filename), () => {
//     test.skip("function-stinger", function() {
//         const sample_in =
//         `
//         /** @memo */
//         function _MEMO_Stringer(
//             arg: string,
//             /** @memo */
//             _MEMO_content: () => void
//         ): void {
//             _MEMO_content()
//         }
//         `
//
//         const sourceFile = ts.factory.createSourceFile(sample_in, ts.ContextState.ES2PANDA_STATE_CHECKED)
//         util.assert(ts.isSourceFile(sourceFile))
//
//         const result = (new MemoTransformer()).visitor(sourceFile)
//         util.assert(ts.isSourceFile(result))
//
//         util.assertEqualsSource(
//             result.node.dumpSrc(),
//             `
//             abstract class ETSGLOBAL {
//             public static _$init$_() {}
//
//             public static Stringer(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: string, _MEMO_content: (()=> void)) {
//                 if (__memo_scope.unchanged) {
//                 return __memo_scope.cached;
//                 }
//                 content(__memo_context, ((__memo_id) + ("key_id_main.ts")));
//                 content(__memo_context, __memo_id);
//                 return __memo_scope.recache();
//             }
//
//
//             }
//             `
//         )
//     })
// })
