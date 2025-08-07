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
 * 通过objectFit属性使图片缩放到高度和宽度确定的框内
 */
@Entry
@Component
struct MyComponent {
  scroller: Scroller = new Scroller();

  build() {
    Scroll(this.scroller) {
      Column() {
        Row() {
          Image($r('app.media.img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 保持宽高比进行缩小或者放大，使得图片完全显示在显示边界内。
            .objectFit(ImageFit.Contain)
            .margin(15)
            .overlay('Contain', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
          Image($r('app.media.ic_img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 保持宽高比进行缩小或者放大，使得图片两边都大于或等于显示边界。
            .objectFit(ImageFit.Cover)
            .margin(15)
            .overlay('Cover', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
          Image($r('app.media.img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 自适应显示。
            .objectFit(ImageFit.Auto)
            .margin(15)
            .overlay('Auto', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
        }

        Row() {
          Image($r('app.media.img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 不保持宽高比进行放大缩小，使得图片充满显示边界。
            .objectFit(ImageFit.Fill)
            .margin(15)
            .overlay('Fill', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
          Image($r('app.media.img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 保持宽高比显示，图片缩小或者保持不变。
            .objectFit(ImageFit.ScaleDown)
            .margin(15)
            .overlay('ScaleDown', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
          Image($r('app.media.img_2'))
            .width(200)
            .height(150)
            .border({ width: 1 })
              // 保持原有尺寸显示。
            .objectFit(ImageFit.None)
            .margin(15)
            .overlay('None', { align: Alignment.Bottom, offset: { x: 0, y: 20 } })
        }
      }
    }
  }
}