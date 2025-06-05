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

export class ReusablePool implements Disposable {
    private cache: Disposable[];
    disposed: boolean = false;

    constructor() {
        this.cache = [];
    }

    /**
     * Returns and removes the first available item from the pool
     */
    get(): Disposable | undefined {
        if (this.disposed) return undefined;
        return this.cache.shift();
    }

    /**
     * Adds an item to the pool
     */
    put(value: Disposable): void {
        if (this.disposed) return;
        this.cache.push(value);
    }

    dispose(): void {
        if (this.disposed) return;
        this.disposed = true;
        for (const value of this.cache) {
            value.dispose();
        }
        this.cache = [];
    }
}
