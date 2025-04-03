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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'

export function testsuite() {
    describe('Foo Test', function () {
        beforeAll(function () {
            console.log("Foo: beforeAll")
        })

        beforeEach(function () {
            console.log("Foo: beforeEach")
        })

        afterEach(function () {
            console.log("Foo: afterEach")
        })

        afterAll(function () {
            console.log("Foo: afterAll")
        })

        it('assertContain',0, function () {
            const a = 'abc'
            const b = 'b'
            expect(a).assertContain(b)
        })
    })
}
