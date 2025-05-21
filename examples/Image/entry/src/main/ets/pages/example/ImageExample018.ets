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
 * 设置HDR图源动态提亮
 */
import { image } from '@kit.ImageKit';

const TAG = 'AceImage';

@Entry
@Component
struct Index {
  @State imgUrl: string = 'img_1';
  @State bright: number = 0; // 默认亮度为0
  aboutToAppear(): void {
    // 获取资源管理器中的媒体资源
    let img = this.getUIContext().getHostContext()?.resourceManager.getMediaByNameSync(this.imgUrl);
    // 创建图片源并获取图片信息
    let imageSource = image.createImageSource(img?.buffer.slice(0));
    let imageInfo = imageSource.getImageInfoSync();
    // 检查图片信息是否获取成功
    if (imageInfo == undefined) {
      console.error(TAG, 'Failed to obtain the image information.');
    } else {
      // 成功获取到图片信息，打印HDR状态
      console.info(TAG, 'imageInfo.isHdr:' + imageInfo.isHdr);
    }
  }

  build() {
    Column() {
      Image($r('app.media.img_1')).width('50%')
        .height('auto')
        .margin({top:160})
        .hdrBrightness(this.bright) // 设置图片的HDR亮度，值由bright状态控制
      Button("图片动态提亮 0->1")
        .onClick(() => {
          // 动画过渡，切换亮度值
          this.getUIContext()?.animateTo({}, () => {
            this.bright = 1.0 - this.bright;
          });
        })
    }
    .height('100%')
    .width('100%')
  }
}