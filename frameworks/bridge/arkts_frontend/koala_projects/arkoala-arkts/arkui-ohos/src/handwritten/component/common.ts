import { GestureOps, OverlayOps } from "./arkui-custom"
import { GestureGroupHandler } from "./gesture"
import { ArkUIAniModule } from "arkui.ani"
import { int32 } from "@koalaui/common"
import { AnimateParam } from "../component"
import { CommonMethodHandWritten } from "./../handwritten"
import { KPointer } from "@koalaui/interop"
import { ComponentContent } from 'arkui/ComponentContent'
import { ArkCommonMethodComponent, CustomBuilder, OverlayOptions } from 'arkui/component'
import { runtimeType, RuntimeType, toPeerPtr} from "@koalaui/interop"
import { FrameNode } from "arkui/FrameNode"
import { WrappedBuilder } from './builder'
import { KeyEventInternal, TouchTestInfo, DragEventInternal } from "arkui/component/common"
import { TypeChecker } from "#components"

export function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T {
    customStyles(this);
    return this;
}

export class UIGestureEvent {
    private peer?: PeerNode
    setPeer(peer?: PeerNode) {
        this.peer = peer
    }
    addGesture(gesture: GestureHandler, priority?: GesturePriority, mask?: GestureMask): void {
        if (gesture instanceof GestureGroupHandler) {
            let gestureGroup = gesture as GestureGroupHandler;
            gestureGroup.addGestureGroupToNode(priority ?? GesturePriority.NORMAL, this.peer, mask)
        } else if (gesture instanceof GestureHandler) {
            gesture.setGesture(priority ?? GesturePriority.NORMAL, this.peer, mask);
        }
    }
    addParallelGesture(gesture: GestureHandler, mask?: GestureMask): void {
        if (gesture instanceof GestureGroupHandler) {
            let gestureGroup = gesture as GestureGroupHandler;
            gestureGroup.addGestureGroupToNode(2, this.peer, mask)
        } else if (gesture instanceof GestureHandler) {
            gesture.setGesture(2, this.peer, mask);
        }
    }
    removeGestureByTag(tag: string): void {
        if (this.peer) {
            let peerNode = this.peer as PeerNode;
            GestureOps.removeGestureByTag(peerNode.peer.ptr, tag);
        }
    }
    clearGestures(): void {
        if (this.peer) {
            let peerNode = this.peer as PeerNode;
            GestureOps.clearGestures(peerNode.peer.ptr);
        }
    }
}

export function hookDrawModifierInvalidateImpl(modifier: DrawModifier): void {
    let peerNode: PeerNode | undefined = modifier.weakRefOfPeerNode?.deref();
    if (peerNode && peerNode.peer.ptr) {
        ArkUIAniModule._Invalidate(peerNode.peer.ptr)
    }
}

export function animateToImmediately(value: AnimateParam, event: (() => void)): void {
    CommonMethodHandWritten.hookCommonMethodAnimateToImmediatelyImpl(value, event);
}
export function hookDrawModifier(arkComponent: ArkCommonMethodComponent, value: DrawModifier | undefined): void {
    if (value !== undefined) {
        let classType: ClassType = (Type.of(value) as ClassType);
        let numberOfFun = classType.getMethodsNum();
        let flag: int32 = 0;
        for (let i = 0; i < numberOfFun; i++) {
            if (classType.getMethod(i)?.getName() === "drawFront") {
                flag = flag + 1;
            } else if (classType.getMethod(i)?.getName() === "drawContent") {
                flag = flag + (1 << 1);
            } else if (classType.getMethod(i)?.getName() === "drawBehind") {
                flag = flag + (1 << 2);
            }
        }
        if (flag) {
            ArkUIAniModule._SetDrawModifier(arkComponent.getPeer().getPeerPtr(), flag, value);
            value.weakRefOfPeerNode = new WeakRef<PeerNode>(arkComponent.getPeer());
        }
    }
}

export class DrawModifier {
    weakRefOfPeerNode?: WeakRef<PeerNode>;
    constructor() {
    }
    public invalidate(): void {
        hookDrawModifierInvalidateImpl(this);
        return
    }
}
export class ChildrenMainSizeInternal {
    public static fromPtr(ptr: KPointer): ChildrenMainSize {
        const obj: ChildrenMainSize = new ChildrenMainSize(0)
        return obj
    }
}

interface ChildrenSizeChangeInfo {
    start: number;
    deleteCount?: number;
    childrenSize?: Array<number>;
}

export class ChildrenMainSize {
    private sizeArray: Array<number> = new Array<number>();
    private changeArray: Array<ChildrenSizeChangeInfo> = new Array<ChildrenSizeChangeInfo>();
    private defaultMainSize: number = -1;

    constructor(childDefaultSize: number) {
        if (this.isInvalid(childDefaultSize)) {
            throw new Error("The parameter check failed.");
        }
        this.defaultMainSize = childDefaultSize as number;
        this.sizeArray = [];
        // -1: represent newly created.
        this.changeArray = [ { start: -1 } ];
    }

    private isInvalid(input: number | undefined): boolean {
        if (input === undefined) {
            return true;
        }
        return !(Number.isFinite(input) && input >= 0);
    }

    set childDefaultSize(value: number) {
        if (this.isInvalid(value)) {
            throw new Error("The parameter check failed.");
        }
        this.defaultMainSize = value as number;
    }

