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
