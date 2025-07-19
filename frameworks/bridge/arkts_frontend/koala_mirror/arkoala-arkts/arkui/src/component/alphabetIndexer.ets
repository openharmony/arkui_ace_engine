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
import { Font_serializer, Position_serializer, ResourceColor, Font, Position, Length } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AlphabetIndexerOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._AlphabetIndexerInterface_setAlphabetIndexerOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupBackgroundAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupSelectedColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupUnselectedColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUsingPopupAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setUsingPopup(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemSizeAttribute(value: string | number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setItemSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Font_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: OnAlphabetIndexerSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestPopupDataAttribute(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnRequestPopupData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPopupSelectAttribute(value: OnAlphabetIndexerPopupSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnPopupSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupPositionAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            Position_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoCollapseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setAutoCollapse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BlurStyle)
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupTitleBackgroundAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupTitleBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignStyleAttribute(value: IndexerAlign | undefined, offset?: Length): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as IndexerAlign)
            thisSerializer.writeInt32(TypeChecker.IndexerAlign_ToNumeric(value_value))
        }
        let offset_type : int32 = RuntimeType.UNDEFINED
        offset_type = runtimeType(offset)
        thisSerializer.writeInt8((offset_type).toChar())
        if ((offset_type) != (RuntimeType.UNDEFINED)) {
            const offset_value  = offset!
            let offset_value_type : int32 = RuntimeType.UNDEFINED
            offset_value_type = runtimeType(offset_value)
            if (RuntimeType.STRING == offset_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const offset_value_0  = offset_value as string
                thisSerializer.writeString(offset_value_0)
            }
            else if (RuntimeType.NUMBER == offset_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const offset_value_1  = offset_value as number
                thisSerializer.writeNumber(offset_value_1)
            }
            else if (RuntimeType.OBJECT == offset_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const offset_value_2  = offset_value as Resource
                Resource_serializer.write(thisSerializer, offset_value_2)
            }
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setAlignStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    set_onChangeEvent_selectedAttribute(callback_: ((selected: number | undefined) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_set_onChangeEvent_selected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export interface AlphabetIndexerAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    selectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedColor")
    }
    popupColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupColor")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    popupBackground(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupBackground")
    }
    popupSelectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupSelectedColor")
    }
    popupUnselectedColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupUnselectedColor")
    }
    popupItemBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupItemBackgroundColor")
    }
    usingPopup(value: boolean | undefined): this {
        throw new Error("Unimplemented method usingPopup")
    }
    selectedFont(value: Font | undefined): this {
        throw new Error("Unimplemented method selectedFont")
    }
    popupFont(value: Font | undefined): this {
        throw new Error("Unimplemented method popupFont")
    }
    popupItemFont(value: Font | undefined): this {
        throw new Error("Unimplemented method popupItemFont")
    }
    itemSize(value: string | number | undefined): this {
        throw new Error("Unimplemented method itemSize")
    }
    font(value: Font | undefined): this {
        throw new Error("Unimplemented method font")
    }
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        throw new Error("Unimplemented method onSelect")
    }
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        throw new Error("Unimplemented method onRequestPopupData")
    }
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        throw new Error("Unimplemented method onPopupSelect")
    }
    selected(value: number | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    popupPosition(value: Position | undefined): this {
        throw new Error("Unimplemented method popupPosition")
    }
    autoCollapse(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoCollapse")
    }
    popupItemBorderRadius(value: number | undefined): this {
        throw new Error("Unimplemented method popupItemBorderRadius")
    }
    itemBorderRadius(value: number | undefined): this {
        throw new Error("Unimplemented method itemBorderRadius")
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        throw new Error("Unimplemented method popupBackgroundBlurStyle")
    }
    popupTitleBackground(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method popupTitleBackground")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        throw new Error("Unimplemented method alignStyle")
    }
    _onChangeEvent_selected(callback_: ((selected: number | undefined) => void)): void {
        throw new Error("Unimplemented method _onChangeEvent_selected")
    }
    attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkAlphabetIndexerStyle extends ArkCommonMethodStyle implements AlphabetIndexerAttribute {
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
    attributeModifier_value?: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public _onChangeEvent_selected(callback_: ((selected: number | undefined) => void)): void {
        throw new Error("Unimplemented")
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: AlphabetIndexerAttribute): void {
        super.apply(target)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
        if (this.selectedColor_value !== undefined)
            target.selectedColor(this.selectedColor_value!)
        if (this.popupColor_value !== undefined)
            target.popupColor(this.popupColor_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.popupBackground_value !== undefined)
            target.popupBackground(this.popupBackground_value!)
        if (this.popupSelectedColor_value !== undefined)
            target.popupSelectedColor(this.popupSelectedColor_value!)
        if (this.popupUnselectedColor_value !== undefined)
            target.popupUnselectedColor(this.popupUnselectedColor_value!)
        if (this.popupItemBackgroundColor_value !== undefined)
            target.popupItemBackgroundColor(this.popupItemBackgroundColor_value!)
        if (this.usingPopup_value !== undefined)
            target.usingPopup(this.usingPopup_value!)
        if (this.selectedFont_value !== undefined)
            target.selectedFont(this.selectedFont_value!)
        if (this.popupFont_value !== undefined)
            target.popupFont(this.popupFont_value!)
        if (this.popupItemFont_value !== undefined)
            target.popupItemFont(this.popupItemFont_value!)
        if (this.itemSize_value !== undefined)
            target.itemSize(this.itemSize_value!)
        if (this.font_value !== undefined)
            target.font(this.font_value!)
        if (this.onSelect_value !== undefined)
            target.onSelect(this.onSelect_value!)
        if (this.onRequestPopupData_value !== undefined)
            target.onRequestPopupData(this.onRequestPopupData_value!)
        if (this.onPopupSelect_value !== undefined)
            target.onPopupSelect(this.onPopupSelect_value!)
        if (this.selected_value !== undefined)
            target.selected(this.selected_value!)
        if (this.popupPosition_value !== undefined)
            target.popupPosition(this.popupPosition_value!)
        if (this.autoCollapse_value !== undefined)
            target.autoCollapse(this.autoCollapse_value!)
        if (this.popupItemBorderRadius_value !== undefined)
            target.popupItemBorderRadius(this.popupItemBorderRadius_value!)
        if (this.itemBorderRadius_value !== undefined)
            target.itemBorderRadius(this.itemBorderRadius_value!)
        if (this.popupBackgroundBlurStyle_value !== undefined)
            target.popupBackgroundBlurStyle(this.popupBackgroundBlurStyle_value!)
        if (this.popupTitleBackground_value !== undefined)
            target.popupTitleBackground(this.popupTitleBackground_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
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
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
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
    public popupColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public popupBackground(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupBackground")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
    public popupSelectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupSelectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupSelectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public popupUnselectedColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupUnselectedColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupUnselectedColorAttribute(value_casted)
            return this
        }
        return this
    }
    public popupItemBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupItemBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupItemBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public usingPopup(value: boolean | undefined): this {
        if (this.checkPriority("usingPopup")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setUsingPopupAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedFont(value: Font | undefined): this {
        if (this.checkPriority("selectedFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setSelectedFontAttribute(value_casted)
            return this
        }
        return this
    }
    public popupFont(value: Font | undefined): this {
        if (this.checkPriority("popupFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setPopupFontAttribute(value_casted)
            return this
        }
        return this
    }
    public popupItemFont(value: Font | undefined): this {
        if (this.checkPriority("popupItemFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setPopupItemFontAttribute(value_casted)
            return this
        }
        return this
    }
    public itemSize(value: string | number | undefined): this {
        if (this.checkPriority("itemSize")) {
            const value_casted = value as (string | number | undefined)
            this.getPeer()?.setItemSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public font(value: Font | undefined): this {
        if (this.checkPriority("font")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setFontAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (OnAlphabetIndexerSelectCallback | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        if (this.checkPriority("onRequestPopupData")) {
            const value_casted = value as (OnAlphabetIndexerRequestPopupDataCallback | undefined)
            this.getPeer()?.setOnRequestPopupDataAttribute(value_casted)
            return this
        }
        return this
    }
    public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        if (this.checkPriority("onPopupSelect")) {
            const value_casted = value as (OnAlphabetIndexerPopupSelectCallback | undefined)
            this.getPeer()?.setOnPopupSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public selected(value: number | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public popupPosition(value: Position | undefined): this {
        if (this.checkPriority("popupPosition")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.setPopupPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public autoCollapse(value: boolean | undefined): this {
        if (this.checkPriority("autoCollapse")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoCollapseAttribute(value_casted)
            return this
        }
        return this
    }
    public popupItemBorderRadius(value: number | undefined): this {
        if (this.checkPriority("popupItemBorderRadius")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setPopupItemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public itemBorderRadius(value: number | undefined): this {
        if (this.checkPriority("itemBorderRadius")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setItemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (this.checkPriority("popupBackgroundBlurStyle")) {
            const value_casted = value as (BlurStyle | undefined)
            this.getPeer()?.setPopupBackgroundBlurStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public popupTitleBackground(value: ResourceColor | undefined): this {
        if (this.checkPriority("popupTitleBackground")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPopupTitleBackgroundAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        if (this.checkPriority("alignStyle")) {
            const value_casted = value as (IndexerAlign | undefined)
            const offset_casted = offset as (Length | undefined)
            this.getPeer()?.setAlignStyleAttribute(value_casted, offset_casted)
            return this
        }
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | undefined) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback__casted = callback_ as (((selected: number | undefined) => void))
            this.getPeer()?.set_onChangeEvent_selectedAttribute(callback__casted)
            return
        }
        return
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withAlphabetIndexerStyle(receiver: AlphabetIndexerAttribute, modifier: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkAlphabetIndexerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("AlphabetIndexer")
// export function AlphabetIndexer(
//     options: AlphabetIndexerOptions,
//     @memo
//     content_?: () => void,
// ): AlphabetIndexerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function AlphabetIndexer(
    @memo
    style: ((attributes: AlphabetIndexerAttribute) => void) | undefined,
    options: AlphabetIndexerOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkAlphabetIndexerComponent>((): ArkAlphabetIndexerComponent => {
        return new ArkAlphabetIndexerComponent()
    })
    NodeAttach<ArkAlphabetIndexerPeer>((): ArkAlphabetIndexerPeer => ArkAlphabetIndexerPeer.create(receiver), (_: ArkAlphabetIndexerPeer): void => {
        receiver.setAlphabetIndexerOptions(options)
        style?.(receiver)
        withAlphabetIndexerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkAlphabetIndexerSet extends ArkCommonMethodSet implements AlphabetIndexerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _color_flag?: boolean
    _color0_value?: ResourceColor | undefined
    _selectedColor_flag?: boolean
    _selectedColor0_value?: ResourceColor | undefined
    _popupColor_flag?: boolean
    _popupColor0_value?: ResourceColor | undefined
    _selectedBackgroundColor_flag?: boolean
    _selectedBackgroundColor0_value?: ResourceColor | undefined
    _popupBackground_flag?: boolean
    _popupBackground0_value?: ResourceColor | undefined
    _popupSelectedColor_flag?: boolean
    _popupSelectedColor0_value?: ResourceColor | undefined
    _popupUnselectedColor_flag?: boolean
    _popupUnselectedColor0_value?: ResourceColor | undefined
    _popupItemBackgroundColor_flag?: boolean
    _popupItemBackgroundColor0_value?: ResourceColor | undefined
    _usingPopup_flag?: boolean
    _usingPopup0_value?: boolean | undefined
    _selectedFont_flag?: boolean
    _selectedFont0_value?: Font | undefined
    _popupFont_flag?: boolean
    _popupFont0_value?: Font | undefined
    _popupItemFont_flag?: boolean
    _popupItemFont0_value?: Font | undefined
    _itemSize_flag?: boolean
    _itemSize0_value?: string | number | undefined
    _font_flag?: boolean
    _font0_value?: Font | undefined
    _onSelect_flag?: boolean
    _onSelect0_value?: OnAlphabetIndexerSelectCallback | undefined
    _onRequestPopupData_flag?: boolean
    _onRequestPopupData0_value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    _onPopupSelect_flag?: boolean
    _onPopupSelect0_value?: OnAlphabetIndexerPopupSelectCallback | undefined
    _selected_flag?: boolean
    _selected0_value?: number | undefined
    _popupPosition_flag?: boolean
    _popupPosition0_value?: Position | undefined
    _autoCollapse_flag?: boolean
    _autoCollapse0_value?: boolean | undefined
    _popupItemBorderRadius_flag?: boolean
    _popupItemBorderRadius0_value?: number | undefined
    _itemBorderRadius_flag?: boolean
    _itemBorderRadius0_value?: number | undefined
    _popupBackgroundBlurStyle_flag?: boolean
    _popupBackgroundBlurStyle0_value?: BlurStyle | undefined
    _popupTitleBackground_flag?: boolean
    _popupTitleBackground0_value?: ResourceColor | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _alignStyle_flag?: boolean
    _alignStyle0_value?: IndexerAlign | undefined
    _alignStyle1_value?: Length | undefined
    __onChangeEvent_selected_flag?: boolean
    __onChangeEvent_selected0_value?: ((selected: number | undefined) => void)
    applyModifierPatch(component: AlphabetIndexerAttribute): void {
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | undefined))
        if (this._selectedColor_flag)
            component.selectedColor((this._selectedColor0_value as ResourceColor | undefined))
        if (this._popupColor_flag)
            component.popupColor((this._popupColor0_value as ResourceColor | undefined))
        if (this._selectedBackgroundColor_flag)
            component.selectedBackgroundColor((this._selectedBackgroundColor0_value as ResourceColor | undefined))
        if (this._popupBackground_flag)
            component.popupBackground((this._popupBackground0_value as ResourceColor | undefined))
        if (this._popupSelectedColor_flag)
            component.popupSelectedColor((this._popupSelectedColor0_value as ResourceColor | undefined))
        if (this._popupUnselectedColor_flag)
            component.popupUnselectedColor((this._popupUnselectedColor0_value as ResourceColor | undefined))
        if (this._popupItemBackgroundColor_flag)
            component.popupItemBackgroundColor((this._popupItemBackgroundColor0_value as ResourceColor | undefined))
        if (this._usingPopup_flag)
            component.usingPopup((this._usingPopup0_value as boolean | undefined))
        if (this._selectedFont_flag)
            component.selectedFont((this._selectedFont0_value as Font | undefined))
        if (this._popupFont_flag)
            component.popupFont((this._popupFont0_value as Font | undefined))
        if (this._popupItemFont_flag)
            component.popupItemFont((this._popupItemFont0_value as Font | undefined))
        if (this._itemSize_flag)
            component.itemSize((this._itemSize0_value as string | number | undefined))
        if (this._font_flag)
            component.font((this._font0_value as Font | undefined))
        if (this._onSelect_flag)
            component.onSelect((this._onSelect0_value as OnAlphabetIndexerSelectCallback | undefined))
        if (this._onRequestPopupData_flag)
            component.onRequestPopupData((this._onRequestPopupData0_value as OnAlphabetIndexerRequestPopupDataCallback | undefined))
        if (this._onPopupSelect_flag)
            component.onPopupSelect((this._onPopupSelect0_value as OnAlphabetIndexerPopupSelectCallback | undefined))
        if (this._selected_flag)
            component.selected((this._selected0_value as number | undefined))
        if (this._popupPosition_flag)
            component.popupPosition((this._popupPosition0_value as Position | undefined))
        if (this._autoCollapse_flag)
            component.autoCollapse((this._autoCollapse0_value as boolean | undefined))
        if (this._popupItemBorderRadius_flag)
            component.popupItemBorderRadius((this._popupItemBorderRadius0_value as number | undefined))
        if (this._itemBorderRadius_flag)
            component.itemBorderRadius((this._itemBorderRadius0_value as number | undefined))
        if (this._popupBackgroundBlurStyle_flag)
            component.popupBackgroundBlurStyle((this._popupBackgroundBlurStyle0_value as BlurStyle | undefined))
        if (this._popupTitleBackground_flag)
            component.popupTitleBackground((this._popupTitleBackground0_value as ResourceColor | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._alignStyle_flag)
            component.alignStyle((this._alignStyle0_value as IndexerAlign | undefined), (this._alignStyle1_value as Length | undefined))
    }
    public color(value: ResourceColor | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public selectedColor(value: ResourceColor | undefined): this {
        this._selectedColor_flag = true
        this._selectedColor0_value = value
        return this
    }
    public popupColor(value: ResourceColor | undefined): this {
        this._popupColor_flag = true
        this._popupColor0_value = value
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        this._selectedBackgroundColor_flag = true
        this._selectedBackgroundColor0_value = value
        return this
    }
    public popupBackground(value: ResourceColor | undefined): this {
        this._popupBackground_flag = true
        this._popupBackground0_value = value
        return this
    }
    public popupSelectedColor(value: ResourceColor | undefined): this {
        this._popupSelectedColor_flag = true
        this._popupSelectedColor0_value = value
        return this
    }
    public popupUnselectedColor(value: ResourceColor | undefined): this {
        this._popupUnselectedColor_flag = true
        this._popupUnselectedColor0_value = value
        return this
    }
    public popupItemBackgroundColor(value: ResourceColor | undefined): this {
        this._popupItemBackgroundColor_flag = true
        this._popupItemBackgroundColor0_value = value
        return this
    }
    public usingPopup(value: boolean | undefined): this {
        this._usingPopup_flag = true
        this._usingPopup0_value = value
        return this
    }
    public selectedFont(value: Font | undefined): this {
        this._selectedFont_flag = true
        this._selectedFont0_value = value
        return this
    }
    public popupFont(value: Font | undefined): this {
        this._popupFont_flag = true
        this._popupFont0_value = value
        return this
    }
    public popupItemFont(value: Font | undefined): this {
        this._popupItemFont_flag = true
        this._popupItemFont0_value = value
        return this
    }
    public itemSize(value: string | number | undefined): this {
        this._itemSize_flag = true
        this._itemSize0_value = value
        return this
    }
    public font(value: Font | undefined): this {
        this._font_flag = true
        this._font0_value = value
        return this
    }
    public onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        this._onSelect_flag = true
        this._onSelect0_value = value
        return this
    }
    public onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        this._onRequestPopupData_flag = true
        this._onRequestPopupData0_value = value
        return this
    }
    public onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        this._onPopupSelect_flag = true
        this._onPopupSelect0_value = value
        return this
    }
    public selected(value: number | undefined): this {
        this._selected_flag = true
        this._selected0_value = value
        return this
    }
    public popupPosition(value: Position | undefined): this {
        this._popupPosition_flag = true
        this._popupPosition0_value = value
        return this
    }
    public autoCollapse(value: boolean | undefined): this {
        this._autoCollapse_flag = true
        this._autoCollapse0_value = value
        return this
    }
    public popupItemBorderRadius(value: number | undefined): this {
        this._popupItemBorderRadius_flag = true
        this._popupItemBorderRadius0_value = value
        return this
    }
    public itemBorderRadius(value: number | undefined): this {
        this._itemBorderRadius_flag = true
        this._itemBorderRadius0_value = value
        return this
    }
    public popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        this._popupBackgroundBlurStyle_flag = true
        this._popupBackgroundBlurStyle0_value = value
        return this
    }
    public popupTitleBackground(value: ResourceColor | undefined): this {
        this._popupTitleBackground_flag = true
        this._popupTitleBackground0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        this._alignStyle_flag = true
        this._alignStyle0_value = value
        this._alignStyle1_value = offset
        return this
    }
    public _onChangeEvent_selected(callback_: ((selected: number | undefined) => void)): void {
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class AlphabetIndexerOptions_serializer {
    public static write(buffer: SerializerBase, value: AlphabetIndexerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_arrayValue  = value.arrayValue
        valueSerializer.writeInt32((value_arrayValue.length).toInt())
        for (let value_arrayValue_counter_i = 0; value_arrayValue_counter_i < value_arrayValue.length; value_arrayValue_counter_i++) {
            const value_arrayValue_element : string = value_arrayValue[value_arrayValue_counter_i]
            valueSerializer.writeString(value_arrayValue_element)
        }
        const value_selected  = value.selected
        valueSerializer.writeNumber(value_selected)
    }
    public static read(buffer: DeserializerBase): AlphabetIndexerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const arrayValue_buf_length : int32 = valueDeserializer.readInt32()
        let arrayValue_buf : Array<string> = new Array<string>(arrayValue_buf_length)
        for (let arrayValue_buf_i = 0; arrayValue_buf_i < arrayValue_buf_length; arrayValue_buf_i++) {
            arrayValue_buf[arrayValue_buf_i] = (valueDeserializer.readString() as string)
        }
        const arrayValue_result : Array<string> = arrayValue_buf
        const selected_result : number = (valueDeserializer.readNumber() as number)
        let value : AlphabetIndexerOptions = ({arrayValue: arrayValue_result, selected: selected_result} as AlphabetIndexerOptions)
        return value
    }
}
