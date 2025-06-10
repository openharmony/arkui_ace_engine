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

import { ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderLevel12Builder(name: string, param: Object) {
  Slider_Level1_2()
}

@Entry
@Component
struct Slider_Level1_2 {
  pathStack: NavPathStack = new NavPathStack()
  @State outSetValueOne: number = 40
  @State inSetValueTwo: number = 40
  @State vOutSetValueOne: number = 40
  @State vInSetValueOne: number = 40
  @State handlePopup: boolean = false
  @State num: number = 0
  @State margin1: Margin | Length | undefined = {}
  @State margin2: Margin | Length | undefined = {}

  build() {
    NavDestination() {
      Column({ space: 8 }) {
        Row() {
          Text(`横向动态切换位置测试`)
          Button() {
            Text('Num++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .focusable(false)
          .key('Num1')
          .margin(5)
          .onClick(() => {
            this.num++
            if (this.num > 1) {
              this.num = 0
              this.margin2 = {}
              this.margin1 = {}
            }
          })

          Button() {
            Text('Num--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .focusable(false)
          .key('Num2')
          .onClick(() => {
            this.num--
            if (this.num < 0) {
              this.num = 1
              this.margin2 = { top: '-3%' }
              this.margin1 = { right: '10%' }
            }
          })
        }.width('100%').margin({ left: '20vp' })

        Column() {
          Slider({
            value: this.vOutSetValueOne,
            style: SliderStyle.OutSet,
            direction: Axis.Horizontal
          })
            .width('50%')
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showTips(true)
            .onChange((value: number, mode: SliderChangeMode) => {
              this.vOutSetValueOne = value
              console.info('value:' + value + 'mode:' + mode.toString())
            })
          Text('横向避让测试').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(10)
        }.height('20%').backgroundColor(Color.Green).margin(this.margin2)

        Text(`纵向动态切换位置测试`)
        Row() {
          Slider({
            value: this.vOutSetValueOne,
            style: SliderStyle.OutSet,
            direction: Axis.Vertical
          })
            .height('20%')
            .blockColor('#191970')
            .trackColor('#ADD8E6')
            .selectedColor('#4169E1')
            .showTips(true)
            .margin(this.margin1)
            .key('slider1')
            .onChange((value: number, mode: SliderChangeMode) => {
              this.vOutSetValueOne = value
              console.info('value:' + value + 'mode:' + mode.toString())
            })
          Text('纵向避让测试').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(10)
        }.backgroundColor(Color.Red).width('60%').margin(this.margin1)
      }
    }
    .title('SliderLevel12')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}