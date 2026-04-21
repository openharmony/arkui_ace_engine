/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';
import { CustomColors } from '@kit.ArkUI';
import { ConfigurationConstant } from '@kit.AbilityKit';

// 自定义颜色类（用于自定义主题）
class CustomTextPickerColors implements CustomColors {
  fontPrimary = '#ff0099cc';
  fontEmphasize = '#ff0099cc';
  fontOnPrimary = '#ffffff';
  compBackgroundTertiary = '#e6f7ff';
  backgroundEmphasize = '#ff0099cc';
  compEmphasizeSecondary = '#33ff0099cc';
  backgroundPrimary = '#f0f8ff';
}

// 自定义主题类
class CustomTextPickerTheme implements CustomTheme {
  colors?: CustomColors;
  constructor(colors: CustomColors) {
    this.colors = colors;
  }
}

// 主题模式枚举
enum ThemeMode {
  SYSTEM = 'system',
  LIGHT = 'light',
  DARK = 'dark',
  CUSTOM = 'custom'
}

@Entry
@Component
struct TextPickerPage {
  // 当前选中的主题模式
  @State currentTheme: ThemeMode = ThemeMode.SYSTEM;
  // 当前系统主题模式
  @State systemTheme: ThemeMode = ThemeMode.LIGHT;
  // 自定义主题实例
  private customTheme: CustomTheme = new CustomTextPickerTheme(new CustomTextPickerColors());
  // 选中的值
  @State selectedValue: number = 2;
  // 可选值数组
  private selectArray: string[] = ['选项1', '选项2', '选项3', '选项4', '选项5'];

  // 点击组件生成方法
  @Builder
  clickComponent(id?: string, title?: string, clickEvent?: Callback<ClickEvent>) {
    Button(title)
      .fontSize(14)
      .backgroundColor('#007DFF')
      .margin({ left: 5, right: 5 })
      .onClick(clickEvent)
  }

  build() {
    Column({ space: 20 }) {
      // 顶部导航栏
      Row() {
        Button('返回')
          .fontSize(16)
          .backgroundColor('#9C27B0')
          .onClick(() => {
            router.back();
          });
        
        Text('TextPicker 主题测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .layoutWeight(1);
        
        // 占位元素，保持标题居中
        Row().width(60);
      }
      .width('100%')
      .padding({ left: 16, right: 16, top: 10, bottom: 10 });

      // 主题选择器
      Flex({ justifyContent: FlexAlign.Center, wrap: FlexWrap.Wrap }) {
        Radio({ value: ThemeMode.SYSTEM, group: 'theme' })
          .checked(this.currentTheme === ThemeMode.SYSTEM)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.currentTheme = ThemeMode.SYSTEM;
            }
          });
        Text('系统默认')
          .fontColor(this.systemTheme === ThemeMode.DARK ? '#FFFFFF' : '#000000');

        Radio({ value: ThemeMode.LIGHT, group: 'theme' })
          .checked(this.currentTheme === ThemeMode.LIGHT)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.currentTheme = ThemeMode.LIGHT;
            }
          });
        Text('浅色模式')
          .fontColor(this.systemTheme === ThemeMode.DARK ? '#FFFFFF' : '#000000');

        Radio({ value: ThemeMode.DARK, group: 'theme' })
          .checked(this.currentTheme === ThemeMode.DARK)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.currentTheme = ThemeMode.DARK;
            }
          });
        Text('深色模式')
          .fontColor(this.systemTheme === ThemeMode.DARK ? '#FFFFFF' : '#000000');

        Radio({ value: ThemeMode.CUSTOM, group: 'theme' })
          .checked(this.currentTheme === ThemeMode.CUSTOM)
          .onChange((isChecked: boolean) => {
            if (isChecked) {
              this.currentTheme = ThemeMode.CUSTOM;
            }
          });
        Text('自定义主题')
          .fontColor(this.systemTheme === ThemeMode.DARK ? '#FFFFFF' : '#000000');
      }
      .padding(10)
      .backgroundColor(this.systemTheme === ThemeMode.DARK ? '#333333' : '#f5f5f5')
      .borderRadius(10)
      .width('100%')
      .margin({ top: 20 });

      // 深浅色切换按钮
      Row({space: 5}) {
        this.clickComponent('dark', '深色', (event: ClickEvent) => {
          let context = this.getUIContext().getHostContext()?.getApplicationContext();
          context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          // 更新系统主题状态
          this.systemTheme = ThemeMode.DARK;
        })
        this.clickComponent('light', '浅色', (event: ClickEvent) => {
          let context = this.getUIContext().getHostContext()?.getApplicationContext();
          context?.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          // 更新系统主题状态
          this.systemTheme = ThemeMode.LIGHT;
        })
      }.width('100%')
      .margin({ top: 10 })
      .justifyContent(FlexAlign.Center);

      // 动态主题下的 TextPicker - 直接在 build 方法中使用条件渲染
      if (this.currentTheme === ThemeMode.CUSTOM) {
        // 自定义主题
        WithTheme({
          theme: this.customTheme,
          colorMode: ThemeColorMode.LIGHT // 自定义主题搭配浅色模式
        }) {
          TextPicker({
            range: this.selectArray,
            selected: this.selectedValue
          })
            .height(200)
            .width('100%')
            .margin({ top: 20 })
        }
      } else if (this.currentTheme === ThemeMode.SYSTEM) {
        // 系统默认主题
        WithTheme({ colorMode: ThemeColorMode.SYSTEM }) {
          TextPicker({
            range: this.selectArray,
            selected: this.selectedValue
          })
            .height(200)
            .width('100%')
            .margin({ top: 20 })
        }
      } else if (this.currentTheme === ThemeMode.LIGHT) {
        // 浅色模式
        WithTheme({ colorMode: ThemeColorMode.LIGHT }) {
          TextPicker({
            range: this.selectArray,
            selected: this.selectedValue
          })
            .height(200)
            .width('100%')
            .margin({ top: 20 })
        }
      } else if (this.currentTheme === ThemeMode.DARK) {
        // 深色模式
        WithTheme({ colorMode: ThemeColorMode.DARK }) {
          TextPicker({
            range: this.selectArray,
            selected: this.selectedValue
          })
            .height(200)
            .width('100%')
            .margin({ top: 20 })
        }
      }

      // 显示当前选中的值
      Text(`当前选中值: ${this.selectArray[this.selectedValue]}`)
        .fontSize(16)
        .fontColor('#333333')
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin({ top: 10 });

      // 操作提示
      Text('提示：选择不同主题模式，观察 TextPicker 外观变化')
        .fontSize(14)
        .fontColor('#666666')
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin({ top: 20 });
    }
    .padding(20)
    .width('100%')
    .height('100%');
  }
}
