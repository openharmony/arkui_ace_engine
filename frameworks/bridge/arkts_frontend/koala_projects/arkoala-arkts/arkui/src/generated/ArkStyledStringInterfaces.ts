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
import { ResourceColor, ResourceStr, SizeOptions, Margin, Padding, BorderRadiuses } from "./ArkUnitsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { FontWeight, FontStyle, TextDecorationType, TextDecorationStyle, TextAlign, TextOverflow, WordBreak, ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { Callback_ClickEvent_Void, Callback_GestureEvent_Void } from "./SyntheticDeclarations"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { LeadingMarginPlaceholder } from "./ArkRichEditorInterfaces"
import { TextStyle_styled_string } from "./ArkTextStyleStyledStringMaterialized"
import { DecorationStyle } from "./ArkDecorationStyleMaterialized"
import { BaselineOffsetStyle } from "./ArkBaselineOffsetStyleMaterialized"
import { LetterSpacingStyle } from "./ArkLetterSpacingStyleMaterialized"
import { TextShadowStyle } from "./ArkTextShadowStyleMaterialized"
import { GestureStyle } from "./ArkGestureStyleMaterialized"
import { ImageAttachment } from "./ArkImageAttachmentMaterialized"
import { ParagraphStyle } from "./ArkParagraphStyleMaterialized"
import { LineHeightStyle } from "./ArkLineHeightStyleMaterialized"
import { UrlStyle } from "./ArkUrlStyleMaterialized"
import { CustomSpan } from "./ArkCustomSpanMaterialized"
import { BackgroundColorStyle } from "./ArkBackgroundColorStyleMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
export interface StyleOptions {
    start?: number;
    length?: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface SpanStyle {
    start: number;
    length: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
export interface TextStyleInterface {
    fontColor?: ResourceColor;
    fontFamily?: ResourceStr;
    fontSize?: LengthMetrics;
    fontWeight?: number | FontWeight | string;
    fontStyle?: FontStyle;
}
export interface DecorationStyleInterface {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
export interface GestureStyleInterface {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
}
export interface ParagraphStyleInterface {
    textAlign?: TextAlign;
    textIndent?: LengthMetrics;
    maxLines?: number;
    overflow?: TextOverflow;
    wordBreak?: WordBreak;
    leadingMargin?: LengthMetrics | LeadingMarginPlaceholder;
}
export type StyledStringValue = TextStyle_styled_string | DecorationStyle | BaselineOffsetStyle | LetterSpacingStyle | TextShadowStyle | GestureStyle | ImageAttachment | ParagraphStyle | LineHeightStyle | UrlStyle | CustomSpan | UserDataSpan | BackgroundColorStyle;
export enum StyledStringKey {
    FONT = 0,
    DECORATION = 1,
    BASELINE_OFFSET = 2,
    LETTER_SPACING = 3,
    TEXT_SHADOW = 4,
    LINE_HEIGHT = 5,
    BACKGROUND_COLOR = 6,
    URL = 7,
    GESTURE = 100,
    PARAGRAPH_STYLE = 200,
    IMAGE = 300,
    CUSTOM_SPAN = 400,
    USER_DATA = 500
}
export interface ImageAttachmentInterface {
    value: PixelMap;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
}
export interface ImageAttachmentLayoutStyle {
    margin?: LengthMetrics | Margin;
    padding?: LengthMetrics | Padding;
    borderRadius?: LengthMetrics | BorderRadiuses;
}
export interface CustomSpanMetrics {
    width: number;
    height?: number;
}
export interface CustomSpanDrawInfo {
    x: number;
    lineTop: number;
    lineBottom: number;
    baseline: number;
}
export interface CustomSpanMeasureInfo {
    fontSize: number;
}
export interface UserDataSpan {
}
