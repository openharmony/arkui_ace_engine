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

// xxx.ets
@Entry
@Component
struct test1 {
  @State color: Color = Color.Blue
  controller: RichEditorController = new RichEditorController()
  controller2: RichEditorController = new RichEditorController()

  // 自定义键盘组件
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
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
            Button(item + "")
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

  build() {
    Column({ space: 20 }) {
      TextInput({ placeholder: '系统键盘' })
        .height(100)
        .borderWidth(1)
        .borderColor(Color.Red)
      RichEditor({ controller: this.controller })// 绑定自定义键盘
        .onReady(() => {
          this.controller.addTextSpan("绑定自定义键盘",
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
        .height(100)
        .borderWidth(1)
        .borderColor(Color.Red)
        .width("100%")
      RichEditor({ controller: this.controller2 })// 绑定自定义键盘
        .onReady(() => {
          this.controller2.addTextSpan("绑定自定义键盘",
            {
              style:
              {
                fontColor: Color.Orange,
                fontSize: 30
              }
            })
        })
        .customKeyboard(this.CustomKeyboardBuilder2())
        .margin(10)
        .border({ width: 1 })
        .height(100)
        .borderWidth(1)
        .borderColor(Color.Red)
        .width("100%")
      TextInput({ placeholder: '系统键盘' })
        .height(100)
        .borderWidth(1)
        .borderColor(Color.Red)
      Button('获焦变红，失焦变蓝')
        .backgroundColor(this.color)
        .onFocus(() => {
          this.color = Color.Red
        })
        .onBlur(() => {
          this.color = Color.Blue
        })
    }
  }
}