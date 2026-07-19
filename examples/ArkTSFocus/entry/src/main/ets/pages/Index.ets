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

interface FocusFeatureItem {
  name: string
  description: string
  router: string
}

@Entry
@Component
struct Index {
  private demandList: FocusFeatureItem[] = [
    {
      name: '基础焦点能力',
      description: 'focusable、defaultFocus、onFocus、onBlur',
      router: 'pages/BasicFocus'
    },
    {
      name: 'Tab 键导航',
      description: 'tabIndex、tabStop',
      router: 'pages/TabNavigation'
    },
    {
      name: '自定义焦点路径',
      description: 'nextFocus 方向键跳转',
      router: 'pages/CustomNextFocus'
    },
    {
      name: '焦点域（分组与优先级）',
      description: 'focusScopeId、focusScopePriority、groupDefaultFocus',
      router: 'pages/FocusScope'
    },
    {
      name: '自定义焦点框样式',
      description: 'focusBox(FocusBoxStyle)',
      router: 'pages/FocusBoxStyle'
    },
    {
      name: '触摸聚焦与命令式 API',
      description: 'focusOnTouch、focusControl.requestFocus',
      router: 'pages/FocusOnTouch'
    }
  ]

  build() {
    Column() {
      Text('ArkTS 焦点示例')
        .width('100%')
        .height(56)
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .padding({ top: 12 })

      List({ space: 8 }) {
        ForEach(this.demandList, (item: FocusFeatureItem) => {
          ListItem() {
            Row({ space: 12 }) {
              Column({ space: 4 }) {
                Text(item.name)
                  .fontSize(18)
                  .fontWeight(FontWeight.Medium)
                  .fontColor('#333333')
                Text(item.description)
                  .fontSize(13)
                  .fontColor('#999999')
              }
              .alignItems(HorizontalAlign.Start)
              .layoutWeight(1)

              Text('›')
                .fontSize(24)
                .fontColor('#CCCCCC')
            }
            .width('100%')
            .padding({ left: 16, right: 16, top: 14, bottom: 14 })
            .backgroundColor('#FFFFFF')
            .borderRadius(8)
            .onClick(() => {
              this.getUIContext().getRouter().pushUrl({ url: item.router });
            })
          }
        }, (item: FocusFeatureItem) => item.name)
      }
      .width('100%')
      .layoutWeight(1)
      .padding({ left: 12, right: 12 })
      .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .height('100%')
  }
}
