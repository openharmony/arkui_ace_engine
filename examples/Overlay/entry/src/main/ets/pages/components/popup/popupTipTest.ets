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

@Builder
export function PopupTipBuilder(name: string, param: Object) {
  TipsExample()
}

@Entry
@Component
struct TipsExample {
  pathStack: NavPathStack = new NavPathStack()
  build() {
    NavDestination() {
      Column({ space: 100 }) {
        Text('测试bindTips')
          .textAlign(TextAlign.Center)
          .fontSize(20)
        Button('Hover Tips')
          .bindTips('test Tips', {
            appearingTime: 700,
            disappearingTime: 300,
            appearingTimeWithContinuousOperation: 300,
            disappearingTimeWithContinuousOperation: 0,
            enableArrow:true,
          })
          .position({ x: 100, y: 250 })

        Button('Hover Tips')
          .bindTips('test Tips', {
            appearingTime: 700,
            disappearingTime: 300,
            appearingTimeWithContinuousOperation: 300,
            disappearingTimeWithContinuousOperation: 0,
            enableArrow:true,
          })
          .position({ x: 100, y: 350 })

        Button('Hover Tips跟随鼠标')
          .bindTips('test Tips', {
            appearingTime: 700,
            disappearingTime: 300,
            appearingTimeWithContinuousOperation: 300,
            disappearingTimeWithContinuousOperation: 0,
            enableArrow: true,
            showAtAnchor: TipsAnchorType.CURSOR,
          })
          .position({ x: 300, y: 250 })

        Button('Hover Tips跟随鼠标')
          .bindTips('1234567890'.repeat(20), {
            appearingTime: 700,
            disappearingTime: 300,
            appearingTimeWithContinuousOperation: 300,
            disappearingTimeWithContinuousOperation: 0,
            enableArrow: true,
            showAtAnchor: TipsAnchorType.CURSOR,
          })
          .position({ x: 300, y: 350 })
      }
      .width('100%')
      .padding({ top: 5 })
    }
    .title('PopupTipTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}