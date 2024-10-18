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

import useEffectTest from '../MyTest/UseEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct UseEffectSample {
  @State bool: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(useEffectTest)
  }

  build() {
    Stack() {
      Image($r("app.media.app_icon"))
        .autoResize(true)
      Column() {
        Text("Normal text with useEffect blur")
          .backgroundColor(Color.Grey)
          .useEffect(this.bool)
          .width('90%')
          .height('48')
          .id('textUseEffect')
        Button('ButtonUseEffect')
          .onClick(() => {
            this.bool = !this.bool
          })
      }
      .width('100%')
    }
  }
}


