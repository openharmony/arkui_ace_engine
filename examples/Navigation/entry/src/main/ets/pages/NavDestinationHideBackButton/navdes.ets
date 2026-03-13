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
let COLOR2: string = "#80D927D0";
let BLUR_STYLE_1: BlurStyle = BlurStyle.BACKGROUND_THIN;
let BLUR_STYLE_2: BlurStyle = BlurStyle.BACKGROUND_THICK;
let isNavDesModeIndex: number = 0;
let isNavDesMode: NavDestinationMode[] = [NavDestinationMode.STANDARD, NavDestinationMode.DIALOG];


class MainTitleTextModfier extends TextModifier {
  useStyle1: boolean = true;

  applyNormalAttribute(instance: TextModifier): void {
    if (this.useStyle1) {
      console.log(`testTag mainTitle use style1`);
      instance.fontColor('#FFFFC000')
      instance.fontSize(70)
      instance.fontWeight(FontWeight.Bolder)
      instance.fontStyle(FontStyle.Normal)
      instance.textShadow({ radius: 5, offsetX: 9 })
    } else {
      console.log(`testTag mainTitle use style2`);
      instance.fontColor('#FF23A98D')
      instance.fontSize(20)
      instance.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      instance.fontWeight(FontWeight.Lighter)
      instance.fontStyle(FontStyle.Italic)
      instance.textShadow({ radius: 3, offsetX: 3 })
    }
  }
}

class SubTitleTextModfier extends TextModifier {
  useStyle1: boolean = true;
  applyNormalAttribute(instance: TextModifier): void {
    if (this.useStyle1) {
      console.log(`testTag subTitle use style1`);
      instance.fontColor('#FFFFC000')
      instance.fontSize(50)
      instance.fontWeight(FontWeight.Bolder)
      instance.fontStyle(FontStyle.Normal)
      instance.textShadow({ radius: 5, offsetX: 9 })
    } else {
      console.log(`testTag subTitle use style2`);
      instance.fontColor('#FF23A98D')
      instance.fontSize(10)
      instance.fontWeight(FontWeight.Lighter)
      instance.fontStyle(FontStyle.Italic)
      instance.textShadow({ radius: 3, offsetX: 3 })
    }
  }
}
// @Component
// export struct PageTwo {
//   pageInfo: NavPathStack = new NavPathStack();
//   @State isHideBackButtonIndex1: number = 0;
//   @State isHideBackButton1: (boolean | undefined | null)[] = [true, false, null, undefined];
//   @State message: string = 'Hello World'
//
//   build() {
//     NavDestination() {
//       Column() {
//         Text("This is Page Two").fontWeight(50).fontSize(80).backgroundColor(Color.Green)
//         Button("hidebackbutton:true")
//           .onClick(() => {
//             this.isHideBackButtonIndex1 = 0
//           })
//         Button("hidebackbutton:false")
//           .onClick(() => {
//             this.isHideBackButtonIndex1 = 1
//           })
//       }.width('100%').height('100%')
//     }
//
//     .hideBackButton(this.isHideBackButton1[this.isHideBackButtonIndex1])
//     .onBackPressed(() => {
//       this.pageInfo.pop({ number: 1 }) // 弹出路由栈栈顶元素。
//       return true
//     })
//     .onReady((context: NavDestinationContext) => {
//       this.pageInfo = context.pathStack;
//     })
//   }
// }

// @Component
// export struct PageThree {
//   private async getPixmapFromMedia(resource: Resource) {
//     let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
//       bundleName: resource.bundleName,
//       moduleName: resource.moduleName,
//       id: resource.id
//     })
//     let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
//     let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
//       desiredPixelFormat: image.PixelMapFormat.RGBA_8888
//     })
//     await imageSource.release()
//     return createPixelMap
//   }
//   pageInfo: NavPathStack = new NavPathStack();
//   @State isHideBackButtonIndex1: number = 0;
//   @State isHideBackButton1: (boolean | undefined | null)[] = [true, false, null, undefined];
//   @State message: string = 'Hello World'
//   @State imagePixelMap: image.PixelMap | undefined = undefined;
//   async aboutToAppear() {
//     this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.startIcon'))
//   }
//
//   @State isBackButton: (SymbolGlyphModifier | image.PixelMap | ResourceStr | undefined)[] = [$r('app.media.app_icon'), new SymbolGlyphModifier($r('sys.symbol.ohos_star')), this.imagePixelMap ]
//   @State isBackButtonIndex: number = 0
//
//   build() {
//     NavDestination() {
//       Column() {
//         Text("This is Page Two").fontWeight(50).fontSize(80).backgroundColor(Color.Green)
//         Button("hidebackbutton:true")
//           .onClick(() => {
//             this.isHideBackButtonIndex1 = 0
//           })
//         Button("hidebackbutton:false")
//           .onClick(() => {
//             this.isHideBackButtonIndex1 = 1
//           })
//       }.width('100%').height('100%')
//     }
//     .backButtonIcon(this.isBackButton[this.isBackButtonIndex])
//     .hideBackButton(this.isHideBackButton1[this.isHideBackButtonIndex1])
//     .onBackPressed(() => {
//       this.pageInfo.pop({ number: 1 }) // 弹出路由栈栈顶元素。
//       return true
//     })
//     .onReady((context: NavDestinationContext) => {
//       this.pageInfo = context.pathStack;
//     })
//   }
// }

