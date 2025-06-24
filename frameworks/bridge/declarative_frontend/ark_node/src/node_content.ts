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

declare class ArkUINativeNodeContent {
    static getNativeContent(value: ArkUINativeNodeContent): Object;
}

class NodeContent extends Content {
    nativeContent_: ArkUINativeNodeContent;
    nativePtr_: NodePtr;
    nativeRef_: NativeStrongRef;
    nodeArray_: Array<FrameNode>;

    constructor() {
        super();
        this.nativeRef_ = getUINativeModule().frameNode.createNodeContent();
        this.nativePtr_ = this.nativeRef_.getNativeHandle();
        this.nodeArray_ = new Array<FrameNode>();
    }

    addFrameNode(node: FrameNode): void {
        if (this.nodeArray_.includes(node)) {
            return;
        }
        if (getUINativeModule().frameNode.addFrameNodeToNodeContent(node.getNodePtr(), this.nativePtr_)) {
            getUINativeModule().frameNode.addBuilderNode(this.nativePtr_, node.getNodePtr());
            this.nodeArray_.push(node);
        }
    }

    removeFrameNode(node: FrameNode): void {
        if (!this.nodeArray_.includes(node)) {
            return;
        }
        getUINativeModule().frameNode.removeBuilderNode(this.nativePtr_, node.getNodePtr());
        if (getUINativeModule().frameNode.removeFrameNodeFromNodeContent(node.getNodePtr(), this.nativePtr_)) {
            let index = this.nodeArray_.indexOf(node);
            if (index > -1) {
                this.nodeArray_.splice(index, 1);
            }
        }
    }
}