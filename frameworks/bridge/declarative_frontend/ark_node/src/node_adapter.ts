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

interface NodeInfo {
    nodeId: number,
    nodePtr: NodePtr
}

class NodeAdapter {
    nativePtr_: NodePtr;
    nativeRef_: NativeStrongRef;
    nodeRefs_: Array<FrameNode> = new Array();
    count_: number = 0;
    attachedNodeRef_: WeakRef<FrameNode>;

    onAttachToNode?: (target: FrameNode) => void;
    onDetachFromNode?: () => void;
    onGetChildId?: (index: number) => number;
    onCreateChild?: (index: number) => FrameNode;
    onDisposeChild?: (id: number, node: FrameNode) => void;
    onUpdateChild?: (id: number, node: FrameNode) => void;

    constructor() {
        this.nativeRef_ = getUINativeModule().nodeAdapter.createAdapter();
        this.nativePtr_ = this.nativeRef_.getNativeHandle();
        getUINativeModule().nodeAdapter.setCallbacks(this.nativePtr_, this,
            this.onAttachToNodePtr, this.onDetachFromNodePtr,
            this.onGetChildId !== undefined ? this.onGetChildId : undefined,
            this.onCreateChild !== undefined ? this.onCreateNewNodePtr : undefined,
            this.onDisposeChild !== undefined ? this.onDisposeNodePtr : undefined,
            this.onUpdateChild !== undefined ? this.onUpdateNodePtr : undefined
        );
    }

    dispose(): void {
        let hostNode = this.attachedNodeRef_.deref();
        if (hostNode !== undefined) {
            NodeAdapter.detachNodeAdapter(hostNode);
        }
        this.nativeRef_.dispose();
        this.nativePtr_ = null;
    }

    set totalNodeCount(count: number) {
        if (count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.setTotalNodeCount(this.nativePtr_, count);
        this.count_ = count;
    }

    get totalNodeCount(): number {
        return this.count_;
    }

    reloadAllItems(): void {
        getUINativeModule().nodeAdapter.notifyItemReloaded(this.nativePtr_);
    }

    reloadItem(start: number, count: number): void {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemChanged(this.nativePtr_, start, count);
    }

    removeItem(start: number, count: number): void {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemRemoved(this.nativePtr_, start, count);
    }

    insertItem(start: number, count: number): void {
        if (start < 0 || count < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemInserted(this.nativePtr_, start, count);
    }

    moveItem(from: number, to: number): void {
        if (from < 0 || to < 0) {
            return;
        }
        getUINativeModule().nodeAdapter.notifyItemMoved(this.nativePtr_, from, to);
    }

    getAllAvailableItems(): Array<FrameNode> {
        let result: Array<FrameNode> = new Array();
        let nodes: Array<NodeInfo> = getUINativeModule().nodeAdapter.getAllItems(this.nativePtr_);
        if (nodes !== undefined) {
            nodes.forEach(node => {
                let nodeId = node.nodeId;
                if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                    let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
                    result.push(frameNode);
                }
            });
        }
        return result;
    }

    onAttachToNodePtr(target: NodeInfo): void {
        let nodeId = target.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (frameNode === undefined) {
                return;
            }
            frameNode.setAdapterRef(this);
            this.attachedNodeRef_ = new WeakRef(frameNode);
            if (this.onAttachToNode !== undefined) {
                this.onAttachToNode(frameNode);
            }
        }
    }

    onDetachFromNodePtr(): void {
        if (this === undefined) {
            return;
        }
        if (this.onDetachFromNode !== undefined) {
            this.onDetachFromNode();
        }
        let attachedNode = this.attachedNodeRef_.deref();
        if (attachedNode !== undefined) {
            attachedNode.setAdapterRef(undefined);
        }
        this.nodeRefs_.splice(0, this.nodeRefs_.length);
    }

    onCreateNewNodePtr(index: number): NodePtr {
        if (this.onCreateChild !== undefined) {
            let node = this.onCreateChild(index);
            if (!this.nodeRefs_.includes(node)) {
                this.nodeRefs_.push(node);
            }
            return node.getNodePtr();
        }
        return null;
    }

    onDisposeNodePtr(id: number, node: NodeInfo): void {
        let nodeId = node.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onDisposeChild !== undefined && frameNode !== undefined) {
                this.onDisposeChild(id, frameNode);
                let index = this.nodeRefs_.indexOf(frameNode);
                if (index > -1) {
                    this.nodeRefs_.splice(index, 1);
                }
            }
        }
    }

    onUpdateNodePtr(id: number, node: NodeInfo): void {
        let nodeId = node.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onUpdateChild !== undefined && frameNode !== undefined) {
                this.onUpdateChild(id, frameNode);
            }
        }
    }

    static attachNodeAdapter(adapter: NodeAdapter, node: FrameNode): boolean {
        if (node === null || node === undefined) {
            return false;
        }
        if (!node.isModifiable()) {
            return false;
        }
        const hasAttributeProperty = Object.prototype.hasOwnProperty.call(node, 'attribute_');
        if (hasAttributeProperty) {
            let frameeNode = node as TypedFrameNode<ArkComponent>;
            if (frameeNode.attribute_.allowChildCount !== undefined) {
                const allowCount = frameeNode.attribute_.allowChildCount();
                if (allowCount <= 1) {
                    return false;
                }
            }
        }
        return getUINativeModule().nodeAdapter.attachNodeAdapter(adapter.nativePtr_, node.getNodePtr());
    }

    static detachNodeAdapter(node: FrameNode) {
        if (node === null || node === undefined) {
            return;
        }
        getUINativeModule().nodeAdapter.detachNodeAdapter(node.getNodePtr());
    }
}