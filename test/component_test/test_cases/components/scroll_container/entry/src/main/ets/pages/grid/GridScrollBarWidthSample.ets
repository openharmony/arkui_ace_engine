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
import gridScrollBarWidthTest from '../MyTest/GridScrollBarWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridScrollBarWidthSample {
  numbers: String[] = ['0', '1', '2', '3', '4']
  @State widLength: string | number = '10px'

  aboutToAppear(): void {
    loadComponentTestEntry(gridScrollBarWidthTest)
  }

  build() {
    Column({ space: 5 }) {
      Grid() {
        ForEach(this.numbers, () => {
          ForEach(this.numbers, (day: string) => {
            GridItem() {
              Text('GridScrollBarWidth' + day)
                .backgroundColor(0xF9CF93)
                .width('100%')
                .height(80)
            }
          }, (day: string) => day)
        }, (day: string) => day)
      }
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      .scrollBarWidth(this.widLength)
      .height(250)
      .id('gridScrollBarWidth')

      Button('GridScrollBarWidth')
        .onClick(() => {
          this.widLength = 10
        })
    }
  }
}