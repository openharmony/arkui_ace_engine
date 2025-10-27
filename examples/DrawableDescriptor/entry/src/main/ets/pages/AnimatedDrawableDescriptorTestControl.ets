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
import {
  AnimatedDrawableDescriptor,
  CommonModifier,
  ImageModifier,
  inspector,
  PixelMapDrawableDescriptor,
  router
} from '@kit.ArkUI'
import image from '@ohos.multimedia.image'
import { AnimationController } from "@ohos.arkui.drawableDescriptor"
import cryptoFramework from '@ohos.security.cryptoFramework';
import { deviceInfo } from '@kit.BasicServicesKit'

@Entry
@Component
struct AnimatedDrawableDescriptorTestOne {
  @State raw: Resource = $rawfile("10M.jpg")
  @State animatedDrawable1?: AnimatedDrawableDescriptor | Resource = undefined
  @State animatedDrawable2?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable3?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable4?: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, duration: 2000 })
  @State pixelmapDrawable?: DrawableDescriptor = undefined
  @State pixelmap?: PixelMap = undefined
  @State visible: Visibility = Visibility.Visible
  @State componentSize: number = 100
  @State status: AnimationStatus = AnimationStatus.Running
  @State count: number = 0
  error?: BusinessError<void> = undefined
  modifier: ImageModifier = new ImageModifier()
  arr: Array<string> = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
  frameDurations: Array<number> = [
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
  ]

  aboutToAppear(): void {
    let resManager = this.getUIContext().getHostContext()?.resourceManager
    if (resManager) {
      let buffer1 = resManager.getMediaContentSync($r('app.media.img2')).buffer
      let buffer2 = resManager.getMediaContentSync($r('app.media.flower')).buffer
      let imageSource1 = image.createImageSource(buffer1)
      let imageSource2 = image.createImageSource(buffer2)
      if (imageSource1) {
        imageSource1.createPixelMapList().then((pixelMaps: Array<PixelMap>) => {
          this.animatedDrawable1 =
            new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 3000, autoPlay: false })
        })
      }
      if (imageSource2) {
        imageSource2.createPixelMapList().then((pixelMaps: Array<PixelMap>) => {
          this.animatedDrawable2 =
            new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 3000, autoPlay: true })
        })
      }
    }
  }

  convertToAnimationStatus(status: AnimationStatus): string {
    switch (status) {
      case AnimationStatus.Initial:
        return "Initial";
      case AnimationStatus.Running:
        return "Running";
      case AnimationStatus.Stopped:
        return "Stopped";
      case AnimationStatus.Paused:
        return "Paused";
    }
    return "undefined"
  }

  animatedDrawableStart(drawable: AnimatedDrawableDescriptor | Resource | undefined, id?: string) {
    if (drawable instanceof AnimatedDrawableDescriptor) {
      let aDrawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
      aDrawable?.getAnimationController(id)?.start()
    }
  }

  animatedDrawableStop(drawable: AnimatedDrawableDescriptor | Resource | undefined, id?: string) {
    if (drawable instanceof AnimatedDrawableDescriptor) {
      let aDrawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
      aDrawable?.getAnimationController(id)?.stop()
    }
  }

  animatedDrawablePause(drawable: AnimatedDrawableDescriptor | Resource | undefined, id?: string) {
    if (drawable instanceof AnimatedDrawableDescriptor) {
      let aDrawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
      aDrawable?.getAnimationController(id)?.pause()
    }
  }

  animatedDrawableResume(drawable: AnimatedDrawableDescriptor | Resource | undefined, id?: string) {
    if (drawable instanceof AnimatedDrawableDescriptor) {
      let aDrawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
      aDrawable?.getAnimationController(id)?.resume()
    }
  }

  animatedDrawableOperation(index: number, drawable: AnimatedDrawableDescriptor | Resource | undefined, id?: string) {
    console.info(`Lee, animate drawable operation random, index = ${index}`)
    switch (index) {
      case 0:
        this.animatedDrawableStart(drawable, id)
        break
      case 1:
        this.animatedDrawableStop(drawable, id)
        break
      case 2:
        this.animatedDrawablePause(drawable, id)
        break
      case 3:
        this.animatedDrawableResume(drawable, id)
        break
      default:
        console.info(`Lee, index = ${index}`)
        break;
    }
  }

  clickRandom(index: number) {
    if (index == 1000) {
      return
    }
    setTimeout(() => {
      try {
        let rand = cryptoFramework.createRandom();
        let randData = rand.generateRandomSync(3);
        let num1: number = randData.data[0] * 4 / 255;
        let num2: number = randData.data[1] * 4 / 255;
        let num3: number = randData.data[2] * 4 / 255;
        this.animatedDrawableOperation(Math.floor(num1), this.animatedDrawable1, "Component1")
        this.animatedDrawableOperation(Math.floor(num2), this.animatedDrawable1, "Component2")
        this.animatedDrawableOperation(Math.floor(num3), this.animatedDrawable2)
        this.clickRandom(index++)
        this.count++
      } catch (error) {
        // TODO: Implement error handling.
      }
    }, 100)
  }

  build() {
    Column() {
      Row({ space: 3 }) {
        Image(this.animatedDrawable1)
          .borderColor(Color.Red)
          .borderWidth(1)
          .width(this.componentSize)
          .height(this.componentSize)
          .renderMode(ImageRenderMode.Template)
          .visibility(this.visible)
          .id("Component1")

        Image(this.animatedDrawable1)
          .borderColor(Color.Red)
          .borderWidth(1)
          .width(this.componentSize)
          .height(this.componentSize)
          .renderMode(ImageRenderMode.Template)
          .visibility(this.visible)
          .syncLoad(true)
          .id("Component2")

        Image(this.animatedDrawable2)
          .borderColor(Color.Red)
          .borderWidth(1)
          .width(this.componentSize)
          .height(this.componentSize)
          .renderMode(ImageRenderMode.Template)
          .visibility(this.visible)
          .syncLoad(true)
      }

      Divider().width('100%').height(10)
      Row({ space: 4 }) {
        Button("c1 start")
          .id("c10")
          .onClick(() => {
            this.animatedDrawableStart(this.animatedDrawable1, "Component1")
          })
        Button("c1 stop")
          .id("c11")
          .onClick(() => {
            this.animatedDrawableStop(this.animatedDrawable1, "Component1")
          })
        Button("c1 pause")
          .id("c12")
          .onClick(() => {
            this.animatedDrawablePause(this.animatedDrawable1, "Component1")
          })
        Button("c1 resume")
          .id("c13")
          .onClick(() => {
            this.animatedDrawableResume(this.animatedDrawable1, "Component1")
          })
      }

      Divider().width('100%').height(10)
      Row({ space: 4 }) {
        Button("c2 start")
          .id("c20")
          .onClick(() => {
            this.animatedDrawableStart(this.animatedDrawable1, "Component2")
          })
        Button("c2 stop")
          .id("c21")
          .onClick(() => {
            this.animatedDrawableStop(this.animatedDrawable1, "Component2")
          })
        Button("c2 pause")
          .id("c22")
          .onClick(() => {
            this.animatedDrawablePause(this.animatedDrawable1, "Component2")
          })
        Button("c2 resume")
          .id("c23")
          .onClick(() => {
            this.animatedDrawableResume(this.animatedDrawable1, "Component2")
          })
      }

      Divider().width('100%').height(10)
      Row({ space: 4 }) {
        Button("c3 start")
          .id("c30")
          .onClick(() => {
            this.animatedDrawableStart(this.animatedDrawable2)
          })
        Button("c3 stop")
          .id("c31")
          .onClick(() => {
            this.animatedDrawableStop(this.animatedDrawable2)
          })
        Button("c3 pause")
          .id("c32")
          .onClick(() => {
            this.animatedDrawablePause(this.animatedDrawable2)
          })
        Button("c3 resume")
          .id("c33")
          .onClick(() => {
            this.animatedDrawableResume(this.animatedDrawable2)
          })
      }

      Divider().width('100%').height(10)
      Row({ space: 4 }) {
        Button("c1 status")
          .onClick(() => {
            if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
              let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
              let status = drawable?.getAnimationController("Component1")?.getStatus()
              try {
                this.getUIContext()
                  .getPromptAction()
                  .showToast({ message: `status: ${this.convertToAnimationStatus(status)}` })
              } catch (error) {
                // TODO: Implement error handling.
              }
            }
          })
        Button("c2 status")
          .onClick(() => {
            if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
              let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
              let status = drawable?.getAnimationController("Component2")?.getStatus()
              try {
                this.getUIContext()
                  .getPromptAction()
                  .showToast({ message: `status: ${this.convertToAnimationStatus(status)}` })
              } catch (error) {
                // TODO: Implement error handling.
              }
            }
          })
        Button("c3 status")
          .onClick(() => {
            if (this.animatedDrawable2 instanceof AnimatedDrawableDescriptor) {
              let drawable = this.animatedDrawable2 as AnimatedDrawableDescriptor
              let status = drawable?.getAnimationController()?.getStatus()
              try {
                this.getUIContext()
                  .getPromptAction()
                  .showToast({ message: `status: ${this.convertToAnimationStatus(status)}` })
              } catch (error) {
                // TODO: Implement error handling.
              }
            }
          })
      }
      Divider().width('100%').height(10)
      Row({space: 4}) {
        Button(`点击触发随机调用${this.count}`)
          .onClick(() => {
            this.clickRandom(0)
          })
      }
    }
    .width('100%')
    .height('100%')
  }
}
