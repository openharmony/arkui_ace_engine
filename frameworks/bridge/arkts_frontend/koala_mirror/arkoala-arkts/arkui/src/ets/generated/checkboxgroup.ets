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
import { ResourceColor, MarkStyle } from "./units"
import { CheckBoxShape, Color } from "./enums"
import { Callback_Boolean_Void } from "./navigation"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCheckboxGroupOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupInterface_setCheckboxGroupOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectAllAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_selectAll(this.peer.ptr, value ? 1 : 0)
    }
    selectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    unselectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_unselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAttribute(value: MarkStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMarkStyle(value)
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_mark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: OnCheckboxGroupChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    checkboxShapeAttribute(value: CheckBoxShape): void {
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute_checkboxShape(this.peer.ptr, TypeChecker.CheckBoxShape_ToNumeric(value))
    }
    _onChangeEvent_selectAllAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._CheckboxGroupAttribute__onChangeEvent_selectAll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selectAll(value: boolean): this
    selectedColor(value: ResourceColor): this
    unselectedColor(value: ResourceColor): this
    mark(value: MarkStyle): this
    onChange(value: OnCheckboxGroupChangeCallback): this
    checkboxShape(value: CheckBoxShape): this
    _onChangeEvent_selectAll(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICheckboxGroupAttribute extends UICommonMethod {
    @memo
    selectAll(value: boolean): this
    @memo
    selectedColor(value: ResourceColor): this
    @memo
    unselectedColor(value: ResourceColor): this
    @memo
    mark(value: MarkStyle): this
    @memo
    onChange(value: OnCheckboxGroupChangeCallback): this
    @memo
    checkboxShape(value: CheckBoxShape): this
    @memo
    _onChangeEvent_selectAll(callback: ((isVisible: boolean) => void)): void
    @memo
    attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCheckboxGroupStyle extends ArkCommonMethodStyle implements CheckboxGroupAttribute {
    selectAll_value?: boolean
    selectedColor_value?: ResourceColor
    unselectedColor_value?: ResourceColor
    mark_value?: MarkStyle
    onChange_value?: OnCheckboxGroupChangeCallback
    checkboxShape_value?: CheckBoxShape
    public selectAll(value: boolean): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public unselectedColor(value: ResourceColor): this {
        return this
    }
    public mark(value: MarkStyle): this {
        return this
    }
    public onChange(value: OnCheckboxGroupChangeCallback): this {
        return this
    }
    public checkboxShape(value: CheckBoxShape): this {
        return this
    }
    public _onChangeEvent_selectAll(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkCheckboxGroupComponent extends ArkCommonMethodComponent implements UICheckboxGroupAttribute {
    getPeer(): ArkCheckboxGroupPeer {
        return (this.peer as ArkCheckboxGroupPeer)
    }
    @memo
    public setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        if (this.checkPriority("setCheckboxGroupOptions")) {
            const options_casted = options as (CheckboxGroupOptions | undefined)
            this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public selectAll(value: boolean): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectAllAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public unselectedColor(value: ResourceColor): this {
        if (this.checkPriority("unselectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.unselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public mark(value: MarkStyle): this {
        if (this.checkPriority("mark")) {
            const value_casted = value as (MarkStyle)
            this.getPeer()?.markAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onChange(value: OnCheckboxGroupChangeCallback): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnCheckboxGroupChangeCallback)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public checkboxShape(value: CheckBoxShape): this {
        if (this.checkPriority("checkboxShape")) {
            const value_casted = value as (CheckBoxShape)
            this.getPeer()?.checkboxShapeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public _onChangeEvent_selectAll(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_selectAll")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_selectAllAttribute(callback_casted)
            return
        }
        return
    }
    @memo
    public attributeModifier(value: AttributeModifier<CheckboxGroupAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("CheckboxGroup")
export function CheckboxGroup(
    options?: CheckboxGroupOptions,
    @memo
    content_?: () => void,
): CheckboxGroupAttribute {
    throw new Error("Not implemented")
}

@memo
export function CheckboxGroup(
    @memo
    style: ((attributes: UICheckboxGroupAttribute) => void) | undefined,
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
