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

import { WaterFlowDataSource } from './WaterFlowDataSource';

@Reusable
@Component
struct ReusableItem {
  @State item: number = 0

  aboutToReuse(params: Record<string, number>) {
    console.info('Reuse item:' + this.item + ' for new:' + params.item)
    this.item = params.item;
  }

  aboutToAppear() {
    console.info('item: ' + this.item)
  }

  build() {
    Column() {
      Text('N' + this.item)
        .fontSize(12)
        .height('16')

      Image('res/waterFlow(' + this.item % 5 + ').JPG')
        .objectFit(ImageFit.Fill)
        .width('100%')
        .layoutWeight(1)
    }
  }
}


@Entry
@Component
struct SwiperCustomAnimationExample {
  private controller: SwiperController = new SwiperController()
  dateSource: WaterFlowDataSource = new WaterFlowDataSource()
  private preJumpIndex: number = -1
  private targetIndex: number = -1
  @State currentIndex: number = 0

  jumpToFarIndex(index: number) {
    if (index - this.currentIndex > 10) {
      this.preJumpIndex = index - 3
      this.targetIndex = index
      this.controller.changeIndex(this.preJumpIndex)
    } else {
      this.controller.changeIndex(index)
    }
  }

  build() {
    Column({ space: 5 }) {
      Button('ChangeIndex to 99')
        .onClick(() => {
          this.jumpToFarIndex(99)
        })

      Swiper(this.controller) {
        LazyForEach(this.dateSource, (item: number) => {
          ReusableItem({ item: item })
        }, (item: string) => item)
      }
      .index($$this.currentIndex)
      .loop(false)
      .width('100%')
      .height(300)
      .indicator(false)
      .displayMode(SwiperDisplayMode.STRETCH)
      .onChange((index: number) => {
        if (index == this.preJumpIndex) {
          this.controller.changeIndex(this.targetIndex, true)
          this.preJumpIndex = -1
          this.targetIndex = -1
        }
      })
    }
    .width('100%')
    .margin({ top: 5 })
  }
}
