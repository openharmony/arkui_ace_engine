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
//测试代码路径
import navigationBackButtonIconTest from '../MyTest/NavigationBackButtonIconTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import image from '@ohos.multimedia.image';

const color: ArrayBuffer = new ArrayBuffer(96);
let opts: image.InitializationOptions = { editable: true, pixelFormat: 3, size: { height: 4, width: 6 } }

@Entry
@Component
struct NavigationBackButtonIconSample {
  @State backButtonIcon: string | PixelMap | Resource = '../../../resources/base/media/test_image.png'

  aboutToAppear(): void {
    loadComponentTestEntry(navigationBackButtonIconTest)
  }

  build() {
    Column() {
      Navigation() {
      }
      .title('hello')
      .height(100)
      .hideBackButton(false)
      .titleMode(NavigationTitleMode.Mini)
      .backButtonIcon(this.backButtonIcon)
      .id('navigationBackButtonIcon')

      Button('NavigationBackButtonIcon1')
        .onClick(() => {
          this.backButtonIcon = $r('sys.media.ohos_ic_public_phone')
        })
      Button('NavigationBackButtonIcon2')
        .onClick(async () => {
          await image.createPixelMap(color, opts).then((srcPixelMap: image.PixelMap) => {
            this.backButtonIcon = srcPixelMap;
          })
        })
    }
  }
}