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

import { Disposable } from "@koalaui/runtime";
import { KoalaCallsiteKey } from "@koalaui/common"

export class ReusablePool implements Disposable {
    private cache: Map<KoalaCallsiteKey, Disposable>;

    constructor() {
        this.cache = new Map<KoalaCallsiteKey, Disposable>();
    }
    disposed: boolean = false

    /**
     * prioritize reusing the same scope. If not found, use the earliest inserted scope
     */
    get(key: KoalaCallsiteKey): Disposable | undefined {
        if (this.disposed) return undefined;
        if (!this.cache.has(key)) {
            const leastUsedKey = this.cache.keys().next().value;
            if (!leastUsedKey) return undefined
            const leastUsedValue = this.cache.get(leastUsedKey!);
            this.cache.delete(leastUsedKey!);
            return leastUsedValue;
        }
        const value = this.cache.get(key)!;
        this.cache.delete(key);
        return value;
    }

    put(key: KoalaCallsiteKey, value: Disposable): void {
        if (this.disposed) return
        if (this.cache.has(key)) {
            throw Error("the same scope is recycled twice")
        }
        this.cache.set(key, value);
    }

    dispose(): void {
        if (this.disposed) return
        this.disposed = true
        for (const value of this.cache.values()) {
            value.dispose();
        }
        this.cache.clear();
    }
}