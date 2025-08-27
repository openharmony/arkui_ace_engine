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
import { int32, int64, float32 } from "@koalaui/common"

export type KStringPtr = string
export type KStringArrayPtr = Uint8Array
export type KInt32ArrayPtr =  Int32Array
export type KFloat32ArrayPtr = Float32Array
export type KUint8ArrayPtr = Uint8Array
export type KInt = int32
export type KUInt = int32
export type KLong = int64
export type KFloat = float32
export type KBoolean = int32
export type KPointer = bigint
export type pointer = KPointer
export type KNativePointer = KPointer
