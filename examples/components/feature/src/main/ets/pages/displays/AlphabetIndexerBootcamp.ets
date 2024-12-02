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
import { ColorBlock, RadioBlock, SliderBlock} from 'common';

@Component
export struct AlphabetIndexerBootcamp {
  private value: string[] = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z']
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableAlphabetIndexerColor: boolean = false
  @State alphabetIndexerColor: ResourceColor = '0x99182431';
  @State enableAlphabetIndexerSelectedColor: boolean = false;
  @State alphabetIndexerSelectedColor: ResourceColor = '0xFF007DFF';
  @State enableAlphabetIndexerPopupColor: boolean = false;
  @State alphabetIndexerPopupColor: ResourceColor = '0xFF007DFF';
  @State enableAlphabetIndexerSelectedBackgroundColor: boolean = false;
  @State alphabetIndexerSelectedBackgroundColor: ResourceColor = '0x1A007DFF';
  @State enableAlphabetIndexerPopupBackground: boolean = false;
  @State alphabetIndexerPopupBackground: ResourceColor = '#66808080';
  @State enableAlphabetIndexerUsingPopup: boolean = false;
  @State alphabetIndexerUsingPopup: boolean = false;
  @State enableAlphabetIndexerSelectedFontSize: boolean = false;
  @State alphabetIndexerSelectedFontSize: number = 10;
  @State enableAlphabetIndexerSelectedFontStyle: boolean = false;
  @State alphabetIndexerSelectedFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerSelectedFontWeight: boolean = false;
  @State alphabetIndexerSelectedFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerPopupFontSize: boolean = false;
  @State alphabetIndexerPopupFontSize: number = 24;
  @State enableAlphabetIndexerPopupFontStyle: boolean = false;
  @State alphabetIndexerPopupFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerPopupFontWeight: boolean = false;
  @State alphabetIndexerPopupFontWeight: FontWeight = FontWeight.Normal;
  @State enableAlphabetIndexerFontSize: boolean = false;
  @State alphabetIndexerFontSize: number = 10;
  @State enableAlphabetIndexerFontStyle: boolean = false;
  @State alphabetIndexerFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerFontWeight: boolean = false;
  @State alphabetIndexerFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerItemSize: boolean = false;
  @State alphabetIndexerItemSize: number = 16;
  @State enableAlphabetIndexerAlignStyleIndexerAlign: boolean = false;
  @State alphabetIndexerAlignStyleIndexerAlign: IndexerAlign = IndexerAlign.END;
  @State enableAlphabetIndexerAlignStyleLength: boolean = false;
  @State alphabetIndexerAlignStyleLength: number = 0;
  @State enableAlphabetIndexerSelected: boolean = false;
  @State alphabetIndexerSelected: number = 0;
  @State enableAlphabetIndexerPopupPositionX: boolean = false;
  @State alphabetIndexerPopupPositionX: number = 60;
  @State enableAlphabetIndexerPopupPositionY: boolean = false;
  @State alphabetIndexerPopupPositionY: number = 48;
  @State enableAlphabetIndexerPopupSelectedColor: boolean = false;
  @State alphabetIndexerPopupSelectedColor: ResourceColor = '#FF182431';
  @State enableAlphabetIndexerPopupUnselectedColor: boolean = false;
  @State alphabetIndexerPopupUnselectedColor: ResourceColor = '#FF182431';
  @State enableAlphabetIndexerPopupItemFontSize: boolean = false;
  @State alphabetIndexerPopupItemFontSize: number = 24;
  @State enableAlphabetIndexerPopupItemFontStyle: boolean = false;
  @State alphabetIndexerPopupItemFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerPopupItemFontWeight: boolean = false;
  @State alphabetIndexerPopupItemFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerPopupItemBackgroundColor: boolean = false;
  @State alphabetIndexerPopupItemBackgroundColor: ResourceColor = '#00000000';
  @State enableAlphabetIndexerAutoCollapse: boolean = false;
  @State alphabetIndexerAutoCollapse: boolean = true;
  @State enableAlphabetIndexerPopupItemBorderRadius: boolean = false;
  @State alphabetIndexerPopupItemBorderRadius: number = 24;
  @State enableAlphabetIndexerItemBorderRadius: boolean = false;
  @State alphabetIndexerItemBorderRadius: number = 8;
  @State enableAlphabetIndexerPopupBackgroundBlurStyle: boolean = false;
  @State alphabetIndexerPopupBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_REGULAR;
  @State enableAlphabetIndexerPopupTitleBackground: boolean = false;
  @State alphabetIndexerPopupTitleBackground: ResourceColor = '#0c182431';
  @State enableAlphabetIndexerEnableHapticFeedback: boolean = false;
  @State alphabetIndexerEnableHapticFeedback: boolean = true;

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
      AlphabetIndexer({ arrayValue: this.value, selected: 0 })
        .color(this.alphabetIndexerColor)
        .selectedColor(this.alphabetIndexerSelectedColor)
        .popupColor(this.alphabetIndexerPopupColor)
        .selectedBackgroundColor(this.alphabetIndexerSelectedBackgroundColor)
        .popupBackground(this.alphabetIndexerPopupBackground)
        .usingPopup(this.alphabetIndexerUsingPopup)
        .selectedFont({ size: this.alphabetIndexerSelectedFontSize,
          style: this.alphabetIndexerSelectedFontStyle, weight: this.alphabetIndexerSelectedFontWeight })
        .popupFont({ size: this.alphabetIndexerPopupFontSize,
          style: this.alphabetIndexerPopupFontStyle, weight: this.alphabetIndexerPopupFontWeight })
        .font({ size: this.alphabetIndexerFontSize,
          style: this.alphabetIndexerFontStyle, weight: this.alphabetIndexerFontWeight })
        .itemSize(this.alphabetIndexerItemSize)
        .alignStyle(this.alphabetIndexerAlignStyleIndexerAlign, this.alphabetIndexerAlignStyleLength)
        .selected(this.alphabetIndexerSelected)
        .popupPosition({x: this.alphabetIndexerPopupPositionX, y: this.alphabetIndexerPopupPositionY})
        .popupSelectedColor(this.alphabetIndexerPopupSelectedColor)
        .popupUnselectedColor(this.alphabetIndexerPopupUnselectedColor)
        .popupItemFont({size: this.alphabetIndexerPopupItemFontSize,
          style: this.alphabetIndexerPopupItemFontStyle,
          weight: this.alphabetIndexerPopupItemFontWeight})
        .popupItemBackgroundColor(this.alphabetIndexerPopupItemBackgroundColor)
        .autoCollapse(this.alphabetIndexerAutoCollapse)
        .popupItemBorderRadius(this.alphabetIndexerPopupItemBorderRadius)
        .itemBorderRadius(this.alphabetIndexerItemBorderRadius)
        .popupBackgroundBlurStyle(this.alphabetIndexerPopupBackgroundBlurStyle)
        .popupTitleBackground(this.alphabetIndexerPopupTitleBackground)
        .enableHapticFeedback(this.alphabetIndexerEnableHapticFeedback)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        ColorBlock({
          title: '未选中项文本颜色',
          isEnabled: this.enableAlphabetIndexerColor,
          color: this.alphabetIndexerColor
        })
        ColorBlock({
          title: '选中项文本颜色',
          isEnabled: this.enableAlphabetIndexerSelectedColor,
          color: this.alphabetIndexerSelectedColor
        })
        ColorBlock({
          title: '提示弹窗一级索引项文本颜色',
          isEnabled: this.enableAlphabetIndexerPopupColor,
          color: this.alphabetIndexerPopupColor
        })
        ColorBlock({
          title: '选中项背景颜色',
          isEnabled: this.enableAlphabetIndexerSelectedBackgroundColor,
          color: this.alphabetIndexerSelectedBackgroundColor
        })
        ColorBlock({
          title: '提示弹窗背景颜色',
          isEnabled: this.enableAlphabetIndexerPopupBackground,
          color: this.alphabetIndexerPopupBackground
        })
        RadioBlock({
          title: '是否使用自定义item',
          isEnabled: this.enableAlphabetIndexerUsingPopup,
          value: this.alphabetIndexerUsingPopup,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        SliderBlock({
          title: '选中项文本大小',
          isEnabled: this.enableAlphabetIndexerSelectedFontSize,
          value: this.alphabetIndexerSelectedFontSize,
          min: 4,
          max: 16
        })
        RadioBlock({
          title: '选中项文本样式',
          isEnabled: this.enableAlphabetIndexerSelectedFontStyle,
          value: this.alphabetIndexerSelectedFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: '选中项文本粗细',
          isEnabled: this.enableAlphabetIndexerSelectedFontWeight,
          value: this.alphabetIndexerSelectedFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: '提示弹窗一级索引文本大小',
          isEnabled: this.enableAlphabetIndexerPopupFontSize,
          value: this.alphabetIndexerPopupFontSize,
          min: 12,
          max: 32
        })
        RadioBlock({
          title: '提示弹窗一级索引文本样式',
          isEnabled: this.enableAlphabetIndexerPopupFontStyle,
          value: this.alphabetIndexerPopupFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: '提示弹窗一级索引文本粗细',
          isEnabled: this.enableAlphabetIndexerPopupFontWeight,
          value: this.alphabetIndexerPopupFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: '未选中项文本大小',
          isEnabled: this.enableAlphabetIndexerFontSize,
          value: this.alphabetIndexerFontSize,
          min: 4,
          max: 16
        })
        RadioBlock({
          title: '未选中项文本样式',
          isEnabled: this.enableAlphabetIndexerFontStyle,
          value: this.alphabetIndexerFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: '未选中项文本粗细',
          isEnabled: this.enableAlphabetIndexerFontWeight,
          value: this.alphabetIndexerFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: '索引项区域大小',
          isEnabled: this.enableAlphabetIndexerItemSize,
          value: this.alphabetIndexerItemSize,
          min: 12,
          max: 32
        })
        RadioBlock({
          title: '索引条提示弹窗的对齐样式',
          isEnabled: this.enableAlphabetIndexerAlignStyleIndexerAlign,
          value: this.alphabetIndexerAlignStyleIndexerAlign,
          dataSource: [
            { label: 'Left', value: IndexerAlign.Left },
            { label: 'Right', value: IndexerAlign.Right },
            { label: 'START', value: IndexerAlign.START },
            { label: 'END', value: IndexerAlign.END },
          ]
        })
        SliderBlock({
          title: '索引条提示弹窗的对齐偏移',
          isEnabled: this.enableAlphabetIndexerAlignStyleLength,
          value: this.alphabetIndexerAlignStyleLength,
          min: 0,
          max: 50
        })
        SliderBlock({
          title: '选中项索引值',
          isEnabled: this.enableAlphabetIndexerSelected,
          value: this.alphabetIndexerSelected,
          min: 0,
          max: this.value.length
        })
        SliderBlock({
          title: '弹出窗口相对于索引条上边框中点的位置X',
          isEnabled: this.enableAlphabetIndexerPopupPositionX,
          value: this.alphabetIndexerPopupPositionX,
          min: 30,
          max: 90
        })
        SliderBlock({
          title: '弹出窗口相对于索引条上边框中点的位置Y',
          isEnabled: this.enableAlphabetIndexerPopupPositionY,
          value: this.alphabetIndexerPopupPositionY,
          min: 24,
          max: 72
        })
        ColorBlock({
          title: '提示弹窗二级索引选中项文本颜色',
          isEnabled: this.enableAlphabetIndexerPopupSelectedColor,
          color: this.alphabetIndexerPopupSelectedColor
        })
        ColorBlock({
          title: '提示弹窗二级索引未选中项文本颜色',
          isEnabled: this.enableAlphabetIndexerPopupUnselectedColor,
          color: this.alphabetIndexerPopupUnselectedColor
        })
        SliderBlock({
          title: '提示弹窗二级索引项文本大小',
          isEnabled: this.enableAlphabetIndexerPopupItemFontSize,
          value: this.alphabetIndexerPopupItemFontSize,
          min: 4,
          max: 16
        })
        RadioBlock({
          title: '提示弹窗二级索引项文本样式',
          isEnabled: this.enableAlphabetIndexerPopupItemFontStyle,
          value: this.alphabetIndexerPopupItemFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: '提示弹窗二级索引项文本粗细',
          isEnabled: this.enableAlphabetIndexerPopupItemFontStyle,
          value: this.alphabetIndexerPopupItemFontStyle,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        ColorBlock({
          title: '提示弹窗二级索引项背景颜色',
          isEnabled: this.enableAlphabetIndexerPopupItemBackgroundColor,
          color: this.alphabetIndexerPopupItemBackgroundColor
        })
        RadioBlock({
          title: '是否使用自适应折叠模式',
          isEnabled: this.enableAlphabetIndexerAutoCollapse,
          value: this.alphabetIndexerAutoCollapse,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        SliderBlock({
          title: '提示弹窗索引项背板圆角半径',
          isEnabled: this.enableAlphabetIndexerPopupItemBorderRadius,
          value: this.alphabetIndexerPopupItemBorderRadius,
          min: 0,
          max: 48
        })
        SliderBlock({
          title: '索引项背板圆角半径',
          isEnabled: this.enableAlphabetIndexerItemBorderRadius,
          value: this.alphabetIndexerItemBorderRadius,
          min: 0,
          max: 16
        })
        RadioBlock({
          title: '提示弹窗的背景模糊材质',
          isEnabled: this.enableAlphabetIndexerPopupBackgroundBlurStyle,
          value: this.alphabetIndexerPopupBackgroundBlurStyle,
          dataSource: [
            { label: '轻薄材质模糊', value: BlurStyle.Thin },
            { label: '普通厚度材质模糊', value: BlurStyle.Regular },
            { label: '厚材质模糊', value: BlurStyle.Thick },
            { label: '近距景深模糊', value: BlurStyle.BACKGROUND_THIN },
            { label: '中距景深模糊', value: BlurStyle.BACKGROUND_REGULAR },
            { label: '远距景深模糊', value: BlurStyle.BACKGROUND_THICK },
            { label: '超远距景深模糊', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: '关闭模糊', value: BlurStyle.NONE },
            { label: '组件超轻薄材质模糊', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: '组件轻薄材质模糊', value: BlurStyle.COMPONENT_THIN },
            { label: '组件普通材质模糊', value: BlurStyle.COMPONENT_REGULAR },
            { label: '组件厚材质模糊', value: BlurStyle.COMPONENT_THICK },
            { label: '组件超厚材质模糊', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })
        ColorBlock({
          title: '提示弹窗一级索引项背景颜色',
          isEnabled: this.enableAlphabetIndexerPopupTitleBackground,
          color: this.alphabetIndexerPopupTitleBackground
        })
        RadioBlock({
          title: '是否使用触控反馈',
          isEnabled: this.enableAlphabetIndexerEnableHapticFeedback,
          value: this.alphabetIndexerEnableHapticFeedback,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
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
    AlphabetIndexerBootcamp({
      title: '索引条/AlphabetIndexerBootcamp'
    })
  }
}