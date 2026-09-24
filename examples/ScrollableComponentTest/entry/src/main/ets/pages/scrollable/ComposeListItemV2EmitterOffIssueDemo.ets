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

import { ComposeListItemV2, ContentItemV2, OperateItemV2 } from '@kit.ArkUI';
import { emitter } from '@kit.BasicServicesKit';

const EVENT_IS_WRAP_TEXT_CHANGE = 10001;
const EVENT_PARENT_FRONT_COLOR_CHANGE = 10004;

/**
 * Issue: ComposeListItemV2 aboutToDisappear called emitter.off(eventId) without
 * a callback, removing ALL listeners for that event across all instances.
 * Destroying one instance caused surviving instances to lose their emitter
 * listeners (frontColor, isWrapText, canFocus, canHover).
 *
 * Must use @ComponentV2 so that conditional removal (if) properly triggers
 * the V2 component's aboutToDisappear lifecycle.
 */
@Entry
@ComponentV2
struct ComposeListItemV2EmitterOffIssueDemo {
  @Local showItemA: boolean = true;
  @Local statusText: string = 'Two ComposeListItemV2 instances created.';

  build() {
    Column({ space: 12 }) {
      Text('ComposeListItemV2 emitter.off Issue Demo')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')

      if (this.showItemA) {
        ComposeListItemV2({
          contentItemV2: new ContentItemV2({
            primaryText: 'Item A (destroyable)',
            secondaryText: 'Destroy A, then emit frontColor — B should still change',
          }),
          operateItemV2: new OperateItemV2({}),
        })
      }

      ComposeListItemV2({
        contentItemV2: new ContentItemV2({
          primaryText: 'Item B (survivor)',
          secondaryText: 'After A is destroyed, does B still respond?',
        }),
        operateItemV2: new OperateItemV2({}),
      })

      Text(this.statusText)
        .fontSize(12)
        .fontColor('#333333')
        .width('100%')
        .layoutWeight(1)
        .backgroundColor('#F5F5F5')
        .padding(8)
        .borderRadius(8)

      Row({ space: 8 }) {
        Button('Destroy Item A')
          .enabled(this.showItemA)
          .layoutWeight(1)
          .onClick(() => {
            this.showItemA = false;
            this.statusText += '\nItem A destroyed.';
          })
        Button('Rebuild Item A')
          .enabled(!this.showItemA)
          .layoutWeight(1)
          .onClick(() => {
            this.showItemA = true;
            this.statusText += '\nItem A rebuilt.';
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Button('emit frontColor=red')
          .layoutWeight(1)
          .fontSize(11)
          .onClick(() => {
            emitter.emit(
              { eventId: EVENT_PARENT_FRONT_COLOR_CHANGE },
              { data: { frontColor: '#FFFF0000' } }
            );
            this.statusText += '\nemit frontColor=red';
          })
        Button('emit isWrapText=true')
          .layoutWeight(1)
          .fontSize(11)
          .onClick(() => {
            emitter.emit(
              { eventId: EVENT_IS_WRAP_TEXT_CHANGE },
              { data: { isWrapText: true } }
            );
            this.statusText += '\nemit isWrapText=true';
          })
      }
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .backgroundColor('#F2F4F7')
  }
}
