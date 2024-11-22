/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock } from 'common';

@Component
export struct BindPopupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State handlePopup: boolean = false;
  @State enablePopupType: boolean = true;
  @State popupType: number = 0;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Button('BindPopup')
        .onClick(() => {
          this.handlePopup=!this.handlePopup;
          console.info('Button click');
        })
        .bindPopup(this.handlePopup, {
          message: this.popupType === 0 ? 'This is a popup with button ' : 'This is a popup only text ',
          placementOnTop: true,
          showInSubWindow: false,
          onStateChange: (e) => {
            console.info(JSON.stringify(e.isVisible))
            if (!e.isVisible) {
              this.handlePopup = false
            }
          },
          primaryButton: this.popupType === 0 ? {
            value: 'confirm ',
            action: () => {
              this.handlePopup=!this.handlePopup;
              console.info('confirm Button click');
            }
          }: null,
          secondaryButton: this.popupType === 0 ? {
            value: 'cancel ',
            action: () => {
              this.handlePopup=!this.handlePopup;
              console.info('cancel Button click')
            }
          } :null,
        })
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '气泡类型',
          isEnabled: $enablePopupType,
          value: $popupType,
          dataSource: [
            { label: '按钮气泡', value: 0 },
            { label: '文本气泡', value: 1 }
          ]
        })
      }
    }
    .height('52%')
  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    BindPopupBootcamp({
      title: '气泡/bindPopup'
    })
  }
}