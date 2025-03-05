/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { Callback_RangeUpdate } from "./ArkArkuiCustomInterfaces"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, isResource, isInstanceOf, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class LazyForEachOpsInternal {
    public static fromPtr(ptr: KPointer): LazyForEachOps {
        const obj : LazyForEachOps = new LazyForEachOps()
        obj.peer = new Finalizable(ptr, LazyForEachOps.getFinalizer())
        return obj
    }
}
export class LazyForEachOps implements MaterializedBase {
    peer?: Finalizable | undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_lazyforeachops(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LazyForEachOps_ctor()
        return retval
    }
     constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = LazyForEachOps.ctor_lazyforeachops()
        this.peer = new Finalizable(ctorPtr, LazyForEachOps.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LazyForEachOps_getFinalizer()
    }
    public static NeedMoreElements(node: KPointer, mark: KPointer, direction: int32): KPointer {
        const node_casted = node as (KPointer)
        const mark_casted = mark as (KPointer)
        const direction_casted = direction as (int32)
        return LazyForEachOps.NeedMoreElements_serialize(node_casted, mark_casted, direction_casted)
    }
    public static OnRangeUpdate(node: KPointer, totalCount: int32, updater: Callback_RangeUpdate): void {
        const node_casted = node as (KPointer)
        const totalCount_casted = totalCount as (int32)
        const updater_casted = updater as (Callback_RangeUpdate)
        LazyForEachOps.OnRangeUpdate_serialize(node_casted, totalCount_casted, updater_casted)
        return
    }
    public static SetCurrentIndex(node: KPointer, index: int32): void {
        const node_casted = node as (KPointer)
        const index_casted = index as (int32)
        LazyForEachOps.SetCurrentIndex_serialize(node_casted, index_casted)
        return
    }
    public static Prepare(node: KPointer, itemCount: int32, offset: int32): void {
        const node_casted = node as (KPointer)
        const itemCount_casted = itemCount as (int32)
        const offset_casted = offset as (int32)
        LazyForEachOps.Prepare_serialize(node_casted, itemCount_casted, offset_casted)
        return
    }
    public static NotifyChange(node: KPointer, startIdx: int32, endIdx: int32, count: int32): void {
        const node_casted = node as (KPointer)
        const startIdx_casted = startIdx as (int32)
        const endIdx_casted = endIdx as (int32)
        const count_casted = count as (int32)
        LazyForEachOps.NotifyChange_serialize(node_casted, startIdx_casted, endIdx_casted, count_casted)
        return
    }
    private static NeedMoreElements_serialize(node: KPointer, mark: KPointer, direction: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LazyForEachOps_NeedMoreElements(node, mark, direction)
        return retval
    }
    private static OnRangeUpdate_serialize(node: KPointer, totalCount: int32, updater: Callback_RangeUpdate): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_OnRangeUpdate(node, totalCount, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetCurrentIndex_serialize(node: KPointer, index: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_SetCurrentIndex(node, index)
    }
    private static Prepare_serialize(node: KPointer, itemCount: int32, offset: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_Prepare(node, itemCount, offset)
    }
    private static NotifyChange_serialize(node: KPointer, startIdx: int32, endIdx: int32, count: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_NotifyChange(node, startIdx, endIdx, count)
    }
}
