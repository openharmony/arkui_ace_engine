/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'use static';
import { FrameNode, NodeContent, NodeController, typeNode } from '@ohos.arkui.node';
import {
  Builder,
  Button,
  ClickEvent,
  Color,
  Column,
  ColumnOptions,
  Component,
  ContentSlot,
  CustomBuilder,
  Entry,
  FontWeight,
  ForEach,
  Margin,
  NodeContainer,
  ProgressStyleOptions,
  ProgressType,
  Text,
  TextAlign,
  UIContext,
  WrappedBuilder
} from '@ohos.arkui.component';
import { TimeHelper } from './TimeHelper'
import { ArrayEntity } from './ArrayEntity'

@Entry
@Component
struct ProgressFrameNodeSample {
  timeHelper: TimeHelper = new TimeHelper('ProgressFrameNodeSample');
  private nodeContent: NodeContent = new NodeContent();

  aboutToAppear(): void {
    let uiContext = this.getUIContext();
    for (let index = 0; index < 100; index++) {
      this.timeHelper.printNodeTime(true);
      let progress = typeNode.createProgressNode(uiContext);
      this.timeHelper.printNodeTime(false);

      this.timeHelper.printAttrTime(true);
      progress.initialize({ value: 30, type: ProgressType.ScaleRing })
        .style({ strokeWidth: 20, scaleCount: 20, scaleWidth: 5 } as ProgressStyleOptions);
      this.timeHelper.printAttrTime(false);
      this.nodeContent.addFrameNode(progress);
    }
  }

  build() {
    Column() {
      Text('ProgressFrameNodeSample')
        .padding('15vp')
        .width('100%')
        .fontSize('25fp')
        .textAlign(TextAlign.Center)
        .margin(5)
      ContentSlot(this.nodeContent)
    }
  }
}
