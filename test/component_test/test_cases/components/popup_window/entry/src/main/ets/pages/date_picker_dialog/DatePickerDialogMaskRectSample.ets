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
import datePickerDialogMaskRectTest from '../MyTest/DatePickerDialogMaskRectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogMaskRectSample {
  @State maskRectNum: number | Resource = 50
  @State maskRectWid: number | Resource = 450
  @State maskRectHei: number | Resource = 100

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogMaskRectTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogMaskRect1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          maskRect: {
            x: '510px',
            y: '510px',
            width: '600px',
            height: '600px'
          }
        })
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          maskRect: {
            x: this.maskRectNum,
            y: this.maskRectNum,
            width: this.maskRectWid,
            height: this.maskRectHei
          }
        })
      })

      Button("DatePickerDialogMaskRect2").onClick(() => {
        this.maskRectNum = $r('app.string.mask_rect');
        this.maskRectWid = $r('app.string.mask_rect');
        this.maskRectHei = $r('app.string.mask_rect');
      })
    }.width('100%')
  }
}