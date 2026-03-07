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

import { BusinessError } from '@kit.BasicServicesKit';
import { image } from '@kit.ImageKit';
import { rcp } from '@kit.RemoteCommunicationKit';

/**
 * 下载与显示网络图片
 */
@Entry
@Component
struct ImageExample002 {
  @State pixelMapImg: PixelMap | undefined = undefined;

  aboutToAppear() {
    try {
      this.requestImageUrl(''); // 请填写一个具体的网络图片地址
    } catch (error) {
      console.error(`aboutToAppear error: ${(error as BusinessError).message}`);
    }
  }

  requestImageUrl(url: string): void {
    const session = rcp.createSession();
    let req = new rcp.Request(url)
    session.fetch(req).then(async (response) => {
      if (response.statusCode === 200) {
        let imgData: ArrayBuffer = response.body as ArrayBuffer;
        console.info(`request image success, size: ${imgData.byteLength}`);
        let imgSource: image.ImageSource = image.createImageSource(imgData);
        let options: image.InitializationOptions = {
          size: { height: 100, width: 100 },
          alphaType: 0,
          editable: false,
          pixelFormat: 3,
          scaleMode: 1
        }
        try {
          await imgSource.createPixelMap(options).then((pixelMap: PixelMap) => {
            console.error('image createPixelMap success');
            this.pixelMapImg = pixelMap;
            imgSource?.release()
          })
        } catch (error) {
          console.error(`createPixelMap error: ${(error as BusinessError).message}`);
        }
      }
    }).catch((error: Error) => {
      console.error(`request image failed: url: ${url}, code: ${error.name}, message: ${error.message}`);
    })
    session.close()
  }

  build() {
    Column() {
      Image(this.pixelMapImg)
        .alt($r('app.media.startIcon'))
        .objectFit(ImageFit.None)
        .width('100%')
        .height('100%')
    }
  }
}
