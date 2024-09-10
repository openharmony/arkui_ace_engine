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
import richEditorBindSelectionMenuTest from '../MyTest/RichEditorBindSelectionMenuTest'

@Entry
@Component
struct RichEditorBindSelectionMenuSample {
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller }
  @State spanType: RichEditorSpanType = RichEditorSpanType.TEXT
  @State responseType: ResponseType = ResponseType.LongPress
  @State richEditorResponseType: RichEditorResponseType = RichEditorResponseType.RIGHT_CLICK
  @State option: SelectionMenuOptions = {
    onDisappear: () => {
    }
  }

  aboutToAppear(): void {
    loadComponentTestEntry(richEditorBindSelectionMenuTest)
  }

  @Builder
  panel() {
    Column() {
      Text('菜单模式')
    }.width(256)
  }

  build() {
    Column() {
      Column() {
        RichEditor(this.options)
          .onReady(() => {
            this.controller.addTextSpan('Hello World', { style: { fontColor: Color.Orange, fontSize: 30 } })
          })
          .bindSelectionMenu(this.spanType, this.panel, this.responseType, this.option)
          .id('richEditorBindSelectionMenu1')
        Button('RichEditorBindSelectionMenu1')
          .onClick(() => {
            this.spanType = RichEditorSpanType.IMAGE
            this.responseType = ResponseType.RightClick
            this.option = {
              onAppear: () => {
              }
            }
          })
        RichEditor(this.options)
          .onReady(() => {
            this.controller.addTextSpan('Hello World', { style: { fontColor: Color.Orange, fontSize: 30 } })
          })
          .bindSelectionMenu(RichEditorSpanType.IMAGE, this.panel, this.richEditorResponseType, {
            onAppear: () => {
            }
          })
          .id('richEditorBindSelectionMenu2')
        Button('RichEditorBindSelectionMenu2')
          .onClick(() => {
            this.richEditorResponseType = RichEditorResponseType.SELECT
          })
        RichEditor(this.options)
          .onReady(() => {
            this.controller.addTextSpan('Hello World', { style: { fontColor: Color.Orange, fontSize: 30 } })
          })
          .bindSelectionMenu(RichEditorSpanType.MIXED, this.panel, RichEditorResponseType.LONG_PRESS, {
            onDisappear: () => {
            }
          })
          .id('richEditorBindSelectionMenu3')
      }
    }.height('100%')
  }
}