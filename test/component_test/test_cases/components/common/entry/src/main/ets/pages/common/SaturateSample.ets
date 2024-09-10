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

import saturateTest from '../MyTest/SaturateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SaturateSample {
  @State saturateNumber: number = 20

  aboutToAppear(): void {
    loadComponentTestEntry(saturateTest)
  }

  build() {
    Column() {
      Image($r('app.media.app_icon'))
        .width('500px').height('280px')
        .id('imageSaturate1')
        .saturate(this.saturateNumber)
      Button('ButtonSaturate')
        .onClick(() => {
          this.saturateNumber = -1
        })
    }
  }
}