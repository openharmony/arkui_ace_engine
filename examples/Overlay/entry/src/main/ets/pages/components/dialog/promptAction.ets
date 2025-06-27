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

@Builder
export function PromptActionBuilder(name: string, param: Object) {
  PromptActionExample()
}

@Entry
@Component
struct PromptActionExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('promptAction.showDialog')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        Button('showDialog')
          .onClick(() => {
            promptAction.showDialog({
              title: 'Title Info',
              message: 'Message Info',
              buttons: [
                {
                  text: 'button1',
                  color: '#000000'
                },
                {
                  text: 'button2',
                  color: '#000000'
                }
              ],
            })
              .then(data => {
                console.info('showDialog success, click button: ' + data.index);
              })
              .catch((err: Error) => {
                console.info('showDialog error: ' + err);
              })
          })

      }.width('100%').margin({ top: 5 })
    }
    .title('PromptAction')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}