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
 * Image Display Test Component
 *
 * This component demonstrates how to display images of various formats (PNG, JPG, BMP, SVG, etc.)
 * using both custom `ImageModifier` and default orientation settings.
 * It allows toggling between different image orientations dynamically.
 */
import { ImageModifier } from '@kit.ArkUI';

class MyImageModifier extends ImageModifier {
  private selfOrientation1: ImageRotateOrientation = ImageRotateOrientation.AUTO;

  constructor(orientation: ImageRotateOrientation) {
    super();
    console.log('hello MyImageModifier');
    this.selfOrientation1 = orientation;
  }

  applyNormalAttribute?(instance: ImageAttribute): void {
    instance.orientation(this.selfOrientation1)
  }
}

@Entry
@Component
struct ImageExample037 {
  @State message: string = 'Hello World';
  @State text: string = 'Image组件引入exif规范不支持的图源，设置autoResize属性'
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State resource: Resource = $r('app.media.image')
  @State onTree: boolean = true
  @State rotateDegree: number = 0
  @State fit: ImageFit = ImageFit.None
  res: Resource = $r('app.media.UP')
  @State selfOrientation: ImageRotateOrientation = ImageRotateOrientation.AUTO;
  @State enabledModifier: boolean = true;

  build() {
    Column() {
      Scroll() {
        Column() {
          Row() {
            Text('png')
            Image($r('app.media.both1'))
              .width(100)
              .height(100)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
              .objectFit(ImageFit.Cover)
            Image($r('app.media.dog1'))
              .width(100)
              .height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
              .objectFit(ImageFit.Cover)
          }

          Row() {
            Text('jpg')
            Image($r('app.media.blr_1'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.both2'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('jpeg ')
            Image($r('app.media.CCW1'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.CW1'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('bmp ')
            Image($r('app.media.flowers'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
              .objectFit(ImageFit.Cover)
            Image($r('app.media.font3'))
              .width(100)
              .height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
              .objectFit(ImageFit.Cover)
          }

          Row() {
            Text('svg ')
            Image($r('app.media.200logo'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.animated_circle'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('webp ')
            Image($r('app.media.webp'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.yellow'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('gif ')
            Image($r('app.media.red'))
              .width(100)
              .height(100)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.leaf'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('heif   ')
            Image($r('app.media.heif'))
              .width(100)
              .height(100)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.pink'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
        }
      }
    }
    .height('80%')
    .width('100%')
  }
}