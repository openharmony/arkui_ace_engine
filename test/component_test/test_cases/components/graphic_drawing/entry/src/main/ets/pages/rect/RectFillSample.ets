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
import rectFillTest from '../MyTest/RectFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectFillSample {
  @State rectFillColorValue1: ResourceColor = $r('app.color.color_blue')
  @State rectFillColorValue2: ResourceColor = 'rgb(255,203,233)'

  aboutToAppear(): void {
    loadComponentTestEntry(rectFillTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect({ width: '90%', height: 50 })
        .fill(this.rectFillColorValue1)
        .id('rectFill1')
      Button('RectFill1')
        .onClick(() => {
          this.rectFillColorValue1 = 0xffc0e6
        })
      Rect({ width: '90%', height: 50 })
        .fill(this.rectFillColorValue2)
        .id('rectFill2')
      Button('RectFill2')
        .onClick(() => {
          this.rectFillColorValue2 = Color.Pink
        })
    }
  }
}