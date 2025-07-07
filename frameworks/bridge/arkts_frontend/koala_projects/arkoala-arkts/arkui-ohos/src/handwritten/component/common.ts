import { GestureOps } from "./arkui-custom"
import { GestureGroupHandler } from "./gesture"
import { ArkUIAniModule } from "arkui.ani"
import { int32 } from "@koalaui/common"
import { AnimateParam } from "../component"
import { CommonMethodHandWritten } from "./../handwritten"
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
