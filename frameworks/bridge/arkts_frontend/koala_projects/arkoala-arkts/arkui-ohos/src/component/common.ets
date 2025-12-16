// this file will be merged with component/xxx.ets by compiler pre-process script

import { PeerNode } from "../PeerNode.ets"
import { WrappedBuilder, CustomBuilderT } from "./builder"
import { GestureGroupHandler, GestureHandler, GesturePriority } from "./gesture"
import { GestureOps } from "./idlize"
import { ArkUIAniModule } from "arkui.ani"
import { DrawContext } from "arkui.Graphics"
import { Bindable, Callback } from "#generated"

export interface AttributeModifier<T> {
    applyNormalAttribute(instance: T): void {}
    applyPressedAttribute(instance: T): void {}
    applyFocusedAttribute(instance: T): void {}
    applyDisabledAttribute(instance: T): void {}
    applySelectedAttribute(instance: T): void {}
    monitoredStates(): int32 { return 0; }
}

export interface AnimatableArithmetic<T> {
    plus(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    subtract(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    multiply(scale:double): AnimatableArithmetic<T>;
    equals(rhs:AnimatableArithmetic<T>): boolean;
}

export interface ContentModifier<T = void> {
  applyContent(): WrappedBuilder<CustomBuilderT<T>>
}

export class DrawModifier {
    weakRefOfPeerNode?: WeakRef<PeerNode>;
    public drawBehind(drawContext: DrawContext): void { }

    public drawContent(drawContext: DrawContext): void { }

    public drawFront(drawContext: DrawContext): void { }

    public drawForeground(drawContext: DrawContext): void { }
    
    public drawOverlay(drawContext: DrawContext): void { }

    public invalidate(): void {
        let peerNode: PeerNode | undefined = this.weakRefOfPeerNode?.deref();
        if (peerNode && peerNode.peer.ptr) {
            ArkUIAniModule._Invalidate(peerNode.peer.ptr)
        }
    }
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

export type CustomStyles =  (instance: CommonMethod) => void;

export interface GestureModifier {
    applyGesture(event: UIGestureEvent): void
}

export function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T {
    customStyles(this);
    return this;
}

export class TouchTestInfo {
    windowX: double;
    windowY: double;
    parentX: double;
    parentY: double;
    x: double;
    y: double;
    rect: RectResult;
    id: string;
    constructor() {
        this.windowX = 0;
        this.windowY = 0;
        this.parentX = 0;
        this.parentY = 0;
        this.x = 0;
        this.y = 0;
        this.rect = { x: 0, y: 0, width: 0, height: 0 };
        this.id = "";
    }
}
export class TouchResult {
    strategy: TouchTestStrategy;
    id?: string;
    constructor() {
        this.strategy = TouchTestStrategy.DEFAULT;
    }
}
export class KeyEventTransfer {

    public static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            return new Object();
        }
        if (input === null) {
            return new Object();
        }
        let esValue: ESValue = ESValue.wrap(input);
        const global = ESValue.getGlobal();
        const bindFunc = global.getProperty('convertKeyEventPointer');
        if (bindFunc.isNull() || bindFunc.isUndefined()) {
            return new Object();
        }
        let convertResult = bindFunc.invoke(esValue);
        let pointerConvertValue = convertResult.toNumber();

        let peer: KPointer = ArkUIAniModule._CreateKeyEventAccessorWithPointer(pointerConvertValue as long)
        return KeyEventInternal.fromPtr(peer);
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
        retValue.setProperty('intentionCode', TypeChecker.IntentionCode_ToNumeric(objectInternal.intentionCode));
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
        retValue.setProperty('id', touchTestInfo.id);
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
        let clickEvent = ClickEventInternal.fromPtr(peer);
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        const heightValue = areaValue.getProperty("height").toNumber();
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        const positionYValue = positionValue.getProperty("y").toNumber();
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        const idValue = targetValue.getProperty("id");
        const target: EventTarget = {
            area: {
                width: widthValue,
                height: heightValue,
                position: {
                    x: positionXValue,
                    y: positionYValue
                },
                globalPosition: {
                    x: globalPositionXValue,
                    y: globalPositionYValue
                }
            },
            id: idValue.isUndefined() ? undefined : idValue.toString()
        };
        clickEvent.target = target;
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        clickEvent.timestamp = timestampValue as int64;
        const sourceValue = esValue.getProperty("source").toNumber();
        clickEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        clickEvent.axisVertical = axisVerticalValue as double;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        clickEvent.axisHorizontal = axisHorizontalValue as double;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        clickEvent.pressure = pressureValue as double;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        clickEvent.tiltX = tiltXValue as double;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        clickEvent.tiltY = tiltYValue as double;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        clickEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        clickEvent.deviceId = deviceIdValue as int32;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        clickEvent.targetDisplayId = targetDisplayIdValue as int32;
        const displayXValue = esValue.getProperty("displayX").toNumber();
        clickEvent.displayX = displayXValue as double;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        clickEvent.displayY = displayYValue as double;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        clickEvent.windowX = windowXValue as double;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        clickEvent.windowY = windowYValue as double;
        const xValue = esValue.getProperty("x").toNumber();
        clickEvent.x = xValue as double;
        const yValue = esValue.getProperty("y").toNumber();
        clickEvent.y = yValue as double;
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
        let hoverEvent = HoverEventInternal.fromPtr(peer);
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        const heightValue = areaValue.getProperty("height").toNumber();
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        const positionYValue = positionValue.getProperty("y").toNumber();
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        const idValue = targetValue.getProperty("id");
        const target: EventTarget = {
            area: {
                width: widthValue,
                height: heightValue,
                position: {
                    x: positionXValue,
                    y: positionYValue
                },
                globalPosition: {
                    x: globalPositionXValue,
                    y: globalPositionYValue
                }
            },
            id: idValue.isUndefined() ? undefined : idValue.toString()
        };
        hoverEvent.target = target;
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        hoverEvent.timestamp = timestampValue as int64;
        const sourceValue = esValue.getProperty("source").toNumber();
        hoverEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        hoverEvent.axisVertical = axisVerticalValue as double;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        hoverEvent.axisHorizontal = axisHorizontalValue as double;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        hoverEvent.pressure = pressureValue as double;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        hoverEvent.tiltX = tiltXValue as double;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        hoverEvent.tiltY = tiltYValue as double;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        hoverEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        hoverEvent.deviceId = deviceIdValue as int32;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        hoverEvent.targetDisplayId = targetDisplayIdValue as int32;
        const displayXValue = esValue.getProperty("displayX").toNumber();
        hoverEvent.displayX = displayXValue as double;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        hoverEvent.displayY = displayYValue as double;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        hoverEvent.windowX = windowXValue as double;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        hoverEvent.windowY = windowYValue as double;
        const xValue = esValue.getProperty("x").toNumber();
        hoverEvent.x = xValue as double;
        const yValue = esValue.getProperty("y").toNumber();
        hoverEvent.y = yValue as double;
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
        let mouseEvent = MouseEventInternal.fromPtr(peer);
        const buttonValue = esValue.getProperty("button").toNumber();
        mouseEvent.button = TypeChecker.MouseButton_FromNumeric(buttonValue as int32);
        const actionValue = esValue.getProperty("action").toNumber();
        mouseEvent.action = TypeChecker.MouseAction_FromNumeric(actionValue as int32);
        const displayXValue = esValue.getProperty("displayX").toNumber();
        mouseEvent.displayX = displayXValue as double;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        mouseEvent.displayY = displayYValue as double;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        mouseEvent.windowX = windowXValue as double;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        mouseEvent.windowY = windowYValue as double;
        const xValue = esValue.getProperty("x").toNumber();
        mouseEvent.x = xValue as double;
        const yValue = esValue.getProperty("y").toNumber();
        mouseEvent.y = yValue as double;
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        mouseEvent.timestamp = timestampValue as int64;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        mouseEvent.deviceId = deviceIdValue as int32;
        const sourceValue = esValue.getProperty("source").toNumber();
        mouseEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const pressureValue = esValue.getProperty("pressure").toNumber();
        mouseEvent.pressure = pressureValue as double;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        mouseEvent.tiltX = tiltXValue as double;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        mouseEvent.tiltY = tiltYValue as double;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        mouseEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        mouseEvent.axisVertical = axisVerticalValue as double;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        mouseEvent.axisHorizontal = axisHorizontalValue as double;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        mouseEvent.targetDisplayId = targetDisplayIdValue as int32;
        const rawDeltaXValue = esValue.getProperty("rawDeltaX").toNumber();
        mouseEvent.rawDeltaX = rawDeltaXValue as double;
        const rawDeltaYValue = esValue.getProperty("rawDeltaY").toNumber();
        mouseEvent.rawDeltaY = rawDeltaYValue as double;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        const heightValue = areaValue.getProperty("height").toNumber();
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        const positionYValue = positionValue.getProperty("y").toNumber();
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        const idValue = targetValue.getProperty("id");
        const target: EventTarget = {
            area: {
                width: widthValue,
                height: heightValue,
                position: {
                    x: positionXValue,
                    y: positionYValue
                },
                globalPosition: {
                    x: globalPositionXValue,
                    y: globalPositionYValue
                }
            },
            id: idValue.isUndefined() ? undefined : idValue.toString()
        };
        mouseEvent.target = target;
        const pressedButtonsValue = esValue.getProperty("pressedButtons");
        for (let button of pressedButtonsValue) {
            mouseEvent.pressedButtons?.push(TypeChecker.MouseButton_FromNumeric(button.toNumber() as int32))
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

        if (mouseEvent.pressedButtons !== undefined) {
            let pressedButtonsArray = mouseEvent!.pressedButtons as Array<MouseButton>;
            let pressedButtonsValue = ESValue.instantiateEmptyArray();
            for (let index = 0; index < pressedButtonsArray.length; index++) {
                pressedButtonsValue.setProperty(index, TypeChecker.MouseButton_ToNumeric(pressedButtonsArray[index]));
            }
            retValue.setProperty('pressedButtons', pressedButtonsValue);
        }

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
        let touchEvent = TouchEventInternal.fromPtr(peer);
        const sourceValue = esValue.getProperty("source").toNumber();
        touchEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        touchEvent.timestamp = timestampValue as int64;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        const heightValue = areaValue.getProperty("height").toNumber();
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        const positionYValue = positionValue.getProperty("y").toNumber();
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        const idValue = targetValue.getProperty("id");
        const target: EventTarget = {
            area: {
                width: widthValue,
                height: heightValue,
                position: {
                    x: positionXValue,
                    y: positionYValue
                },
                globalPosition: {
                    x: globalPositionXValue,
                    y: globalPositionYValue
                }
            },
            id: idValue.isUndefined() ? undefined : idValue.toString()
        };
        touchEvent.target = target;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        touchEvent.pressure = pressureValue as double;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        touchEvent.deviceId = deviceIdValue as int32;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        touchEvent.tiltX = tiltXValue as double;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        touchEvent.tiltY = tiltYValue as double;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        touchEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        touchEvent.axisVertical = axisVerticalValue as double;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        touchEvent.axisHorizontal = axisHorizontalValue as double;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        touchEvent.targetDisplayId = targetDisplayIdValue as int32;
        const typeValue = esValue.getProperty("type").toNumber();
        touchEvent.type = TypeChecker.TouchType_FromNumeric(typeValue as int32);
        const changedTouchesValue = esValue.getProperty("changedTouches");
        let changedTouchArray: Array<TouchObject> = [];
        let index = 0;
        for (let changedTouch of changedTouchesValue) {
            let staticChangedTouch: TouchObject = {
                type: TypeChecker.TouchType_FromNumeric(changedTouch.getProperty("type").toNumber() as int32),
                id: changedTouch.getProperty("id").toNumber() as int32,
                displayX: changedTouch.getProperty("displayX").toNumber() as double,
                displayY: changedTouch.getProperty("displayY").toNumber() as double,
                windowX: changedTouch.getProperty("windowX").toNumber() as double,
                windowY: changedTouch.getProperty("windowY").toNumber() as double,
                x: changedTouch.getProperty("x").toNumber() as double,
                y: changedTouch.getProperty("y").toNumber() as double,
                hand: TypeChecker.InteractionHand_FromNumeric(changedTouch.getProperty("hand").toNumber() as int32),
                pressedTime: changedTouch.getProperty("pressedTime").toNumber() as int64,
                pressure: changedTouch.getProperty("pressure").toNumber() as double,
                width: changedTouch.getProperty("width").toNumber() as double,
                height: changedTouch.getProperty("height").toNumber() as double,
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
                id: touch.getProperty("id").toNumber() as int32,
                displayX: touch.getProperty("displayX").toNumber() as double,
                displayY: touch.getProperty("displayY").toNumber() as double,
                windowX: touch.getProperty("windowX").toNumber() as double,
                windowY: touch.getProperty("windowY").toNumber() as double,
                x: touch.getProperty("x").toNumber() as double,
                y: touch.getProperty("y").toNumber() as double,
                hand: TypeChecker.InteractionHand_FromNumeric(touch.getProperty("hand").toNumber() as int32),
                pressedTime: touch.getProperty("pressedTime").toNumber() as int64,
                pressure: touch.getProperty("pressure").toNumber() as double,
                width: touch.getProperty("width").toNumber() as double,
                height: touch.getProperty("height").toNumber() as double,
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
        let axisEvent = AxisEventInternal.fromPtr(peer);
        const sourceValue = esValue.getProperty("source").toNumber();
        axisEvent.source = TypeChecker.SourceType_FromNumeric(sourceValue as int32);
        const timestampValue = esValue.getProperty("timestamp").toNumber();
        axisEvent.timestamp = timestampValue as int64;
        const targetValue = esValue.getProperty("target");
        const areaValue = targetValue.getProperty("area");
        const widthValue = areaValue.getProperty("width").toNumber();
        const heightValue = areaValue.getProperty("height").toNumber();
        const positionValue = areaValue.getProperty("position");
        const positionXValue = positionValue.getProperty("x").toNumber();
        const positionYValue = positionValue.getProperty("y").toNumber();
        const globalPositionValue = areaValue.getProperty("globalPosition");
        const globalPositionXValue = globalPositionValue.getProperty("x").toNumber();
        const globalPositionYValue = globalPositionValue.getProperty("y").toNumber();
        const idValue = targetValue.getProperty("id");
        const target: EventTarget = {
            area: {
                width: widthValue,
                height: heightValue,
                position: {
                    x: positionXValue,
                    y: positionYValue
                },
                globalPosition: {
                    x: globalPositionXValue,
                    y: globalPositionYValue
                }
            },
            id: idValue.isUndefined() ? undefined : idValue.toString()
        };
        axisEvent.target = target;
        const pressureValue = esValue.getProperty("pressure").toNumber();
        axisEvent.pressure = pressureValue as double;
        const deviceIdValue = esValue.getProperty("deviceId").toNumber();
        axisEvent.deviceId = deviceIdValue as int32;
        const tiltXValue = esValue.getProperty("tiltX").toNumber();
        axisEvent.tiltX = tiltXValue as double;
        const tiltYValue = esValue.getProperty("tiltY").toNumber();
        axisEvent.tiltY = tiltYValue as double;
        const sourceToolValue = esValue.getProperty("sourceTool").toNumber();
        axisEvent.sourceTool = TypeChecker.SourceTool_FromNumeric(sourceToolValue as int32);
        const axisVerticalValue = esValue.getProperty("axisVertical").toNumber();
        axisEvent.axisVertical = axisVerticalValue as double;
        const axisHorizontalValue = esValue.getProperty("axisHorizontal").toNumber();
        axisEvent.axisHorizontal = axisHorizontalValue as double;
        const targetDisplayIdValue = esValue.getProperty("targetDisplayId").toNumber();
        axisEvent.targetDisplayId = targetDisplayIdValue as int32;
        const actionValue = esValue.getProperty("action").toNumber();
        axisEvent.action = TypeChecker.AxisAction_FromNumeric(actionValue as int32);
        const displayXValue = esValue.getProperty("displayX").toNumber();
        axisEvent.displayX = displayXValue as double;
        const displayYValue = esValue.getProperty("displayY").toNumber();
        axisEvent.displayY = displayYValue as double;
        const windowXValue = esValue.getProperty("windowX").toNumber();
        axisEvent.windowX = windowXValue as double;
        const windowYValue = esValue.getProperty("windowY").toNumber();
        axisEvent.windowY = windowYValue as double;
        const xValue = esValue.getProperty("x").toNumber();
        axisEvent.x = xValue as double;
        const yValue = esValue.getProperty("y").toNumber();
        axisEvent.y = yValue as double;
        const scrollStepValue = esValue.getProperty("scrollStep").toNumber();
        axisEvent.scrollStep = scrollStepValue as int32;
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

export class ChildrenMainSizeInternal {
    public static fromPtr(ptr: KPointer): ChildrenMainSize {
        const obj: ChildrenMainSize = new ChildrenMainSize(0)
        return obj
    }
}

interface ChildrenSizeChangeInfo {
    start: int32;
    deleteCount?: int32;
    childrenSize?: Array<double>;
}

export class ChildrenMainSize {
    private sizeArray: Array<double> = new Array<double>();
    private changeArray: Array<ChildrenSizeChangeInfo> = new Array<ChildrenSizeChangeInfo>();
    private defaultMainSize: double = -1;

    constructor(childDefaultSize: double) {
        if (this.isDoubleInvalid(childDefaultSize)) {
            throw new BusinessError(401, 'The parameter check failed.');
        }
        this.defaultMainSize = childDefaultSize;
        this.sizeArray = [];
        // -1: represent newly created.
        this.changeArray = [ { start: -1 } ];
    }

    private isIntInvalid(input: int32 | undefined): boolean {
        if (input === undefined) {
            return true;
        }
        return !(Number.isFinite(input) && input >= 0);
    }

    private isDoubleInvalid(input: double | undefined): boolean {
        if (input === undefined) {
            return true;
        }
        return !(input >= 0);
    }

    set childDefaultSize(value: double) {
        if (this.isDoubleInvalid(value)) {
            throw new BusinessError(401, 'The parameter check failed.');
        }
        this.defaultMainSize = value;
    }

    get childDefaultSize(): double {
        return this.defaultMainSize;
    }

    public splice(start: int32, deleteCount?: int32, childrenSize?: Array<double>): void {
        if (this.isIntInvalid(start)) {
            throw new BusinessError(401, 'The parameter check failed.');
        }
        const startValue: int32 = start;
        const deleteCountValue: int32 = deleteCount && !(this.isIntInvalid(deleteCount)) ? deleteCount : 0;
        if (deleteCount === undefined && childrenSize === undefined) {
            this.sizeArray.splice(startValue);
            this.changeArray.push({ start: startValue });
        } else if (childrenSize === undefined) {
            this.sizeArray.splice(startValue, deleteCountValue);
            this.changeArray.push({ start: startValue, deleteCount: deleteCountValue });
        } else {
            const childrenSizeLength: int32 = childrenSize ? childrenSize.length : 0;
            if (childrenSizeLength === 0) {
                childrenSize = [];
            }
            for (let i: int32 = 0; i < childrenSizeLength; i++) {
                if (this.isDoubleInvalid(childrenSize[i])) {
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

    public update(index: int32, childSize: double): void {
        if (this.isIntInvalid(index)) {
            throw new BusinessError(401, 'The parameter check failed.');
        } else if (this.isDoubleInvalid(childSize)) {
            // -1: represent default size.
            childSize = -1;
        }
        const startValue: int32 = index;
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
export class ArkCommonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCommonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIAniModule._Common_construct(peerId, flags)
        const _peer  = new ArkCommonPeer(_peerPtr, peerId, "Common", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCommonOptionsAttribute(): void {
        ArkUIAniModule._CommonInterface_setCommonOptions(this.peer.ptr)
    }
}

export interface DynamicNode {
    onMove(handler?: OnMoveHandler): this;
    onMove(handler?: OnMoveHandler, eventHandler?: ItemDragEventHandler): this;
}

export function makeBindable<T>(value: T, onChange: Callback<T>): Bindable<T> {
    return { value, onChange } as Bindable<T>;
}