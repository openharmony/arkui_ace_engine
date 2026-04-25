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

/**
 * Radio WithTheme + radioStyle 自定义颜色优先级测试
 *
 * 测试点（通过 Test++/Test-- 切换用例）：
 * 0. 无 WithTheme、无 radioStyle —— 系统默认颜色
 * 1. WithTheme 自定义主题、无 radioStyle —— Radio 颜色跟随自定义主题
 * 2. WithTheme + radioStyle.checkedBackgroundColor —— checkedBackgroundColor 以 radioStyle 为准
 * 3. WithTheme + radioStyle.uncheckedBorderColor —— uncheckedBorderColor 以 radioStyle 为准
 * 4. WithTheme + radioStyle.indicatorColor —— indicatorColor 以 radioStyle 为准
 * 5. WithTheme + radioStyle 全部自定义颜色 —— 三个颜色均以 radioStyle 为准
 * 6. WithTheme 深色模式 + radioStyle 自定义颜色 —— 深色背景 + radioStyle 指定颜色
 * 7. WithTheme 自定义主题 + 深色模式 + radioStyle 自定义颜色 —— 三者叠加
 *
 * 预期：
 * - 用例0：全局Radio和测试Radio颜色一致，均为系统默认
 * - 用例1：测试Radio已选中背景色 #9370DB，未选中边框 #DDA0DD，指示器 #FFFAF0；全局Radio不变
 * - 用例2：checkedBackgroundColor 为 #FF4500（覆盖主题色），其余颜色跟随主题
 * - 用例3：uncheckedBorderColor 为 #32CD32（覆盖主题色），其余颜色跟随主题
 * - 用例4：indicatorColor 为 #FFD700（覆盖主题色），其余颜色跟随主题
 * - 用例5：checkedBackgroundColor=#FF4500, uncheckedBorderColor=#32CD32, indicatorColor=#FFD700，全部覆盖主题色
 * - 用例6：背景为深色模式样式，checkedBackgroundColor=#FF6347, indicatorColor=#FFFF00
 * - 用例7：自定义主题 + 深色模式叠加背景，checkedBackgroundColor=#00CED1, indicatorColor=#FF69B4
 * - 全局对比参照Radio始终不随 Test++/Test-- 切换而变化
 */

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';
import { ConfigurationConstant } from '@kit.AbilityKit';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioWithTheme3Builder(name: string, param: Object) {
  RadioWithTheme3()
}

export class RadioCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class PurpleColors implements CustomColors {
  public compBackgroundEmphasize = '#9370DB'
  public iconOnPrimary = '#FFFAF0'
  public iconFourth = '#DDA0DD'
}

interface TestCase {
  info: string
  themeOptions?: WithThemeOptions
  checkedBackgroundColor?: ResourceColor
  uncheckedBorderColor?: ResourceColor
  indicatorColor?: ResourceColor
}

