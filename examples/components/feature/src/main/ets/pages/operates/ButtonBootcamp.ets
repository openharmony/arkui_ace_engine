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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
import promptAction from '@ohos.promptAction';

@Component
export struct ButtonBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableBtnType: boolean = false;
  @State btnType: ButtonType = ButtonType.Capsule;
  @State enableButtonStyle: boolean = false;
  @State buttonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableControlSize: boolean = false;
  @State controlSize: ControlSize = ControlSize.NORMAL;
  @State enableStateEffect: boolean = false;
  @State stateEffect: boolean = true;
  @State enableOverFlow: boolean = false;
  @State overflow: TextOverflow = TextOverflow.Clip;
  @State enableMaxLines: boolean = false;
  @State maxLines: number = 1;
  @State enableCustomWidth: boolean = false;
  @State customWidth: number = 64;
  @State enableCustomHeight: boolean = false;
  @State customHeight: number = 40;
  @State enableBorderRadius: boolean = false;
  @State btnBorderRadius: number = 30;
  @State enableLabelNum: boolean = false;
  @State labelNum: number = 2;
  @State enableLabelTextSize: boolean = false;
  @State labelTextSize: number = 16;
  @State enableFontColor: boolean = false;
  @State btnFontColor: ResourceColor = $r('sys.color.font_on_primary');
  @State enableRole: boolean = false;
  @State btnRole: ButtonRole = ButtonRole.NORMAL;

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
      Button(
        this.enableLabelNum ? '按钮'.repeat(this.labelNum / 2) : '按钮',
        {
          type: useEnabled(this.enableBtnType, this.btnType),
          buttonStyle: useEnabled(this.enableButtonStyle, this.buttonStyle),
          controlSize: useEnabled(this.enableControlSize, this.controlSize),
          role: useEnabled(this.enableRole, this.btnRole)
        }
      )
        .fontColor(useEnabled(this.enableFontColor, this.btnFontColor))
        .stateEffect(useEnabled(this.enableStateEffect, this.stateEffect))
        .labelStyle({
          overflow: useEnabled(this.enableOverFlow, this.overflow),
          maxLines: useEnabled(this.enableMaxLines, this.maxLines),
        })
        .width(useEnabled(this.enableCustomWidth, this.customWidth))
        .height(useEnabled(this.enableCustomHeight, this.customHeight))
        .borderRadius(useEnabled(this.enableBorderRadius, this.btnBorderRadius))
        .fontSize(useEnabled(this.enableLabelTextSize, this.labelTextSize))
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
              { label: '圆形按钮', value: ButtonType.Circle },
              { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
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

        SliderBlock({
          title: '自定义按钮宽度',
          isEnabled: $enableCustomWidth,
          value: $customWidth,
          min: 20,
          max: 80
        })

        SliderBlock({
          title: '自定义按钮高度',
          isEnabled: $enableCustomHeight,
          value: $customHeight,
          min: 20,
          max: 80
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

        ColorBlock({
          title: '字体颜色',
          isEnabled: $enableFontColor,
          color: $btnFontColor
        })

        RadioBlock({
          title: '设置按钮角色',
          isEnabled: $enableRole,
          value: $btnRole,
          dataSource: [
            { label: '正常按钮', value: ButtonRole.NORMAL },
            { label: '警示按钮', value: ButtonRole.ERROR },
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    ButtonBootcamp({
      title: '按钮/Button'
    })
  }
}