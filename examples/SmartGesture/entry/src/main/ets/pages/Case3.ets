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

// [Start smartgesture_case3]
import {
  BaseGestureHandlingProposal,
  ClickActionProposal,
  GestureHandlingResolution,
  SelectActionProposal,
  TargetedGestureProposal,
} from '@kit.ArkUI';

@Entry
@Component
struct Demo3 {
  private controller = this.getUIContext().getSmartGestureController();
  @State hint: string = 'Demo3: 单页面+多组件\n划一划切换选中组件 → 敲一敲触发点击';
  @State btnCount: number = 0;
  @State textClickCount: number = 0;
  @State toggleOn: boolean = false;
  @State sliderVal: number = 30;

  private callback = (proposal: BaseGestureHandlingProposal): GestureHandlingResolution => {
    let targetProposal = proposal as TargetedGestureProposal;
    let nodeId = targetProposal.node ? targetProposal.node.getId() : '';
    this.hint = `意图=${proposal.operateIntention}, 动作=${proposal.action}, 目标=${nodeId}`;
    const resolution = new GestureHandlingResolution(true);

    if (proposal.action === SmartGestureAction.CLICK) {
      if (nodeId) {
        const node = this.getUIContext().getFrameNodeById(nodeId);
        if (node) {
          resolution.selectedProposal = new ClickActionProposal(node);
        }
      }
    } else if (proposal.action === SmartGestureAction.SELECT) {
      if (nodeId) {
        const node = this.getUIContext().getFrameNodeById(nodeId);
        if (node) {
          resolution.selectedProposal = new SelectActionProposal(node);
        }
      }
    }

    return resolution;
  };

  aboutToAppear(): void {
    this.controller.enableSmartTapAndSlideGestures(true);
    this.controller.registerMonitor(this.callback);
  }

  aboutToDisappear(): void {
    this.controller.clearMonitors();
    this.controller.enableSmartTapAndSlideGestures(false);
  }

  build() {
    Scroll() {
      Column({ space: 16 }) {
        Text('Demo3: 单页面 + 多组件')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Text(this.hint)
          .fontSize(13)
          .fontColor('#666')
          .width('100%')
          .textAlign(TextAlign.Center)
          .padding(8)
          .borderRadius(8)
          .backgroundColor('#e8e8e8')

        Text('可点击文本')
          .id('comp_text')
          .fontSize(18)
          .width('100%')
          .padding(16)
          .borderRadius(10)
          .borderWidth(1)
          .textAlign(TextAlign.Center)
          .backgroundColor('#e3f2fd')
          .smartGestureShortcut({ action: GestureShortcut.PRIMARY, enabled: true, selectable: true })
          .onClick(() => {
            this.textClickCount += 1;
            this.hint = `文本 onClick 触发, 点击=${this.textClickCount}`;
          })

        Row() {
          Text(`文本点击次数: ${this.textClickCount}`)
            .fontSize(14)
            .fontColor('#555')
        }.width('100%').justifyContent(FlexAlign.Center)

        Button(`按钮 / 点击=${this.btnCount}`)
          .id('comp_button')
          .width('100%')
          .backgroundColor('#1976d2')
          .smartGestureShortcut({ action: GestureShortcut.PRIMARY, enabled: true, selectable: true })
          .onClick(() => {
            this.btnCount += 1;
            this.hint = `按钮 onClick 触发, 点击=${this.btnCount}`;
          })

        Row() {
          Toggle({ type: ToggleType.Switch, isOn: this.toggleOn })
            .id('comp_toggle')
            .selectedColor('#4caf50')
            .smartGestureShortcut({ action: GestureShortcut.PRIMARY, enabled: true, selectable: true })
            .onChange((isOn: boolean) => {
              this.toggleOn = isOn;
              this.hint = `Toggle onChange → ${isOn ? '开' : '关'}`;
            })
          Text(`开关状态: ${this.toggleOn ? '开' : '关'}`)
            .fontSize(14)
            .margin({ left: 12 })
        }
        .width('100%')
        .padding(12)
        .borderRadius(10)
        .borderWidth(1)
        .justifyContent(FlexAlign.Start)

        Row({ space: 8 }) {
          Button('选中按钮').layoutWeight(1)
            .onClick(() => this.controller.requestSelected('comp_button'))
          Button('选中文本').layoutWeight(1)
            .onClick(() => this.controller.requestSelected('comp_text'))
          Button('选中开关').layoutWeight(1)
            .onClick(() => this.controller.requestSelected('comp_toggle'))
        }.width('100%')

        Button('清空选中')
          .width('100%')
          .onClick(() => {
            this.controller.clearSelected();
            this.hint = '选中已清空';
          })
      }
      .width('100%')
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f3f5')
  }
}
// [End smartgesture_case3]