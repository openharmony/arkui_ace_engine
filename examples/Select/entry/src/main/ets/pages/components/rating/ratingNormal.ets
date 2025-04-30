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
export function RatingNormalBuilder(name: string, param: Object) {
  RatingNormalExample()
}

@Entry
@Component
struct RatingNormalExample {
  pathStack: NavPathStack = new NavPathStack()
  @State rating: number = 3.5;
  @State dateTime: string = '2021/06/02';
  @State context: string = 'Yue';
  @State text: string = '1st Floor';
  @State title: string = 'RatingNormal';
  @State number_1: number = 20;
  @State number_2: number = 0.5;
  @State number_3: number = 5;

  build() {
    NavDestination() {
      Column() {
        Column() {
          Rating({ rating: this.rating, indicator: false })
            .stars(this.number_3)
            .stepSize(this.number_2)
            .margin({ top: 24 })
            .onChange((value: number) => {
              this.rating = value;
            })
          Text('current score is ' + this.rating)
            .fontSize(16)
            .fontColor('rgba(24,36,49,0.60)')
            .margin({ top: 16 })
        }
        .width(360)
        .height(113)
        .backgroundColor('#FFFFFF')
        .margin({ top: 68 })

        Row() {
          Image('common/testImage.jpg')
            .width(40)
            .height(40)
            .borderRadius(this.number_1)
            .margin({ left: 24 })
          Column() {
            Text(this.context)
              .fontSize(16)
              .fontColor('#182431')
              .fontWeight(500)
            Row() {
              Rating({ rating: 3.5, indicator: false })
                .margin({ top: 1, right: 8 })
              Text(this.dateTime)
                .fontSize(10)
                .fontColor('#182431')
            }
          }
          .margin({ left: 12 })
          .alignItems(HorizontalAlign.Start)

          Text(this.text)
            .fontSize(10)
            .fontColor('#182431')
            .position({ x: 295, y: 8 })
        }
        .width(360)
        .height(56)
        .backgroundColor('#FFFFFF')
        .margin({ top: 64 })
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#F1F3F5')
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