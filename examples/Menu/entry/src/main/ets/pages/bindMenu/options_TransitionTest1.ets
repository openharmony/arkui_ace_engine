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

import { SymbolGlyphModifier } from '@kit.ArkUI';
import { ComponentContent, FrameNode } from '@kit.ArkUI';
let showInSubWindowIndex:number = 0;
let showInSubWindowList:(boolean|undefined|null)[]=[
  true,
  false,
  undefined,
  null
]
export function doSomething1111(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu1111(context, uniqueId, contentNode);
}

@Builder
function MyMenu1111() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu1111(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    preview: MenuPreviewMode.IMAGE,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
}
export function doSomething111(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu111(context, uniqueId, contentNode);
}

@Builder
function MyMenu111() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu111(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    preview: MenuPreviewMode.NONE,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
}

export function doSomething2(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu2(context, uniqueId, contentNode);
}

@Builder
function MyMenu2() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu2(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
  setTimeout(() => {
    promptAction.closeMenu(contentNode);
  }, 2000)
}
export function doSomething2222(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu2222(context, uniqueId, contentNode);
}

@Builder
function MyMenu2222() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu2222(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    preview: MenuPreviewMode.IMAGE,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
  setTimeout(() => {
    promptAction.closeMenu(contentNode);
  }, 2000)
}
export function doSomething222(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu222(context, uniqueId, contentNode);
}

@Builder
function MyMenu222() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu222(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    preview: MenuPreviewMode.NONE,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
  setTimeout(() => {
    promptAction.closeMenu(contentNode);
  }, 2000)
}
export function doSomething1(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {
  showMenu1(context, uniqueId, contentNode);
}

@Builder
function MyMenu1() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
    }
  }
  // .width('80%')
  .padding('20lpx')
}

