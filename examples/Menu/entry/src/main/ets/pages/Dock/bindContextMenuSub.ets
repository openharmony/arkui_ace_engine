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
struct ContextMenuSubExample {

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '子菜单1' })
      MenuItem({ content: '子菜单2' })
      MenuItem({ content: '子菜单3' })
      MenuItem({ content: '子菜单4' })
      MenuItem({ content: '子菜单5' })
      MenuItem({ content: '子菜单6' })
      MenuItem({ content: '子菜单7' })
      MenuItem({ content: '子菜单8' })
      MenuItem({ content: '子菜单9' })
      MenuItem({ content: '子菜单10' })
      MenuItem({ content: '子菜单11' })
      MenuItem({ content: '子菜单12' })
      MenuItem({ content: '子菜单13' })
      MenuItem({ content: '子菜单14' })
      MenuItem({ content: '子菜单15' })
      MenuItem({ content: '子菜单16' })
      MenuItem({ content: '子菜单17' })
      MenuItem({ content: '子菜单18' })
      MenuItem({ content: '子菜单19' })
      MenuItem({ content: '子菜单20' })
    }
  }

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu1',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu2',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu3',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu4',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu5' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu6' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu7',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu8' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu9' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu10',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu11' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu12' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu13',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu14' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu15' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu16',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu17' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu18' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu19' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu20',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
    }
  }

  build() {
    Column() {
      Text('RightClick for menu').fontSize(25)
    }
    .bindContextMenu(this.MenuBuilder, ResponseType.RightClick)
    .width('100%')
    .height('100%')
  }
}