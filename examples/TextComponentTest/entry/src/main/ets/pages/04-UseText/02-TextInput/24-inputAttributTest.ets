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

import { router } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit';
import font from '@ohos.font';
@Entry
@Component
struct TextInputSR20240201979716 {
  @State text: string = ''
  @State text1: string = ''
  @State textOverflow: (TextOverflow | undefined | null)[] = [TextOverflow.Clip, TextOverflow.None, TextOverflow.Ellipsis, TextOverflow.MARQUEE, undefined, null]
  @State textOverflowStr: string[] = ['Clip', 'None', 'Ellipsis', 'MARQUEE', 'undefined', 'null']
  @State textOverflowIndex: number = 0
  @State maxLines: number = 2
  @State type: InputType[] = [InputType.Normal, InputType.URL,InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber,InputType.NUMBER_PASSWORD ,InputType.USER_NAME, InputType.NEW_PASSWORD,InputType.NUMBER_DECIMAL]
  @State typeStr: string[] = ['Normal', 'URL','Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'USER_NAME', 'NEW_PASSWORD','NUMBER_DECIMAL']
  @State inputIndex: number = 0
  @State style: TextContentStyle[] = [TextContentStyle.DEFAULT,TextContentStyle.INLINE]
  @State styleStr: string[] = ['DEFAULT','INLINE']
  @State styleIndex: number = 0
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakStr: string[] = ['NORMAL', 'BREAK_ALL', 'BREAK_WORD']
  @State wordBreakIndex: number = 2
  @State textIndent: Dimension[] = [ 0,0.9, 10, 40,500, '15vp', '15px','40%', '50%', $r('app.string.size')]
  @State textIndentIndex: number = 0
  @State paddingTest: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 300
  @State letterSpacing: (number | string | Resource)[] = [-10, 0, 10, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State value: string = ''
  @State value1: string = ''
  @State color: string[] = ['rgba(0,0,0,0.4)', 'rgba(243, 11, 11, 1)', 'rgba(11, 234, 33, 0.98)', 'rgba(7, 122, 245, 0.98)', 'rgba(0,0,0,1)']
  @State selectedBackgroundColor: number = 0
  @State selectionStart: number = 0
  @State selectionEnd: number = 0
  @State caretColor: number = 1
  @State showUnderline: boolean[] = [false,true]
  @State showUnderlinestr: string[] = ['false','true']
  @State showUnderlineIndex: number = 0
  @State showCounter: boolean[] = [true,false]
  @State showCounterstr: string[] = ['true','false']
  @State showCounterIndex: number = 0
  @State fontSize: number = 16
  @State enterkeytype: EnterKeyType[] = [EnterKeyType.Go,EnterKeyType.Search,EnterKeyType.Send,EnterKeyType.Next,EnterKeyType.Done,EnterKeyType.PREVIOUS,EnterKeyType.NEW_LINE]
  @State enterkeytypeStr: string[] = ['Go','Search','Send','Next','Done','PREVIOUS','NEW_LINE']
  @State enterkeytypeIndex: number = 0
  @State positionInfo: CaretOffset = { index: 0, x: 0, y: 0 }
  @State TextAlign: TextAlign[] = [TextAlign.Start,TextAlign.Center,TextAlign.End,TextAlign.JUSTIFY]
  @State TextAlignStr: string[] = ["Start", "Center", "End", "JUSTIFY"]
  @State TextAlignIndex: number = 0
  @State cancelButon: CancelButtonStyle[] = [CancelButtonStyle.INPUT,CancelButtonStyle.CONSTANT,CancelButtonStyle.INVISIBLE]
  @State cancelButonStr: string[] = ["INPUT", "CONSTANT", "INVISIBLE"]
  @State cancelButonIndex: number = 0
  controller: TextInputController = new TextInputController()
  controller1: TextInputController = new TextInputController()
  @State copyOption: CopyOptions[] = [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ["None", "InApp", "LocalDevice", "CROSS_DEVICE"]
  @State copyOptionIndex: number = 1
  @State showPasswordIcon: boolean = true
  @State caretPosition: number = 0
  @State PassWordSrc1: Resource = $r('app.media.22')
  @State PassWordSrc2: Resource = $r('app.media.81')
  @State selectionMenuHidden: boolean = false
  @State barState: BarState[] = [BarState.Off, BarState.Auto, BarState.On]
  @State barStateStr: string[] = ["Off", "Auto", "On"]
  @State barStateIndex: number = 0;
  @State selectAll: boolean = false
  @State lineHeight: number = 20
  @State textDecorationType: TextDecorationType[] = [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.Overline, TextDecorationType.LineThrough]
  @State textDecorationTypeStr: string[] = ["None", "Underline", "Overline", "LineThrough"]
  @State textDecorationTypeIndex: number = 0
  @State textDecorationStyle: TextDecorationStyle[] = [TextDecorationStyle.SOLID, TextDecorationStyle.DOUBLE, TextDecorationStyle.DOTTED, TextDecorationStyle.DASHED, TextDecorationStyle.WAVY]
  @State textDecorationStyleStr: string[] = ["SOLID", "DOUBLE", "DOTTED", "DASHED", "WAVY"]
  @State textDecorationStyleIndex: number = 0
  @State showPassword: boolean = true
  @State enterKeyType: EnterKeyType[] = [EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Next, EnterKeyType.Done, EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE]
  @State enterKeyTypeStr: string[] = ["Go", "Search", "Send", "Next", "Done", "PREVIOUS", "NEW_LINE"]
  @State enterKeyTypeIndex: number = 0
  @State isEditing: boolean = true
  @State totalOffsetX: number = 0
  @State totalOffsetY: number = 0
  @State passwordState: boolean = false
  @State selectIndex: number = 0
  @State selectValue: string[] = ['KB', 'MB', 'GB', 'TB']

  aboutToAppear() {
    font.registerFont({
      familyName: '新字体',
      familySrc: $rawfile('founderfont.ttf')
    })
  }



  @Builder itemEnd() {
    Select([{ value: 'KB' },
      { value: 'MB' },
      { value: 'GB' },
      { value: 'TB', }])
      .height("48vp")
      .borderRadius(0)
      // .selected(0)
      .align(Alignment.Center)
      .value(this.selectValue[this.selectIndex])
      .font({ size: 20, weight: 500 })
      .fontColor('#182431')
      .selectedOptionFont({ size: 20, weight: 400 })
      .optionFont({ size: 20, weight: 400 })
      .backgroundColor(Color.Transparent)
      .responseRegion({ height: "40vp", width: "80%", x: '10%', y: '6vp' })
      .onSelect((index: number) => {
        this.selectIndex = index
        console.info('Select:' + index)
      })
  }


  build() {
    Column({ space: 5 }) {
      Button('back')
        .margin(5)
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          console.info(`Succeeded in clicking the 'Back' button.`)
          try {
            // 返回第一页
            router.back()
            console.info('Succeeded in returning to the first page.')
          } catch (err) {
            let code = (err as BusinessError).code;
            let message = (err as BusinessError).message;
            console.error(`Failed to return to the first page. Code is ${code}, message is ${message}`)
          }
        })
      // Text('普通输入框，URL模式')
      TextInput({text: this.value,placeholder:'TextInput组件。。', controller:this.controller1})
        .width('80%').height(50)
        .cancelButton({style:CancelButtonStyle.INPUT,icon:{color: Color.Red}})
        .fontWeight('10fp')
        .margin({bottom:20})
        .onChange((value: string) => {
          this.value = value
        })
        .maxLength(100)
        .showCounter(true)
        .showUnderline(true)

      Button('Set caretPosition 1')
        .margin(5)
        .onClick(() => {
          // 将光标移动至第一个字符后
          this.controller1.caretPosition(1)
        })
      Button('Get CaretOffset')
        .margin(5)
        .onClick(() => {
          this.positionInfo = this.controller1.getCaretOffset()
        })


      Text(this.text)

      // Text('天將降大任于斯人也，必先苦其心志，劳其筋骨，饿其体肤，空乏其身，行拂乱其所为，所以动心忍性，增益其所不能。')
      //   .width(300).height(100)
      //   .maxLines(this.maxLines).textOverflow({overflow:TextOverflow.Ellipsis})
      //   .textIndent(this.textIndent[this.textIndentIndex])
      //   .borderWidth(2)
      //   .copyOption(CopyOptions.InApp)
      //   .clip(true)
      Text('属性测试')
      TextInput({ text: this.value1 , placeholder:'input your word....', controller: this.controller})
        .textAlign(this.TextAlign[this.TextAlignIndex])
        // .borderWidth(2)
        .enablePreviewText(true)
        .fontSize(this.fontSize)
        // .caretPosition(this.caretPosition)
          // .minFontSize(10)
          // .maxFontSize(20)
        .showError('错误提示文本')
        .showCounter(this.showCounter[this.showCounterIndex])
        .maxLength(100)
        .textOverflow(this.textOverflow[this.textOverflowIndex])
        .maxLines(this.maxLines)
        .type(this.type[this.inputIndex])
        .style(this.style[this.styleIndex])
        .wordBreak(this.wordBreak[this.wordBreakIndex])
        .cancelButton({style:this.cancelButon[this.cancelButonIndex],icon:{color: Color.Red}})
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.color[this.selectedBackgroundColor])
        .caretColor(this.color[this.caretColor])
        .padding(this.paddingTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .enterKeyType(this.enterkeytype[this.enterkeytypeIndex])
        .onChange((value: string) => {
          this.value1 = value
        })
        .showUnderline(this.showUnderline[this.showUnderlineIndex])
        .copyOption(this.copyOption[this.copyOptionIndex])
        .showPasswordIcon(this.showPasswordIcon)
        .showUnit(this.itemEnd)
        .underlineColor({normal:Color.Orange,typing:Color.Green,error:Color.Red,disable:Color.Gray})
        .passwordIcon({ onIconSrc: this.PassWordSrc1, offIconSrc: this.PassWordSrc2 })
        .selectionMenuHidden(this.selectionMenuHidden)
        .barState(this.barState[this.barStateIndex])
        .selectAll(this.selectAll)
        .lineHeight(this.lineHeight)
        .decoration({type: this.textDecorationType[this.textDecorationTypeIndex], color: Color.Red, style: this.textDecorationStyle[this.textDecorationStyleIndex]})
        .showPassword(this.passwordState)
        .onSubmit((enterKey: EnterKeyType) => {
          console.log("this.EnterKeyType:" + enterKey)
        })
        .onEditChange((isEditing: boolean) => {
          this.isEditing = isEditing
          console.log("this.isEditing:" + this.isEditing)
        })
        .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
          this.selectionStart = selectionStart
          this.selectionEnd = selectionEnd
          console.log("zyl: 起始位置:" + selectionStart +  "     终点位置: " + selectionEnd)
        })
        .onContentScroll((totalOffsetX: number, totalOffsetY: number) => {
          this.totalOffsetX = totalOffsetX
          this.totalOffsetY = totalOffsetY
          console.log("totalOffsetX:" + totalOffsetX +  "     totalOffsetY " + totalOffsetY)
        })
        .onSecurityStateChange(((isShowPassword: boolean) => {
          // 更新密码显示状态
          console.info('isShowPassword',isShowPassword)
          this.passwordState = isShowPassword
        }))




      Scroll() {
        Column() {
          Row(){

            Button("stopEditing")
              .width('40%')
              .onClick(() => {
                this.controller.stopEditing()
              })

            Button("Decoration：" + this.textDecorationTypeStr[this.textDecorationTypeIndex])
              .width('40%')
              .onClick(() => {
                this.textDecorationTypeIndex ++
                if (this.textDecorationTypeIndex > (this.textDecorationTypeStr.length - 1)) {
                  this.textDecorationTypeIndex = 0
                }
              })
          }

          Row(){
            Button('selectAll：' + this.selectAll)
              .width('40%')
              .onClick(() => {
                this.selectAll = !this.selectAll
              })
            Button('showPassword：' + this.passwordState)
              .width('40%')
              .onClick(() => {
                this.passwordState = !this.passwordState
              })
          }
          Row(){
            Button('lineHeight+：' + this.lineHeight)
              .width('40%')
              .onClick(() => {
                this.lineHeight += 5
              })

            Button('lineHeight-：' + this.lineHeight)
              .width('40%')
              .onClick(() => {
                this.lineHeight -= 5
              })
          }
          Row(){
            Button('selectionMenuHidden:' + this.selectionMenuHidden)
              .width('40%')
              .onClick(() => {
                this.selectionMenuHidden = !this.selectionMenuHidden
              })

            Button("barState:" + this.barStateStr[this.barStateIndex])
              .width('40%')
              .onClick(() => {
                this.barStateIndex ++
                if (this.barStateIndex > (this.barStateStr.length - 1)) {
                  this.barStateIndex = 0
                }
              })
          }

          Row(){
            Button("CopyOption:" + this.copyOptionStr[this.copyOptionIndex])
              .width('40%')
              .onClick(() => {
                this.copyOptionIndex ++
                if (this.copyOptionIndex > (this.copyOptionStr.length - 1)) {
                  this.copyOptionIndex = 0
                }
              })

            Button("showPasswordIcon:" + this.showPasswordIcon)
              .width('40%')
              .onClick(() => {
                this.showPasswordIcon = !this.showPasswordIcon
              })

          }

          Row(){
            Button("caretPosition+:" + this.caretPosition)
              .width('40%')
              .onClick(() => {
                this.caretPosition ++
                this.controller.caretPosition(this.caretPosition)
              })

            Button("caretPosition-:" + this.caretPosition)
              .width('40%')
              .onClick(() => {
                this.caretPosition --
                this.controller.caretPosition(this.caretPosition)
              })
          }

          Row(){
            Button('fontSize+:' + this.fontSize).onClick((event: ClickEvent) => {
              this.fontSize += 2
            }).margin(2)
              .width('40%')
            Button('fontSize-:' + this.fontSize).onClick((event: ClickEvent) => {
              this.fontSize -= 2
            }).margin(2)
              .width('40%')
          }
          Row(){
            Button('selectionStart+,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart += 1
                this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
              }).margin(2)

            Button('selectionStart-,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart -= 1
                this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
              }).margin(2)


          }

          Row() {
            Button('selectionEnd+,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd += 1
                this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
              }).margin(2)

            Button('selectionEnd-,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd -= 1
                this.controller.setTextSelection(this.selectionStart, this.selectionEnd)
              }).margin(2)
          }

          Row() {
            Button('setTextSelection')
              .width('40%')
              .onClick(() => {
                this.controller.setTextSelection(this.selectionStart,this.selectionEnd)
              }).margin(2)


            Button('showUnderLine:' + this.showUnderlinestr[this.showUnderlineIndex])
              .width('40%')
              .onClick(() => {
                this.showUnderlineIndex = (this.showUnderlineIndex + 1) % this.showUnderline.length
              }).margin(2)
          }


          Row() {
            Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
              .width('40%')
              .onClick(() => {
                this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              }).margin(2)

            Button('type:' + this.typeStr[this.inputIndex])
              .width('40%')
              .onClick(() => {
                this.inputIndex = (this.inputIndex + 1) % this.type.length
              }).margin(2)
          }

          Row() {
            Button('maxLines+,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines += 1
              }).margin(2)

            Button('maxLines-,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines -= 1
              }).margin(2)
          }

          Row() {
            Button('Style：' + this.styleStr[this.styleIndex]).onClick(() => {
              this.styleIndex ++
              if (this.styleIndex > (this.styleStr.length - 1)) {
                this.styleIndex = 0
              }
            }).margin(2)

            Button('enterKeyType：' + this.enterkeytypeStr[this.enterkeytypeIndex]).onClick(() => {
              this.enterkeytypeIndex ++
              if (this.enterkeytypeIndex > (this.enterkeytypeStr.length - 1)) {
                this.enterkeytypeIndex = 0
              }
            }).margin(2)

          }

          Row() {

            Button('textIndent:' + this.textIndent[this.textIndentIndex])
              .width('40%')
              .onClick(() => {
                this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
              }).margin(2)

            Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
              .width('40%')
              .onClick(() => {
                this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
              }).margin(2)
          }

          Row() {
            Button('padding+,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest += 10
              }).margin(2)

            Button('padding-,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest -= 10
              }).margin(2)
          }

          Row() {
            Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
              .width('40%')
              .onClick(() => {
                this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
              }).margin(2)

            Button('底板颜色:' + this.color[this.selectedBackgroundColor])
              .width('40%')
              .onClick(() => {
                this.selectedBackgroundColor ++
                if (this.selectedBackgroundColor > (this.color.length - 1)) {
                  this.selectedBackgroundColor = 0
                }
              }).margin(2)

          }

          Row() {

            Button('caretColor:' + this.color[this.caretColor])
              .width('40%')
              .onClick(() => {
                this.caretColor ++
                if (this.caretColor > (this.color.length - 1)) {
                  this.caretColor = 0
                }
              }).margin(2)

            Button('TextAlign:' + this.TextAlignStr[this.TextAlignIndex])
              .width('40%')
              .onClick(() => {
                this.TextAlignIndex ++
                if (this.TextAlignIndex > (this.TextAlignStr.length - 1)) {
                  this.TextAlignIndex = 0
                }
              })
          }

          Row() {
            Button('height+,' + this.heightTest)
              .width('40%')
              .onClick(() => {
                this.heightTest += 10
              }).margin(2)

            Button('height-,' + this.heightTest)
              .width('40%')
              .onClick(() => {
                this.heightTest -= 10
              }).margin(2)
          }

          Row() {
            Button('width+,' + this.widthTest)
              .width('40%')
              .onClick(() => {
                this.widthTest += 10
              }).margin(2)

            Button('width-,' + this.widthTest)
              .width('40%')
              .onClick(() => {
                this.widthTest -= 10
              }).margin(2)
          }
          Row() {
            Button('CancelButtonStyle: ' + this.cancelButonStr[this.cancelButonIndex])
              .width('40%')
              .onClick(() => {
                this.cancelButonIndex ++
                if (this.cancelButonIndex > (this.cancelButonStr.length - 1)) {
                  this.cancelButonIndex = 0
                }
              })

            Button('showCounter:' + this.showCounterstr[this.showCounterIndex])
              .width('40%')
              .onClick(() => {
                this.showCounterIndex = (this.showCounterIndex + 1) % this.showCounterstr.length
              }).margin(2)
          }
        }.padding({ bottom:150 })
      }.height('40%').margin(5)

    }
    .width('100%')
    .height('100%')
  }
}