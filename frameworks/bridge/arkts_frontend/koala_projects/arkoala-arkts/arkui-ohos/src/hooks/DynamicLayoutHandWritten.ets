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
import { ArkDynamicLayoutPeer } from '@ohos.arkui.components.ArkDynamicLayout';
import { LayoutAlgorithm, StackLayoutAlgorithm, RowLayoutAlgorithm, ColumnLayoutAlgorithm, CustomLayoutAlgorithm } from './../LayoutAlgorithm'
import { FrameNode } from 'arkui.FrameNode'
import { UIContextUtil } from 'arkui/base/UIContextUtil';
import { UIContext } from '@ohos.arkui.UIContext';

export class DynamicLayoutHandWritten {
    static hookSetDynamicLayoutOptionsImpl(peer: ArkDynamicLayoutPeer, value: LayoutAlgorithm): void {
        if (value instanceof StackLayoutAlgorithm) {
            ArkUIAniModule._SetDynamicLayoutStackLayoutAlgorithm(peer.peer.ptr, value)
        } else if (value instanceof RowLayoutAlgorithm) {
            ArkUIAniModule._SetDynamicLayoutRowLayoutAlgorithm(peer.peer.ptr, value)
        } else if (value instanceof ColumnLayoutAlgorithm) {
            ArkUIAniModule._SetDynamicLayoutColumnLayoutAlgorithm(peer.peer.ptr, value)
        } else if (value instanceof CustomLayoutAlgorithm) {
            const nodeId: number = peer.getId()
            const context: UIContext = UIContextUtil.getOrCreateCurrentUIContext() as UIContext
            const frameNode = context.getFrameNodeByNodeId(nodeId)
            if (frameNode) {
                ArkUIAniModule._SetDynamicLayoutCustomLayoutAlgorithm(peer.peer.ptr, value, frameNode as FrameNode)
            }
        }
    }
}