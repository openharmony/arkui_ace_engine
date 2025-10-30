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

import router from '@ohos.router'

@Entry
@Component
struct PopupExample {
  @State customPopup: boolean = false
  @State customPopup2: boolean = false
  @State customPopup3: boolean = false
  @State customPopup4: boolean = false
  @State customPopup5: boolean = false
  @State customPopup6: boolean = false
  @State color: Color = Color.Blue
  controller: RichEditorController = new RichEditorController()
  controller2: RichEditorController = new RichEditorController()

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.controller.addTextSpan(item + '', {
                offset: this.controller.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller.setCaretOffset(this.controller.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
  }

  @Builder
  CustomKeyboardBuilder2() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.controller2.addTextSpan(item + '', {
                offset: this.controller2.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller2.setCaretOffset(this.controller2.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Pink)
  }

  // popup构造器定义弹框内容
  @Builder
  popupBuilder1() {
    Column() {
      RichEditor({ controller: this.controller })// 绑定自定义键盘
        .onReady(() => {
          this.controller.addTextSpan('绑定自定义键盘',
            {
              style:
              {
                fontColor: Color.Orange,
                fontSize: 30
              }
            })
        })
        .customKeyboard(this.CustomKeyboardBuilder())
        .margin(10)
        .border({ width: 1 })
        .height(80)
        .borderWidth(1)
        .borderColor(Color.Red)
        .width('100%')
    }.width(200).height(100).padding(5)
  }

  // popup构造器定义弹框内容
  @Builder
  popupBuilder2() {
    Row() {
      TextInput({ text: 'TextInput' })
    }.width(200).height(100).padding(5)
  }

  // popup构造器定义弹框内容
  @Builder
  popupBuilder3() {
    Row() {
      Button('获焦变红，失焦变蓝')
        .backgroundColor(this.color)
        .onFocus(() => {
          this.color = Color.Red
        })
        .onBlur(() => {
          this.color = Color.Blue
        })
    }.width(200).height(100).padding(5)
  }

  build() {
    Column({ space: 10 }) {
      // CustomPopupOptions 类型设置弹框内容

      Button('使用自定义键盘')
        .onClick(() => {
          this.customPopup3 = !this.customPopup3
        })
        .bindPopup(this.customPopup3,
          {
            builder: this.popupBuilder1,
            placement: Placement.Top,
            mask: { color: '#33000000' },
            popupColor: Color.Yellow,
            primaryButton: {
              value: 'Cancel',
              action: () => {
                this.customPopup3 = !this.customPopup3
              }
            },
            enableArrow: true,
            showInSubWindow: false,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.customPopup3 = false
              }
            }
          })

      Button('使用系统键盘')
        .onClick(() => {
          this.customPopup4 = !this.customPopup4
        })
        .bindPopup(this.customPopup4,
          {
            builder: this.popupBuilder2,
            placement: Placement.Top,
            mask: { color: '#33000000' },
            popupColor: Color.Yellow,
            primaryButton: {
              value: 'Cancel',
              action: () => {
                this.customPopup4 = !this.customPopup4
              }
            },
            enableArrow: true,
            showInSubWindow: false,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.customPopup4 = false
              }
            }
          })

      Button('button')
        .onClick(() => {
          this.customPopup5 = !this.customPopup5
        })
        .bindPopup(this.customPopup5,
          {
            builder: this.popupBuilder3,
            placement: Placement.Top,
            mask: { color: '#33000000' },
            popupColor: Color.Yellow,
            primaryButton: {
              value: 'Cancel',
              action: () => {
                this.customPopup5 = !this.customPopup5
              }
            },
            enableArrow: true,
            showInSubWindow: false,
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.customPopup5 = false
              }
            }
          })
    }.width('100%').padding({ top: 5 })
  }
}