/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
import { int32 } from "@koalaui/common"
import { pointer, KInt, wrapCallback, disposeCallback, Finalizable } from "@koalaui/interop"
import { ArkUINativeModule } from "./generated/ArkUINativeModule"
import { PeerNode } from "./PeerNode"

export class NativePeerNode extends Finalizable {
    private peer: PeerNode
    constructor(peer: PeerNode, ptr: pointer, needCustomCallback: boolean) {
        super(ptr, ArkUINativeModule._GetNodeFinalizer())
        this.peer = peer
        if (needCustomCallback) {
            let callbackId = wrapCallback((args1: Uint8Array, length: int32) => {
                const args = new Int32Array(args1.buffer)
                return this.peer.customizationCallback(args)
            }, false)
            ArkUINativeModule._SetCustomCallback(ptr, callbackId)
            this.customCallbackId = callbackId
        }
    }

    private customCallbackId: int32 = -1

    static create(peer: PeerNode, peerPtr: pointer, flags: int32): NativePeerNode {
        return new NativePeerNode(peer, peerPtr, flags != 0)
    }

    dispose(): void {
        if (this.customCallbackId != -1) {
            disposeCallback(this.customCallbackId)
        }
        this.close()
    }

    addChild(child: NativePeerNode): void {
        ArkUINativeModule._AddChild(this.ptr, child.ptr)
    }

    removeChild(child: NativePeerNode): void {
        ArkUINativeModule._RemoveChild(this.ptr, child.ptr)
    }

    insertChildAfter(child: pointer, sibling: pointer): void {
        ArkUINativeModule._InsertChildAfter(this.ptr, child, sibling)
    }

    insertChildBefore(child: pointer, sibling: pointer): void {
        ArkUINativeModule._InsertChildBefore(this.ptr, child, sibling)
    }

    insertChildAt(child: pointer, position: KInt): void {
        ArkUINativeModule._InsertChildAt(this.ptr, child, position)
    }
    get name(): string {
        console.log("name: method not implemented")
        return ""
    }

    get id(): number {
        console.log("id: method not implemented")
        return 0
    }

    getAttribute(name: string): string {
        console.log("getAttribute: method not implemented")
        return ""
    }

    setAttribute(name: string, value: string) {
        console.log("setAttribute: method not implemented")
    }

    dump() {
        ArkUINativeModule._DumpTreeNode(this.ptr)
    }

    toString(): string {
        return "NativePeerNode: " + this.ptr.toString(16)
    }
}
