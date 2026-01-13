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

 /*
  * Description: 通过OnItemDragStart等事件实现了ListItem在两个List组件间的拖拽效果
  * Writer: dailihuan
  */

import { ComponentContent } from '@kit.ArkUI'; //通过listitemgroup的footer实现特殊居中项，能避开lanes(2)的约束影响

interface Item {
  id: number,
  type: string,
  text: string
}

class FootBuilderParams {
  item: Item;

  constructor(item: Item) {
    this.item = item;
  }
}

@Builder
function ItemFoot(params: FootBuilderParams) {
  Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
    Text(params.item.text)
      .fontSize(18)
      .fontColor('#FFFFFF')
      .padding(20)
      .backgroundColor('#FF007DFF')
      .borderRadius(12)
      .onClick(() => {
        console.info(params.item.text)
      })
  }
}

interface TimeTable {
  title: string;
  projects: string[];
}

@Preview
@Entry
@Component
struct SpecialListLayout {
  @State dataList: Item[] = [// 模拟数据
    { id: 1, type: 'normal', text: '普通项1' },
    { id: 2, type: 'normal', text: '普通项2' },
    { id: 3, type: 'special', text: '独立居中项' }, // 特殊居中项
    { id: 4, type: 'normal', text: '普通项3' },
    { id: 5, type: 'normal', text: '普通项4' }
  ]
  footer?: ComponentContent<FootBuilderParams> = undefined

  aboutToAppear(): void {

  }

  build() {
    List({ space: 10 }) {
      // 普通双列项
      ForEach(this.dataList, (item: Item) => {
        // 只渲染普通项（过滤特殊项）
        if (item.type === 'normal') {
          ListItem() {
            Text(item.text)
              .fontSize(16)
              .backgroundColor('#F0F0F0')
              .padding(10)
              .borderRadius(8)
          }
          .width('100%') // 关键：让普通项参与双列布局
        } else {
          // 特殊居中项（独立处理）
          ListItemGroup({ footer: ItemFoot(new FootBuilderParams(item)) }) {
            ListItem() {
            }
          }
        }
      })
    }
    .lanes(2) // 全局双列布局
    .alignListItem(ListItemAlign.Start)
    .backgroundColor('#FFFFFF')
  }
}
