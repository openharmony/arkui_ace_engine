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
import alignTest_two from '../MyTest/AlignTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlignSample_two {
  @State myAlignment: Alignment[] =
    [Alignment.End, Alignment.BottomStart, Alignment.Bottom, Alignment.BottomEnd]
  index = 0
  @State anyAlignment: Alignment = this.myAlignment[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(alignTest_two)
  }

  build() {
    Column() {
      Column({ space: 10 }) {
        Stack() {
          Text('align')
        }
        .width('90%')
        .height(50)
        .margin({ top: 5 })
        .backgroundColor(0xFFE4C4)
        .id('stackAlign2')
        .align(this.anyAlignment)

        Button('ButtonAlign1')
          .onClick(() => {
            this.index++
            this.anyAlignment = this.myAlignment[this.index % 4]
          })
      }
    }
  }
}