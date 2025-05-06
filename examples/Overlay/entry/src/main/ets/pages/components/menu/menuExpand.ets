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
export function MenuExpandBuilder(name: string, param: Object) {
  MenuExpandExample()
}

@Entry
@Component
struct MenuExpandExample {
  pathStack: NavPathStack = new NavPathStack()
  @State message: string = 'Hello World';
  @State isShow: boolean = false;
  @State height1: number = 500;

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '子菜单1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单2', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '子菜单3', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单4', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '子菜单5', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单6', labelInfo: 'Ctrl+V', builder: this.SubMenu() })
    }
  }

  @Builder
  SubMenu2() {
    Menu() {
      MenuItem({ content: '子菜单1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单2', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '子菜单3', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单4', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '子菜单5', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '子菜单6', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  SIDE_EXPAND() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '内容', labelInfo: 'Ctrl+V', builder: this.SubMenu })
    }.subMenuExpandingMode(SubMenuExpandingMode.SIDE_EXPAND)
  }

  @Builder
  EMBEDDED_EXPAND() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '内容', labelInfo: 'Ctrl+V', builder: this.SubMenu })
    }.subMenuExpandingMode(SubMenuExpandingMode.EMBEDDED_EXPAND)
  }

  @Builder
  STACK_EXPAND() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
      MenuItem({ content: '内容', labelInfo: 'Ctrl+V', builder: this.SubMenu })
    }.subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  SIDE_EXPAND2() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C', builder: this.SubMenu })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V', builder: this.SubMenu })
      MenuItem({ content: '内容', labelInfo: 'Ctrl+V', builder: this.SubMenu })
    }.subMenuExpandingMode(SubMenuExpandingMode.SIDE_EXPAND)
  }

  @Builder
  SIDE_EXPAND3() {
    Column() {
      Menu() {
        MenuItem({ content: '复制', labelInfo: 'Ctrl+C', builder: this.SubMenu })
        MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V', builder: this.SubMenu })
        MenuItem({ content: '内容', labelInfo: 'Ctrl+V', builder: this.SubMenu })
      }.subMenuExpandingMode(SubMenuExpandingMode.SIDE_EXPAND)
    }
  }

  build() {
    NavDestination() {
      Column() {
        Scroll() {
          Column() {
            Button('基础场景-次级菜单类型-SIDE')
              .bindMenu(this.SIDE_EXPAND())
              .stateStyles({
                normal: {
                  .backgroundColor(Color.Yellow)
                }
              })
              .margin(20)
              .fontColor(Color.Black)

            Button('基础场景-次级菜单类型-EMBEDDED')
              .bindMenu(this.EMBEDDED_EXPAND())
              .margin(20)

            Button('基础场景-次级菜单类型-STACK')
              .bindMenu(this.STACK_EXPAND())
              .margin(20)

            Button('带箭头的菜单')
              .bindMenu(this.SIDE_EXPAND(), { enableArrow: true })
              .margin(20)

            Button('设置多个主菜单选项弹出side次级菜单')
              .bindMenu(this.SIDE_EXPAND2(), { showInSubWindow: false })
              .margin(20)

            Button('设置多个主菜单选项弹出side次级菜单，子窗场景')
              .bindContextMenu(this.SIDE_EXPAND2(), ResponseType.RightClick)
              .margin(20)

            Button('预览菜单测试')
              .bindContextMenu(this.isShow, this.SIDE_EXPAND2(), { preview: MenuPreviewMode.IMAGE })
              .onClick(() => {
                console.error('111')
                this.isShow = !this.isShow
              })
              .margin(20)

            Button('设置多个主菜单选项弹出side次级菜单')
              .bindMenu(this.SIDE_EXPAND3(), { showInSubWindow: false })
              .margin(20)
          }
        }.height(this.height1)
      }
      .height('100%')
      .width('100%')
    }
    .title('MenuExpand')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { MenuExpandExample };