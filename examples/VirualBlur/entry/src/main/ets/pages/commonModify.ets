/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';
@Entry
@Component
struct CommonEts {
  build() {
    Column() {
      Column() {
        Button("当前modify页，点击返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Column() {
        Button("blur")
          .onClick(() => {
            router.pushUrl({ url: 'pages/modify/blur' }, router.RouterMode.Single)
          })
        Button("backdropBlur")
          .onClick(() => {
            router.pushUrl({ url: 'pages/modify/backdropBlur' }, router.RouterMode.Single)
          })
          .margin({ top: 50 })
        Button("backgroundBlurStyle")
          .onClick(() => {
            router.pushUrl({ url: 'pages/modify/backgroundBlurStyle' }, router.RouterMode.Single)
          })
          .margin({ top: 50 })
        Button("foregroundBlurStyle")
          .onClick(() => {
            router.pushUrl({ url: 'pages/modify/foregroundBlurStyle' }, router.RouterMode.Single)
          })
          .margin({ top: 50 })
        // Button("foregroundEffect")
        //   .onClick(() => {
        //     router.pushUrl({ url: 'pages/modify/foregroundEffect' }, router.RouterMode.Single)
        //   })
        //   .margin({ top: 50 })
        Button("backgroundEffect")
          .onClick(() => {
            router.pushUrl({ url: 'pages/modify/backgroundEffect' }, router.RouterMode.Single)
          })
          .margin({ top: 50 })
      }
      .height('90%')
      .justifyContent(FlexAlign.Center)
    }.width('100%').margin({ top: 5 })
  }
}