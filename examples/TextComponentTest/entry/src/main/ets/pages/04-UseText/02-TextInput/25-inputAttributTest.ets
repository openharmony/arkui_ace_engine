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

import font from '@ohos.font';
import { SymbolGlyphModifier } from '@kit.ArkUI';

@Entry
@Component
struct TextInputSR20240201979716 {
  @State text: string = ''
  @State text1: string = ''
  @State textOverflow: (TextOverflow | undefined | null)[] = [TextOverflow.Clip, TextOverflow.None, TextOverflow.Ellipsis, TextOverflow.MARQUEE, undefined, null]
  @State textOverflowStr: string[] = ['Clip', 'None', 'Ellipsis', 'MARQUEE', 'undefined', 'null']
  @State textOverflowIndex: number = 0
  @State maxLines: number = 2
  @State type: InputType[] = [InputType.Normal, InputType.URL,InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber,InputType.NUMBER_PASSWORD ,InputType.USER_NAME, InputType.NEW_PASSWORD,InputType.NUMBER_DECIMAL,InputType.ONE_TIME_CODE]
  @State typeStr: string[] = ['Normal', 'URL','Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'USER_NAME', 'NEW_PASSWORD','NUMBER_DECIMAL','ONE_TIME_CODE']
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
  @State marginTest: number = 0
  @State heightTest: number = 80
  @State lineheightTest: number = -1
  @State lineSpacingTest: number = -1
  @State widthTest: number = 300
  @State letterSpacing: (number | string | Resource)[] = [-10, 0, 10, '5px', '10%']
  @State letterSpacingIndex: number = 4
  @State value: string = ''
  @State value1: string = ''
  @State color: string[] = ['rgba(0,0,0,0.4)', 'rgba(243,  11, 11, 1)', 'rgba(11, 234, 33, 0.98)', 'rgba(7, 122, 245, 0.98)', 'rgba(0,0,0,1)']
  @State selectedBackgroundColor: number = 0
  @State selectionStart: number = 0
  @State selectionEnd: number = 0
  @State options:MenuPolicy =MenuPolicy.SHOW
  @State caretColor: number = 1
  @State caretWidth: number = -1
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
  @State Direction: Direction[] = [Direction.Auto,Direction.Ltr,Direction.Rtl]
  @State DirectionStr: string[] = ['Auto','Ltr','Rtl']
  @State DirectionIndex: number = 0
  @State ellipsisMode: (undefined|null|EllipsisMode)[] = [null,undefined,EllipsisMode.START,EllipsisMode.CENTER,EllipsisMode.END]
  @State ellipsisModeStr: string[] = ['null','undefined','START','CENTER','END']
  @State ellipsisModeIndex: number = 0
  @State halfleading: (boolean | undefined | null)[] = [false , true, undefined, null];
  @State halfleadingStr: string[] = ['false' , 'true', 'undefined', 'null'];
  @State halfleadingIndex: number = 0
  @State copyOption: CopyOptions[] = [ CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.None,CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = [ "InApp", "LocalDevice","None","CROSS_DEVICE"]
  @State copyOptionIndex: number = 0
  @State passwordState: boolean = false
  @State cancelButtonSize: number = -1
  @State minFontSize: number = 15
  @State maxFontSize: number = 15
  controller: TextInputController = new TextInputController()
  controller1: TextInputController = new TextInputController()
  @State selected: number = 2
  valueText: string[] = ['Kilogram','MB','GB','Centimeter' ]

  aboutToAppear() {
    font.registerFont({
      familyName: '新字体',
      familySrc: $rawfile('font4.ttf')
    })
  }



  @Builder itemEnd() {
    Select([
      { value: 'Kilogram' },
      { value: 'MB' },
      { value: 'GB' },
      { value: 'Centimeter', }])
      .height("48vp")
      .borderRadius(0)
      .selected(this.selected)
      .align(Alignment.Center)
      .value(this.valueText[this.selected])
      .font({ size: 20, weight: 500 })
      .fontColor('#182431')
      .selectedOptionFont({ size: 20, weight: 400 })
      .optionFont({ size: 20, weight: 400 })
      .backgroundColor(Color.Transparent)
      .responseRegion({
        height: "40vp",
        width: "80%",
        x: '10%',
        y: '6vp'
      })
      .onSelect((index: number) => {
        console.info('Select:' + index)
        this.selected = index
      })
  }

  build() {
    Column({ space: 5 }) {
      Text('普通输入框').fontSize('13vp')
      TextInput({text: this.value,placeholder:'请输入...', controller:this.controller1})
        .width(300)
        .height(50)
        .cancelButton({style:CancelButtonStyle.INPUT,icon:new SymbolGlyphModifier($r('sys.symbol.trash')).fontSize('16fp')})
        .fontWeight('10fp')
        // .fontFamily('新字体')
        .showPasswordIcon(false)
        .selectedBackgroundColor(Color.Red)
        .margin({bottom:20})
        .borderWidth(1)
        .borderColor(Color.Green)
        .padding(0)
        .type(InputType.Password)
        // .maxLength(20)
        .showError('错误状态')
        .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
        // .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
        // .style(this.style[this.styleIndex])
        .copyOption(CopyOptions.LocalDevice)
        .onChange((value: string) => {
          this.value = value
        })
        .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
          // event.keepEditableState()  //保持编辑态
          console.log(`asdfTextInput   EnterKeyType: ${enterKey},Text: ${event.text}`);

        })
        // .selectionMenuHidden(true)
        // .enabled(false)
        // .focusable(false)
        // .showPassword(false)
      // .showUnderline(true)

      // Button('Set caretPosition 1')
      //   .margin(5)
      //   .onClick(() => {
      //     // 将光标移动至第一个字符后
      //     this.controller1.caretPosition(1)
      //   })
      // Button('Get CaretOffset')
      //   .margin(5)
      //   .onClick(() => {
      //     this.positionInfo = this.controller1.getCaretOffset()
      //   })
      // Text(this.text).fontSize('13vp')



      Text("属性测试").fontSize('13vp').copyOption(CopyOptions.LocalDevice)
      TextInput({ text: this.value1 , placeholder:'这是提示文本', controller: this.controller})
        .showPassword(this.passwordState)
        .onSecurityStateChange(((isShowPassword: boolean) => {
          // 更新密码显示状态
          this.passwordState = isShowPassword
        }))
        .stopBackPress(false)
        .clip(false)
        .placeholderColor(Color.Green)
        .direction(this.Direction[this.DirectionIndex])
        .textAlign(this.TextAlign[this.TextAlignIndex])
        .borderWidth(1)
        .borderColor(Color.Green)
        .enablePreviewText(true)
        .fontSize(this.fontSize)
        .showUnit(this.itemEnd)
        // .showPassword(false)
        .copyOption(this.copyOption[this.copyOptionIndex])
        .decoration({type:TextDecorationType.Underline})
        .showError('错误提示文本')
          // .caretPosition(3)
          .minFontSize(this.minFontSize)
          .maxFontSize(this.maxFontSize)
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
        .showCounter(this.showCounter[this.showCounterIndex])
        .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
        .maxLength(50)
        // .inputFilter("[！@#￥%……&*]",(value:string) => {
        //
        // })
        .textOverflow(this.textOverflow[this.textOverflowIndex])
        .maxLines(this.maxLines)
        .type(this.type[this.inputIndex])
        .style(this.style[this.styleIndex])
        .wordBreak(this.wordBreak[this.wordBreakIndex])
        .cancelButton({style:this.cancelButon[this.cancelButonIndex],icon:{size:this.cancelButtonSize,color: Color.Red}})
        .textIndent(this.textIndent[this.textIndentIndex])
        .selectedBackgroundColor(this.color[this.selectedBackgroundColor])
        .caretStyle({color:Color.Red,width:this.caretWidth})
        .caretColor(this.color[this.caretColor])
        .padding(this.paddingTest)
        .margin(this.marginTest)
        .width(this.widthTest)
        .height(this.heightTest)
        .lineHeight(this.lineheightTest)
        .letterSpacing(this.letterSpacing[this.letterSpacingIndex])
        .enterKeyType(this.enterkeytype[this.enterkeytypeIndex])
        .showUnderline(this.showUnderline[this.showUnderlineIndex])
        .halfLeading(this.halfleading[this.halfleadingIndex])
        .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
        // .minFontScale(1)
        // .maxFontScale(1)
          .onChange((value: string) => {
            this.value1 = value
          })

        .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
          // 用户名不正确会清空输入框和用户名并提示错误文本

            // 调用keepEditableState方法，输入框保持编辑态
            event.keepEditableState()

        })

