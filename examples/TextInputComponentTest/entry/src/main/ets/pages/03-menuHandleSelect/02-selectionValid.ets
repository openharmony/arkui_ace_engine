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
struct Selection_Valid {
  @State button_text_1: string = 'start = 8,end = 2,click times = '
  @State button_1_click_times: number = 0
  controller_1: TextInputController = new TextInputController()
  @State button_text_2: string = 'start = -2,end = 8,click times = '
  @State button_2_click_times: number = 0
  controller_2: TextInputController = new TextInputController()
  @State button_text_3: string = 'start = 2,end = 100,click times = '
  @State button_3_click_times: number = 0
  controller_3: TextInputController = new TextInputController()
  @State button_text_4: string = 'start = 5,end = 5,click times = '
  @State button_4_click_times: number = 0
  controller_4: TextInputController = new TextInputController()
  @State text_5: string = '超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本超长文本'
  @State button_text_5: string = 'start = 5,end = 5,click times = '
  @State button_5_click_times: number = 0
  controller_5: TextInputController = new TextInputController()
  @State button_6_click_times_default: number = 0
  @State button_6_click_times_hide: number = 0
  @State button_6_click_times_show: number = 0
  controller_6: TextInputController = new TextInputController()
  controller_7: TextInputController = new TextInputController()

  build() {
    Flex({ justifyContent: FlexAlign.Center, }) {
      Scroll() {
        Column({ space: 10 }) {
          Text() {
            Span('共6条规格')
            Span('规格1、selectionStart>selectionEnd，无选中效果:\n')
            Span('规格2、入参selectionStart<0则选0 \n')
            Span('规格3、selectionEnd>最大文本长度，则选最大文本长度 \n')
            Span('规格4、 selectionStart == selectionEnd，闪光标\n')
            Span('规格5、入参合法有效，则显示选中区并将选中区移动到可视区域内，除PC外会显示手柄 \n')
            Span('规格6、入参SelectionOptions控制菜单显示，MenuPolicy::HIDE不显示菜单，MenuPolicy::SHOW显示菜单，如果使用鼠标操作，则不显示手柄和菜单\n')
            Span('规格7、selection选中一半emoji时，拖动、剪切、删除、输入等操作都会影响整个emoji\n')
          }

          Column({ space: 5 }) {
            Text('规格1、selectionStart>selectionEnd，无选中效果 \n')
            Text('selectionStart>selectionEnd，点击按钮后，没有出现选中区，规格1 pass \n')
            TextInput({ text: '0123456789，观察，光标位置不变', controller: this.controller_1 })
              .border({
                color: Color.Blue,
                width: 1,
                radius: 0,
                style: BorderStyle.Solid
              })
              .defaultFocus(true)
              .caretPosition(5)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text(this.button_text_1 + this.button_1_click_times)
            }
            .height(25)
            .onClick(() => {
              this.controller_1.setTextSelection(8, 2)
              this.button_1_click_times = this.button_1_click_times + 1
            })
          }
          .width('95%')
          .border({
            color: Color.Black,
            width: 1,
            radius: 0,
            style: BorderStyle.Solid
          })


          Column({ space: 5 }) {
            Text('规格2、入参selectionStart<0则选0 \n')
            Text('selectionStart<0，先点击文本框，再点击按钮，观察选中区，左侧在0之前，规格2 pass \n')
            TextInput({ text: '0123456789，观察选中区', controller: this.controller_2 })
              .borderWidth(1)
              .caretPosition(5)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text(this.button_text_2 + this.button_2_click_times)
            }
            .height(25)
            .onClick(() => {
              this.controller_2.setTextSelection(-2, 8)
              this.button_2_click_times = this.button_2_click_times + 1
            })
          }
          .borderWidth(1)


          Column({ space: 5 }) {
            Text('规格3、selectionEnd>最大文本长度，则选最大文本长度 \n')
            Text('先点击文本框，再点击按钮，观察选中区，右侧在所有文本之后，规格3 pass \n')
            TextInput({ text: '0123456789，观察选中区', controller: this.controller_3 })
              .borderWidth(1)
              .caretPosition(5)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text(this.button_text_3 + this.button_3_click_times)
            }
            .height(25)
            .onClick(() => {
              this.controller_3.setTextSelection(2, 100)
              this.button_3_click_times = this.button_3_click_times + 1
            })
          }
          .borderWidth(1)


          Column({ space: 5 }) {
            Text('规格4、selectionStart == selectionEnd，闪光标 \n')
            Text('先点击文本框，再点击按钮，观察选中区，光标在5之前闪烁，规格4 pass \n')
            TextInput({ text: '0123456789，观察选中区', controller: this.controller_4 })
              .borderWidth(1)
              .caretPosition(0)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text(this.button_text_4 + this.button_4_click_times)
            }
            .height(25)
            .onClick(() => {
              this.controller_4.setTextSelection(5, 5)
              this.button_4_click_times = this.button_4_click_times + 1
            })
          }
          .borderWidth(1)


