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

import heightTest from '../MyTest/HeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct HeightSample {
  @State num: Length = '30px'

  aboutToAppear(): void {
    loadComponentTestEntry(heightTest)
  }

  build() {
    Column() {
      Column().width(30).height(20).backgroundColor(0xff0000)
        .id('columnHeight1')
      Column().width(30).height(this.num)
        .id('columnHeight2')
      Button('ButtonHeight')
        .onClick(() => {
          this.num = $r('app.string.common_height')
        })
    }
  }
}

