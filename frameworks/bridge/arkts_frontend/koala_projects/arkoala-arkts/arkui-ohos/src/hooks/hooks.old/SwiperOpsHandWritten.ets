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

import { ArkUIAniModule } from "arkui.ani"
import { WaterFlowOptions, ArkWaterFlowComponent } from "../component/waterFlow"
import { PeerNode, findPeerNode } from "arkui/PeerNode"
import { UIContextUtil } from 'arkui/handwritten/UIContextUtil'
import { UIContextImpl } from "./UIContextImpl"
import { ArkComponentRootPeer, CustomBuilder } from 'arkui/component'
import { createUiDetachedRoot } from "arkui/ArkUIEntry"
import { InteropNativeModule, KPointer } from "@koalaui/interop"
import { GlobalStateManager, IncrementalNode, memoEntry, StateContext, StateManager, createStateManager } from "@koalaui/runtime"

export function hookWaterFlowOptionsImpl(node: ArkWaterFlowComponent, options: WaterFlowOptions | undefined): void {
    if (options === undefined) {
        return;
    }

    if (options.sections !== undefined) {
        ArkUIAniModule._SetWaterFlowSection(node.getPeer().peer.ptr, options.sections!)
        options.footer = undefined;
    } else if (options.footerContent !== undefined) {
        ArkUIAniModule._SetWaterFlowFooterContent(node.getPeer().peer.ptr, options.footerContent!.getNodePtr()!)
        options.footer = undefined;
    } else if (options.footer !== undefined) {
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        if (options.footer instanceof CustomBuilder) {
            const value_builder = options.footer as CustomBuilder
            const old = GlobalStateManager.instance;
            let manager: StateManager = createStateManager()!;
            GlobalStateManager.SetLocalManager(manager);
            let stageNode = manager.updatableNode<IncrementalNode>(new IncrementalNode(), (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                memoEntry<void>(context, 0, value_builder)
                manager.frozen = frozen
            })
            GlobalStateManager.SetLocalManager(old);
            let peerNode: PeerNode | undefined = findPeerNode(stageNode.value)
            ArkUIAniModule._SetWaterFlowFooter(node.getPeer().peer.ptr, peerNode!.peer.ptr);
        }
    }
    if (options.layoutMode !== undefined) {
        ArkUIAniModule._SetWaterFlowLayoutMode(node.getPeer().peer.ptr, options.layoutMode!)
    }
    if (options.scroller !== undefined) {
        ArkUIAniModule._SetWaterFlowScroller(node.getPeer().peer.ptr, options.scroller!.getPeer()!.ptr)
    }
}