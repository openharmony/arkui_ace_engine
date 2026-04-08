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
 * Radio WithTheme 嵌套主题 + 深浅色切换测试
 *
 * 测试点：
 * 1. 外层 WithTheme 设置蓝色系自定义主题 + colorMode，外层 Radio 跟随外层主题
 * 2. 内层 WithTheme 不传 theme（仅 colorMode），内层 Radio 使用系统默认颜色 + 指定深浅色
 * 3. 内层 WithTheme 同时传入自定义 theme + colorMode，内层 Radio 完全覆盖外层主题
 * 4. 外层深浅色切换不影响已设置独立内层的 Radio 颜色
 * 5. 全局深浅色（setColorMode）与外层/内层 colorMode 各自独立
 *
 * 预期：
 * - 外层Radio：已选中背景色 #4169E1，未选中边框 #6495ED，指示器 #F0F8FF
 *
 * - "内层浅色"按钮（不传theme，colorMode=LIGHT）：
 *   内层Radio使用系统默认浅色样式，不继承外层蓝色主题
 *
 * - "内层深色"按钮（不传theme，colorMode=DARK）：
 *   内层Radio使用系统默认深色样式，不继承外层蓝色主题
 *
 * - "内层自定义浅色"按钮（传theme=InnerLightColors + colorMode=LIGHT）：
 *   内层Radio已选中背景色 #32CD32，未选中边框 #90EE90，指示器 #FFFFFF
 *
 * - "内层自定义深色"按钮（传theme=InnerDarkColors + colorMode=DARK）：
 *   内层Radio已选中背景色 #8B0000，未选中边框 #CD5C5C，指示器 #FFFACD
 *
 * - 切换外层浅色/深色：外层Radio颜色在蓝色系基础上呈现浅色/深色差异
 * - 切换全局浅色/深色：内层已独立设置colorMode的Radio不受全局影响
 * - Radio组（X/Y/Z）在内层主题下互斥选中功能正常，颜色跟随内层主题
 */

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';
import { ConfigurationConstant, common } from '@kit.AbilityKit';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioWithTheme4Builder(name: string, param: Object) {
  RadioWithTheme4()
}

export class RadioCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class OuterColors implements CustomColors {
  public compBackgroundEmphasize = '#4169E1'
  public iconOnPrimary = '#F0F8FF'
  public iconFourth = '#6495ED'
}

export class InnerLightColors implements CustomColors {
  public compBackgroundEmphasize = '#32CD32'
  public iconOnPrimary = '#FFFFFF'
  public iconFourth = '#90EE90'
}

export class InnerDarkColors implements CustomColors {
  public compBackgroundEmphasize = '#8B0000'
  public iconOnPrimary = '#FFFACD'
  public iconFourth = '#CD5C5C'
}

@Entry
@Component
struct RadioWithTheme4 {
  pathStack: NavPathStack = new NavPathStack()
  @State outerColorMode: ThemeColorMode = ThemeColorMode.LIGHT
  @State innerColorMode: ThemeColorMode = ThemeColorMode.LIGHT
  @State useCustomInnerTheme: boolean = false
  @State globalColorMode: ConfigurationConstant.ColorMode = ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT
  private uiAbilityContext: common.UIAbilityContext =
    this.getUIContext().getHostContext() as common.UIAbilityContext
  private outerTheme: CustomTheme = new RadioCustomTheme(new OuterColors())
  private innerLightTheme: CustomTheme = new RadioCustomTheme(new InnerLightColors())
  private innerDarkTheme: CustomTheme = new RadioCustomTheme(new InnerDarkColors())

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Divider()
          Text('Radio WithTheme 嵌套主题 + 深浅色切换')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Divider()
          Text('全局深浅色控制：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button(`全局深浅色: ${this.globalColorMode === ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT ? 'LIGHT' : 'DARK'}`)
              .onClick(() => {
                this.globalColorMode = this.globalColorMode === ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT ?
                  ConfigurationConstant.ColorMode.COLOR_MODE_DARK : ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT;
                this.uiAbilityContext.setColorMode(this.globalColorMode);
              })
              .margin({ left: 20, right: 20, bottom: 10 })
          }

          Divider()
          Text('外层WithTheme colorMode切换：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button('外层浅色')
              .fontSize(14)
              .backgroundColor(this.outerColorMode === ThemeColorMode.LIGHT ? '#4169E1' : Color.Gray)
              .onClick(() => {
                this.outerColorMode = ThemeColorMode.LIGHT
              })
              .key('Btn_OuterLight')
            Button('外层深色')
              .fontSize(14)
              .backgroundColor(this.outerColorMode === ThemeColorMode.DARK ? '#4169E1' : Color.Gray)
              .onClick(() => {
                this.outerColorMode = ThemeColorMode.DARK
              })
              .key('Btn_OuterDark')
          }

