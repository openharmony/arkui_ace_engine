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

import { ArkUIAniModule } from 'arkui.ani';
import { WaterFlowOptions, ArkWaterFlowComponent } from '../component/waterFlow';
import { PeerNode, findPeerNode } from 'arkui/PeerNode';
import { UIContextImpl } from 'arkui/base/UIContextImpl';
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { CustomBuilder } from 'arkui/framework';
import { StateContext } from 'arkui.incremental.runtime.state';
import { GlobalStateManager, IncrementalNode, memoEntry, StateManager, createStateManager } from '@koalaui/runtime';

export class WaterFlowHandWritten {
    static hookWaterFlowOptionsImpl(node: ArkWaterFlowComponent, options: WaterFlowOptions | undefined): void {
        if (options === undefined) {
            return;
        }

        if (options.sections !== undefined) {
            const waterFlowNodePtr = node.getPeer().peer.ptr;
            options.sections!.waterFlowNodePtr = waterFlowNodePtr;
            ArkUIAniModule._SetWaterFlowSection(waterFlowNodePtr, options.sections!);
            options.footer = undefined;
            options.footerContent = undefined;
        } else {
            if (options.footerContent !== undefined) {
                const peerPtr = node.getPeer().peer.ptr;
                const footerNodePtr = options.footerContent!.getNodePtr()!;
                ArkUIAniModule._SetWaterFlowFooterContent(peerPtr, footerNodePtr);
                options.footer = undefined;
            } else if (options.footer !== undefined) {
                let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
                if (options.footer instanceof CustomBuilder) {
                    const valueBuilder = options.footer as CustomBuilder;
                    const old = GlobalStateManager.instance;
                    let manager: StateManager = createStateManager()!;
                    GlobalStateManager.SetLocalManager(manager);
                    let stageNode = manager.updatableNode<IncrementalNode>(
                        new IncrementalNode(),
                        (context: StateContext) => {
                            memoEntry<void>(context, 0, valueBuilder);
                        }
                    );
                    GlobalStateManager.SetLocalManager(old);
                    let peerNode: PeerNode | undefined = findPeerNode(stageNode.value);
                    ArkUIAniModule._SetWaterFlowFooter(node.getPeer().peer.ptr, peerNode!.peer.ptr);
                }
            } else {
                ArkUIAniModule._ResetWaterFlowFooter(node.getPeer().peer.ptr);
            }
        }

        if (options.layoutMode !== undefined) {
            ArkUIAniModule._SetWaterFlowLayoutMode(node.getPeer().peer.ptr, options.layoutMode!);
        }

        if (options.scroller !== undefined) {
            ArkUIAniModule._SetWaterFlowScroller(node.getPeer().peer.ptr, options.scroller!.getPeer()!.ptr);
        }
    }
}