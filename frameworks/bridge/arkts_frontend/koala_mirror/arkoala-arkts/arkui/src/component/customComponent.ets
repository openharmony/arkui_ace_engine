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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { GeometryInfo_serializer, Layoutable_serializer, Measurable_serializer, SizeResult_serializer, GeometryInfo, Layoutable, LayoutableInternal, Measurable, MeasurableInternal, SizeResult } from "./common"
import { ConstraintSizeOptions_serializer, ConstraintSizeOptions } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export interface LayoutCallback {
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult
}
export class LayoutCallbackInternal implements MaterializedBase,LayoutCallback {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LayoutCallbackInternal.getFinalizer())
    }
    constructor() {
        this(LayoutCallbackInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LayoutCallback_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutCallback_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LayoutCallbackInternal {
        return new LayoutCallbackInternal(ptr)
    }
    public onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
        const selfLayoutInfo_casted = selfLayoutInfo as (GeometryInfo)
        const children_casted = children as (Array<Layoutable>)
        const constraint_casted = constraint as (ConstraintSizeOptions)
        this.onPlaceChildren_serialize(selfLayoutInfo_casted, children_casted, constraint_casted)
        return
    }
    public onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        const selfLayoutInfo_casted = selfLayoutInfo as (GeometryInfo)
        const children_casted = children as (Array<Measurable>)
        const constraint_casted = constraint as (ConstraintSizeOptions)
        return this.onMeasureSize_serialize(selfLayoutInfo_casted, children_casted, constraint_casted)
    }
    private onPlaceChildren_serialize(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        GeometryInfo_serializer.write(thisSerializer, selfLayoutInfo)
        thisSerializer.writeInt32((children.length).toInt())
        for (let children_counter_i = 0; children_counter_i < children.length; children_counter_i++) {
            const children_element : Layoutable = children[children_counter_i]
            Layoutable_serializer.write(thisSerializer, children_element)
        }
        ConstraintSizeOptions_serializer.write(thisSerializer, constraint)
        ArkUIGeneratedNativeModule._LayoutCallback_onPlaceChildren(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onMeasureSize_serialize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions): SizeResult {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        GeometryInfo_serializer.write(thisSerializer, selfLayoutInfo)
        thisSerializer.writeInt32((children.length).toInt())
        for (let children_counter_i = 0; children_counter_i < children.length; children_counter_i++) {
            const children_element : Measurable = children[children_counter_i]
            Measurable_serializer.write(thisSerializer, children_element)
        }
        ConstraintSizeOptions_serializer.write(thisSerializer, constraint)
        const retval  = ArkUIGeneratedNativeModule._LayoutCallback_onMeasureSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SizeResult = SizeResult_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export interface PageLifeCycle {
    onPageShow(): void
    onPageHide(): void
    onBackPress(): boolean
    pageTransition(): void
    onNewParam(param: Object | undefined): void
}
export class PageLifeCycleInternal implements MaterializedBase,PageLifeCycle {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PageLifeCycleInternal.getFinalizer())
    }
    constructor() {
        this(PageLifeCycleInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PageLifeCycle_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PageLifeCycle_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PageLifeCycleInternal {
        return new PageLifeCycleInternal(ptr)
    }
    public onPageShow(): void {
        this.onPageShow_serialize()
        return
    }
    public onPageHide(): void {
        this.onPageHide_serialize()
        return
    }
    public onBackPress(): boolean {
        return this.onBackPress_serialize()
    }
    public pageTransition(): void {
        this.pageTransition_serialize()
        return
    }
    public onNewParam(param: Object | undefined): void {
        const param_casted = param as (Object | undefined)
        this.onNewParam_serialize(param_casted)
        return
    }
    private onPageShow_serialize(): void {
        ArkUIGeneratedNativeModule._PageLifeCycle_onPageShow(this.peer!.ptr)
    }
    private onPageHide_serialize(): void {
        ArkUIGeneratedNativeModule._PageLifeCycle_onPageHide(this.peer!.ptr)
    }
    private onBackPress_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._PageLifeCycle_onBackPress(this.peer!.ptr)
        return retval
    }
    private pageTransition_serialize(): void {
        ArkUIGeneratedNativeModule._PageLifeCycle_pageTransition(this.peer!.ptr)
    }
    private onNewParam_serialize(param: Object | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let param_type : int32 = RuntimeType.UNDEFINED
        param_type = runtimeType(param)
        thisSerializer.writeInt8((param_type).toChar())
        if ((param_type) != (RuntimeType.UNDEFINED)) {
            const param_value  = param!
            thisSerializer.holdAndWriteObject(param_value)
        }
        ArkUIGeneratedNativeModule._PageLifeCycle_onNewParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class LayoutCallback_serializer {
    public static write(buffer: SerializerBase, value: LayoutCallback): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LayoutCallback {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LayoutCallbackInternal.fromPtr(ptr)
    }
}
export class PageLifeCycle_serializer {
    public static write(buffer: SerializerBase, value: PageLifeCycle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PageLifeCycle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PageLifeCycleInternal.fromPtr(ptr)
    }
}
