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
import geometryTransitionTest from '../MyTest/GeometryTransitionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GeometryTransitionSample {
  @State isShow: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(geometryTransitionTest)
  }

  build() {
    Stack({ alignContent: Alignment.Center }) {
      if (this.isShow) {
        Image($r('app.media.app_icon'))
          .width(300)
          .height(300)
          .geometryTransition("picture")
          .id('imageGeometryTransition1')
      } else {
        Column() {
          Image($r('app.media.app_icon'))
            .width('30%')
            .height('30%')
        }.width('50%')
        .height('50%')
      }
    }
    .onClick(() => {
      animateTo({ duration: 1000 }, () => {
        this.isShow = !this.isShow
      })
    })
  }
}