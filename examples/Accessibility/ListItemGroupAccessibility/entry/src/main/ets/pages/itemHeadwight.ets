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

import { TimeTable, ProjectsDataSource, TimeTableDataSource } from './ListDataSource';
import window from '@ohos.window';
import { common } from '@kit.AbilityKit';

@Extend(Button)
function ButtonStyle() {
  .width('40%')
  .height(40)
  .backgroundColor('#007aff')
  .fontColor('#FFFFFF')
  .borderRadius(10)
  .fontSize(16)
  .fontWeight(FontWeight.Medium)
  .stateEffect(true)
  .margin(5)
  .alignRules({
    center: { anchor: '__container__', align: VerticalAlign.Center },
    middle: { anchor: '__container__', align: HorizontalAlign.Center }
  })
}

@Entry
@Component
struct ListItemGroupExample {
  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE :
        window.Orientation.PORTRAIT)
    })
  }

  itemGroupArray: TimeTableDataSource = new TimeTableDataSource([]);

  aboutToAppear(): void {
    let timeTable: TimeTable[] = [
      {
        title: '星期一',
        projects: ['语文', '数学', '英语', '物理', '化学', '生物']
      },
      {
        title: '星期二',
        projects: ['物理', '化学', '生物', '历史', '地理', '政治']
      },
      {
        title: '星期三',
        projects: ['历史', '地理', '政治', '美术', '音乐', '体育']
      },
      {
        title: '星期四',
        projects: ['美术', '音乐', '体育', '物理', '化学', '生物']
      }
    ];
    this.itemGroupArray = new TimeTableDataSource(timeTable);
  }

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(10)
      .height(30)
      .enabled(false)
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + '节课')
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(5)
      .height(30)
      .enabled(false)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20 }) {
          LazyForEach(this.itemGroupArray, (item: TimeTable) => {
            ListItemGroup({ header: this.itemHead(item.title), footer: this.itemFoot(item.projects.length) }) {
              LazyForEach(new ProjectsDataSource(item.projects), (project: string) => {
                ListItem() {
                  Text(project)
                    .width('100%')
                    .height(30)
                    .fontSize(20)
                    .textAlign(TextAlign.Center)
                    .backgroundColor(0xFFFFFF)

                }
              }, (item: string) => item)
            }
            .divider({ strokeWidth: 1, color: Color.Blue }) // 每行之间的分界线
          })
        }
        .height('80%')
        .width('80%')
        .sticky(StickyStyle.Header | StickyStyle.Footer)
        .scrollBar(BarState.Off)
        .margin(20)


        Button("竖屏").onClick(() => {
          this.changeOrientation(false)
        }).ButtonStyle();
        Button("横屏").onClick(() => {
          this.changeOrientation(true)
        }).ButtonStyle();
      }.width('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
    }
  }
}