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
 * ArcSlider onChange 事件测试用例
 * 包括：
 * - onChange 事件的基础触发测试
 * - 数值变化的详细记录
 * - 不同范围下的变化统计
 * - 增量变化和方向检测
 * - 事件频率统计
 */
import {
  ArcSlider,
  ArcSliderPosition,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderLayoutOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

// 事件记录
interface ChangeRecord {
  id: number;
  value: number;
  previousValue: number;
  delta: number;
  direction: string;
  timestamp: string;
}

// 统计数据
interface ChangeStats {
  totalChanges: number;
  increaseCount: number;
  decreaseCount: number;
  noChangeCount: number;
  minValue: number;
  maxValue: number;
  avgDelta: number;
}

@Entry
@ComponentV2
struct ArcSliderExample007 {
  // ========== 数值配置 ==========
  @Local progress: number = 50;
  @Local minValue: number = 0;
  @Local maxValue: number = 100;

  // ========== 位置配置 ==========
  @Local currentPosition: ArcSliderPosition = ArcSliderPosition.RIGHT;
  @Local reverse: boolean = true;

  // ========== 样式配置 ==========
  @Local trackThickness: number = 8;
  @Local activeTrackThickness: number = 24;
  @Local trackColor: string = '#33FFFFFF';
  @Local selectedColor: string = '#FF5EA1FF';
  @Local trackBlur: number = 20;

  // ========== 事件记录 ==========
  @Local changeRecords: ChangeRecord[] = [];
  @Local maxRecords: number = 15;

  @Local previousProgress: number = 50;
  @Local currentDelta: number = 0;
  @Local currentDirection: string = '无';

  // ========== 统计数据 ==========
  @Local changeStats: ChangeStats = {
    totalChanges: 0,
    increaseCount: 0,
    decreaseCount: 0,
    noChangeCount: 0,
    minValue: 50,
    maxValue: 50,
    avgDelta: 0
  };

  @Local firstChangeTime: number = 0;
  @Local lastChangeTime: number = 0;
  @Local totalDeltaSum: number = 0;

  // ========== 控制开关 ==========
  @Local enableDetailedLog: boolean = true;
  @Local enableStats: boolean = true;

  // ========== ArcSlider配置 ==========
  @Local arcSliderOptions: ArcSliderOptions = new ArcSliderOptions({});

  @Local recordId: number = 0;

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
        trackThickness: this.trackThickness,
        activeTrackThickness: this.activeTrackThickness,
        trackColor: this.trackColor,
        selectedColor: this.selectedColor,
        trackBlur: this.trackBlur
      }),
      digitalCrownSensitivity: CrownSensitivity.MEDIUM,
      onChange: (value: number) => {
        this.handleOnChange(value);
      }
    });
  }

  handleOnChange(value: number) {
    if (!this.enableDetailedLog) {
      return;
    }

    const now = Date.now();

    // 计算变化量
    this.currentDelta = value - this.previousProgress;
    this.previousProgress = value;

    // 判断方向
    if (this.currentDelta > 0.01) {
      this.currentDirection = '增加';
    } else if (this.currentDelta < -0.01) {
      this.currentDirection = '减少';
    } else {
      this.currentDirection = '不变';
    }

    // 更新进度
    this.progress = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.progress = value;
    }

    // 更新统计数据
    if (this.enableStats) {
      this.updateStats(value, now);
    }

    // 记录变化
    this.recordChange(value, now);
  }

  updateStats(value: number, now: number) {
    this.changeStats.totalChanges++;

    // 记录首次变化时间
    if (this.firstChangeTime === 0) {
      this.firstChangeTime = now;
    }
    this.lastChangeTime = now;

    // 更新变化方向统计
    if (this.currentDelta > 0.01) {
      this.changeStats.increaseCount++;
    } else if (this.currentDelta < -0.01) {
      this.changeStats.decreaseCount++;
    } else {
      this.changeStats.noChangeCount++;
    }

    // 更新最小最大值
    if (value < this.changeStats.minValue) {
      this.changeStats.minValue = value;
    }
    if (value > this.changeStats.maxValue) {
      this.changeStats.maxValue = value;
    }

    // 计算平均变化量
    this.totalDeltaSum += Math.abs(this.currentDelta);
    this.changeStats.avgDelta = this.totalDeltaSum / this.changeStats.totalChanges;
  }

  recordChange(value: number, now: number) {
    this.recordId++;
    const record: ChangeRecord = {
      id: this.recordId,
      value: value,
      previousValue: this.previousProgress,
      delta: this.currentDelta,
      direction: this.currentDirection,
      timestamp: new Date(now).toLocaleTimeString()
    };
    this.changeRecords.unshift(record);
    if (this.changeRecords.length > this.maxRecords) {
      this.changeRecords = this.changeRecords.slice(0, this.maxRecords);
    }
  }

  getDirectionColor(direction: string): string {
    switch (direction) {
      case '增加':
        return '#FF00FF00';
      case '减少':
        return '#FFFF0000';
      case '不变':
        return '#666666';
      default:
        return '#999999';
    }
  }

  clearRecords() {
    this.changeRecords = [];
    this.changeStats = {
      totalChanges: 0,
      increaseCount: 0,
      decreaseCount: 0,
      noChangeCount: 0,
      minValue: this.progress,
      maxValue: this.progress,
      avgDelta: 0
    };
    this.previousProgress = this.progress;
    this.currentDelta = 0;
    this.currentDirection = '无';
    this.recordId = 0;
    this.firstChangeTime = 0;
    this.lastChangeTime = 0;
    this.totalDeltaSum = 0;
  }

  updateProgress(value: number) {
    this.progress = value;
    this.previousProgress = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.progress = value;
    }
  }

  build() {
    Scroll() {
      Column() {
        // 标题
        Text('ArcSlider onChange 事件测试')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15, bottom: 10 })

        Text('测试数值变化、方向检测、统计信息')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 20 })

        // ========== 统计面板 ==========
        Column() {
          Row() {
            Text('变化统计')
              .fontSize(15)
              .fontWeight(FontWeight.Bold)
              .margin({ right: 10 })

            Button('清除')
              .fontSize(11)
              .padding({ left: 8, right: 8, top: 4, bottom: 4 })
              .backgroundColor('#EEDDDD')
              .onClick(() => {
                this.clearRecords();
              })
          }
          .width('100%')
          .margin({ bottom: 12 })

          // 统计卡片
          Row() {
            this.statCard('总变化', this.changeStats.totalChanges, '#FF5EA1FF')
            Blank().width(10)
            this.statCard('增加', this.changeStats.increaseCount, '#FF00FF00')
            Blank().width(10)
            this.statCard('减少', this.changeStats.decreaseCount, '#FFFF0000')
          }
          .width('100%')

          // 数值范围
          Row() {
            Column() {
              Text('最小值')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ bottom: 4 })
              Text(this.changeStats.minValue.toFixed(1))
                .fontSize(16)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width(60)

            Blank()

            Column() {
              Text('最大值')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ bottom: 4 })
              Text(this.changeStats.maxValue.toFixed(1))
                .fontSize(16)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width(60)

            Blank()

            Column() {
              Text('平均变化')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ bottom: 4 })
              Text(this.changeStats.avgDelta.toFixed(2))
                .fontSize(16)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width(70)
          }
          .width('100%')
          .margin({ top: 12 })

          // 当前状态
          Row() {
            Text('当前值: ')
              .fontSize(13)
            Text(this.progress.toFixed(1))
              .fontSize(18)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)

            Blank()

            Text('方向: ')
              .fontSize(13)
            Text(this.currentDirection)
              .fontSize(14)
              .fontColor(this.getDirectionColor(this.currentDirection))
              .fontWeight(FontWeight.Bold)

            Blank()

            Text('变化量: ')
              .fontSize(13)
            Text((this.currentDelta >= 0 ? '+' : '') + this.currentDelta.toFixed(2))
              .fontSize(14)
              .fontColor(this.currentDelta > 0 ? '#FF00FF00' : (this.currentDelta < 0 ? '#FFFF0000' : '#666666'))
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ top: 10 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FAFAFA')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== 控制开关 ==========
        Column() {
          Text('控制开关')
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          // 详细日志开关
          Row() {
            Text('启用详细日志')
              .fontSize(13)
            Blank()
            Toggle({ type: ToggleType.Switch, isOn: this.enableDetailedLog })
              .selectedColor('#FF5EA1FF')
              .onChange((isOn: boolean) => {
                this.enableDetailedLog = isOn;
              })
          }
          .width('100%')
          .margin({ bottom: 10 })

          // 统计开关
          Row() {
            Text('启用统计')
              .fontSize(13)
            Blank()
            Toggle({ type: ToggleType.Switch, isOn: this.enableStats })
              .selectedColor('#FF5EA1FF')
              .onChange((isOn: boolean) => {
                this.enableStats = isOn;
              })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== ArcSlider展示区域 ==========
        Column() {
          Stack() {
            Circle({ width: 480, height: 480 })
              .strokeWidth(0.5)
              .fill(Color.White)

            ArcSlider({ options: this.arcSliderOptions })
          }
          .width(500)
          .height(500)

          // 当前进度显示
          Row() {
            Text('当前进度: ')
              .fontSize(14)
            Text(this.progress.toFixed(1).toString())
              .fontSize(24)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
              .margin({ left: 8 })
          }
          .width('100%')
          .margin({ top: 15 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFFFFF')
        .borderRadius(12)
        .margin({ bottom: 20 })

        // ========== 数值配置 ==========
        Column() {
          Text('数值配置')
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          Column() {
            Text('进度值')
              .fontSize(13)
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
          .margin({ bottom: 10 })

          Row() {
            Column() {
              Text('最小值')
                .fontSize(12)
                .margin({ bottom: 6 })
              Text(this.minValue.toString())
                .fontSize(14)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width('48%')
            .padding(8)
            .backgroundColor('#F5FFF5')
            .borderRadius(8)

            Blank()

            Column() {
              Text('最大值')
                .fontSize(12)
                .margin({ bottom: 6 })
              Text(this.maxValue.toString())
                .fontSize(14)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width('48%')
            .padding(8)
            .backgroundColor('#FF5FFF5')
            .borderRadius(8)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== 变化记录 ==========
        Column() {
          Text('数值变化记录 (最新15条)')
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          if (this.changeRecords.length === 0) {
            Column() {
              Text('暂无变化记录')
                .fontSize(13)
                .fontColor('#999999')
                .margin({ top: 15, bottom: 8 })

              Text('请在ArcSlider上进行拖动操作')
                .fontSize(12)
                .fontColor('#BBBBBB')
                .margin({ bottom: 8 })

              Text('提示：')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 4 })

              Text('• 增加: 数值变大')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })

              Text('• 减少: 数值变小')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })

              Text('• 变化量: 与上次的差值')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })
            }
            .width('100%')
            .padding(20)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
          } else {
            List({ space: 3 }) {
              ForEach(this.changeRecords, (record: ChangeRecord, index: number) => {
                ListItem() {
                  Row() {
                    Column() {
                      Text(`#${record.id}`)
                        .fontSize(11)
                        .fontColor('#999999')
                      Text(record.value.toFixed(1))
                        .fontSize(14)
                        .fontColor('#FF5EA1FF')
                        .fontWeight(FontWeight.Bold)
                    }
                    .width(60)

                    Column() {
                      Row() {
                        Text('变化量: ')
                          .fontSize(11)
                        Text((record.delta >= 0 ? '+' : '') + record.delta.toFixed(2))
                          .fontSize(12)
                          .fontColor(record.delta > 0 ? '#FF00FF00' : (record.delta < 0 ? '#FFFF0000' : '#666666'))
                      }
                      .width('100%')
                      .margin({ bottom: 4 })

                      Row() {
                        Text('方向: ')
                          .fontSize(11)
                        Text(record.direction)
                          .fontSize(12)
                          .fontColor(this.getDirectionColor(record.direction))
                      }
                      .width('100%')
                    }
                    .layoutWeight(1)
                    .margin({ left: 8 })

                    Column() {
                      Text(record.timestamp)
                        .fontSize(10)
                        .fontColor('#999999')
                    }
                    .width(80)
                  }
                  .width('100%')
                  .padding({ left: 10, right: 10, top: 6, bottom: 6 })
                  .backgroundColor(index % 2 === 0 ? '#FFFFFF' : '#FAFAFA')
                  .borderRadius(6)
                }
              })
            }
          }
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FFFFFF')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })

        // ========== 说明区域 ==========
        Column() {
          Text('事件说明')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Column() {
            this.explainItem('onChange', '进度值变化事件', '当ArcSlider的进度值发生变化时触发')
            this.explainItem('progress', '当前进度值', '返回当前ArcSlider的进度值，数值在[min, max]范围内')
            this.explainItem('增量检测', '变化量计算', '通过比较当前值和上次值计算变化量')
            this.explainItem('方向检测', '变化方向', '根据变化量判断是增加、减少或不变')
            this.explainItem('统计功能', '事件统计', '记录总变化次数、增加减少次数、平均变化量等')
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
  statCard(label: string, count: number, color: string) {
    Column() {
      Text(label)
        .fontSize(11)
        .fontColor('#666666')
        .margin({ bottom: 4 })
      Text(count.toString())
        .fontSize(20)
        .fontColor(color)
        .fontWeight(FontWeight.Bold)
    }
    .width(60)
    .padding(10)
    .backgroundColor('#FFFFFF')
    .borderRadius(8)
    .shadow({
      radius: 2,
      color: '#1A000000',
      offsetX: 0,
      offsetY: 1
    })
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
