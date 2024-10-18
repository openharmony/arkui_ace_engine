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

import setCursorTest_one from '../MyTest/SetCursorTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import pointer from '@ohos.multimodalInput.pointer';

@Entry
@Component
struct SetCursorSample_one {
  @State text: string = ''
  @State cursorWest: PointerStyle = pointer.PointerStyle.WEST
  @State cursorNorth: PointerStyle = pointer.PointerStyle.SOUTH

  aboutToAppear(): void {
    loadComponentTestEntry(setCursorTest_one)
  }

  build() {
    Column() {
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Blue)
        .position({ x: 0, y: 0 })
        .id('rowSetCursor1')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.DEFAULT)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Black)
        .position({ x: 50, y: 0 })
        .id('rowSetCursor2')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.EAST)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Green)
        .position({ x: 100, y: 0 })
        .id('rowSetCursor3')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorWest)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor1')
        .onClick(() => {
          this.cursorWest = pointer.PointerStyle.NORTH
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Pink)
        .position({ x: 150, y: 0 })
        .id('rowSetCursor4')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorNorth)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor2')
        .onClick(() => {
          this.cursorNorth = pointer.PointerStyle.NORTH_SOUTH
        })
    }.width('100%')
  }
}