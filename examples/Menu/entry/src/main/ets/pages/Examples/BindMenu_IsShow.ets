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
import { webview } from '@kit.ArkWeb';
import { pasteboard } from '@kit.BasicServicesKit';

const TAG = 'ContextMenu';

@Builder
export function BindMenuBuilder() {
  BindMenuTest()
}

@Entry
@Component
struct BindMenuTest {
  pageInfos: NavPathStack = new NavPathStack();
  controller: webview.WebviewController = new webview.WebviewController();
  private result: WebContextMenuResult | undefined = undefined;
  @State linkUrl: string = '';
  @State offsetX: number = 0;
  @State offsetY: number = 0;
  @State showMenu: boolean = false;
  uiContext: UIContext = this.getUIContext();

  @Builder
  // 构建自定义菜单及触发功能接口
  MenuBuilder() {
    // 以垂直列表形式显示的菜单。
    Menu() {
      // 展示菜单Menu中具体的item菜单项。
      MenuItem({content: '撤销',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.undo();
          this.showMenu = false;
        })
      MenuItem({content: '重做',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.redo();
          this.showMenu = false;
        })
      MenuItem({content: '粘贴为纯文本',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.pasteAndMatchStyle();
          this.showMenu = false;
        })
      MenuItem({content: '复制图片',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.copyImage();
          this.showMenu = false;
        })
      MenuItem({content: '剪切',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.cut();
          this.showMenu = false;
        })
      MenuItem({content: '复制',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.copy();
          this.showMenu = false;
        })
      MenuItem({content: '粘贴',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.paste();
          this.showMenu = false;
        })
      MenuItem({content: '复制链接',})
        .width(100)
        .height(50)
        .onClick(() => {
          let pasteData = pasteboard.createData('text/plain', this.linkUrl);
          pasteboard.getSystemPasteboard().setData(pasteData, (error) => {
            if (error) {
              return;
            }
          })
          this.showMenu = false;
        })
      MenuItem({content: '全选',})
        .width(100)
        .height(50)
        .onClick(() => {
          this.result?.selectAll();
          this.showMenu = false;
        })
    }
    .width(150)
    .height(450)
  }

  private iconStr: Resource = $r('app.media.app_icon')
  @State isShow: boolean = false
  @State isShow2: boolean = false
  private menuElementList: Array<MenuElement> = [
    { 
        value: '菜单一',
        icon: $r('app.media.app_icon'),
        action: () => {console.log('www data click on menu 1')}
    },
    { 
        value: '菜单二',
        icon: $r('app.media.app_icon'),
        action: () => {console.log('www data click on menu 2')}
    },
    { 
        value: '菜单三',
        icon: $r('app.media.app_icon'),
        action: () => {console.log('www data click on menu 3')}
    },
    { 
        value: '菜单四',
        icon: $r('app.media.app_icon'),
        action: () => {console.log('www data click on menu 4')}
    },
    { 
        value: '菜单五',
        icon: $r('app.media.app_icon'),
        action: () => {console.log('www data click on menu 5')}
    },
  ]

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr,content: '菜单选项'})
      MenuItem({startIcon: this.iconStr,content: '菜单选项'})
      MenuItem({startIcon: this.iconStr,content: '菜单选项'})
    }
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({space: 10}) {
          Web({ src: '', controller: this.controller })
          // 触发自定义弹窗
            .onContextMenuShow((event) => {
              if (event) {
                this.result = event.result
                console.info(TAG + 'x coord = ' + event.param.x());
                console.info(TAG + 'link url = ' + event.param.getLinkUrl());
                this.linkUrl = event.param.getLinkUrl();
              }
              console.info(TAG, `x: ${this.offsetX}, y: ${this.offsetY}`);
              this.showMenu = true;
              this.offsetX = 0;
              this.offsetY = Math.max(this.uiContext!.px2vp(event?.param.y() ?? 0) - 0, 0);
              return true;
            })
            .bindMenu(this.showMenu, this.MenuBuilder(), {
              enableArrow: false,
              placement: Placement.LeftTop,
              offset: {x: this.offsetX,y: this.offsetY},
              mask: false,
              onDisappear: () => {
                this.showMenu = false;
                this.result!.closeContextMenu();
              },
              showInSubWindow: false
            })
            .fileAccess(true)
            .javaScriptAccess(true)
            .domStorageAccess(true)
        }
        .width('100%')
        .height('100%')
      }
    }.title('BindMenu_IsShow')
    .onBackPressed(() => {
      // 弹出路由栈栈顶元素
      this.pageInfos.pop();
      return true;
    }).onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}