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
import matrix4 from '@ohos.matrix4'


@Entry
@Component
struct TextInput4740 {
  controller: TextInputController = new TextInputController()
  @State inputValue: string = ""
  @State colorAll: (Color | number | string | Resource)[] = [Color.White, Color.Pink, 0x008000 ,'rgb(255,0,0)', '#0000ff', Color.Brown, $r('app.color.color_yellow')]
  @State decorationType: TextDecorationType[] = [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State type: InputType[] = [InputType.Normal, InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber, InputType.USER_NAME, InputType.NEW_PASSWORD]
  @State typeStr: string[] = ['Normal', 'Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'SCREEN_LOCK_PASSWORD', 'USER_NAME', 'NEW_PASSWORD']
  @State inputIndex: number = 0
  @State style: TextContentStyle = TextContentStyle.DEFAULT
  @State textAlign: TextAlign[] = [TextAlign.Start, TextAlign.Center, TextAlign.End]
  @State textAlignStr: string[] = ['Start', 'Center', 'End']
  @State textAlignIndex: number = 0
  @State fontSize:number = 16
  @State placeholderFontSize:number = 16
  @State showUnderline: boolean = false
  @State letterSpacing: (number | string | Resource)[] = [-2, 0, 3, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State lineHeight: (number | string | Resource)[] = [-5, 0, 10, 20, '40vp', '30%']
  @State lineHeightIndex: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 250
  @State paddingTest: number = 0
  @State sizeAll: (number | string | Resource | undefined)[] = [-1, 0, 20, 'hsp', undefined, '20px', '10abc', $r('app.string.number_20px'), $r('app.string.number_10abc')]
  @State fontWeight: (FontWeight | number | undefined | string)[] = [100,200,300,400,500,600,700,800,900,0,1000,undefined,'205abc',FontWeight.Lighter,FontWeight.Normal,FontWeight.Regular,FontWeight.Medium,FontWeight.Bold,FontWeight.Bolder]
  @State fontWeightStr: string[] = ['100','200','300','400','500','600','700','800','900','0','1000', 'undefined','205abc', 'Lighter','Normal','Regular','Medium','Bold','Bolder']
  @State fontWeightIndex: number = 3
  @State textIndent: Dimension[] = [2, '5vp', '10%', $r('app.string.size')]
  @State textIndentIndex: number = 0
  @State isShow: boolean = false
  @State scaleX: number = 1
  @State scaleY: number = 1
  @State scaleZ: number = 1
  @State scaleCenterX: number = 50
  @State scaleCenterY: number = 50
  @State rotateX: number = 0
  @State rotateY: number = 0
  @State rotateZ: number = 0
  @State rotateCenterX: number = 50
  @State rotateCenterY: number = 50
  @State rotateAngle: number = 0
  @State translateX: number = 0
  @State translateY: number = 0
  @State translateZ: number = 0

  @State scaleX2: number = 1
  @State scaleY2: number = 1
  @State scaleZ2: number = 1
  @State scaleCenterX2: number = 50
  @State scaleCenterY2: number = 50
  @State rotateX2: number = 0
  @State rotateY2: number = 0
  @State rotateZ2: number = 0
  @State rotateCenterX2: number = 50
  @State rotateCenterY2: number = 50
  @State rotateAngle2: number = 0
  @State translateX2: number = 0
  @State translateY2: number = 0
  @State translateZ2: number = 0

  @State marginTest: number = 0
  @State borderWeight: number = 1
  @State colorIndex: number = 0
  @State caretWidth: number = 1

  build() {
    Column() {
      TextInput()
      if (this.isShow) {
        TextInput({ controller: this.controller, text: this.inputValue ,placeholder:'input your word...'})
          .onChange((value: string) => {
            this.inputValue = value
          })
          .decoration({
            type: this.decorationType[this.typeIndex],
            color: this.colorAll[this.decorationColor]
          }).margin({ top: 10 })
          .type(this.type[this.inputIndex])
          .textAlign(this.textAlign[this.textAlignIndex])
          .style(this.style)
          .fontSize(this.fontSize)
          .fontWeight(this.fontWeight[this.fontWeightIndex])
          .textIndent(this.textIndent[this.textIndentIndex])
          .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
          .lineHeight(this.lineHeight[this.lineHeightIndex])
          .width(this.widthTest)
          .height(this.heightTest)
          .padding(this.paddingTest)
          .borderWidth(this.borderWeight)
          .margin(this.marginTest)
          .caretStyle({
            width: this.caretWidth
          })
          .backgroundColor(this.colorAll[this.colorIndex])
          .placeholderFont({ size: this.placeholderFontSize })
          .translate({
            x: this.translateX,
            y: this.translateY,
            z: this.translateZ,
          })
          .rotate({
            x: this.rotateX,
            y: this.rotateY,
            z: this.rotateZ,
            centerX: this.rotateCenterX + '%',
            centerY: this.rotateCenterY + '%',
            angle: this.rotateAngle
          })
          .scale({
            x: this.scaleX,
            y: this.scaleY,
            z: this.scaleZ,
            centerX: this.scaleCenterX + '%',
            centerY: this.scaleCenterY + '%'
          })
          .transform(matrix4.identity()
            .translate({
              x: this.translateX2,
              y: this.translateY2,
              z: this.translateZ2,
            })
            .scale({
              x: this.scaleX2,
              y: this.scaleY2,
              z: this.scaleZ2
            })
            .rotate({
              x: this.rotateX2,
              y: this.rotateY2,
              z: this.rotateZ2,
              angle: this.rotateAngle2
            }))
      } else {
        TextInput({ controller: this.controller, text: this.inputValue ,placeholder:'input your word...'})
          .onChange((value: string) => {
            this.inputValue = value
          })
          .decoration({
            type: this.decorationType[this.typeIndex],
            color: this.colorAll[this.decorationColor]
          }).margin({ top: 10 })
          .type(this.type[this.inputIndex])
          .textAlign(this.textAlign[this.textAlignIndex])
          .style(this.style)
          .fontSize(this.fontSize)
          .fontWeight(this.fontWeight[this.fontWeightIndex])
          .textIndent(this.textIndent[this.textIndentIndex])
          .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
          .lineHeight(this.lineHeight[this.lineHeightIndex])
          .padding(this.paddingTest)
          .borderWidth(this.borderWeight)
          .margin(this.marginTest)
          .caretStyle({
            width: this.caretWidth
          })
          .backgroundColor(this.colorAll[this.colorIndex])
          .placeholderFont({ size: this.placeholderFontSize })
          .translate({
            x: this.translateX,
            y: this.translateY,
            z: this.translateZ,
          })
          .rotate({
            x: this.rotateX,
            y: this.rotateY,
            z: this.rotateZ,
            centerX: this.rotateCenterX + '%',
            centerY: this.rotateCenterY + '%',
            angle: this.rotateAngle
          })
          .scale({
            x: this.scaleX,
            y: this.scaleY,
            z: this.scaleZ,
            centerX: this.scaleCenterX + '%',
            centerY: this.scaleCenterY + '%'
          })
          .transform(matrix4.identity()
            .translate({
              x: this.translateX2,
              y: this.translateY2,
              z: this.translateZ2,
            })
            .scale({
              x: this.scaleX2,
              y: this.scaleY2,
              z: this.scaleZ2
            })
            .rotate({
              x: this.rotateX2,
              y: this.rotateY2,
              z: this.rotateZ2,
              angle: this.rotateAngle2
            }))
      }





      Scroll() {
        Column() {

          Row() {
            Button('不设置宽高')
              .width('40%')
              .onClick(() => {
                this.isShow = false
              })

            Button('设置宽高')
              .width('40%')
              .onClick(() => {
                this.isShow = true
              })

          }.margin({ top: 5 })

          Row() {
            Button('scaleX+,' + this.scaleX)
              .width('40%')
              .onClick(() => {
                this.scaleX += 0.5
              })

            Button('scaleX-,' + this.scaleX)
              .width('40%')
              .onClick(() => {
                this.scaleX -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleY+,' + this.scaleY)
              .width('40%')
              .onClick(() => {
                this.scaleY += 0.5
              })

            Button('scaleY-,' + this.scaleY)
              .width('40%')
              .onClick(() => {
                this.scaleY -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleZ+,' + this.scaleZ)
              .width('40%')
              .onClick(() => {
                this.scaleZ += 0.5
              })

            Button('scaleZ-,' + this.scaleZ)
              .width('40%')
              .onClick(() => {
                this.scaleZ -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleCenterX+,' + this.scaleCenterX + '%')
              .width('40%')
              .onClick(() => {
                this.scaleCenterX += 10
              })

            Button('scaleCenterX-,' + this.scaleCenterX + '%')
              .width('40%')
              .onClick(() => {
                this.scaleCenterX -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleCenterY+,' + this.scaleCenterY + '%')
              .width('40%')
              .onClick(() => {
                this.scaleCenterY += 10
              })

            Button('scaleCenterY-,' + this.scaleCenterY + '%')
              .width('40%')
              .onClick(() => {
                this.scaleCenterY -= 10
              })
          }.margin({ top: 5 })

          // rotate
          Row() {
            Button('rotateX+,' + this.rotateX)
              .width('40%')
              .onClick(() => {
                this.rotateX += 0.5
              })

            Button('rotateX-,' + this.rotateX)
              .width('40%')
              .onClick(() => {
                this.rotateX -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateY+,' + this.rotateY)
              .width('40%')
              .onClick(() => {
                this.rotateY += 0.5
              })

            Button('rotateY-,' + this.rotateY)
              .width('40%')
              .onClick(() => {
                this.rotateY -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateZ+,' + this.rotateZ)
              .width('40%')
              .onClick(() => {
                this.rotateZ += 0.5
              })

            Button('rotateZ-,' + this.rotateZ)
              .width('40%')
              .onClick(() => {
                this.rotateZ -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateCenterX+,' + this.rotateCenterX + '%')
              .width('40%')
              .onClick(() => {
                this.rotateCenterX += 10
              })

            Button('rotateCenterX-,' + this.rotateCenterX + '%')
              .width('40%')
              .onClick(() => {
                this.rotateCenterX -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateCenterY+,' + this.rotateCenterY + '%')
              .width('40%')
              .onClick(() => {
                this.rotateCenterY += 10
              })

            Button('rotateCenterY-,' + this.rotateCenterY + '%')
              .width('40%')
              .onClick(() => {
                this.rotateCenterY -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateAngle+,' + this.rotateAngle)
              .width('40%')
              .onClick(() => {
                this.rotateAngle += 100
              })

            Button('rotateAngle-,' + this.rotateAngle)
              .width('40%')
              .onClick(() => {
                this.rotateAngle -= 100
              })
          }.margin({ top: 5 })

          // translate
          Row() {
            Button('translateX+,' + this.translateX)
              .width('40%')
              .onClick(() => {
                this.translateX += 10
              })

            Button('translateX-,' + this.translateX)
              .width('40%')
              .onClick(() => {
                this.translateX -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('translateY+,' + this.translateY)
              .width('40%')
              .onClick(() => {
                this.translateY += 10
              })

            Button('translateY-,' + this.translateY)
              .width('40%')
              .onClick(() => {
                this.translateY -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('translateZ+,' + this.translateZ)
              .width('40%')
              .onClick(() => {
                this.translateZ += 10
              })

            Button('translateZ-,' + this.translateZ)
              .width('40%')
              .onClick(() => {
                this.translateZ -= 10
              })
          }.margin({ top: 5 })

          // transform
          Text('transform:').margin({ top: 5 })
          Row() {
            Button('scaleX+,' + this.scaleX2)
              .width('40%')
              .onClick(() => {
                this.scaleX2 += 0.5
              })

            Button('scaleX-,' + this.scaleX2)
              .width('40%')
              .onClick(() => {
                this.scaleX2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleY+,' + this.scaleY2)
              .width('40%')
              .onClick(() => {
                this.scaleY2 += 0.5
              })

            Button('scaleY-,' + this.scaleY2)
              .width('40%')
              .onClick(() => {
                this.scaleY2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('scaleZ+,' + this.scaleZ2)
              .width('40%')
              .onClick(() => {
                this.scaleZ2 += 0.5
              })

            Button('scaleZ-,' + this.scaleZ2)
              .width('40%')
              .onClick(() => {
                this.scaleZ2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateX+,' + this.rotateX2)
              .width('40%')
              .onClick(() => {
                this.rotateX2 += 0.5
              })

            Button('rotateX-,' + this.rotateX2)
              .width('40%')
              .onClick(() => {
                this.rotateX2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateY+,' + this.rotateY2)
              .width('40%')
              .onClick(() => {
                this.rotateY2 += 0.5
              })

            Button('rotateY-,' + this.rotateY2)
              .width('40%')
              .onClick(() => {
                this.rotateY2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateZ+,' + this.rotateZ2)
              .width('40%')
              .onClick(() => {
                this.rotateZ2 += 0.5
              })

            Button('rotateZ-,' + this.rotateZ2)
              .width('40%')
              .onClick(() => {
                this.rotateZ2 -= 0.5
              })
          }.margin({ top: 5 })

          Row() {
            Button('rotateAngle+,' + this.rotateAngle2)
              .width('40%')
              .onClick(() => {
                this.rotateAngle2 += 100
              })

            Button('rotateAngle-,' + this.rotateAngle2)
              .width('40%')
              .onClick(() => {
                this.rotateAngle2 -= 100
              })
          }.margin({ top: 5 })

          Row() {
            Button('translateX+,' + this.translateX2)
              .width('40%')
              .onClick(() => {
                this.translateX2 += 10
              })

            Button('translateX-,' + this.translateX2)
              .width('40%')
              .onClick(() => {
                this.translateX2 -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('translateY+,' + this.translateY2)
              .width('40%')
              .onClick(() => {
                this.translateY2 += 10
              })

            Button('translateY-,' + this.translateY2)
              .width('40%')
              .onClick(() => {
                this.translateY2 -= 10
              })
          }.margin({ top: 5 })

          Row() {
            Button('translateZ+,' + this.translateZ2)
              .width('40%')
              .onClick(() => {
                this.translateZ2 += 10
              })

            Button('translateZ-,' + this.translateZ2)
              .width('40%')
              .onClick(() => {
                this.translateZ2 -= 10
              })
          }.margin({ top: 5 })


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

          Row() {
            Button('placeholderFontSize+,' + this.placeholderFontSize)
              .width('40%')
              .onClick(() => {
                this.placeholderFontSize += 5
              })

            Button('placeholderFontSize-,' + this.placeholderFontSize)
              .width('40%')
              .onClick(() => {
                this.placeholderFontSize -= 5
              })
          }.margin({ top: 5 })

          Row() {
            Button('fontWeight:' + this.fontWeightStr[this.fontWeightIndex])
              .width('40%')
              .onClick(() => {
                this.fontWeightIndex = (this.fontWeightIndex + 1) % this.fontWeight.length
              })

            Button('textIndent:' + this.textIndent[this.textIndentIndex])
              .width('40%')
              .onClick(() => {
                this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
              })
          }.margin({ top: 5 })

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
          }.margin({ top: 5 })

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
          }.margin({ top: 5 })

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
          }.margin({ top: 5 })

          Row() {
            Button('margin+,' + this.marginTest)
              .width('40%')
              .onClick(() => {
                this.marginTest += 5
              })

            Button('margin-,' + this.marginTest)
              .width('40%')
              .onClick(() => {
                this.marginTest -= 5
              })
          }.margin({ top: 5 })

          Row() {
            Button('borderWidth+,' + this.borderWeight)
              .width('40%')
              .onClick(() => {
                this.borderWeight += 2
              })

            Button('borderWidth-,' + this.borderWeight)
              .width('40%')
              .onClick(() => {
                this.borderWeight -= 2
              })
          }.margin({ top: 5 })

          Row() {
            Button('backgroundColor+,' + this.colorAll[this.colorIndex])
              .width('80%')
              .onClick(() => {
                this.colorIndex = (this.colorIndex + 1) % this.colorAll.length
              })
          }.margin({ top: 5 })

          Row() {
            Button('caretWidth+,' + this.caretWidth)
              .width('40%')
              .onClick(() => {
                this.caretWidth += 1
              })

            Button('caretWidth-,' + this.caretWidth)
              .width('40%')
              .onClick(() => {
                this.caretWidth -= 1
              })
          }.margin({ top: 5 })



















        }.padding({ bottom: 150 })
      }.margin({ top:50 }).height('60%')

    }
  }
}