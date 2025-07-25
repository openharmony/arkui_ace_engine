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

export function unsafeCast<T>(value: unknown): T {
    return value as unknown as T
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