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
 * ArcButton进度条交互示例 - 展示进度条的动态更新和用户交互
 * 包含步进控制、跳转到特定进度、颜色自定义等场景
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample007 {
  @Local currentProgress: number = 25;
  @Local totalProgress: number = 100;
  @Local stepSize: number = 10;
  @Local progressOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local controlOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local quickJumpProgress: number = 75;
  @Local quickJumpTotal: number = 100;
  @Local customColor: string = '#1F71FF';
  @Local showAdvancedControls: boolean = false;

  aboutToAppear() {
    this.progressOptions = new ArcButtonOptions({
      label: this.currentProgress + '%',
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: {
        value: this.currentProgress,
        total: this.totalProgress,
        color: this.customColor
      }
    });
    this.updateControlButton();
  }

  updateProgressButton() {
    if (this.progressOptions) {
      this.progressOptions.label = this.currentProgress + '%'
      if (this.progressOptions.progressConfig) {
        this.progressOptions.progressConfig.value = this.currentProgress
        this.progressOptions.progressConfig.total = this.totalProgress
        this.progressOptions.progressConfig.color = this.customColor
      }
    }
  }

  updateControlButton() {
    this.controlOptions = new ArcButtonOptions({
      label: '控制',
      styleMode: 0, // NORMAL_LIGHT
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true
    });
  }

  handleStep(direction: number) {
    const newValue = this.currentProgress + direction * this.stepSize;
    if (newValue < 0) {
      this.currentProgress = 0;
    } else if (newValue > this.totalProgress) {
      this.currentProgress = this.totalProgress;
    } else {
      this.currentProgress = newValue;
    }
    this.updateProgressButton();
  }

  jumpToProgress(target: number) {
    this.currentProgress = Math.max(0, Math.min(this.totalProgress, target));
    this.updateProgressButton();
  }

  changeColor(color: string) {
    this.customColor = color;
    this.updateProgressButton();
  }
  build(){
    Scroll(){
      Column() {
        Column() {
          // 标题区域
          Column() {
            Text('ArcButton 进度条交互示例')
              .fontSize(24)
              .fontWeight(FontWeight.Bold)
              .margin({ top: 20, bottom: 15 })

            Row() {
              Text('当前进度: ')
                .fontSize(14)
              Text(this.currentProgress + '%')
                .fontSize(14)
                .fontColor('#1F71FF')
                .fontWeight(FontWeight.Bold)
            }
            .margin({ bottom: 10 })

            Row() {
              Text('总进度: ')
                .fontSize(14)
              Text(this.totalProgress.toString())
                .fontSize(14)
                .fontColor('#666666')
            }
          }
          .width('90%')
          .padding(15)
          .backgroundColor('#F5F5F5')
          .borderRadius(10)
          .margin({ top: 10, bottom: 15 })

          // 步进控制
          Column() {
            Text('步进控制')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Row() {
              Text('步进大小: ')
                .fontSize(14)

              Button('-')
                .fontSize(12)
                .width(40)
                .height(30)
                .margin({ right: 10 })
                .onClick(() => {
                  if (this.stepSize > 1) {
                    this.stepSize--;
                  }
                })

              Text(this.stepSize.toString())
                .fontSize(14)
                .fontColor('#1F71FF')

              Button('+')
                .fontSize(12)
                .width(40)
                .height(30)
                .margin({ left: 10 })
                .onClick(() => {
                  if (this.stepSize < 50) {
                    this.stepSize++;
                  }
                })
            }
            .margin({ bottom: 10 })
            .justifyContent(FlexAlign.Center)

            Row() {
              Button('-10')
                .fontSize(12)
                .width(80)
                .margin({ right: 5 })
                .onClick(() => this.handleStep(-1))

              Button('-5')
                .fontSize(12)
                .width(70)
                .margin({ right: 5 })
                .onClick(() => this.handleStep(-1))

              Button('+5')
                .fontSize(12)
                .width(70)
                .margin({ right: 5 })
                .onClick(() => this.handleStep(1))

              Button('+10')
                .fontSize(12)
                .width(80)
                .margin({ left: 5 })
                .onClick(() => this.handleStep(1))

              Button('重置')
                .fontSize(12)
                .width(70)
                .margin({ left: 10 })
                .backgroundColor('#FFE5E5')
                .onClick(() => {
                  this.currentProgress = 0;
                  this.updateProgressButton();
                })
            }
            .margin({ bottom: 10 })
            .justifyContent(FlexAlign.SpaceBetween)

            Row() {
              Button('0%')
                .fontSize(12)
                .width(70)
                .onClick(() => this.jumpToProgress(0))

              Button('25%')
                .fontSize(12)
                .width(70)
                .onClick(() => this.jumpToProgress(25))

              Button('50%')
                .fontSize(12)
                .width(70)
                .onClick(() => this.jumpToProgress(50))

              Button('75%')
                .fontSize(12)
                .width(70)
                .onClick(() => this.jumpToProgress(75))

              Button('100%')
                .fontSize(12)
                .width(70)
                .onClick(() => this.jumpToProgress(100))
            }
            .margin({ bottom: 10 })
            .justifyContent(FlexAlign.SpaceBetween)
          }
          .width('90%')
          .padding(15)
          .backgroundColor('#F0F0F0')
          .borderRadius(10)
          .margin({ bottom: 15 })

          // 颜色选择
          Column() {
            Text('进度条颜色')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Row() {
              Button({
                type: ButtonType.Circle,
                stateEffect: this.customColor === '#1F71FF' ? true : false
              })
                .width(40)
                .height(40)
                .backgroundColor('#1F71FF')
                .margin({ right: 10 })
                .onClick(() => this.changeColor('#1F71FF'))

              Button({
                type: ButtonType.Circle,
                stateEffect: this.customColor === '#FF6200EE' ? true : false
              })
                .width(40)
                .height(40)
                .backgroundColor('#FF6200EE')
                .margin({ right: 10 })
                .onClick(() => this.changeColor('#FF6200EE'))

              Button({
                type: ButtonType.Circle,
                stateEffect: this.customColor === '#00BCD4' ? true : false
              })
                .width(40)
                .height(40)
                .backgroundColor('#00BCD4')
                .margin({ right: 10 })
                .onClick(() => this.changeColor('#00BCD4'))

              Button({
                type: ButtonType.Circle,
                stateEffect: this.customColor === '#E91E63' ? true : false
              })
                .width(40)
                .height(40)
                .backgroundColor('#E91E63')
                .onClick(() => this.changeColor('#E91E63'))

              Button({
                type: ButtonType.Circle,
                stateEffect: this.customColor === '#FF5722' ? true : false
              })
                .width(40)
                .height(40)
                .backgroundColor('#FF5722')
                .onClick(() => this.changeColor('#FF5722'))
            }
          }
          .width('90%')
          .padding(15)
          .backgroundColor('#F0F0F0')
          .borderRadius(10)
          .margin({ bottom: 15 })

          // 高级控制
          Column() {
            Row() {
              Text('高级控制')
                .fontSize(18)
                .fontWeight(FontWeight.Bold)
                .margin({ right: 10 })

              Toggle({
                type: ToggleType.Switch,
                isOn: this.showAdvancedControls
              })
                .onChange((isOn: boolean) => {
                  this.showAdvancedControls = isOn;
                })
            }
            .margin({ bottom: 10 })

            if (this.showAdvancedControls) {
              Column() {
                Text('快速跳转')
                  .fontSize(14)
                  .margin({ bottom: 5 })

                Row() {
                  Text('快速跳转到: ')
                    .fontSize(12)

                  Button('75%')
                    .fontSize(12)
                    .width(60)
                    .margin({ right: 5 })
                    .onClick(() => this.jumpToProgress(75))

                  Text(' / ')
                    .fontSize(12)

                  TextInput({
                    text: this.quickJumpProgress.toString(),

                  })
                    .width(60)
                    .height(30)
                    .onChange((value: string) => {
                      this.quickJumpProgress = parseInt(value) || 0;
                    })

                  Button('跳转')
                    .fontSize(12)
                    .width(50)
                    .onClick(() => {
                      this.jumpToProgress(this.quickJumpProgress);
                    })
                }
              }
              .margin({ bottom: 10 })

              Row() {
                Text('自定义总数: ')
                  .fontSize(12)

                TextInput({
                  text: this.quickJumpTotal.toString(),

                })
                  .width(100)
                  .height(30)
                  .onChange((value: string) => {
                    this.quickJumpTotal = parseInt(value) || 100;
                  })

                Button('设置')
                  .fontSize(12)
                  .width(60)
                  .margin({ left: 10 })
                  .onClick(() => {
                    this.totalProgress = this.quickJumpTotal;
                    this.currentProgress = Math.min(this.currentProgress, this.totalProgress);
                    this.updateProgressButton();
                  })
              }
            }
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ArcButton展示区域
        Column() {
          Row() {
            // 进度条按钮
            Column() {
              Stack() {
                Circle({ width: 200, height: 200 })
                  .strokeWidth(0.1)
                  .fill(Color.White)

                Column() {
                  Blank()
                  ArcButton({ options: this.progressOptions })
                }
                .width('100%')
                .height('100%')
              }
              .width(200)
              .height(200)

              Text('进度条')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })

            // 控制按钮
            Column() {
              Stack() {
                Circle({ width: 200, height: 200 })
                  .strokeWidth(0.1)
                  .fill(Color.White)

                Column() {
                  Blank()
                  ArcButton({ options: this.controlOptions })
                }
                .width('100%')
                .height('100%')
              }
              .width(200)
              .height(200)

              Text('点击控制步进')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
          }
          .margin({ top: 30 })
          .justifyContent(FlexAlign.Center)

          // 使用说明
          Column() {
            Text('使用说明')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Text('• 点击控制按钮可以步进或跳转进度')
              .fontSize(12)
              .margin({ bottom: 5 })

            Text('• 可以调整步进大小（1-50）')
              .fontSize(12)
              .margin({ bottom: 5 })

            Text('• 可以选择不同的进度条颜色')
              .fontSize(12)
              .margin({ bottom: 5 })

            Text('• 高级控制支持自定义总数和快速跳转')
              .fontSize(12)
              .margin({ bottom: 5 })

            Text('• 进度值会自动限制在 [0, total] 范围内')
              .fontSize(12)
              .margin({ bottom: 5 })
          }
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)
        .margin({ top: 20 })
      }
      .width('100%')
      .height('200%')
      .backgroundColor('#E8E8EB')
    }
  }
}

