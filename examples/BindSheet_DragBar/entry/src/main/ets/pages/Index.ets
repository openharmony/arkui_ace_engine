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
export class TestListOption {
  title: string = ''
  url: string= ''
  key: string= ''
}
const testList:TestListOption[] = [
  { title: '无标题', url: 'pages/noneTitle', key:'noneTitle' },
  { title: 'sheetTitleOptions', url: 'pages/sheetTitleOptions', key:'sheetTitleOptions' },
  { title: 'CustomBuilder', url: 'pages/CustomBuilder', key:'CustomBuilder' },
]

@Entry
@Component
struct Index {
  scroll: Scroller = new Scroller()

  build() {
    Column() {
      Scroll(this.scroll) {
        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
          ForEach(testList, (item:TestListOption) => {
            Button(item.title)
              .width(300)
              .height(50)
              .margin(10)
              .padding({ top: 5, bottom: 5 })
              .onClick(() => {
                this.getUIContext().getRouter().pushUrl({ url: item.url }, router.RouterMode.Single)
              })
          }, (item:TestListOption) => item.title)
        }
        .width('100%')
      }
    }
  }
}