import { int32 } from "@koalaui/common"
import { IncrementalNode } from "@koalaui/runtime"
import { NativePeerNode } from "./NativePeerNode"
import { nullptr, pointer } from "@koalaui/interop"
import { ArkRootPeer } from "./generated/peers/ArkStaticComponentsPeer"

export const PeerNodeType = 11
export const LazyForEachType = 13
const InitialID = 999

export class PeerNode extends IncrementalNode {
    static generateRootPeer() {
        return ArkRootPeer.create()
    }
    peer: NativePeerNode
    protected static currentId: int32 = InitialID
    static nextId(): int32 { return ++PeerNode.currentId }
    private id: int32

    setId(id: int32) {
        PeerNode.peerNodeMap.delete(this.id)
        this.id = id
        PeerNode.peerNodeMap.set(this.id, this)
    }

    getId(): int32 {
        return this.id
    }

    private static peerNodeMap = new Map<number, PeerNode>()

    static findPeerByNativeId(id: number): PeerNode | undefined {
        return PeerNode.peerNodeMap.get(id)
    }
    readonly name: string
    private insertMark: pointer = nullptr
    private insertDirection: int32 = 0

    setInsertMark(mark: pointer, upDirection: boolean) {
        this.insertMark = mark
        this.insertDirection = upDirection ? 0 : 1
    }

    constructor(peerPtr: pointer, id: int32, name: string, flags: int32) {
        super(PeerNodeType)
        this.id = id
        this.peer = NativePeerNode.create(this, peerPtr, flags)
        PeerNode.peerNodeMap.set(this.id, this)
        this.onChildInserted = (child: IncrementalNode) => {
            // TODO: rework to avoid search
            let peer = findPeerNode(child)
            if (peer) {
                let peerPtr = peer.peer.ptr
                if (this.insertMark != nullptr) {
                    if (this.insertDirection == 0) {
                        this.peer.insertChildBefore(peerPtr, this.insertMark)
                    } else {
                        this.peer.insertChildAfter(peerPtr, this.insertMark)
                    }
                    this.insertMark = peerPtr
                    return
                }
                // Find the closest peer node backward.
                let sibling: PeerNode | undefined = undefined
                for (let node = child.previousSibling; node; node = node!.previousSibling) {
                    if (node!.isKind(PeerNodeType)) {
                        sibling = node as PeerNode
                        break
                }
            }
            this.peer.insertChildAfter(peerPtr, sibling?.peer?.ptr ?? nullptr)
            }
        }
        this.name = name
    }
    applyAttributes(attrs: Object) {}
    dispose(): void {
        let parent = this.parent
        if (parent != undefined && parent.isKind(PeerNodeType)) {
            (parent as PeerNode).peer.removeChild(this.peer.ptr)
        }
        this.peer.close()
        PeerNode.peerNodeMap.delete(this.id)
        super.dispose()
    }
}

function findPeerNode(node: IncrementalNode): PeerNode | undefined {
    if (node.isKind(PeerNodeType)) return node as PeerNode
    for (let child = node.firstChild; child; child = child!.nextSibling) {
        let peer = findPeerNode(child!)
        if (peer) return peer
    }
    return undefined
}