          Column({ space: 5 }) {
            Text('规格5、入参合法有效，则显示选中区并将选中区移动到可视区域内，除PC外会显示手柄 \n')
            Text('超长文本：先点击文本框，再点击按钮，观察选中区，光标在5之前闪烁，规格5 pass \n')
            TextInput({ text: this.text_5 + '01234567890', controller: this.controller_5 })
              .borderWidth(1)
              .caretPosition(0)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text(this.button_text_5 + this.button_5_click_times)
            }
            .height(25)
            .onClick(() => {
              this.controller_5.setTextSelection(this.text_5.length, this.text_5.length + 5)
              this.button_5_click_times = this.button_5_click_times + 1
            })
          }
          .borderWidth(1)


          Column({ space: 5 }) {
            Text('规格6、入参SelectionOptions控制菜单显示，MenuPolicy::HIDE不显示菜单，MenuPolicy::SHOW显示菜单，如果使用鼠标操作，则不显示手柄和菜单 \n')
            Text('default、hide不弹出菜单，show 弹出菜单， 规格6 pass \n')
            TextInput({ text: '01234567890 控制菜单显示', controller: this.controller_6 })
              .borderWidth(1)
              .caretPosition(0)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text('控制菜单显示 default' + this.button_6_click_times_default)
            }
            .height(25)
            .onClick(() => {
              this.controller_6.setTextSelection(2, 5, { menuPolicy: MenuPolicy.DEFAULT })
              this.button_6_click_times_default = this.button_6_click_times_default + 1
            })

            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text('控制菜单显示 HIDE' + this.button_6_click_times_hide)
            }
            .height(25)
            .onClick(() => {
              this.controller_6.setTextSelection(2, 5, { menuPolicy: MenuPolicy.HIDE })
              this.button_6_click_times_hide = this.button_6_click_times_hide + 1
            })

            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text('控制菜单显示 SHOW' + this.button_6_click_times_show)
            }
            .height(25)
            .onClick(() => {
              this.controller_6.setTextSelection(2, 5, { menuPolicy: MenuPolicy.SHOW })
              this.button_6_click_times_show = this.button_6_click_times_show + 1
            })
          }
          .borderWidth(1)

          Column({ space: 5 }) {
            Text('规格7、selection选中一半emoji时，拖动、剪切、删除、输入等操作都会影响整个emoji \n')
            Text('步骤：先点击输入框，再点击按钮 选中一半emoji \n')
            Text('pass条件：拖动、剪切、删除、输入等操作都会影响整个emoji，文本不会被清空 \n')
            TextInput({ text: '12😅34', controller: this.controller_7 })
              .borderWidth(1)
              .caretPosition(0)
            Button({ buttonStyle: ButtonStyleMode.NORMAL }) {
              Text('选中一半emoji')
            }
            .height(25)
            .onClick(() => {
              this.controller_7.setTextSelection(0, 3)
            })
          }
          .borderWidth(1)

          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }
        .width('95%')
        .border({
          color: Color.Black,
          width: 1,
          radius: 0,
          style: BorderStyle.Solid
        })
        .alignItems(HorizontalAlign.Start)
      }
    }
    // .height('100%')

    .align(Alignment.TopStart)
  }
}