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
import useShadowBatchingTest from '../MyTest/UseShadowBatchingTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct UseShadowBatchingSample {
  @State useShadowBoolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(useShadowBatchingTest)
  }

  build() {
    Column() {
      Column({ space: 10 }) {
        Stack() {
        }
        .width('90%')
        .height(50)
        .margin({ top: 100 })
        .backgroundColor(0xFFE4C4)
        .shadow({ radius: 200, color: Color.Green })

        Stack() {
        }
        .width('90%')
        .height(50)
        .margin({ top: 40 })
        .backgroundColor(0xFFE4C4)
        .shadow({ radius: 200, color: Color.Red })

      }
      .useShadowBatching(this.useShadowBoolean)
      .id('columUseShadowBatching1')

      Button('ButtonUseShadowBatching1')
        .onClick(() => {
          if (this.useShadowBoolean) {
            this.useShadowBoolean = false;
          } else {
            this.useShadowBoolean = true;
          }
        })
    }
    .width('100%').margin({ top: 5 })
  }
}