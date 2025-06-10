/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { GesturePeerEvent, UseProperties } from "@koalaui/arkoala"
import { Access, KPointer, withIntArray } from "@koalaui/interop"
import { makeEventTarget } from "./Events"

export enum GestureName {
    Tap,
    LongPress,
    Pan,
    Pinch,
    Swipe,
    Rotate,
    Group
}

function getGestureMask(mask: GestureMask): number {
    switch(mask) {
        case GestureMask.NORMAL:
            return 0;
        case GestureMask.IGNORE_INTERNAL:
            return 1;
    }
    return 0
}

function getGestureMode(mode: GestureMode): number {
    switch(mode) {
        case GestureMode.SEQUENCE:
            return 0;
        case GestureMode.PARALLEL:
            return 1;
        case GestureMode.EXCLUSIVE:
            return 2;
    }
    return 0
}

function convertEvent(event : GesturePeerEvent) : GestureEvent {
    return {
        repeat: event.gestureEvent[0] ? true : false,
        offsetX: event.gestureEvent[1],
        offsetY: event.gestureEvent[2],
        angle: event.gestureEvent[3],
        scale: event.gestureEvent[4],
        pinchCenterX: event.gestureEvent[5],
        pinchCenterY: event.gestureEvent[6],
        speed: event.gestureEvent[7],
        fingerList: [],
        velocity: event.gestureEvent[16],
        velocityX: event.gestureEvent[14],
        velocityY: event.gestureEvent[15],
        target: makeEventTarget({
            width: 0,
            height: 0,
            position: {},
            globalPosition: {}
        }),
        timestamp: event.gestureEvent[8],
        source: event.gestureEvent[9],
        pressure: event.gestureEvent[10],
        tiltX: event.gestureEvent[11],
        tiltY: event.gestureEvent[12],
        sourceTool: event.gestureEvent[13],
        getModifierKeyState: (keys: string[]) => { return false } // API_12
    }
}

class GestureComponent<T> {
    public readonly type : GestureName
    public readonly value?: T
    public hasEvent = new Int32Array(4).fill(0)

    constructor(type: GestureName, value?: T) {
        this.type = type
        this.value = value
    }

    public setEvent(index: number) {
        this.hasEvent[index] = 1;
    }
}

function cast<T>(obj : object) : T {
    return (obj as unknown) as T
}

/** @memo:stable */
class TapGestureComponent extends GestureComponent<{ count?: number; fingers?: number; }> {
    public action?: (event?: GestureEvent) => void

    constructor(public value?: { count?: number; fingers?: number; }) {
        super(GestureName.Tap, value)
    }

    public onAction(event: (event?: GestureEvent) => void) : TapGestureInterface {
        this.action = event
        this.setEvent(0)
        return cast(this)
    }
}

export const TapGesture: TapGestureInterface = ((value?: { count?: number; fingers?: number; }) => {
    return cast(new TapGestureComponent(value))
}) as TapGestureInterface

/** @memo:stable */
class LongPressGestureComponent extends GestureComponent<{ fingers?: number; repeat?: boolean; duration?: number; }> {
    public action?: (event?: GestureEvent) => void
    public actionEnd?: (event?: GestureEvent) => void
    public actionCancel?: () => void


    constructor(public value?: { fingers?: number; repeat?: boolean; duration?: number; }) {
        // TODO handle value
        super(GestureName.LongPress, value)
    }

    public onAction(event: (event?: GestureEvent) => void) : LongPressGestureInterface {
        this.action = event
        this.setEvent(0)
        return cast(this)
    }

    public onActionEnd(event: (event?: GestureEvent) => void): LongPressGestureInterface {
        this.actionEnd = event
        this.setEvent(1)
        return cast(this)
    }

    public onActionCancel(event: () => void): LongPressGestureInterface {
        this.actionCancel = event
        this.setEvent(2)
        return cast(this)
    }
}


export const LongPressGesture: LongPressGestureInterface = ((value?: { fingers?: number; repeat?: boolean; duration?: number; }) => {
    return cast(new LongPressGestureComponent(value))
}) as LongPressGestureInterface


export class PanGestureOptions {
    public fingers: number = 1
    public direction: PanDirection = PanDirection.ALL
    public distance: number = 5

