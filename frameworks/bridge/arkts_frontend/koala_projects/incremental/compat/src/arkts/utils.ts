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

export function errorAsString(error: Any): string {
    if (error instanceof Error) {
        const stack = error.stack
        return stack ? error.toString() + '\n' + stack : error.toString()
    }
    return JSON.stringify(error)
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

export function launchJob(task: () => void): Promise<Any> {
    return taskpool.execute(task)
}

export type WorkerLocalValue<T> = WorkerLocal<T>
