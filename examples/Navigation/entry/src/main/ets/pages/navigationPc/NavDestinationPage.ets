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
import { NavDestinationModifier } from '@ohos.arkui.modifier';
import base from '@ohos.base';
import window from '@ohos.window';
import { LengthMetrics } from '@kit.ArkUI';
import { TextModifier } from '@ohos.arkui.modifier';

class MainTitleTextModfier extends TextModifier {
  useStyle1: boolean = true;

  applyNormalAttribute(instance: TextModifier): void {
    if (this.useStyle1) {
      console.log(`testTag mainTitle use style1`);
      instance.fontColor('#FFFFC000')
      instance.fontSize(35)
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
      instance.fontSize(15)
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

class MyNavDestinationModifier extends NavDestinationModifier {
  applyNavDestinationAttribute(instance: NavDestinationAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(value:CustomBuilder,barStyleValue:BarStyle): void {
    this.title(value, {backgroundColor:Color.Orange, barStyle: BarStyle.STACK})
  }
}

@Entry
@Component
struct NavDestinationPage {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  @Builder
  pageMap (name: string) {
    if (name == 'PageOne') {
      PageOne()
    }
    else if (name == 'PageTwo') {
      PageTwo()
    }
    else if (name == 'PageThree') {
      PageThree()
    }
    else if (name == 'PageFour') {
      PageFour()
    }
    else if (name == 'PageFive') {
      PageFive()
    }
    else if (name == 'PageSix') {
      PageSix()
    }
    else if (name == 'PageContent') {
      PageContent()
    }
    else if (name == 'PageTitle') {
      PageTitle()
    }
    else if (name == 'PageModifier') {
      PageModifier()
    }
    else if (name == 'Dialog') {
      PageDialog()
    }
  }
  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }
  @State navigationMode: NavigationMode = NavigationMode.Auto;
  @State navBarPosition: NavBarPosition = NavBarPosition.Start;
  @State allPathName: Array<string> = []
  @State paddingVal: string = '0vp'
  @State heightVal: string = '75%'
  build() {
    Column() {
      Navigation(this.pageInfos) {

      }
      .height(this.heightVal)
      .padding(this.paddingVal)
      .title('NavDestination title')
      .id('navigationId')
      .navDestination(this.pageMap)
      .mode(this.navigationMode)
      .navBarPosition(this.navBarPosition)
      Flex({ wrap: FlexWrap.Wrap }) {
        Button('push pageOne menus1').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageOne'})
        }).margin(4)
        Button('push pageTwo menus2').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageTwo'})
        }).margin(4)
        Button('push pageThree menus3').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageThree'})
        }).margin(4)
        Button('push pageFour menus4').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageFour'})
        }).margin(4)
        Button('push pageSix').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageSix'})
        }).margin(4)
        Button('push pageFive').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'PageFive'})
        }).margin(4)
        Button('NavigationMode：Split').fontSize(14).onClick(() => {
          this.navigationMode = NavigationMode.Split;
        }).margin(4)
        Button('SetWindowDecorVisible：false').fontSize(14).onClick(() => {
          this.SetWindowDecorVisible(false)
        }).margin(4)
        Button('SetWindowDecorVisible：true').fontSize(14).onClick(() => {
          this.SetWindowDecorVisible(true)
        }).margin(4)
        Button('NavigationMode：Stack').fontSize(14).onClick(() => {
          this.navigationMode = NavigationMode.Stack;
        }).margin(4)
        Button('NavigationMode：Auto').fontSize(14).onClick(() => {
          this.navigationMode = NavigationMode.Auto;
        }).margin(4)
        Button('navBarPosition：End').fontSize(14).onClick(() => {
          this.navBarPosition = NavBarPosition.End;
        }).margin(4)

        Button('navBarPosition：Start').fontSize(14).onClick(() => {
          this.navBarPosition = NavBarPosition.Start;
        }).margin(4)
        Button('getAllPathName').fontSize(14).onClick(() => {
          this.allPathName = this.pageInfos.getAllPathName()
        }).margin(4)
        Text(this.allPathName.toString())

        Button('push Dialog').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name: 'Dialog'})
        }).margin(4)

        Button('padding：100').fontSize(14).onClick(() => {
          this.paddingVal = '100vp'
        }).margin(4)

        Button('NavDestination height：50%').onClick(() => {
          this.heightVal = '50%'
        }).margin(4)

        Button('Navigation：not full screen').fontSize(14).onClick(() => {
          this.heightVal = '75%'
        }).margin(4)
        Button('Navigation：full screen').fontSize(14).onClick(() => {
          this.heightVal = '100%'
        }).margin(4)
        Button('clear').fontSize(14).onClick(() => {
          this.pageInfos.clear()
        }).margin(4)
        Button('pop').fontSize(14).onClick(() => {
          this.pageInfos.pop()
        }).margin(4)
        Button('push pageTwo/Three/Dialog').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name:'PageTwo'})
          this.pageInfos.pushPath({name:'PageThree'})
          this.pageInfos.pushPath({name:'Dialog'})
        }).margin(4)
        Button('push pageTwo/Three/Two').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name:'PageTwo'})
          this.pageInfos.pushPath({name:'PageThree'})
          this.pageInfos.pushPath({name:'PageTwo'})
        }).margin(4)

        Button('push systemTransition TITLE').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name:'PageTitle'})
        }).margin(4)

        Button('push systemTransition CONTENT').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name:'PageContent'})
        }).margin(4)

        Button('push modifier').fontSize(14).onClick(() => {
          this.pageInfos.pushPath({name:'PageModifier'})
        }).margin(4)
      }
    }
    .width('100%')
    .height('100%')
  }
}


