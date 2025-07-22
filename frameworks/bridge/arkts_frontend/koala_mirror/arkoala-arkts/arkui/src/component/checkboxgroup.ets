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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color, CheckBoxShape } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkCheckboxGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCheckboxGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CheckboxGroup_construct(peerId, flags)
        const _peer  = new ArkCheckboxGroupPeer(_peerPtr, peerId, "CheckboxGroup", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCheckboxGroupOptionsAttribute(options?: CheckboxGroupOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            CheckboxGroupOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupInterface_setCheckboxGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectAllAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectAll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setMark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnCheckboxGroupChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCheckboxShapeAttribute(value: CheckBoxShape | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CheckBoxShape)
            thisSerializer.writeInt32(TypeChecker.CheckBoxShape_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setCheckboxShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectAllAttribute(callback_: ((selectAll: boolean | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_set_onChangeEvent_selectAll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SelectStatus {
    ALL = 0,
    All = 0,
    PART = 1,
    Part = 1,
    NONE = 2,
    None = 2
}
export interface CheckboxGroupOptions {
    group?: string;
}
export interface CheckboxGroupResult {
    name: Array<string>;
    status: SelectStatus;
}
export type OnCheckboxGroupChangeCallback = (value: CheckboxGroupResult) => void;
export interface CheckboxGroupAttribute extends CommonMethod {
    selectAll(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectAll")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    unselectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method unselectedColor")
    }
    mark(value: MarkStyle | undefined): this {
        throw new Error("Unimplemented method mark")
    }
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    checkboxShape(value: CheckBoxShape | undefined): this {
        throw new Error("Unimplemented method checkboxShape")
    }
    _onChangeEvent_selectAll(callback_: ((selectAll: boolean | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selectAll")
    }
    attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCheckboxGroupStyle extends ArkCommonMethodStyle implements CheckboxGroupAttribute {
    selectAll_value?: boolean | undefined
    selectedColor_value?: ResourceColor | undefined
    unselectedColor_value?: ResourceColor | undefined
    mark_value?: MarkStyle | undefined
    onChange_value?: OnCheckboxGroupChangeCallback | undefined
    checkboxShape_value?: CheckBoxShape | undefined
    attributeModifier_value?: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    public selectAll(value: boolean | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public unselectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public mark(value: MarkStyle | undefined): this {
        return this
    }
    public onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        return this
    }
    public checkboxShape(value: CheckBoxShape | undefined): this {
        return this
    }
    public _onChangeEvent_selectAll(callback_: ((selectAll: boolean | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: CheckboxGroupAttribute): void {
        super.apply(target)
        if (this.selectAll_value !== undefined)
            target.selectAll(this.selectAll_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.unselectedColor_value !== undefined)
            target.unselectedColor(this.unselectedColor_value!)
        if (this.mark_value !== undefined)
            target.mark(this.mark_value!)
        if (this.onChange_value !== undefined)
            target.onChange(this.onChange_value!)
        if (this.checkboxShape_value !== undefined)
            target.checkboxShape(this.checkboxShape_value!)
    }
}

export class ArkCheckboxGroupComponent extends ArkCommonMethodComponent implements CheckboxGroupAttribute {
    getPeer(): ArkCheckboxGroupPeer {
        return (this.peer as ArkCheckboxGroupPeer)
    }
    public setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        if (this.checkPriority("setCheckboxGroupOptions")) {
            const options_casted = options as (CheckboxGroupOptions | undefined)
            this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public selectAll(value: boolean | undefined): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectAllAttribute(value_casted)
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
    public onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnCheckboxGroupChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public checkboxShape(value: CheckBoxShape | undefined): this {
        if (this.checkPriority("checkboxShape")) {
            const value_casted = value as (CheckBoxShape | undefined)
            this.getPeer()?.setCheckboxShapeAttribute(value_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selectAll(callback_: ((selectAll: boolean | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selectAll")) {
            const callback__casted = callback_ as (((selectAll: boolean | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectAllAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCheckboxGroupStyle(receiver: CheckboxGroupAttribute, modifier: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCheckboxGroupStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("CheckboxGroup")
// export function CheckboxGroup(
//     options?: CheckboxGroupOptions,
//     @memo
//     content_?: () => void,
// ): CheckboxGroupAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function CheckboxGroup(
    @memo
    style: ((attributes: CheckboxGroupAttribute) => void) | undefined,
    options?: CheckboxGroupOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCheckboxGroupComponent>((): ArkCheckboxGroupComponent => {
        return new ArkCheckboxGroupComponent()
    })
    NodeAttach<ArkCheckboxGroupPeer>((): ArkCheckboxGroupPeer => ArkCheckboxGroupPeer.create(receiver), (_: ArkCheckboxGroupPeer): void => {
        receiver.setCheckboxGroupOptions(options)
        style?.(receiver)
        withCheckboxGroupStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkCheckboxGroupSet extends ArkCommonMethodSet implements CheckboxGroupAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selectAll_flag?: boolean
    _selectAll0_value?: boolean | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | undefined
    _unselectedColor_flag?: boolean
    _unselectedColor0_value?: ResourceColor | undefined
    _mark_flag?: boolean
    _mark0_value?: MarkStyle | undefined
    _onChange_flag?: boolean
    _onChange0_value?: OnCheckboxGroupChangeCallback | undefined
    _checkboxShape_flag?: boolean
    _checkboxShape0_value?: CheckBoxShape | undefined
    __onChangeEvent_selectAll_flag?: boolean
    __onChangeEvent_selectAll0_value?: ((selectAll: boolean | undefined) => void)
    applyModifierPatch(component: CheckboxGroupAttribute): void {
        if (this._selectAll_flag)
            component.selectAll((this._selectAll0_value as boolean | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | undefined))
        if (this._unselectedColor_flag)
            component.unselectedColor((this._unselectedColor0_value as ResourceColor | undefined))
        if (this._mark_flag)
            component.mark((this._mark0_value as MarkStyle | undefined))
        if (this._onChange_flag)
            component.onChange((this._onChange0_value as OnCheckboxGroupChangeCallback | undefined))
        if (this._checkboxShape_flag)
            component.checkboxShape((this._checkboxShape0_value as CheckBoxShape | undefined))
    }
    public selectAll(value: boolean | undefined): this {
        this._selectAll_flag = true
        this._selectAll0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
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
    public onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        this._onChange_flag = true
        this._onChange0_value = value
        return this
    }
    public checkboxShape(value: CheckBoxShape | undefined): this {
        this._checkboxShape_flag = true
        this._checkboxShape0_value = value
        return this
    }
    public _onChangeEvent_selectAll(callback_: ((selectAll: boolean | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class CheckboxGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_group  = value.group
        let value_group_type : int32 = RuntimeType.UNDEFINED
        value_group_type = runtimeType(value_group)
        valueSerializer.writeInt8((value_group_type).toChar())
        if ((value_group_type) != (RuntimeType.UNDEFINED)) {
            const value_group_value  = value_group!
            valueSerializer.writeString(value_group_value)
        }
    }
    public static read(buffer: DeserializerBase): CheckboxGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const group_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let group_buf : string | undefined
        if ((group_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            group_buf = (valueDeserializer.readString() as string)
        }
        const group_result : string | undefined = group_buf
        let value : CheckboxGroupOptions = ({group: group_result} as CheckboxGroupOptions)
        return value
    }
}
export class CheckboxGroupResult_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_name  = value.name
        valueSerializer.writeInt32((value_name.length).toInt())
        for (let value_name_counter_i = 0; value_name_counter_i < value_name.length; value_name_counter_i++) {
            const value_name_element : string = value_name[value_name_counter_i]
            valueSerializer.writeString(value_name_element)
        }
        const value_status  = value.status
        valueSerializer.writeInt32(TypeChecker.SelectStatus_ToNumeric(value_status))
    }
    public static read(buffer: DeserializerBase): CheckboxGroupResult {
        let valueDeserializer : DeserializerBase = buffer
        const name_buf_length : int32 = valueDeserializer.readInt32()
        let name_buf : Array<string> = new Array<string>(name_buf_length)
        for (let name_buf_i = 0; name_buf_i < name_buf_length; name_buf_i++) {
            name_buf[name_buf_i] = (valueDeserializer.readString() as string)
        }
        const name_result : Array<string> = name_buf
        const status_result : SelectStatus = TypeChecker.SelectStatus_FromNumeric(valueDeserializer.readInt32())
        let value : CheckboxGroupResult = ({name: name_result, status: status_result} as CheckboxGroupResult)
        return value
    }
}
