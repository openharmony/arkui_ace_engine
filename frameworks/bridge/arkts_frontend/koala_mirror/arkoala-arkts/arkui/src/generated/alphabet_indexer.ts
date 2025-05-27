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
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Font, Position, Length } from "./units"
import { Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkAlphabetIndexerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkAlphabetIndexerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._AlphabetIndexer_construct(peerId, flags)
        const _peer  = new ArkAlphabetIndexerPeer(_peerPtr, peerId, "AlphabetIndexer", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAlphabetIndexerOptionsAttribute(options: AlphabetIndexerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeAlphabetIndexerOptions(options)
        ArkUIGeneratedNativeModule._AlphabetIndexerInterface_setAlphabetIndexerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectedAttribute(value: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupBackgroundAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupSelectedColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupUnselectedColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupItemBackgroundColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    usingPopupAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_usingPopup(this.peer.ptr, value ? 1 : 0)
    }
    selectedFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupItemFontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemSizeAttribute(value: string | number): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_itemSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: OnAlphabetIndexerSelectCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestPopupDataAttribute(value: OnAlphabetIndexerRequestPopupDataCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onRequestPopupData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPopupSelectAttribute(value: OnAlphabetIndexerPopupSelectCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onPopupSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selected(this.peer.ptr, value)
    }
    popupPositionAttribute(value: Position): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(value)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoCollapseAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_autoCollapse(this.peer.ptr, value ? 1 : 0)
    }
    popupItemBorderRadiusAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemBorderRadius(this.peer.ptr, value)
    }
    itemBorderRadiusAttribute(value: number): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_itemBorderRadius(this.peer.ptr, value)
    }
    popupBackgroundBlurStyleAttribute(value: BlurStyle): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupBackgroundBlurStyle(this.peer.ptr, TypeChecker.BlurStyle_ToNumeric(value))
    }
    popupTitleBackgroundAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupTitleBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    alignStyleAttribute(value: IndexerAlign, offset?: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            let offset_value_type : int32 = RuntimeType.UNDEFINED
            offset_value_type = runtimeType(offset_value)
            if (RuntimeType.STRING == offset_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const offset_value_0  = offset_value as string
                thisSerializer.writeString(offset_value_0)
            }
            else if (RuntimeType.NUMBER == offset_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const offset_value_1  = offset_value as number
                thisSerializer.writeNumber(offset_value_1)
            }
            else if (RuntimeType.OBJECT == offset_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const offset_value_2  = offset_value as Resource
                thisSerializer.writeResource(offset_value_2)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_alignStyle(this.peer.ptr, TypeChecker.IndexerAlign_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((index: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute__onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum IndexerAlign {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    START = 2,
    END = 3
}
export interface AlphabetIndexerOptions {
    arrayValue: Array<string>;
    selected: number;
}

export type OnAlphabetIndexerSelectCallback = (index: number) => void;
export type OnAlphabetIndexerPopupSelectCallback = (index: number) => void;
export type OnAlphabetIndexerRequestPopupDataCallback = (index: number) => Array<string>;
export type Callback_Number_Void = (index: number) => void;
export interface AlphabetIndexerAttribute extends CommonMethod {
    onSelected(value: ((index: number) => void)): this
    color(value: ResourceColor): this
    selectedColor(value: ResourceColor): this
    popupColor(value: ResourceColor): this
    selectedBackgroundColor(value: ResourceColor): this
    popupBackground(value: ResourceColor): this
    popupSelectedColor(value: ResourceColor): this
    popupUnselectedColor(value: ResourceColor): this
    popupItemBackgroundColor(value: ResourceColor): this
    usingPopup(value: boolean): this
    selectedFont(value: Font): this
    popupFont(value: Font): this
    popupItemFont(value: Font): this
    itemSize(value: string | number): this
    font(value: Font): this
    onSelect(value: OnAlphabetIndexerSelectCallback): this
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): this
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): this
    selected(value: number): this
    popupPosition(value: Position): this
    autoCollapse(value: boolean): this
    popupItemBorderRadius(value: number): this
    itemBorderRadius(value: number): this
    popupBackgroundBlurStyle(value: BlurStyle): this
    popupTitleBackground(value: ResourceColor): this
    enableHapticFeedback(value: boolean): this
    alignStyle(value: IndexerAlign, offset?: Length): this
    _onChangeEvent_selected(callback: ((index: number) => void)): void
    attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIAlphabetIndexerAttribute extends UICommonMethod {
    /** @memo */
    onSelected(value: ((index: number) => void)): this
    /** @memo */
    color(value: ResourceColor): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    popupColor(value: ResourceColor): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    popupBackground(value: ResourceColor): this
    /** @memo */
    popupSelectedColor(value: ResourceColor): this
    /** @memo */
    popupUnselectedColor(value: ResourceColor): this
    /** @memo */
    popupItemBackgroundColor(value: ResourceColor): this
    /** @memo */
    usingPopup(value: boolean): this
    /** @memo */
    selectedFont(value: Font): this
    /** @memo */
    popupFont(value: Font): this
    /** @memo */
    popupItemFont(value: Font): this
    /** @memo */
    itemSize(value: string | number): this
    /** @memo */
    font(value: Font): this
    /** @memo */
    onSelect(value: OnAlphabetIndexerSelectCallback): this
    /** @memo */
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): this
    /** @memo */
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): this
    /** @memo */
    selected(value: number): this
    /** @memo */
    popupPosition(value: Position): this
    /** @memo */
    autoCollapse(value: boolean): this
    /** @memo */
    popupItemBorderRadius(value: number): this
    /** @memo */
    itemBorderRadius(value: number): this
    /** @memo */
    popupBackgroundBlurStyle(value: BlurStyle): this
    /** @memo */
    popupTitleBackground(value: ResourceColor): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    alignStyle(value: IndexerAlign, offset?: Length): this
    /** @memo */
    _onChangeEvent_selected(callback: ((index: number) => void)): void
    /** @memo */
    attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkAlphabetIndexerStyle extends ArkCommonMethodStyle implements AlphabetIndexerAttribute {
    onSelected_value?: ((index: number) => void)
    color_value?: ResourceColor
    selectedColor_value?: ResourceColor
    popupColor_value?: ResourceColor
    selectedBackgroundColor_value?: ResourceColor
    popupBackground_value?: ResourceColor
    popupSelectedColor_value?: ResourceColor
    popupUnselectedColor_value?: ResourceColor
    popupItemBackgroundColor_value?: ResourceColor
    usingPopup_value?: boolean
    selectedFont_value?: Font
    popupFont_value?: Font
    popupItemFont_value?: Font
    itemSize_value?: string | number
    font_value?: Font
    onSelect_value?: OnAlphabetIndexerSelectCallback
    onRequestPopupData_value?: OnAlphabetIndexerRequestPopupDataCallback
    onPopupSelect_value?: OnAlphabetIndexerPopupSelectCallback
    selected_value?: number
    popupPosition_value?: Position
    autoCollapse_value?: boolean
    popupItemBorderRadius_value?: number
    itemBorderRadius_value?: number
    popupBackgroundBlurStyle_value?: BlurStyle
    popupTitleBackground_value?: ResourceColor
    enableHapticFeedback_value?: boolean
    public onSelected(value: ((index: number) => void)): this {
        return this
    }
    public color(value: ResourceColor): this {
        return this
    }
    public selectedColor(value: ResourceColor): this {
        return this
    }
    public popupColor(value: ResourceColor): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor): this {
        return this
    }
    public popupBackground(value: ResourceColor): this {
        return this
    }
    public popupSelectedColor(value: ResourceColor): this {
        return this
    }
    public popupUnselectedColor(value: ResourceColor): this {
        return this
    }
    public popupItemBackgroundColor(value: ResourceColor): this {
        return this
    }
    public usingPopup(value: boolean): this {
        return this
    }
    public selectedFont(value: Font): this {
        return this
    }
    public popupFont(value: Font): this {
        return this
    }
    public popupItemFont(value: Font): this {
        return this
    }
    public itemSize(value: string | number): this {
        return this
    }
    public font(value: Font): this {
        return this
    }
    public onSelect(value: OnAlphabetIndexerSelectCallback): this {
        return this
    }
    public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): this {
        return this
    }
    public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): this {
        return this
    }
    public selected(value: number): this {
        return this
    }
    public popupPosition(value: Position): this {
        return this
    }
    public autoCollapse(value: boolean): this {
        return this
    }
    public popupItemBorderRadius(value: number): this {
        return this
    }
    public itemBorderRadius(value: number): this {
        return this
    }
    public popupBackgroundBlurStyle(value: BlurStyle): this {
        return this
    }
    public popupTitleBackground(value: ResourceColor): this {
        return this
    }
    public enableHapticFeedback(value: boolean): this {
        return this
    }
    public alignStyle(value: IndexerAlign, offset?: Length): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((index: number) => void)): void {
        throw new Error("Unimplmented")
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkAlphabetIndexerComponent extends ArkCommonMethodComponent implements UIAlphabetIndexerAttribute {
    getPeer(): ArkAlphabetIndexerPeer {
        return (this.peer as ArkAlphabetIndexerPeer)
    }
    /** @memo */
    public setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this {
        if (this.checkPriority("setAlphabetIndexerOptions")) {
            const options_casted = options as (AlphabetIndexerOptions)
            this.getPeer()?.setAlphabetIndexerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelected(value: ((index: number) => void)): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((index: number) => void))
            this.getPeer()?.onSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public color(value: ResourceColor): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.colorAttribute(value_casted)
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
    public popupColor(value: ResourceColor): this {
        if (this.checkPriority("popupColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupBackground(value: ResourceColor): this {
        if (this.checkPriority("popupBackground")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupSelectedColor(value: ResourceColor): this {
        if (this.checkPriority("popupSelectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupUnselectedColor(value: ResourceColor): this {
        if (this.checkPriority("popupUnselectedColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupItemBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("popupItemBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupItemBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public usingPopup(value: boolean): this {
        if (this.checkPriority("usingPopup")) {
            const value_casted = value as (boolean)
            this.getPeer()?.usingPopupAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedFont(value: Font): this {
        if (this.checkPriority("selectedFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.selectedFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupFont(value: Font): this {
        if (this.checkPriority("popupFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.popupFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupItemFont(value: Font): this {
        if (this.checkPriority("popupItemFont")) {
            const value_casted = value as (Font)
            this.getPeer()?.popupItemFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public itemSize(value: string | number): this {
        if (this.checkPriority("itemSize")) {
            const value_casted = value as (string | number)
            this.getPeer()?.itemSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public font(value: Font): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: OnAlphabetIndexerSelectCallback): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnAlphabetIndexerSelectCallback)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): this {
        if (this.checkPriority("onRequestPopupData")) {
            const value_casted = value as (OnAlphabetIndexerRequestPopupDataCallback)
            this.getPeer()?.onRequestPopupDataAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): this {
        if (this.checkPriority("onPopupSelect")) {
            const value_casted = value as (OnAlphabetIndexerPopupSelectCallback)
            this.getPeer()?.onPopupSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: number): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupPosition(value: Position): this {
        if (this.checkPriority("popupPosition")) {
            const value_casted = value as (Position)
            this.getPeer()?.popupPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoCollapse(value: boolean): this {
        if (this.checkPriority("autoCollapse")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoCollapseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupItemBorderRadius(value: number): this {
        if (this.checkPriority("popupItemBorderRadius")) {
            const value_casted = value as (number)
            this.getPeer()?.popupItemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public itemBorderRadius(value: number): this {
        if (this.checkPriority("itemBorderRadius")) {
            const value_casted = value as (number)
            this.getPeer()?.itemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupBackgroundBlurStyle(value: BlurStyle): this {
        if (this.checkPriority("popupBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle)
            this.getPeer()?.popupBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public popupTitleBackground(value: ResourceColor): this {
        if (this.checkPriority("popupTitleBackground")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.popupTitleBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignStyle(value: IndexerAlign, offset?: Length): this {
        if (this.checkPriority("alignStyle")) {
            const value_casted = value as (IndexerAlign)
            const offset_casted = offset as (Length | undefined)
            this.getPeer()?.alignStyleAttribute(value_casted, offset_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((index: number) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((index: number) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkAlphabetIndexer(
    /** @memo */
    style: ((attributes: UIAlphabetIndexerAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options: AlphabetIndexerOptions,
): void {
    const receiver = remember(() => {
        return new ArkAlphabetIndexerComponent()
    })
    NodeAttach<ArkAlphabetIndexerPeer>((): ArkAlphabetIndexerPeer => ArkAlphabetIndexerPeer.create(receiver), (_: ArkAlphabetIndexerPeer) => {
        receiver.setAlphabetIndexerOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