@Component
struct PageOne {
  @Consume('pageInfos') pageInfos: NavPathStack

  @State hideTitleValue: boolean = false

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  @Builder
  CustomMenu() {
    Column() {
      Text('CustomMenu')
    }.justifyContent(FlexAlign.Center).width('50%').height('50%').backgroundColor(Color.Blue)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageOne')
          Button('pageOne SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
          Button('hideTitle: animte true').onClick(() => {
            this.hideTitleValue = true;
          })
          Button('hideTitle: animte false').onClick(() => {
            this.hideTitleValue = false;
          })
        }
      }
    }
    .title('pageOne',{backgroundColor:Color.Green})
    .menus(this.CustomMenu)
    .hideTitleBar(this.hideTitleValue)
  }
}

@Component
struct PageTwo {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }


  SetWindowDecorHeight(h: number) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorHeight(h);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorHeight: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems1: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems7: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '4',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '5',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '6',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '7',
      icon: 'resources/base/media/startIcon.png',
    }

  ]

  @State menus: Array<NavigationMenuItem> = this.menuItems1;
  @State allPathName: Array<string> = []
  @State color: ResourceColor = Color.Transparent;
  @State blurStyle: BlurStyle = BlurStyle.NONE;
  @State barStyle: BarStyle = BarStyle.STANDARD
  @State paddingStart: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_left'))
  @State paddingEnd: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_right'))
  @State mainTitleModifier: MainTitleTextModfier = new MainTitleTextModfier();
  @State subTitleModifier: SubTitleTextModfier = new SubTitleTextModfier();
  @State applyModifier: boolean = false
  scroller: Scroller = new Scroller()
  scroller1: Scroller = new Scroller()
  @State mainTitle: ResourceStr = 'Main title'
  @State subTitle: ResourceStr = 'sub title'
  @State hasSubTitle: boolean = false;
  @State title: ResourceStr | NavigationCommonTitle = 'Title'
  @State arr: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
  controller: TextInputController = new TextInputController()
  @State heightVal: string = '100%'
  @State hideTitleValue: boolean = false
  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 3}) {
          Text('pageTwo')
          Flex({wrap:FlexWrap.Wrap}) {
            Button('pageTwo menucount ：3').onClick(() => {
              this.menus = this.menuItems3
            }).margin(10)
            Button('pageTwo menucount ：7').onClick(() => {
              this.menus = this.menuItems7
            }).margin(10)
            Button('pageTwo SetWindowDecorVisible：false').onClick(() => {
              this.SetWindowDecorVisible(false)
            }).margin(10)
            Button('pageTwo SetWindowDecorVisible：true').onClick(() => {
              this.SetWindowDecorVisible(true)
            }).margin(10)
            Button('pageTwo hideTitle: animte true').onClick(() => {
              this.hideTitleValue = true;
            }).margin(10)
            Button('pageTwo hideTitle: animte false').onClick(() => {
              this.hideTitleValue = false;
            }).margin(10)
            Text(this.allPathName.toString()).margin(10)
            Button('removeByName pageTwo').onClick(() => {
              this.pageInfos.removeByName('PageTwo')
            }).margin(10)
            Button('pageTwo title backgroundColor：Red').onClick(() => {
              this.color = Color.Red
            }).margin(10)
            Button('pageTwo title backgroundColor：Yellow').onClick(() => {
              this.color = Color.Yellow
            }).margin(10)
            Button('pageTwo title backgroundBlurStyle：Thick').onClick(() => {
              this.blurStyle = BlurStyle.Thick
            }).margin(10)
            Button('pageTwo title BarStyle：STANDARD').onClick(() => {
              this.barStyle = BarStyle.STANDARD
            }).margin(10)
            Button('pageTwo title BarStyle：STACK').onClick(() => {
              this.barStyle = BarStyle.STACK
            }).margin(10)
            Button('pageTwo title BarStyle：SAFE_AREA_PADDING').onClick(() => {
              this.barStyle = BarStyle.SAFE_AREA_PADDING
            }).margin(10)
            Button('pageTwo title paddingStart：100vp').onClick(() => {
              this.paddingStart = LengthMetrics.vp(100)
            }).margin(10)
            Button('pageTwo title paddingEnd：100vp').onClick(() => {
              this.paddingEnd = LengthMetrics.vp(100)
            }).margin(10)
            Button('pageTwo TitleModifier').onClick(() => {
              this.applyModifier = true;
            }).margin(10)
            Button('NavDestination: mainTitle').onClick(() => {
              this.hasSubTitle = false;
              this.title = this.mainTitle
            }).margin(10)
            Button('NavDestination: main&sub Title').onClick(() => {
              this.title ={ main: this.mainTitle, sub: this.subTitle }
              this.hasSubTitle = true;
            }).margin(10)
          }
          Row() {
            TextInput({ text: this.mainTitle as string, placeholder: 'MainTitle...', controller: this.controller })
              .key('MainTitle')
              .placeholderColor(Color.Grey)
              .placeholderFont({ size: 14, weight: 400 })
              .caretColor(Color.Blue)
              .width('45%')
              .height(40)
              .fontSize(14)
              .fontColor(Color.Black)
              .onChange((value: string) => {
                this.mainTitle = value;
                if (this.hasSubTitle) {
                  this.title = this.title ={ main: this.mainTitle, sub: this.subTitle }
                } else {
                  this.title =this.mainTitle
                }
              })
            TextInput({ text: this.subTitle as string, placeholder: 'SubTitle...', controller: this.controller })
              .key('SubTitle')
              .placeholderColor(Color.Grey)
              .placeholderFont({ size: 14, weight: 400 })
              .caretColor(Color.Blue)
              .width('45%')
              .height(40)
              .fontSize(14)
              .fontColor(Color.Black)
              .onChange((value: string) => {
                this.subTitle = value
                if (this.hasSubTitle) {
                  this.title = this.title ={ main: this.mainTitle, sub: this.subTitle }
                } else {
                  this.title =this.mainTitle
                }
              })
          }
          Button('setWindowDecorHeight：50').onClick(() => {
            this.SetWindowDecorHeight(50)
          })
          Button('setWindowDecorHeight：100').onClick(() => {
            this.SetWindowDecorHeight(100)
          })

          ForEach(this.arr, (item: string) => {
            Button('test'+item)
          }, (item: string) => item)
        }
      }
      .margin({left:'20vp', right: '20vp'})
      .backgroundColor(Color.Pink)
      .scrollBar(BarState.Off)
    }
    .bindToScrollable([this.scroller])
    .title(this.title,
      this.applyModifier ? {
        backgroundColor: this.color,
        backgroundBlurStyle: this.blurStyle,
        barStyle: this.barStyle,
        paddingStart: this.paddingStart,
        paddingEnd: this.paddingEnd,
        mainTitleModifier: this.mainTitleModifier,
        subTitleModifier: this.subTitleModifier,
      }:
        {
          backgroundColor: this.color,
          backgroundBlurStyle: this.blurStyle,
          barStyle: this.barStyle,
          paddingStart: this.paddingStart,
          paddingEnd: this.paddingEnd,
        })
    .menus(this.menus)
    .height(this.heightVal)
    .hideTitleBar(this.hideTitleValue,true)
  }
}

