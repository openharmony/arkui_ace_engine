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
export function SliderLevel15Builder(name: string, param: Object) {
  Slider_Level1_5()
}

export class PageCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class DefaultTheme implements CustomColors {
  public sliderTrackSelectedColor = 'rgb(226, 132, 96)' //选中滑轨颜色
  public compBackgroundSecondary = '#87CEFA' //未选中滑轨颜色
  public compBackgroundPrimaryContrary = '#2E8B57' //滑块颜色
}

const customDefaultTheme: CustomTheme = new PageCustomTheme(new DefaultTheme());
ThemeControl.setDefaultTheme(customDefaultTheme);

export class Colors implements CustomColors {
  public sliderTrackSelectedColor = 'rgb(22, 83, 5)'
  public compBackgroundSecondary = '#C71585'
  public compBackgroundPrimaryContrary = '#FF7F50'
}

export class RedColors implements CustomColors {
  public sliderTrackSelectedColor = '#FFD700'
  public compBackgroundSecondary = '#7B68EE'
  public compBackgroundPrimaryContrary = '#008080'
}

export class GreenColors implements CustomColors {
  public sliderTrackSelectedColor = $r('app.color.Color_test4')
  public compBackgroundSecondary = $r('app.color.Color_orange')
  public compBackgroundPrimaryContrary = $r('app.color.Color_test3')
}

interface CasesObject1 {
  info?: string
  themeOptions?: WithThemeOptions,
  blockColor?: ResourceColor,
  trackColor?: ResourceColor,
  selectedColor?: ResourceColor
}

@Entry
@Component
struct Slider_Level1_5 {
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
      blockColor: $r('app.color.Color_test1'),
      trackColor: $r('app.color.Color_test2'),
      selectedColor: $r('app.color.Color_test4')
    },
    {
      info: '6-局部适配theme，有自定义颜色，深色模式',
      themeOptions: { theme: new PageCustomTheme(new GreenColors), colorMode: ThemeColorMode.DARK },
      blockColor: $r('app.color.Color_test1'),
      trackColor: $r('app.color.Color_test2'),
      selectedColor: $r('app.color.Color_test4')
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

            Divider()

            Text('应用级全局主题：')
              .fontSize(12)
              .focusable(false)
              .width('100%')
            Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
              Column({ space: 5 }) {
                Text('OutSet').fontSize(14)
                Slider({
                  value: 30,
                  step: 10,
                  style: SliderStyle.OutSet
                })
                  .width('45%')
                  .key('Slider1')
                Slider({
                  value: 50,
                  step: 10,
                  style: SliderStyle.OutSet
                })
                  .width('45%')
                  .showSteps(true)
                  .key('Slider2')
              }

              Column({ space: 5 }) {
                Text('InSet').fontSize(14)
                Slider({
                  value: 50,
                  step: 10,
                  style: SliderStyle.InSet
                })
                  .width('45%')
                  .key('Slider3')
                Slider({
                  value: 30,
                  step: 10,
                  style: SliderStyle.InSet
                })
                  .width('45%')
                  .showSteps(true)
                  .key('Slider4')
              }
            }.width('95%')

            WithTheme({ theme: new PageCustomTheme(new Colors) }) {
              Column({ space: 10 }) {
                Text('最外层设置主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')

                Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                  Column({ space: 5 }) {
                    Slider({
                      value: 30,
                      step: 10,
                      style: SliderStyle.OutSet
                    })
                      .width('45%')
                      .key('Slider5')
                    Slider({
                      value: 50,
                      step: 10,
                      style: SliderStyle.OutSet
                    })
                      .width('45%')
                      .showSteps(true)
                      .key('Slider6')
                  }

                  Column({ space: 5 }) {
                    Slider({
                      value: 50,
                      step: 10,
                      style: SliderStyle.InSet
                    })
                      .width('45%')
                      .key('Slider7')
                    Slider({
                      value: 30,
                      step: 10,
                      style: SliderStyle.InSet
                    })
                      .width('45%')
                      .showSteps(true)
                      .key('Slider8')
                  }
                }.width('95%')

                Text('局部主题：')
                  .fontSize(12)
                  .focusable(false)
                  .width('100%')
                WithTheme(this.testCases[this.index].themeOptions) {
                  Column({ space: '8vp' }) {
                    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Slider({
                          value: 30,
                          step: 10,
                          style: SliderStyle.OutSet
                        })
                          .width('45%')
                          .key('Slider9')
                        Slider({
                          value: 50,
                          step: 10,
                          style: SliderStyle.OutSet
                        })
                          .width('45%')
                          .showSteps(true)
                          .key('Slider10')
                      }

                      Column({ space: 5 }) {
                        Slider({
                          value: 50,
                          step: 10,
                          style: SliderStyle.InSet
                        })
                          .width('45%')
                          .key('Slider11')
                        Slider({
                          value: 30,
                          step: 10,
                          style: SliderStyle.InSet
                        })
                          .width('45%')
                          .showSteps(true)
                          .key('Slider12')
                      }
                    }.width('95%')

                    Text('自定义颜色切换：')
                      .fontSize(12)
                      .focusable(false)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Slider({
                          value: 30,
                          step: 10,
                          style: SliderStyle.OutSet
                        })
                          .key('Slider13')
                          .width('45%')
                          .blockColor(this.testCases[this.index].blockColor)
                          .trackColor(this.testCases[this.index].trackColor)
                          .selectedColor(this.testCases[this.index].selectedColor)
                        Slider({
                          value: 50,
                          step: 10,
                          style: SliderStyle.OutSet
                        })
                          .key('Slider14')
                          .width('45%')
                          .showSteps(true)
                          .blockColor(this.testCases[this.index].blockColor)
                          .trackColor(this.testCases[this.index].trackColor)
                          .selectedColor(this.testCases[this.index].selectedColor)
                      }

                      Column({ space: 5 }) {
                        Slider({
                          value: 50,
                          step: 10,
                          style: SliderStyle.InSet
                        })
                          .key('Slider15')
                          .width('45%')
                          .blockColor(this.testCases[this.index].blockColor)
                          .trackColor(this.testCases[this.index].trackColor)
                          .selectedColor(this.testCases[this.index].selectedColor)
                        Slider({
                          value: 30,
                          step: 10,
                          style: SliderStyle.InSet
                        })
                          .key('Slider16')
                          .width('45%')
                          .showSteps(true)
                          .blockColor(this.testCases[this.index].blockColor)
                          .trackColor(this.testCases[this.index].trackColor)
                          .selectedColor(this.testCases[this.index].selectedColor)
                      }
                    }.width('95%')
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
    .title('SliderLevel15')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}