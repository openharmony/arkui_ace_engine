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

import router from '@ohos.router';
import { WaterFlowControllerStore } from './WaterFlowControllerStore';

@Entry
@Component
struct WaterFlowDestroySubPage {
  @State private resultText: string = '';
  @State private modeText: string = '';

  aboutToAppear(): void {
    this.resultText = WaterFlowControllerStore.getResult();
    this.modeText = `Navigation mode: ${WaterFlowControllerStore.getNavigationMode()}`;
  }

  private updateResult(result: string): void {
    this.resultText = result;
  }

  build() {
    Column({ space: 12 }) {
      Text('Child Page')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text(this.modeText)
        .fontSize(14)
      Text('Use push to verify page recovery on Back. Use replace to verify behavior after the parent page is really replaced.')
        .fontSize(14)
      Text(this.resultText)
        .fontSize(14)

      Row({ space: 10 }) {
        Button('Call scrollBy').onClick(() => {
          this.updateResult(WaterFlowControllerStore.callScrollBy());
        })
        Button('Call scrollTop').onClick(() => {
          this.updateResult(WaterFlowControllerStore.callScrollTop());
        })
      }

      Row({ space: 10 }) {
        Button('Call scrollBottom').onClick(() => {
          this.updateResult(WaterFlowControllerStore.callScrollBottom());
        })
        Button('Read Offset').onClick(() => {
          this.updateResult(WaterFlowControllerStore.callReadOffset());
        })
      }

      Button('Back').onClick(() => {
        router.back();
      })
    }
    .padding(16)
    .width('100%')
    .height('100%')
    .alignItems(HorizontalAlign.Start)
  }
}