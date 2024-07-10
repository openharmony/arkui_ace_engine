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

import { Drawer } from '../../components/Drawer';
import { RadioBlock, SliderBlock } from 'common';
import promptAction from '@ohos.promptAction';

@Component
export struct ButtonBootcamp {
  @State showParameters: boolean = false
  @State enableBtnType: boolean = false
  @State btnType: ButtonType = ButtonType.Capsule
  @State enableButtonStyle: boolean = false
  @State buttonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED
  @State enableControlSize: boolean = false
  @State controlSize: ControlSize = ControlSize.NORMAL
  @State enableStateEffect: boolean = false
  @State stateEffect: boolean = true
  @State enableOverFlow: boolean = false
  @State overflow: TextOverflow = TextOverflow.Clip
  @State enableMaxLines: boolean = false
  @State maxLines: number = 1
  @State enableCustomSize: boolean = false
  @State customSize: string = '64*40'
  @State enableBorderRadius: boolean = false
  @State btnBorderRadius: number = 30
  @State enableLabelNum: boolean = false
  @State labelNum: number = 2
  @State enableLabelTextSize: boolean = false
  @State labelTextSize: number = 16

  build() {
    NavDestination() {
      Drawer({
        title: '按钮/Button',
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
      Button(
        this.enableLabelNum ? '按钮'.repeat(this.labelNum / 2) : '按钮',
        {
          type: this.enableBtnType ? this.btnType : undefined,
          buttonStyle: this.enableButtonStyle ? this.buttonStyle : undefined,
          controlSize: this.enableControlSize ? this.controlSize : undefined,
        }
      )
        .stateEffect(this.enableStateEffect ? this.stateEffect : undefined)
        .labelStyle({
          overflow: this.enableOverFlow ? this.overflow : undefined,
          maxLines: this.enableMaxLines ? this.maxLines : undefined,
        })
        .width(this.enableCustomSize ? this.customSize.split('*')[0] : undefined)
        .height(this.enableCustomSize ? this.customSize.split('*')[1] : undefined)
        .borderRadius(this.enableBorderRadius ? this.btnBorderRadius : undefined)
        .fontSize(this.enableLabelTextSize ? this.labelTextSize : undefined)
        .onClick(() => {
          promptAction.showToast({
            message: '按钮被点击！'
          });
        })
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '按钮类型',
          isEnabled: $enableBtnType,
          value: $btnType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle }
          ]
        })


        RadioBlock({
          title: '按钮样式',
          isEnabled: $enableButtonStyle,
          value: $buttonStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: '按钮尺寸',
          isEnabled: $enableControlSize,
          value: $controlSize,
          dataSource: [
            { label: '正常尺寸', value: ControlSize.NORMAL },
            { label: '小尺寸', value: ControlSize.SMALL }
          ]
        })


        RadioBlock({
          title: '按压态效果',
          isEnabled: $enableStateEffect,
          value: $stateEffect,
          dataSource: [
            { label: '显示效果', value: true },
            { label: '关闭效果', value: false }
          ]
        })

        RadioBlock({
          title: '超长规则',
          isEnabled: $enableOverFlow,
          value: $overflow,
          dataSource: [
            { label: '省略号', value: TextOverflow.Ellipsis },
            { label: '跑马灯', value: TextOverflow.MARQUEE },
            { label: '截断', value: TextOverflow.Clip }
          ]
        })


        RadioBlock({
          title: '最大行数',
          isEnabled: $enableMaxLines,
          value: $maxLines,
          dataSource: [
            { label: '1', value: 1 },
            { label: '2', value: 2 }
          ]
        })


        RadioBlock({
          title: '自定义按钮尺寸',
          isEnabled: $enableCustomSize,
          value: $customSize,
          dataSource: [
            { label: '64x40', value: '64*40' },
            { label: '28x28', value: '28*28' },
            { label: '300x56', value: '300*56' }
          ]
        })

        SliderBlock({
          title: '普通按钮圆角尺寸(vp)',
          isEnabled: $enableBorderRadius,
          value: $btnBorderRadius,
          min: 0,
          max: 30
        })

        SliderBlock({
          title: 'Label字数',
          isEnabled: $enableLabelNum,
          value: $labelNum,
          step: 2,
          min: 0,
          max: 30
        })

        SliderBlock({
          title: 'Label文本尺寸(vp)',
          isEnabled: $enableLabelTextSize,
          value: $labelTextSize,
          min: 9,
          max: 36
        })

      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    ButtonBootcamp()
  }
}