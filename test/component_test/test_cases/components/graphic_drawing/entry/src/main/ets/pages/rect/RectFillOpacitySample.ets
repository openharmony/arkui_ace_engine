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
// 测试代码路径
import rectFillOpacityTest from '../MyTest/RectFillOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectFillOpacitySample {
  @State fillOpacityValue: Length = '0.2px'

  aboutToAppear(): void {
    loadComponentTestEntry(rectFillOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect()
        .width('90%')
        .height(50)
        .fill(Color.Pink)
        .fillOpacity(0.5)
        .id('rectFillOpacity1')
      Rect()
        .width('90%')
        .height(50)
        .fill(Color.Pink)
        .fillOpacity(this.fillOpacityValue)
        .id('rectFillOpacity2')
      Button('RectFillOpacity')
        .onClick(() => {
          this.fillOpacityValue = $r('app.string.fill_opacity')
        })
    }
  }
}