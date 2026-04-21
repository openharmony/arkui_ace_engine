/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Builder
export function SoftKeyboardLevel03Builder(name: string, param: Object) {
  SoftKeyboardLevel03()
}

@Entry
@Component
struct SoftKeyboardLevel03 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State supportAvoidance: boolean | undefined = undefined
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };
  @State showPopup: boolean = false
  @State keyHeight: number = 250
  @State showKeyboard: boolean = true;

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Row({ space: 2 }) {
        Button('高度+').onClick(() => {
          this.keyHeight += 10
        }).key('keyHeight+')
        Button('关闭').onClick(() => {
          this.controller_textInput.stopEditing()
          this.controller_textArea.stopEditing()
        })
        Button('高度-').onClick(() => {
          this.keyHeight -= 10
        }).key('keyHeight-')
      }

      Grid() {
        ForEach(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'], (item: string) => {
          GridItem() {
            Button(item)
              .width(110).onClick(() => {
              this.inputValue += item
            })
              .key('Button_' + item)
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
    .height(this.keyHeight)
  }

  @Builder
  popupBuilder() {
    Column({ space: 10 }) {
      TextInput({ placeholder: 'Popup中的TextInput', controller: this.controller_textInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('TextInput_Popup')
      TextArea({ placeholder: 'Popup中的TextArea', controller: this.controller_textArea })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('TextArea_Popup')
      RichEditor(this.options)
        .placeholder('Popup中的RichEditor')
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_Popup')
    }.width('60%').padding(15).backgroundColor(Color.White)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('Grid布局中的输入组件测试')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('100%')
            .key('Text_Header')

          Grid() {
            ForEach([1, 2, 3, 4, 5, 6], (item: number) => {
              GridItem() {
                Column({ space: 5 }) {
                  TextInput({ placeholder: 'Grid TextInput ' + item, text: this.inputValue })
                    .borderWidth(1)
                    .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
                    .key('TextInput_Grid_' + item)
                  TextArea({ placeholder: 'Grid TextArea ' + item })
                    .borderWidth(1)
                    .height(60)
                    .key('TextArea_Grid_' + item)
                }
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(10)
          .columnsGap(10)
          .height(300)

          Divider().color(Color.Gray)

          Text('List布局中的输入组件测试')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('100%')
            .key('Text_ListHeader')

          List({ space: 8 }) {
            ForEach([1, 2, 3, 4, 5], (item: number) => {
              ListItem() {
                Row({ space: 10 }) {
                  TextInput({ placeholder: 'List TextInput ' + item })
                    .borderWidth(1)
                    .layoutWeight(1)
                    .key('TextInput_List_' + item)
                  TextArea({ placeholder: 'List TextArea ' + item })
                    .borderWidth(1)
                    .layoutWeight(1)
                    .height(50)
                    .key('TextArea_List_' + item)
                }
              }
            })
          }
          .height(300)

          Divider().color(Color.Gray)

          Text('控制按钮')
            .fontSize(12)
            .fontColor(0xCCCCCC)
            .width('100%')

          Row({ space: 10 }) {
            Button('显示Popup')
              .onClick(() => {
                this.showPopup = true
              })
              .bindPopup(this.showPopup, {
                builder: this.popupBuilder,
                onStateChange: (e) => {
                  if (!e.isVisible) {
                    this.showPopup = false
                  }
                }
              })
              .key('Button_ShowPopup')

            Button('避让 true')
              .onClick(() => {
                this.supportAvoidance = true
              })
              .key('Button_AvoidanceTrue')

            Button('避让 false')
              .onClick(() => {
                this.supportAvoidance = false
              })
              .key('Button_AvoidanceFalse')
          }

        }
        .width('100%')
        .padding(10)
      }
    }
    .title('SoftKeyboardLevel03')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
