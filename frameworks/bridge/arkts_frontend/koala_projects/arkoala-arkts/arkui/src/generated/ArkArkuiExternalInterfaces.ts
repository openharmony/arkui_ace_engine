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
import { BusinessError } from "./ArkBaseInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FontStyle, FontWeight, TextAlign, TextOverflow, TextCase, WordBreak } from "./ArkEnumsInterfaces"
import { Dimension } from "./ArkUnitsInterfaces"
export interface NodeController {
}
export interface TextModifier {
}
export enum RectWidthStyle {
    TIGHT = 0,
    MAX = 1
}
export enum Affinity {
    UPSTREAM = 0,
    DOWNSTREAM = 1
}
export enum RectHeightStyle {
    TIGHT = 0,
    MAX = 1,
    INCLUDE_LINE_SPACE_MIDDLE = 2,
    INCLUDE_LINE_SPACE_TOP = 3,
    INCLUDE_LINE_SPACE_BOTTOM = 4,
    STRUT = 5
}
export interface Want {
    bundleName?: string;
    abilityName?: string;
    deviceId?: string;
    uri?: string;
    type?: string;
    flags?: number;
    action?: string;
    parameters?: Map<string, Object>;
    entities?: Array<string>;
    moduleName?: string;
}
export enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4
}
export interface WebHeader {
    headerKey: string;
    headerValue: string;
}
export interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
}
export enum PerfMonitorActionType {
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
}
export enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4
}
export type ErrorCallback = (err: BusinessError) => void;
export interface ShapeSize {
    width?: number | string;
    height?: number | string;
}
export interface RectShapeOptions extends ShapeSize {
    radius?: number | string | Array<number | string>;
}
export interface RoundRectShapeOptions extends ShapeSize {
    radiusWidth?: number | string;
    radiusHeight?: number | string;
}
export interface PathShapeOptions {
    commands?: string;
}
export interface FontOptions {
    familyName: string | Resource;
    familySrc: string | Resource;
}
export interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
}
export interface MeasureOptions {
    textContent: string | Resource;
    constraintWidth?: number | string | Resource;
    fontSize?: number | string | Resource;
    fontStyle?: number | FontStyle;
    fontWeight?: number | string | FontWeight;
    fontFamily?: string | Resource;
    letterSpacing?: number | string;
    textAlign?: number | TextAlign;
    overflow?: number | TextOverflow;
    maxLines?: number;
    lineHeight?: number | string | Resource;
    baselineOffset?: number | string;
    textCase?: number | TextCase;
    textIndent?: number | string;
    wordBreak?: WordBreak;
}
export enum EffectDirection {
    DOWN = 0,
    UP = 1
}
export enum EffectScope {
    LAYER = 0,
    WHOLE = 1
}
export interface TouchPoint {
    x: Dimension;
    y: Dimension;
}
