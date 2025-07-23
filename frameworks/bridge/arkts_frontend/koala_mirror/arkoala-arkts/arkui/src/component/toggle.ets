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
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ContentModifier, AttributeModifier, hookToggleContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { ResourceColor } from "./units"
import { Color } from "./enums"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkTogglePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTogglePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(peerId, flags)
        const _peer  = new ArkTogglePeer(_peerPtr, peerId, "Toggle", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setToggleOptionsAttribute(options: ToggleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ToggleOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ToggleInterface_setToggleOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((value0: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<ToggleConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwitchPointColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSwitchPointColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSwitchStyleAttribute(value: SwitchStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            SwitchStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ToggleAttribute_setSwitchStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_isOnAttribute(callback_: ((isOn: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._ToggleAttribute_set_onChangeEvent_isOn(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ToggleType {
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2
}
export interface SwitchStyle {
    pointRadius?: number | Resource;
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: number | Resource;
}
export interface ToggleConfiguration extends CommonConfiguration<ToggleConfiguration> {
    isOn: boolean;
    toggleEnabled: boolean;
    triggerChange: ((value0: boolean) => void);
}
export interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean | undefined;
}
export interface ToggleAttribute extends CommonMethod {
    onChange(value: ((value0: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    switchPointColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method switchPointColor")
    }
    switchStyle(value: SwitchStyle | undefined): this {
        throw new Error("Unimplemented method switchStyle")
    }
    _onChangeEvent_isOn(callback_: ((isOn: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_isOn")
    }
    attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkToggleStyle extends ArkCommonMethodStyle implements ToggleAttribute {
    onChange_value?: ((value0: boolean) => void) | undefined
    contentModifier_value?: ContentModifier<ToggleConfiguration> | undefined
    selectedColor_value?: ResourceColor | undefined
    switchPointColor_value?: ResourceColor | undefined
    switchStyle_value?: SwitchStyle | undefined
    attributeModifier_value?: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined
    public onChange(value: ((value0: boolean) => void) | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        return this
    }
    public _onChangeEvent_isOn(callback_: ((isOn: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ToggleAttribute): void {
        super.apply(target)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.switchPointColor_value !== undefined)
            target.switchPointColor(this.switchPointColor_value!)
        if (this.switchStyle_value !== undefined)
            target.switchStyle(this.switchStyle_value!)
    }
}

export class ArkToggleComponent extends ArkCommonMethodComponent implements ToggleAttribute {
    getPeer(): ArkTogglePeer {
        return (this.peer as ArkTogglePeer)
    }
    public setToggleOptions(options: ToggleOptions): this {
        if (this.checkPriority("setToggleOptions")) {
            const options_casted = options as (ToggleOptions)
            this.getPeer()?.setToggleOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public onChange(value: ((value0: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((value0: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<ToggleConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("switchPointColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSwitchPointColorAttribute(value_casted)
            return this
        }
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        if (this.checkPriority("switchStyle")) {
            const value_casted = value as (SwitchStyle | undefined)
            this.getPeer()?.setSwitchStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_isOn(callback_: ((isOn: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_isOn")) {
            const callback__casted = callback_ as (((isOn: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_isOnAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withToggleStyle(receiver: ToggleAttribute, modifier: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkToggleStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Toggle")
// export function Toggle(
//     options: ToggleOptions,
//     @memo
//     content_?: () => void,
// ): ToggleAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Toggle(
    @memo
    style: ((attributes: ToggleAttribute) => void) | undefined,
    options: ToggleOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkToggleComponent>((): ArkToggleComponent => {
        return new ArkToggleComponent()
    })
    NodeAttach<ArkTogglePeer>((): ArkTogglePeer => ArkTogglePeer.create(receiver), (_: ArkTogglePeer): void => {
        receiver.setToggleOptions(options)
        style?.(receiver)
        withToggleStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkToggleSet extends ArkCommonMethodSet implements ToggleAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onChange_flag?: boolean
    _onChange0_value?: ((value0: boolean) => void) | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<ToggleConfiguration> | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | undefined
    _switchPointColor_flag?: boolean
    _switchPointColor0_value?: ResourceColor | undefined
    _switchStyle_flag?: boolean
    _switchStyle0_value?: SwitchStyle | undefined
    __onChangeEvent_isOn_flag?: boolean
    __onChangeEvent_isOn0_value?: ((isOn: boolean | undefined) => void)
    applyModifierPatch(component: ToggleAttribute): void {
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as ((value0: boolean) => void) | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<ToggleConfiguration> | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | undefined))
        if (this._switchPointColor_flag)
            component.switchPointColor((this._switchPointColor0_value as ResourceColor | undefined))
        if (this._switchStyle_flag)
            component.switchStyle((this._switchStyle0_value as SwitchStyle | undefined))
    }
    public onChange(value: ((value0: boolean) => void) | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
        return this
    }
    public switchPointColor(value: ResourceColor | undefined): this {
        this._switchPointColor_flag = true
        this._switchPointColor0_value = value
        return this
    }
    public switchStyle(value: SwitchStyle | undefined): this {
        this._switchStyle_flag = true
        this._switchStyle0_value = value
        return this
    }
    public _onChangeEvent_isOn(callback_: ((isOn: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ToggleConfiguration_serializer {
    public static write(buffer: SerializerBase, value: ToggleConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_isOn  = value.isOn
        valueSerializer.writeBoolean(value_isOn)
        const value_toggleEnabled  = value.toggleEnabled
        valueSerializer.writeBoolean(value_toggleEnabled)
        const value_triggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(value_triggerChange)
    }
    public static read(buffer: DeserializerBase): ToggleConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<ToggleConfiguration> = (valueDeserializer.readObject() as ContentModifier<ToggleConfiguration>)
        const isOn_result : boolean = valueDeserializer.readBoolean()
        const toggleEnabled_result : boolean = valueDeserializer.readBoolean()
        const triggerChange_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const triggerChange_buf_call : KPointer = valueDeserializer.readPointer()
        const triggerChange_buf_callSync : KPointer = valueDeserializer.readPointer()
        const triggerChange_result : ((value0: boolean) => void) = (value0: boolean):void => { 
    const triggerChange_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    triggerChange_buf_argsSerializer.writeInt32(triggerChange_buf_resource.resourceId);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_call);
    triggerChange_buf_argsSerializer.writePointer(triggerChange_buf_callSync);
    triggerChange_buf_argsSerializer.writeBoolean(value0);
    InteropNativeModule._CallCallback(313269291, triggerChange_buf_argsSerializer.asBuffer(), triggerChange_buf_argsSerializer.length());
    triggerChange_buf_argsSerializer.release();
    return; }
        let value : ToggleConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, isOn: isOn_result, toggleEnabled: toggleEnabled_result, triggerChange: triggerChange_result} as ToggleConfiguration)
        return value
    }
}
export class ToggleOptions_serializer {
    public static write(buffer: SerializerBase, value: ToggleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.ToggleType_ToNumeric(value_type))
        const value_isOn  = value.isOn
        let value_isOn_type : int32 = RuntimeType.UNDEFINED
        value_isOn_type = runtimeType(value_isOn)
        valueSerializer.writeInt8((value_isOn_type).toChar())
        if ((value_isOn_type) != (RuntimeType.UNDEFINED)) {
            const value_isOn_value  = value_isOn!
            valueSerializer.writeBoolean(value_isOn_value)
        }
    }
    public static read(buffer: DeserializerBase): ToggleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : ToggleType = TypeChecker.ToggleType_FromNumeric(valueDeserializer.readInt32())
        const isOn_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isOn_buf : boolean | undefined
        if ((isOn_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            isOn_buf = valueDeserializer.readBoolean()
        }
        const isOn_result : boolean | undefined = isOn_buf
        let value : ToggleOptions = ({type: type_result, isOn: isOn_result} as ToggleOptions)
        return value
    }
}
export class SwitchStyle_serializer {
    public static write(buffer: SerializerBase, value: SwitchStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_pointRadius  = value.pointRadius
        let value_pointRadius_type : int32 = RuntimeType.UNDEFINED
        value_pointRadius_type = runtimeType(value_pointRadius)
        valueSerializer.writeInt8((value_pointRadius_type).toChar())
        if ((value_pointRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_pointRadius_value  = value_pointRadius!
            let value_pointRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_pointRadius_value_type = runtimeType(value_pointRadius_value)
            if (RuntimeType.NUMBER == value_pointRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_pointRadius_value_0  = value_pointRadius_value as number
                valueSerializer.writeNumber(value_pointRadius_value_0)
            }
            else if (RuntimeType.OBJECT == value_pointRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_pointRadius_value_1  = value_pointRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_pointRadius_value_1)
            }
        }
        const value_unselectedColor  = value.unselectedColor
        let value_unselectedColor_type : int32 = RuntimeType.UNDEFINED
        value_unselectedColor_type = runtimeType(value_unselectedColor)
        valueSerializer.writeInt8((value_unselectedColor_type).toChar())
        if ((value_unselectedColor_type) != (RuntimeType.UNDEFINED)) {
            const value_unselectedColor_value  = value_unselectedColor!
            let value_unselectedColor_value_type : int32 = RuntimeType.UNDEFINED
            value_unselectedColor_value_type = runtimeType(value_unselectedColor_value)
            if (TypeChecker.isColor(value_unselectedColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_unselectedColor_value_0  = value_unselectedColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_unselectedColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_unselectedColor_value_1  = value_unselectedColor_value as number
                valueSerializer.writeNumber(value_unselectedColor_value_1)
            }
            else if (RuntimeType.STRING == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_unselectedColor_value_2  = value_unselectedColor_value as string
                valueSerializer.writeString(value_unselectedColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_unselectedColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_unselectedColor_value_3  = value_unselectedColor_value as Resource
                Resource_serializer.write(valueSerializer, value_unselectedColor_value_3)
            }
        }
        const value_pointColor  = value.pointColor
        let value_pointColor_type : int32 = RuntimeType.UNDEFINED
        value_pointColor_type = runtimeType(value_pointColor)
        valueSerializer.writeInt8((value_pointColor_type).toChar())
        if ((value_pointColor_type) != (RuntimeType.UNDEFINED)) {
            const value_pointColor_value  = value_pointColor!
            let value_pointColor_value_type : int32 = RuntimeType.UNDEFINED
            value_pointColor_value_type = runtimeType(value_pointColor_value)
            if (TypeChecker.isColor(value_pointColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_pointColor_value_0  = value_pointColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_pointColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_pointColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_pointColor_value_1  = value_pointColor_value as number
                valueSerializer.writeNumber(value_pointColor_value_1)
            }
            else if (RuntimeType.STRING == value_pointColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_pointColor_value_2  = value_pointColor_value as string
                valueSerializer.writeString(value_pointColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_pointColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_pointColor_value_3  = value_pointColor_value as Resource
                Resource_serializer.write(valueSerializer, value_pointColor_value_3)
            }
        }
        const value_trackBorderRadius  = value.trackBorderRadius
        let value_trackBorderRadius_type : int32 = RuntimeType.UNDEFINED
        value_trackBorderRadius_type = runtimeType(value_trackBorderRadius)
        valueSerializer.writeInt8((value_trackBorderRadius_type).toChar())
        if ((value_trackBorderRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_trackBorderRadius_value  = value_trackBorderRadius!
            let value_trackBorderRadius_value_type : int32 = RuntimeType.UNDEFINED
            value_trackBorderRadius_value_type = runtimeType(value_trackBorderRadius_value)
            if (RuntimeType.NUMBER == value_trackBorderRadius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_trackBorderRadius_value_0  = value_trackBorderRadius_value as number
                valueSerializer.writeNumber(value_trackBorderRadius_value_0)
            }
            else if (RuntimeType.OBJECT == value_trackBorderRadius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_trackBorderRadius_value_1  = value_trackBorderRadius_value as Resource
                Resource_serializer.write(valueSerializer, value_trackBorderRadius_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): SwitchStyle {
        let valueDeserializer : DeserializerBase = buffer
        const pointRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointRadius_buf : number | Resource | undefined
        if ((pointRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const pointRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let pointRadius_buf_ : number | Resource | undefined
            if (pointRadius_buf__selector == (0).toChar()) {
                pointRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (pointRadius_buf__selector == (1).toChar()) {
                pointRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for pointRadius_buf_ has to be chosen through deserialisation.")
            }
            pointRadius_buf = (pointRadius_buf_ as number | Resource)
        }
        const pointRadius_result : number | Resource | undefined = pointRadius_buf
        const unselectedColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let unselectedColor_buf : ResourceColor | undefined
        if ((unselectedColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const unselectedColor_buf__selector : int32 = valueDeserializer.readInt8()
            let unselectedColor_buf_ : Color | number | string | Resource | undefined
            if (unselectedColor_buf__selector == (0).toChar()) {
                unselectedColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (unselectedColor_buf__selector == (1).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (unselectedColor_buf__selector == (2).toChar()) {
                unselectedColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (unselectedColor_buf__selector == (3).toChar()) {
                unselectedColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for unselectedColor_buf_ has to be chosen through deserialisation.")
            }
            unselectedColor_buf = (unselectedColor_buf_ as Color | number | string | Resource)
        }
        const unselectedColor_result : ResourceColor | undefined = unselectedColor_buf
        const pointColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let pointColor_buf : ResourceColor | undefined
        if ((pointColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const pointColor_buf__selector : int32 = valueDeserializer.readInt8()
            let pointColor_buf_ : Color | number | string | Resource | undefined
            if (pointColor_buf__selector == (0).toChar()) {
                pointColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (pointColor_buf__selector == (1).toChar()) {
                pointColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (pointColor_buf__selector == (2).toChar()) {
                pointColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (pointColor_buf__selector == (3).toChar()) {
                pointColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for pointColor_buf_ has to be chosen through deserialisation.")
            }
            pointColor_buf = (pointColor_buf_ as Color | number | string | Resource)
        }
        const pointColor_result : ResourceColor | undefined = pointColor_buf
        const trackBorderRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let trackBorderRadius_buf : number | Resource | undefined
        if ((trackBorderRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const trackBorderRadius_buf__selector : int32 = valueDeserializer.readInt8()
            let trackBorderRadius_buf_ : number | Resource | undefined
            if (trackBorderRadius_buf__selector == (0).toChar()) {
                trackBorderRadius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (trackBorderRadius_buf__selector == (1).toChar()) {
                trackBorderRadius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for trackBorderRadius_buf_ has to be chosen through deserialisation.")
            }
            trackBorderRadius_buf = (trackBorderRadius_buf_ as number | Resource)
        }
        const trackBorderRadius_result : number | Resource | undefined = trackBorderRadius_buf
        let value : SwitchStyle = ({pointRadius: pointRadius_result, unselectedColor: unselectedColor_result, pointColor: pointColor_result, trackBorderRadius: trackBorderRadius_result} as SwitchStyle)
        return value
    }
}
