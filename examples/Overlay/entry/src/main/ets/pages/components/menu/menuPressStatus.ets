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

import { LengthMetrics } from '@ohos.arkui.node';

@Builder
export function MenuPressStatusBuilder(name: string, param: Object) {
  PressStatusDemo()
}

@Component
struct PressStatusDemo {
  pathStack: NavPathStack = new NavPathStack()
  private selects: ResourceStr[] = ['Linear', 'Ease', 'FastOutSlowIn', 'Sharp', 'Rhythm', 'Smooth', 'Friction'];
  private selectOption: SelectOption[] = [];
  @State isShow: boolean = false
  controller: TextController = new TextController()
  options: TextOptions = { controller: this.controller }

  aboutToAppear() {
    this.selects.forEach((selects, index) => {
      this.selectOption[index] = { value: selects }
    })
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: $r('sys.media.ohos_ic_public_copy'), content: '剪切', labelInfo: 'Ctrl+X' })
      MenuItem({ startIcon: $r('sys.media.ohos_ic_public_copy'), content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ startIcon: $r('sys.media.ohos_ic_public_copy'), content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ startIcon: $r('sys.media.ohos_ic_public_copy'), content: '全选', labelInfo: 'Ctrl+A' })
    }.menuItemDivider({ strokeWidth: LengthMetrics.px(1), color: Color.Gray })
  }

  @Builder
  LongPressImageCustomMenu() {
    Column() {
      Menu() {
        MenuItemGroup() {
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Long Press Image Menu 1', labelInfo: '' })
            .onClick((event) => {
              this.controller.closeSelectionMenu()
            })
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Long Press Image Menu 2', labelInfo: '' })
          MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Long Press Image Menu 3', labelInfo: '' })
        }
      }
      .radius($r('sys.float.ohos_id_corner_radius_card'))
      .clip(true)
      .backgroundColor('#F0F0F0')
    }
  }

  @Builder
  MenuItemContent() {
    Text('MenuItem')
      .height(50)
  }

  @Builder
  MyCustomMenu() {
    Menu() {
      MenuItem(this.MenuItemContent())
      MenuItem(this.MenuItemContent())
      MenuItem(this.MenuItemContent())
      MenuItem(this.MenuItemContent())
    }.menuItemDivider({ strokeWidth: LengthMetrics.px(1), color: Color.Gray })
  }

  build() {
    NavDestination() {
      Column({ space: 50 }) {

        Button('BindMenu非子窗')
          .bindMenu(this.MyMenu())

        Button('BindMenu子窗')
          .bindContextMenu(this.MyMenu(), ResponseType.LongPress)

        Button('当成普通组件使用')
          .bindPopup(this.isShow, {
            builder: this.MyMenu(),
            onWillDismiss: () => {
              this.isShow = false;
            }
          })
          .onClick(() => {
            this.isShow = !this.isShow
          })

        Button('BindMenu自定义MenuItem')
          .bindMenu(this.MyCustomMenu())

        Text(undefined, this.options) {
          Span('Hello World')
          ImageSpan($r('app.media.app_icon'))
            .width('100px')
            .height('100px')
            .objectFit(ImageFit.Fill)
            .verticalAlign(ImageSpanAlignment.CENTER)
        }
        .bindSelectionMenu(TextSpanType.IMAGE, this.LongPressImageCustomMenu, TextResponseType.LONG_PRESS, {
          onDisappear: () => {
            console.info(`自定义选择菜单关闭时回调`)
          },
          onAppear: () => {
            console.info(`自定义选择菜单弹出时回调`)
          }
        })

      }.padding(24)
    }
    .title('MenuPressStatus')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { PressStatusDemo };