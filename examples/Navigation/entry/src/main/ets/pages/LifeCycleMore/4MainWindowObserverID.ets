/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import UIContext from '@ohos.arkui.UIContext';
import window from '@ohos.window';
import base from '@ohos.base';
import { pageOne, pageTwo, navId1, pageThree } from './common';

@Entry
@Component
struct MainWindowObserverID {
  @State stackA: NavPathStack = new NavPathStack();
  @State stackB: NavPathStack = new NavPathStack();
  private obs: UIContext.UIObserver | null = null;
  private myWindow: window.Window | null = null;

  @Builder
  PageMapA(name: string) {
    if (name === 'pageOne') {
      pageOne({str:'MainA'})
    } else if (name === 'pageTwo'){
      pageTwo({str:'MainA'})
    } else if (name === 'pageThree'){
      pageThree({str:'MainA'})
    }
  }

  @Builder
  PageMapB(name: string) {
    if (name === 'pageOne') {
      pageOne({str:'MainB'})
    } else if (name === 'pageTwo'){
      pageTwo({str:'MainB'})
    } else if (name === 'pageThree'){
      pageThree({str:'MainB'})
    }
  }

  @Builder Title1() {
    Column() {
      Text('MainA Navigation').fontSize(18)
    }.alignItems(HorizontalAlign.Start)
  }

  @Builder Title2() {
    Column() {
      Text('MainB Navigation').fontSize(18)
    }.alignItems(HorizontalAlign.Start)
  }


  createWindow() {
    try {
      window.createWindow({name: "testWindowObserverID", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2500);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/LifeCycleMore/4SubWindowObserverID', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }


  build() {
    Scroll() {
      Column({ space: 5 }) {
        Text('全局监听+指定NavigationID').fontSize(18)
        Button('开启子窗口')
          .onClick(() => {
            this.createWindow();
          })


        Navigation(this.stackA) {
          Column({ space: 10 }) {
            Button('MainA push pageOne')
              .onClick(() => {
                this.stackA.pushPath({ name: 'pageOne', param: 1 })
              })

            NavRouter({ name: "pageOne", param: 1 }) {
              Stack({ alignContent: Alignment.Center }) {
                Text('MainA navRouter pageOne')
                  .padding(5)
                  .fontSize(20)
              }
            }.borderWidth(1)
          }

        }
        .expandSafeArea([SafeAreaType.KEYBOARD])
        .navDestination(this.PageMapA)
        .title({ builder: this.Title1, height: '40vp' })
        .backgroundColor(Color.Pink)
        .width('100%')
        .height('280vp')


        Navigation(this.stackB) {
          Column({ space: 10 }) {
            Button('MainB push pageOne')
              .onClick(() => {
                this.stackB.pushPath({ name: 'pageOne', param: 1 })
              })

            NavRouter({ name: "pageOne", param: 1 }) {
              Stack({ alignContent: Alignment.Center }) {
                Text('MainB navRouter pageOne')
                  .padding(5)
                  .fontSize(20)
              }
            }.borderWidth(1)
          }

        }
        .id(navId1)
        .expandSafeArea([SafeAreaType.KEYBOARD])
        .navDestination(this.PageMapB)
        .title({ builder: this.Title2, height: '40vp' })
        .backgroundColor('#ffc7f5c7')
        .width('100%')
        .height('280vp')

      }
      .width('100%')
    }
  }
}