    get childDefaultSize(): number {
        return this.defaultMainSize;
    }
    // splice(start: number, deleteCount?: number, childrenSize?: Array<number>);
    public splice(start: number, deleteCount?: number, childrenSize?: Array<number>): void {
        if (this.isInvalid(start)) {
            throw new Error("The parameter check failed.");
        }
        const startValue: number = Math.trunc(start);
        const deleteCountValue: number = deleteCount && !(this.isInvalid(deleteCount)) ? Math.trunc(deleteCount) : 0;
        if (deleteCount === undefined && childrenSize === undefined) {
            this.sizeArray.splice(startValue);
            this.changeArray.push({ start: startValue });
        } else if (childrenSize === undefined) {
            this.sizeArray.splice(startValue, deleteCountValue);
            this.changeArray.push({ start: startValue, deleteCount: deleteCountValue });
        } else {
            const childrenSizeLength: number = childrenSize ? childrenSize.length : 0;
            if (childrenSizeLength === 0) {
                childrenSize = [];
            }
            for (let i: number = 0; i < childrenSizeLength; i++) {
                if (this.isInvalid(childrenSize[i])) {
                    // -1: represent default size.
                    childrenSize[i] = -1;
                }
            }
            while (startValue >= this.sizeArray.length) {
                this.sizeArray.push(-1);
            }
            this.sizeArray.splice(startValue, deleteCountValue, ...childrenSize);
            this.changeArray.push({ start: startValue, deleteCount: deleteCountValue, childrenSize: childrenSize });
        }
    }

    public update(index: number, childSize: number): void {
        if (this.isInvalid(index)) {
            throw new Error("The parameter check failed.");
        } else if (this.isInvalid(childSize)) {
            // -1: represent default size.
            childSize = -1;
        }
        const startValue: number = Math.trunc(index);
        while (startValue >= this.sizeArray.length) {
            this.sizeArray.push(-1);
        }
        this.sizeArray.splice(startValue, 1, childSize);
        this.changeArray.push({ start: startValue, deleteCount: 1, childrenSize: [childSize] });
    }

    public clearChanges(): void {
        this.changeArray.splice(0);
    }
}

export function hookOverlayImpl(node: ArkCommonMethodComponent, value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions) : void {
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) !== (value_type)) {
        if (value instanceof ComponentContent) {
            const value_component = value as ComponentContent
            let frameNode = value_component.getFrameNode()
            if (frameNode === undefined || frameNode === null) {
                ArkUIAniModule._SetOverlay_ComponentContent(node.getPeer().getPeerPtr(), 0, options)
                return
            }
            let nodePtr = toPeerPtr(frameNode as FrameNode) as KPointer
            ArkUIAniModule._SetOverlay_ComponentContent(node.getPeer().getPeerPtr(), nodePtr, options)
            return
        }
    }
    const value_const = value as (string | CustomBuilder| undefined)
    OverlayOps.setOverlayAttribute(node.getPeer().getPeerPtr(), value_const, options)
}

export type CustomBuilderT<T> =
/** @memo */
(t: T) => void;

export interface ContentModifier<T> {
    applyContent(): WrappedBuilder<CustomBuilderT<T>>;
}

export interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
}

export class KeyEventTransfer {

    public static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            return new Object();
        }
        if (input === null) {
            return new Object();
        }
        let objectInternal: KeyEventInternal = new KeyEventInternal();
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('convertKeyEventPointer');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = bindFunc.invoke(esValue);
        let pointerConvertValue = convertResult.toNumber();

        let peer: KPointer = ArkUIAniModule._CreateKeyEventAccessorWithPointer(pointerConvertValue as long)
        objectInternal.peer!.ptr = peer;
        return objectInternal;
    }

    public static transferDynamic(input: Object): Any {
        if (input == null) {
            return new Object();
        }
        let objectInternal: KeyEventInternal = input as KeyEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._TransferKeyEventPointer(objectInternal.peer!.ptr as long);
        let retValue = ESValue.instantiateEmptyObject()
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapKeyEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        retValue.setProperty('type', TypeChecker.KeyType_ToNumeric(objectInternal.type));
        retValue.setProperty('keyCode', objectInternal.keyCode);
        retValue.setProperty('keyText', objectInternal.keyText);
        retValue.setProperty('keySource', TypeChecker.KeySource_ToNumeric(objectInternal.keySource));
        retValue.setProperty('deviceId', objectInternal.deviceId);
        retValue.setProperty('metaKey', objectInternal.metaKey);
        retValue.setProperty('unicode', objectInternal.unicode);
        retValue.setProperty('timestamp', objectInternal.timestamp);
        retValue.setProperty('intentionCode', objectInternal.intentionCode);
        return retValue;
    }
}

