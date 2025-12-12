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
  private selectedDate: Date = new Date('2024-08-05');

  build() {
    Column() {
      Column() {
        CalendarPicker({ hintRadius: 6, selected: this.selectedDate })
          .edgeAlign(CalendarAlign.END)
          .margin(10)
          .onChange((value) => {
            console.info(`CalendarPicker onChange: ${value.toString()}`);
          })
          .responseRegion( { x: 0, y: 0, width: '100%', height: '100%'})

          .markToday(true)
          .align(Alignment.TopStart)
      }

      Text('日历日期选择器').fontSize(30)
    }.width('100%')
  }
}