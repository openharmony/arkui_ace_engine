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

/*用例描述
 1、本用例通过给Scroll设置.layoutWeight(1)和.align(Alignment.TopStart)，
 使Scroll内容大小小于自身时，内容置顶显示，Scroll内容大小大于自身时，可正常滚动到底部
*/
@Entry
@Component
struct ScrollWithLayoutWeight {
  @State tabsIndex: number = 0;
  private tabsController: TabsController = new TabsController();
  private scroller: Scroller = new Scroller();
  @State arr: string[] = ['信息咨询', '协同办公', '内部邮箱'];
  @State menu1: string[] = ['菜单1', '菜单2', '菜单3'];
  @State menu2: string[] =
    ['菜单1', '菜单2', '菜单3', '菜单4', '菜单5', '菜单6', '菜单7', '菜单8', '菜单9', '菜单10', '菜单11', '菜单12',
      '菜单13'];
  @State menu3: string[] = ['菜单1', '菜单2', '菜单3', '菜单4', '菜单5', '菜单6', '菜单7'];
  @State menu4: string[] = ['菜单1'];

  @Builder
  MenuItem(item: string) {
    Column() {
      Image($r('app.media.startIcon'))
        .width(34)
        .width(34)
        .objectFit(ImageFit.Fill)

      Text(item)
        .fontSize(16)
        .margin({ top: 6, bottom: 6 })
        .textAlign(TextAlign.Center)
    }
    .width(90)
  }

  @Builder
  MenuList(menuArr: string[]) {
    ForEach(menuArr, (item: string) => {
      GridCol({ span: 6 }) {
        this.MenuItem(item)
      }
    })
  }

  @Builder
  MenuView(canScroll: boolean) {
    Column() {
      Text('我是标题')
        .width('100%')
        .margin({ top: 10, bottom: 10 })
        .textAlign(TextAlign.Center)

      Scroll(this.scroller) {
        Column({ space: 12 }) {
          ForEach(this.arr, (title: string) => {
            Column() {
              Text(title)
                .textAlign(TextAlign.Start)
                .width('95%')
                .fontSize(18)
                .margin({ top: 12, bottom: 12 })

              Line()
                .width('95%')
                .height(1)
                .backgroundColor(Color.Gray)

              GridRow({ columns: 24, gutter: { y: 10 } }) {
                if (title === '信息咨询') {
                  this.MenuList(this.menu1)
                } else if (title === '协同办公') {
                  if (canScroll) {
                    this.MenuList(this.menu2)
                  } else {
                    this.MenuList(this.menu3)
                  }
                } else if (title === '内部邮箱') {
                  if (canScroll) {
                    this.MenuList(this.menu2)
                  } else {
                    this.MenuList(this.menu4)
                  }
                }
              }
              .margin({ top: 15, bottom: 15 })
            }
            .width('100%')
            .backgroundColor(Color.White)
          })
        }
      }
      .layoutWeight(1)
      .align(Alignment.TopStart)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
  }

  build() {
    Tabs({ barPosition: BarPosition.End, index: this.tabsIndex, controller: this.tabsController }) {
      TabContent() {
        this.MenuView(true)
      }.tabBar(SubTabBarStyle.of('可滚动时'))

      TabContent() {
        this.MenuView(false)
      }.tabBar(SubTabBarStyle.of('不可滚动时'))
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
    .onChange((index: number) => {
      this.tabsIndex = index;
    })
  }
}