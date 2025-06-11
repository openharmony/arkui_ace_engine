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

import { int32 } from "@koalaui/common"

export enum Access {
    READ = 1, // 1 << 0,
    WRITE = 2, // 1 << 1,
    READWRITE = 3, // READ | WRITE
}
export function isRead(access: Access) {
    return access & Access.READ
}
export function isWrite(access: Access) {
    return access & Access.WRITE
}

export type Exec<P, R> = (pointer: P) => R
export type ExecWithLength<P, R> = (pointer: P, length: int32) => R

export type TypedArray =
    Uint8Array
    | Int8Array
    | Uint16Array
    | Int16Array
    | Uint32Array
    | Int32Array
    | Float32Array
    | Float64Array

export type PtrArray = Uint32Array | BigUint64Array