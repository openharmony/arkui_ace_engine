/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { AnimatedDrawableDescriptor, ImageModifier } from '@kit.ArkUI'
import image from '@ohos.multimedia.image'
import { JSON } from '@kit.ArkTS';

@Entry
@Component
struct AnimatedDrawableDescriptorTestScroll {
  @State animatedDrawable1?: AnimatedDrawableDescriptor | Resource = undefined
  @State animatedDrawable2?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable3?: AnimatedDrawableDescriptor = undefined
  @State pixelmapDrawable?: DrawableDescriptor = undefined
  @State pixelmap?: PixelMap = undefined
  @State visible: Visibility = Visibility.Visible
  modifier: ImageModifier = new ImageModifier()
  arr: Array<string> = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]

  aboutToAppear(): void {
    let resManager = this.getUIContext().getHostContext()?.resourceManager
    if (resManager) {
      try {
        let buffer = resManager.getMediaContentSync($r('app.media.img2')).buffer
        let imageSource = image.createImageSource(buffer)
        if (imageSource) {
          imageSource.createPixelMapList().then((pixelMaps: Array<PixelMap>) => {
            this.animatedDrawable1 = new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 3000})
            this.animatedDrawable2 = new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 5000})
          }).catch((error: BusinessError<void>) => {
            console.error(`Lee, erorr = ${JSON.stringify(error)}`)
          })
        }
      } catch (error) {
        console.error(`Lee, error = ${JSON.stringify(error)}`)
      }
    }
  }

  build() {
    Column() {
      List() {
        ForEach(this.arr, (item: string, index) => {
          ListItem() {
            Row() {
              Image(this.animatedDrawable1)
                .borderColor(Color.Red)
                .borderWidth(1)
                .width(200)
                .height(200)
                .visibility(this.visible)
              Image(this.animatedDrawable2)
                .borderColor(Color.Red)
                .borderWidth(1)
                .width(200)
                .height(200)
                .visibility(this.visible)
            }
          }
        })
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
    .width('100%')
  }
}
