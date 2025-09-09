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
    new TextList(2, 'childrenMainSize', 'pages/List/childrenMainSize/ListItemGroupScenario'),
    new TextList(3, 'RepeatList1', 'pages/List/RepeatList/RepeatList1'),
    new TextList(4, 'AutoSort', 'pages/List/AutoSort/AutoSort'),
    new TextList(5, 'DeleteAndShift', 'pages/List/DeleteAndShift/DeleteAndShift'),
    new TextList(6, 'DragAndDropSorting', 'pages/List/DragAndDropSorting/DragAndDropSorting'),
    new TextList(7, 'FadingEdge', 'pages/List/FadingEdge/FadingEdge'),
    new TextList(8, 'LoopScrolling', 'pages/List/LoopScrolling/LoopScrolling'),
    new TextList(9, 'Sideslip', 'pages/List/Sideslip/Sideslip'),
    new TextList(10, 'MouseDragSlide', 'pages/List/MouseDragSlide'),
    new TextList(11, 'LayoutFromBottom', 'pages/List/LayoutFromBottom'),
    new TextList(12, 'CustomSlidingCurve', 'pages/List/CustomSlidingCurve'),
    new TextList(13, 'SlideHorizontallyOneSide', 'pages/List/SlideHorizontallyOneSide'),
    new TextList(14, 'FoldExpand', 'pages/List/FoldExpand'),
    new TextList(15, 'MultiSelectSliding', 'pages/List/MultiSelectSliding'),
    new TextList(16, '点击放大item', 'pages/List/DragAndDropSorting/ListItemGroup'),
    new TextList(17, 'OnWillStopDragging', 'pages/List/ListOnWillStopDragging/OnWillStopDragging'),
    new TextList(18, 'Table', 'pages/List/Table/TableDemo'),
    new TextList(19, 'Graduator', 'pages/List/Graduator/Graduator'),
    new TextList(20, 'simulateSwiper', 'pages/List/simulateSwiper'),
    new TextList(21, 'scrollToControlParent', 'pages/List/scrollToControlParent'),
    new TextList(22, 'dividerColor', 'pages/List/divider/dividerColor'),
    new TextList(23, 'dividerEndMargin', 'pages/List/divider/dividerEndMargin'),
    new TextList(24, 'dividerStartMargin', 'pages/List/divider/dividerStartMargin'),
    new TextList(25, 'dividerStrokeWidth', 'pages/List/divider/dividerStrokeWidth'),
    new TextList(26, 'friction', 'pages/List/friction/friction'),
    new TextList(27, 'lanesMaxLength', 'pages/List/Lanes/lanesMaxLength'),
    new TextList(28, 'lanesMinLength', 'pages/List/Lanes/lanesMinLength'),
    new TextList(29, 'dividerColor(ListItemGroup)', 'pages/List/ListItemGroup/dividerColor'),
    new TextList(30, 'dividerEndMargin(ListItemGroup)', 'pages/List/ListItemGroup/dividerEndMargin'),
    new TextList(31, 'dividerStartMargin(ListItemGroup)', 'pages/List/ListItemGroup/dividerStartMargin'),
    new TextList(32, 'dividerStrokeWidth(ListItemGroup)', 'pages/List/ListItemGroup/dividerStrokeWidth'),
    new TextList(33, 'listCAPILazy', 'pages/List/CAPI/ListCAPILazy'),
    new TextList(34, 'listCAPIGroup', 'pages/List/CAPI/ListCAPIGroup'),
    new TextList(35, 'dividerColor(ListItemGroupModifier)', 'pages/List/ListItemGroupModifier/dividerColor'),
    new TextList(36, 'dividerEndMargin(ListItemGroupModifier)', 'pages/List/ListItemGroupModifier/dividerEndMargin'),
    new TextList(37, 'dividerStartMargin(ListItemGroupModifier)', 'pages/List/ListItemGroupModifier/dividerStartMargin'),
    new TextList(38, 'dividerStrokeWidth(ListItemGroupModifier)', 'pages/List/ListItemGroupModifier/dividerStrokeWidth'),
    new TextList(39, 'dividerColor(ListModifier)', 'pages/List/ListModifier/dividerColor'),
    new TextList(40, 'dividerEndMargin(ListModifier)', 'pages/List/ListModifier/dividerEndMargin'),
    new TextList(41, 'dividerStartMargin(ListModifier)', 'pages/List/ListModifier/dividerStartMargin'),
    new TextList(42, 'dividerStrokeWidth(ListModifier)', 'pages/List/ListModifier/dividerStrokeWidth'),
    new TextList(43, 'friction(ListModifier)', 'pages/List/ListModifier/friction'),
    new TextList(44, 'lanesMaxLength(ListModifier)', 'pages/List/ListModifier/lanesMaxLength'),
    new TextList(45, 'lanesMinLength(ListModifier)', 'pages/List/ListModifier/lanesMinLength')
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