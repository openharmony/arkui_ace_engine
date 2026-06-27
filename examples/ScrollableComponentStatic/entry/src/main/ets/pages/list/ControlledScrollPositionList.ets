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
import common from '@ohos.app.ability.common';

import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  Text,
  Button,
  Image,
  Stack,
  ForEach,
  Scroller,
  NavDestination,
  Alignment,
  TextAlign
} from '@kit.ArkUI';
import { $r } from '@kit.ArkUI';

@Entry
@Component
export struct ControlledScrollPositionList {
  private listScroller: Scroller = new Scroller();
  private arr: int[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.ControlledScrollPositionList_titleExample') }) {
          Stack({ alignContent: Alignment.Bottom }) {
            // Use listScroller to initialize the scroller parameter of the List component, completing the binding
            // of listScroller with the list.
            List({ space: 20, scroller: this.listScroller }) {
              ForEach(this.arr, (item: int) => {
                ListItem() {
                  // Please configure a resource with name 'list_text1' in resources\base\element\string.json file,
                  // with a non-empty string value
                  Text(this.context.resourceManager.getStringByNameSync('list_text1') + item)
                    .width('100%')
                    .height(100)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .borderRadius(10)
                    .backgroundColor('#FFF1F3F5')
                }
              }, (item: int) => item.toString())
            }

            Button() {
              Image($r('sys.media.ohos_ic_public_arrow_up')).width(40).height(40)
            }
            .backgroundColor('#FFE0E2E4')
            .position({ x: '80%', y: '90%' })
            .onClick(() => {
              // When clicking the button, specify the jump position and return to the top of the list
              this.listScroller.scrollToIndex(0);
            })
          }
          .height('90%')
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.ControlledScrollPositionList_title'))
  }
}
