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

import { int32, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontStyle, FontWeight, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode } from "./../../component/enums"
import { LengthMetrics } from "../../Graphics"
import { ResizableOptions } from "./../../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { AttributeModifier } from "./../../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface } from "./../../component/gesture"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { TextOverflowOptions, TextAttribute, TextSpanType, TextResponseType, TextOptions } from "./../../component/text"
import { DecorationStyleInterface } from "./../../component/styledString"
import { Callback_String_Void } from "./../../component/gridRow"
import { TextDataDetectorConfig, EditMenuOptions, FontSettingOptions } from "./../../component/textCommon"
import { Callback_Number_Number_Void } from "./../../component/grid"
import { SelectionMenuOptions } from "./../../component/richEditor"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
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
            thisSerializer.writeInt32(value_0.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_fontStyle(this.peer.ptr, value.valueOf())
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
            thisSerializer.writeInt32(value_1.valueOf())
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
            thisSerializer.writeInt32(weight_1.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_textAlign(this.peer.ptr, value.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_textCase(this.peer.ptr, value.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_copyOption(this.peer.ptr, value.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_heightAdaptivePolicy(this.peer.ptr, value.valueOf())
    }
    textIndentAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._TextAttribute_textIndent(this.peer.ptr, value)
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextAttribute_wordBreak(this.peer.ptr, value.valueOf())
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextAttribute_lineBreakStrategy(this.peer.ptr, value.valueOf())
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
            thisSerializer.writeInt32(value_0.valueOf())
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
            thisSerializer.writeInt32(value_0.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_ellipsisMode(this.peer.ptr, value.valueOf())
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
        ArkUIGeneratedNativeModule._TextAttribute_textSelectable(this.peer.ptr, value.valueOf())
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        ArkUIGeneratedNativeModule._TextAttribute_editMenuOptions(this.peer.ptr, toPeerPtr(value))
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
        ArkUIGeneratedNativeModule._TextAttribute_bindSelectionMenu(this.peer.ptr, spanType.valueOf(), thisSerializer.asBuffer(), thisSerializer.length(), responseType.valueOf())
        thisSerializer.release()
    }
}
export interface ArkTextAttributes extends ArkCommonMethodAttributes {
    font?: Font
    fontColor?: ResourceColor
    fontSize?: number | string | Resource
    minFontSize?: number | string | Resource
    maxFontSize?: number | string | Resource
    minFontScale?: number | Resource
    maxFontScale?: number | Resource
    fontStyle?: FontStyle
    fontWeight?: number | FontWeight | string
    lineSpacing?: LengthMetrics
    textAlign?: TextAlign
    lineHeight?: number | string | Resource
    textOverflow?: TextOverflowOptions
    fontFamily?: string | Resource
    maxLines?: number
    decoration?: DecorationStyleInterface
    letterSpacing?: number | string
    textCase?: TextCase
    baselineOffset?: number | string
    copyOption?: CopyOptions
    draggable?: boolean
    textShadow?: ShadowOptions | Array<ShadowOptions>
    heightAdaptivePolicy?: TextHeightAdaptivePolicy
    textIndent?: Length
    wordBreak?: WordBreak
    lineBreakStrategy?: LineBreakStrategy
    onCopy?: ((breakpoints: string) => void)
    caretColor?: ResourceColor
    selectedBackgroundColor?: ResourceColor
    ellipsisMode?: EllipsisMode
    enableDataDetector?: boolean
    dataDetectorConfig?: TextDataDetectorConfig
    onTextSelectionChange?: ((first: number,last: number) => void)
    fontFeature?: string
    privacySensitive?: boolean
    textSelectable?: TextSelectableMode
    editMenuOptions?: EditMenuOptions
    halfLeading?: boolean
    enableHapticFeedback?: boolean
}