@Component
struct PageModifier {

  @State myModifier: NavDestinationModifier = new MyNavDestinationModifier()
    .title('PageModifier', {backgroundColor:Color.Orange, barStyle: BarStyle.STACK})

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageOne')

        }
      }
    }
    .title('pageOne',{backgroundColor:Color.Green})
    .attributeModifier(this.myModifier as MyNavDestinationModifier)
  }
}

@Component
struct PageTitle {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }


  SetWindowDecorHeight(h: number) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorHeight(h);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorHeight: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems1: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems7: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '4',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '5',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '6',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '7',
      icon: 'resources/base/media/startIcon.png',
    }

  ]

  @State menus: Array<NavigationMenuItem> = this.menuItems1;
  @State allPathName: Array<string> = []
  @State color: ResourceColor = Color.Transparent;
  @State blurStyle: BlurStyle = BlurStyle.NONE;
  @State barStyle: BarStyle = BarStyle.STANDARD
  @State paddingStart: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_left'))
  @State paddingEnd: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_right'))
  @State mainTitleModifier: MainTitleTextModfier = new MainTitleTextModfier();
  @State subTitleModifier: SubTitleTextModfier = new SubTitleTextModfier();
  @State applyModifier: boolean = false
  scroller: Scroller = new Scroller()
  scroller1: Scroller = new Scroller()
  @State mainTitle: ResourceStr = 'Main title'
  @State subTitle: ResourceStr = 'sub title'
  @State hasSubTitle: boolean = false;
  @State title: ResourceStr | NavigationCommonTitle = 'Title'
  @State arr: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
  controller: TextInputController = new TextInputController()
  @State heightVal: string = '100%'
  @State hideTitleValue: boolean = false
  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 3}) {
          Text('this is PageTitle page')
          Button('PageTitle menu count：3').onClick(() => {
            this.menus = this.menuItems3
          })
          Button('menu count：7').onClick(() => {
            this.menus = this.menuItems7
          })
        }
      }
      .margin({left:'20vp', right: '20vp'})
      .scrollBarColor(Color.Green)
      .scrollBarWidth(10)
      .backgroundColor(Color.Pink)

    }
    .bindToScrollable([this.scroller])
    .title(this.title,
      this.applyModifier ? {
        backgroundColor: this.color,
        backgroundBlurStyle: this.blurStyle,
        barStyle: this.barStyle,
        paddingStart: this.paddingStart,
        paddingEnd: this.paddingEnd,
        mainTitleModifier: this.mainTitleModifier,
        subTitleModifier: this.subTitleModifier,
      }:
        {
          backgroundColor: this.color,
          backgroundBlurStyle: this.blurStyle,
          barStyle: this.barStyle,
          paddingStart: this.paddingStart,
          paddingEnd: this.paddingEnd,
        })
    .menus(this.menus)
    .height(this.heightVal)
    .hideTitleBar(this.hideTitleValue,true)
    .systemTransition(NavigationSystemTransitionType.TITLE)
  }
}

