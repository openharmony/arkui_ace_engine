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

class TextList {
  public id: number;
  public text: string;
  public url: string;

  constructor(id: number, text: string, url: string) {
    this.id = id;
    this.text = text;
    this.url = url;
  }
}

@Entry
@Component
struct IndexPage {
  scroll: Scroller = new Scroller()
  @State arr: TextList[] = [
    new TextList(1, 'Back', 'pages/Index'),
    new TextList(2, 'CustomSnap', 'pages/Scroll/CustomSnap'),
    new TextList(3, 'InfiniteScrolling', 'pages/Scroll/InfiniteScrolling'),
    new TextList(4, 'NestedScrollBar', 'pages/Scroll/NestedScrollBar'),
    new TextList(5, 'RecycleView', 'pages/Scroll/RecycleView/Index'),
    new TextList(6, 'ScrollNode', 'pages/Scroll/ScrollNode'),
    new TextList(7, 'ScrollWithLayoutWeight', 'pages/Scroll/ScrollWithLayoutWeight'),
    new TextList(8, 'FreeScroll', 'pages/Scroll/FreeScroll'),
    new TextList(9, 'OnDidScrollAndTranslate', 'pages/Scroll/OnDidScrollAndTranslate'),
    new TextList(10, 'ParentDriveChild', 'pages/Scroll/ParentDriveChild'),
    new TextList(11, 'NestedScrollTypeOne', 'pages/Scroll/NestedScrollTypeOne'),
    new TextList(12, 'NestedScrollTypeTwo', 'pages/Scroll/NestedScrollTypeTwo'),
    new TextList(13, 'friction', 'pages/Scroll/friction'),
    new TextList(14, 'initialOffsetXOffset', 'pages/Scroll/initialOffsetXOffset'),
    new TextList(15, 'initialOffsetYOffset', 'pages/Scroll/initialOffsetYOffset'),
    new TextList(16, 'scrollSnap', 'pages/Scroll/scrollSnap')
  ]
  @State fontSize: Resource | undefined = undefined
  build() {
    Column() {
      Scroll(this.scroll) {
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
          ForEach(this.arr, (item: TextList) => {
            Button(item.text)
              .width(300)
              .height(50)
              .margin(10)
              .padding({ top: 5, bottom: 5 })
              .onClick(() => {
                router.pushUrl({ url: item.url })
              })
          }, (item: TextList) => JSON.stringify(item.id))
        }
        .width('100%')
      }
      .scrollBar(BarState.Off)
    }
  }
}