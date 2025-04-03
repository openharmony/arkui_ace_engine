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

const someId = "xxx"

interface Holder {
    /** @memo */
    func: (x: number) => string
}

function foo():
/** @memo */
(x: number) => string
{
    return (
        /** @memo */
        (x: number): string => {
            return x.toString()
        }
    )
}

/** @memo */
function wrapper(): string {

    const
        /** @memo */
        holder: ((x: number) => string) = foo()

    return holder(17)
}

function changer(
    /** @memo */
    exec: (value: number) => string
):
    /** @memo */
    (x: number) => string
{
    return (
        /** @memo */
        (x: number):string => exec(x + 100)
    )
}

/** @memo */
function runner(
    /** @memo */
    exec: (value: number) => string
): string {
    return exec(19)
}

suite("Returning memo functions", () => {
    test("Non-memo returns a memo", () => {
        let result: any
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            result = wrapper()
        }
        start(new Context(), someId)
        assert.equal(result, "17")
    })

    test("Memo lambda id", () => {
        let result: any
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            result = runner(changer(foo()))
        }
        start(new Context(), someId)
        assert.equal(result, "119")
    })
})

