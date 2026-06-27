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
import { State } from '@ohos.arkui.stateManagement';
import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  $r,
  Text,
  Badge,
  ForEach,
  NavDestination,
  TextAlign,
  BadgePosition,
  BadgeParamWithNumber
} from '@kit.ArkUI';

@Entry
@Component
export struct TaggedListItems {
  @State arr: int[] = [0, 1, 2, 3];
  private context: common.UIAbilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext;

  build(): void {
    NavDestination() {
      Column() {
        ComponentCard({ title: $r('app.string.TaggedListItems_titleExample') }) {
          List() {
            ForEach(this.arr, (item: int) => {
              ListItem() {
                // Badge component implements the function of adding a mark in the upper right corner of the message
                Badge({
                  count: 1,
                  position: BadgePosition.RightTop,
                  style: { badgeSize: 16, badgeColor: '#FA2A2D' }
                } as BadgeParamWithNumber) {
                  // Please configure a resource with name 'list_text2' in resources\base\element\string.json file,
                  // with a non-empty string value
                  Text(this.context.resourceManager.getStringByNameSync('list_text2') + item)
                    .width('95%')
                    .height(50)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .borderRadius(10)
                    .backgroundColor('#FFF1F3F5')
                }
              }
              .margin({ top: 12 })
            }, (item: int) => item.toString())
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.TaggedListItems_title'))
  }
}
