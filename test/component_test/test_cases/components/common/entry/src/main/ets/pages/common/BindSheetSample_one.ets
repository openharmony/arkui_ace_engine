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

import bindSheetTest_one from '../MyTest/BindSheetTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindSheetSample_one {
  @Builder
  myBuilder() {
    Column() {
      Button("myBuilder")
        .margin(10)
        .fontSize(20)
    }
  }

  @State any_boolean: boolean = true
  @State my_height: Length = '100'
  @State my_SheetSize: SheetSize = SheetSize.MEDIUM
  @State any_detents: [(SheetSize | Length), (SheetSize | Length)?, (SheetSize | Length)?] =
    [SheetSize.MEDIUM, SheetSize.LARGE, SheetSize.FIT_CONTENT]

  aboutToAppear(): void {
    loadComponentTestEntry(bindSheetTest_one)
  }

  build() {
    Column() {
      Button("BindSheet_1")
        .bindSheet(this.any_boolean, this.myBuilder(), {
          height: this.my_height,
          detents: this.any_detents,
          shouldDismiss: ((sheetDismiss: SheetDismiss) => {
            console.log("bind sheet shouldDismiss")
            sheetDismiss.dismiss()
          }),
          showClose: this.any_boolean,
          dragBar: this.any_boolean
        }).id('buttonBindSheet1')

      Button("BindSheet_2")
        .bindSheet(this.any_boolean, this.myBuilder(), { height: this.my_SheetSize })
        .id('buttonBindSheet2')

      Row() {
        Button("ButtonBindSheet1").onClick(() => {
          this.any_boolean = !this.any_boolean
          this.my_height = 100
          this.my_SheetSize = SheetSize.LARGE
          this.any_detents = [100, '100', $r("app.string.common_value_two")]
        })
        Button("ButtonBindSheet2").onClick(() => {
          this.my_height = $r("app.string.common_value_two")
          this.my_SheetSize = SheetSize.FIT_CONTENT
        })
      }
    }
  }
}