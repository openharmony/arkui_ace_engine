'use static';
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
import { Entry, Component, Builder, Column, Text, FontWeight } from '@ohos.arkui.component';

//[Start virtual_node_example_start]
@Entry
@Component
struct VirtualNodeExample {
  @Builder customAccessibilityNode(): void {
    Text('文本2')
      .fontSize(50)
      .fontWeight(FontWeight.Bold)
  }

  build(): void {
    Column() {
      Text('文本1')
        .fontSize(50)
        .fontWeight(FontWeight.Bold)
    }
    .accessibilityVirtualNode(this.customAccessibilityNode)
  }
}
//[End virtual_node_example_start]