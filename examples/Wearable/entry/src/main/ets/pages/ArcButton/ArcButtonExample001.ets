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

/**
 * ArcButton综合示例 - 展示各种样式和配置
 * 包含样式模式切换、位置切换、状态切换、自定义样式等功能
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonStyleMode,
  ArcButtonPosition,
  ColorMetrics,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample001 {
  // 样式模式数组
  private styleModes: ArcButtonStyleMode[] = [
    ArcButtonStyleMode.EMPHASIZED_LIGHT,
    ArcButtonStyleMode.EMPHASIZED_DARK,
    ArcButtonStyleMode.NORMAL_LIGHT,
    ArcButtonStyleMode.NORMAL_DARK,
    ArcButtonStyleMode.CUSTOM
  ];
  private styleModeNames: string[] = [
    '强调亮色',
    '强调暗色',
    '常规亮色',
    '常规暗色',
    '自定义'
  ];
  @Local currentStyleModeIndex: number = 0;

  // 位置数组
  private positions: ArcButtonPosition[] = [
    ArcButtonPosition.TOP_EDGE,
    ArcButtonPosition.BOTTOM_EDGE
  ];
  private positionNames: string[] = ['顶部', '底部'];
  @Local currentPositionIndex: number = 0;

  // 状态数组
  private statuses: ArcButtonStatus[] = [
    ArcButtonStatus.NORMAL,
    ArcButtonStatus.PRESSED,
    ArcButtonStatus.DISABLED
  ];
  private statusNames: string[] = ['正常', '按下', '禁用'];
  @Local currentStatusIndex: number = 0;

  // ArcButton配置
  @Local topOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local bottomOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 自定义样式配置
  @Local shadowEnabled: boolean = true;
  @Local fontSize: number = 15;

  aboutToAppear() {
    this.updateArcButtons();
  }

  // 更新ArcButton配置
  updateArcButtons() {
    const currentStyleMode = this.styleModes[this.currentStyleModeIndex];
    const currentPosition = this.positions[this.currentPositionIndex];
    const currentStatus = this.statuses[this.currentStatusIndex];

    // 自定义颜色配置
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');
    const customPressedColor: ColorMetrics = ColorMetrics.resourceColor('#FFAA00DD');
    const shadowColor: ColorMetrics = ColorMetrics.resourceColor('#80000000');

    this.topOptions = new ArcButtonOptions({
      label: this.positionNames[this.currentPositionIndex] + '按钮',
      position: currentPosition,
      styleMode: currentStyleMode,
      status: currentStatus,
      fontSize: new LengthMetrics(this.fontSize, LengthUnit.FP),
      shadowEnabled: this.shadowEnabled,
      shadowColor: shadowColor,
      // 自定义样式
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      pressedFontColor: customPressedColor,
      onClick: () => {
        console.info('Top ArcButton clicked');
      },
      onTouch: (event) => {
        console.info('Top ArcButton touch: ' + event.type);
      }
    });

    this.bottomOptions = new ArcButtonOptions({
      label: '底部按钮',
      styleMode: currentStyleMode,
      status: currentStatus,
      fontSize: new LengthMetrics(this.fontSize, LengthUnit.FP),
      shadowEnabled: this.shadowEnabled,
      shadowColor: shadowColor,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      onClick: () => {
        console.info('Bottom ArcButton clicked');
      }
    });
  }

  build() {
    Stack() {
      Column() {
        // 控制面板
        Column() {
          Text('ArcButton 综合示例')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 15 })

          // 样式模式切换
          Row() {
            Text('样式模式: ')
              .fontSize(14)
            Text(this.styleModeNames[this.currentStyleModeIndex])
              .fontSize(14)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 5 })

          Row() {
            Button('<')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentStyleModeIndex =
                  (this.currentStyleModeIndex - 1 + this.styleModes.length) % this.styleModes.length;
                this.topOptions.styleMode = this.styleModes[this.currentStyleModeIndex];
                this.bottomOptions.styleMode = this.styleModes[this.currentStyleModeIndex];
              })

            Blank()

            Button('>')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentStyleModeIndex = (this.currentStyleModeIndex + 1) % this.styleModes.length;
                this.topOptions.styleMode = this.styleModes[this.currentStyleModeIndex];
                this.bottomOptions.styleMode = this.styleModes[this.currentStyleModeIndex];
              })
          }
          .width('80%')
          .margin({ bottom: 10 })

          // 位置切换
          Row() {
            Text('位置: ')
              .fontSize(14)
            Text(this.positionNames[this.currentPositionIndex])
              .fontSize(14)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 5 })

          Row() {
            Button('<')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentPositionIndex =
                  (this.currentPositionIndex - 1 + this.positions.length) % this.positions.length;
                this.topOptions.position = this.positions[this.currentPositionIndex];
                this.topOptions.label = this.positionNames[this.currentPositionIndex] + '按钮';
              })

            Blank()

            Button('>')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentPositionIndex = (this.currentPositionIndex + 1) % this.positions.length;
                this.topOptions.position = this.positions[this.currentPositionIndex];
                this.topOptions.label = this.positionNames[this.currentPositionIndex] + '按钮';
              })
          }
          .width('80%')
          .margin({ bottom: 10 })

          // 状态切换
          Row() {
            Text('状态: ')
              .fontSize(14)
            Text(this.statusNames[this.currentStatusIndex])
              .fontSize(14)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 5 })

          Row() {
            Button('<')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentStatusIndex =
                  (this.currentStatusIndex - 1 + this.statuses.length) % this.statuses.length;
                this.topOptions.status = this.statuses[this.currentStatusIndex];
                this.bottomOptions.status = this.statuses[this.currentStatusIndex];
              })

            Blank()

            Button('>')
              .fontSize(12)
              .width(40)
              .height(30)
              .onClick(() => {
                this.currentStatusIndex = (this.currentStatusIndex + 1) % this.statuses.length;
                this.topOptions.status = this.statuses[this.currentStatusIndex];
                this.bottomOptions.status = this.statuses[this.currentStatusIndex];
              })
          }
          .width('80%')
          .margin({ bottom: 10 })

          // 阴影开关
          Row() {
            Text('阴影: ')
              .fontSize(14)
            Toggle({ type: ToggleType.Switch, isOn: this.shadowEnabled })
              .onChange((isOn: boolean) => {
                this.shadowEnabled = isOn;
                this.topOptions.shadowEnabled = isOn;
                this.bottomOptions.shadowEnabled = isOn;
              })
          }
          .width('80%')
          .margin({ bottom: 10 })

          // 字体大小
          Row() {
            Text('字体大小: ')
              .fontSize(14)
            Text(this.fontSize.toString())
              .fontSize(14)
              .fontColor('#FF6200EE')
          }
          .width('80%')
          .margin({ bottom: 5 })

          Slider({
            value: this.fontSize,
            min: 10,
            max: 25,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('80%')
            .onChange((value: number) => {
              this.fontSize = value;
              const newFontSize = new LengthMetrics(value, LengthUnit.FP);
              this.topOptions.fontSize = newFontSize;
              this.bottomOptions.fontSize = newFontSize;
            })
        }
        .width(300)
        .padding(15)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)
        .margin({ top: 20, bottom: 10 })

        // ArcButton展示区域
        Stack() {
          Circle({ width: 233, height: 233 })
            .strokeWidth(0.1)
            .fill(Color.White)

          Column() {
            ArcButton({ options: this.topOptions })
            Blank()
            ArcButton({ options: this.bottomOptions })
          }
          .width('100%')
          .height('100%')
        }
        .width(233)
        .height(233)
        .margin({ top: 10 })
      }
      .width('100%')
      .height('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
  }
}
