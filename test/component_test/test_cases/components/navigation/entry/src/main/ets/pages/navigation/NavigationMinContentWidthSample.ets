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
import navigationMinContentWidthTest from '../MyTest/NavigationMinContentWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationMinContentWidthSample {
  aboutToAppear(): void {
    loadComponentTestEntry(navigationMinContentWidthTest)
  }

  @State minContentWidth: Dimension = '300vp'
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

  build() {
    Column() {
      Navigation() {
        TextInput({ placeholder: 'search...' })
          .width('90%')
          .height(40)
          .backgroundColor('#FFFFFF')
          .margin({ top: 8 })

        List({ space: 12, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('80%')
                .height(72)
                .backgroundColor(Color.Pink)
                .borderRadius(24)
                .fontSize(16)
                .fontWeight(500)
                .textAlign(TextAlign.Center)
            }
          }, (item: number) => item.toString())
        }
        .height(324)
        .width('100%')
        .margin({ top: 12, left: '10%' })
      }
      .height(300)
      .minContentWidth(this.minContentWidth)
      .mode(NavigationMode.Split)
      .id('navigationMinContentWidth')

      Button('NavigationMinContentWidth1')
        .onClick(() => {
          this.minContentWidth = '10lpx'
        })
      Button('NavigationMinContentWidth2')
        .onClick(() => {
          this.minContentWidth = '5fp'
        })
    }
  }
}