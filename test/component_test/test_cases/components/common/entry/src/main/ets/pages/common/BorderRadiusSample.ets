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

import borderRadiusTest from '../MyTest/BorderRadiusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderRadiusSample {
  private appleFruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  @State borderRadiusOne: number | Resource = 10
  @State borderRadiusTwo: number | Resource = 30

  aboutToAppear(): void {
    loadComponentTestEntry(borderRadiusTest)
  }

  build() {
    Column() {
      TextTimer()
        .backgroundColor(0x00FFFF)
        .id('textTimer1')
        .borderRadius('10px')
      TextTimer()
        .backgroundColor(0xAAFFAA)
        .id('textTimer2')
        .borderRadius(this.borderRadiusOne)

      Button('ButtonBorderRadius1')
        .onClick((event: ClickEvent) => {
          this.borderRadiusOne = $r('app.string.border_radius')
        })

      Row() {
        TextPicker({ range: this.appleFruits, selected: 2 })
          .onChange((value: string | string[], index: number | number[]) => {
          })
          .backgroundColor(0xa52a2a)
          .id('textPicker1')
          .borderRadius({
            topLeft: '100',
            topRight: '100',
            bottomLeft: '100',
            bottomRight: '100'
          })

        TextPicker({ range: this.appleFruits, selected: 1 })
          .onChange((value: string | string[], index: number | number[]) => {
          })
          .backgroundColor(0x0000ff)
          .id('textPicker2')
          .borderRadius({
            topLeft: this.borderRadiusTwo,
            topRight: this.borderRadiusTwo,
            bottomLeft: this.borderRadiusTwo,
            bottomRight: this.borderRadiusTwo
          })

        Button('ButtonBorderRadius2')
          .onClick((event: ClickEvent) => {
            this.borderRadiusTwo = $r('app.string.border_radius')
          })
      }
    }
  }
}