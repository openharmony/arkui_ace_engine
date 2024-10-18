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
import datePickerDialogTextStyleTest from '../MyTest/DatePickerDialogTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogTextStyleSample {
  @State textStyleColor: ResourceColor = 'rgb(142, 255, 101)'
  @State textStyleText: number | string = 10

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogTextStyleTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogTextStyle1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: { font: { weight: FontWeight.Lighter } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: { font: { weight: FontWeight.Normal } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: { font: { weight: FontWeight.Regular } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: { font: { weight: FontWeight.Medium } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: { color: Color.Blue, font: { weight: FontWeight.Bold } },
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: {
            color: 0xa52a2a, font: {
              size: $r('app.string.text_style_size'),
              weight: FontWeight.Bolder
            }
          },
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          textStyle: {
            color: this.textStyleColor,
            font: { size: this.textStyleText, weight: this.textStyleText }
          },
        })
      })

      Button("DatePickerDialogTextStyle2").onClick(() => {
        this.textStyleColor = $r('sys.color.ohos_fa_palette1');
        this.textStyleText = '30';
      })
    }.width('100%')
  }
}