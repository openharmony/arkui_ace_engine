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

import nativeNode from 'libnativeNode.so';

@Entry
@Component
struct Index {
  @State focusActive: boolean = false;
  @State autoTransfer: boolean = true;
  @State nodeTabStop: boolean = true;
  @State keyProcessingMode: number = 0;

  build() {
    Column({ space: 15 }) {
      // 标题
      Text('Native Interface Focus API Test')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20 })
        .textAlign(TextAlign.Center)

      // 当前焦点状态显示
      Column({ space: 8 }) {
        Text($r('app.string.state_information'))
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row() {
          Text($r('app.string.a_status'))
            .fontSize(14)
          Text(this.focusActive ? $r('app.string.is_status') : $r('app.string.no_status'))
            .fontSize(14)
            .fontColor(this.focusActive ? Color.Green : Color.Red)
            .fontWeight(FontWeight.Bold)
        }
        .width('100%')
        .justifyContent(FlexAlign.Start)

        Row() {
          Text($r('app.string.transfer_status'))
            .fontSize(14)
          Text(this.autoTransfer ? $r('app.string.enable') : $r('app.string.disable'))
            .fontSize(14)
            .fontColor(this.autoTransfer ? Color.Green : Color.Red)
            .fontWeight(FontWeight.Bold)
        }
        .width('100%')
        .justifyContent(FlexAlign.Start)
      }
      .width('100%')
      .padding(15)
      .backgroundColor('#F0F8FF')
      .borderRadius(10)

      // Native组件区域
      XComponent({
        id: 'focusTest',
        type: XComponentType.NODE,
        libraryname: 'nativeNode'
      })
        .onAppear(() => {
          nativeNode.createNativeNode('focusTest', this.getUIContext());
        })
        .width('100%')
        .height(280)
        .backgroundColor('#FFFAFA')
        .border({ width: 2, color: Color.Gray, style: BorderStyle.Dashed })
        .borderRadius(8)

      // 焦点控制按钮区域
      Scroll() {
        Column() {
          Column({ space: 15 }) {
            Text($r('app.string.control_operation'))
              .fontSize(18)
              .fontWeight(FontWeight.Medium)

            // Menu测试
            Row({ space: 10 }) {
              Button($r('app.string.test_button'))
                .bindMenu([
                  {
                    value: $r('app.string.check_button'),
                    action: () => {
                    }
                  }
                ])
                .id('menu')
                .fontSize(12)
                .focusable(true)
                .fontWeight(FontWeight.Medium)
            }

            // 节点可聚焦控制
            Row({ space: 10 }) {
              Button($r('app.string.set_be_focusable'))
                .onClick(() => {
                  this.setNodeFocusable('Button0', true);
                })
                .id('setNodeFocusableTrue')
                .fontSize(12)

              Button($r('app.string.set_be_not_focusable'))
                .onClick(() => {
                  this.setNodeFocusable('Button0', false);
                })
                .id('setNodeFocusableFalse')
                .fontSize(12)
            }

            // 请求焦点/清理焦点操作
            Row({ space: 10 }) {
              Button($r('app.string.synchronize_request_focus'))
                .onClick(() => {
                  this.requestFocus('Button0');
                })
                .fontSize(12)
                .id('requestButton0')

              Button($r('app.string.synchronize_request_focus1'))
                .onClick(() => {
                  this.requestFocusAsync('Button1');
                })
                .fontSize(12)
            }
            Button($r('app.string.clear_focus'))
              .onClick(() => {
                this.clearFocus();
              })
              .fontSize(12)

            // 焦点通用属性
              Button('SetFocusOnTouch(2) false')
                .onClick(() => {
                  this.setNodeFocusOnTouch('Button2', false);
                })
                .fontSize(12)

              Button('SetFocusOnTouch(3) true')
                .onClick(() => {
                  this.setNodeFocusOnTouch('Button3', true);
                })
                .fontSize(12)

            Row({ space: 10 }) {
              Button('SetTabStop(4) ' + this.nodeTabStop)
                .onClick(() => {
                  this.setNodeTabStop('Column4', this.nodeTabStop);
                  this.nodeTabStop = !this.nodeTabStop;
                })
                .fontSize(12)
                .id('setTabStopButton')
            }

            Row({ space: 10 }) {
              Button('SetNextFocus(5→7)')
                .onClick(() => {
                  this.setNodeNextFocus('Button5', 'Button7', 0); // 0表示tab
                })
                .fontSize(12)

              Button('SetFocusBox(8)')
                .onClick(() => {
                  this.setNodeFocusBox('Button8', 5.0, 2.0, 0xFF00FF00);
                })
                .fontSize(12)
            }

            // 焦点激活控制
            Row({ space: 10 }) {
              Button(this.focusActive ? $r('app.string.deactivate') : $r('app.string.activate_focus'))
                .onClick(() => {
                  this.focusActive = !this.focusActive;
                  this.activateFocus(this.focusActive);
                })
                .fontSize(12)

              Button(this.autoTransfer ? $r('app.string.disable_automatic_transfer') :
                $r('app.string.enable_automatic_transfer'))
                .onClick(() => {
                  this.autoTransfer = !this.autoTransfer;
                  this.setAutoTransfer(this.autoTransfer);
                })
                .fontSize(12)
            }

            Button(this.keyProcessingMode ? $r('app.string.propagate_upward_to_ancestor_components') :
              $r('app.string.key_events_are_used_for_focus_navigation'))
              .onClick(() => {
                this.keyProcessingMode = Number(!this.keyProcessingMode);
                this.SetKeyProcessingMode(this.keyProcessingMode);
              })
              .fontSize(12)
          }
          .width('100%')
          .padding(20)
          .backgroundColor('#F5F5F5')
          .borderRadius(10)
        }
      }.height(300)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  private SetKeyProcessingMode(mode: number) {
    try {
      nativeNode.SetKeyProcessingMode(mode);
    } catch (error) {
    }
  }

