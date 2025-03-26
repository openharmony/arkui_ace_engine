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

@Builder
export function ActionSheetBuilder(name: string, param: Object) {
  ActionSheetExample()
}

@Entry
@Component
struct ActionSheetExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('ActionSheet.show')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        Button('Click to Show ActionSheet')
          .onClick(() => {
            ActionSheet.show({
              title: 'ActionSheet title',
              subtitle: 'ActionSheet subtitle',
              message: 'message',
              autoCancel: true,
              confirm: {
                defaultFocus: true,
                value: 'Confirm button',
                action: () => {
                  console.log('Get Alert Dialog handled')
                }
              },
              cancel: () => {
                console.log('actionSheet canceled')
              },
              sheets: [
                {
                  title: 'apples',
                  action: () => {
                    console.log('apples')
                  }
                },
                {
                  title: 'bananas',
                  action: () => {
                    console.log('bananas')
                  }
                },
                {
                  title: 'pears',
                  action: () => {
                    console.log('pears')
                  }
                }
              ]
            })
          })

        Text('UIContext.showActionSheet')
          .fontColor(Color.Gray)
          .width('100%')
          .padding(10)

        Button('Click to Show ActionSheet')
          .onClick(() => {
            this.getUIContext().showActionSheet({
              title: 'ActionSheet title',
              subtitle: 'ActionSheet subtitle',
              message: 'message',
              autoCancel: true,
              confirm: {
                defaultFocus: true,
                value: 'Confirm button',
                action: () => {
                  console.log('Get Alert Dialog handled')
                }
              },
              cancel: () => {
                console.log('actionSheet canceled')
              },
              sheets: [
                {
                  title: 'apples',
                  action: () => {
                    console.log('apples')
                  }
                },
                {
                  title: 'bananas',
                  action: () => {
                    console.log('bananas')
                  }
                },
                {
                  title: 'pears',
                  action: () => {
                    console.log('pears')
                  }
                }
              ]
            })
          })
      }.width('100%').margin({ top: 5 })
    }
    .title('ActionSheet')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}