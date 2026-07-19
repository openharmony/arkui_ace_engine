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

import { ArkUIAniModule } from 'arkui.ani'
import { ArkLazyDynamicLayoutPeer } from '@ohos.arkui.components.ArkLazyDynamicLayout';
import { LazyLayoutAlgorithm, LazyCustomLayoutAlgorithm } from './../LazyLayoutAlgorithm'
import { FrameNode } from 'arkui.FrameNode'
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { UIContext } from '@ohos.arkui.UIContext';
import { int32, float32 } from '@koalaui/common'

export class LazyDynamicLayoutHandWritten {
    static hookSetLazyDynamicLayoutOptionsImpl(peer: ArkLazyDynamicLayoutPeer, value: LazyLayoutAlgorithm): void {
        if (value instanceof LazyCustomLayoutAlgorithm) {
            const nodeId: number = peer.getId()
            const context: UIContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContext
            const frameNode = context.getFrameNodeByNodeId(nodeId)
            if (frameNode) {
                ArkUIAniModule._SetLazyDynamicLayoutCustomLayoutAlgorithm(peer.peer.ptr, value, frameNode as FrameNode)
            }
        }
    }

    static hookSetLazyDynamicLayoutOnVisibleIndexesChangeImpl(peer: ArkLazyDynamicLayoutPeer, callback: ((indexes: Array<int32>) => void) | undefined): void {
        ArkUIAniModule._SetLazyDynamicLayoutOnVisibleIndexesChange(peer.peer.ptr, callback)
    }
}