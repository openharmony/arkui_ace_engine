/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
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
struct struct_03_menuHandleSelect_index {
  scroll: Scroller = new Scroller()
  @State arr: TextList[] = [
    new TextList(2, '02-selectionValid', 'pages/03-menuHandleSelect/02-selectionValid',),
    new TextList(3, '03-caretColor', 'pages/03-menuHandleSelect/03-caretColor',),
    new TextList(4, '04-caretStyle', 'pages/03-menuHandleSelect/04-caretStyle',),
    new TextList(5, '05-caretPosition', 'pages/03-menuHandleSelect/05-caretPosition',),
    new TextList(7, '07-selectAll', 'pages/03-menuHandleSelect/07-selectAll',),
    new TextList(8, '08-selectAllAfterDraws', 'pages/03-menuHandleSelect/08-selectAllAfterDraws',),
    new TextList(9, '09-swiperMoveNextHideMenu', 'pages/03-menuHandleSelect/09-swiperMoveNextHideMenu',),
    new TextList(10, '10-moveTextToTarContentNeedHideHandle',
      'pages/03-menuHandleSelect/10-moveTextToTarContentNeedHideHandle',),
    new TextList(11, '11-changeLandscapePortraitHideMenusKeepSelection',
      'pages/03-menuHandleSelect/11-changeLandscapePortraitHideMenusKeepSelection',)
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