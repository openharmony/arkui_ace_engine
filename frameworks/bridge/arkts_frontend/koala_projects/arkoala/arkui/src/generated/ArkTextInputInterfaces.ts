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
import { ResourceColor, ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { TextInputController } from "./ArkTextInputControllerMaterialized"
import { TextContentControllerBase } from "./ArkTextContentControllerBaseMaterialized"
import { CaretOffset, RectResult, SelectionOptions, MenuPolicy, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, TextDecorationOptions, InputCounterOptions } from "./ArkCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, TextOverflow, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy, TextDecorationType, TextDecorationStyle } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./ArkGestureInterfaces"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { ContentType } from "./ArkTextAreaInterfaces"
import { EditableTextOnChangeCallback, CaretStyle, InsertValue, DeleteValue, TextMenuItem, TextRange, TextDeleteDirection } from "./ArkTextCommonInterfaces"
import { CancelButtonOptions, CancelButtonSymbolOptions, CancelButtonStyle, IconOptions } from "./ArkSearchInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { KeyboardOptions, PasteEvent } from "./ArkRichEditorInterfaces"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
export enum InputType {
    NORMAL,
    Normal = NORMAL,
    NUMBER = 1,
    Number = NUMBER,
    PHONE_NUMBER = 2,
    PhoneNumber = PHONE_NUMBER,
    EMAIL = 3,
    Email = EMAIL,
    PASSWORD = 4,
    Password = PASSWORD,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
export enum EnterKeyType {
    GO = 2,
    Go = GO,
    SEARCH = 3,
    Search = SEARCH,
    SEND = 4,
    Send = SEND,
    NEXT = 5,
    Next = NEXT,
    DONE = 6,
    Done = DONE,
    PREVIOUS = 7,
    NEW_LINE = 8,
}
export interface UnderlineColor {
    typing?: ResourceColor | undefined;
    normal?: ResourceColor | undefined;
    error?: ResourceColor | undefined;
    disable?: ResourceColor | undefined;
}
export interface TextInputOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextInputController;
}
export enum TextInputStyle {
    DEFAULT,
    Default = DEFAULT,
    INLINE = 1,
    Inline = INLINE,
}
export type TextInputInterface = (value?: TextInputOptions) => TextInputAttribute;
export interface PasswordIcon {
    onIconSrc?: string | Resource;
    offIconSrc?: string | Resource;
}
export type OnSubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type OnTextSelectionChangeCallback = (selectionStart: number, selectionEnd: number) => void;
export type OnContentScrollCallback = (totalOffsetX: number, totalOffsetY: number) => void;
export type OnPasteCallback = (content: string, event: PasteEvent) => void;
export interface TextInputAttribute extends CommonMethod<TextInputAttribute> {
    type: InputType;
    contentType: ContentType;
    placeholderColor: ResourceColor;
    textOverflow: TextOverflow;
    textIndent: Dimension;
    placeholderFont?: Font;
    enterKeyType: EnterKeyType;
    caretColor: ResourceColor;
    onEditChanged: ((parameter: boolean) => void);
    onEditChange: ((parameter: boolean) => void);
    onSubmit: OnSubmitCallback;
    onChange: EditableTextOnChangeCallback;
    onTextSelectionChange: OnTextSelectionChangeCallback;
    onContentScroll: OnContentScrollCallback;
    maxLength: number;
    fontColor: ResourceColor;
    fontSize: Length;
    fontStyle: FontStyle;
    fontWeight: number | FontWeight | string;
    fontFamily: ResourceStr;
    onCopy: ((breakpoints: string) => void);
    onCut: ((breakpoints: string) => void);
    onPaste: OnPasteCallback;
    copyOption: CopyOptions;
    showPasswordIcon: boolean;
    textAlign: TextAlign;
    style: TextInputStyle | TextContentStyle;
    caretStyle: CaretStyle;
    selectedBackgroundColor: ResourceColor;
    caretPosition: number;
    enableKeyboardOnFocus: boolean;
    passwordIcon: PasswordIcon;
    showError?: ResourceStr | undefined;
    showUnit: CustomBuilder;
    showUnderline: boolean;
    underlineColor: ResourceColor | UnderlineColor | undefined;
    selectionMenuHidden: boolean;
    barState: BarState;
    maxLines: number;
    wordBreak: WordBreak;
    lineBreakStrategy: LineBreakStrategy;
    cancelButton: CancelButtonOptions;

    selectAll: boolean;
    minFontSize: number | string | Resource;
    maxFontSize: number | string | Resource;
    heightAdaptivePolicy: TextHeightAdaptivePolicy;
    enableAutoFill: boolean;
    decoration: TextDecorationOptions;
    letterSpacing: number | string | Resource;
    lineHeight: number | string | Resource;
    passwordRules: string;
    fontFeature: string;
    showPassword: boolean;
    onSecurityStateChange: ((parameter: boolean) => void);
    onWillInsert: ((parameter: InsertValue) => boolean);
    onDidInsert: ((parameter: InsertValue) => void);
    onWillDelete: ((parameter: DeleteValue) => boolean);
    onDidDelete: ((parameter: DeleteValue) => void);
    editMenuOptions: EditMenuOptions;
    enablePreviewText: boolean;
    enableHapticFeedback: boolean;
}
