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
    count_: number = 0;
    onAttachToNode?: (target: FrameNode) => void;
    onDetachFromNode?: () => void;
    onGetChildId?: (index: number) => number;
    onCreateNewChild?: (index: number) => FrameNode;
    onDisposeChild?: (id: number, node: FrameNode) => void;

    constructor() {
        this.nativeRef_ = getUINativeModule().nodeAdapter.createAdapter();
        this.nativePtr_ = this.nativeRef_.getNativeHandle();
        getUINativeModule().nodeAdapter.setCallbacks(this.nativePtr_,
            this.onAttachToNode !== undefined ? this.onAttachToNodePtr : undefined,
            this.onDetachFromNode !== undefined ? this.onDetachFromNode : undefined,
            this.onGetChildId !== undefined ? this.onGetChildId : undefined,
            this.onCreateNewChild !== undefined ? this.onCreateNewNodePtr : undefined,
            this.onDisposeChild !== undefined ? this.onDisposeNodePtr : undefined
        )
    }

    dispose(): void {
        this.nativeRef_.dispose();
        this.nativePtr_ = null;
    }

    set totalNodeCount(count: number) {
        this.count_ = count;
        getUINativeModule().nodeAdapter.setTotalNodeCount(this.nativePtr_, this.count_);
    }

    get totalNodeCount(): number {
        return this.count_;
    }

    notifyItemReloaded(): void {
        getUINativeModule().nodeAdapter.notifyItemReloaded(this.nativePtr_);
    }

    notifyItemChanged(start: number, count: number): void {
        getUINativeModule().nodeAdapter.notifyItemChanged(this.nativePtr_, start, count);
    }

    notifyItemRemoved(start: number, count: number): void {
        getUINativeModule().nodeAdapter.notifyItemRemoved(this.nativePtr_, start, count);
    }

    notifyItemInserted(start: number, count: number): void {
        getUINativeModule().nodeAdapter.notifyItemInserted(this.nativePtr_, start, count);
    }

    notifyItemMoved(from: number, to: number): void {
        getUINativeModule().nodeAdapter.notifyItemMoved(this.nativePtr_, from, to);
    }

    getAllItems(): Array<FrameNode> {
        let result: Array<FrameNode> = new Array();
        let nodes: Array<NodeInfo> = getUINativeModule().nodeAdapter.getAllItems(this.nativePtr_);
        nodes.forEach(node => {
            let nodeId = node.nodeId;
            if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
                let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
                result.push(frameNode);
            }
        });
        return result;
    }

    onAttachToNodePtr(target: NodeInfo): void {
        let nodeId = target.nodeId
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onAttachToNode !== undefined && frameNode !== undefined) {
                this.onAttachToNode(frameNode);
            }
        }
    }

    onCreateNewNodePtr(index: number): NodePtr {
        if (this.onCreateNewChild !== undefined) {
            let node = this.onCreateNewChild(index);
            return node.getNodePtr();
        }
        return null;
    }

    onDisposeNodePtr(id: number, node: NodeInfo) {
        let nodeId = node.nodeId;
        if (FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.has(nodeId)) {
            let frameNode = FrameNodeFinalizationRegisterProxy.ElementIdToOwningFrameNode_.get(nodeId).deref();
            if (this.onDisposeChild !== undefined && frameNode !== undefined) {
                this.onDisposeChild(id, frameNode);
            }
        }
    }

    static attachNodeAdapter(adapter: NodeAdapter, node: FrameNode) {
        getUINativeModule().nodeAdapter.attachNodeAdapter(adapter.nativePtr_, node.getNodePtr());
    }

    static detachNodeAdapter(node: FrameNode) {
        getUINativeModule().nodeAdapter.detachNodeAdapter(node.getNodePtr());
    }
}