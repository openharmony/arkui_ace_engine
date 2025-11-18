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
struct RichEditor15_2 {
  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller };
  @State message: string = "[-1, -1]"
  @State content: string = ""
  @State copyOption: CopyOptions[] = [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State decorationAll: TextDecorationType[] = [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.Overline, TextDecorationType.LineThrough]
  @State decorationAllStr: string[] = ['None', 'Underline', 'Overline', 'LineThrough']
  @State decoration: number = 0
  @State selectCaret: number = 0
  private start: number = -1;
  private end: number = -1;
  @State enable: boolean = true
  @State fontColorAll: [Color, Color, number, string] = [Color.Black, Color.Green, 0xffc0cb, 'rgb(255, 100, 255)']
  @State decorationColor: number = 0

  build() {
    Column() {

      Column() {
        RichEditor(this.options)
          .draggable(true)
          .borderWidth(1)
          .borderColor(Color.Green)
          .width("100%")
          .height("30%")
          .enabled(this.enable)
          .copyOptions(this.copyOption[this.index])
      }
      .borderWidth(1)
      .borderColor(Color.Red)
      .width("100%")

      TextArea({placeholder:'TextArea'}).height(100).width('80%')

      Column() {
        Row(){
          Button("添加文本").onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            this.controller.addTextSpan("0123456789",
              {
                offset: CaretOffset
              })
            this.controller.setCaretOffset(CaretOffset + 10)
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
          })
        }
        Row(){
          Button('copyOption:' + this.copyOptionStr[this.index]).onClick(() => {
            this.index ++
            if (this.index > (this.copyOptionStr.length - 1)) {
              this.index = 0
            }
          })
          Button('enabled:' + this.enable).onClick((event: ClickEvent) => {
            this.enable = !this.enable
          })
        }
        Row() {
          Button("装饰线样式" + this.decorationAllStr[this.decoration]).onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            if (this.selectCaret != CaretOffset) {
              this.start = -1
              this.end = -1
            }
            this.decoration ++
            if (this.decoration > (this.decorationAll.length - 1)) {
              this.decoration = 0
            }
            this.controller.updateSpanStyle({
              start: this.start,
              end: this.end,
              textStyle:
              {
                decoration: {
                  type: this.decorationAll[this.decoration],
                  color: this.fontColorAll[this.decorationColor]
                }
              }
            })
          })

          Button("装饰线颜色" + this.fontColorAll[this.decorationColor]).onClick(() => {
            let CaretOffset = this.controller.getCaretOffset()
            if (this.selectCaret != CaretOffset) {
              this.start = -1
              this.end = -1
            }
            this.decorationColor ++
            if (this.decorationColor > (this.decorationAll.length - 1)) {
              this.decorationColor = 0
            }
            this.controller.updateSpanStyle({
              start: this.start,
              end: this.end,
              textStyle:
              {
                decoration: {
                  type: this.decorationAll[this.decoration],
                  color: this.fontColorAll[this.decorationColor]
                }
              }
            })
          })
        }
      }



    }
  }
}