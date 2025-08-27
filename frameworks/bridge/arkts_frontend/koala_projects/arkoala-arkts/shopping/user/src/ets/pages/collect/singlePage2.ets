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

import { GoodsType} from '../../data/singleData';

@Component
export struct SinglePage2 {
  @Prop ratio: number
  @State collectData: GoodsType = new GoodsType('/resources/detailImg/swiper/swiper1.png',
    '【首降600+12期免息】XX/XXMate 40 Pro 5G 全网通 （亮黑色） 超大内存 极快网速 全球n多人的选择，你值得拥有',
    '300+人收藏', '￥4500', true);;

  build() {
    Column() {
      Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Flex({ alignItems: ItemAlign.Center }) {
            Text('宝贝状态')
              .fontSize(12 * this.ratio)
            Image('/resources/icon/sort-down.png')
              .width(10)
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
          }

          Flex({ alignItems: ItemAlign.Center }) {
            Text('收藏时间')
              .fontSize(12 * this.ratio)
            Image('/resources/icon/sort-down.png')
              .width(10)
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
          }
        }
        .width('45%')
      }
      .backgroundColor(Color.White)
      .border({ radius: 5 } as BorderOptions)
      .padding(10)

      Row() {
        Column() {
          Text('最近收藏')
            .fontSize(15 * this.ratio)
            .margin({ top: 10, bottom: 10 } as Margin)
          Text('运动出行')
            .fontSize(15 * this.ratio)
            .margin({ top: 10, bottom: 10 } as Margin)
        }
        .width('25%')
        .height('100%')
        .backgroundColor('#dfe5e3')
        .alignItems(HorizontalAlign.Start)
        .padding({ left: 10 } as Padding)

        Column() {
          Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
            Column() {
              Image(this.collectData.src)
                .width('20%')
                .height('8%')
                .objectFit(ImageFit.Contain)
                .border({ radius: 5 * this.ratio } as BorderOptions)
                .margin({ bottom: 5 } as Margin)
              Text(this.collectData.price)
                .fontSize(12 * this.ratio)
                .fontColor(Color.Red)
                .width('20%')
                .textAlign(TextAlign.Center)
            }
            .alignItems(HorizontalAlign.Start)
            .padding(10)
          }
        }
        .width('75%')
        .height('100%')
        .backgroundColor(Color.White)
      }
    }
  }
}
