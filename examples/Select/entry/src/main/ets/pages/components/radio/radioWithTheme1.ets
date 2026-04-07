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
 * Radio WithTheme 基础主题切换测试
 *
 * 测试点：
 * 1. WithTheme({ theme }) 传入不同 CustomColors 自定义主题，Radio 颜色跟随变化
 * 2. 全局Radio（无WithTheme包裹）与局部Radio（WithTheme包裹）颜色互不影响
 * 3. 动态切换 theme 时，WithTheme 包裹内的 Radio 实时刷新颜色
 * 4. Radio 组（group）在 WithTheme 下的互斥选中功能正常
 *
 * 预期：
 * - 点击"红色主题"按钮：局部Radio已选中背景色变为 #FFD53032，指示器颜色 #FFD700，未选中边框 #7B68EE
 * - 点击"绿色主题"按钮：局部Radio已选中背景色变为 #2E8B57，指示器颜色 #FFFFFF，未选中边框 #3CB371
 * - 点击"蓝色主题"按钮：局部Radio已选中背景色变为 #1E90FF，指示器颜色 #F0F8FF，未选中边框 #87CEEB
 * - 全局Radio始终保持系统默认颜色，不随局部主题变化
 * - Radio组中点击选项B/C后，选项A取消选中，B/C中选中的那个高亮显示，颜色跟随当前局部主题
 */

import { CustomColors, CustomTheme, ThemeControl } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(undefined);

@Builder
export function RadioWithTheme1Builder(name: string, param: Object) {
  RadioWithTheme1()
}

export class RadioCustomTheme implements CustomTheme {
  public colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors
  }
}

export class RedColors implements CustomColors {
  public compBackgroundEmphasize = '#FFD53032'
  public iconOnPrimary = '#FFD700'
  public iconFourth = '#7B68EE'
}

export class GreenColors implements CustomColors {
  public compBackgroundEmphasize = '#2E8B57'
  public iconOnPrimary = '#FFFFFF'
  public iconFourth = '#3CB371'
}

export class BlueColors implements CustomColors {
  public compBackgroundEmphasize = '#1E90FF'
  public iconOnPrimary = '#F0F8FF'
  public iconFourth = '#87CEEB'
}

@Entry
@Component
struct RadioWithTheme1 {
  pathStack: NavPathStack = new NavPathStack()
  @State currentThemeIndex: number = 0
  private themeList: CustomTheme[] = [
    new RadioCustomTheme(new RedColors()),
    new RadioCustomTheme(new GreenColors()),
    new RadioCustomTheme(new BlueColors()),
  ]
  private themeNames: string[] = ['红色主题', '绿色主题', '蓝色主题']

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Divider()
          Text('Radio WithTheme 基础主题切换')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Divider()
          Text('全局主题（无WithTheme包裹）：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
            Column({ space: 5 }) {
              Text('未选中').fontSize(12)
              Radio({ value: 'R1_global', group: 'globalGroup' })
                .checked(false)
                .height(50)
                .width(50)
                .key('Radio_Global_Unchecked')
            }
            Column({ space: 5 }) {
              Text('已选中').fontSize(12)
              Radio({ value: 'R2_global', group: 'globalGroup' })
                .checked(true)
                .height(50)
                .width(50)
                .key('Radio_Global_Checked')
            }
          }.width('100%')

          Divider()
          Text('局部主题（WithTheme包裹）：')
            .fontSize(14)
            .width('100%')
          Text(`当前局部主题：${this.themeNames[this.currentThemeIndex]}`)
            .fontSize(14)
            .fontColor(Color.Orange)
            .width('100%')

          WithTheme({ theme: this.themeList[this.currentThemeIndex] }) {
            Column({ space: 10 }) {
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('未选中').fontSize(12)
                  Radio({ value: 'R1_local', group: 'localGroup1' })
                    .checked(false)
                    .height(50)
                    .width(50)
                    .key('Radio_Local_Unchecked')
                }
                Column({ space: 5 }) {
                  Text('已选中').fontSize(12)
                  Radio({ value: 'R2_local', group: 'localGroup1' })
                    .checked(true)
                    .height(50)
                    .width(50)
                    .key('Radio_Local_Checked')
                }
              }.width('100%')

              Text('Radio组：')
                .fontSize(12)
                .width('100%')
              Flex({ justifyContent: FlexAlign.SpaceEvenly, alignItems: ItemAlign.Center }) {
                Column({ space: 5 }) {
                  Text('选项A').fontSize(12)
                  Radio({ value: 'A', group: 'localRadioGroup1' })
                    .checked(true)
                    .height(40)
                    .width(40)
                    .key('Radio_Local_A')
                }
                Column({ space: 5 }) {
                  Text('选项B').fontSize(12)
                  Radio({ value: 'B', group: 'localRadioGroup1' })
                    .height(40)
                    .width(40)
                    .key('Radio_Local_B')
                }
                Column({ space: 5 }) {
                  Text('选项C').fontSize(12)
                  Radio({ value: 'C', group: 'localRadioGroup1' })
                    .height(40)
                    .width(40)
                    .key('Radio_Local_C')
                }
              }.width('100%')
            }
            .backgroundColor($r('sys.color.background_primary'))
            .width('100%')
            .padding(10)
          }

          Divider()
          Text('切换局部自定义主题：')
            .fontSize(14)
            .width('100%')
          Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
            Button('红色主题')
              .fontSize(14)
              .backgroundColor(this.currentThemeIndex === 0 ? Color.Red : Color.Gray)
              .onClick(() => {
                this.currentThemeIndex = 0
              })
              .key('Btn_RedTheme')
            Button('绿色主题')
              .fontSize(14)
              .backgroundColor(this.currentThemeIndex === 1 ? Color.Green : Color.Gray)
              .onClick(() => {
                this.currentThemeIndex = 1
              })
              .key('Btn_GreenTheme')
            Button('蓝色主题')
              .fontSize(14)
              .backgroundColor(this.currentThemeIndex === 2 ? Color.Blue : Color.Gray)
              .onClick(() => {
                this.currentThemeIndex = 2
              })
              .key('Btn_BlueTheme')
          }
        }
        .padding({ left: 15, right: 15 })
      }
      .scrollBar(BarState.Off)
      .width('100%')
    }
    .title('RadioWithTheme1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
