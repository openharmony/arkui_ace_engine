/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { hilog } from '@kit.PerformanceAnalysisKit';

const TAG = 'FocusScaleTest';

/**
 * Issue: When a Button inside a horizontal List gets focus, the framework
 * applies a scale (from ButtonTheme::scaleHoverOrFocus). The focus scroll
 * calculation in GetMoveOffset used GetFrameSize() (unscaled layout size)
 * for the child size but GetTransformRelativeOffset() (which includes
 * scale) for the child position. This inconsistency caused the 5vp safe
 * margin to be insufficient.
 *
 * Use keyboard TAB (code 2049) to activate focus mode, then DPAD_RIGHT
 * (code 2015) to move focus horizontally.
 */
@Entry
@Component
struct HorizontalListFocusScaleDemo {
  @State focusedIndex: number = 0

  private itemWidth: number = 120
  private itemHeight: number = 60
  private focusScale: number = 1.3

  build() {
    Column({ space: 12 }) {
      Text('HorizontalList Focus+Scale 5vp Margin Demo')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      List({ space: 10 }) {
        ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], (i: number) => {
          ListItem() {
            Button('Btn ' + i)
              .width(this.itemWidth)
              .height(this.itemHeight)
              .fontSize(14)
              .scale(this.focusedIndex === i ?
                { x: this.focusScale, y: this.focusScale } : { x: 1, y: 1 })
              .focusable(true)
              .defaultFocus(i === 0)
              .onFocus(() => {
                this.focusedIndex = i
                hilog.info(0x3900, TAG, `Btn ${i} focused`)
              })
          }
        })
      }
      .listDirection(Axis.Horizontal)
      .width('100%')
      .height(100)
      .padding(10)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)

      Text('TAB to activate focus, then DPAD_RIGHT to navigate. Check 5vp margin.')
        .fontSize(12)
        .fontColor('#666666')
        .width('100%')

      Text(`Focused: Btn ${this.focusedIndex}`)
        .fontSize(14)
        .fontColor('#333333')
        .width('100%')
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .backgroundColor('#FFFFFF')
  }
}
