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
export function SelectLevel3Builder(name: string, param: Object) {
  SelectLevel3Example()
}

export class PageCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class DefaultTheme implements CustomColors {
  public fontPrimary = '#F0E68C'
  public compBackgroundTertiary = 'rgb(226, 132, 96)'
  public fontEmphasize = '#2E8B57'
  public iconPrimary = '#87CEFA'
  public compEmphasizeSecondary = '#C71585'
  public compDivider = '#FFE4E1'
}

const customDefaultTheme: CustomTheme = new PageCustomTheme(new DefaultTheme());
ThemeControl.setDefaultTheme(customDefaultTheme);

export class Colors implements CustomColors {
  public fontPrimary = 'rgb(22, 83, 5)'
  public compBackgroundTertiary = '#C71585'
  public fontEmphasize = '#FFD53032'
  public iconPrimary = '#FF7F50'
  public compEmphasizeSecondary = '#F0E68C'
  public compDivider = '#3CB371'
}

export class RedColors implements CustomColors {
  public fontPrimary = '#87CEEB'
  public compBackgroundTertiary = '#FFD700'
  public fontEmphasize = '#7B68EE'
  public iconPrimary = '#008080'
  public compEmphasizeSecondary = '#9400D3'
  public compDivider = '#DA70D6'
}

export class GreenColors implements CustomColors {
  public fontPrimary = $r('app.color.Color_test4')
  public compBackgroundTertiary = $r('app.color.Color_orange')
  public fontEmphasize = $r('app.color.Color_test3')
  public iconPrimary = $r('app.color.Color_orange')
  public compEmphasizeSecondary = $r('app.color.Color_test2')
  public compDivider = $r('app.color.Color_test3')
}

interface CasesObject1 {
  info?: string
  themeOptions?: WithThemeOptions,
  fontColor?: ResourceColor,
  backgroundColor?: ResourceColor,
  optionBgColor?: ResourceColor,
  optionFontColor?: ResourceColor,
  selectedOptionBgColor?: ResourceColor,
  selectedOptionFontColor?: ResourceColor,
  dividerColor?: ResourceColor
}

@Entry
@Component
struct SelectLevel3Example {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0
  private testCases: CasesObject1[] = [
    {
      info: '2-局部深色模式，主题undefined',
      themeOptions: { theme: undefined, colorMode: ThemeColorMode.DARK }
    },
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
      info: '5-局部适配theme，有自定义颜色',
      themeOptions: { theme: new PageCustomTheme(new GreenColors) },
      fontColor: $r('app.color.Color_red'),
      backgroundColor: $r('app.color.Color_green')
    },
    {
      info: '6-局部适配theme，有自定义颜色，深色模式',
      themeOptions: { theme: new PageCustomTheme(new GreenColors), colorMode: ThemeColorMode.DARK },
      fontColor: $r('app.color.Color_red'),
      backgroundColor: $r('app.color.Color_green')
    }
  ]
  @State isSelect1: number = 0
  @State value1: string = '默认菜单'

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

            Divider()
            Text('应用级全局主题：' + this.isSelect1)
              .fontSize(12)
              .focusable(false)
              .width('100%')
            Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
              Select([{ value: '菜单1' },
                { value: '菜单2' },
                { value: '菜单3' },
                { value: '菜单4' },
                { value: 'oa+ jila Ltt ojrljlt' }])
                .width('50%')
                .selected(this.isSelect1!!)
                .key('Select1')
            }

            WithTheme({ theme: new PageCustomTheme(new Colors) }) {
              Column({ space: 10 }) {
                Text('最外层设置主题：' + this.value1)
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')

                Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
                  Select([{ value: '菜单1' },
                    { value: '菜单2' },
                    { value: '菜单3' },
                    { value: '菜单4' },
                    { value: 'oa+ jila Ltt ojrljlt' }])
                    .value(this.value1!!)
                    .width('50%')
                    .key('Select2')
                }

                Text('局部主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')
                WithTheme(this.testCases[this.index].themeOptions) {
                  Column({ space: '8vp' }) {
                    Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
                      Select([{ value: '菜单1' },
                        { value: '菜单2' },
                        { value: '菜单3' },
                        { value: '菜单4' },
                        { value: 'oa+ jila Ltt ojrljlt' }])
                        .value('默认菜单')
                        .width('50%')
                        .selected(2)
                        .key('Select3')
                    }

                    Text('自定义颜色切换：')
                      .fontSize(12)
                      .focusable(false)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
                      Select([{ value: '菜单1' },
                        { value: '菜单2' },
                        { value: '菜单3' },
                        { value: '菜单4' },
                        { value: 'oa+ jila Ltt ojrljlt' }])
                        .value('默认菜单')
                        .width('50%')
                        .selected(3)
                        .key('Select4')
                        .fontColor(this.testCases[this.index].fontColor)
                        .backgroundColor(undefined)
                        .menuBackgroundColor(this.testCases[this.index].backgroundColor)
                        .optionBgColor(this.testCases[this.index].optionBgColor)
                        .optionFontColor(this.testCases[this.index].optionFontColor)
                        .selectedOptionBgColor(this.testCases[this.index].selectedOptionBgColor)
                        .selectedOptionFontColor(this.testCases[this.index].selectedOptionFontColor)
                        .divider({ color: this.testCases[this.index].dividerColor })
                    }
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
    .title('SelectLevel3')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}