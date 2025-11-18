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
import { AnimatedDrawableDescriptor, LayeredDrawableDescriptor } from '@kit.ArkUI';

@Entry
@Component
struct ImageVisibleTest {
  @State visible: Visibility = Visibility.Visible
  @State src: DrawableDescriptor = new AnimatedDrawableDescriptor($r('app.media.img2'), { iterations: -1 })
  @State wid: number = 100
  @State hei: number = 100

  aboutToAppear(): void {
    try {
      let drawable = this.getUIContext()
        .getHostContext()?.resourceManager.getDrawableDescriptor($r('app.media.layered_image')) as LayeredDrawableDescriptor
    } catch (error) {
      // TODO: Implement error handling.
    }
    let context = this.getUIContext().getHostContext()
  }

  build() {
    Column() {
      Column() {
        Image(this.src)
          .width(this.wid)
          .height(this.hei)
      }
      .backgroundColor(Color.Red)
      .visibility(this.visible)

      Button("点击切换组件大小")
        .onClick(() => {
          this.getUIContext().animateTo({ duration: 2000, curve: Curve.EaseIn }, () => {
            this.wid = 300
            this.hei = 300
          })
        })
    }
    .height('100%')
    .width('100%')
  }
}
