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
import { router } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  @State message: string = 'ImageAnimator Example';

  build() {
    RelativeContainer() {
      Scroll() {
        Column() {

          Button('router ImageAnimatorExample001').onClick(() => {
            console.log('router ImageAnimatorExample001');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample001' })
          })

          Button('router ImageAnimatorExample002').onClick(() => {
            console.log('router ImageAnimatorExample002');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample002' })
          })

          Button('router ImageAnimatorExample003').onClick(() => {
            console.log('router ImageAnimatorExample003');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample003' })
          })

          Button('router ImageAnimatorExample014').onClick(() => {
            console.log('router ImageAnimatorExample014');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample014' })
          })

          Button('router ImageAnimatorExample015').onClick(() => {
            console.log('router ImageAnimatorExample015');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample015' })
          })

          Button('router ImageAnimatorExample016').onClick(() => {
            console.log('router ImageAnimatorExample016');
            router.pushUrl({ url: 'pages/example/ImageAnimatorExample016' })
          })

        }
      }
    }
    .height('100%')
    .width('100%')
  }
}
