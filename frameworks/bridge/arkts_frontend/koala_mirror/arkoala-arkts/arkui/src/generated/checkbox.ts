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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, MarkStyle } from "./units"
import { CheckBoxShape, Color } from "./enums"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Callback_Boolean_Void } from "./navigation"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeCheckboxOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CheckboxInterface_setCheckboxOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CheckboxAttribute_select(this.peer.ptr, value ? 1 : 0)
    }
    selectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    shapeAttribute(value: CheckBoxShape): void {
        ArkUIGeneratedNativeModule._CheckboxAttribute_shape(this.peer.ptr, TypeChecker.CheckBoxShape_ToNumeric(value))
    }
    unselectedColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._CheckboxAttribute_unselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    markAttribute(value: MarkStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeMarkStyle(value)
        ArkUIGeneratedNativeModule._CheckboxAttribute_mark(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: OnCheckboxChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CheckboxAttribute_onChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._CheckboxAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectAttribute(callback: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._CheckboxAttribute__onChangeEvent_select(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface CheckboxOptions {
    name?: string;
    group?: string;
    indicatorBuilder?: CustomBuilder;
}
export interface CheckBoxConfiguration extends CommonConfiguration {
    name: string;
    selected: boolean;
    triggerChange: ((isVisible: boolean) => void);
}

export type OnCheckboxChangeCallback = (value: boolean) => void;
export interface CheckboxAttribute extends CommonMethod {
    select(value: boolean): this
    selectedColor(value: ResourceColor): this
    shape(value: CheckBoxShape): this
    unselectedColor(value: ResourceColor): this
    mark(value: MarkStyle): this
    onChange(value: OnCheckboxChangeCallback): this
    contentModifier(value: ContentModifier): this
    _onChangeEvent_select(callback: ((isVisible: boolean) => void)): void
    attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UICheckboxAttribute extends UICommonMethod {
    /** @memo */
    select(value: boolean): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    shape(value: CheckBoxShape): this
    /** @memo */
    unselectedColor(value: ResourceColor): this
    /** @memo */
    mark(value: MarkStyle): this
    /** @memo */
    onChange(value: OnCheckboxChangeCallback): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    _onChangeEvent_select(callback: ((isVisible: boolean) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkCheckboxStyle extends ArkCommonMethodStyle implements CheckboxAttribute {
    select_value?: boolean
    selectedColor_value?: ResourceColor
    shape_value?: CheckBoxShape
    unselectedColor_value?: ResourceColor
    mark_value?: MarkStyle
    onChange_value?: OnCheckboxChangeCallback
    contentModifier_value?: ContentModifier
    public select(value: boolean): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public shape(value: CheckBoxShape): this {
        return this
    }
    public unselectedColor(value: ResourceColor): this {
        return this
    }
    public mark(value: MarkStyle): this {
        return this
    }
    public onChange(value: OnCheckboxChangeCallback): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public _onChangeEvent_select(callback: ((isVisible: boolean) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkCheckboxComponent extends ArkCommonMethodComponent implements UICheckboxAttribute {
    getPeer(): ArkCheckboxPeer {
        return (this.peer as ArkCheckboxPeer)
    }
    /** @memo */
    public setCheckboxOptions(options?: CheckboxOptions): this {
        if (this.checkPriority("setCheckboxOptions")) {
            const options_casted = options as (CheckboxOptions | undefined)
            this.getPeer()?.setCheckboxOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public select(value: boolean): this {
        if (this.checkPriority("select")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedColor(value: ResourceColor): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public shape(value: CheckBoxShape): this {
        if (this.checkPriority("shape")) {
            const value_casted = value as (CheckBoxShape)
            this.getPeer()?.shapeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public unselectedColor(value: ResourceColor): this {
        if (this.checkPriority("unselectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.unselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mark(value: MarkStyle): this {
        if (this.checkPriority("mark")) {
            const value_casted = value as (MarkStyle)
            this.getPeer()?.markAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onChange(value: OnCheckboxChangeCallback): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (OnCheckboxChangeCallback)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_select(callback: ((isVisible: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_select")) {
            const callback_casted = callback as (((isVisible: boolean) => void))
            this.getPeer()?._onChangeEvent_selectAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkCheckbox(
    /** @memo */
    style: ((attributes: UICheckboxAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options?: CheckboxOptions,
): void {
    const receiver = remember(() => {
        return new ArkCheckboxComponent()
    })
    NodeAttach<ArkCheckboxPeer>((): ArkCheckboxPeer => ArkCheckboxPeer.create(receiver), (_: ArkCheckboxPeer) => {
        receiver.setCheckboxOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
