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
//测试代码路径
import gridItemSelectableTest from '../MyTest/GridItemSelectableTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridItemSelectableSample {
  @State selectable: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(gridItemSelectableTest)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('4')
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
        }
        .selectable(this.selectable).id('gridItemSelectable1')

      }.multiSelectable(true)
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr')
      .height(100)

      Button("GridItemSelectable")
        .onClick(() => {
          this.selectable = !this.selectable
        })
      Grid() {
        GridItem() {
          Text('5')
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
        }
        .selectable(true).id('gridItemSelectable2')
      }.multiSelectable(false)
      .columnsTemplate('1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr')
    }.width('90%').margin({ top: 5, left: 5, right: 5 })
    .align(Alignment.Center)
  }
}