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

import web_webview from '@ohos.web.webview'
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { Skip } from './Utils/Skip';

interface Info {
  caseName: string;
  pageUrl: string;
}

@Entry
@Component
struct WebComponent {
  controller: web_webview.WebviewController = new web_webview.WebviewController()

  private changeOrientation(isLandscape: boolean) {
    // 获取UIAbility实例的上下文信息
    let context = getContext(this) as common.UIAbilityContext;
    // 调用该接口手动改变设备横竖屏状态
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  private scroller: Scroller = new Scroller()
  @State simpleList: Array<Info> = [
    { caseName: "border_width", pageUrl: "pages/22DEV/SR20240204021754/border_width" },
    { caseName: "border_color", pageUrl: "pages/22DEV/SR20240204021754/border_color" },
    { caseName: "border_radius", pageUrl: "pages/22DEV/SR20240204021754/border_radius" },
  ];

  build() {
    Column() {
      Stack({ alignContent: Alignment.End }) {
        Scroll(this.scroller) {
          Flex({ direction: FlexDirection.Column }) {
            ForEach(this.simpleList, (item: Info) => {
              Skip({ butName: item.caseName, pushUrl: item.pageUrl })
            })
          }.margin({ right: 15 }).borderColor("rgba(0,0,0,0)")
        }
        .width('100%')
        .scrollBar(BarState.Off)
        .scrollable(ScrollDirection.Vertical)

        ScrollBar({ scroller: this.scroller, direction: ScrollBarDirection.Vertical, state: BarState.Auto }) {
          Text()
            .width(20)
            .height(100)
            .borderRadius(10)
            .backgroundColor('#C0C0C0')
        }.width(20).backgroundColor('#ededed')
      }
    }.height('90%')
  }
}

