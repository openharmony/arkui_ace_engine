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
//测试代码路径
import progressColorResourceColorTest from '../MyTest/ProgressColorResourceColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressColorResourceColorSample {
  @State color: ResourceColor = Color.Red

  aboutToAppear(): void {
    loadComponentTestEntry(progressColorResourceColorTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 70 })
        .color(this.color)
        .id('progressColorResourceColor1')
      Button('ProgressColorResourceColor1')
        .onClick(() => {
          this.color = 0x000000
        })
      Button('ProgressColorResourceColor2')
        .onClick(() => {
          this.color = '#0000ff'
        })
      Progress({ value: 70 })
        .color($r("app.color.progress_color"))
        .id('progressColorResourceColor2')
    }
  }
}