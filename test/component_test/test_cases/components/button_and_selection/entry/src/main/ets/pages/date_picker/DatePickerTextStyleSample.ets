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
import datePickerTextStyleTest from '../MyTest/DatePickerTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font'

@Entry
@Component
struct DatePickerTextStyleSample {
  @State textStyleColor: ResourceColor = 'rgb(142, 255, 101)'
  @State textStyleStrok: number | string = 50
  @State textStyleSty: FontStyle = FontStyle.Normal

  aboutToAppear() {
    loadComponentTestEntry(datePickerTextStyleTest)

    font.registerFont({
      familyName: 'TESTFONT',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Flex() {
      Column() {
        DatePicker().textStyle({
          color: Color.Green
        }).height(200).width(190).id('datePickerTextStyle1')
        DatePicker().textStyle({
          color: 0xa52a2a
        }).height(200).width(190).id('datePickerTextStyle2')
        DatePicker().textStyle({
          color: this.textStyleColor
        }).height(200).width(190).id('datePickerTextStyle3')
      }

      Column() {
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Lighter
          }
        }).height(200).width(190).id('datePickerTextStyle4')
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Normal
          }
        }).height(200).width(190).id('datePickerTextStyle5')
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Regular
          }
        }).height(200).width(190).id('datePickerTextStyle6')
      }

      Column() {
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Medium
          }
        }).height(200).width(190).id('datePickerTextStyle7')
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Bold
          }
        }).height(200).width(190).id('datePickerTextStyle8')
        DatePicker().textStyle({
          font: {
            weight: FontWeight.Bolder,
            size: $r('app.string.size'),
            family: 'Arial'
          }
        }).height(200).width(190).id('datePickerTextStyle9')
      }

      Column() {
        DatePicker().textStyle({
          font: {
            weight: this.textStyleStrok,
            size: this.textStyleStrok,
            family: 'TESTFONT',
            style: this.textStyleSty
          }
        }).height(200).width(190).id('datePickerTextStyle10')
        Button('DatePickerTextStyle1').onClick(() => {
          this.textStyleColor = $r('sys.color.ohos_fa_palette1')
        })
        Button('DatePickerTextStyle2').onClick(() => {
          this.textStyleStrok = '200';
          this.textStyleSty = FontStyle.Italic;
        })
      }
    }.width('100%')
  }
}