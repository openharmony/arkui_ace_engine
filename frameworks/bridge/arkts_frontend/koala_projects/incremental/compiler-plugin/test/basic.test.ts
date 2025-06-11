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
import { qox, til, zex as wax, accessId, juv, Zan, ryq, bae } from "./module.test"
import { exported } from "./exports.test"
import defexport  from "./default-export.test"
import { E } from "./export-as.test"
import { __id, Context } from "./context.test"
import { log, getLogFiltered, resetLog, cleanDumpDirectory, checkDump } from "./util.test"

const someId = "xxx"

suite("Function and callsite transformations", () => {
    cleanDumpDirectory()

    test("Can find the declaration through named import", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            wax(() => {
                log("wax lambda")
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm zex
wax lambda
`
        )
    })
    test("A user argument is passed correctly", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            til("apple", () => {
                log("til lambda")
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm til, I have an apple
til lambda
`
        )
    })

    test("Access to __id() intrinsic works", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            accessId("orange", () => {
                log("accessId lambda, I have an id on the call site: " + __id())
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm accessId, I have an orange
accessId lambda, I have an id on the call site: xxx5___key_id_DIRNAME/basic.test.ts7___key_id_DIRNAME/module.test.ts
`
        )
    })

    test("Events absence is allowed", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            qox("apple", () => {
                log("qox lambda")
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm qox, I have an apple
qox lambda
`
        )
    })

    test("Compute transformation on a global", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            juv("plum", () => {
                log("juv lambda")
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm juv, I have a plum
`
        )
    })

    test("Member call site compute transformation", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            const zan = new Zan()
            zan.rek("avocado")
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm rek the member. I have an avocado
`
        )
    })

    test("Member call site component transformation", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            const zan = new Zan()
            zan.cep("onion", () => {
                log("cep lambda")
            })
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`I'm cep the member. I have an onion, false
cep lambda
`
        )
    })

    test("UI arrows work when passed as UI parameters", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            ryq("jumps", "thoughtfully")
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`funny ui cow thoughtfully jumps
happy non-ui goat thoughtfully jumps
`
        )
    })

    test("UI function expressions work when passed as UI parameters", () => {
        resetLog()

        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            bae("dances", "brainlessly")
        }
        start(new Context(), someId)

        assert.equal(
            getLogFiltered(),
`funny ui pig brainlessly dances
happy non-ui horse brainlessly dances
`
        )
    })

    test("The real declaration is discoverable through explicit export", () => {
        resetLog()
        let x: number = 0
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            x = exported(17)
        }
        start(new Context(), someId)
        assert.equal(x, 18)
    })

    test("The real declaration is discoverable through export as", () => {
        resetLog()
        let x: number = 0
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            x = E(17)
        }
        start(new Context(), someId)
        assert.equal(x, 18)

    })

    test("Default export can be found", () => {
        resetLog()
        let x: number = 0
        /** @memo:entry */
        function start(__memo_context: Context, __memo_id: any) {
            x = defexport()
        }
        start(new Context(), someId)
        assert.equal(x, 29)
    })

    for (let name of ["accessId", "cep", "juv", "qox", "rek", "til", "zex", "kla", "ryq", "bae"]) {
        checkDump(name, "module")
    }

    for (let name of ["exported"]) {
        checkDump(name, "exported")
    }

    for (let name of ["intrinsicFunctionUsingThis"]) {
        checkDump(name, "receiver")
    }

    for (let name of ["functionUsingThis"]) {
        checkDump(name, "receiver")
    }

    for (let name of ["entry1", "entry2", "entry3", "entry4"]) {
        checkDump(name, "property")
    }
})
