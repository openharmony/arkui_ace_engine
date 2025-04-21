/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { webview } from '@kit.ArkWeb'

@Entry
@Component
struct OnContentWillChange {
  @State nums: number[] = []
  @State currentIndex: number = 0
  @State inputIndex: number = 0
  private controller: TabsController = new TabsController()
  private webController0: WebviewController = new webview.WebviewController();
  private webController1: WebviewController = new webview.WebviewController();

  aboutToAppear(): void {
    for (let i = 0; i < 4; i++) {
      this.nums.push(i)
    }
  }

  build() {
    Column() {
      Tabs({ index: this.currentIndex, controller: this.controller }) {
        TabContent() {
          Web({ src: 'test', controller: this.webController0 }).width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar('green')

        TabContent() {
          Web({ src: 'test', controller: this.webController1 }).width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar('blue')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar('yellow')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar('pink')
      }
      .height(500)
      .onChange((index: number) => {
        this.currentIndex = index
      })
      .onContentWillChange((currentIndex: number, comingIndex: number) => {
        console.info(('onContentWillChange currentIndex:' + currentIndex + ', comingIndex:' + comingIndex))
        return true
      })

      Row() {
        TextInput({ placeholder: 'input index' })
          .width('30%')
          .margin({ right: 10 })
          .inputFilter('[0-9]', (e) => {
            console.log('inputFilter' + JSON.stringify(e))
          })
          .onChange((value: string) => {
            this.inputIndex = parseInt(value)
          })

        Button('changeIndex')
          .onClick(() => {
            if (this.inputIndex >= 0 && this.inputIndex < this.nums.length) {
              this.controller.changeIndex(this.inputIndex)
            }
          })
        Button('index')
          .onClick(() => {
            if (this.inputIndex >= 0 && this.inputIndex < this.nums.length) {
              this.currentIndex = this.inputIndex
            }
          })
      }.margin({ top: 10 })
    }
  }
}