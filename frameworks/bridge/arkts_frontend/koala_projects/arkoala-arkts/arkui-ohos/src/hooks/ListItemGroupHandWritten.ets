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

import { ArkUIAniModule } from 'arkui.ani'
import { ListItemGroupOptions, ArkListItemGroupComponent, ListItemGroupStyle } from '../component/listItemGroup'
import { PeerNode, findPeerNode } from 'arkui/PeerNode'
import { UIContextImpl } from 'arkui/base/UIContextImpl'
import { UIContextUtil } from 'arkui/base/UIContextUtil'
import { CustomBuilder, ArkComponentRootPeer } from 'arkui/framework'
import { StateContext } from 'arkui.incremental.runtime.state';
import { GlobalStateManager, IncrementalNode, memoEntry, StateManager, createStateManager } from '@koalaui/runtime'
export class ListItemGroupHandWritten {
    static hookListItemGroupOptionsImpl(
        node: ArkListItemGroupComponent,
        options: ListItemGroupOptions | undefined
    ): void {
        if (options === undefined) {
            ArkUIAniModule._SetListItemGroupSpace(node.getPeer().peer.ptr, 0)
            ArkUIAniModule._SetListItemGroupStyle(node.getPeer().peer.ptr, ListItemGroupStyle.NONE)
            ArkUIAniModule._ResetListItemGroupHeader(node.getPeer().peer.ptr);
            ArkUIAniModule._ResetListItemGroupFooter(node.getPeer().peer.ptr);
            return;
        }

        if (options.headerComponent !== undefined) {
            ArkUIAniModule._SetListItemGroupHeaderContent(
                node.getPeer().peer.ptr, options.headerComponent!.getNodePtr()!)
        } else if (options.header !== undefined) {
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            if (options.header instanceof CustomBuilder) {
                const valueBuilder = options.header as CustomBuilder
                const old = GlobalStateManager.instance;
                let manager: StateManager = createStateManager()!;
                GlobalStateManager.SetLocalManager(manager);
                const builderNode = manager.updatableNode<PeerNode>(
                    ArkComponentRootPeer.create(undefined), (context: StateContext) => {
                    const frozen = manager.frozen
                    manager.frozen = true
                    memoEntry<void>(context, 0, valueBuilder)
                    manager.frozen = frozen
                })
                GlobalStateManager.SetLocalManager(old);
                ArkUIAniModule._SetListItemGroupHeader(
                    node.getPeer().peer.ptr, builderNode.value!.peer.ptr);
            }
        } else {
            ArkUIAniModule._ResetListItemGroupHeader(node.getPeer().peer.ptr);
        }

        if (options.footerComponent !== undefined) {
            ArkUIAniModule._SetListItemGroupFooterContent(
                node.getPeer().peer.ptr, options.footerComponent!.getNodePtr()!)
        } else if (options.footer !== undefined) {
            let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
            if (options.footer instanceof CustomBuilder) {
                const valueBuilder = options.footer as CustomBuilder
                const old = GlobalStateManager.instance;
                let manager: StateManager = createStateManager()!;
                GlobalStateManager.SetLocalManager(manager);
                const builderNode = manager.updatableNode<PeerNode>(
                    ArkComponentRootPeer.create(undefined), (context: StateContext) => {
                    const frozen = manager.frozen
                    manager.frozen = true
                    memoEntry<void>(context, 0, valueBuilder)
                    manager.frozen = frozen
                })
                GlobalStateManager.SetLocalManager(old);
                ArkUIAniModule._SetListItemGroupFooter(node.getPeer().peer.ptr, builderNode.value!.peer.ptr);
            }
        } else {
            ArkUIAniModule._ResetListItemGroupFooter(node.getPeer().peer.ptr);
        }

        if (options.space !== undefined) {
            ArkUIAniModule._SetListItemGroupSpace(node.getPeer().peer.ptr, options.space!)
        } else {
            ArkUIAniModule._SetListItemGroupSpace(node.getPeer().peer.ptr, 0)
        }

        if (options.style !== undefined) {
            ArkUIAniModule._SetListItemGroupStyle(node.getPeer().peer.ptr, options.style!)
        } else {
            ArkUIAniModule._SetListItemGroupStyle(node.getPeer().peer.ptr, ListItemGroupStyle.NONE)
        }
    }
}