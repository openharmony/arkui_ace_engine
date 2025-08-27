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
export function RatingStarStyleBuilder(name: string, param: Object) {
  RatingStarStyleExample()
}

@Entry
@Component
struct RatingStarStyleExample {
  pathStack: NavPathStack = new NavPathStack()
  @State rating: number = 3.5;
  @State title: string = 'RatingStarStyle';
  @State indicator: boolean = false;

  build() {
    NavDestination() {
      Column() {
        Rating({ rating: this.rating, indicator: this.indicator })
          .stars(5)
          .stepSize(0.5)
          .starStyle({
            backgroundUri: '/common/imag1.png',
            foregroundUri: '/common/imag2.png',
            secondaryUri: '/common/imag3.png'
          })
          .margin({ top: 24 })
          .onChange((value: number) => {
            this.rating = value;
          })
        Text('current score is ' + this.rating)
          .fontSize(16)
          .fontColor('rgba(24,36,49,0.60)')
          .margin({ top: 16 })
      }
      .width('100%')
      .height('100%')
      .backgroundColor($r('app.color.background_color_9'))
    }
    .title(this.title)
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}