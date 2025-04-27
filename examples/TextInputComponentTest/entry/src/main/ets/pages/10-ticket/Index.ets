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
struct struct_09_font_index {
  scroll: Scroller = new Scroller()
  @State arr: TextList[] = [
    new TextList(1, '01-showUnderline', 'pages/10-ticket/01-showUnderline',),
    new TextList(2, '02-textAreaHandleWithEllipsis ', 'pages/10-ticket/02-textAreaHandleWithEllipsis',),
    new TextList(3, '03-cancelButton', 'pages/10-ticket/03-cancelButton',),
    new TextList(4, '04-textInputUnderline', 'pages/10-ticket/04-textInputUnderline',),
    new TextList(5, '05-textMarquee', 'pages/10-ticket/05-textMarquee',),
    new TextList(6, '06-textInput', 'pages/10-ticket/06-textInput',),
    new TextList(7, '07-textInputCancelWithFocus', 'pages/10-ticket/07-textInputCancelWithFocus',),
    new TextList(8, '08-editorMenuOptions', 'pages/10-ticket/08-editorMenuOptions',),
    new TextList(9, '09-hyperlink', 'pages/10-ticket/09-hyperlink',),
    new TextList(10, '10-textInputMaxFontSizeOverLineHeight', 'pages/10-ticket/10-textInputMaxFontSizeOverLineHeight',),
    new TextList(11, '11-canPasteImages', 'pages/10-ticket/11-canPasteImages',),
    new TextList(12, '12-allSelectTabsChange', 'pages/10-ticket/12-allSelectTabsChange',),
    new TextList(13, '13-spanGetStyles', 'pages/10-ticket/13-spanGetStyles',),
    new TextList(14, '14-navigation', 'pages/10-ticket/14-navigation',),
    new TextList(15, '15-navigationSearchIndex', 'pages/10-ticket/15-navigationSearchIndex',),
    new TextList(16, '16-navigationIndexImmersive', 'pages/10-ticket/16-navigationIndexImmersive',),
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