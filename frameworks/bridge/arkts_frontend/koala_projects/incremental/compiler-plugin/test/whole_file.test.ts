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
import * as fs from "fs"

function assertUnmemoizedEqualGolden(filename: string) {
    const unmemoized = fs.readFileSync(`./test/unmemoized/${filename}`, "utf8");
    const golden = fs.readFileSync(`./test/golden/${filename}`, "utf8");
    return assert.equal(golden, unmemoized)
}

suite("Memo stable", () => {
    test("Memo stable rewrites: this management",
        () => assertUnmemoizedEqualGolden("examples/memo_stable.ts")
    )
})

suite("Union memo types", () => {
    test("Union type parameters",
        () => assertUnmemoizedEqualGolden("examples/union_type_parameters.ts")
    )
})

suite("Local export as", () => {
    test("Local export as",
        () => assertUnmemoizedEqualGolden("examples/localexported.ts")
    )
})
