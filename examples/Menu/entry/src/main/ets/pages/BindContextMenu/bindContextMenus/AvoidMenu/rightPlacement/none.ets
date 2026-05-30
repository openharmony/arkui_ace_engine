/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
struct rightPlacement_none {
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '二级组件1' })
      MenuItem({ content: '二级组件2' })
      MenuItemGroup({ header: '菜单项目组' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单', endIcon: $r('app.media.app_icon') }).contentFont({ size: 20 })
      }
    }
  }

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ content: '菜单菜单' })
      MenuItem({ content: '菜单菜单' })
      MenuItem({ content: '二级菜单', builder: ():void=>this.SubMenu() })
        .id('SubMenu')
    }
  }

  build() {
    Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.End, alignItems: ItemAlign.Center }){
      Row() {
        Text('长按展示菜单')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .id('longPress')
      }
      .width('20%')
      .bindContextMenu(this.MenuBuilder, ResponseType.LongPress)
    }.height('100%')
  }
}