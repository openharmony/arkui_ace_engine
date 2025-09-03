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

import { Disposable, scheduleCallback } from "@koalaui/runtime";

export class ReusablePool implements Disposable {
    private _maxSize: number = Number.POSITIVE_INFINITY
    private _cache: Disposable[] = []
    private _disposed: boolean = false;

    get disposed(): boolean {
        return this._disposed
    }

    /**
     * Returns and removes the first available item from the pool
     */
    get(): Disposable | undefined {
        if (this.disposed) return undefined;
        return this._cache.shift();
    }

    /**
     * Adds an item to the pool
     */
    put(value: Disposable): void {
        if (this.disposed || this._cache.length >= this._maxSize) return;
        this._cache.push(value);
    }

    dispose(): void {
        if (this.disposed) return;
        this._disposed = true;
        for (const value of this._cache) {
            value.dispose();
        }
        this._cache = [];
    }

    setMaxSize(value: number) {
        this._maxSize = value
        if (this._cache.length > this._maxSize) {
            const removed = this._cache.splice(this._maxSize);
            scheduleCallback(() => {
                for (const value of removed)
                    value.dispose();
            })
        }
    }
}
