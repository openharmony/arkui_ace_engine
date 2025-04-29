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

import motionPathTest from '../MyTest/MotionPathTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MotionPathSample {
  @State toggle: boolean = true
  @State any_boolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(motionPathTest)
  }

  build() {
    Column() {

      Radio({ value: 'Radio1', group: 'radioGroup' })
        .motionPath({
          path: 'Mstart.x start.y L400 200 L200 500 Lend.x end.y',
          from: 0.0,
          to: 1.0,
          rotatable: this.any_boolean
        })
        .onClick(() => {
          animateTo({ duration: 4000, curve: Curve.Linear }, () => {
            this.toggle = !this.toggle
          })
        }).id('radioMotionPath1')

      Button('ButtonMotionPath1').onClick(() => {
        this.any_boolean = !this.any_boolean
      })

    }.width('100%').height('100%').alignItems(this.toggle ? HorizontalAlign.Start : HorizontalAlign.Center)
  }
}
