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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { SelectionOptions_serializer, SelectionOptions, ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { StyledString, StyledStringInternal, DecorationStyleInterface_serializer, DecorationStyleInterface } from "./styledString"
import { LayoutManager, LayoutManagerInternal, TextDataDetectorConfig_serializer, EditMenuOptions_serializer, FontSettingOptions_serializer, TextDataDetectorConfig, EditMenuOptions, FontSettingOptions, MenuType } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ArkThemeScopeManager } from "#arktheme"
import { Resource_serializer } from "./../framework/resource"
import { LengthMetrics_serializer } from "./../Graphics"
import { Font_serializer, ResourceColor, Length, Font, VoidCallback } from "./units"
import { SelectionMenuOptions_serializer, SelectionMenuOptions, MenuOnAppearCallback, MenuCallback, PreviewMenuOptions } from "./richEditor"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight, TextOverflow } from "./enums"
import { Resource } from "global.resource"
import { LengthMetrics } from "arkui.Graphics"
import { AttributeModifier, hookTextAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { TextModifier } from "./../TextModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkThemeScopeManager } from "arkui/theme/ArkThemeScopeManager.ets";
export class TextControllerInternal {
    public static fromPtr(ptr: KPointer): TextController {
        return new TextController(ptr)
    }
}
export class TextController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextController.getFinalizer())
    }
    constructor() {
        this(TextController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextController_getFinalizer()
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public setStyledString(value: StyledString): void {
        const value_casted = value as (StyledString)
        this.setStyledString_serialize(value_casted)
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    public setTextSelection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (int32 | undefined)
        const selectionEnd_casted = selectionEnd as (int32 | undefined)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextController_closeSelectionMenu(this.peer!.ptr)
    }
    setStyledString_serialize(value: StyledString): void {
        ArkUIGeneratedNativeModule._TextController_setStyledString(this.peer!.ptr, toPeerPtr(value))
    }
    getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._TextController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
    setTextSelection_serialize(selectionStart: int32 | undefined, selectionEnd: int32 | undefined, options?: SelectionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (selectionStart !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectionStartTmpValue  = selectionStart!
            thisSerializer.writeInt32(selectionStartTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (selectionEnd !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectionEndTmpValue  = selectionEnd!
            thisSerializer.writeInt32(selectionEndTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextController_setTextSelection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkTextPeer extends ArkCommonMethodPeer {
    attributeSet?: TextModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Text_construct(peerId, flags)
        const _peer  = new ArkTextPeer(_peerPtr, peerId, 'Text', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextOptionsAttribute(content?: string | Resource, value?: TextOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            if (contentTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const contentTmpValueForIdx0  = contentTmpValue as string
                thisSerializer.writeString(contentTmpValueForIdx0)
            } else if (contentTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const contentTmpValueForIdx1  = contentTmpValue as Resource
                Resource_serializer.write(thisSerializer, contentTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextInterface_setTextOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._TextAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: double | string | Resource | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: double | string | Resource | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(value: double | string | Resource | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FontStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineSpacingAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            LengthMetrics_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setTextAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: double | string | Resource | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextOverflowAttribute(value: TextOverflowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextOverflowOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLetterSpacingAttribute(value: double | string | undefined): void {
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
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as TextCase)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBaselineOffsetAttribute(value: double | string | undefined): void {
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
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setBaselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDraggableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDraggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ShadowOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (TypeChecker.isArray_ShadowOptions(valueTmpValue)) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Array<ShadowOptions>
                thisSerializer.writeInt32((valueTmpValueForIdx1.length).toInt())
                for (let valueTmpValueForIdx1CounterI = 0; valueTmpValueForIdx1CounterI < valueTmpValueForIdx1.length; valueTmpValueForIdx1CounterI++) {
                    const valueTmpValueForIdx1TmpElement : ShadowOptions = valueTmpValueForIdx1[valueTmpValueForIdx1CounterI]
                    ShadowOptions_serializer.write(thisSerializer, valueTmpValueForIdx1TmpElement)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setHeightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIndentAttribute(value: Length | undefined): void {
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
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWordBreakAttribute(value: WordBreak | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as WordBreak)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setWordBreak(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as LineBreakStrategy)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineBreakStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: ((value: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._TextAttribute_setCaretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEllipsisModeAttribute(value: EllipsisMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EllipsisMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEllipsisMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEnableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: ((selectionStart: int32,selectionEnd: int32) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarqueeOptionsAttribute(value: TextMarqueeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextMarqueeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMarqueeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnMarqueeStateChangeAttribute(value: ((value0: MarqueeState) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnMarqueeStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextSelectableAttribute(value: TextSelectableMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as TextSelectableMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setHalfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(fontValue: Font | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (fontValue !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fontValueTmpValue  = fontValue!
            Font_serializer.write(thisSerializer, fontValueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            FontSettingOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (weight !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const weightTmpValue  = weight!
            if (weightTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const weightTmpValueForIdx0  = weightTmpValue as int32
                thisSerializer.writeInt32(weightTmpValueForIdx0)
            } else if (weightTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const weightTmpValueForIdx1  = weightTmpValue as FontWeight
                thisSerializer.writeInt32(weightTmpValueForIdx1.valueOf())
            } else if (weightTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const weightTmpValueForIdx2  = weightTmpValue as string
                thisSerializer.writeString(weightTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            FontSettingOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionAttribute(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (selectionStart !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectionStartTmpValue  = selectionStart!
            thisSerializer.writeInt32(selectionStartTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (selectionEnd !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectionEndTmpValue  = selectionEnd!
            thisSerializer.writeInt32(selectionEndTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setSelection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (spanType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const spanTypeTmpValue  = (spanType as TextSpanType)
            thisSerializer.writeInt32(spanTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(contentTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (responseType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTypeTmpValue  = (responseType as TextResponseType)
            thisSerializer.writeInt32(responseTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionMenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setBindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextOverflowOptions {
    overflow: TextOverflow | undefined;
}
export interface TextAttribute extends CommonMethod {
    setTextOptions(content?: string | Resource, value?: TextOptions): this {
        throw new Error("Unimplemented method setTextOptions")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    minFontSize(value: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    maxFontSize(value: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontSize")
    }
    minFontScale(value: double | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: double | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method lineSpacing")
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error("Unimplemented method textAlign")
    }
    lineHeight(value: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        throw new Error("Unimplemented method textOverflow")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    maxLines(value: int32 | undefined): this {
        throw new Error("Unimplemented method maxLines")
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    letterSpacing(value: double | string | undefined): this {
        throw new Error("Unimplemented method letterSpacing")
    }
    textCase(value: TextCase | undefined): this {
        throw new Error("Unimplemented method textCase")
    }
    baselineOffset(value: double | string | undefined): this {
        throw new Error("Unimplemented method baselineOffset")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    draggable(value: boolean | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error("Unimplemented method textShadow")
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        throw new Error("Unimplemented method heightAdaptivePolicy")
    }
    textIndent(value: Length | undefined): this {
        throw new Error("Unimplemented method textIndent")
    }
    wordBreak(value: WordBreak | undefined): this {
        throw new Error("Unimplemented method wordBreak")
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        throw new Error("Unimplemented method lineBreakStrategy")
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCopy")
    }
    caretColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method caretColor")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        throw new Error("Unimplemented method ellipsisMode")
    }
    enableDataDetector(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableDataDetector")
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        throw new Error("Unimplemented method dataDetectorConfig")
    }
    onTextSelectionChange(value: ((selectionStart: int32,selectionEnd: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onTextSelectionChange")
    }
    fontFeature(value: string | undefined): this {
        throw new Error("Unimplemented method fontFeature")
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        throw new Error("Unimplemented method marqueeOptions")
    }
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        throw new Error("Unimplemented method onMarqueeStateChange")
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error("Unimplemented method privacySensitive")
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        throw new Error("Unimplemented method textSelectable")
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error("Unimplemented method editMenuOptions")
    }
    halfLeading(value: boolean | undefined): this {
        throw new Error("Unimplemented method halfLeading")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        throw new Error("Unimplemented method font")
    }
    fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        throw new Error("Unimplemented method fontWeight")
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        throw new Error("Unimplemented method selection")
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        throw new Error("Unimplemented method bindSelectionMenu")
    }
    attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTextStyle extends ArkCommonMethodStyle implements TextAttribute {
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: double | string | Resource | undefined
    minFontSize_value?: double | string | Resource | undefined
    maxFontSize_value?: double | string | Resource | undefined
    minFontScale_value?: double | Resource | undefined
    maxFontScale_value?: double | Resource | undefined
    fontStyle_value?: FontStyle | undefined
    lineSpacing_value?: LengthMetrics | undefined
    textAlign_value?: TextAlign | undefined
    lineHeight_value?: double | string | Resource | undefined
    textOverflow_value?: TextOverflowOptions | undefined
    fontFamily_value?: string | Resource | undefined
    maxLines_value?: int32 | undefined
    decoration_value?: DecorationStyleInterface | undefined
    letterSpacing_value?: double | string | undefined
    textCase_value?: TextCase | undefined
    baselineOffset_value?: double | string | undefined
    copyOption_value?: CopyOptions | undefined
    draggable_value?: boolean | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy | undefined
    textIndent_value?: Length | undefined
    wordBreak_value?: WordBreak | undefined
    lineBreakStrategy_value?: LineBreakStrategy | undefined
    onCopy_value?: ((value: string) => void) | undefined
    caretColor_value?: ResourceColor | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    ellipsisMode_value?: EllipsisMode | undefined
    enableDataDetector_value?: boolean | undefined
    dataDetectorConfig_value?: TextDataDetectorConfig | undefined
    onTextSelectionChange_value?: ((selectionStart: int32,selectionEnd: int32) => void) | undefined
    fontFeature_value?: string | undefined
    marqueeOptions_value?: TextMarqueeOptions | undefined
    onMarqueeStateChange_value?: ((value0: MarqueeState) => void) | undefined
    privacySensitive_value?: boolean | undefined
    textSelectable_value?: TextSelectableMode | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    halfLeading_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined
    setTextOptions(content?: string | Resource, value?: TextOptions): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    fontSize(value: double | string | Resource | undefined): this {
        return this
    }
    minFontSize(value: double | string | Resource | undefined): this {
        return this
    }
    maxFontSize(value: double | string | Resource | undefined): this {
        return this
    }
    minFontScale(value: double | Resource | undefined): this {
        return this
    }
    maxFontScale(value: double | Resource | undefined): this {
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        return this
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        return this
    }
    textAlign(value: TextAlign | undefined): this {
        return this
    }
    lineHeight(value: double | string | Resource | undefined): this {
        return this
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        return this
    }
    maxLines(value: int32 | undefined): this {
        return this
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        return this
    }
    letterSpacing(value: double | string | undefined): this {
        return this
    }
    textCase(value: TextCase | undefined): this {
        return this
    }
    baselineOffset(value: double | string | undefined): this {
        return this
    }
    copyOption(value: CopyOptions | undefined): this {
        return this
    }
    draggable(value: boolean | undefined): this {
        return this
    }
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    textIndent(value: Length | undefined): this {
        return this
    }
    wordBreak(value: WordBreak | undefined): this {
        return this
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        return this
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        return this
    }
    caretColor(value: ResourceColor | undefined): this {
        return this
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        return this
    }
    enableDataDetector(value: boolean | undefined): this {
        return this
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        return this
    }
    onTextSelectionChange(value: ((selectionStart: int32,selectionEnd: int32) => void) | undefined): this {
        return this
    }
    fontFeature(value: string | undefined): this {
        return this
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        return this
    }
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        return this
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        return this
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    halfLeading(value: boolean | undefined): this {
        return this
    }
    enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        return this
    }
    fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        return this
    }
    selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        return this
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    DEFAULT = 3
}
export enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export enum MarqueeState {
    START = 0,
    BOUNCE = 1,
    FINISH = 2
}
export enum MarqueeStartPolicy {
    DEFAULT = 0,
    ON_FOCUS = 1
}
export interface TextOptions {
    controller: TextController;
}
export interface TextMarqueeOptions {
    start: boolean;
    step?: double;
    loop?: int32;
    fromStart?: boolean;
    delay?: int32;
    fadeout?: boolean;
    marqueeStartPolicy?: MarqueeStartPolicy;
}

export class ArkTextComponent extends ArkCommonMethodComponent implements TextAttribute {
    getPeer(): ArkTextPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkTextPeer)
    }
    public setTextOptions(content?: string | Resource, value?: TextOptions): this {
        if (this.checkPriority("setTextOptions")) {
            const content_casted = content as (string | Resource | undefined)
            const value_casted = value as (TextOptions | undefined)
            this.getPeer()?.setTextOptionsAttribute(content_casted, value_casted)
            this.applyOptionsFinish('TextAttribute');
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
    public fontSize(value: double | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (double | string | Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: double | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (double | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: double | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (double | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: double | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (double | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: double | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (double | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setLineSpacingAttribute(value_casted)
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
    public lineHeight(value: double | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (double | string | Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflowOptions | undefined)
            this.getPeer()?.setTextOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: int32 | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMaxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: double | string | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.setTextCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: double | string | undefined): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setBaselineOffsetAttribute(value_casted)
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
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDraggableAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.setTextShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.setHeightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Length | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTextIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak | undefined)
            this.getPeer()?.setWordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy | undefined)
            this.getPeer()?.setLineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value: string) => void) | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setCaretColorAttribute(value_casted)
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
    public ellipsisMode(value: EllipsisMode | undefined): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode | undefined)
            this.getPeer()?.setEllipsisModeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig | undefined)
            this.getPeer()?.setDataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: int32,selectionEnd: int32) => void) | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((selectionStart: int32,selectionEnd: int32) => void) | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
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
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (this.checkPriority("marqueeOptions")) {
            const value_casted = value as (TextMarqueeOptions | undefined)
            this.getPeer()?.setMarqueeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        if (this.checkPriority("onMarqueeStateChange")) {
            const value_casted = value as (((value0: MarqueeState) => void) | undefined)
            this.getPeer()?.setOnMarqueeStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        if (this.checkPriority("textSelectable")) {
            const value_casted = value as (TextSelectableMode | undefined)
            this.getPeer()?.setTextSelectableAttribute(value_casted)
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
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHalfLeadingAttribute(value_casted)
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
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("font")) {
            const fontValue_casted = fontValue as (Font | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.setFontAttribute(fontValue_casted, options_casted)
            return this
        }
        return this
    }
    public fontWeight(weight: int32 | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("fontWeight")) {
            const weight_casted = weight as (int32 | FontWeight | string | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.setFontWeightAttribute(weight_casted, options_casted)
            return this
        }
        return this
    }
    public selection(selectionStart: int32 | undefined, selectionEnd: int32 | undefined): this {
        if (this.checkPriority("selection")) {
            const selectionStart_casted = selectionStart as (int32 | undefined)
            const selectionEnd_casted = selectionEnd as (int32 | undefined)
            this.getPeer()?.setSelectionAttribute(selectionStart_casted, selectionEnd_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const spanType_casted = spanType as (TextSpanType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (TextResponseType | undefined)
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.setBindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookTextAttributeModifier(this, value);
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
export function TextImpl(
    @memo
    style: ((attributes: TextAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextComponent>((): ArkTextComponent => {
        return new ArkTextComponent()
    })
    NodeAttach<ArkTextPeer>((): ArkTextPeer => ArkTextPeer.create(receiver), (peer: ArkTextPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class TextController_serializer {
    public static write(buffer: SerializerBase, value: TextController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextControllerInternal.fromPtr(ptr)
    }
}
export class TextOptions_serializer {
    public static write(buffer: SerializerBase, value: TextOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForController  = value.controller
        TextController_serializer.write(valueSerializer, valueHolderForController)
    }
    public static read(buffer: DeserializerBase): TextOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controllerTmpResult : TextController = (TextController_serializer.read(valueDeserializer) as TextController)
        let value : TextOptions = ({controller: controllerTmpResult} as TextOptions)
        return value
    }
}
export class TextOverflowOptions_serializer {
    public static write(buffer: SerializerBase, value: TextOverflowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextOverflowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        let value : TextOverflowOptions = ({overflow: overflowTmpResult} as TextOverflowOptions)
        return value
    }
}
export class TextMarqueeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMarqueeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        valueSerializer.writeBoolean(valueHolderForStart)
        const valueHolderForStep  = value.step
        if (valueHolderForStep !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStepTmpValue  = valueHolderForStep!
            valueSerializer.writeFloat64(valueHolderForStepTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLoop  = value.loop
        if (valueHolderForLoop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLoopTmpValue  = valueHolderForLoop!
            valueSerializer.writeInt32(valueHolderForLoopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFromStart  = value.fromStart
        if (valueHolderForFromStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFromStartTmpValue  = valueHolderForFromStart!
            valueSerializer.writeBoolean(valueHolderForFromStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDelay  = value.delay
        if (valueHolderForDelay !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDelayTmpValue  = valueHolderForDelay!
            valueSerializer.writeInt32(valueHolderForDelayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFadeout  = value.fadeout
        if (valueHolderForFadeout !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFadeoutTmpValue  = valueHolderForFadeout!
            valueSerializer.writeBoolean(valueHolderForFadeoutTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMarqueeStartPolicy  = value.marqueeStartPolicy
        if (valueHolderForMarqueeStartPolicy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarqueeStartPolicyTmpValue  = (valueHolderForMarqueeStartPolicy as MarqueeStartPolicy)
            valueSerializer.writeInt32(valueHolderForMarqueeStartPolicyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextMarqueeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpResult : boolean = valueDeserializer.readBoolean()
        const stepTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let stepTmpBuf : double | undefined = undefined
        if ((stepTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stepTmpBuf = valueDeserializer.readFloat64()
        }
        const stepTmpResult : double | undefined = stepTmpBuf
        const loopTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let loopTmpBuf : int32 | undefined = undefined
        if ((loopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            loopTmpBuf = valueDeserializer.readInt32()
        }
        const loopTmpResult : int32 | undefined = loopTmpBuf
        const fromStartTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromStartTmpBuf : boolean | undefined = undefined
        if ((fromStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fromStartTmpBuf = valueDeserializer.readBoolean()
        }
        const fromStartTmpResult : boolean | undefined = fromStartTmpBuf
        const delayTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let delayTmpBuf : int32 | undefined = undefined
        if ((delayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            delayTmpBuf = valueDeserializer.readInt32()
        }
        const delayTmpResult : int32 | undefined = delayTmpBuf
        const fadeoutTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fadeoutTmpBuf : boolean | undefined = undefined
        if ((fadeoutTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fadeoutTmpBuf = valueDeserializer.readBoolean()
        }
        const fadeoutTmpResult : boolean | undefined = fadeoutTmpBuf
        const marqueeStartPolicyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marqueeStartPolicyTmpBuf : MarqueeStartPolicy | undefined = undefined
        if ((marqueeStartPolicyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            marqueeStartPolicyTmpBuf = MarqueeStartPolicy.fromValue(valueDeserializer.readInt32())
        }
        const marqueeStartPolicyTmpResult : MarqueeStartPolicy | undefined = marqueeStartPolicyTmpBuf
        let value : TextMarqueeOptions = ({start: startTmpResult, step: stepTmpResult, loop: loopTmpResult, fromStart: fromStartTmpResult, delay: delayTmpResult, fadeout: fadeoutTmpResult, marqueeStartPolicy: marqueeStartPolicyTmpResult} as TextMarqueeOptions)
        return value
    }
}
