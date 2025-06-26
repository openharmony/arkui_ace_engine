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

function checkKind(actual: string, expected: string) {
    assert.equal(actual, expected)
}

suite("CheckTestKind", () => {
    test("passed", () => { checkKind("passed", "passed") })
    test("failed", () => { checkKind("failed", "fail failed") })

    test.expectFailure("because", "expected failed", () => { checkKind("expected failed", "expected failed - fail!") })
    test.expectFailure("because", "unexpectedly passed", () => { checkKind("unexpectedly passed", "unexpectedly passed") })

    test.skip("skipped", () => { checkKind("skipped", "skipped") })
    suite.skip("skip several tests", () => {
        test("skip1", () => {})
        test("skip2", () => {})
        test("skip3", () => {})
    })
})
