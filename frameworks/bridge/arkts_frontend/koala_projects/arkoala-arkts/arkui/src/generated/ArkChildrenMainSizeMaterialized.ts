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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export class ChildrenMainSizeInternal {
    public static fromPtr(ptr: KPointer): ChildrenMainSize {
        const obj : ChildrenMainSize = new ChildrenMainSize(undefined)
        obj.peer = new Finalizable(ptr, ChildrenMainSize.getFinalizer())
        return obj
    }
}
export class ChildrenMainSize implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get childDefaultSize(): number {
        return this.getChildDefaultSize()
    }
    set childDefaultSize(childDefaultSize: number) {
        this.setChildDefaultSize(childDefaultSize)
    }
    static ctor_childrenmainsize(childDefaultSize: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ChildrenMainSize_ctor(childDefaultSize)
        return retval
    }
    constructor(childDefaultSize?: number) {
        if ((childDefaultSize) !== (undefined))
        {
            const ctorPtr : KPointer = ChildrenMainSize.ctor_childrenmainsize((childDefaultSize)!)
            this.peer = new Finalizable(ctorPtr, ChildrenMainSize.getFinalizer())
        }
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ChildrenMainSize_getFinalizer()
    }
    public splice(start: number, deleteCount?: number, childrenSize?: Array<number>): void {
        const start_casted = start as (number)
        const deleteCount_casted = deleteCount as (number | undefined)
        const childrenSize_casted = childrenSize as (Array<number> | undefined)
        this.splice_serialize(start_casted, deleteCount_casted, childrenSize_casted)
        return
    }
    public update(index: number, childSize: number): void {
        const index_casted = index as (number)
        const childSize_casted = childSize as (number)
        this.update_serialize(index_casted, childSize_casted)
        return
    }
    private getChildDefaultSize(): number {
        return this.getChildDefaultSize_serialize()
    }
    private setChildDefaultSize(childDefaultSize: number): void {
        const childDefaultSize_casted = childDefaultSize as (number)
        this.setChildDefaultSize_serialize(childDefaultSize_casted)
        return
    }
    private splice_serialize(start: number, deleteCount?: number, childrenSize?: Array<number>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let deleteCount_type : int32 = RuntimeType.UNDEFINED
        deleteCount_type = runtimeType(deleteCount)
        thisSerializer.writeInt8(deleteCount_type as int32)
        if ((RuntimeType.UNDEFINED) != (deleteCount_type)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let childrenSize_type : int32 = RuntimeType.UNDEFINED
        childrenSize_type = runtimeType(childrenSize)
        thisSerializer.writeInt8(childrenSize_type as int32)
        if ((RuntimeType.UNDEFINED) != (childrenSize_type)) {
            const childrenSize_value  = childrenSize!
            thisSerializer.writeInt32(childrenSize_value.length as int32)
            for (let i = 0; i < childrenSize_value.length; i++) {
                const childrenSize_value_element : number = childrenSize_value[i]
                thisSerializer.writeNumber(childrenSize_value_element)
            }
        }
        ArkUIGeneratedNativeModule._ChildrenMainSize_splice(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private update_serialize(index: number, childSize: number): void {
        ArkUIGeneratedNativeModule._ChildrenMainSize_update(this.peer!.ptr, index, childSize)
    }
    private getChildDefaultSize_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._ChildrenMainSize_getChildDefaultSize(this.peer!.ptr)
        return retval
    }
    private setChildDefaultSize_serialize(childDefaultSize: number): void {
        ArkUIGeneratedNativeModule._ChildrenMainSize_setChildDefaultSize(this.peer!.ptr, childDefaultSize)
    }
}
