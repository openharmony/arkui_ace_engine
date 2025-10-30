/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// xxx.ets
@Entry
@Component
struct RichEditor4263 {

  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller };
  @State selectionStart: number = 0
  @State selectionEnd: number = 0

  build() {
    Column() {
      RichEditor(this.options)
        .height(100)
      RichEditor(this.options)
        .onReady(() => {
          this.controller.addTextSpan("012345",
            {
              style:
              {
                fontColor: Color.Orange,
                fontSize: 30
              }
            })
          this.controller.addSymbolSpan($r("sys.symbol.ohos_trash"),
            {
              style:
              {
                fontSize: 30
              }
            })
          this.controller.addImageSpan($r("app.media.icon"),
            {
              imageStyle:
              {
                size: ["57px", "57px"]
              }
            })
          this.controller.addTextSpan("56789",
            {
              style:
              {
                fontColor: Color.Black,
                fontSize: 30
              }
            })
        })
        .height(100)


      Scroll() {
        Column() {
          Row(){
            Button('selectionStart-,' + this.selectionStart)
              .width('50%')
              .onClick((event: ClickEvent) => {
                this.selectionStart -= 2
              })
            Button('selectionStart+,' + this.selectionStart)
              .width('50%')
              .onClick((event: ClickEvent) => {
                this.selectionStart += 2
              })
          }
          Row(){
            Button('selectionEnd-,' + this.selectionEnd)
              .width('50%')
              .onClick((event: ClickEvent) => {
                this.selectionEnd -= 2
              })
            Button('selectionEnd+,' + this.selectionEnd)
              .width('50%')
              .onClick((event: ClickEvent) => {
                this.selectionEnd += 2
              })
          }
          Row() {
            Button('setTextSelection')
              .width('100%')
              .onClick((event: ClickEvent) => {
                this.controller.setSelection(this.selectionStart,this.selectionEnd)

              })
          }
        }
      }.margin({ top:50 }).height('60%')
    }
  }
}