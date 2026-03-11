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

import window from '@ohos.window';
import base from '@ohos.base';
import { TitleBar } from '../common/TitleBar'

@Entry
@Component
export struct ArkUIHDS_NavDestination_0050 {
  private myWindow: window.Window | null = null;

  createWindow() {
    try {
      window.createWindow({ name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this) })
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(600, 1320);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/NavDestinationAdaptationImage/ArkUIHDS_NavDestination_0010', ls)
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
    Column() {
      TitleBar({ name: 'NavDestination_0050' })
      Button("createWindow").onClick(() => {
        this.createWindow();
      }).width('40%')
        .height(50)
        .margin(10)
    }
  }
}