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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
import { MarkStyle_serializer, ResourceColor, MarkStyle } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, CheckBoxShape } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkCheckboxGroupPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCheckboxGroupPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CheckboxGroup_construct(peerId, flags)
        const _peer  = new ArkCheckboxGroupPeer(_peerPtr, peerId, 'CheckboxGroup', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCheckboxGroupOptionsAttribute(options?: CheckboxGroupOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            CheckboxGroupOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupInterface_setCheckboxGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectAllAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectAll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUnselectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0))
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setMark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: OnCheckboxGroupChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCheckboxShapeAttribute(value: CheckBoxShape | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CheckBoxShape)
            thisSerializer.writeInt32(TypeChecker.CheckBoxShape_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_setCheckboxShape(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
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
    attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCheckboxGroupStyle extends ArkCommonMethodStyle implements CheckboxGroupAttribute {
    selectAll_value?: boolean | Bindable<boolean> | undefined
    selectedColor_value?: ResourceColor | undefined
    unselectedColor_value?: ResourceColor | undefined
    mark_value?: MarkStyle | undefined
    onChange_value?: OnCheckboxGroupChangeCallback | undefined
    checkboxShape_value?: CheckBoxShape | undefined
    attributeModifier_value?: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined
    public selectAll(value: boolean | Bindable<boolean> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public selectAll(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
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
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class CheckboxGroupModifier extends CommonMethodModifier implements CheckboxGroupAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _selectAll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectAll_0_0value?: boolean | Bindable<boolean> | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _unselectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _unselectedColor_0_0value?: ResourceColor | undefined
    _mark_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mark_0_0value?: MarkStyle | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: OnCheckboxGroupChangeCallback | undefined
    _checkboxShape_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _checkboxShape_0_0value?: CheckBoxShape | undefined
    applyModifierPatch(peer: ArkCheckboxGroupPeer): void {
        super.applyModifierPatch(peer)
        if (this._selectAll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectAll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectAllAttribute((this._selectAll_0_0value as boolean | Bindable<boolean> | undefined));
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectAll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectAllAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._unselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._unselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUnselectedColorAttribute((this._unselectedColor_0_0value as ResourceColor | undefined));
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._unselectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._mark_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mark_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarkAttribute((this._mark_0_0value as MarkStyle | undefined));
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mark_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mark_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarkAttribute((undefined as MarkStyle | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnCheckboxGroupChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as OnCheckboxGroupChangeCallback | undefined));
                }
            }
        }
        if (this._checkboxShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._checkboxShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCheckboxShapeAttribute((this._checkboxShape_0_0value as CheckBoxShape | undefined));
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._checkboxShape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCheckboxShapeAttribute((undefined as CheckBoxShape | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CheckboxGroupModifier): void {
        super.mergeModifier(modifier)
        if (modifier._selectAll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectAll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectAll(modifier._selectAll_0_0value);
                    break;
                }
                default: {
                    this.selectAll((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._unselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._unselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.unselectedColor(modifier._unselectedColor_0_0value);
                    break;
                }
                default: {
                    this.unselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._mark_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mark_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mark(modifier._mark_0_0value);
                    break;
                }
                default: {
                    this.mark((undefined as MarkStyle | undefined));
                }
            }
        }
        if (modifier._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnCheckboxGroupChangeCallback | undefined));
                }
            }
        }
        if (modifier._checkboxShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._checkboxShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.checkboxShape(modifier._checkboxShape_0_0value);
                    break;
                }
                default: {
                    this.checkboxShape((undefined as CheckBoxShape | undefined));
                }
            }
        }
    }
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._selectAll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectAll_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectAll_0_0value = value
        } else
        {
            this._selectAll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
        } else
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    unselectedColor(value: ResourceColor | undefined): this {
        if (((this._unselectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._unselectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._unselectedColor_0_0value = value
        } else
        {
            this._unselectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mark(value: MarkStyle | undefined): this {
        if (((this._mark_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mark_0_flag = AttributeUpdaterFlag.UPDATE
            this._mark_0_0value = value
        } else
        {
            this._mark_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        if (((this._onChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChange_0_0value = value
        } else
        {
            this._onChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    checkboxShape(value: CheckBoxShape | undefined): this {
        if (((this._checkboxShape_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._checkboxShape_0_flag = AttributeUpdaterFlag.UPDATE
            this._checkboxShape_0_0value = value
        } else
        {
            this._checkboxShape_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class CheckboxGroupOptions_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForGroup  = value.group
        if (valueHolderForGroup !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGroupTmpValue  = valueHolderForGroup!
            valueSerializer.writeString(valueHolderForGroupTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CheckboxGroupOptions {
        let valueDeserializer : DeserializerBase = buffer
        const groupTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let groupTmpBuf : string | undefined
        if ((groupTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            groupTmpBuf = (valueDeserializer.readString() as string)
        }
        const groupTmpResult : string | undefined = groupTmpBuf
        let value : CheckboxGroupOptions = ({group: groupTmpResult} as CheckboxGroupOptions)
        return value
    }
}
export class CheckboxGroupResult_serializer {
    public static write(buffer: SerializerBase, value: CheckboxGroupResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForName  = value.name
        valueSerializer.writeInt32((valueHolderForName.length).toInt())
        for (let valueHolderForNameCounterI = 0; valueHolderForNameCounterI < valueHolderForName.length; valueHolderForNameCounterI++) {
            const valueHolderForNameTmpElement : string = valueHolderForName[valueHolderForNameCounterI]
            valueSerializer.writeString(valueHolderForNameTmpElement)
        }
        const valueHolderForStatus  = value.status
        valueSerializer.writeInt32(TypeChecker.SelectStatus_ToNumeric(valueHolderForStatus))
    }
    public static read(buffer: DeserializerBase): CheckboxGroupResult {
        let valueDeserializer : DeserializerBase = buffer
        const nameTmpBufLength : int32 = valueDeserializer.readInt32()
        let nameTmpBuf : Array<string> = new Array<string>(nameTmpBufLength)
        for (let nameTmpBufBufCounterI = 0; nameTmpBufBufCounterI < nameTmpBufLength; nameTmpBufBufCounterI++) {
            nameTmpBuf[nameTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : Array<string> = nameTmpBuf
        const statusTmpResult : SelectStatus = TypeChecker.SelectStatus_FromNumeric(valueDeserializer.readInt32())
        let value : CheckboxGroupResult = ({name: nameTmpResult, status: statusTmpResult} as CheckboxGroupResult)
        return value
    }
}
