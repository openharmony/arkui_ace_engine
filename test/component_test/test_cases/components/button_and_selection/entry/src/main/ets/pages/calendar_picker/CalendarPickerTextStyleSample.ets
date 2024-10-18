/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

// 测试代码路径
import calendarPickerTextStyleTest from '../MyTest/CalendarPickerTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct CalendarPickerTextStyleSample {
  private selectedDate: Date = new Date()
  @State pickerTextColor: ResourceColor = 'rgb(142, 255, 101)'
  @State pickerTextStrok: number | string = 50
  @State pickerTextStyle: FontStyle = FontStyle.Normal

  aboutToAppear(): void {
    loadComponentTestEntry(calendarPickerTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          color: Color.Black
        }).id('calendarPickerTextStyle1')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          color: 0xa52a2a
        }).id('calendarPickerTextStyle2')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          color: this.pickerTextColor
        }).id('calendarPickerTextStyle3')
      }

      Column() {
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).id('calendarPickerTextStyle4')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).id('calendarPickerTextStyle5')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).id('calendarPickerTextStyle6')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).id('calendarPickerTextStyle7')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Bold,
            size: $r('app.string.size')
          }
        }).id('calendarPickerTextStyle8')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: FontWeight.Bolder,
            size: '10px',
            family: 'Arial'
          }
        }).id('calendarPickerTextStyle9')
        CalendarPicker({ hintRadius: 10, selected: this.selectedDate }).textStyle({
          font: {
            weight: this.pickerTextStrok,
            size: this.pickerTextStrok,
            family: 'TESTFONT',
            style: this.pickerTextStyle
          }
        }).id('calendarPickerTextStyle10')
        Button('CalendarPickerTextStyle1').onClick(() => {
          this.pickerTextColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('CalendarPickerTextStyle2').onClick(() => {
          this.pickerTextStrok = '100';
          this.pickerTextStyle = FontStyle.Italic
        })
      }
    }
  }
}