/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { LengthUnit } from '@kit.ArkUI'

@Entry
@Component
struct PatternLockExample {
  private patternLockController: PatternLockController = new PatternLockController()

  build() {
    Column() {
      PatternLock(this.patternLockController)
        .sideLength(300)
        .circleRadius(10)
        .pathStrokeWidth(10)
        .activeColor('#707070')
        .selectedColor('#707070')
        .pathColor('#707070')
        .backgroundColor('#F5F5F5')
        .autoReset(true)
        .activateCircleStyle({
          color: Color.Green,
          radius: { value: 20, unit: LengthUnit.VP },
          enableForeground: true
        })

      PatternLock(this.patternLockController)
        .sideLength(300)
        .circleRadius(10)
        .pathStrokeWidth(10)
        .activeColor('#707070')
        .selectedColor('#707070')
        .pathColor('#707070')
        .backgroundColor('#F5F5F5')
        .autoReset(true)
        .activateCircleStyle({
          color: Color.Green,
          radius: { value: 20, unit: LengthUnit.VP },
          enableForeground: false
        })
    }.width('100%').height('100%')
  }
}