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
 * ArcSlider 位置测试用例 - 主要测试位置相关配置
 * 包括：
 * - 位置测试：LEFT/RIGHT
 * - 反向测试：reverse true/false
 * - 基础数值配置：progress, min, max
 * - 事件处理：onChange, onEnlarge
 */
import {
  ArcSlider,
  ArcSliderPosition,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderLayoutOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

// 位置配置
interface PositionConfig {
  name: string;
  position: ArcSliderPosition;
  reverse: boolean;
  description: string;
}

@Entry
@ComponentV2
struct ArcarSliderExample005 {
  // ========== 位置配置 ==========
  @Local currentPosition: ArcSliderPosition = ArcSliderPosition.RIGHT;
  @Local reverse: boolean = true;

  // 位置预设
  private positionConfigs: PositionConfig[] = [
    {
      name: '右侧-正向',
      position: ArcSliderPosition.RIGHT,
      reverse: true,
      description: '从下往上滑动'
    },
    {
      name: '右侧-反向',
      position: ArcSliderPosition.RIGHT,
      reverse: false,
      description: '从上往下滑动'
    },
    {
      name: '左侧-正向',
      position: ArcSliderPosition.LEFT,
      reverse: true,
      description: '从下往上滑动'
    },
    {
      name: '左侧-反向',
      position: ArcSliderPosition.LEFT,
      reverse: false,
      description: '从上往下滑动'
    }
  ];

  // ========== 数值配置 ==========
  @Local progress: number = 60;
  @Local minValue: number = 0;
  @Local maxValue: number = 100;

  // ========== 样式配置 ==========
  @Local trackColor: string = '#33FFFFFF';
  @Local selectedColor: string = '#FF5EA1FF';

  // ========== 状态 ==========
  @Local isEnlarged: boolean = false;

  // ========== 事件日志 ==========
  @Local eventLogs: string[] = [];
  @Local maxLogs: number = 8;

  // ========== ArcSlider配置 ==========
  @Local arcSliderOptions: ArcSliderOptions = new ArcSliderOptions({});

  aboutToAppear() {
    this.initializeOptions();
  }

  initializeOptions() {
    this.arcSliderOptions = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.progress,
        min: this.minValue,
        max: this.maxValue
      }),
      layoutOptions: new ArcSliderLayoutOptions({
        position: this.currentPosition,
        reverse: this.reverse
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 8,
        activeTrackThickness: 24,
        trackColor: this.trackColor,
        selectedColor: this.selectedColor,
        trackBlur: 20
      }),
      digitalCrownSensitivity: CrownSensitivity.MEDIUM,
      onChange: (value: number) => {
        this.progress = value;
        if (this.arcSliderOptions.valueOptions) {
          this.arcSliderOptions.valueOptions.progress = value;
        }
        this.addEventLog(`onChange: ${value.toFixed(1)}`);
      },
      onEnlarge: (enlarged: boolean) => {
        this.isEnlarged = enlarged;
        this.addEventLog(`onEnlarge: ${enlarged ? '放大' : '正常'}`);
      }
    });
  }

  addEventLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLogs.unshift(`[${timestamp}] ${message}`);
    if (this.eventLogs.length > this.maxLogs) {
      this.eventLogs = this.eventLogs.slice(0, this.maxLogs);
    }
  }

  clearLogs() {
    this.eventLogs = [];
  }

  // ========== 更新配置的方法 ==========
  updatePosition(pos: ArcSliderPosition, rev: boolean) {
    this.currentPosition = pos;
    this.reverse = rev;
    if (this.arcSliderOptions.layoutOptions) {
      this.arcSliderOptions.layoutOptions.position = pos;
      this.arcSliderOptions.layoutOptions.reverse = rev;
    }
    this.addEventLog(`位置更新: ${pos === ArcSliderPosition.LEFT ? 'LEFT' : 'RIGHT'}, 反向: ${rev}`);
  }

  updateProgress(value: number) {
    this.progress = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.progress = value;
    }
  }

  build() {
    Scroll() {
      Column() {
        // 标题
        Text('ArcSlider 位置测试')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15, bottom: 10 })

        Text('位置 · 反向 · 数值 · 事件')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 })

        // ========== 位置配置区域 ==========
        Column() {
          Text('位置配置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          // 位置预设按钮
          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.positionConfigs, (config: PositionConfig, index: number) => {
              Column() {
                Text(config.name)
                  .fontSize(12)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(
                    this.currentPosition === config.position && this.reverse === config.reverse ?
                      '#FFFFFF' : '#333333'
                  )
                  .margin({ bottom: 4 })
                Text(config.description)
                  .fontSize(10)
                  .fontColor(
                    this.currentPosition === config.position && this.reverse === config.reverse ?
                      '#FFFFFF' : '#666666'
                  )
              }
              .padding({ left: 14, right: 14, top: 10, bottom: 10 })
              .margin(6)
              .backgroundColor(
                this.currentPosition === config.position && this.reverse === config.reverse ?
                  '#FF5EA1FF' : '#E0E0E0'
              )
              .borderRadius(12)
              .onClick(() => {
                this.updatePosition(config.position, config.reverse);
              })
            })
          }
          .width('100%')
          .margin({ bottom: 12 })

          // 当前配置说明
          Row() {
            Text('当前位置: ')
              .fontSize(13)
            Text(this.currentPosition === ArcSliderPosition.LEFT ? 'LEFT (左侧)' : 'RIGHT (右侧)')
              .fontSize(13)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ bottom: 8 })

          Row() {
            Text('滑动方向: ')
              .fontSize(13)
            Text(this.reverse ? '正向（从下往上）' : '反向（从上往下）')
              .fontSize(13)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5FF')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== ArcSlider展示区域 ==========
        Column() {
          Stack() {
            Circle({ width: 466, height: 466 })
              .strokeWidth(0.5)
              .fill(Color.White)

            ArcSlider({ options: this.arcSliderOptions })
          }
          .width(476)
          .height(476)

          // 当前值显示
          Row() {
            Text('当前进度: ')
              .fontSize(14)
            Text(this.progress.toFixed(1).toString())
              .fontSize(24)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
              .margin({ left: 8 })

            Text(' / ' + this.maxValue.toString())
              .fontSize(14)
              .margin({ left: 4 })

            Blank()

            Text('状态: ')
              .fontSize(12)
            Text(this.isEnlarged ? '放大' : '正常')
              .fontSize(12)
              .fontColor(this.isEnlarged ? '#FF5EA1FF' : '#999999')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ top: 15 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FAFAFA')
        .borderRadius(12)
        .margin({ bottom: 20 })

        // ========== 数值配置区域 ==========
        Column() {
          Text('数值配置')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          // Progress控制
          Column() {
            Row() {
              Text('进度值')
                .fontSize(13)
              Text('(' + this.minValue + ' ~ ' + this.maxValue + ')')
                .fontSize(11)
                .fontColor('#666666')
            }
            .width('100%')
            .margin({ bottom: 8 })

            Slider({
              value: this.progress,
              min: this.minValue,
              max: this.maxValue,
              step: 1,
              style: SliderStyle.OutSet
            })
              .width('100%')
              .onChange((value: number) => {
                this.updateProgress(value);
              })
          }
          .width('100%')
          .margin({ bottom: 12 })

          // 最小最大值显示
          Row() {
            Column() {
              Text('范围: [' + this.minValue.toString())
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 6 })
              Text(this.maxValue.toString() + ']')
                .fontSize(14)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width('48%')
            .padding(10)
            .backgroundColor('#F5FFF5')
            .borderRadius(8)

            Blank()

            Column() {
              Text('说明')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 6 })
              Text('位置决定ArcSlider')
                .fontSize(11)
              Text('在屏幕上的位置')
                .fontSize(11)
            }
            .width('48%')
            .padding(10)
            .backgroundColor('#FFF5F5')
            .borderRadius(8)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== 事件日志 ==========
        Column() {
          Row() {
            Text('事件日志')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .margin({ right: 10 })

            Button('清除')
              .fontSize(11)
              .padding({ left: 12, right: 12, top: 4, bottom: 4 })
              .backgroundColor('#E0E0E0')
              .onClick(() => {
                this.clearLogs();
              })
          }
          .width('100%')
          .margin({ bottom: 10 })

          if (this.eventLogs.length === 0) {
            Text('暂无事件日志，请切换位置或拖动ArcSlider')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 20, bottom: 20 })
          } else {
            List({ space: 4 }) {
              ForEach(this.eventLogs, (log: string, index: number) => {
                ListItem() {
                  Text(log)
                    .fontSize(10)
                    .fontColor('#333333')
                    .padding({ left: 10, right: 10, top: 6, bottom: 6 })
                    .backgroundColor(index % 2 === 0 ? '#FFFFFF' : '#F5F5F5')
                    .borderRadius(4)
                    .width('100%')
                }
              })
            }
            .height(140)
          }
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FAFAFA')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })

        // ========== 说明区域 ==========
        Column() {
          Text('位置说明')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Column() {
            this.explainItem('ArcSliderPosition.LEFT', '左侧位置', 'ArcSlider显示在屏幕左侧')
            this.explainItem('ArcSliderPosition.RIGHT', '右侧位置', 'ArcSlider显示在屏幕右侧')
            this.explainItem('reverse: true', '正向方向', '从下往上滑动，起始点在下方')
            this.explainItem('reverse: false', '反向方向', '从上往下滑动，起始点在上方')
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FFFFF0')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })
      }
      .width('100%')
      .padding({ left: 15, right: 15 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
  }

  @Builder
  explainItem(title: string, desc: string, detail: string) {
    Column() {
      Text(title)
        .fontSize(13)
        .fontColor('#FF5EA1FF')
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 4 })
      Text(desc)
        .fontSize(11)
        .fontColor('#666666')
        .margin({ bottom: 2 })
      Text(detail)
        .fontSize(10)
        .fontColor('#999999')
        .margin({ bottom: 8 })
    }
    .width('100%')
  }
}
