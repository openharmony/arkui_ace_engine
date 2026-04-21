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
@Entry
@Component
struct BindMenu {
  @State message: string = 'Hello World';
  @State listData: number[] = [0, 0, 0];
  @State symbolIconModifier1: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_photo')).fontSize('24vp');
  @State symbolIconModifier2: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_photo')).fontSize('24vp');

  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      ForEach(this.listData, (item:number, index) => {
        Column() {
          Row() {
            // $r('app.media.icon')需要替换为开发者所需的图像资源文件。
            Image($r("app.media.app_icon")).width(20).height(20).margin({ right: 5 })
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
  private iconStr: ResourceStr = $r("sys.media.ohos_save_button_filled")
  private iconStr2: ResourceStr = $r("sys.media.ohos_ic_public_ok_filled")
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
      MenuItem({ startIcon: $r("app.media.app_icon"), content: "菜单选项" })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: "菜单选项",
        endIcon: this.iconStr2,
        builder: ():void=>this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: "菜单选项",
          endIcon: this.iconStr2,
          builder: ():void=>this.SubMenu()
        })
        MenuItem({
          startIcon: $r("app.media.app_icon"),
          content: "菜单选项",
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
  build() {
    Column() {
      Column() {
        Text('bindMenu通过配置MenuElement弹出普通菜单').fontSize(16).width("100%")
          Button('bindMenu')
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
          ])
        Text('bindMenu通过配置CustomBuilder弹出自定义菜单').fontSize(16).width("100%")
          Button('bindMenu1')
          .bindMenu(this.MenuBuilder, { hapticFeedbackMode: HapticFeedbackMode.ENABLED })
        Text('bindMenu通过配置MenuElement的symbolIcon弹出菜单').fontSize(16).width("100%")
          Button('bindMenu2')
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
        Text('bindMenu:配置MenuItem中的builder参数实现多级菜单')
        Button('bindMenu3')
          .bindMenu(this.MyMenu)

      }
      .width('100%')
    }
    .height('100%')
  }
}