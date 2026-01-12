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

import { CustomDialogExample } from '../../../../common/CustomDialogController'
import { router, LevelMode, ImmersiveMode, LevelOrder } from '@kit.ArkUI'
import { MyComponent } from '../../../../common/MyComponent'
import { CompareDialog } from '../../../../common/CompareDialog'

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


@Entry
@Component
struct CustomDialogTestLevel0_9 {
  scroller: Scroller = new Scroller()
  //
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      textValue: $textValue,
      inputValue: $inputValue
    }),

    onWillAppear: () => {
      console.info('customDialog onWillAppear')
    },
    onDidAppear: () => {
      console.info('customDialog onDidAppear')
    },
    onWillDisappear: () => {
      console.info('customDialog onWillDisappear')
    },
    onDidDisappear: () => {
      console.info('customDialog onDidDisappear')
    },
  })

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证CustomDialog的层级相关属性`)
          .paramTextStyle()
        Column({ space: 5 }) {
          MyComponent({
            title: '跳转导航页', func: () => {
              router.pushUrl({
                url: 'pages/CustomDialogRouter',
              }, router.RouterMode.Standard)
            }
          })
          TextInput()
            .id('keyboard')
        }
        .columnStyle()

        CompareDialog()

        Column({ space: 5 }) {
          Text(`切换层级不同参数`)
            .paramTextStyle()
          Select([
            { value: '设置levelMode为OVERLAY' },
            { value: '设置levelMode为EMBEDDED' },
            { value: '设置EMBEDDED,正确UniqueId' },
            { value: '设置EMBEDDED,错误UniqueId' },
            { value: '设置EMBEDDED,ImmersiveMode.DEFAULT' },
            { value: '设置EMBEDDED,ImmersiveMode.EXTEND' },

            { value: '设置levelOrder为-100001' },
            { value: '设置levelOrder为-100' },
            { value: '设置levelOrder为0' },
            { value: '设置levelOrder为100' },
            { value: '设置levelOrder为100001' },
            { value: '设置EMBEDDED,levelOrder为100' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '设置levelMode为OVERLAY':
                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.OVERLAY,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;

                case '设置levelMode为EMBEDDED':
                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.EMBEDDED,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;

                case '设置EMBEDDED,正确UniqueId':
                  const node: FrameNode | null = this.getUIContext().getFrameNodeById('pageCol') || null;
                  let levelUniqueId = node?.getUniqueId();

                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.EMBEDDED,
                    levelUniqueId: levelUniqueId,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置EMBEDDED,错误UniqueId':
                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.EMBEDDED,
                    levelUniqueId: 1237,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;

                case '设置EMBEDDED,ImmersiveMode.DEFAULT':
                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.EMBEDDED,
                    immersiveMode: ImmersiveMode.DEFAULT,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: true,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置EMBEDDED,ImmersiveMode.EXTEND':
                  this.dialogController = new CustomDialogController({
                    levelMode: LevelMode.EMBEDDED,
                    immersiveMode: ImmersiveMode.EXTEND,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: true,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;

                case '设置levelOrder为-100001':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(-100001),

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置levelOrder为100001':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(100001),

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置levelOrder为-100':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(-100),

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置levelOrder为100':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(100),

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置levelOrder为0':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(0),

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
                case '设置EMBEDDED,levelOrder为100':
                  this.dialogController = new CustomDialogController({
                    levelOrder: LevelOrder.clamp(100),
                    levelMode: LevelMode.EMBEDDED,

                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -40 },

                    isModal: false,
                    builder: CustomDialogExample({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),

                    onWillAppear: () => {
                      console.info('customDialog onWillAppear')
                    },
                    onDidAppear: () => {
                      console.info('customDialog onDidAppear')
                    },
                    onWillDisappear: () => {
                      console.info('customDialog onWillDisappear')
                    },
                    onDidDisappear: () => {
                      console.info('customDialog onDidDisappear')
                    },
                  })
                  break;
              }
            })
            .key('select_dialogLevelAttr')

          Text(`CustomDialog: 层级`)
            .componentTextStyle()
            .onClick(() => {
              this.dialogController?.open()
            })
        }
        .columnStyle()
      }
      .width('100%')
      .id('pageCol')
    }
    .backgroundColor('#1a1459f7')
    .scrollBar(BarState.Off)
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%')
    .height('100%')
  }
}