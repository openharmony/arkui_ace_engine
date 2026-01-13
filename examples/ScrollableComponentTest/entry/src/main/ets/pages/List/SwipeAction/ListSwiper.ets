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

 /*
  * Description: 通过滑动手势PanGesture监听List的滑动方向和距离，每滑一次更新显示相应Item，模拟实现Swiper
  * Writer: dailihuan
  */

@Entry
@Component
struct ListSwiperComponent {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  scroller: Scroller = new Scroller()
  @State currentIndex: number = 0;
  @State isScroll: boolean = false;
  @State positionX: number = 0;
  @State offsetX: number = 0;
  @State preOffsetX: number = 0;

  build() {
    Column() {
      List({ space: 20, initialIndex: 0, scroller: this.scroller }) {
        ForEach(this.arr, (item: number) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
          }
        }, (item: string) => item)
      }
      .listDirection(Axis.Horizontal) // 排列方向
      .scrollBar(BarState.Off)
      .friction(0.6)
      .enableScrollInteraction(false)
      .gesture(
        // 绑定滑动手势
        PanGesture()
        // 当触发滑动手势时，根据回调函数修改组件的布局位置信息
          .onActionUpdate((event: GestureEvent | undefined) => {
            if (event) {
              if (this.currentIndex === this.arr.length - 1 && event.offsetX < 0) {
                this.offsetX = 0;
              }
              this.offsetX = this.offsetX + this.preOffsetX - event.offsetX;
              this.scroller.scrollTo({ xOffset: this.offsetX, yOffset: 0 })
              this.preOffsetX = event.offsetX;
            }
          })
          .onActionEnd((event: GestureEvent | undefined) => {
            const length = this.arr.length;
            if (event) {
              if (event.offsetX < 0) {  //向右滑动
                this.currentIndex = this.currentIndex === length - 1 ? 0 : this.currentIndex + 1;
                this.scroller.scrollToIndex(this.currentIndex)
              }
              if (event.offsetX > 0) { //向左滑动
                this.currentIndex = this.currentIndex === 0 ? this.currentIndex = length - 1 : this.currentIndex - 1;
                this.scroller.scrollToIndex(this.currentIndex)
              }
              setTimeout(() => {
                this.offsetX = this.scroller.currentOffset().xOffset;
                this.preOffsetX = 0;
              }, 500)
            }
          })
      )
      .width('90%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}
