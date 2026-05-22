/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct bindMenuBuilderNoMenuExample {

  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('Test menu item 1')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 2')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 3')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 4')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 5')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 6')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 7')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 8')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 9')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 10')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 11')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 12')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 13')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 14')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 15')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 16')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 17')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 18')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 19')
        .fontSize(20)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 20')
        .fontSize(20)
        .textAlign(TextAlign.Center)
    }
  }

  build() {
    Column() {
      Text('click for Menu').fontSize(25)
    }
    .bindMenu(this.MenuBuilder)
    .width('60%')
    .height('100%')
  }
}