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

export interface Thunk {
    clean(): void
}

interface FinalizationRegistry {
    register(target: object, value: any, token?: object): void;
    unregister(token: object): void;
}

interface FinalizationRegistryConstructor {
    readonly prototype: FinalizationRegistry;
    new(callback: (value: any) => void): FinalizationRegistry;
}

declare const FinalizationRegistry: FinalizationRegistryConstructor

const registry = new FinalizationRegistry((thunk: Thunk) => {
    thunk.clean()
})

export function finalizerRegister(target: object, thunk: object) {
    registry.register(target, thunk)
}

export function finalizerUnregister(target: object) {
    registry.unregister(target)
}
