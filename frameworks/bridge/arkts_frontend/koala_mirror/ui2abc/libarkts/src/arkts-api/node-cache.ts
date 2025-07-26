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

import { KNativePointer } from "@koalaui/interop"
import { AstNode } from "./peers/AstNode"

export class NodeCache {
    private static cache = new Map<KNativePointer, AstNode>()

    static cached<T extends AstNode>(pointer: KNativePointer, factory: (pointer: KNativePointer) => AstNode): T {
        const cached = NodeCache.cache.get(pointer)
        if (cached !== undefined) {
            return cached as T
        }
        const node = factory(pointer)
        NodeCache.addToCache(pointer, node)
        return node as T
    }

    public static addToCache(pointer: KNativePointer, node: AstNode) {
        NodeCache.cache.set(pointer, node)
    }

    public static clear(): void {
        NodeCache.cache.clear()
    }
}
