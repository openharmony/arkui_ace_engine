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
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font } from "./ArkUnitsInterfaces"
import { TextAreaController } from "./ArkTextAreaControllerMaterialized"
import { EnterKeyType } from "./ArkTextInputInterfaces"
import { SubmitEvent } from "./ArkSubmitEventMaterialized"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions, InputCounterOptions } from "./ArkCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_EnterKeyType_Void, Callback_Number_Number_Void, Callback_Boolean_Void, Callback_String_Void, Callback_String_PasteEvent_Void, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void, Callback_ResourceStr_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
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
import { CaretStyle, EditableTextOnChangeCallback, InsertValue, DeleteValue } from "./ArkTextCommonInterfaces"
import { PasteEvent, KeyboardOptions } from "./ArkRichEditorInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
export interface TextAreaOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextAreaController;
}
export type TextAreaInterface = (value?: TextAreaOptions) => TextAreaAttribute;
export enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum ContentType {
    USER_NAME = 0,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25
}
export type TextAreaSubmitCallback = (enterKeyType: EnterKeyType, event?: SubmitEvent) => void;
export interface TextAreaAttribute extends CommonMethod<TextAreaAttribute> {
    placeholderColor: ResourceColor;
    placeholderFont: Font;
    enterKeyType: EnterKeyType;
    textAlign: TextAlign;
    caretColor: ResourceColor;
    fontColor: ResourceColor;
    fontSize: Length;
    fontStyle: FontStyle;
    fontWeight: number | FontWeight | string;
    fontFamily: ResourceStr;
    textOverflow: TextOverflow;
    textIndent: Dimension;
    caretStyle: CaretStyle;
    selectedBackgroundColor: ResourceColor;
    onSubmit: ((enterKey: EnterKeyType) => void);

    onChange: EditableTextOnChangeCallback;
    onTextSelectionChange: ((first: number,last: number) => void);
    onContentScroll: ((first: number,last: number) => void);
    onEditChange: ((parameter: boolean) => void);
    onCopy: ((breakpoints: string) => void);
    onCut: ((breakpoints: string) => void);
    onPaste: ((value: string,event: PasteEvent) => void);
    copyOption: CopyOptions;
    enableKeyboardOnFocus: boolean;
    maxLength: number;
    style: TextContentStyle;
    barState: BarState;
    selectionMenuHidden: boolean;
    minFontSize: number | string | Resource;
    maxFontSize: number | string | Resource;
    heightAdaptivePolicy: TextHeightAdaptivePolicy;
    maxLines: number;
    wordBreak: WordBreak;
    lineBreakStrategy: LineBreakStrategy;
    decoration: TextDecorationOptions;
    letterSpacing: number | string | Resource;
    lineSpacing: LengthMetrics;
    lineHeight: number | string | Resource;
    type: TextAreaType;
    enableAutoFill: boolean;
    contentType: ContentType;
    fontFeature: string;
    onWillInsert: ((parameter: InsertValue) => boolean);
    onDidInsert: ((parameter: InsertValue) => void);
    onWillDelete: ((parameter: DeleteValue) => boolean);
    onDidDelete: ((parameter: DeleteValue) => void);
    editMenuOptions: EditMenuOptions;
    enablePreviewText: boolean;
    enableHapticFeedback: boolean;
}
