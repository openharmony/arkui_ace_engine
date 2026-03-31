/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
declare enum PanDirection {
    None,
    Horizontal,
    Left,
    Right,
    Vertical,
    Up,
    Down,
    All
}
declare enum SwipeDirection {
    None,
    Horizontal,
    Vertical,
    All
}
declare enum GestureMode {
    Sequence,
    Parallel,
    Exclusive
}
declare enum GestureMask {
    Normal,
    IgnoreInternal
}
declare enum GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1
}
declare namespace GestureControl {
    enum GestureType {
        TAP_GESTURE = 0,
        LONG_PRESS_GESTURE = 1,
        PAN_GESTURE = 2,
        PINCH_GESTURE = 3,
        SWIPE_GESTURE = 4,
        ROTATION_GESTURE = 5,
        DRAG = 6,
        CLICK = 7,
        BOX_SELECT_GESTURE = 8,
        WEB_SCROLL_GESTURE = 9,
        TEXT_FIELD_SELECT_GESTURE = 10,
        CONTEXT_MENU_HOVER_GESTURE = 11
    }
}
declare interface GestureInfo {
    tag?: string;
    type: GestureControl.GestureType;
    isSystemGesture: boolean;
}
declare interface EventLocationInfo {
    x: number;
    y: number;
    windowX: number;
    windowY: number;
    displayX: number;
    displayY: number;
    globalDisplayX?: number;
    globalDisplayY?: number;
}
interface FingerInfo {
    id: number;
    globalDisplayX?: number;
    globalDisplayY?: number;
    globalX: number;
    globalY: number;
    localX: number;
    localY: number;
    displayX: number;
    displayY: number;
    hand?: InteractionHand;
}
declare type GestureType = TapGestureInterface | LongPressGestureInterface | PanGestureInterface | PinchGestureInterface | SwipeGestureInterface | RotationGestureInterface | GestureGroupInterface;
interface BaseGestureEvent extends BaseEvent {
    fingerList: FingerInfo[];
    fingerInfos?: FingerInfo[];
}
interface GestureEvent extends BaseEvent {
    repeat: boolean;
    fingerList: FingerInfo[];
    fingerInfos?: FingerInfo[];
    offsetX: number;
    offsetY: number;
    angle: number;
    speed: number;
    scale: number;
    pinchCenterX: number;
    pinchCenterY: number;
    velocityX: number;
    velocityY: number;
    velocity: number;
    tapLocation?: EventLocationInfo;
}
interface GestureInterface<T> {
    tag(tag: string): T;
    allowedTypes(types: Array<SourceTool>): T;
}
interface BaseHandlerOptions {
    isFingerCountLimited?: boolean;
}
declare interface TapGestureParameters extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
interface TapGestureInterface extends GestureInterface<TapGestureInterface> {
    (value?: TapGestureParameters): TapGestureInterface;
    onAction(event: (event: GestureEvent) => void): TapGestureInterface;
}
interface LongPressGestureInterface extends GestureInterface<LongPressGestureInterface> {
    (value?: {
        fingers?: number;
        repeat?: boolean;
        duration?: number;
    }): LongPressGestureInterface;
    (options?: LongPressGestureHandlerOptions): LongPressGestureInterface;
    onAction(event: (event: GestureEvent) => void): LongPressGestureInterface;
    onActionEnd(event: (event: GestureEvent) => void): LongPressGestureInterface;
    onActionCancel(event: () => void): LongPressGestureInterface;
    onActionCancel(event: Callback<GestureEvent>): LongPressGestureInterface;
}
declare class PanGestureOptions {
    constructor(value?: {
        fingers?: number;
        direction?: PanDirection;
        distance?: number;
    });
}
interface PanGestureInterface extends GestureInterface<PanGestureInterface> {
    (value?: {
        fingers?: number;
        direction?: PanDirection;
        distance?: number;
    } | PanGestureOptions): PanGestureInterface;
    (options?: PanGestureHandlerOptions): PanGestureInterface;
    onActionStart(event: (event: GestureEvent) => void): PanGestureInterface;
    onActionUpdate(event: (event: GestureEvent) => void): PanGestureInterface;
    onActionEnd(event: (event: GestureEvent) => void): PanGestureInterface;
    onActionCancel(event: () => void): PanGestureInterface;
    onActionCancel(event: Callback<GestureEvent>): PanGestureInterface;
}
interface SwipeGestureInterface extends GestureInterface<SwipeGestureInterface> {
    (value?: {
        fingers?: number;
        direction?: SwipeDirection;
        speed?: number;
    }): SwipeGestureInterface;
    (options?: SwipeGestureHandlerOptions): SwipeGestureInterface;
    onAction(event: (event: GestureEvent) => void): SwipeGestureInterface;
}
interface PinchGestureInterface extends GestureInterface<PinchGestureInterface> {
    (value?: {
        fingers?: number;
        distance?: number;
    }): PinchGestureInterface;
    (options?: PinchGestureHandlerOptions): PinchGestureInterface;
    onActionStart(event: (event: GestureEvent) => void): PinchGestureInterface;
    onActionUpdate(event: (event: GestureEvent) => void): PinchGestureInterface;
    onActionEnd(event: (event: GestureEvent) => void): PinchGestureInterface;
    onActionCancel(event: () => void): PinchGestureInterface;
    onActionCancel(event: Callback<GestureEvent>): PinchGestureInterface;
}
interface RotationGestureInterface extends GestureInterface<RotationGestureInterface> {
    (value?: {
        fingers?: number;
        angle?: number;
    }): RotationGestureInterface;
    (options?: RotationGestureHandlerOptions): RotationGestureInterface;
    onActionStart(event: (event: GestureEvent) => void): RotationGestureInterface;
    onActionUpdate(event: (event: GestureEvent) => void): RotationGestureInterface;
    onActionEnd(event: (event: GestureEvent) => void): RotationGestureInterface;
    onActionCancel(event: () => void): RotationGestureInterface;
    onActionCancel(event: Callback<GestureEvent>): RotationGestureInterface;
}
interface GestureGroupInterface {
    (mode: GestureMode, ...gesture: GestureType[]): GestureGroupInterface;
    onCancel(event: () => void): GestureGroupInterface;
}
declare const TapGesture: TapGestureInterface;
declare const LongPressGesture: LongPressGestureInterface;
declare const PanGesture: PanGestureInterface;
declare const SwipeGesture: SwipeGestureInterface;
declare const PinchGesture: PinchGestureInterface;
declare const RotationGesture: RotationGestureInterface;
declare const GestureGroup: GestureGroupInterface;
declare class GestureHandler<T> implements GestureInterface<T> {
}
interface TapGestureHandlerOptions extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
declare class TapGestureHandler extends GestureHandler<TapGestureHandler> {
    constructor(options?: TapGestureHandlerOptions);
}
interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
    allowableMovement?: number;
}
declare class LongPressGestureHandler extends GestureHandler<LongPressGestureHandler> {
    constructor(options?: LongPressGestureHandlerOptions);
}
interface PanGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
    distanceMap?: Map<SourceTool, number>;
}
declare class PanGestureHandler extends GestureHandler<PanGestureHandler> {
    constructor(options?: PanGestureHandlerOptions);
}
interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
declare class SwipeGestureHandler extends GestureHandler<SwipeGestureHandler> {
    constructor(options?: SwipeGestureHandlerOptions);
}
interface PinchGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    distance?: number;
}
declare class PinchGestureHandler extends GestureHandler<PinchGestureHandler> {
    constructor(options?: PinchGestureHandlerOptions);
}
interface RotationGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    angle?: number;
}
declare class RotationGestureHandler extends GestureHandler<RotationGestureHandler> {
    constructor(options?: RotationGestureHandlerOptions);
}
interface GestureGroupGestureHandlerOptions {
    mode: GestureMode;
    gestures: GestureHandler<TapGestureHandler | LongPressGestureHandler | PanGestureHandler | SwipeGestureHandler | PinchGestureHandler | RotationGestureHandler | GestureGroupHandler>[];
}
declare class GestureGroupHandler extends GestureHandler<GestureGroupHandler> {
    constructor(options?: GestureGroupGestureHandlerOptions);
}
declare enum GesturePriority {
    NORMAL = 0,
    PRIORITY = 1
}
declare enum GestureRecognizerState {
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5
}
declare class EventTargetInfo {
}
declare class TouchRecognizer {
}
declare class GestureRecognizer {
}
