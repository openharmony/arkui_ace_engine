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

import { finalizerRegister as finalizerRegisterCompat, finalizerUnregister as finalizerUnregisterCompat, Thunk } from "@koalaui/compat"

export { Thunk } from "@koalaui/compat"

export function finalizerRegister(target: object, thunk: Thunk) {
    finalizerRegisterCompat(target, thunk)
}

export function finalizerRegisterWithCleaner(target: object, cleaner: () => void) {
    finalizerRegisterCompat(target, new CleanerThunk(cleaner))
}

export function finalizerUnregister(target: object) {
    finalizerUnregisterCompat(target)
}

class CleanerThunk implements Thunk {
    private cleaner:  () => void
    constructor(cleaner: () => void) {
        this.cleaner = cleaner
    }
    clean() {
        this.cleaner()
    }
}
