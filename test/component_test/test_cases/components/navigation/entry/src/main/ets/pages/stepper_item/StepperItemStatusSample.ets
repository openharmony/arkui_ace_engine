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
import stepperItemStatusTest from '../MyTest/StepperItemStatusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct StepperItemStatusSample {
  @State itemStatus1: ItemState = ItemState.Normal

  aboutToAppear(): void {
    loadComponentTestEntry(stepperItemStatusTest)
  }

  build() {
    Column() {
      Stepper() {
        StepperItem() {
          Text('stepperItemStatusText1')
        }.status(this.itemStatus1)
        .id('stepperItemStatus1')
      }.height('60%')

      Button('StepperItemStatus1')
        .onClick(() => {
          this.itemStatus1 = ItemState.Disabled
        })
      Button('StepperItemStatus2')
        .onClick(() => {
          this.itemStatus1 = ItemState.Skip
        })
      Button('StepperItemStatus3')
        .onClick(() => {
          this.itemStatus1 = ItemState.Waiting
        })
    }
  }
}