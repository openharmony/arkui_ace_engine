/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


/**
 * Computes a hash code from the string {@link value}.
 */
export function hashCodeFromString(value: string): int32 {
    let hash = 5381
    for(let i = 0; i < value.length; i++) {
        hash = (hash * 33) ^ value.charCodeAt(i)
        hash |= 0
    }
    return hash
}
