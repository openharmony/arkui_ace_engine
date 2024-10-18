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
import progressBackgroundColorTest from '../MyTest/ProgressBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressBackgroundColorSample {
  @State backgroundColorStatus: ResourceColor = Color.Red

  aboutToAppear(): void {
    loadComponentTestEntry(progressBackgroundColorTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 70 }).backgroundColor(this.backgroundColorStatus)
        .id('progressBackgroundColor1')
      Button('ProgressBackgroundColor1')
        .onClick(() => {
          this.backgroundColorStatus = 0x000000
        })
      Button('ProgressBackgroundColor2')
        .onClick(() => {
          this.backgroundColorStatus = '#0000ff'
        })
      Progress({ value: 70 }).backgroundColor($r("app.color.progress_background_color"))
        .id('progressBackgroundColor2')
    }
  }
}