export class TouchTestInfoTransfer {
    public static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            return new Object();
        }
        if (input === null) {
            return new Object();
        }
        let touchTestInfo: TouchTestInfo = new TouchTestInfo();
        let esValue: ESValue = ESValue.wrap(input);
        touchTestInfo.windowX = esValue.getProperty("windowX").toNumber()
        touchTestInfo.windowY = esValue.getProperty("windowY").toNumber()
        touchTestInfo.parentX = esValue.getProperty("parentX").toNumber()
        touchTestInfo.parentY = esValue.getProperty("parentY").toNumber()
        touchTestInfo.x = esValue.getProperty("x").toNumber()
        touchTestInfo.y = esValue.getProperty("y").toNumber()
        let rect = esValue.getProperty("rect")
        touchTestInfo.rect = {
            x: rect.getProperty("x").toNumber(),
            y: rect.getProperty("y").toNumber(),
            width: rect.getProperty("width").toNumber(),
            height: rect.getProperty("height").toNumber()
        };
        touchTestInfo.id = esValue.getProperty("id").toString()
        return touchTestInfo;
    }

    public static transferDynamic(input: Object): Any {
        if (input == null) {
            return new Object();
        }
        let touchTestInfo: TouchTestInfo = input as TouchTestInfo;
        let retValue = ESValue.instantiateEmptyObject()
        retValue.setProperty('windowX', touchTestInfo.windowX);
        retValue.setProperty('windowY', touchTestInfo.windowY);
        retValue.setProperty('parentX', touchTestInfo.parentX);
        retValue.setProperty('parentY', touchTestInfo.parentY);
        retValue.setProperty('x', touchTestInfo.x);
        retValue.setProperty('y', touchTestInfo.y);
        let rect = ESValue.instantiateEmptyObject();
        rect.setProperty('x', touchTestInfo.rect.x);
        rect.setProperty('y', touchTestInfo.rect.y);
        rect.setProperty('width', touchTestInfo.rect.width);
        rect.setProperty('height', touchTestInfo.rect.height);
        retValue.setProperty('rect', rect);
        return retValue
    }
}

export class DragEventTransfer {
    public static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input)
        const global = ESValue.getGlobal()
        const wrapFunc = global.getProperty('getDragEventPointer')
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            throw Error("The wrapFunc is null, DragEvent transferDynamic fail")
        }
        let convertResult = wrapFunc.invoke(esValue)
        let ptr = convertResult.toNumber() as long
        let peer: KPointer = ArkUIAniModule._createDragEventAccessorWithPointer(ptr)
        return DragEventInternal.fromPtr(peer)
    }

    public static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let dragEvent: DragEventInternal = input as DragEventInternal
        const nativePointer: KPointer = ArkUIAniModule._getDragEventPointer(dragEvent.peer!.ptr)
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapDragEventPointer')
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        let result = wrapFunc.invoke(nativePointer)
        return result
    }
}