@Component
struct PageContent {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }


  SetWindowDecorHeight(h: number) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorHeight(h);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorHeight: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems1: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  private menuItems7: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '4',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '5',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '6',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '7',
      icon: 'resources/base/media/startIcon.png',
    }

  ]

  @State menus: Array<NavigationMenuItem> = this.menuItems1;
  @State allPathName: Array<string> = []
  @State color: ResourceColor = Color.Transparent;
  @State blurStyle: BlurStyle = BlurStyle.NONE;
  @State barStyle: BarStyle = BarStyle.STANDARD
  @State paddingStart: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_left'))
  @State paddingEnd: LengthMetrics = LengthMetrics.resource($r('sys.float.margin_right'))
  @State mainTitleModifier: MainTitleTextModfier = new MainTitleTextModfier();
  @State subTitleModifier: SubTitleTextModfier = new SubTitleTextModfier();
  @State applyModifier: boolean = false
  scroller: Scroller = new Scroller()
  scroller1: Scroller = new Scroller()
  @State mainTitle: ResourceStr = 'Main title'
  @State subTitle: ResourceStr = 'sub title'
  @State hasSubTitle: boolean = false;
  @State title: ResourceStr | NavigationCommonTitle = 'Title'
  @State arr: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
  controller: TextInputController = new TextInputController()
  @State heightVal: string = '100%'
  @State hideTitleValue: boolean = false
  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 3}) {
          Text('this PageContent page')
          Button('menucount ：3').onClick(() => {
            this.menus = this.menuItems3
          })
          Button('menucount ：7').onClick(() => {
            this.menus = this.menuItems7
          })
          Button('SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
          Button('SetWindowDecorVisible：true').onClick(() => {
            this.SetWindowDecorVisible(true)
          })
        }
      }
      .margin({left:'20vp', right: '20vp'})
      .scrollBarColor(Color.Green)
      .scrollBarWidth(10)
      .backgroundColor(Color.Pink)

    }
    .bindToScrollable([this.scroller])
    .title(this.title,
      this.applyModifier ? {
        backgroundColor: this.color,
        backgroundBlurStyle: this.blurStyle,
        barStyle: this.barStyle,
        paddingStart: this.paddingStart,
        paddingEnd: this.paddingEnd,
        mainTitleModifier: this.mainTitleModifier,
        subTitleModifier: this.subTitleModifier,
      }:
        {
          backgroundColor: this.color,
          backgroundBlurStyle: this.blurStyle,
          barStyle: this.barStyle,
          paddingStart: this.paddingStart,
          paddingEnd: this.paddingEnd,
        })
    .menus(this.menus)
    .height(this.heightVal)
    .hideTitleBar(this.hideTitleValue,true)
    .systemTransition(NavigationSystemTransitionType.CONTENT)
  }
}

