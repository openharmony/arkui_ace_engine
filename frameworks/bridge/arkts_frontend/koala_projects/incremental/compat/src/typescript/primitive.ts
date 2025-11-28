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

import { float32, float64, int32, int64 } from './types';

export function float32to64(value: float32): float64 {
    return value; // toDouble()
}
export function float32toInt32(value: float32): int32 {
    return value | 0; // toInt()
}
export function float32toInt64(value: float32): int64 {
    return Math.trunc(value); // toLong()
}

export function float64to32(value: float64): float32 {
    return value; // toFloat()
}
export function float64toInt32(value: float64): int32 {
    return value | 0; // toInt()
}
export function float64toInt64(value: float64): int64 {
    return Math.trunc(value); // toLong()
}

export function int32toFloat32(value: int32): float32 {
    return value; // toFloat()
}
export function int32toFloat64(value: int32): float64 {
    return value; // toDouble()
}
export function int32to64(value: int32): int64 {
    return Math.trunc(value); // toLong()
}

export function int64toFloat32(value: int64): float32 {
    return value; // toFloat()
}
export function int64toFloat64(value: int64): float64 {
    return value; // toDouble()
}
export function int64to32(value: int64): int32 {
    return value | 0; // toInt()
}

export function asFloat64(value: string): float64 {
    return Number(value);
}
