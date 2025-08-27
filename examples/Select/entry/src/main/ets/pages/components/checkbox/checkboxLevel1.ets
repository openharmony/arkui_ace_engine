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

import { SymbolGlyphModifier, ThemeControl } from '@kit.ArkUI';

@Builder
export function CheckboxLevel1Builder(name: string, param: Object) {
  CheckboxLevel1Example()
}

ThemeControl.setDefaultTheme(undefined);

interface testCaseOptions {
  testInfo?: string | undefined
  controlSize?: ControlSize | undefined
  width?: Length | undefined
  height?: Length | undefined
  size?: Length | undefined
}

@Entry
@Component
struct CheckboxLevel1Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller
  @State selectedDate: Date = new Date()
  @State index: number[] = [0, 0, 0, 0]
  @State show: boolean = false
  testCase: testCaseOptions[] = [
    {
      testInfo: '1.1 正常，都未加参数'
    },
    {
      testInfo: '1.2 ControlSize.SMALL',
      controlSize: ControlSize.SMALL
    },
    {
      testInfo: '1.3 controlSize: undefined',
      controlSize: undefined
    },
    {
      testInfo: '1.4 固定宽高、字体大小、ControlSize.NORMAL',
      width: 300,
      height: 150,
      size: '120px',
      controlSize: ControlSize.NORMAL
    },
    {
      testInfo: '1.5 固定宽高、字体undefined',
      width: 200,
      height: 10,
      size: undefined,
    },
    {
      testInfo: '1.6 宽高undefined、字体固定、ControlSize.SMALL',
      width: undefined,
      height: undefined,
      size: '100lpx',
      controlSize: ControlSize.SMALL
    },
    {
      testInfo: '1.7 字体固定',
      size: '40fp',
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
            .focusable(false)
            .onClick(() => {
              this.show = !this.show
            })

          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + '/')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .focusable(false)
            Text(`${this.testCase.length}`).key('SelectLevel1_4')
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
          Text('验证Select适老化')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')

          Column() {
            Select([{
              value: 'aaa',
              symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_star')).fontColor([Color.Red])
            },
              {
                value: '超长超长长长发生的个地方bbb',
                icon: $r('app.media.app_icon')
              },
              {
                value: 'ccc',
                symbolIcon: new SymbolGlyphModifier($r('sys.symbol.exposure')).fontColor([Color.Green])
              },
              {
                value: 'ddd',
                icon: $r('app.media.app_icon')
              }])
              .key('Select001')
              .value('请点击选择')
              .font({ size: this.testCase[this.index[0]].size })
              .fontColor($r('sys.color.font_primary'))
              .selectedOptionFont({ size: this.testCase[this.index[0]].size })
              .optionFont({ size: this.testCase[this.index[0]].size })
              .controlSize(this.testCase[this.index[0]].controlSize)
              .width(this.testCase[this.index[0]].width)
              .height(this.testCase[this.index[0]].height)
              .arrowPosition(ArrowPosition.END)
              .onSelect((index: number, text?: string | undefined) => {
                console.info('lhg-Select: ' + index + ' ' + text)
              })
          }
          .height('75%')
          .width('100%')

          Divider()
          if (this.show) {
            Text(this.testCase[this.index[0]].testInfo)
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
          }
        }
        .height('100%')
        .width('100%')
      }
      .scrollBar(BarState.Off)
    }
    .title('CheckboxLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}