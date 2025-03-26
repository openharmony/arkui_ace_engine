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

@Builder
export function BindContextMenuBuilder(name: string, param: Object) {
  BindContextMenuExample()
}

@Entry
@Component
struct BindContextMenuExample {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
    }
  }

  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(100)
        .height(100)
    }
  }

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('bindContextMenu + 长按弹出')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        Image($r('app.media.app_icon'))
          .width(100)
          .height(100)
          .bindContextMenu(this.MyMenu, ResponseType.LongPress,
            {
              preview: this.MyPreview,
              previewAnimationOptions: {
                scale: [1.0, 1.5]
              }
            })

      }.width('100%').margin({ top: 5 })
    }
    .title('BindContextMenu')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}