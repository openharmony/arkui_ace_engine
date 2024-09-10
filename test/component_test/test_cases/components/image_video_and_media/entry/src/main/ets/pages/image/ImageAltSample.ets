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
import imageAltTest from '../MyTest/ImageAltTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAltSample {
  @State altString: string | Resource = "pages/image/image_one.png"
  @State altResource: string | Resource = $r('app.media.city_icon')

  aboutToAppear(): void {
    loadComponentTestEntry(imageAltTest)
  }

  build() {
    Column() {
      Image("https://img.doooor.com/img/forum/201910/10/190503u31393swb09q1bkb.jpg.thumb.jpg")
        .width(110)
        .height(110)
        .alt(this.altResource)
        .id('imageAlt1')
      Button('ImageAlt1')
        .onClick(() => {
          this.altResource = "pages/image/image_two.png"
        })
      Image("https://img.doooor.com/img/forum/201910/10/190503u31393swb09q1bkb.jpg.thumb.jpg")
        .width(110)
        .height(110)
        .alt(this.altString)
        .id('imageAlt2')
      Button('ImageAlt2')
        .onClick(() => {
          this.altString = $r('app.media.run_icon')
        })
    }
  }
}