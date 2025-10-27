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

import { prompt, SymbolGlyphModifier } from '@kit.ArkUI';
import window from '@ohos.window';
import base from '@ohos.base';
import { TextModifier } from '@ohos.arkui.modifier';

class MainTitleTextModifier extends TextModifier {
  useStyle1: boolean = true;
  applyNormalAttribute(instance: TextModifier): void {
    if (this.useStyle1) {
      console.log(`testTag mainTitle use style1`);
      instance.fontColor('#FFFFC000')
      instance.fontSize(35)
      instance.fontWeight(FontWeight.Bolder)
      instance.fontStyle(FontStyle.Normal)
      instance.textShadow({radius: 5, offsetX: 9})
    } else {
      console.log(`testTag mainTitle use style2`);
      instance.fontColor('#FF23A98D')
      instance.fontSize(20)
      instance.heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      instance.fontWeight(FontWeight.Lighter)
      instance.fontStyle(FontStyle.Italic)
      instance.textShadow({radius: 3, offsetX: 3})
    }
  }
}

class SubTitleTextModifier extends TextModifier {
  useStyle1: boolean = true;
  applyNormalAttribute(instance: TextModifier): void {
    if (this.useStyle1) {
      console.log(`testTag subTitle use style1`);
      instance.fontColor('#FFFFC000')
      instance.fontSize(15)
      instance.fontWeight(FontWeight.Bolder)
      instance.fontStyle(FontStyle.Normal)
      instance.textShadow({radius: 5, offsetX: 9})
    } else {
      console.log(`testTag subTitle use style2`);
      instance.fontColor('#FF23A98D')
      instance.fontSize(10)
      instance.fontWeight(FontWeight.Lighter)
      instance.fontStyle(FontStyle.Italic)
      instance.textShadow({radius: 3, offsetX: 3})
    }
  }
}