// @Component
// struct NavDes {
//   @State isHideBackButtonIndex: number = 0;
//   @State isHideBackButton: (boolean | undefined | null)[] = [true, false, null, undefined];
//   @State ispaddingnum1: number = 0;
//   @State ispadding1: number[] = [0, 10];
//   @State isDesTool1: boolean = false;
//   @State isHideTitleBar1: boolean = false;
//   @State isHoverMode1Index: number = 0;
//   @State isHoverMode1: (boolean | null | undefined)[] = [false, true, null, undefined];
//   @State isBarStyle1Index: number = 0;
//   @State isBarStyle1: BarStyle[] = [BarStyle.STACK, BarStyle.STANDARD]
//   @State isText1: string[] = ['上下布局', '层叠布局']
//   // 初始化标题栏起始端内间距
//   @State paddingStart1: LengthMetrics = LengthMetrics.vp(0);
//   // 初始化标题栏结束端内间距
//   @State paddingEnd1: LengthMetrics = LengthMetrics.vp(0);
//   // 主标题样式修改器
//   @State mainTitleModifier1: MainTitleTextModfier = new MainTitleTextModfier();
//   // 副标题样式修改器
//   @State subTitleModifier1: SubTitleTextModfier = new SubTitleTextModfier();
//   @State applyModifier1: boolean = false;
//   @State customBuilder: boolean = false;
//   @State useStyle1: boolean = true;
//   @State useColor2: boolean = true;
//   @State useBlur2: boolean = true;
//   @State imagePixelMap: image.PixelMap | undefined = undefined;
//
//   @State menuItems: Array<NavigationMenuItem> = [
//     {
//       value: 'menuItem1',
//       icon: 'resources/base/media/ic', // 图标资源路径
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_wifi')),
//     },
//     {
//       value: 'menuItem2',
//       icon: 'resources/base/media/ic_public_ok.svg', // 图标资源路径
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_folder_badge_plus')).fontColor([Color.Red, Color.Green])
//         .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR),
//     },
//     {
//       value: 'menuItem3',
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
//     },
//     {
//       value: 'menuItem3',
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
//     },
//     {
//       value: 'menuItem3',
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
//     },
//     {
//       value: 'menuItem3',
//       symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs')),
//     },
//   ]
//
//
//   @Builder
//   MyPreview() {
//     Column() {
//       Image($r('app.media.startIcon'))
//         .width(50)
//         .height(50)
//       Text('CustomBuilder')
//     }
//   }
//   @Builder
//   TitleBuilder() {
//     Column() {
//       Marquee({
//         start: true,
//         loop: Number.POSITIVE_INFINITY,
//         fromStart: true,
//         src: 'this.accumulateTime',
//       })
//         .width('100%')
//         .height(130)
//         .fontColor('#ff20abee')
//         .fontSize(60)
//         .fontWeight(FontWeight.Bolder)
//         .backgroundColor('#ff2cc896')
//         .margin({ bottom: 20 })
//     }.height(130).width('100%')
//   }
//
//   build() {
//     // NavDestination() {
//     NavDestination() {
//       Stack({ alignContent: Alignment.Center }) {
//         Column() {
//           Image($r('app.media.startIcon'))// 设置与标题栏高度一致，以便观察STACK效果
//             .height(56)
//             .width('100%')
//           Row() {
//             Button("Padding" + (this.ispadding1[this.ispaddingnum1]))
//               .onClick(() => {
//                 if (this.ispaddingnum1 < this.ispadding1.length) {
//                   this.ispaddingnum1++
//                 }
//                 if (this.ispaddingnum1 == this.ispadding1.length) {
//                   this.ispaddingnum1 = 0
//                 }
//               })
//
//           }
//
//           Row() {
//             Button("当前HoverMode为" + (this.isHoverMode1[this.isHoverMode1Index]))
//               .onClick(() => {
//                 if (this.isHoverMode1Index < this.isHoverMode1.length) {
//                   this.isHoverMode1Index++
//                 }
//                 if (this.isHoverMode1Index == this.isHoverMode1.length) {
//                   this.isHoverMode1Index = 0
//                 }
//               })
//             Button("点击TitleBar" + (this.isHideTitleBar1 ? "显示" : "隐藏"))
//               .onClick(() => {
//                 this.isHideTitleBar1 = !this.isHideTitleBar1
//               })
//           }.padding({ bottom: 5, top: 5 })
//
//           Row() {
//             Button("上下布局STANDARD")
//               .onClick(() => {
//                 this.isBarStyle1Index = 1
//               })
//             Button("层叠布局STACK")
//               .onClick(() => {
//                 this.isBarStyle1Index = 0
//               })
//           }
//
//           //修改间距
//           Row() {
//             Button('apply padding 32vp')
//               .onClick(() => {
//                 this.paddingStart1 = LengthMetrics.vp(32);
//                 this.paddingEnd1 = LengthMetrics.vp(32);
//               })
//
//             Button('apply padding 20vp')
//               .onClick(() => {
//                 this.paddingStart1 = LengthMetrics.vp(20);
//                 this.paddingEnd1 = LengthMetrics.vp(20);
//               })
//           }.padding({ top: 5 })
//
//           //TextModifier修改主副标题文本样式
//           Row() {
//             Text(`apply Modifier`)
//             Toggle({ isOn: this.applyModifier1, type: ToggleType.Switch }).onChange((isOn: boolean) => {
//               this.applyModifier1 = isOn;
//             })
//             Text(`use Style1`)
//             Toggle({ isOn: this.useStyle1, type: ToggleType.Switch }).onChange((isOn: boolean) => {
//               this.mainTitleModifier1.useStyle1 = isOn;
//               this.subTitleModifier1.useStyle1 = isOn;
//               this.useStyle1 = isOn;
//             })
//             Text(`custom builder`)
//             Toggle({ isOn: this.customBuilder, type: ToggleType.Switch }).onChange((isOn: boolean) => {
//               this.customBuilder = isOn;
//             })
//           }.padding({ top: 5 })
//
//           //Color和Blur测试
//           Text("Color和Blur测试").padding({ top: 5 })
//           Row() {
//             Button("switch color")
//               .onClick(() => {
//                 this.useColor2 = !this.useColor2;
//               })
//             Button("switch blur")
//               .onClick(() => {
//                 this.useBlur2 = !this.useBlur2;
//               })
//
//           }
//           Text("更改hidebackbutton状态")
//           Row() {
//             Button("true")
//               .onClick(() => {
//                 this.isHideBackButtonIndex = 0
//               })
//             Button("false")
//               .onClick(() => {
//                 this.isHideBackButtonIndex = 1
//               })
//             Button("null")
//               .onClick(() => {
//                 this.isHideBackButtonIndex = 2
//               })
//             Button("undefined")
//               .onClick(() => {
//                 this.isHideBackButtonIndex = 3
//               })
//           }
//         }
//         .width('100%')
//         .height('100%')
//         .backgroundColor(Color.Gray)
//       }.width('100%')
//       .height('100%')
//     }
//     .title(
//       this.customBuilder ? this.TitleBuilder() :
//       {main: 'NavTitle',
//       sub: 'NavSub'},
//       this.applyModifier1 ?
//         {
//           mainTitleModifier: this.mainTitleModifier1,
//           subTitleModifier: this.subTitleModifier1,
//           paddingStart: this.paddingStart1,
//           paddingEnd: this.paddingEnd1,
//           barStyle: this.isBarStyle1[this.isBarStyle1Index],
//           enableHoverMode: this.isHoverMode1[this.isHoverMode1Index],
//           backgroundColor: this.useColor2 ? COLOR1 : COLOR2,
//           backgroundBlurStyle: this.useBlur2 ? BLUR_STYLE_1 : BLUR_STYLE_2,
//         }
//             : {
//         paddingStart: this.paddingStart1,
//         paddingEnd: this.paddingEnd1,
//         barStyle: this.isBarStyle1[this.isBarStyle1Index],
//         enableHoverMode: this.isHoverMode1[this.isHoverMode1Index],
//         backgroundColor: this.useColor2 ? COLOR1 : COLOR2,
//         backgroundBlurStyle: this.useBlur2 ? BLUR_STYLE_1 : BLUR_STYLE_2,
//       }
//     )
//     .hideBackButton(this.isHideBackButton[this.isHideBackButtonIndex])
//     .padding(this.ispadding1[this.ispaddingnum1])
//     .mode(isNavDesMode[isNavDesModeIndex])
//     .hideTitleBar(this.isHideTitleBar1, true)
//     .menus(this.menuItems)
//   }
// }

