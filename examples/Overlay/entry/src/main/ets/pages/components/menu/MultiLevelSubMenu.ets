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
export function MultiLevelSubMenuBuilder(name: string, param: Object) {
  MultiLevelSubMenuExample()
}

@Entry
@Component
struct MultiLevelSubMenuExample {
  pathStack: NavPathStack = new NavPathStack()

  private menuItemMargin(): Length | undefined {
    return 4;
  }

  private menuItemPadding(): Length | undefined {
    return 12;
  }

  @Builder
  SubMenuBuilder() {
    Menu() {
      MenuItem({ content: ' aa', builder: this.SubMenuBuilder() })
      MenuItem({ content: ' bb', builder: this.SubMenuBuilder() })
    }.width(20)
  }

  @Builder
  MenuBuilder() {
    Menu() {
      MenuItem({
        content: 'AAAAAAAAA'.repeat(2),
        labelInfo: 'A',
        builder: this.SubMenuBuilder()
      })
        .margin({
          left: this.menuItemMargin(),
          right: this.menuItemMargin(),
        })
        .padding({
          left: this.menuItemPadding(),
          right: this.menuItemPadding(),
        })
      MenuItem({
        content: 'AAAAAAAAA'.repeat(2),
        labelInfo: 'B',
        builder: this.SubMenuBuilder()
      })
      MenuItem({
        content: 'AAAAAAAAA'.repeat(2),
        labelInfo: 'C',
        builder: this.SubMenuBuilder()
      })
      MenuItem({
        content: 'AAAAAAAAA'.repeat(2),
        labelInfo: 'D',
        builder: this.SubMenuBuilder()
      })
    }
    .padding({
      left: 0,
      right: 0,
    })
  }

  build() {
    NavDestination() {
      Row() {
        Button('bindMenu: 菜单')
          .key('bindMenu: 菜单')
          .backgroundColor(Color.Orange)
          .borderRadius(0)
          .bindMenu(this.MenuBuilder())
      }
      .width('100%')
      .justifyContent(FlexAlign.End)
    }
    .title('MultiLevelSubMenu')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}