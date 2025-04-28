/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArktsObject } from "./peers/ArktsObject"
import { KNativePointer } from "@koalaui/interop"

export class NodeCache {
    private static cache = new Map<KNativePointer, ArktsObject>()

    static cached<T extends ArktsObject>(pointer: KNativePointer, factory: (pointer: KNativePointer) => ArktsObject): T {
        const cached = NodeCache.cache.get(pointer)
        if (cached !== undefined) {
            return cached as T
        }
        const node = factory(pointer)
        NodeCache.cache.set(pointer, node)
        return node as T
    }

    public static clear(): void {
        NodeCache.cache.clear()
    }
}
