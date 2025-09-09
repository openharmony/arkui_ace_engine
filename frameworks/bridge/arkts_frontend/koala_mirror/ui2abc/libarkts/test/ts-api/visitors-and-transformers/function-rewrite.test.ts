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
//         // Improve:
//         util.nativeModule._VarBinderInitTopScope(global.context)
//         util.nativeModule._VarBinderIdentifierAnalysis(global.context)
//         ts.proceedToState(ts.ContextState.ES2PANDA_STATE_BIN_GENERATED)
//     })
// })
