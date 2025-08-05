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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, Finalizable } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { SymbolGlyphModifier_serializer, SymbolGlyphModifier } from "./../generated/arkui.SymbolGlyphModifier"
import { CaretStyle_serializer, EditMenuOptions_serializer, CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from "./textCommon"
import { Font_serializer, ResourceColor, Dimension, Font, ResourceStr, Length } from "./units"
import { TextDecorationOptions_serializer, ArkCommonMethodPeer, CommonMethod, TextDecorationOptions, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier, Bindable_String_serializer, SelectionOptions_serializer, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from "./common"
import { KeyboardOptions_serializer, PasteEvent, KeyboardOptions } from "./richEditor"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Color, CopyOptions, TextAlign } from "./enums"
import { EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from "./textInput"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkSearchPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSearchPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Search_construct(peerId, flags)
        const _peer  = new ArkSearchPeer(_peerPtr, peerId, 'Search', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSearchOptionsAttribute(options?: SearchOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SearchOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchInterface_setSearchOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SearchAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSearchIconAttribute(value: IconOptions | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof IconOptions) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as IconOptions
                IconOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setSearchIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCancelButtonAttribute(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof CancelButtonOptions) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as CancelButtonOptions
                CancelButtonOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof CancelButtonSymbolOptions) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as CancelButtonSymbolOptions
                CancelButtonSymbolOptions_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCancelButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIndentAttribute(value: Dimension | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEditChangeAttribute(value: ((value0: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnEditChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretStyleAttribute(value: CaretStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            CaretStyle_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCaretStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setTextFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnterKeyTypeAttribute(value: EnterKeyType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EnterKeyType)
            thisSerializer.writeInt32(TypeChecker.EnterKeyType_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setEnterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSubmitAttribute(value: ((value0: string) => void) | SearchSubmitCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ((value0: string) => void)) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ((value0: string) => void)
                thisSerializer.holdAndWriteCallback(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof SearchSubmitCallback) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as SearchSubmitCallback
                thisSerializer.holdAndWriteCallback(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: EditableTextOnChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: OnTextSelectionChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnContentScrollAttribute(value: OnContentScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnContentScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: ((value0: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCutAttribute(value: ((value0: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPasteAttribute(value: OnPasteCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLengthAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAlignAttribute(value: TextAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as TextAlign)
            thisSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setTextAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableKeyboardOnFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setEnableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionMenuHiddenAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setSelectionMenuHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: TextDecorationOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextDecorationOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLetterSpacingAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTypeAttribute(value: SearchType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SearchType)
            thisSerializer.writeInt32(TypeChecker.SearchType_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillInsertAttribute(value: ((value0: InsertValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidInsertAttribute(value: ((value0: InsertValue) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnDidInsert(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillDeleteAttribute(value: ((value0: DeleteValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidDeleteAttribute(value: ((value0: DeleteValue) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnDidDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            EditMenuOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnablePreviewTextAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setEnablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._SearchAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoCapitalizationModeAttribute(value: AutoCapitalizationMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as AutoCapitalizationMode)
            thisSerializer.writeInt32(TypeChecker.AutoCapitalizationMode_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setAutoCapitalizationMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHalfLeadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setHalfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStopBackPressAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setStopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillChangeAttribute(value: ((value0: EditableTextChangeValue) => boolean) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setOnWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAppearanceAttribute(value: KeyboardAppearance | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as KeyboardAppearance)
            thisSerializer.writeInt32(TypeChecker.KeyboardAppearance_ToNumeric(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setKeyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSearchButtonAttribute(value: ResourceStr | undefined, option?: SearchButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (option !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionTmpValue  = option!
            SearchButtonOptions_serializer.write(thisSerializer, optionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setSearchButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInputFilterAttribute(value: ResourceStr | undefined, error?: ((value0: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (error !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const errorTmpValue  = error!
            thisSerializer.holdAndWriteCallback(errorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setInputFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomKeyboardAttribute(value: CustomBuilder | undefined, options?: KeyboardOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            KeyboardOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCustomKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum CancelButtonStyle {
    CONSTANT = 0,
    INVISIBLE = 1,
    INPUT = 2
}
export enum SearchType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export interface SearchOptions {
    value?: string | Bindable<string>;
    placeholder?: ResourceStr;
    icon?: string;
    controller?: SearchController;
}
export interface IconOptions {
    size?: Length;
    color?: ResourceColor;
    src?: ResourceStr;
}
export interface SearchButtonOptions {
    fontSize?: Length;
    fontColor?: ResourceColor;
    autoDisable?: boolean;
}
export interface CancelButtonOptions {
    style?: CancelButtonStyle;
    icon?: IconOptions;
}
export interface CancelButtonSymbolOptions {
    style?: CancelButtonStyle;
    icon?: SymbolGlyphModifier;
}
export type SearchSubmitCallback = (searchContent: string, event?: SubmitEvent) => void;
export interface SearchAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method searchIcon")
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        throw new Error("Unimplemented method cancelButton")
    }
    textIndent(value: Dimension | undefined): this {
        throw new Error("Unimplemented method textIndent")
    }
    onEditChange(value: ((value0: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onEditChange")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    caretStyle(value: CaretStyle | undefined): this {
        throw new Error("Unimplemented method caretStyle")
    }
    placeholderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method placeholderColor")
    }
    placeholderFont(value: Font | undefined): this {
        throw new Error("Unimplemented method placeholderFont")
    }
    textFont(value: Font | undefined): this {
        throw new Error("Unimplemented method textFont")
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        throw new Error("Unimplemented method enterKeyType")
    }
    onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        throw new Error("Unimplemented method onSubmit")
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        throw new Error("Unimplemented method onTextSelectionChange")
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        throw new Error("Unimplemented method onContentScroll")
    }
    onCopy(value: ((value0: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCopy")
    }
    onCut(value: ((value0: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCut")
    }
    onPaste(value: OnPasteCallback | undefined): this {
        throw new Error("Unimplemented method onPaste")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    maxLength(value: number | undefined): this {
        throw new Error("Unimplemented method maxLength")
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error("Unimplemented method textAlign")
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableKeyboardOnFocus")
    }
    selectionMenuHidden(value: boolean | undefined): this {
        throw new Error("Unimplemented method selectionMenuHidden")
    }
    minFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontSize")
    }
    minFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    decoration(value: TextDecorationOptions | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method letterSpacing")
    }
    lineHeight(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    type(value: SearchType | undefined): this {
        throw new Error("Unimplemented method type")
    }
    fontFeature(value: string | undefined): this {
        throw new Error("Unimplemented method fontFeature")
    }
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillInsert")
    }
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        throw new Error("Unimplemented method onDidInsert")
    }
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillDelete")
    }
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        throw new Error("Unimplemented method onDidDelete")
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error("Unimplemented method editMenuOptions")
    }
    enablePreviewText(value: boolean | undefined): this {
        throw new Error("Unimplemented method enablePreviewText")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        throw new Error("Unimplemented method autoCapitalizationMode")
    }
    halfLeading(value: boolean | undefined): this {
        throw new Error("Unimplemented method halfLeading")
    }
    stopBackPress(value: boolean | undefined): this {
        throw new Error("Unimplemented method stopBackPress")
    }
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        throw new Error("Unimplemented method onWillChange")
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        throw new Error("Unimplemented method keyboardAppearance")
    }
    searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        throw new Error("Unimplemented method searchButton")
    }
    inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        throw new Error("Unimplemented method inputFilter")
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        throw new Error("Unimplemented method customKeyboard")
    }
    attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSearchStyle extends ArkCommonMethodStyle implements SearchAttribute {
    fontColor_value?: ResourceColor | undefined
    searchIcon_value?: IconOptions | SymbolGlyphModifier | undefined
    cancelButton_value?: CancelButtonOptions | CancelButtonSymbolOptions | undefined
    textIndent_value?: Dimension | undefined
    onEditChange_value?: ((value0: boolean) => void) | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    caretStyle_value?: CaretStyle | undefined
    placeholderColor_value?: ResourceColor | undefined
    placeholderFont_value?: Font | undefined
    textFont_value?: Font | undefined
    enterKeyType_value?: EnterKeyType | undefined
    onSubmit_value?: ((value0: string) => void) | SearchSubmitCallback | undefined
    onChange_value?: EditableTextOnChangeCallback | undefined
    onTextSelectionChange_value?: OnTextSelectionChangeCallback | undefined
    onContentScroll_value?: OnContentScrollCallback | undefined
    onCopy_value?: ((value0: string) => void) | undefined
    onCut_value?: ((value0: string) => void) | undefined
    onPaste_value?: OnPasteCallback | undefined
    copyOption_value?: CopyOptions | undefined
    maxLength_value?: number | undefined
    textAlign_value?: TextAlign | undefined
    enableKeyboardOnFocus_value?: boolean | undefined
    selectionMenuHidden_value?: boolean | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    decoration_value?: TextDecorationOptions | undefined
    letterSpacing_value?: number | string | Resource | undefined
    lineHeight_value?: number | string | Resource | undefined
    type_value?: SearchType | undefined
    fontFeature_value?: string | undefined
    onWillInsert_value?: ((value0: InsertValue) => boolean) | undefined
    onDidInsert_value?: ((value0: InsertValue) => void) | undefined
    onWillDelete_value?: ((value0: DeleteValue) => boolean) | undefined
    onDidDelete_value?: ((value0: DeleteValue) => void) | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    enablePreviewText_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    autoCapitalizationMode_value?: AutoCapitalizationMode | undefined
    halfLeading_value?: boolean | undefined
    stopBackPress_value?: boolean | undefined
    onWillChange_value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    keyboardAppearance_value?: KeyboardAppearance | undefined
    attributeModifier_value?: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        return this
    }
    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        return this
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        return this
    }
    public textFont(value: Font | undefined): this {
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        return this
    }
    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        return this
    }
    public onCopy(value: ((value0: string) => void) | undefined): this {
        return this
    }
    public onCut(value: ((value0: string) => void) | undefined): this {
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public maxLength(value: number | undefined): this {
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        return this
    }
    public type(value: SearchType | undefined): this {
        return this
    }
    public fontFeature(value: string | undefined): this {
        return this
    }
    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        return this
    }
    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        return this
    }
    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        return this
    }
    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        return this
    }
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        return this
    }
    public searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkSearchComponent extends ArkCommonMethodComponent implements SearchAttribute {
    getPeer(): ArkSearchPeer {
        return (this.peer as ArkSearchPeer)
    }
    public setSearchOptions(options?: SearchOptions): this {
        if (this.checkPriority("setSearchOptions")) {
            const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("searchIcon")) {
            const value_casted = value as (IconOptions | SymbolGlyphModifier | undefined)
            this.getPeer()?.setSearchIconAttribute(value_casted)
            return this
        }
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if (this.checkPriority("cancelButton")) {
            const value_casted = value as (CancelButtonOptions | CancelButtonSymbolOptions | undefined)
            this.getPeer()?.setCancelButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setTextIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditChange(value: ((value0: boolean) => void) | undefined): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((value0: boolean) => void) | undefined)
            this.getPeer()?.setOnEditChangeAttribute(value_casted)
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
    public caretStyle(value: CaretStyle | undefined): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle | undefined)
            this.getPeer()?.setCaretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("placeholderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPlaceholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderFont(value: Font | undefined): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setPlaceholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    public textFont(value: Font | undefined): this {
        if (this.checkPriority("textFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setTextFontAttribute(value_casted)
            return this
        }
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType | undefined)
            this.getPeer()?.setEnterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (((value0: string) => void) | SearchSubmitCallback | undefined)
            this.getPeer()?.setOnSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (OnTextSelectionChangeCallback | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (OnContentScrollCallback | undefined)
            this.getPeer()?.setOnContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value0: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value0: string) => void) | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: ((value0: string) => void) | undefined): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((value0: string) => void) | undefined)
            this.getPeer()?.setOnCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (OnPasteCallback | undefined)
            this.getPeer()?.setOnPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLength(value: number | undefined): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.setTextAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | Resource | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: SearchType | undefined): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (SearchType | undefined)
            this.getPeer()?.setTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((value0: InsertValue) => boolean) | undefined)
            this.getPeer()?.setOnWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((value0: InsertValue) => void) | undefined)
            this.getPeer()?.setOnDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((value0: DeleteValue) => boolean) | undefined)
            this.getPeer()?.setOnWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((value0: DeleteValue) => void) | undefined)
            this.getPeer()?.setOnDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePreviewTextAttribute(value_casted)
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
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (this.checkPriority("autoCapitalizationMode")) {
            const value_casted = value as (AutoCapitalizationMode | undefined)
            this.getPeer()?.setAutoCapitalizationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHalfLeadingAttribute(value_casted)
            return this
        }
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        if (this.checkPriority("stopBackPress")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStopBackPressAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((value0: EditableTextChangeValue) => boolean) | undefined)
            this.getPeer()?.setOnWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (this.checkPriority("keyboardAppearance")) {
            const value_casted = value as (KeyboardAppearance | undefined)
            this.getPeer()?.setKeyboardAppearanceAttribute(value_casted)
            return this
        }
        return this
    }
    public searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        if (this.checkPriority("searchButton")) {
            const value_casted = value as (ResourceStr | undefined)
            const option_casted = option as (SearchButtonOptions | undefined)
            this.getPeer()?.setSearchButtonAttribute(value_casted, option_casted)
            return this
        }
        return this
    }
    public inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr | undefined)
            const error_casted = error as (((value0: string) => void) | undefined)
            this.getPeer()?.setInputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.setCustomKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

@memo
export function Search(
    @memo
    style: ((attributes: SearchAttribute) => void) | undefined,
    options?: SearchOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSearchComponent>((): ArkSearchComponent => {
        return new ArkSearchComponent()
    })
    NodeAttach<ArkSearchPeer>((): ArkSearchPeer => ArkSearchPeer.create(receiver), (_: ArkSearchPeer): void => {
        receiver.setSearchOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class SearchModifier extends CommonMethodModifier implements SearchAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: ResourceColor | undefined
    _searchIcon_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _searchIcon_0_0value?: IconOptions | SymbolGlyphModifier | undefined
    _cancelButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _cancelButton_0_0value?: CancelButtonOptions | CancelButtonSymbolOptions | undefined
    _textIndent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textIndent_0_0value?: Dimension | undefined
    _onEditChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onEditChange_0_0value?: ((value0: boolean) => void) | undefined
    _selectedBackgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedBackgroundColor_0_0value?: ResourceColor | undefined
    _caretStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _caretStyle_0_0value?: CaretStyle | undefined
    _placeholderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderColor_0_0value?: ResourceColor | undefined
    _placeholderFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _placeholderFont_0_0value?: Font | undefined
    _textFont_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textFont_0_0value?: Font | undefined
    _enterKeyType_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enterKeyType_0_0value?: EnterKeyType | undefined
    _onSubmit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSubmit_0_0value?: ((value0: string) => void) | SearchSubmitCallback | undefined
    _onChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChange_0_0value?: EditableTextOnChangeCallback | undefined
    _onTextSelectionChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTextSelectionChange_0_0value?: OnTextSelectionChangeCallback | undefined
    _onContentScroll_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onContentScroll_0_0value?: OnContentScrollCallback | undefined
    _onCopy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCopy_0_0value?: ((value0: string) => void) | undefined
    _onCut_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCut_0_0value?: ((value0: string) => void) | undefined
    _onPaste_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPaste_0_0value?: OnPasteCallback | undefined
    _copyOption_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _copyOption_0_0value?: CopyOptions | undefined
    _maxLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxLength_0_0value?: number | undefined
    _textAlign_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _textAlign_0_0value?: TextAlign | undefined
    _enableKeyboardOnFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableKeyboardOnFocus_0_0value?: boolean | undefined
    _selectionMenuHidden_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectionMenuHidden_0_0value?: boolean | undefined
    _minFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontSize_0_0value?: number | string | Resource | undefined
    _maxFontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontSize_0_0value?: number | string | Resource | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: number | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: number | Resource | undefined
    _decoration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _decoration_0_0value?: TextDecorationOptions | undefined
    _letterSpacing_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _letterSpacing_0_0value?: number | string | Resource | undefined
    _lineHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lineHeight_0_0value?: number | string | Resource | undefined
    _type_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _type_0_0value?: SearchType | undefined
    _fontFeature_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontFeature_0_0value?: string | undefined
    _onWillInsert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillInsert_0_0value?: ((value0: InsertValue) => boolean) | undefined
    _onDidInsert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidInsert_0_0value?: ((value0: InsertValue) => void) | undefined
    _onWillDelete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillDelete_0_0value?: ((value0: DeleteValue) => boolean) | undefined
    _onDidDelete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDidDelete_0_0value?: ((value0: DeleteValue) => void) | undefined
    _editMenuOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _editMenuOptions_0_0value?: EditMenuOptions | undefined
    _enablePreviewText_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enablePreviewText_0_0value?: boolean | undefined
    _enableHapticFeedback_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableHapticFeedback_0_0value?: boolean | undefined
    _autoCapitalizationMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoCapitalizationMode_0_0value?: AutoCapitalizationMode | undefined
    _halfLeading_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _halfLeading_0_0value?: boolean | undefined
    _stopBackPress_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _stopBackPress_0_0value?: boolean | undefined
    _onWillChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onWillChange_0_0value?: ((value0: EditableTextChangeValue) => boolean) | undefined
    _keyboardAppearance_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardAppearance_0_0value?: KeyboardAppearance | undefined
    _searchButton_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _searchButton_0_0value?: ResourceStr | undefined
    _searchButton_0_1value?: SearchButtonOptions | undefined
    _inputFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _inputFilter_0_0value?: ResourceStr | undefined
    _inputFilter_0_1value?: ((value0: string) => void) | undefined
    _customKeyboard_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customKeyboard_0_0value?: CustomBuilder | undefined
    _customKeyboard_0_1value?: KeyboardOptions | undefined
    applyModifierPatch(peer: ArkSearchPeer): void {
        super.applyModifierPatch(peer)
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as ResourceColor | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._searchIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._searchIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSearchIconAttribute((this._searchIcon_0_0value as IconOptions | SymbolGlyphModifier | undefined));
                    this._searchIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._searchIcon_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._searchIcon_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSearchIconAttribute((undefined as IconOptions | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (this._cancelButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._cancelButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCancelButtonAttribute((this._cancelButton_0_0value as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                    this._cancelButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._cancelButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._cancelButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCancelButtonAttribute((undefined as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                }
            }
        }
        if (this._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextIndentAttribute((this._textIndent_0_0value as Dimension | undefined));
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textIndent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextIndentAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnEditChangeAttribute((this._onEditChange_0_0value as ((value0: boolean) => void) | undefined));
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onEditChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnEditChangeAttribute((undefined as ((value0: boolean) => void) | undefined));
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
        if (this._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._caretStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCaretStyleAttribute((this._caretStyle_0_0value as CaretStyle | undefined));
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._caretStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCaretStyleAttribute((undefined as CaretStyle | undefined));
                }
            }
        }
        if (this._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._placeholderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlaceholderColorAttribute((this._placeholderColor_0_0value as ResourceColor | undefined));
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlaceholderColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._placeholderFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlaceholderFontAttribute((this._placeholderFont_0_0value as Font | undefined));
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._placeholderFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlaceholderFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._textFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextFontAttribute((this._textFont_0_0value as Font | undefined));
                    this._textFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textFont_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textFont_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextFontAttribute((undefined as Font | undefined));
                }
            }
        }
        if (this._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnterKeyTypeAttribute((this._enterKeyType_0_0value as EnterKeyType | undefined));
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enterKeyType_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnterKeyTypeAttribute((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (this._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSubmitAttribute((this._onSubmit_0_0value as ((value0: string) => void) | SearchSubmitCallback | undefined));
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSubmit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSubmitAttribute((undefined as ((value0: string) => void) | SearchSubmitCallback | undefined));
                }
            }
        }
        if (this._onChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as EditableTextOnChangeCallback | undefined));
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChangeAttribute((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (this._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTextSelectionChangeAttribute((this._onTextSelectionChange_0_0value as OnTextSelectionChangeCallback | undefined));
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTextSelectionChangeAttribute((undefined as OnTextSelectionChangeCallback | undefined));
                }
            }
        }
        if (this._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnContentScrollAttribute((this._onContentScroll_0_0value as OnContentScrollCallback | undefined));
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onContentScroll_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnContentScrollAttribute((undefined as OnContentScrollCallback | undefined));
                }
            }
        }
        if (this._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCopyAttribute((this._onCopy_0_0value as ((value0: string) => void) | undefined));
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCopy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCopyAttribute((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (this._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCutAttribute((this._onCut_0_0value as ((value0: string) => void) | undefined));
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCut_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCutAttribute((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (this._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPasteAttribute((this._onPaste_0_0value as OnPasteCallback | undefined));
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPaste_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPasteAttribute((undefined as OnPasteCallback | undefined));
                }
            }
        }
        if (this._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCopyOptionAttribute((this._copyOption_0_0value as CopyOptions | undefined));
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._copyOption_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCopyOptionAttribute((undefined as CopyOptions | undefined));
                }
            }
        }
        if (this._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxLengthAttribute((this._maxLength_0_0value as number | undefined));
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxLengthAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._textAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._textAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTextAlignAttribute((this._textAlign_0_0value as TextAlign | undefined));
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._textAlign_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTextAlignAttribute((undefined as TextAlign | undefined));
                }
            }
        }
        if (this._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableKeyboardOnFocusAttribute((this._enableKeyboardOnFocus_0_0value as boolean | undefined));
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableKeyboardOnFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectionMenuHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectionMenuHiddenAttribute((this._selectionMenuHidden_0_0value as boolean | undefined));
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectionMenuHiddenAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontSizeAttribute((this._minFontSize_0_0value as number | string | Resource | undefined));
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontSizeAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontSizeAttribute((this._maxFontSize_0_0value as number | string | Resource | undefined));
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontSizeAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as number | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as number | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDecorationAttribute((this._decoration_0_0value as TextDecorationOptions | undefined));
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._decoration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._decoration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDecorationAttribute((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (this._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLetterSpacingAttribute((this._letterSpacing_0_0value as number | string | Resource | undefined));
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._letterSpacing_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLetterSpacingAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLineHeightAttribute((this._lineHeight_0_0value as number | string | Resource | undefined));
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lineHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLineHeightAttribute((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (this._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTypeAttribute((this._type_0_0value as SearchType | undefined));
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._type_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._type_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTypeAttribute((undefined as SearchType | undefined));
                }
            }
        }
        if (this._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontFeature_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontFeatureAttribute((this._fontFeature_0_0value as string | undefined));
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontFeature_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontFeatureAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillInsertAttribute((this._onWillInsert_0_0value as ((value0: InsertValue) => boolean) | undefined));
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillInsertAttribute((undefined as ((value0: InsertValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidInsertAttribute((this._onDidInsert_0_0value as ((value0: InsertValue) => void) | undefined));
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidInsert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidInsertAttribute((undefined as ((value0: InsertValue) => void) | undefined));
                }
            }
        }
        if (this._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillDeleteAttribute((this._onWillDelete_0_0value as ((value0: DeleteValue) => boolean) | undefined));
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillDeleteAttribute((undefined as ((value0: DeleteValue) => boolean) | undefined));
                }
            }
        }
        if (this._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDidDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDidDeleteAttribute((this._onDidDelete_0_0value as ((value0: DeleteValue) => void) | undefined));
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDidDelete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDidDeleteAttribute((undefined as ((value0: DeleteValue) => void) | undefined));
                }
            }
        }
        if (this._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEditMenuOptionsAttribute((this._editMenuOptions_0_0value as EditMenuOptions | undefined));
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._editMenuOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEditMenuOptionsAttribute((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (this._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnablePreviewTextAttribute((this._enablePreviewText_0_0value as boolean | undefined));
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enablePreviewText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnablePreviewTextAttribute((undefined as boolean | undefined));
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
        if (this._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoCapitalizationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoCapitalizationModeAttribute((this._autoCapitalizationMode_0_0value as AutoCapitalizationMode | undefined));
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoCapitalizationModeAttribute((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (this._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._halfLeading_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHalfLeadingAttribute((this._halfLeading_0_0value as boolean | undefined));
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._halfLeading_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHalfLeadingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStopBackPressAttribute((this._stopBackPress_0_0value as boolean | undefined));
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._stopBackPress_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStopBackPressAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnWillChangeAttribute((this._onWillChange_0_0value as ((value0: EditableTextChangeValue) => boolean) | undefined));
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onWillChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnWillChangeAttribute((undefined as ((value0: EditableTextChangeValue) => boolean) | undefined));
                }
            }
        }
        if (this._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyboardAppearanceAttribute((this._keyboardAppearance_0_0value as KeyboardAppearance | undefined));
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardAppearance_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyboardAppearanceAttribute((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (this._searchButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._searchButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSearchButtonAttribute((this._searchButton_0_0value as ResourceStr | undefined), (this._searchButton_0_1value as SearchButtonOptions | undefined));
                    this._searchButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._searchButton_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._searchButton_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSearchButtonAttribute((undefined as ResourceStr | undefined), (undefined as SearchButtonOptions | undefined | undefined));
                }
            }
        }
        if (this._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInputFilterAttribute((this._inputFilter_0_0value as ResourceStr | undefined), (this._inputFilter_0_1value as ((value0: string) => void) | undefined));
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._inputFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInputFilterAttribute((undefined as ResourceStr | undefined), (undefined as ((value0: string) => void) | undefined | undefined));
                }
            }
        }
        if (this._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomKeyboardAttribute((this._customKeyboard_0_0value as CustomBuilder | undefined), (this._customKeyboard_0_1value as KeyboardOptions | undefined));
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customKeyboard_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomKeyboardAttribute((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SearchModifier): void {
        super.mergeModifier(modifier)
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._searchIcon_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._searchIcon_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.searchIcon(modifier._searchIcon_0_0value);
                    break;
                }
                default: {
                    this.searchIcon((undefined as IconOptions | SymbolGlyphModifier | undefined));
                }
            }
        }
        if (modifier._cancelButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._cancelButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.cancelButton(modifier._cancelButton_0_0value);
                    break;
                }
                default: {
                    this.cancelButton((undefined as CancelButtonOptions | CancelButtonSymbolOptions | undefined));
                }
            }
        }
        if (modifier._textIndent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textIndent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textIndent(modifier._textIndent_0_0value);
                    break;
                }
                default: {
                    this.textIndent((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._onEditChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onEditChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onEditChange(modifier._onEditChange_0_0value);
                    break;
                }
                default: {
                    this.onEditChange((undefined as ((value0: boolean) => void) | undefined));
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
        if (modifier._caretStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._caretStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.caretStyle(modifier._caretStyle_0_0value);
                    break;
                }
                default: {
                    this.caretStyle((undefined as CaretStyle | undefined));
                }
            }
        }
        if (modifier._placeholderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._placeholderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.placeholderColor(modifier._placeholderColor_0_0value);
                    break;
                }
                default: {
                    this.placeholderColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._placeholderFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._placeholderFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.placeholderFont(modifier._placeholderFont_0_0value);
                    break;
                }
                default: {
                    this.placeholderFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._textFont_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textFont_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textFont(modifier._textFont_0_0value);
                    break;
                }
                default: {
                    this.textFont((undefined as Font | undefined));
                }
            }
        }
        if (modifier._enterKeyType_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enterKeyType_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enterKeyType(modifier._enterKeyType_0_0value);
                    break;
                }
                default: {
                    this.enterKeyType((undefined as EnterKeyType | undefined));
                }
            }
        }
        if (modifier._onSubmit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSubmit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSubmit(modifier._onSubmit_0_0value);
                    break;
                }
                default: {
                    this.onSubmit((undefined as ((value0: string) => void) | SearchSubmitCallback | undefined));
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
                    this.onChange((undefined as EditableTextOnChangeCallback | undefined));
                }
            }
        }
        if (modifier._onTextSelectionChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTextSelectionChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTextSelectionChange(modifier._onTextSelectionChange_0_0value);
                    break;
                }
                default: {
                    this.onTextSelectionChange((undefined as OnTextSelectionChangeCallback | undefined));
                }
            }
        }
        if (modifier._onContentScroll_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onContentScroll_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onContentScroll(modifier._onContentScroll_0_0value);
                    break;
                }
                default: {
                    this.onContentScroll((undefined as OnContentScrollCallback | undefined));
                }
            }
        }
        if (modifier._onCopy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCopy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCopy(modifier._onCopy_0_0value);
                    break;
                }
                default: {
                    this.onCopy((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (modifier._onCut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCut_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCut(modifier._onCut_0_0value);
                    break;
                }
                default: {
                    this.onCut((undefined as ((value0: string) => void) | undefined));
                }
            }
        }
        if (modifier._onPaste_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPaste_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPaste(modifier._onPaste_0_0value);
                    break;
                }
                default: {
                    this.onPaste((undefined as OnPasteCallback | undefined));
                }
            }
        }
        if (modifier._copyOption_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._copyOption_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.copyOption(modifier._copyOption_0_0value);
                    break;
                }
                default: {
                    this.copyOption((undefined as CopyOptions | undefined));
                }
            }
        }
        if (modifier._maxLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxLength(modifier._maxLength_0_0value);
                    break;
                }
                default: {
                    this.maxLength((undefined as number | undefined));
                }
            }
        }
        if (modifier._textAlign_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._textAlign_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.textAlign(modifier._textAlign_0_0value);
                    break;
                }
                default: {
                    this.textAlign((undefined as TextAlign | undefined));
                }
            }
        }
        if (modifier._enableKeyboardOnFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableKeyboardOnFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableKeyboardOnFocus(modifier._enableKeyboardOnFocus_0_0value);
                    break;
                }
                default: {
                    this.enableKeyboardOnFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._selectionMenuHidden_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectionMenuHidden_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectionMenuHidden(modifier._selectionMenuHidden_0_0value);
                    break;
                }
                default: {
                    this.selectionMenuHidden((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._minFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontSize(modifier._minFontSize_0_0value);
                    break;
                }
                default: {
                    this.minFontSize((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontSize(modifier._maxFontSize_0_0value);
                    break;
                }
                default: {
                    this.maxFontSize((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._decoration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._decoration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.decoration(modifier._decoration_0_0value);
                    break;
                }
                default: {
                    this.decoration((undefined as TextDecorationOptions | undefined));
                }
            }
        }
        if (modifier._letterSpacing_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._letterSpacing_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.letterSpacing(modifier._letterSpacing_0_0value);
                    break;
                }
                default: {
                    this.letterSpacing((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._lineHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lineHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lineHeight(modifier._lineHeight_0_0value);
                    break;
                }
                default: {
                    this.lineHeight((undefined as number | string | Resource | undefined));
                }
            }
        }
        if (modifier._type_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._type_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.type(modifier._type_0_0value);
                    break;
                }
                default: {
                    this.type((undefined as SearchType | undefined));
                }
            }
        }
        if (modifier._fontFeature_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontFeature_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontFeature(modifier._fontFeature_0_0value);
                    break;
                }
                default: {
                    this.fontFeature((undefined as string | undefined));
                }
            }
        }
        if (modifier._onWillInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillInsert(modifier._onWillInsert_0_0value);
                    break;
                }
                default: {
                    this.onWillInsert((undefined as ((value0: InsertValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDidInsert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidInsert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidInsert(modifier._onDidInsert_0_0value);
                    break;
                }
                default: {
                    this.onDidInsert((undefined as ((value0: InsertValue) => void) | undefined));
                }
            }
        }
        if (modifier._onWillDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillDelete(modifier._onWillDelete_0_0value);
                    break;
                }
                default: {
                    this.onWillDelete((undefined as ((value0: DeleteValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._onDidDelete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDidDelete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDidDelete(modifier._onDidDelete_0_0value);
                    break;
                }
                default: {
                    this.onDidDelete((undefined as ((value0: DeleteValue) => void) | undefined));
                }
            }
        }
        if (modifier._editMenuOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._editMenuOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.editMenuOptions(modifier._editMenuOptions_0_0value);
                    break;
                }
                default: {
                    this.editMenuOptions((undefined as EditMenuOptions | undefined));
                }
            }
        }
        if (modifier._enablePreviewText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enablePreviewText_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enablePreviewText(modifier._enablePreviewText_0_0value);
                    break;
                }
                default: {
                    this.enablePreviewText((undefined as boolean | undefined));
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
        if (modifier._autoCapitalizationMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoCapitalizationMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoCapitalizationMode(modifier._autoCapitalizationMode_0_0value);
                    break;
                }
                default: {
                    this.autoCapitalizationMode((undefined as AutoCapitalizationMode | undefined));
                }
            }
        }
        if (modifier._halfLeading_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._halfLeading_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.halfLeading(modifier._halfLeading_0_0value);
                    break;
                }
                default: {
                    this.halfLeading((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._stopBackPress_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._stopBackPress_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.stopBackPress(modifier._stopBackPress_0_0value);
                    break;
                }
                default: {
                    this.stopBackPress((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onWillChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onWillChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onWillChange(modifier._onWillChange_0_0value);
                    break;
                }
                default: {
                    this.onWillChange((undefined as ((value0: EditableTextChangeValue) => boolean) | undefined));
                }
            }
        }
        if (modifier._keyboardAppearance_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._keyboardAppearance_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardAppearance(modifier._keyboardAppearance_0_0value);
                    break;
                }
                default: {
                    this.keyboardAppearance((undefined as KeyboardAppearance | undefined));
                }
            }
        }
        if (modifier._searchButton_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._searchButton_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.searchButton(modifier._searchButton_0_0value, modifier._searchButton_0_1value);
                    break;
                }
                default: {
                    this.searchButton((undefined as ResourceStr | undefined), (undefined as SearchButtonOptions | undefined | undefined));
                }
            }
        }
        if (modifier._inputFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._inputFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.inputFilter(modifier._inputFilter_0_0value, modifier._inputFilter_0_1value);
                    break;
                }
                default: {
                    this.inputFilter((undefined as ResourceStr | undefined), (undefined as ((value0: string) => void) | undefined | undefined));
                }
            }
        }
        if (modifier._customKeyboard_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customKeyboard_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customKeyboard(modifier._customKeyboard_0_0value, modifier._customKeyboard_0_1value);
                    break;
                }
                default: {
                    this.customKeyboard((undefined as CustomBuilder | undefined), (undefined as KeyboardOptions | undefined | undefined));
                }
            }
        }
    }
    fontColor(value: ResourceColor | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        if (((this._searchIcon_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._searchIcon_0_flag = AttributeUpdaterFlag.UPDATE
            this._searchIcon_0_0value = value
        } else
        {
            this._searchIcon_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if (((this._cancelButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._cancelButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._cancelButton_0_0value = value
        } else
        {
            this._cancelButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textIndent(value: Dimension | undefined): this {
        if (((this._textIndent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textIndent_0_flag = AttributeUpdaterFlag.UPDATE
            this._textIndent_0_0value = value
        } else
        {
            this._textIndent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onEditChange(value: ((value0: boolean) => void) | undefined): this {
        if (((this._onEditChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onEditChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onEditChange_0_0value = value
        } else
        {
            this._onEditChange_0_flag = AttributeUpdaterFlag.SKIP
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
    caretStyle(value: CaretStyle | undefined): this {
        if (((this._caretStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._caretStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._caretStyle_0_0value = value
        } else
        {
            this._caretStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    placeholderColor(value: ResourceColor | undefined): this {
        if (((this._placeholderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderColor_0_0value = value
        } else
        {
            this._placeholderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    placeholderFont(value: Font | undefined): this {
        if (((this._placeholderFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._placeholderFont_0_0value = value
        } else
        {
            this._placeholderFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textFont(value: Font | undefined): this {
        if (((this._textFont_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textFont_0_flag = AttributeUpdaterFlag.UPDATE
            this._textFont_0_0value = value
        } else
        {
            this._textFont_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        if (((this._enterKeyType_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.UPDATE
            this._enterKeyType_0_0value = value
        } else
        {
            this._enterKeyType_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSubmit(value: ((value0: string) => void) | SearchSubmitCallback | undefined): this {
        if (((this._onSubmit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSubmit_0_0value = value
        } else
        {
            this._onSubmit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
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
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        if (((this._onTextSelectionChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTextSelectionChange_0_0value = value
        } else
        {
            this._onTextSelectionChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        if (((this._onContentScroll_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.UPDATE
            this._onContentScroll_0_0value = value
        } else
        {
            this._onContentScroll_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCopy(value: ((value0: string) => void) | undefined): this {
        if (((this._onCopy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCopy_0_0value = value
        } else
        {
            this._onCopy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCut(value: ((value0: string) => void) | undefined): this {
        if (((this._onCut_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCut_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCut_0_0value = value
        } else
        {
            this._onCut_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPaste(value: OnPasteCallback | undefined): this {
        if (((this._onPaste_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPaste_0_0value = value
        } else
        {
            this._onPaste_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        if (((this._copyOption_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.UPDATE
            this._copyOption_0_0value = value
        } else
        {
            this._copyOption_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxLength(value: number | undefined): this {
        if (((this._maxLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._maxLength_0_0value) !== (value)))
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxLength_0_0value = value
        } else
        {
            this._maxLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        if (((this._textAlign_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._textAlign_0_flag = AttributeUpdaterFlag.UPDATE
            this._textAlign_0_0value = value
        } else
        {
            this._textAlign_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        if (((this._enableKeyboardOnFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableKeyboardOnFocus_0_0value) !== (value)))
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableKeyboardOnFocus_0_0value = value
        } else
        {
            this._enableKeyboardOnFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectionMenuHidden(value: boolean | undefined): this {
        if (((this._selectionMenuHidden_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._selectionMenuHidden_0_0value) !== (value)))
        {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectionMenuHidden_0_0value = value
        } else
        {
            this._selectionMenuHidden_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontSize(value: number | string | Resource | undefined): this {
        if (((this._minFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontSize_0_0value = value
        } else
        {
            this._minFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        if (((this._maxFontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontSize_0_0value = value
        } else
        {
            this._maxFontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: number | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: number | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    decoration(value: TextDecorationOptions | undefined): this {
        if (((this._decoration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._decoration_0_flag = AttributeUpdaterFlag.UPDATE
            this._decoration_0_0value = value
        } else
        {
            this._decoration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    letterSpacing(value: number | string | Resource | undefined): this {
        if (((this._letterSpacing_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.UPDATE
            this._letterSpacing_0_0value = value
        } else
        {
            this._letterSpacing_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lineHeight(value: number | string | Resource | undefined): this {
        if (((this._lineHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._lineHeight_0_0value = value
        } else
        {
            this._lineHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    type(value: SearchType | undefined): this {
        if (((this._type_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._type_0_flag = AttributeUpdaterFlag.UPDATE
            this._type_0_0value = value
        } else
        {
            this._type_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontFeature(value: string | undefined): this {
        if (((this._fontFeature_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fontFeature_0_0value) !== (value)))
        {
            this._fontFeature_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontFeature_0_0value = value
        } else
        {
            this._fontFeature_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): this {
        if (((this._onWillInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillInsert_0_0value = value
        } else
        {
            this._onWillInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): this {
        if (((this._onDidInsert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidInsert_0_0value = value
        } else
        {
            this._onDidInsert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): this {
        if (((this._onWillDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillDelete_0_0value = value
        } else
        {
            this._onWillDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): this {
        if (((this._onDidDelete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDidDelete_0_0value = value
        } else
        {
            this._onDidDelete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        if (((this._editMenuOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._editMenuOptions_0_0value = value
        } else
        {
            this._editMenuOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enablePreviewText(value: boolean | undefined): this {
        if (((this._enablePreviewText_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enablePreviewText_0_0value) !== (value)))
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.UPDATE
            this._enablePreviewText_0_0value = value
        } else
        {
            this._enablePreviewText_0_flag = AttributeUpdaterFlag.SKIP
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
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (((this._autoCapitalizationMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoCapitalizationMode_0_0value = value
        } else
        {
            this._autoCapitalizationMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    halfLeading(value: boolean | undefined): this {
        if (((this._halfLeading_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._halfLeading_0_0value) !== (value)))
        {
            this._halfLeading_0_flag = AttributeUpdaterFlag.UPDATE
            this._halfLeading_0_0value = value
        } else
        {
            this._halfLeading_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    stopBackPress(value: boolean | undefined): this {
        if (((this._stopBackPress_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._stopBackPress_0_0value) !== (value)))
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.UPDATE
            this._stopBackPress_0_0value = value
        } else
        {
            this._stopBackPress_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): this {
        if (((this._onWillChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onWillChange_0_0value = value
        } else
        {
            this._onWillChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (((this._keyboardAppearance_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardAppearance_0_0value = value
        } else
        {
            this._keyboardAppearance_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    searchButton(value: ResourceStr | undefined, option?: SearchButtonOptions): this {
        if (((this._searchButton_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._searchButton_0_flag = AttributeUpdaterFlag.UPDATE
            this._searchButton_0_0value = value
            this._searchButton_0_1value = option
        } else
        {
            this._searchButton_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void)): this {
        if (((this._inputFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._inputFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._inputFilter_0_0value = value
            this._inputFilter_0_1value = error
        } else
        {
            this._inputFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (((this._customKeyboard_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.UPDATE
            this._customKeyboard_0_0value = value
            this._customKeyboard_0_1value = options
        } else
        {
            this._customKeyboard_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SearchController_serializer {
    public static write(buffer: SerializerBase, value: SearchController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SearchController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SearchControllerInternal.fromPtr(ptr)
    }
}
export class CancelButtonSymbolOptions_serializer {
    public static write(buffer: SerializerBase, value: CancelButtonSymbolOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as CancelButtonStyle)
            valueSerializer.writeInt32(TypeChecker.CancelButtonStyle_ToNumeric(valueHolderForStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CancelButtonSymbolOptions {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : CancelButtonStyle | undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TypeChecker.CancelButtonStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const styleTmpResult : CancelButtonStyle | undefined = styleTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : SymbolGlyphModifier | undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = SymbolGlyphModifier_serializer.read(valueDeserializer)
        }
        const iconTmpResult : SymbolGlyphModifier | undefined = iconTmpBuf
        let value : CancelButtonSymbolOptions = ({style: styleTmpResult, icon: iconTmpResult} as CancelButtonSymbolOptions)
        return value
    }
}
export class SearchOptions_serializer {
    public static write(buffer: SerializerBase, value: SearchOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        if (valueHolderForValue !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueTmpValue  = valueHolderForValue!
            if (valueHolderForValueTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as string
                valueSerializer.writeString(valueHolderForValueTmpValueForIdx0)
            } else if (valueHolderForValueTmpValue instanceof Bindable<string>) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForValueTmpValueForIdx1  = valueHolderForValueTmpValue as Bindable<string>
                Bindable_String_serializer.write(valueSerializer, valueHolderForValueTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPlaceholder  = value.placeholder
        if (valueHolderForPlaceholder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPlaceholderTmpValue  = valueHolderForPlaceholder!
            if (valueHolderForPlaceholderTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForPlaceholderTmpValueForIdx0  = valueHolderForPlaceholderTmpValue as string
                valueSerializer.writeString(valueHolderForPlaceholderTmpValueForIdx0)
            } else if (valueHolderForPlaceholderTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForPlaceholderTmpValueForIdx1  = valueHolderForPlaceholderTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            valueSerializer.writeString(valueHolderForIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForController  = value.controller
        if (valueHolderForController !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForControllerTmpValue  = valueHolderForController!
            SearchController_serializer.write(valueSerializer, valueHolderForControllerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SearchOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let valueTmpBuf : string | Bindable<string> | undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBuf_ : string | Bindable<string> | undefined
            if (valueTmpBuf_UnionSelector == (0).toChar()) {
                valueTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (valueTmpBuf_UnionSelector == (1).toChar()) {
                valueTmpBuf_ = Bindable_String_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for valueTmpBuf_ has to be chosen through deserialisation.")
            }
            valueTmpBuf = (valueTmpBuf_ as string | Bindable<string>)
        }
        const valueTmpResult : string | Bindable<string> | undefined = valueTmpBuf
        const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let placeholderTmpBuf : ResourceStr | undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const placeholderTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let placeholderTmpBuf_ : string | Resource | undefined
            if (placeholderTmpBuf_UnionSelector == (0).toChar()) {
                placeholderTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (placeholderTmpBuf_UnionSelector == (1).toChar()) {
                placeholderTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for placeholderTmpBuf_ has to be chosen through deserialisation.")
            }
            placeholderTmpBuf = (placeholderTmpBuf_ as string | Resource)
        }
        const placeholderTmpResult : ResourceStr | undefined = placeholderTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : string | undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = (valueDeserializer.readString() as string)
        }
        const iconTmpResult : string | undefined = iconTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controllerTmpBuf : SearchController | undefined
        if ((controllerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            controllerTmpBuf = (SearchController_serializer.read(valueDeserializer) as SearchController)
        }
        const controllerTmpResult : SearchController | undefined = controllerTmpBuf
        let value : SearchOptions = ({value: valueTmpResult, placeholder: placeholderTmpResult, icon: iconTmpResult, controller: controllerTmpResult} as SearchOptions)
        return value
    }
}
export class IconOptions_serializer {
    public static write(buffer: SerializerBase, value: IconOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            if (valueHolderForSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSizeTmpValueForIdx0  = valueHolderForSizeTmpValue as string
                valueSerializer.writeString(valueHolderForSizeTmpValueForIdx0)
            } else if (valueHolderForSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSizeTmpValueForIdx1  = valueHolderForSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValueForIdx1)
            } else if (valueHolderForSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForSizeTmpValueForIdx2  = valueHolderForSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForColorTmpValueForIdx0))
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue  = valueHolderForSrc!
            if (valueHolderForSrcTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSrcTmpValueForIdx0  = valueHolderForSrcTmpValue as string
                valueSerializer.writeString(valueHolderForSrcTmpValueForIdx0)
            } else if (valueHolderForSrcTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSrcTmpValueForIdx1  = valueHolderForSrcTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSrcTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): IconOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : Length | undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBuf_ : string | number | Resource | undefined
            if (sizeTmpBuf_UnionSelector == (0).toChar()) {
                sizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (sizeTmpBuf_UnionSelector == (1).toChar()) {
                sizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBuf_UnionSelector == (2).toChar()) {
                sizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for sizeTmpBuf_ has to be chosen through deserialisation.")
            }
            sizeTmpBuf = (sizeTmpBuf_ as string | number | Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const srcTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let srcTmpBuf : ResourceStr | undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const srcTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let srcTmpBuf_ : string | Resource | undefined
            if (srcTmpBuf_UnionSelector == (0).toChar()) {
                srcTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (srcTmpBuf_UnionSelector == (1).toChar()) {
                srcTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for srcTmpBuf_ has to be chosen through deserialisation.")
            }
            srcTmpBuf = (srcTmpBuf_ as string | Resource)
        }
        const srcTmpResult : ResourceStr | undefined = srcTmpBuf
        let value : IconOptions = ({size: sizeTmpResult, color: colorTmpResult, src: srcTmpResult} as IconOptions)
        return value
    }
}
export class SearchButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: SearchButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueHolderForFontColorTmpValueForIdx0))
            } else if (valueHolderForFontColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAutoDisable  = value.autoDisable
        if (valueHolderForAutoDisable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoDisableTmpValue  = valueHolderForAutoDisable!
            valueSerializer.writeBoolean(valueHolderForAutoDisableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SearchButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSizeTmpBuf : Length | undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBuf_ : string | number | Resource | undefined
            if (fontSizeTmpBuf_UnionSelector == (0).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBuf_UnionSelector == (1).toChar()) {
                fontSizeTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontSizeTmpBuf_UnionSelector == (2).toChar()) {
                fontSizeTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontSizeTmpBuf_ has to be chosen through deserialisation.")
            }
            fontSizeTmpBuf = (fontSizeTmpBuf_ as string | number | Resource)
        }
        const fontSizeTmpResult : Length | undefined = fontSizeTmpBuf
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontColorTmpBuf : ResourceColor | undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBuf_ : Color | number | string | Resource | undefined
            if (fontColorTmpBuf_UnionSelector == (0).toChar()) {
                fontColorTmpBuf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            } else if (fontColorTmpBuf_UnionSelector == (1).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (fontColorTmpBuf_UnionSelector == (2).toChar()) {
                fontColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBuf_UnionSelector == (3).toChar()) {
                fontColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for fontColorTmpBuf_ has to be chosen through deserialisation.")
            }
            fontColorTmpBuf = (fontColorTmpBuf_ as Color | number | string | Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const autoDisableTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoDisableTmpBuf : boolean | undefined
        if ((autoDisableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoDisableTmpBuf = valueDeserializer.readBoolean()
        }
        const autoDisableTmpResult : boolean | undefined = autoDisableTmpBuf
        let value : SearchButtonOptions = ({fontSize: fontSizeTmpResult, fontColor: fontColorTmpResult, autoDisable: autoDisableTmpResult} as SearchButtonOptions)
        return value
    }
}
export class CancelButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: CancelButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as CancelButtonStyle)
            valueSerializer.writeInt32(TypeChecker.CancelButtonStyle_ToNumeric(valueHolderForStyleTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            IconOptions_serializer.write(valueSerializer, valueHolderForIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CancelButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : CancelButtonStyle | undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TypeChecker.CancelButtonStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const styleTmpResult : CancelButtonStyle | undefined = styleTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : IconOptions | undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = IconOptions_serializer.read(valueDeserializer)
        }
        const iconTmpResult : IconOptions | undefined = iconTmpBuf
        let value : CancelButtonOptions = ({style: styleTmpResult, icon: iconTmpResult} as CancelButtonOptions)
        return value
    }
}
export class SearchControllerInternal {
    public static fromPtr(ptr: KPointer): SearchController {
        return new SearchController(ptr)
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(SearchController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SearchController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._SearchController_caretPosition(this.peer!.ptr, value)
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._SearchController_stopEditing(this.peer!.ptr)
    }
    private setTextSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
