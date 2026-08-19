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

// Entry page for the WaterFlow clipContent demos. Each group pairs a clipContent case with the
// matching baseline (no clipContent) so the clip extension area can be compared directly.
import { FlowItemClipContentTest } from './flowitem/ClipContent'
import { FlowItemNoClipContentTest } from './flowitem/NoClipContent'
import { FlowItemFrameNodeClipContentTest } from './flowitem/FrameNodeClipContent'
import { FlowItemFrameNodeNoClipContentTest } from './flowitem/FrameNodeNoClipContent'
import { LazyColumnClipContentTest } from './lazycolumn/ClipContent'
import { LazyColumnNoClipContentTest } from './lazycolumn/NoClipContent'
import { LazyVGridClipContentTest } from './lazyvgrid/ClipContent'
import { LazyVGridNoClipContentTest } from './lazyvgrid/NoClipContent'
import { LazyVWaterFlowClipContentTest } from './lazyvwaterflow/ClipContent'
import { LazyVWaterFlowNoClipContentTest } from './lazyvwaterflow/NoClipContent'

@Entry
@ComponentV2
struct ClipContentMainPage {
  @Provider('navPathStack') navPathStack: NavPathStack = new NavPathStack();

  @Builder
  pageMap(name: string) {
    if (name === 'FlowItemClipContentTest') {
      FlowItemClipContentTest();
    } else if (name === 'FlowItemNoClipContentTest') {
      FlowItemNoClipContentTest();
    } else if (name === 'FlowItemFrameNodeClipContentTest') {
      FlowItemFrameNodeClipContentTest();
    } else if (name === 'FlowItemFrameNodeNoClipContentTest') {
      FlowItemFrameNodeNoClipContentTest();
    } else if (name === 'LazyColumnClipContentTest') {
      LazyColumnClipContentTest();
    } else if (name === 'LazyColumnNoClipContentTest') {
      LazyColumnNoClipContentTest();
    } else if (name === 'LazyVGridClipContentTest') {
      LazyVGridClipContentTest();
    } else if (name === 'LazyVGridNoClipContentTest') {
      LazyVGridNoClipContentTest();
    } else if (name === 'LazyVWaterFlowClipContentTest') {
      LazyVWaterFlowClipContentTest();
    } else if (name === 'LazyVWaterFlowNoClipContentTest') {
      LazyVWaterFlowNoClipContentTest();
    }
  }

  @Builder
  navButton(label: string, page: string) {
    Button(label)
      .width('100%')
      .margin({ top: 4, bottom: 4 })
      .onClick(() => {
        this.navPathStack.pushPathByName(page, null);
      })
  }

  // One titled group: a header plus its ClipContent / NoClipContent entries.
  @Builder
  navGroup(title: string, clipPage: string, noClipPage: string) {
    Column() {
      Text(title)
        .width('100%')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#3050C0')
        .margin({ bottom: 4 })
      this.navButton('ClipContent', clipPage)
      this.navButton('NoClipContent', noClipPage)
    }
    .width('90%')
    .padding(12)
    .margin({ top: 8, bottom: 8 })
    .borderRadius(12)
    .backgroundColor('#FFFFFF')
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Navigation(this.navPathStack) {
      Scroll() {
        Column() {
          Button('Back')
            .width('90%')
            .margin({ top: 8, bottom: 8 })
            .onClick(() => {
              this.getUIContext().getRouter().back();
            })
          this.navGroup('FlowItem', 'FlowItemClipContentTest', 'FlowItemNoClipContentTest')
          this.navGroup('FlowItem FrameNode', 'FlowItemFrameNodeClipContentTest', 'FlowItemFrameNodeNoClipContentTest')
          this.navGroup('LazyColumn', 'LazyColumnClipContentTest', 'LazyColumnNoClipContentTest')
          this.navGroup('LazyVGrid', 'LazyVGridClipContentTest', 'LazyVGridNoClipContentTest')
          this.navGroup('LazyVWaterFlow', 'LazyVWaterFlowClipContentTest', 'LazyVWaterFlowNoClipContentTest')
        }
        .width('100%')
        .padding({ top: 12, bottom: 12 })
      }
      .width('100%')
      .backgroundColor('#F0F0F0')
    }
    .navDestination(this.pageMap)
    .title('WaterFlow ClipContent')
  }
}
