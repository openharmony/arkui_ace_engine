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

export class TextList {
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
    new TextList(2, 'BasicScrollSample', 'pages/Scroll/BasicScrollSample'),
    new TextList(3, 'CustomSnap', 'pages/Scroll/CustomSnap'),
    new TextList(4, 'InfiniteScrolling', 'pages/Scroll/InfiniteScrolling'),
    new TextList(5, 'NestedScrollBar', 'pages/Scroll/NestedScrollBar'),
    new TextList(6, 'RecycleView', 'pages/Scroll/RecycleView/Index'),
    new TextList(7, 'ScrollNode', 'pages/Scroll/ScrollNode'),
    new TextList(8, 'ScrollWithLayoutWeight', 'pages/Scroll/ScrollWithLayoutWeight'),
    new TextList(9, 'FreeScroll', 'pages/Scroll/FreeScroll'),
    new TextList(10, 'OnDidScrollAndTranslate', 'pages/Scroll/OnDidScrollAndTranslate'),
    new TextList(11, 'ParentDriveChild', 'pages/Scroll/ParentDriveChild'),
    new TextList(12, 'NestedScrollTypeOne', 'pages/Scroll/NestedScrollTypeOne'),
    new TextList(13, 'NestedScrollTypeTwo', 'pages/Scroll/NestedScrollTypeTwo'),
    new TextList(14, 'friction', 'pages/Scroll/friction'),
    new TextList(15, 'initialOffsetXOffset', 'pages/Scroll/initialOffsetXOffset'),
    new TextList(16, 'initialOffsetYOffset', 'pages/Scroll/initialOffsetYOffset'),
    new TextList(17, 'scrollSnap', 'pages/Scroll/scrollSnap'),
    new TextList(18, 'friction(ScrollModifier)', 'pages/Scroll/ScrollModifier/friction'),
    new TextList(19, 'initialOffsetXOffset(ScrollModifier)', 'pages/Scroll/ScrollModifier/initialOffsetXOffset'),
    new TextList(20, 'initialOffsetYOffset(ScrollModifier)', 'pages/Scroll/ScrollModifier/initialOffsetYOffset'),
    new TextList(21, 'scrollSnap(ScrollModifier)', 'pages/Scroll/ScrollModifier/scrollSnap'),
    new TextList(22, 'ScrollIndex', 'pages/Scroll/ScrollIndex'),
    new TextList(23, 'ScrollModifierIndex', 'pages/Scroll/ScrollModifier/ScrollModifierIndex'),
    new TextList(24, 'scrollBarColor', 'pages/Scroll/scrollBarColor'),
    new TextList(25, 'scrollBarColor(ScrollModifier)', 'pages/Scroll/ScrollModifier/scrollBarColor'),
    new TextList(26, 'ScrollableInfiniteScroll', 'pages/Scroll/CAPI/ScrollableInfiniteScroll'),
    new TextList(27, 'LayoutConstraints', 'pages/Scroll/LayoutConstraints/LayoutConstraints_MainPage'),
    new TextList(28, 'BindControllerDeclare', 'pages/Scroll/bindController/ScrollDeclare'),
    new TextList(29, 'BindControllerCommand', 'pages/Scroll/bindController/ScrollCommand'),
    new TextList(30, 'ScrollerGetFrameNodeScenes', 'pages/Scroll/bindController/ScrollFrameNodeScenes'),
    new TextList(31, 'ScrollEventReport', 'pages/Scroll/ScrollEventReport'),
    new TextList(32, 'ScrollEventReportNestedScroll', 'pages/Scroll/ScrollEventReportNestedScroll'),
    new TextList(33, 'HorizontalGallerySample', 'pages/Scroll/HorizontalGallerySample'),
    new TextList(34, 'PagingCardsSample', 'pages/Scroll/PagingCardsSample'),
    new TextList(35, 'EdgeEffectSample', 'pages/Scroll/EdgeEffectSample'),
    new TextList(36, 'ComplexDashboardScrollSample', 'pages/Scroll/ComplexDashboardScrollSample'),
    new TextList(37, 'ComplexControlMatrixScrollSample', 'pages/Scroll/ComplexControlMatrixScrollSample'),
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
                this.getUIContext().getRouter().pushUrl({ url: item.url })
              })
          }, (item: TextList) => JSON.stringify(item.id))
        }
        .width('100%')
      }
      .scrollBar(BarState.Off)
    }
  }
}
