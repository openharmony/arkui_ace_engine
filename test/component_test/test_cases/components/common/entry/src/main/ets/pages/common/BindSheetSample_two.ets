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

import bindSheetTest_two from '../MyTest/BindSheetTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindSheetSample_two {
  @State any_boolean: boolean = true
  @State any_preferType: SheetType.CENTER | SheetType.POPUP = SheetType.CENTER
  @State any_blurStyle_1: BlurStyle = BlurStyle.Thin
  @State any_blurStyle_2: BlurStyle = BlurStyle.Regular

  @Builder
  myBuilder() {
    Column() {
      Button("myBuilder")
        .margin(10)
        .fontSize(20)
    }
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindSheetTest_two)
  }

  build() {
    Column() {
      Button("BindSheet1")
        .bindSheet(true, this.myBuilder(), {
          preferType: this.any_preferType,
          showClose: this.any_boolean,
          dragBar: this.any_boolean,
          blurStyle: this.any_blurStyle_1,
          enableOutsideInteractive: this.any_boolean,
          title: () => {
            this.myBuilder()
          }
        })
        .id('buttonBindSheet3')
      Button("BindSheet2")
        .bindSheet(true, this.myBuilder(), { showClose: $r('app.boolean.false'), blurStyle: this.any_blurStyle_2 })
        .id('buttonBindSheet4')
      Button("ButtonBindSheet").onClick(() => {
        this.any_boolean = !this.any_boolean
        this.any_preferType = SheetType.POPUP
        this.any_blurStyle_1 = BlurStyle.Thick
        this.any_blurStyle_2 = BlurStyle.NONE
      })
    }
  }
}