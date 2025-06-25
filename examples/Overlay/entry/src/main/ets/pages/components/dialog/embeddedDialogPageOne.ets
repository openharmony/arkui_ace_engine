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

import { promptAction, LevelMode, ImmersiveMode, router } from '@kit.ArkUI'

let customDialogId: number = 0

@Builder
export function EmbeddedDialogPageOneBuilder(name: string, param: Object) {
  EmbeddedDialogPageOne()
}

@Builder
function customDialogBuilder() {
  Column() {
    Text('Custom dialog Message').fontSize(20).height(100)
    Row() {
      Button('Next').onClick(() => {
        // 在弹窗内部进行路由跳转。
        router.pushUrl({url: 'pages/components/dialog/embeddedDialogPageTwo'})
      })
      Blank().width(50)
      Button('Close').onClick(() => {
        promptAction.closeCustomDialog(customDialogId)
      })
    }
  }.padding(20)
}

@Component
export struct EmbeddedDialogPageOne {
  @State message: string = 'Hello World'

  @Builder
  customDialogComponent() {
    customDialogBuilder()
  }

  build() {
    NavDestination() {
      Column() {
        Text(this.message).id('test_text')
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            const node: FrameNode | null = this.getUIContext().getFrameNodeById('test_text') || null;
            promptAction.openCustomDialog({
              builder: () => {
                this.customDialogComponent()
              },
              levelMode: LevelMode.EMBEDDED, // 启用页面级弹出框
              levelUniqueId: node?.getUniqueId(), // 设置页面级弹出框所在页面的任意节点ID
              immersiveMode: ImmersiveMode.EXTEND, // 设置页面级弹出框蒙层的显示模式
            }).then((dialogId: number) => {
              customDialogId = dialogId
            })
          })
      }
      .width('100%')
    }
  }
}