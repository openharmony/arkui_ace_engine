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

import { int32 } from "@koalaui/common";
import { Disposable, scheduleCallback, callScheduledCallbacks } from "@koalaui/runtime";

const DEFAULT_IDLE_TRIM_KEEP_SIZE: int32 = 8;
const DEFAULT_IDLE_TRIM_DELAY_MS: int32 = 300000;

export class ReusablePool implements Disposable {
    private _maxSize: int32 = Number.POSITIVE_INFINITY.toInt()
    private _cache: Disposable[] = []
    private _disposed: boolean = false;
    private _idleTrimEnabled: boolean = false;
    private _lastOperateTime: number = 0;
    private _idleTrimTaskPending: boolean = false;

    get disposed(): boolean {
        return this._disposed
    }

    get size(): int32 {
        return this._cache.length.toInt()
    }

    /**
     * Returns and removes the first available item from the pool
     */
    get(): Disposable | undefined {
        if (this.disposed) return undefined;
        const value = this._cache.shift();
        this.touch();
        return value;
        
    }

    getLastNode(): Disposable | undefined {
        if (this.disposed) {
            return undefined;
        }
        const value = this._cache.pop();
        this.touch();
        return value;
    }

    /**
     * Adds an item to the pool
     */
    put(value: Disposable): void {
        if (this.disposed || this._cache.length >= this._maxSize) return;
        this._cache.push(value);
        this.touch();
    }

    dispose(): void {
        if (this.disposed) return;
        this._disposed = true;
        for (const value of this._cache) {
            value.dispose();
        }
        this._cache = [];
        callScheduledCallbacks();
    }

    setMaxSize(value: int32) {
        this._maxSize = value
        if (this._cache.length > this._maxSize) {
            const removed = this._cache.splice(this._maxSize.toInt());
            scheduleCallback(() => {
                for (const value of removed)
                    value.dispose();
            })
        }
    }

    enableIdleTrim(): void {
        this._idleTrimEnabled = true;
        this.touch();
    }

    private touch(): void {
        if (!this._idleTrimEnabled || this.disposed) {
            return;
        }
        this._lastOperateTime = Date.now();
        if (this._idleTrimTaskPending) {
            return;
        }
        this._idleTrimTaskPending = true;
        this.scheduleIdleTrim(DEFAULT_IDLE_TRIM_DELAY_MS);
    }

    private scheduleIdleTrim(delayMs: int32): void {
        setTimeout(() => {
            this.handleIdleTrim();
        }, delayMs);
    }

    private handleIdleTrim(): void {
        if (this.disposed) {
            this._idleTrimTaskPending = false;
            return;
        }
        const idleTime = Date.now() - this._lastOperateTime;
        if (idleTime < DEFAULT_IDLE_TRIM_DELAY_MS) {
            this.scheduleIdleTrim((DEFAULT_IDLE_TRIM_DELAY_MS - idleTime).toInt());
            return;
        }
        this._idleTrimTaskPending = false;
        if (this._cache.length > DEFAULT_IDLE_TRIM_KEEP_SIZE) {
            const removed = this._cache.splice(DEFAULT_IDLE_TRIM_KEEP_SIZE.toInt());
            for (const value of removed) {
                value.dispose();
            }
            callScheduledCallbacks();
        }
    }
}