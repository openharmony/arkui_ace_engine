/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { nullptr } from "@koalaui/interop"
import { ArkToggleComponent, ToggleOptions, ToggleType } from "#generated"
import { PeerNode, findSiblingPeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, ArkUINativeModule } from "#components"

export class ToggleHandWritten {
    static hookSetToggleOptions(toggle: ArkToggleComponent, options: ToggleOptions): void {
        if (!toggle.getPeer().peer.ptr) {
            if (options.type == ToggleType.SWITCH) {
                const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else if (options.type == ToggleType.CHECKBOX) {
                const _peerPtr  = ArkUIGeneratedNativeModule._ToggleExtender_constructCheckbox(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else if (options.type == ToggleType.BUTTON) {
                const _peerPtr  = ArkUIGeneratedNativeModule._ToggleExtender_constructButton(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else {
                throw new Error("Invalid Toggle Type")
                return
            }
        } else {
            if (!toggle.getPeer().parent || toggle.getPeer().parent == undefined) {
                console.log("Toggle's parent is null")
                return
            }

            let sibling: PeerNode | undefined = findSiblingPeerNode(toggle.getPeer(), true)
            const node = toggle.getPeer().parent! as PeerNode
            const preNativePtr = toggle.getPeer().peer.ptr
            node.peer.removeChild(toggle.getPeer().peer.ptr)
            ArkUINativeModule._DisposeNode(preNativePtr)
            
            if (options.type == ToggleType.SWITCH) {
                const _peerPtr  = ArkUIGeneratedNativeModule._Toggle_construct(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else if (options.type == ToggleType.CHECKBOX) {
                const _peerPtr  = ArkUIGeneratedNativeModule._ToggleExtender_constructCheckbox(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else if (options.type == ToggleType.BUTTON) {
                const _peerPtr  = ArkUIGeneratedNativeModule._ToggleExtender_constructButton(toggle.getPeer().getId(), 0)
                toggle.getPeer().peer.ptr = _peerPtr
            } else {
                throw new Error("Invalid Toggle Type")
                return
            }

            if (sibling === undefined) {
                // Add to the end (common case!).
                node.peer.addChild(toggle.getPeer().peer.ptr)
            } else {
                // Insert child in the middle.
                node.peer.insertChildBefore(toggle.getPeer().peer.ptr, sibling?.peer?.ptr ?? nullptr)
            }
        }
    }
}