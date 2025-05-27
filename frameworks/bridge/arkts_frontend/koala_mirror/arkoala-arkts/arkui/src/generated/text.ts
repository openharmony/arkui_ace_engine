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

import { StyledString, StyledStringInternal, DecorationStyleInterface } from "./styled_string"
import { LayoutManager, LayoutManagerInternal, TextDataDetectorConfig, EditMenuOptions, FontSettingOptions, MenuType } from "./text_common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ShadowOptions, CustomBuilder, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Font, ResourceColor, Length } from "./units"
import { Resource } from "./resource"
import { FontStyle, EllipsisMode } from "./arkui-graphics-text"
import { FontWeight, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, TextSelectableMode, Color, TextOverflow } from "./enums"
import { LengthMetrics } from "./arkui-graphics"
import { Callback_String_Void } from "./grid_row"
import { Callback_Number_Number_Void } from "./grid"
import { SelectionMenuOptions, MenuOnAppearCallback } from "./rich_editor"
import { Callback_Void } from "./ability_component"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextControllerInternal {
    public static fromPtr(ptr: KPointer): TextController {
        const obj : TextController = new TextController()
        obj.peer = new Finalizable(ptr, TextController.getFinalizer())
        return obj
    }
}
export class TextController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextController.ctor_textcontroller()
        this.peer = new Finalizable(ctorPtr, TextController.getFinalizer())
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
        const thisSerializer : Serializer = Serializer.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type as int32)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const content_value_1  = content_value as Resource
                thisSerializer.writeResource(content_value_1)
            }
        }
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTextOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextInterface_setTextOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    font0Attribute(value: Font): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._TextAttribute_font0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    font1Attribute(fontValue: Font, options?: FontSettingOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeFont(fontValue)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeFontSettingOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_font1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._TextAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._TextAttribute_fontStyle(this.peer.ptr, TypeChecker.FontStyle_ToNumeric(value))
    }
    fontWeight0Attribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontWeight0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeight1Attribute(weight: number | FontWeight | string, options?: FontSettingOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let weight_type : int32 = RuntimeType.UNDEFINED
        weight_type = runtimeType(weight)
        if (RuntimeType.NUMBER == weight_type) {
            thisSerializer.writeInt8(0 as int32)
            const weight_0  = weight as number
            thisSerializer.writeNumber(weight_0)
        }
        else if (TypeChecker.isFontWeight(weight)) {
            thisSerializer.writeInt8(1 as int32)
            const weight_1  = weight as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(weight_1))
        }
        else if (RuntimeType.STRING == weight_type) {
            thisSerializer.writeInt8(2 as int32)
            const weight_2  = weight as string
            thisSerializer.writeString(weight_2)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeFontSettingOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontWeight1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineSpacingAttribute(value: LengthMetrics): void {
        ArkUIGeneratedNativeModule._TextAttribute_lineSpacing(this.peer.ptr, toPeerPtr(value))
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._TextAttribute_textAlign(this.peer.ptr, TypeChecker.TextAlign_ToNumeric(value))
    }
    lineHeightAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_lineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextOverflowOptions(value)
        ArkUIGeneratedNativeModule._TextAttribute_textOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextAttribute_maxLines(this.peer.ptr, value)
    }
    decorationAttribute(value: DecorationStyleInterface): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDecorationStyleInterface(value)
        ArkUIGeneratedNativeModule._TextAttribute_decoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_letterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    textCaseAttribute(value: TextCase): void {
        ArkUIGeneratedNativeModule._TextAttribute_textCase(this.peer.ptr, TypeChecker.TextCase_ToNumeric(value))
    }
    baselineOffsetAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_baselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._TextAttribute_copyOption(this.peer.ptr, TypeChecker.CopyOptions_ToNumeric(value))
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_draggable(this.peer.ptr, value ? 1 : 0)
    }
    textShadowAttribute(value: ShadowOptions | Array<ShadowOptions>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isShadowOptions(value, false, false, false, false, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ShadowOptions
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_ShadowOptions(value))) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Array<ShadowOptions>
            thisSerializer.writeInt32(value_1.length as int32)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element : ShadowOptions = value_1[i]
                thisSerializer.writeShadowOptions(value_1_element)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_textShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy): void {
        ArkUIGeneratedNativeModule._TextAttribute_heightAdaptivePolicy(this.peer.ptr, TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value))
    }
    textIndentAttribute(value: Length): void {
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
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_textIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextAttribute_wordBreak(this.peer.ptr, TypeChecker.WordBreak_ToNumeric(value))
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextAttribute_lineBreakStrategy(this.peer.ptr, TypeChecker.LineBreakStrategy_ToNumeric(value))
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAttribute_onCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._TextAttribute_caretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._TextAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ellipsisModeAttribute(value: EllipsisMode): void {
        ArkUIGeneratedNativeModule._TextAttribute_ellipsisMode(this.peer.ptr, TypeChecker.EllipsisMode_ToNumeric(value))
    }
    enableDataDetectorAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_enableDataDetector(this.peer.ptr, value ? 1 : 0)
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextDataDetectorConfig(value)
        ArkUIGeneratedNativeModule._TextAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextAttribute_fontFeature(this.peer.ptr, value)
    }
    privacySensitiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_privacySensitive(this.peer.ptr, value ? 1 : 0)
    }
    textSelectableAttribute(value: TextSelectableMode): void {
        ArkUIGeneratedNativeModule._TextAttribute_textSelectable(this.peer.ptr, TypeChecker.TextSelectableMode_ToNumeric(value))
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeEditMenuOptions(value)
        ArkUIGeneratedNativeModule._TextAttribute_editMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    halfLeadingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_halfLeading(this.peer.ptr, value ? 1 : 0)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_enableHapticFeedback(this.peer.ptr, value ? 1 : 0)
    }
    selectionAttribute(selectionStart: number, selectionEnd: number): void {
        ArkUIGeneratedNativeModule._TextAttribute_selection(this.peer.ptr, selectionStart, selectionEnd)
    }
    bindSelectionMenuAttribute(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_bindSelectionMenu(this.peer.ptr, TypeChecker.TextSpanType_ToNumeric(spanType), thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.TextResponseType_ToNumeric(responseType))
        thisSerializer.release()
    }
}
export interface TextOverflowOptions {
    overflow: TextOverflow;
}

