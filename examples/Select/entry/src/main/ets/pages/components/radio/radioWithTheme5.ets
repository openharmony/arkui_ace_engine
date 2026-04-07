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
 * Radio WithTheme 使用 $r() 资源引用自定义 token 颜色随深浅色自动切换测试
 *
 * 测试点：
 * 1. CustomColors 中使用 $r('app.color.xxx') 引用资源文件颜色，WithTheme colorMode 切换时 Radio 颜色自动变化
 * 2. 对比组：CustomColors 使用硬编码颜色字符串，切换深浅色后 Radio 自定义 token 颜色不变
 * 3. 全局深浅色（setColorMode）与局部 WithTheme colorMode 的联动
 * 4. Radio 组在深浅色切换时互斥功能和颜色同时正确
 *
 * 资源文件中 $r() 引用的深浅色色值对照：
 *   app.color.Color_red    -> 浅色 #FFFF0000（纯红）/ 深色 #FF6347（番茄红）
 *   app.color.Color_green  -> 浅色 #6495ED（矢车菊蓝）/ 深色 #E1FFFF（浅青）
 *   app.color.Color_orange -> 浅色 #FFFF7E00（亮橙）/ 深色 #808000（橄榄色）
 *
 * 预期：
 * - "$r()引用"区域，点击"局部浅色"按钮：
 *   Radio已选中背景色 #FFFF0000（纯红），未选中边框 #6495ED（矢车菊蓝），指示器 #FFFF7E00（亮橙）
 * - "$r()引用"区域，点击"局部深色"按钮：
 *   Radio已选中背景色 #FF6347（番茄红），未选中边框 #E1FFFF（浅青），指示器 #808000（橄榄色）
 * - "$r()引用"区域，点击"跟随系统"按钮：
 *   Radio颜色随全局深浅色自动切换
 * - "硬编码"对比组区域，切换深浅色：
 *   Radio颜色始终为硬编码值（#4169E1 / #6495ED / #F0F8FF），不随深浅色变化
 *   背景等未覆盖的系统 token 仍会跟随深浅色切换
 * - 全局Radio始终使用系统默认颜色
 */

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';
import { ConfigurationConstant, common } from '@kit.AbilityKit';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioWithTheme5Builder(name: string, param: Object) {
  RadioWithTheme5()
}

// 使用 $r() 资源引用，颜色值由 resources/base 和 resources/dark 资源文件自动决定
class ResourceTokenColors implements CustomColors {
  public compBackgroundEmphasize = $r('app.color.Color_red')
  public iconOnPrimary = $r('app.color.Color_orange')
  public iconFourth = $r('app.color.Color_green')
}

// 硬编码颜色（对比组），不随深浅色变化
class HardcodeTokenColors implements CustomColors {
  public compBackgroundEmphasize = '#4169E1'
  public iconOnPrimary = '#F0F8FF'
  public iconFourth = '#6495ED'
}

class RadioCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

