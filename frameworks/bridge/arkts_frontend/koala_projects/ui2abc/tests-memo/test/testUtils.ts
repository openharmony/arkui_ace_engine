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

import { int32, KoalaCallsiteKey, UniqueId, asArray } from "@koalaui/common"
import { Assert } from "@koalaui/harness"
import { GlobalStateManager, MutableState } from "@koalaui/runtime"


export function assertResultArray<T>(actual: Array<T>, ...expected: T[]) {
    Assert.deepEqual(actual, asArray(expected))
}

export class GlobalStateHolder {
    static globalState: MutableState<number> = GlobalStateManager.instance.mutableState<number>(0, true)
}

export enum TransformPlugin {
    MEMO_PLUGIN,
    COMPILER_PLUGIN
}

export enum Language {
    TS,
    ArkTS
}

let TRANSFORM_PLUGIN: TransformPlugin = TransformPlugin.COMPILER_PLUGIN 

export function setTransformPlugin(plugin: TransformPlugin) {
    TRANSFORM_PLUGIN = plugin
}

export function isMemoPlugin(): boolean {
    return TRANSFORM_PLUGIN == TransformPlugin.MEMO_PLUGIN
}

export function isCompilerPlugin(): boolean {
    return TRANSFORM_PLUGIN == TransformPlugin.COMPILER_PLUGIN
}

let TEST_LANGUAGE: Language = Language.TS

export function setLanguage(language: Language) {
    TEST_LANGUAGE = language
}

export function isArktsTest() {
    return TEST_LANGUAGE == Language.ArkTS
}

export function isTSTest() {
    return TEST_LANGUAGE == Language.TS
}

export function key(name: string): KoalaCallsiteKey {
    if (isArktsTest()) {
        let key: KoalaCallsiteKey = 0
        for (let i = 0; i < name.length; i++) {
            key = (key << 3) | (key >> 29) ^ (name[i] as int32)
        }
        return key
    } else {
        return parseInt(new UniqueId().addString(name).compute().slice(0, 10), 16) as KoalaCallsiteKey
    }
}