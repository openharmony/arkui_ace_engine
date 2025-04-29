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
import loadingProgressColorTest from '../MyTest/LoadingProgressColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LoadingProgressColorSample {
  @State colorStatus: ResourceColor = Color.Pink

  aboutToAppear(): void {
    loadComponentTestEntry(loadingProgressColorTest)
  }

  build() {
    Column({ space: 5 }) {
      LoadingProgress()
        .color(this.colorStatus)
        .width(100)
        .height(100)
        .id('loadingProgressColor1')

      LoadingProgress()
        .color(0xFFFF00)
        .width(100)
        .height(100)
        .id('loadingProgressColor2')

      Button('LoadingProgressColor1')
        .onClick(() => {
          this.colorStatus = "#ff07f31d"
        })

      Button('LoadingProgressColor2')
        .onClick(() => {
          this.colorStatus = $r('app.color.loadingProgress_color')
        })
    }
  }
}