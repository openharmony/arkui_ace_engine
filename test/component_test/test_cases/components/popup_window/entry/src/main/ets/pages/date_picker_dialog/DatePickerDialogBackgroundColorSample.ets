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
import datePickerDialogBackgroundColorTest from '../MyTest/DatePickerDialogBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogBackgroundColorSample {
  @State backgroundCol: ResourceColor[] =
    [Color.Orange, 0xa52a2a, 'rgb(142, 255, 101)', $r('sys.color.ohos_fa_palette1')]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogBackgroundColorTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogBackgroundColor1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          backgroundColor: this.backgroundCol[this.index]
        })
      })
      Button("DatePickerDialogBackgroundColor2").onClick(() => {
        this.index++;
        this.index %= 4;
      })
    }.width('100%')
  }
}