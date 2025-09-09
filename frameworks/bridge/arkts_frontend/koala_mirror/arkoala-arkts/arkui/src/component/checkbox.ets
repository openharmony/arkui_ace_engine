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
import { MarkStyle_serializer, ResourceColor, MarkStyle } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color, CheckBoxShape } from "./enums"
import { ContentModifier, AttributeModifier, hookCheckBoxContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkCheckboxPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCheckboxPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Checkbox_construct(peerId, flags)
        const _peer  = new ArkCheckboxPeer(_peerPtr, peerId, "Checkbox", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCheckboxOptionsAttribute(options?: CheckboxOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            CheckboxOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._CheckboxInterface_setCheckboxOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CheckboxAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShapeAttribute(value: CheckBoxShape | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CheckBoxShape)
            thisSerializer.writeInt32(TypeChecker.CheckBoxShape_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUnselectedColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._CheckboxAttribute_setUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkAttribute(value: MarkStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            MarkStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setMark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnCheckboxChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<CheckBoxConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectAttribute(callback_: ((select: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CheckboxAttribute_set_onChangeEvent_select(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    triggerChange: ((value0: boolean) => void);
}
export type OnCheckboxChangeCallback = (value: boolean) => void;
export interface CheckboxAttribute extends CommonMethod {
    select(value: boolean | undefined): this {
        throw new Error("Unimplemented method select")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    shape(value: CheckBoxShape | undefined): this {
        throw new Error("Unimplemented method shape")
    }
    unselectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method unselectedColor")
    }
    mark(value: MarkStyle | undefined): this {
        throw new Error("Unimplemented method mark")
    }
    onChange(value: OnCheckboxChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    _onChangeEvent_select(callback_: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_select")
    }
    attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCheckboxStyle extends ArkCommonMethodStyle implements CheckboxAttribute {
    select_value?: boolean | undefined
    selectedColor_value?: ResourceColor | undefined
    shape_value?: CheckBoxShape | undefined
    unselectedColor_value?: ResourceColor | undefined
    mark_value?: MarkStyle | undefined
    onChange_value?: OnCheckboxChangeCallback | undefined
    contentModifier_value?: ContentModifier<CheckBoxConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined
    public select(value: boolean | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public shape(value: CheckBoxShape | undefined): this {
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        return this
    }
    public onChange(value: OnCheckboxChangeCallback | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        return this
    }
    public _onChangeEvent_select(callback_: ((select: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: CheckboxAttribute): void {
        super.apply(target)
        if (this.select_value !== undefined)
            target.select(this.select_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.shape_value !== undefined)
            target.shape(this.shape_value!)
        if (this.unselectedColor_value !== undefined)
            target.unselectedColor(this.unselectedColor_value!)
        if (this.mark_value !== undefined)
            target.mark(this.mark_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}

export class ArkCheckboxComponent extends ArkCommonMethodComponent implements CheckboxAttribute {
    getPeer(): ArkCheckboxPeer {
        return (this.peer as ArkCheckboxPeer)
    }
    public setCheckboxOptions(options?: CheckboxOptions): this {
        if (this.checkPriority("setCheckboxOptions")) {
            const options_casted = options as (CheckboxOptions | undefined)
            this.getPeer()?.setCheckboxOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public select(value: boolean | undefined): this {
        if (this.checkPriority("select")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectAttribute(value_casted)
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
    public shape(value: CheckBoxShape | undefined): this {
        if (this.checkPriority("shape")) {
            const value_casted = value as (CheckBoxShape | undefined)
            this.getPeer()?.setShapeAttribute(value_casted)
            return this
        }
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("unselectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        if (this.checkPriority("mark")) {
            const value_casted = value as (MarkStyle | undefined)
            this.getPeer()?.setMarkAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: OnCheckboxChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnCheckboxChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<CheckBoxConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_select(callback_: ((select: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_select")) {
            const callback__casted = callback_ as (((select: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCheckboxStyle(receiver: CheckboxAttribute, modifier: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCheckboxStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Checkbox")
// export function Checkbox(
//     options?: CheckboxOptions,
//     @memo
//     content_?: () => void,
// ): CheckboxAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Checkbox(
    @memo
    style: ((attributes: CheckboxAttribute) => void) | undefined,
    options?: CheckboxOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCheckboxComponent>((): ArkCheckboxComponent => {
        return new ArkCheckboxComponent()
    })
    NodeAttach<ArkCheckboxPeer>((): ArkCheckboxPeer => ArkCheckboxPeer.create(receiver), (_: ArkCheckboxPeer): void => {
        receiver.setCheckboxOptions(options)
        style?.(receiver)
        withCheckboxStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkCheckboxSet extends ArkCommonMethodSet implements CheckboxAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _select_flag?: boolean
    _select0_value?: boolean | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | undefined
    _shape_flag?: boolean
    _shape0_value?: CheckBoxShape | undefined
    _unselectedColor_flag?: boolean
    _unselectedColor0_value?: ResourceColor | undefined
    _mark_flag?: boolean
    _mark0_value?: MarkStyle | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnCheckboxChangeCallback | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<CheckBoxConfiguration> | undefined
    __onChangeEvent_select_flag?: boolean
    __onChangeEvent_select0_value?: ((select: boolean | undefined) => void)
    applyModifierPatch(component: CheckboxAttribute): void {
        if (this._select_flag)
            component.select((this._select0_value as boolean | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | undefined))
        if (this._shape_flag)
            component.shape((this._shape0_value as CheckBoxShape | undefined))
        if (this._unselectedColor_flag)
            component.unselectedColor((this._unselectedColor0_value as ResourceColor | undefined))
        if (this._mark_flag)
            component.mark((this._mark0_value as MarkStyle | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnCheckboxChangeCallback | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<CheckBoxConfiguration> | undefined))
    }
    public select(value: boolean | undefined): this {
        this._select_flag = true
        this._select0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
        return this
    }
    public shape(value: CheckBoxShape | undefined): this {
        this._shape_flag = true
        this._shape0_value = value
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        this._unselectedColor_flag = true
        this._unselectedColor0_value = value
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        this._mark_flag = true
        this._mark0_value = value
        return this
    }
    public onChange(value: OnCheckboxChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public _onChangeEvent_select(callback_: ((select: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class CheckBoxConfiguration_serializer {
    public static write(buffer: SerializerBase, value: CheckBoxConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_name  = value.name
        valueSerializer.writeString(value_name)
        const value_selected  = value.selected
        valueSerializer.writeBoolean(value_selected)
        const value_triggerChange  = value.triggerChange
        valueSerializer.holdAndWriteCallback(value_triggerChange)
    }
    public static read(buffer: DeserializerBase): CheckBoxConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<CheckBoxConfiguration> = (valueDeserializer.readObject() as ContentModifier<CheckBoxConfiguration>)
        const name_result : string = (valueDeserializer.readString() as string)
        const selected_result : boolean = valueDeserializer.readBoolean()
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
        let value : CheckBoxConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, name: name_result, selected: selected_result, triggerChange: triggerChange_result} as CheckBoxConfiguration)
        return value
    }
}
export class CheckboxOptions_serializer {
    public static write(buffer: SerializerBase, value: CheckboxOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_name  = value.name
        let value_name_type : int32 = RuntimeType.UNDEFINED
        value_name_type = runtimeType(value_name)
        valueSerializer.writeInt8((value_name_type).toChar())
        if ((value_name_type) != (RuntimeType.UNDEFINED)) {
            const value_name_value  = value_name!
            valueSerializer.writeString(value_name_value)
        }
        const value_group  = value.group
        let value_group_type : int32 = RuntimeType.UNDEFINED
        value_group_type = runtimeType(value_group)
        valueSerializer.writeInt8((value_group_type).toChar())
        if ((value_group_type) != (RuntimeType.UNDEFINED)) {
            const value_group_value  = value_group!
            valueSerializer.writeString(value_group_value)
        }
        const value_indicatorBuilder  = value.indicatorBuilder
        let value_indicatorBuilder_type : int32 = RuntimeType.UNDEFINED
        value_indicatorBuilder_type = runtimeType(value_indicatorBuilder)
        valueSerializer.writeInt8((value_indicatorBuilder_type).toChar())
        if ((value_indicatorBuilder_type) != (RuntimeType.UNDEFINED)) {
            const value_indicatorBuilder_value  = value_indicatorBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_indicatorBuilder_value))
        }
    }
    public static read(buffer: DeserializerBase): CheckboxOptions {
        let valueDeserializer : DeserializerBase = buffer
        const name_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let name_buf : string | undefined
        if ((name_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            name_buf = (valueDeserializer.readString() as string)
        }
        const name_result : string | undefined = name_buf
        const group_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let group_buf : string | undefined
        if ((group_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            group_buf = (valueDeserializer.readString() as string)
        }
        const group_result : string | undefined = group_buf
        const indicatorBuilder_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let indicatorBuilder_buf : CustomBuilder | undefined
        if ((indicatorBuilder_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const indicatorBuilder_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const indicatorBuilder_buf__call : KPointer = valueDeserializer.readPointer()
            const indicatorBuilder_buf__callSync : KPointer = valueDeserializer.readPointer()
            indicatorBuilder_buf = ():void => { 
    const indicatorBuilder_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    indicatorBuilder_buf__argsSerializer.writeInt32(indicatorBuilder_buf__resource.resourceId);
    indicatorBuilder_buf__argsSerializer.writePointer(indicatorBuilder_buf__call);
    indicatorBuilder_buf__argsSerializer.writePointer(indicatorBuilder_buf__callSync);
    InteropNativeModule._CallCallback(737226752, indicatorBuilder_buf__argsSerializer.asBuffer(), indicatorBuilder_buf__argsSerializer.length());
    indicatorBuilder_buf__argsSerializer.release();
    return; }
        }
        const indicatorBuilder_result : CustomBuilder | undefined = indicatorBuilder_buf
        let value : CheckboxOptions = ({name: name_result, group: group_result, indicatorBuilder: indicatorBuilder_result} as CheckboxOptions)
        return value
    }
}
