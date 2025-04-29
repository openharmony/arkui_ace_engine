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
 * 播放PixelMap数组动画
 */
import {AnimationOptions, AnimatedDrawableDescriptor} from '@kit.ArkUI'
import { image } from '@kit.ImageKit'

@Entry
@Component
struct ImageExample {
  pixelmaps: Array<PixelMap>  = [];
  options: AnimationOptions = {duration:2000, iterations:1};
  @State animated: AnimatedDrawableDescriptor | undefined = undefined;

  async aboutToAppear() {
    this.pixelmaps = await this.getPixelMaps();
    this.animated = new AnimatedDrawableDescriptor(this.pixelmaps, this.options);
  }

  build() {
    Column() {
      Row() {
        Image(this.animated)
          .width('500px').height('500px')
          .onFinish(() => {
            console.info('finish')
          })
      }.height('50%')
      Row() {
        Button('once').width(100).padding(5).onClick(() => {
          this.options = {duration:2000, iterations:1};
          this.animated = new AnimatedDrawableDescriptor(this.pixelmaps, this.options);
        }).margin(5)
        Button('infinite').width(100).padding(5).onClick(() => {
          this.options = {duration:2000, iterations:-1};
          this.animated = new AnimatedDrawableDescriptor(this.pixelmaps, this.options);
        }).margin(5)
      }
    }.width('50%')
  }

  private async getPixmapListFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: Array<image.PixelMap> = await imageSource.createPixelMapList({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
  }

  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
  }

  private async getPixelMaps() {
    let mypixelmaps:Array<PixelMap> = await this.getPixmapListFromMedia($r('app.media.view'))//gif图, 生成多张PixelMap
    mypixelmaps.push(await this.getPixmapFromMedia($r('app.media.icon'))) //添加一张图片
    return mypixelmaps;
  }
}
