'use static'

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

import {
  Entry,
  Component,
  Builder,
  LengthMetrics,
  Column,
  List,
  ListItem,
  Text,
  ForEach,
  Scroller,
  NavDestination,
  ResourceStr,
  EdgeEffect,
  ScrollAlign,
  Color,
  ShadowOptions
} from '@kit.ArkUI';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';

export class News {
  public id: string;
  public title: ResourceStr;
  public content: ResourceStr;
  public type: string;

  constructor(id: string, title: ResourceStr, content: ResourceStr, type: string) {
    this.id = id;
    this.title = title;
    this.content = content;
    this.type = type;
  }
}
const FRICTION_SCALE: double = 4.2;
const DEFAULT_FRICTION: float = 1;

@Entry
@Component
export struct SupportSlidingHand {
  @State newsData: Array<News> = [
    // The value of app.string.new_title in resource file is 'News Title'
    // The value of app.string.new_short in resource file is 'This is the first short news item with
    // less content, quickly swipe to switch'
    new News('1', $r('app.string.new_title'), $r('app.string.new_short'), 'short'),
    new News('2', $r('app.string.new_title'), $r('app.string.new_short'), 'short'),
    // The value of app.string.new_long in resource file is 'This is the second long news item with
    // more content, you can freely swipe to view the complete content.'
    new News('3', $r('app.string.new_title'), $r('app.string.new_long'), 'long'),
    new News('4', $r('app.string.new_title'), $r('app.string.new_short'), 'short'),
    new News('5', $r('app.string.new_title'), $r('app.string.new_long'), 'long'),
  ];
  // Index of the currently displayed news
  @State currentIndex: int = 0;
  private scrollerForList: Scroller = new Scroller();
  @State listHeight: int = 500;

  // Determine whether the current news is short news
  IsShortNews(currentIndex: int): boolean {
    return this.newsData[currentIndex].type === 'short'
  }

  build(): void {
    NavDestination() {
      Column() {
        // Top navigation bar
        this.topBar()
        // News list
        List({ scroller: this.scrollerForList, space: 10 }) {
          ForEach(this.newsData, (item: News, index) => {
            ListItem() {
              Column() {
                Text(item.title)
                  .fontSize(18)
                  .fontColor(Color.Black)
                  .fontWeight(index === this.currentIndex ? 700 : 400)
                  .backgroundColor(index === this.currentIndex ? '#FF9800' : '#FFFFFF')
                  .padding({ top: 10, bottom: 5 })

                Text(item.content)
                  .fontSize(14)
                  .fontColor('#666666')
              }
              .width('100%')
              .height(item.type === 'short' ? '70%' : '200%')
              .backgroundColor(index === this.currentIndex ? '#FFFFFF' : '#F5F5F5')
              .borderRadius(8)
              .shadow(index === this.currentIndex ? { fill: true, color: '#9E9E9E', radius: 5 } as ShadowOptions :
                { radius: 5, fill: false } as ShadowOptions)
            }
          }, (item: News) => item.id)
        }
        .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true })
        .width('100%')
        .height('80%')
        .onScrollIndex((startIndex: int) => {
          this.currentIndex = startIndex
        })
        .id('scrollToIndex')
        // Implementation reference
        .onWillStopDragging((velocity: double) => {
          if (velocity < 0) {
            // Swipe down handling
          } else {
            // Swipe up handling
          }
          // Short news handling
          if (this.IsShortNews(this.currentIndex)) {
            if (velocity > 10) {
              this.scrollerForList.scrollToIndex(this.currentIndex, true, ScrollAlign.START)
            } else if (velocity < -10) {
              this.scrollerForList.scrollToIndex(this.currentIndex + 1, true, ScrollAlign.START)
            }
            return;
          }
          // Long news handling
          let rect = this.scrollerForList.getItemRect(this.currentIndex);
          if (velocity < -30) {
            if (rect) {
              // Remaining display range of the current node within the page
              let leftRect = rect.y + rect.height;
              // Target position
              let mainPosition = -velocity * DEFAULT_FRICTION / FRICTION_SCALE;
              if (leftRect + mainPosition > 0.75 * this.listHeight) {
                this.scrollerForList.scrollToIndex(this.currentIndex + 1, true, ScrollAlign.START);
                return;
              } else if (leftRect + mainPosition < 0.25 * this.listHeight) {
                this.scrollerForList.scrollToIndex(this.currentIndex, true, ScrollAlign.END,
                  { extraOffset: LengthMetrics.vp(this.listHeight * 0.3) })
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
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
      .height(this.listHeight)
      .backgroundColor(Color.White)
      .padding({ top: 20 })
    }.backgroundColor('#f1f2f3')
    .title($r('app.string.Support_Sliding_Hand_Event'))

  }

  @Builder
  topBar(): void {
    Column() {
      Column() {
        // Please replace $r('app.string.Today_Hot_News') with the actual resource file.
        // In this example, the value of this resource file is "Today's Hot News"
        Text($r('app.string.Today_Hot_News'))
          .fontSize(20)
          .fontColor(Color.Black)
          .fontWeight(700)
          .margin({ bottom: 10 })
      }
    }
  }
}
