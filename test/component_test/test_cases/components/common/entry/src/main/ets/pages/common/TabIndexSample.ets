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

import tabIndexTest from '../MyTest/TabIndexTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabIndexSample {
  @State index: number = 1

  aboutToAppear(): void {
    loadComponentTestEntry(tabIndexTest)
  }

  build() {
    Column() {
      TextArea()
        .focusable(true)
        .tabIndex(this.index)
        .id('textAreaTabIndex')
      Button('ButtonTabIndex')
        .onClick(() => {
          this.index = -1
        })
    }
  }
}

