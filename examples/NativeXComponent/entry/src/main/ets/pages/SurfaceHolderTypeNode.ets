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
// [Start surface_holder_type_node_ets]
import native from 'libnativerender.so';
import { FrameNode, NodeController, typeNode, UIContext } from '@kit.ArkUI';

class MyNodeController extends NodeController {
  // [StartExclude surface_holder_type_node_ets]
  public xComponent: typeNode.XComponent | undefined = undefined;
  public xComponentId: string = 'xcp' + (new Date().getTime());
  public node: FrameNode | undefined = undefined;
  public column: typeNode.Column | undefined = undefined;
  public attachButton: typeNode.Button | undefined = undefined;
  public detachButton: typeNode.Button | undefined = undefined;
  // [EndExclude surface_holder_type_node_ets]
  makeNode(uiContext: UIContext): FrameNode | null {
    // [StartExclude surface_holder_type_node_ets]
    this.node = new FrameNode(uiContext);
    this.column = typeNode.createNode(uiContext, 'Column')
    this.column.initialize()
      .width('100%')
      .height('100%')
    try {
      this.node.appendChild(this.column);
    } catch (error) {
      console.error('Fail to append child: ', error);
    }
    // [EndExclude surface_holder_type_node_ets]
    // 创建XComponent组件节点
    this.xComponent = typeNode.createNode(uiContext, 'XComponent', { type: XComponentType.SURFACE });
    this.xComponent.attribute
      .id(this.xComponentId)
      .focusable(true)
      .focusOnTouch(true)
    native.bindNode(this.xComponentId, this.xComponent)
    // [StartExclude surface_holder_type_node_ets]
    try {
      this.column.appendChild(this.xComponent);
    } catch (error) {
      console.error('Fail to append child: ', error);
    }

    return this.node;
    // [EndExclude surface_holder_type_node_ets]
  }
  // [StartExclude surface_holder_type_node_ets]
  aboutToDisappear(): void {
    native.unbindNode(this.xComponentId)
    try {
      this.node?.removeChild(this.xComponent);
    } catch (error) {
      console.error('Fail to remove child: ', error);
    }
    this.xComponent?.dispose();
  }
  // [EndExclude surface_holder_type_node_ets]
}

// [StartExclude surface_holder_type_node_ets]
@Builder
export function SurfaceHolderTypeNodeBuilder(name: string, param: Object) {
  SurfaceHolderTypeNode()
}
// [EndExclude surface_holder_type_node_ets]

@Component
export struct SurfaceHolderTypeNode {
  // [StartExclude surface_holder_type_node_ets]
  @State isShow: boolean = true;
  @State minRate: number = 0;
  @State maxRate: number = 120;
  @State expected: number = 60;
  needSoftKeyboard: boolean = false;
  @State needSoftKeyboardState: string = 'needSoftKeyboard=' + this.needSoftKeyboard;
  @State text: string = '单指点击XComponent软键盘消失';
  controller: TextInputController = new TextInputController();
  // [EndExclude surface_holder_type_node_ets]
  myNodeController: MyNodeController = new MyNodeController();

  build() {
    NavDestination() {
      Column() {
        // [StartExclude surface_holder_type_node_ets]
        TextInput({ text: this.text, placeholder: 'please input ...', controller: this.controller })
          .id('textInput')
          .placeholderColor(Color.Grey)
          .placeholderFont({ size: 14, weight: 400 })
          .caretColor(Color.Blue)
          .width(400)
          .height(40)
          .margin(10)
          .fontSize(14)
          .fontColor(Color.Black)
          .onChange((value: string) => {
            this.text = value
          })
        // [EndExclude surface_holder_type_node_ets]
        Column() {
          if (this.isShow) {
            NodeContainer(this.myNodeController)
              .width(200)
              .height(200)
              .focusable(true)
              .focusOnTouch(true)
              .defaultFocus(true)
          }
        }.height(200)
        // [StartExclude surface_holder_type_node_ets]
        Row({ space: 5 }) {
          Button('Draw Star')
            .onClick(() => {
              native.drawPatternForSurfaceHolder(this.myNodeController.xComponent!);
            })
            .width('40%')

          Button('创建/销毁').onClick(() => {
            this.isShow = !this.isShow;
          }).width('40%')
        }.margin({
          top: 10,
          bottom: 10,
          left: 12,
          right: 12
        })

        Column() {
          Text('期望帧率设置：')
            .textAlign(TextAlign.Start)
            .fontSize(15)
            .border({ width: 1 })
            .padding(10)
            .width('100%')
            .margin(5)
          Text('min: ' + this.minRate)
          Slider({
            value: this.minRate,
            min: 0,
            max: 240,
            step: 1
          }).onChange((value: number, mode: SliderChangeMode) => {
            this.minRate = value;
            native.setFrameRate(this.myNodeController.xComponentId, this.minRate, this.maxRate, this.expected)
          }).width('100%')
            .id('minSlider')
          Text('max: ' + this.maxRate)
          Slider({
            value: this.maxRate,
            min: 0,
            max: 240,
            step: 1
          }).onChange((value: number, mode: SliderChangeMode) => {
            this.maxRate = value;
            native.setFrameRate(this.myNodeController.xComponentId, this.minRate, this.maxRate, this.expected)
          }).width('100%')
            .id('maxSlider')
          Text('expected: ' + this.expected)
          Slider({
            value: this.expected,
            min: 0,
            max: 240,
            step: 1
          }).onChange((value: number, mode: SliderChangeMode) => {
            this.expected = value;
            native.setFrameRate(this.myNodeController.xComponentId, this.minRate, this.maxRate, this.expected)
          }).width('100%')
            .id('expectedSlider')
        }.backgroundColor('#F0FAFF')

        Button(this.needSoftKeyboardState)
          .onClick(() => {
            this.needSoftKeyboard = !this.needSoftKeyboard;
            this.needSoftKeyboardState = 'needSoftKeyboard=' + this.needSoftKeyboard;
            native.setNeedSoftKeyboard(this.myNodeController.xComponentId, this.needSoftKeyboard);
            this.text = this.needSoftKeyboard ? '单指点击XComponent软键盘不消失' : '单指点击XComponent软键盘消失'
          })
          .width('50%')
          .margin({
            top: 10,
            left: 12,
            right: 12
          })
        Button('Initialize')
          .onClick(() => {
            native.initialize(this.myNodeController.xComponentId)
          })
          .width('50%')
          .margin({
            top: 10,
            left: 12,
            right: 12
          })
        Button('Finalize')
          .onClick(() => {
            native.finalize(this.myNodeController.xComponentId)
          })
          .width('50%')
          .margin({
            top: 10,
            left: 12,
            right: 12
          })
          // [EndExclude surface_holder_type_node_ets]
      }
      .width('100%')
    }
  }
}
// [End surface_holder_type_node_ets]
