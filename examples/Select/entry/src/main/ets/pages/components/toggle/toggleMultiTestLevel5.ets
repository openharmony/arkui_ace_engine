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

ThemeControl.setDefaultTheme(undefined);

@Builder
export function ToggleMultiTestLevel5Builder(name: string, param: Object) {
  toggleMultiTestLevel5()
}

export class PageCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class DefaultTheme implements CustomColors {
  public compBackgroundEmphasize = '#F0E68C'
  public iconOnPrimary = 'rgb(226, 132, 96)'
  public iconFourth = '#2E8B57'
  public compEmphasizeSecondary = '#87CEFA'
  public compBackgroundPrimaryContrary = '#C71585'
  public compBackgroundTertiary = '#FFE4E1'
}

const customDefaultTheme: CustomTheme = new PageCustomTheme(new DefaultTheme());
ThemeControl.setDefaultTheme(customDefaultTheme);

export class Colors implements CustomColors {
  public compBackgroundEmphasize = 'rgb(22, 83, 5)'
  public iconOnPrimary = '#C71585'
  public iconFourth = '#FFD53032'
  public compEmphasizeSecondary = '#FF7F50'
  public compBackgroundPrimaryContrary = '#F0E68C'
  public compBackgroundTertiary = '#3CB371'
}

export class RedColors implements CustomColors {
  public compBackgroundEmphasize = '#87CEEB'
  public iconOnPrimary = '#FFD700'
  public iconFourth = '#7B68EE'
  public compEmphasizeSecondary = '#008080'
  public compBackgroundPrimaryContrary = '#9400D3'
  public compBackgroundTertiary = '#DA70D6'
}

export class GreenColors implements CustomColors {
  public compBackgroundEmphasize = $r('app.color.Color_test4')
  public iconOnPrimary =
    $r('app.color.Color_orange')
  public iconFourth = $r('app.color.Color_test3')
  public compEmphasizeSecondary =
    $r('app.color.Color_orange')
  public compBackgroundPrimaryContrary = $r('app.color.Color_test3')
  public compBackgroundTertiary =
    $r('app.color.Color_test3')
}

interface CasesObject1 {
  info?: string
  themeOptions?: WithThemeOptions,
  backgroundColor?: ResourceColor,
  selectedColor?: ResourceColor,
  switchPointColor?: ResourceColor,
  pointColor?: ResourceColor,
  switchUnselectedColor?: ResourceColor
}

