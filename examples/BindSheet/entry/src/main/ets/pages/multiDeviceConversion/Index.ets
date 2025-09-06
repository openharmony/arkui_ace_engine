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

  build() {
    Row(){
      Column(){
        Button($r('app.string.MultiDevice1'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index01'}) })

        Button($r('app.string.MultiDevice2'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index02'}) })

        Button($r('app.string.MultiDevice3'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index03'}) })

        Button($r('app.string.MultiDevice4'))
          .width('100%').fontSize('16vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index08'}) })

        Button($r('app.string.MultiDevice5'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index04'}) })

        Button($r('app.string.MultiDevice6'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index05'}) })

        Button($r('app.string.MultiDevice7'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index06'}) })

        Button($r('app.string.MultiDevice8'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index07'}) })

        Button($r('app.string.MultiDevice9'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index09'}) })

        Button($r('app.string.MultiDevice10'))
          .width('100%').fontSize('20vp')
          .margin({ bottom: 15})
          .onClick(()=>{ router.pushUrl({url: 'pages/multiDeviceConversion/Index10'}) })
      }
      .width('100%')
    }
    .height('100%')
  }
}
