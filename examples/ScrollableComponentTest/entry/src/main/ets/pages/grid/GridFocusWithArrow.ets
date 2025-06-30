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

//该示例实现了Grid组件开启方向键换行属性后走焦规则优化
@Entry
@Component
struct GridFocusWithArrow {
  @State numbers: String[] = ['0', '1', '2', '3', '4'];
  @State rowNumbers: String[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'];
  scroller: Scroller = new Scroller();

  build() {
    Column({ space: 5 }) {
      Text('scroll').fontColor(0xCCCCCC).fontSize(9).width('90%')

      Grid(this.scroller) {
        GridItem() {
          Text('A')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('B')
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('C')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }.columnStart(2).columnEnd(3)

        GridItem() {
          Text('D')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }.margin({ left: 50 })

        GridItem() {
          Text('E')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('F')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(180)
            .textAlign(TextAlign.Center)
        }.columnStart(1).columnEnd(2).rowStart(1).rowEnd(2)

        GridItem() {
          Text('G')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('H')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('I')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('J')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('K')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('L')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('M')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('N')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('O')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('P')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(180)
            .textAlign(TextAlign.Center)
        }.rowStart(3).rowEnd(4)

        GridItem() {
          Text('Q')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('R')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('S')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('T')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('U')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('V')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('W')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('X')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('Y')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }

        GridItem() {
          Text('Z')
            .focusable(true)
            .fontSize(16)
            .backgroundColor(0xF9CF93)
            .width('100%')
            .height(80)
            .textAlign(TextAlign.Center)
        }
      }
      .focusWrapMode(FocusWrapMode.WRAP_WITH_ARROW)
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(20)
      .friction(0.6)
      .enableScrollInteraction(true)
      .supportAnimation(false)
      .multiSelectable(false)
      .edgeEffect(EdgeEffect.Spring)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Grey)
      .scrollBarWidth(4)
      .width('90%')
      .backgroundColor(0xDCDCDC)
      .height('80%')
    }.width('100%').margin({ top: 5 })
  }
}