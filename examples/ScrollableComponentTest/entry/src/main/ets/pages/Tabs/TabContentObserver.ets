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

import { uiObserver } from '@kit.ArkUI'

function callbackWithIdFunc(info: uiObserver.TabContentInfo) {
  console.info('tabContentUpdate width id', JSON.stringify(info))
}

function callbackFunc(info: uiObserver.TabContentInfo) {
  console.info('tabContentUpdate', JSON.stringify(info))
}

@Entry
@Component
struct TabContentObserver {
  @State currentIndex: number = 0
  private controller: TabsController = new TabsController()
  @State isShow: boolean = false

  build() {
    Column() {
      Tabs({ index: this.currentIndex, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor('#00CB87')
        }.tabBar('green').id('tabContentId1')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor('#007DFF')
        }.tabBar('blue').id('tabContentId2')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor('#FFBF00')
        }.tabBar('yellow').id('tabContentId3')

        if (this.isShow) {
          TabContent() {
            Column().width('100%').height('100%').backgroundColor('#E67C92')
          }.tabBar('pink').id('tabContentId4')
        }
      }
      .id('tabsId')
      .width(360)
      .height(296)
      .onChange((index: number) => {
        console.info('onChange index:' + index)
        this.currentIndex = index
      })
      .backgroundColor('#F1F3F5')

      Row() {
        Button('observer on with id')
          .onClick(() => {
            uiObserver.on('tabContentUpdate', { id: 'tabsId' }, callbackWithIdFunc)
          })

        Button('observer off with id')
          .onClick(() => {
            uiObserver.off('tabContentUpdate', { id: 'tabsId' }, callbackWithIdFunc)
          })
      }.margin({ top: 5 })

      Row() {
        Button('observer on')
          .onClick(() => {
            uiObserver.on('tabContentUpdate', callbackFunc)
          })

        Button('observer off')
          .onClick(() => {
            uiObserver.off('tabContentUpdate', callbackFunc)
          })
      }.margin({ top: 5 })

      Row() {
        Text('changeIndex:').margin({ right: 10 }).fontSize(15)
        ForEach([0, 1, 2, 3], (index: number) => {
          Button(index.toString())
            .onClick(() => {
              this.controller.changeIndex(index)
            })
        })
      }.margin({ top: 5 })

      Row() {
        Text('index:').margin({ right: 10 }).fontSize(15)
        ForEach([0, 1, 2, 3], (index: number) => {
          Button(index.toString())
            .onClick(() => {
              this.controller.changeIndex(index)
            })
        })
      }.margin({ top: 5 })

      Row() {
        Button('Show last node')
          .onClick(() => {
            this.isShow = true
          })

        Button('Hide last node')
          .onClick(() => {
            this.isShow = false
          })
      }.margin({ top: 5 })
    }
  }
}