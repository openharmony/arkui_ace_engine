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
 * ArcSlider基础示例 - 展示ArcSlider组件的基本用法
 * 包括数值配置、布局配置、样式配置和事件处理
 * 常用于穿戴设备中快速调节设置值，如音量调节、亮度调节等
 */
import {
  ArcSlider,
  ArcSliderPosition,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderLayoutOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcSliderExample01 {
  // 位置数组
  private positions: ArcSliderPosition[] = [
    ArcSliderPosition.LEFT,
    ArcSliderPosition.RIGHT
  ];
  private positionNames: string[] = ['左侧', '右侧'];
  @Local currentPositionIndex: number = 1;

  // 数值配置
  @Local progressValue: number = 60;
  @Local minValue: number = 0;
  @Local maxValue: number = 100;

  // 布局配置
  @Local reverse: boolean = true;

  // 样式配置
  @Local trackThickness: number = 8;
  @Local activeTrackThickness: number = 24;
  @Local trackColor: string = '#33FFFFFF';
  @Local selectedColor: string = '#FF5EA1FF';
  @Local trackBlur: number = 20;

  // 表冠灵敏度
  @Local crownSensitivity: CrownSensitivity = CrownSensitivity.MEDIUM;
  private sensitivityLevels: CrownSensitivity[] = [
    CrownSensitivity.LOW,
    CrownSensitivity.MEDIUM,
    CrownSensitivity.HIGH
  ];
  private sensitivityNames: string[] = ['低', '中', '高'];
  @Local currentSensitivityIndex: number = 1;

  // 事件日志
  @Local eventLogs: string[] = [];
  @Local maxLogs: number = 8;

  // 放大状态
  @Local isEnlarged: boolean = false;

  // ArcSlider配置
  @Local arcSliderOptions: ArcSliderOptions = new ArcSliderOptions({});

  aboutToAppear() {
    // 初始化ArcSlider配置
    this.arcSliderOptions = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.progressValue,
        min: this.minValue,
        max: this.maxValue
      }),
      layoutOptions: new ArcSliderLayoutOptions({
        reverse: this.reverse,
        position: this.positions[this.currentPositionIndex]
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: this.trackThickness,
        activeTrackThickness: this.activeTrackThickness,
        trackColor: this.trackColor,
        selectedColor: this.selectedColor,
        trackBlur: this.trackBlur
      }),
      digitalCrownSensitivity: this.crownSensitivity,
      onTouch: (event) => {
        this.addEventLog('onTouch - 触摸事件触发');
      },
      onChange: (progress: number) => {
        this.progressValue = progress;
        if (this.arcSliderOptions.valueOptions) {
          this.arcSliderOptions.valueOptions.progress = progress;
        }
        this.addEventLog(`onChange - 进度值: ${progress.toFixed(1)}`);
      },
      onEnlarge: (isEnlarged: boolean) => {
        this.isEnlarged = isEnlarged;
        this.addEventLog(`onEnlarge - ${isEnlarged ? '放大' : '缩小'}状态`);
      }
    });
  }

  // 添加事件日志
  addEventLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLogs.unshift(`[${timestamp}] ${message}`);
    if (this.eventLogs.length > this.maxLogs) {
      this.eventLogs = this.eventLogs.slice(0, this.maxLogs);
    }
  }

  // 清除日志
  clearLogs() {
    this.eventLogs = [];
  }

  build() {
    Scroll() {
      Column() {
        // 控制面板
        Column() {
          Text('ArcSlider 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          // 当前值显示
          Row() {
            Text('当前值: ')
              .fontSize(14)
            Text(this.progressValue.toFixed(1).toString())
              .fontSize(20)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 10 })

          // 放大状态
          Row() {
            Text('状态: ')
              .fontSize(14)
            Text(this.isEnlarged ? '放大' : '正常')
              .fontSize(14)
              .fontColor(this.isEnlarged ? '#FF5EA1FF' : '#999999')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 10 })

          // 位置切换
          Row() {
            Text('位置: ')
              .fontSize(13)
            Text(this.positionNames[this.currentPositionIndex])
              .fontSize(13)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 5 })

          Row() {
            Button('<')
              .fontSize(11)
              .width(35)
              .height(25)
              .onClick(() => {
                this.currentPositionIndex =
                  (this.currentPositionIndex - 1 + this.positions.length) % this.positions.length;
                if(this.arcSliderOptions.layoutOptions){
                  this.arcSliderOptions.layoutOptions.position = this.positions[this.currentPositionIndex];
                }
              })

            Blank()

            Button('>')
              .fontSize(11)
              .width(35)
              .height(25)
              .onClick(() => {
                this.currentPositionIndex = (this.currentPositionIndex + 1) % this.positions.length;
                if(this.arcSliderOptions.layoutOptions) {
                  this.arcSliderOptions.layoutOptions.position = this.positions[this.currentPositionIndex];
                }
              })
          }
          .width('90%')
          .margin({ bottom: 8 })

          // 最小值设置
          Row() {
            Text('最小值: ')
              .fontSize(13)
            Text(this.minValue.toString())
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 3 })

          Slider({
            value: this.minValue,
            min: 0,
            max: 50,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.minValue = value;
              if (this.arcSliderOptions.valueOptions) {
                this.arcSliderOptions.valueOptions.min = value;
              }
              if (this.minValue >= this.maxValue) {
                this.maxValue = this.minValue + 10;
                if (this.arcSliderOptions.valueOptions) {
                  this.arcSliderOptions.valueOptions.max = this.maxValue;
                }
              }
              if (this.progressValue < this.minValue) {
                this.progressValue = this.minValue;
                if (this.arcSliderOptions.valueOptions) {
                  this.arcSliderOptions.valueOptions.progress = this.minValue;
                }
              }
            })

          // 最大值设置
          Row() {
            Text('最大值: ')
              .fontSize(13)
            Text(this.maxValue.toString())
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 3 })
          .margin({ top: 8 })

          // 最大值设置
          Slider({
            value: this.maxValue,
            min: 50,
            max: 200,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.maxValue = value;
              if (this.arcSliderOptions.valueOptions) {
                this.arcSliderOptions.valueOptions.max = value;
              }
              if (this.maxValue <= this.minValue) {
                this.minValue = this.maxValue - 10;
                if (this.arcSliderOptions.valueOptions) {
                  this.arcSliderOptions.valueOptions.min = this.minValue;
                }
              }
              if (this.progressValue > this.maxValue) {
                this.progressValue = this.maxValue;
                if (this.arcSliderOptions.valueOptions) {
                  this.arcSliderOptions.valueOptions.progress = this.maxValue;
                }
              }
            })

          // 表冠灵敏度
          Row() {
            Text('表冠灵敏度: ')
              .fontSize(13)
            Text(this.sensitivityNames[this.currentSensitivityIndex])
              .fontSize(13)
              .fontColor('#FF6200EE')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 5 })
          .margin({ top: 8 })

          Row() {
            Button('<')
              .fontSize(11)
              .width(35)
              .height(25)
              .onClick(() => {
                this.currentSensitivityIndex =
                  (this.currentSensitivityIndex - 1 + this.sensitivityLevels.length) % this.sensitivityLevels.length;
                this.crownSensitivity = this.sensitivityLevels[this.currentSensitivityIndex];
                this.arcSliderOptions.digitalCrownSensitivity = this.crownSensitivity;
              })

            Blank()

            Button('>')
              .fontSize(11)
              .width(35)
              .height(25)
              .onClick(() => {
                this.currentSensitivityIndex = (this.currentSensitivityIndex + 1) % this.sensitivityLevels.length;
                this.crownSensitivity = this.sensitivityLevels[this.currentSensitivityIndex];
                this.arcSliderOptions.digitalCrownSensitivity = this.crownSensitivity;
              })
          }
          .width('90%')
          .margin({ bottom: 8 })

          // 方向切换
          Row() {
            Text('方向: ')
              .fontSize(13)
            Text(this.reverse ? '从下往上' : '从上往下')
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 8 })

          Toggle({ type: ToggleType.Switch, isOn: this.reverse })
            .onChange((isOn: boolean) => {
              this.reverse = isOn;
              if (this.arcSliderOptions.layoutOptions) {
                this.arcSliderOptions.layoutOptions.reverse = isOn;
              }
            })

          // 描边粗细
          Row() {
            Text('描边粗细: ')
              .fontSize(13)
            Text(this.trackThickness.toString())
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 3 })
          .margin({ top: 8 })

          Slider({
            value: this.trackThickness,
            min: 5,
            max: 16,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.trackThickness = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.trackThickness = value;
              }
            })

          // 放大粗细
          Row() {
            Text('放大粗细: ')
              .fontSize(13)
            Text(this.activeTrackThickness.toString())
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 3 })
          .margin({ top: 8 })

          Slider({
            value: this.activeTrackThickness,
            min: 24,
            max: 36,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.activeTrackThickness = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.activeTrackThickness = value;
              }
            })

          // 模糊值
          Row() {
            Text('模糊值: ')
              .fontSize(13)
            Text(this.trackBlur.toString())
              .fontSize(13)
              .fontColor('#FF6200EE')
          }
          .width('100%')
          .margin({ bottom: 3 })
          .margin({ top: 8 })

          Slider({
            value: this.trackBlur,
            min: 0,
            max: 40,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.trackBlur = value;
              if (this.arcSliderOptions.styleOptions) {
                this.arcSliderOptions.styleOptions.trackBlur = value;
              }
            })

          // 清除日志按钮
          Button('清除日志')
            .fontSize(12)
            .width(100)
            .height(30)
            .margin({ top: 10 })
            .backgroundColor('#F5F5F5')
            .onClick(() => {
              this.clearLogs();
            })
        }
        .width(280)
        .padding(12)
        .backgroundColor('#F0F0F0')
        .borderRadius(10)
        .margin({ top: 15, left: 15 })

        // ArcSlider展示区域和日志
        Column() {

          // ArcSlider展示
          Stack() {
            Circle({ width: 466, height: 466 })
              .strokeWidth(0.1)
              .fill(Color.White)

            ArcSlider({ options: this.arcSliderOptions })
          }
          .width("100%")
          .height("30%")
          .margin({ top: 10, bottom: 15 })

          // 事件日志区域
          Column() {
            Row() {
              Text('事件日志')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .margin({ right: 10 })
              Text(`(最近${this.maxLogs}条)`)
                .fontSize(11)
                .fontColor('#666666')
            }
            .width('100%')
            .margin({ bottom: 8 })

            if (this.eventLogs.length === 0) {
              Text('暂无事件日志，请拖动ArcSlider')
                .fontSize(12)
                .fontColor('#999999')
                .margin({ top: 15, bottom: 15 })
            } else {
              List({ space: 4 }) {
                ForEach(this.eventLogs, (log: string, index: number) => {
                  ListItem() {
                    Text(log)
                      .fontSize(10)
                      .fontColor(index % 2 === 0 ? '#333333' : '#555555')
                      .padding({ left: 8, right: 8, top: 4, bottom: 4 })
                      .backgroundColor(index % 2 === 0 ? '#FFFFFF' : '#F9F9F9')
                      .borderRadius(4)
                      .width('100%')
                  }
                })
              }
              .width('100%')
              .height(150)
            }
          }
          .width('90%')
          .padding(12)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ left: 15, right: 15, bottom: 15 })
        }
      }
      .width('100%')
      .height('150%')
    }
    .width('100%')
    .height('150%')
    .backgroundColor(Color.Gray)
  }
}
