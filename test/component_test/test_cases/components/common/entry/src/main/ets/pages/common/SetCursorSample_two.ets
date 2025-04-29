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

import setCursorTest_two from '../MyTest/SetCursorTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import pointer from '@ohos.multimodalInput.pointer';

@Entry
@Component
struct SetCursorSample_two {
  @State text: string = ''
  @State cursorOne: PointerStyle = pointer.PointerStyle.NORTH_WEST
  @State cursorTwo: PointerStyle = pointer.PointerStyle.SOUTH_EAST

  aboutToAppear(): void {
    loadComponentTestEntry(setCursorTest_two)
  }

  build() {
    Column() {
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Blue)
        .position({ x: 0, y: 0 })
        .id('rowSetCursor5')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.NORTH_SOUTH)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Black)
        .position({ x: 50, y: 0 })
        .id('rowSetCursor6')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.NORTH_EAST)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Green)
        .position({ x: 100, y: 0 })
        .id('rowSetCursor7')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorOne)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor1')
        .onClick(() => {
          this.cursorOne = pointer.PointerStyle.SOUTH_WEST
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Pink)
        .position({ x: 150, y: 0 })
        .id('rowSetCursor8')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorTwo)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor2')
        .onClick(() => {
          this.cursorTwo = pointer.PointerStyle.NORTH_EAST_SOUTH_WEST
        })
    }.width('100%')
  }
}