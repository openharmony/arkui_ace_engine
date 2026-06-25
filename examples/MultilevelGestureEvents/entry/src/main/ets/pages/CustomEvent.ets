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
// 使用类来定义矩形区域
class CustomRect {
  public   x: number;
  public   y: number;
  public   width: number;
  public   height: number;
  constructor(x: number, y: number, width: number, height: number) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
  };
};
const rect1 : CustomRect = new CustomRect(10, 10, 80, 40);
const rect2 : CustomRect = new CustomRect(110, 10, 80, 40);
const rect3 : CustomRect = new CustomRect(10, 60, 80, 40);
const rect4 : CustomRect = new CustomRect(0, 0, 200, 150);
@Entry
@Component
struct CustomEvent {
  build() {
    Column() {
      // [Start response_region]
      Column() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))
          .responseRegion([rect1, rect2, rect3])
      }
      .id('ComponentA')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      .responseRegion([rect4])
      //   [End response_region]

      // [Start hittestbehavior_first]
      Column() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))

        Column() {
          Column()
            .id('ComponentD')
            .onTouch(() => {})
            .gesture(TapGesture({count: 1}))
        }
        .id('ComponentC')
        .onTouch(() => {})
        .gesture(TapGesture({count: 1}))
        .hitTestBehavior(HitTestMode.Block)
      }
      .id('ComponentA')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      //   [End hittestbehavior_first]

      // [Start responseregion_second]
      Stack() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))

        Column()
          .id('ComponentC')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))
          .hitTestBehavior(HitTestMode.Transparent)
      }
      .id('Stack A')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      // [End responseregion_second]

      // [Start responseregion_thirdly]
      Column() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))
      }
      .id('ComponentA')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      .hitTestBehavior(HitTestMode.None)
      // [End responseregion_thirdly]

      // [Start responseregion_fourth]
      Stack() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))
        Column() {
          Column()
            .id('ComponentD')
            .onTouch(() => {})
            .gesture(TapGesture({count: 1}))
        }
        .id('ComponentC')
        .onTouch(() => {})
        .gesture(TapGesture({count: 1}))
        .hitTestBehavior(HitTestMode.BLOCK_HIERARCHY)
      }
      .id('Stack A')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      // [End responseregion_fourth]

      // [Start responseregion_fifth]
      Stack() {
        Column()
          .id('ComponentB')
          .onTouch(() => {})
          .gesture(TapGesture({count: 1}))
        Column() {
          Column()
            .id('ComponentD')
            .onTouch(() => {})
            .gesture(TapGesture({count: 1}))
        }
        .id('ComponentC')
        .onTouch(() => {})
        .gesture(TapGesture({count: 1}))
        .hitTestBehavior(HitTestMode.BLOCK_DESCENDANTS)
      }
      .id('Stack A')
      .onTouch(() => {})
      .gesture(TapGesture({count: 1}))
      // [End responseregion_fifth]

      // [Start bindingfirst_gesture]
      Column() {
        Column()
          .id('ComponentB')
          .gesture(TapGesture({count: 1}))
      }
      .id('ComponentA')
      .gesture(TapGesture({count: 1}))
      // [End bindingfirst_gesture]

      // [Start bindingsecond_gesture]
      Column() {
        Column()
          .id('ComponentB')
          .gesture(TapGesture({count: 1}))
      }
      .id('ComponentA')
      .priorityGesture(TapGesture({count: 1}))
      // [End bindingsecond_gesture]

      // [Start bindingthirdly_gesture]
      Column() {
        Column()
          .id('ComponentB')
          .gesture(TapGesture({count: 1}))
      }
      .id('ComponentA')
      .parallelGesture(TapGesture({count: 1}))
      // [End bindingthirdly_gesture]
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
    .justifyContent(FlexAlign.Start)
  }
}