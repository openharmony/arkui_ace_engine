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
import { ResourceColor, SizeOptions, Length, Margin, Padding, BorderRadiuses, ResourceStr } from "./ArkUnitsInterfaces"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { TextDecorationType, TextDecorationStyle, ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { StyledString } from "./ArkStyledStringMaterialized"
import { ImageAttachment } from "./ArkImageAttachmentMaterialized"
import { CustomSpan } from "./ArkCustomSpanMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { DrawContext } from "./ArkCommonInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Affinity } from "./ArkArkuiExternalInterfaces"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
export enum TextDataDetectorType {
    PHONE_NUMBER,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4,
}
export interface TextDataDetectorConfig {
    types: Array<TextDataDetectorType>;
    onDetectResultUpdate?: ((breakpoints: string) => void);
    color?: ResourceColor;
    decoration?: DecorationStyleInterface;
}
export interface TextRange {
    start?: number;
    end?: number;
}
export interface InsertValue {
    insertOffset: number;
    insertValue: string;
}
export enum TextDeleteDirection {
    BACKWARD,
    FORWARD = 1,
}
export enum MenuType {
    SELECTION_MENU,
    PREVIEW_MENU = 1,
}
export interface DeleteValue {
    deleteOffset: number;
    direction: TextDeleteDirection;
    deleteValue: string;
}
export type OnDidChangeCallback = (rangeBefore: TextRange, rangeAfter: TextRange) => void;
export type EditableTextOnChangeCallback = (value: string, previewText?: PreviewText) => void;
export interface StyledStringChangedListener {
    onWillChange?: ((parameter: StyledStringChangeValue) => boolean);
    onDidChange?: OnDidChangeCallback;
}
export interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
export interface PositionWithAffinity {
    position: number;
    affinity: Affinity;
}
export interface LineMetrics {
    _LineMetricsStub: string;
}
export interface TextBox {
    _TextBoxStub: string;
}
export interface CaretStyle {
    width?: Length;
    color?: ResourceColor;
}
export interface PreviewText {
    offset: number;
    value: string;
}
export interface TextMenuItem {
    content: ResourceStr;
    icon?: ResourceStr;
    id: TextMenuItemId;
}
export interface DecorationStyleResult {
    type: TextDecorationType;
    color: ResourceColor;
    style?: TextDecorationStyle;
}
export interface FontSettingOptions {
    enableVariableFontWeight?: boolean;
}
