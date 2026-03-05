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
export function SoftKeyboardLevel09Builder(name: string, param: Object) {
  SoftKeyboardLevel09()
}

@Entry
@Component
struct SoftKeyboardLevel09 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State scrollPosition: number = 0
  controller_textInput: TextInputController = new TextInputController()
  controller_textArea: TextAreaController = new TextAreaController()
  scroller: Scroller = new Scroller()

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          GridItem() {
            Button(item)
              .width(80)
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

      Row({ space: 10 }) {
        Button('关闭')
          .onClick(() => {
            this.controller_textInput.stopEditing()
            this.controller_textArea.stopEditing()
          })
        Button('滚动到顶部')
          .onClick(() => {
            this.scroller.scrollToIndex(0)
          })
      }
    }
    .backgroundColor(Color.Gray)
    .padding(10)
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('滚动容器中的输入组件测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .key('Text_Header')

        Column({ space: 10 }) {
          Text('控制按钮')
            .fontSize(14)
            .fontColor(0xCCCCCC)

          Row({ space: 10 }) {
            Button('滚动到顶部')
              .onClick(() => {
                this.scroller.scrollToIndex(0)
              })
              .key('Button_ScrollTop')

            Button('滚动到底部')
              .onClick(() => {
                this.scroller.scrollToIndex(50)
              })
              .key('Button_ScrollBottom')

            Button('滚动到中间')
              .onClick(() => {
                this.scroller.scrollToIndex(25)
              })
              .key('Button_ScrollMiddle')
          }
        }
        .backgroundColor(Color.Pink)
        .padding(10)

        Scroll(this.scroller) {
          Column({ space: 15 }) {
            ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], (item: number) => {
              Column({ space: 10 }) {
                Text(`输入项 ${item}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Bold)

                TextInput({ placeholder: `TextInput ${item}`, text: this.inputValue, controller: this.controller_textInput })
                  .borderWidth(1)
                  .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                  .key(`TextInput_${item}`)

                if (item % 3 === 0) {
                  TextArea({ placeholder: `TextArea ${item}`, text: this.inputValue, controller: this.controller_textArea })
                    .borderWidth(1)
                    .height(60)
                    .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                    .key(`TextArea_${item}`)
                }

                if (item % 5 === 0) {
                  Search({ placeholder: `Search ${item}`, value: this.inputValue })
                    .borderWidth(1)
                    .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                    .key(`Search_${item}`)
                }
              }
              .width('100%')
              .padding(10)
              .backgroundColor(item % 2 === 0 ? Color.White : Color.Grey)
            }, (item: number) => item.toString())
          }
          .width('100%')
        }
        .width('100%')
        .layoutWeight(1)
        .scrollBar(BarState.Auto)
        .edgeEffect(EdgeEffect.Spring)
        .onScroll((xOffset: number, yOffset: number) => {
          this.scrollPosition = yOffset
        })
        .onScrollEdge((side: Edge) => {
          console.info(`ScrollEdge: ${side}`)
        })
        .onScrollEnd(() => {
          console.info('ScrollEnd')
        })

        Divider().color(Color.Gray)

        Column({ space: 5 }) {
          Text('滚动位置信息')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          Text(`当前滚动位置: ${this.scrollPosition}`)
            .fontSize(12)
            .fontColor(0x666666)
        }
        .padding(10)

      }
      .width('100%')
      .height('100%')
      .padding(10)
    }
    .title('SoftKeyboardLevel09')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
