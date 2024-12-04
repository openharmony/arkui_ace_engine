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
import { promptAction } from '@kit.ArkUI';

@Component
export struct TabContentBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State selectedIndex: number = 0;

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
      Column() {
        Tabs({ index: $$this.selectedIndex, barPosition: BarPosition.Start }) {
          TabContent() {
            Text('1')
          }
          .tabBar('tab1')
          .onWillShow(() => {
            promptAction.showToast({
              message: 'tab1出现了'
            })
          })
          .onWillHide(() => {
            promptAction.showToast({
              message: 'tab1隐藏了'
            })
          })

          TabContent() {
            Text('2')
          }
          .tabBar('tab2')
          .onWillShow(() => {
            promptAction.showToast({
              message: 'tab2出现了'
            })
          })
          .onWillHide(() => {
            promptAction.showToast({
              message: 'tab2隐藏了'
            })
          })

          TabContent() {
            Text('3')
          }
          .tabBar('tab3')
          .onWillShow(() => {
            promptAction.showToast({
              message: 'tab3出现了'
            })
          })
          .onWillHide(() => {
            promptAction.showToast({
              message: 'tab3隐藏了'
            })
          })
        }
        .onChange((index: number) => {
          this.selectedIndex = index;
        })
      }.width('100%').height('100%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct TabContentBootcampPreviewer {
  build() {
    TabContentBootcamp({ title: '页签内容/TabContent' })
  }
}