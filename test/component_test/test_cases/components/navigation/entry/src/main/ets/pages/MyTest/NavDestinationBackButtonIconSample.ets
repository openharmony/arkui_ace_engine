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
import image from '@ohos.multimedia.image';

const color: ArrayBuffer = new ArrayBuffer(96);
let opts: image.InitializationOptions = { editable: true, pixelFormat: 3, size: { height: 4, width: 6 } }

@Entry
@ComponentV2
export struct NavDestinationBackButtonIconSample {
  @Consumer('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @Local backButtonIcon: ResourceStr | PixelMap = '../../../resources/base/media/icon.png'

  build() {
    NavDestination() {
      Column() {
        Button('NavDestinationBackButtonIcon1')
          .onClick(() => {
            this.backButtonIcon = $r('app.media.startIcon')
          })
        Button('NavDestinationBackButtonIcon2')
          .onClick(async () => {
            await image.createPixelMap(color, opts).then((srcPixelMap: image.PixelMap) => {
              this.backButtonIcon = srcPixelMap;
            })
          })
      }
    }
    .title('NavDestinationBackButtonIcon')
    .backButtonIcon(this.backButtonIcon)
    .id('navDestinationBackButtonIcon')
  }
}