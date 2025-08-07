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

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';

@Builder
export function ButtonLevel11Builder(name: string, param: Object) {
  ButtonLevel11Example()
}

export class PageCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class DefaultTheme implements CustomColors {
  public fontEmphasize = '#F0E68C'
  public compBackgroundTertiary = 'rgb(226, 132, 96)'
}

const customDefaultTheme: CustomTheme = new PageCustomTheme(new DefaultTheme());
ThemeControl.setDefaultTheme(customDefaultTheme);

export class Colors implements CustomColors {
  public fontEmphasize = 'rgb(22, 83, 5)'
  public compBackgroundTertiary = '#00CED1'
}

export class RedColors implements CustomColors {
  public fontEmphasize = 'rgb(22, 83, 5)'
  public compBackgroundTertiary = '#FFD53032'
  public backgroundEmphasize = '#FFD00000'
  public warning = '#FF4500'
  public brand = '#33FF1111'
}

export class GreenColors implements CustomColors {
  public fontEmphasize = Color.Orange
  public compBackgroundTertiary = 'rgb(0, 128, 0)'
  public warning = 'rgb(22, 83, 5)'
  public brand = $r('app.color.Color_test3')
}

interface CasesObject {
  info?: string
  themeOptions?: WithThemeOptions,
  fontColor?: ResourceColor,
  backgroundColor?: ResourceColor
}

@Entry
@Component
struct ButtonLevel11Example {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0
  private testCases: CasesObject[] = [
    {
      info: '0-全undefined'
    },
    {
      info: '1-局部适配theme',
      themeOptions: { theme: new PageCustomTheme(new RedColors) }
    },
    {
      info: '2-局部深色模式，theme不传',
      themeOptions: { colorMode: ThemeColorMode.DARK }
    },
    {
      info: '3-局部浅色模式，theme传',
      themeOptions: { theme: new PageCustomTheme(new GreenColors), colorMode: ThemeColorMode.LIGHT }
    },
    {
      info: '4-局部深色模式，theme传',
      themeOptions: { theme: new PageCustomTheme(new RedColors), colorMode: ThemeColorMode.DARK }
    },
    {
      info: '5-局部适配theme，有自定义文本和背景颜色',
      themeOptions: { theme: new PageCustomTheme(new GreenColors) },
      fontColor: $r('app.color.Color_orange'),
      backgroundColor: $r('app.color.Color_test3')
    },
    {
      info: '6-局部适配theme，有自定义文本和背景颜色，深色模式',
      themeOptions: { theme: new PageCustomTheme(new GreenColors), colorMode: ThemeColorMode.DARK },
      fontColor: $r('app.color.Color_orange'),
      backgroundColor: $r('app.color.Color_test3')
    },
  ]

  build() {
    NavDestination() {
      Row() {
        Scroll() {
          Column({ space: 10 }) {
            Divider()
            Row({ space: 5 }) {
              Text(`${this.index} /`)
                .fontSize(15)
                .focusable(false)
              Text(`${this.testCases.length - 1}`)
                .fontSize(15)
                .key(`totalTest`)
                .focusable(false)
              Text('Test++')
                .fontSize(15)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .focusable(false)
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
                .focusable(false)
                .onClick(() => {
                  this.index--
                  if (this.index < 0) {
                    this.index = this.testCases.length - 1
                  }
                })
            }

            Button('应用级全局按钮验证',
              { buttonStyle: ButtonStyleMode.NORMAL, controlSize: ControlSize.SMALL })
              .key('Button11')

            WithTheme({ theme: new PageCustomTheme(new Colors) }) {
              Column({ space: 10 }) {
                Divider()
                Button('最外层设置主题',
                  { buttonStyle: ButtonStyleMode.NORMAL, controlSize: ControlSize.SMALL })
                  .key('Button00')

                Text('局部主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')
                WithTheme(this.testCases[this.index].themeOptions) {
                  Column({ space: '8vp' }) {
                    Button('NORMAL 正常普通按钮',
                      { buttonStyle: ButtonStyleMode.NORMAL, controlSize: ControlSize.NORMAL })
                      .key('Button01')
                    Button('EMPHASIZED 强调按钮',
                      { buttonStyle: ButtonStyleMode.EMPHASIZED })
                      .key('Button02')
                    Button('TEXTUAL 文本按钮',
                      { buttonStyle: ButtonStyleMode.TEXTUAL, controlSize: ControlSize.NORMAL })
                      .key('Button03')
                    Button('NORMAL role 正常按钮',
                      { role: ButtonRole.NORMAL, controlSize: ControlSize.SMALL })
                      .key('Button04')
                    Button('ERROR role  警示按钮',
                      { role: ButtonRole.ERROR, controlSize: ControlSize.SMALL })
                      .key('Button05')
                    Button('Normal 普通按钮', { type: ButtonType.Normal })
                      .key('Button06')
                    Button('Capsule 胶囊按钮', { type: ButtonType.Capsule })
                      .width(200)
                      .height(60)
                      .key('Button07')
                    Button('Circle 圆形按钮', { type: ButtonType.Circle })
                      .height(60)
                      .key('Button08')
                    Button('圆角矩形按钮', { type: ButtonType.ROUNDED_RECTANGLE })
                      .width(200)
                      .height(60)
                      .key('Button09')
                    Button('自定义颜色按钮')
                      .key('Button10')
                      .fontColor(this.testCases[this.index].fontColor)
                      .backgroundColor(this.testCases[this.index].backgroundColor)
                  }
                  .backgroundColor($r('sys.color.background_primary'))
                  .width('100%')
                }

                Divider()
                Text(this.testCases[this.index].info)
                  .fontSize(12)
              }
            }
          }
        }
        .scrollBar(BarState.Off)
        .width('100%')
      }
    }
    .title('ButtonLevel11')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}