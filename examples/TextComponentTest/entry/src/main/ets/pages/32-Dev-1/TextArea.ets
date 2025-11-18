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
struct TextArea32dev2 {
  controller: TextAreaController = new TextAreaController()
  @State textOverflow: (TextOverflow | undefined | null)[] =
    [TextOverflow.Clip, TextOverflow.None, TextOverflow.Ellipsis, TextOverflow.MARQUEE, undefined, null]
  @State textOverflowStr: string[] = ['Clip', 'None', 'Ellipsis', 'MARQUEE', 'undefined', 'null']
  @State textOverflowIndex: number = 0
  @State maxLines: number = 2
  @State type: TextAreaType[] =
    [TextAreaType.NORMAL, TextAreaType.NUMBER, TextAreaType.PHONE_NUMBER, TextAreaType.EMAIL,
      TextAreaType.NUMBER_DECIMAL]
  @State typeStr: string[] = ['NORMAL', 'NUMBER', 'PHONE_NUMBER', 'EMAIL', 'NUMBER_DECIMAL']
  @State inputIndex: number = 0
  @State style: TextContentStyle = TextContentStyle.DEFAULT
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakStr: string[] = ['NORMAL', 'BREAK_ALL', 'BREAK_WORD']
  @State wordBreakIndex: number = 2
  @State textIndent: (Dimension)[] =
    [0.1, -10, 10, '15vp', '15px', '50%', $r('app.string.size'), $r('app.string.size2')]
  @State textIndentIndex: number = 0
  @State paddingTest: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 250
  @State letterSpacing: (number | string | Resource)[] = [-2, 0, 3, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State value: string = ''
  @State colorAll: (Color | number | string | Resource | null | undefined)[] =
    [Color.Green, 0xffff00, '#FFb6c1', $r('app.color.red'), -12, null, undefined]
  @State color: string[] = ['Color.Green', '0xffff00', '#FFb6c1', '$r(app.color.red)', '-12', 'null', 'undefined']
  @State selectedBackgroundColor: number = 1
  @State selectionStart: number = 0
  @State selectionEnd: number = 0
  @State caretWidthAll: (string | number | Resource | null)[] =
    [0, 10, -10, '10vp', '50px', '50%', '10abc', null, $r('app.string.size')]
  @State caretWidth: number = 0
  @State caretColor: number = 0
  @State maxLength: number = 6
  @State decorationType: TextDecorationType[] =
    [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State insertValue: string = ''
  @State deleteValue: string = ''
  @State errorText: string = ''
  @State isShow: number = 0
  @State enterKeyType: EnterKeyType[] =
    [EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Next, EnterKeyType.Done,
      EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE]
  @State enterKeyTypeIndex: number = 0
  @State previewRangeStart: string = ''
  @State previewRangeEnd: string = ''
  @State enablePreviewText: (boolean | undefined)[] = [true, false, undefined]
  @State enableIndex: number = 2

  build() {
    Column({ space: 5 }) {
      Text('error:' + this.errorText)
      Text('insertValue:' + this.insertValue)
      Text('deleteValue:' + this.deleteValue)
      Text('previewRangeStart:' + this.previewRangeStart + 'previewRangeEnd:' + this.previewRangeEnd)

      TextArea()
        .margin({ top: 5 })
        .textOverflow(this.textOverflow[this.textOverflowIndex])

      TextArea()
        .margin({ top: 5 })
        .textOverflow(this.textOverflow[this.textOverflowIndex])

      if (this.isShow === 0) {
        TextArea({ text: this.value, placeholder: 'input your word....', controller: this.controller })
          .textOverflow(this.textOverflow[this.textOverflowIndex])
          .margin({ top: 5 })
          .maxLines(this.maxLines)
          .type(this.type[this.inputIndex])
          .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
          .style(this.style)
          .enablePreviewText(this.enablePreviewText[this.enableIndex])
          .maxLength(this.maxLength)
          .wordBreak(this.wordBreak[this.wordBreakIndex])
          .textIndent(this.textIndent[this.textIndentIndex])
          .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
          .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
          .padding(this.paddingTest)
          .width(this.widthTest)
          .height(this.heightTest)
          .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
          .caretStyle({
            width: this.caretWidthAll[this.caretWidth],
            color: this.colorAll[this.caretColor]
          })
          .onChange((value: string, previewRange: PreviewText, options: TextChangeOptions) => {
            this.value = value
            this.previewRangeStart = options.rangeAfter.start + ''
            this.previewRangeEnd = options.rangeAfter.end + ''
          })
          .decoration({
            type: this.decorationType[this.typeIndex],
            color: this.colorAll[this.decorationColor]
          })
          .onWillInsert((info: InsertValue) => {
            this.insertValue = info.insertValue
            return true;
          })
          .onWillDelete((info: DeleteValue) => {
            this.deleteValue = info.deleteValue
            info.direction
            return true;
          })
      } else if (this.isShow === 1) {
        TextArea({ text: this.value, placeholder: 'input your word....', controller: this.controller })
          .textOverflow(this.textOverflow[this.textOverflowIndex])
          .margin({ top: 5 })
          .maxLines(this.maxLines)
          .type(this.type[this.inputIndex])
          .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
          .enablePreviewText(this.enablePreviewText[this.enableIndex])
          .style(this.style)
          .maxLength(this.maxLength)
          .wordBreak(this.wordBreak[this.wordBreakIndex])
          .textIndent(this.textIndent[this.textIndentIndex])
          .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
          .selectedBackgroundColor(this.colorAll[this.selectedBackgroundColor])
          .padding(this.paddingTest)
          .width(this.widthTest)
          .height(this.heightTest)
          .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
          .caretStyle({
            width: this.caretWidthAll[this.caretWidth],
            color: this.colorAll[this.caretColor]
          })
          .onChange((value: string, previewRange: PreviewText, options: TextChangeOptions) => {
            this.value = value
            this.previewRangeStart = options.rangeAfter.start + ''
            this.previewRangeEnd = options.rangeAfter.end + ''
          })
          .decoration({
            type: this.decorationType[this.typeIndex],
            color: this.colorAll[this.decorationColor]
          })
          .inputFilter('[a-z]', (value: string) => {
            this.errorText = value
          })
          .onWillInsert((info: InsertValue) => {
            this.insertValue = info.insertValue
            return true;
          })
          .onWillDelete((info: DeleteValue) => {
            this.deleteValue = info.deleteValue
            info.direction
            return true;
          })
      }

      Scroll() {
        Column() {

          Row() {
            Button('enablePreviewText:' + this.enablePreviewText[this.enableIndex])
              .width('80%')
              .onClick(() => {
                this.enableIndex = (this.enableIndex + 1) % this.enablePreviewText.length
              })
          }

          Row() {
            Button('inputFilter 不设置')
              .width('40%')
              .onClick(() => {
                this.isShow = 0
              })

            Button('inputFilter [a-z]')
              .width('40%')
              .onClick(() => {
                this.isShow = 1
              })
          }

          Row() {
            Button('selectionEnd+,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd += 1
              })

            Button('selectionEnd-,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd -= 1
              })
          }

          Row() {
            Button('最大字符数+,' + this.maxLength)
              .width('40%')
              .onClick((event: ClickEvent) => {
                this.maxLength += 2
              })
            Button('最大字符数-,' + this.maxLength)
              .width('40%')
              .onClick((event: ClickEvent) => {
                this.maxLength -= 2
              })
          }

          Row() {
            Button('decorationType')
              .width('40%')
              .onClick(() => {
                this.typeIndex = (this.typeIndex + 1) % this.decorationType.length
              })

            Button('decorationColor')
              .width('40%')
              .onClick(() => {
                this.decorationColor = (this.decorationColor + 1) % this.colorAll.length
              })
          }

          Row() {
            Button('setTextSelection')
              .width('40%')
              .onClick(() => {
                this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
              })

            Button('caretWidth:' + this.caretWidthAll[this.caretWidth])
              .width('40%')
              .onClick(() => {
                this.caretWidth = (this.caretWidth + 1) % this.caretWidthAll.length
              })

          }

          Row() {
            Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
              .width('40%')
              .onClick(() => {
                this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              })

            Button('type:' + this.typeStr[this.inputIndex])
              .width('40%')
              .onClick(() => {
                this.inputIndex = (this.inputIndex + 1) % this.type.length
              })
          }

          Row() {
            Button('maxLines+,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines += 1
              })

            Button('maxLines-,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines -= 1
              })
          }

          Row() {
            Button('style:Default')
              .width('40%')
              .onClick(() => {
                this.style = TextContentStyle.DEFAULT
              })

            Button('style:Inline')
              .width('40%')
              .onClick(() => {
                this.style = TextContentStyle.INLINE
              })
          }

          Row() {

            Button('textIndent:' + this.textIndent[this.textIndentIndex])
              .width('40%')
              .onClick(() => {
                this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
              })

            Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
              .width('40%')
              .onClick(() => {
                this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
              })
          }

          Row() {
            Button('padding+,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest += 10
              })

            Button('padding-,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest -= 10
              })
          }

