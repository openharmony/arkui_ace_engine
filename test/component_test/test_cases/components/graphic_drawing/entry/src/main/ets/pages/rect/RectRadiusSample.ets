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
import rectRadiusTest from '../MyTest/RectRadiusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectRadiusSample {
  @State radiusValue: string | number | Array<string | number> = 20

  aboutToAppear(): void {
    loadComponentTestEntry(rectRadiusTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect({ width: '90%', height: 80 })
        .radius(this.radiusValue)
        .id('rectRadius1')
      Button('RectRadius')
        .onClick(() => {
          this.radiusValue = '50'
        })
      Rect({ width: '90%', height: 80 })
        .radius([['40', '40'], ['20', ' 20'], ['40', ' 40'], ['20', '20']])
        .id('rectRadius2')
      Rect({ width: '90%', height: 80 })
        .radius([[40, 40], [20, 20], [40, 40], [20, 20]])
        .id('rectRadius3')
    }
  }
}