export class ClickEventTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const convertFunc = global.getProperty('convertEventPointer');
        if (convertFunc.isNull() || convertFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = convertFunc.invoke(esValue);
        let innerPointer = convertResult.toNumber();
        let peer: KPointer = ArkUIAniModule._createClickEventAccessorWithPointer(innerPointer as long)
        let clickEvent: ClickEventInternal = new ClickEventInternal();
        clickEvent.peer!.ptr = peer;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        clickEvent.target.area.width = widthValue;
        const heightValue = areaValue.getProperty("height").toNumber();
        clickEvent.target.area.height = heightValue;
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        clickEvent.target.area.position.x = positionXValue;
        const positionYValue = positionValue.getProperty("y").toNumber();
        clickEvent.target.area.position.y = positionYValue;
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        clickEvent.target.area.globalPosition.x = globalPositionXValue;
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        clickEvent.target.area.globalPosition.y = globalPositionYValue;
        const idValue = targetValue.getProperty("id");
        if (idValue.isUndefined()) {
            clickEvent.target.id = undefined;
        } else {
            clickEvent.target.id = idValue.toString();
        }
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        clickEvent.timestamp = timestampValue;
        const sourceValue = esValue.getProperty("source").toNumber();
        clickEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        clickEvent.axisVertical = axisVerticalValue;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        clickEvent.axisHorizontal = axisHorizontalValue;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        clickEvent.pressure = pressureValue;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        clickEvent.tiltX = tiltXValue;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        clickEvent.tiltY = tiltYValue;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        clickEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        clickEvent.deviceId = deviceIdValue;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        clickEvent.targetDisplayId = targetDisplayIdValue;
        const displayXValue = esValue.getProperty("displayX").toNumber();
        clickEvent.displayX = displayXValue;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        clickEvent.displayY = displayYValue;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        clickEvent.windowX = windowXValue;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        clickEvent.windowY = windowYValue;
        const xValue = esValue.getProperty("x").toNumber();
        clickEvent.x = xValue;
        const yValue = esValue.getProperty("y").toNumber();
        clickEvent.y = yValue;
        const handValue = esValue.getProperty("hand").toNumber();
        clickEvent.hand = TypeChecker.InteractionHand_FromNumeric(handValue as int32);
        return clickEvent;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let clickEvent: ClickEventInternal = input as ClickEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._getClickEventPointer(clickEvent.peer!.ptr);
        let retValue = ESValue.instantiateEmptyObject()
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapClickEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        let areaValue = ESValue.instantiateEmptyObject();
        areaValue.setProperty('width', clickEvent.target.area.width);
        areaValue.setProperty('height', clickEvent.target.area.height);
        let positionValue = ESValue.instantiateEmptyObject();
        positionValue.setProperty('x', clickEvent.target.area.position.x);
        positionValue.setProperty('y', clickEvent.target.area.position.y);
        areaValue.setProperty('position', positionValue);
        let globalPositionValue = ESValue.instantiateEmptyObject();
        globalPositionValue.setProperty('x', clickEvent.target.area.globalPosition.x);
        globalPositionValue.setProperty('y', clickEvent.target.area.globalPosition.y);
        areaValue.setProperty('globalPosition', globalPositionValue);
        let targetValue = ESValue.instantiateEmptyObject();
        targetValue.setProperty('area', areaValue);
        if (clickEvent.target.id !== undefined) {
            targetValue.setProperty('id', clickEvent.target.id);
        } else {
            targetValue.setProperty('id', ESValue.Undefined);
        }
        retValue.setProperty('target', targetValue);
        retValue.setProperty('timestamp', clickEvent.timestamp);
        retValue.setProperty('source', TypeChecker.SourceType_ToNumeric(clickEvent.source));
        retValue.setProperty('axisVertical', clickEvent.axisVertical);
        retValue.setProperty('axisHorizontal', clickEvent.axisHorizontal);
        retValue.setProperty('pressure', clickEvent.pressure);
        retValue.setProperty('tiltX', clickEvent.tiltX);
        retValue.setProperty('tiltY', clickEvent.tiltY);
        retValue.setProperty('sourceTool', TypeChecker.SourceTool_ToNumeric(clickEvent.sourceTool));
        retValue.setProperty('deviceId', clickEvent.deviceId);
        retValue.setProperty('targetDisplayId', clickEvent.targetDisplayId);
        retValue.setProperty('displayX', clickEvent.displayX);
        retValue.setProperty('displayY', clickEvent.displayY);
        retValue.setProperty('windowX', clickEvent.windowX);
        retValue.setProperty('windowY', clickEvent.windowY);
        retValue.setProperty('x', clickEvent.x);
        retValue.setProperty('y', clickEvent.y);
        retValue.setProperty('hand', TypeChecker.InteractionHand_ToNumeric(clickEvent.hand as InteractionHand));
        return retValue;
    }
}
export class HoverEventTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const convertFunc = global.getProperty('convertEventPointer');
        if (convertFunc.isNull() || convertFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = convertFunc.invoke(esValue);
        let innerPointer = convertResult.toNumber();
        let peer: KPointer = ArkUIAniModule._createHoverEventAccessorWithPointer(innerPointer as long)
        let hoverEvent: HoverEventInternal = new HoverEventInternal();
        hoverEvent.peer!.ptr = peer;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        hoverEvent.target.area.width = widthValue;
        const heightValue = areaValue.getProperty("height").toNumber();
        hoverEvent.target.area.height = heightValue;
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        hoverEvent.target.area.position.x = positionXValue;
        const positionYValue = positionValue.getProperty("y").toNumber();
        hoverEvent.target.area.position.y = positionYValue;
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        hoverEvent.target.area.globalPosition.x = globalPositionXValue;
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        hoverEvent.target.area.globalPosition.y = globalPositionYValue;
        const idValue = targetValue.getProperty("id");
        if (idValue.isUndefined()) {
            hoverEvent.target.id = undefined;
        } else {
            hoverEvent.target.id = idValue.toString();
        }
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        hoverEvent.timestamp = timestampValue;
        const sourceValue = esValue.getProperty("source").toNumber();
        hoverEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        hoverEvent.axisVertical = axisVerticalValue;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        hoverEvent.axisHorizontal = axisHorizontalValue;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        hoverEvent.pressure = pressureValue;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        hoverEvent.tiltX = tiltXValue;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        hoverEvent.tiltY = tiltYValue;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        hoverEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        hoverEvent.deviceId = deviceIdValue;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        hoverEvent.targetDisplayId = targetDisplayIdValue;
        const displayXValue = esValue.getProperty("displayX").toNumber();
        hoverEvent.displayX = displayXValue;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        hoverEvent.displayY = displayYValue;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        hoverEvent.windowX = windowXValue;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        hoverEvent.windowY = windowYValue;
        const xValue = esValue.getProperty("x").toNumber();
        hoverEvent.x = xValue;
        const yValue = esValue.getProperty("y").toNumber();
        hoverEvent.y = yValue;
        return hoverEvent;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let hoverEvent: HoverEventInternal = input as HoverEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._getHoverEventPointer(hoverEvent.peer!.ptr);
        let retValue = ESValue.instantiateEmptyObject()
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapHoverEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        let areaValue = ESValue.instantiateEmptyObject();
        areaValue.setProperty('width', hoverEvent.target.area.width);
        areaValue.setProperty('height', hoverEvent.target.area.height);
        let positionValue = ESValue.instantiateEmptyObject();
        positionValue.setProperty('x', hoverEvent.target.area.position.x);
        positionValue.setProperty('y', hoverEvent.target.area.position.y);
        areaValue.setProperty('position', positionValue);
        let globalPositionValue = ESValue.instantiateEmptyObject();
        globalPositionValue.setProperty('x', hoverEvent.target.area.globalPosition.x);
        globalPositionValue.setProperty('y', hoverEvent.target.area.globalPosition.y);
        areaValue.setProperty('globalPosition', globalPositionValue);
        let targetValue = ESValue.instantiateEmptyObject();
        targetValue.setProperty('area', areaValue);
        if (hoverEvent.target.id !== undefined) {
            targetValue.setProperty('id', hoverEvent.target.id);
        } else {
            targetValue.setProperty('id', ESValue.Undefined);
        }
        retValue.setProperty('target', targetValue);
        retValue.setProperty('timestamp', hoverEvent.timestamp);
        retValue.setProperty('source', TypeChecker.SourceType_ToNumeric(hoverEvent.source));
        retValue.setProperty('axisVertical', hoverEvent.axisVertical);
        retValue.setProperty('axisHorizontal', hoverEvent.axisHorizontal);
        retValue.setProperty('pressure', hoverEvent.pressure);
        retValue.setProperty('tiltX', hoverEvent.tiltX);
        retValue.setProperty('tiltY', hoverEvent.tiltY);
        retValue.setProperty('sourceTool', TypeChecker.SourceTool_ToNumeric(hoverEvent.sourceTool));
        retValue.setProperty('deviceId', hoverEvent.deviceId);
        retValue.setProperty('targetDisplayId', hoverEvent.targetDisplayId);
        retValue.setProperty('displayX', hoverEvent.displayX);
        retValue.setProperty('displayY', hoverEvent.displayY);
        retValue.setProperty('windowX', hoverEvent.windowX);
        retValue.setProperty('windowY', hoverEvent.windowY);
        retValue.setProperty('x', hoverEvent.x);
        retValue.setProperty('y', hoverEvent.y);
        return retValue;
    }
}
export class MouseEventTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const convertFunc = global.getProperty('convertEventPointer');
        if (convertFunc.isNull() || convertFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = convertFunc.invoke(esValue);
        let innerPointer = convertResult.toNumber();
        let peer: KPointer = ArkUIAniModule._createMouseEventAccessorWithPointer(innerPointer as long)
        let mouseEvent: MouseEventInternal = new MouseEventInternal();
        mouseEvent.peer!.ptr = peer;
        const buttonValue = esValue.getProperty("button").toNumber();
        mouseEvent.button = TypeChecker.MouseButton_FromNumeric(buttonValue as int32);
        const actionValue = esValue.getProperty("action").toNumber();
        mouseEvent.action = TypeChecker.MouseAction_FromNumeric(actionValue as int32);
        const displayXValue = esValue.getProperty("displayX").toNumber();
        mouseEvent.displayX = displayXValue;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        mouseEvent.displayY = displayYValue;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        mouseEvent.windowX = windowXValue;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        mouseEvent.windowY = windowYValue;
        const xValue = esValue.getProperty("x").toNumber();
        mouseEvent.x = xValue;
        const yValue = esValue.getProperty("y").toNumber();
        mouseEvent.y = yValue;
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        mouseEvent.timestamp = timestampValue;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        mouseEvent.deviceId = deviceIdValue;
        const sourceValue = esValue.getProperty("source").toNumber();
        mouseEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const pressureValue = esValue.getProperty("pressure").toNumber();
        mouseEvent.pressure = pressureValue;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        mouseEvent.tiltX = tiltXValue;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        mouseEvent.tiltY = tiltYValue;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        mouseEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        mouseEvent.axisVertical = axisVerticalValue;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        mouseEvent.axisHorizontal = axisHorizontalValue;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        mouseEvent.targetDisplayId = targetDisplayIdValue;
        const rawDeltaXValue = esValue.getProperty("rawDeltaX").toNumber();
        mouseEvent.rawDeltaX = rawDeltaXValue;
        const rawDeltaYValue = esValue.getProperty("rawDeltaY").toNumber();
        mouseEvent.rawDeltaY = rawDeltaYValue;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        mouseEvent.target.area.width = widthValue;
        const heightValue = areaValue.getProperty("height").toNumber();
        mouseEvent.target.area.height = heightValue;
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        mouseEvent.target.area.position.x = positionXValue;
        const positionYValue = positionValue.getProperty("y").toNumber();
        mouseEvent.target.area.position.y = positionYValue;
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        mouseEvent.target.area.globalPosition.x = globalPositionXValue;
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        mouseEvent.target.area.globalPosition.y = globalPositionYValue;
        const idValue = targetValue.getProperty("id");
        if (idValue.isUndefined()) {
            mouseEvent.target.id = undefined;
        } else {
            mouseEvent.target.id = idValue.toString();
        }
        const pressedButtonsValue = esValue.getProperty("pressedButtons");
        for (let button of pressedButtonsValue) {
            mouseEvent.pressedButtons?.push(TypeChecker.MouseButton_FromNumeric(button.invokeMethod("valueOf").toNumber() as int32))
        }
        return mouseEvent;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let mouseEvent: MouseEventInternal = input as MouseEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._getMouseEventPointer(mouseEvent.peer!.ptr);
        let retValue = ESValue.instantiateEmptyObject()
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapMouseEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        retValue.setProperty('button', TypeChecker.MouseButton_ToNumeric(mouseEvent.button));
        retValue.setProperty('action', TypeChecker.MouseAction_ToNumeric(mouseEvent.action));
        retValue.setProperty('displayX', mouseEvent.displayX);
        retValue.setProperty('displayY', mouseEvent.displayY);
        retValue.setProperty('windowX', mouseEvent.windowX);
        retValue.setProperty('windowY', mouseEvent.windowY);
        retValue.setProperty('x', mouseEvent.x);
        retValue.setProperty('y', mouseEvent.y);
        retValue.setProperty('timestamp', mouseEvent.timestamp);
        retValue.setProperty('deviceId', mouseEvent.deviceId);
        retValue.setProperty('source', TypeChecker.SourceType_ToNumeric(mouseEvent.source));
        retValue.setProperty('pressure', mouseEvent.pressure);
        retValue.setProperty('tiltX', mouseEvent.tiltX);
        retValue.setProperty('tiltY', mouseEvent.tiltY);
        retValue.setProperty('sourceTool', TypeChecker.SourceTool_ToNumeric(mouseEvent.sourceTool));
        retValue.setProperty('axisVertical', mouseEvent.axisVertical);
        retValue.setProperty('axisHorizontal', mouseEvent.axisHorizontal);
        let areaValue = ESValue.instantiateEmptyObject();
        areaValue.setProperty('width', mouseEvent.target.area.width);
        areaValue.setProperty('height', mouseEvent.target.area.height);
        let positionValue = ESValue.instantiateEmptyObject();
        positionValue.setProperty('x', mouseEvent.target.area.position.x);
        positionValue.setProperty('y', mouseEvent.target.area.position.y);
        areaValue.setProperty('position', positionValue);
        let globalPositionValue = ESValue.instantiateEmptyObject();
        globalPositionValue.setProperty('x', mouseEvent.target.area.globalPosition.x);
        globalPositionValue.setProperty('y', mouseEvent.target.area.globalPosition.y);
        areaValue.setProperty('globalPosition', globalPositionValue);
        let targetValue = ESValue.instantiateEmptyObject();
        targetValue.setProperty('area', areaValue);
        if (mouseEvent.target.id !== undefined) {
            targetValue.setProperty('id', mouseEvent.target.id);
        } else {
            targetValue.setProperty('id', ESValue.Undefined);
        }
        retValue.setProperty('target', targetValue);
        retValue.setProperty('targetDisplayId', mouseEvent.targetDisplayId);
        retValue.setProperty('rawDeltaX', mouseEvent.rawDeltaX);
        retValue.setProperty('rawDeltaY', mouseEvent.rawDeltaY);
        retValue.setProperty('pressedButtons', mouseEvent.pressedButtons);
        return retValue;
    }
}
export class TouchEventTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const convertFunc = global.getProperty('convertEventPointer');
        if (convertFunc.isNull() || convertFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = convertFunc.invoke(esValue);
        let innerPointer = convertResult.toNumber();
        let peer: KPointer = ArkUIAniModule._createTouchEventAccessorWithPointer(innerPointer as long)
        let touchEvent: TouchEventInternal = new TouchEventInternal();
        touchEvent.peer!.ptr = peer;
        const sourceValue = esValue.getProperty("source").toNumber();
        touchEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        touchEvent.timestamp = timestampValue;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        touchEvent.target.area.width = widthValue;
        const heightValue = areaValue.getProperty("height").toNumber();
        touchEvent.target.area.height = heightValue;
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        touchEvent.target.area.position.x = positionXValue;
        const positionYValue = positionValue.getProperty("y").toNumber();
        touchEvent.target.area.position.y = positionYValue;
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        touchEvent.target.area.globalPosition.x = globalPositionXValue;
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        touchEvent.target.area.globalPosition.y = globalPositionYValue;
        const idValue = targetValue.getProperty("id");
        if (idValue.isUndefined()) {
            touchEvent.target.id = undefined;
        } else {
            touchEvent.target.id = idValue.toString();
        }
        const pressureValue = esValue.getProperty("pressure").toNumber();
        touchEvent.pressure = pressureValue;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        touchEvent.deviceId = deviceIdValue;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        touchEvent.tiltX = tiltXValue;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        touchEvent.tiltY = tiltYValue;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        touchEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        touchEvent.axisVertical = axisVerticalValue;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        touchEvent.axisHorizontal = axisHorizontalValue;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        touchEvent.targetDisplayId = targetDisplayIdValue;
        const typeValue = esValue.getProperty("type").toNumber();
        touchEvent.type = TypeChecker.TouchType_FromNumeric(typeValue as int32);
        const changedTouchesValue = esValue.getProperty("changedTouches");
        let changedTouchArray: Array<TouchObject> = [];
        let index: number = 0;
        for (let changedTouch of changedTouchesValue) {
            let staticChangedTouch: TouchObject = {
                type: TypeChecker.TouchType_FromNumeric(changedTouch.getProperty("type").toNumber() as int32),
                id: changedTouch.getProperty("id").toNumber(),
                displayX: changedTouch.getProperty("displayX").toNumber(),
                displayY: changedTouch.getProperty("displayY").toNumber(),
                windowX: changedTouch.getProperty("windowX").toNumber(),
                windowY: changedTouch.getProperty("windowY").toNumber(),
                x: changedTouch.getProperty("x").toNumber(),
                y: changedTouch.getProperty("y").toNumber(),
                hand: TypeChecker.InteractionHand_FromNumeric(changedTouch.getProperty("hand").toNumber() as int32),
                pressedTime: touchEvent.changedTouches[index].pressedTime,
                pressure: changedTouch.getProperty("pressure").toNumber(),
                width: changedTouch.getProperty("width").toNumber(),
                height: changedTouch.getProperty("height").toNumber(),
                // Note: according to spec 7.5.2, Properties of a non-optional type cannot be skipped in an object literal, 
                // despite some property types having default values
                screenX: 0,
                screenY: 0
            };
            index++;
            changedTouchArray.push(staticChangedTouch)
        }
        touchEvent.changedTouches = changedTouchArray;
        const touchesValue = esValue.getProperty("touches");
        let touchesArray: Array<TouchObject> = [];
        index = 0;
        for (let touch of touchesValue) {
            let staticTouch: TouchObject = {
                type: TypeChecker.TouchType_FromNumeric(touch.getProperty("type").toNumber() as int32),
                id: touch.getProperty("id").toNumber(),
                displayX: touch.getProperty("displayX").toNumber(),
                displayY: touch.getProperty("displayY").toNumber(),
                windowX: touch.getProperty("windowX").toNumber(),
                windowY: touch.getProperty("windowY").toNumber(),
                x: touch.getProperty("x").toNumber(),
                y: touch.getProperty("y").toNumber(),
                hand: TypeChecker.InteractionHand_FromNumeric(touch.getProperty("hand").toNumber() as int32),
                pressedTime: touchEvent.touches[index].pressedTime,
                pressure: touch.getProperty("pressure").toNumber(),
                width: touch.getProperty("width").toNumber(),
                height: touch.getProperty("height").toNumber(),
                // Note: according to spec 7.5.2, Properties of a non-optional type cannot be skipped in an object literal,
                // despite some property types having default values
                screenX: 0,
                screenY: 0
            };
            index++;
            touchesArray.push(staticTouch)
        }
        touchEvent.touches = touchesArray;
        return touchEvent;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let touchEvent: TouchEventInternal = input as TouchEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._getTouchEventPointer(touchEvent.peer!.ptr);
        let retValue = ESValue.instantiateEmptyObject();
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapTouchEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        retValue.setProperty('source', TypeChecker.SourceType_ToNumeric(touchEvent.source));
        retValue.setProperty('timestamp', touchEvent.timestamp);
        let areaValue = ESValue.instantiateEmptyObject();
        areaValue.setProperty('width', touchEvent.target.area.width);
        areaValue.setProperty('height', touchEvent.target.area.height);
        let positionValue = ESValue.instantiateEmptyObject();
        positionValue.setProperty('x', touchEvent.target.area.position.x);
        positionValue.setProperty('y', touchEvent.target.area.position.y);
        areaValue.setProperty('position', positionValue);
        let globalPositionValue = ESValue.instantiateEmptyObject();
        globalPositionValue.setProperty('x', touchEvent.target.area.globalPosition.x);
        globalPositionValue.setProperty('y', touchEvent.target.area.globalPosition.y);
        areaValue.setProperty('globalPosition', globalPositionValue);
        let targetValue = ESValue.instantiateEmptyObject();
        targetValue.setProperty('area', areaValue);
        if (touchEvent.target.id !== undefined) {
            targetValue.setProperty('id', touchEvent.target.id);
        } else {
            targetValue.setProperty('id', ESValue.Undefined);
        }
        retValue.setProperty('target', targetValue);
        retValue.setProperty('pressure', touchEvent.pressure);
        retValue.setProperty('deviceId', touchEvent.deviceId);
        retValue.setProperty('tiltX', touchEvent.tiltX);
        retValue.setProperty('tiltY', touchEvent.tiltY);
        retValue.setProperty('sourceTool', TypeChecker.SourceTool_ToNumeric(touchEvent.sourceTool));
        retValue.setProperty('axisVertical', touchEvent.axisVertical);
        retValue.setProperty('axisHorizontal', touchEvent.axisHorizontal);
        retValue.setProperty('targetDisplayId', touchEvent.targetDisplayId);
        retValue.setProperty('type', TypeChecker.TouchType_ToNumeric(touchEvent.type));
        let touchesArray = touchEvent.touches;
        let touchesValue = ESValue.instantiateEmptyArray();
        for (let index = 0; index < touchesArray.length; index++) {
            let touchItemValue = ESValue.instantiateEmptyObject();
            touchItemValue.setProperty('type', TypeChecker.TouchType_ToNumeric(touchesArray[index].type));
            touchItemValue.setProperty('id', touchesArray[index].id);
            touchItemValue.setProperty('displayX', touchesArray[index].displayX);
            touchItemValue.setProperty('displayY', touchesArray[index].displayY);
            touchItemValue.setProperty('windowX', touchesArray[index].windowX);
            touchItemValue.setProperty('windowY', touchesArray[index].windowY);
            touchItemValue.setProperty('x', touchesArray[index].x);
            touchItemValue.setProperty('y', touchesArray[index].y);
            touchItemValue.setProperty('hand', TypeChecker.InteractionHand_ToNumeric(touchesArray[index].hand as InteractionHand));
            touchItemValue.setProperty('pressedTime', touchesArray[index].pressedTime);
            touchItemValue.setProperty('pressure', touchesArray[index].pressure);
            touchItemValue.setProperty('width', touchesArray[index].width);
            touchItemValue.setProperty('height', touchesArray[index].height);
            touchesValue.setProperty(index, touchItemValue);
        }
        retValue.setProperty('touches', touchesValue);
        let changedTouchesArray = touchEvent.changedTouches;
        let changedTouchesValue = ESValue.instantiateEmptyArray();
        for (let index = 0; index < changedTouchesArray.length; index++) {
            let touchItemValue = ESValue.instantiateEmptyObject();
            touchItemValue.setProperty('type', TypeChecker.TouchType_ToNumeric(changedTouchesArray[index].type));
            touchItemValue.setProperty('id', changedTouchesArray[index].id);
            touchItemValue.setProperty('displayX', changedTouchesArray[index].displayX);
            touchItemValue.setProperty('displayY', changedTouchesArray[index].displayY);
            touchItemValue.setProperty('windowX', changedTouchesArray[index].windowX);
            touchItemValue.setProperty('windowY', changedTouchesArray[index].windowY);
            touchItemValue.setProperty('x', changedTouchesArray[index].x);
            touchItemValue.setProperty('y', changedTouchesArray[index].y);
            touchItemValue.setProperty('hand', TypeChecker.InteractionHand_ToNumeric(changedTouchesArray[index].hand as InteractionHand));
            touchItemValue.setProperty('pressedTime', changedTouchesArray[index].pressedTime);
            touchItemValue.setProperty('pressure', changedTouchesArray[index].pressure);
            touchItemValue.setProperty('width', changedTouchesArray[index].width);
            touchItemValue.setProperty('height', changedTouchesArray[index].height);
            changedTouchesValue.setProperty(index, touchItemValue);
        }
        retValue.setProperty('changedTouches', changedTouchesValue);
        return retValue;
    }
}
export class AxisEventTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object' || input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const convertFunc = global.getProperty('convertEventPointer');
        if (convertFunc.isNull() || convertFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = convertFunc.invoke(esValue);
        let innerPointer = convertResult.toNumber();
        let peer: KPointer = ArkUIAniModule._createAxisEventAccessorWithPointer(innerPointer as long)
        let axisEvent: AxisEventInternal = new AxisEventInternal();
        axisEvent.peer!.ptr = peer;
        const sourceValue = esValue.getProperty("source").toNumber();
        axisEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        axisEvent.timestamp = timestampValue;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        axisEvent.target.area.width = widthValue;
        const heightValue = areaValue.getProperty("height").toNumber();
        axisEvent.target.area.height = heightValue;
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        axisEvent.target.area.position.x = positionXValue;
        const positionYValue = positionValue.getProperty("y").toNumber();
        axisEvent.target.area.position.y = positionYValue;
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        axisEvent.target.area.globalPosition.x = globalPositionXValue;
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        axisEvent.target.area.globalPosition.y = globalPositionYValue;
        const idValue = targetValue.getProperty("id");
        if (idValue.isUndefined()) {
            axisEvent.target.id = undefined;
        } else {
            axisEvent.target.id = idValue.toString();
        }
        const pressureValue = esValue.getProperty("pressure").toNumber();
        axisEvent.pressure = pressureValue;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        axisEvent.deviceId = deviceIdValue;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        axisEvent.tiltX = tiltXValue;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        axisEvent.tiltY = tiltYValue;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        axisEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        axisEvent.axisVertical = axisVerticalValue;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        axisEvent.axisHorizontal = axisHorizontalValue;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        axisEvent.targetDisplayId = targetDisplayIdValue;
        const actionValue = esValue.getProperty("action").toNumber();
        axisEvent.action = TypeChecker.AxisAction_FromNumeric(actionValue as int32);
        const displayXValue = esValue.getProperty("displayX").toNumber();
        axisEvent.displayX = displayXValue;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        axisEvent.displayY = displayYValue;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        axisEvent.windowX = windowXValue;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        axisEvent.windowY = windowYValue;
        const xValue = esValue.getProperty("x").toNumber();
        axisEvent.x = xValue;
        const yValue = esValue.getProperty("y").toNumber();
        axisEvent.y = yValue;
        const scrollStepValue = esValue.getProperty("scrollStep").toNumber();
        axisEvent.scrollStep = scrollStepValue;
        return axisEvent;
    }
    static transferDynamic(input: Object): Any {
        if (input === null) {
            return new Object();
        }
        let axisEvent: AxisEventInternal = input as AxisEventInternal;
        const nativePointer: KPointer = ArkUIAniModule._getAxisEventPointer(axisEvent.peer!.ptr);
        let retValue = ESValue.instantiateEmptyObject()
        const global = ESValue.getGlobal();
        const wrapFunc = global.getProperty('wrapAxisEventPointer');
        if (wrapFunc.isNull() || wrapFunc.isUndefined()) {
            return new Object();
        }
        wrapFunc.invoke(retValue, nativePointer);
        retValue.setProperty('source', TypeChecker.SourceType_ToNumeric(axisEvent.source));
        retValue.setProperty('timestamp', axisEvent.timestamp);
        let areaValue = ESValue.instantiateEmptyObject();
        areaValue.setProperty('width', axisEvent.target.area.width);
        areaValue.setProperty('height', axisEvent.target.area.height);
        let positionValue = ESValue.instantiateEmptyObject();
        positionValue.setProperty('x', axisEvent.target.area.position.x);
        positionValue.setProperty('y', axisEvent.target.area.position.y);
        areaValue.setProperty('position', positionValue);
        let globalPositionValue = ESValue.instantiateEmptyObject();
        globalPositionValue.setProperty('x', axisEvent.target.area.globalPosition.x);
        globalPositionValue.setProperty('y', axisEvent.target.area.globalPosition.y);
        areaValue.setProperty('globalPosition', globalPositionValue);
        let targetValue = ESValue.instantiateEmptyObject();
        targetValue.setProperty('area', areaValue);
        if (axisEvent.target.id !== undefined) {
            targetValue.setProperty('id', axisEvent.target.id);
        } else {
            targetValue.setProperty('id', ESValue.Undefined);
        }
        retValue.setProperty('target', targetValue);
        retValue.setProperty('pressure', axisEvent.pressure);
        retValue.setProperty('deviceId', axisEvent.deviceId);
        retValue.setProperty('tiltX', axisEvent.tiltX);
        retValue.setProperty('tiltY', axisEvent.tiltY);
        retValue.setProperty('sourceTool', TypeChecker.SourceTool_ToNumeric(axisEvent.sourceTool));
        retValue.setProperty('axisVertical', axisEvent.axisVertical);
        retValue.setProperty('axisHorizontal', axisEvent.axisHorizontal);
        retValue.setProperty('targetDisplayId', axisEvent.targetDisplayId);
        retValue.setProperty('action', TypeChecker.AxisAction_ToNumeric(axisEvent.action));
        retValue.setProperty('displayX', axisEvent.displayX);
        retValue.setProperty('displayY', axisEvent.displayY);
        retValue.setProperty('windowX', axisEvent.windowX);
        retValue.setProperty('windowY', axisEvent.windowY);
        retValue.setProperty('x', axisEvent.x);
        retValue.setProperty('y', axisEvent.y);
        retValue.setProperty('scrollStep', axisEvent.scrollStep);
        return retValue;
    }
}