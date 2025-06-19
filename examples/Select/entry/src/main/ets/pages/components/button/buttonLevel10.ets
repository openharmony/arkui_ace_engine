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

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ButtonLevel10Builder(name: string, param: Object) {
  ButtonLevel10Example()
}

interface testCaseOptions {
  testInfo?: string | undefined
  label?: string | Resource
  type?: ButtonType
  role?: ButtonRole
  buttonStyle?: ButtonStyleMode
  controlSize?: ControlSize
  width?: Length | undefined
  height?: Length | undefined
  size?: Length | undefined
  overflow?: TextOverflow | undefined
  maxLines?: number | undefined
  maxFontSize?: Length | undefined
}

@Entry
@Component
struct ButtonLevel10Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller
  @State selectedDate: Date = new Date()
  @State selectTime: Date = new Date()
  @State index: number[] = [0, 0, 0, 0]
  @State show: boolean = false
  testCase: testCaseOptions[] = [
    {
      testInfo: '1',
      label: '按钮正常',
    },
    {
      testInfo: '2',
      label: 'Success is not final, failure is not fatal: it is the courage to continue that counts.',
      controlSize: ControlSize.NORMAL,
      type: ButtonType.Circle,
      buttonStyle: ButtonStyleMode.NORMAL,
      overflow: TextOverflow.Clip,
    },
    {
      testInfo: '3',
      label: '按钮文本换行过长超过一行后\nThe expert in anything was once a beginner.',
      controlSize: ControlSize.SMALL,
      type: undefined,
      buttonStyle: ButtonStyleMode.TEXTUAL,
      overflow: undefined,
    },
    {
      testInfo: '4',
      label: '按钮正常',
      controlSize: undefined,
      type: ButtonType.Normal,
      buttonStyle: ButtonStyleMode.NORMAL,
      overflow: TextOverflow.Clip,
    },
    {
      testInfo: '5',
      label: '跑马灯按钮文本过长超过一行后Education is not the filling of a pail, but the lighting of a fire.',
      controlSize: ControlSize.SMALL,
      type: ButtonType.Capsule,
      buttonStyle: undefined,
      overflow: TextOverflow.MARQUEE
    },
    {
      testInfo: '6',
      label: '最多两行设置一下Success is not final, failure is not fatal: it is the courage to continue that counts.',
      controlSize: ControlSize.NORMAL,
      type: ButtonType.ROUNDED_RECTANGLE,
      buttonStyle: ButtonStyleMode.TEXTUAL,
      maxLines: 2
    },
    {
      testInfo: '7',
      label: '按钮正常7Don\'t watch the clock; do what it does. Keep going.',
      buttonStyle: ButtonStyleMode.EMPHASIZED,
      type: 0,
      maxLines: undefined
    },
    {
      testInfo: '8',
      label: '按钮正常8',
      role: ButtonRole.ERROR,
      width: 300,
      height: 100,
      size: '90px',
      type: 1,
      controlSize: ControlSize.SMALL
    },
    {
      testInfo: '9',
      label: '按钮正常',
      role: undefined,
      width: 200,
      height: 80,
      size: undefined,
      type: 2,
    },
    {
      testInfo: '10',
      label: '按钮正常',
      role: ButtonRole.ERROR,
      width: undefined,
      height: undefined,
      type: 3,
      size: '25lpx'
    },
    {
      testInfo: '11',
      label: '按钮正常',
      role: ButtonRole.NORMAL,
      size: '20fp',
      type: 10
    },
    {
      testInfo: '12',
      label: '按钮50vp正常',
      role: ButtonRole.ERROR,
      size: '80vp'
    },
    {
      testInfo: '13',
      label: 'maxFontSize限制最大字体大小看看适老化',
      maxFontSize: '20px'
    },
    {
      testInfo: '14',
      label: '',
    },
    {
      testInfo: '15',
      label: 'OO\nDD',
    }
  ]

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 10 }) {
          Divider()
          Text('切换参数，显示参数=' + this.show)
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .onClick(() => {
              this.show = !this.show
            })
            .focusable(false)

          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + '/')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .focusable(false)
            Text(`${this.testCase.length}`).key('ButtonLevel1_8')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .focusable(false)
            Text('Test++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .focusable(false)
              .onClick(() => {
                this.index[0]++
                if (this.index[0] == this.testCase.length) {
                  this.index[0] = 0
                }
              })

            Text('Test--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .focusable(false)
              .onClick(() => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.testCase.length - 1
                }
              })
          }

          Divider()
          Text('验证Button适老化')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .focusable(false)

          Column({ space: 4 }) {
            Text('Button未设置任何属性')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .focusable(false)
            Button(this.testCase[this.index[0]].label)
              .key('Button000')
            Text('ButtonOptions设置type、buttonStyle、controlSize、role')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .focusable(false)
            Button(
              this.testCase[this.index[0]].label,
              {
                type: this.testCase[this.index[0]].type,
                buttonStyle: this.testCase[this.index[0]].buttonStyle,
                controlSize: this.testCase[this.index[0]].controlSize,
                role: this.testCase[this.index[0]].role
              })
              .width(this.testCase[this.index[0]].width)
              .height(this.testCase[this.index[0]].height)
              .fontSize(this.testCase[this.index[0]].size)
              .borderRadius(10)
              .key('Button001')

            Text('ButtonOptions设置type、buttonStyle、controlSize、role，子组件包含了Text')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .focusable(false)
            Button(
              {
                type: this.testCase[this.index[0]].type,
                buttonStyle: this.testCase[this.index[0]].buttonStyle,
                controlSize: this.testCase[this.index[0]].controlSize,
                role: this.testCase[this.index[0]].role
              }) {
              Text(this.testCase[this.index[0]].label)
            }
            .width(this.testCase[this.index[0]].width)
            .height(this.testCase[this.index[0]].height)
            .fontSize(this.testCase[this.index[0]].size)
            .borderRadius(10)
            .key('Button002')

            Text('属性设置type、buttonStyle、controlSize、role，加了labelStyle')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .focusable(false)
            Button(this.testCase[this.index[0]].label)
              .type(this.testCase[this.index[0]].type)
              .buttonStyle(this.testCase[this.index[0]].buttonStyle)
              .controlSize(this.testCase[this.index[0]].controlSize)
              .role(this.testCase[this.index[0]].role)
              .labelStyle({
                overflow: this.testCase[this.index[0]].overflow,
                maxLines: this.testCase[this.index[0]].maxLines,
                maxFontSize: this.testCase[this.index[0]].maxFontSize,
                font: {
                  size: this.testCase[this.index[0]].size
                }
              })
              .width(this.testCase[this.index[0]].width)
              .height(this.testCase[this.index[0]].height)
              .borderRadius(10)
              .key('Button003')
          }
          .width('100%')

          Divider()
          if (this.show) {
            Text(JSON.stringify(this.testCase[this.index[0]]))
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
          }
        }
        .width('100%')
      }
      .scrollBar(BarState.Off)
    }
    .title('ButtonLevel10')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}