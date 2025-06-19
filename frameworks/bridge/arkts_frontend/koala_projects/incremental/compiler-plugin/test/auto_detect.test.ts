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
import { log, getLogFiltered, resetLog } from "./util.test"

const someId = "xxx"

suite("Deduce annotation by assignment destination", () => {

    test("Direct initializer of annotated variable", () => {
        resetLog()
        let q = 11
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            let
            /** @memo */
            p: ((k: number)=>number) =
                (n:number):number => n+1

            q = p(17)
        }
        start(new Context(), someId)
        assert.equal(q, 18)
    })

    test("Direct initializer of annotated variable v.2", () => {
        resetLog()
        let q = 11
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            let
            /** @memo */
            p: ((k: number, x:()=>void)=>number) =
                (n, y):number => n+1

            q = p(17, ()=>{})
        }
        start(new Context(), someId)
        assert.equal(q, 18)
    })

    test("Direct argument of annotated parameter", () => {
        resetLog()
        function start(__memo_context: Context, __memo_id: any) {
            /** @memo:entry */
            function foo(
                a: number,
                /** @memo */
                p: (x: number) => void
            ) {
                p(a)
            }

            foo(17, (x: number) => {
                log("got: " + x)
            })
        }
        start(new Context(), someId)
        assert.equal(getLogFiltered(), "got: 17\n")
    })
})
