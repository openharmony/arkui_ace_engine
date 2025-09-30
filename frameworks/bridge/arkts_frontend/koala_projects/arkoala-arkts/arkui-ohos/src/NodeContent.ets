/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { Content } from 'arkui.Content';
import { NodeContentExtender } from './framework';
import { extractors } from "#handwritten";
import { FrameNode } from './FrameNode';
import {
    Finalizable, toPeerPtr, KPointer, MaterializedBase, nullptr, KSerializerBuffer, KUint8ArrayPtr, pointer,
    NativeThunk, SerializerBase
} from "@koalaui/interop";

export class NodeContent implements MaterializedBase, Content {
    peer?: Finalizable | undefined = undefined;
    private nativePtr_: KPointer | undefined;
    nodeArray_: Array<FrameNode>;
    constructor() {
        const ctorPtr: KPointer = NodeContentExtender.constructorNodeContent()
        this.peer = new Finalizable(ctorPtr, NodeContentExtender.getDestroy())
        this.nativePtr_ = this.peer?.ptr;
        this.nodeArray_ = new Array<FrameNode>();
    }
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public addFrameNode(node: FrameNode): void {
        if (this.nodeArray_.includes(node)) {
            return;
        }
        if (toPeerPtr(this) && toPeerPtr(node) && NodeContentExtender.addFrameNode(toPeerPtr(this), toPeerPtr(node))) {
            this.nodeArray_.push(node);
        }
    }
    public removeFrameNode(node: FrameNode): void {
        const index = this.nodeArray_.indexOf(node);
        if (index === -1) {
            return;
        }
        if (toPeerPtr(this) && toPeerPtr(node) && NodeContentExtender.removeFrameNode(toPeerPtr(this), toPeerPtr(node)) && index > -1) {
            this.nodeArray_.splice(index, 1);
        }
    }
}