@Entry
@Component
struct RadioWithTheme3 {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0
  private testCases: TestCase[] = [
    {
      info: '0-无WithTheme，无自定义颜色'
    },
    {
      info: '1-WithTheme自定义主题，无radioStyle自定义颜色',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()) }
    },
    {
      info: '2-WithTheme自定义主题 + radioStyle自定义checkedBackgroundColor',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()) },
      checkedBackgroundColor: '#FF4500'
    },
    {
      info: '3-WithTheme自定义主题 + radioStyle自定义uncheckedBorderColor',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()) },
      uncheckedBorderColor: '#32CD32'
    },
    {
      info: '4-WithTheme自定义主题 + radioStyle自定义indicatorColor',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()) },
      indicatorColor: '#FFD700'
    },
    {
      info: '5-WithTheme自定义主题 + radioStyle全部自定义颜色',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()) },
      checkedBackgroundColor: '#FF4500',
      uncheckedBorderColor: '#32CD32',
      indicatorColor: '#FFD700'
    },
    {
      info: '6-WithTheme深色模式 + radioStyle自定义颜色',
      themeOptions: { colorMode: ThemeColorMode.DARK },
      checkedBackgroundColor: '#FF6347',
      indicatorColor: '#FFFF00'
    },
    {
      info: '7-WithTheme自定义主题 + 深色模式 + radioStyle自定义颜色',
      themeOptions: { theme: new RadioCustomTheme(new PurpleColors()), colorMode: ThemeColorMode.DARK },
      checkedBackgroundColor: '#00CED1',
      indicatorColor: '#FF69B4'
    },
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Divider()
          Text('Radio WithTheme + radioStyle自定义颜色')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Divider()
          Row({ space: 5 }) {
            Text(`${this.index} /`)
              .fontSize(15)
            Text(`${this.testCases.length - 1}`)
              .fontSize(15)
              .key('totalTest')
            Text('Test++')
              .fontSize(15)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .onClick(() => {
                this.index++
                if (this.index >= this.testCases.length) {
                  this.index = 0
                }
              })
            Text('Test--')
              .fontSize(15)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .onClick(() => {
                this.index--
                if (this.index < 0) {
                  this.index = this.testCases.length - 1
                }
              })
          }

          Divider()
          Text('全局Radio（对比参照）：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
            Column({ space: 5 }) {
              Text('未选中').fontSize(12)
              Radio({ value: 'R1_ref', group: 'refGroup3' })
                .checked(false)
                .height(50)
                .width(50)
                .key('Radio_Ref3_Unchecked')
            }
            Column({ space: 5 }) {
              Text('已选中').fontSize(12)
              Radio({ value: 'R2_ref', group: 'refGroup3' })
                .checked(true)
                .height(50)
                .width(50)
                .key('Radio_Ref3_Checked')
            }
          }.width('100%')

          Divider()
          Text('测试Radio：')
            .fontSize(14)
            .width('100%')
          WithTheme(this.testCases[this.index].themeOptions) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_test', group: 'testGroup3' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .radioStyle({
                      checkedBackgroundColor: this.testCases[this.index].checkedBackgroundColor,
                      uncheckedBorderColor: this.testCases[this.index].uncheckedBorderColor,
                      indicatorColor: this.testCases[this.index].indicatorColor,
                    })
                    .key('Radio_Test3_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_test', group: 'testGroup3' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .radioStyle({
                      checkedBackgroundColor: this.testCases[this.index].checkedBackgroundColor,
                      uncheckedBorderColor: this.testCases[this.index].uncheckedBorderColor,
                      indicatorColor: this.testCases[this.index].indicatorColor,
                    })
                    .key('Radio_Test3_Checked')
                }
              }.width('100%')

              Text('Radio组：')
                .fontSize(12)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('选项A').fontSize(12)
                  Radio({ value: 'A3', group: 'testRadioGroup3' })
                    .checked(true)
                    .height(40)
                    .width(40)
                    .radioStyle({
                      checkedBackgroundColor: this.testCases[this.index].checkedBackgroundColor,
                      uncheckedBorderColor: this.testCases[this.index].uncheckedBorderColor,
                      indicatorColor: this.testCases[this.index].indicatorColor,
                    })
                    .key('Radio_Test3_A')
                }
                Column({ space: 5 }) {
                  Text('选项B').fontSize(12)
                  Radio({ value: 'B3', group: 'testRadioGroup3' })
                    .height(40)
                    .width(40)
                    .radioStyle({
                      checkedBackgroundColor: this.testCases[this.index].checkedBackgroundColor,
                      uncheckedBorderColor: this.testCases[this.index].uncheckedBorderColor,
                      indicatorColor: this.testCases[this.index].indicatorColor,
                    })
                    .key('Radio_Test3_B')
                }
                Column({ space: 5 }) {
                  Text('选项C').fontSize(12)
                  Radio({ value: 'C3', group: 'testRadioGroup3' })
                    .height(40)
                    .width(40)
                    .radioStyle({
                      checkedBackgroundColor: this.testCases[this.index].checkedBackgroundColor,
                      uncheckedBorderColor: this.testCases[this.index].uncheckedBorderColor,
                      indicatorColor: this.testCases[this.index].indicatorColor,
                    })
                    .key('Radio_Test3_C')
                }
              }.width('100%')
            }
            .backgroundColor($r('sys.color.background_primary'))
            .width('100%')
            .padding(10)
          }

          Divider()
          Text(this.testCases[this.index].info)
            .fontSize(14)
            .fontColor(Color.Orange)
            .width('100%')
        }
        .padding({ left: 15, right: 15 })
      }
      .scrollBar(BarState.Off)
      .width('100%')
    }
    .title('RadioWithTheme3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
