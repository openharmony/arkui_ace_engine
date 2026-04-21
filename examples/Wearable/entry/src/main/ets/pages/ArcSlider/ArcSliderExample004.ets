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
 * ArcSlider数值测试用例 - 测试ValueOptions的各种行为
 * 包括正常数值拖动、异常值边界处理、范围限制等
 * 验证文档描述的行为：
 * 1. 当min >= max时，min取默认值0，max取默认值100
 * 2. progress不在[min, max]范围时，取min或max（靠近min取min，靠近max取max）
 */
import {
  ArcSlider,
  ArcSliderOptions,
  ArcSliderValueOptions,
  ArcSliderStyleOptions
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcSliderExample004 {
  // 正常数值测试
  @Local normalProgress: number = 50;
  @Local normalMin: number = 0;
  @Local normalMax: number = 100;

  // 边界测试
  @Local edgeProgress: number = 50;
  @Local edgeMin: number = 0;
  @Local edgeMax: number = 100;

  // 异常测试1: min >= max
  @Local abnormalProgress1: number = 50;
  @Local abnormalMin1: number = 80;
  @Local abnormalMax1: number = 70;

  // 异常测试2: progress超出范围
  @Local abnormalProgress2: number = 150;
  @Local abnormalMin2: number = 0;
  @Local abnormalMax2: number = 100;

  // 异常测试3: progress超出范围（靠近max）
  @Local abnormalProgress3: number = 120;
  @Local abnormalMin3: number = 10;
  @Local abnormalMax3: number = 100;

  // 事件日志
  @Local eventLogs: string[] = [];
  @Local maxLogs: number = 6;

  // ArcSlider配置对象
  @Local normalOptions: ArcSliderOptions = new ArcSliderOptions({});
  @Local edgeOptions: ArcSliderOptions = new ArcSliderOptions({});
  @Local abnormalOptions1: ArcSliderOptions = new ArcSliderOptions({});
  @Local abnormalOptions2: ArcSliderOptions = new ArcSliderOptions({});
  @Local abnormalOptions3: ArcSliderOptions = new ArcSliderOptions({});

  aboutToAppear() {
    this.initializeOptions();
  }

  initializeOptions() {
    // 正常数值配置
    this.normalOptions = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.normalProgress,
        min: this.normalMin,
        max: this.normalMax
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 8,
        activeTrackThickness: 24,
        trackColor: '#33FFFFFF',
        selectedColor: '#FF5EA1FF',
        trackBlur: 20
      }),
      onChange: (progress: number) => {
        this.normalProgress = progress;
        if (this.normalOptions.valueOptions) {
          this.normalOptions.valueOptions.progress = progress;
        }
        this.addEventLog('正常: onChange - ' + progress.toFixed(1));
      },
      onEnlarge: (isEnlarged: boolean) => {
        this.addEventLog('正常: onEnlarge - ' + (isEnlarged ? '放大' : '正常'));
      }
    });

    // 边界测试配置
    this.edgeOptions = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.edgeProgress,
        min: this.edgeMin,
        max: this.edgeMax
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 8,
        activeTrackThickness: 24,
        trackColor: '#33FFFFFF',
        selectedColor: '#FF00FF00',
        trackBlur: 20
      }),
      onChange: (progress: number) => {
        this.edgeProgress = progress;
        if (this.edgeOptions.valueOptions) {
          this.edgeOptions.valueOptions.progress = progress;
        }
        this.addEventLog('边界: onChange - ' + progress.toFixed(1));
      },
      onEnlarge: (isEnlarged: boolean) => {
        this.addEventLog('边界: onEnlarge - ' + (isEnlarged ? '放大' : '正常'));
      }
    });

    // 异常测试1配置: min >= max
    // 根据文档，这种情况min应取默认值0，max应取默认值100
    this.abnormalOptions1 = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.abnormalProgress1,
        min: this.abnormalMin1,
        max: this.abnormalMax1
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 6,
        activeTrackThickness: 20,
        trackColor: '#33FFFFFF',
        selectedColor: '#FFFF0000',
        trackBlur: 15
      }),
      onChange: (progress: number) => {
        this.abnormalProgress1 = progress;
        if (this.abnormalOptions1.valueOptions) {
          this.abnormalOptions1.valueOptions.progress = progress;
        }
        this.addEventLog('异常1: onChange - ' + progress.toFixed(1));
      }
    });

    // 异常测试2配置: progress超出范围
    // 初始progress=150，范围[0,100]，应被限制到max=100
    this.abnormalOptions2 = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.abnormalProgress2,
        min: this.abnormalMin2,
        max: this.abnormalMax2
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 6,
        activeTrackThickness: 20,
        trackColor: '#33FFFFFF',
        selectedColor: '#FFFFD700',
        trackBlur: 15
      }),
      onChange: (progress: number) => {
        this.abnormalProgress2 = progress;
        if (this.abnormalOptions2.valueOptions) {
          this.abnormalOptions2.valueOptions.progress = progress;
        }
        this.addEventLog('异常2: onChange - ' + progress.toFixed(1));
      }
    });

    // 异常测试3配置: progress超出范围（靠近max）
    // 初始progress=120，范围[10,100]，应被限制到max=100
    this.abnormalOptions3 = new ArcSliderOptions({
      valueOptions: new ArcSliderValueOptions({
        progress: this.abnormalProgress3,
        min: this.abnormalMin3,
        max: this.abnormalMax3
      }),
      styleOptions: new ArcSliderStyleOptions({
        trackThickness: 6,
        activeTrackThickness: 20,
        trackColor: '#33FFFFFF',
        selectedColor: '#FF9932CC',
        trackBlur: 15
      }),
      onChange: (progress: number) => {
        this.abnormalProgress3 = progress;
        if (this.abnormalOptions3.valueOptions) {
          this.abnormalOptions3.valueOptions.progress = progress;
        }
        this.addEventLog('异常3: onChange - ' + progress.toFixed(1));
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

  updateNormalMin(value: number) {
    this.normalMin = value;
    if (this.normalOptions.valueOptions) {
      this.normalOptions.valueOptions.min = value;
    }
  }

  updateNormalMax(value: number) {
    this.normalMax = value;
    if (this.normalOptions.valueOptions) {
      this.normalOptions.valueOptions.max = value;
    }
  }

  build() {
    Scroll() {
      Column() {
        Text('ArcSlider 数值测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 15, bottom: 10 })

        // 测试1: 正常数值
        this.testSection(
          '测试1 - 正常数值',
          '范围: 0-100, 当前: ' + this.normalProgress.toFixed(1),
          this.normalOptions
        )

        // 测试2: 边界数值
        this.testSection(
          '测试2 - 边界数值',
          '范围: 0-100, 当前: ' + this.edgeProgress.toFixed(1),
          this.edgeOptions
        )

        // 测试3: 异常值 min >= max
        Column() {
          Text('测试3 - 异常值 (min >= max)')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Text('说明: 根据文档，min>=max时min取默认值0，max取默认值100')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ bottom: 8 })

          Row() {
            Text('设置值: ')
              .fontSize(13)
            Text('min=' + this.abnormalMin1 + ', max=' + this.abnormalMax1)
              .fontSize(13)
              .fontColor('#FFFF0000')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ bottom: 8 })

          Text('预期行为: min→0, max→100 (使用默认值)')
            .fontSize(12)
            .fontColor('#FF6600')
            .margin({ bottom: 8 })

          Row() {
            Text('实际值: ')
              .fontSize(13)
            if (this.abnormalOptions1.valueOptions) {
              Text('min=' + this.abnormalOptions1.valueOptions.min +
                ', max=' + this.abnormalOptions1.valueOptions.max)
                .fontSize(13)
                .fontColor((this.abnormalOptions1.valueOptions.min === 0 &&
                  this.abnormalOptions1.valueOptions.max === 100) ? '#FF00FF00' : '#FFFF0000')
                .fontWeight(FontWeight.Bold)
            }
          }

          Row() {
            Text('当前progress: ')
              .fontSize(13)
            Text(this.abnormalProgress1.toFixed(1))
              .fontSize(13)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .margin({ top: 8 })

          Stack() {
            Circle({ width: 150, height: 150 })
              .strokeWidth(0.1)
              .fill(Color.White)

            ArcSlider({ options: this.abnormalOptions1 })
          }
          .width(150)
          .height(150)
          .margin({ top: 10 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FFF5F5')
        .borderRadius(8)
        .margin({ bottom: 20 })

        // 测试4: progress超出范围（正向）
        Column() {
          Text('测试4 - progress超出范围 (正向)')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('说明: 初始progress=150，超出范围[0,100]')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ bottom: 8 })

          Text('预期行为: progress应被限制到max=100（靠近max取max）')
            .fontSize(12)
            .fontColor('#FF6600')
            .margin({ bottom: 8 })

          Row() {
            Text('初始值: ')
              .fontSize(13)
            Text('progress=150, 范围[0,100]')
              .fontSize(13)
              .fontColor('#FFFF0000')
          }
          .margin({ bottom: 8 })

          Row() {
            Text('实际progress: ')
              .fontSize(13)
            Text(this.abnormalProgress2.toFixed(1))
              .fontSize(13)
              .fontColor(this.abnormalProgress2 <= 100 ? '#FF00FF00' : '#FFFF0000')
              .fontWeight(FontWeight.Bold)
          }

          Stack() {
            Circle({ width: 150, height: 150 })
              .strokeWidth(0.1)
              .fill(Color.White)

            ArcSlider({ options: this.abnormalOptions2 })
          }
          .width(150)
          .height(150)
          .margin({ top: 10 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FFF5F5')
        .borderRadius(8)
        .margin({ bottom: 20 })

        // 测试：动态调整min/max
        Column() {
          Text('测试5 - 动态调整范围')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          // min值控制
          Row() {
            Text('最小值: ')
              .fontSize(13)
            Text(this.normalMin.toString())
              .fontSize(13)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .width('90%')
          .margin({ bottom: 5 })

          Slider({
            value: this.normalMin,
            min: -50,
            max: 50,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.updateNormalMin(value);
            })

          // max值控制
          Row() {
            Text('最大值: ')
              .fontSize(13)
            Text(this.normalMax.toString())
              .fontSize(13)
              .fontColor('#FF5EA1FF')
              .fontWeight(FontWeight.Bold)
          }
          .width('90%')
          .margin({ top: 10, bottom: 5 })

          Slider({
            value: this.normalMax,
            min: 50,
            max: 200,
            step: 1,
            style: SliderStyle.OutSet
          })
            .width('90%')
            .onChange((value: number) => {
              this.updateNormalMax(value);
            })

          // 当前范围显示
          Row() {
            Text('当前范围: [')
              .fontSize(13)
            Text(this.normalMin.toString())
              .fontSize(13)
              .fontColor('#FF5EA1FF')
            Text(', ')
              .fontSize(13)
            Text(this.normalMax.toString())
              .fontSize(13)
              .fontColor('#FF5EA1FF')
            Text(']')
              .fontSize(13)
          }
          .width('90%')
          .margin({ top: 10, bottom: 10 })

          // ArcSlider展示
          Stack() {
            Circle({ width: 200, height: 200 })
              .strokeWidth(0.1)
              .fill(Color.White)

            ArcSlider({ options: this.normalOptions })
          }
          .width(200)
          .height(200)
          .margin({ top: 10 })
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F9F9F9')
        .borderRadius(8)
        .margin({ bottom: 20 })

        // 事件日志
        Column() {
          Row() {
            Text('事件日志')
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
              .margin({ right: 10 })
            Button('清除日志')
              .fontSize(11)
              .onClick(() => {
                this.clearLogs();
              })
          }
          .width('100%')
          .margin({ bottom: 10 })

          if (this.eventLogs.length === 0) {
            Text('暂无事件日志，请拖动ArcSlider')
              .fontSize(12)
              .fontColor('#999999')
              .margin({ top: 15 })
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
            .height(120)
          }
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
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
  testSection(title: string, desc: string, options: ArcSliderOptions) {
    Column() {
      Text(title)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 })

      Text(desc)
        .fontSize(12)
        .fontColor('#666666')
        .margin({ bottom: 10 })

      Stack() {
        Circle({ width: 150, height: 150 })
          .strokeWidth(0.1)
          .fill(Color.White)

        ArcSlider({ options: options })
      }
      .width(150)
      .height(150)
    }
    .width('90%')
    .padding(12)
    .backgroundColor('#F5F5F5')
    .borderRadius(8)
    .margin({ bottom: 20 })
  }
}
