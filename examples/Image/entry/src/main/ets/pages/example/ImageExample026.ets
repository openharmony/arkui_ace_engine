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
 * 通过objectRepeat属性设置图片的重复样式方式
 */
@Entry
@Component
struct MyComponent {
  build() {
    Column({ space: 10 }) {
      Row({ space: 5 }) {
        Image($r('app.media.ic_public_favor_filled_1'))
          .width(110)
          .height(115)
          .border({ width: 1 })
          .objectRepeat(ImageRepeat.XY)
          .objectFit(ImageFit.ScaleDown)
          // 在水平轴和竖直轴上同时重复绘制图片
          .overlay('ImageRepeat.XY', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
        Image($r('app.media.ic_public_favor_filled_1'))
          .width(110)
          .height(115)
          .border({ width: 1 })
          .objectRepeat(ImageRepeat.Y)
          .objectFit(ImageFit.ScaleDown)
          // 只在竖直轴上重复绘制图片
          .overlay('ImageRepeat.Y', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
        Image($r('app.media.ic_public_favor_filled_1'))
          .width(110)
          .height(115)
          .border({ width: 1 })
          .objectRepeat(ImageRepeat.X)
          .objectFit(ImageFit.ScaleDown)
          // 只在水平轴上重复绘制图片
          .overlay('ImageRepeat.X', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
      }
    }.height(150).width('100%').padding(8)
  }
}