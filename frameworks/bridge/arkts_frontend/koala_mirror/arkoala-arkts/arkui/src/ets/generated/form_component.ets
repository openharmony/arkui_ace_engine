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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { SizeOptions } from "./units"
import { Visibility } from "./enums"
import { FormComponentAttribute_onRouter_callback_type } from "./type-replacements"
import { Callback_Void } from "./ability_component"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Want } from "./ohos.app.ability"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFormComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFormComponentPeer {
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
    sizeAttribute(value: SizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(value)
        ArkUIGeneratedNativeModule._FormComponentAttribute_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    moduleNameAttribute(value: string): void {
        ArkUIGeneratedNativeModule._FormComponentAttribute_moduleName(this.peer.ptr, value)
    }
    dimensionAttribute(value: FormDimension): void {
        ArkUIGeneratedNativeModule._FormComponentAttribute_dimension(this.peer.ptr, TypeChecker.FormDimension_ToNumeric(value))
    }
    allowUpdateAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._FormComponentAttribute_allowUpdate(this.peer.ptr, value ? 1 : 0)
    }
    visibilityAttribute(value: Visibility): void {
        ArkUIGeneratedNativeModule._FormComponentAttribute_visibility(this.peer.ptr, TypeChecker.Visibility_ToNumeric(value))
    }
    onAcquiredAttribute(value: ((parameter: FormCallbackInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FormComponentAttribute_onAcquired(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ((info: Literal_Number_errcode_String_msg) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FormComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRouterAttribute(value: ((info: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FormComponentAttribute_onRouter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUninstallAttribute(value: ((parameter: FormCallbackInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._FormComponentAttribute_onUninstall(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
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
    DIMENSION_6_4 = 7
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
export interface FormComponentAttribute extends CommonMethod {
    size(value: SizeOptions): this
    moduleName(value: string): this
    dimension(value: FormDimension): this
    allowUpdate(value: boolean): this
    visibility(value: Visibility): this
    onAcquired(value: ((parameter: FormCallbackInfo) => void)): this
    onError(value: ((info: Literal_Number_errcode_String_msg) => void)): this
    onRouter(value: ((info: string) => void)): this
    onUninstall(value: ((parameter: FormCallbackInfo) => void)): this
    onLoad(value: (() => void)): this
    attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIFormComponentAttribute extends UICommonMethod {
    @memo
    size(value: SizeOptions): this
    @memo
    moduleName(value: string): this
    @memo
    dimension(value: FormDimension): this
    @memo
    allowUpdate(value: boolean): this
    @memo
    visibility(value: Visibility): this
    @memo
    onAcquired(value: ((parameter: FormCallbackInfo) => void)): this
    @memo
    onError(value: ((info: Literal_Number_errcode_String_msg) => void)): this
    @memo
    onRouter(value: ((info: string) => void)): this
    @memo
    onUninstall(value: ((parameter: FormCallbackInfo) => void)): this
    @memo
    onLoad(value: (() => void)): this
    @memo
    attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkFormComponentStyle extends ArkCommonMethodStyle implements FormComponentAttribute {
    size_value?: SizeOptions
    moduleName_value?: string
    dimension_value?: FormDimension
    allowUpdate_value?: boolean
    visibility_value?: Visibility
    onAcquired_value?: ((parameter: FormCallbackInfo) => void)
    onError_value?: ((info: Literal_Number_errcode_String_msg) => void)
    onRouter_value?: ((info: string) => void)
    onUninstall_value?: ((parameter: FormCallbackInfo) => void)
    onLoad_value?: (() => void)
    public size(value: SizeOptions): this {
        return this
    }
    public moduleName(value: string): this {
        return this
    }
    public dimension(value: FormDimension): this {
        return this
    }
    public allowUpdate(value: boolean): this {
        return this
    }
    public visibility(value: Visibility): this {
        return this
    }
    public onAcquired(value: ((parameter: FormCallbackInfo) => void)): this {
        return this
    }
    public onError(value: ((info: Literal_Number_errcode_String_msg) => void)): this {
        return this
    }
    public onRouter(value: ((info: string) => void)): this {
        return this
    }
    public onUninstall(value: ((parameter: FormCallbackInfo) => void)): this {
        return this
    }
    public onLoad(value: (() => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkFormComponentComponent extends ArkCommonMethodComponent implements UIFormComponentAttribute {
    getPeer(): ArkFormComponentPeer {
        return (this.peer as ArkFormComponentPeer)
    }
    @memo
    public setFormComponentOptions(value: FormInfo): this {
        if (this.checkPriority("setFormComponentOptions")) {
            const value_casted = value as (FormInfo)
            this.getPeer()?.setFormComponentOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public size(value: SizeOptions): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions)
            this.getPeer()?.sizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public moduleName(value: string): this {
        if (this.checkPriority("moduleName")) {
            const value_casted = value as (string)
            this.getPeer()?.moduleNameAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public dimension(value: FormDimension): this {
        if (this.checkPriority("dimension")) {
            const value_casted = value as (FormDimension)
            this.getPeer()?.dimensionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public allowUpdate(value: boolean): this {
        if (this.checkPriority("allowUpdate")) {
            const value_casted = value as (boolean)
            this.getPeer()?.allowUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public visibility(value: Visibility): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility)
            this.getPeer()?.visibilityAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onAcquired(value: ((parameter: FormCallbackInfo) => void)): this {
        if (this.checkPriority("onAcquired")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void))
            this.getPeer()?.onAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onError(value: ((info: Literal_Number_errcode_String_msg) => void)): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((info: Literal_Number_errcode_String_msg) => void))
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onRouter(value: ((info: string) => void)): this {
        if (this.checkPriority("onRouter")) {
            const value_casted = value as (((info: string) => void))
            this.getPeer()?.onRouterAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onUninstall(value: ((parameter: FormCallbackInfo) => void)): this {
        if (this.checkPriority("onUninstall")) {
            const value_casted = value as (((parameter: FormCallbackInfo) => void))
            this.getPeer()?.onUninstallAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onLoad(value: (() => void)): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onLoadAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("FormComponent")
export function FormComponent(
    value: FormInfo,
    @memo
    content_?: () => void,
): FormComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function FormComponent(
    @memo
    style: ((attributes: UIFormComponentAttribute) => void) | undefined,
    value: FormInfo,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFormComponentComponent>((): ArkFormComponentComponent => {
        return new ArkFormComponentComponent()
    })
    NodeAttach<ArkFormComponentPeer>((): ArkFormComponentPeer => ArkFormComponentPeer.create(receiver), (_: ArkFormComponentPeer): void => {
        receiver.setFormComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