export function showMenu1(context: UIContext, uniqueId: string, contentNode: ComponentContent<Object>) {

  const promptAction = context.getPromptAction();

  promptAction.openMenu(contentNode, { id: uniqueId }, {
    enableArrow: true,
    mask: true,
    showInSubWindow: showInSubWindowList[showInSubWindowIndex]
  });
}
@Entry
@Component
struct MenuExample {
  private iconStr: ResourceStr = $r("app.media.layered_image");
  private iconStr2: ResourceStr = $r("app.media.layered_image");
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }

  @Builder
  MyMenu1(){
    Menu() {
      MenuItem({ startIcon: $r("app.media.layered_image"), content: "菜单选项" })
      MenuItem({ startIcon: $r("app.media.layered_image"), content: "菜单选项" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项1",
        endIcon: this.iconStr2,
        builder: ():void=>this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项2",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
        MenuItem({
          startIcon: $r("app.media.startIcon"),
          content: "菜单选项3",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
      })
    }
  }
  @State listData: number[] = [0, 0, 0];
  @State symbolIconModifier1: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_photo')).fontSize('24vp');
  @State symbolIconModifier2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_photo')).fontSize('24vp');
  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      ForEach(this.listData, (item:number, index) => {
        Column() {
          Row() {
            Image($r("app.media.startIcon")).width(20).height(20).margin({ right: 5 })
            Text(`Menu${index as number + 1}`).fontSize(20)
          }
          .width('100%')
          .height(30)
          .justifyContent(FlexAlign.Center)
          .align(Alignment.Center)
          .onClick(() => {
            console.info(`Menu${index as number + 1} Clicked!`);
          })

          if (index != this.listData.length - 1) {
            Divider().height(10).width('80%').color('#ccc')
          }
        }.padding(5).height(40)
      })
    }.width(100)
  }
  @Builder MenuBuilder1() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Text('Options')
      Divider().strokeWidth(2).margin(5).color('#F0F0F0')
      Text('Hide')
      Divider().strokeWidth(2).margin(5).color('#F0F0F0')
      Text('Exit')
    }
    .width(200)
  }
  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
      MenuItem({ startIcon: this.iconStr, content: "菜单选项" })
    }
  }
  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.startIcon'))
        .width(200)
        .height(200)
    }
  }
  @State showInSubWindowIndex:number = 0;
  @State showInSubWindowList:(boolean|undefined|null)[]=[
    true,
    false,
    undefined,
    null
  ]
  @State menuModeIndex: number = 0;
  @State menuModeList: (SubMenuExpandingMode | undefined)[] = [
    SubMenuExpandingMode.SIDE_EXPAND,
    SubMenuExpandingMode.EMBEDDED_EXPAND,
    SubMenuExpandingMode.STACK_EXPAND,
    undefined
  ]
  @State isShown: boolean = false;
  @State isShow32Index: number = 0;
  @State isShow32List: (boolean)[] = [
    false,
    true
  ];
  @Builder
  SubMenu11() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }
  @Builder
  MyMenu11() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项1" })
      MenuItem({ startIcon: $r("app.media.startIcon"), content: "菜单选项2" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项3",
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu11()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项4",
          endIcon: this.iconStr2,
          builder: (): void => this.SubMenu11()
        })
        MenuItem({
          startIcon: $r("app.media.layered_image"),
          content: "菜单选项5",
          endIcon: this.iconStr2,
          builder: (): void => this.SubMenu11()
        })
      }

      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
      })
    }
    .subMenuExpandingMode(this.menuModeList[this.menuModeIndex])
  }

  build() {
    Column(){
      Scroll(){
        Column() {
          Button('showInSubWindow:' + this.showInSubWindowList[this.showInSubWindowIndex])
            .margin({top:10})
            .onClick(()=>{
              this.showInSubWindowIndex = (this.showInSubWindowIndex + 1) % this.showInSubWindowList.length;
            })
          Text('bindMenu通过配置MenuElement弹出普通菜单').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindMenu([
              {
                value: 'Menu1',
                action: () => {
                  console.info('handle Menu1 select');
                }
              },
              {
                value: 'Menu2',
                action: () => {
                  console.info('handle Menu2 select');
                }
              },
            ],{
              showInSubWindow:this.showInSubWindowList[this.showInSubWindowIndex]
            })
          Text('bindMenu通过配置CustomBuilder弹出自定义菜单').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindMenu(this.MenuBuilder,{showInSubWindow:this.showInSubWindowList[this.showInSubWindowIndex]})
          Text('bindContextMenu通过配置responseType.LongPress弹出菜单').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindContextMenu(this.MenuBuilder, ResponseType.LongPress)
          Text('bindContextMenu通过配置responseType.RightClick、enableArrow弹出指向型菜单').margin({top:10})
          Button('menu')
            .id("TraniSation_003")
            .margin({top:10})
            .bindContextMenu(this.MenuBuilder1, ResponseType.RightClick, {
              enableArrow: true,
              placement: Placement.Bottom
            })
          Text('bindContextMenu通过配置responseType.LongPress、preview的MenuPreviewMode类型弹出菜单预览样式').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              { preview: MenuPreviewMode.IMAGE,
                previewAnimationOptions: {scale: [0.8, 1.0]},
              })
          Text('bindContextMenu通过配置responseType.LongPress、preview的CustomBuilder类型弹出菜单自定义预览样式').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              {
                preview: this.MyPreview
              })
          Text('bindContextMenu通过配置isShown弹出菜单预览样式').margin({top:10})
          Row({space:10}){
            Button('menu')
              .bindContextMenu(this.isShown, this.MyMenu,
                {
                  preview: this.MyPreview,
                  aboutToDisappear: ()=>{
                    this.isShown = false;
                  }
                })
            Button('click')
              .onClick(()=>{
                this.isShown = true;
              })
          }.margin({top:10})
          Text('bindContextMenu通过配置transition，实现自定义菜单以及菜单预览时的显示和退出动效').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindContextMenu(
              this.MenuBuilder,
              ResponseType.LongPress,{
              transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                TransitionEffect.rotate({ z: 1, angle: 180 })),
              preview: this.MyPreview,
              previewAnimationOptions: {
                scale: [0.8, 1.0],
                transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                  TransitionEffect.rotate({ z: 1, angle: 180 }))
              }
            })
          Text('bindMenu通过配置MenuElement的symbolIcon弹出菜单').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindMenu([
              {
                value: 'Menu1',
                symbolIcon:this.symbolIconModifier1,
                action: () => {
                  console.info('handle Menu1 select');
                }
              },
              {
                value: 'Menu2',
                symbolIcon:this.symbolIconModifier2,
                action: () => {
                  console.info('handle Menu2 select');
                }
              },
            ])
          Text('MenuItem中的builder参数实现多级菜单').margin({top:10})
          Button('menu')
            .margin({top:10})
            .bindMenu(this.MyMenu1)
          Text('------------openMenu------------').margin({top:10})
          Button('openMenu', { type: ButtonType.Normal, stateEffect: true }).id('01')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu1));
              doSomething1(context, '01', contentNode)
            })
          Button('none', { type: ButtonType.Normal, stateEffect: true }).id('05')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu111));
              doSomething111(context, '05', contentNode)
            })
          Button('image', { type: ButtonType.Normal, stateEffect: true }).id('09')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu1111));
              doSomething1111(context, '09', contentNode)
            })
          Text('------------Close------------').margin({top:10})
          Button('openMenu', { type: ButtonType.Normal, stateEffect: true }).id('02')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu2));
              doSomething2(context, '02', contentNode)
            })
          Button('none', { type: ButtonType.Normal, stateEffect: true }).id('06')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu222));
              doSomething222(context, '06', contentNode)
            })
          Button('image', { type: ButtonType.Normal, stateEffect: true }).id('08')
            .margin({top:10})
            .onClick(() => {
              let context = this.getUIContext()
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu2222));
              doSomething2222(context, '08', contentNode)
            })
          Text('bindMenu:配置MenuItem中的builder参数实现二级菜单').margin({ top: 10 })
          Button('Menu子菜单展开样式:' + this.menuModeList[this.menuModeIndex])
            .id("TraniSation_001")
            .margin({ top: 10 })
            .onClick(() => {
              this.menuModeIndex = (this.menuModeIndex + 1) % this.menuModeList.length
            })
          Button('DISABLED')
            .bindMenu(this.isShow32List[this.isShow32Index], this.MyMenu11)
          Button('二级菜单:' + this.isShow32List[this.isShow32Index])
            .id("TraniSation_002")
            .onClick(() => {
              this.isShow32Index = (this.isShow32Index + 1) % this.isShow32List.length
            })
        }
        .width('100%')
        .margin({ top: 5 })
      }
    }
  }
}