      // Text(this.text)





      Scroll() {
        Column() {
          Row(){
            Button("CopyOption:" + this.copyOptionStr[this.copyOptionIndex])

              .onClick(() => {
                this.copyOptionIndex ++
                if (this.copyOptionIndex > (this.copyOptionStr.length - 1)) {
                  this.copyOptionIndex = 0
                }
              }).width('40%').fontSize('13vp')

            Button('halfleading:' + this.halfleadingStr[this.halfleadingIndex]).onClick(() => {
              this.halfleadingIndex ++
              if (this.halfleadingIndex > (this.halfleadingStr.length - 1)) {
                this.halfleadingIndex = 0
              }
            }).width('40%').fontSize('13vp')
          }
          Row(){
            Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
              .width('40%')
              .onClick(() => {
                this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              }).margin(2).fontSize('13vp')


            Button('ellipsisMode:' + this.ellipsisModeStr[this.ellipsisModeIndex])
              .width('40%')
              .onClick(() => {
                this.ellipsisModeIndex = (this.ellipsisModeIndex + 1) % this.ellipsisModeStr.length
              }).margin(2).fontSize('13vp')
          }


          Row(){
            Button('fontSize+,' + this.fontSize).onClick((event: ClickEvent) => {
              this.fontSize += 2
            })
              .fontSize('13vp')
              .margin(2)
              .width('40%')
            Button('fontSize-,' + this.fontSize).onClick((event: ClickEvent) => {
              this.fontSize -= 2
            }).margin(2)
              .width('40%')
              .fontSize('13vp')
          }
          Row(){
            Button('minFontSize+,' + this.minFontSize).onClick((event: ClickEvent) => {
              this.minFontSize += 5
            })
              .fontSize('13vp')
              .margin(2)
              .width('40%')
            Button('minFontSize-,' + this.minFontSize).onClick((event: ClickEvent) => {
              this.minFontSize -= 5
            }).margin(2)
              .width('40%')
              .fontSize('13vp')
          }
          Row(){
            Button('maxFontSize+,' + this.maxFontSize).onClick((event: ClickEvent) => {
              this.maxFontSize += 5
            })
              .fontSize('13vp')
              .margin(2)
              .width('40%')
            Button('maxFontSize-,' + this.maxFontSize).onClick((event: ClickEvent) => {
              this.maxFontSize -= 5
            }).margin(2)
              .width('40%')
              .fontSize('13vp')
          }
          Row(){
            Button('selectionStart+,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart += 1
              }).margin(2) .fontSize('13vp')

            Button('selectionStart-,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart -= 1
              }).margin(2)  .fontSize('13vp')


          }

