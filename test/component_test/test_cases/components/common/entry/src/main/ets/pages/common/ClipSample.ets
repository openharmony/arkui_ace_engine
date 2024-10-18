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

import clipTest from '../MyTest/ClipTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ClipSample {
  @State any_1: boolean | PathAttribute = new Path({ width: 180, height: 180 })
  @State any_2: boolean | EllipseAttribute = new Ellipse({ width: 100, height: 50 })
  @State any_3: CircleAttribute | RectAttribute = new Rect({ width: '70%', height: 40 })

  aboutToAppear(): void {
    loadComponentTestEntry(clipTest)
  }

  build() {
    Row({ space: 10 }) {
      Image($r('app.media.app_icon'))
        .width('180px')
        .height('180px')
        .clip(this.any_1)
        .borderRadius(20)
        .id('imageClip1')

      Image($r('app.media.app_icon'))
        .width('180px')
        .height('180px')
        .clip(this.any_2)
        .borderRadius(20)
        .id('imageClip2')

      Image($r('app.media.app_icon'))
        .width('180px')
        .height('180px')
        .clip(this.any_3)
        .borderRadius(20)
        .id('imageClip3')

      Button('ButtonImageClip')
        .onClick(() => {
          this.any_1 = true
          this.any_2 = false
          this.any_3 = new Circle({ width: 60, height: 60 })
        })
    }
  }
}
