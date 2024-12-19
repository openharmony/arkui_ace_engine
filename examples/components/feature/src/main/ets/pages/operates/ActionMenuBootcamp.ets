/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, useEnabled } from 'common';
import { promptAction } from '@kit.ArkUI';

@Component
export struct ActionMenuBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableShowInSubWindow: boolean = false;
  @State showInSubWindow: boolean = false;
  @State enableIsModal: boolean = false;
  @State isModal: boolean = false;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Button('弹出菜单弹窗')
        .onClick(() => {
          try {
            promptAction.showActionMenu({
              title: 'title',
              showInSubWindow: useEnabled(this.enableShowInSubWindow, this.showInSubWindow),
              isModal: useEnabled(this.enableIsModal, this.isModal),
              buttons: [
                {
                  text: 'item1',
                  color: '#666666'
                },
                {
                  text: 'item2',
                  color: '#000000'
                },
                {
                  text: 'item3',
                  color: '#000000'
                },
              ]
            })

          } catch (err) {

          }
        })
    }

  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'ActionMenuOptions.showInSubWindow',
          isEnabled: $enableShowInSubWindow,
          value: $showInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'ActionMenuOptions.isModal',
          isEnabled: $enableIsModal,
          value: $isModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })


      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ActionMenuBootcampPreviewer {
  build() {
    ActionMenuBootcamp({
      title: '菜单弹窗/ActionMenu'
    })
  }
}
