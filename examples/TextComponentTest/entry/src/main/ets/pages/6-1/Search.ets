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
struct Search50019 {
  controller: SearchController = new SearchController()
  @State inputValue: string = ""
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
  @State maxLength: number = 50
  @State letterSpacing: (number | string | Resource)[] = [-2, 0, 3, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State lineHeight: (number | string | Resource)[] = [-5, 0, 10, 20, '40vp', '30%']
  @State lineHeightIndex: number = 0

  build() {
    Column() {
      Text('decoration、letterSpacing不设置').margin({ top: 10 })
      Search()  .searchButton('search')
      Search({ controller: this.controller, value: this.inputValue ,placeholder:'input your word...'})
        .onChange((value: string) => {
          this.inputValue = value
        })
        .decoration(
          {
            type: this.decorationType[this.typeIndex],
            color: this.colorAll[this.decorationColor]
          }
        ).margin({ top: 10 })
        .type(this.type[this.inputIndex])
        .textAlign(this.textAlign[this.textAlignIndex])
        .textFont({ size:this.fontSize })
        .maxLength(this.maxLength)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .lineHeight(this.lineHeight[this.lineHeightIndex])
        .searchButton('搜索')

      Scroll() {
        Column() {
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
          }.margin({ top: 5 })

          // Row() {
          //   Button('不设置修饰线颜色')
          //     .width('40%')
          //     .onClick(() => {
          //       this.decoration = {type: this.decorationType[this.typeIndex]}
          //     })
          //
          //   Button('设置修饰线颜色')
          //     .width('40%')
          //     .onClick(() => {
          //       this.decoration = {type: this.decorationType[this.typeIndex]}
          //     })
          // }.margin({ top: 5 })

          Row() {
            Button('type:' + this.typeStr[this.inputIndex])
              .width('40%')
              .onClick(() => {
                this.inputIndex = (this.inputIndex + 1) % this.type.length
              })

            Button('textAlign:' + this.textAlignStr[this.textAlignIndex])
              .width('40%')
              .onClick(() => {
                this.textAlignIndex = (this.textAlignIndex + 1) % this.textAlign.length

              })
          }.margin({ top: 5 })



          Row() {
            Button('fontSize+,' + this.fontSize)
              .width('40%')
              .onClick(() => {
                this.fontSize += 5
              })

            Button('fontSize-,' + this.fontSize)
              .width('40%')
              .onClick(() => {
                this.fontSize -= 5
              })
          }.margin({ top: 5 })


          Row(){
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
          }.margin({ top: 5 })

          Row() {
            Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
              .width('40%')
              .onClick(() => {
                this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
              })

            Button('lineHeight:' + this.lineHeight[this.lineHeightIndex])
              .width('40%')
              .onClick(() => {
                this.lineHeightIndex = (this.lineHeightIndex + 1) % this.lineHeight.length
              })

          }.margin({ top: 5 })
























        }
      }.margin({ top:50 }).height('60%')

    }
  }
}