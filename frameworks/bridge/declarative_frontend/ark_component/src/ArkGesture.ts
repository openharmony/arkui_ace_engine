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
    limitFingerCount?: boolean;
    gestureTag?: string;
    allowedTypes?: Array<SourceTool>;
    onActionCallback?: Callback<GestureEvent>;

    constructor(options?: TapGestureHandlerOptions) {
        super(CommonGestureType.TAP_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.count = options.count;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }
    onAction(event: Callback<GestureEvent>): TapGestureHandler {
        this.onActionCallback = event;
        return this;
    }
    tag(tag: string): TapGestureHandler {
        this.gestureTag = tag;
        return this;
    }
    allowedTypes(types: Array<SourceTool>): TapGestureHandler {
        this.allowedTypes = types;
        return this;
    }
}

class LongPressGestureHandler extends GestureHandler {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
    gestureTag?: string;
    limitFingerCount?: boolean;
    allowedTypes?: Array<SourceTool>;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: LongPressGestureHandlerOptions) {
        super(CommonGestureType.LONG_PRESS_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.repeat = options.repeat;
            this.duration = options.duration;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }

    onAction(event: Callback<GestureEvent>): LongPressGestureHandler {
        this.onActionCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>): LongPressGestureHandler {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<GestureEvent>): LongPressGestureHandler {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string): LongPressGestureHandler {
        this.gestureTag = tag;
        return this;
    }

    allowedTypes(types: Array<SourceTool>): LongPressGestureHandler {
        this.allowedTypes = types;
        return this;
    }
}

class PanGestureHandler extends GestureHandler {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
    limitFingerCount?: boolean;
    gestureTag?: string;
    allowedTypes?: Array<SourceTool>;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PanGestureHandlerOptions) {
        super(CommonGestureType.PAN_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.direction = options.direction;
            this.distance = options.distance;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }

    onActionStart(event: Callback<GestureEvent>): PanGestureHandler {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>): PanGestureHandler {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>): PanGestureHandler {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<GestureEvent>): PanGestureHandler {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string): PanGestureHandler {
        this.gestureTag = tag;
        return this;
    }

    allowedTypes(types: Array<SourceTool>): PanGestureHandler {
        this.allowedTypes = types;
        return this;
    }
}

class SwipeGestureHandler extends GestureHandler {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
    limitFingerCount?: boolean;
    gestureTag?: string;
    allowedTypes?: Array<SourceTool>;
    onActionCallback?: Callback<GestureEvent>;
    constructor(options?: SwipeGestureHandlerOptions) {
        super(CommonGestureType.PAN_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.direction = options.direction;
            this.speed = options.speed;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }

    onAction(event: Callback<GestureEvent>): SwipeGestureHandler {
        this.onActionCallback = event;
        return this;
    }

    tag(tag: string): SwipeGestureHandler {
        this.gestureTag = tag;
        return this;
    }

    allowedTypes(types: Array<SourceTool>): SwipeGestureHandler {
        this.allowedTypes = types;
        return this;
    }
}

class PinchGestureHandler extends GestureHandler {
    fingers?: number;
    distance?: number;
    limitFingerCount?: boolean;
    gestureTag?: string;
    allowedTypes?: Array<SourceTool>;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PinchGestureHandlerOptions) {
        super(CommonGestureType.PINCH_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.distance = options.distance;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }

    onActionStart(event: Callback<GestureEvent>): PinchGestureHandler {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>): PinchGestureHandler {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>): PinchGestureHandler {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<GestureEvent>): PinchGestureHandler {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string): PinchGestureHandler {
        this.gestureTag = tag;
        return this;
    }

    allowedTypes(types: Array<SourceTool>): PinchGestureHandler {
        this.allowedTypes = types;
        return this;
    }
}

class RotationGestureHandler extends GestureHandler {
    fingers?: number;
    angle?: number;
    limitFingerCount?: boolean;
    gestureTag?: string;
    allowedTypes?: Array<SourceTool>;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: RotationGestureHandlerOptions) {
        super(CommonGestureType.ROTATION_GESTURE);
        if (options !== undefined) {
            this.fingers = options.fingers;
            this.angle = options.angle;
            this.limitFingerCount = options.isFingerCountLimited;
        }
    }

    onActionStart(event: Callback<GestureEvent>): RotationGestureHandler {
        this.onActionStartCallback = event;
        return this;
    }

    onActionUpdate(event: Callback<GestureEvent>): RotationGestureHandler {
        this.onActionUpdateCallback = event;
        return this;
    }

    onActionEnd(event: Callback<GestureEvent>): RotationGestureHandler {
        this.onActionEndCallback = event;
        return this;
    }

    onActionCancel(event: Callback<GestureEvent>): RotationGestureHandler {
        this.onActionCancelCallback = event;
        return this;
    }

    tag(tag: string): RotationGestureHandler {
        this.gestureTag = tag;
        return this;
    }

    allowedTypes(types: Array<SourceTool>): RotationGestureHandler {
        this.allowedTypes = types;
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

    onCancel(event: Callback<void>): GestureGroupHandler {
        this.onCancelCallback = event;
        return this;
    }

    tag(tag: string): GestureGroupHandler {
        this.gestureTag = tag;
        return this;
    }
}