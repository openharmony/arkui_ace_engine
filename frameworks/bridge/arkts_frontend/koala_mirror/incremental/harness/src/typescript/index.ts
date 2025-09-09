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

import { doTest, TestKind } from "../arkts/shared"
export { Assert, Assert as assert } from "./assert"
export { TestFilter, setTestFilter } from "../arkts/shared"

export function test(name: string, content?: () => void) {
    doTest(TestKind.PASS, name, `test: "${name}"`, content)
}

export namespace test {
    export function skip(name: string, content?: () => void) {
        doTest(TestKind.SKIP, name, `test: "${name}"`, content)
    }

    export function expectFailure(reason: string, name: string, content?: () => void) {
        doTest(TestKind.FAIL, name, `test: "${name}"; reason: "${reason}"`, content)
    }

    export function conditional(condition: boolean, name: string, content?: () => void) {
        if (condition) {
            test(name, content)
        } else {
            test.skip(name, content)
        }
    }

    export function expect(expectSuccess: boolean, name: string, content?: () => void) {
        if (expectSuccess) {
            test(name, content)
        } else {
            test.expectFailure("Description of the problem", name, content)
        }
    }
}

export function suite(name: string, content?: () => void) {
    doTest(TestKind.PASS, name, `suite: "${name}"`, content, true)
}

export namespace suite {
    export function skip(name: string, content?: () => void) {
        doTest(TestKind.SKIP, name, `suite: "${name}"`, content)
    }
}
