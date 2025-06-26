/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import { float64, int32, float32, int64 } from "./types"

export function float32To64(value: float32): float64 {
    return value
}

export function float64To32(value: float64): float32 {
    return value
}

export function asFloat64(value: string): float64 {
    return Number(value)
}

export function asString(value: float64 | undefined): string | undefined {
    return value?.toString()
}

export function float32FromBits(value: int32): float32 {
    return value
}

export function int32BitsFromFloat(value: float32): int32 {
    return value
}

export function float64ToInt(value: float64): int32 {
    return value
}

export function float64ToLong(value: float64): int64 {
    return value
}

export function charToInt(value: string): int32 {
    return parseInt(value)
}

