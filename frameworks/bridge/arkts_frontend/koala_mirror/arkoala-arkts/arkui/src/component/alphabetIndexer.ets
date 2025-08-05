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
import { Resource_serializer, Resource } from "./../generated/resource"
import { Font_serializer, Position_serializer, ResourceColor, Font, Position, Length } from "./units"
import { Bindable_Number_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkAlphabetIndexerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupBackgroundAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupBackground(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupSelectedColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupSelectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupUnselectedColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupUnselectedColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPopupItemBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
    setItemSizeAttribute(value: string | number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
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
    setSelectedAttribute(value: number | Bindable<number> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<number>) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<number>
                Bindable_Number_serializer.write(thisSerializer, valueTmpValueForIdx1)
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
    setPopupItemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AlphabetIndexerAttribute_setPopupItemBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemBorderRadiusAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
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
            thisSerializer.writeInt32(TypeChecker.BlurStyle_ToNumeric(valueTmpValue))
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
            thisSerializer.writeInt32(TypeChecker.IndexerAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (offset !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const offsetTmpValue  = offset!
            if (offsetTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const offsetTmpValueForIdx0  = offsetTmpValue as string
                thisSerializer.writeString(offsetTmpValueForIdx0)
            } else if (offsetTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const offsetTmpValueForIdx1  = offsetTmpValue as number
                thisSerializer.writeNumber(offsetTmpValueForIdx1)
            } else if (offsetTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
    selected: number | Bindable<number>;
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
    selected(value: number | Bindable<number> | undefined): this {
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
    selected_value?: number | Bindable<number> | undefined
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
    public selected(value: number | Bindable<number> | undefined): this {
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
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
    public selected(value: number | Bindable<number> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (number | Bindable<number> | undefined)
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
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class AlphabetIndexerModifier extends CommonMethodModifier implements AlphabetIndexerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _color_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _color_0_0value?: ResourceColor | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _popupColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupColor_0_0value?: ResourceColor | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _popupBackground_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupBackground_0_0value?: ResourceColor | undefined
    _popupSelectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupSelectedColor_0_0value?: ResourceColor | undefined
    _popupUnselectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupUnselectedColor_0_0value?: ResourceColor | undefined
    _popupItemBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemBackgroundColor_0_0value?: ResourceColor | undefined
    _usingPopup_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _usingPopup_0_0value?: boolean | undefined
    _selectedFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedFont_0_0value?: Font | undefined
    _popupFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupFont_0_0value?: Font | undefined
    _popupItemFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemFont_0_0value?: Font | undefined
    _itemSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemSize_0_0value?: string | number | undefined
    _font_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _font_0_0value?: Font | undefined
    _onSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSelect_0_0value?: OnAlphabetIndexerSelectCallback | undefined
    _onRequestPopupData_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRequestPopupData_0_0value?: OnAlphabetIndexerRequestPopupDataCallback | undefined
    _onPopupSelect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPopupSelect_0_0value?: OnAlphabetIndexerPopupSelectCallback | undefined
    _selected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selected_0_0value?: number | Bindable<number> | undefined
    _popupPosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupPosition_0_0value?: Position | undefined
    _autoCollapse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoCollapse_0_0value?: boolean | undefined
    _popupItemBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupItemBorderRadius_0_0value?: number | undefined
    _itemBorderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _itemBorderRadius_0_0value?: number | undefined
    _popupBackgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupBackgroundBlurStyle_0_0value?: BlurStyle | undefined
    _popupTitleBackground_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _popupTitleBackground_0_0value?: ResourceColor | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _alignStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignStyle_0_0value?: IndexerAlign | undefined
    _alignStyle_0_1value?: Length | undefined
    applyModifierPatch(peer: ArkAlphabetIndexerPeer): void {
        super.applyModifierPatch(peer)
        if (this._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorAttribute((this._color_0_0value as ResourceColor | undefined));
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._color_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._color_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorAttribute((undefined as ResourceColor | undefined));
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
        if (this._popupColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupColorAttribute((this._popupColor_0_0value as ResourceColor | undefined));
                    this._popupColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedBackgroundColorAttribute((this._selectedBackgroundColor_0_0value as ResourceColor | undefined));
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupBackground_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupBackgroundAttribute((this._popupBackground_0_0value as ResourceColor | undefined));
                    this._popupBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupBackground_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupSelectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupSelectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupSelectedColorAttribute((this._popupSelectedColor_0_0value as ResourceColor | undefined));
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupSelectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupUnselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupUnselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupUnselectedColorAttribute((this._popupUnselectedColor_0_0value as ResourceColor | undefined));
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._popupItemBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupItemBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupItemBackgroundColorAttribute((this._popupItemBackgroundColor_0_0value as ResourceColor | undefined));
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupItemBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._usingPopup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._usingPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUsingPopupAttribute((this._usingPopup_0_0value as boolean | undefined));
                    this._usingPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._usingPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._usingPopup_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUsingPopupAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selectedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedFontAttribute((this._selectedFont_0_0value as Font | undefined));
                    this._selectedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._popupFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupFontAttribute((this._popupFont_0_0value as Font | undefined));
                    this._popupFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._popupItemFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupItemFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupItemFontAttribute((this._popupItemFont_0_0value as Font | undefined));
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupItemFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._itemSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._itemSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setItemSizeAttribute((this._itemSize_0_0value as string | number | undefined));
                    this._itemSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setItemSizeAttribute((undefined as string | number | undefined));
                }
            }
        }
        if (this._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontAttribute((this._font_0_0value as Font | undefined));
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._font_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._font_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as OnAlphabetIndexerSelectCallback | undefined));
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSelectAttribute((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (this._onRequestPopupData_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRequestPopupData_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRequestPopupDataAttribute((this._onRequestPopupData_0_0value as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRequestPopupData_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRequestPopupDataAttribute((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (this._onPopupSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPopupSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPopupSelectAttribute((this._onPopupSelect_0_0value as OnAlphabetIndexerPopupSelectCallback | undefined));
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPopupSelect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPopupSelectAttribute((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (this._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedAttribute((this._selected_0_0value as number | Bindable<number> | undefined));
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedAttribute((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (this._popupPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupPositionAttribute((this._popupPosition_0_0value as Position | undefined));
                    this._popupPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupPosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupPosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupPositionAttribute((undefined as Position | undefined));
                }
            }
        }
        if (this._autoCollapse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoCollapse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoCollapseAttribute((this._autoCollapse_0_0value as boolean | undefined));
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoCollapse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoCollapseAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._popupItemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupItemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupItemBorderRadiusAttribute((this._popupItemBorderRadius_0_0value as number | undefined));
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupItemBorderRadiusAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._itemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._itemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setItemBorderRadiusAttribute((this._itemBorderRadius_0_0value as number | undefined));
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._itemBorderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setItemBorderRadiusAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._popupBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupBackgroundBlurStyleAttribute((this._popupBackgroundBlurStyle_0_0value as BlurStyle | undefined));
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined));
                }
            }
        }
        if (this._popupTitleBackground_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._popupTitleBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPopupTitleBackgroundAttribute((this._popupTitleBackground_0_0value as ResourceColor | undefined));
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._popupTitleBackground_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPopupTitleBackgroundAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableHapticFeedbackAttribute((this._enableHapticFeedback_0_0value as boolean | undefined));
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableHapticFeedbackAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._alignStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignStyleAttribute((this._alignStyle_0_0value as IndexerAlign | undefined), (this._alignStyle_0_1value as Length | undefined));
                    this._alignStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignStyleAttribute((undefined as IndexerAlign | undefined), (undefined as Length | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: AlphabetIndexerModifier): void {
        super.mergeModifier(modifier)
        if (modifier._color_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._color_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.color(modifier._color_0_0value);
                    break;
                }
                default: {
                    this.color((undefined as ResourceColor | undefined));
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
        if (modifier._popupColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupColor(modifier._popupColor_0_0value);
                    break;
                }
                default: {
                    this.popupColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedBackgroundColor(modifier._selectedBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.selectedBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupBackground_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupBackground(modifier._popupBackground_0_0value);
                    break;
                }
                default: {
                    this.popupBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupSelectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupSelectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupSelectedColor(modifier._popupSelectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupSelectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupUnselectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupUnselectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupUnselectedColor(modifier._popupUnselectedColor_0_0value);
                    break;
                }
                default: {
                    this.popupUnselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._popupItemBackgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupItemBackgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemBackgroundColor(modifier._popupItemBackgroundColor_0_0value);
                    break;
                }
                default: {
                    this.popupItemBackgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._usingPopup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._usingPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.usingPopup(modifier._usingPopup_0_0value);
                    break;
                }
                default: {
                    this.usingPopup((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selectedFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedFont(modifier._selectedFont_0_0value);
                    break;
                }
                default: {
                    this.selectedFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._popupFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupFont(modifier._popupFont_0_0value);
                    break;
                }
                default: {
                    this.popupFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._popupItemFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupItemFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemFont(modifier._popupItemFont_0_0value);
                    break;
                }
                default: {
                    this.popupItemFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._itemSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._itemSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemSize(modifier._itemSize_0_0value);
                    break;
                }
                default: {
                    this.itemSize((undefined as string | number | undefined));
                }
            }
        }
        if (modifier._font_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._font_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.font(modifier._font_0_0value);
                    break;
                }
                default: {
                    this.font((undefined as Font | undefined));
                }
            }
        }
        if (modifier._onSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as OnAlphabetIndexerSelectCallback | undefined));
                }
            }
        }
        if (modifier._onRequestPopupData_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRequestPopupData_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRequestPopupData(modifier._onRequestPopupData_0_0value);
                    break;
                }
                default: {
                    this.onRequestPopupData((undefined as OnAlphabetIndexerRequestPopupDataCallback | undefined));
                }
            }
        }
        if (modifier._onPopupSelect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPopupSelect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPopupSelect(modifier._onPopupSelect_0_0value);
                    break;
                }
                default: {
                    this.onPopupSelect((undefined as OnAlphabetIndexerPopupSelectCallback | undefined));
                }
            }
        }
        if (modifier._selected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as number | Bindable<number> | undefined));
                }
            }
        }
        if (modifier._popupPosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupPosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupPosition(modifier._popupPosition_0_0value);
                    break;
                }
                default: {
                    this.popupPosition((undefined as Position | undefined));
                }
            }
        }
        if (modifier._autoCollapse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoCollapse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoCollapse(modifier._autoCollapse_0_0value);
                    break;
                }
                default: {
                    this.autoCollapse((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._popupItemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupItemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupItemBorderRadius(modifier._popupItemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.popupItemBorderRadius((undefined as number | undefined));
                }
            }
        }
        if (modifier._itemBorderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._itemBorderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.itemBorderRadius(modifier._itemBorderRadius_0_0value);
                    break;
                }
                default: {
                    this.itemBorderRadius((undefined as number | undefined));
                }
            }
        }
        if (modifier._popupBackgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupBackgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupBackgroundBlurStyle(modifier._popupBackgroundBlurStyle_0_0value);
                    break;
                }
                default: {
                    this.popupBackgroundBlurStyle((undefined as BlurStyle | undefined));
                }
            }
        }
        if (modifier._popupTitleBackground_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._popupTitleBackground_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.popupTitleBackground(modifier._popupTitleBackground_0_0value);
                    break;
                }
                default: {
                    this.popupTitleBackground((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._enableHapticFeedback_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableHapticFeedback_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableHapticFeedback(modifier._enableHapticFeedback_0_0value);
                    break;
                }
                default: {
                    this.enableHapticFeedback((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._alignStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignStyle(modifier._alignStyle_0_0value, modifier._alignStyle_0_1value);
                    break;
                }
                default: {
                    this.alignStyle((undefined as IndexerAlign | undefined), (undefined as Length | undefined | undefined));
                }
            }
        }
    }
    color(value: ResourceColor | undefined): this {
        if (((this._color_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._color_0_flag = AttributeUpdaterFlag.UPDATE
            this._color_0_0value = value
        } else
        {
            this._color_0_flag = AttributeUpdaterFlag.SKIP
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
    popupColor(value: ResourceColor | undefined): this {
        if (((this._popupColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupColor_0_0value = value
        } else
        {
            this._popupColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._selectedBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedBackgroundColor_0_0value = value
        } else
        {
            this._selectedBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupBackground(value: ResourceColor | undefined): this {
        if (((this._popupBackground_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupBackground_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupBackground_0_0value = value
        } else
        {
            this._popupBackground_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupSelectedColor(value: ResourceColor | undefined): this {
        if (((this._popupSelectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupSelectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupSelectedColor_0_0value = value
        } else
        {
            this._popupSelectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupUnselectedColor(value: ResourceColor | undefined): this {
        if (((this._popupUnselectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupUnselectedColor_0_0value = value
        } else
        {
            this._popupUnselectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemBackgroundColor(value: ResourceColor | undefined): this {
        if (((this._popupItemBackgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemBackgroundColor_0_0value = value
        } else
        {
            this._popupItemBackgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    usingPopup(value: boolean | undefined): this {
        if (((this._usingPopup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._usingPopup_0_0value) !== (value)))
        {
            this._usingPopup_0_flag = AttributeUpdaterFlag.UPDATE
            this._usingPopup_0_0value = value
        } else
        {
            this._usingPopup_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedFont(value: Font | undefined): this {
        if (((this._selectedFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedFont_0_0value = value
        } else
        {
            this._selectedFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupFont(value: Font | undefined): this {
        if (((this._popupFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupFont_0_0value = value
        } else
        {
            this._popupFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemFont(value: Font | undefined): this {
        if (((this._popupItemFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupItemFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemFont_0_0value = value
        } else
        {
            this._popupItemFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemSize(value: string | number | undefined): this {
        if (((this._itemSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemSize_0_0value) !== (value)))
        {
            this._itemSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemSize_0_0value = value
        } else
        {
            this._itemSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    font(value: Font | undefined): this {
        if (((this._font_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._font_0_flag = AttributeUpdaterFlag.UPDATE
            this._font_0_0value = value
        } else
        {
            this._font_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): this {
        if (((this._onSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSelect_0_0value = value
        } else
        {
            this._onSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): this {
        if (((this._onRequestPopupData_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRequestPopupData_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRequestPopupData_0_0value = value
        } else
        {
            this._onRequestPopupData_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): this {
        if (((this._onPopupSelect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPopupSelect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPopupSelect_0_0value = value
        } else
        {
            this._onPopupSelect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selected(value: number | Bindable<number> | undefined): this {
        if (((this._selected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selected_0_flag = AttributeUpdaterFlag.UPDATE
            this._selected_0_0value = value
        } else
        {
            this._selected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupPosition(value: Position | undefined): this {
        if (((this._popupPosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupPosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupPosition_0_0value = value
        } else
        {
            this._popupPosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoCollapse(value: boolean | undefined): this {
        if (((this._autoCollapse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoCollapse_0_0value) !== (value)))
        {
            this._autoCollapse_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoCollapse_0_0value = value
        } else
        {
            this._autoCollapse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupItemBorderRadius(value: number | undefined): this {
        if (((this._popupItemBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._popupItemBorderRadius_0_0value) !== (value)))
        {
            this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupItemBorderRadius_0_0value = value
        } else
        {
            this._popupItemBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    itemBorderRadius(value: number | undefined): this {
        if (((this._itemBorderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._itemBorderRadius_0_0value) !== (value)))
        {
            this._itemBorderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._itemBorderRadius_0_0value = value
        } else
        {
            this._itemBorderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupBackgroundBlurStyle(value: BlurStyle | undefined): this {
        if (((this._popupBackgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupBackgroundBlurStyle_0_0value = value
        } else
        {
            this._popupBackgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    popupTitleBackground(value: ResourceColor | undefined): this {
        if (((this._popupTitleBackground_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._popupTitleBackground_0_flag = AttributeUpdaterFlag.UPDATE
            this._popupTitleBackground_0_0value = value
        } else
        {
            this._popupTitleBackground_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        if (((this._enableHapticFeedback_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableHapticFeedback_0_0value) !== (value)))
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableHapticFeedback_0_0value = value
        } else
        {
            this._enableHapticFeedback_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alignStyle(value: IndexerAlign | undefined, offset?: Length): this {
        if (((this._alignStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._alignStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignStyle_0_0value = value
            this._alignStyle_0_1value = offset
        } else
        {
            this._alignStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        if (valueHolderForSelected instanceof number) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForSelectedForIdx0  = valueHolderForSelected as number
            valueSerializer.writeNumber(valueHolderForSelectedForIdx0)
        } else if (valueHolderForSelected instanceof Bindable<number>) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForSelectedForIdx1  = valueHolderForSelected as Bindable<number>
            Bindable_Number_serializer.write(valueSerializer, valueHolderForSelectedForIdx1)
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
        let selectedTmpBuf : number | Bindable<number> | undefined
        if (selectedTmpBufUnionSelector == (0).toChar()) {
            selectedTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (selectedTmpBufUnionSelector == (1).toChar()) {
            selectedTmpBuf = Bindable_Number_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for selectedTmpBuf has to be chosen through deserialisation.")
        }
        const selectedTmpResult : number | Bindable<number> = (selectedTmpBuf as number | Bindable<number>)
        let value : AlphabetIndexerOptions = ({arrayValue: arrayValueTmpResult, selected: selectedTmpResult} as AlphabetIndexerOptions)
        return value
    }
}
