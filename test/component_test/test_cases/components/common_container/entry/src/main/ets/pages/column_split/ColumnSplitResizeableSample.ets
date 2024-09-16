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
import columnSplitResizeableTest from '../MyTest/ColumnSplitResizeableTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ColumnSplitResizeableSample {
  @State columnSplitResizeable: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(columnSplitResizeableTest)
  }

  build() {
    Column() {
      ColumnSplit() {
        Text('ColumnSplitText1').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('ColumnSplitText2').width('100%').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('ColumnSplitText3').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('ColumnSplitText4').width('100%').height(50).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('ColumnSplitText5').width('100%').height(50).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
      }
      .id('columnSplitResizeable1')
      .borderWidth(1)
      .resizeable(this.columnSplitResizeable)
      .width('90%')
      .height('60%')

      Button('ColumnSplitResizeable').onClick(() => {
        this.columnSplitResizeable = !this.columnSplitResizeable
      })
    }.width('100%')
  }
}