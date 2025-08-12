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
import { GestureControl } from "./ArkGestureControlNamespace"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { SourceTool, EventTarget, SourceType } from "./ArkCommonInterfaces"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { Area, Length, Position } from "./ArkUnitsInterfaces"
export enum PanDirection {
    NONE,
    None = NONE,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
    LEFT = 2,
    Left = LEFT,
    RIGHT = 3,
    Right = RIGHT,
    VERTICAL = 4,
    Vertical = VERTICAL,
    UP = 5,
    Up = UP,
    DOWN = 6,
    Down = DOWN,
    ALL = 7,
    All = ALL,
}
export enum SwipeDirection {
    NONE,
    None = NONE,
    HORIZONTAL = 1,
    Horizontal = HORIZONTAL,
    VERTICAL = 2,
    Vertical = VERTICAL,
    ALL = 3,
    All = ALL,
}
export enum GestureMode {
    SEQUENCE,
    Sequence = SEQUENCE,
    PARALLEL = 1,
    Parallel = PARALLEL,
    EXCLUSIVE = 2,
    Exclusive = EXCLUSIVE,
}
export enum GestureMask {
    NORMAL,
    Normal = NORMAL,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = IGNORE_INTERNAL,
}
export enum GestureJudgeResult {
    CONTINUE,
    REJECT = 1,
}
export interface GestureInfo {
    tag?: string;
    type: GestureControl.GestureType;
    isSystemGesture: boolean;
}
export interface FingerInfo {
    id: number;
    globalX: number;
    globalY: number;
    localX: number;
    localY: number;
    displayX: number;
    displayY: number;
}
export type GestureType = TapGestureInterface | LongPressGestureInterface | PanGestureInterface | PinchGestureInterface | SwipeGestureInterface | RotationGestureInterface | GestureGroupInterface;
export interface GestureInterface<T> {
}
export interface TapGestureParameters {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
export interface GestureHandler<T> {
}
export interface TapGestureHandlerOptions {
    count?: number;
    fingers?: number;
}
export interface TapGestureHandler extends GestureHandler<TapGestureHandler> {
}
export interface LongPressGestureHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
export interface LongPressGestureHandler extends GestureHandler<LongPressGestureHandler> {
}
export interface PanGestureHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
export interface PanGestureHandler extends GestureHandler<PanGestureHandler> {
}
export interface SwipeGestureHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
export interface SwipeGestureHandler extends GestureHandler<SwipeGestureHandler> {
}
export interface PinchGestureHandlerOptions {
    fingers?: number;
    distance?: number;
}
export interface PinchGestureHandler extends GestureHandler<PinchGestureHandler> {
}
export interface RotationGestureHandlerOptions {
    fingers?: number;
    angle?: number;
}
export interface RotationGestureHandler extends GestureHandler<RotationGestureHandler> {
}
export interface GestureGroupGestureHandlerOptions {
    stub: string;
}
export enum GesturePriority {
    NORMAL,
    PRIORITY = 1,
}
export enum GestureRecognizerState {
    READY,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5,
}
