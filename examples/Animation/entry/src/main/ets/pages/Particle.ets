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
struct ParticleExample {
  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Column() {
        Button("demo1")
          .onClick(() => {
            router.pushUrl({ url: 'pages/Particle/Particle1' }, router.RouterMode.Single)
          })
        Button("demo2")
          .onClick(() => {
            router.pushUrl({ url: 'pages/Particle/Particle2' }, router.RouterMode.Single)
          })
          .margin({ top: 100 })
        Button("demo3")
          .onClick(() => {
            router.pushUrl({ url: 'pages/Particle/Particle3' }, router.RouterMode.Single)
          })
          .margin({ top: 100 })
        Button("demo4")
          .onClick(() => {
            router.pushUrl({ url: 'pages/Particle/Particle4' }, router.RouterMode.Single)
          })
          .margin({ top: 100 })
      }
      .height('90%')
      .justifyContent(FlexAlign.Center)
    }.width('100%').margin({ top: 5 })
  }
}