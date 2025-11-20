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
import { Resource_serializer } from "./../framework/resource"
import { Font_serializer, Position_serializer, ResourceColor, Font, Position, Length } from "./units"
import { Bindable_I32_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { AttributeModifier, hookAlphabetIndexerAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { AlphabetIndexerModifier } from "./../AlphabetIndexerModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkAlphabetIndexerPeer extends ArkCommonMethodPeer {
    attributeSet?: AlphabetIndexerModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkAlphabetIndexerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._AlphabetIndexer_construct(peerId, flags)
        const _peer  = new ArkAlphabetIndexerPeer(_peerPtr, peerId, 'AlphabetIndexer', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupBackgroundAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupSelectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupUnselectedColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setUsingPopupAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setUsingPopup(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemSizeAttribute(value: string | double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setItemSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: OnAlphabetIndexerSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestPopupDataAttribute(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnRequestPopupData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPopupSelectAttribute(value: OnAlphabetIndexerPopupSelectCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setOnPopupSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: int32 | Bindable<int32> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<int32>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupPositionAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Position_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoCollapseAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setAutoCollapse(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemBorderRadiusAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemBorderRadiusAttribute(value: double | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupBackgroundBlurStyleAttribute(value: BlurStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BlurStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupBackgroundBlurStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupTitleBackgroundAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupTitleBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignStyleAttribute(value: IndexerAlign | undefined, offset?: Length): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as IndexerAlign)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (offset !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const offsetTmpValue  = offset!
            if (offsetTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const offsetTmpValueForIdx0  = offsetTmpValue as string
                thisSerializer.writeString(offsetTmpValueForIdx0)
            } else if (offsetTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const offsetTmpValueForIdx1  = offsetTmpValue as number
                thisSerializer.writeNumber(offsetTmpValueForIdx1)
            } else if (offsetTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const offsetTmpValueForIdx2  = offsetTmpValue as Resource
                Resource_serializer.write(thisSerializer, offsetTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setAlignStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    selected: int32 | Bindable<int32>;
}
export type OnAlphabetIndexerSelectCallback = (index: int32) => void;
export type OnAlphabetIndexerPopupSelectCallback = (index: int32) => void;
export type OnAlphabetIndexerRequestPopupDataCallback = (index: int32) => Array<string>;
export interface AlphabetIndexerAttribute extends CommonMethod {
    setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this {
        throw new Error("Unimplemented method setAlphabetIndexerOptions")
    }
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
    itemSize(value: string | double | undefined): this {
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
    selected(value: int32 | Bindable<int32> | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    popupPosition(value: Position | undefined): this {
        throw new Error("Unimplemented method popupPosition")
    }
    autoCollapse(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoCollapse")
    }
    popupItemBorderRadius(value: double | undefined): this {
        throw new Error("Unimplemented method popupItemBorderRadius")
    }
    itemBorderRadius(value: double | undefined): this {
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
    itemSize_value?: string | double | undefined
    font_value?: Font | undefined
    onSelect_value?: OnAlphabetIndexerSelectCallback | undefined
    onRequestPopupData_value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    onPopupSelect_value?: OnAlphabetIndexerPopupSelectCallback | undefined
    selected_value?: int32 | Bindable<int32> | undefined
    popupPosition_value?: Position | undefined
    autoCollapse_value?: boolean | undefined
    popupItemBorderRadius_value?: double | undefined
    itemBorderRadius_value?: double | undefined
    popupBackgroundBlurStyle_value?: BlurStyle | undefined
    popupTitleBackground_value?: ResourceColor | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined
    setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this {
        return this
    }
    color(value: ResourceColor | undefined): this {
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        return this
    }
    popupColor(value: ResourceColor | undefined): this {
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    popupBackground(value: ResourceColor | undefined): this {
        return this
    }
    popupSelectedColor(value: ResourceColor | undefined): this {
        return this
    }
    popupUnselectedColor(value: ResourceColor | undefined): this {
        return this
    }
    popupItemBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    usingPopup(value: boolean | undefined): this {
        return this
    }
    selectedFont(value: Font | undefined): this {
        return this
    }
    popupFont(value: Font | undefined): this {
        return this
    }
    popupItemFont(value: Font | undefined): this {
        return this
    }
    itemSize(value: string | double | undefined): this {
        return this
    }
    font(value: Font | undefined): this {
        return this
    }
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        return this
    }
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        return this
    }
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        return this
    }
    selected(value: int32 | Bindable<int32> | undefined): this {
        return this
    }
    popupPosition(value: Position | undefined): this {
        return this
    }
    autoCollapse(value: boolean | undefined): this {
        return this
    }
    popupItemBorderRadius(value: double | undefined): this {
        return this
    }
    itemBorderRadius(value: double | undefined): this {
        return this
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        return this
    }
    popupTitleBackground(value: ResourceColor | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkAlphabetIndexerComponent extends ArkCommonMethodComponent implements AlphabetIndexerAttribute {
    getPeer(): ArkAlphabetIndexerPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkAlphabetIndexerPeer)
    }
    public setAlphabetIndexerOptions(options: AlphabetIndexerOptions): this {
        if (this.checkPriority("setAlphabetIndexerOptions")) {
            const options_casted = options as (AlphabetIndexerOptions)
            this.getPeer()?.setAlphabetIndexerOptionsAttribute(options_casted)
            this.applyOptionsFinish('AlphabetIndexerAttribute');
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
    public itemSize(value: string | double | undefined): this {
        if (this.checkPriority("itemSize")) {
            const value_casted = value as (string | double | undefined)
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
    public selected(value: int32 | Bindable<int32> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (int32 | Bindable<int32> | undefined)
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
    public popupItemBorderRadius(value: double | undefined): this {
        if (this.checkPriority("popupItemBorderRadius")) {
            const value_casted = value as (double | undefined)
            this.getPeer()?.setPopupItemBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public itemBorderRadius(value: double | undefined): this {
        if (this.checkPriority("itemBorderRadius")) {
            const value_casted = value as (double | undefined)
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
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookAlphabetIndexerAttributeModifier(this, value);
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
export function AlphabetIndexerImpl(
    @memo
    style: ((attributes: AlphabetIndexerAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkAlphabetIndexerComponent>((): ArkAlphabetIndexerComponent => {
        return new ArkAlphabetIndexerComponent()
    })
    NodeAttach<ArkAlphabetIndexerPeer>((): ArkAlphabetIndexerPeer => ArkAlphabetIndexerPeer.create(receiver), (peer: ArkAlphabetIndexerPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class AlphabetIndexerOptions_serializer {
    public static write(buffer: SerializerBase, value: AlphabetIndexerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForArrayValue  = value.arrayValue
        valueSerializer.writeInt32((valueHolderForArrayValue.length).toInt())
        for (let valueHolderForArrayValueCounterI = 0; valueHolderForArrayValueCounterI < valueHolderForArrayValue.length; valueHolderForArrayValueCounterI++) {
            const valueHolderForArrayValueTmpElement : string = valueHolderForArrayValue[valueHolderForArrayValueCounterI]
            valueSerializer.writeString(valueHolderForArrayValueTmpElement)
        }
        const valueHolderForSelected  = value.selected
        if (valueHolderForSelected instanceof int32) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSelectedForIdx0  = valueHolderForSelected as int32
            valueSerializer.writeInt32(valueHolderForSelectedForIdx0)
        } else if (valueHolderForSelected instanceof Bindable<int32>) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSelectedForIdx1  = valueHolderForSelected as Bindable<int32>
            Bindable_I32_serializer.write(valueSerializer, valueHolderForSelectedForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): AlphabetIndexerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const arrayValueTmpBufLength : int32 = valueDeserializer.readInt32()
        let arrayValueTmpBuf : Array<string> = new Array<string>(arrayValueTmpBufLength)
        for (let arrayValueTmpBufBufCounterI = 0; arrayValueTmpBufBufCounterI < arrayValueTmpBufLength; arrayValueTmpBufBufCounterI++) {
            arrayValueTmpBuf[arrayValueTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const arrayValueTmpResult : Array<string> = arrayValueTmpBuf
        const selectedTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let selectedTmpBuf : int32 | Bindable<int32> | undefined
        if (selectedTmpBufUnionSelector == (0).toChar()) {
            selectedTmpBuf = valueDeserializer.readInt32()
        } else if (selectedTmpBufUnionSelector == (1).toChar()) {
            selectedTmpBuf = Bindable_I32_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for selectedTmpBuf has to be chosen through deserialisation.")
        }
        const selectedTmpResult : int32 | Bindable<int32> = (selectedTmpBuf as int32 | Bindable<int32>)
        let value : AlphabetIndexerOptions = ({arrayValue: arrayValueTmpResult, selected: selectedTmpResult} as AlphabetIndexerOptions)
        return value
    }
}
