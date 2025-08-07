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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Visibility } from "./enums"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Want, Want_serializer } from "./../generated/ohos.app.ability.Want"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkFormComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFormComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormComponent_construct(peerId, flags)
        const _peer  = new ArkFormComponentPeer(_peerPtr, peerId, 'FormComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormComponentOptionsAttribute(value: FormInfo): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FormInfo_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._FormComponentInterface_setFormComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSizeAttribute(value: FormSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            FormSize_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModuleNameAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setModuleName(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDimensionAttribute(value: FormDimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FormDimension)
            thisSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setDimension(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowUpdateAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setAllowUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVisibilityAttribute(value: Visibility | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as Visibility)
            thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setVisibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAcquiredAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnAcquired(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ((value0: ErrorInformation) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRouterAttribute(value: ((value0: Object) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnRouter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUninstallAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnUninstall(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUpdateAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface FormCallbackInfo {
    id: int64;
    idString: string;
}
export interface FormSize {
    width: double;
    height: double;
}
export interface ErrorInformation {
    errcode: int32;
    msg: string;
}
export interface FormComponentAttribute extends CommonMethod {
    size(value: FormSize | undefined): this
    moduleName(value: string | undefined): this {
        throw new Error("Unimplemented method moduleName")
    }
    dimension(value: FormDimension | undefined): this {
        throw new Error("Unimplemented method dimension")
    }
    allowUpdate(value: boolean | undefined): this {
        throw new Error("Unimplemented method allowUpdate")
    }
    visibility(value: Visibility | undefined): this
    onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onAcquired")
    }
    onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        throw new Error("Unimplemented method onError")
    }
    onRouter(value: ((value0: Object) => void) | undefined): this {
        throw new Error("Unimplemented method onRouter")
    }
    onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onUninstall")
    }
    onLoad(value: VoidCallback | undefined): this {
        throw new Error("Unimplemented method onLoad")
    }
    onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        throw new Error("Unimplemented method onUpdate")
    }
    attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFormComponentStyle extends ArkCommonMethodStyle implements FormComponentAttribute {
    size_value?: FormSize | undefined
    moduleName_value?: string | undefined
    dimension_value?: FormDimension | undefined
    allowUpdate_value?: boolean | undefined
    visibility_value?: Visibility | undefined
    onAcquired_value?: ((value0: FormCallbackInfo) => void) | undefined
    onError_value?: ((value0: ErrorInformation) => void) | undefined
    onRouter_value?: ((value0: Object) => void) | undefined
    onUninstall_value?: ((value0: FormCallbackInfo) => void) | undefined
    onLoad_value?: VoidCallback | undefined
    onUpdate_value?: ((value0: FormCallbackInfo) => void) | undefined
    attributeModifier_value?: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined
    public size(value: FormSize | undefined): this {
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
    public onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        return this
    }
    public onRouter(value: ((value0: Object) => void) | undefined): this {
        return this
    }
    public onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public onLoad(value: VoidCallback | undefined): this {
        return this
    }
    public onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public size(value: FormSize | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (FormSize | undefined)
            this.getPeer()?.setSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public moduleName(value: string | undefined): this {
        if (this.checkPriority("moduleName")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setModuleNameAttribute(value_casted)
            return this
        }
        return this
    }
    public dimension(value: FormDimension | undefined): this {
        if (this.checkPriority("dimension")) {
            const value_casted = value as (FormDimension | undefined)
            this.getPeer()?.setDimensionAttribute(value_casted)
            return this
        }
        return this
    }
    public allowUpdate(value: boolean | undefined): this {
        if (this.checkPriority("allowUpdate")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAllowUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public visibility(value: Visibility | undefined): this {
        if (this.checkPriority("visibility")) {
            const value_casted = value as (Visibility | undefined)
            this.getPeer()?.setVisibilityAttribute(value_casted)
            return this
        }
        return this
    }
    public onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onAcquired")) {
            const value_casted = value as (((value0: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.setOnAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((value0: ErrorInformation) => void) | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onRouter(value: ((value0: Object) => void) | undefined): this {
        if (this.checkPriority("onRouter")) {
            const value_casted = value as (((value0: Object) => void) | undefined)
            this.getPeer()?.setOnRouterAttribute(value_casted)
            return this
        }
        return this
    }
    public onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onUninstall")) {
            const value_casted = value as (((value0: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.setOnUninstallAttribute(value_casted)
            return this
        }
        return this
    }
    public onLoad(value: VoidCallback | undefined): this {
        if (this.checkPriority("onLoad")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onUpdate")) {
            const value_casted = value as (((value0: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.setOnUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function FormComponent(
    @memo
    style: ((attributes: FormComponentAttribute) => void) | undefined,
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

export class FormComponentModifier extends CommonMethodModifier implements FormComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _size_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _size_0_0value?: FormSize | undefined
    _moduleName_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _moduleName_0_0value?: string | undefined
    _dimension_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dimension_0_0value?: FormDimension | undefined
    _allowUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowUpdate_0_0value?: boolean | undefined
    _visibility_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _visibility_0_0value?: Visibility | undefined
    _onAcquired_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAcquired_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ((value0: ErrorInformation) => void) | undefined
    _onRouter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRouter_0_0value?: ((value0: Object) => void) | undefined
    _onUninstall_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUninstall_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    _onLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoad_0_0value?: VoidCallback | undefined
    _onUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUpdate_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    applyModifierPatch(peer: ArkFormComponentPeer): void {
        super.applyModifierPatch(peer)
        if (this._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSizeAttribute((this._size_0_0value as FormSize | undefined));
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._size_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSizeAttribute((undefined as FormSize | undefined));
                }
            }
        }
        if (this._moduleName_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._moduleName_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setModuleNameAttribute((this._moduleName_0_0value as string | undefined));
                    this._moduleName_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._moduleName_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._moduleName_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setModuleNameAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._dimension_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dimension_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDimensionAttribute((this._dimension_0_0value as FormDimension | undefined));
                    this._dimension_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dimension_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dimension_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDimensionAttribute((undefined as FormDimension | undefined));
                }
            }
        }
        if (this._allowUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAllowUpdateAttribute((this._allowUpdate_0_0value as boolean | undefined));
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAllowUpdateAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVisibilityAttribute((this._visibility_0_0value as Visibility | undefined));
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._visibility_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVisibilityAttribute((undefined as Visibility | undefined));
                }
            }
        }
        if (this._onAcquired_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAcquired_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAcquiredAttribute((this._onAcquired_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onAcquired_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAcquired_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAcquired_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAcquiredAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ((value0: ErrorInformation) => void) | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ((value0: ErrorInformation) => void) | undefined));
                }
            }
        }
        if (this._onRouter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRouter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRouterAttribute((this._onRouter_0_0value as ((value0: Object) => void) | undefined));
                    this._onRouter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRouter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRouter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRouterAttribute((undefined as ((value0: Object) => void) | undefined));
                }
            }
        }
        if (this._onUninstall_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUninstall_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUninstallAttribute((this._onUninstall_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onUninstall_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUninstall_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUninstall_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUninstallAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (this._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUpdateAttribute((this._onUpdate_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUpdateAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FormComponentModifier): void {
        super.mergeModifier(modifier)
        if (modifier._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as FormSize | undefined));
                }
            }
        }
        if (modifier._moduleName_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._moduleName_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.moduleName(modifier._moduleName_0_0value);
                    break;
                }
                default: {
                    this.moduleName((undefined as string | undefined));
                }
            }
        }
        if (modifier._dimension_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dimension_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dimension(modifier._dimension_0_0value);
                    break;
                }
                default: {
                    this.dimension((undefined as FormDimension | undefined));
                }
            }
        }
        if (modifier._allowUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowUpdate(modifier._allowUpdate_0_0value);
                    break;
                }
                default: {
                    this.allowUpdate((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.visibility(modifier._visibility_0_0value);
                    break;
                }
                default: {
                    this.visibility((undefined as Visibility | undefined));
                }
            }
        }
        if (modifier._onAcquired_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAcquired_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAcquired(modifier._onAcquired_0_0value);
                    break;
                }
                default: {
                    this.onAcquired((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ((value0: ErrorInformation) => void) | undefined));
                }
            }
        }
        if (modifier._onRouter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRouter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRouter(modifier._onRouter_0_0value);
                    break;
                }
                default: {
                    this.onRouter((undefined as ((value0: Object) => void) | undefined));
                }
            }
        }
        if (modifier._onUninstall_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUninstall_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUninstall(modifier._onUninstall_0_0value);
                    break;
                }
                default: {
                    this.onUninstall((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUpdate(modifier._onUpdate_0_0value);
                    break;
                }
                default: {
                    this.onUpdate((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
    }
    size(value: FormSize | undefined): this {
        if (((this._size_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._size_0_flag = AttributeUpdaterFlag.UPDATE
            this._size_0_0value = value
        } else
        {
            this._size_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    moduleName(value: string | undefined): this {
        if (((this._moduleName_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._moduleName_0_0value) !== (value)))
        {
            this._moduleName_0_flag = AttributeUpdaterFlag.UPDATE
            this._moduleName_0_0value = value
        } else
        {
            this._moduleName_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dimension(value: FormDimension | undefined): this {
        if (((this._dimension_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dimension_0_flag = AttributeUpdaterFlag.UPDATE
            this._dimension_0_0value = value
        } else
        {
            this._dimension_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    allowUpdate(value: boolean | undefined): this {
        if (((this._allowUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._allowUpdate_0_0value) !== (value)))
        {
            this._allowUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowUpdate_0_0value = value
        } else
        {
            this._allowUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    visibility(value: Visibility | undefined): this {
        if (((this._visibility_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._visibility_0_flag = AttributeUpdaterFlag.UPDATE
            this._visibility_0_0value = value
        } else
        {
            this._visibility_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onAcquired_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAcquired_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAcquired_0_0value = value
        } else
        {
            this._onAcquired_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRouter(value: ((value0: Object) => void) | undefined): this {
        if (((this._onRouter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRouter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRouter_0_0value = value
        } else
        {
            this._onRouter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onUninstall_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUninstall_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUninstall_0_0value = value
        } else
        {
            this._onUninstall_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._onLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoad_0_0value = value
        } else
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUpdate_0_0value = value
        } else
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FormSize_serializer {
    public static write(buffer: SerializerBase, value: FormSize): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): FormSize {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : double = valueDeserializer.readFloat64()
        const heightTmpResult : double = valueDeserializer.readFloat64()
        let value : FormSize = ({width: widthTmpResult, height: heightTmpResult} as FormSize)
        return value
    }
}
export class ErrorInformation_serializer {
    public static write(buffer: SerializerBase, value: ErrorInformation): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForErrcode  = value.errcode
        valueSerializer.writeInt32(valueHolderForErrcode)
        const valueHolderForMsg  = value.msg
        valueSerializer.writeString(valueHolderForMsg)
    }
    public static read(buffer: DeserializerBase): ErrorInformation {
        let valueDeserializer : DeserializerBase = buffer
        const errcodeTmpResult : int32 = valueDeserializer.readInt32()
        const msgTmpResult : string = (valueDeserializer.readString() as string)
        let value : ErrorInformation = ({errcode: errcodeTmpResult, msg: msgTmpResult} as ErrorInformation)
        return value
    }
}
export class FormCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: FormCallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeInt64(valueHolderForId)
        const valueHolderForIdString  = value.idString
        valueSerializer.writeString(valueHolderForIdString)
    }
    public static read(buffer: DeserializerBase): FormCallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : int64 = valueDeserializer.readInt64()
        const idStringTmpResult : string = (valueDeserializer.readString() as string)
        let value : FormCallbackInfo = ({id: idTmpResult, idString: idStringTmpResult} as FormCallbackInfo)
        return value
    }
}
export class FormInfo_serializer {
    public static write(buffer: SerializerBase, value: FormInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        if (valueHolderForId instanceof int64) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForIdForIdx0  = valueHolderForId as int64
            valueSerializer.writeInt64(valueHolderForIdForIdx0)
        } else if (valueHolderForId instanceof string) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForIdForIdx1  = valueHolderForId as string
            valueSerializer.writeString(valueHolderForIdForIdx1)
        }
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForBundle  = value.bundle
        valueSerializer.writeString(valueHolderForBundle)
        const valueHolderForAbility  = value.ability
        valueSerializer.writeString(valueHolderForAbility)
        const valueHolderForModule  = value.module
        valueSerializer.writeString(valueHolderForModule)
        const valueHolderForDimension  = value.dimension
        if (valueHolderForDimension !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDimensionTmpValue  = (valueHolderForDimension as FormDimension)
            valueSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(valueHolderForDimensionTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTemporary  = value.temporary
        if (valueHolderForTemporary !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTemporaryTmpValue  = valueHolderForTemporary!
            valueSerializer.writeBoolean(valueHolderForTemporaryTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWant  = value.want
        if (valueHolderForWant !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWantTmpValue  = valueHolderForWant!
            Want_serializer.write(valueSerializer, valueHolderForWantTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRenderingMode  = value.renderingMode
        if (valueHolderForRenderingMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRenderingModeTmpValue  = (valueHolderForRenderingMode as FormRenderingMode)
            valueSerializer.writeInt32(TypeChecker.FormRenderingMode_ToNumeric(valueHolderForRenderingModeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape  = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue  = (valueHolderForShape as FormShape)
            valueSerializer.writeInt32(TypeChecker.FormShape_ToNumeric(valueHolderForShapeTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FormInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let idTmpBuf : int64 | string | undefined
        if (idTmpBufUnionSelector == (0).toChar()) {
            idTmpBuf = valueDeserializer.readInt64()
        } else if (idTmpBufUnionSelector == (1).toChar()) {
            idTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error("One of the branches for idTmpBuf has to be chosen through deserialisation.")
        }
        const idTmpResult : int64 | string = (idTmpBuf as int64 | string)
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const bundleTmpResult : string = (valueDeserializer.readString() as string)
        const abilityTmpResult : string = (valueDeserializer.readString() as string)
        const moduleTmpResult : string = (valueDeserializer.readString() as string)
        const dimensionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dimensionTmpBuf : FormDimension | undefined
        if ((dimensionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dimensionTmpBuf = TypeChecker.FormDimension_FromNumeric(valueDeserializer.readInt32())
        }
        const dimensionTmpResult : FormDimension | undefined = dimensionTmpBuf
        const temporaryTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let temporaryTmpBuf : boolean | undefined
        if ((temporaryTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            temporaryTmpBuf = valueDeserializer.readBoolean()
        }
        const temporaryTmpResult : boolean | undefined = temporaryTmpBuf
        const wantTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wantTmpBuf : Want | undefined
        if ((wantTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wantTmpBuf = Want_serializer.read(valueDeserializer)
        }
        const wantTmpResult : Want | undefined = wantTmpBuf
        const renderingModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let renderingModeTmpBuf : FormRenderingMode | undefined
        if ((renderingModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            renderingModeTmpBuf = TypeChecker.FormRenderingMode_FromNumeric(valueDeserializer.readInt32())
        }
        const renderingModeTmpResult : FormRenderingMode | undefined = renderingModeTmpBuf
        const shapeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shapeTmpBuf : FormShape | undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = TypeChecker.FormShape_FromNumeric(valueDeserializer.readInt32())
        }
        const shapeTmpResult : FormShape | undefined = shapeTmpBuf
        let value : FormInfo = ({id: idTmpResult, name: nameTmpResult, bundle: bundleTmpResult, ability: abilityTmpResult, module: moduleTmpResult, dimension: dimensionTmpResult, temporary: temporaryTmpResult, want: wantTmpResult, renderingMode: renderingModeTmpResult, shape: shapeTmpResult} as FormInfo)
        return value
    }
}