    constructor(value?: {
        fingers?: number
        direction?: PanDirection
        distance?: number
    }) {
        if (value) {
            this.fingers = value.fingers ?? 1
            this.direction = value.direction ?? PanDirection.ALL
            this.distance = value.distance ?? 5
        }
    }

    setDirection(value: PanDirection) {
        this.direction = value
    }

    setDistance(value: number) {
        this.distance = value
    }

    setFingers(value: number) {
        this.fingers = value
    }
}

/** @memo:stable */
class PanGestureComponent extends GestureComponent<{ fingers?: number; direction?: PanDirection; distance?: number; } | PanGestureOptions> {
    public actionStart?: (event?: GestureEvent) => void
    public actionUpdate?: (event?: GestureEvent) => void
    public actionEnd?: (event?: GestureEvent) => void
    public actionCancel?: () => void


    constructor(value?: { fingers?: number; direction?: PanDirection; distance?: number; } | PanGestureOptions) {
        super(GestureName.Pan, value)
    }

    public onActionStart(event: (event?: GestureEvent) => void) : PanGestureInterface {
        this.actionStart = event
        this.setEvent(0)
        return cast(this)
    }

    public onActionUpdate(event: (event?: GestureEvent) => void): PanGestureInterface {
        this.actionUpdate = event
        this.setEvent(1)
        return cast(this)
    }

    public onActionEnd(event: (event?: GestureEvent) => void): PanGestureInterface {
        this.actionEnd = event
        this.setEvent(2)
        return cast(this)
    }

    public onActionCancel(event: () => void): PanGestureInterface {
        this.actionCancel = event
        this.setEvent(3)
        return cast(this)
    }
}

export const PanGesture: PanGestureInterface = ((value?: { fingers?: number; direction?: PanDirection; distance?: number; } | PanGestureOptions) => {
    return cast(new PanGestureComponent(value))
}) as PanGestureInterface

/** @memo:stable */
class PinchGestureComponent extends GestureComponent<{ fingers?: number; distance?: number;}> {
    public actionStart?: (event?: GestureEvent) => void
    public actionUpdate?: (event?: GestureEvent) => void
    public actionEnd?: (event?: GestureEvent) => void
    public actionCancel?: () => void


    constructor(value?: { fingers?: number; distance?: number;}) {
        // TODO handle value
        super(GestureName.Pinch, value)
    }

    public onActionStart(event: (event?: GestureEvent) => void) : PinchGestureComponent {
        this.actionStart = event
        this.setEvent(0)
        return cast(this)
    }

    public onActionUpdate(event: (event?: GestureEvent) => void): PinchGestureComponent {
        this.actionUpdate = event
        this.setEvent(1)
        return cast(this)
    }

    public onActionEnd(event: (event?: GestureEvent) => void): PinchGestureComponent {
        this.actionEnd = event
        this.setEvent(2)
        return cast(this)
    }

    public onActionCancel(event: () => void): PinchGestureComponent {
        this.actionCancel = event
        this.setEvent(3)
        return cast(this)
    }
}


export const PinchGesture: PinchGestureInterface = ((value?: { fingers?: number; distance?: number;}) => {
    return cast(new PinchGestureComponent(value))
}) as PinchGestureInterface

export class GestureGroupComponent extends GestureComponent<{mode: GestureMode, gestures: GestureType[]}> {
    public actionCancel?: () => void

    constructor(public mode: GestureMode, public gestures: GestureType[]) {
        // TODO handle value
        super(GestureName.Group, {mode: mode, gestures: gestures})
    }

    public onCancel(event: () => void) : GestureGroupInterface {
        this.actionCancel = event
        this.setEvent(0)
        return cast(this)
    }
}

export const GestureGroup: GestureGroupInterface = ((mode: GestureMode, ...gesture: GestureType[]) => {
    return cast(new GestureGroupComponent(mode, gesture))
}) as GestureGroupInterface