          Row() {

            Button('caretColor:' + this.color[this.caretColor])
              .width('40%')
              .onClick(() => {
                this.caretColor++
                if (this.caretColor > (this.color.length - 1)) {
                  this.caretColor = 0
                }
              })

            Button('enterKeyType: ' + EnterKeyType[this.enterKeyTypeIndex])
              .width('40%')
              .onClick(() => {
                this.enterKeyTypeIndex = (this.enterKeyTypeIndex + 1) % this.enterKeyType.length
              })
          }

          Row() {
            Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
              .width('40%')
              .onClick(() => {
                this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
              })

            Button('底板颜色:' + this.color[this.selectedBackgroundColor])
              .width('40%')
              .onClick(() => {
                this.selectedBackgroundColor++
                if (this.selectedBackgroundColor > (this.color.length - 1)) {
                  this.selectedBackgroundColor = 0
                }
              })
          }

          Row() {
            Button('height+,' + this.heightTest)
              .width('40%')
              .onClick(() => {
                this.heightTest += 10
              })

            Button('height-,' + this.heightTest)
              .width('40%')
              .onClick(() => {
                this.heightTest -= 10
              })
          }

          Row() {
            Button('width+,' + this.widthTest)
              .width('40%')
              .onClick(() => {
                this.widthTest += 10
              })

            Button('width-,' + this.widthTest)
              .width('40%')
              .onClick(() => {
                this.widthTest -= 10
              })
          }

        }.padding({ bottom: 150 })
      }.height('40%')

    }
    .width('100%')
    .height('100%')
  }
}