/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import UIContext from '@ohos.arkui.UIContext';
import observer from '@ohos.arkui.observer';
import window from '@ohos.window';
import base from '@ohos.base';

@Entry
@Component
struct MainWindow9800 {
  @State stackA: NavPathStack = new NavPathStack();
  @State stackB: NavPathStack = new NavPathStack();
  private myWindow: window.Window | null = null;




  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/50019/page10', ls)
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

  createWindow2() {
    try {
      window.createWindow({name: "testWindow2", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/50019/page11', ls)
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

  createWindow3() {
    try {
      window.createWindow({name: "testWindow3", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/50019/page12', ls)
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
    Column({space:5}) {
      Button('开启TextInput子窗口')
        .onClick(() => {
          this.createWindow();
        })
      Button('开启TextArea子窗口')
        .onClick(() => {
          this.createWindow2();
        })
      Button('开启Search子窗口')
        .onClick(() => {
          this.createWindow3();
        })


    }
    .width('100%')
    .height('100%')
  }
}