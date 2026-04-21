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
export function PageThreeBuilder(name: string, param: Object) {
  NavDestinationHideBackButtonpageThree()
}
@Entry
@Component
export struct NavDestinationHideBackButtonpageThree {
  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
  }
  pageInfo: NavPathStack = new NavPathStack();
  @State isHideBackButtonIndex1: number = 0;
  @State isHideBackButton1: (boolean | undefined | null)[] = [true, false, null, undefined];
  @State message: string = 'Hello World'
  @State imagePixelMap: image.PixelMap | undefined = undefined
  async aboutToAppear() {
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.png2'))
  }

  @State isBackButton: (SymbolGlyphModifier | image.PixelMap | ResourceStr | undefined)[] = [$r('app.media.app_icon'), new SymbolGlyphModifier($r('sys.symbol.ohos_star')) ]
  @State isBackButtonIndex: number = 0


  build() {
    NavDestination() {
      Column() {
        Text('改变HideBackButton')
        Row(){
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
          Button("hidebackbutton:undefined")
            .onClick(() => {
              this.isHideBackButtonIndex1 = 3
            })
        }
        Text('改变返回键样式')
        Row(){
          Button("ResourceStr")
            .onClick(() => {
              this.isBackButtonIndex = 0
            })
          Button("SymbolGlyphModifier")
            .onClick(() => {
              this.isBackButtonIndex = 1
            })
          // Button("PixelMap")
          //   .onClick(() => {
          //     this.isBackButtonIndex = 2
          //   })
        }

      }.width('100%').height('100%')
    }
    .mode(NavDestinationMode.STANDARD)
    .title({ main: 'this Page three', sub: 'Page Three' })
    .backButtonIcon(
      this.imagePixelMap
      )
    .hideBackButton(this.isHideBackButton1[this.isHideBackButtonIndex1])
  }
}


