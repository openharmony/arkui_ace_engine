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

import hitTestBehaviorTest from '../MyTest/HitTestBehaviorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct HitTestBehaviorSample {
  @State hitTestModeArr: HitTestMode[] = [HitTestMode.Default, HitTestMode.Block,
    HitTestMode.Transparent, HitTestMode.None]
  index: number = 0
  @State hitTestMode: HitTestMode = this.hitTestModeArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(hitTestBehaviorTest)
  }

  build() {
    Column() {

      Text('Transparent')
        .id('textHitTestBehavior')
        .hitTestBehavior(this.hitTestMode)

      Button('ButtonHitTestBehavior').onClick(() => {
        this.index++
        this.hitTestMode = this.hitTestModeArr[this.index % 4]
      })
    }
  }
}