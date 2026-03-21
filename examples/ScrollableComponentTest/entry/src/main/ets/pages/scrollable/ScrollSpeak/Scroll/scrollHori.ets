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

import { NodeController, FrameNode, typeNode } from '@kit.ArkUI';

class MyNodeController extends NodeController {
  public rootNode: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.rootNode.commonAttribute.width(100);
    return this.rootNode;
  }

  addCommonEvent(frameNode: FrameNode) {
    // 获取Scroll事件
    let scrollEvent: UIScrollEvent | undefined = typeNode.getEvent(frameNode, 'Scroll');

    // 设置OnWillScroll事件
    scrollEvent?.setOnWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState,
      scrollSource: ScrollSource) => {
      console.info('onWillScroll xOffset = ${xOffset}, yOffset = ${yOffset}, scrollState = ${scrollState}, scrollSource = ${scrollSource}');
    });

    // 设置OnDidScroll事件
    scrollEvent?.setOnDidScroll((scrollOffset: number, scrollState: ScrollState) => {
      console.info('onDidScroll scrollOffset = ${scrollOffset}, scrollState = ${scrollState}');
    });

    // 设置OnReachStart事件
    scrollEvent?.setOnReachStart(() => {
      console.info('onReachStart');
    });

    // 设置OnReachEnd事件
    scrollEvent?.setOnReachEnd(() => {
      console.info('onReachEnd');
    });

    // 设置OnScrollStart事件
    scrollEvent?.setOnScrollStart(() => {
      console.info('onScrollStart');
    });

    // 设置OnScrollStop事件
    scrollEvent?.setOnScrollStop(() => {
      console.info('onScrollStop');
    });

    // 设置OnScrollFrameBegin事件
    scrollEvent?.setOnScrollFrameBegin((offset: number, state: ScrollState) => {
      console.info('onScrollFrameBegin offset = ${offset}, state = ${state}');
      return undefined;
    });
  }
}

@Entry
@Component
struct ScrollHoriIndex {
  @State index: number = 0;
  private myNodeController: MyNodeController = new MyNodeController();
  @State numbers: string[] = [];

  aboutToAppear() {
    for (let i = 0; i < 10; i++) {
      this.numbers.push(`${i+1}`);
    }
  }

  build() {
    Column() {
      Scroll() {
        Row() {
          ForEach(this.numbers, (day: string, index: number) => {
            Row() {
              Text(day)
                .fontSize(16)
                .backgroundColor(0xF9CF93)
                .width('90%')
                .height(80)
                .textAlign(TextAlign.Center)
                .margin({ top: 10 })
            }
            .width('100%')
            .justifyContent(FlexAlign.Center)
            // .alignItems(HorizontalAlign.Center)
          }, (day: string, index: number) => index.toString() + day)
        }
      }
      // .scrollable(ScrollDirection.Vertical)
      .scrollable(ScrollDirection.Horizontal)
      .edgeEffect(EdgeEffect.Spring)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      NodeContainer(this.myNodeController)
    }
  }
}
