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
import datePickerSelectedTextStyleTest from '../MyTest/DatePickerSelectedTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct DatePickerSelectedTextStyleSample {
  @State selectedTextColor: ResourceColor = 'rgb(142, 255, 101)'
  @State selectedTextStrok: number | string = 50
  @State selectedTextSty: FontStyle = FontStyle.Normal

  aboutToAppear() {
    loadComponentTestEntry(datePickerSelectedTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        DatePicker().selectedTextStyle({
          color: Color.Green
        }).height(200).width(190).id('datePickerSelectedTextStyle1')
        DatePicker().selectedTextStyle({
          color: 0xa52a2a
        }).height(200).width(190).id('datePickerSelectedTextStyle2')
        DatePicker().selectedTextStyle({
          color: this.selectedTextColor
        }).height(200).width(190).id('datePickerSelectedTextStyle3')
      }

      Column() {
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle4')
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle5')
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle6')
      }

      Column() {
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle7')
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Bold
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle8')
        DatePicker().selectedTextStyle({
          font: {
            weight: FontWeight.Bolder,
            size: $r('app.string.size'),
            family: 'Arial'
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle9')
      }

      Column() {
        DatePicker().selectedTextStyle({
          font: {
            weight: this.selectedTextStrok,
            size: this.selectedTextStrok,
            family: 'TESTFONT',
            style: this.selectedTextSty
          }
        }).height(200).width(190).id('datePickerSelectedTextStyle10')
        Button('DatePickerSelectedTextStyle1').onClick(() => {
          this.selectedTextColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('DatePickerSelectedTextStyle2').onClick(() => {
          this.selectedTextStrok = '200';
          this.selectedTextSty = FontStyle.Italic;
        })
      }
    }.width('100%')
  }
}