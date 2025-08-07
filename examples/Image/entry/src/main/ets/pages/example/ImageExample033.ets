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
 * Demonstrates how to set the `aiController` property for an Image component
 * to enable AI-based image analysis features like subject detection.
 */
import image from '@ohos.multimedia.image'
import common from '@ohos.app.ability.common';


class MyDataSource implements IDataSource {
  private list: (image.PixelMap | undefined | ResourceStr)[] = []

  constructor(list: (image.PixelMap | undefined | ResourceStr)[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): image.PixelMap | undefined | ResourceStr {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct ImageExample033 {

  build() {
    Column() {
      Image($r('app.media.font3'), {
        types: [ImageAnalyzerType.SUBJECT],
        aiController: new ImageAnalyzerController()
      })
      Image($r('app.media.font2')).overlay(this.builder)
        .width(300).height(200)
    }
  }

  @Builder
  builder() {
    Text('132321321')
      .width(90)
      .height(30)
  }
}