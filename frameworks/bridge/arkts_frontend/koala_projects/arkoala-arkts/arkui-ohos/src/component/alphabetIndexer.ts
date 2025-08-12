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
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Font, Position, Length } from "./units"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkAlphabetIndexerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkAlphabetIndexerPeer {
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
    onSelectedAttribute(value: ((index: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupBackgroundAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupUnselectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupItemBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    usingPopupAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_usingPopup(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selectedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupItemFontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemSizeAttribute(value: string | number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_itemSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(value: Font | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeFont(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectAttribute(value: OnAlphabetIndexerSelectCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestPopupDataAttribute(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onRequestPopupData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onPopupSelectAttribute(value: OnAlphabetIndexerPopupSelectCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_onPopupSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupPositionAttribute(value: Position | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writePosition(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoCollapseAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_autoCollapse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupItemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_itemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    popupTitleBackgroundAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_popupTitleBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignStyleAttribute(value: IndexerAlign | undefined, offset?: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as IndexerAlign)
            thisSerializer.writeInt32(TypeChecker.IndexerAlign_ToNumeric(value_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8(offset_type as int32)
        if ((RuntimeType.UNDEFINED) != (offset_type)) {
            const offset_value  = offset!
            thisSerializer.writeLength(offset_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_alignStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_selectedAttribute(callback: ((selected: number | undefined) => void)): void {
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
export type AlphabetIndexerInterface = (options: AlphabetIndexerOptions) => AlphabetIndexerAttribute;
export type OnAlphabetIndexerSelectCallback = (index: number) => void;
export type OnAlphabetIndexerPopupSelectCallback = (index: number) => void;
export type OnAlphabetIndexerRequestPopupDataCallback = (index: number) => Array<string>;
export type Callback_Number_Void = (index: number) => void;
export type Callback_Opt_Number_Void = (selected: number | undefined) => void;
export interface AlphabetIndexerAttribute extends CommonMethod {
    onSelected(value: ((index: number) => void) | undefined): this
    color(value: ResourceColor | undefined): this
    selectedColor(value: ResourceColor | undefined): this
    popupColor(value: ResourceColor | undefined): this
    selectedBackgroundColor(value: ResourceColor | undefined): this
    popupBackground(value: ResourceColor | undefined): this
    popupSelectedColor(value: ResourceColor | undefined): this
    popupUnselectedColor(value: ResourceColor | undefined): this
    popupItemBackgroundColor(value: ResourceColor | undefined): this
    usingPopup(value: boolean | undefined): this
    selectedFont(value: Font | undefined): this
    popupFont(value: Font | undefined): this
    popupItemFont(value: Font | undefined): this
    itemSize(value: string | number | undefined): this
    font(value: Font | undefined): this
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this
    selected(value: number | undefined): this
    popupPosition(value: Position | undefined): this
    autoCollapse(value: boolean | undefined): this
    popupItemBorderRadius(value: number | undefined): this
    itemBorderRadius(value: number | undefined): this
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this
    popupTitleBackground(value: ResourceColor | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this
    _onChangeEvent_selected(callback: ((selected: number | undefined) => void)): void
}
export class ArkAlphabetIndexerStyle extends ArkCommonMethodStyle implements AlphabetIndexerAttribute {
    onSelected_value?: ((index: number) => void) | undefined
    color_value?: ResourceColor | undefined
    selectedColor_value?: ResourceColor | undefined
    popupColor_value?: ResourceColor | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    popupBackground_value?: ResourceColor | undefined
    popupSelectedColor_value?: ResourceColor | undefined
    popupUnselectedColor_value?: ResourceColor | undefined
    popupItemBackgroundColor_value?: ResourceColor | undefined
    usingPopup_value?: boolean | undefined
    selectedFont_value?: Font | undefined
    popupFont_value?: Font | undefined
    popupItemFont_value?: Font | undefined
    itemSize_value?: string | number | undefined
    font_value?: Font | undefined
    onSelect_value?: OnAlphabetIndexerSelectCallback | undefined
    onRequestPopupData_value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    onPopupSelect_value?: OnAlphabetIndexerPopupSelectCallback | undefined
    selected_value?: number | undefined
    popupPosition_value?: Position | undefined
    autoCollapse_value?: boolean | undefined
    popupItemBorderRadius_value?: number | undefined
    itemBorderRadius_value?: number | undefined
    popupBackgroundBlurStyle_value?: BlurStyle | undefined
    popupTitleBackground_value?: ResourceColor | undefined
    enableHapticFeedback_value?: boolean | undefined
    public onSelected(value: ((index: number) => void) | undefined): this {
        return this
    }
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public popupColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public popupBackground(value: ResourceColor | undefined): this {
        return this
    }
    public popupSelectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public popupUnselectedColor(value: ResourceColor | undefined): this {
        return this
    }
    public popupItemBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public usingPopup(value: boolean | undefined): this {
        return this
    }
    public selectedFont(value: Font | undefined): this {
        return this
    }
    public popupFont(value: Font | undefined): this {
        return this
    }
    public popupItemFont(value: Font | undefined): this {
        return this
    }
    public itemSize(value: string | number | undefined): this {
        return this
    }
    public font(value: Font | undefined): this {
        return this
    }
    public onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        return this
    }
    public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        return this
    }
    public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        return this
    }
    public selected(value: number | undefined): this {
        return this
    }
    public popupPosition(value: Position | undefined): this {
        return this
    }
    public autoCollapse(value: boolean | undefined): this {
        return this
    }
    public popupItemBorderRadius(value: number | undefined): this {
        return this
    }
    public itemBorderRadius(value: number | undefined): this {
        return this
    }
    public popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    public popupTitleBackground(value: ResourceColor | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        return this
    }
    public _onChangeEvent_selected(callback: ((selected: number | undefined) => void)): void {
        throw new Error("Unimplmented")
    }
}
export class ArkAlphabetIndexerComponent extends ArkCommonMethodComponent implements AlphabetIndexerAttribute {
    getPeer(): ArkAlphabetIndexerPeer {
        return (this.peer as ArkAlphabetIndexerPeer)
    }
        public setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this {
        if (this.checkPriority("setAlphabetIndexerOptions")) {
            const options_casted = options as (AlphabetIndexerOptions)
            this.getPeer()?.setAlphabetIndexerOptionsAttribute(options_casted)
            return this
        }
        return this
    }
        public onSelected(value: ((index: number) => void) | undefined): this {
        if (this.checkPriority("onSelected")) {
            const value_casted = value as (((index: number) => void) | undefined)
            this.getPeer()?.onSelectedAttribute(value_casted)
            return this
        }
        return this
    }
        public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
        public selectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedColorAttribute(value_casted)
            return this
        }
        return this
    }
        public popupColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupColorAttribute(value_casted)
            return this
        }
        return this
    }
        public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
        public popupBackground(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupBackground")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
        public popupSelectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupSelectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
        public popupUnselectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupUnselectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
        public popupItemBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupItemBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupItemBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
        public usingPopup(value: boolean | undefined): this {
        if (this.checkPriority("usingPopup")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.usingPopupAttribute(value_casted)
            return this
        }
        return this
    }
        public selectedFont(value: Font | undefined): this {
        if (this.checkPriority("selectedFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.selectedFontAttribute(value_casted)
            return this
        }
        return this
    }
        public popupFont(value: Font | undefined): this {
        if (this.checkPriority("popupFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.popupFontAttribute(value_casted)
            return this
        }
        return this
    }
        public popupItemFont(value: Font | undefined): this {
        if (this.checkPriority("popupItemFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.popupItemFontAttribute(value_casted)
            return this
        }
        return this
    }
        public itemSize(value: string | number | undefined): this {
        if (this.checkPriority("itemSize")) {
            const value_casted = value as (string | number | undefined)
            this.getPeer()?.itemSizeAttribute(value_casted)
            return this
        }
        return this
    }
        public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.fontAttribute(value_casted)
            return this
        }
        return this
    }
        public onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnAlphabetIndexerSelectCallback | undefined)
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
        public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        if (this.checkPriority("onRequestPopupData")) {
            const value_casted = value as (OnAlphabetIndexerRequestPopupDataCallback | undefined)
            this.getPeer()?.onRequestPopupDataAttribute(value_casted)
            return this
        }
        return this
    }
        public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        if (this.checkPriority("onPopupSelect")) {
            const value_casted = value as (OnAlphabetIndexerPopupSelectCallback | undefined)
            this.getPeer()?.onPopupSelectAttribute(value_casted)
            return this
        }
        return this
    }
        public selected(value: number | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
        public popupPosition(value: Position | undefined): this {
        if (this.checkPriority("popupPosition")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.popupPositionAttribute(value_casted)
            return this
        }
        return this
    }
        public autoCollapse(value: boolean | undefined): this {
        if (this.checkPriority("autoCollapse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoCollapseAttribute(value_casted)
            return this
        }
        return this
    }
        public popupItemBorderRadius(value: number | undefined): this {
        if (this.checkPriority("popupItemBorderRadius")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.popupItemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
        public itemBorderRadius(value: number | undefined): this {
        if (this.checkPriority("itemBorderRadius")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.itemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
        public popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("popupBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.popupBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
        public popupTitleBackground(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupTitleBackground")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.popupTitleBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
        public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
        public alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        if (this.checkPriority("alignStyle")) {
            const value_casted = value as (IndexerAlign | undefined)
            const offset_casted = offset as (Length)
            this.getPeer()?.alignStyleAttribute(value_casted, offset_casted)
            return this
        }
        return this
    }
        public _onChangeEvent_selected(callback: ((selected: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((selected: number | undefined) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function AlphabetIndexer(
    /** @memo */
    style: ((attributes: AlphabetIndexerAttribute) => void) | undefined,
    options: AlphabetIndexerOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