@Component
struct PageThree {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  @Builder
  CustomMenu() {
    Column() {
      Text('CustomMenu')
    }.justifyContent(FlexAlign.Center).width('50%').height('50%').backgroundColor(Color.Blue)
  }

  @Builder
  CustomTitle() {
    Column() {
      Text('CustomTitle')
    }.justifyContent(FlexAlign.Start).width('50%').height('50%').backgroundColor(Color.Green)
  }

  @State allPathName: Array<string> = []

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageThree')
          Button('pageThree SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
          Button('pageThree getAllPathName').onClick(() => {
            this.allPathName = this.pageInfos.getAllPathName()
          })
          Text(this.allPathName.toString())

          Button('moveToTop pageTwo').onClick(() => {
            this.pageInfos.moveToTop('PageTwo')
          })
          Button('push pageTwo menus').onClick(() => {
            this.pageInfos.pushPath({name: 'PageTwo'})
          })
        }
      }
    }
    .title(this.CustomTitle,{backgroundColor:Color.Green})
    .menus(this.CustomMenu)
  }
}

@Component
struct PageFour {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  @Builder
  CustomTitle() {
    Column() {
      Text('CustomTitle')
    }.justifyContent(FlexAlign.Start).width('50%').height('50%').backgroundColor(Color.Green)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageFour')
          Button('pageFour SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
        }
      }
    }
    .title(this.CustomTitle,{backgroundColor:Color.Green})
    .menus(this.menuItems3)
  }
}

@Component
struct PageFive {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageFive')
          Button('pageFive SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
        }
      }
    }
    .menus(this.menuItems3)
  }
}

@Component
struct PageSix {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('pageSix')
          Button('pageSix SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
          Button('SetWindowDecorVisible：true').onClick(() => {
            this.SetWindowDecorVisible(true)
          })
        }
      }
    }
    .title('Title',{backgroundColor:Color.Blue})
    .menus(this.menuItems3)
    .toolbarConfiguration([
      { value: 'a' },
      { value: 'b' },
      { value: 'c' }
    ])
  }
}


@Component
struct PageDialog {
  @Consume('pageInfos') pageInfos: NavPathStack

  SetWindowDecorVisible(visible: boolean) {
    let ctx = this.getUIContext().getHostContext();
    if (ctx) {
      window.getLastWindow(ctx, (err: base.BusinessError, win: window.Window) => {
        if (err.code) {
          console.log(`testTag failed to getLastWindow: ${JSON.stringify(err)}`);
          return;
        }
        try {
          win.setWindowDecorVisible(visible);
        } catch (e) {
          console.log(`testTag failed to setWindowDecorVisible: ${JSON.stringify(e)}`);
        }
      })
    } else {
      console.log(`testTag failed to getHostContext`);
    }
  }

  private menuItems3: Array<NavigationMenuItem> = [
    {
      value: '1',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '2',
      icon: 'resources/base/media/startIcon.png',
    },
    {
      value: '3',
      icon: 'resources/base/media/startIcon.png',
    }
  ]
  @State allPathName: Array<string> = []
  build() {
    NavDestination() {
      Scroll() {
        Column({ space: '10vp' }) {
          Text('Dialog Page')
          Button('Dialog SetWindowDecorVisible：false').onClick(() => {
            this.SetWindowDecorVisible(false)
          })
          Button('getAllPathName').onClick(() => {
            this.allPathName = this.pageInfos.getAllPathName()
          })
          Text(this.allPathName.toString())
        }
      }
    }
    .title('Title',{backgroundColor:Color.Blue})
    .menus(this.menuItems3)
    .mode(NavDestinationMode.DIALOG)
  }
}