          Divider()
          Text('内层WithTheme控制：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button('内层浅色')
              .fontSize(14)
              .backgroundColor(this.innerColorMode === ThemeColorMode.LIGHT && !this.useCustomInnerTheme ? '#32CD32' :
                Color.Gray)
              .onClick(() => {
                this.innerColorMode = ThemeColorMode.LIGHT
                this.useCustomInnerTheme = false
              })
              .key('Btn_InnerLight')
            Button('内层深色')
              .fontSize(14)
              .backgroundColor(this.innerColorMode === ThemeColorMode.DARK && !this.useCustomInnerTheme ? '#8B0000' :
                Color.Gray)
              .onClick(() => {
                this.innerColorMode = ThemeColorMode.DARK
                this.useCustomInnerTheme = false
              })
              .key('Btn_InnerDark')
            Button('内层自定义浅色')
              .fontSize(14)
              .backgroundColor(this.useCustomInnerTheme && this.innerColorMode === ThemeColorMode.LIGHT ? '#32CD32' :
                Color.Gray)
              .onClick(() => {
                this.innerColorMode = ThemeColorMode.LIGHT
                this.useCustomInnerTheme = true
              })
              .key('Btn_InnerCustomLight')
            Button('内层自定义深色')
              .fontSize(14)
              .backgroundColor(this.useCustomInnerTheme && this.innerColorMode === ThemeColorMode.DARK ? '#8B0000' :
                Color.Gray)
              .onClick(() => {
                this.innerColorMode = ThemeColorMode.DARK
                this.useCustomInnerTheme = true
              })
              .key('Btn_InnerCustomDark')
          }

          Divider()
          WithTheme({ theme: this.outerTheme, colorMode: this.outerColorMode }) {
            Column({ space: 10 }) {
              Text('外层WithTheme（蓝色系主题）：')
                .fontSize(14)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_outer', group: 'outerGroup4' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_Outer_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_outer', group: 'outerGroup4' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_Outer_Checked')
                }
              }.width('100%')

              Divider()
              if (this.useCustomInnerTheme) {
                WithTheme({
                  theme: this.innerColorMode === ThemeColorMode.LIGHT ? this.innerLightTheme : this.innerDarkTheme,
                  colorMode: this.innerColorMode
                }) {
                  Column({ space: 10 }) {
                    Text('内层WithTheme（自定义主题 + colorMode）：')
                      .fontSize(14)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Text('未选中').fontSize(12)
                        Radio({ value: 'R1_inner_custom', group: 'innerGroup4' })
                          .checked(false)
                          .height(50)
                          .width(50)
                          .key('Radio_InnerCustom_Unchecked')
                      }
                      Column({ space: 5 }) {
                        Text('已选中').fontSize(12)
                        Radio({ value: 'R2_inner_custom', group: 'innerGroup4' })
                          .checked(true)
                          .height(50)
                          .width(50)
                          .key('Radio_InnerCustom_Checked')
                      }
                    }.width('100%')

                    Text('Radio组：')
                      .fontSize(12)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Text('X').fontSize(12)
                        Radio({ value: 'X4', group: 'innerRadioGroup4' })
                          .checked(true)
                          .height(40)
                          .width(40)
                          .key('Radio_Inner_X')
                      }
                      Column({ space: 5 }) {
                        Text('Y').fontSize(12)
                        Radio({ value: 'Y4', group: 'innerRadioGroup4' })
                          .height(40)
                          .width(40)
                          .key('Radio_Inner_Y')
                      }
                      Column({ space: 5 }) {
                        Text('Z').fontSize(12)
                        Radio({ value: 'Z4', group: 'innerRadioGroup4' })
                          .height(40)
                          .width(40)
                          .key('Radio_Inner_Z')
                      }
                    }.width('100%')
                  }
                  .backgroundColor($r('sys.color.background_primary'))
                  .width('100%')
                  .padding(10)
                }
              } else {
                WithTheme({ colorMode: this.innerColorMode }) {
                  Column({ space: 10 }) {
                    Text('内层WithTheme（仅colorMode，不传theme）：')
                      .fontSize(14)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Text('未选中').fontSize(12)
                        Radio({ value: 'R1_inner_cm', group: 'innerGroup4cm' })
                          .checked(false)
                          .height(50)
                          .width(50)
                          .key('Radio_InnerCM_Unchecked')
                      }
                      Column({ space: 5 }) {
                        Text('已选中').fontSize(12)
                        Radio({ value: 'R2_inner_cm', group: 'innerGroup4cm' })
                          .checked(true)
                          .height(50)
                          .width(50)
                          .key('Radio_InnerCM_Checked')
                      }
                    }.width('100%')

                    Text('Radio组：')
                      .fontSize(12)
                      .width('100%')
                    Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                      Column({ space: 5 }) {
                        Text('X').fontSize(12)
                        Radio({ value: 'X4cm', group: 'innerRadioGroup4cm' })
                          .checked(true)
                          .height(40)
                          .width(40)
                          .key('Radio_InnerCM_X')
                      }
                      Column({ space: 5 }) {
                        Text('Y').fontSize(12)
                        Radio({ value: 'Y4cm', group: 'innerRadioGroup4cm' })
                          .height(40)
                          .width(40)
                          .key('Radio_InnerCM_Y')
                      }
                      Column({ space: 5 }) {
                        Text('Z').fontSize(12)
                        Radio({ value: 'Z4cm', group: 'innerRadioGroup4cm' })
                          .height(40)
                          .width(40)
                          .key('Radio_InnerCM_Z')
                      }
                    }.width('100%')
                  }
                  .backgroundColor($r('sys.color.background_primary'))
                  .width('100%')
                  .padding(10)
                }
              }
            }
            .backgroundColor($r('sys.color.background_primary'))
            .width('100%')
            .padding(10)
          }
        }
        .padding({ left: 15, right: 15 })
      }
      .scrollBar(BarState.Off)
      .width('100%')
    }
    .title('RadioWithTheme4')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
