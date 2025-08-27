/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

import { Cart } from './cart'
import { Other } from './other'

@Component
export struct ShopCart {
  @State cartNum: Array<number> = new Array<number>(0.0, 1.0, 2.0, 3, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)
  @State isSelected1: boolean = false
  @State isSelected2: boolean = false
  @State isOn: boolean = false
  @Prop ratio: number

  build() {
    Column() {
      Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        Row() {
          Text('购物车')
            .fontSize(15 * this.ratio)
            .fontWeight(FontWeight.Bold)
        }

        Flex({ justifyContent: FlexAlign.SpaceAround, alignItems: ItemAlign.Center }) {
          Text('降价')
            .fontSize(14 * this.ratio)
          Text('经常购')
            .fontSize(14 * this.ratio)
          Text('管理')
            .fontSize(14 * this.ratio)
        }
        .width('45%')
      }
      .backgroundColor('#dfe5e3')
      .padding({ top: 8, bottom: 8 } as Padding)

      Scroll() {
        Column() {
          Column() {
            Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
              Row() {
                Image('/resources/icon/smile.png')
                  .width(30 * this.ratio)
                  .aspectRatio(1)
                Text('XX官方旗舰店')
                  .fontSize(15 * this.ratio)
                  .margin({ left: 10 } as Margin)
              }
            }
            .padding({ top: 5, bottom: 5 } as Padding)

            Cart({ ratio: this.ratio })
            Cart({ ratio: this.ratio })
          }
          .padding({ left: 5, right: 5 } as Padding)
          .width('100%')
          .backgroundColor(Color.White)
          .border({ radius: 10 * this.ratio } as BorderOptions)

          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Text('- - - -')
              .fontSize(15 * this.ratio)
              .fontColor('#80FF0000')
              .margin({ right: 10 } as Margin)
            Column() {
              Image('/resources/icon/hearted.png')
                .width('70%')
                .aspectRatio(1)
                .objectFit(ImageFit.Contain)
            }
            .border({ radius: 100 } as BorderOptions)
            .width('5%')
            .aspectRatio(1)

            Text('你可能还喜欢')
              .fontSize(15 * this.ratio)
              .fontColor('#80FF0000')
              .margin({ right: 10 } as Margin)
            Text('- - - -')
              .fontSize(15 * this.ratio)
              .fontColor('#80FF0000')
              .margin({ right: 10 } as Margin)
          }
          .margin({ top: 10, bottom: 10 } as Margin)

          Row() {
            Column() {
              ForEach<Number>(this.cartNum, (item: Number, index: number) => {
                Column() {
                  Other({ item: item.valueOf() % 6, ratio: this.ratio })
                }
              }, (item: Number, index: number) => JSON.stringify(item.valueOf()))
            }
            .margin(2)

            Column() {
              ForEach<Number>(this.cartNum, (item: Number, index: number) => {
                Column() {
                  Other({ item: item.valueOf() % 6, ratio: this.ratio })
                }
              }, (item: Number, index: number) => JSON.stringify(item.valueOf()))
            }
            .margin(2)
          }
          .border({ radius: 10 * this.ratio } as BorderOptions)
          .alignItems(VerticalAlign.Top)
        }
        .margin({ bottom: 30 } as Margin)
      }
      .scrollBar(BarState.Off)
    }
    .padding(5)
    .width('100%')
    .backgroundColor('#dfe5e3')
  }
}
