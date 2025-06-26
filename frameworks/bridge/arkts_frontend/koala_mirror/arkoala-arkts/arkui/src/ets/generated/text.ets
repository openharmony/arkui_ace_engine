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

import { StyledString, StyledStringInternal, DecorationStyleInterface_serializer, DecorationStyleInterface } from "./styledString"
import { LayoutManager, LayoutManagerInternal, TextDataDetectorConfig_serializer, EditMenuOptions_serializer, FontSettingOptions_serializer, TextDataDetectorConfig, EditMenuOptions, FontSettingOptions, MenuType } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./resource"
import { LengthMetrics_serializer, LengthMetrics } from "./ark.Graphics"
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Font_serializer, ResourceColor, Length, Font, VoidCallback } from "./units"
import { SelectionMenuOptions_serializer, SelectionMenuOptions, MenuOnAppearCallback, MenuCallback, PreviewMenuOptions } from "./richEditor"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight, TextOverflow } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextController_ctor()
        return retval
    }
    constructor() {
        this(TextController.ctor())
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
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextController_closeSelectionMenu(this.peer!.ptr)
    }
    private setStyledString_serialize(value: StyledString): void {
        ArkUIGeneratedNativeModule._TextController_setStyledString(this.peer!.ptr, toPeerPtr(value))
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._TextController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
}
export class ArkTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Text_construct(peerId, flags)
        const _peer  = new ArkTextPeer(_peerPtr, peerId, "Text", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextOptionsAttribute(content?: string | Resource, value?: TextOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0)
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1)
                const content_value_1  = content_value as Resource
                Resource_serializer.write(thisSerializer, content_value_1)
            }
        }
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextInterface_setTextOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineSpacingAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            LengthMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_lineSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textAlignAttribute(value: TextAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextAlign)
            thisSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_textAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineHeightAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextOverflowOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_textOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    decorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextCase)
            thisSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_textCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    baselineOffsetAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_baselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_copyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    draggableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_draggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isShadowOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_ShadowOptions(value_value))) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Array<ShadowOptions>
                thisSerializer.writeInt32(value_value_1.length as int32)
                for (let i = 0; i < value_value_1.length; i++) {
                    const value_value_1_element : ShadowOptions = value_value_1[i]
                    ShadowOptions_serializer.write(thisSerializer, value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_heightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textIndentAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    wordBreakAttribute(value: WordBreak | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as WordBreak)
            thisSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_wordBreak(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as LineBreakStrategy)
            thisSerializer.writeInt32(TypeChecker.LineBreakStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_lineBreakStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onCopyAttribute(value: ((value: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3)
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ellipsisModeAttribute(value: EllipsisMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as EllipsisMode)
            thisSerializer.writeInt32(TypeChecker.EllipsisMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_ellipsisMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_enableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    marqueeOptionsAttribute(value: TextMarqueeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TextMarqueeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_marqueeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onMarqueeStateChangeAttribute(value: ((value0: MarqueeState) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_onMarqueeStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textSelectableAttribute(value: TextSelectableMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as TextSelectableMode)
            thisSerializer.writeInt32(TypeChecker.TextSelectableMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_textSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            EditMenuOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    halfLeadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_halfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_enableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontAttribute(fontValue: Font | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let fontValue_type : int32 = RuntimeType.UNDEFINED
        fontValue_type = runtimeType(fontValue)
        thisSerializer.writeInt8(fontValue_type)
        if ((RuntimeType.UNDEFINED) != (fontValue_type)) {
            const fontValue_value  = fontValue!
            Font_serializer.write(thisSerializer, fontValue_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            FontSettingOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_font(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let weight_type : int32 = RuntimeType.UNDEFINED
        weight_type = runtimeType(weight)
        thisSerializer.writeInt8(weight_type)
        if ((RuntimeType.UNDEFINED) != (weight_type)) {
            const weight_value  = weight!
            let weight_value_type : int32 = RuntimeType.UNDEFINED
            weight_value_type = runtimeType(weight_value)
            if (RuntimeType.NUMBER == weight_value_type) {
                thisSerializer.writeInt8(0)
                const weight_value_0  = weight_value as number
                thisSerializer.writeNumber(weight_value_0)
            }
            else if (TypeChecker.isFontWeight(weight_value)) {
                thisSerializer.writeInt8(1)
                const weight_value_1  = weight_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(weight_value_1))
            }
            else if (RuntimeType.STRING == weight_value_type) {
                thisSerializer.writeInt8(2)
                const weight_value_2  = weight_value as string
                thisSerializer.writeString(weight_value_2)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            FontSettingOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    selectionAttribute(selectionStart: number | undefined, selectionEnd: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let selectionStart_type : int32 = RuntimeType.UNDEFINED
        selectionStart_type = runtimeType(selectionStart)
        thisSerializer.writeInt8(selectionStart_type)
        if ((RuntimeType.UNDEFINED) != (selectionStart_type)) {
            const selectionStart_value  = selectionStart!
            thisSerializer.writeNumber(selectionStart_value)
        }
        let selectionEnd_type : int32 = RuntimeType.UNDEFINED
        selectionEnd_type = runtimeType(selectionEnd)
        thisSerializer.writeInt8(selectionEnd_type)
        if ((RuntimeType.UNDEFINED) != (selectionEnd_type)) {
            const selectionEnd_value  = selectionEnd!
            thisSerializer.writeNumber(selectionEnd_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_selection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSelectionMenuAttribute(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let spanType_type : int32 = RuntimeType.UNDEFINED
        spanType_type = runtimeType(spanType)
        thisSerializer.writeInt8(spanType_type)
        if ((RuntimeType.UNDEFINED) != (spanType_type)) {
            const spanType_value  = (spanType as TextSpanType)
            thisSerializer.writeInt32(TypeChecker.TextSpanType_ToNumeric(spanType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8(responseType_type)
        if ((RuntimeType.UNDEFINED) != (responseType_type)) {
            const responseType_value  = (responseType as TextResponseType)
            thisSerializer.writeInt32(TypeChecker.TextResponseType_ToNumeric(responseType_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            SelectionMenuOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_bindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextOverflowOptions {
    overflow: TextOverflow;
}
export interface TextAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): this
    fontSize(value: number | string | Resource | undefined): this
    minFontSize(value: number | string | Resource | undefined): this
    maxFontSize(value: number | string | Resource | undefined): this
    minFontScale(value: number | Resource | undefined): this
    maxFontScale(value: number | Resource | undefined): this
    fontStyle(value: FontStyle | undefined): this
    lineSpacing(value: LengthMetrics | undefined): this
    textAlign(value: TextAlign | undefined): this
    lineHeight(value: number | string | Resource | undefined): this
    textOverflow(value: TextOverflowOptions | undefined): this
    fontFamily(value: string | Resource | undefined): this
    maxLines(value: number | undefined): this
    decoration(value: DecorationStyleInterface | undefined): this
    letterSpacing(value: number | string | undefined): this
    textCase(value: TextCase | undefined): this
    baselineOffset(value: number | string | undefined): this
    copyOption(value: CopyOptions | undefined): this
    draggable(value: boolean | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this
    textIndent(value: Length | undefined): this
    wordBreak(value: WordBreak | undefined): this
    lineBreakStrategy(value: LineBreakStrategy | undefined): this
    onCopy(value: ((value: string) => void) | undefined): this
    caretColor(value: ResourceColor | undefined): this
    selectedBackgroundColor(value: ResourceColor | undefined): this
    ellipsisMode(value: EllipsisMode | undefined): this
    enableDataDetector(value: boolean | undefined): this
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this
    onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this
    fontFeature(value: string | undefined): this
    marqueeOptions(value: TextMarqueeOptions | undefined): this
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this
    privacySensitive(value: boolean | undefined): this
    textSelectable(value: TextSelectableMode | undefined): this
    editMenuOptions(value: EditMenuOptions | undefined): this
    halfLeading(value: boolean | undefined): this
    enableHapticFeedback(value: boolean | undefined): this
    font(fontValue: Font | undefined, options?: FontSettingOptions): this
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this
    attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTextStyle extends ArkCommonMethodStyle implements TextAttribute {
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: number | string | Resource | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    fontStyle_value?: FontStyle | undefined
    lineSpacing_value?: LengthMetrics | undefined
    textAlign_value?: TextAlign | undefined
    lineHeight_value?: number | string | Resource | undefined
    textOverflow_value?: TextOverflowOptions | undefined
    fontFamily_value?: string | Resource | undefined
    maxLines_value?: number | undefined
    decoration_value?: DecorationStyleInterface | undefined
    letterSpacing_value?: number | string | undefined
    textCase_value?: TextCase | undefined
    baselineOffset_value?: number | string | undefined
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
    onTextSelectionChange_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    fontFeature_value?: string | undefined
    marqueeOptions_value?: TextMarqueeOptions | undefined
    onMarqueeStateChange_value?: ((value0: MarqueeState) => void) | undefined
    privacySensitive_value?: boolean | undefined
    textSelectable_value?: TextSelectableMode | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    halfLeading_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
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
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public maxLines(value: number | undefined): this {
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        return this
    }
    public textCase(value: TextCase | undefined): this {
        return this
    }
    public baselineOffset(value: number | string | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public draggable(value: boolean | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    public textIndent(value: Length | undefined): this {
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        return this
    }
    public fontFeature(value: string | undefined): this {
        return this
    }
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        return this
    }
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        return this
    }
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextAttribute): void {
        super.apply(target)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.minFontSize_value !== undefined)
            target.minFontSize(this.minFontSize_value!)
        if (this.maxFontSize_value !== undefined)
            target.maxFontSize(this.maxFontSize_value!)
        if (this.minFontScale_value !== undefined)
            target.minFontScale(this.minFontScale_value!)
        if (this.maxFontScale_value !== undefined)
            target.maxFontScale(this.maxFontScale_value!)
        if (this.fontStyle_value !== undefined)
            target.fontStyle(this.fontStyle_value!)
        if (this.lineSpacing_value !== undefined)
            target.lineSpacing(this.lineSpacing_value!)
        if (this.textAlign_value !== undefined)
            target.textAlign(this.textAlign_value!)
        if (this.lineHeight_value !== undefined)
            target.lineHeight(this.lineHeight_value!)
        if (this.textOverflow_value !== undefined)
            target.textOverflow(this.textOverflow_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.maxLines_value !== undefined)
            target.maxLines(this.maxLines_value!)
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
        if (this.letterSpacing_value !== undefined)
            target.letterSpacing(this.letterSpacing_value!)
        if (this.textCase_value !== undefined)
            target.textCase(this.textCase_value!)
        if (this.baselineOffset_value !== undefined)
            target.baselineOffset(this.baselineOffset_value!)
        if (this.copyOption_value !== undefined)
            target.copyOption(this.copyOption_value!)
        if (this.draggable_value !== undefined)
            target.draggable(this.draggable_value!)
        if (this.textShadow_value !== undefined)
            target.textShadow(this.textShadow_value!)
        if (this.heightAdaptivePolicy_value !== undefined)
            target.heightAdaptivePolicy(this.heightAdaptivePolicy_value!)
        if (this.textIndent_value !== undefined)
            target.textIndent(this.textIndent_value!)
        if (this.wordBreak_value !== undefined)
            target.wordBreak(this.wordBreak_value!)
        if (this.lineBreakStrategy_value !== undefined)
            target.lineBreakStrategy(this.lineBreakStrategy_value!)
        if (this.onCopy_value !== undefined)
            target.onCopy(this.onCopy_value!)
        if (this.caretColor_value !== undefined)
            target.caretColor(this.caretColor_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.ellipsisMode_value !== undefined)
            target.ellipsisMode(this.ellipsisMode_value!)
        if (this.enableDataDetector_value !== undefined)
            target.enableDataDetector(this.enableDataDetector_value!)
        if (this.dataDetectorConfig_value !== undefined)
            target.dataDetectorConfig(this.dataDetectorConfig_value!)
        if (this.onTextSelectionChange_value !== undefined)
            target.onTextSelectionChange(this.onTextSelectionChange_value!)
        if (this.fontFeature_value !== undefined)
            target.fontFeature(this.fontFeature_value!)
        if (this.marqueeOptions_value !== undefined)
            target.marqueeOptions(this.marqueeOptions_value!)
        if (this.onMarqueeStateChange_value !== undefined)
            target.onMarqueeStateChange(this.onMarqueeStateChange_value!)
        if (this.privacySensitive_value !== undefined)
            target.privacySensitive(this.privacySensitive_value!)
        if (this.textSelectable_value !== undefined)
            target.textSelectable(this.textSelectable_value!)
        if (this.editMenuOptions_value !== undefined)
            target.editMenuOptions(this.editMenuOptions_value!)
        if (this.halfLeading_value !== undefined)
            target.halfLeading(this.halfLeading_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
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
    step?: number;
    loop?: number;
    fromStart?: boolean;
    delay?: number;
    fadeout?: boolean;
    marqueeStartPolicy?: MarqueeStartPolicy;
}

export class ArkTextComponent extends ArkCommonMethodComponent implements TextAttribute {
    getPeer(): ArkTextPeer {
        return (this.peer as ArkTextPeer)
    }
    public setTextOptions(content?: string | Resource, value?: TextOptions): this {
        if (this.checkPriority("setTextOptions")) {
            const content_casted = content as (string | Resource | undefined)
            const value_casted = value as (TextOptions | undefined)
            this.getPeer()?.setTextOptionsAttribute(content_casted, value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.lineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.textAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflowOptions | undefined)
            this.getPeer()?.textOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.textCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: number | string | undefined): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.baselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.textShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Length | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak | undefined)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy | undefined)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value: string) => void) | undefined)
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.caretColorAttribute(value_casted)
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
    public ellipsisMode(value: EllipsisMode | undefined): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode | undefined)
            this.getPeer()?.ellipsisModeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig | undefined)
            this.getPeer()?.dataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((selectionStart: number,selectionEnd: number) => void) | undefined)
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (this.checkPriority("marqueeOptions")) {
            const value_casted = value as (TextMarqueeOptions | undefined)
            this.getPeer()?.marqueeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        if (this.checkPriority("onMarqueeStateChange")) {
            const value_casted = value as (((value0: MarqueeState) => void) | undefined)
            this.getPeer()?.onMarqueeStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        if (this.checkPriority("textSelectable")) {
            const value_casted = value as (TextSelectableMode | undefined)
            this.getPeer()?.textSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.halfLeadingAttribute(value_casted)
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
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("font")) {
            const fontValue_casted = fontValue as (Font | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.fontAttribute(fontValue_casted, options_casted)
            return this
        }
        return this
    }
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("fontWeight")) {
            const weight_casted = weight as (number | FontWeight | string | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.fontWeightAttribute(weight_casted, options_casted)
            return this
        }
        return this
    }
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        if (this.checkPriority("selection")) {
            const selectionStart_casted = selectionStart as (number | undefined)
            const selectionEnd_casted = selectionEnd as (number | undefined)
            this.getPeer()?.selectionAttribute(selectionStart_casted, selectionEnd_casted)
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
            this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextStyle(receiver: TextAttribute, modifier: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("TextImpl")
export function Text(
    content?: string | Resource | undefined, value?: TextOptions | undefined,
    @memo
    content_?: () => void,
): TextAttribute {
    throw new Error("Not implemented")
}

@memo
export function TextImpl(
    @memo
    style: ((attributes: TextAttribute) => void) | undefined,
    content?: string | Resource | undefined, value?: TextOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextComponent>((): ArkTextComponent => {
        return new ArkTextComponent()
    })
    NodeAttach<ArkTextPeer>((): ArkTextPeer => ArkTextPeer.create(receiver), (_: ArkTextPeer): void => {
        receiver.setTextOptions(content,value)
        style?.(receiver)
        withTextStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
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
        const value_controller  = value.controller
        TextController_serializer.write(valueSerializer, value_controller)
    }
    public static read(buffer: DeserializerBase): TextOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controller_result : TextController = (TextController_serializer.read(valueDeserializer) as TextController)
        let value : TextOptions = ({controller: controller_result} as TextOptions)
        return value
    }
}
export class TextOverflowOptions_serializer {
    public static write(buffer: SerializerBase, value: TextOverflowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_overflow  = value.overflow
        valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow))
    }
    public static read(buffer: DeserializerBase): TextOverflowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const overflow_result : TextOverflow = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        let value : TextOverflowOptions = ({overflow: overflow_result} as TextOverflowOptions)
        return value
    }
}
export class TextMarqueeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMarqueeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeBoolean(value_start)
        const value_step  = value.step
        let value_step_type : int32 = RuntimeType.UNDEFINED
        value_step_type = runtimeType(value_step)
        valueSerializer.writeInt8(value_step_type)
        if ((RuntimeType.UNDEFINED) != (value_step_type)) {
            const value_step_value  = value_step!
            valueSerializer.writeNumber(value_step_value)
        }
        const value_loop  = value.loop
        let value_loop_type : int32 = RuntimeType.UNDEFINED
        value_loop_type = runtimeType(value_loop)
        valueSerializer.writeInt8(value_loop_type)
        if ((RuntimeType.UNDEFINED) != (value_loop_type)) {
            const value_loop_value  = value_loop!
            valueSerializer.writeNumber(value_loop_value)
        }
        const value_fromStart  = value.fromStart
        let value_fromStart_type : int32 = RuntimeType.UNDEFINED
        value_fromStart_type = runtimeType(value_fromStart)
        valueSerializer.writeInt8(value_fromStart_type)
        if ((RuntimeType.UNDEFINED) != (value_fromStart_type)) {
            const value_fromStart_value  = value_fromStart!
            valueSerializer.writeBoolean(value_fromStart_value)
        }
        const value_delay  = value.delay
        let value_delay_type : int32 = RuntimeType.UNDEFINED
        value_delay_type = runtimeType(value_delay)
        valueSerializer.writeInt8(value_delay_type)
        if ((RuntimeType.UNDEFINED) != (value_delay_type)) {
            const value_delay_value  = value_delay!
            valueSerializer.writeNumber(value_delay_value)
        }
        const value_fadeout  = value.fadeout
        let value_fadeout_type : int32 = RuntimeType.UNDEFINED
        value_fadeout_type = runtimeType(value_fadeout)
        valueSerializer.writeInt8(value_fadeout_type)
        if ((RuntimeType.UNDEFINED) != (value_fadeout_type)) {
            const value_fadeout_value  = value_fadeout!
            valueSerializer.writeBoolean(value_fadeout_value)
        }
        const value_marqueeStartPolicy  = value.marqueeStartPolicy
        let value_marqueeStartPolicy_type : int32 = RuntimeType.UNDEFINED
        value_marqueeStartPolicy_type = runtimeType(value_marqueeStartPolicy)
        valueSerializer.writeInt8(value_marqueeStartPolicy_type)
        if ((RuntimeType.UNDEFINED) != (value_marqueeStartPolicy_type)) {
            const value_marqueeStartPolicy_value  = (value_marqueeStartPolicy as MarqueeStartPolicy)
            valueSerializer.writeInt32(TypeChecker.MarqueeStartPolicy_ToNumeric(value_marqueeStartPolicy_value))
        }
    }
    public static read(buffer: DeserializerBase): TextMarqueeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : boolean = valueDeserializer.readBoolean()
        const step_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let step_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (step_buf_runtimeType))
        {
            step_buf = (valueDeserializer.readNumber() as number)
        }
        const step_result : number | undefined = step_buf
        const loop_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let loop_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (loop_buf_runtimeType))
        {
            loop_buf = (valueDeserializer.readNumber() as number)
        }
        const loop_result : number | undefined = loop_buf
        const fromStart_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fromStart_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (fromStart_buf_runtimeType))
        {
            fromStart_buf = valueDeserializer.readBoolean()
        }
        const fromStart_result : boolean | undefined = fromStart_buf
        const delay_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let delay_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (delay_buf_runtimeType))
        {
            delay_buf = (valueDeserializer.readNumber() as number)
        }
        const delay_result : number | undefined = delay_buf
        const fadeout_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let fadeout_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (fadeout_buf_runtimeType))
        {
            fadeout_buf = valueDeserializer.readBoolean()
        }
        const fadeout_result : boolean | undefined = fadeout_buf
        const marqueeStartPolicy_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let marqueeStartPolicy_buf : MarqueeStartPolicy | undefined
        if ((RuntimeType.UNDEFINED) != (marqueeStartPolicy_buf_runtimeType))
        {
            marqueeStartPolicy_buf = TypeChecker.MarqueeStartPolicy_FromNumeric(valueDeserializer.readInt32())
        }
        const marqueeStartPolicy_result : MarqueeStartPolicy | undefined = marqueeStartPolicy_buf
        let value : TextMarqueeOptions = ({start: start_result, step: step_result, loop: loop_result, fromStart: fromStart_result, delay: delay_result, fadeout: fadeout_result, marqueeStartPolicy: marqueeStartPolicy_result} as TextMarqueeOptions)
        return value
    }
}
