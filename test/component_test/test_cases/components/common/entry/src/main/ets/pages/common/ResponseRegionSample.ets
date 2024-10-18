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

import responseRegionTest from '../MyTest/ResponseRegionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ResponseRegionSample {
  @State responseRegionRectangle: Array<Rectangle> | Rectangle = {
    x: '0px',
    y: '0px',
    width: '50px',
    height: '100px'
  }

  aboutToAppear(): void {
    loadComponentTestEntry(responseRegionTest)
  }

  build() {
    Column() {
      Button("Button1")
        .responseRegion({
          x: 0,
          y: 0,
          width: 50,
          height: 100
        })
        .id('buttonResponseRegion1')
      Button("Button2")
        .responseRegion([
          {
            x: 100,
            y: 0,
            width: 50,
            height: 100
          },
          {
            x: 0,
            y: 0,
            width: '50',
            height: '100'
          }
        ])
        .id('buttonResponseRegion2')

      Button("button3")
        .responseRegion(this.responseRegionRectangle)
        .id('buttonResponseRegion3')
      Button('ButtonResponseRegion')
        .onClick(() => {
          this.responseRegionRectangle = {
            x: $r('app.string.commonPosition_length'),
            y: $r('app.string.commonPosition_length'),
            width: $r('app.string.commonImage_width'),
            height: $r('app.string.commonImage_height')
          }
        })
    }.width('100%')
  }
}
