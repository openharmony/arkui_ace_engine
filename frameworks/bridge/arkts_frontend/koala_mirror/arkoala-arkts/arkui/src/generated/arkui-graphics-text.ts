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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { common2D } from "./ohos.graphics.common2D"
import { FontMetrics } from "./arkui-drawing"
import { Rect } from "./arkui-graphics"
import { FontWeight } from "./enums"
export enum Affinity {
    UPSTREAM = 0,
    DOWNSTREAM = 1
}
export enum TextDecorationType {
    NONE = 0,
    UNDERLINE = 1,
    OVERLINE = 2,
    LINE_THROUGH = 3
}
export enum TextDecorationStyle {
    SOLID = 0,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4
}
export enum FontStyle {
    NORMAL = 0,
    ITALIC = 1,
    OBLIQUE = 2
}
export enum FontWidth {
    ULTRA_CONDENSED = 1,
    EXTRA_CONDENSED = 2,
    CONDENSED = 3,
    SEMI_CONDENSED = 4,
    NORMAL = 5,
    SEMI_EXPANDED = 6,
    EXPANDED = 7,
    EXTRA_EXPANDED = 8,
    ULTRA_EXPANDED = 9
}
export enum TextBaseline {
    ALPHABETIC = 0,
    IDEOGRAPHIC = 1
}
export enum EllipsisMode {
    START = 0,
    MIDDLE = 1,
    END = 2
}
export interface Decoration {
    textDecoration?: TextDecorationType;
    color?: common2D.Color;
    decorationStyle?: TextDecorationStyle;
    decorationThicknessScale?: number;
}
export interface FontFeature {
    name: string;
    value: number;
}
export interface TextShadow {
    color?: common2D.Color;
    point?: common2D.Point;
    blurRadius?: number;
}
export interface RectStyle {
    color: common2D.Color;
    leftTopRadius: number;
    rightTopRadius: number;
    rightBottomRadius: number;
    leftBottomRadius: number;
}
export interface FontVariation {
    axis: string;
    value: number;
}
export interface RunMetrics {
    textStyle: text.TextStyle;
    fontMetrics: FontMetrics;
}
export interface LineMetrics {
    startIndex: number;
    endIndex: number;
    ascent: number;
    descent: number;
    height: number;
    width: number;
    left: number;
    baseline: number;
    lineNumber: number;
    topHeight: number;
    runMetrics: Map<number, RunMetrics>;
}
export enum TextDirection {
    RTL = 0,
    LTR = 1
}
export interface TextBox {
    rect: Rect;
    direction: TextDirection;
}
export namespace text {
    export interface TextStyle {
        decoration?: Decoration;
        color?: common2D.Color;
        fontWeight?: FontWeight;
        fontStyle?: FontStyle;
        baseline?: TextBaseline;
        fontFamilies?: Array<string>;
        fontSize?: number;
        letterSpacing?: number;
        wordSpacing?: number;
        heightScale?: number;
        halfLeading?: boolean;
        heightOnly?: boolean;
        ellipsis?: string;
        ellipsisMode?: EllipsisMode;
        locale?: string;
        baselineShift?: number;
        fontFeatures?: Array<FontFeature>;
        textShadows?: Array<TextShadow>;
        backgroundRect?: RectStyle;
        fontVariations?: Array<FontVariation>;
    }
}
