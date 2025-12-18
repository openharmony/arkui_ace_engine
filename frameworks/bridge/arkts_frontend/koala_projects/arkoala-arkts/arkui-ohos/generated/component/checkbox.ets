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
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, resourceFinalizerRegister, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, CommonConfiguration, Callback as arkui_component_common_Callback, ArkCommonMethodComponent } from './common'
import { global_resource_Resource_serializer } from './../framework/resource'
import { MarkStyle_serializer, ResourceColor, Resource as arkui_component_units_Resource, MarkStyle } from './units'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { Color as arkui_component_enums_Color, CheckBoxShape } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ContentModifier, AttributeModifier, hookCheckBoxContentModifier, hookCheckboxAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { CustomBuilder } from './builder'
import { CheckboxModifier } from './../CheckboxModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkCheckboxPeer extends ArkCommonMethodPeer {
    attributeSet?: CheckboxModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCheckboxPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Checkbox_construct(peerId, flags)
        const _peer  = new ArkCheckboxPeer(_peerPtr, peerId, 'Checkbox', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCheckboxOptionsAttribute(options?: CheckboxOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CheckboxOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxInterface_setCheckboxOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShapeAttribute(value: CheckBoxShape | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CheckBoxShape)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUnselectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkAttribute(value: MarkStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            MarkStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setMark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnCheckboxChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CheckboxOptions {
    name?: string;
    group?: string;
    indicatorBuilder?: CustomBuilder;
}
export interface CheckBoxConfiguration extends CommonConfiguration<CheckBoxConfiguration> {
    name: string;
    selected: boolean;
    triggerChange: arkui_component_common_Callback<boolean, void>;
}
export type OnCheckboxChangeCallback = (value: boolean) => void;
export interface CheckboxAttribute extends CommonMethod {
    setCheckboxOptions(options?: CheckboxOptions): this {
        throw new Error('Unimplemented method setCheckboxOptions')
    }
    select(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error('Unimplemented method select')
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedColor')
    }
    shape(value: CheckBoxShape | undefined): this {
        throw new Error('Unimplemented method shape')
    }
    unselectedColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method unselectedColor')
    }
    mark(value: MarkStyle | undefined): this {
        throw new Error('Unimplemented method mark')
    }
    onChange(value: OnCheckboxChangeCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkCheckboxComponent extends ArkCommonMethodComponent implements CheckboxAttribute {
    getPeer(): ArkCheckboxPeer {
        return (this.peer as ArkCheckboxPeer)
    }
    public setCheckboxOptions(options?: CheckboxOptions): this {
        if (this.checkPriority('setCheckboxOptions')) {
            const options_casted = options as (CheckboxOptions | undefined)
            this.getPeer()?.setCheckboxOptionsAttribute(options_casted)
            this.applyOptionsFinish('CheckboxAttribute');
            return this
        }
        return this
    }
    public select(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority('select')) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public shape(value: CheckBoxShape | undefined): this {
        if (this.checkPriority('shape')) {
            const value_casted = value as (CheckBoxShape | undefined)
            this.getPeer()?.setShapeAttribute(value_casted)
            return this
        }
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('unselectedColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        if (this.checkPriority('mark')) {
            const value_casted = value as (MarkStyle | undefined)
            this.getPeer()?.setMarkAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnCheckboxChangeCallback | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (OnCheckboxChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookCheckBoxContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookCheckboxAttributeModifier(this, value);
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
export function CheckboxImpl(
    @memo @memo_skip
    style: ((attributes: CheckboxAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkCheckboxComponent>((): ArkCheckboxComponent => {
        return new ArkCheckboxComponent()
    })
    NodeAttach<ArkCheckboxPeer>((): ArkCheckboxPeer => ArkCheckboxPeer.create(receiver), (_: ArkCheckboxPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class CheckBoxConfiguration_serializer {
    public static write(buffer: SerializerBase, value: CheckBoxConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForName  = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForSelected  = value.selected
        valueSerializer.writeBoolean(valueHolderForSelected)
        const valueHolderForTriggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(valueHolderForTriggerChange)
    }
    public static read(buffer: DeserializerBase): CheckBoxConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<CheckBoxConfiguration> = (valueDeserializer.readObject() as ContentModifier<CheckBoxConfiguration>)
        const nameTmpResult : string = (valueDeserializer.readString() as string)
        const selectedTmpResult : boolean = valueDeserializer.readBoolean()
        const triggerChangeTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChangeTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const triggerChangeTmpBufClosure  = (data: boolean):void => {
            const triggerChangeTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            triggerChangeTmpBufBufArgsSerializer.writeInt32(triggerChangeTmpBufBufResource.resourceId);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCall);
            triggerChangeTmpBufBufArgsSerializer.writePointer(triggerChangeTmpBufBufCallSync);
            triggerChangeTmpBufBufArgsSerializer.writeBoolean(data);
            InteropNativeModule._CallCallbackSync(10, -1691789173, triggerChangeTmpBufBufArgsSerializer.asBuffer(), triggerChangeTmpBufBufArgsSerializer.length());
            triggerChangeTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(triggerChangeTmpBufClosure, triggerChangeTmpBufBufResource)
        const triggerChangeTmpResult : arkui_component_common_Callback<boolean, void> = triggerChangeTmpBufClosure
        let value : CheckBoxConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, name: nameTmpResult, selected: selectedTmpResult, triggerChange: triggerChangeTmpResult} as CheckBoxConfiguration)
        return value
    }
}
export class CheckboxOptions_serializer {
    public static write(buffer: SerializerBase, value: CheckboxOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        if (valueHolderForName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNameTmpValue  = valueHolderForName!
            valueSerializer.writeString(valueHolderForNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGroup  = value.group
        if (valueHolderForGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGroupTmpValue  = valueHolderForGroup!
            valueSerializer.writeString(valueHolderForGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIndicatorBuilder  = value.indicatorBuilder
        if (valueHolderForIndicatorBuilder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIndicatorBuilderTmpValue  = valueHolderForIndicatorBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForIndicatorBuilderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CheckboxOptions {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let nameTmpBuf : string | undefined = undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : string | undefined = nameTmpBuf
        const groupTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let groupTmpBuf : string | undefined = undefined
        if ((groupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            groupTmpBuf = (valueDeserializer.readString() as string)
        }
        const groupTmpResult : string | undefined = groupTmpBuf
        const indicatorBuilderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let indicatorBuilderTmpBuf : CustomBuilder | undefined = undefined
        if ((indicatorBuilderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const indicatorBuilderTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const indicatorBuilderTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const indicatorBuilderTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const indicatorBuilderTmpBufOptClosure  = ():void => {
                const indicatorBuilderTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                indicatorBuilderTmpBufOptBufArgsSerializer.writeInt32(indicatorBuilderTmpBufOptBufResource.resourceId);
                indicatorBuilderTmpBufOptBufArgsSerializer.writePointer(indicatorBuilderTmpBufOptBufCall);
                indicatorBuilderTmpBufOptBufArgsSerializer.writePointer(indicatorBuilderTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, indicatorBuilderTmpBufOptBufArgsSerializer.asBuffer(), indicatorBuilderTmpBufOptBufArgsSerializer.length());
                indicatorBuilderTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(indicatorBuilderTmpBufOptClosure, indicatorBuilderTmpBufOptBufResource)
            indicatorBuilderTmpBuf = indicatorBuilderTmpBufOptClosure
        }
        const indicatorBuilderTmpResult : CustomBuilder | undefined = indicatorBuilderTmpBuf
        let value : CheckboxOptions = ({name: nameTmpResult, group: groupTmpResult, indicatorBuilder: indicatorBuilderTmpResult} as CheckboxOptions)
        return value
    }
}
