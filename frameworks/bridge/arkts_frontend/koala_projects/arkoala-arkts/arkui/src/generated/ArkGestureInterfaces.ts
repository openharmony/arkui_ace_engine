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
import { GestureControl } from "./ArkGestureControlNamespace"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { SourceTool } from "./ArkCommonInterfaces"
import { Callback_GestureEvent_Void, Callback_Void } from "./SyntheticDeclarations"
import { GestureEvent } from "./ArkGestureEventMaterialized"
export enum PanDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    LEFT = 2,
    Left = 2,
    RIGHT = 3,
    Right = 3,
    VERTICAL = 4,
    Vertical = 4,
    UP = 5,
    Up = 5,
    DOWN = 6,
    Down = 6,
    ALL = 7,
    All = 7
}
export enum SwipeDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    VERTICAL = 2,
    Vertical = 2,
    ALL = 3,
    All = 3
}
export enum GestureMode {
    SEQUENCE = 0,
    Sequence = 0,
    PARALLEL = 1,
    Parallel = 1,
    EXCLUSIVE = 2,
    Exclusive = 2
}
export enum GestureMask {
    NORMAL = 0,
    Normal = 0,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = 1
}
export enum GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1
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
    NORMAL = 0,
    PRIORITY = 1
}
export enum GestureRecognizerState {
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5
}
