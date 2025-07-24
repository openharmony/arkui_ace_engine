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
import { assertGeneratedEqualsGolden, testFolder } from "./utils"

suite("Basic rewrites of ArkUI syntactic features", () => {
    test("Basic rewrites", () => assertGeneratedEqualsGolden("Rewrite.ts"))
    test("LocalStorageLinkExample rewrites", () => assertGeneratedEqualsGolden("Rewrite2.ts"))
    test("LocalStoragePropExample rewrites", () => assertGeneratedEqualsGolden("Rewrite3.ts"))
    test("Rewrite of property-to-property initialization", () => assertGeneratedEqualsGolden("PropertyDeps.ts"))
    test("Ets component call rewrites", () => {
        assertGeneratedEqualsGolden("ets-component-call/ets-call.ts")
        assertGeneratedEqualsGolden("ets-component-call/user-function-declaration.ts")
    })
    test("Ets component call rewrites", () => assertGeneratedEqualsGolden("state-class-property/class.ts"))
    test("Ets builder lambda rewrites", () => assertGeneratedEqualsGolden("builder-lambda/builder-lambda.ts"))
    test(
        "UIAbility import rewrites to ArkoalaAbility",
        () => assertGeneratedEqualsGolden("arkoala-ability/EntryAbility.ts")
    )
    test("UIAbility import is preserved if in ArkoalaAbility declaration file",
        () => assertGeneratedEqualsGolden("arkoala-ability/ArkoalaAbility.ts")
    )
    test("Rewrite mixed default and named imports",
        () => assertGeneratedEqualsGolden("arkoala-ability/default-and-named.ts")
    )
    test("Trailing block user structs", () => assertGeneratedEqualsGolden("trailing-block.ts"))
})

testFolder("dollar-dollar")

suite("Arkts rewrites", () => {
    test("Rewrite.ets", () => assertGeneratedEqualsGolden("arkts/Rewrite.ts"))
    test("Rewrite2.ets", () => assertGeneratedEqualsGolden("arkts/Rewrite2.ts"))
    test("Rewrite3.ets", () => assertGeneratedEqualsGolden("arkts/Rewrite3.ts"))
})
