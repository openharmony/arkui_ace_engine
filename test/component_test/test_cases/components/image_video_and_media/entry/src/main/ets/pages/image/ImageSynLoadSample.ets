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
import imageSynLoadTest from '../MyTest/ImageSynLoadTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageSynLoadSample {
  @State syncLoad: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(imageSynLoadTest)
  }

  build() {
    Column() {
      Button('ImageSynLoad1')
        .onClick(() => {
          this.syncLoad = !this.syncLoad
        })
      Image("https://img.doooor.com/img/forum/201910/10/190503u31393swb09q1bkb.jpg.thumb.jpg")
        .width('40%')
        .margin(15)
        .alt($r('app.media.test_icon'))
        .syncLoad(this.syncLoad)
        .id('imageSynLoad')
    }
  }
}