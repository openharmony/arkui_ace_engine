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
import pointer from '@ohos.multimodalInput.pointer';
import setCursorTest_five from '../MyTest/SetCursorTest_five'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SetCursorSample_five {
  @State text: string = ''
  @State cursorOne: PointerStyle = pointer.PointerStyle.TEXT_CURSOR
  @State cursorTwo: PointerStyle = pointer.PointerStyle.ZOOM_IN

  aboutToAppear(): void {
    loadComponentTestEntry(setCursorTest_five)
  }

  build() {
    Column() {
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Blue)
        .position({ x: 0, y: 0 })
        .id('rowSetCursor17')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.SCREENSHOT_CHOOSE)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Black)
        .position({ x: 50, y: 0 })
        .id('rowSetCursor18')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(pointer.PointerStyle.SCREENSHOT_CURSOR)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Green)
        .position({ x: 100, y: 0 })
        .id('rowSetCursor19')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorOne)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor1')
        .onClick(() => {
          this.cursorOne = pointer.PointerStyle.ZOOM_OUT
        })
      Row()
        .height(50)
        .width(50)
        .backgroundColor(Color.Pink)
        .position({ x: 150, y: 0 })
        .id('rowSetCursor20')
        .onHover((flag) => {
          if (flag) {
            cursorControl.setCursor(this.cursorTwo)
          } else {
            cursorControl.restoreDefault()
          }
        })
      Button('ButtonSetCursor2')
        .onClick(() => {
          this.cursorTwo = pointer.PointerStyle.MIDDLE_BTN_EAST
        })
    }.width('100%')
  }
}