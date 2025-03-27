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

import { ProductDataModel } from '../../model/homeModel'
import { productData } from '../../data/homeData'

class GoodListSource implements IDataSource<Number> {
  totalCount(): number {
    return this.num
  }

  getData(index: number): Number {
    return index
  }

  registerDataChangeListener(listener: DataChangeListener) {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener)
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener) {
    const pos = this.listeners.indexOf(listener)
    if (pos >= 0) {
      this.listeners.splice(pos, 1)
    }
  }

  // TODO: fix LazyForEach!
  num: number = 60 // 5040
  listeners: Array<DataChangeListener> = new Array<DataChangeListener>()
}

@Reusable
@Component
struct GGGItem {
  @State data: ProductDataModel = new ProductDataModel('/resources/homeImg/imgLoads/product001.png', 'XX设备 优惠直购', '尊享', '￥4122.0', 0)
  @Link ratio: number
  build() {
    GridItem() {
      Column() {
        Image(this.data.uri)
          .width('100%')
          .height('40%')
          .objectFit(ImageFit.Contain)
          .margin({ bottom: 40 } as Margin)
        Text(this.data.title)
          .fontSize(16 * this.ratio)
          .fontWeight(600)
          .margin({ bottom: 10, left: 10 } as Margin)
        Row() {
          Text(this.data.labels)
            .fontSize(10 * this.ratio)
            .border({ width: 1, color: '#FA808080' } as BorderOptions)
            .margin({ bottom: 2, left: 10 } as Margin)
            .padding(2)
        }
      .margin({ bottom: 2 } as Margin)

        Text(`￥`)
          .fontSize(16 * this.ratio)
          .fontColor(Color.Red)
          .margin({ left: 10 } as Margin)
      }
      .alignItems(HorizontalAlign.Start)
    }
    .width('95%')
    .height(300)
    .border({ width: 1, color: '#70808080', radius: 10 } as BorderOptions)
    .margin({ top: 3, bottom: 3 } as Margin)
    .backgroundColor(Color.White)
  }

  aboutToReuse(param: Record<string, Object>) {
    console.log(`reusing, new data = ${param}`)
    if (param["data"] instanceof ProductDataModel) {
      this.data = param["data"] as ProductDataModel
    }
  }

  aboutToRecycle() {
    console.log("recycling")
  }
}

@Component
export struct GoodsList {
  @State data: GoodListSource = new GoodListSource();
  @State productData: Array<ProductDataModel> = productData
  @Link ListIndex: number
  @Link ratio: number
  @State GridIndex: number = 0
  @State save: number = 0
  @State move: number = 0

  aboutToAppear() {
    this.data = new GoodListSource();
  }

  build() {
    Column() {
      Grid() {
        LazyForEach<Number>(this.data, (item: Number, index: number): void => {
          GGGItem({ data: this.productData[item.valueOf() % 14], ratio: this.ratio })
        }, (item: Number, index: number): string => JSON.stringify(item.valueOf()))
      }
      .columnsTemplate('1fr 1fr')
        .padding({ bottom: 60 } as Padding)
        .onScrollIndex((first: number, second: number) => {
          this.GridIndex = Number(first)
        })
    }
    .width('100%')
    .backgroundColor('#10000000')
  }
}