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
export function SoftKeyboardLevel04Builder(name: string, param: Object) {
  SoftKeyboardLevel04()
}

@Entry
@Component
struct SoftKeyboardLevel04 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State showSheet: boolean = false
  @State showBindContentCover: boolean = false
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          GridItem() {
            Button(item)
              .width(100)
              .height(60)
              .onClick(() => {
                this.inputValue += item
              })
          }
        })
      }
      .maxCount(3)
      .columnsGap(5)
      .rowsGap(5)
      .padding(5)

      Row({ space: 5 }) {
        Button('清除').onClick(() => {
          this.inputValue = ''
        })
        Button('删除').onClick(() => {
          if (this.inputValue.length > 0) {
            this.inputValue = this.inputValue.substring(0, this.inputValue.length - 1)
          }
        })
      }
    }
    .backgroundColor(Color.Gray)
    .padding(10)
  }

  @Builder
  sheetBuilder() {
    Column({ space: 10 }) {
      Text('半模态中的输入组件')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      TextInput({ placeholder: 'Sheet TextInput', text: this.inputValue, controller: this.controller_textInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('TextInput_Sheet')

      TextArea({ placeholder: 'Sheet TextArea', controller: this.controller_textArea })
        .borderWidth(1)
        .height(100)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('TextArea_Sheet')

      RichEditor(this.options)
        .placeholder('Sheet RichEditor')
        .borderWidth(1)
        .height(100)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_Sheet')

      Button('关闭')
        .onClick(() => {
          this.showSheet = false
        })
    }
    .width('100%')
    .padding(20)
  }

  @Builder
  contentCoverBuilder() {
    Column({ space: 10 }) {
      Text('全模态中的输入组件')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      TextInput({ placeholder: 'Cover TextInput', text: this.inputValue, controller: this.controller_textInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('TextInput_Cover')

      TextArea({ placeholder: 'Cover TextArea', controller: this.controller_textArea })
        .borderWidth(1)
        .height(100)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('TextArea_Cover')

      RichEditor(this.options)
        .placeholder('Cover RichEditor')
        .borderWidth(1)
        .height(100)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_Cover')

      Button('关闭')
        .onClick(() => {
          this.showBindContentCover = false
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  build() {
    NavDestination() {
      Column({ space: 20 }) {
        Text('Tabs组件中的输入组件测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .width('100%')

        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            Column({ space: 10 }) {
              Text('Tab 1 - 普通通输入组件')
                .fontSize(14)

              TextInput({ placeholder: 'Tab1 TextInput', text: this.inputValue })
                .borderWidth(1)
                .key('TextInput_Tab1')

              TextArea({ placeholder: 'Tab1 TextArea' })
                .borderWidth(1)
                .height(80)
                .key('TextArea_Tab1')

              Search({ placeholder: 'Tab1 Search', value: this.inputValue })
                .borderWidth(1)
                .key('Search_Tab1')
            }
            .width('100%')
            .padding(20)
          }
          .tabBar('Tab 1')

          TabContent() {
            Column({ space: 10 }) {
              Text('Tab 2 - 自定义键盘输入组件')
                .fontSize(14)

              TextInput({ placeholder: 'Tab2 TextInput', text: this.inputValue, controller: this.controller_textInput })
                .borderWidth(1)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .key('TextInput_Tab2')

              TextArea({ placeholder: 'Tab2 TextArea', controller: this.controller_textArea })
                .borderWidth(1)
                .height(80)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .key('TextArea_Tab2')

              RichEditor(this.options)
                .placeholder('Tab2 RichEditor')
                .borderWidth(1)
                .height(80)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .key('RichEditor_Tab2')
            }
            .width('100%')
            .padding(20)
          }
          .tabBar('Tab 2')

          TabContent() {
            Column({ space: 10 }) {
              Text('Tab 3 - 弹窗测试')
                .fontSize(14)

              Button('打开半模态')
                .onClick(() => {
                  this.showSheet = true
                })
                .bindSheet($$this.showSheet, this.sheetBuilder(), {
                  height: 400,
                  backgroundColor: Color.White,
                  enableOutsideInteractive: true,
                  mode: SheetMode.OVERLAY,
                  preferType: SheetType.BOTTOM
                })
                .key('Button_OpenSheet')

              Button('打开全模态')
                .onClick(() => {
                  this.showBindContentCover = true
                })
                .bindContentCover($$this.showBindContentCover, this.contentCoverBuilder(), {
                  modalTransition: ModalTransition.DEFAULT,
                  backgroundColor: Color.Gray,
                })
                .key('Button_OpenCover')
            }
            .width('100%')
            .padding(20)
          }
          .tabBar('Tab 3')
        }
        .width('100%')
        .height('80%')
        .barMode(BarMode.Fixed)

      }
      .width('100%')
      .height('100%')
      .padding(10)
    }
    .title('SoftKeyboardLevel04')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
