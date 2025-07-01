import { GestureOps } from "./arkui-custom"
import { GestureGroupHandler } from "./gesture"
import { ArkUIAniModule } from "arkui.ani"

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

export function hookDrawModifier(arkComponent: ArkCommonMethodComponent, value: DrawModifier | undefined): void {
    if (value !== undefined) {
        ArkUIAniModule._SetDrawModifier(arkComponent.getPeer().getPeerPtr(), value);
        value.weakRefOfPeerNode = new WeakRef<PeerNode>(arkComponent.getPeer());
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