@Entry
@Component
struct RadioWithTheme5 {
  pathStack: NavPathStack = new NavPathStack()
  @State colorMode: ThemeColorMode = ThemeColorMode.SYSTEM
  @State colorModeText: string = 'SYSTEM'
  @State globalColorMode: ConfigurationConstant.ColorMode = ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT
  private uiAbilityContext: common.UIAbilityContext =
    this.getUIContext().getHostContext() as common.UIAbilityContext
  private resourceTheme: CustomTheme = new RadioCustomTheme(new ResourceTokenColors())
  private hardcodeTheme: CustomTheme = new RadioCustomTheme(new HardcodeTokenColors())

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Divider()
          Text('Radio $r()资源引用 Token颜色随深浅色切换')
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
          Text('当前局部 colorMode：' + this.colorModeText)
            .fontSize(14)
            .fontColor(Color.Orange)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button('局部浅色')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.LIGHT ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.LIGHT
                this.colorModeText = 'LIGHT'
              })
              .key('Btn_LocalLight5')
            Button('局部深色')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.DARK ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.DARK
                this.colorModeText = 'DARK'
              })
              .key('Btn_LocalDark5')
            Button('跟随系统')
              .fontSize(14)
              .backgroundColor(this.colorMode === ThemeColorMode.SYSTEM ? '#FF6347' : Color.Gray)
              .onClick(() => {
                this.colorMode = ThemeColorMode.SYSTEM
                this.colorModeText = 'SYSTEM'
              })
              .key('Btn_LocalSystem5')
          }

          Divider()
          Text('全局Radio（无WithTheme包裹）：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
            Column({ space: 5 }) {
              Text('未选中').fontSize(12)
              Radio({ value: 'R1_global5', group: 'globalGroup5' })
                .checked(false)
                .height(50)
                .width(50)
                .key('Radio_Global5_Unchecked')
            }
            Column({ space: 5 }) {
              Text('已选中').fontSize(12)
              Radio({ value: 'R2_global5', group: 'globalGroup5' })
                .checked(true)
                .height(50)
                .width(50)
                .key('Radio_Global5_Checked')
            }
          }.width('100%')

          Divider()
          Text('$r()引用 —— 颜色随深浅色自动切换：')
            .fontSize(14)
            .fontColor(Color.Red)
            .width('100%')
          Text('compBackgroundEmphasize=$r(Color_red), iconFourth=$r(Color_green), iconOnPrimary=$r(Color_orange)')
            .fontSize(11)
            .fontColor('#888888')
            .width('100%')
          WithTheme({ theme: this.resourceTheme, colorMode: this.colorMode }) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_res', group: 'resGroup5' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_Res_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_res', group: 'resGroup5' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_Res_Checked')
                }
              }.width('100%')

              Text('Radio组：')
                .fontSize(12)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('选项A').fontSize(12)
                  Radio({ value: 'A5r', group: 'resRadioGroup5' })
                    .checked(true)
                    .height(40)
                    .width(40)
                    .key('Radio_Res_A')
                }
                Column({ space: 5 }) {
                  Text('选项B').fontSize(12)
                  Radio({ value: 'B5r', group: 'resRadioGroup5' })
                    .height(40)
                    .width(40)
                    .key('Radio_Res_B')
                }
                Column({ space: 5 }) {
                  Text('选项C').fontSize(12)
                  Radio({ value: 'C5r', group: 'resRadioGroup5' })
                    .height(40)
                    .width(40)
                    .key('Radio_Res_C')
                }
              }.width('100%')
            }
            .backgroundColor($r('sys.color.background_primary'))
            .width('100%')
            .padding(10)
          }

          Divider()
          Text('硬编码对比组 —— 颜色不随深浅色变化：')
            .fontSize(14)
            .width('100%')
          Text('compBackgroundEmphasize=#4169E1, iconFourth=#6495ED, iconOnPrimary=#F0F8FF')
            .fontSize(11)
            .fontColor('#888888')
            .width('100%')
          WithTheme({ theme: this.hardcodeTheme, colorMode: this.colorMode }) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_hard', group: 'hardGroup5' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_Hard_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_hard', group: 'hardGroup5' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_Hard_Checked')
                }
              }.width('100%')

              Text('Radio组：')
                .fontSize(12)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('选项A').fontSize(12)
                  Radio({ value: 'A5h', group: 'hardRadioGroup5' })
                    .checked(true)
                    .height(40)
                    .width(40)
                    .key('Radio_Hard_A')
                }
                Column({ space: 5 }) {
                  Text('选项B').fontSize(12)
                  Radio({ value: 'B5h', group: 'hardRadioGroup5' })
                    .height(40)
                    .width(40)
                    .key('Radio_Hard_B')
                }
                Column({ space: 5 }) {
                  Text('选项C').fontSize(12)
                  Radio({ value: 'C5h', group: 'hardRadioGroup5' })
                    .height(40)
                    .width(40)
                    .key('Radio_Hard_C')
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
    .title('RadioWithTheme5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
