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

import { SearchTextModel, FindTitleTextModel } from '../../model/homeModel'
import { findSearchTextData, findTitleTextData } from '../../data/homeData'
import { ImageItem } from './imageItem'

const items = new Array<Number>(1, 2, 3, 4, 5, 6, 7, 8, 9)

@Component
export struct FindPage {
  @Link bgColor: string
  @Link ratio: number
  @State searchText: Array<SearchTextModel> = findSearchTextData
  @State titleText: Array<FindTitleTextModel> = findTitleTextData

  build() {
    Column() {
      List() {
        ListItem() {
          Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
            Image('/resources/icon/search.png')
              .width(25 * this.ratio)
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .fillColor(Color.Orange)
              .margin({ left: 10 } as Margin)
            Divider()
              .vertical(true)
              .height('8%')
            Swiper() {
              ForEach<SearchTextModel>(this.searchText, (item: SearchTextModel, index: number) => {
                Text(item.searchText)
                  .fontSize(15 * this.ratio)
                  .fontColor(Color.Grey)
              }, (item: SearchTextModel, index: number) => JSON.stringify(item))
            }
            .width('65%')
            .autoPlay(false)
            .loop(true)
            .vertical(true)
            .indicator(false)
            .interval(2000)

            Column() {
              Text('搜索')
                .fontSize(15 * this.ratio)
                .fontColor(Color.White)
                .lineHeight('100%')
                .height('100%')
            }
            .height('100%')
            .width('16%')
            .backgroundColor(Color.Orange)
            .padding(0)
          }
          .height('5%')
          .clip(true)
          .border({ width: 2, color: Color.Orange, radius: 20 } as BorderOptions)
          .width('100%')
          .backgroundColor(Color.White)
        }
        .padding({ left: 10, right: 10 } as Padding)
        .margin({ bottom: 10 } as Margin)

        ListItem() {
          Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
            ForEach(this.titleText, (item: FindTitleTextModel, index: number) => {
              Text(item.titleText)
                .fontSize(15 * this.ratio)
            }, (item: FindTitleTextModel, index: number) => JSON.stringify(item))
          }
          .padding({ left: 15, right: 15 } as Padding)
        }
        .backgroundColor(Color.White)
        .padding({ top: 10, bottom: 10 } as Padding)
        .border({ radius: 10 * this.ratio } as BorderOptions)

        ListItem() {
          Column() {
            ForEach(items, (item: Number, index: number) => {
              Row() {
                Column() {
                  ImageItem({ ratio: this.ratio })
                }
                .padding({ right: 3 } as Padding)

                Column() {
                  ImageItem({ ratio: this.ratio })
                }
                .padding({ right: 3 } as Padding)
              }
              .width('100%')
              .aspectRatio(1.1)
              .margin({ top: 10 } as Margin)
            }, (item: Number, index: number) => JSON.stringify(item.valueOf()))
          }
          .padding({ left: 10, right: 10 } as Padding)
        }
        .width('100%')
        .backgroundColor(Color.White)
        .offset({ x: 0, y: -10 } as Position)
      }
      .backgroundColor('#dfe5e3')
      // TODO: why do I need to add the third argument?
      .onScrollIndex((first: number, last: number, _: number) => {
        if (first != 0) {
          this.bgColor = '#FFFFFF'
        } else {
          this.bgColor = '#dfe5e3'
        }
      })
    }
    .padding({ top: 10, bottom: 10 } as Padding)
  }
}
