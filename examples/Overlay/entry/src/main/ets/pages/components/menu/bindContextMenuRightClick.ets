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
export function BindContextMenuRightClickBuilder(name: string, param: Object) {
  DirectiveMenuExample()
}

@Entry
@Component
struct DirectiveMenuExample {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Text('Options')
      Divider().strokeWidth(2).margin(5).color('#F0F0F0')
      Text('Hide')
      Divider().strokeWidth(2).margin(5).color('#F0F0F0')
      Text('Exit')
    }
    .width(200)
  }

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
        Column() {
          Text('DirectiveMenuExample')
            .fontSize(20)
            .width('100%')
            .height('25%')
            .backgroundColor('#F0F0F0')
            .textAlign(TextAlign.Center)
            .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
              enableArrow: true,
              placement: Placement.Bottom
            })
        }
      }
      .width('100%')
      .height('100%')
    }
    .title('BindContextMenuRightClick')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}