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

import prompt from '@system.prompt';

@Entry
@Component
struct struct_10_02_textAreaHandleWithEllipsis {
  @State text: string = 'TextAreaType.NORMAL and 内联模式'
  controller: TextAreaController = new TextAreaController()
  @State text1: string = '123456789test001'
  @State text2: string = '123456789test001'
  controller1: TextAreaController = new TextAreaController()
  controller2: TextAreaController = new TextAreaController()

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Column() {
          Text('操作 双击输入框文字 TextAreaType ，左手柄拖动到省略号后；').fontColor(Color.Blue)
          Text('Pass条件：预期手柄与选中背板贴合').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        TextArea({
          text: this.text,
          placeholder: 'TextAlign.Start,maxLines(3)',
          controller: this.controller
        })
          .placeholderColor(Color.Red)
          .placeholderFont({ size: 26, weight: 400 })
          .maxLength(500)
          .showCounter(true)
          .textAlign(TextAlign.Start)
          .width(336)
          .height(120)
          .margin(20)// .padding(0)
          .barState(BarState.Auto)
          .fontSize(30)
          .caretColor(Color.Red)
          .caretStyle({ width: '10vp' })
          .fontWeight(FontWeight.Bolder)// .lineHeight('22')
          .decoration({
            type: TextDecorationType.Overline,
            color: Color.Red
          })
          .textOverflow(TextOverflow.Ellipsis)
          .maxLines(1)
          .fontColor(Color.Green)
          .backgroundColor('#ff15f8de')
          .onChange((value: string) => {
            this.text = value
          })
          .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
            prompt.showToast({
              message: `选中文本selectionStart:${selectionStart}selectionEnd:${selectionEnd}`,
              duration: 2000
            });
          })
        Divider()

        Column() {
          Text('操作 点击输入框末尾，输入两次换行，预期光标均正常在末尾显示；').fontColor(Color.Blue)
          Text('Pass条件：双击文字部分全选，预期双手柄显示正常').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
          Text('TextOverflow.Ellipsis（超长显示省略号）').fontSize(20).fontColor(Color.Blue).width('90%').padding(10)
          TextArea({ text: this.text1, placeholder: 'TextAreaType.NUMBER and 内联模式', controller: this.controller1 })
            .placeholderFont({ size: 26, weight: 500, family: 'Sans' })
            .fontSize(30)
            .border({ width: 1 })
            .padding(10)
            .width('100%')
            .textOverflow(TextOverflow.Ellipsis)
            .maxLines(1)
            .onChange((value: string) => {
              this.text1 = value
            })
          Text(this.text1)
            .borderWidth(1)

          Divider()
          Column() {
            Text('操作 12345后输入换行').fontColor(Color.Blue)
            Text('Pass条件：输入换行后出现省略').fontColor(Color.Red)
          }
          .borderWidth(2)
          .margin(10)
          .alignItems(HorizontalAlign.Start)
          .borderColor(Color.Blue)
          .padding(2)

          Text('TextOverflow.Ellipsis 右对齐').fontSize(20).fontColor(Color.Red).width('90%').padding(10)
          TextArea({ text: this.text2, controller: this.controller2 })
            .fontSize(30)// .style(TextContentStyle.INLINE)
            .textAlign(TextAlign.End)
            .border({ width: 1 })
            .padding(10)
            .width('100%')
            .textOverflow(TextOverflow.Ellipsis)
            .maxLines(1)// .textIndent(30)// .lineBreakStrategy(LineBreakStrategy.HIGH_QUALITY)
            .onChange((value: string) => {
              this.text2 = value
            })
        }.width('100%')
      }
    }
  }
}
