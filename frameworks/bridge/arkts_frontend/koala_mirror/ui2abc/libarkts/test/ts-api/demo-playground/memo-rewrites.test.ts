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
