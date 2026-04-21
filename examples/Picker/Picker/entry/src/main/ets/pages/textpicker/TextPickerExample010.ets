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

@Entry
@Component
struct TextPickerExample010 {
  // 选中的日期数据（存储索引）
  @State selectedYearIndex: number = 4; // 2024-2020 = 4
  @State selectedMonthIndex: number = 0; // 0-11
  @State selectedDayIndex: number = 0; // 0-30
  @State selectedHourIndex: number = 0; // 0-23
  @State selectedMinuteIndex: number = 0; // 0-59

  // 可选择的范围
  private startYear: number = 2020;
  private endYear: number = 2030;

  // 日志类型
  @State selectedLogTypeIndex: number = 0;

  // 日志级别
  @State selectedLogLevelIndex: number = 0;

  // 年份数组
  private years: string[] = ['2020年', '2021年', '2022年', '2023年', '2024年', '2025年',
    '2026年', '2027年', '2028年', '2029年', '2030年'];

  // 月份数组
  private months: string[] = ['1月', '2月', '3月', '4月', '5月', '6月',
    '7月', '8月', '9月', '10月', '11月', '12月'];

  // 日期数组（31天，最大值）
  private days: string[] = ['1日', '2日', '3日', '4日', '5日', '6日', '7日', '8日', '9日', '10日',
    '11日', '12日', '13日', '14日', '15日', '16日', '17日', '18日', '19日', '20日',
    '21日', '22日', '23日', '24日', '25日', '26日', '27日', '28日', '29日', '30日', '31日'];

  // 小时数组
  private hours: string[] = ['00时', '01时', '02时', '03时', '04时', '05时', '06时', '07时', '08时', '09时',
    '10时', '11时', '12时', '13时', '14时', '15时', '16时', '17时', '18时', '19时',
    '20时', '21时', '22时', '23时'];

  // 分钟数组
  private minutes: string[] = ['00分', '01分', '02分', '03分', '04分', '05分', '06分', '07分', '08分', '09分',
    '10分', '11分', '12分', '13分', '14分', '15分', '16分', '17分', '18分', '19分',
    '20分', '21分', '22分', '23分', '24分', '25分', '26分', '27分', '28分', '29分',
    '30分', '31分', '32分', '33分', '34分', '35分', '36分', '37分', '38分', '39分',
    '40分', '41分', '42分', '43分', '44分', '45分', '46分', '47分', '48分', '49分',
    '50分', '51分', '52分', '53分', '54分', '55分', '56分', '57分', '58分', '59分'];

  // 日志类型数组
  private logTypes: string[] = ['全部日志', '系统日志', '应用日志', '安全日志', '网络日志'];

  // 日志级别数组
  private logLevels: string[] = ['全部级别', 'DEBUG', 'INFO', 'WARN', 'ERROR', 'FATAL'];

  // 获取选中的日期字符串
  getSelectedDateText(): string {
    const year: number = this.startYear + this.selectedYearIndex;
    const month: number = this.selectedMonthIndex + 1;
    const monthStr: string = month < 10 ? '0' + month.toString() : month.toString();
    const day: number = this.selectedDayIndex + 1;
    const dayStr: string = day < 10 ? '0' + day.toString() : day.toString();
    const hourStr: string = this.hours[this.selectedHourIndex].substring(0, 2);
    const minuteStr: string = this.minutes[this.selectedMinuteIndex].substring(0, 2);
    return year + '-' + monthStr + '-' + dayStr + ' ' + hourStr + ':' + minuteStr;
  }

  // 查询日志
  onQueryLogs() {
    const dateText: string = this.getSelectedDateText();
    const typeText: string = this.logTypes[this.selectedLogTypeIndex];
    const levelText: string = this.logLevels[this.selectedLogLevelIndex];
    console.info('查询日志 - 日期: ' + dateText + ', 类型: ' + typeText + ', 级别: ' + levelText);
  }

