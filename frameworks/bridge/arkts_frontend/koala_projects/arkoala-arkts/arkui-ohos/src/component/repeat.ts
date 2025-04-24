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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface VirtualScrollOptions {
    totalCount?: number | undefined
    reusable?: boolean | undefined
    onLazyLoading(index: number): void
    onTotalCount(): number
}
export class VirtualScrollOptionsInternal implements MaterializedBase,VirtualScrollOptions {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get totalCount(): number | undefined {
        return this.getTotalCount()
    }
    set totalCount(totalCount: number | undefined) {
        const totalCount_NonNull  = (totalCount as number)
        this.setTotalCount(totalCount_NonNull)
    }
    get reusable(): boolean | undefined {
        return this.getReusable()
    }
    set reusable(reusable: boolean | undefined) {
        const reusable_NonNull  = (reusable as boolean)
        this.setReusable(reusable_NonNull)
    }
    static ctor_virtualscrolloptions(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._VirtualScrollOptions_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = VirtualScrollOptionsInternal.ctor_virtualscrolloptions()
        this.peer = new Finalizable(ctorPtr, VirtualScrollOptionsInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._VirtualScrollOptions_getFinalizer()
    }
    public onLazyLoading(index: number): void {
        const index_casted = index as (number)
        this.onLazyLoading_serialize(index_casted)
        return
    }
    public onTotalCount(): number {
        return this.onTotalCount_serialize()
    }
    private getTotalCount(): number | undefined {
        return this.getTotalCount_serialize()
    }
    private setTotalCount(totalCount: number): void {
        const totalCount_casted = totalCount as (number)
        this.setTotalCount_serialize(totalCount_casted)
        return
    }
    private getReusable(): boolean | undefined {
        return this.getReusable_serialize()
    }
    private setReusable(reusable: boolean): void {
        const reusable_casted = reusable as (boolean)
        this.setReusable_serialize(reusable_casted)
        return
    }
    private onLazyLoading_serialize(index: number): void {
        ArkUIGeneratedNativeModule._VirtualScrollOptions_onLazyLoading(this.peer!.ptr, index)
    }
    private onTotalCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._VirtualScrollOptions_onTotalCount(this.peer!.ptr)
        return retval
    }
    private getTotalCount_serialize(): number | undefined {
        const retval  = ArkUIGeneratedNativeModule._VirtualScrollOptions_getTotalCount(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setTotalCount_serialize(totalCount: number): void {
        ArkUIGeneratedNativeModule._VirtualScrollOptions_setTotalCount(this.peer!.ptr, totalCount)
    }
    private getReusable_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._VirtualScrollOptions_getReusable(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setReusable_serialize(reusable: boolean): void {
        ArkUIGeneratedNativeModule._VirtualScrollOptions_setReusable(this.peer!.ptr, reusable ? 1 : 0)
    }
    public static fromPtr(ptr: KPointer): VirtualScrollOptionsInternal {
        const obj : VirtualScrollOptionsInternal = new VirtualScrollOptionsInternal()
        obj.peer = new Finalizable(ptr, VirtualScrollOptionsInternal.getFinalizer())
        return obj
    }
}
export interface TemplateOptions {
    cachedCount?: number;
}
export type RepeatArray<T> = Array<T> | object | object;