@Entry
@Component
struct toggleMultiTestLevel5 {
  pathStack: NavPathStack = new NavPathStack()
  @State index: number = 0
  private testCases: CasesObject1[] = [
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
      backgroundColor: $r('app.color.Color_red'),
      selectedColor:
      $r('app.color.Color_green'),
      switchPointColor: $r('app.color.Color_test1'),
      pointColor:
      $r('app.color.Color_test2'),
      switchUnselectedColor: $r('app.color.Color_test4')
    },
    {
      info: '6-局部适配theme，有自定义颜色，深色模式',
      themeOptions: { theme: new PageCustomTheme(new GreenColors), colorMode: ThemeColorMode.DARK },
      backgroundColor:
      $r('app.color.Color_red'),
      selectedColor: $r('app.color.Color_green'),
      switchPointColor:
      $r('app.color.Color_test1'),
      pointColor: $r('app.color.Color_test2'),
      switchUnselectedColor:
      $r('app.color.Color_test4')
    },
  ]

  build() {
    NavDestination() {
      Row() {
        Scroll() {
          Column({ space: 10 }) {
            Divider()
            Row({ space: 5 }) {
              Text('${this.index}' + '/')
                .fontSize(15)
                .focusable(false)
              Text('${this.testCases.length - 1}')
                .fontSize(15)
                .key('totalTest')
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

            Text('应用级全局主题：')
              .fontSize(12)
              .focusable(false)
              .width('100%')
            Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
              Column({ space: 5 }) {
                Text('未选中状态').fontSize(14)
                Row({ space: 8 }) {
                  Toggle({
                    type: ToggleType.Switch,
                  })
                    .key('Toggle1')
                  Toggle({
                    type: ToggleType.Button,
                  })
                    .width(40)
                    .height(20)
                    .key('Toggle2')
                  Toggle({
                    type: ToggleType.Checkbox,
                  })
                    .key('Toggle3')
                }
              }

              Column({ space: 5 }) {
                Text('已选中状态').fontSize(14)
                Row({ space: 8 }) {
                  Toggle({
                    type: ToggleType.Switch,
                    isOn: true
                  })
                    .key('Toggle4')
                  Toggle({
                    type: ToggleType.Button,
                    isOn: true
                  })
                    .width(40)
                    .height(20)
                    .key('Toggle5')
                  Toggle({
                    type: ToggleType.Checkbox,
                    isOn: true
                  })
                    .key('Toggle6')
                }
              }
            }.width('70%')

            WithTheme({ theme: new PageCustomTheme(new Colors) }) {
              Column({ space: 10 }) {
                Text('最外层设置主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')

                Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                  Column({ space: 5 }) {
                    Row({ space: 8 }) {
                      Toggle({
                        type: ToggleType.Switch,
                      })
                        .key('Toggle7')
                      Toggle({
                        type: ToggleType.Button,
                      })
                        .width(40)
                        .height(20)
                        .key('Toggle8')
                      Toggle({
                        type: ToggleType.Checkbox,
                      })
                        .key('Toggle9')
                    }
                  }

                  Column({ space: 5 }) {
                    Row({ space: 8 }) {
                      Toggle({
                        type: ToggleType.Switch,
                        isOn: true
                      })
                        .key('Toggle10')
                      Toggle({
                        type: ToggleType.Button,
                        isOn: true
                      })
                        .width(40)
                        .height(20)
                        .key('Toggle11')
                      Toggle({
                        type: ToggleType.Checkbox,
                        isOn: true
                      })
                        .key('Toggle12')
                    }
                  }
                }.width('70%')

                Text('局部主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')
                WithTheme(this.testCases[this.index].themeOptions) {
                  Column({ space: '8vp' }) {
                    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Row({ space: 8 }) {
                          Toggle({
                            type: ToggleType.Switch,
                          })
                            .key('Toggle13')
                          Toggle({
                            type: ToggleType.Button,
                          })
                            .width(40)
                            .height(20)
                            .key('Toggle14')
                          Toggle({
                            type: ToggleType.Checkbox,
                          })
                            .key('Toggle15')
                        }
                      }

                      Column({ space: 5 }) {
                        Row({ space: 8 }) {
                          Toggle({
                            type: ToggleType.Switch,
                            isOn: true
                          })
                            .key('Toggle16')
                          Toggle({
                            type: ToggleType.Button,
                            isOn: true
                          })
                            .width(40)
                            .height(20)
                            .key('Toggle17')
                          Toggle({
                            type: ToggleType.Checkbox,
                            isOn: true
                          })
                            .key('Toggle18')
                        }
                      }
                    }.width('70%')

                    Text('自定义颜色切换：')
                      .fontSize(12)
                      .focusable(false)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Row({ space: 8 }) {
                          Toggle({
                            type: ToggleType.Switch,
                          })
                            .key('Toggle19')
                            .switchStyle({
                              pointColor: this.testCases[this.index].pointColor,
                              unselectedColor: this.testCases[this.index].switchUnselectedColor
                            })
                          Toggle({
                            type: ToggleType.Button,
                          })
                            .width(40)
                            .height(20)
                            .key('Toggle20')
                            .backgroundColor(this.testCases[this.index].backgroundColor)
                          Toggle({
                            type: ToggleType.Checkbox,
                          })
                            .key('Toggle21')
                        }
                      }

                      Column({ space: 5 }) {
                        Row({ space: 8 }) {
                          Toggle({
                            type: ToggleType.Switch,
                            isOn: true
                          })
                            .key('Toggle22')
                            .switchPointColor(this.testCases[this.index].switchPointColor)
                            .selectedColor(this.testCases[this.index].selectedColor)
                          Toggle({
                            type: ToggleType.Button,
                            isOn: true
                          })
                            .width(40)
                            .height(20)
                            .key('Toggle23')
                            .selectedColor(this.testCases[this.index].selectedColor)
                          Toggle({
                            type: ToggleType.Checkbox,
                            isOn: true
                          })
                            .key('Toggle24')
                            .selectedColor(this.testCases[this.index].selectedColor)
                        }
                      }
                    }.width('70%')
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
    .title('ToggleMultiTestLevel5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}