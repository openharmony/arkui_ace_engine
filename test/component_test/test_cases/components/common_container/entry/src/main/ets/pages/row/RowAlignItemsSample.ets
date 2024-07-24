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
// 测试代码路径
import rowAlignItemsTest from '../MyTest/RowAlignItemsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RowAlignItemsSample {
  @State rowAlignItems: VerticalAlign = VerticalAlign.Center

  aboutToAppear(): void {
    loadComponentTestEntry(rowAlignItemsTest)
  }

  build() {
    Column({ space: 5 }) {
      Text('alignItems(Top)').width('90%')
      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }
      .id('rowAlignItems1')
      .width('90%')
      .alignItems(VerticalAlign.Top)
      .height('15%')
      .border({ width: 1 })

      Row() {
        Row().width('30%').height(50).backgroundColor(0xAFEEEE)
        Row().width('30%').height(50).backgroundColor(0x00FFFF)
      }
      .id('rowAlignItems2')
      .width('90%')
      .alignItems(this.rowAlignItems)
      .height('15%')
      .border({ width: 1 })

      Button('RowAlignItems').onClick(() => {
        this.rowAlignItems = VerticalAlign.Bottom
      })
    }
  }
}