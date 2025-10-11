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

import { common, ConfigurationConstant } from '@kit.AbilityKit';

// xxx.ets
@Entry
@Component
struct ListItemGroupExample {
  private timeTable: TimeTable[] = [
    {
      title: '星期一',
      projects: ['语文', '数学', '英语']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期一',
      projects: ['数学', '英语', '语文']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期六',
      projects: ['阅读', '写作', '讨论']
    },
    {
      title: '星期日',
      projects: ['休息', '娱乐', '自由活动']
    },
    {
      title: '星期一',
      projects: ['数学', '英语', '语文']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期六',
      projects: ['阅读', '写作', '讨论']
    },
    {
      title: '星期日',
      projects: ['休息', '娱乐', '自由活动']
    },
    {
      title: '星期一',
      projects: ['数学', '英语', '语文']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期六',
      projects: ['阅读', '写作', '讨论']
    },
    {
      title: '星期日',
      projects: ['休息', '娱乐', '自由活动']
    },
    {
      title: '星期一',
      projects: ['数学', '英语', '语文']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期六',
      projects: ['阅读', '写作', '讨论']
    },
    {
      title: '星期日',
      projects: ['休息', '娱乐', '自由活动']
    }
  ]

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(10)
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + '节课')
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(5)
  }

  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State changeIndex: number = 0;
  @State changeList: (Color | number | string | undefined | null)[] = [
    Color.Blue, 0xFFFF00FF, 'rgb(255, 100, 255)', '#FFFF00FF', undefined, null
  ];

  build() {
    Column() {

      Button('深浅色')
        .onClick(() => {
          if (this.isDark) {
            this.isDark = false;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          } else {
            this.isDark = true;
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          }
        })
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++;
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      List({ space: 20 }) {
        ForEach(this.timeTable, (item: TimeTable) => {
          ListItemGroup({ header: this.itemHead(item.title), footer: this.itemFoot(item.projects.length) }) {
            ForEach(item.projects, (project: string) => {
              ListItem() {
                Text(project)
                  .width('100%')
                  .height(100)
                  .fontSize(20)
                  .textAlign(TextAlign.Center)
                  .backgroundColor('#87F787')
              }.backgroundColor('#87F787')
            }, (item: string) => item)
          }
        })
      }
      .divider({
        strokeWidth: 200
      }) // 每行之间的分界线
      .width('90%')
      .sticky(StickyStyle.Header | StickyStyle.Footer)
      .scrollBar(BarState.On) // 滚动条常驻显示
      .scrollBarColor(this.changeList[this.changeIndex])
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}

interface TimeTable {
  title: string;
  projects: string[];
}
