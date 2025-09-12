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
 * Purpose: This example demonstrates how to load a network image using HTTP and decode it into a PixelMap for display.
 * It also shows how to apply dynamic image attributes such as dynamicRangeMode and borderRadius via a modifier.
 */
import http from '@ohos.net.http';
import ResponseCode from '@ohos.net.http';
import image from '@ohos.multimedia.image';
import { BusinessError } from '@ohos.base';
import { rcp } from '@kit.RemoteCommunicationKit';

class ImageModifier implements AttributeModifier<ImageAttribute> {
  public value: DynamicRangeMode = DynamicRangeMode.HIGH
  public bo: number = 10

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.dynamicRangeMode(this.value)
    instance.borderRadius(this.bo)
  }
}

@Entry
@Component
struct DarkModeTest {
  @State modifier: ImageModifier = new ImageModifier()
  @State show: Boolean = true
  @State imagePixelMap: PixelMap | undefined = undefined;

  httpRequest() {
    const session = rcp.createSession();
    let req = new rcp.Request('')// 填写具体网络图片地址
    session.fetch(req).then(async (response)=> {
      if (response.statusCode === 200) {
        console.error(`WYXX http reqeust success.`);
        let imageData: ArrayBuffer = response.body as ArrayBuffer;
        let imageSource: image.ImageSource = image.createImageSource(imageData);
        console.error(`WYXX http reqeust size = ${imageData.byteLength}`);

        class Tmp {
          public height: number = 100
          public width: number = 100
        }

        let options: Record<string, number | boolean | Tmp> = {
          'alphaType': 0, // 透明度
          'editable': false, // 是否可编辑
          'pixelFormat': 3, // 像素格式
          'scaleMode': 1, // 缩略值
          'size': { height: 100, width: 100 }
        } // 创建图片大小
        await imageSource.createPixelMap(options).then((pixelMap: PixelMap) => {
          this.imagePixelMap = pixelMap
          imageSource?.release()
        })
      }

    }).catch((error: Error) => {
      console.error(`WYXX http reqeust failed with. Code: ${error.name}, message: ${error.message}`);
    })
    session.close()
  }

  build() {
    Column() {
      Button('Show')
        .onClick(() => {
          if (this.show) {
            this.show = false;
          } else {
            this.show = true;
          }
        })
      if (this.show) {
        Image($r('app.media.svg_text'))
          .height(200)
          .width(200)
          .fillColor(Color.Red)
        Divider()
        Image($r('app.media.cat'))
          .height('350vp')
          .width('350vp')
          .attributeModifier(this.modifier)
          .onClick(() => {
            this.modifier.value = DynamicRangeMode.CONSTRAINT
            this.modifier.bo = 30
          })
          .renderMode(ImageRenderMode.Original)
          .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
          .enhancedImageQuality(image.ResolutionQuality.LOW)
      }
    }.backgroundColor('#CCCCCC').width('100%').height('100%')
  }
}