          Row() {
            Button('selectionEnd+,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd += 1
              }).margin(2).fontSize('13vp')

            Button('selectionEnd-,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd -= 1
              }).margin(2).fontSize('13vp')
          }

          Row() {
            Button('setTextSelection')
              .width('40%')
              .onClick(() => {
                this.controller.setTextSelection(this.selectionStart,this.selectionEnd, { menuPolicy:this.options } )
              }).margin(2).fontSize('13vp')


            Button('showUnderLine:' + this.showUnderlinestr[this.showUnderlineIndex])
              .width('40%')
              .onClick(() => {
                this.showUnderlineIndex = (this.showUnderlineIndex + 1) % this.showUnderline.length
              }).margin(2).fontSize('13vp')
          }


          Row() {


            Button('Direction:' + this.DirectionStr[this.DirectionIndex])
              .width('40%')
              .onClick(() => {
                this.DirectionIndex ++
                if (this.DirectionIndex > (this.DirectionStr.length - 1)) {
                  this.DirectionIndex = 0
                }
              }).fontSize('13vp').margin(2)

            Button('type:' + this.typeStr[this.inputIndex])
              .width('40%')
              .onClick(() => {
                this.inputIndex = (this.inputIndex + 1) % this.type.length
              }).margin(2).fontSize('13vp')
          }

          Row() {
            Button('maxLines+,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines += 1
              }).margin(2).fontSize('13vp')

            Button('maxLines-,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines -= 1
              }).margin(2).fontSize('13vp')
          }

          Row() {
            Button('Style：' + this.styleStr[this.styleIndex]).onClick(() => {
              this.styleIndex ++
              if (this.styleIndex > (this.styleStr.length - 1)) {
                this.styleIndex = 0
              }
            }).margin(2).fontSize('13vp')

            Button('enterKeyType：' + this.enterkeytypeStr[this.enterkeytypeIndex]).onClick(() => {
              this.enterkeytypeIndex ++
              if (this.enterkeytypeIndex > (this.enterkeytypeStr.length - 1)) {
                this.enterkeytypeIndex = 0
              }
            }).margin(2).fontSize('13vp')

          }

          Row() {

            Button('textIndent:' + this.textIndent[this.textIndentIndex])
              .width('40%')
              .onClick(() => {
                this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
              }).margin(2).fontSize('13vp')

            Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
              .width('40%')
              .onClick(() => {
                this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
              }).margin(2).fontSize('13vp')
          }

          Row() {
            Button('padding+,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest += 10
              }).margin(2).fontSize('13vp')

            Button('padding-,' + this.paddingTest)
              .width('40%')
              .onClick(() => {
                this.paddingTest -= 10
              }).margin(2).fontSize('13vp')
          }
          Row() {
            Button('margin+,' + this.marginTest)
              .width('40%')
              .onClick(() => {
                this.marginTest += 10
              }).margin(2).fontSize('13vp')

            Button('margin-,' + this.marginTest)
              .width('40%')
              .onClick(() => {
                this.marginTest -= 10
              }).margin(2).fontSize('13vp')
          }

          Row() {
            Button('letterSpacing:' + this.letterSpacing[this.letterSpacingIndex])
              .width('40%')
              .onClick(() => {
                this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
              }).margin(2).fontSize('13vp')

            Button('底板颜色:' + this.color[this.selectedBackgroundColor])
              .width('40%')
              .onClick(() => {
                this.selectedBackgroundColor ++
                if (this.selectedBackgroundColor > (this.color.length - 1)) {
                  this.selectedBackgroundColor = 0
                }
              }).margin(2).fontSize('13vp')

          }
          Row() {
            Button('caretWidth+,' + this.caretWidth)
              .width('40%')
              .onClick(() => {
                this.caretWidth += 1
              }).margin(2).fontSize('13vp')

            Button('caretWidth-,' + this.caretWidth)
              .width('40%')
              .onClick(() => {
                this.caretWidth -= 1
              }).margin(2).fontSize('13vp')
          }
          Row() {

            Button('caretColor:' + this.color[this.caretColor])
              .width('40%')
              .onClick(() => {
                this.caretColor ++
                if (this.caretColor > (this.color.length - 1)) {
                  this.caretColor = 0
                }
              }).margin(2).fontSize('13vp')

            Button('TextAlign:' + this.TextAlignStr[this.TextAlignIndex])
              .width('40%')
              .fontSize('13vp')
              .onClick(() => {
                this.TextAlignIndex ++
                if (this.TextAlignIndex > (this.TextAlignStr.length - 1)) {
                  this.TextAlignIndex = 0
                }
              })
          }
          Row() {
            Button('lineHeight+,' + this.lineheightTest)
              .width('40%').fontSize('13vp')
              .onClick(() => {
                this.lineheightTest += 10
              }).margin(2)

            Button('lineheight-,' + this.lineheightTest)
              .width('40%')
              .fontSize('13vp')
              .onClick(() => {
                this.lineheightTest -= 10
              }).margin(2)
          }


          Row() {
            Button('height+,' + this.heightTest)
              .width('40%').fontSize('13vp')
              .onClick(() => {
                this.heightTest += 10
              }).margin(2)

            Button('height-,' + this.heightTest)
              .width('40%')
              .fontSize('13vp')
              .onClick(() => {
                this.heightTest -= 10
              }).margin(2)
          }

          Row() {
            Button('width+,' + this.widthTest)
              .width('40%')
              .fontSize('13vp')
              .onClick(() => {
                this.widthTest += 10
              }).margin(2)

            Button('width-,' + this.widthTest)
              .width('40%')
              .fontSize('13vp')
              .onClick(() => {
                this.widthTest -= 10
              }).margin(2)
          }
          Column() {
            Button('CancelButtonStyle: ' + this.cancelButonStr[this.cancelButonIndex])
              .width('80%')
              .fontSize('13vp')
              .onClick(() => {
                this.cancelButonIndex ++
                if (this.cancelButonIndex > (this.cancelButonStr.length - 1)) {
                  this.cancelButonIndex = 0
                }
              })

            Button('showCounter:' + this.showCounterstr[this.showCounterIndex])
              .width('80%')
              .fontSize('13vp')
              .onClick(() => {
                this.showCounterIndex = (this.showCounterIndex + 1) % this.showCounterstr.length
              }).margin(2)
          }
          Column(){
            Button('cancelButtonSize+:,' + this.cancelButtonSize).onClick((event: ClickEvent) => {
              this.cancelButtonSize += 2
            })
              .fontSize('13vp')
              .margin(2)
              .width('80%')
            Button('cancelButtonSize-,' + this.cancelButtonSize).onClick((event: ClickEvent) => {
              this.cancelButtonSize -= 2
            }).margin(2)
              .width('80%')
              .fontSize('13vp')
          }
        }.padding({ bottom:150 })
      }.height('40%').margin(5)

    }
    .width('100%')
    .height('100%')
  }
}