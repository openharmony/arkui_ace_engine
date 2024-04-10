/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />
enum CommonGestureType {
    TAP_GESTURE = 0,
    LONG_PRESS_GESTURE,
    PAN_GESTURE,
    SWIPE_GESTURE,
    PINCH_GESTURE,
    ROTATION_GESTURE,
    GESTURE_GROUP,
}

class GestureHandler {
    gestureType: CommonGestureType;

    constructor(gestureType: CommonGestureType) {
        this.gestureType = gestureType;
    }
}

class TapGestureHandler extends GestureHandler {
    fingers?: number;
    count?: number;
    gestureTag?: string;
    onActionCallback?: Callback<GestureEvent>;

    constructor(options?: TapGestureHandlerOptions) {
        super(CommonGestureType.TAP_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.count = options.count;
        }
    }
    onAction(event: Callback<GestureEvent>) {
        this.onActionCallback = event;
        return this;
    }
    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class LongPressGestureHandler extends GestureHandler {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
    gestureTag?: string;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<void>;
    constructor(options?: LongPressGestureHandlerOptions) {
        super(CommonGestureType.LONG_PRESS_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.repeat = options.repeat;
            this.duration = options.duration;
        }
    }

    onAction(event: Callback<GestureEvent>) {
        this.onActionCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>) {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<void>) {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class PanGestureHandler extends GestureHandler {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
    gestureTag?: string;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<void>;
    constructor(options?: PanGestureHandlerOptions) {
        super(CommonGestureType.PAN_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.direction = options.direction;
            this.distance = options.distance;
        }
    }

    onActionStart(event: Callback<GestureEvent>) {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>) {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>) {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<void>) {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class SwipeGestureHandler extends GestureHandler {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
    gestureTag?: string;
    onActionCallback?: Callback<GestureEvent>;
    constructor(options?: SwipeGestureHandlerOptions) {
        super(CommonGestureType.PAN_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.direction = options.direction;
            this.speed = options.speed;
        }
    }

    onAction(event: Callback<GestureEvent>) {
        this.onActionCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class PinchGestureHandler extends GestureHandler {
    fingers?: number;
    distance?: number;
    gestureTag?: string;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<void>;
    constructor(options?: PinchGestureHandlerOptions) {
        super(CommonGestureType.PINCH_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.distance = options.distance;
        }
    }

    onActionStart(event: Callback<GestureEvent>) {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>) {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>) {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<void>) {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class RotationGestureHandler extends GestureHandler {
    fingers?: number;
    angle?: number;
    gestureTag?: string;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<void>;
    constructor(options?: RotationGestureHandlerOptions) {
        super(CommonGestureType.ROTATION_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.angle = options.angle;
        }
    }

    onActionStart(event: Callback<GestureEvent>) {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>) {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>) {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<void>) {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}

class GestureGroupHandler extends GestureHandler {
    mode?: GestureMode;
    gestures?: GestureHandler[];
    gestureTag?: string;
    onCancelCallback?: Callback<void>;
    constructor(options?: GestureGroupGestureHandlerOptions) {
        super(CommonGestureType.GESTURE_GROUP);
        if (options !== undefined) {
            this.mode = options.mode;
            this.gestures = options.gestures;
        }
    }

    onCancel(event: Callback<void>) {
        this.onCancelCallback = event;
        return this;
    }

    tag(tag: string) {
        this.gestureTag = tag;
        return this;
    }
}