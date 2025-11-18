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
import { BusinessError } from '#external';
import {
    Finalizable, toPeerPtr, KPointer, MaterializedBase, nullptr, KSerializerBuffer, KUint8ArrayPtr, pointer,
    NativeThunk, SerializerBase
} from "@koalaui/interop";

const ERROR_CODE_NODE_IS_ADOPTED = 106206;
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
        if (toPeerPtr(this) && toPeerPtr(node)) {
            let result = NodeContentExtender.addFrameNode(toPeerPtr(this), toPeerPtr(node));
            if (result === ERROR_CODE_NODE_IS_ADOPTED) {
                const error = Error("The parameter 'node' is invalid: the node has already been adopted.");
                throw new BusinessError(100025, error);
            } else if (result === 0) {
                this.nodeArray_.push(node);
            }
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