@Entry
@Component
struct NavigationExample {
  @State isHideBackButtonIndex: number = 0;
  @State isHideBackButton: (boolean | undefined | null)[] = [true, false, null, undefined];
  // 主标题样式修改器
  @State mainTitleModifier1: MainTitleTextModfier = new MainTitleTextModfier();
  // 副标题样式修改器
  @State subTitleModifier1: SubTitleTextModfier = new SubTitleTextModfier();
  pageInfo: NavPathStack = new NavPathStack()

  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
  private scrollerForScroll: Scroller = new Scroller();
  @State isHideTitleBar: boolean = false;
  @State isBarStyleIndex: number = 0;
  @State isBarStyle: BarStyle[] = [BarStyle.STACK, BarStyle.STANDARD]
  @State isTitleModeIndex: number = 0;
  @State isTitleMode: NavigationTitleMode[] =
    [NavigationTitleMode.Free, NavigationTitleMode.Full, NavigationTitleMode.Mini];
  @State isTitleModeString: string[] = ['Free', 'Full', 'Mini']
  @State isModeIndex: number = 0;
  @State isMode: NavigationMode[] = [NavigationMode.Stack, NavigationMode.Auto, NavigationMode.Split];
  @State isText: string[] = ['上下布局', '层叠布局']
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'menuItem1',
      icon: 'resources/base/media/ic_public_ok.svg', // 图标资源路径
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
    },
  ]


  // @Builder
  // myRouter(name: string, param?: Object) {
  //   if (name === 'NavigationMenu') {
  //     NavDes();
  //   }
  //   if (name === 'PageTwo') {
  //     PageTwo();
  //   }
  //   if (name === 'PageThree') {
  //     PageThree();
  //   }
  // }

  @Builder
  TitleBuilder() {
    Column() {
      Marquee({
        start: true,
        loop: Number.POSITIVE_INFINITY,
        fromStart: true,
        src: 'this.accumulateTime',
      })
        .width('100%')
        .height(130)
        .fontColor('#ff20abee')
        .fontSize(60)
        .fontWeight(FontWeight.Bolder)
        .backgroundColor('#ff2cc896')
        .margin({ bottom: 20 })
    }.height(130).width('100%')
  }

  build() {
    Column() {
      Column() {
        Navigation(this.pageInfo) {
          Column() {
            Scroll(this.scrollerForScroll) {
              Column() {
                Image($r('app.media.startIcon'))// 设置与标题栏高度一致，以便观察STACK效果
                  .height(138)
                  .width('100%')

                Text("改变TitleMode")
                Row(){
                  Button("Free")
                    .onClick(() => {
                        this.isTitleModeIndex = 0
                    })
                  Button("Full")
                    .onClick(() => {
                      this.isTitleModeIndex = 1
                    })
                  Button("MINI")
                    .onClick(() => {
                      this.isTitleModeIndex = 2
                    })
                }
                Text("改变Navigation mode")
                Row(){
                  Button("Stack")
                    .onClick(() => {
                        this.isModeIndex = 0
                    })
                  Button("Auto")
                    .onClick(() => {
                        this.isModeIndex = 1
                    })
                  Button("Split")
                    .onClick(() => {
                        this.isModeIndex = 2
                    })
                }

                Row() {
                  Button("push pageone")
                    .onClick(() => {
                      this.pageInfo.pushPath({ name: 'NavDestinationHideBackButton-pageOne' });
                    })
                }.margin(5)

                Row() {
                  Button("Push Pagetwo")
                    .onClick(() => {
                      this.pageInfo.pushPath({ name: 'NavDestinationHideBackButton-pageTwo' });
                    })
                }.margin(5)

                Row() {
                  Button("Push PageThree")
                    .onClick(() => {
                      this.pageInfo.pushPath({ name: 'NavDestinationHideBackButton-pageThree' });
                    })
                }.margin(5)
                Row() {
                  Button("Push PageFour(Dialog)")
                    .onClick(() => {
                      this.pageInfo.pushPath({ name: 'NavDestinationHideBackButton-pageFour' });
                    })
                }.margin(5)
                Row() {
                  Button("当前hideback: " + (this.isHideBackButton[this.isHideBackButtonIndex]))
                    .onClick(() => {
                      if (this.isHideBackButtonIndex < this.isHideBackButton.length) {
                        this.isHideBackButtonIndex++
                      }
                      if (this.isHideBackButtonIndex == this.isHideBackButton.length) {
                        this.isHideBackButtonIndex = 0
                      }
                    })
                }.margin(5)
              }
            }
          }
          .width('100%')
          .height('100%')
          .backgroundColor(0xDCDCDC)
        }
        .title(
          {
            main: 'NavTitle',
            sub: 'subtitle'
          })
        .hideBackButton(this.isHideBackButton[this.isHideBackButtonIndex])
        .mode(this.isMode[this.isModeIndex])
        .titleMode(this.isTitleMode[this.isTitleModeIndex])
        .hideToolBar(false)
        .hideTitleBar(false)
        .menus(this.menuItems)

      }
    }.width('100%').height('100%').backgroundColor('#F1F3F5')
  }
}


