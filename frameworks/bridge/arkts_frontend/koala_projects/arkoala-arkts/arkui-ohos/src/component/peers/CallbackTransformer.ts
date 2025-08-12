/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { KPointer } from "@koalaui/interop"
import { PeerNode } from "../../PeerNode"
import { CustomBuilder } from "../common"
import { CustomNodeBuilder } from "../customBuilder"
import { ArkComponentRootPeer } from "../staticComponents"

// TODO need invert dependency: createUiDetachedRoot should be imported from @koalaui/arkoala same as in TS
export type UIDetachedRootCreator = (
    peerFactory: () => PeerNode,
    /** @memo */
    builder: () => void
) => PeerNode

function createUiDetachedRootStub(
    factory: () => PeerNode,
    /** @memo */
    builder: () => void
): PeerNode {
    throw new Error("Not implemented")
}

let createUiDetachedRoot: UIDetachedRootCreator = createUiDetachedRootStub

export function setUIDetachedRootCreator(creator: UIDetachedRootCreator): void {
    createUiDetachedRoot = creator
}

function componentRootPeerFactory(): PeerNode {
    return ArkComponentRootPeer.create(undefined)
}

export class CallbackTransformer {
    static transformFromCustomBuilder(value: CustomBuilder): CustomNodeBuilder {
        return (parentNodeId: KPointer): KPointer => {
            const peer = createUiDetachedRoot(componentRootPeerFactory, value)
            return peer.peer.ptr
        }
    }
    static transformToCustomBuilder(value: CustomNodeBuilder): CustomBuilder {
        throw new Error("Not implemented")
    }
    static transformToCallbackVoid(value: (data: undefined) => void): (() => void) {
        return () => {
            return value(undefined)
        }
    }
    static transformFromCallbackVoid(value: () => void): ((data: undefined) => void) {
        return (data: undefined) => {
            return value()
        }
    }
}