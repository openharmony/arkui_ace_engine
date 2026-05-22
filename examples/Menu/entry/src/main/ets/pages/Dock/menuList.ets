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
struct MenuListExample {
  @State arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: number) => {
          ListItem() {
            Text('' + item)
              .width('100%').height(100).fontSize(16)
              .textAlign(TextAlign.Center).borderRadius(10).backgroundColor(0xFFFFFF)
          }
        }, (item: number) => item.toString())
      }.height('80%')

      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单3' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单4' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单5' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单6' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单7' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单8' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单9' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单10' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单11' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单12' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单13' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单14' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单15' })
    }
  }

  build() {
    Column() {
      Text('click for Menu').fontSize(25)
    }
    .bindMenu(this.MenuBuilder)
    .width('100%')
    .height('100%')
  }
}