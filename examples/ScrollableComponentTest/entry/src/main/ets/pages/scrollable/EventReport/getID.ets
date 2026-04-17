/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { UIContext } from '@ohos.arkui.UIContext';


export class NodeIdUtils {
  static getNodeInternalId(uiContext: UIContext, firstNode: string, child: string, childSize: number) {
    if (!uiContext) {
      return;
    }

    // 通过自定义ID查找FrameNode
    const frameNode = uiContext.getFrameNodeById(firstNode);

    if (frameNode) {
      const internalId = frameNode.getUniqueId?.() ?? -1;
      console.info("through uiSa " + firstNode + "节点的内部数值ID是:" + `${internalId}`);
    }
    for (let i = 0; i < childSize; i++) {
      const textNode = uiContext.getFrameNodeById(child + i.toString());
      if (textNode) {
        const internalId = textNode.getUniqueId?.() ?? -1;
        console.info("through uiSa textNode" + i.toString() + "节点的内部数值ID是:" + `${internalId}`);
      }
    }
  }
}

