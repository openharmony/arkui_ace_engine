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

suite.skip(util.basename(__filename), () => {
    test("imported-function-call", function() {
        const sample_in =
        `
        import { X } from "./variable"
 
        export function main() {
            console.log(X)
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        util.cleanGenerated()
        util.fileToAbc(`./input/variable.sts`, true)
        util.contextToAbc()
        util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })

    test("rewrite-imported-function-call", function() {
        const sample_in =
        `
        import { X } from "./variable"
 
        export function main() {
            console.log(Y)
        }
        `

        let sourceFile = ts.factory.createSourceFile(sample_in)
        util.assert(ts.isSourceFile(sourceFile))

        util.cleanGenerated()
        util.fileToAbc(`./input/variable.sts`, true)
        util.contextToAbc()
        util.runAbc(`./generated/main.abc`, ['./generated/variable.abc'])
    })
})
