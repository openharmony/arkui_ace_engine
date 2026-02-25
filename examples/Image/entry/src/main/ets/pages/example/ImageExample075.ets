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
 * 图片滑动查看示例（轮播图）
 */
@Entry
@Component
struct ImageExample075 {
  @State currentIndex: number = 0
  private swiperController: SwiperController = new SwiperController()
  private images: Resource[] = [
    $r('app.media.png'),
    $r('app.media.jpg'),
    $r('app.media.gif'),
    $r('app.media.svg'),
    $r('app.media.app_icon')
  ]

  build() {
    Column() {
      Text('图片滑动查看示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Swiper(this.swiperController) {
        ForEach(this.images, (image: Resource, index: number) => {
          Image(image)
            .width('100%')
            .height(300)
            .objectFit(ImageFit.Cover)
            .borderRadius(15)
        })
      }
      .index(this.currentIndex)
      .autoPlay(true)
      .interval(3000)
      .indicator(true)
      .loop(true)
      .duration(500)
      .itemSpace(10)
      .onChange((index: number) => {
        this.currentIndex = index
      })

      Row({ space: 10 }) {
        Button('上一张')
          .onClick(() => {
            this.swiperController.showPrevious()
          })

        Button('下一张')
          .onClick(() => {
            this.swiperController.showNext()
          })
      }
      .margin({ top: 20 })

      Text('当前: ' + (this.currentIndex + 1) + ' / ' + this.images.length)
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
