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

import { TestListOption } from '../../../common/DataModel'

@Builder
export function CustomDialogBuilder(name: string, param: Object) {
  CustomDialogExample()
}

const testList: TestListOption[] = [
  { title: '自定义弹窗_基本功能_0', url: 'pages/components/dialog/page/CustomDialogTestLevel0_0' },
  { title: '自定义弹窗_基本功能_1', url: 'pages/components/dialog/page/CustomDialogTestLevel0_1' },
  { title: '自定义弹窗_基本功能_生命周期', url: 'pages/components/dialog/page/CustomDialogTestLevel0_2' },
]

@Entry
@Component
struct CustomDialogExample {
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
    .title('CustomDialog')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}