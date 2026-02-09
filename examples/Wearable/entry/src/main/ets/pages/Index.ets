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
import { router } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  @State message: string = 'Wearable ArcButton Examples';

  build() {
    RelativeContainer() {
      Scroll() {
        Column() {
          Text(this.message)
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 20 })

          Button('Example001 - 综合配置')
            .width('80%')
            .margin(10)
            .onClick(() => {
              console.log('router ArcButtonExample001');
              router.pushUrl({ url: 'pages/ArcButton/ArcButtonExample001' })
            })

          Button('Example002 - 进度条按钮')
            .width('80%')
            .margin(10)
            .onClick(() => {
              console.log('router ArcButtonExample002');
              router.pushUrl({ url: 'pages/ArcButton/ArcButtonExample002' })
            })

          Button('Example003 - 样式对比')
            .width('80%')
            .margin(10)
            .onClick(() => {
              console.log('router ArcButtonExample003');
              router.pushUrl({ url: 'pages/ArcButton/ArcButtonExample003' })
            })

          Button('Example004 - 事件与字体')
            .width('80%')
            .margin(10)
            .onClick(() => {
              console.log('router ArcButtonExample004');
              router.pushUrl({ url: 'pages/ArcButton/ArcButtonExample004' })
            })

          Button('Example005 - 进度条与样式冲突')
            .width('80%')
            .margin(10)
            .onClick(() => {
              console.log('router ArcButtonExample005');
              router.pushUrl({ url: 'pages/ArcButton/ArcButtonExample005' })
            })
        }
        .width('100%')
        .padding({ left: 20, right: 20 })
      }
    }
    .height('100%')
    .width('100%')
  }
}
