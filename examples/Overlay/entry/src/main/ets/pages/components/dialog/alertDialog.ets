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

import router from '@ohos.router';
import {TestListOption} from '../../../common/DataModel'
@Builder
export function AlertDialogBuilder(name: string, param: Object) {
  AlertDialogExample()
}

const testList: TestListOption[] = [
  { title: '警告弹窗_1个button', url: 'pages/components/dialog/page/AlertDialogTestLevel0_0' },
  { title: '警告弹窗_2个button', url: 'pages/components/dialog/page/AlertDialogTestLevel0_1' },
  { title: '警告弹窗_多个button', url: 'pages/components/dialog/page/AlertDialogTestLevel0_2' },
  { title: '警告弹窗_基本功能_3', url: 'pages/components/dialog/page/AlertDialogTestLevel0_3' },
]

@Entry
@Component
struct AlertDialogExample {
  pathStack: NavPathStack = new NavPathStack()
  build() {
    NavDestination() {
      List({ space: 8 }) {
        ForEach(testList, (item: TestListOption) => {
          ListItem() {
            Text(item.title).width('100%').backgroundColor(Color.Pink).fontSize(20)
              .onClick(() => {
                router.pushUrl({
                  url: item.url
                }, router.RouterMode.Single)
              })
          }
        }, (item: TestListOption) => item.title)
      }.borderWidth(2).padding(5)
    }
    .title('AlertDialog')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
