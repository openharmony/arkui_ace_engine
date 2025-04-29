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
import columnAlignItemsTest from '../MyTest/ColumnAlignItemsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ColumnAlignItemsSample {
  @State columnAlignItems: HorizontalAlign = HorizontalAlign.Center

  aboutToAppear(): void {
    loadComponentTestEntry(columnAlignItemsTest)
  }

  build() {
    Column({ space: 5 }) {
      Column() {
        Column().width('50%').height(30).backgroundColor(0xAFEEEE)
        Column().width('50%').height(30).backgroundColor(0x00FFFF)
      }
      .id('columnAlignItems1')
      .alignItems(HorizontalAlign.Start).width('90%').border({ width: 1 })


      Column() {
        Column().width('50%').height(30).backgroundColor(0xAFEEEE)
        Column().width('50%').height(30).backgroundColor(0x00FFFF)
      }
      .id('columnAlignItems2')
      .alignItems(this.columnAlignItems).width('90%').border({ width: 1 })

      Button('ColumnAlignItems').onClick(() => {
        this.columnAlignItems = HorizontalAlign.End
      })
    }
  }
}