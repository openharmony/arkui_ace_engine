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
import listChainAnimationTest from '../MyTest/ListChainAnimationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListChainAnimationSample {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State chainAnimation: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(listChainAnimationTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          })
        }
        .height("80%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .chainAnimation(this.chainAnimation)
        .id('listChainAnimation')

        Button('ListChainAnimation')
          .margin('5vp')
          .onClick(() => {
            this.chainAnimation = !this.chainAnimation
          })
      }
      .backgroundColor(0xDCDCDC)
    }
  }
}