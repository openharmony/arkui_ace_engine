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

@Entry
@Component
struct Richeditor5_2 {
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller };
  controller2: RichEditorController = new RichEditorController();
  options2: RichEditorOptions = { controller: this.controller2 };
  private start: number = -1;
  private end: number = -1;
  @State message: string = "[-1, -1]"
  @State content: string = ""
  @State copyOption: CopyOptions[] = [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2

  build() {
    Column() {

      Column() {
        RichEditor(this.options2)
          .borderWidth(1)
          .borderColor(Color.Green)
          .width("100%")
          .height("30%")
          .copyOptions(this.copyOption[this.index])
        RichEditor(this.options)
          .borderWidth(1)
          .borderColor(Color.Green)
          .width("100%")
          .height("30%")
          .copyOptions(this.copyOption[this.index])
      }
      .borderWidth(1)
      .borderColor(Color.Red)
      .width("100%")

      Column() {
        Row(){
          Button("添加文本").onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            this.controller.addTextSpan("0123456789",
              {
                offset: CaretOffset
              })
            this.controller.setCaretOffset(CaretOffset + 10)
            let CaretOffset2 = this.controller2.getCaretOffset()
            this.controller2.addTextSpan("0123456789",
              {
                offset: CaretOffset2
              })
            this.controller2.setCaretOffset(CaretOffset2 + 10)
          })

          Button("添加图片").onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            this.controller.addImageSpan($r("app.media.icon"),
              {
                offset: CaretOffset,
                imageStyle:
                {
                  size: ["57px", "57px"]
                }
              })
            this.controller.setCaretOffset(CaretOffset + 1)

            let CaretOffset2 = this.controller2.getCaretOffset()
            this.controller2.addImageSpan($r("app.media.icon"),
              {
                offset: CaretOffset2,
                imageStyle:
                {
                  size: ["57px", "57px"]
                }
              })
            this.controller2.setCaretOffset(CaretOffset2 + 1)
          })
        }
        Row(){
          Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
            this.index ++
            if (this.index > (this.copyOptionStr.length - 1)) {
              this.index = 0
            }
          })
        }
      }



    }
  }
}