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
import timePickerDisappearTextStyleTest from '../MyTest/TimePickerDisappearTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct TimePickerDisappearTextStyleSample {
  @State disappearTextColor: ResourceColor = 'rgb(142, 255, 101)'
  @State disappearTextStrok: number | string = 50
  @State disappearTextSty: FontStyle = FontStyle.Normal
  private selectedTime: Date = new Date('2022-07-22T08:00:00')

  aboutToAppear() {
    loadComponentTestEntry(timePickerDisappearTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          color: Color.Green
        }).height(200).width(190).id('timePickerDisappearTextStyle1')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          color: 0xa52a2a
        }).height(200).width(190).id('timePickerDisappearTextStyle2')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          color: this.disappearTextColor
        }).height(200).width(190).id('timePickerDisappearTextStyle3')
      }

      Column() {
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle4')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle5')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle6')
      }

      Column() {
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle7')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Bold
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle8')
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: FontWeight.Bolder,
            size: $r('app.string.size'),
            family: 'Arial'
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle9')
      }

      Column() {
        TimePicker({ selected: this.selectedTime }).disappearTextStyle({
          font: {
            weight: this.disappearTextStrok,
            size: this.disappearTextStrok,
            family: 'TESTFONT',
            style: this.disappearTextSty
          }
        }).height(200).width(190).id('timePickerDisappearTextStyle10')
        Button('TimePickerDisappearTextStyle1').onClick(() => {
          this.disappearTextColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('TimePickerDisappearTextStyle2').onClick(() => {
          this.disappearTextStrok = '200';
          this.disappearTextSty = FontStyle.Italic;
        })
      }
    }.width('100%')
  }
}