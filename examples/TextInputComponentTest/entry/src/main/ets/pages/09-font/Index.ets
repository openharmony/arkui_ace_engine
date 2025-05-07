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
    new TextList(1, '01-fontFeature', 'pages/09-font/01-fontFeature',),
    new TextList(2, '02-heightAdaptivePolicy', 'pages/09-font/02-heightAdaptivePolicy',),
    new TextList(3, '03-letterSpacing', 'pages/09-font/03-letterSpacing',),
    new TextList(4, '04-lineBreakStrategy', 'pages/09-font/04-lineBreakStrategy',),
    new TextList(5, '05-lineHeight', 'pages/09-font/05-lineHeight',),
    new TextList(6, '06-maxFontSize', 'pages/09-font/06-maxFontSize',),
    new TextList(7, '07-minFontSize', 'pages/09-font/07-minFontSize',),
    new TextList(8, '08-textIndent', 'pages/09-font/08-textIndent',),
    new TextList(9, '09-textOverflow', 'pages/09-font/09-textOverflow',),
    new TextList(10, '10-workBreak', 'pages/09-font/10-workBreak',),
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