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

/**
 * This demo demonstrates how to achieve the effect of gradually fading the top
 * and bottom edges of a List through the overlay and blendMode properties.
 */

@Entry
@Component
struct FadingEdgeExample {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  @Builder overlayBuilder() {
    Stack().height('100%').width('100%')
      .linearGradient({
        direction: GradientDirection.Bottom, // 渐变方向
        colors: [['#00FFFFFF', 0.0], ['#FFFFFFFF', 0.3], ['#FFFFFFFF', 0.7], ['#00FFFFFF', 1]] // 数组末尾元素占比小于1时满足重复着色效果
      }).blendMode(BlendMode.DST_IN,BlendApplyType.OFFSCREEN)
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
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
      }.width('90%')
      .scrollBar(BarState.Off)
      .overlay(this.overlayBuilder())
      .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}
