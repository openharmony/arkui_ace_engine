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


import { promptAction } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit';

@Builder
export function ShowToastBuilder(name: string, param: Object) {
  toastExample02()
}
@Entry
@Component
struct toastExample02 {
  pathStack: NavPathStack = new NavPathStack()
  @State toastId: number = 0;

  build() {
    NavDestination() {
      Column() {
        Button('Open Toast')
          .height(100)
          .type(ButtonType.Capsule)
          .onClick(() => {
            promptAction.openToast({
              message: 'Toast Massage',
              duration: 10000,
            }).then((toastId: number) => {
              this.toastId = toastId;
            })
              .catch((error: BusinessError) => {
                console.error(`openToast error code is ${error.code}, message is ${error.message}`)
              })
          })
        Blank().height(50);
        Button('Close Toast')
          .height(100)
          .type(ButtonType.Capsule)
          .onClick(() => {
            try {
              promptAction.closeToast(this.toastId);
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`CloseToast error code is ${code}, message is ${message}`);
            };
          })
      }
      .height('100%')
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .title('showToastTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}