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

@Entry
@Component
struct BindContextMenu {
  @State message: string = 'Hello World';
  private iconStr: ResourceStr = $r("sys.media.ohos_save_button_filled")
  private iconStr2: ResourceStr = $r("sys.media.ohos_ic_public_ok_filled")
  @State isShown: boolean = false;
  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('Test menu item 1')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 2')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
    }.width(100)
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
      Image($r('app.media.app_icon'))
        .width(200)
        .height(200)
    }
  }
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }
  @Builder
  MyMenu1() {
    Menu() {
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项",
          endIcon: this.iconStr2,
          builder: (): void => this.SubMenu()
        })
        MenuItem({
          startIcon: $r("app.media.app_icon"),
          content: "菜单选项",
          endIcon: this.iconStr2,
          builder: (): void => this.SubMenu()
        })
      }
    }
  }

  build() {
    Column() {
      Column() {
        Text('bindContextMenu:通过配置responseType.LongPress弹出菜单')
        Button('原生')
          .bindContextMenu(this.MenuBuilder, ResponseType.LongPress)
        Text('bindContextMenu:配置responseType.RightClick、enableArrow弹出指向型菜单')
        Button('原生')
          .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
            enableArrow: true,
            placement: Placement.Bottom
          })
        Text('bindContextMenu:配置responseType.LongPress、preview的CustomBuilder类型弹出菜单自定义预览样式')
        Button('原生')
          .bindContextMenu(this.MyMenu, ResponseType.LongPress,
            {
              preview: this.MyPreview
            })
        Text('bindContextMenu:二级菜单')
        Button('原生')
          .bindContextMenu(this.MyMenu1, ResponseType.LongPress)
        Text('bindContextMenu通过配置isShown弹出菜单预览样式')
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
      }
      .width('100%')
    }
    .height('100%')
  }
}