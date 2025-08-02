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
import { Resource } from "./ArkResourceInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { BorderStyle, Color, FontWeight, FontStyle } from "./ArkEnumsInterfaces"
import { OutlineStyle } from "./ArkCommonInterfaces"
export type Length = string | number | Resource;
export type PX = string;
export type VP = string | number;
export type FP = string;
export type LPX = string;
export type Percentage = string;
export type Degree = string;
export type Dimension = PX | VP | FP | LPX | Percentage | Resource;
export type ResourceStr = string | Resource;
export interface Padding {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
export interface LocalizedPadding {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
export type Margin = Padding;
export type EdgeWidth = EdgeWidths;
export interface EdgeWidths {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
export interface LocalizedEdgeWidths {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
export interface EdgeOutlineWidths {
    top?: Dimension;
    right?: Dimension;
    bottom?: Dimension;
    left?: Dimension;
}
export interface BorderRadiuses {
    topLeft?: Length;
    topRight?: Length;
    bottomLeft?: Length;
    bottomRight?: Length;
}
export interface LocalizedBorderRadiuses {
    topStart?: LengthMetrics;
    topEnd?: LengthMetrics;
    bottomStart?: LengthMetrics;
    bottomEnd?: LengthMetrics;
}
export interface OutlineRadiuses {
    topLeft?: Dimension;
    topRight?: Dimension;
    bottomLeft?: Dimension;
    bottomRight?: Dimension;
}
export interface EdgeColors {
    top?: ResourceColor;
    right?: ResourceColor;
    bottom?: ResourceColor;
    left?: ResourceColor;
}
export interface LocalizedEdgeColors {
    top?: ResourceColor;
    end?: ResourceColor;
    bottom?: ResourceColor;
    start?: ResourceColor;
}
export type LocalizedMargin = LocalizedPadding;
export interface EdgeStyles {
    top?: BorderStyle;
    right?: BorderStyle;
    bottom?: BorderStyle;
    left?: BorderStyle;
}
export interface EdgeOutlineStyles {
    top?: OutlineStyle;
    right?: OutlineStyle;
    bottom?: OutlineStyle;
    left?: OutlineStyle;
}
export interface Offset {
    dx: Length;
    dy: Length;
}
export type ResourceColor = Color | number | string | Resource;
export interface LengthConstrain {
    minLength: Length;
    maxLength: Length;
}
export type VoidCallback = () => void;
export interface LengthMetricsUnit {
    _LengthMetricsUnitStub: string;
}
export interface Font {
    size?: Length;
    weight?: FontWeight | number | string;
    family?: string | Resource;
    style?: FontStyle;
}
export interface Area {
    width: Length;
    height: Length;
    position: Position;
    globalPosition: Position;
}
export interface Position {
    x?: Length;
    y?: Length;
}
export interface LocalizedPosition {
    start?: LengthMetrics;
    top?: LengthMetrics;
}
export interface Edges {
    top?: Dimension;
    left?: Dimension;
    bottom?: Dimension;
    right?: Dimension;
}
export interface LocalizedEdges {
    top?: LengthMetrics;
    start?: LengthMetrics;
    bottom?: LengthMetrics;
    end?: LengthMetrics;
}
export interface Bias {
    horizontal?: number;
    vertical?: number;
}
export interface ConstraintSizeOptions {
    minWidth?: Length;
    maxWidth?: Length;
    minHeight?: Length;
    maxHeight?: Length;
}
export interface SizeOptions {
    width?: Length;
    height?: Length;
}
export interface BorderOptions {
    width?: EdgeWidths | Length | LocalizedEdgeWidths;
    color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
    radius?: BorderRadiuses | Length | LocalizedBorderRadiuses;
    style?: EdgeStyles | BorderStyle;
    dashGap?: EdgeWidths | LengthMetrics | LocalizedEdgeWidths;
    dashWidth?: EdgeWidths | LengthMetrics | LocalizedEdgeWidths;
}
export interface OutlineOptions {
    width?: EdgeOutlineWidths | Dimension;
    color?: EdgeColors | ResourceColor | LocalizedEdgeColors;
    radius?: OutlineRadiuses | Dimension;
    style?: EdgeOutlineStyles | OutlineStyle;
}
export interface MarkStyle {
    strokeColor?: ResourceColor;
    size?: Length;
    strokeWidth?: Length;
}
export interface TouchPoint {
    x: Dimension;
    y: Dimension;
}
export interface DirectionalEdgesT {
    start: number;
    end: number;
    top: number;
    bottom: number;
}
export interface DividerStyleOptions {
    strokeWidth?: LengthMetrics;
    color?: ResourceColor;
    startMargin?: LengthMetrics;
    endMargin?: LengthMetrics;
}
export interface ChainWeightOptions {
    horizontal?: number;
    vertical?: number;
}
export interface AccessibilityOptions {
    accessibilityPreferred?: boolean;
}
