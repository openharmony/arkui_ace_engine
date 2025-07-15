/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/compat"

export type KoalaCallsiteKey = int32

export class KoalaCallsiteKeys {
    static readonly empty: KoalaCallsiteKey = 0

    static combine(key1: KoalaCallsiteKey, key2: KoalaCallsiteKey): KoalaCallsiteKey {
        return key1 + key2
    }

    static asString(key: KoalaCallsiteKey): string {
        return new Number(key).toString(16)
    }
}

/**
 * Utility method to compute a positional id from the string representation.
 * @param str - a string representation of a callsite position
 * @returns a positional id for the given string
 */
export function toKoalaCallsiteKey(str: string): KoalaCallsiteKey {
    let key = KoalaCallsiteKeys.empty
    for (let i = 0; i < str.length; i++) {
        key = (key << 3) | (key >> 29) ^ str.charCodeAt(i)
    }
    // DEBUG: console.log(`KEY: ${KoalaCallsiteKeys.asString(key)} from "${str}"`)
    return key
}