@Entry
@Component
struct Test2 {
  private stack: NavPathStack = new NavPathStack();
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'hello',
      icon: $r('app.media.background'),
      action: () => {
        prompt.showToast({
          message: 'Hello world'
        })
      },
      isEnabled: true
    },
    {
      value: 'hello',
      icon: $r('app.media.foreground'),
      isEnabled: false
    },
    {
      value: $r('app.media.startIcon'),
      icon: $r('app.media.startIcon'),
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs'))
    },
    {
      value: $r('app.float.menuValFloat'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.float.menuValFloat')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValString')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValLongString')
    },
  ]
  @State menuItems2: Array<NavigationMenuItem> = [
    {
      value: 'hello',
      icon: $r('app.media.startIcon'),
      action: () => {
        console.log('Hello world')
      },
      isEnabled: true
    },
    {
      value: 'hello',
      icon: $r('app.media.startIcon'),
      isEnabled: false
    },
    {
      value: $r('app.media.startIcon'),
      icon: $r('app.media.foreground'),
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs'))
    },
    {
      value: $r('app.float.menuValFloat'),
      icon: $r('app.media.foreground')
    },
    {
      value: $r('app.string.menuValString'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.media.startIcon'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.float.menuValFloat')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValString')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValLongString')
    },
  ]
  @State barStyle: BarStyle = BarStyle.STANDARD

  private myWindow: window.Window | null = null;

  createWindow() {
    try {
      window.createWindow({name: 'testWindow', windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          let ls = new LocalStorage();
          this.myWindow?.loadContent('pages/vvv/Test2', ls)
            .then(() => {
              console.log(`testTag success to loadContent`)
              this.myWindow?.showWindow().then(() => {
                console.log(`testTag success to showWindow`)
                this.myWindow?.resize(1000, 1000);
                this.myWindow?.moveWindowTo(50, 200);
              }).catch((e: base.BusinessError) => {
                console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
              });
            }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
          })

        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

  @Builder
  PageBuilder(name: string) {
    pageTwo()
  }

  @State subTitle: string | Resource = 'subTitle'
  @State mainTitle: string | Resource = 'mainTitle'
  @State colorFlag: boolean = false;
  scroller: Scroller = new Scroller()
  @State modifierTitleFlag: boolean = false;
  @State mainTitleModifier: MainTitleTextModifier = new MainTitleTextModifier();
  @State subTitleModifier: SubTitleTextModifier = new SubTitleTextModifier();
  @State titleMode: NavigationTitleMode = NavigationTitleMode.Free;
  @State model: NavigationMode = NavigationMode.Auto;
  @State navBarPosition: NavBarPosition = NavBarPosition.Start
  build() {
    Navigation(this.stack) {
      Scroll(this.scroller) {
        Column() {
          Row() {
            Text(`title set backgroundColor&blur`).fontSize(10)
            Toggle({ isOn: this.colorFlag, type: ToggleType.Switch }).onChange((isOn: boolean) => {
              this.colorFlag = isOn;
            })
          }

          Row() {
            Text(`title modifier`).fontSize(10)
            Toggle({ isOn: this.modifierTitleFlag, type: ToggleType.Switch }).onChange((isOn: boolean) => {
              this.modifierTitleFlag = isOn;
            })
          }

          Flex({ wrap: FlexWrap.Wrap }) {
            Button('gif valid')
              .onClick(() => {
                this.menuItems = this.menuItems2
              }).controlSize(ControlSize.SMALL)
            Button('NavigationTitleOptions：barStyle：STANDARD').onClick(() => {
              this.barStyle = BarStyle.STANDARD
            }).controlSize(ControlSize.SMALL)
            Button('NavigationTitleOptions：barStyle：STACK').onClick(() => {
              this.barStyle = BarStyle.STACK
            }).controlSize(ControlSize.SMALL)
            Button('open subwindow').onClick(() => {
              this.createWindow()
            }).controlSize(ControlSize.SMALL)
            Button('push pageTwo').onClick(() => {
              this.stack.pushPath({ name: 'pageTwo' })
            }).controlSize(ControlSize.SMALL)
            Button('stringType-mainshotTitle').onClick(() => {
              this.mainTitle = 'This is Main Title'
            }).controlSize(ControlSize.SMALL)
            Button('resourceType-subshotTitle').onClick(() => {
              this.subTitle = $r('app.string.shortTitle')
            }).controlSize(ControlSize.SMALL)
            Button('stringType-mainsuperLongTitle').onClick(() => {
              this.mainTitle =
                'This is Main Title This is Main Title This is Main Title This is Main TitleThis is Main TitleThis is Main TitleThis is Main TitleThis is Main TitleThis is Main Title'
            }).controlSize(ControlSize.SMALL)
            Button('resourceType-subsuperLongTitle').onClick(() => {
              this.subTitle = $r('app.string.longTitle')
            }).controlSize(ControlSize.SMALL)
            Button('resourceType-mainshotTitle').onClick(() => {
              this.mainTitle = $r('app.string.shortTitle')
            }).controlSize(ControlSize.SMALL)
            Button('resourceType-mainsuperLongTitle').onClick(() => {
              this.mainTitle = $r('app.string.longTitle')
            }).controlSize(ControlSize.SMALL)
            Button('stringType-subshotTitle').onClick(() => {
              this.subTitle = 'stringShortTitle'
            }).controlSize(ControlSize.SMALL)
            Button('stringType-subsuperLongTitle').onClick(() => {
              this.subTitle =
                'string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title'
            }).controlSize(ControlSize.SMALL)

            Button('titleMode：Free').onClick(() => {
              this.titleMode = NavigationTitleMode.Free
            }).controlSize(ControlSize.SMALL)
            Button('titleMode：Mini').onClick(() => {
              this.titleMode = NavigationTitleMode.Mini
            }).controlSize(ControlSize.SMALL)
            Button('titleMode：Full').onClick(() => {
              this.titleMode = NavigationTitleMode.Full
            }).controlSize(ControlSize.SMALL)
            Button('mode：Stack').onClick(() => {
              this.model = NavigationMode.Stack
            }).controlSize(ControlSize.SMALL)
            Button('mode：Split').onClick(() => {
              this.model = NavigationMode.Split
            }).controlSize(ControlSize.SMALL)
            Button('mode：Auto').onClick(() => {
              this.model = NavigationMode.Auto
            }).controlSize(ControlSize.SMALL)
            Button('navBarPosition：start').onClick(() => {
              this.navBarPosition = NavBarPosition.Start
            }).controlSize(ControlSize.SMALL)
            Button('navBarPosition：end').onClick(() => {
              this.navBarPosition = NavBarPosition.End
            }).controlSize(ControlSize.SMALL)
          }
        }.width('100%')
        .width('100%')
      }}
    .width('100%')
    .height('100%')
    .menus(this.menuItems)
    .title({
      main: this.mainTitle,
      sub: this.subTitle
    },
      this.modifierTitleFlag ? {
        mainTitleModifier: this.mainTitleModifier,
        subTitleModifier: this.subTitleModifier,
        barStyle: this.barStyle,
        backgroundColor: this.colorFlag ? '17A98D' : 'white',
        backgroundBlurStyle:  this.colorFlag ? BlurStyle.BACKGROUND_THICK : BlurStyle.NONE,
      } :
        {
          barStyle: this.barStyle,
          backgroundColor: this.colorFlag ? '17A98D' : 'white',
          backgroundBlurStyle:  this.colorFlag ? BlurStyle.BACKGROUND_THICK : BlurStyle.NONE,
        })
    .titleMode(this.titleMode)
    .navDestination(this.PageBuilder)
    .mode(this.model)
    .navBarPosition(this.navBarPosition)
  }
}

@Component
struct pageTwo {
  @State menuItems: Array<NavigationMenuItem> = [
    {
      value: 'hello',
      icon: $r('app.media.startIcon'),
      action: () => {
        console.log('Hello world')
      },
      isEnabled: true
    },
    {
      value: 'hello',
      icon: $r('app.media.startIcon'),
      isEnabled: false
    },
    {
      value: $r('app.media.startIcon'),
      icon: $r('app.media.startIcon'),
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs'))
    },
    {
      value: $r('app.float.menuValFloat'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.media.startIcon'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.float.menuValFloat')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValString')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValLongString')
    },
  ]
  @State menuItems2: Array<NavigationMenuItem> = [
    {
      value: 'hello',
      icon: $r('app.media.background'),
      action: () => {
        console.log('Hello world')
      },
      isEnabled: true
    },
    {
      value: 'hello',
      icon: $r('app.media.background'),
      isEnabled: false
    },
    {
      value: 'startIcon',
      icon: $r('app.media.startIcon'),
      symbolIcon: new SymbolGlyphModifier($r('sys.symbol.ohos_lungs'))
    },
    {
      value: $r('app.float.menuValFloat'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValString'),
      icon: $r('app.media.background')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.foreground')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.media.startIcon')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.float.menuValFloat')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValString')
    },
    {
      value: $r('app.string.menuValLongString'),
      icon: $r('app.string.menuValLongString')
    },
  ]
  @State barStyle: BarStyle = BarStyle.STANDARD
  private myWindow: window.Window | null = null;
  createWindow2() {
    try {
      window.createWindow({name: 'testWindow', windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          let ls = new LocalStorage();
          this.myWindow?.loadContent('pages/vvv/WindowTwo', ls)
            .then(() => {
              console.log(`testTag success to loadContent`)
              this.myWindow?.showWindow().then(() => {
                console.log(`testTag success to showWindow`)
                this.myWindow?.resize(1000, 1000);
                this.myWindow?.moveWindowTo(50, 200);
              }).catch((e: base.BusinessError) => {
                console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
              });
            }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
          })

        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }
  @State mainTitle: string | Resource = 'main Title'
  @State subTitle: string | Resource = 'sub Title'
  @State colorFlag: boolean = false;
  scroller: Scroller = new Scroller()
  @State modifierTitleFlag: boolean = false;
  @State mainTitleModifier: MainTitleTextModifier = new MainTitleTextModifier();
  @State subTitleModifier: SubTitleTextModifier = new SubTitleTextModifier();
  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column() {
          Row() {
            Text(`title set color&blur`)
            Toggle({isOn: this.colorFlag, type: ToggleType.Switch}).onChange((isOn: boolean) => {
              this.colorFlag = isOn;
            })
          }.margin(5)
          Row() {
            Text(`title modifier`)
            Toggle({isOn: this.modifierTitleFlag, type: ToggleType.Switch}).onChange((isOn: boolean) => {
              this.modifierTitleFlag = isOn;
            })
          }.margin(5)
          Button('gif valid')
            .onClick(()=>{
              this.menuItems = this.menuItems2
            }).fontSize(14).width('100%')
          Button('NavigationTitleOptions：barStyle：STANDARD')
            .onClick(() => {
              this.barStyle = BarStyle.STANDARD
            }).fontSize(14).width('100%')
          Button('NavigationTitleOptions：barStyle：STACK')
            .onClick(() => {
              this.barStyle = BarStyle.STACK
            }).fontSize(14).width('100%')
          Button('open subwindow')
            .onClick(() => {
              this.createWindow2()
            }).fontSize(14).width('100%')
          Button('stringType-mainshotTitle').onClick(() => {
            this.mainTitle = 'This is Main Title'
          }).fontSize(14).width('100%')
          Button('resourceType-subshotTitle').onClick(() => {
            this.subTitle = $r('app.string.shortTitle')
          }).fontSize(14).width('100%')
          Button('stringType-mainsuperLongTitle').onClick(() => {
            this.mainTitle = 'This is Main Title This is Main Title This is Main Title This is Main TitleThis is Main TitleThis is Main TitleThis is Main TitleThis is Main TitleThis is Main Title'
          }).fontSize(14).width('100%')
          Button('resourceType-subsuperLongTitle').onClick(() => {
            this.subTitle = $r('app.string.longTitle')
          }).fontSize(14).width('100%')
          Button('resourceType-mainshotTitle').onClick(() => {
            this.mainTitle =  $r('app.string.shortTitle')
          }).fontSize(14).width('100%')
          Button('resourceType-mainsuperLongTitle').onClick(() => {
            this.mainTitle = $r('app.string.longTitle')
          }).fontSize(14).width('100%')
          Button('stringType-subshotTitle').onClick(() => {
            this.subTitle = 'string short Title'
          }).fontSize(14).width('100%')
          Button('stringType-subsuperLongTitle').onClick(() => {
            this.subTitle = 'string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title string long Title'
          }).fontSize(14).width('100%')
        }
      }
    }
    .width('100%')
    .height('100%')
    .title({
      main: this.mainTitle,
      sub: this.subTitle
    },
      this.modifierTitleFlag ? {
        mainTitleModifier: this.mainTitleModifier,
        subTitleModifier: this.subTitleModifier,
        barStyle: this.barStyle,
        backgroundColor: this.colorFlag ? '17A98D' : 'white',
        backgroundBlurStyle:  this.colorFlag ? BlurStyle.BACKGROUND_THICK : BlurStyle.NONE,
      } :
        {
          barStyle: this.barStyle,
          backgroundColor: this.colorFlag ? '17A98D' : 'white',
          backgroundBlurStyle:  this.colorFlag ? BlurStyle.BACKGROUND_THICK : BlurStyle.NONE,
        })
    .menus(this.menuItems)
  }
}