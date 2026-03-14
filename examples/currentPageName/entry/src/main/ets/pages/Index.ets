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

import router from '@ohos.router';
import AppController from '@hms.ai.appController';

@Entry
@Component
struct Index {
  @State message: string = 'Hello';

  aboutToAppear() {
    setInterval(() =>{
      let focusedWindowId: number = AppController.getFocusedWindowId();
      AppController.getPageContent(focusedWindowId).then((inspectorTreeInfo: string) => {
        console.log("wxlJS::::::::::::::::::::::");
      });
    }, 5000);
  }

  build() {
    Column() {
      Text(this.message)
        .id('HelloArkUI')
        .fontSize(50)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })

      Button('基本功能验证')
        .margin({  top: 60, bottom: 40 })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/SimpleNavigation'
          })
        })

    }
    .height('100%')
    .width('100%')
  }
}