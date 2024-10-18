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
import listEnableScrollInteractionTest from '../MyTest/ListEnableScrollInteractionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListEnableScrollInteractionSample {
  @State xOffset: number = 0;
  @State yOffset: number = 1200;
  @State enableScrollInteraction: boolean = false
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  aboutToAppear(): void {
    loadComponentTestEntry(listEnableScrollInteractionTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('50%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          }, (item: string) => item)
        }
        .width('100%')
        .height('80%')
        .border({ width: 3, color: Color.Red })
        .enableScrollInteraction(this.enableScrollInteraction)
        .id('listEnableScrollInteraction')

        Button('ListEnableScrollInteraction')
          .margin('5vp')
          .onClick(() => {
            this.enableScrollInteraction = !this.enableScrollInteraction;
          })
      }
      .backgroundColor(0xDCDCDC)
    }
  }
}