  build() {
    Column() {
      // 标题栏
      Row() {
        Text('日志查询器')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .fontColor('#333333')
      }
      .width('100%')
      .height(50)
      .justifyContent(FlexAlign.Center)
      .backgroundColor('#F5F5F5')

      // 选择器区域
      Column() {
        // 日期选择标题
        Text('选择日期')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor('#666666')
          .margin({ top: 20, bottom: 15 })

        // 日期选择器
        Row() {
          // 年份选择
          Column() {
            Text('年')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ bottom: 8 })

            TextPicker({ range: this.years, selected: this.selectedYearIndex })
              .onChange((value: string | string[], index: number | number[]) => {
                this.selectedYearIndex = index as number;
              })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 月份选择
          Column() {
            Text('月')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ bottom: 8 })

            TextPicker({ range: this.months, selected: this.selectedMonthIndex })
              .onChange((value: string | string[], index: number | number[]) => {
                this.selectedMonthIndex = index as number;
              })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 日期选择
          Column() {
            Text('日')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ bottom: 8 })

            TextPicker({ range: this.days, selected: this.selectedDayIndex })
              .onChange((value: string | string[], index: number | number[]) => {
                this.selectedDayIndex = index as number;
              })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 小时选择
          Column() {
            Text('时')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ bottom: 8 })

            TextPicker({ range: this.hours, selected: this.selectedHourIndex })
              .onChange((value: string | string[], index: number | number[]) => {
                this.selectedHourIndex = index as number;
              })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)

          // 分钟选择
          Column() {
            Text('分')
              .fontSize(14)
              .fontColor('#999999')
              .margin({ bottom: 8 })

            TextPicker({ range: this.minutes, selected: this.selectedMinuteIndex })
              .onChange((value: string | string[], index: number | number[]) => {
                this.selectedMinuteIndex = index as number;
              })
          }
          .layoutWeight(1)
          .alignItems(HorizontalAlign.Center)
        }
        .width('100%')
        .height(180)
        .justifyContent(FlexAlign.SpaceEvenly)

        // 日志类型选择
        Text('日志类型')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor('#666666')
          .margin({ top: 30, bottom: 15 })

        TextPicker({ range: this.logTypes, selected: this.selectedLogTypeIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            this.selectedLogTypeIndex = index as number;
          })

        // 日志级别选择
        Text('日志级别')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor('#666666')
          .margin({ top: 30, bottom: 15 })

        TextPicker({ range: this.logLevels, selected: this.selectedLogLevelIndex })
          .onChange((value: string | string[], index: number | number[]) => {
            this.selectedLogLevelIndex = index as number;
          })
      }
      .width('100%')
      .padding({ left: 20, right: 20 })

      // 分割线
      Divider()
        .color('#E5E5E5')
        .strokeWidth(1)
        .margin({ top: 20, bottom: 20 })

      // 当前选择显示
      Column() {
        Text('当前选择的查询条件')
          .fontSize(14)
          .fontColor('#999999')
          .margin({ bottom: 10 })

        Row() {
          Text('日期时间: ')
            .fontSize(14)
            .fontColor('#666666')

          Text(this.getSelectedDateText())
            .fontSize(16)
            .fontColor('#007DFF')
            .fontWeight(FontWeight.Medium)
        }

        Row() {
          Text('日志类型: ')
            .fontSize(14)
            .fontColor('#666666')

          Text(this.logTypes[this.selectedLogTypeIndex])
            .fontSize(16)
            .fontColor('#007DFF')
            .fontWeight(FontWeight.Medium)
        }
        .margin({ top: 8 })

        Row() {
          Text('日志级别: ')
            .fontSize(14)
            .fontColor('#666666')

          Text(this.logLevels[this.selectedLogLevelIndex])
            .fontSize(16)
            .fontColor('#007DFF')
            .fontWeight(FontWeight.Medium)
        }
        .margin({ top: 8 })
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
      .alignItems(HorizontalAlign.Start)

      // 查询按钮区域
      Row() {
        Button('重置')
          .type(ButtonType.Normal)
          .fontSize(16)
          .fontColor('#007DFF')
          .backgroundColor('#FFFFFF')
          .border({ width: 1, color: '#007DFF' })
          .borderRadius(8)
          .height(44)
          .padding({ left: 30, right: 30 })
          .onClick(() => {
            this.selectedYearIndex = 4;
            this.selectedMonthIndex = 0;
            this.selectedDayIndex = 0;
            this.selectedHourIndex = 0;
            this.selectedMinuteIndex = 0;
            this.selectedLogTypeIndex = 0;
            this.selectedLogLevelIndex = 0;
          })
          .margin({ right: 20 })

        Button('查询日志')
          .type(ButtonType.Capsule)
          .fontSize(16)
          .fontColor('#FFFFFF')
          .backgroundColor('#007DFF')
          .height(44)
          .padding({ left: 40, right: 40 })
          .onClick(() => {
            this.onQueryLogs();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
      .margin({ top: 30, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }
}

