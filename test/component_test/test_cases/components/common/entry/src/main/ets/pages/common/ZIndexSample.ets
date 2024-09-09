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
import zIndexTest from '../MyTest/ZIndexTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ZIndexSample {
  @State zIndexNumber: number = 1

  aboutToAppear(): void {
    loadComponentTestEntry(zIndexTest)
  }

  build() {
    Column() {
      Stack() {
        Text('textZIndex1')
          .size({ width: '40%', height: '30%' }).backgroundColor(0xbbb2cb)
          .zIndex(2)
          .id('textZIndex1')
        Text('textZIndex2')
          .size({ width: '70%', height: '50%' })
          .backgroundColor(0xd2cab3)
          .align(Alignment.TopStart)
          .zIndex(this.zIndexNumber)
          .id('textZIndex2')
      }.width('100%').height(200)

      Button('ButtonZIndex1')
        .onClick(() => {
          this.zIndexNumber = 3
        })
    }.width('100%').height(200)
  }
}