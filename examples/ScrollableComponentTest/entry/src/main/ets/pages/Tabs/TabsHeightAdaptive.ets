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

@Entry
@Component
struct TabsHeightAdaptive {
  @State currentIndex: number = 1
  private controller: TabsController = new TabsController()
  @State isShow: boolean = false
  @State tabsHeight: Length = 'auto'
  @State columnHeight: Length = '50%'

  build() {
    Column() {
      Tabs({ index: this.currentIndex, controller: this.controller }) {
        if (this.isShow) {
          TabContent() {
            Column().width('100%').height('500vp').backgroundColor(Color.Green)
          }.tabBar('Green')

          TabContent() {
            Column().width('100%').height(100).backgroundColor(Color.Blue)
          }.tabBar('Blue')

          TabContent() {
            Column().width('100%').height(0).backgroundColor(Color.Yellow)
          }.tabBar('Yellow')

          TabContent() {
            Column().width('100%').height('100%').backgroundColor(Color.Pink)
          }.tabBar('Pink')
        }
      }
      .backgroundColor(0xf1f3f5)
      .width('100%')
      .height(this.tabsHeight)
      .barHeight(0)
      .onChange((index: number) => {
        this.currentIndex = index
      })

      // Tabs高度自适应时，初始数据为空，数据异步加载后，页面是否可正常显示
      Row() {
        Button('Show Data')
          .onClick(() => {
            this.isShow = true
          })

        Button('Hide data')
          .onClick(() => {
            this.isShow = false
          })
      }.margin({ top: 5 })

      // Tabs高度自适应时，跳转至高度为0的页面后，是否还可以正常跳转至其他页面
      Row() {
        Text('changeIndex').margin({ left: 10, right: 10 }).fontSize(15)
        ForEach([0, 1, 2, 3], (index: number) => {
          Button(index.toString())
            .onClick(() => {
              this.controller.changeIndex(index)
            })
        })
      }.margin({ top: 5 })

      // 动态变化Tabs父组件高度为其他百分比，Tabs的高度是否可正常跟随父组件高度变化
      Row() {
        Button('height auto')
          .onClick(() => {
            this.columnHeight = '50%'
            this.tabsHeight = 'auto'
          })

        Button('equal parent height')
          .onClick(() => {
            this.columnHeight = '80%'
            this.tabsHeight = '100%'
          })
      }.margin({ top: 5 })
    }
    .height(this.columnHeight)
  }
}