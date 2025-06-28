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

interface Categories {
  title:string,
  url:string
}

@Entry
@Component
struct Index {
  private items: Categories[] = [
    { title: "示例1：弹出普通菜单", url: "pages/Examples/MenuItemDemo" },
    { title: "示例2：弹出自定义菜单", url: "pages/Examples/MenuBuilder" },
    { title: "示例3：长按弹出菜单", url: "pages/Examples/MenuLongPress" },
    { title: "示例4：右键弹出指向型菜单", url: "pages/Examples/MenuRightClick" },
    { title: "示例5：长按弹出菜单的截图预览样式", url: "pages/Examples/MenuImagePreview" },
    { title: "示例6：长按弹出菜单的自定义预览样式", url: "pages/Examples/MenuBuilderPreview" },
    { title: "示例7：设置状态变量弹出菜单", url: "pages/Examples/ContextMenuIsShown" },
    { title: "示例8：设置菜单和预览的动效", url: "pages/Examples/ContextMenuTransition" },
    { title: "示例9：设置symbol类型图标", url: "pages/Examples/MenuSymbolIcon" },
    { title: "示例10：设置一镜到底动效", url: "pages/Examples/MenuHoverScale" },
    { title: "示例11：菜单基本功能_0_bM内容/自定义尺寸", url: "pages/Examples/MenuTestLevel0_0" },
    { title: "示例12：菜单基本功能_1_bCM内容/自定义尺寸", url: "pages/Examples/MenuTestLevel0_1" },
    { title: "示例13：菜单基本功能_2_标题/subwindow", url: "pages/Examples/MenuTestLevel0_2" },
    { title: "示例14：菜单基本功能_3_位置", url: "pages/Examples/MenuTestLevel0_3" },
  ]

  build() {
    Column() {
      Text('菜单控制示例代码').fontSize(22)
      List({ space: '10vp' }) {
        ForEach(this.items, (item: Categories) => {
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
      }.alignListItem(ListItemAlign.Center).margin(({ top: '10vp' })).width('100%').height('70%')
    }.width('100%').height('100%')
  }
}