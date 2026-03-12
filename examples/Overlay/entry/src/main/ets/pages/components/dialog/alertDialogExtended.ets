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
import { TestListOption } from '../../../common/DataModel'

@Builder
export function AlertDialogExtendedBuilder(name: string, param: Object) {
  AlertDialogExtendedExample()
}

const testList: TestListOption[] = [
  { title: '警告弹窗_扩展功能_样式测试', url: 'pages/components/dialog/page/AlertDialogExtended_Styles' },
  { title: '警告弹窗_扩展功能_事件回调', url: 'pages/components/dialog/page/AlertDialogExtended_Callbacks' },
  { title: '警告弹窗_扩展功能_位置对齐', url: 'pages/components/dialog/page/AlertDialogExtended_Alignment' },
  { title: '警告弹窗_扩展功能_自动取消', url: 'pages/components/dialog/page/AlertDialogExtended_AutoCancel' },
  { title: '警告弹窗_扩展功能_遮罩颜色', url: 'pages/components/dialog/page/AlertDialogExtended_MaskColor' },
  { title: '警告弹窗_扩展功能_圆角测试', url: 'pages/components/dialog/page/AlertDialogExtended_CornerRadius' },
  { title: '警告弹窗_扩展功能_文本样式', url: 'pages/components/dialog/page/AlertDialogExtended_TextStyle' },
  { title: '警告弹窗_扩展功能_按钮样式', url: 'pages/components/dialog/page/AlertDialogExtended_ButtonStyle' },
]

@Entry
@Component
struct AlertDialogExtendedExample {
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
    .title('AlertDialog Extended')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
