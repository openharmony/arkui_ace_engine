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
 * Radio WithTheme 局部深浅色模式测试
 *
 * 测试点：
 * 1. 全局深浅色切换（setColorMode）对无 WithTheme 包裹的 Radio 生效
 * 2. WithTheme({ colorMode: LIGHT/DARK/SYSTEM }) 局部覆盖全局 colorMode
 * 3. WithTheme({ theme, colorMode }) 同时传入自定义主题和 colorMode 的组合效果
 * 4. 局部 colorMode 为 DARK 时，即使全局为 LIGHT，局部 Radio 仍显示深色样式
 *
 * 预期：
 * - 点击"全局浅色"按钮：全局Radio和未被WithTheme包裹的区域切换为浅色样式
 * - 点击"全局深色"按钮：全局Radio和未被WithTheme包裹的区域切换为深色样式
 * - 点击"局部浅色"按钮：局部WithTheme区域内Radio强制显示浅色，不受全局深浅色影响
 * - 点击"局部深色"按钮：局部WithTheme区域内Radio强制显示深色，不受全局深浅色影响
 * - 点击"跟随系统"按钮：局部WithTheme区域内Radio跟随系统/全局深浅色
 * - "局部WithTheme + 自定义theme + colorMode"区域：
 *   已选中背景色为 #FF6347，未选中边框为 #CD853F，同时遵循 colorMode 深浅色背景
 * - 全局Radio的颜色始终跟随全局设置，不受局部 WithTheme 的 colorMode 影响
 */

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';
import { ConfigurationConstant } from '@kit.AbilityKit';
import { common } from '@kit.AbilityKit';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioWithTheme2Builder(name: string, param: Object) {
  RadioWithTheme2()
}

export class RadioCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class CustomColorsImpl implements CustomColors {
  public compBackgroundEmphasize = '#FF6347'
  public iconOnPrimary = '#FFF5EE'
  public iconFourth = '#CD853F'
}

@Entry
@Component
struct RadioWithTheme2 {
  pathStack: NavPathStack = new NavPathStack()
  @State colorMode: ThemeColorMode = ThemeColorMode.SYSTEM
  @State colorModeText: string = 'SYSTEM'
  @State globalColorMode: ConfigurationConstant.ColorMode = ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT
  private uiAbilityContext: common.UIAbilityContext =
    this.getUIContext().getHostContext() as common.UIAbilityContext
  private customTheme: CustomTheme = new RadioCustomTheme(new CustomColorsImpl())

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Divider()
          Text('Radio WithTheme 局部深浅色模式')
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
          Text(`当前局部 colorMode：${this.colorModeText}`)
            .fontSize(14)
            .fontColor(Color.Orange)
            .width('100%')

          Text('局部深浅色控制（不传theme）：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button('局部浅色')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.LIGHT ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.LIGHT
                this.colorModeText = 'LIGHT'
              })
              .key('Btn_LocalLight')
            Button('局部深色')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.DARK ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.DARK
                this.colorModeText = 'DARK'
              })
              .key('Btn_LocalDark')
            Button('跟随系统')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.SYSTEM ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.SYSTEM
                this.colorModeText = 'SYSTEM'
              })
              .key('Btn_LocalSystem')
          }

          Divider()
          Text('全局Radio（无WithTheme）：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
            Column({ space: 5 }) {
              Text('未选中').fontSize(12)
              Radio({ value: 'R1_noTheme', group: 'noThemeGroup' })
                .checked(false)
                .height(50)
                .width(50)
                .key('Radio_NoTheme_Unchecked')
            }
            Column({ space: 5 }) {
              Text('已选中').fontSize(12)
              Radio({ value: 'R2_noTheme', group: 'noThemeGroup' })
                .checked(true)
                .height(50)
                .width(50)
                .key('Radio_NoTheme_Checked')
            }
          }.width('100%')

          Divider()
          Text('局部WithTheme包裹的Radio：')
            .fontSize(14)
            .width('100%')
          WithTheme({ colorMode: this.colorMode }) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_cm', group: 'cmGroup' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_CM_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_cm', group: 'cmGroup' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_CM_Checked')
                }
              }.width('100%')

              Text('Radio组：')
                .fontSize(12)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('选项A').fontSize(12)
                  Radio({ value: 'A_cm', group: 'cmRadioGroup' })
                    .checked(true)
                    .height(40)
                    .width(40)
                    .key('Radio_CM_A')
                }
                Column({ space: 5 }) {
                  Text('选项B').fontSize(12)
                  Radio({ value: 'B_cm', group: 'cmRadioGroup' })
                    .height(40)
                    .width(40)
                    .key('Radio_CM_B')
                }
                Column({ space: 5 }) {
                  Text('选项C').fontSize(12)
                  Radio({ value: 'C_cm', group: 'cmRadioGroup' })
                    .height(40)
                    .width(40)
                    .key('Radio_CM_C')
                }
              }.width('100%')
            }
            .backgroundColor($r('sys.color.background_primary'))
            .width('100%')
            .padding(10)
          }

          Divider()
          Text('局部WithTheme + 自定义theme + colorMode：')
            .fontSize(14)
            .width('100%')
          WithTheme({ theme: this.customTheme, colorMode: this.colorMode }) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_ct', group: 'ctGroup' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_CT_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_ct', group: 'ctGroup' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_CT_Checked')
                }
              }.width('100%')
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
    .title('RadioWithTheme2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
