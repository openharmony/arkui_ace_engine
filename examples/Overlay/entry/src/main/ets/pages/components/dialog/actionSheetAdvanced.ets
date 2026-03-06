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
export function ActionSheetAdvancedBuilder(name: string, param: Object) {
  ActionSheetAdvancedExample()
}

const testList: TestListOption[] = [
  { title: '操作表单_高级功能_样式定制', url: 'pages/components/dialog/page/ActionSheetAdvanced_Style' },
  { title: '操作表单_高级功能_事件处理', url: 'pages/components/dialog/page/ActionSheetAdvanced_Events' },
  { title: '操作表单_高级功能_分组显示', url: 'pages/components/dialog/page/ActionSheetAdvanced_Groups' },
  { title: '操作表单_高级功能_图标选项', url: 'pages/components/dialog/page/ActionSheetAdvanced_Icons' },
]

@Entry
@Component
struct ActionSheetAdvancedExample {
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
    .title('ActionSheet Advanced')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
