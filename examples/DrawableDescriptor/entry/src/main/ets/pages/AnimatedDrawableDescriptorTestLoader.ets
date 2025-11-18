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
import { AnimatedDrawableDescriptor } from '@kit.ArkUI'
import { DrawableDescriptorLoadedResult } from '@ohos.arkui.drawableDescriptor'
import { JSON } from '@kit.ArkTS'

@Entry
@Component
struct AnimatedDrawableDescriptorTestLoader {
  @State drawable1: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor($r('app.media.flower'), { iterations: -1 })
  @State drawable2: AnimatedDrawableDescriptor =
    new AnimatedDrawableDescriptor("/data/xxx/xxx", { iterations: -1 })

  build() {
    Column() {
      Button("同步加载drawable1")
        .onClick(() => {
          try {
            let result = this.drawable1.loadSync()
            this.getUIContext().getPromptAction().showToast({ message: `加载成功: ${JSON.stringify(result)}` })
          } catch (e) {
            this.getUIContext().getPromptAction().showToast({ message: `加载失败` })
            console.info(`加载失败`)
          }
        })
      Button("异步加载drawable1")
        .onClick(() => {
          this.drawable1.load().then((result: DrawableDescriptorLoadedResult) => {
            try {
              this.getUIContext().getPromptAction().showToast({ message: `加载成功: ${JSON.stringify(result)}` })
            } catch (error) {
              console.error("show toast failed")
            }
          }).catch((error: BusinessError<void>) => {
            console.error(`Lee, load failed, error = ${JSON.stringify(error)}`)
          })
        })

      Button("同步加载drawable2")
        .onClick(() => {
          try {
            let result = this.drawable2.loadSync()
            this.getUIContext().getPromptAction().showToast({ message: `加载成功: ${JSON.stringify(result)}` })
          } catch (error) {
            console.info(`Lee, load failed, error = ${JSON.stringify(error.code)}`)
            this.getUIContext().getPromptAction().showToast({ message: `加载失败: ${error.code} ${error.message}` })
          }
        })
      Button("异步加载drawable2")
        .onClick(() => {
          this.drawable2.load().catch((error: BusinessError<void>) => {
            try {
              this.getUIContext().getPromptAction().showToast({ message: `加载失败 ${error.code} ${error.message}` })
            } catch (error) {
              // TODO: Implement error handling.
            }
          })
        })
    }
    .height('100%')
    .width('100%')
  }
}
