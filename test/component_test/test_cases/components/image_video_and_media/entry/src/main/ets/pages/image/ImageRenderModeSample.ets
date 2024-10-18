/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import imageRenderModeTest from '../MyTest/ImageRenderModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageRenderModeSample {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original

  aboutToAppear(): void {
    loadComponentTestEntry(imageRenderModeTest)
  }

  build() {
    Column() {
      Button('ImageRenderMode1')
        .onClick(() => {
          this.renderMode = ImageRenderMode.Template
        })
      Image($r('app.media.test_image'))
        .width(100)
        .height(100)
        .margin(20)
        .renderMode(this.renderMode)
        .id('imageRenderMode')
    }
  }
}