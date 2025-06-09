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
import { isInstanceOf } from "@koalaui/interop"
import { isResource, isPadding } from "../../utils"
import { ArkUIGeneratedNativeModule } from "../ArkUIGeneratedNativeModule"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, TextOverflow, TextDecorationType, TextDecorationStyle, ImageSpanAlignment, ImageFit } from "./../ArkEnumsInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./../ArkGestureInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, RectWidthStyle, RectHeightStyle } from "./../ArkArkuiExternalInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ICurve } from "./../ArkICurveMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { TextOverflowOptions, TextAttribute, TextSpanType, TextResponseType, TextOptions } from "./../ArkTextInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./../ArkStyledStringInterfaces"
import { TextDataDetectorConfig, FontSettingOptions, TextDataDetectorType, TextMenuItem, TextRange, MenuType, PositionWithAffinity, LineMetrics, TextBox, Affinity } from "./../ArkTextCommonInterfaces"
import { EditMenuOptions } from "./../ArkEditMenuOptionsMaterialized"
import { SelectionMenuOptions, MenuOnAppearCallback } from "./../ArkRichEditorInterfaces"
import { TextMenuItemId } from "./../ArkTextMenuItemIdMaterialized"
import { TextController } from "./../ArkTextControllerMaterialized"
import { StyledString } from "./../ArkStyledStringMaterialized"
import { LayoutManager } from "./../ArkLayoutManagerMaterialized"
import { ImageAttachment } from "./../ArkImageAttachmentMaterialized"
import { CustomSpan } from "./../ArkCustomSpanMaterialized"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Text_construct(peerId, flags)
        const _peer = new ArkTextPeer(_peerPtr, peerId, "Text", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextOptionsAttribute(content?: string | Resource, value?: TextOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let content_type: int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8(content_type)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value = content!
            let content_value_type: int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8(0)
                const content_value_0 = unsafeCast<string>(content_value)
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8(1)
                const content_value_1 = unsafeCast<Resource>(content_value)
                thisSerializer.writeResource(content_value_1)
            }
        }
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeTextOptions(value_value)
        }
        ArkUIGeneratedNativeModule._TextInterface_setTextOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    font0Attribute(value: Font): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFont(value)
        ArkUIGeneratedNativeModule._TextAttribute_font0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    font1Attribute(fontValue: Font, options?: FontSettingOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFont(fontValue)
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeFontSettingOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_font1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    minFontScaleAttribute(value: number | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_minFontScale(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maxFontScaleAttribute(value: number | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_maxFontScale(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontStyleAttribute(value: FontStyle): void {
        ArkUIGeneratedNativeModule._TextAttribute_fontStyle(this.peer.ptr, value)
    }
    fontWeight0Attribute(value: number | FontWeight | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (5))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<FontWeight>(value)
            thisSerializer.writeInt32(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontWeight0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeight1Attribute(weight: number | FontWeight | string, options?: FontSettingOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let weight_type: int32 = RuntimeType.UNDEFINED
        weight_type = runtimeType(weight)
        if (RuntimeType.NUMBER == weight_type) {
            thisSerializer.writeInt8(0)
            const weight_0 = unsafeCast<number>(weight)
            thisSerializer.writeNumber(weight_0)
        }
        else if (((RuntimeType.NUMBER) == (weight_type)) && ((unsafeCast<int32>(weight)) >= (0)) && ((unsafeCast<int32>(weight)) <= (5))) {
            thisSerializer.writeInt8(1)
            const weight_1 = unsafeCast<FontWeight>(weight)
            thisSerializer.writeInt32(weight_1)
        }
        else if (RuntimeType.STRING == weight_type) {
            thisSerializer.writeInt8(2)
            const weight_2 = unsafeCast<string>(weight)
            thisSerializer.writeString(weight_2)
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeFontSettingOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontWeight1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    lineSpacingAttribute(value: LengthMetrics): void {
        ArkUIGeneratedNativeModule._TextAttribute_lineSpacing(this.peer.ptr, toPeerPtr(value))
    }
    textAlignAttribute(value: TextAlign): void {
        ArkUIGeneratedNativeModule._TextAttribute_textAlign(this.peer.ptr, value)
    }
    lineHeightAttribute(value: number | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._TextAttribute_lineHeight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    textOverflowAttribute(value: TextOverflowOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeTextOverflowOptions(value)
        ArkUIGeneratedNativeModule._TextAttribute_textOverflow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFamilyAttribute(value: string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_fontFamily(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maxLinesAttribute(value: number): void {
        ArkUIGeneratedNativeModule._TextAttribute_maxLines(this.peer.ptr, value)
    }
    decorationAttribute(value: DecorationStyleInterface): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeDecorationStyleInterface(value)
        ArkUIGeneratedNativeModule._TextAttribute_decoration(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    letterSpacingAttribute(value: number | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_letterSpacing(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    textCaseAttribute(value: TextCase): void {
        ArkUIGeneratedNativeModule._TextAttribute_textCase(this.peer.ptr, value)
    }
    baselineOffsetAttribute(value: number | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._TextAttribute_baselineOffset(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._TextAttribute_copyOption(this.peer.ptr, value)
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_draggable(this.peer.ptr, +value)
    }
    textShadowAttribute(value: ShadowOptions | Array<ShadowOptions>): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("radius")))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ShadowOptions>(value)
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof Array<ShadowOptions>)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Array<ShadowOptions>>(value)
            thisSerializer.writeInt32(value_1.length)
            for (let i = 0; i < value_1.length; i++) {
                const value_1_element: ShadowOptions = value_1[i]
                thisSerializer.writeShadowOptions(value_1_element)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_textShadow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    heightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy): void {
        ArkUIGeneratedNativeModule._TextAttribute_heightAdaptivePolicy(this.peer.ptr, value)
    }
    textIndentAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._TextAttribute_textIndent(this.peer.ptr, value)
    }
    wordBreakAttribute(value: WordBreak): void {
        ArkUIGeneratedNativeModule._TextAttribute_wordBreak(this.peer.ptr, value)
    }
    lineBreakStrategyAttribute(value: LineBreakStrategy): void {
        ArkUIGeneratedNativeModule._TextAttribute_lineBreakStrategy(this.peer.ptr, value)
    }
    onCopyAttribute(value: ((breakpoints: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAttribute_onCopy(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    caretColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAttribute_caretColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    selectedBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._TextAttribute_selectedBackgroundColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    ellipsisModeAttribute(value: EllipsisMode): void {
        ArkUIGeneratedNativeModule._TextAttribute_ellipsisMode(this.peer.ptr, value)
    }
    enableDataDetectorAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_enableDataDetector(this.peer.ptr, +value)
    }
    dataDetectorConfigAttribute(value: TextDataDetectorConfig): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeTextDataDetectorConfig(value)
        ArkUIGeneratedNativeModule._TextAttribute_dataDetectorConfig(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onTextSelectionChangeAttribute(value: ((first: number, last: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._TextAttribute_onTextSelectionChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fontFeatureAttribute(value: string): void {
        ArkUIGeneratedNativeModule._TextAttribute_fontFeature(this.peer.ptr, value)
    }
    privacySensitiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_privacySensitive(this.peer.ptr, +value)
    }
    textSelectableAttribute(value: TextSelectableMode): void {
        ArkUIGeneratedNativeModule._TextAttribute_textSelectable(this.peer.ptr, value)
    }
    editMenuOptionsAttribute(value: EditMenuOptions): void {
        ArkUIGeneratedNativeModule._TextAttribute_editMenuOptions(this.peer.ptr, toPeerPtr(value))
    }
    halfLeadingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_halfLeading(this.peer.ptr, +value)
    }
    enableHapticFeedbackAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._TextAttribute_enableHapticFeedback(this.peer.ptr, +value)
    }
    selectionAttribute(selectionStart: number, selectionEnd: number): void {
        ArkUIGeneratedNativeModule._TextAttribute_selection(this.peer.ptr, selectionStart, selectionEnd)
    }
    bindSelectionMenuAttribute(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeSelectionMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_bindSelectionMenu(this.peer.ptr, spanType, thisSerializer.asArray(), thisSerializer.length(), responseType)
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
    onTextSelectionChange?: ((first: number, last: number) => void)
    fontFeature?: string
    privacySensitive?: boolean
    textSelectable?: TextSelectableMode
    editMenuOptions?: EditMenuOptions
    halfLeading?: boolean
    enableHapticFeedback?: boolean
}
