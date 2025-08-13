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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { SizeOptions } from "./units"
import { Visibility } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Want } from "./ohos.app.ability"

export class ArkFormComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkFormComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormComponent_construct(peerId, flags)
        const _peer  = new ArkFormComponentPeer(_peerPtr, peerId, "FormComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormComponentOptionsAttribute(value: FormInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFormInfo(value)
        ArkUIGeneratedNativeModule._FormComponentInterface_setFormComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    moduleNameAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_moduleName(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dimensionAttribute(value: FormDimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FormDimension)
            thisSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_dimension(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    allowUpdateAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_allowUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visibilityAttribute(value: Visibility | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Visibility)
            thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_visibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAcquiredAttribute(value: ((parameter: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onAcquired(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ((info: Literal_Number_errcode_String_msg) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRouterAttribute(value: ((info: object) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onRouter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUninstallAttribute(value: ((parameter: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onUninstall(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum FormDimension {
    DIMENSION_1_2 = 0,
    Dimension_1_2 = 0,
    DIMENSION_2_2 = 1,
    Dimension_2_2 = 1,
    DIMENSION_2_4 = 2,
    Dimension_2_4 = 2,
    DIMENSION_4_4 = 3,
    Dimension_4_4 = 3,
    DIMENSION_2_1 = 4,
    Dimension_2_1 = 4,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9
}
export enum FormRenderingMode {
    FULL_COLOR = 0,
    SINGLE_COLOR = 1
}
export enum FormShape {
    RECT = 1,
    CIRCLE = 2
}
export interface FormInfo {
    id: int64 | string;
    name: string;
    bundle: string;
    ability: string;
    module: string;
    dimension?: FormDimension;
    temporary?: boolean;
    want?: Want;
    renderingMode?: FormRenderingMode;
    shape?: FormShape;
}
export type FormComponentInterface = (value: FormInfo) => FormComponentAttribute;
export interface FormCallbackInfo {
    id: int64;
    idString: string;
}
export type Callback_FormCallbackInfo_Void = (parameter: FormCallbackInfo) => void;
export interface Literal_Number_errcode_String_msg {
    errcode: number;
    msg: string;
}
export type Callback_Literal_Number_errcode_String_msg_Void = (info: Literal_Number_errcode_String_msg) => void;
export type Callback_Any_Void = (info: object) => void;
export interface FormComponentAttribute extends CommonMethod {
    size(value: SizeOptions | undefined): this
    moduleName(value: string | undefined): this
    dimension(value: FormDimension | undefined): this
    allowUpdate(value: boolean | undefined): this
    visibility(value: Visibility | undefined): this
    onAcquired(value: ((parameter: FormCallbackInfo) => void) | undefined): this
    onError(value: ((info: Literal_Number_errcode_String_msg) => void) | undefined): this
    onRouter(value: ((info: object) => void) | undefined): this
    onUninstall(value: ((parameter: FormCallbackInfo) => void) | undefined): this
    onLoad(value: (() => void) | undefined): this
}
export class ArkFormComponentStyle extends ArkCommonMethodStyle implements FormComponentAttribute {
    size_value?: SizeOptions | undefined
    moduleName_value?: string | undefined
    dimension_value?: FormDimension | undefined
    allowUpdate_value?: boolean | undefined
    visibility_value?: Visibility | undefined
    onAcquired_value?: ((parameter: FormCallbackInfo) => void) | undefined
    onError_value?: ((info: Literal_Number_errcode_String_msg) => void) | undefined
    onRouter_value?: ((info: object) => void) | undefined
    onUninstall_value?: ((parameter: FormCallbackInfo) => void) | undefined
    onLoad_value?: (() => void) | undefined
    public size(value: SizeOptions | undefined): this {
        return this
    }
    public moduleName(value: string | undefined): this {
        return this
    }
    public dimension(value: FormDimension | undefined): this {
        return this
    }
    public allowUpdate(value: boolean | undefined): this {
        return this
    }
    public visibility(value: Visibility | undefined): this {
        return this
    }
    public onAcquired(value: ((parameter: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public onError(value: ((info: Literal_Number_errcode_String_msg) => void) | undefined): this {
        return this
    }
    public onRouter(value: ((info: object) => void) | undefined): this {
        return this
    }
    public onUninstall(value: ((parameter: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public onLoad(value: (() => void) | undefined): this {
        return this
        }
}
export class ArkFormComponentComponent extends ArkCommonMethodComponent implements FormComponentAttribute {
    getPeer(): ArkFormComponentPeer {
        return (this.peer as ArkFormComponentPeer)
    }
    public setFormComponentOptions(value: FormInfo): this {
        if (this.checkPriority("setFormComponentOptions")) {
            const value_casted = value as (FormInfo)
            this.getPeer()?.setFormComponentOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public size(value: SizeOptions | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    public moduleName(value: string | undefined): this {
        if (this.checkPriority("moduleName")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.moduleNameAttribute(value_casted)
            return this
        }
        return this
    }
    public dimension(value: FormDimension | undefined): this {
        if (this.checkPriority("dimension")) {
            const value_casted = value as (FormDimension | undefined)
            this.getPeer()?.dimensionAttribute(value_casted)
            return this
        }
        return this
    }
    public allowUpdate(value: boolean | undefined): this {
        if (this.checkPriority("allowUpdate")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.allowUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public visibility(value: Visibility | undefined): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility | undefined)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    public onAcquired(value: ((parameter: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onAcquired")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.onAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ((info: Literal_Number_errcode_String_msg) => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((info: Literal_Number_errcode_String_msg) => void) | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onRouter(value: ((info: object) => void) | undefined): this {
        if (this.checkPriority("onRouter")) {
            const value_casted = value as (((info: object) => void) | undefined)
            this.getPeer()?.onRouterAttribute(value_casted)
            return this
        }
        return this
    }
    public onUninstall(value: ((parameter: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onUninstall")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.onUninstallAttribute(value_casted)
            return this
        }
        return this
    }
    public onLoad(value: (() => void) | undefined): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onLoadAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function FormComponent(
    /** @memo */
    style: ((attributes: FormComponentAttribute) => void) | undefined,
    value: FormInfo,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkFormComponentComponent()
    })
    NodeAttach<ArkFormComponentPeer>((): ArkFormComponentPeer => ArkFormComponentPeer.create(receiver), (_: ArkFormComponentPeer) => {
        receiver.setFormComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
