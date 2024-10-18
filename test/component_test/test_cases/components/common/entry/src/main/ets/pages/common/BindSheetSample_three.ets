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

import bindSheetTest_three from '../MyTest/BindSheetTest_three'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindSheetSample_three {
  @Builder
  myBuilder() {
    Column() {
      Button("myBuilder")
        .margin(10)
        .fontSize(20)
    }
  }

  @State any_boolean: boolean = true
  @State any_maskColor_1: ResourceColor = $r("app.string.common_color")
  @State any_maskColor_2: ResourceColor = 'rgb(192,124,3)'

  aboutToAppear(): void {
    loadComponentTestEntry(bindSheetTest_three)
  }

  build() {
    Column() {

      Button("BindSheet_1")
        .bindSheet(true, this.myBuilder(), {
          maskColor: this.any_maskColor_1,
          title: { title: "title", subtitle: "subtitle" },
          enableOutsideInteractive: this.any_boolean,
          shouldDismiss: ((sheetDismiss: SheetDismiss) => {
            console.log("bind sheet shouldDismiss")
            sheetDismiss.dismiss()
          })
        }).id('buttonBindSheet5')

      Button("BindSheet_2")
        .bindSheet(true, this.myBuilder(),
          { title: { title: $r('app.string.module_desc'), subtitle: $r('app.string.module_desc') } })
        .id('buttonBindSheet6')

      Text("BindSheet_3")
        .bindSheet(false, this.myBuilder(), {
          maskColor: this.any_maskColor_2, title: () => {
            this.myBuilder()
          }
        })
        .id('textBindSheet7')

      Button("ButtonBindSheet").onClick(() => {
        this.any_boolean = !this.any_boolean
        this.any_maskColor_1 = Color.Black
        this.any_maskColor_2 = 0x77fa6e
      })
    }
  }
}