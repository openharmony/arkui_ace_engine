/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import router from '@ohos.router'

@Entry
@Component
struct Search50019_2 {
  controller: SearchController = new SearchController()
  @State inputValue: string = ""
  @State isSupportAvoidance: boolean = true
  @State marginTop: number = 0
  @State cusHeight: number = 300
  @State focusable1: boolean = true

  // 自定义键盘组件
  @Builder CustomKeyboardBuilder() {
    Column() {

      Row() {
        Button('x')
          .width('50%')
          .onClick(() => {
          this.controller.stopEditing()
        })

        Button('focusable:' + this.focusable1)
          .width('50%')
          .onClick(() => {
            this.focusable1 = !this.focusable1
          })
      }.width('100%').margin({ top: 10 })
      Row() {
        Button('height+,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight += 10
          })

        Button('height-,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight -= 10
          })
      }.width('100%').margin({ top: 10 })
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }

  aboutToAppear() {
    this.marginTop = JSON.parse(JSON.stringify(router.getParams())).height
    this.isSupportAvoidance = JSON.parse(JSON.stringify(router.getParams())).isSupportAvoidance
  }

  build() {
    Scroll() {
      Column() {
        Text().height(this.marginTop)
        Search({ controller: this.controller, value: this.inputValue})
          .focusable(this.focusable1)
          .defaultFocus(true)
          .customKeyboard(this.CustomKeyboardBuilder(),{ supportAvoidance: this.isSupportAvoidance })
          // .margin({ top: this.marginTop })
          .border({ width: 1 })

      }.height('100%')
    }.height('100%')

  }
}