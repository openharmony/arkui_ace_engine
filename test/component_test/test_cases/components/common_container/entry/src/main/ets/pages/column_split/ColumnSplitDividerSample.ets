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
import columnSplitDividerTest from '../MyTest/ColumnSplitDividerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ColumnSplitDividerSample {
  @State columnSplitDividerMargin: Dimension = '10fp'

  aboutToAppear(): void {
    loadComponentTestEntry(columnSplitDividerTest)
  }

  build() {
    Column() {
      ColumnSplit() {
        Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
        Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
      }
      .id('columnSplitDivider1')
      .borderWidth(1)
      .divider(null)
      .width('30%')
      .height(150)

      Row() {
        ColumnSplit() {
          Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
          Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
          Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        }
        .id('columnSplitDivider2')
        .borderWidth(1)
        .divider({ startMargin: $r('app.string.pixel_float_size'), endMargin: $r('app.string.pixel_float_size') })
        .width('30%')
        .height(150)

        ColumnSplit() {
          Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
          Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
          Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        }
        .id('columnSplitDivider3')
        .borderWidth(1)
        .divider({ startMargin: '100000%', endMargin: '100000%' })
        .width('30%')
        .height(150)

        ColumnSplit() {
          Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
          Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
          Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        }
        .id('columnSplitDivider4')
        .borderWidth(1)
        .divider({ startMargin: '10px', endMargin: '10px' })
        .width('30%')
        .height(150)
      }

      Row() {
        ColumnSplit() {
          Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
          Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
          Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        }
        .id('columnSplitDivider5')
        .borderWidth(1)
        .divider({ startMargin: '10vp', endMargin: '10vp' })
        .width('30%')
        .height(150)

        ColumnSplit() {
          Text('ColumnSplitText1').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
          Text('ColumnSplitText2').width('100%').height(20).backgroundColor(0xD2B48C).textAlign(TextAlign.Center)
          Text('ColumnSplitText3').width('100%').height(20).backgroundColor(0xF5DEB3).textAlign(TextAlign.Center)
        }
        .id('columnSplitDivider6')
        .borderWidth(1)
        .divider({ startMargin: this.columnSplitDividerMargin, endMargin: this.columnSplitDividerMargin })
        .width('30%')
        .height(150)

        Button('ColumnSplitDivider').onClick(() => {
          this.columnSplitDividerMargin = '10lpx'
        })
      }
    }
  }
}