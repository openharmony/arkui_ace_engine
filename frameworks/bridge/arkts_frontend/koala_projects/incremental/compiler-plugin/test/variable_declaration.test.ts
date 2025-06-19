/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { Assert as assert, suite, test } from "@koalaui/harness"
import { Context } from "./context.test"
import { checkDump } from "./util.test"

const someId = "xxx"

suite("Variable declaration", () => {

    test("Variable declaration list @memo", () => {
        /** @memo */
        function f() {
            return
        }

        /** @memo */
        function ui() {
            /** @memo */
            let x1 = f, y1 = f

            x1()
            y1()

            const
                /** @memo */
                x2 = f,
                y2 = f

            x2()
            y2()
        }
    })

    for (let name of ["ui"]) {
        checkDump(name, "variable_declaration")
    }
})
