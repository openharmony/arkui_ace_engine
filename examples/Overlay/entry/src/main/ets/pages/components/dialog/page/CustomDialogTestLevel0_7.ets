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

import { MyComponent } from '../../../../common/MyComponent'
import {CustomDialogExample, CustomDialog_Blur} from '../../../../common/CustomDialogController'


@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(5).padding(5)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct CustomDialogTestLevel0_7 {
  scroller: Scroller = new Scroller()

  //
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialog_Blur({
      textValue: $textValue,
      inputValue: $inputValue
    }),
  })


  build() {
    Scroll(this.scroller){
      Column({space: 5}) {
        Text(`验证弹窗模糊属性的绘制效果`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`弹窗模糊效果设置`)
            .paramTextStyle()
          Select([
            { value:'子窗True/蒙层False/不设置模糊效果' },
            { value:'子窗False/蒙层False/不设置模糊效果' },
            { value:'子窗True/蒙层False/设置模糊效果' },
            { value:'子窗False/蒙层False/设置模糊效果' },

            { value:'customStyle为True/设置模糊效果' },
            { value:'customStyle为False/设置模糊效果' },

            // 子窗True/蒙层False, 设置inactiveColor为orange
            { value:'设置bgBlurOpt.policy为follows' },
            { value:'设置bgBlurOpt.policy为active' },
            { value:'设置bgBlurOpt.policy为UN' },
            { value:'设置bgBlurOpt.policy为inactive' },
            // 子窗True/蒙层False, policy设置follow类型
            { value:'不设置bgBlurOpt.inActColor' },
            { value:'colorMode为SYSTEM/inActColor为UN' },
            { value:'scale为0.5/inActColor为str正常' },
            { value:'adaColor为DEFAULT/inActColor为str异常' },
            { value:'adaColor为AVERAGE/inActColor为res异常' },

            // 子窗True/蒙层False, effectOpt设置不同参数
            { value:'设置bgEffect为UN' },
            { value:'bgEffect设置R角为8' },
            { value:'bgEffect设置饱和度0.5' },
            { value:'bgEffect设置亮度2' },
            { value:'bgEffect设置AVERAGE颜色' },
            { value:'bgEffect设置DEFAULT颜色' },
            { value:'bgEffect设置灰阶0/127' },
            { value:'bgEffect设置灰阶127/0' },
            { value:'bgEffect设置激活策略' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '子窗True/蒙层False/不设置模糊效果':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                })
                  break;
                case '子窗False/蒙层False/不设置模糊效果':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: false,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '子窗True/蒙层False/设置模糊效果':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: true,
                    isModal: false,

                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: Color.Green,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange,
                    },

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '子窗False/蒙层False/设置模糊效果':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: false,
                    isModal: false,

                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: Color.Green,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange,
                    },

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;

                case 'customStyle为True/设置模糊效果':
                  new CustomDialogController({
                    showInSubWindow: true,
                    isModal: false,
                    customStyle: true,

                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: Color.Green,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange,
                    },

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'customStyle为False/设置模糊效果':
                  new CustomDialogController({
                    showInSubWindow: true,
                    isModal: false,
                    customStyle: false,

                    backgroundBlurStyle: BlurStyle.Thin,
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: '#A5D61D'
                    },
                    backgroundEffect: {
                      radius: 8,
                      saturation: 4,
                      brightness: 0.5,
                      color: Color.Green,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [0, 64],
                      },
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange,
                    },

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                  
                case '设置bgBlurOpt.policy为follows':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '设置bgBlurOpt.policy为active':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      inactiveColor: Color.Orange
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '设置bgBlurOpt.policy为UN':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: undefined,
                      inactiveColor: Color.Orange
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '设置bgBlurOpt.policy为inactive':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: Color.Orange
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case '不设置bgBlurOpt.inActColor':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'colorMode为SYSTEM/inActColor为UN':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      colorMode: ThemeColorMode.SYSTEM,
                      inactiveColor: undefined
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'scale为0.5/inActColor为str正常':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      scale: 0.5,
                      inactiveColor: '#ff4cbfb7'
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'adaColor为DEFAULT/inActColor为str异常':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      inactiveColor: 'Color.Red'
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'adaColor为AVERAGE/inActColor为res异常':
                  this.dialogController = new CustomDialogController({
                    backgroundBlurStyleOptions: {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      adaptiveColor: AdaptiveColor.AVERAGE,
                      inactiveColor: $r('app.string.module_desc')
                    },
                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;

                case '设置bgEffect为UN':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: undefined,

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置R角为8':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置饱和度0.5':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      saturation: 0.5
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置亮度2':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      brightness: 2
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置AVERAGE颜色':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      color: '#739dff00',
                      adaptiveColor: AdaptiveColor.AVERAGE
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置DEFAULT颜色':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      color: '#739dff00',
                      adaptiveColor: AdaptiveColor.DEFAULT
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置灰阶0/127':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      blurOptions: {grayscale: [0, 127]}
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置灰阶127/0':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      blurOptions: {grayscale: [127, 0]}
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;
                case 'bgEffect设置激活策略':
                  this.dialogController = new CustomDialogController({
                    backgroundEffect: {
                      radius: 8,
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Orange
                    },

                    showInSubWindow: true,
                    isModal: false,

                    builder: CustomDialog_Blur({
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                  })
                  break;

              }
            })
            .key('select_bgBlur')
          Text(`自定义弹窗：模糊效果`)
            .componentTextStyle()
            .onClick( () => {
              this.dialogController?.open()
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .backgroundColor('#D2CAB3')
    .scrollBar(BarState.Off)
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}