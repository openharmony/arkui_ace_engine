import { nullptr } from "@koalaui/interop"
import { Callback } from "./common"
import { GestureOps } from "./idlize"
import { PeerNode } from "../PeerNode"
import { GlobalStateManager, MutableState } from '@koalaui/runtime'
import { KeyEventInternal, TouchTestInfo } from "arkui/component/common"
import { TypeChecker } from "#components"
import { ArkUIAniModule } from "arkui.ani"

export type GestureType = Gesture | GestureGroup;
export class GestureHandler {
    gestureTag: string | undefined;
    types: Array<SourceTool> | undefined;
    tag(tag: string): this {
        this.gestureTag = tag;
        return this;
    }
    allowedTypes(value: Array<SourceTool>): this {
        this.types = value;
        return this;
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void { }
    addGestureToGroup(group: KPointer): void { }
}
export class TapGestureHandler extends GestureHandler {
    finger?: int32;
    count?: int32;
    distanceThreshold?: double;
    isFingerCountLimited?: boolean;
    onActionCallback?: (event: GestureEvent) => void;
    pointer: KPointer = nullptr;
    constructor(options?: TapGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.count = options?.count;
        this.distanceThreshold = options?.distanceThreshold;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: (event: GestureEvent) => void): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetTapGestureAttr(): void {
        this.pointer = GestureOps.createTapGesture(this.finger ?? 1, this.count ?? 1, this.distanceThreshold ?? Infinity, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (((event: GestureEvent) => void)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetTapGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetTapGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class LongPressGestureHandler extends GestureHandler {
    finger?: int32;
    duration?: int32;
    repeat?: boolean;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: LongPressGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.duration = options?.duration;
        this.repeat = options?.repeat;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetLongPressGestureAttr(): void {
        this.pointer = GestureOps.createLongPressGesture(this.finger ?? 1, this.repeat ?? false, this.duration ?? 500, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetLongPressGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetLongPressGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PanGestureHandler extends GestureHandler {
    finger?: int32;
    direction?: PanDirection;
    distance?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PanGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.direction = options?.direction;
        this.distance = options?.distance;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPanGestureAttr(): void {
        this.pointer = GestureOps.createPanGesture(this.finger ?? 1, this.direction ?? PanDirection.ALL, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPanGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPanGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class SwipeGestureHandler extends GestureHandler {
    finger?: int32;
    direction?: SwipeDirection;
    speed?: double;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    constructor(options?: SwipeGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.direction = options?.direction;
        this.speed = options?.speed;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetSwipeGestureAttr(): void {
        this.pointer = GestureOps.createSwipeGesture(this.finger ?? 1, this.direction ?? SwipeDirection.ALL, this.speed ?? 100, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as ((Callback<GestureEvent>)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetSwipeGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetSwipeGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PinchGestureHandler extends GestureHandler {
    finger?: int32;
    distance?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: PinchGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.distance = options?.distance;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPinchGestureAttr(): void {
        this.pointer = GestureOps.createPinchGesture(this.finger ?? 2, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPinchGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPinchGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class RotationGestureHandler extends GestureHandler {
    finger?: int32;
    angle?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    constructor(options?: RotationGestureHandlerOptions) {
        super();
        this.finger = options?.fingers;
        this.angle = options?.angle;
        this.isFingerCountLimited = options?.isFingerCountLimited;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetRotationGestureAttr(): void {
        this.pointer = GestureOps.createRotationGesture(this.finger ?? 2, this.angle ?? 1, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetRotationGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetRotationGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class GestureGroupHandler extends GestureHandler {
    mode: GestureMode = GestureMode.SEQUENCE;
    gestures: GestureHandler[] = [];
    onCancelCallback?: () => void;
    pointer: KPointer = nullptr;
    constructor(options?: GestureGroupGestureHandlerOptions) {
        super();
        this.mode = options?.mode ?? GestureMode.SEQUENCE;
        if (options?.gestures !== undefined) {
            for (let gesture of (options?.gestures as GestureHandler[])) {
                this.gestures.push(gesture)
            }
        }
    }
    onCancel(event: () => void): this {
        this.onCancelCallback = event;
        return this;
    }
    createGestureGroup(): KPointer {
        this.pointer = GestureOps.createGestureGroup(this.mode);
        return this.pointer;
    }
    addGestureToGroup(group: KPointer): void {
        this.createGestureGroup();
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        GestureOps.addGestureToGroup(group, this.pointer);
    }
    addGestureGroupToNode(priority: number, node?: PeerNode, mask?: GestureMask): void {
        this.createGestureGroup();
        if (this.onCancelCallback !== undefined) {
            GestureOps.setOnCancel(this.pointer, this.onCancelCallback as (() => void));
        }
        for (let gesture of this.gestures) {
            if (gesture instanceof GestureGroupHandler) {
                let gestureGroup = gesture as GestureGroupHandler;
                gestureGroup.addGestureToGroup(this.pointer);
            } else if (gesture instanceof GestureHandler) {
                let singleGesture = gesture as GestureHandler;
                singleGesture.addGestureToGroup(this.pointer);
            }
        }
        if (node) {
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, true);
        }
    }
}
export class Gesture {
    gestureTag: string | undefined;
    types: Array<SourceTool> | undefined;
    tag(tag: string): this {
        this.gestureTag = tag;
        return this;
    }
    allowedTypes(value: Array<SourceTool>): this {
        this.types = value;
        return this;
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void { }
    addGestureToGroup(group: KPointer): void { }
}
export class TapGesture extends Gesture {
    finger?: int32;
    count?: int32;
    distanceThreshold?: double;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => TapGesture, value?: TapGestureParameters): TapGesture {
        console.log(`zcb TapGesture _instantiate`);
        const tap = factory();
        tap.finger = value?.fingers;
        tap.count = value?.count;
        tap.distanceThreshold = value?.distanceThreshold;
        tap.isFingerCountLimited = value?.isFingerCountLimited;
        return tap;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetTapGestureAttr(): void {
        this.pointer = GestureOps.createTapGesture(this.finger ?? 1, this.count ?? 1, this.distanceThreshold ?? Infinity, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            console.log(`zcb TapGesture setGesture`);
            this.createAndSetTapGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetTapGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class LongPressGesture extends Gesture {
    finger?: int32;
    duration?: int32;
    repeat?: boolean;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => LongPressGesture, value?: LongPressGestureHandlerOptions): LongPressGesture {
        const longPress = factory();
        longPress.finger = value?.fingers;
        longPress.duration = value?.duration;
        longPress.repeat = value?.repeat;
        longPress.isFingerCountLimited = value?.isFingerCountLimited;
        return longPress;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetLongPressGestureAttr(): void {
        this.pointer = GestureOps.createLongPressGesture(this.finger ?? 1, this.repeat ?? false, this.duration ?? 500, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetLongPressGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetLongPressGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PanGesture extends Gesture {
    finger?: int32;
    direction?: PanDirection;
    distance?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    panGestureOptions?: PanGestureOptions;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => PanGesture, value?: PanGestureHandlerOptions | PanGestureOptions): PanGesture {
        const pan = factory();
        if (TypeChecker.isPanGestureHandlerOptions(value, false, false, false)) {
            let options = value as PanGestureHandlerOptions;
            pan.finger = options?.fingers;
            pan.direction = options?.direction;
            pan.distance = options?.distance;
            pan.isFingerCountLimited = options?.isFingerCountLimited;
        } else if (value !== undefined) {
            let panGestureOptions = value as PanGestureOptions;
            pan.panGestureOptions = panGestureOptions;
        }
        return pan;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPanGestureAttr(): void {
        if (this.panGestureOptions !== undefined) {
            this.panGestureOptions!.getOptionState()
            this.pointer = GestureOps.createPanGestureWithPanGestureOptions(this.panGestureOptions!.getPeer()!.ptr);
        } else {
            this.pointer = GestureOps.createPanGesture(this.finger ?? 1, this.direction ?? PanDirection.ALL, this.distance ?? 5, this.isFingerCountLimited ?? false);
        }
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPanGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPanGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class PinchGesture extends Gesture {
    finger?: int32;
    distance?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => PinchGesture, value?: PinchGestureHandlerOptions): PinchGesture {
        const pinch = factory();
        pinch.finger = value?.fingers;
        pinch.distance = value?.distance;
        pinch.isFingerCountLimited = value?.isFingerCountLimited;
        return pinch;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetPinchGestureAttr(): void {
        this.pointer = GestureOps.createPinchGesture(this.finger ?? 2, this.distance ?? 5, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetPinchGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetPinchGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class RotationGesture extends Gesture {
    finger?: int32;
    angle?: double;
    isFingerCountLimited?: boolean;
    pointer: KPointer = nullptr;
    onActionStartCallback?: Callback<GestureEvent>;
    onActionUpdateCallback?: Callback<GestureEvent>;
    onActionEndCallback?: Callback<GestureEvent>;
    onActionCancelCallback?: Callback<GestureEvent>;
    static $_instantiate(factory: () => RotationGesture, value?: RotationGestureHandlerOptions): RotationGesture {
        const rotation = factory();
        rotation.finger = value?.fingers;
        rotation.angle = value?.angle;
        rotation.isFingerCountLimited = value?.isFingerCountLimited;
        return rotation;
    }
    onActionStart(event: Callback<GestureEvent>): this {
        this.onActionStartCallback = event;
        return this;
    }
    onActionUpdate(event: Callback<GestureEvent>): this {
        this.onActionUpdateCallback = event;
        return this;
    }
    onActionEnd(event: Callback<GestureEvent>): this {
        this.onActionEndCallback = event;
        return this;
    }
    onActionCancel(event: Callback<GestureEvent>): this {
        this.onActionCancelCallback = event;
        return this;
    }
    createAndSetRotationGestureAttr(): void {
        this.pointer = GestureOps.createRotationGesture(this.finger ?? 2, this.angle ?? 1, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionStartCallback !== undefined) {
            GestureOps.setOnActionStart(this.pointer, this.onActionStartCallback as (Callback<GestureEvent>));
        }
        if (this.onActionUpdateCallback !== undefined) {
            GestureOps.setOnActionUpdate(this.pointer, this.onActionUpdateCallback as (Callback<GestureEvent>));
        }
        if (this.onActionEndCallback !== undefined) {
            GestureOps.setOnActionEnd(this.pointer, this.onActionEndCallback as (Callback<GestureEvent>));
        }
        if (this.onActionCancelCallback !== undefined) {
            GestureOps.setOnActionCancel(this.pointer, this.onActionCancelCallback as (Callback<GestureEvent>));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetRotationGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetRotationGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class SwipeGesture extends Gesture {
    finger?: int32;
    direction?: SwipeDirection;
    speed?: double;
    isFingerCountLimited?: boolean;
    onActionCallback?: Callback<GestureEvent>;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => SwipeGesture, value?: SwipeGestureHandlerOptions): SwipeGesture {
        const swipe = factory();
        swipe.finger = value?.fingers;
        swipe.direction = value?.direction;
        swipe.speed = value?.speed;
        swipe.isFingerCountLimited = value?.isFingerCountLimited;
        return swipe;
    }
    onAction(event: Callback<GestureEvent>): this {
        this.onActionCallback = event;
        return this;
    }
    createAndSetSwipeGestureAttr(): void {
        this.pointer = GestureOps.createSwipeGesture(this.finger ?? 1, this.direction ?? SwipeDirection.ALL, this.speed ?? 100, this.isFingerCountLimited ?? false);
        if (this.gestureTag !== undefined) {
            GestureOps.setGestureTag(this.pointer, this.gestureTag ?? "");
        }
        if (this.onActionCallback !== undefined) {
            GestureOps.setOnAction(this.pointer, this.onActionCallback as ((Callback<GestureEvent>)));
        }
        if (this.types !== undefined) {
            GestureOps.setAllowedTypes(this.pointer, this.types as Array<SourceTool>);
        }
    }
    setGesture(priority: number, node?: PeerNode, mask?: GestureMask): void {
        if (node) {
            this.createAndSetSwipeGestureAttr();
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
    addGestureToGroup(group: KPointer): void {
        this.createAndSetSwipeGestureAttr();
        GestureOps.addGestureToGroup(group, this.pointer);
    }
}
export class GestureGroup {
    mode: GestureMode = GestureMode.SEQUENCE;
    gestures: GestureType[] = [];
    onCancelCallback?: () => void;
    pointer: KPointer = nullptr;
    static $_instantiate(factory: () => GestureGroup, mode: GestureMode, ...gestures: GestureType[]): GestureGroup {
        const group = factory();
        group.mode = mode;
        group.gestures = gestures;
        return group;
    }
    onCancel(event: () => void): this {
        this.onCancelCallback = event;
        return this;
    }
    createGestureGroup(): KPointer {
        this.pointer = GestureOps.createGestureGroup(this.mode);
        return this.pointer;
    }
    addGestureToGroup(group: KPointer): void {
        this.createGestureGroup();
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        GestureOps.addGestureToGroup(group, this.pointer);
    }
    addGestureGroupToNode(priority: number, node?: PeerNode, mask?: GestureMask): void {
        this.createGestureGroup();
        if (this.onCancelCallback !== undefined) {
            GestureOps.setOnCancel(this.pointer, this.onCancelCallback as (() => void));
        }
        for (let gesture of this.gestures) {
            if (gesture instanceof Gesture) {
                let singleGesture = gesture as Gesture;
                singleGesture.addGestureToGroup(this.pointer);
            }
            if (gesture instanceof GestureGroup) {
                let gestureGroup = gesture as GestureGroup;
                gestureGroup.addGestureToGroup(this.pointer);
            }
        }
        if (node) {
            GestureOps.addGestureToNode(node.peer.ptr, priority, mask ?? GestureMask.NORMAL, this.pointer, false);
        }
    }
}

// export class PanGestureOptions implements MaterializedBase {
//     peer?: Finalizable | undefined = undefined
//     public optionState: MutableState<int32>
//     public getPeer(): Finalizable | undefined {
//         return this.peer
//     }
//     static ctor_pangestureoptions(value?: PanGestureHandlerOptions): KPointer {
//         const thisSerializer: Serializer = Serializer.hold()
//         let value_type: int32 = RuntimeType.UNDEFINED
//         value_type = runtimeType(value)
//         thisSerializer.writeInt8(value_type)
//         if ((RuntimeType.UNDEFINED) != (value_type)) {
//             const value_value = value!
//             thisSerializer.writePanGestureHandlerOptions(value_value)
//         }
//         const retval = ArkUIGeneratedNativeModule._PanGestureOptions_ctor(thisSerializer.asBuffer(), thisSerializer.length())
//         thisSerializer.release()
//         return retval
//     }
//     constructor(value?: PanGestureHandlerOptions) {
//         const ctorPtr: KPointer = PanGestureOptions.ctor_pangestureoptions(value)
//         const manager = GlobalStateManager.instance
//         this.optionState = manager.mutableState<int32>(0 as int32, true)
//         this.peer = new Finalizable(ctorPtr, PanGestureOptions.getFinalizer())
//     }
//     static getFinalizer(): KPointer {
//         return ArkUIGeneratedNativeModule._PanGestureOptions_getFinalizer()
//     }
//     public getOptionState(): number {
//         return this.optionState!.value
//     }
//     public setOptionState(): void {
//         this.optionState!.value = this.optionState!.value % 100 + 1
//     }
//     public setDirection(value: PanDirection): void {
//         const value_casted = value as (PanDirection)
//         this.setDirection_serialize(value_casted)
//         this.setOptionState()
//     }
//     public setDistance(value: number): void {
//         const value_casted = value as (number)
//         this.setDistance_serialize(value_casted)
//         this.setOptionState()
//     }
//     public setFingers(value: number): void {
//         const value_casted = value as (number)
//         this.setFingers_serialize(value_casted)
//         this.setOptionState()
//     }
//     public getDirection(): PanDirection {
//         return this.getDirection_serialize()
//     }
//     public getDistance(): number {
//         return this.getDistance_serialize()
//     }
//     private setDirection_serialize(value: PanDirection): void {
//         ArkUIGeneratedNativeModule._PanGestureOptions_setDirection(this.peer!.ptr, TypeChecker.PanDirection_ToNumeric(value))
//     }
//     private setDistance_serialize(value: number): void {
//         ArkUIGeneratedNativeModule._PanGestureOptions_setDistance(this.peer!.ptr, value)
//     }
//     private setFingers_serialize(value: number): void {
//         ArkUIGeneratedNativeModule._PanGestureOptions_setFingers(this.peer!.ptr, value)
//     }
//     private getDirection_serialize(): PanDirection {
//         const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDirection(this.peer!.ptr)
//         return TypeChecker.PanDirection_FromNumeric(retval)
//     }
//     private getDistance_serialize(): number {
//         const retval  = ArkUIGeneratedNativeModule._PanGestureOptions_getDistance(this.peer!.ptr)
//         return retval
//     }
// }

export class ScrollableTargetInfoTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            return new Object();
        }
        if(input === null) {
            return new Object();
        }
        let objectInternal : ScrollableTargetInfo = new ScrollableTargetInfo();
        let peer: KPointer = ArkUIAniModule._CreateScrollableTargetInfoAccessor()
        let esValue: ESValue = ESValue.wrap(input);
        let id = esValue.invokeMethod("getId");
        if (id.isString()) {
            ArkUIAniModule._ScrollableTargetInfoAccessorWithId(peer, id.toString())
        }
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('getScrollableTargetInfoPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        let pointer = wrapFunc.invoke(esValue);
        if (pointer.isNumber()) {
            ArkUIAniModule._ScrollableTargetInfoAccessorWithPointer(peer, pointer.toNumber() as long)
        }
        objectInternal.peer!.ptr = peer;
        return objectInternal;
    }
    static transferDynamic(input: Object): Any { 
        if (input == null) {
            return new Object();
        }
        let objectInternal: EventTargetInfo = input as EventTargetInfo;
        const nativePointer: KPointer = ArkUIAniModule._TransferScrollableTargetInfoPointer(objectInternal.peer!.ptr as long);
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapScrollableTargetInfoPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        let retValue = wrapFunc.invoke(objectInternal.getId(), nativePointer);
        return retValue;
    }
}

export class EventTargetInfoTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            return new Object();
        }
        if(input === null) {
            return new Object();
        }
        let objectInternal : EventTargetInfo = new EventTargetInfo();
        let esValue: ESValue = ESValue.wrap(input);
        let peer: KPointer = ArkUIAniModule._CreateEventTargetInfoAccessor()
        let id = esValue.invokeMethod("getId");
        if (id.isString()) {
            ArkUIAniModule._EventTargetInfoAccessorWithId(peer, id.toString())
        }
        objectInternal.peer!.ptr = peer;
        return objectInternal;
    }
    static transferDynamic(input: Object): Any { 
        if (input == null) {
            return new Object();
        }
        
        let objectInternal: EventTargetInfo = input as EventTargetInfo;
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('WrapEventTargetInfoPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        let retValue = wrapFunc.invoke(objectInternal.getId());
        return retValue;
    }
}