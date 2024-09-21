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
import imageAutoResizeTest from '../MyTest/ImageAutoResizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAutoResizeSample {
  @State autoResize: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(imageAutoResizeTest)
  }

  build() {
    Column() {
      Row() {
        Button('ImageAutoResize1')
          .onClick(() => {
            this.autoResize = !this.autoResize
          })
      }

      Image($r('app.media.city_icon'))
        .width(200)
        .height(200)
        .margin(15)
        .autoResize(this.autoResize)
        .id('imageAutoResize')
    }
  }
}