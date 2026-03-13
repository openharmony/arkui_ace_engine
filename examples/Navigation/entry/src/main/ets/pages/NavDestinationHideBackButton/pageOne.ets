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

let COLOR1: string = "#809542db";
let BLUR_STYLE_1: BlurStyle = BlurStyle.BACKGROUND_THIN;

function CreatePixelMap() : image.PixelMap{
  const color: ArrayBuffer = new ArrayBuffer(96); // 96为需要创建的像素buffer大小，取值为：height * width *4
  let opts: image.InitializationOptions = { editable: true, pixelFormat: image.PixelMapFormat.RGBA_8888, size: { height: 4, width: 6 } }
  let pixelMap: image.PixelMap = image.createPixelMapSync(color, opts)
  return pixelMap;
}

@Builder
export function PageOneBuilder(name: string, param: Object) {
  NavDestinationHideBackButtonpageOne()
}

@Entry
@Component
export struct NavDestinationHideBackButtonpageOne {
  @State isHideBackButtonIndex: number = 0;
  @State isHideBackButton: (boolean | undefined | null)[] = [true, false, null, undefined];
  @State isDesTool1: boolean = false;
  @State isHideTitleBar1: boolean = false;
  @State isHoverMode1Index: number = 0;
  @State isHoverMode1: (boolean | null | undefined)[] = [false, true, null, undefined];
  @State isBarStyle1Index: number = 0;
  @State isBarStyle1: BarStyle[] = [BarStyle.STACK, BarStyle.STANDARD]
  @State isText1: string[] = ['上下布局', '层叠布局']
  @State applyModifier1: boolean = false;
  @State customBuilder: boolean = false;
  @State useStyle1: boolean = true;
  @State useColor2: boolean = true;
  @State useBlur2: boolean = true;
  @State imagePixelMap: image.PixelMap | undefined = undefined;

  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'menuItem1',
      icon: 'resources/base/media/ic', // 图标资源路径
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),
    },
    {
      value: 'menuItem2',
      icon: 'resources/base/media/ic_public_ok.svg', // 图标资源路径
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontColor([Color.Red, Color.Green])
        .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
    },
    {
      value: 'menuItem3',
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
    }]


  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Center }) {
        Column() {
          Image($r('app.media.startIcon'))// 设置与标题栏高度一致，以便观察STACK效果
            .height(56)
            .width('100%')
          Row() {
            Button("当前HoverMode为" + (this.isHoverMode1[this.isHoverMode1Index]))
              .onClick(() => {
                if (this.isHoverMode1Index < this.isHoverMode1.length) {
                  this.isHoverMode1Index++
                }
                if (this.isHoverMode1Index == this.isHoverMode1.length) {
                  this.isHoverMode1Index = 0
                }
              })
            Button("点击TitleBar" + (this.isHideTitleBar1 ? "显示" : "隐藏"))
              .onClick(() => {
                this.isHideTitleBar1 = !this.isHideTitleBar1
              })
          }.padding({ bottom: 5, top: 5 })

          Row() {
            Button("上下布局STANDARD")
              .onClick(() => {
                this.isBarStyle1Index = 1
              })
            Button("层叠布局STACK")
              .onClick(() => {
                this.isBarStyle1Index = 0
              })
          }
          Text("更改hidebackbutton状态")
          Row() {
            Button("true")
              .onClick(() => {
                this.isHideBackButtonIndex = 0
              })
            Button("false")
              .onClick(() => {
                this.isHideBackButtonIndex = 1
              })
            Button("null")
              .onClick(() => {
                this.isHideBackButtonIndex = 2
              })
            Button("undefined")
              .onClick(() => {
                this.isHideBackButtonIndex = 3
              })
          }
        }
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Gray)
      }.width('100%')
      .height('100%')
    }
    .title(
      {
        main: 'PageFour',
        sub: 'PageFourSub'
      },
      {
        barStyle: this.isBarStyle1[this.isBarStyle1Index],
        enableHoverMode: this.isHoverMode1[this.isHoverMode1Index],
        backgroundColor: COLOR1,
        backgroundBlurStyle: BLUR_STYLE_1,
      }
    )
    .hideBackButton(this.isHideBackButton[this.isHideBackButtonIndex])
    .mode(NavDestinationMode.STANDARD)
    .hideTitleBar(this.isHideTitleBar1, true)
    .menus(this.menuItems)
  }
}

