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

import { promptAction } from '@kit.ArkUI'
import { BusinessError } from '@kit.BasicServicesKit';

@Builder
export function ToastBuilder(name: string, param: Object) {
  ToastExample()
}

@Entry
@Component
struct ToastExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('promptAction.showToast')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        Button('Show toast')
          .fontSize(20)
          .onClick(() => {
            try {
              this.getUIContext().getPromptAction().showToast({
                message: 'Hello World',
                duration: 2000,
                showMode: promptAction.ToastShowMode.TOP_MOST
              });
            } catch (error) {
              let message = (error as BusinessError).message
              let code = (error as BusinessError).code
              console.error(`showToast args error code is ${code}, message is ${message}`);
            }
          })
      }.width('100%').margin({ top: 5 })
    }
    .title('Toast')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}