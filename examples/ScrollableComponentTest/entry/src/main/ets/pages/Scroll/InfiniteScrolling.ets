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

/*用例描述
 本用例使用scroll组件实现了无限滚动效果，适用于阅读场景
 1、onScrollFrameBegin返回每帧将要滚动的偏移量，通过该偏移量计算每页的位移
 2、onScrollFrameBegin返回值设置为0，禁用scroll本身的滚动，通过设置Stack的translate实现滚动效果
*/
/* 关键结构
 |-> Scroll
  |-> Stack
    | -> Stack
    | -> Stack
    | -> Stack
*/

@Entry
@Component
export struct InfiniteScroll {
  @Builder
  doNothingBuilder() {
  };

  @BuilderParam builder: () => void = this.doNothingBuilder;
  @State xOffset: number = 0
  @State yOffset: number = 0
  private selfHeight: number = 0
  scroller: Scroller = new Scroller()

  getOffset(index: number): number {
    let offset = this.yOffset - index * this.selfHeight
    if (offset > 1.5 * this.selfHeight) {
      offset -= 3 * this.selfHeight;
    } else if (offset < -1.5 * this.selfHeight) {
      offset += 3 * this.selfHeight;
    }
    return offset
  }

  build() {
    Scroll(this.scroller) {
      Stack() {
        Stack() {
          Text('3').fontSize(100)
        }
        .backgroundColor(Color.Brown)
        .height('100%')
        .width('100%')
        .translate({ y: -this.getOffset(-1) })

        Stack() {
          Text('1').fontSize(100)
        }
        .backgroundColor(Color.Blue)
        .height('100%')
        .width('100%')
        .translate({ y: -this.getOffset(0) })

        Stack() {
          Text('2').fontSize(100)
        }
        .backgroundColor(Color.Green)
        .height('100%')
        .width('100%')
        .translate({ y: -this.getOffset(1) })
      }
    }
    .clip(true)
    .height('100%')
    .width('100%')
    .backgroundColor(Color.Yellow)
    .onScrollFrameBegin((offset: number) => {
      this.yOffset += offset
      if (this.yOffset < 0) {
        this.yOffset += 3 * this.selfHeight
      } else if (this.yOffset > 3 * this.selfHeight) {
        this.yOffset -= 3 * this.selfHeight
      }
      return { offsetRemain: 0 };
    })
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.selfHeight = newValue.height as number
    })
  }
}