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

import {
    withFloat32Array,
    withFloat64Array,
    withInt16Array,
    withInt32Array,
    withInt8Array,
    withUint16Array,
    withUint32Array,
    withUint8Array,
    wasmHeap as wasmHeapArrayBuffer
} from "#common/wrappers/arrays"

export { registerCallback, setCallbackRegistry } from "#common/wrappers/Callback"

export { Access, Exec } from "./arrays"
export { Finalizable, NativeThunk } from "./Finalizable"
export { nullable } from "./nullable"
export { getPtr, isNullPtr, nullptr, ptrEqual, Wrapper, ptrToBits, bitsToPtr } from "./Wrapper"

export {
    decodeToString,
    encodeToData,
    withString,
    withStringArray,
    withPtrArray,
    fromPtrArray,
    toPtrArray
} from "#common/wrappers/arrays"

export const withFloatArray = withFloat32Array
export const withByteArray = withUint8Array
export const withIntArray = withInt32Array

export const wasmHeap = wasmHeapArrayBuffer

export {
    withFloat32Array,
    withFloat64Array,
    withInt8Array,
    withInt16Array,
    withInt32Array,
    withUint8Array,
    withUint16Array,
    withUint32Array,
}

export * from "./Platform"
export * from "./InteropTypes"

export * from "./InteropOps"
export * from "./NativeString"
export * from "./buffer"
export * from "../arkts/ResourceManager"
export * from "./NativeBuffer"
export { InteropNativeModule, loadInteropNativeModule } from "./InteropNativeModule"
export { SerializerBase, RuntimeType, Tags, runtimeType, CallbackResource, unsafeCast, isInstanceOf, toPeerPtr } from "./SerializerBase"
export { DeserializerBase } from "./DeserializerBase"
export { loadNativeModuleLibrary, loadNativeLibrary, registerNativeModuleLibraryName } from "./loadLibraries"
export * from "./MaterializedBase"
