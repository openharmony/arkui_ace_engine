/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

export function assertEquals<E, A>(name: String, expected: E, actual: A) {
    if (expected != actual) {
        console.log(`TEST ${name} FAIL:\n  EXPECTED "${expected}"\n  ACTUAL   "${actual}"`)
    } else {
        console.log(`TEST ${name} PASS`)
    }
}

export function assertThrows(name: String, fn: () => void) {
    let caught = false
    try {
        fn()
    } catch (e) {
        caught = true
    }
    if (!caught) {
        console.log(`TEST ${name} FAIL:\n  No exception thrown`)
    } else {
        console.log(`TEST ${name} PASS`)
    }
}
