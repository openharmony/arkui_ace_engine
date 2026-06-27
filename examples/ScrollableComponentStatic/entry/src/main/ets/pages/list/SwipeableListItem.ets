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

import { ComponentCard } from '../../common/Card';
import {
  Entry,
  Component,
  Builder,
  Column,
  List,
  ListItem,
  Text,
  Button,
  Image,
  ForEach,
  NavDestination,
  TextAlign,
  ButtonType
} from '@kit.ArkUI';
import { State } from '@ohos.arkui.stateManagement';
import { $r } from '@kit.ArkUI';

@Entry
@Component
export struct SwipeListItem {
  private index: int = 0;
  @State arr: int[] = [0, 1, 2, 3];

  @Builder
  itemEnd(index: int): void {
    // Build the trailing swipe-out component
    Button({ type: ButtonType.Circle }) {
      Image($r('sys.media.ohos_ic_bottomsheet_close'))
        .width(40)
        .height(40)
    }
    .backgroundColor('#FFE1E2E3')
    .onClick(() => {
      // this.arr is the list data source, which can be constructed according to the actual scenario.
      // After clicking, delete the specified data item from the data source.
      this.arr.splice(index, 1);
    })
  }

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.SwipeListItem_titleExample') }) {
          List({ space: 12 }) {
            ForEach(this.arr, (item: int) => {
              // When building List, use ForEach to cyclically render ListItem based on data source.
              ListItem() {
                Text('Message ' + item)
                  .width('100%')
                  .height(50)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor('#FFF1F3F5')
              }.swipeAction({
                end: {
                  // index is the index value of this ListItem in the List.
                  builder: () => {
                    this.index = this.arr.indexOf(item);
                    this.itemEnd(this.index);
                  },
                }
              }) // Set swipe action property.
            }, (item: int) => item.toString())
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.SwipeListItem_title'))
  }
}
