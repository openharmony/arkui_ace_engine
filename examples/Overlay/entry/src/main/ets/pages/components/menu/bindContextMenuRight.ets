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

import { subMenuOne, subMenuTwo, subMenuThree } from './customMenu';

@Builder
export function bindContextMenuRightBuilder(name: string, param: Object) {
  bindContextMenuRightExample()
}

@Entry
@Component
struct bindContextMenuRightExample {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  MenuOne() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项A',
        builder: subMenuOne()
      })
      MenuItemGroup() {
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项B',
          builder: subMenuOne()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项C',
          builder: subMenuOne()
        })
      }

      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项D',
        builder: subMenuOne()
      })
    }
    .width('40%')
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  MenuTwo() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项A',
        builder: subMenuTwo()
      })
      MenuItemGroup() {
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项B',
          builder: subMenuTwo()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项C',
          builder: subMenuTwo()
        })
      }

      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项D',
        builder: subMenuTwo()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项E',
        builder: subMenuTwo()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项F',
        builder: subMenuTwo()
      })
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  MenuThree() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项A',
        builder: subMenuThree()
      })
      MenuItemGroup() {
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项B',
          builder: subMenuThree()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项C',
          builder: subMenuThree()
        })
      }

      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项D',
        builder: subMenuThree()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项E',
        builder: subMenuThree()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项F',
        builder: subMenuThree()
      })
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Button('LongPress for menuOne')
          .margin({ right: '35%' })
          .backgroundColor('#55DFFE')
          .width('40%')
          .bindContextMenu(this.MenuOne, ResponseType.LongPress, {
            placement: Placement.Right,
          })
        Button('LongPress for menuTwo')
          .margin({ right: '35%' })
          .backgroundColor('#55DFFE')
          .width('40%')
          .bindContextMenu(this.MenuTwo, ResponseType.LongPress, {
            placement: Placement.Right,
          })
        Button('LongPress for menuThree')
          .margin({ right: '35%' })
          .backgroundColor('#55DFFE')
          .width('40%')
          .bindContextMenu(this.MenuThree, ResponseType.LongPress, {
            placement: Placement.Right,
          })
      }
      .height('100%')
      .width('100%')
    }
    .title('bindContextMenuPreviewRight')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
