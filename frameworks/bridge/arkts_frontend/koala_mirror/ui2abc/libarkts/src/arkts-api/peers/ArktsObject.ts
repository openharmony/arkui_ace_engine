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

import { KNativePointer } from "@koalaui/interop"

export abstract class ArktsObject {
    protected constructor(peer: KNativePointer) {
        this.peer = peer
    }

    peer: KNativePointer

    public onUpdate(node: ArktsObject) {}
}

export function isSameNativeObject<T extends ArktsObject | number | string | boolean | undefined>(
    first: T | readonly T[],
    second: T | readonly T[]
): boolean {
    if (Array.isArray(first) && Array.isArray(second)) {
        if (first.length !== second.length) {
            return false
        }
        for (let i = 0; i < first.length; i++) {
            if (!isSameNativeObject(first[i], second[i])) {
                return false
            }
        }
        return true
    }
    if (first instanceof ArktsObject && second instanceof ArktsObject) {
        return first?.peer === second?.peer
    }
    return first === second
}
