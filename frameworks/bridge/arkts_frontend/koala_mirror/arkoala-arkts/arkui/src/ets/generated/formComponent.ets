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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Visibility } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Want, Want_serializer } from "./ohos.app.ability.Want"
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
    sizeAttribute(value: FormSize | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            FormSize_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_size(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    moduleNameAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_moduleName(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dimensionAttribute(value: FormDimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FormDimension)
            thisSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_dimension(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    allowUpdateAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_allowUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    visibilityAttribute(value: Visibility | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Visibility)
            thisSerializer.writeInt32(TypeChecker.Visibility_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_visibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onAcquiredAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onAcquired(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ((value0: FormError) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRouterAttribute(value: ((value0: Object | undefined) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onRouter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onUninstallAttribute(value: ((value0: FormCallbackInfo) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_onUninstall(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onLoadAttribute(value: (() => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
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
    DIMENSION_3_3 = 9,
    DIMENSION_3_4 = 10
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
    id: number | string;
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
    id: number;
    idString: string;
}
export interface FormSize {
    width: number;
    height: number;
}
export interface FormError {
    errcode: number;
    msg: string;
}
export interface FormComponentAttribute extends CommonMethod {
    size(value: FormSize | undefined): this
    moduleName(value: string | undefined): this
    dimension(value: FormDimension | undefined): this
    allowUpdate(value: boolean | undefined): this
    visibility(value: Visibility | undefined): this
    onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this
    onError(value: ((value0: FormError) => void) | undefined): this
    onRouter(value: ((value0: Object | undefined) => void) | undefined): this
    onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this
    onLoad(value: (() => void) | undefined): this
    attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkFormComponentStyle extends ArkCommonMethodStyle implements FormComponentAttribute {
    size_value?: FormSize | undefined
    moduleName_value?: string | undefined
    dimension_value?: FormDimension | undefined
    allowUpdate_value?: boolean | undefined
    visibility_value?: Visibility | undefined
    onAcquired_value?: ((value0: FormCallbackInfo) => void) | undefined
    onError_value?: ((value0: FormError) => void) | undefined
    onRouter_value?: ((value0: Object | undefined) => void) | undefined
    onUninstall_value?: ((value0: FormCallbackInfo) => void) | undefined
    onLoad_value?: (() => void) | undefined
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
    public onError(value: ((value0: FormError) => void) | undefined): this {
        return this
    }
    public onRouter(value: ((value0: Object | undefined) => void) | undefined): this {
        return this
    }
    public onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        return this
    }
    public onLoad(value: (() => void) | undefined): this {
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
    public onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onAcquired")) {
            const value_casted = value as (((value0: FormCallbackInfo) => void) | undefined)
            this.getPeer()?.onAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ((value0: FormError) => void) | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (((value0: FormError) => void) | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onRouter(value: ((value0: Object | undefined) => void) | undefined): this {
        if (this.checkPriority("onRouter")) {
            const value_casted = value as (((value0: Object | undefined) => void) | undefined)
            this.getPeer()?.onRouterAttribute(value_casted)
            return this
        }
        return this
    }
    public onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (this.checkPriority("onUninstall")) {
            const value_casted = value as (((value0: FormCallbackInfo) => void) | undefined)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("FormComponentImpl")
export function FormComponent(
    value: FormInfo,
    @memo
    content_?: () => void,
): FormComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function FormComponentImpl(
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

export class FormCallbackInfo_serializer {
    public static write(buffer: SerializerBase, value: FormCallbackInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_id  = value.id
        valueSerializer.writeNumber(value_id)
        const value_idString  = value.idString
        valueSerializer.writeString(value_idString)
    }
    public static read(buffer: DeserializerBase): FormCallbackInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_result : number = (valueDeserializer.readNumber() as number)
        const idString_result : string = (valueDeserializer.readString() as string)
        let value : FormCallbackInfo = ({id: id_result, idString: idString_result} as FormCallbackInfo)
        return value
    }
}
export class FormError_serializer {
    public static write(buffer: SerializerBase, value: FormError): void {
        let valueSerializer : SerializerBase = buffer
        const value_errcode  = value.errcode
        valueSerializer.writeNumber(value_errcode)
        const value_msg  = value.msg
        valueSerializer.writeString(value_msg)
    }
    public static read(buffer: DeserializerBase): FormError {
        let valueDeserializer : DeserializerBase = buffer
        const errcode_result : number = (valueDeserializer.readNumber() as number)
        const msg_result : string = (valueDeserializer.readString() as string)
        let value : FormError = ({errcode: errcode_result, msg: msg_result} as FormError)
        return value
    }
}
export class FormSize_serializer {
    public static write(buffer: SerializerBase, value: FormSize): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_height  = value.height
        valueSerializer.writeNumber(value_height)
    }
    public static read(buffer: DeserializerBase): FormSize {
        let valueDeserializer : DeserializerBase = buffer
        const width_result : number = (valueDeserializer.readNumber() as number)
        const height_result : number = (valueDeserializer.readNumber() as number)
        let value : FormSize = ({width: width_result, height: height_result} as FormSize)
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
            valueSerializer.writeInt8(0)
            const value_id_0  = value_id as number
            valueSerializer.writeNumber(value_id_0)
        }
        else if (RuntimeType.STRING == value_id_type) {
            valueSerializer.writeInt8(1)
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
        valueSerializer.writeInt8(value_dimension_type)
        if ((RuntimeType.UNDEFINED) != (value_dimension_type)) {
            const value_dimension_value  = (value_dimension as FormDimension)
            valueSerializer.writeInt32(TypeChecker.FormDimension_ToNumeric(value_dimension_value))
        }
        const value_temporary  = value.temporary
        let value_temporary_type : int32 = RuntimeType.UNDEFINED
        value_temporary_type = runtimeType(value_temporary)
        valueSerializer.writeInt8(value_temporary_type)
        if ((RuntimeType.UNDEFINED) != (value_temporary_type)) {
            const value_temporary_value  = value_temporary!
            valueSerializer.writeBoolean(value_temporary_value)
        }
        const value_want  = value.want
        let value_want_type : int32 = RuntimeType.UNDEFINED
        value_want_type = runtimeType(value_want)
        valueSerializer.writeInt8(value_want_type)
        if ((RuntimeType.UNDEFINED) != (value_want_type)) {
            const value_want_value  = value_want!
            Want_serializer.write(valueSerializer, value_want_value)
        }
        const value_renderingMode  = value.renderingMode
        let value_renderingMode_type : int32 = RuntimeType.UNDEFINED
        value_renderingMode_type = runtimeType(value_renderingMode)
        valueSerializer.writeInt8(value_renderingMode_type)
        if ((RuntimeType.UNDEFINED) != (value_renderingMode_type)) {
            const value_renderingMode_value  = (value_renderingMode as FormRenderingMode)
            valueSerializer.writeInt32(TypeChecker.FormRenderingMode_ToNumeric(value_renderingMode_value))
        }
        const value_shape  = value.shape
        let value_shape_type : int32 = RuntimeType.UNDEFINED
        value_shape_type = runtimeType(value_shape)
        valueSerializer.writeInt8(value_shape_type)
        if ((RuntimeType.UNDEFINED) != (value_shape_type)) {
            const value_shape_value  = (value_shape as FormShape)
            valueSerializer.writeInt32(TypeChecker.FormShape_ToNumeric(value_shape_value))
        }
    }
    public static read(buffer: DeserializerBase): FormInfo {
        let valueDeserializer : DeserializerBase = buffer
        const id_buf_selector : int32 = valueDeserializer.readInt8()
        let id_buf : number | string | undefined
        if (id_buf_selector == 0) {
            id_buf = (valueDeserializer.readNumber() as number)
        }
        else if (id_buf_selector == 1) {
            id_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for id_buf has to be chosen through deserialisation.")
        }
        const id_result : number | string = (id_buf as number | string)
        const name_result : string = (valueDeserializer.readString() as string)
        const bundle_result : string = (valueDeserializer.readString() as string)
        const ability_result : string = (valueDeserializer.readString() as string)
        const module_result : string = (valueDeserializer.readString() as string)
        const dimension_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dimension_buf : FormDimension | undefined
        if ((RuntimeType.UNDEFINED) != (dimension_buf_runtimeType))
        {
            dimension_buf = TypeChecker.FormDimension_FromNumeric(valueDeserializer.readInt32())
        }
        const dimension_result : FormDimension | undefined = dimension_buf
        const temporary_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let temporary_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (temporary_buf_runtimeType))
        {
            temporary_buf = valueDeserializer.readBoolean()
        }
        const temporary_result : boolean | undefined = temporary_buf
        const want_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let want_buf : Want | undefined
        if ((RuntimeType.UNDEFINED) != (want_buf_runtimeType))
        {
            want_buf = Want_serializer.read(valueDeserializer)
        }
        const want_result : Want | undefined = want_buf
        const renderingMode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let renderingMode_buf : FormRenderingMode | undefined
        if ((RuntimeType.UNDEFINED) != (renderingMode_buf_runtimeType))
        {
            renderingMode_buf = TypeChecker.FormRenderingMode_FromNumeric(valueDeserializer.readInt32())
        }
        const renderingMode_result : FormRenderingMode | undefined = renderingMode_buf
        const shape_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let shape_buf : FormShape | undefined
        if ((RuntimeType.UNDEFINED) != (shape_buf_runtimeType))
        {
            shape_buf = TypeChecker.FormShape_FromNumeric(valueDeserializer.readInt32())
        }
        const shape_result : FormShape | undefined = shape_buf
        let value : FormInfo = ({id: id_result, name: name_result, bundle: bundle_result, ability: ability_result, module: module_result, dimension: dimension_result, temporary: temporary_result, want: want_result, renderingMode: renderingMode_result, shape: shape_result} as FormInfo)
        return value
    }
}
