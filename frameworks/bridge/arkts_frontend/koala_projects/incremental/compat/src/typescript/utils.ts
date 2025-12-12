/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { AtomicRef } from './atomic'

export function errorAsString(error: unknown): string {
    if (error instanceof Error) {
        return error.stack ?? error.toString()
    }
    return JSON.stringify(error)
}

export function unsafeCast<T>(value: unknown): T {
    return value as T
}

export function scheduleCoroutine(): void {}

export function memoryStats(): string {
    return `none`
}

export function launchJob(job: () => void): Promise<void> {
    return new Promise<void>(resolve => setTimeout(() => {
            resolve()
            job()
        }, 0)
    )
}

export class WorkerLocalValue<T> {
    private ref?: AtomicRef<T>

    /**
     * @param init - a factory function to provide initial worker-local value if needed
     */
    constructor(private init?: () => T) {}

    /**
     * @returns the worker-local value for current worker
     * @throws `Error` when value not initialized and no `init` function provided
     */
    get(): T {
        const ref = this.ref
        if (ref) return ref.value
        const init = this.init
        if (!init) { throw new Error('WorkerLocalValue not initialized: call set() first or provide init() function.') }
        const value = init()
        this.ref = new AtomicRef<T>(value)
        return value
    }

    /**
     * Updates the worker-local value for current worker.
     * @param value - new value to store
     */
    set(value: T) {
        const ref = this.ref
        if (ref) {
            ref.value = value
        } else {
            this.ref = new AtomicRef<T>(value)
        }
    }

    /**
     * Deletes the worker-local value for current worker.
     */
    delete(): void {
        this.ref = undefined
    }
}
