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
  @State message: string = 'Image Example';

  build() {
    RelativeContainer() {
      Scroll() {
        Column() {

          Button('router ImageExample001').onClick(() => {
            console.log('router ImageExample001');
            router.pushUrl({ url: 'pages/example/ImageExample001' })
          })

          Button('router ImageExample002').onClick(() => {
            console.log('router ImageExample002');
            router.pushUrl({ url: 'pages/example/ImageExample002' })
          })

          Button('router ImageExample003').onClick(() => {
            console.log('router ImageExample003');
            router.pushUrl({ url: 'pages/example/ImageExample003' })
          })

          Button('router ImageExample004').onClick(() => {
            console.log('router ImageExample004');
            router.pushUrl({ url: 'pages/example/ImageExample004' })
          })

          Button('router ImageExample005').onClick(() => {
            console.log('router ImageExample005');
            router.pushUrl({ url: 'pages/example/ImageExample005' })
          })

          Button('router ImageExample006').onClick(() => {
            console.log('router ImageExample006');
            router.pushUrl({ url: 'pages/example/ImageExample006' })
          })

          Button('router ImageExample007').onClick(() => {
            console.log('router ImageExample007');
            router.pushUrl({ url: 'pages/example/ImageExample007' })
          })

          Button('router ImageExample008').onClick(() => {
            console.log('router ImageExample008');
            router.pushUrl({ url: 'pages/example/ImageExample008' })
          })

          Button('router ImageExample009').onClick(() => {
            console.log('router ImageExample009');
            router.pushUrl({ url: 'pages/example/ImageExample009' })
          })

          Button('router ImageExample010').onClick(() => {
            console.log('router ImageExample010');
            router.pushUrl({ url: 'pages/example/ImageExample010' })
          })

          Button('router ImageExample011').onClick(() => {
            console.log('router ImageExample011');
            router.pushUrl({ url: 'pages/example/ImageExample011' })
          })

          Button('router ImageExample012').onClick(() => {
            console.log('router ImageExample012');
            router.pushUrl({ url: 'pages/example/ImageExample012' })
          })

          Button('router ImageExample013').onClick(() => {
            console.log('router ImageExample013');
            router.pushUrl({ url: 'pages/example/ImageExample013' })
          })

          Button('router ImageExample014').onClick(() => {
            console.log('router ImageExample014');
            router.pushUrl({ url: 'pages/example/ImageExample0140' })
          })

          Button('router ImageExample015').onClick(() => {
            console.log('router ImageExample015');
            router.pushUrl({ url: 'pages/example/ImageExample015' })
          })

          Button('router ImageExample016').onClick(() => {
            console.log('router ImageExample016');
            router.pushUrl({ url: 'pages/example/ImageExample016' })
          })

          Button('router ImageExample017').onClick(() => {
            console.log('router ImageExample017');
            router.pushUrl({ url: 'pages/example/ImageExample017' })
          })

          Button('router ImageModifier001').onClick(() => {
            console.log('router ImageModifierTestCase001');
            router.pushUrl({ url: 'pages/testcase/ImageModifierTestCase001' })
          })

          Button('router ImageModifier002').onClick(() => {
            console.log('router ImageModifier002');
            router.pushUrl({ url: 'pages/testcase/ImageModifier002' })
          })

          Button('router ImageTestcase001').onClick(() => {
            console.log('router ImageTestcase001');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase001' })
          })

          Button('router ImageTestcase002').onClick(() => {
            console.log('router ImageTestcase002');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase002' })
          })

          Button('router ImageTestcase003').onClick(() => {
            console.log('router ImageTestcase003');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase003' })
          })
          Button('router ImageTestcase004').onClick(() => {
            console.log('router ImageTestcase004');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase004' })
          })
          Button('router ImageTestcase005').onClick(() => {
            console.log('router ImageTestcase005');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase005' })
          })
          Button('router ImageTestcase006').onClick(() => {
            console.log('router ImageTestcase006');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase006' })
          })
          Button('router ImageTestcase007').onClick(() => {
            console.log('router ImageTestcase007');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase007' })
          })
          Button('router ImageTestcase008').onClick(() => {
            console.log('router ImageTestcase008');
            router.pushUrl({ url: 'pages/testcase/ImageTestcase008' })
          })

        }
      }
    }
    .height('100%')
    .width('100%')
  }
}
