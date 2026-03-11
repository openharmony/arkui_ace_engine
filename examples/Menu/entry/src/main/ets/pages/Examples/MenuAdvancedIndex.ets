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

interface ListCategories {
  title: string,
  url: string
}

@Entry
@Component
struct MenuAdvancedIndex {
  scroller: Scroller = new Scroller()
  private items: ListCategories[] = [
    { title: '示例1: 高级菜单选项配置', url: 'pages/Examples/MenuAdvancedOptions' },
    { title: '示例2: 菜单位置放置示例', url: 'pages/Examples/MenuPlacementDemo' },
    { title: '示例3: 菜单动画效果示例', url: 'pages/Examples/MenuAnimationDemo' },
    { title: '示例4: 嵌套子菜单示例', url: 'pages/Examples/MenuNestedSubMenu' },
    { title: '示例5: 菜单与预览图结合示例', url: 'pages/Examples/MenuWithPreview' },
    { title: '示例6: 菜单遮罩效果示例', url: 'pages/Examples/MenuMaskDemo' },
    { title: '示例7: 菜单系统材质示例', url: 'pages/Examples/MenuSystemMaterial' },
  ]

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Menu高级功能示例')
          .fontSize(22)
          .fontColor(0xFFFFFF)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .height('40vp')
          .backgroundColor('#2ebd82')
        List({ space: '10vp' }) {
          ForEach(this.items, (item: ListCategories) => {
            ListItem() {
              Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
            }
            .width('90%')
            .height('40vp')
            .backgroundColor('#ff53ecd9')
            .borderRadius(10)
            .onClick(() => {
              router.pushUrl({ url: item.url })
            })
          })
        }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('80%')
      }.width('100%').height('100%')
    }
  }
}
