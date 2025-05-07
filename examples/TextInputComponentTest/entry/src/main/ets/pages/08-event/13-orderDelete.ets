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
struct Ets_8_13_order_delete {
  @State time_share_1: number = 0
  @State time_onchange_1: number = 0
  @State time_onSubmit_1: number = 0
  @State time_onEditChange_1: number = 0
  @State time_onCopy_1: number = 0
  @State time_onCut_1: number = 0
  @State time_onPaste_1: number = 0
  @State time_onTextSelectionChange_1: number = 0
  @State time_onContentScroll_1: number = 0
  @State time_onSecurityStateChange_1: number = 0
  @State time_onWillInsert_1: number = 0
  @State time_onDidInsert_1: number = 0
  @State time_onWillDelete_1: number = 0
  @State time_onDidDelete_1: number = 0

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('删除时，事件触发顺序')
        }

        Column() {
          Text('规格1 软键盘输入文本，事件顺序').fontColor(Color.Blue)
          Text('测试步骤：\n 1、点击输入框末尾空白处，点击reset 2、按一次删除键')

          Text('pass条件：顺序是300,000,400,001,2').fontColor(Color.Red)
          Text('下面是 需要测试的区域')
          TextInput({ text: '这是一段示例内容用于测试onChange' })
            .margin(1)
            .type(InputType.Normal)
            .onChange((value: string) => {
              this.time_share_1++;
              this.time_onchange_1 = this.time_share_1
            })
            .onSubmit(() => {
              this.time_share_1++;
              this.time_onSubmit_1 = this.time_share_1
            })
            .onEditChange((isEditing: boolean) => {
              this.time_share_1++;
              this.time_onEditChange_1 = this.time_share_1
            })

            .onCopy((value: string) => {
              this.time_share_1++
              this.time_onCopy_1 = this.time_share_1
            })
            .onCut((value: string) => {
              this.time_share_1++;
              this.time_onCut_1 = this.time_share_1
            })
            .onPaste((value: string, event: PasteEvent) => {
              this.time_share_1++;
              this.time_onPaste_1 = this.time_share_1
            })

            .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
              this.time_share_1++;
              this.time_onTextSelectionChange_1 = this.time_share_1
            })
            .onContentScroll(() => {
              this.time_share_1++;
              this.time_onContentScroll_1 = this.time_share_1;
            })
            .onSecurityStateChange((callback: Boolean) => {
              this.time_share_1++
              this.time_onSecurityStateChange_1 = this.time_share_1;
            })

            .onWillInsert(() => {
              this.time_share_1++
              this.time_onWillInsert_1 = this.time_share_1
              return true
            })
            .onDidInsert(() => {
              this.time_share_1++
              this.time_onDidInsert_1 = this.time_share_1
            })
            .onWillDelete(() => {
              this.time_share_1++
              this.time_onWillDelete_1 = this.time_share_1
              return true
            })

            .onDidDelete(() => {
              this.time_share_1++
              this.time_onDidDelete_1 = this.time_share_1
            })
          Row() {
            Text('回调').width('50%')
            Text('触发顺序 ').margin(1).width('50%')
          }

          Divider().height('1px').color(Color.Black)

          Row() {
            Text('onchange').width('50%')
            Text('顺序 ' + this.time_onchange_1).margin(1).width('50%')
          }

          Row() {
            Text('onSubmit').width('50%')
            Text('顺序 ' + this.time_onSubmit_1).margin(1).width('50%')
          }

          Row() {
            Text('onEditChange').width('50%')
            Text('顺序 ' + this.time_onEditChange_1).margin(1).width('50%')
          }

          Divider().height('1px').color(Color.Black)

          Row() {
            Text('onCopy').width('50%')
            Text('顺序 ' + this.time_onCopy_1).margin(1).width('50%')
          }

          Row() {
            Text('onCut').width('50%')
            Text('顺序 ' + this.time_onCut_1).margin(1).width('50%')
          }

          Row() {
            Text('onPaste').width('50%')
            Text('顺序 ' + this.time_onPaste_1).margin(1).width('50%')
          }

          Divider().height('1px').color(Color.Black)

          Row() {
            Text('onTextSelectionChange').width('50%')
            Text('顺序 ' + this.time_onTextSelectionChange_1).margin(1).width('50%')
          }

          Row() {
            Text('onContentScroll').width('50%')
            Text('顺序 ' + this.time_onContentScroll_1).margin(1).width('50%')
          }

          Row() {
            Text('onSecurityStateChange').width('50%')
            Text('顺序 ' + this.time_onSecurityStateChange_1).margin(1).width('50%')
          }

          Divider().height('1px').color(Color.Black)

          Row() {
            Text('onWillInsert').width('50%')
            Text('顺序 ' + this.time_onWillInsert_1).margin(1).width('50%')
          }

          Row() {
            Text('onDidInsert').width('50%')
            Text('顺序 ' + this.time_onDidInsert_1).margin(1).width('50%')
          }

          Row() {
            Text('onWillDelete').width('50%')
            Text('顺序 ' + this.time_onWillDelete_1).margin(1).width('50%')
          }

          Divider().height('1px').color(Color.Black)

          Row() {
            Text('onDidDelete').width('50%')
            Text('顺序 ' + this.time_onDidDelete_1).margin(1).width('50%')
          }


          Button('Reset')
            .onClick(() => {
              this.time_share_1 = 0

              this.time_onchange_1 = 0
              this.time_onSubmit_1 = 0
              this.time_onEditChange_1 = 0

              this.time_onCopy_1 = 0
              this.time_onCut_1 = 0
              this.time_onPaste_1 = 0

              this.time_onTextSelectionChange_1 = 0
              this.time_onContentScroll_1 = 0
              this.time_onSecurityStateChange_1 = 0

              this.time_onWillInsert_1 = 0
              this.time_onDidInsert_1 = 0
              this.time_onWillDelete_1 = 0

              this.time_onDidDelete_1 = 0
            })

        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)

      }
    }
  }
}