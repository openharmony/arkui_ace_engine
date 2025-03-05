import { int32 } from "@koalaui/common"
import { nullptr, pointer } from "@koalaui/interop"
import { Finalizable } from "@koalaui/interop"
import { ArkUINativeModule } from "#components"
import { PeerNode } from "./PeerNode"

export class NativePeerNode extends Finalizable {
    constructor(peer: PeerNode, ptr: pointer) {
        super(ptr, ArkUINativeModule._GetNodeFinalizer())
    }

    static create(peer: PeerNode, peerPtr: pointer, flags: int32): NativePeerNode {
        return new NativePeerNode(peer, peerPtr)
    }

    addChild(node: pointer) {
        ArkUINativeModule._AddChild(this.ptr, node)
    }
    removeChild(node: pointer) {
        ArkUINativeModule._RemoveChild(this.ptr, node)
    }
    insertChildBefore(node: pointer, sibling: pointer) {
        ArkUINativeModule._InsertChildBefore(this.ptr, node, sibling)
    }
    insertChildAfter(node: pointer, sibling: pointer) {
        ArkUINativeModule._InsertChildAfter(this.ptr, node, sibling)
    }
    insertChildAt(node: pointer, position: int32) {
        ArkUINativeModule._InsertChildAt(this.ptr, node, position)
    }
    dumpTree() {
        ArkUINativeModule._DumpTreeNode(this.ptr)
    }
}
