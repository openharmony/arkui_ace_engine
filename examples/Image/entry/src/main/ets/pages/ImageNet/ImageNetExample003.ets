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

/*
 * This code defines a component named 'ImagePreLoadMTBF' designed for preloading and displaying images.
 * It includes:
 * - State variables to manage the height, width of images, an array of image source URLs, and a tracker for the
 * current image index.
 * - The 'aboutToAppear' lifecycle method attempts to preload an image from the source array when the component is
 * about to be displayed. 
 */

import { DrawableDescriptor, AnimationOptions, AnimatedDrawableDescriptor } from '@kit.ArkUI'
import { image } from '@kit.ImageKit'
import cacheDownload from '@ohos.request.cacheDownload';

@Entry
@Component
struct ImagePreLoadMTBF {
  @State height1: number = 100;
  @State width1: number = 100;
  @State srcArray: string[] = [
    'xxx01.jpeg',
    'xxx02.jpeg',
    'xxx03.jpg',
    'xxx04.jpg',
    'xxx05.jpg',
    'xxx06.jpg',
    'xxx07.jpg',
    'xxx08.png',
    'xxx09.jpg',
    'xxx10.jpeg',
    'xxx11.webp',
    'xxx12.gif',
    'xxx13.svg'
  ] // 填写具体网络图片地址
  @State srcNum: number = 0;

  async aboutToAppear() {
    cacheDownload.download(this.srcArray[this.srcNum], {})
  }

  build() {
    Column() {
      Button('CancelPreLoad').onClick((event: ClickEvent) => {
        cacheDownload.cancel(this.srcArray[this.srcNum])
      }).width(150).margin(20)

      Image('xxx01.jpeg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx02.jpeg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx03.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx04.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx05.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx06.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx07.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx08.png')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx09.jpg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx10.jpeg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx11.webp')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx12.gif')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })

      Image('xxx13.svg')// 填写具体网络图片地址
        .height(this.height1)
        .width(this.width1)
        .margin({ top: 10 })
    }.margin(20)
  }
}