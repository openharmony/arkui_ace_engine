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

import { LengthMetrics } from '@kit.ArkUI';

class News {
  public id: string;
  public title: string;
  public content: string;
  public type: string;

  constructor(id: string, title: string, content: string, type: string) {
    this.id = id;
    this.title = title;
    this.content = content;
    this.type = type;
  }
}

const FRICTION_SCALE: number = 4.2
const DEFAULT_FRICTION: number = 1

@Entry
@Component
struct NewsListPage {
  @State newsData: Array<News> = [
    new News('1', '新闻标题1', '这是第一条短新闻，内容较少，快速滑动切换', 'short'),
    new News('2', '新闻标题2', '这是第一条短新闻，内容较少，快速滑动切换', 'short'),
    new News('3', '新闻标题3', '这是第二条长新闻，内容较多，可以自由滑动查看完整内容。', 'long'),
    new News('4', '新闻标题4', '这是第三条短新闻，内容较少，快速滑动切换', 'short'),
    new News('5', '新闻标题5', '这是第四条长新闻，内容较多，可以自由滑动查看完整内容。', 'long')
  ];
  @State currentIndex: number = 0; // 当前显示的新闻索引
  private scrollerForList: Scroller = new Scroller();
  @State listHeight: number = 500;

  // 判断当前新闻是否为短新闻
  isShortNews(currentIndex: number): boolean {
    return this.newsData[currentIndex].type === 'short';
  }

  build() {
    Column({ space: 10 }) {
      // 顶部导航栏
      this.topBar()
      // 新闻列表
      List({
        scroller: this.scrollerForList,
        space: 10,
        initialIndex: 0
      }) {
        ForEach(this.newsData, (item: News, index) => {
          ListItem() {
            Column({ space: 10 }) {
              Text(item.title)
                .fontSize(18)
                .fontColor('#000000')
                .fontWeight(index === this.currentIndex ? 700 : 400)
                .backgroundColor(index === this.currentIndex ? '#FF9800' : '#FFFFFF')
                .padding({ top: 10, bottom: 5 })

              Text(item.content)
                .fontSize(14)
                .fontColor('#666666')
            }
            .width('100%')
            .height(item.type == 'short' ? '70%' : '200%')
            .backgroundColor(index === this.currentIndex ? '#FFFFFF' : '#F5F5F5')
            .borderRadius(8)
            .shadow(index === this.currentIndex ? { fill: true, color: '#9E9E9E', radius: 5 } :
              { radius: 5, fill: false })
          }
        }, (item: News) => item.id)
      }
      .listDirection(Axis.Vertical)
      .alignListItem(ListItemAlign.Start)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true })
      .width('100%')
      .height('80%')
      .onWillStopDragging((velocity: number) => {
        // 短新闻处理
        if (this.isShortNews(this.currentIndex)) {
          if (velocity > 10) {
            this.scrollerForList.scrollToIndex(this.currentIndex, true, ScrollAlign.START);
          } else if (velocity < -10) {
            this.scrollerForList.scrollToIndex(this.currentIndex + 1, true, ScrollAlign.START);
          }
          return;
        }

        // 长新闻处理
        let rect = this.scrollerForList.getItemRect(this.currentIndex);
        if (velocity < -30) {
          if (rect) {
            // 当前节点在页面内的剩余显示范围
            let leftRect = rect.y + rect.height;
            // 终点位置
            let mainPosition = -velocity * DEFAULT_FRICTION / FRICTION_SCALE;
            if (leftRect + mainPosition > 0.75 * this.listHeight) {
              this.scrollerForList.scrollToIndex(this.currentIndex + 1, true, ScrollAlign.START);
              return;
            } else if (leftRect + mainPosition < 0.25 * this.listHeight) {
              this.scrollerForList.scrollToIndex(this.currentIndex, true, ScrollAlign.END,
                { extraOffset: LengthMetrics.vp(this.listHeight * 0.3) });
              return;
            }
          }
        } else if (velocity > 30) {
          let leftRect = rect?.y + rect?.height;
          let mainPosition = velocity * DEFAULT_FRICTION / FRICTION_SCALE;
          if (leftRect + mainPosition > 0.75 * this.listHeight) {
            this.scrollerForList.scrollToIndex(this.currentIndex, true, ScrollAlign.START);
            return;
          }
        }
      })
      .onScrollIndex((startIndex: number) => {
        this.currentIndex = startIndex;
      })
    }
    .width('100%')
    .height(this.listHeight)
    .backgroundColor('#FFFFFF')
    .padding({ top: 20 })
  }

  // 顶部导航栏
  @Builder
  topBar() {
    Column() {
      Text('今日热点新闻')
        .fontSize(20)
        .fontColor('#000000')
        .fontWeight(700)
        .margin({ bottom: 10 })
    }
  }
}