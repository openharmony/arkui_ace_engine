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
import imageResizableTest from '../MyTest/ImageResizableTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageResizableSample {
  @State resizable: ResizableOptions = {
    slice: {
      top: 30,
      left: 30,
      bottom: 30,
      right: 30
    }
  }

  aboutToAppear(): void {
    loadComponentTestEntry(imageResizableTest)
  }

  build() {
    Column() {
      Image($r('app.media.run_icon'))
        .width(100)
        .height(100)
      Image($r('app.media.run_icon'))
        .width(100)
        .height(100)
        .resizable(this.resizable)
        .objectFit(ImageFit.Contain)
        .id('imageResizeable')
    }
  }
}