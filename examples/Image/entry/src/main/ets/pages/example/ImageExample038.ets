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
 * Image Orientation and Display Test Component
 *
 * This component demonstrates how to load and display images with various Exif orientation values.
 * It allows users to dynamically set the image orientation via buttons and compares the rendering results
 * between using a custom ImageModifier and the default behavior.
 *
 * Features:
 * - Displays images with different EXIF orientations.
 * - Provides buttons to change the current orientation setting.
 * - Compares images with and without custom ImageModifier applied.
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
struct ImageExample038 {
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
      Column() {
        Row() {
          Button('AUTO').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.AUTO
          })
          Button('LEFT').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.LEFT
          })
          Button('RIGHT').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.RIGHT
          })
          Button('UP').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.UP
          })
          Button('DOWN').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.DOWN
          })
        }
        Row() {
          Button('LEFT_MIRROR').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.LEFT_MIRRORED
          })
          Button('RIGHT_MIRROR').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.RIGHT_MIRRORED
          })

        }
        Row() {
          Button('UP_MIRROR').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.UP_MIRRORED
          })
          Button('DOWN_MIRROR').onClick(() => {
            this.selfOrientation = ImageRotateOrientation.DOWN_MIRRORED
          })
        }
      }
      Scroll() {
        Column() {
          Row() {
            Text('Bottom_left  v_mirrored')
            Image($r('app.media.Exif_Bottom_left'))
              .width(100)
              .height(100)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
              .objectFit(ImageFit.Fill)
            Image($r('app.media.Exif_Bottom_left'))
              .width(100)
              .height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
              .objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Bottom_right CW180')
            Image($r('app.media.Exif_Bottom_right'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Bottom_right'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Left_bottom CCW90')
            Image($r('app.media.Exif_Left_bottom'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Left_bottom'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Left_top hm_ccw90')
            Image($r('app.media.Exif_Left_top'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
              .objectFit(ImageFit.Cover)
            Image($r('app.media.Exif_Left_top'))
              .width(100)
              .height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
              .objectFit(ImageFit.Cover)
          }

          Row() {
            Text('Right_bottom hm_cw90')
            Image($r('app.media.Exif_Right_bottom'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Right_bottom'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Right_top cw90')
            Image($r('app.media.Exif_Right_top'))
              .width(100)
              .height(100).objectFit(ImageFit.Fill)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Right_top'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Top_left up')
            Image($r('app.media.Exif_Top_left'))
              .width(100)
              .height(100).objectFit(ImageFit.Fill)

              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Top_left'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }

          Row() {
            Text('Top_right hm')
            Image($r('app.media.Exif_Top_right'))
              .width(100)
              .height(100)
              .objectFit(ImageFit.Fill)
              .attributeModifier(this.enabledModifier ? new MyImageModifier(this.selfOrientation) : new ImageModifier())
              .margin(5)
            Image($r('app.media.Exif_Top_right'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Fill)
          }
        }
      }
    }
    .height('80%')
    .width('100%')
  }
}