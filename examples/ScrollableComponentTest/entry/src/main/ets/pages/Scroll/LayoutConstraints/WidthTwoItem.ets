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

 /*
  * Description: 滚动组件布局约束范围提升
  * Writer: renxiaowen
  */

@Entry
@Component
struct ScrollWidthTwoItem {

  /*
   * 用例描述：Scroll组件内包含多个子组件，子组件的宽度设置成不同数值，点击按钮切换数值
   * 关键结构：
   * |-> Scroll
   *    |-> Column
   *      |-> Column
   *          |-> Text
   */

  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '9999500px', '1100000px', '16776716px', undefined, null, -1800000000, 1000000
  ];
  scroller: Scroller = new Scroller;

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++;
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      Scroll(this.scroller) {
        Row() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Yellow)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Orange)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Green)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Gray)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Green)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Red)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Brown)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Black)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Blue)

          Column() {
            Text('数值' + this.changeList[this.changeIndex])
              .fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%')
          // 测试点：子组件宽度设置成不同数值
          .width(this.changeList[this.changeIndex])
          .backgroundColor(Color.Grey)

          Column() {
            Button()
          }
        }
      }
      .height(400)
      .scrollable(ScrollDirection.FREE)
      .minZoomScale(1)
      .maxZoomScale(2)
      .enableBouncesZoom(true)
    }
  }
}