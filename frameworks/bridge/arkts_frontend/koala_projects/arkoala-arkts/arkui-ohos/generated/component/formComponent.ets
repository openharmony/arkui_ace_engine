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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, ArkCommonMethodComponent } from './common'
import { Visibility } from './enums'
import { VoidCallback } from './units'
import { AttributeModifier, extractors, hookFormComponentAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { default as Want } from '@ohos.app.ability.Want'
import { FormComponentModifier } from './../FormComponentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { Want_serializer } from './../framework/ohos.app.ability.Want'
export class ArkFormComponentPeer extends ArkCommonMethodPeer {
    attributeSet?: FormComponentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFormComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FormComponent_construct(peerId, flags)
        const _peer  = new ArkFormComponentPeer(_peerPtr, peerId, 'FormComponent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFormComponentOptionsAttribute(formInfo: FormInfo): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FormInfo_serializer.write(thisSerializer, formInfo)
        ArkUIGeneratedNativeModule._FormComponentInterface_setFormComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSizeAttribute(value: FormSize): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FormSize_serializer.write(thisSerializer, value)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FormComponentAttribute_setVisibility(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnAcquiredAttribute(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): void {
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
    setOnErrorAttribute(value: arkui_component_common_Callback<ErrorInformation, void> | undefined): void {
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
    setOnRouterAttribute(value: arkui_component_common_Callback<Object, void> | undefined): void {
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
    setOnUninstallAttribute(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): void {
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
    setOnUpdateAttribute(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): void {
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
    Dimension_1_2 = 0,
    Dimension_2_2 = 1,
    Dimension_2_4 = 2,
    Dimension_4_4 = 3,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9,
    DIMENSION_1_2 = 0,
    DIMENSION_2_2 = 1,
    DIMENSION_2_4 = 2,
    DIMENSION_4_4 = 3,
    DIMENSION_1_1_DUMMY = 6,
    DIMENSION_6_4_DUMMY = 7,
    DIMENSION_2_3_DUMMY = 8,
    DIMENSION_3_3_DUMMY = 9
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
    setFormComponentOptions(formInfo: FormInfo): this {
        throw new Error('Unimplemented method setFormComponentOptions')
    }
    size(value: FormSize): this
    moduleName(value: string | undefined): this {
        throw new Error('Unimplemented method moduleName')
    }
    dimension(value: FormDimension | undefined): this {
        throw new Error('Unimplemented method dimension')
    }
    allowUpdate(value: boolean | undefined): this {
        throw new Error('Unimplemented method allowUpdate')
    }
    visibility(value: Visibility | undefined): this
    onAcquired(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        throw new Error('Unimplemented method onAcquired')
    }
    onError(value: arkui_component_common_Callback<ErrorInformation, void> | undefined): this {
        throw new Error('Unimplemented method onError')
    }
    onRouter(value: arkui_component_common_Callback<Object, void> | undefined): this {
        throw new Error('Unimplemented method onRouter')
    }
    onUninstall(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        throw new Error('Unimplemented method onUninstall')
    }
    onLoad(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onLoad')
    }
    onUpdate(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        throw new Error('Unimplemented method onUpdate')
    }
    attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkFormComponentComponent extends ArkCommonMethodComponent implements FormComponentAttribute {
    getPeer(): ArkFormComponentPeer {
        return (this.peer as ArkFormComponentPeer)
    }
    public setFormComponentOptions(formInfo: FormInfo): this {
        if (this.checkPriority('setFormComponentOptions')) {
            const formInfo_casted = formInfo as (FormInfo)
            this.getPeer()?.setFormComponentOptionsAttribute(formInfo_casted)
            this.applyOptionsFinish('FormComponentAttribute');
            return this
        }
        return this
    }
    public size(value: FormSize): this {
        if (this.checkPriority('size')) {
            const value_casted = value as (FormSize)
            this.getPeer()?.setSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public moduleName(value: string | undefined): this {
        if (this.checkPriority('moduleName')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setModuleNameAttribute(value_casted)
            return this
        }
        return this
    }
    public dimension(value: FormDimension | undefined): this {
        if (this.checkPriority('dimension')) {
            const value_casted = value as (FormDimension | undefined)
            this.getPeer()?.setDimensionAttribute(value_casted)
            return this
        }
        return this
    }
    public allowUpdate(value: boolean | undefined): this {
        if (this.checkPriority('allowUpdate')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAllowUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public visibility(value: Visibility | undefined): this {
        if (this.checkPriority('visibility')) {
            const value_casted = value as (Visibility | undefined)
            this.getPeer()?.setVisibilityAttribute(value_casted)
            return this
        }
        return this
    }
    public onAcquired(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (this.checkPriority('onAcquired')) {
            const value_casted = value as (arkui_component_common_Callback<FormCallbackInfo, void> | undefined)
            this.getPeer()?.setOnAcquiredAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: arkui_component_common_Callback<ErrorInformation, void> | undefined): this {
        if (this.checkPriority('onError')) {
            const value_casted = value as (arkui_component_common_Callback<ErrorInformation, void> | undefined)
            this.getPeer()?.setOnErrorAttribute(value_casted)
            return this
        }
        return this
    }
    public onRouter(value: arkui_component_common_Callback<Object, void> | undefined): this {
        if (this.checkPriority('onRouter')) {
            const value_casted = value as (arkui_component_common_Callback<Object, void> | undefined)
            this.getPeer()?.setOnRouterAttribute(value_casted)
            return this
        }
        return this
    }
    public onUninstall(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (this.checkPriority('onUninstall')) {
            const value_casted = value as (arkui_component_common_Callback<FormCallbackInfo, void> | undefined)
            this.getPeer()?.setOnUninstallAttribute(value_casted)
            return this
        }
        return this
    }
    public onLoad(value: VoidCallback | undefined): this {
        if (this.checkPriority('onLoad')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnLoadAttribute(value_casted)
            return this
        }
        return this
    }
    public onUpdate(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (this.checkPriority('onUpdate')) {
            const value_casted = value as (arkui_component_common_Callback<FormCallbackInfo, void> | undefined)
            this.getPeer()?.setOnUpdateAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookFormComponentAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function FormComponentImpl(
    @memo @memo_skip
    style: ((attributes: FormComponentAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkFormComponentComponent>((): ArkFormComponentComponent => {
        return new ArkFormComponentComponent()
    })
    NodeAttach<ArkFormComponentPeer>((): ArkFormComponentPeer => ArkFormComponentPeer.create(receiver), (_: ArkFormComponentPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForIdForIdx0  = valueHolderForId as int64
            valueSerializer.writeInt64(valueHolderForIdForIdx0)
        } else if (valueHolderForId instanceof string) {
            valueSerializer.writeInt8((1).toByte())
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
            valueSerializer.writeInt32(valueHolderForDimensionTmpValue.valueOf())
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
            valueSerializer.writeInt32(valueHolderForRenderingModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape  = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue  = (valueHolderForShape as FormShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FormInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let idTmpBuf : int64 | string | undefined
        if (idTmpBufUnionSelector == (0).toByte()) {
            idTmpBuf = valueDeserializer.readInt64()
        } else if (idTmpBufUnionSelector == (1).toByte()) {
            idTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error('One of the branches for idTmpBuf has to be chosen through deserialisation.')
        }
        const idTmpResult : int64 | string = (idTmpBuf as int64 | string)
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const bundleTmpResult : string = (valueDeserializer.readString() as string)
        const abilityTmpResult : string = (valueDeserializer.readString() as string)
        const moduleTmpResult : string = (valueDeserializer.readString() as string)
        const dimensionTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dimensionTmpBuf : FormDimension | undefined = undefined
        if ((dimensionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dimensionTmpBuf = FormDimension.fromValue(valueDeserializer.readInt32())
        }
        const dimensionTmpResult : FormDimension | undefined = dimensionTmpBuf
        const temporaryTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let temporaryTmpBuf : boolean | undefined = undefined
        if ((temporaryTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            temporaryTmpBuf = valueDeserializer.readBoolean()
        }
        const temporaryTmpResult : boolean | undefined = temporaryTmpBuf
        const wantTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wantTmpBuf : Want | undefined = undefined
        if ((wantTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wantTmpBuf = (Want_serializer.read(valueDeserializer) as Want)
        }
        const wantTmpResult : Want | undefined = wantTmpBuf
        const renderingModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let renderingModeTmpBuf : FormRenderingMode | undefined = undefined
        if ((renderingModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            renderingModeTmpBuf = FormRenderingMode.fromValue(valueDeserializer.readInt32())
        }
        const renderingModeTmpResult : FormRenderingMode | undefined = renderingModeTmpBuf
        const shapeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let shapeTmpBuf : FormShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = FormShape.fromValue(valueDeserializer.readInt32())
        }
        const shapeTmpResult : FormShape | undefined = shapeTmpBuf
        let value : FormInfo = ({id: idTmpResult, name: nameTmpResult, bundle: bundleTmpResult, ability: abilityTmpResult, module: moduleTmpResult, dimension: dimensionTmpResult, temporary: temporaryTmpResult, want: wantTmpResult, renderingMode: renderingModeTmpResult, shape: shapeTmpResult} as FormInfo)
        return value
    }
}
