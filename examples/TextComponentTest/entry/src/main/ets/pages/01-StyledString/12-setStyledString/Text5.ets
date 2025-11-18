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

import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct styled_string_demo5 {
  @State start: number = 0
  @State length: number = 1
  @State fontSize: number = 16
  @State fontWeight1: number = 400
  @State colorAll: Color[] = [Color.Black, Color.Blue, Color.Pink, Color.Yellow, Color.Brown]
  @State color: number = 0
  @State text: string = ''
  @State decorationType: TextDecorationType[] =
    [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State enableDataDetector: boolean = false
  @State copyOption: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State width1: number = 200
  @State height1: number = 50
  @State ellipsisMode: EllipsisMode[] = [EllipsisMode.START, EllipsisMode.CENTER, EllipsisMode.END]
  @State ellipsisModeStr: string[] = ['START', 'CENTER', 'END']
  @State ellipsisModeIndex: number = 2
  @State textOverflow: TextOverflow[] =
    [TextOverflow.Clip, TextOverflow.None, TextOverflow.Ellipsis, TextOverflow.MARQUEE]
  @State textOverflowStr: string[] = ['Clip', 'None', 'Ellipsis', 'MARQUEE']
  @State textOverflowIndex: number = 0
  @State obscured1: ObscuredReasons[] = []
  @State obscured2: ObscuredReasons[] = [ObscuredReasons.PLACEHOLDER]
  @State maxLines: number = 1
  @State selectionStart: number = -1
  @State selectionEnd: number = -1
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakStr: string[] = ['NORMAL', 'BREAK_ALL', 'BREAK_WORD']
  @State wordBreakIndex: number = 2
  @State clip1: boolean = true
  scroll: Scroller = new Scroller();
  mutableStyledString11: MutableStyledString =
    new MutableStyledString("This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content. This is the setting of textOverflow to Clip text content This is the setting of textOverflow to None text content.",
      [
        {
          start: 0,
          length: 4,
          styledKey: StyledStringKey.FONT,
          styledValue: new TextStyle({ fontColor: Color.Blue })
        },
        {
          start: 4,
          length: 4,
          styledKey: StyledStringKey.FONT,
          styledValue: new TextStyle({ fontColor: Color.Red })
        }
      ]);
  mutableStyledString1: MutableStyledString = new MutableStyledString("😄这是一段测试文字", [
    {
      start: 1,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 1,
      length: 10,
      styledKey: StyledStringKey.LETTER_SPACING,
      styledValue: new LetterSpacingStyle(new LengthMetrics(3, 1))
    },
    {
      start: 4,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    }
  ]);
  mutableStyledString2: MutableStyledString = new MutableStyledString("输入框", [{
    start: 0,
    length: 3,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Green })
  }]);
  mutableStyledString3: MutableStyledString = new MutableStyledString("文本输入", [{
    start: 0,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Green })
  }]);
  mutableStyledString4: MutableStyledString = new MutableStyledString("插入", [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }]);
  mutableStyledString5: MutableStyledString = new MutableStyledString("替换", [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Orange })
  }]);
  fontStyleAttr1: TextStyle = new TextStyle({ fontColor: Color.Pink })
  mutableStyledString8: MutableStyledString = new MutableStyledString("这是一段测试文字", [
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 4,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    }
  ]);
  controller1: TextController = new TextController();
  controller2: TextController = new TextController();
  controller3: TextController = new TextController();
  controller: TextController = new TextController()

  async onPageShow() {
    this.controller1.setStyledString(this.mutableStyledString1)
  }

  aboutToAppear(): void {
    this.controller.setStyledString(new StyledString("123456")) // 变更前，由于此时controller还未和Text绑定，此次设置不生效。变更后，属性字符串可以正确的显示
  }

  build() {
    Column() {
      TextInput().height(60)
      Text(undefined, { controller: this.controller }).borderWidth(1)
      Divider()
      Text(undefined, { controller: this.controller1 })
        .margin({ top: 10 })
        .borderWidth(1)
        .borderWidth(1)
        .height(this.height1)
        .width(this.width1)
        .fontSize(this.fontSize)
        .fontColor(this.colorAll[this.color])
        .decoration({
          type: this.decorationType[this.typeIndex],
          color: this.colorAll[this.decorationColor]
        })
        .enableDataDetector(this.enableDataDetector)
        .copyOption(this.copyOption[this.index])
        .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
        .textOverflow({
          overflow: this.textOverflow[this.textOverflowIndex]
        })
        .obscured(this.obscured1)
        .maxLines(this.maxLines)
        .selection(this.selectionStart, this.selectionEnd)
        .wordBreak(this.wordBreak[this.wordBreakIndex])
        .clip(this.clip1)


      Text(this.text).margin({ top: 10 }).borderWidth(1)

      Scroll(this.scroll) {
        Column() {
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
          }

          Row() {
            Button('width+,' + this.width1)
              .width('40%')
              .onClick(() => {
                this.width1 += 10
              })

            Button('width-,' + this.width1)
              .width('40%')
              .onClick(() => {
                this.width1 -= 10
              })
          }

          Row() {
            Button('height+,' + this.height1)
              .width('40%')
              .onClick(() => {
                this.height1 += 10
              })

            Button('height-,' + this.height1)
              .width('40%')
              .onClick(() => {
                this.height1 -= 10
              })
          }

          Row() {
            Button('fontColor:' + this.colorAll[this.color])
              .width('80%')
              .onClick(() => {
                this.color = (this.color + 1) % this.colorAll.length
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
            Button('enableDataDetector:' + this.enableDataDetector)
              .width('80%')
              .onClick(() => {
                this.enableDataDetector = !this.enableDataDetector
              })
          }

          Row() {
            Button('copyOption:' + this.copyOptionStr[this.index])
              .width('80%')
              .onClick(() => {
                this.index++
                if (this.index > (this.copyOptionStr.length - 1)) {
                  this.index = 0
                }
              })
          }

          Row() {
            Button('ellipsisMode:' + this.ellipsisModeStr[this.ellipsisModeIndex])
              .width('40%')
              .onClick(() => {
                this.ellipsisModeIndex = (this.ellipsisModeIndex + 1) % this.ellipsisMode.length
              })

            Button('clip:' + this.clip1)
              .width('40%')
              .onClick(() => {
                this.clip1 = !this.clip1
              })
          }

          Row() {
            Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
              .width('80%')
              .onClick(() => {
                this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              })
          }

          Row() {
            Button('文本遮罩')
              .width('40%')
              .onClick(() => {
                this.obscured1 = [ObscuredReasons.PLACEHOLDER]
              })

            Button('不遮罩')
              .width('40%')
              .onClick(() => {
                this.obscured1 = []
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
            Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
              .width('80%')
              .onClick(() => {
                this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
              })
          }


          Row() {
            Button('start+,' + this.start)
              .width('40%')
              .onClick(() => {
                this.start++
              })

            Button('start-,' + this.start)
              .width('40%')
              .onClick(() => {
                this.start--
              })
          }.margin({ top: 10 })

          Row() {
            Button('length+,' + this.length)
              .width('40%')
              .onClick(() => {
                this.length++
              })

            Button('length-,' + this.length)
              .width('40%')
              .onClick(() => {
                this.length--
              })
          }.margin({ top: 10 })


          Row() {
            Button('replaceStyledString')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.replaceStyledString(this.start, this.length, this.mutableStyledString5)
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('getStyles')
              .width('40%')
              .onClick(() => {
                this.text =
                  JSON.stringify(this.mutableStyledString1.getStyles(this.start, this.length, StyledStringKey.FONT))
                let styles = this.mutableStyledString1.getStyles(this.start, this.length)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })
          }.margin({ top: 10 })

          Row() {
            Button('insertStyledString')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.insertStyledString(this.start, this.mutableStyledString4)
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('appendStyledString')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.appendStyledString(this.mutableStyledString3)
                this.controller1.setStyledString(this.mutableStyledString1)
              })
          }.margin({ top: 10 })


          Row() {
            Button('getString')
              .width('40%')
              .onClick(() => {
                this.text = this.mutableStyledString1.getString()
              })

            Button('length')
              .width('40%')
              .onClick(() => {
                this.text = this.mutableStyledString1.length + ''
              })
          }.margin({ top: 10 })

          Row() {
            Button('replaceString')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.replaceString(this.start, this.length, '已经替换')
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('insert：/n')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.insertString(this.start, '\n')
                this.controller1.setStyledString(this.mutableStyledString1)
              })
          }.margin({ top: 10 })

          Row() {
            Button('insert：输入框')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.insertString(this.start, '输入框')
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('insert： ')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.insertString(this.start, ' ')
                this.controller1.setStyledString(this.mutableStyledString1)
              })

          }.margin({ top: 10 })

          Row() {
            Button('removeString')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.removeString(this.start, this.length)
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('replaceStyle')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.replaceStyle({
                  start: this.start,
                  length: this.length,
                  styledKey: StyledStringKey.FONT,
                  styledValue: new TextStyle({ fontColor: Color.Blue })
                })
                this.controller1.setStyledString(this.mutableStyledString1)
              })

          }.margin({ top: 10 })

          Row() {
            Button('setStyle')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.setStyle({
                  start: this.start,
                  length: this.length,
                  styledKey: StyledStringKey.FONT,
                  styledValue: new TextStyle({ fontColor: Color.Green })
                })
                this.controller1.setStyledString(this.mutableStyledString1)
              })

            Button('removeStyle')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.removeStyle(this.start, this.length, StyledStringKey.FONT)
                this.controller1.setStyledString(this.mutableStyledString1)
              })
          }.margin({ top: 10 })


          Row() {
            Button('clearStyles')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.clearStyles()
                this.controller1.setStyledString(this.mutableStyledString1)

              })

            Button('removeStyles')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString1.removeStyles(this.start, this.length)
                this.controller1.setStyledString(this.mutableStyledString1)

              })
          }.margin({ top: 10 })

        }
      }
      .expandSafeArea([SafeAreaType.KEYBOARD])
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Gray)
      .height('50%')
      .scrollBarWidth(10)
      .padding({ bottom: 50 })
      .edgeEffect(EdgeEffect.None)
    }
    .width('100%')
  }
}