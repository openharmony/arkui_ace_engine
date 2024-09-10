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
import rectStrokeMiterLimitTest from '../MyTest/RectStrokeMiterLimitTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectStrokeMiterLimitSample {
  @State strokeMiterLimitValue: number | string = 0.8

  aboutToAppear(): void {
    loadComponentTestEntry(rectStrokeMiterLimitTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect()
        .width('90%')
        .height(50)
        .stroke(Color.Red)
        .strokeLineJoin(LineJoinStyle.Miter)
        .strokeMiterLimit(this.strokeMiterLimitValue)
        .id('rectStrokeMiterLimit')
      Button('RectStrokeMiterLimit1')
        .onClick(() => {
          this.strokeMiterLimitValue = '10'
        })
      Button('RectStrokeMiterLimit2')
        .onClick(() => {
          this.strokeMiterLimitValue = '-100'
        })
    }
  }
}