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
import datePickerDialogDisappearTextStyleTest from '../MyTest/DatePickerDialogDisappearTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogDisappearTextStyleSample {
  @State disappearTextStyleColor: ResourceColor = 'rgb(142, 255, 101)'
  @State disappearTextStyleText: number | string = 10

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogDisappearTextStyleTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogDisappearTextStyle1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: { font: { weight: FontWeight.Lighter } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: { font: { weight: FontWeight.Normal } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: { font: { weight: FontWeight.Regular } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: { font: { weight: FontWeight.Medium } }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: { color: Color.Blue, font: { weight: FontWeight.Bold } },
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: {
            color: 0xa52a2a, font: {
              size: $r('app.string.text_style_size'),
              weight: FontWeight.Bolder
            }
          },
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          disappearTextStyle: {
            color: this.disappearTextStyleColor,
            font: { size: this.disappearTextStyleText, weight: this.disappearTextStyleText }
          }
        })
      })

      Button("DatePickerDialogDisappearTextStyle2").onClick(() => {
        this.disappearTextStyleColor = $r('sys.color.ohos_fa_palette1');
        this.disappearTextStyleText = '30';
      })
    }.width('100%')
  }
}