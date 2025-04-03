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

suite("Wrapping literals in compute", () => {

    test("Object literal is wrapped in compute", () => {
        /** @memo */
        function foo(a: any): any {
            return a
        }
        let result: any
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            result = foo({x: 17, y: 19})
        }
        start(new Context(), someId)
        assert.equal(result.x, 17)
        assert.equal(result.y, 19)
    })

    test("Arrow function is wrapped in compute", () => {
        let counter = 0
        /** @memo */
        function arrowFunctionReceiver(a: any) {
            counter++
        }
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            arrowFunctionReceiver(() => {})
        }
        start(new Context(), someId)
        assert.equal(counter, 1)
    })


    for (let name of ["foo"]) {
        checkDump(name, "wrap_object_literal")
    }
})
