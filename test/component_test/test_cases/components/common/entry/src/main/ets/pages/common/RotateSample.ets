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

import rotateTest from '../MyTest/RotateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RotateSample {
  private arrayA: string[] = ['甲', '乙', '丙']
  @State rotateType: number | string = 10

  aboutToAppear(): void {
    loadComponentTestEntry(rotateTest)
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .rotate({
          x: 0,
          y: 0,
          z: 1,
          angle: this.rotateType,
          centerX: this.rotateType,
          centerY: this.rotateType,
          centerZ: 10,
          perspective: 10
        })
        .id('alphabetIndexerRotate1')
        .margin({ left: 10, bottom: 20 })
      Button('ButtonRotate1')
        .onClick(() => {
          this.rotateType = "90deg"
        })
    }
  }
}