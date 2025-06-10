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

import { suite, test } from "@koalaui/harness"
// import { Context } from "./context.test"
import { checkDump } from "./util.test"

// const someId: string = "xxx"

suite("Parenthesised call expressions", () => {
    test("Parenthesised memo functions", () => {
        /** @memo */
        function f(): void {
            return
        }

        /** @memo */
        function g(x: number, y: number): number {
            return x + y
        }

        /** @memo */
        function expr_memo(): void {
            f();
            (f)();
            f();
            (((((f)))))();

            g(1, 2);
            (g)(3, 4);
            g(5, 6);
            (((((g)))))(7, 8);
        }
    })

    test("Parenthesised non memo functions", () => {
        function f(): void {
            return
        }

        function g(x: number, y: number): number {
            return x + y
        }

        /** @memo */
        function expr_non_memo(): void {
            f();
            (f)();
            f();
            (((((f)))))();

            g(1, 2);
            (g)(3, 4);
            g(5, 6);
            (((((g)))))(7, 8);
        }
    })


    for (let name of ["expr_memo", "expr_non_memo"]) {
        checkDump(name, "parenthesised-call")
    }
})
