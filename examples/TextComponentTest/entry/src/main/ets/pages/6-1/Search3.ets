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
struct Search50019_3 {
  controller: SearchController = new SearchController()
  @State inputValue: string = ""
  @State inputValue2: string = ""
  @State colorAll: (Color | number | string | Resource)[] = [Color.Pink, 0x008000 ,'rgb(255,0,0)', '#0000ff', Color.Brown, $r('app.color.color_yellow')]
  @State decorationType: TextDecorationType[] = [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State type: SearchType[] = [SearchType.NORMAL, SearchType.EMAIL, SearchType.NUMBER, SearchType.PHONE_NUMBER]
  @State typeStr: string[] = ['NORMAL', 'EMAIL', 'NUMBER', 'PHONE_NUMBER']
  @State inputIndex: number = 0
  @State decoration: TextDecorationOptions = {
    type: this.decorationType[this.typeIndex],
    color: this.colorAll[this.decorationColor]
  }
  @State style: TextContentStyle = TextContentStyle.DEFAULT
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
  @State selectionStart: number = 0
  @State selectionEnd: number = 0
  @State menuPolicy: MenuPolicy | null | number | undefined = MenuPolicy.DEFAULT
  @State selectionMenuHidden: boolean = false
  @State ButtonColor1: Color = Color.Blue
  @State ButtonColor2: Color = Color.Blue
  @State ButtonColor3: Color = Color.Blue
  @State ButtonColor4: Color = Color.Blue
  @State ButtonColor5: Color = Color.Blue
  @State ButtonColor6: Color = Color.Blue
  build() {
    Column() {
      Search({ value: this.inputValue2 ,placeholder:'duration: 600'}).margin({ top: 10 })
        .searchButton('search')
        .height(100)
        .onChange((value: string) => {
          this.inputValue2 = value
        })
        .type(this.type[this.inputIndex])
        .selectionMenuHidden(this.selectionMenuHidden)
        .gesture(
          LongPressGesture({ duration: 600 })
            .tag("longPress1")
            .onAction((event?: GestureEvent) => {
              console.log("LongPressGesture onAction");
              this.controller.setTextSelection(this.selectionStart,this.selectionEnd, { menuPolicy: this.menuPolicy })
            })
        )
      Search({ controller: this.controller, value: this.inputValue ,placeholder:'duration: 450'})
        .searchButton('search')
        .height(100)
        .onChange((value: string) => {
          this.inputValue = value
        })
        .type(this.type[this.inputIndex])
        .selectionMenuHidden(this.selectionMenuHidden)
        .gesture(
          LongPressGesture({ duration: 450 })
            .tag("longPress1")
            .onAction((event?: GestureEvent) => {
              console.log("LongPressGesture onAction");
              this.controller.setTextSelection(this.selectionStart,this.selectionEnd, { menuPolicy: this.menuPolicy })
            })
        )
      Column() {

        Row() {
          Button('type:' + this.typeStr[this.inputIndex])
            .width('40%')
            .onClick(() => {
              this.inputIndex = (this.inputIndex + 1) % this.type.length
            })

          Button('selectionMenuHidden:' + this.selectionMenuHidden)
            .width('40%')
            .onClick(() => {
              this.selectionMenuHidden = !this.selectionMenuHidden
            })
        }.margin({ top: 5 })

        Row() {
          Button('selectionStart+,' + this.selectionStart)
            .width('40%')
            .onClick(() => {
              this.selectionStart += 1
            })

          Button('selectionStart-,' + this.selectionStart)
            .width('40%')
            .onClick(() => {
              this.selectionStart -= 1
            })
        }.margin({ top: 5 })

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
        }.margin({ top: 5 })

        Row() {
          Button('setTextSelection')
            .width('80%')
            .onClick(() => {
              this.controller.setTextSelection(this.selectionStart,this.selectionEnd)
            })

        }.margin({ top: 5 })

        Row() {
          Button('DEFAULT')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = MenuPolicy.DEFAULT
            })
            .focusOnTouch(true)
            .backgroundColor(this.ButtonColor1)
            .onFocus(() => {
              this.ButtonColor1 = Color.Red
            })

          Button('HIDE')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = MenuPolicy.HIDE
            })
            .focusOnTouch(true)
            .backgroundColor(this.ButtonColor2)
            .onFocus(() => {
              this.ButtonColor2 = Color.Red
            })


          Button('ALWAYS')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = MenuPolicy.SHOW
            })
            .focusOnTouch(true)
            .backgroundColor(this.ButtonColor3)
            .onFocus(() => {
              this.ButtonColor3 = Color.Red
            })

        }.margin({ top: 5 })

        Row() {
          Button('undefined')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = undefined
            })
            .backgroundColor(this.ButtonColor4)
            .focusOnTouch(true)
            .onFocus(() => {
              this.ButtonColor4 = Color.Red
            })
          Button('null')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = null
            })
            .focusOnTouch(true)
            .backgroundColor(this.ButtonColor5)
            .onFocus(() => {
              this.ButtonColor5 = Color.Red
            })
          Button('-1')
            .width('30%')
            .onClick(() => {
              this.menuPolicy = -1
            })
            .backgroundColor(this.ButtonColor6)
            .focusOnTouch(true)
            .onFocus(() => {
              this.ButtonColor6 = Color.Red
            })
        }.margin({ top: 5 })















      }

    }
  }
}