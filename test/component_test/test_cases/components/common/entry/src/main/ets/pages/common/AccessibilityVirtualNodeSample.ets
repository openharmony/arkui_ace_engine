/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import accessibilityVirtualNodeTest from '../MyTest/AccessibilityVirtualNodeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AccessibilityVirtualNodeSample {
  aboutToAppear(): void {
    loadComponentTestEntry(accessibilityVirtualNodeTest)
  }

  @Builder
  customAccessibilityNode() {
    Column() {
      Text(`customAccessibilityNode`)
    }
    .width(10)
    .height(10)
  }

  build() {
    Row() {
      Text("文本1").id('textAccessibilityVirtualNode1')
        .accessibilityVirtualNode(this.customAccessibilityNode)
    }
  }
}