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

export function errorAsString(error: Error): string {
    const stack = error.stack
    return stack
        ? error.toString() + '\n' + stack
        : error.toString()
}

export function unsafeCast<T>(value: Object): T {
    return value as T
}

export function scheduleCoroutine(): void {
    Coroutine.Schedule()
}

export function memoryStats(): string {
    return `used ${GC.getUsedHeapSize()} free ${GC.getFreeHeapSize()}`
}

export function launchJob(job: () => void): Promise<void> {
    throw new Error("unsupported yet: return launch job()")
}

export class CoroutineLocalValue<T> {
    private map = new containers.ConcurrentHashMap<int, T>
    get(): T | undefined {
        return this.map.get(CoroutineExtras.getWorkerId())
    }
    set(value: T | undefined) {
        if (value) {
            this.map.set(CoroutineExtras.getWorkerId(), value)
        } else {
            this.map.delete(CoroutineExtras.getWorkerId())
        }
    }
}
