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
import gridRowsGapTest from '../MyTest/GridRowsGapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridRowsGapSample {
  @State len: Length = '15px'

  aboutToAppear(): void {
    loadComponentTestEntry(gridRowsGapTest)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('gridRowsGap1Test1')
            .backgroundColor(0xF9CF93).width('100%').height('100%')
        }

        GridItem() {
          Text('gridRowsGap1Test2')
            .backgroundColor(0xF9CF93).width('100%').height('100%')
        }

      }.height('30%')
      .rowsTemplate('1fr 1fr 1fr')
      .rowsGap(2)
      .id('gridRowsGap1')

      Grid() {
        GridItem() {
          Text('gridRowsGap1Test1').backgroundColor(0xF9CF93).width('100%').height('100%')
        }

        GridItem() {
          Text('gridRowsGap1Test2').backgroundColor(0xF9CF93).width('100%').height('100%')
        }
      }.height('30%')
      .rowsTemplate('1fr 1fr 1fr ')
      .rowsGap(-1)
      .id('gridRowsGap2')

      Grid() {
        GridItem() {
          Text('gridRowsGap1Test1').backgroundColor(0xF9CF93).width('100%').height('100%')
        }

        GridItem() {
          Text('gridRowsGap1Test2').backgroundColor(0xF9CF93).width('100%').height('100%')
        }
      }.height('30%')
      .rowsTemplate('1fr 1fr 1fr ')
      .rowsGap(this.len)
      .id('gridRowsGap3')

      Button('GridRowsGap')
        .onClick(() => {
          this.len = $r('app.string.length')
        })
    }
  }
}