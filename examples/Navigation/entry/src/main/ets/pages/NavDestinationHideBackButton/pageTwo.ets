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
import { LengthMetrics, PixelMapDrawableDescriptor } from '@kit.ArkUI';
import router from '@ohos.router';
import { TextModifier } from '@ohos.arkui.modifier';
import { SymbolGlyphModifier } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { fileIo as fs } from '@kit.CoreFileKit';

function CreatePixelMap() : image.PixelMap{
  const color: ArrayBuffer = new ArrayBuffer(96); // 96为需要创建的像素buffer大小，取值为：height * width *4
  let opts: image.InitializationOptions = { editable: true, pixelFormat: image.PixelMapFormat.RGBA_8888, size: { height: 4, width: 6 } }
  let pixelMap: image.PixelMap = image.createPixelMapSync(color, opts)
  return pixelMap;
}
@Builder
export function PageTwoBuilder(name: string, param: Object) {
  NavDestinationHideBackButtonpageTwo()
}

@Entry
@Component
export struct NavDestinationHideBackButtonpageTwo {
  @State isHideBackButtonIndex1: number = 0;
  @State isHideBackButton1: (boolean | undefined | null)[] = [true, false, null, undefined];
  @State message: string = 'Hello World'

  build() {
    NavDestination() {
      Column() {
        Text("This is Page Two").fontWeight(50).fontSize(80).backgroundColor(Color.Green)
        Button("hidebackbutton:true")
          .onClick(() => {
            this.isHideBackButtonIndex1 = 0
          })
        Button("hidebackbutton:false")
          .onClick(() => {
            this.isHideBackButtonIndex1 = 1
          })
        Button("hidebackbutton:null")
          .onClick(() => {
            this.isHideBackButtonIndex1 = 2
          })
        Button("hidebackbutton:undefin")
          .onClick(() => {
            this.isHideBackButtonIndex1 = 3
          })
      }.width('100%').height('100%')
    }
    .mode(NavDestinationMode.STANDARD)
    .hideBackButton(this.isHideBackButton1[this.isHideBackButtonIndex1])
  }
}


