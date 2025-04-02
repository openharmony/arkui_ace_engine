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

import { Context } from "./context.test"
import { resetLog } from "./util.test"

const someId = "xxx"

/** @memo */
function foo() {}

interface Y {
    /** @memo */
    prop: () => void
}

class X {
    /** @memo */
    prop: () => void = foo
}

class Z implements Y {
    /** @memo */
    prop: () => void = foo
}

class W extends X {
}

/** @memo */
function entry1() {
    const x = new X()
    x.prop()
}

/** @memo */
function entry2() {
    const z = new Z()
    z.prop()
}

/** @memo */
function entry3() {
    const w = new W()
    w.prop()
}

/** @memo */
function entry4() {
    const y: Y = { prop: foo }
    y.prop()
}

suite("Memo functional type property", () => {
    test("Memo functional type property is expanded", () => {
        resetLog()
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            entry1()
        }
        start(new Context(), someId)
    })
    test("Memo override functional type property is expanded", () => {
        resetLog()
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            entry2()
        }
        start(new Context(), someId)
    })
    test("Memo inherit functional type property is expanded", () => {
        resetLog()
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            entry3()
        }
        start(new Context(), someId)
    })
    test("Memo functional type property in interface is expanded", () => {
        resetLog()
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            entry4()
        }
        start(new Context(), someId)
    })
})

