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
import imageSourceSizeTest from '../MyTest/ImageSourceSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageSourceSizeSample {
  aboutToAppear(): void {
    loadComponentTestEntry(imageSourceSizeTest)
  }

  build() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .sourceSize({
          width: 10,
          height: 10
        })
        .id('imageSourceSize1')
        .objectFit(ImageFit.ScaleDown)

      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .sourceSize({
          width: 10,
          height: 10
        })
        .id('imageSourceSize2')
        .objectFit(ImageFit.Fill)

      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
        .sourceSize({
          width: 1000,
          height: 1000
        })
        .id('imageSourceSize3')
        .objectFit(ImageFit.ScaleDown)
    }
  }
}