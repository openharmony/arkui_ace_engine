/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ComponentContent, FrameNode } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit';

interface PopupParam {
  closeFunc?: () => void;
  enableHoverMode?: boolean,
  showInSubWindow?: boolean,
  placement?: Placement,
}

export function showPopup(context: UIContext, uniqueId: number, contentNode: ComponentContent<Object>,
  popupParam: PopupParam) {
  const promptAction = context.getPromptAction();
  let frameNode: FrameNode | null = context.getFrameNodeByUniqueId(uniqueId);
  let targetId = frameNode?.getFirstChild()?.getUniqueId();
  promptAction.openPopup(contentNode, { id: 'OpenPopup' }, {
    radius: 16,
    enableArrow: true,
    enableHoverMode: popupParam.enableHoverMode,
    showInSubWindow: popupParam.showInSubWindow,
    placement: popupParam.placement
  })
    .then(() => {
      console.info('openPopup success');
    })
    .catch((err: BusinessError) => {
      console.info('openPopup error: ' + err.code + ' ' + err.message);
    })
  popupParam.closeFunc = () => {
    promptAction.closePopup(contentNode)
      .then(() => {
        console.info('closePopup success');
      })
      .catch((err: BusinessError) => {
        console.info('closePopup error: ' + err.code + ' ' + err.message);
      })
  }
}

@Builder
function buildText(param?: PopupParam) {
  Column() {
    Text('popup')
    Button('Close Popup')
      .fontSize(20)
      .onClick(() => {
        param?.closeFunc?.();
      })
  }
}

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';
  @State index: number = 0;
  @State arrayStr: Array<string> = ['上半屏', '中轴', '下半屏']
  @State enableHoverMode: boolean | undefined = true;
  @State showInSubwindow: boolean = false;
  @State placement: Placement | undefined = Placement.Bottom;
  @State isShow: boolean = false
  @State customPopup: boolean = false;

  @Builder popupBuilder() {
    Row({ space: 2 }) {
      Image($r('app.media.app_icon')).width(24).height(24).margin({ left: -5 })
      Text('Custom Popup').fontSize(10)
    }.width(100).height(50).padding(5)
  }

  build() {
    RelativeContainer() {
      Column({space: 10}) {
        Button('测试区域:' + this.arrayStr[this.index])
          .onClick(() => {
            if (this.index < 2) {
              this.index++
            } else {
              this.index = 0
            }
          })

        Button('子窗显示:' + (this.showInSubwindow ? '子窗' : '非子窗'))
          .onClick(() => {
            this.showInSubwindow = !this.showInSubwindow
          })

        Row(){
          Text('enableHoverMode: ' )
          TextPicker({ range: [
            'true',
            'false',
            'undefined',
          ], selected: 0 })
            .width(100)
            .height(60)
            .selectedTextStyle({ font: { size: 14 } })
            .disappearTextStyle({ font: { size: 14 } })
            .canLoop(false)
            .textStyle({ font: { size: 14 } })
            .defaultPickerItemHeight(20)
            .onChange((value: string | string[], index: number | number[]) => {
              switch (value) {
                case 'true':
                  this.enableHoverMode = true
                  break;
                case 'false':
                  this.enableHoverMode = false
                  break;
                case 'undefined':
                  this.enableHoverMode = undefined
                  break;
              }
            })
        }
        Row(){
          Text('placement: ' )
          TextPicker({ range: [
            'Bottom',
            'Left',
            'Top',
            'Right',
          ], selected: 0 })
            .width(100)
            .height(60)
            .selectedTextStyle({ font: { size: 14 } })
            .disappearTextStyle({ font: { size: 14 } })
            .canLoop(false)
            .textStyle({ font: { size: 14 } })
            .defaultPickerItemHeight(20)
            .onChange((value: string | string[], index: number | number[]) => {
              switch (value) {
                case 'Bottom':
                  this.placement = Placement.Bottom
                  break;
                case 'Right':
                  this.placement = Placement.Right
                  break;
                case 'Left':
                  this.placement = Placement.Left
                  break;
                case 'Top':
                  this.placement = Placement.Top
                  break;
              }
            })
        }
      }

      Row() {
        Button('Popup')
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.isShow = !this.isShow
          })
          .bindPopup(this.isShow, {
            enableHoverMode: this.enableHoverMode,
            showInSubWindow: this.showInSubwindow,
            placement: this.placement,
            message: 'This is a popup with PopupOptions',
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.isShow = false;
              }
            }
          })



        Button('CustomPopup')
          .onClick(() => {
            this.customPopup = !this.customPopup;
          })
          .bindPopup(this.customPopup, {
            builder: this.popupBuilder,
            placement: this.placement,
            mask: {color:'#33000000'},
            popupColor: Color.Yellow,
            enableArrow: true,
            enableHoverMode: this.enableHoverMode,
            showInSubWindow: this.showInSubwindow,
            transition:TransitionEffect.asymmetric(
              TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                TransitionEffect.translate({ x: 50, y: 50 })),
              TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                TransitionEffect.translate({ x: 50, y: 50 }))),
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.customPopup = false;
              }
            }
          })

        Button('OpenPopup')
          .fontSize(20)
          .id('OpenPopup')
          .onClick(() => {
            let context = this.getUIContext();
            const popupParam: PopupParam = {enableHoverMode: this.enableHoverMode, showInSubWindow: this.showInSubwindow, placement: this.placement,};
            const contentNode = new ComponentContent(context, wrapBuilder(buildText), popupParam);
            showPopup(context, this.getUniqueId(), contentNode, popupParam);
          })
      }
      .alignRules({
        center: { anchor: '__container__', align: VerticalAlign.Center },
        middle: { anchor: '__container__', align: HorizontalAlign.Center }
      })
      .margin({
        top: this.index == 2 ? 200 : this.index == 1 ? 50 : 250,
        bottom: this.index == 0 ? 330 : 0
      })
    }
    .height('100%')
    .width('100%')

  }
}