export interface TextAttribute extends CommonMethod {
    font(fontValue: Font, options?: FontSettingOptions): this
    fontColor(value: ResourceColor): this
    fontSize(value: number | string | Resource): this
    minFontSize(value: number | string | Resource): this
    maxFontSize(value: number | string | Resource): this
    minFontScale(value: number | Resource): this
    maxFontScale(value: number | Resource): this
    fontStyle(value: FontStyle): this
    fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this
    lineSpacing(value: LengthMetrics): this
    textAlign(value: TextAlign): this
    lineHeight(value: number | string | Resource): this
    textOverflow(value: TextOverflowOptions): this
    fontFamily(value: string | Resource): this
    maxLines(value: number): this
    decoration(value: DecorationStyleInterface): this
    letterSpacing(value: number | string): this
    textCase(value: TextCase): this
    baselineOffset(value: number | string): this
    copyOption(value: CopyOptions): this
    draggable(value: boolean): this
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    textIndent(value: Length): this
    wordBreak(value: WordBreak): this
    lineBreakStrategy(value: LineBreakStrategy): this
    onCopy(value: ((breakpoints: string) => void)): this
    caretColor(value: ResourceColor): this
    selectedBackgroundColor(value: ResourceColor): this
    ellipsisMode(value: EllipsisMode): this
    enableDataDetector(value: boolean): this
    dataDetectorConfig(value: TextDataDetectorConfig): this
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    fontFeature(value: string): this
    privacySensitive(value: boolean): this
    textSelectable(value: TextSelectableMode): this
    editMenuOptions(value: EditMenuOptions): this
    halfLeading(value: boolean): this
    enableHapticFeedback(value: boolean): this
    selection(selectionStart: number, selectionEnd: number): this
    bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this
    attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UITextAttribute extends UICommonMethod {
    /** @memo */
    font(fontValue: Font, options?: FontSettingOptions): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: number | string | Resource): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    minFontScale(value: number | Resource): this
    /** @memo */
    maxFontScale(value: number | Resource): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this
    /** @memo */
    lineSpacing(value: LengthMetrics): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    textOverflow(value: TextOverflowOptions): this
    /** @memo */
    fontFamily(value: string | Resource): this
    /** @memo */
    maxLines(value: number): this
    /** @memo */
    decoration(value: DecorationStyleInterface): this
    /** @memo */
    letterSpacing(value: number | string): this
    /** @memo */
    textCase(value: TextCase): this
    /** @memo */
    baselineOffset(value: number | string): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    draggable(value: boolean): this
    /** @memo */
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    /** @memo */
    textIndent(value: Length): this
    /** @memo */
    wordBreak(value: WordBreak): this
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    caretColor(value: ResourceColor): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    ellipsisMode(value: EllipsisMode): this
    /** @memo */
    enableDataDetector(value: boolean): this
    /** @memo */
    dataDetectorConfig(value: TextDataDetectorConfig): this
    /** @memo */
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    privacySensitive(value: boolean): this
    /** @memo */
    textSelectable(value: TextSelectableMode): this
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this
    /** @memo */
    halfLeading(value: boolean): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    selection(selectionStart: number, selectionEnd: number): this
    /** @memo */
    bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this
    /** @memo */
    attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkTextStyle extends ArkCommonMethodStyle implements TextAttribute {
    font_value?: Font
    fontColor_value?: ResourceColor
    fontSize_value?: number | string | Resource
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    minFontScale_value?: number | Resource
    maxFontScale_value?: number | Resource
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    lineSpacing_value?: LengthMetrics
    textAlign_value?: TextAlign
    lineHeight_value?: number | string | Resource
    textOverflow_value?: TextOverflowOptions
    fontFamily_value?: string | Resource
    maxLines_value?: number
    decoration_value?: DecorationStyleInterface
    letterSpacing_value?: number | string
    textCase_value?: TextCase
    baselineOffset_value?: number | string
    copyOption_value?: CopyOptions
    draggable_value?: boolean
    textShadow_value?: ShadowOptions | Array<ShadowOptions>
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    textIndent_value?: Length
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    onCopy_value?: ((breakpoints: string) => void)
    caretColor_value?: ResourceColor
    selectedBackgroundColor_value?: ResourceColor
    ellipsisMode_value?: EllipsisMode
    enableDataDetector_value?: boolean
    dataDetectorConfig_value?: TextDataDetectorConfig
    onTextSelectionChange_value?: ((first: number,last: number) => void)
    fontFeature_value?: string
    privacySensitive_value?: boolean
    textSelectable_value?: TextSelectableMode
    editMenuOptions_value?: EditMenuOptions
    halfLeading_value?: boolean
    enableHapticFeedback_value?: boolean
    public font(fontValue: Font, options?: FontSettingOptions): this {
        return this
    }
    public fontColor(value: ResourceColor): this {
        return this
    }
    public fontSize(value: number | string | Resource): this {
        return this
    }
    public minFontSize(value: number | string | Resource): this {
        return this
    }
    public maxFontSize(value: number | string | Resource): this {
        return this
    }
    public minFontScale(value: number | Resource): this {
        return this
    }
    public maxFontScale(value: number | Resource): this {
        return this
    }
    public fontStyle(value: FontStyle): this {
        return this
    }
    public fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this {
        return this
    }
    public lineSpacing(value: LengthMetrics): this {
        return this
    }
    public textAlign(value: TextAlign): this {
        return this
    }
    public lineHeight(value: number | string | Resource): this {
        return this
    }
    public textOverflow(value: TextOverflowOptions): this {
        return this
    }
    public fontFamily(value: string | Resource): this {
        return this
    }
    public maxLines(value: number): this {
        return this
    }
    public decoration(value: DecorationStyleInterface): this {
        return this
    }
    public letterSpacing(value: number | string): this {
        return this
    }
    public textCase(value: TextCase): this {
        return this
    }
    public baselineOffset(value: number | string): this {
        return this
    }
    public copyOption(value: CopyOptions): this {
        return this
    }
    public draggable(value: boolean): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions>): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        return this
    }
    public textIndent(value: Length): this {
        return this
    }
    public wordBreak(value: WordBreak): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy): this {
        return this
    }
    public onCopy(value: ((breakpoints: string) => void)): this {
        return this
    }
    public caretColor(value: ResourceColor): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor): this {
        return this
    }
    public ellipsisMode(value: EllipsisMode): this {
        return this
    }
    public enableDataDetector(value: boolean): this {
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig): this {
        return this
    }
    public onTextSelectionChange(value: ((first: number,last: number) => void)): this {
        return this
    }
    public fontFeature(value: string): this {
        return this
    }
    public privacySensitive(value: boolean): this {
        return this
    }
    public textSelectable(value: TextSelectableMode): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions): this {
        return this
    }
    public halfLeading(value: boolean): this {
        return this
    }
    public enableHapticFeedback(value: boolean): this {
        return this
    }
    public selection(selectionStart: number, selectionEnd: number): this {
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2
}
export enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2
}
export interface TextOptions {
    controller: TextController;
}
/** @memo:stable */
export class ArkTextComponent extends ArkCommonMethodComponent implements UITextAttribute {
    getPeer(): ArkTextPeer {
        return (this.peer as ArkTextPeer)
    }
    /** @memo */
    public setTextOptions(content?: string | Resource, value?: TextOptions): this {
        if (this.checkPriority("setTextOptions")) {
            const content_casted = content as (string | Resource | undefined)
            const value_casted = value as (TextOptions | undefined)
            this.getPeer()?.setTextOptionsAttribute(content_casted, value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public font(fontValue: Font, options?: FontSettingOptions): this {
        if (this.checkPriority("font")) {
            const fontValue_type = runtimeType(fontValue)
            const options_type = runtimeType(options)
            const value_casted = fontValue as (Font)
            this.getPeer()?.font0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: number | string | Resource): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minFontSize(value: number | string | Resource): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxFontSize(value: number | string | Resource): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minFontScale(value: number | Resource): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.minFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxFontScale(value: number | Resource): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.maxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this {
        if (this.checkPriority("fontWeight")) {
            const weight_type = runtimeType(weight)
            const options_type = runtimeType(options)
            if ((RuntimeType.NUMBER == weight_type) || (TypeChecker.isFontWeight(weight)) || (RuntimeType.STRING == weight_type)) {
                const value_casted = weight as (number | FontWeight | string)
                this.getPeer()?.fontWeight0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.NUMBER == weight_type) || (TypeChecker.isFontWeight(weight)) || (RuntimeType.STRING == weight_type)) {
                const weight_casted = weight as (number | FontWeight | string)
                const options_casted = options as (FontSettingOptions | undefined)
                this.getPeer()?.fontWeight1Attribute(weight_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public lineSpacing(value: LengthMetrics): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics)
            this.getPeer()?.lineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textAlign(value: TextAlign): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign)
            this.getPeer()?.textAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineHeight(value: number | string | Resource): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textOverflow(value: TextOverflowOptions): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflowOptions)
            this.getPeer()?.textOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: string | Resource): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource)
            this.getPeer()?.fontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLines(value: number): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public decoration(value: DecorationStyleInterface): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public letterSpacing(value: number | string): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textCase(value: TextCase): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase)
            this.getPeer()?.textCaseAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public baselineOffset(value: number | string): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (number | string)
            this.getPeer()?.baselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textShadow(value: ShadowOptions | Array<ShadowOptions>): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions>)
            this.getPeer()?.textShadowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textIndent(value: Length): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Length)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public wordBreak(value: WordBreak): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineBreakStrategy(value: LineBreakStrategy): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCopy(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretColor(value: ResourceColor): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.caretColorAttribute(value_casted)
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
    public ellipsisMode(value: EllipsisMode): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode)
            this.getPeer()?.ellipsisModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableDataDetector(value: boolean): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dataDetectorConfig(value: TextDataDetectorConfig): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig)
            this.getPeer()?.dataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTextSelectionChange(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFeature(value: string): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public privacySensitive(value: boolean): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textSelectable(value: TextSelectableMode): this {
        if (this.checkPriority("textSelectable")) {
            const value_casted = value as (TextSelectableMode)
            this.getPeer()?.textSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public halfLeading(value: boolean): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean)
            this.getPeer()?.halfLeadingAttribute(value_casted)
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
    public selection(selectionStart: number, selectionEnd: number): this {
        if (this.checkPriority("selection")) {
            const selectionStart_casted = selectionStart as (number)
            const selectionEnd_casted = selectionEnd as (number)
            this.getPeer()?.selectionAttribute(selectionStart_casted, selectionEnd_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const spanType_casted = spanType as (TextSpanType)
            const content_casted = content as (CustomBuilder)
            const responseType_casted = responseType as (TextResponseType)
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkText(
    /** @memo */
    style: ((attributes: UITextAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    content?: string | Resource, value?: TextOptions,
): void {
    const receiver = remember(() => {
        return new ArkTextComponent()
    })
    NodeAttach<ArkTextPeer>((): ArkTextPeer => ArkTextPeer.create(receiver), (_: ArkTextPeer) => {
        receiver.setTextOptions(content,value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