/** @memo */
export function setGestureEvent(nodePtr: KPointer, gesture: GestureType, mask: GestureMask, priority: GesturePriority) {
    let gestureInfo = cast<GestureComponent<any>>(gesture)
    let gestureMask = getGestureMask(mask);
    if (gestureInfo.hasEvent!.some(item => item === 1) || gestureInfo.type === GestureName.Group) {
        switch(gestureInfo.type) {
            case GestureName.Tap:
                UseProperties({
                    onAction: (gestureEvent) => {
                        (gestureInfo as TapGestureComponent).action!(convertEvent(gestureEvent))
                    }
                })
                // todo
                // nativeModule()._TapGestureAsyncEvent(nodePtr, gestureMask, priority, gestureInfo.value?.count ?? 1, gestureInfo.value?.fingers ?? 1)
                break;
            case GestureName.LongPress:
                if (gestureInfo.hasEvent[0]) {
                    UseProperties({
                        onAction: (gestureEvent) => {
                            (gestureInfo as LongPressGestureComponent).action!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[1]) {
                    UseProperties({
                        onActionEnd: (gestureEvent) => {
                            (gestureInfo as LongPressGestureComponent).actionEnd!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[2]) {
                    UseProperties({
                        onActionCancel: () => {
                            (gestureInfo as LongPressGestureComponent).actionCancel!()
                        }
                    })
                }
                withIntArray(gestureInfo!.hasEvent, Access.READ, (hasEvent) => {
                    // todo
                    // nativeModule()._LongPressGestureAsyncEvent(nodePtr, gestureMask, priority, gestureInfo.value?.fingers ?? 1, gestureInfo.value?.repeat ? 1 : 0, gestureInfo.value?.duration ?? 500, hasEvent)
                })
                break;
            case GestureName.Pan:
                if (gestureInfo.hasEvent[0]) {
                    UseProperties({
                        onActionStart: (gestureEvent) => {
                            (gestureInfo as PanGestureComponent).actionStart!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[1]) {
                    UseProperties({
                        onActionUpdate: (gestureEvent) => {
                            (gestureInfo as PanGestureComponent).actionUpdate!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[2]) {
                    UseProperties({
                        onActionEnd: (gestureEvent) => {
                            (gestureInfo as PanGestureComponent).actionEnd!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[3]) {
                    UseProperties({
                        onActionCancel: () => {
                            (gestureInfo as PanGestureComponent).actionCancel!()
                        }
                    })
                }
                withIntArray(gestureInfo!.hasEvent, Access.READ, (hasEvent) => {
                    // todo
                    // nativeModule()._PanGestureAsyncEvent(nodePtr, gestureMask, priority, gestureInfo.value?.fingers ?? 1, gestureInfo.value?.direction ?? PanDirection.All, gestureInfo.value?.distance ?? 5, hasEvent)
                })

                break;
            case GestureName.Pinch:
                if (gestureInfo.hasEvent[0]) {
                    UseProperties({
                        onActionStart: (gestureEvent) => {
                            (gestureInfo as PinchGestureComponent).actionStart!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[1]) {
                    UseProperties({
                        onActionUpdate: (gestureEvent) => {
                            (gestureInfo as PinchGestureComponent).actionUpdate!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[2]) {
                    UseProperties({
                        onActionEnd: (gestureEvent) => {
                            (gestureInfo as PinchGestureComponent).actionEnd!(convertEvent(gestureEvent))
                        }
                    })
                }
                if (gestureInfo.hasEvent[3]) {
                    UseProperties({
                        onActionCancel: () => {
                            (gestureInfo as PinchGestureComponent).actionCancel!()
                        }
                    })
                }
                withIntArray(gestureInfo!.hasEvent, Access.READ, (hasEvent) => {
                    // todo
                    // nativeModule()._PinchGestureAsyncEvent(nodePtr, gestureMask, priority, gestureInfo.value?.fingers ?? 2, gestureInfo.value?.distance ?? 3, hasEvent)
                })
                break;
            case GestureName.Group:
                let gestureMode = getGestureMode(gestureInfo.value?.mode ?? GestureMode.SEQUENCE)
                if ((gestureInfo as GestureGroupComponent).actionCancel) {
                    UseProperties({
                        onActionCancel: () => {
                            (gestureInfo as GestureGroupComponent).actionCancel!()
                        }
                    })
                }
                for (let subGesture of gestureInfo.value.gestures) {
                    setGestureEvent(nodePtr, subGesture, gestureMask, priority)
                }
                withIntArray(gestureInfo!.hasEvent, Access.READ, (hasEvent) => {
                    // todo
                    // nativeModule()._GroupGestureAsyncEvent(nodePtr, gestureMode, hasEvent)
                })


        }
    } else {
        // todo
        // nativeModule()._NotifyResetGestureAsyncEvent(nodePtr, GestureAsyncEventSubKind.OnAction)
    }
}