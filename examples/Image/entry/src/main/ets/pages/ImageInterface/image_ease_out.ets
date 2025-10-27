/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
@Entry
@Component
struct AttrAnimationExample {
  @State widthSize: number = 250
  @State heightSize: number = 100

  build() {
    Column() {
      Image($r('app.media.jpg'))
        .width('1260px')
        .height('813px')
        .padding({left: 4, right: 4})
        .objectFit(ImageFit.Cover)
      Image($r('app.media.jpg'))
        .width('1260px')
        .height('813px')
        .objectFit(ImageFit.Contain)
        .padding({left: 4, right: 4})
      Text('222')
        .onClick(() => {
          this.widthSize = 1
          this.heightSize = 60
        })
        .margin(30)
        .width(this.widthSize)
        .height(this.heightSize)
      .animation({
        duration: 2000,
        curve: Curve.EaseOut,
        iterations: 1,
        playMode: PlayMode.Normal
      })
      Image($r('app.media.startIcon'))
        .onClick(() => {
          this.widthSize = 0
          this.heightSize = 60
        })
        .margin(30)
        .width(this.widthSize)
        .height(this.heightSize)
        .animation({
          duration: 2000,
          curve: Curve.EaseOut,
          iterations: 1,
          playMode: PlayMode.Normal
        })
    }
    .width('100%').margin({ top: 20 })
  }
}
