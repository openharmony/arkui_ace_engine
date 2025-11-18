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
struct test3 {
  @State color: Color = Color.Blue
  controller: RichEditorController = new RichEditorController()
  controller2: RichEditorController = new RichEditorController()
  controller3: RichEditorController = new RichEditorController()
  controller4: RichEditorController = new RichEditorController()
  controller5: RichEditorController = new RichEditorController()
  controller6: RichEditorController = new RichEditorController()

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

  @Builder
  CustomKeyboardBuilder3() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.controller3.addTextSpan(item + '', {
                offset: this.controller3.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller3.setCaretOffset(this.controller3.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Pink)
  }

  @Builder
  CustomKeyboardBuilder4() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.controller4.addTextSpan(item + '', {
                offset: this.controller4.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller4.setCaretOffset(this.controller4.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Pink)
  }

  @Builder
  CustomKeyboardBuilder5() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.controller5.addTextSpan(item + '', {
                offset: this.controller5.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller5.setCaretOffset(this.controller5.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Pink)
  }

  @Builder
  CustomKeyboardBuilder6() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.controller6.addTextSpan(item + '', {
                offset: this.controller6.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller6.setCaretOffset(this.controller6.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Pink)
  }

  build() {
    Column() {
      Navigation() {
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
        }

        NavRouter() {
          Row() {
            Text(`页面2`)
              .fontSize(22)
              .fontWeight(500)
              .textAlign(TextAlign.Center)
          }
          .width(180)
          .height(72)

          NavDestination() {
            Navigation() {
              Column({ space: 20 }) {
                TextInput({ placeholder: '系统键盘' })
                  .height(100)
                  .borderWidth(1)
                  .borderColor(Color.Red)
                RichEditor({ controller: this.controller3 })// 绑定自定义键盘
                  .onReady(() => {
                    this.controller3.addTextSpan("绑定自定义键盘",
                      {
                        style:
                        {
                          fontColor: Color.Orange,
                          fontSize: 30
                        }
                      })
                  })
                  .customKeyboard(this.CustomKeyboardBuilder3())
                  .margin(10)
                  .border({ width: 1 })
                  .height(100)
                  .borderWidth(1)
                  .borderColor(Color.Red)
                  .width("100%")
                RichEditor({ controller: this.controller4 })// 绑定自定义键盘
                  .onReady(() => {
                    this.controller4.addTextSpan("绑定自定义键盘",
                      {
                        style:
                        {
                          fontColor: Color.Orange,
                          fontSize: 30
                        }
                      })
                  })
                  .customKeyboard(this.CustomKeyboardBuilder4())
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
              }

              NavRouter() {
                Row() {
                  Text(`页面3`)
                    .fontSize(22)
                    .fontWeight(500)
                    .textAlign(TextAlign.Center)
                }
                .width(180)
                .height(72)

                NavDestination() {
                  Column({ space: 20 }) {
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
            }
            .mode(NavigationMode.Split)

          }
        }
      }
      .mode(NavigationMode.Split)

    }
  }
}