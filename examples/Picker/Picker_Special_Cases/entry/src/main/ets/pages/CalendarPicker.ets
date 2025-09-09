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

@Entry
@Component
struct CalendarPickerExample {
  @State selectedCalendar: Date = new Date('1989-08-04T23:30:01')
  private startDate: Date = new Date('1900-01-05')
  private endDate: Date = new Date('2025-12-25')

  aboutToAppear(): void {
    console.log('aboutToAppear() : ' + this.selectedCalendar)
  }

  build() {
    Column() {
      Text('CalendarPicker').fontSize(20).fontColor(Color.Black).width(200)

      CalendarPicker({
        hintRadius: 10,
        selected: this.selectedCalendar,
        start: this.startDate,
        end: this.endDate
      })
        .width(300)
        .height(200)
        .textStyle({ color: '#ff1824ff', font: { size: 20, weight: FontWeight.Normal } })
        .onChange((value) => {
          this.selectedCalendar = value
          console.log('CalendarPicker onChange(): ' + JSON.stringify(value) + '\n' + this.selectedCalendar);
        })
        .visibility(Visibility.Visible)
    }
    .backgroundColor('#90EE90')
    .width('100%')
    .height('100%')
  }
}