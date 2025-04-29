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
struct CaretColorStruct {
  @State positionInfo: CaretOffset = { index: 0, x: 0, y: 0 }
  controller: TextAreaController = new TextAreaController()
  @State colorNumberIndex: number = 0
  @State text: string = ''
  @State testCaseListCaretColor: (ResourceColor | undefined | null)[] = [
    Color.Black, Color.Blue, Color.Brown, Color.Gray, Color.Grey, Color.Green,
    Color.Orange, Color.Pink, Color.Red, Color.White, Color.Yellow, Color.Transparent,
    0x000000, 0x808080, 0x0000ff0000ff0000ff0000ff0000ff, '#ffffff', '#ff000000',
    'rgb(255, 100, 255)', 'rgba(0, 0, 255, 0.1)', 'rgba(0, 0, 255, 0.5)', 'rgba(0, 0, 255, 1)',
    '', '0x0000ffabc', $r('sys.color.brand'), 0, -1, 1.500, 9999, undefined, null
  ]

  build() {
    Column() {
      Text('API>=12时，光标与手柄颜色一致').margin({ top: 20 })
      Text('输入文本并选中，查看光标与手柄颜色').margin({ top: 20 })
      TextArea({ placeholder: ' TextArea', controller: this.controller })
        .caretColor(this.testCaseListCaretColor[this.colorNumberIndex])
        .margin(10)
        .textAlign(TextAlign.Start)
        .width('95%')
        .height(60)

      TextInput({ placeholder: 'TextInput', controller: this.controller })
        .caretColor(this.testCaseListCaretColor[this.colorNumberIndex])
        .fontSize(20)
        .type(InputType.Normal)
        .width('95%')
        .height(60)
        .textAlign(TextAlign.Start)

      Row({ space: 10 }) {
        Text(this.colorNumberIndex + 1 + '/' + this.testCaseListCaretColor.length).width(50)
        Button('改变颜色')
          .backgroundColor(this.testCaseListCaretColor[this.colorNumberIndex])
          .onClick(() => {
            this.colorNumberIndex++
            if (this.colorNumberIndex > this.testCaseListCaretColor.length - 1) {
              this.colorNumberIndex = 0
            }
          })
      }
    }
  }
}