  // 请求焦点
  private requestFocus(nodeId: string) {
    try {
      let result: number = nativeNode.requestFocus(nodeId);
    } catch (error) {
    }
  }

  // 请求焦点异步
  private requestFocusAsync(nodeId: string) {
    try {
      let result: number = nativeNode.requestFocusAsync(nodeId);
    } catch (error) {
    }
  }

  // 清除焦点
  private clearFocus() {
    try {
      nativeNode.clearFocus();
    } catch (error) {
    }
  }

  // 激活焦点
  private activateFocus(isActive: boolean) {
    try {
      nativeNode.activateFocus(isActive, true);
    } catch (error) {
    }
  }

  // 设置自动转移
  private setAutoTransfer(autoTransfer: boolean) {
    try {
      nativeNode.setAutoTransfer(autoTransfer);
    } catch (error) {
    }
  }

  // 设置节点可聚焦
  private setNodeFocusable(nodeId: string, focusable: boolean) {
    try {
      let result: number = nativeNode.setNodeFocusable(nodeId, focusable);
    } catch (error) {
    }
  }

  // 设置节点TabStop属性
  private setNodeTabStop(nodeId: string, tabStop: boolean) {
    try {
      let result: number = nativeNode.setNodeTabStop(nodeId, tabStop);
    } catch (error) {
    }
  }

  // 设置节点可点击获焦
  private setNodeFocusOnTouch(nodeId: string, focusOnTouch: boolean) {
    try {
      let result: number = nativeNode.setNodeFocusOnTouch(nodeId, focusOnTouch);
    } catch (error) {
    }
  }

  // 设置节点焦点框
  private setNodeFocusBox(nodeId: string, distance: number, width: number, color: number) {
    try {
      let result: number = nativeNode.setNodeFocusBox(nodeId, distance, width, color);
    } catch (error) {
    }
  }

  // 设置节点默认焦点
  private setNodeDefaultFocus(nodeId: string, defaultFocus: boolean) {
    try {
      let result: number = nativeNode.setNodeDefaultFocus(nodeId, defaultFocus);
    } catch (error) {
    }
  }

  // 设置节点下一个焦点
  private setNodeNextFocus(nodeId: string, nextNodeId: string, direction: number) {
    try {
      let result: number = nativeNode.setNodeNextFocus(nodeId, nextNodeId, direction);
      const directionName = ['tab', 'shift+tab', 'up', 'down', 'left', 'right'][direction] || '未知';
    } catch (error) {
    }
  }
}
