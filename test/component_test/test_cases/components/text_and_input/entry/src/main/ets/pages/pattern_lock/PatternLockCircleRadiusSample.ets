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
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import patternLockCircleRadiusTest from '../MyTest/PatternLockCircleRadiusTest'

@Entry
@Component
struct PatternLockCircleRadiusSample {
  @State circleRadiusType: Length = 50

  aboutToAppear(): void {
    loadComponentTestEntry(patternLockCircleRadiusTest)
  }

  build() {
    Column() {
      PatternLock()
        .circleRadius(this.circleRadiusType)
        .id('patternLockCircleRadius1')
      Button('PatternLockCircleRadius1')
        .onClick(() => {
          this.circleRadiusType = '20px'
        })
      Button('PatternLockCircleRadius2')
        .onClick(() => {
          this.circleRadiusType = -1
        })
      PatternLock()
        .circleRadius($r('app.string.vp_length'))
        .id('patternLockCircleRadius2')
    }
  }
}