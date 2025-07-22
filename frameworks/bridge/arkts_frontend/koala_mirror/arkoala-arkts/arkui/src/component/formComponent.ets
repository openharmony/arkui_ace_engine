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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Visibility } from "./enums"
import { VoidCallback } from "./units"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Want, Want_serializer } from "./../generated/ohos.app.ability.Want"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FormInfo_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._FormComponentInterface_setFormComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSizeAttribute(value: FormSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            FormSize_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setModuleNameAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setModuleName(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDimensionAttribute(value: FormDimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FormDimension)
            thisSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setDimension(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAllowUpdateAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setAllowUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setVisibilityAttribute(value: Visibility | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as Visibility)
            thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setVisibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAcquiredAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnAcquired(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnErrorAttribute(value: ((value0: ErrorInformation) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRouterAttribute(value: ((value0: Object) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnRouter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUninstallAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnUninstall(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnLoadAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setOnLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnUpdateAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
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
    public apply(target: FormComponentAttribute): void {
        super.apply(target)
        if (this.size_value !== undefined)
            target.size(this.size_value!)
        if (this.moduleName_value !== undefined)
            target.moduleName(this.moduleName_value!)
        if (this.dimension_value !== undefined)
            target.dimension(this.dimension_value!)
        if (this.allowUpdate_value !== undefined)
            target.allowUpdate(this.allowUpdate_value!)
        if (this.visibility_value !== undefined)
            target.visibility(this.visibility_value!)
        if (this.onAcquired_value !== undefined)
            target.onAcquired(this.onAcquired_value!)
        if (this.onError_value !== undefined)
            target.onError(this.onError_value!)
        if (this.onRouter_value !== undefined)
            target.onRouter(this.onRouter_value!)
        if (this.onUninstall_value !== undefined)
            target.onUninstall(this.onUninstall_value!)
        if (this.onLoad_value !== undefined)
            target.onLoad(this.onLoad_value!)
        if (this.onUpdate_value !== undefined)
            target.onUpdate(this.onUpdate_value!)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withFormComponentStyle(receiver: FormComponentAttribute, modifier: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkFormComponentStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("FormComponent")
// export function FormComponent(
//     value: FormInfo,
//     @memo
//     content_?: () => void,
// ): FormComponentAttribute {
//     throw new Error("Not implemented")
// }

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
        withFormComponentStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkFormComponentSet extends ArkCommonMethodSet implements FormComponentAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _size_flag?: boolean
    _size0_value?: FormSize | undefined
    _moduleName_flag?: boolean
    _moduleName0_value?: string | undefined
    _dimension_flag?: boolean
    _dimension0_value?: FormDimension | undefined
    _allowUpdate_flag?: boolean
    _allowUpdate0_value?: boolean | undefined
    _visibility_flag?: boolean
    _visibility0_value?: Visibility | undefined
    _onAcquired_flag?: boolean
    _onAcquired0_value?: ((value0: FormCallbackInfo) => void) | undefined
    _onError_flag?: boolean
    _onError0_value?: ((value0: ErrorInformation) => void) | undefined
    _onRouter_flag?: boolean
    _onRouter0_value?: ((value0: Object) => void) | undefined
    _onUninstall_flag?: boolean
    _onUninstall0_value?: ((value0: FormCallbackInfo) => void) | undefined
    _onLoad_flag?: boolean
    _onLoad0_value?: VoidCallback | undefined
    _onUpdate_flag?: boolean
    _onUpdate0_value?: ((value0: FormCallbackInfo) => void) | undefined
    applyModifierPatch(component: FormComponentAttribute): void {
        if (this._size_flag)
            component.size((this._size0_value as FormSize | undefined))
        if (this._moduleName_flag)
            component.moduleName((this._moduleName0_value as string | undefined))
        if (this._dimension_flag)
            component.dimension((this._dimension0_value as FormDimension | undefined))
        if (this._allowUpdate_flag)
            component.allowUpdate((this._allowUpdate0_value as boolean | undefined))
        if (this._visibility_flag)
            component.visibility((this._visibility0_value as Visibility | undefined))
        if (this._onAcquired_flag)
            component.onAcquired((this._onAcquired0_value as ((value0: FormCallbackInfo) => void) | undefined))
        if (this._onError_flag)
            component.onError((this._onError0_value as ((value0: ErrorInformation) => void) | undefined))
        if (this._onRouter_flag)
            component.onRouter((this._onRouter0_value as ((value0: Object) => void) | undefined))
        if (this._onUninstall_flag)
            component.onUninstall((this._onUninstall0_value as ((value0: FormCallbackInfo) => void) | undefined))
        if (this._onLoad_flag)
            component.onLoad((this._onLoad0_value as VoidCallback | undefined))
        if (this._onUpdate_flag)
            component.onUpdate((this._onUpdate0_value as ((value0: FormCallbackInfo) => void) | undefined))
    }
    public size(value: FormSize | undefined): this {
        this._size_flag = true
        this._size0_value = value
        return this
    }
    public moduleName(value: string | undefined): this {
        this._moduleName_flag = true
        this._moduleName0_value = value
        return this
    }
    public dimension(value: FormDimension | undefined): this {
        this._dimension_flag = true
        this._dimension0_value = value
        return this
    }
    public allowUpdate(value: boolean | undefined): this {
        this._allowUpdate_flag = true
        this._allowUpdate0_value = value
        return this
    }
    public visibility(value: Visibility | undefined): this {
        this._visibility_flag = true
        this._visibility0_value = value
        return this
    }
    public onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        this._onAcquired_flag = true
        this._onAcquired0_value = value
        return this
    }
    public onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        this._onError_flag = true
        this._onError0_value = value
        return this
    }
    public onRouter(value: ((value0: Object) => void) | undefined): this {
        this._onRouter_flag = true
        this._onRouter0_value = value
        return this
    }
    public onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        this._onUninstall_flag = true
        this._onUninstall0_value = value
        return this
    }
    public onLoad(value: VoidCallback | undefined): this {
        this._onLoad_flag = true
        this._onLoad0_value = value
        return this
    }
    public onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        this._onUpdate_flag = true
        this._onUpdate0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class FormSize_serializer {
    public static write(buffer: SerializerBase, value: FormSize): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeFloat64(value_width)
        const value_height  = value.height
        valueSerializer.writeFloat64(value_height)
    }
    public static read(buffer: DeserializerBase): FormSize {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : double = valueDeserializer.readFloat64()
        const height_result : double = valueDeserializer.readFloat64()
        let value : FormSize = ({width: width_result, height: height_result} as FormSize)
        return value
    }
}
export class ErrorInformation_serializer {
    public static write(buffer: SerializerBase, value: ErrorInformation): void {
        let valueSerializer : SerializerBase = buffer
        const value_errcode  = value.errcode
        valueSerializer.writeInt32(value_errcode)
        const value_msg  = value.msg
        valueSerializer.writeString(value_msg)
    }
    public static read(buffer: DeserializerBase): ErrorInformation {
        let valueDeserializer : DeserializerBase = buffer
        const errcode_result : int32 = valueDeserializer.readInt32()
        const msg_result : string = (valueDeserializer.readString() as string)
        let value : ErrorInformation = ({errcode: errcode_result, msg: msg_result} as ErrorInformation)
        return value
    }
}
export class FormCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: FormCallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeInt64(value_id)
        const value_idString  = value.idString
        valueSerializer.writeString(value_idString)
    }
    public static read(buffer: DeserializerBase): FormCallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : int64 = valueDeserializer.readInt64()
        const idString_result : string = (valueDeserializer.readString() as string)
        let value : FormCallbackInfo = ({id: id_result, idString: idString_result} as FormCallbackInfo)
        return value
    }
}
export class FormInfo_serializer {
    public static write(buffer: SerializerBase, value: FormInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        let value_id_type : int32 = RuntimeType.UNDEFINED
        value_id_type = runtimeType(value_id)
        if (RuntimeType.NUMBER == value_id_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_id_0  = value_id as int64
            valueSerializer.writeInt64(value_id_0)
        }
        else if (RuntimeType.STRING == value_id_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_id_1  = value_id as string
            valueSerializer.writeString(value_id_1)
        }
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_bundle  = value.bundle
        valueSerializer.writeString(value_bundle)
        const value_ability  = value.ability
        valueSerializer.writeString(value_ability)
        const value_module  = value.module
        valueSerializer.writeString(value_module)
        const value_dimension  = value.dimension
        let value_dimension_type : int32 = RuntimeType.UNDEFINED
        value_dimension_type = runtimeType(value_dimension)
        valueSerializer.writeInt8((value_dimension_type).toChar())
        if ((value_dimension_type) != (RuntimeType.UNDEFINED)) {
            const value_dimension_value  = (value_dimension as FormDimension)
            valueSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(value_dimension_value))
        }
        const value_temporary  = value.temporary
        let value_temporary_type : int32 = RuntimeType.UNDEFINED
        value_temporary_type = runtimeType(value_temporary)
        valueSerializer.writeInt8((value_temporary_type).toChar())
        if ((value_temporary_type) != (RuntimeType.UNDEFINED)) {
            const value_temporary_value  = value_temporary!
            valueSerializer.writeBoolean(value_temporary_value)
        }
        const value_want  = value.want
        let value_want_type : int32 = RuntimeType.UNDEFINED
        value_want_type = runtimeType(value_want)
        valueSerializer.writeInt8((value_want_type).toChar())
        if ((value_want_type) != (RuntimeType.UNDEFINED)) {
            const value_want_value  = value_want!
            Want_serializer.write(valueSerializer, value_want_value)
        }
        const value_renderingMode  = value.renderingMode
        let value_renderingMode_type : int32 = RuntimeType.UNDEFINED
        value_renderingMode_type = runtimeType(value_renderingMode)
        valueSerializer.writeInt8((value_renderingMode_type).toChar())
        if ((value_renderingMode_type) != (RuntimeType.UNDEFINED)) {
            const value_renderingMode_value  = (value_renderingMode as FormRenderingMode)
            valueSerializer.writeInt32(TypeChecker.FormRenderingMode_ToNumeric(value_renderingMode_value))
        }
        const value_shape  = value.shape
        let value_shape_type : int32 = RuntimeType.UNDEFINED
        value_shape_type = runtimeType(value_shape)
        valueSerializer.writeInt8((value_shape_type).toChar())
        if ((value_shape_type) != (RuntimeType.UNDEFINED)) {
            const value_shape_value  = (value_shape as FormShape)
            valueSerializer.writeInt32(TypeChecker.FormShape_ToNumeric(value_shape_value))
        }
    }
    public static read(buffer: DeserializerBase): FormInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_buf_selector : int32 = valueDeserializer.readInt8()
        let id_buf : int64 | string | undefined
        if (id_buf_selector == (0).toChar()) {
            id_buf = valueDeserializer.readInt64()
        }
        else if (id_buf_selector == (1).toChar()) {
            id_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for id_buf has to be chosen through deserialisation.")
        }
        const id_result : int64 | string = (id_buf as int64 | string)
        const name_result : string = (valueDeserializer.readString() as string)
        const bundle_result : string = (valueDeserializer.readString() as string)
        const ability_result : string = (valueDeserializer.readString() as string)
        const module_result : string = (valueDeserializer.readString() as string)
        const dimension_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dimension_buf : FormDimension | undefined
        if ((dimension_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dimension_buf = TypeChecker.FormDimension_FromNumeric(valueDeserializer.readInt32())
        }
        const dimension_result : FormDimension | undefined = dimension_buf
        const temporary_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let temporary_buf : boolean | undefined
        if ((temporary_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            temporary_buf = valueDeserializer.readBoolean()
        }
        const temporary_result : boolean | undefined = temporary_buf
        const want_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let want_buf : Want | undefined
        if ((want_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            want_buf = Want_serializer.read(valueDeserializer)
        }
        const want_result : Want | undefined = want_buf
        const renderingMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let renderingMode_buf : FormRenderingMode | undefined
        if ((renderingMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            renderingMode_buf = TypeChecker.FormRenderingMode_FromNumeric(valueDeserializer.readInt32())
        }
        const renderingMode_result : FormRenderingMode | undefined = renderingMode_buf
        const shape_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shape_buf : FormShape | undefined
        if ((shape_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            shape_buf = TypeChecker.FormShape_FromNumeric(valueDeserializer.readInt32())
        }
        const shape_result : FormShape | undefined = shape_buf
        let value : FormInfo = ({id: id_result, name: name_result, bundle: bundle_result, ability: ability_result, module: module_result, dimension: dimension_result, temporary: temporary_result, want: want_result, renderingMode: renderingMode_result, shape: shape_result} as FormInfo)
        return value
    }
}
