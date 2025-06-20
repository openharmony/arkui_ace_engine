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
 * 通过DrawableDescriptor显示图片及动画
 */
import {
  DrawableDescriptor,
  PixelMapDrawableDescriptor,
  LayeredDrawableDescriptor,
  AnimatedDrawableDescriptor,
  AnimationOptions
} from '@kit.ArkUI';
import { image } from '@kit.ImageKit';

@Entry
@Component
struct Index {
  // 声明DrawableDescriptor对象
  @State pixmapDesc: DrawableDescriptor | null = null;
  @State pixelMapDesc: PixelMapDrawableDescriptor | null = null;
  @State layeredDesc: LayeredDrawableDescriptor | null = null;
  @State animatedDesc: AnimatedDrawableDescriptor | null = null;
  // 动画配置
  private animationOptions: AnimationOptions = {
    duration: 3000,
    iterations: -1
  };

  async aboutToAppear() {
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resManager) {
      return;
    }
    // 创建普通DrawableDescriptor
    let pixmapDescResult = resManager.getDrawableDescriptor($r('app.media.landscape').id);
    if (pixmapDescResult) {
      this.pixmapDesc = pixmapDescResult as DrawableDescriptor;
    }
    // 创建PixelMapDrawableDescriptor
    const pixelMap = await this.getPixmapFromMedia($r('app.media.landscape'));
    this.pixelMapDesc = new PixelMapDrawableDescriptor(pixelMap);
    // 创建分层图标
    const foreground = await this.getDrawableDescriptor($r('app.media.foreground'));
    const background = await this.getDrawableDescriptor($r('app.media.landscape'));
    this.layeredDesc = new LayeredDrawableDescriptor(foreground, background);
    // 创建动画图片（需加载多张图片）
    const frame1 = await this.getPixmapFromMedia($r('app.media.sky'));
    const frame2 = await this.getPixmapFromMedia($r('app.media.landscape'));
    const frame3 = await this.getPixmapFromMedia($r('app.media.clouds'));
    if (frame1 && frame2 && frame3) {
      this.animatedDesc = new AnimatedDrawableDescriptor([frame1, frame2, frame3], this.animationOptions);
    }
  }

  // 辅助方法：从资源获取PixelMap
  private async getPixmapFromMedia(resource: Resource): Promise<image.PixelMap | undefined> {
    const unit8Array = await this.getUIContext().getHostContext()?.resourceManager.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    });
    if (!unit8Array) {
      return undefined;
    }
    const imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
    const pixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    });
    await imageSource.release();
    return pixelMap;
  }

  // 辅助方法：获取DrawableDescriptor
  private async getDrawableDescriptor(resource: Resource): Promise<DrawableDescriptor | undefined> {
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resManager) {
      return undefined;
    }
    return (resManager.getDrawableDescriptor(resource.id)) as DrawableDescriptor;
  }

  build() {
    RelativeContainer() {
      Column() {

        // 显示普通图片
        Image(this.pixmapDesc)
          .width(100)
          .height(100)
          .border({ width: 1, color: Color.Black })
        // 显示PixelMap图片
        Image(this.pixelMapDesc)
          .width(100)
          .height(100)
          .border({ width: 1, color: Color.Red })
        // 显示分层图标
        if (this.layeredDesc) {
          Image(this.layeredDesc)
            .width(100)
            .height(100)
            .border({ width: 1, color: Color.Blue })
        }
        // 显示动画图片
        if (this.animatedDesc) {
          Image(this.animatedDesc)
            .width(200)
            .height(200)
            .margin({ top: 20 })
        }
      }
    }
    .height('100%')
    .width('100%')
    .margin(50)
  }
}