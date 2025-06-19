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

import { CoreDataModel } from '../../model/homeModel'
import { coreData } from '../../data/homeData'

@Component
export struct Core1 {
  @Prop ratio: number
  @State cols: Array<number> = new Array<number>(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0)
  @State rows: Array<number> = new Array<number>(0.0, 1.0)
  @State coreData: Array<CoreDataModel> = coreData

  build() {
    Column() {
      List() {
        ForEach<Number>(this.cols, (item1: Number, index: number) => {
          ListItem() {
            Grid() {
              ForEach<Number>(this.rows, (item2: Number, index: number) => {
                GridItem() {
                  Column() {
                    Image(`${this.coreData[item1.valueOf() * 2 + item2.valueOf()].uri}`)
                      .width(40 * this.ratio)
                      .aspectRatio(1)
                      .objectFit(ImageFit.Contain)
                    Text(`${this.coreData[item1.valueOf() * 2 + item2.valueOf()].title}`)
                      .fontSize(15 * this.ratio)
                      .margin({ top: 5 } as Margin)
                  }
                }
                .width('100%')
              }, (item2: Number, index: number) => JSON.stringify(item2.valueOf()))
            }
            .rowsTemplate('1fr 1fr')
            .columnsTemplate('1fr')
          }
          .width('20%')
        }, (item1: Number, index: number) => JSON.stringify(item1.valueOf()))
      }
      .listDirection(Axis.Horizontal)
      .height(160 * this.ratio)
    }
  }
}