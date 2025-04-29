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

import visibilityTest from '../MyTest/VisibilityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct VisibilitySample {
  @State visibilityType: Visibility = Visibility.Hidden

  aboutToAppear(): void {
    loadComponentTestEntry(visibilityTest)
  }

  build() {
    Column() {
      Column() {
        Circle({ width: 150, height: 150 })
          .fillOpacity(0)
          .visibility(Visibility.Visible)
          .id('circleVisibility1')
          .backgroundColor(0xAFEEEE)
        Circle({ width: 150, height: 150 })
          .fillOpacity(0)
          .visibility(this.visibilityType)
          .backgroundColor(0xAFEEEE)
          .id('circleVisibility2')
        Button('ButtonVisibility')
          .onClick(() => {
            this.visibilityType = Visibility.None
          })
      }
    }
  }
}