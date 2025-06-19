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

import { getParamsInfo } from './util';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function SliderLevel11Builder(name: string, param: Object) {
  Slider_Level1_1()
}

ThemeControl.setDefaultTheme(null);

interface objectSample {
  value?: number | undefined,
  min?: number | undefined,
  max?: number | undefined,
  step?: number | undefined,
  style?: SliderStyle,
  direction?: Axis,
  reverse?: boolean | undefined,
  accessibilityText?: string | undefined,
  accessibilityDescription?: string | undefined,
  accessibilityText1?: Resource | undefined,
  accessibilityDescription1?: Resource | undefined,
  accessibilityLevel?: string | undefined,
  direction1?: Direction | undefined,
}

@Entry
@Component
struct Slider_Level1_1 {
  pathStack: NavPathStack = new NavPathStack()
  @State text1: number | undefined = undefined
  @State index: number = 0
  @State show: boolean = false
  testCases: Array<objectSample> = [
    {
      //0
      value: 4.1,
      min: 3,
      max: 8,
      step: 1.5,
      style: SliderStyle.OutSet,
      direction: Axis.Horizontal,
      reverse: false,
      accessibilityText: '横向滑动条',
      accessibilityDescription: '可上下左右滑动调节',
      accessibilityText1: $r('app.string.rTrackThickness'),
      accessibilityDescription1: $r('app.string.EntryAbility_desc')
    },
    {
      //1
      value: 5,
      min: 3,
      max: 8,
      step: 1.5,
      style: SliderStyle.InSet,
      direction: Axis.Vertical,
      reverse: true,
      accessibilityText: '竖向滑动条',
      accessibilityDescription: '左右上下可滑动调节',
      accessibilityText1: $r('sys.string.ohos_id_text_camera_input'),
      accessibilityDescription1: $r('sys.string.ohos_unstable_connect_server')
    },
    {
      //2
      value: 7,
      min: 3,
      max: 8,
      step: 1.5,
      style: SliderStyle.OutSet,
      direction: Axis.Horizontal,
      reverse: true,
      accessibilityText: 'Level no',
      accessibilityDescription: 'Level nonono',
      accessibilityLevel: 'no'
    },
    {
      //3
      value: 7.7,
      min: 3,
      max: 8,
      step: 1.5,
      style: SliderStyle.InSet,
      direction: Axis.Vertical,
      reverse: false,
      accessibilityText: 'no-hide-descendants',
      accessibilityDescription: 'Level 所有组件',
      accessibilityLevel: 'no-hide-descendants'
    },
    {
      //4
      value: 2,
      min: 1,
      max: 8,
      step: 2,
      style: SliderStyle.InSet,
      direction: Axis.Vertical,
      reverse: true,
      accessibilityText: '',
      accessibilityDescription: '',
    },
    {
      //5
      value: 4,
      min: 1,
      max: 8,
      step: 2,
      style: SliderStyle.OutSet,
      direction: Axis.Horizontal,
      reverse: false,
      direction1: Direction.Rtl,
      accessibilityText: '从右到左',
      accessibilityDescription: 'RTL反方向'
    },
    {
      //6
      value: 6,
      min: 1,
      max: 8,
      step: 2,
      style: SliderStyle.InSet,
      direction: Axis.Vertical,
      reverse: true
    },
    {
      //7
      value: 7.5,
      min: 1,
      max: 8,
      step: 2,
      style: SliderStyle.OutSet,
      direction: Axis.Horizontal,
      reverse: false,
      direction1: Direction.Auto
    }
  ]

  aboutToAppear(): void {
    this.text1 = this.testCases[this.index].value
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('获焦滑动').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row() {
            Slider({
              value: this.text1,
              min: this.testCases[this.index].min,
              max: this.testCases[this.index].max,
              step: this.testCases[this.index].step,
              style: this.testCases[this.index].style,
              direction: this.testCases[this.index].direction,
              reverse: this.testCases[this.index].reverse
            })
              .key('Slider_01')
              .width('80%')
              .height('50%')
              .showTips(true, this.text1?.toFixed(2))
              .showSteps(true)
              .onChange((value: number) => {
                this.text1 = value
              })
              .direction(this.testCases[this.index].direction1)
              .accessibilityText(this.testCases[this.index].accessibilityText)
              .accessibilityDescription(this.testCases[this.index].accessibilityDescription)
              .accessibilityLevel(this.testCases[this.index].accessibilityLevel)

            Text(this.text1?.toFixed(2)).fontSize(12)
          }

          Divider()
          Text('切换测试参数,显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%').onClick(() => {
            this.show = !this.show
          })
          Row({ space: 4 }) {
            Text(`${this.index} /`)
            Text(`${this.testCases.length - 1}`)
              .key(`totalTest2`)
            Text('Test++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.index++
                if (this.index >= this.testCases.length) {
                  this.index = 0
                }
                this.text1 = this.testCases[this.index].value
              })
            Text('Test--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.index--
                if (this.index < 0) {
                  this.index = this.testCases.length - 1
                }
                this.text1 = this.testCases[this.index].value
              })
          }

          Slider({})
            .key('Slider_02')
            .width('80%')
            .height('20%')
            .accessibilityText(this.testCases[this.index].accessibilityText1)
            .accessibilityDescription(this.testCases[this.index].accessibilityDescription1)

          if (this.show) {
            Text(getParamsInfo(this.testCases[this.index]))
          }
        }
        .width('100%')
        .align(Alignment.Top)
      }.scrollBar(BarState.Off)
    }
    .title('SliderLevel11')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}