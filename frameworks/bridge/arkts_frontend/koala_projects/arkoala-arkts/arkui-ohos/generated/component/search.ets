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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, Finalizable, MaterializedBaseTag } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { SymbolGlyphModifier_serializer } from './../framework/SymbolGlyphModifier'
import { CaretStyle_serializer, EditMenuOptions_serializer, CaretStyle, EditableTextOnChangeCallback, PreviewText, TextChangeOptions, InsertValue, DeleteValue, EditMenuOptions, AutoCapitalizationMode, EditableTextChangeValue, KeyboardAppearance } from './textCommon'
import { arkui_component_units_Font_serializer, ResourceColor, Resource as arkui_component_units_Resource, Dimension, Font as arkui_component_units_Font, ResourceStr as arkui_component_units_ResourceStr, Length } from './units'
import { TextDecorationOptions_serializer, ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, TextDecorationOptions, Bindable, ArkCommonMethodComponent, Bindable_String_serializer, SelectionOptions_serializer, TextContentControllerBase, TextContentControllerBaseInternal, SelectionOptions } from './common'
import { KeyboardOptions_serializer, PasteEvent, KeyboardOptions } from './richEditor'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { Color as arkui_component_enums_Color, CopyOptions, TextAlign } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { extractors, AttributeModifier, hookSearchAttributeModifier, AttributeUpdater } from '#handwritten'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
import { EnterKeyType, SubmitEvent, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from './textInput'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { SearchModifier } from './../SearchModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkSearchPeer extends ArkCommonMethodPeer {
    attributeSet?: SearchModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as IconOptions
                IconOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((1).toByte())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as CancelButtonOptions
                CancelButtonOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof CancelButtonSymbolOptions) {
                thisSerializer.writeInt8((1).toByte())
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
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEditChangeAttribute(value: arkui_component_common_Callback<boolean, void> | undefined): void {
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setPlaceholderFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextFontAttribute(value: arkui_component_units_Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            arkui_component_units_Font_serializer.write(thisSerializer, valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setEnterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSubmitAttribute(value: SearchSubmitCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
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
    setOnCopyAttribute(value: arkui_component_common_Callback<string, void> | undefined): void {
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
    setOnCutAttribute(value: arkui_component_common_Callback<string, void> | undefined): void {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLengthAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setMinFontSizeAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: double | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: double | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
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
    setLetterSpacingAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: double | string | global_resource_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setOnWillInsertAttribute(value: arkui_component_common_Callback<InsertValue, boolean> | undefined): void {
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
    setOnDidInsertAttribute(value: arkui_component_common_Callback<InsertValue, void> | undefined): void {
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
    setOnWillDeleteAttribute(value: arkui_component_common_Callback<DeleteValue, boolean> | undefined): void {
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
    setOnDidDeleteAttribute(value: arkui_component_common_Callback<DeleteValue, void> | undefined): void {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
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
    setOnWillChangeAttribute(value: arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined): void {
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
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SearchAttribute_setKeyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSearchButtonAttribute(value: string | undefined, option?: SearchButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
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
    setInputFilterAttribute(value: arkui_component_units_ResourceStr | undefined, error?: arkui_component_common_Callback<string, void>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
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
    placeholder?: arkui_component_units_ResourceStr;
    icon?: string;
    controller?: SearchController;
}
export interface IconOptions {
    size?: Length;
    color?: ResourceColor;
    src?: arkui_component_units_ResourceStr;
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
    setSearchOptions(options?: SearchOptions): this {
        throw new Error('Unimplemented method setSearchOptions')
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method fontColor')
    }
    searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        throw new Error('Unimplemented method searchIcon')
    }
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        throw new Error('Unimplemented method cancelButton')
    }
    textIndent(value: Dimension | undefined): this {
        throw new Error('Unimplemented method textIndent')
    }
    onEditChange(value: arkui_component_common_Callback<boolean, void> | undefined): this {
        throw new Error('Unimplemented method onEditChange')
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedBackgroundColor')
    }
    caretStyle(value: CaretStyle | undefined): this {
        throw new Error('Unimplemented method caretStyle')
    }
    placeholderColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method placeholderColor')
    }
    placeholderFont(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method placeholderFont')
    }
    textFont(value: arkui_component_units_Font | undefined): this {
        throw new Error('Unimplemented method textFont')
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        throw new Error('Unimplemented method enterKeyType')
    }
    onSubmit(value: SearchSubmitCallback | undefined): this {
        throw new Error('Unimplemented method onSubmit')
    }
    onChange(value: EditableTextOnChangeCallback | undefined): this {
        throw new Error('Unimplemented method onChange')
    }
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        throw new Error('Unimplemented method onTextSelectionChange')
    }
    onContentScroll(value: OnContentScrollCallback | undefined): this {
        throw new Error('Unimplemented method onContentScroll')
    }
    onCopy(value: arkui_component_common_Callback<string, void> | undefined): this {
        throw new Error('Unimplemented method onCopy')
    }
    onCut(value: arkui_component_common_Callback<string, void> | undefined): this {
        throw new Error('Unimplemented method onCut')
    }
    onPaste(value: OnPasteCallback | undefined): this {
        throw new Error('Unimplemented method onPaste')
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error('Unimplemented method copyOption')
    }
    maxLength(value: int32 | undefined): this {
        throw new Error('Unimplemented method maxLength')
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error('Unimplemented method textAlign')
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableKeyboardOnFocus')
    }
    selectionMenuHidden(value: boolean | undefined): this {
        throw new Error('Unimplemented method selectionMenuHidden')
    }
    minFontSize(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method minFontSize')
    }
    maxFontSize(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method maxFontSize')
    }
    minFontScale(value: double | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method minFontScale')
    }
    maxFontScale(value: double | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method maxFontScale')
    }
    decoration(value: TextDecorationOptions | undefined): this {
        throw new Error('Unimplemented method decoration')
    }
    letterSpacing(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method letterSpacing')
    }
    lineHeight(value: double | string | global_resource_Resource | undefined): this {
        throw new Error('Unimplemented method lineHeight')
    }
    type(value: SearchType | undefined): this {
        throw new Error('Unimplemented method type')
    }
    fontFeature(value: string | undefined): this {
        throw new Error('Unimplemented method fontFeature')
    }
    onWillInsert(value: arkui_component_common_Callback<InsertValue, boolean> | undefined): this {
        throw new Error('Unimplemented method onWillInsert')
    }
    onDidInsert(value: arkui_component_common_Callback<InsertValue, void> | undefined): this {
        throw new Error('Unimplemented method onDidInsert')
    }
    onWillDelete(value: arkui_component_common_Callback<DeleteValue, boolean> | undefined): this {
        throw new Error('Unimplemented method onWillDelete')
    }
    onDidDelete(value: arkui_component_common_Callback<DeleteValue, void> | undefined): this {
        throw new Error('Unimplemented method onDidDelete')
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error('Unimplemented method editMenuOptions')
    }
    enablePreviewText(value: boolean | undefined): this {
        throw new Error('Unimplemented method enablePreviewText')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        throw new Error('Unimplemented method autoCapitalizationMode')
    }
    halfLeading(value: boolean | undefined): this {
        throw new Error('Unimplemented method halfLeading')
    }
    stopBackPress(value: boolean | undefined): this {
        throw new Error('Unimplemented method stopBackPress')
    }
    onWillChange(value: arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined): this {
        throw new Error('Unimplemented method onWillChange')
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        throw new Error('Unimplemented method keyboardAppearance')
    }
    searchButton(value: string | undefined, option?: SearchButtonOptions): this {
        throw new Error('Unimplemented method searchButton')
    }
    inputFilter(value: arkui_component_units_ResourceStr | undefined, error?: arkui_component_common_Callback<string, void>): this {
        throw new Error('Unimplemented method inputFilter')
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        throw new Error('Unimplemented method customKeyboard')
    }
    attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkSearchComponent extends ArkCommonMethodComponent implements SearchAttribute {
    getPeer(): ArkSearchPeer {
        return (this.peer as ArkSearchPeer)
    }
    public setSearchOptions(options?: SearchOptions): this {
        if (this.checkPriority('setSearchOptions')) {
            const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
            this.applyOptionsFinish('SearchAttribute');
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('fontColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public searchIcon(value: IconOptions | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority('searchIcon')) {
            const value_casted = value as (IconOptions | SymbolGlyphModifier | undefined)
            this.getPeer()?.setSearchIconAttribute(value_casted)
            return this
        }
        return this
    }
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions | undefined): this {
        if (this.checkPriority('cancelButton')) {
            const value_casted = value as (CancelButtonOptions | CancelButtonSymbolOptions | undefined)
            this.getPeer()?.setCancelButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Dimension | undefined): this {
        if (this.checkPriority('textIndent')) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setTextIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditChange(value: arkui_component_common_Callback<boolean, void> | undefined): this {
        if (this.checkPriority('onEditChange')) {
            const value_casted = value as (arkui_component_common_Callback<boolean, void> | undefined)
            this.getPeer()?.setOnEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedBackgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public caretStyle(value: CaretStyle | undefined): this {
        if (this.checkPriority('caretStyle')) {
            const value_casted = value as (CaretStyle | undefined)
            this.getPeer()?.setCaretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('placeholderColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setPlaceholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public placeholderFont(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('placeholderFont')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setPlaceholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    public textFont(value: arkui_component_units_Font | undefined): this {
        if (this.checkPriority('textFont')) {
            const value_casted = value as (arkui_component_units_Font | undefined)
            this.getPeer()?.setTextFontAttribute(value_casted)
            return this
        }
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        if (this.checkPriority('enterKeyType')) {
            const value_casted = value as (EnterKeyType | undefined)
            this.getPeer()?.setEnterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSubmit(value: SearchSubmitCallback | undefined): this {
        if (this.checkPriority('onSubmit')) {
            const value_casted = value as (SearchSubmitCallback | undefined)
            this.getPeer()?.setOnSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: EditableTextOnChangeCallback | undefined): this {
        if (this.checkPriority('onChange')) {
            const value_casted = value as (EditableTextOnChangeCallback | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): this {
        if (this.checkPriority('onTextSelectionChange')) {
            const value_casted = value as (OnTextSelectionChangeCallback | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onContentScroll(value: OnContentScrollCallback | undefined): this {
        if (this.checkPriority('onContentScroll')) {
            const value_casted = value as (OnContentScrollCallback | undefined)
            this.getPeer()?.setOnContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: arkui_component_common_Callback<string, void> | undefined): this {
        if (this.checkPriority('onCopy')) {
            const value_casted = value as (arkui_component_common_Callback<string, void> | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: arkui_component_common_Callback<string, void> | undefined): this {
        if (this.checkPriority('onCut')) {
            const value_casted = value as (arkui_component_common_Callback<string, void> | undefined)
            this.getPeer()?.setOnCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: OnPasteCallback | undefined): this {
        if (this.checkPriority('onPaste')) {
            const value_casted = value as (OnPasteCallback | undefined)
            this.getPeer()?.setOnPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority('copyOption')) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLength(value: int32 | undefined): this {
        if (this.checkPriority('maxLength')) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMaxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority('textAlign')) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.setTextAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority('enableKeyboardOnFocus')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public selectionMenuHidden(value: boolean | undefined): this {
        if (this.checkPriority('selectionMenuHidden')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('minFontSize')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('maxFontSize')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: double | global_resource_Resource | undefined): this {
        if (this.checkPriority('minFontScale')) {
            const value_casted = value as (double | global_resource_Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: double | global_resource_Resource | undefined): this {
        if (this.checkPriority('maxFontScale')) {
            const value_casted = value as (double | global_resource_Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: TextDecorationOptions | undefined): this {
        if (this.checkPriority('decoration')) {
            const value_casted = value as (TextDecorationOptions | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('letterSpacing')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: double | string | global_resource_Resource | undefined): this {
        if (this.checkPriority('lineHeight')) {
            const value_casted = value as (double | string | global_resource_Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public type(value: SearchType | undefined): this {
        if (this.checkPriority('type')) {
            const value_casted = value as (SearchType | undefined)
            this.getPeer()?.setTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority('fontFeature')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillInsert(value: arkui_component_common_Callback<InsertValue, boolean> | undefined): this {
        if (this.checkPriority('onWillInsert')) {
            const value_casted = value as (arkui_component_common_Callback<InsertValue, boolean> | undefined)
            this.getPeer()?.setOnWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidInsert(value: arkui_component_common_Callback<InsertValue, void> | undefined): this {
        if (this.checkPriority('onDidInsert')) {
            const value_casted = value as (arkui_component_common_Callback<InsertValue, void> | undefined)
            this.getPeer()?.setOnDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillDelete(value: arkui_component_common_Callback<DeleteValue, boolean> | undefined): this {
        if (this.checkPriority('onWillDelete')) {
            const value_casted = value as (arkui_component_common_Callback<DeleteValue, boolean> | undefined)
            this.getPeer()?.setOnWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidDelete(value: arkui_component_common_Callback<DeleteValue, void> | undefined): this {
        if (this.checkPriority('onDidDelete')) {
            const value_casted = value as (arkui_component_common_Callback<DeleteValue, void> | undefined)
            this.getPeer()?.setOnDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority('editMenuOptions')) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority('enablePreviewText')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority('enableHapticFeedback')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public autoCapitalizationMode(value: AutoCapitalizationMode | undefined): this {
        if (this.checkPriority('autoCapitalizationMode')) {
            const value_casted = value as (AutoCapitalizationMode | undefined)
            this.getPeer()?.setAutoCapitalizationModeAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority('halfLeading')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHalfLeadingAttribute(value_casted)
            return this
        }
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        if (this.checkPriority('stopBackPress')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStopBackPressAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillChange(value: arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined): this {
        if (this.checkPriority('onWillChange')) {
            const value_casted = value as (arkui_component_common_Callback<EditableTextChangeValue, boolean> | undefined)
            this.getPeer()?.setOnWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (this.checkPriority('keyboardAppearance')) {
            const value_casted = value as (KeyboardAppearance | undefined)
            this.getPeer()?.setKeyboardAppearanceAttribute(value_casted)
            return this
        }
        return this
    }
    public searchButton(value: string | undefined, option?: SearchButtonOptions): this {
        if (this.checkPriority('searchButton')) {
            const value_casted = value as (string | undefined)
            const option_casted = option as (SearchButtonOptions | undefined)
            this.getPeer()?.setSearchButtonAttribute(value_casted, option_casted)
            return this
        }
        return this
    }
    public inputFilter(value: arkui_component_units_ResourceStr | undefined, error?: arkui_component_common_Callback<string, void>): this {
        if (this.checkPriority('inputFilter')) {
            const value_casted = value as (arkui_component_units_ResourceStr | undefined)
            const error_casted = error as (arkui_component_common_Callback<string, void> | undefined)
            this.getPeer()?.setInputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority('customKeyboard')) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.setCustomKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SearchAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSearchAttributeModifier(this, value);
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
export function SearchImpl(
    @memo @memo_skip
    style: ((attributes: SearchAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkSearchComponent>((): ArkSearchComponent => {
        return new ArkSearchComponent()
    })
    NodeAttach<ArkSearchPeer>((): ArkSearchPeer => ArkSearchPeer.create(receiver), (_: ArkSearchPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
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
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : CancelButtonStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = CancelButtonStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : CancelButtonStyle | undefined = styleTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueTmpValueForIdx0  = valueHolderForValueTmpValue as string
                valueSerializer.writeString(valueHolderForValueTmpValueForIdx0)
            } else if (valueHolderForValueTmpValue instanceof Bindable) {
                valueSerializer.writeInt8((1).toByte())
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPlaceholderTmpValueForIdx0  = valueHolderForPlaceholderTmpValue as string
                valueSerializer.writeString(valueHolderForPlaceholderTmpValueForIdx0)
            } else if (valueHolderForPlaceholderTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPlaceholderTmpValueForIdx1  = valueHolderForPlaceholderTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPlaceholderTmpValueForIdx1)
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
        const valueTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueTmpBuf : string | Bindable<string> | undefined = undefined
        if ((valueTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let valueTmpBufOpt : string | Bindable<string> | undefined
            if (valueTmpBufOptUnionSelector == (0).toByte()) {
                valueTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (valueTmpBufOptUnionSelector == (1).toByte()) {
                valueTmpBufOpt = Bindable_String_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for valueTmpBufOpt has to be chosen through deserialisation.')
            }
            valueTmpBuf = (valueTmpBufOpt as string | Bindable<string>)
        }
        const valueTmpResult : string | Bindable<string> | undefined = valueTmpBuf
        const placeholderTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let placeholderTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((placeholderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const placeholderTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let placeholderTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (placeholderTmpBufOptUnionSelector == (0).toByte()) {
                placeholderTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (placeholderTmpBufOptUnionSelector == (1).toByte()) {
                placeholderTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for placeholderTmpBufOpt has to be chosen through deserialisation.')
            }
            placeholderTmpBuf = (placeholderTmpBufOpt as string | arkui_component_units_Resource)
        }
        const placeholderTmpResult : arkui_component_units_ResourceStr | undefined = placeholderTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : string | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = (valueDeserializer.readString() as string)
        }
        const iconTmpResult : string | undefined = iconTmpBuf
        const controllerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let controllerTmpBuf : SearchController | undefined = undefined
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValueForIdx0  = valueHolderForSizeTmpValue as string
                valueSerializer.writeString(valueHolderForSizeTmpValueForIdx0)
            } else if (valueHolderForSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValueForIdx1  = valueHolderForSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForSizeTmpValueForIdx1)
            } else if (valueHolderForSizeTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValueForIdx2  = valueHolderForSizeTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSrcTmpValue  = valueHolderForSrc!
            if (valueHolderForSrcTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSrcTmpValueForIdx0  = valueHolderForSrcTmpValue as string
                valueSerializer.writeString(valueHolderForSrcTmpValueForIdx0)
            } else if (valueHolderForSrcTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSrcTmpValueForIdx1  = valueHolderForSrcTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSrcTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): IconOptions {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : Length | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (sizeTmpBufOptUnionSelector == (0).toByte()) {
                sizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptUnionSelector == (1).toByte()) {
                sizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (sizeTmpBufOptUnionSelector == (2).toByte()) {
                sizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOpt has to be chosen through deserialisation.')
            }
            sizeTmpBuf = (sizeTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const sizeTmpResult : Length | undefined = sizeTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const srcTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let srcTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((srcTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const srcTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let srcTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (srcTmpBufOptUnionSelector == (0).toByte()) {
                srcTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (srcTmpBufOptUnionSelector == (1).toByte()) {
                srcTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for srcTmpBufOpt has to be chosen through deserialisation.')
            }
            srcTmpBuf = (srcTmpBufOpt as string | arkui_component_units_Resource)
        }
        const srcTmpResult : arkui_component_units_ResourceStr | undefined = srcTmpBuf
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
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForFontColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForFontColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
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
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : Length | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (fontSizeTmpBufOptUnionSelector == (0).toByte()) {
                fontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBufOptUnionSelector == (1).toByte()) {
                fontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBufOptUnionSelector == (2).toByte()) {
                fontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            fontSizeTmpBuf = (fontSizeTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const fontSizeTmpResult : Length | undefined = fontSizeTmpBuf
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (fontColorTmpBufOptUnionSelector == (0).toByte()) {
                fontColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBufOptUnionSelector == (1).toByte()) {
                fontColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontColorTmpBufOptUnionSelector == (2).toByte()) {
                fontColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBufOptUnionSelector == (3).toByte()) {
                fontColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontColorTmpBufOpt has to be chosen through deserialisation.')
            }
            fontColorTmpBuf = (fontColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const autoDisableTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let autoDisableTmpBuf : boolean | undefined = undefined
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
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
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
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : CancelButtonStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = CancelButtonStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : CancelButtonStyle | undefined = styleTmpBuf
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : IconOptions | undefined = undefined
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
        return new SearchController(MaterializedBaseTag.NOP, ptr)
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, SearchController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SearchController_getFinalizer()
    }
    public caretPosition(value: int32): void {
        const value_casted = value as (int32)
        this.caretPosition_serialize(value_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setTextSelection(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (int32)
        const selectionEnd_casted = selectionEnd as (int32)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    private caretPosition_serialize(value: int32): void {
        ArkUIGeneratedNativeModule._SearchController_caretPosition(this.peer!.ptr, value)
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._SearchController_stopEditing(this.peer!.ptr)
    }
    private setTextSelection_serialize(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
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
