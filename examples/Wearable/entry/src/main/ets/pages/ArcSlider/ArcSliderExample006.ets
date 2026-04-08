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
 * ArcSlider事件测试用例 - 专门测试onTouch事件
 * 包括：
 * - TouchType事件类型测试（Down/Up/Move/Cancel）
 * - touches和changedTouches的区别展示
 * - 事件冒泡相关测试
 * - 结合位置、样式、数值的综合配置
 * - 事件统计和详细日志
 */
import {
  ArcSlider,
  ArcSliderPosition,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderLayoutOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

// 事件统计
interface EventStats {
  down: number;
  up: number;
  move: number;
  cancel: number;
  total: number;
}

// 触摸事件记录
interface TouchRecord {
  id: number;
  type: string;
  touchesCount: number;
  changedTouchesCount: number;
  timestamp: string;
}

// 位置配置
interface PositionConfig {
  name: string;
  position: ArcSliderPosition;
  reverse: boolean;
}

@Entry
@ComponentV2
struct ArcSliderExample006 {
  // ========== 数值配置 ==========
  @Local progress: number = 50;
  @Local minValue: number = 0;
  @Local maxValue: number = 100;

  // ========== 位置配置 ==========
  @Local currentPosition: ArcSliderPosition = ArcSliderPosition.RIGHT;
  @Local reverse: boolean = true;

  private positionConfigs: PositionConfig[] = [
    { name: '右侧', position: ArcSliderPosition.RIGHT, reverse: true },
    { name: '左侧', position: ArcSliderPosition.LEFT, reverse: true }
  ];

  // ========== 样式配置 ==========
  @Local trackThickness: number = 8;
  @Local activeTrackThickness: number = 24;
  @Local trackBlur: number = 20;
  @Local trackColor: string = '#33FFFFFF';
  @Local selectedColor: string = '#FF5EA1FF';

  // ========== 事件统计 ==========
  @Local eventStats: EventStats = {
    down: 0,
    up: 0,
    move: 0,
    cancel: 0,
    total: 0
  };

  @Local touchRecords: TouchRecord[] = [];
  @Local maxRecords: number = 10;

  @Local lastEventType: string = '无';
  @Local lastTouchesCount: number = 0;
  @Local lastChangedTouchesCount: number = 0;

  // ========== 控制开关 ==========
  @Local enableDetailedLog: boolean = true;
  @Local enableStats: boolean = true;
  @Local enableTouchVisual: boolean = true;

  // ========== 放大状态 ==========
  @Local isEnlarged: boolean = false;

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
      onTouch: (event: TouchEvent) => {
        this.handleTouchEvent(event);
      },
      onChange: (value: number) => {
        this.progress = value;
        if (this.arcSliderOptions.valueOptions) {
          this.arcSliderOptions.valueOptions.progress = value;
        }
      },
      onEnlarge: (enlarged: boolean) => {
        this.isEnlarged = enlarged;
      }
    });
  }

  handleTouchEvent(event: TouchEvent) {
    if (!this.enableDetailedLog) {
      return;
    }

    // 更新事件统计
    this.eventStats.total++;
    switch (event.type) {
      case TouchType.Down:
        this.eventStats.down++;
        break;
      case TouchType.Up:
        this.eventStats.up++;
        break;
      case TouchType.Move:
        this.eventStats.move++;
        break;
      case TouchType.Cancel:
        this.eventStats.cancel++;
        break;
    }

    // 更新最后事件信息
    this.lastEventType = this.getTouchTypeName(event.type);
    this.lastTouchesCount = event.touches.length;
    this.lastChangedTouchesCount = event.changedTouches.length;

    // 记录触摸事件
    if (this.enableStats) {
      this.recordId++;
      const record: TouchRecord = {
        id: this.recordId,
        type: this.getTouchTypeName(event.type),
        touchesCount: event.touches.length,
        changedTouchesCount: event.changedTouches.length,
        timestamp: new Date().toLocaleTimeString()
      };
      this.touchRecords.unshift(record);
      if (this.touchRecords.length > this.maxRecords) {
        this.touchRecords = this.touchRecords.slice(0, this.maxRecords);
      }
    }
  }

  getTouchTypeName(type: number): string {
    switch (type) {
      case TouchType.Down:
        return 'Down';
      case TouchType.Up:
        return 'Up';
      case TouchType.Move:
        return 'Move';
      case TouchType.Cancel:
        return 'Cancel';
      default:
        return 'Unknown';
    }
  }

  getTouchTypeColor(type: string): string {
    switch (type) {
      case 'Down':
        return '#FF00FF00';
      case 'Up':
        return '#FFFF0000';
      case 'Move':
        return '#FF5EA1FF';
      case 'Cancel':
        return '#FFFF6600';
      default:
        return '#666666';
    }
  }

  clearRecords() {
    this.touchRecords = [];
    this.eventStats = {
      down: 0,
      up: 0,
      move: 0,
      cancel: 0,
      total: 0
    };
    this.lastEventType = '无';
    this.lastTouchesCount = 0;
    this.lastChangedTouchesCount = 0;
    this.recordId = 0;
  }

  updatePosition(pos: ArcSliderPosition, rev: boolean) {
    this.currentPosition = pos;
    this.reverse = rev;
    if (this.arcSliderOptions.layoutOptions) {
      this.arcSliderOptions.layoutOptions.position = pos;
      this.arcSliderOptions.layoutOptions.reverse = rev;
    }
  }

  updateProgress(value: number) {
    this.progress = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.progress = value;
    }
  }

  updateMin(value: number) {
    this.minValue = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.min = value;
    }
  }

  updateMax(value: number) {
    this.maxValue = value;
    if (this.arcSliderOptions.valueOptions) {
      this.arcSliderOptions.valueOptions.max = value;
    }
  }

  build() {
    Scroll() {
      Column() {
        // 标题
        Text('ArcSlider onTouch 事件测试')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15, bottom: 10 })

        Text('测试触摸事件类型、touches/changedTouches、事件统计')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 20 })

        // ========== 事件统计面板 ==========
        Column() {
          Row() {
            Text('事件统计')
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
            this.statCard('Down', this.eventStats.down, '#FF00FF00')
            Blank().width(10)
            this.statCard('Up', this.eventStats.up, '#FFFF0000')
            Blank().width(10)
            this.statCard('Move', this.eventStats.move, '#FF5EA1FF')
            Blank().width(10)
            this.statCard('Cancel', this.eventStats.cancel, '#FFFF6600')
          }
          .width('100%')

          // 总计
          Row() {
            Text('总事件数: ')
              .fontSize(13)
            Text(this.eventStats.total.toString())
              .fontSize(18)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)

            Blank()

            Text('状态: ')
              .fontSize(13)
            Text(this.isEnlarged ? '放大' : '正常')
              .fontSize(13)
              .fontColor(this.isEnlarged ? '#FF5EA1FF' : '#666666')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
          .margin({ top: 12 })

          // 最后事件信息
          Column() {
            Text('最后一次触摸事件')
              .fontSize(12)
              .fontColor('#666666')
              .margin({ bottom: 8 })

            Row() {
              Text('事件类型: ')
                .fontSize(13)
              Text(this.lastEventType)
                .fontSize(16)
                .fontColor(this.getTouchTypeColor(this.lastEventType))
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')
            .margin({ bottom: 6 })

            Row() {
              Text('touches数量: ')
                .fontSize(13)
              Text(this.lastTouchesCount.toString())
                .fontSize(14)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)

              Blank()

              Text('changedTouches数量: ')
                .fontSize(13)
              Text(this.lastChangedTouchesCount.toString())
                .fontSize(14)
                .fontColor('#FF5EA1FF')
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')
          }
          .width('100%')
          .padding(10)
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
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

          // 事件记录开关
          Row() {
            Text('启用事件记录')
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

            // 触摸状态指示器
            if (this.enableTouchVisual && this.lastEventType !== '无' && this.lastEventType !== 'Up') {
              Circle({ width: 200, height: 200 })
                .fill(this.getTouchTypeColor(this.lastEventType))
                .opacity(0.3)
            }
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

        // ========== 位置配置 ==========
        Column() {
          Text('位置配置')
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          Flex({ wrap: FlexWrap.Wrap }) {
            ForEach(this.positionConfigs, (config: PositionConfig, index: number) => {
              Text(config.name)
                .fontSize(13)
                .padding({ left: 16, right: 16, top: 8, bottom: 8 })
                .margin(8)
                .backgroundColor(
                  this.currentPosition === config.position && this.reverse === config.reverse ?
                  '#FF5EA1FF' : '#E0E0E0'
                )
                .fontColor(
                  this.currentPosition === config.position && this.reverse === config.reverse ?
                  '#FFFFFF' : '#333333'
                )
                .borderRadius(20)
                .onClick(() => {
                  this.updatePosition(config.position, config.reverse);
                })
            })
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5FF')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // ========== 事件记录 ==========
        Column() {
          Text('触摸事件记录 (最新10条)')
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 12 })

          if (this.touchRecords.length === 0) {
            Column() {
              Text('暂无触摸事件记录')
                .fontSize(13)
                .fontColor('#999999')
                .margin({ top: 15, bottom: 8 })

              Text('请在ArcSlider上进行触摸操作')
                .fontSize(12)
                .fontColor('#BBBBBB')
                .margin({ bottom: 8 })

              Text('提示：')
                .fontSize(12)
                .fontColor('#666666')
                .margin({ bottom: 4 })

              Text('• Down: 手指按下')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })

              Text('• Up: 手指抬起')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })

              Text('• Move: 手指移动')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ left: 15, bottom: 4 })

              Text('• Cancel: 触摸事件取消')
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
              ForEach(this.touchRecords, (record: TouchRecord, index: number) => {
                ListItem() {
                  Row() {
                    Column() {
                      Text(`#${record.id}`)
                        .fontSize(11)
                        .fontColor('#999999')
                      Text(record.type)
                        .fontSize(14)
                        .fontColor(this.getTouchTypeColor(record.type))
                        .fontWeight(FontWeight.Bold)
                    }
                    .width(60)

                    Column() {
                      Row() {
                        Text('touches: ')
                          .fontSize(11)
                        Text(record.touchesCount.toString())
                          .fontSize(12)
                          .fontColor('#FF5EA1FF')
                      }
                      .width('100%')
                      .margin({ bottom: 4 })

                      Row() {
                        Text('changed: ')
                          .fontSize(11)
                        Text(record.changedTouchesCount.toString())
                          .fontSize(12)
                          .fontColor('#FF5EA1FF')
                      }
                      .width('100%')
                    }
                    .layoutWeight(1)
                    .margin({ left: 8 })

                    Text(record.timestamp)
                      .fontSize(10)
                      .fontColor('#999999')
                      .width(80)
                      .textAlign(TextAlign.End)
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
            this.explainItem('TouchType', '触摸事件的类型', '包括 Down/Up/Move/Cancel 四种类型')
            this.explainItem('touches', '全部屏幕触点信息', '多指触摸时的所有触点数据，按屏幕刷新率上报')
            this.explainItem('changedTouches', '产生事件的手指信息', '发生变化的触点数据，用于定位触发事件的手指')
            this.explainItem('stopPropagation', '阻塞事件冒泡', '阻止事件继续向父组件传递')
            this.explainItem('preventDefault', '阻止默认事件', '仅支持部分组件使用，如 Hyperlink')
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
