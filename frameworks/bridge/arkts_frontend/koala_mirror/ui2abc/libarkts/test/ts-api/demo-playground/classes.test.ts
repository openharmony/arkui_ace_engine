/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
