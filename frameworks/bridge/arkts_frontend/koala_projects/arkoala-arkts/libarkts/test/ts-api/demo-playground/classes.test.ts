// import * as util from "../../test-util"
// import * as ts from "../../../src/ts-api"
// import { MemoTransformer } from "../../../plugins/src/memo-transformer"
//
// suite(util.basename(__filename), () => {
//     test.skip("stinger-node-class", function() {
//         const sample_in =
//         `
//         // import { uint32 } from "@koalaui/common"
//         // import { CONTEXT_ROOT_SCOPE, IncrementalNode, NodeAttach, ReadonlyTreeNode,
//         //     contextLocalValue, memoRoot, mutableState, updateStateManager,
//         // } from "@koalaui/runtime"
//
//         // type uint32 = int
//
//         abstract class IncrementalNode {
//             constructor(kind: int) {}
//         };
//
//         class StringerNode extends IncrementalNode {
//             constructor(kind: int = 1) {
//                 super(kind)
//             }
//             data: string | undefined = undefined
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
//             `
//         )
//     })
// })
