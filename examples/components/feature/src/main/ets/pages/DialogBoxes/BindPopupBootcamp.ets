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
import { formatDate } from 'common/src/main/ets/utils/timeUtil';
import { BlockTag } from 'common/src/main/ets/model/BlockTag';

@Component
export struct BindPopupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State handlePopup: boolean = false;
  @State enableCompPopupType: boolean = true;
  @State compPopupType: number = 0;
  @State compPopupAvoidTargetMessage: string = (() => {
    const baseText = 'This is a popup with AvoidanceMode.AVOID_AROUND_TARGET. ';
    return Array(40).fill(baseText).join('');
  })();
  @State enableCompBindPopupArrowOffset: boolean = false;
  @State compBindPopupArrowOffset: number = 0;
  @State enableCompBindPopupShowInSubWindow: boolean = false;
  @State compBindPopupShowInSubWindow: boolean = true;
  @State enableCompBindPopupMaskType: boolean = false;
  @State compBindPopupMaskType: boolean = true;
  @State enableCompBindPopupMaskBoolean: boolean = false;
  @State compBindPopupMaskBoolean: boolean = true;
  @State enableCompBindPopupMaskColor: boolean = false;
  @State compBindPopupMaskColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupMessageOptionsTextColor: boolean = false;
  @State compBindPopupMessageOptionsTextColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupMessageOptionsFontSize: boolean = false;
  @State compBindPopupMessageOptionsFontSize: number = 16;
  @State enableCompBindPopupMessageOptionsFontWeight: boolean = false;
  @State compBindPopupMessageOptionsFontWeight: FontWeight = FontWeight.Normal;
  @State enableCompBindPopupMessageOptionsFontStyle: boolean = false;
  @State compBindPopupMessageOptionsFontStyle: FontStyle = FontStyle.Normal;
  @State enableCompBindPopupTargetSpace: boolean = false;
  @State compBindPopupTargetSpace: number = 0;
  @State enableCompBindPopupPlacement: boolean = false;
  @State compBindPopupPlacement: Placement = Placement.Bottom;
  @State enableCompBindPopupAvoidTarget: boolean = false;
  @State compBindPopupAvoidTarget: AvoidanceMode = AvoidanceMode.COVER_TARGET;
  @State enableCompBindPopupOffsetX: boolean = false;
  @State compBindPopupOffsetX: number = 0;
  @State enableCompBindPopupOffsetY: boolean = false;
  @State compBindPopupOffsetY: number = 0;
  @State enableCompBindPopupEnableArrow: boolean = false;
  @State compBindPopupEnableArrow: boolean = true;
  @State enableCompBindPopupPopupColor: boolean = false;
  @State compBindPopupPopupColor: ResourceStr = '#ff000000';
  @State enableCompBindPopupAutoCancel: boolean = false;
  @State compBindPopupAutoCancel: boolean = true;
  @State enableCompBindPopupWidth: boolean = false;
  @State compBindPopupWidth: number = 0;
  @State enableCompBindPopupArrowPointPosition: boolean = false;
  @State compBindPopupArrowPointPosition: ArrowPointPosition = ArrowPointPosition.CENTER;
  @State enableCompBindPopupArrowWidth: boolean = false;
  @State compBindPopupArrowWidth: number = 16;
  @State enableCompBindPopupArrowHeight: boolean = false;
  @State compBindPopupArrowHeight: number = 8;
  @State enableCompBindPopupRadius: boolean = false;
  @State compBindPopupRadius: number = 20;
  @State enableCompBindPopupShadowType: boolean = false;
  @State compBindPopupShadowType: boolean = true;
  @State enableCompBindPopupShadowStyle: boolean = false;
  @State compBindPopupShadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;
  @State enableCompBindPopupShadowOptionsRadius: boolean = false;
  @State compBindPopupShadowOptionsRadius: number = 0;
  @State enableCompBindPopupShadowOptionsType: boolean = false;
  @State compBindPopupShadowOptionsType: ShadowType = ShadowType.COLOR;
  @State enableCompBindPopupShadowOptionsColor: boolean = false;
  @State compBindPopupShadowOptionsColor: ResourceColor = '#ff000000';
  @State enableCompBindPopupShadowOptionsOffsetX: boolean = false;
  @State compBindPopupShadowOptionsOffsetX: number = 0;
  @State enableCompBindPopupShadowOptionsOffsetY: boolean = false;
  @State compBindPopupShadowOptionsOffsetY: number = 0;
  @State enableCompBindPopupShadowOptionsFill: boolean = false;
  @State compBindPopupShadowOptionsFill: boolean = false;
  @State enableCompBindPopupBackgroundBlurStyle: boolean = false;
  @State compBindPopupBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableTransitionTransitionEffect: boolean = false;
  @State transitionTransitionEffect: TransitionEffect = TransitionEffect.IDENTITY;
  @State enableCompBindPopupTransitionOpacity: boolean = false;
  @State compBindPopupTransitionOpacity: number = 1;
  @State enableCompBindPopupTransitionTranslateX: boolean = false;
  @State compBindPopupTransitionTranslateX: number = 0;
  @State enableCompBindPopupTransitionTranslateY: boolean = false;
  @State compBindPopupTransitionTranslateY: number = 0;
  @State enableCompBindPopupTransitionTranslateZ: boolean = false;
  @State compBindPopupTransitionTranslateZ: number = 0;
  @State enableCompBindPopupTransitionScaleX: boolean = false;
  @State compBindPopupTransitionScaleX: number = 0;
  @State enableCompBindPopupTransitionScaleY: boolean = false;
  @State compBindPopupTransitionScaleY: number = 0;
  @State enableCompBindPopupTransitionScaleZ: boolean = false;
  @State compBindPopupTransitionScaleZ: number = 0;
  @State enableCompBindPopupTransitionScaleCenterX: boolean = false;
  @State compBindPopupTransitionScaleCenterX: number = 0;
  @State enableCompBindPopupTransitionScaleCenterY: boolean = false;
  @State compBindPopupTransitionScaleCenterY: number = 0;
  @State enableCompBindPopupTransitionRotateX: boolean = false;
  @State compBindPopupTransitionRotateX: number = 0;
  @State enableCompBindPopupTransitionRotateY: boolean = false;
  @State compBindPopupTransitionRotateY: number = 0;
  @State enableCompBindPopupTransitionRotateZ: boolean = false;
  @State compBindPopupTransitionRotateZ: number = 0;
  @State enableCompBindPopupTransitionRotateAngle: boolean = false;
  @State compBindPopupTransitionRotateAngle: number = 0;
  @State enableCompBindPopupTransitionRotateCenterX: boolean = false;
  @State compBindPopupTransitionRotateCenterX: number = 0;
  @State enableCompBindPopupTransitionRotateCenterY: boolean = false;
  @State compBindPopupTransitionRotateCenterY: number = 0;
  @State enableCompBindPopupTransitionRotateCenterZ: boolean = false;
  @State compBindPopupTransitionRotateCenterZ: number = 0;
  @State enableCompBindPopupTransitionRotatePerspective: boolean = false;
  @State compBindPopupTransitionRotatePerspective: number = 0;
  @State enableCompBindPopupTransitionMove: boolean = false;
  @State compBindPopupTransitionMove: TransitionEdge = TransitionEdge.START;
  @StorageLink('Block') listEventTriggeredTags: Array<BlockTag> = [];
  @State listEventTriggeredTagsTemp: Array<BlockTag> = [];
  scroller: Scroller = new Scroller();

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  //compEvent
  compEventTriggeredLog(value: string) {
    let time = formatDate(new Date(Date.now()))
    this.listEventTriggeredTagsTemp.push(
      new BlockTag(time, value)
    )
    setTimeout(() => {
      if (AppStorage.get('Block')) {
        this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
          this.listEventTriggeredTagsTemp
        );
        this.listEventTriggeredTagsTemp = [];
      } else {
        if (this.listEventTriggeredTagsTemp) {
          this.listEventTriggeredTags = this.listEventTriggeredTags.concat(
            this.listEventTriggeredTagsTemp
          );
        }
        if (this.listEventTriggeredTags) {
          this.listEventTriggeredTagsTemp = [];
        }
      }
    }, 200)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        generic: () => {
          this.Generic()
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
      Button('BindPopup')
        .onClick(() => {
          this.handlePopup = !this.handlePopup;
          console.info('Button click');
        })
        .bindPopup(this.handlePopup, {
          message: this.compPopupType == 0 ? 'This is a popup with button ' : useEnabled(
            this.enableCompBindPopupAvoidTarget, this.compPopupAvoidTargetMessage, 'This is a popup only Text '),
          arrowOffset: useEnabled(this.enableCompBindPopupArrowOffset, this.compBindPopupArrowOffset) ?
          useEnabled(this.enableCompBindPopupArrowOffset, this.compBindPopupArrowOffset) : null,
          showInSubWindow: useEnabled(this.enableCompBindPopupShowInSubWindow, this.compBindPopupShowInSubWindow),
          mask: useEnabled(this.enableCompBindPopupMaskType, this.compBindPopupMaskType) ?
          useEnabled(this.enableCompBindPopupMaskBoolean, this.compBindPopupMaskBoolean) :
            { color: useEnabled(this.enableCompBindPopupMaskColor, this.compBindPopupMaskColor) },
          messageOptions: {
            textColor: useEnabled(this.enableCompBindPopupMessageOptionsTextColor,
              this.compBindPopupMessageOptionsTextColor),
            font: {
              size: useEnabled(this.enableCompBindPopupMessageOptionsFontSize,
                this.compBindPopupMessageOptionsFontSize),
              weight: useEnabled(this.enableCompBindPopupMessageOptionsFontWeight,
                this.compBindPopupMessageOptionsFontWeight),
              style: useEnabled(this.enableCompBindPopupMessageOptionsFontStyle,
                this.compBindPopupMessageOptionsFontStyle),
            }
          },
          targetSpace: useEnabled(this.enableCompBindPopupTargetSpace, this.compBindPopupTargetSpace),
          placement: useEnabled(this.enableCompBindPopupPlacement, this.compBindPopupPlacement, Placement.Top),
          avoidTarget: useEnabled(this.enableCompBindPopupAvoidTarget, this.compBindPopupAvoidTarget),
          offset: {
            x: useEnabled(this.enableCompBindPopupOffsetX, this.compBindPopupOffsetX),
            y: useEnabled(this.enableCompBindPopupOffsetY, this.compBindPopupOffsetY),
          },
          enableArrow: useEnabled(this.enableCompBindPopupEnableArrow, this.compBindPopupEnableArrow),
          popupColor: useEnabled(this.enableCompBindPopupPopupColor, this.compBindPopupPopupColor),
          autoCancel: useEnabled(this.enableCompBindPopupAutoCancel, this.compBindPopupAutoCancel),
          width: useEnabled(this.enableCompBindPopupWidth, this.compBindPopupWidth),
          arrowPointPosition: useEnabled(this.enableCompBindPopupArrowPointPosition,
            this.compBindPopupArrowPointPosition),
          arrowWidth: useEnabled(this.enableCompBindPopupArrowWidth, this.compBindPopupArrowWidth),
          arrowHeight: useEnabled(this.enableCompBindPopupArrowHeight, this.compBindPopupArrowHeight),
          radius: useEnabled(this.enableCompBindPopupRadius, this.compBindPopupRadius),
          shadow: useEnabled(this.enableCompBindPopupShadowType, this.compBindPopupShadowType) ?
          useEnabled(this.enableCompBindPopupShadowStyle, this.compBindPopupShadowStyle) : {
              radius: useEnabled(this.enableCompBindPopupShadowOptionsRadius,
                this.compBindPopupShadowOptionsRadius),
              type: useEnabled(this.enableCompBindPopupShadowOptionsType, this.compBindPopupShadowOptionsType),
              color: useEnabled(this.enableCompBindPopupShadowOptionsColor, this.compBindPopupShadowOptionsColor),
              offsetX: useEnabled(this.enableCompBindPopupShadowOptionsOffsetX,
                this.compBindPopupShadowOptionsOffsetX),
              offsetY: useEnabled(this.enableCompBindPopupShadowOptionsOffsetY,
                this.compBindPopupShadowOptionsOffsetY),
              fill: useEnabled(this.enableCompBindPopupShadowOptionsFill, this.compBindPopupShadowOptionsFill),
            },
          backgroundBlurStyle: useEnabled(this.enableCompBindPopupBackgroundBlurStyle,
            this.compBindPopupBackgroundBlurStyle),
          transition:
          (TransitionEffect.opacity(
            useEnabled(this.enableCompBindPopupTransitionOpacity, this.compBindPopupTransitionOpacity)
          )
            .combine(TransitionEffect.translate({
              x: useEnabled(
                this.enableCompBindPopupTransitionTranslateX,
                this.compBindPopupTransitionTranslateX
              ),
              y: useEnabled(
                this.enableCompBindPopupTransitionTranslateY,
                this.compBindPopupTransitionTranslateY
              ),
              z: useEnabled(
                this.enableCompBindPopupTransitionTranslateZ,
                this.compBindPopupTransitionTranslateZ
              )
            }))
            .combine(TransitionEffect.scale({
              x: useEnabled(
                this.enableCompBindPopupTransitionScaleX,
                this.compBindPopupTransitionScaleX
              ),
              y: useEnabled(
                this.enableCompBindPopupTransitionScaleY,
                this.compBindPopupTransitionScaleY
              ),
              z: useEnabled(
                this.enableCompBindPopupTransitionScaleZ,
                this.compBindPopupTransitionScaleZ
              ),
              centerX: useEnabled(
                this.enableCompBindPopupTransitionScaleCenterX,
                this.compBindPopupTransitionScaleCenterX
              ),
              centerY: useEnabled(
                this.enableCompBindPopupTransitionScaleCenterY,
                this.compBindPopupTransitionScaleCenterY
              ),
            }))
            .combine(TransitionEffect.rotate({
              x: useEnabled(this.enableCompBindPopupTransitionRotateX, this.compBindPopupTransitionRotateX),
              y: useEnabled(this.enableCompBindPopupTransitionRotateY, this.compBindPopupTransitionRotateY),
              z: useEnabled(this.enableCompBindPopupTransitionRotateZ, this.compBindPopupTransitionRotateZ),
              angle: useEnabled(this.enableCompBindPopupTransitionRotateAngle,
                this.compBindPopupTransitionRotateAngle),
              centerX: useEnabled(this.enableCompBindPopupTransitionRotateCenterX,
                this.compBindPopupTransitionRotateCenterX),
              centerY: useEnabled(this.enableCompBindPopupTransitionRotateCenterY,
                this.compBindPopupTransitionRotateCenterY),
              centerZ: useEnabled(this.enableCompBindPopupTransitionRotateCenterZ,
                this.compBindPopupTransitionRotateCenterZ),
              perspective: useEnabled(this.enableCompBindPopupTransitionRotatePerspective,
                this.compBindPopupTransitionRotatePerspective),
            }))
            .combine(TransitionEffect.move(
              useEnabled(this.enableCompBindPopupTransitionMove, this.compBindPopupTransitionMove)
            )))
        ,
          onStateChange: (e) => {
            console.info('onStateChange', JSON.stringify(e.isVisible))
            this.compEventTriggeredLog('onStateChange触发')
            if (!e.isVisible) {
              this.handlePopup = false
            }

          },
          primaryButton: this.compPopupType == 0 ? {
            value: 'confirm ',
            action: () => {
              this.handlePopup = !this.handlePopup;
              console.info('confirm Button click');
              this.compEventTriggeredLog('confirm Button click触发')
            }
          } : null,
          secondaryButton: this.compPopupType == 0 ? {
            value: 'cancel ',
            action: () => {
              this.handlePopup = !this.handlePopup;
              console.info('cancel Button click')
              this.compEventTriggeredLog('cancel Button click触发')
            }
          } : null,
          onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
            if (dismissPopupAction.reason == DismissReason.PRESS_BACK) {
              dismissPopupAction.dismiss()
            }
            this.compEventTriggeredLog('BindPopup:onWillDismiss()')
          }
        })
    }
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'show.buttons',
          isEnabled: $enableCompPopupType,
          value: $compPopupType,
          dataSource: [
            { label: 'true', value: 0 },
            { label: 'false', value: 1 }
          ]
        })


        SliderBlock({
          title: 'popupOptions.arrowOffset',
          isEnabled: $enableCompBindPopupArrowOffset,
          value: $compBindPopupArrowOffset,
          min: 0,
          max: 50
        })

        RadioBlock({
          title: 'popupOptions.showInSubWindow',
          isEnabled: $enableCompBindPopupShowInSubWindow,
          value: $compBindPopupShowInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'popupOptions.maskType',
          isEnabled: $enableCompBindPopupMaskType,
          value: $compBindPopupMaskType,
          dataSource: [
            { label: 'boolean', value: true },
            { label: 'color', value: false }
          ]
        })

        if (this.compBindPopupMaskType) {

          RadioBlock({
            title: 'popupOptions.mask.boolean',
            isEnabled: $enableCompBindPopupMaskBoolean,
            value: $compBindPopupMaskBoolean,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })

        } else {

          ColorBlock({
            title: 'popupOptions.mask.color',
            isEnabled: $enableCompBindPopupMaskColor,
            color: $compBindPopupMaskColor
          })

        }

        ColorBlock({
          title: 'popupOptions.messageOptions.textColor',
          isEnabled: $enableCompBindPopupMessageOptionsTextColor,
          color: $compBindPopupMessageOptionsTextColor,
        })

        SliderBlock({
          title: 'popupOptions.messageOptions.font.size',
          isEnabled: $enableCompBindPopupMessageOptionsFontSize,
          value: $compBindPopupMessageOptionsFontSize,
          min: 0,
          max: 30
        })

        RadioBlock({
          title: 'popupOptions.messageOptions.font.weight',
          isEnabled: $enableCompBindPopupMessageOptionsFontWeight,
          value: $compBindPopupMessageOptionsFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'popupOptions.messageOptions.font.style',
          isEnabled: $enableCompBindPopupMessageOptionsFontStyle,
          value: $compBindPopupMessageOptionsFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        SliderBlock({
          title: 'popupOptions.targetSpace',
          isEnabled: $enableCompBindPopupTargetSpace,
          value: $compBindPopupTargetSpace,
          min: 0,
          max: 30
        })

        RadioBlock({
          title: 'popupOptions.placement',
          isEnabled: $enableCompBindPopupPlacement,
          value: $compBindPopupPlacement,
          dataSource: [
            { label: 'Left', value: Placement.Left },
            { label: 'Right', value: Placement.Right },
            { label: 'Top', value: Placement.Top },
            { label: 'Bottom', value: Placement.Bottom },
            { label: 'TopRight', value: Placement.TopRight },
            { label: 'TopLeft', value: Placement.TopLeft },
            { label: 'BottomLeft', value: Placement.BottomLeft },
            { label: 'BottomRight', value: Placement.BottomRight },
            { label: 'RightTop', value: Placement.RightTop },
            { label: 'RightBottom', value: Placement.RightBottom },
            { label: 'LeftTop', value: Placement.LeftTop },
            { label: 'LeftBottom', value: Placement.LeftBottom },
          ]
        })

        RadioBlock({
          title: 'popupOptions.avoidTarget',
          isEnabled: $enableCompBindPopupAvoidTarget,
          value: $compBindPopupAvoidTarget,
          dataSource: [
            { label: 'COVER_TARGET', value: AvoidanceMode.COVER_TARGET },
            { label: 'AVOID_AROUND_TARGET', value: AvoidanceMode.AVOID_AROUND_TARGET },
          ]
        })

        SliderBlock({
          title: 'popupOptions.offsetX',
          isEnabled: $enableCompBindPopupOffsetX,
          value: $compBindPopupOffsetX,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'popupOptions.offsetY',
          isEnabled: $enableCompBindPopupOffsetY,
          value: $compBindPopupOffsetY,
          min: 0,
          max: 50
        })

        RadioBlock({
          title: 'popupOptions.enableArrow',
          isEnabled: $enableCompBindPopupEnableArrow,
          value: $compBindPopupEnableArrow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        ColorBlock({
          title: 'popupOptions.popupColor',
          isEnabled: $enableCompBindPopupPopupColor,
          color: $compBindPopupPopupColor,
        })

        RadioBlock({
          title: 'popupOptions.autoCancel',
          isEnabled: $enableCompBindPopupAutoCancel,
          value: $compBindPopupAutoCancel,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'popupOptions.width',
          isEnabled: $enableCompBindPopupWidth,
          value: $compBindPopupWidth,
          min: 0,
          max: 400
        })

        RadioBlock({
          title: 'popupOptions.arrowPointPosition',
          isEnabled: $enableCompBindPopupArrowPointPosition,
          value: $compBindPopupArrowPointPosition,
          dataSource: [
            { label: 'CENTER', value: ArrowPointPosition.CENTER },
            { label: 'START', value: ArrowPointPosition.START },
            { label: 'END', value: ArrowPointPosition.END },
          ]
        })

        RadioBlock({
          title: 'popupOptions.shadow',
          isEnabled: $enableCompBindPopupShadowType,
          value: $compBindPopupShadowType,
          dataSource: [
            { label: 'shadowStyle', value: true },
            { label: 'shadowOptions', value: false }
          ]
        })

        if (this.compBindPopupShadowType) {
          RadioBlock({
            title: 'popupOptions.shadow.shadowStyle',
            isEnabled: $enableCompBindPopupShadowStyle,
            value: $compBindPopupShadowStyle,
            dataSource: [
              { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
              { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
              { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
              { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
              { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
              { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
            ]
          })
        } else {

          SliderBlock({
            title: 'popupOptions.shadow.shadowOptions.radius',
            isEnabled: $enableCompBindPopupShadowOptionsRadius,
            value: $compBindPopupShadowOptionsRadius,
            min: 0,
            max: 30,
          })

          RadioBlock({
            title: 'popupOptions.shadow.shadowOptions.type',
            isEnabled: $enableCompBindPopupShadowOptionsType,
            value: $compBindPopupShadowOptionsType,
            dataSource: [
              { label: 'COLOR', value: ShadowType.COLOR },
              { label: 'BLUR', value: ShadowType.BLUR },
            ]
          })

          ColorBlock({
            title: 'popupOptions.shadow.shadowOptions.color',
            isEnabled: $enableCompBindPopupShadowOptionsColor,
            color: $compBindPopupShadowOptionsColor,
          })

          SliderBlock({
            title: 'popupOptions.shadow.shadowOptions.offsetX',
            isEnabled: $enableCompBindPopupShadowOptionsOffsetX,
            value: $compBindPopupShadowOptionsOffsetX,
            min: 0,
            max: 40,
          })

          SliderBlock({
            title: 'popupOptions.shadow.shadowOptions.offsetY',
            isEnabled: $enableCompBindPopupShadowOptionsOffsetY,
            value: $compBindPopupShadowOptionsOffsetY,
            min: 0,
            max: 40,
          })

          RadioBlock({
            title: 'popupOptions.shadow.shadowOptions.fill',
            isEnabled: $enableCompBindPopupShadowOptionsFill,
            value: $compBindPopupShadowOptionsFill,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

        }

        RadioBlock({
          title: 'popupOptions.BackgroundBlurStyle',
          isEnabled: $enableCompBindPopupBackgroundBlurStyle,
          value: $compBindPopupBackgroundBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })

        SliderBlock({
          title: 'popupOptions.transition.opacity',
          isEnabled: $enableCompBindPopupTransitionOpacity,
          value: $compBindPopupTransitionOpacity,
          step: 0.1,
          min: 0,
          max: 1
        })


        SliderBlock({
          title: 'popupOptions.transition.translateX',
          isEnabled: $enableCompBindPopupTransitionTranslateX,
          value: $compBindPopupTransitionTranslateX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.translateY',
          isEnabled: $enableCompBindPopupTransitionTranslateY,
          value: $compBindPopupTransitionTranslateY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.translateZ',
          isEnabled: $enableCompBindPopupTransitionTranslateZ,
          value: $compBindPopupTransitionTranslateZ,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.scaleX',
          isEnabled: $enableCompBindPopupTransitionScaleX,
          value: $compBindPopupTransitionScaleX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.scaleY',
          isEnabled: $enableCompBindPopupTransitionScaleY,
          value: $compBindPopupTransitionScaleY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.scaleZ',
          isEnabled: $enableCompBindPopupTransitionScaleZ,
          value: $compBindPopupTransitionScaleZ,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.scale.centerX',
          isEnabled: $enableCompBindPopupTransitionScaleCenterX,
          value: $compBindPopupTransitionScaleCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.scale.centerY',
          isEnabled: $enableCompBindPopupTransitionScaleCenterY,
          value: $compBindPopupTransitionScaleCenterY,
          min: 0,
          max: 100
        })


        SliderBlock({
          title: 'popupOptions.transition.RotateX',
          isEnabled: $enableCompBindPopupTransitionRotateX,
          value: $compBindPopupTransitionRotateX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.RotateY',
          isEnabled: $enableCompBindPopupTransitionRotateY,
          value: $compBindPopupTransitionRotateY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.RotateY',
          isEnabled: $enableCompBindPopupTransitionRotateZ,
          value: $compBindPopupTransitionRotateZ,
          min: 0,
          max: 100
        })


        SliderBlock({
          title: 'popupOptions.transition.Rotate.CenterX',
          isEnabled: $enableCompBindPopupTransitionRotateCenterX,
          value: $compBindPopupTransitionRotateCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'popupOptions.transition.Rotate.CenterY',
          isEnabled: $enableCompBindPopupTransitionRotateCenterY,
          value: $compBindPopupTransitionRotateCenterY,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'popupOptions.transition.move',
          isEnabled: $enableCompBindPopupTransitionMove,
          value: $compBindPopupTransitionMove,
          dataSource: [
            { label: 'TOP', value: TransitionEdge.TOP },
            { label: 'BOTTOM', value: TransitionEdge.BOTTOM },
            { label: 'START', value: TransitionEdge.START },
            { label: 'END', value: TransitionEdge.END },
          ]
        })

      }
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {

  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    BindPopupBootcamp({
      title: '气泡/bindPopup'
    })
  }
}