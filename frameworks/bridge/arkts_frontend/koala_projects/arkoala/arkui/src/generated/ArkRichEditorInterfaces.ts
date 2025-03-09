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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor, Length, ResourceStr, Dimension, Margin, BorderRadiuses, Area, Position, Font, SizeOptions, Padding, ConstraintSizeOptions, ChainWeightOptions, LocalizedPadding, LocalizedMargin, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Bias } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit, HitTestMode, ImageSize, Alignment, BorderStyle, HoverEffect, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, CopyOptions, BarState } from "./ArkEnumsInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { ShadowOptions, ShadowType, EventTarget, SourceType, SourceTool, SelectionOptions, CustomBuilder, MenuPolicy, DrawContext, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, DragItemInfo, MotionPathOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, RectResult, TouchTestStrategy, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./ArkSymbolglyphInterfaces"
import { DecorationStyleResult, TextRange, PreviewText, PositionWithAffinity, LineMetrics, TextBox, Affinity, StyledStringChangedListener, OnDidChangeCallback, StyledStringChangeValue, MenuType, TextDataDetectorConfig, TextDataDetectorType, TextMenuItem } from "./ArkTextCommonInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { FingerInfo, GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority } from "./ArkGestureInterfaces"
import { RichEditorController } from "./ArkRichEditorControllerMaterialized"
import { RichEditorBaseController } from "./ArkRichEditorBaseControllerMaterialized"
import { TextEditControllerEx } from "./ArkTextEditControllerExMaterialized"
import { TextBaseController } from "./ArkTextBaseControllerMaterialized"
import { LayoutManager } from "./ArkLayoutManagerMaterialized"
import { StyledString } from "./ArkStyledStringMaterialized"
import { RectWidthStyle, RectHeightStyle, LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { ImageAttachment } from "./ArkImageAttachmentMaterialized"
import { CustomSpan } from "./ArkCustomSpanMaterialized"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { RichEditorStyledStringController } from "./ArkRichEditorStyledStringControllerMaterialized"
import { StyledStringController } from "./ArkStyledStringControllerMaterialized"
import { MutableStyledString } from "./ArkMutableStyledStringMaterialized"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { EnterKeyType } from "./ArkTextInputInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
export enum RichEditorDeleteDirection {
    BACKWARD,
    FORWARD = 1,
}
export enum RichEditorSpanType {
    TEXT,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
}
export enum RichEditorResponseType {
    RIGHT_CLICK,
    LONG_PRESS = 1,
    SELECT = 2,
}
export interface RichEditorSpanPosition {
    spanIndex: number;
    spanRange: [ number, number ];
}
export interface RichEditorTextStyle {
    fontColor?: ResourceColor;
    fontSize?: Length | number;
    fontStyle?: FontStyle;
    fontWeight?: number | FontWeight | string;
    fontFamily?: ResourceStr;
    decoration?: DecorationStyleInterface;
    textShadow?: ShadowOptions | Array<ShadowOptions>;
    letterSpacing?: number | string;
    lineHeight?: number | string | Resource;
    fontFeature?: string;
}
export interface LeadingMarginPlaceholder {
    pixelMap: PixelMap;
    size: [ Dimension, Dimension ];
}
export interface RichEditorParagraphStyle {
    textAlign?: TextAlign;
    leadingMargin?: Dimension | LeadingMarginPlaceholder;
    wordBreak?: WordBreak;
    lineBreakStrategy?: LineBreakStrategy;
}
export interface PasteEvent {
    preventDefault?: (() => void);
}
export interface RichEditorTextSpan {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle?: RichEditorTextStyle;
}
export interface RichEditorLayoutStyle {
    margin?: Dimension | Margin;
    borderRadius?: Dimension | BorderRadiuses;
}
export interface RichEditorImageSpanStyle {
    size?: [ Dimension, Dimension ];
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorSymbolSpanStyle {
    fontSize?: number | string | Resource;
    fontColor?: Array<ResourceColor>;
    fontWeight?: number | FontWeight | string;
    effectStrategy?: SymbolEffectStrategy;
    renderingStrategy?: SymbolRenderingStrategy;
}
export interface RichEditorTextStyleResult {
    fontColor: ResourceColor;
    fontSize: number;
    fontStyle: FontStyle;
    fontWeight: number;
    fontFamily: string;
    decoration: DecorationStyleResult;
    textShadow?: Array<ShadowOptions>;
    letterSpacing?: number;
    lineHeight?: number;
    fontFeature?: string;
}
export interface RichEditorParagraphResult {
    style: RichEditorParagraphStyle;
    range: [ number, number ];
}
export interface RichEditorSymbolSpanStyleResult {
    fontSize: number | string | Resource;
    fontColor: Array<ResourceColor>;
    fontWeight: number | FontWeight | string;
    effectStrategy: SymbolEffectStrategy;
    renderingStrategy: SymbolRenderingStrategy;
}
export interface RichEditorTextSpanResult {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle: RichEditorTextStyleResult;
    offsetInSpan: [ number, number ];
    symbolSpanStyle?: RichEditorSymbolSpanStyle;
    valueResource?: Resource;
    paragraphStyle?: RichEditorParagraphStyle;
    previewText?: string;
}
export interface RichEditorImageSpanStyleResult {
    size: [ number, number ];
    verticalAlign: ImageSpanAlignment;
    objectFit: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorImageSpanResult {
    spanPosition: RichEditorSpanPosition;
    valuePixelMap?: PixelMap;
    valueResourceStr?: ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ number, number ];
}
export interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: PixelMap | ResourceStr;
    imageStyle?: RichEditorImageSpanStyle;
}
export interface RichEditorRange {
    start?: number;
    end?: number;
}
export interface RichEditorGesture {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
}
export interface RichEditorTextSpanOptions {
    offset?: number;
    style?: RichEditorTextStyle;
    paragraphStyle?: RichEditorParagraphStyle;
    gesture?: RichEditorGesture;
}
export interface KeyboardOptions {
    supportAvoidance?: boolean;
}
export interface RichEditorImageSpanOptions {
    offset?: number;
    imageStyle?: RichEditorImageSpanStyle;
    gesture?: RichEditorGesture;
}
export interface RichEditorBuilderSpanOptions {
    offset?: number;
}
export interface PlaceholderStyle {
    font?: Font;
    fontColor?: ResourceColor;
}
export interface RichEditorSpanStyleOptions extends RichEditorRange {
}
export interface RichEditorParagraphStyleOptions extends RichEditorRange {
    style: RichEditorParagraphStyle;
}
export interface RichEditorUpdateTextSpanStyleOptions extends RichEditorSpanStyleOptions {
    textStyle: RichEditorTextStyle;
}
export interface RichEditorUpdateImageSpanStyleOptions extends RichEditorSpanStyleOptions {
    imageStyle: RichEditorImageSpanStyle;
}
export interface RichEditorUpdateSymbolSpanStyleOptions extends RichEditorSpanStyleOptions {
    symbolStyle: RichEditorSymbolSpanStyle;
}
export interface RichEditorSymbolSpanOptions {
    offset?: number;
    style?: RichEditorSymbolSpanStyle;
}
export interface RichEditorSelection {
    selection: [ number, number ];
    spans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorInsertValue {
    insertOffset: number;
    insertValue: string;
    previewText?: string;
}
export interface RichEditorDeleteValue {
    offset: number;
    direction: RichEditorDeleteDirection;
    length: number;
    richEditorDeleteSpans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorChangeValue {
    rangeBefore: TextRange;
    replacedSpans: Array<RichEditorTextSpanResult>;
    replacedImageSpans: Array<RichEditorImageSpanResult>;
    replacedSymbolSpans: Array<RichEditorTextSpanResult>;
}
export interface RichEditorOptions {
    controller: RichEditorController;
}
export interface RichEditorStyledStringOptions {
    controller: RichEditorStyledStringController;
}
export interface SelectionMenuOptions {
    onAppear?: MenuOnAppearCallback;
    onDisappear?: (() => void);
    menuType?: MenuType;
}
export type RichEditorSpan = RichEditorImageSpanResult | RichEditorTextSpanResult;
export interface RichEditorAttribute extends CommonMethod<RichEditorAttribute> {
    onReady: (() => void);
    onSelect: ((parameter: RichEditorSelection) => void);
    onSelectionChange: ((parameter: RichEditorRange) => void);
    aboutToIMEInput: ((parameter: RichEditorInsertValue) => boolean);
    onIMEInputComplete: ((parameter: RichEditorTextSpanResult) => void);
    onDidIMEInput: ((parameter: TextRange) => void);
    aboutToDelete: ((parameter: RichEditorDeleteValue) => boolean);
    onDeleteComplete: (() => void);
    copyOptions: CopyOptions;
    onPaste: PasteEventCallback;
    enableDataDetector: boolean;
    enablePreviewText: boolean;
    dataDetectorConfig: TextDataDetectorConfig;
    caretColor: ResourceColor;
    selectedBackgroundColor: ResourceColor;
    onEditingChange: ((parameter: boolean) => void);
    enterKeyType: EnterKeyType;
    onSubmit: SubmitCallback;
    onWillChange: ((parameter: RichEditorChangeValue) => boolean);
    onDidChange: OnDidChangeCallback;
    onCut: ((parameter: CutEvent) => void);
    onCopy: ((parameter: CopyEvent) => void);
    editMenuOptions: EditMenuOptions;
    enableKeyboardOnFocus: boolean;
    enableHapticFeedback: boolean;
    barState: BarState;
}
export interface CutEvent {
    preventDefault?: (() => void);
}
export interface CopyEvent {
    preventDefault?: (() => void);
}
export type SubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type MenuOnAppearCallback = (start: number, end: number) => void;
export type PasteEventCallback = (event?: PasteEvent) => void;
export interface RichEditorInterface {
    invoke(value: RichEditorOptions): RichEditorAttribute;

}
