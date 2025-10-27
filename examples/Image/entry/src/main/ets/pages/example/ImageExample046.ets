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

import router from '@ohos.router';

@Entry
@Component
struct AnimatorTest {
  private values: string[] = [
    "High", "Medium", "LOW", "Medium", "Low"
  ]
  @State idx: number = 0; 
  // 动态范围模式数组，存储5种图片动态范围模式
  @State dy: DynamicRangeMode[] = [
    DynamicRangeMode.HIGH,
    DynamicRangeMode.CONSTRAINT,
    DynamicRangeMode.STANDARD,
    DynamicRangeMode.CONSTRAINT,
    DynamicRangeMode.STANDARD
  ]

  build() {
    // 垂直布局容器：子组件间距10
    Column({space:10}) {
      Blank().height(50) 
      Divider() // 分割线
      Text(this.values[this.idx])

      // 图片组件：绑定当前索引的动态范围模式，点击切换
      Image($r("app.media.JPEGISOSingle"))
        .height(200)
        .width(200)
        .dynamicRangeMode(this.dy[this.idx]) // 应用当前动态范围模式
        .onClick(()=>{
          // 点击循环切换索引（0-4循环）
          this.idx = (this.idx + 1) % 5
        })
    }
    .width('100%')
    .height('100%')
  }
}