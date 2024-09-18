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
import rowSplitResizeableTest from '../MyTest/RowSplitResizeableTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RowSplitResizeableSample {
  @State rowSplitResizeable: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(rowSplitResizeableTest)
  }

  build() {
    Column() {
      RowSplit() {
        Text('RowSplitText1').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('RowSplitText2').width('10%').height(100).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('RowSplitText3').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('RowSplitText4').width('10%').height(100).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('RowSplitText5').width('10%').height(100).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
      }
      .id('rowSplitResizeable1')
      .resizeable(this.rowSplitResizeable)
      .width('90%').height(100)

      Button('RowSplitResizeable').onClick(() => {
        this.rowSplitResizeable = !this.rowSplitResizeable
      })
    }.width('100%').margin({ top: 5 })
  }
}