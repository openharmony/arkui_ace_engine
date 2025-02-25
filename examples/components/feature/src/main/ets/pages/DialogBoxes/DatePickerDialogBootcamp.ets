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
import { RadioBlock, ColorBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct DatePickerDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  selectedDate: Date = new Date('2010-1-1');
  @State enableFormat: boolean = false;
  @State enableMilitaryTime: boolean = false;
  @State enableHourFormat: boolean = false;
  @State enableMinuteFormat: boolean = false;
  @State enableSecondFormat: boolean = false;
  @State isMilitaryTime: boolean = false;
  @State hourFormat: string = 'numeric';
  @State minuteFormat: string = '2-digit';
  @State secondFormat: string = '2-digit';
  @State enabledAcceptButtonType: boolean = false;
  @State acceptButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableAcceptButtonStyle: boolean = false;
  @State acceptButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableAcceptButtonRole: boolean = false;
  @State acceptButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableAcceptButtonFontSize: boolean = false;
  @State acceptButtonFontSize: Length = '16fp';
  @State enableAcceptButtonFontColor: boolean = false;
  @State acceptButtonFontColor: ResourceColor = '#ffffff';
  @State enableAcceptButtonFontWeight: boolean = false;
  @State acceptButtonFontWeight: FontWeight = 400;
  @State enableAcceptButtonFontStyle: boolean = false;
  @State acceptButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableAcceptButtonFontFamily: boolean = false;
  @State acceptButtonFontFamily: string = 'sans-serif';
  @State enableAcceptButtonBackGroundColor: boolean = false;
  @State acceptButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableAcceptButtonBorderRadius: boolean = false;
  @State acceptButtonBorderRadius: Length = 10;
  @State enabledCancelButtonType: boolean = false;
  @State cancelButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableCancelButtonStyle: boolean = false;
  @State cancelButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableCancelButtonRole: boolean = false;
  @State cancelButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableCancelButtonFontSize: boolean = false;
  @State cancelButtonFontSize: Length = '16fp';
  @State enableCancelButtonFontColor: boolean = false;
  @State cancelButtonFontColor: ResourceColor = '#ffffff';
  @State enableCancelButtonFontWeight: boolean = false;
  @State cancelButtonFontWeight: FontWeight = 400;
  @State enableCancelButtonFontStyle: boolean = false;
  @State cancelButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableCancelButtonFontFamily: boolean = false;
  @State cancelButtonFontFamily: string = 'sans-serif';
  @State enableCancelButtonBackGroundColor: boolean = false;
  @State cancelButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableCancelButtonBorderRadius: boolean = false;
  @State cancelButtonBorderRadius: Length = 10;
  @State enableLunar: boolean = false;
  @State lunar: boolean = false;
  @State enableLunarSwitch: boolean = false;
  @State lunarSwitch: boolean = false;
  @State enableShowTime: boolean = false;
  @State showTime: boolean = false;
  @State enableDisappearTextStyleColor: boolean = false;
  @State disappearTextStyleColor: ResourceColor = '#ff182431';
  @State enableDisappearTextStyleFontSize: boolean = false;
  @State disappearTextStyleFontSize: Length = '14fp';
  @State enableDisappearTextStyleFontWeight: boolean = false;
  @State disappearTextStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableTextStyleColor: boolean = false;
  @State textStyleColor: ResourceColor = '#ff182431';
  @State enableTextStyleFontSize: boolean = false;
  @State textStyleFontSize: Length = '16fp';
  @State enableTextStyleFontWeight: boolean = false;
  @State textStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableSelectedTextStyleColor: boolean = false;
  @State selectedTextStyleColor: ResourceColor = '#ff007dff';
  @State enableSelectedTextStyleFontSize: boolean = false;
  @State selectedTextStyleFontSize: Length = '20vp';
  @State enableSelectedTextStyleFontWeight: boolean = false;
  @State selectedTextStyleFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlignment: boolean = false;
  @State alignment: DialogAlignment = DialogAlignment.Default;
  @State enableOffsetDx: boolean = false;
  @State offsetDx: number = 0;
  @State enableOffsetDy: boolean = false;
  @State offsetDy: number = 0;
  @State enableMaskRectX: boolean = false;
  @State maskRectX: number = 0;
  @State enableMaskRectY: boolean = false;
  @State maskRectY: number = 0;
  @State enableMaskRectWidth: boolean = false;
  @State maskRectWidth: string = '100%';
  @State enableMaskRectHeight: boolean = false;
  @State maskRectHeight: string = '100%';
  @State enableDialogBackgroundColor: boolean = false;
  @State dialogBackgroundColor: ResourceColor = Color.Transparent;
  @State enableDialogBackgroundBlurStyle: boolean = false;
  @State dialogBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableDialogShadow: boolean = false;
  @State dialogShadow: ShadowStyle = ShadowStyle.OUTER_FLOATING_SM;
  @State enableHapticFeedback: boolean = false;
  @State isHapticFeedback: boolean = true;

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
      Button('弹出弹窗')
        .margin(20)
        .onClick(() => {
          DatePickerDialog.show({
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            selected: this.selectedDate,
            lunar: useEnabled(this.enableLunar, this.lunar),
            lunarSwitch: useEnabled(this.enableLunarSwitch, this.lunarSwitch),
            showTime: useEnabled(this.enableShowTime, this.showTime),
            useMilitaryTime: useEnabled(this.enableMilitaryTime, this.isMilitaryTime),
            enableHapticFeedback: useEnabled(this.enableHapticFeedback, this.isHapticFeedback),
            disappearTextStyle: {
              color: useEnabled(this.enableDisappearTextStyleColor, this.disappearTextStyleColor),
              font: {
                size: useEnabled(this.enableDisappearTextStyleFontSize, this.disappearTextStyleFontSize),
                weight: useEnabled(this.enableDisappearTextStyleFontWeight, this.disappearTextStyleFontWeight),
              }
            },
            textStyle: {
              color: useEnabled(this.enableTextStyleColor, this.textStyleColor),
              font: {
                size: useEnabled(this.enableTextStyleFontSize, this.textStyleFontSize),
                weight: useEnabled(this.enableTextStyleFontWeight, this.textStyleFontWeight),
              }
            },
            selectedTextStyle: {
              color: useEnabled(this.enableSelectedTextStyleColor, this.selectedTextStyleColor),
              font: {
                size: useEnabled(this.enableSelectedTextStyleFontSize, this.selectedTextStyleFontSize),
                weight: useEnabled(this.enableSelectedTextStyleFontWeight, this.selectedTextStyleFontWeight),
              }
            },
            acceptButtonStyle: {
              type: useEnabled(this.enabledAcceptButtonType, this.acceptButtonType),
              style: useEnabled(this.enableAcceptButtonStyle, this.acceptButtonStyle),
              role: useEnabled(this.enableAcceptButtonRole, this.acceptButtonRole),
              fontColor: useEnabled(this.enableAcceptButtonFontColor, this.acceptButtonFontColor),
              fontSize: useEnabled(this.enableAcceptButtonFontSize, this.acceptButtonFontSize),
              fontWeight: useEnabled(this.enableAcceptButtonFontWeight, this.acceptButtonFontWeight),
              fontStyle: useEnabled(this.enableAcceptButtonFontStyle, this.acceptButtonFontStyle),
              fontFamily: useEnabled(this.enableAcceptButtonFontFamily, this.acceptButtonFontFamily),
              backgroundColor: useEnabled(this.enableAcceptButtonBackGroundColor, this.acceptButtonBackGroundColor),
              borderRadius: useEnabled(this.enableAcceptButtonBorderRadius, this.acceptButtonBorderRadius),
            },
            cancelButtonStyle: {
              type: useEnabled(this.enabledCancelButtonType, this.cancelButtonType),
              style: useEnabled(this.enableCancelButtonStyle, this.cancelButtonStyle),
              role: useEnabled(this.enableCancelButtonRole, this.cancelButtonRole),
              fontColor: useEnabled(this.enableCancelButtonFontColor, this.cancelButtonFontColor),
              fontSize: useEnabled(this.enableCancelButtonFontSize, this.cancelButtonFontSize),
              fontWeight: useEnabled(this.enableCancelButtonFontWeight, this.cancelButtonFontWeight),
              fontStyle: useEnabled(this.enableCancelButtonFontStyle, this.cancelButtonFontStyle),
              fontFamily: useEnabled(this.enableCancelButtonFontFamily, this.cancelButtonFontFamily),
              backgroundColor: useEnabled(this.enableCancelButtonBackGroundColor, this.cancelButtonBackGroundColor),
              borderRadius: useEnabled(this.enableCancelButtonBorderRadius, this.cancelButtonBorderRadius),
            },
            alignment: useEnabled(this.enableAlignment, this.alignment),
            offset: {
              dx: useEnabled(this.enableOffsetDx, this.offsetDx),
              dy: useEnabled(this.enableOffsetDy, this.offsetDy),
            },
            maskRect: {
              x: useEnabled(this.enableMaskRectX, this.maskRectX),
              y: useEnabled(this.enableMaskRectY, this.maskRectY),
              width: useEnabled(this.enableMaskRectWidth, this.maskRectWidth),
              height: useEnabled(this.enableMaskRectHeight, this.maskRectHeight),
            },
            backgroundColor: useEnabled(this.enableDialogBackgroundColor, this.dialogBackgroundColor),
            backgroundBlurStyle: useEnabled(this.enableDialogBackgroundBlurStyle, this.dialogBackgroundBlurStyle),
            shadow: useEnabled(this.enableDialogShadow, this.dialogShadow),
            dateTimeOptions: {
              hour: useEnabled(this.enableHourFormat, this.hourFormat),
              minute: useEnabled(this.enableMinuteFormat, this.minuteFormat),
            },
            onDateAccept: (value: Date) => {
              this.selectedDate = value
              console.info('DatePickerDialog:onDateAccept()' + value.toString())
            },
            onCancel: () => {
              console.info('DatePickerDialog:onCancel()')
            },
            onDateChange: (value: Date) => {
              console.info('DatePickerDialog:onDateChange()' + value.toString())
            },
            onDidAppear: () => {
              console.info('DatePickerDialog:onDidAppear()')
            },
            onDidDisappear: () => {
              console.info('DatePickerDialog:onDidDisappear()')
            },
            onWillAppear: () => {
              console.info('DatePickerDialog:onWillAppear()')
            },
            onWillDisappear: () => {
              console.info('DatePickerDialog:onWillDisappear()')
            }
          })
        })
    }.width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '显示为农历',
          isEnabled: $enableLunar,
          value: $lunar,
          dataSource: [
            { label: '开启', value: true },
            { label: '关闭', value: false }
          ]
        })

        RadioBlock({
          title: '展示切换农历的开关',
          isEnabled: $enableLunarSwitch,
          value: $lunarSwitch,
          dataSource: [
            { label: '展示', value: true },
            { label: '隐藏', value: false }
          ]
        })

        RadioBlock({
          title: '展示时间项',
          isEnabled: $enableShowTime,
          value: $showTime,
          dataSource: [
            { label: '开启', value: true },
            { label: '关闭', value: false }
          ]
        })

        RadioBlock({
          title: '是否为24小时制',
          isEnabled: $enableMilitaryTime,
          value: $isMilitaryTime,
          dataSource: [
            { label: '24小时制', value: true },
            { label: '12小时制', value: false }
          ]
        })

        ColorBlock({
          title: '最上和最下两个选项的文本颜色',
          isEnabled: $enableDisappearTextStyleColor,
          color: $disappearTextStyleColor
        })

        RadioBlock({
          title: '最上和最下两个选项的文本字号',
          isEnabled: $enableDisappearTextStyleFontSize,
          value: $disappearTextStyleFontSize,
          dataSource: [
            { label: '小型', value: '12fp' },
            { label: '正常', value: '14fp' },
            { label: '大型', value: '20fp' },
          ]
        })

        RadioBlock({
          title: '最上和最下两个选项的文本字体粗细',
          isEnabled: $enableDisappearTextStyleFontWeight,
          value: $disappearTextStyleFontWeight,
          dataSource: [
            { label: '常规', value: FontWeight.Regular },
            { label: '中等', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: '除了最上、最下及选中项以外的文本颜色',
          isEnabled: $enableTextStyleColor,
          color: $textStyleColor
        })

        RadioBlock({
          title: '除了最上、最下及选中项以外的文本字号',
          isEnabled: $enableTextStyleFontSize,
          value: $textStyleFontSize,
          dataSource: [
            { label: '小型', value: '12fp' },
            { label: '正常', value: '16fp' },
            { label: '大型', value: '20fp' },
          ]
        })

        RadioBlock({
          title: '除了最上、最下及选中项以外的文本字体粗细',
          isEnabled: $enableTextStyleFontWeight,
          value: $textStyleFontWeight,
          dataSource: [
            { label: '常规', value: FontWeight.Regular },
            { label: '中等', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: '选中项的文本颜色',
          isEnabled: $enableSelectedTextStyleColor,
          color: $selectedTextStyleColor
        })

        RadioBlock({
          title: '选中项的文本字号',
          isEnabled: $enableSelectedTextStyleFontSize,
          value: $selectedTextStyleFontSize,
          dataSource: [
            { label: '小型', value: '12vp' },
            { label: '正常', value: '20vp' },
            { label: '大型', value: '30vp' },
          ]
        })

        RadioBlock({
          title: '选中项的文本字体粗细',
          isEnabled: $enableSelectedTextStyleFontWeight,
          value: $selectedTextStyleFontWeight,
          dataSource: [
            { label: '常规', value: FontWeight.Regular },
            { label: '中等', value: FontWeight.Medium },
          ]
        })

        RadioBlock({
          title: '确认按钮类型',
          isEnabled: this.enabledAcceptButtonType,
          value: this.acceptButtonType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '取消按钮类型',
          isEnabled: this.enabledCancelButtonType,
          value: this.cancelButtonType,
          dataSource: [
            { label: '胶囊按钮', value: ButtonType.Capsule },
            { label: '普通按钮', value: ButtonType.Normal },
            { label: '圆形按钮', value: ButtonType.Circle },
            { label: '圆角矩形按钮', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: '确认按钮样式',
          isEnabled: this.enableAcceptButtonStyle,
          value: this.acceptButtonStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: '取消按钮样式',
          isEnabled: this.enableCancelButtonStyle,
          value: this.cancelButtonStyle,
          dataSource: [
            { label: '强调型', value: ButtonStyleMode.EMPHASIZED },
            { label: '普通型', value: ButtonStyleMode.NORMAL },
            { label: '文本型', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: '确认按钮字体颜色',
          isEnabled: this.enableAcceptButtonFontColor,
          color: this.acceptButtonFontColor
        })

        ColorBlock({
          title: '取消按钮字体颜色',
          isEnabled: this.enableCancelButtonFontColor,
          color: this.cancelButtonFontColor
        })

        RadioBlock({
          title: '确认按钮角色',
          isEnabled: this.enableAcceptButtonRole,
          value: this.acceptButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: '取消按钮角色',
          isEnabled: this.enableCancelButtonRole,
          value: this.cancelButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: '确认按钮尺寸',
          isEnabled: this.enableAcceptButtonFontSize,
          value: this.acceptButtonFontSize,
          dataSource: [
            { label: '正常', value: '16fp' },
            { label: '小型', value: '12fp' },
          ]
        })

        RadioBlock({
          title: '取消按钮尺寸',
          isEnabled: this.enableCancelButtonFontSize,
          value: this.cancelButtonFontSize,
          dataSource: [
            { label: '正常', value: '16fp' },
            { label: '小型', value: '12fp' },
          ]
        })

        RadioBlock({
          title: '确认按钮字体粗细',
          isEnabled: this.enableAcceptButtonFontWeight,
          value: this.acceptButtonFontWeight,
          dataSource: [
            { label: '正常', value: 400 },
            { label: '加粗', value: 800 },
          ]
        })

        RadioBlock({
          title: '取消按钮字体粗细',
          isEnabled: this.enableCancelButtonFontWeight,
          value: this.cancelButtonFontWeight,
          dataSource: [
            { label: '正常', value: 400 },
            { label: '加粗', value: 800 },
          ]
        })

        RadioBlock({
          title: '确认按钮字体样式',
          isEnabled: this.enableAcceptButtonFontStyle,
          value: this.acceptButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: '取消按钮字体样式',
          isEnabled: this.enableCancelButtonFontStyle,
          value: this.cancelButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: '确认按钮背景颜色',
          isEnabled: this.enableAcceptButtonBackGroundColor,
          color: this.acceptButtonBackGroundColor
        })

        ColorBlock({
          title: '取消按钮背景颜色',
          isEnabled: this.enableCancelButtonBackGroundColor,
          color: this.cancelButtonBackGroundColor
        })

        RadioBlock({
          title: '确认按钮边框圆角半径',
          isEnabled: this.enableAcceptButtonBorderRadius,
          value: this.acceptButtonBorderRadius,
          dataSource: [
            { label: '正常', value: 10 },
            { label: '较大', value: 100 },
          ]
        })

        RadioBlock({
          title: '取消按钮边框圆角半径',
          isEnabled: this.enableCancelButtonBorderRadius,
          value: this.cancelButtonBorderRadius,
          dataSource: [
            { label: '正常', value: 10 },
            { label: '较大', value: 100 },
          ]
        })

        RadioBlock({
          title: '弹窗在竖直方向上的对齐方式',
          isEnabled: $enableAlignment,
          value: $alignment,
          dataSource: [
            { label: '顶部', value: DialogAlignment.Top },
            { label: '中心', value: DialogAlignment.Center },
            { label: '底部', value: DialogAlignment.Bottom },
            { label: '默认', value: DialogAlignment.Default }
          ]
        })

        SliderBlock({
          title: '弹窗相对alignment所在位置的偏移量：x',
          isEnabled: $enableOffsetDx,
          value: $offsetDx,
          min: -40,
          max: 40
        })

        SliderBlock({
          title: '弹窗相对alignment所在位置的偏移量：y',
          isEnabled: $enableOffsetDy,
          value: $offsetDy,
          min: -100,
          max: 100
        })

        SliderBlock({
          title: '弹窗遮蔽层区域偏移量：x',
          isEnabled: $enableMaskRectX,
          value: $maskRectX,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: '弹窗遮蔽层区域偏移量：y',
          isEnabled: $enableMaskRectY,
          value: $maskRectY,
          min: 0,
          max: 400
        })

        RadioBlock({
          title: '弹窗遮蔽层区域：宽度比例',
          isEnabled: $enableMaskRectWidth,
          value: $maskRectWidth,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '100%', value: '100%' }
          ]
        })

        RadioBlock({
          title: '弹窗遮蔽层区域：高度比例',
          isEnabled: $enableMaskRectHeight,
          value: $maskRectHeight,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '100%', value: '100%' }
          ]
        })

        ColorBlock({
          title: '弹窗背板颜色',
          isEnabled: $enableDialogBackgroundColor,
          color: $dialogBackgroundColor
        })

        RadioBlock({
          title: '弹窗背板模糊材质',
          isEnabled: $enableDialogBackgroundBlurStyle,
          value: $dialogBackgroundBlurStyle,
          dataSource: [
            { label: '薄型', value: BlurStyle.Thin },
            { label: '组件超厚', value: BlurStyle.COMPONENT_ULTRA_THICK }
          ]
        })

        RadioBlock({
          title: '弹窗背板阴影',
          isEnabled: $enableDialogShadow,
          value: $dialogShadow,
          dataSource: [
            { label: '外部浮动MD', value: ShadowStyle.OUTER_FLOATING_MD },
            { label: '外部浮动SM', value: ShadowStyle.OUTER_FLOATING_SM }
          ]
        })

        RadioBlock({
          title: '小时是否有前导0',
          isEnabled: this.enableHourFormat,
          value: this.hourFormat,
          dataSource: [
            { label: '有前导0', value: '2-digit' },
            { label: '无前导0', value: 'numeric' },
          ]
        })

        RadioBlock({
          title: '分钟是否有前导0',
          isEnabled: this.enableMinuteFormat,
          value: this.minuteFormat,
          dataSource: [
            { label: '有前导0', value: '2-digit' },
            { label: '无前导0', value: 'numeric' },
          ]
        })

        RadioBlock({
          title: '是否开启音效震动',
          isEnabled: this.enableHapticFeedback,
          value: this.isHapticFeedback,
          dataSource: [
            { label: '开启', value: true },
            { label: '关闭', value: false },
          ]
        })
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct DatePickerDialogBootcampPreviewer {
  build() {
    DatePickerDialogBootcamp({
      title: '日期选择器弹窗/DatepickerDialog'
    })
  }
}