/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
export function SoftKeyboardLevel02Builder(name: string, param: Object) {
  SoftKeyboardLevel02()
}

@Entry
@Component
struct SoftKeyboardLevel02 {
  pathStack: NavPathStack = new NavPathStack()
  normalIcon: Resource = $r('app.media.app_icon')
  selectedIcon: Resource = $r('app.media.app_icon')
  @State arr: number[] = [1, 2, 3]
  @State current: number = 1
  @State style: TextContentStyle = TextContentStyle.DEFAULT
  @State inputValue: string = ''
  controller_richEditor: RichEditorController = new RichEditorController()
  options: RichEditorOptions = { controller: this.controller_richEditor }
  controller_richEditor2: RichEditorController = new RichEditorController()
  options2: RichEditorOptions = { controller: this.controller_richEditor2 }
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()

  // 自定义键盘组件
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Row({ space: 2 }) {
        Button('x_textInput').onClick(() => {
          // 关闭自定义键盘
          this.controller_textInput.stopEditing()
        })
          .key('Button_01')
        Button('x_textarea').onClick(() => {
          // 关闭自定义键盘
          this.controller_textArea.stopEditing()
        })
          .key('Button_02')
      }

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '').width(110).onClick(() => {
              this.inputValue += item
            })
              .key('Button_03' + item)
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
  }

  build() {
    NavDestination() {
      Column() {
        SideBarContainer(SideBarContainerType.Embed) {
          Column() {
            ForEach(this.arr, (item: number) => {
              Column({ space: 5 }) {
                Image(this.current === item ? this.selectedIcon : this.normalIcon).width(50).height(50)
                Text('Index0' + item)
                  .fontSize(20)
                  .fontColor(this.current === item ? '#0A59F7' : '#999')
                  .fontFamily('source-sans-pro,cursive,sans-serif')
              }
              .onClick(() => {
                this.current = item
              })
              .key('SideBar_' + item)
            }, (item: string) => item)
          }.width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .backgroundColor('#19000000')

          if (this.current == 1) {
            Column({ space: 5 }) {
              Text('welcome Index0' + this.current)
                .copyOption(CopyOptions.LocalDevice)
              TextInput({ placeholder: '普通TextInput', text: '普通TextInput' })
                .borderWidth(1)
                .width('80%')
                .defaultFocus(true)
                .style(this.style)
                .key('TextInput_01')
              TextArea({ placeholder: '普通TextArea', text: '普通TextArea' })
                .borderWidth(1)
                .defaultFocus(true)
                .width('80%')
                .style(this.style)
                .key('TextArea_01')
              Search({ placeholder: '普通Search', value: '普通Search' })
                .borderWidth(1)
                .width('80%')
                .key('Search_01')
              RichEditor(this.options)
                .placeholder('普通RichEditor')
                .borderWidth(1)
                .width('80%')
                .key('RichEditor_01')
                .onReady(() => {
                  this.controller_richEditor.addTextSpan('12 3',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controller_richEditor.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                })
              TextInput({
                placeholder: '绑定自定义键盘的TextInput',
                text: '自定义键盘TextInput',
                controller: this.controller_textInput
              })
                .borderWidth(1)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .enableKeyboardOnFocus(false)
                .style(this.style)
                .key('TextInput_02')

            }.margin({ top: 50, left: 20, right: 30 })
          } else if (this.current == 2) {
            Column({ space: 5 }) {
              Text('welcome Index0' + this.current)
                .copyOption(CopyOptions.LocalDevice)
              TextInput({ placeholder: '普通TextInput', text: '普通TextInput' })
                .borderWidth(1)
                .width('80%')
                .style(this.style)
                .key('TextInput_03')
              TextArea({ placeholder: '普通TextArea', text: '普通TextArea' })
                .borderWidth(1)
                .width('80%')
                .defaultFocus(true)
                .style(this.style)
                .key('TextArea_02')
              Search({ placeholder: '普通Search', value: '普通Search' })
                .borderWidth(1)
                .width('80%')
                .key('Search_02')
              RichEditor(this.options)
                .placeholder('普通RichEditor')
                .borderWidth(1)
                .width('80%')
                .key('RichEditor_02')
                .onReady(() => {
                  this.controller_richEditor.addTextSpan('12 3',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controller_richEditor.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                })
              TextArea({
                placeholder: '绑定自定义键盘的TextArea',
                text: '自定义键盘TextArea',
                controller: this.controller_textArea
              })
                .borderWidth(1)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .enableKeyboardOnFocus(false)
                .style(this.style)
                .key('TextArea_03')
            }.margin({ top: 50, left: 20, right: 30 })
          } else if (this.current == 3) {
            Column({ space: 5 }) {
              Text('welcome Index0' + this.current)
                .copyOption(CopyOptions.LocalDevice)
              TextInput({ placeholder: '普通TextInput', text: '普通TextInput' })
                .borderWidth(1)
                .width('80%')
                .style(this.style)
                .key('TextInput_04')
              TextArea({ placeholder: '普通TextArea', text: '普通TextArea' })
                .borderWidth(1)
                .width('80%')
                .defaultFocus(true)
                .style(this.style)
                .key('TextArea_04')
              Search({ placeholder: '普通Search', value: '普通Search' })
                .borderWidth(1)
                .width('80%')
                .key('Search_03')
              RichEditor(this.options)
                .placeholder('普通RichEditor')
                .borderWidth(1)
                .width('80%')
                .defaultFocus(true)
                .key('RichEditor_03')
                .onReady(() => {
                  this.controller_richEditor.addTextSpan('12 3',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controller_richEditor.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                })
              RichEditor(this.options2)
                .borderWidth(1)
                .placeholder('绑定自定义键盘的RichEditor')
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .key('RichEditor_04')
            }.margin({ top: 50, left: 20, right: 30 })
          }

        }
        .controlButton({
          icons: {
            hidden: undefined,
            shown: undefined,
            switching: undefined
          }
        })
        .sideBarWidth(150)
        .minSideBarWidth(50)
        .maxSideBarWidth(300)
        .minContentWidth(0)
        .onChange((value: boolean) => {
          console.info('status:' + value)
        })
        .divider({
          strokeWidth: '1vp',
          color: Color.Gray,
          startMargin: '4vp',
          endMargin: '4vp'
        })
        .height('60%')

        Divider()
          .color(Color.Gray)
          .strokeWidth('1vp')
          .margin(5)
        Column() {
          Flex({ justifyContent: FlexAlign.SpaceAround }) {
            Button('内联模式')
              .onClick(() => {
                this.style = TextContentStyle.INLINE
              })
              .key('Button_04')
            Button('普通模式')
              .onClick(() => {
                this.style = TextContentStyle.DEFAULT
              })
              .key('Button_05')
          }.width('100%')

          Row({ space: 5 }) {
            Column({ space: 5 }) {
              TextInput({ placeholder: '普通TextInput', text: '普通TextInput' })
                .borderWidth(1)
                .style(this.style)
                .key('TextInput_05')
              TextArea({ placeholder: '普通TextArea', text: '普通TextArea' })
                .borderWidth(1)
                .style(this.style)
                .key('TextArea_05')
            }.width('50%')

            Column({ space: 5 }) {
              Search({ placeholder: '普通Search', value: '普通Search' })
                .borderWidth(1)
                .key('Search_04')
              RichEditor(this.options)
                .placeholder('普通RichEditor')
                .borderWidth(1)
                .key('RichEditor_05')
                .onReady(() => {
                  this.controller_richEditor.addTextSpan('12 3',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controller_richEditor.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                })
            }.width('50%')
          }

          Row({ space: 5 }) {
            Column() {
              TextInput({
                text: this.inputValue,
                placeholder: '自定义键盘TextInput',
                controller: this.controller_textInput
              })
                .borderWidth(1)
                .defaultFocus(true)
                .enterKeyType(EnterKeyType.Send)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .margin(5)
                .border({ width: 1 })
                .key('TextInput_06')
                .onSubmit((enterKey) => {
                  console.info('TextInput2 onSubmit=' + EnterKeyType[enterKey])
                })
                .onEditChange((isEditing) => {
                  console.info('TextInput2 onEditChange=' + isEditing)
                })
                .style(this.style)

              Search({ placeholder: '自定义键盘Search', value: this.inputValue })
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .borderWidth(1)
                .margin(5)
                .key('Search_05')
            }
            .layoutWeight(2)

            TextArea({
              placeholder: '绑定自定义键盘的TextArea',
              text: this.inputValue,
              controller: this.controller_textArea
            })
              .layoutWeight(1)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .margin(5)
              .border({ width: 1 })
              .enableKeyboardOnFocus(true)
              .style(this.style)
              .key('TextArea_06')

            RichEditor(this.options2)
              .layoutWeight(1)
              .borderWidth(1)
              .key('RichEditor_07')
              .onReady(() => {
                this.controller_richEditor2.addTextSpan('自定义',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 30
                    }
                  })
                this.controller_richEditor2.addImageSpan($r('app.media.startIcon'),
                  {
                    imageStyle:
                    {
                      size: ['57px', '57px']
                    }
                  })
                this.controller_richEditor2.addTextSpan('键盘',
                  {
                    style:
                    {
                      fontColor: Color.Black,
                      fontSize: 30
                    }
                  })
              })
              .aboutToIMEInput((value: RichEditorInsertValue) => {
                console.info('zzz RichEditor2 aboutToIMEInput=' + JSON.stringify(value))
                return true;
              })
              .onIMEInputComplete((value: RichEditorTextSpanResult) => {
                console.info('zzz RichEditor2 onIMEInputComplete=' + JSON.stringify(value))
              })
              .aboutToDelete((value: RichEditorDeleteValue) => {
                console.info('zzz RichEditor2 aboutToDelete=' + JSON.stringify(value))
                return true;
              })
              .onDeleteComplete(() => {
                console.log('zzz RichEditor2 onDeleteComplete')
              })
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
          }
        }.backgroundColor(Color.Pink)
      }
    }
    .title('SoftKeyboardLevel02')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}