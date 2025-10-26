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
import { fileUriService } from '@kit.ScenarioFusionKit'
import { fileUri } from '@kit.CoreFileKit'

@Entry
@Component
struct AnimatedDrawableDescriptorTestDiffType {
  @State base64: string = '';
  error?: BusinessError<void> = undefined
  modifier: ImageModifier = new ImageModifier()
  arr: Array<string> = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
  frameDurations: Array<number> = [
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
    40, 30, 200, 50, 60,
  ]
  @State raw: Resource = $rawfile("10M.jpg")
  @State pixelmapDrawable?: DrawableDescriptor = undefined
  @State pixelmap?: PixelMap = undefined
  @State visible: Visibility = Visibility.Visible
  @State componentSize: number = 100
  @State status: AnimationStatus = AnimationStatus.Running
  @State animatedDrawable1?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable2?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable3?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable4?: AnimatedDrawableDescriptor = undefined
  @State animatedDrawable5?: AnimatedDrawableDescriptor = undefined

  aboutToAppear(): void {
    let files = this.getUIContext().getHostContext()?.filesDir
    let path = "file://" + files + "/flower.gif";
    let resultPath = fileUri.getUriFromPath(path)
    console.info(`Lee, result path = ${resultPath}`)
    this.animatedDrawable1 =
      new AnimatedDrawableDescriptor(path, { iterations: -1, duration: 3000, autoPlay: false })
    this.animatedDrawable2 =
      new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: -1, duration: 3000, autoPlay: false })
    this.animatedDrawable3 =
      new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1, duration: 3000, autoPlay: false })
    this.animatedDrawable4 =
      new AnimatedDrawableDescriptor(this.base64, { duration: 5000, iterations: -1, autoPlay: false })
    this.animatedDrawable5 = new AnimatedDrawableDescriptor("")
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

  build() {
    Column() {
      Image(this.animatedDrawable1)
        .borderColor(Color.Red)
        .borderWidth(1)
        .width(this.componentSize)
        .height(this.componentSize)
        .visibility(this.visible)
        .id("Component1")
      Image(this.animatedDrawable2)
        .borderColor(Color.Red)
        .borderWidth(1)
        .width(this.componentSize)
        .height(this.componentSize)
        .visibility(this.visible)
        .id("Component2")
      Image(this.animatedDrawable3)
        .borderColor(Color.Red)
        .borderWidth(1)
        .width(this.componentSize)
        .height(this.componentSize)
        .visibility(this.visible)
        .id("Component3")
      Image(this.animatedDrawable4)
        .borderColor(Color.Red)
        .borderWidth(1)
        .width(this.componentSize)
        .height(this.componentSize)
        .visibility(this.visible)
        .id("Component4")


      Button("获取所有节点的控制器并start")
        .onClick(() => {
          if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
            let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
            drawable?.getAnimationController("hello")?.start()
          }
        })
      Button("获取所有节点的控制器并stop")
        .onClick(() => {
          if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
            let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
            drawable?.getAnimationController()?.stop()
          }
        })
      Button("获取所有节点的控制器并pause")
        .onClick(() => {
          if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
            let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
            drawable?.getAnimationController()?.pause()
          }
        })
      Button("获取所有节点的控制器并resume")
        .onClick(() => {
          if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
            let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
            drawable?.getAnimationController()?.resume()
          }
        })
      Button("获取当前节点的状态")
        .onClick(() => {
          if (this.animatedDrawable1 instanceof AnimatedDrawableDescriptor) {
            let drawable = this.animatedDrawable1 as AnimatedDrawableDescriptor
            let status = drawable?.getAnimationController()?.getStatus()
            this.getUIContext()
              .getPromptAction()
              .showToast({ message: `number: ${status} status: ${this.convertToAnimationStatus(status)}` })
          }
        })
    }
    .width('100%')
    .height('100%')
  }
}
