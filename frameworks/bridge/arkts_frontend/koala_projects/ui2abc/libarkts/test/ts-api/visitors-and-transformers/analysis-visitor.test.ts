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
