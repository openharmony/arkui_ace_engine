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
struct TextInput4263 {
  controller: TextInputController = new TextInputController()
  @State inputValue: string = ""
  @State colorAll: (Color | number | string | Resource)[] = [Color.Pink, 0x008000 ,'rgb(255,0,0)', '#0000ff', Color.Brown, $r('app.color.color_yellow')]
  @State decorationType: TextDecorationType[] = [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State type: InputType[] = [InputType.Normal, InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber, InputType.USER_NAME, InputType.NEW_PASSWORD]
  @State typeStr: string[] = ['Normal', 'Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'SCREEN_LOCK_PASSWORD', 'USER_NAME', 'NEW_PASSWORD']
  @State inputIndex: number = 0
  @State decoration: TextDecorationOptions = {
    type: this.decorationType[this.typeIndex],
    color: this.colorAll[this.decorationColor]
  }
  @State style: TextInputStyle = TextInputStyle.Default
  @State textAlign: TextAlign[] = [TextAlign.Start, TextAlign.Center, TextAlign.End]
  @State textAlignStr: string[] = ['Start', 'Center', 'End']
  @State textAlignIndex: number = 0
  @State fontSize:number = 16
  @State showUnderline: boolean = false
  @State maxLength: number = 6
  @State letterSpacing: (number | string | Resource)[] = [-2, 0, 3, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State lineHeight: (number | string | Resource)[] = [-5, 0, 10, 20, '40vp', '30%']
  @State lineHeightIndex: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 250
  @State paddingTest: number = 0
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakIndex: number = 0
  @State sizeAll: (number | string | Resource | undefined)[] = [-1, 0, 20, 'hsp', undefined, '20px', '10abc', $r('app.string.number_20px'), $r('app.string.number_10abc')]
  @State maxFontSize: number = 2
  @State minFontSize: number = 2
  @State heightAdaptivePolicy: TextHeightAdaptivePolicy[] = [TextHeightAdaptivePolicy.MAX_LINES_FIRST, TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST]
  @State heightAdaptiveIndex: number = 0
  @State selectionStart: number = 0
  @State selectionEnd: number = 0

  build() {
    Column() {
      TextInput()
      TextInput({ controller: this.controller, text: this.inputValue ,placeholder:'input your word...'})
        .onChange((value: string) => {
          this.inputValue = value
        })
        .type(this.type[this.inputIndex])
        .style(this.style)
        .textAlign(this.textAlign[this.textAlignIndex])

      Scroll() {
        Column({ space:5}) {
          Row() {
            Button('type:' + this.typeStr[this.inputIndex])
              .width('50%')
              .onClick(() => {
                this.inputIndex = (this.inputIndex + 1) % this.type.length
              })

            Button('textAlign:' + this.textAlignStr[this.textAlignIndex])
              .width('50%')
              .onClick(() => {
                this.textAlignIndex = (this.textAlignIndex + 1) % this.textAlign.length
              })
          }

          Row() {
            Button('style:Default')
              .width('50%')
              .onClick(() => {
                this.style = TextInputStyle.Default
              })

            Button('style:Inline')
              .width('50%')
              .onClick(() => {
                this.style = TextInputStyle.Inline
              })
          }

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
                this.controller.setTextSelection(this.selectionStart,this.selectionEnd)
            })
          }
        }
      }.margin({ top:50 }).height('60%')
    }
  }
}