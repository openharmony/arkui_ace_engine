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

import { JSON } from '@kit.ArkTS';
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct TimePickerExample {
  @State isMilitaryTime: boolean = false
  @State format: TimePickerFormat = TimePickerFormat.HOUR_MINUTE
  @State selectedTimeList: (Date)[] = [
    new Date('2024-12-12 6:12:34'),
    new Date('2024-12-12 5:12:34')
  ];
  @State selected: Date = new Date('2024-12-12 6:12:34');
  @State startEndTimeList: (Date | undefined | null)[][] = [
    [new Date('2024-12-12 00:00:00'), new Date('2024-12-12 23:00:00')],
    [new Date('2024-12-12 00:00:00'), new Date('2024-12-12 6:12:34')],
    [new Date('2024-12-12 00:00:00'), new Date('2024-12-12 5:12:34')],
    [new Date('2024-12-12 5:12:36'), new Date('2024-12-12 5:12:35')],
    [undefined, undefined],
    [new Date('2024-12-12 00:00:00'), undefined],
    [new Date('2024-12-12 00:00:00'), null],
    [new Date('2024-12-12 5:12:34'), new Date('2024-12-12 5:12:34')],
    [new Date('2024-12-12 6:12:34'), new Date('2024-12-12 6:12:34')],
    [new Date('2024-12-12 7:12:34'), new Date('2024-12-12 7:12:34')],
    [new Date('2024-12-12 6:12:34'), new Date('2024-12-12 23:00:00')],
    [new Date('2024-12-12 7:12:34'), new Date('2024-12-12 23:00:00')],
    [undefined, new Date('2024-12-12 23:00:00')],
    [null, new Date('2024-12-12 23:00:00')],
    [new Date('2024-12-12 23:00:00'), new Date('2024-12-12 00:00:00')]
  ];
  @State selectedTimeIndex: number = 0;
  @State startEndTimeIndex: number = 0;

  build() {
    Column() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Column() {
          Text('正常TimePicker')
          TimePicker({
            selected: this.selected,
            format: this.format,
            start: this.startEndTimeList[this.startEndTimeIndex][0],
            end: this.startEndTimeList[this.startEndTimeIndex][1],
          })
            .onEnterSelectedArea((TimePickerResult) => {
              console.info('Picker item onDidEnterSelectedArea' + JSON.stringify(TimePickerResult))
            })
            .dateTimeOptions({ hour: 'numeric' })
            .loop(true)
            .useMilitaryTime(this.isMilitaryTime)
            .onChange((value: TimePickerResult) => {
              this.selected = new Date('2024-12-12' + value.hour + ':' + value.minute + ':' + value.second)
            })
            .width(180)
        }
      }.width('100%')

      Button('TimePickerDialog')
        .onClick(() => {
          TimePickerDialog.show({
            alignment: DialogAlignment.Top,
            useMilitaryTime: this.isMilitaryTime,
            selected: this.selected,
            format: this.format,
            start: this.startEndTimeList[this.startEndTimeIndex][0],
            end: this.startEndTimeList[this.startEndTimeIndex][1],
          })
        })
        .margin({ top: 50 })

      Text(`selected: ${this.formatDate(this.selectedTimeList[this.selectedTimeIndex])}`);
      Text(`start: ${this.formatDate(this.startEndTimeList[this.startEndTimeIndex][0])}`);
      Text(`end: ${this.formatDate(this.startEndTimeList[this.startEndTimeIndex][1])}`);

      Flex({ wrap: FlexWrap.Wrap, space: { main: LengthMetrics.px(20), cross: LengthMetrics.px(10) } }) {
        Button(`selected${this.selectedTimeIndex}/${this.selectedTimeList.length - 1}`)
          .onClick(() => {
            this.selectedTimeIndex++;
            if (this.selectedTimeIndex > this.selectedTimeList.length - 1) {
              this.selectedTimeIndex = 0;
            }
            this.selected = this.selectedTimeList[this.selectedTimeIndex]
          })
        Button(`chang time${this.startEndTimeIndex}/${this.startEndTimeList.length - 1}`)
          .onClick(() => {
            this.startEndTimeIndex++;
            if (this.startEndTimeIndex > this.startEndTimeList.length - 1) {
              this.startEndTimeIndex = 0;
            }
          })
        Button(`${this.isMilitaryTime ? '24小时制' : '12小时制'}`)
          .onClick(() => {
            this.isMilitaryTime = !this.isMilitaryTime
          })
        Button(`TimePicker的格式:${this.format == TimePickerFormat.HOUR_MINUTE ? '时分' : '时分秒'}`)
          .onClick(() => {
            if (this.format == TimePickerFormat.HOUR_MINUTE) {
              this.format = TimePickerFormat.HOUR_MINUTE_SECOND;
            } else {
              this.format = TimePickerFormat.HOUR_MINUTE;
            }
          })
      }
    }.width('100%')
  }

  formatDate(date?: Date) {
    if (!!date) {
      const year = date.getFullYear();
      const month = String(date.getMonth() + 1).padStart(2, '0');
      const day = String(date.getDate()).padStart(2, '0');
      const hours = String(date.getHours()).padStart(2, '0');
      const minutes = String(date.getMinutes()).padStart(2, '0');
      const seconds = String(date.getSeconds()).padStart(2, '0');

      return `${hours}:${minutes}:${seconds}`;
      // return `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;
    } else {
      return JSON.stringify(date);
    }
  }
}
