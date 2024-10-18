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

import alignRulesTest from '../MyTest/AlignRulesTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlignRulesSample {
  private value: string = 'AlignRules'
  @State change_value_1: AlignRuleOption = {
    top: { anchor: "__container__", align: VerticalAlign.Top },
    bottom: { anchor: "__container__", align: VerticalAlign.Bottom },
    left: { anchor: "__container__", align: HorizontalAlign.Start },
    right: { anchor: "__container__", align: HorizontalAlign.End },
    middle: { anchor: "__container__", align: HorizontalAlign.Center },
    center: { anchor: "__container__", align: VerticalAlign.Center },
    bias: { horizontal: 0, vertical: 0 }
  }
  @State change_value_2: AlignRuleOption = {
    top: { anchor: "__container__", align: VerticalAlign.Bottom },
    bottom: { anchor: "__container__", align: VerticalAlign.Top },
    left: { anchor: "__container__", align: HorizontalAlign.End },
    right: { anchor: "__container__", align: HorizontalAlign.Start },
    middle: { anchor: "__container__", align: HorizontalAlign.Start },
    center: { anchor: "__container__", align: VerticalAlign.Top },
    bias: { horizontal: 0, vertical: 0 }
  }
  @State change_value_3: AlignRuleOption = {
    top: { anchor: "__container__", align: VerticalAlign.Center },
    bottom: { anchor: "__container__", align: VerticalAlign.Center },
    left: { anchor: "__container__", align: HorizontalAlign.Center },
    right: { anchor: "__container__", align: HorizontalAlign.Center },
    middle: { anchor: "__container__", align: HorizontalAlign.End },
    center: { anchor: "__container__", align: VerticalAlign.Bottom },
    bias: { horizontal: 0, vertical: 0 }
  }

  aboutToAppear(): void {
    loadComponentTestEntry(alignRulesTest)
  }

  build() {
    Column({ space: 100 }) {
      RelativeContainer() {
        QRCode(this.value)
          .alignRules(this.change_value_1)
          .id("qRCodeAlignRules1")
      }.width(100).height(100)

      RelativeContainer() {
        QRCode(this.value)
          .alignRules(this.change_value_3)
          .id("qRCodeAlignRules2")
      }.width(100).height(100)

      Button('ButtonAlignRules1').onClick(() => {
        this.change_value_1 = this.change_value_2
      })
    }
  }
}