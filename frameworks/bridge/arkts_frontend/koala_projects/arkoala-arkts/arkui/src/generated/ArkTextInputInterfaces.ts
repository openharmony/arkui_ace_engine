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
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor, ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font } from "./ArkUnitsInterfaces"
import { TextInputController } from "./ArkTextInputControllerMaterialized"
import { Resource } from "./ArkResourceInterfaces"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
import { PasteEvent, KeyboardOptions } from "./ArkRichEditorInterfaces"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions, InputCounterOptions } from "./ArkCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, TextOverflow, FontStyle, FontWeight, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean_Void, Callback_String_Void, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_ResourceStr_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { ContentType } from "./ArkTextAreaInterfaces"
import { EditableTextOnChangeCallback, CaretStyle, InsertValue, DeleteValue } from "./ArkTextCommonInterfaces"
import { CancelButtonOptions, CancelButtonSymbolOptions } from "./ArkSearchInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
export enum InputType {
    NORMAL = 0,
    Normal = 0,
    NUMBER = 1,
    Number = 1,
    PHONE_NUMBER = 2,
    PhoneNumber = 2,
    EMAIL = 3,
    Email = 3,
    PASSWORD = 4,
    Password = 4,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum EnterKeyType {
    GO = 2,
    Go = 2,
    SEARCH = 3,
    Search = 3,
    SEND = 4,
    Send = 4,
    NEXT = 5,
    Next = 5,
    DONE = 6,
    Done = 6,
    PREVIOUS = 7,
    NEW_LINE = 8
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
    DEFAULT = 0,
    Default = 0,
    INLINE = 1,
    Inline = 1
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
