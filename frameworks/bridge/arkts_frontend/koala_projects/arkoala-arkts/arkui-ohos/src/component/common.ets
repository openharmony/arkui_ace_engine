// this file will be merged with component/xxx.ets by compiler pre-process script

import { WrappedBuilder, CustomBuilderT } from "./builder"
import { GestureGroupHandler, GestureHandler, GesturePriority } from "./gesture"
import { GestureOps } from "./idlize"

export interface AttributeModifier<T> {
    applyNormalAttribute(instance: T): void {}
    applyPressedAttribute(instance: T): void {}
    applyFocusedAttribute(instance: T): void {}
    applyDisabledAttribute(instance: T): void {}
    applySelectedAttribute(instance: T): void {}
}

export interface AnimatableArithmetic<T> {
    plus(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    subtract(rhs:AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    multiply(scale:number): AnimatableArithmetic<T>;
    equals(rhs:AnimatableArithmetic<T>): boolean;
}

export interface ContentModifier<T = void> {
  applyContent(): WrappedBuilder<CustomBuilderT<T>>
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
