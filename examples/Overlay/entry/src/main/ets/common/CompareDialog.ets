/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { promptAction, LevelOrder } from '@kit.ArkUI';
import { MyComponent } from '../common/MyComponent'

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Extend(Select)
function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@ComponentV2
export struct CustomDialogBuilder {
  build() {
    Column() {
      Text('弹窗层级参考Dialog').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput()
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            let controller: PromptActionDialogController = this.getDialogController();
            if (controller != undefined) {
              controller.close();
              console.info('---1237---    this.getDialogController().close() close dialog @ComponentV2')
              console.info(`---1237---    controller: ${controller}`)
            } else {
              console.info('---1237---    this.getDialogController() return undefined')
              console.info(`---1237---    controller: ${controller}`)
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('confirm')
          .onClick(() => {
            let controller: PromptActionDialogController = this.getDialogController();
            if (controller != undefined) {
              controller.close();
              console.info('---1237---    this.getDialogController().close() close dialog @ComponentV2')
              console.info(`---1237---    controller: ${controller}`)
            } else {
              console.info('---1237---    this.getDialogController() return undefined')
              console.info(`---1237---    controller: ${controller}`)
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })
    }
  }
}

@Preview
@Component
export struct CompareDialog {
  // levelOrder对照弹窗

  @Builder
  OpenCustomDialogBuilder() {
    CustomDialogBuilder()
  }

  //
  @State openCustomDialogOption: promptAction.CustomDialogOptions = {
    builder: () => {
      this.OpenCustomDialogBuilder()
    },
    showInSubWindow: false,
    isModal: false,
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -10 },
    backgroundColor: '#BBB2C8',
    backgroundBlurStyle: BlurStyle.NONE
  }

  build() {
    Column({ space: 5 }) {
      Text(`对照弹窗子窗类型: ${this.openCustomDialogOption.showInSubWindow}`)
        .paramTextStyle()
      Row({ space: 3 }) {
        MyComponent({
          title: 'subWindow: True', func: () => {
            this.openCustomDialogOption.showInSubWindow = true
          }
        })
        MyComponent({
          title: 'subWindow: False', func: () => {
            this.openCustomDialogOption.showInSubWindow = false
          }
        })
      }

      Text(`对照弹窗层级order`)
        .paramTextStyle()
      Select([
        { value: 'test_order: 0' },
        { value: 'test_order: -100000' },
        { value: 'test_order: 100000' },
      ])
        .selectStyle()
        .onSelect((idx, value: string) => {
          switch (value) {
            case 'test_order: 0':
              this.openCustomDialogOption.levelOrder = LevelOrder.clamp(0)
              break;
            case 'test_order: -100000':
              this.openCustomDialogOption.levelOrder = LevelOrder.clamp(-100000)
              break;
            case 'test_order: 100000':
              this.openCustomDialogOption.levelOrder = LevelOrder.clamp(100000)
              break;
          }
        })
        .key('select_test_levelOrder')
      Text(`对照弹窗`)
        .componentTextStyle()
        .onClick(() => {
          promptAction.openCustomDialog(this.openCustomDialogOption)
        })
    }
    .columnStyle()
  }
}