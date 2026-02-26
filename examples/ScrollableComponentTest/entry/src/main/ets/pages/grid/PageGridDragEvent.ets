/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

import Napi from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  private nodeContent = new NodeContent();
  aboutToAppear() {
    // 通过C-API创建节点，并添加到管理器nodeContent上
    Napi.createGridNativeNodeDragEvent(this.nodeContent);
  }
  build() {
    Column() {
      ContentSlot(this.nodeContent)
    }
    .width('100%')
    .height('100%')
  }
}
