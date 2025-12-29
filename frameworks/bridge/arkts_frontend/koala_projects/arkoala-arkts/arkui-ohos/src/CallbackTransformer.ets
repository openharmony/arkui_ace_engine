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

import { memo, memo_intrinsic, memo_entry, memo_stable, memo_skip } from "@koalaui/runtime/annotations"
import { KPointer, nullptr } from '@koalaui/interop';
import { IncrementalNode, GlobalStateManager } from '@koalaui/runtime';
import { PeerNode } from "./PeerNode"
import { CustomBuilder, CustomBuilderT } from "./component/builder"
import { CustomNodeBuilder, ArkComponentRootPeer, CustomBuilderT_Arkui_Component_Enums_ResponseType } from "#generated"
import { UIContextUtil } from './base/UIContextUtil';
import { UIContextImpl } from './base/UIContextImpl';
import { ObserveSingleton } from './stateManagement/base/observeSingleton';
import { ExtendableComponent } from './component/extendableComponent';
import { ResponseType } from "./component/enums"

// Improve: need invert dependency: createUiDetachedRoot should be imported from @koalaui/arkoala same as in TS
export type UIDetachedRootCreator = (
    peerFactory: () => PeerNode,
    @memo
    builder: () => void
) => PeerNode

function createUiDetachedRootStub(
    factory: () => PeerNode,
    @memo
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

function componentFreeRootFactory(): IncrementalNode {
    return new IncrementalNode();
}

export class CallbackTransformer {
    static transformFromCustomBuilder(value: CustomBuilder): CustomNodeBuilder {
        const context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
        const currentExtendableComponent = ExtendableComponent.current;
        const currentStateManager = GlobalStateManager.instance;
        return (parentNodeId: KPointer): KPointer => {
            /** @memo */
            const cb = () => {
                const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
                const lastExtendableComponent = ExtendableComponent.current;
                const latestStateManager = GlobalStateManager.instance;
                ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
                ExtendableComponent.current = currentExtendableComponent;
                // set StateManager which is the customComponent created before invoking build function
                GlobalStateManager.setLocalManager(currentStateManager);
                try {
                    value();
                } finally {
                    ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
                    ExtendableComponent.current = lastExtendableComponent;
                    // revert stateManager is using mow
                    GlobalStateManager.setLocalManager(latestStateManager);
                }
            };
            const latestStateManager = GlobalStateManager.instance;
            GlobalStateManager.setLocalManager(currentStateManager);
            const peer = context.getDetachedRootEntryManager().createUiDetachedFreeRoot(componentFreeRootFactory, cb);
            GlobalStateManager.setLocalManager(latestStateManager);
            return peer ? peer.peer.ptr : nullptr;
        }
    }
    static transformToCustomBuilder(value: CustomNodeBuilder): CustomBuilder {
        throw new Error("Not implemented")
    }
    static transformToPeerFromCustomBuilder(value: CustomBuilder): KPointer {
        const peer = createUiDetachedRoot(componentRootPeerFactory, value)
        return peer.peer.ptr
    }

    static transformFromCustomBuilderT(value: CustomBuilderT<ResponseType>): CustomBuilderT_Arkui_Component_Enums_ResponseType {
        const context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
        const currentExtendableComponent = ExtendableComponent.current;
        return (t: ResponseType, parentNodeId: KPointer): KPointer => {
            /** @memo */
            const cb = () => {
                const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
                const lastExtendableComponent = ExtendableComponent.current;
                ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
                ExtendableComponent.current = currentExtendableComponent;
                try {
                    value(t);
                } finally {
                    ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
                    ExtendableComponent.current = lastExtendableComponent;
                }
            };
            const peer = createUiDetachedRoot(componentRootPeerFactory, cb);
            return peer.peer.ptr;
        }
    }
}
