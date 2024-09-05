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
import gridScrollBarColorTest from '../MyTest/GridScrollBarColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridScrollBarColorSample {
  numbers: String[] = ['0', '1', '2', '3', '4']
  @State barColor: string | number | Color = 'rgb(255,100,255)'

  aboutToAppear(): void {
    loadComponentTestEntry(gridScrollBarColorTest)
  }

  build() {
    Column() {
      Grid() {
        ForEach(this.numbers, () => {
          ForEach(this.numbers, (day: string) => {
            GridItem() {
              Text('gridScrollBarColorTest' + day)
                .backgroundColor(0xF9CF93)
                .width('100%')
                .height(80)
            }
          }, (day: string) => day)
        }, (day: string) => day)
      }
      .width('100%')
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      .scrollBarColor(Color.Orange)
      .height(250)
      .id('gridScrollBarColor1')

      Grid() {
        ForEach(this.numbers, () => {
          ForEach(this.numbers, (day: string) => {
            GridItem() {
              Text('gridScrollBarColorTest' + day)
                .backgroundColor(0xF9CF93)
                .width('100%')
                .height(80)
            }
          }, (day: string) => day)
        }, (day: string) => day)
      }
      .width('100%')
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      .scrollBarColor(this.barColor)
      .height(250)
      .id('gridScrollBarColor2')

      Button('GridScrollBarColor')
        .onClick(() => {
          this.barColor = 0xffa500
        })
    }.width('100%')
  }
}