/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/*用例描述
  本用例导入了三方库apng，在自定义刷新样式中使用apng实现了自定义刷新动画，并通过监听刷新状态的变化控制动画的执行与停止。
*/

import { apng, ApngController } from '@ohos/apng';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { ComponentContent } from '@ohos.arkui.node';

class Params {
  public controller: ApngController;

  constructor(controller: ApngController) {
    this.controller = controller;
  }
}

@Builder
function customRefreshComponent(params: Params) {
    Stack() {
      Row() {
        Column() {
          apng({
            src: $r('app.media.startIcon'),
            controller: params.controller
          })
            .margin({ top: 40 })
        }
      }
      .alignItems(VerticalAlign.Center)
    }
    .align(Alignment.Center)
    .clip(true)
    .constraintSize({ minHeight: 32 })
    .width('100%')
  }

@Entry
@Component
struct RefreshAPNGExample {
  @State isRefreshing: boolean = false;
  @State isRunning: boolean = false;
  @State arr: string[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'];
  controller: ApngController = new ApngController();
  private contentNode?: ComponentContent<Object> = undefined;
  private params: Params = new Params(this.controller);

  aboutToAppear(): void {
    let uiContext = this.getUIContext();
    this.contentNode = new ComponentContent(uiContext, wrapBuilder(customRefreshComponent), this.params);
  }

  build() {
    Column() {
      Refresh({ refreshing: $$this.isRefreshing, refreshingContent: this.contentNode }) {
        Scroll() {
          Column() {
            ForEach(this.arr, (item: string) => {
              ListItem() {
                Text('' + item)
                  .height(80)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .fontColor(0xF1F3F5)
              }
            }, (item: string) => item)
          }
        }
        .scrollBar(BarState.Off)
      }
      .backgroundColor(0xF1F3F5)
      .pullToRefresh(true)
      .refreshOffset(64)
      .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM])
      // Use onStateChange and apng controller to control play and stop
      .onStateChange((refreshStatus: RefreshStatus) => {
        if (refreshStatus >= 1 && refreshStatus < 4) {
          this.controller.play();
        } else {
          this.controller.stop();
        }
        hilog.info(0x0000, 'testTag', 'Refresh onStatueChange state is ' + refreshStatus);
      })
      .onRefreshing(() => {
        setTimeout(() => {
          this.isRefreshing = false;
        }, 2000)
        hilog.info(0x0000, 'testTag', 'onRefreshing test')
      })
    }
  }
}