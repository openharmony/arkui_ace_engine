import { ColorBlock, RadioBlock, SliderBlock } from 'common';

@Component
export struct CompPopupControlBlocks {
  @Link enableCompBindPopupType: boolean;
  @Link compBindPopupType: boolean;
  @Link handlePopup: boolean;
  @Link enableCompPopupType: boolean;
  @Link compPopupType: number;
  @Link enableCompBindPopupArrowOffset: boolean;
  @Link compBindPopupArrowOffset: number;
  @Link enableCompBindPopupShowInSubWindow: boolean;
  @Link compBindPopupShowInSubWindow: boolean;
  @Link enableCompBindPopupMaskType: boolean;
  @Link compBindPopupMaskType: boolean;
  @Link enableCompBindPopupMaskBoolean: boolean;
  @Link compBindPopupMaskBoolean: boolean;
  @Link enableCompBindPopupMaskColor: boolean;
  @Link compBindPopupMaskColor: ResourceStr;
  @Link enableCompBindPopupMessageOptionsTextColor: boolean;
  @Link compBindPopupMessageOptionsTextColor: ResourceStr;
  @Link enableCompBindPopupMessageOptionsFontSize: boolean;
  @Link compBindPopupMessageOptionsFontSize: number;
  @Link enableCompBindPopupMessageOptionsFontWeight: boolean;
  @Link compBindPopupMessageOptionsFontWeight: FontWeight;
  @Link enableCompBindPopupMessageOptionsFontStyle: boolean;
  @Link compBindPopupMessageOptionsFontStyle: FontStyle;
  @Link enableCompBindPopupTargetSpace: boolean;
  @Link compBindPopupTargetSpace: number;
  @Link enableCompBindPopupPlacement: boolean;
  @Link compBindPopupPlacement: Placement;
  @Link enableCompBindPopupOffsetX: boolean;
  @Link compBindPopupOffsetX: number;
  @Link enableCompBindPopupOffsetY: boolean;
  @Link compBindPopupOffsetY: number;
  @Link enableCompBindPopupEnableArrow: boolean;
  @Link compBindPopupEnableArrow: boolean;
  @Link enableCompBindPopupPopupColor: boolean;
  @Link compBindPopupPopupColor: ResourceStr;
  @Link enableCompBindPopupAutoCancel: boolean;
  @Link compBindPopupAutoCancel: boolean;
  @Link enableCompBindPopupWidth: boolean;
  @Link compBindPopupWidth: number;
  @Link enableCompBindPopupArrowPointPosition: boolean;
  @Link compBindPopupArrowPointPosition: ArrowPointPosition;
  @Link enableCompBindPopupArrowWidth: boolean;
  @Link compBindPopupArrowWidth: number;
  @Link enableCompBindPopupArrowHeight: boolean;
  @Link compBindPopupArrowHeight: number;
  @Link enableCompBindPopupRadius: boolean;
  @Link compBindPopupRadius: number;
  @Link enableCompBindPopupShadowType: boolean;
  @Link compBindPopupShadowType: boolean;
  @Link enableCompBindPopupShadowStyle: boolean;
  @Link compBindPopupShadowStyle: ShadowStyle;
  @Link enableCompBindPopupShadowOptionsRadius: boolean;
  @Link compBindPopupShadowOptionsRadius: number;
  @Link enableCompBindPopupShadowOptionsType: boolean;
  @Link compBindPopupShadowOptionsType: ShadowType;
  @Link enableCompBindPopupShadowOptionsColor: boolean;
  @Link compBindPopupShadowOptionsColor: ResourceColor;
  @Link enableCompBindPopupShadowOptionsOffsetX: boolean;
  @Link compBindPopupShadowOptionsOffsetX: number;
  @Link enableCompBindPopupShadowOptionsOffsetY: boolean;
  @Link compBindPopupShadowOptionsOffsetY: number;
  @Link enableCompBindPopupShadowOptionsFill: boolean;
  @Link compBindPopupShadowOptionsFill: boolean;
  @Link enableCompBindPopupBackgroundBlurStyle: boolean;
  @Link compBindPopupBackgroundBlurStyle: BlurStyle;
  @Link enableTransitionTransitionEffect: boolean;
  @Link transitionTransitionEffect: TransitionEffect;
  @Link enableCompBindPopupTransitionOpacity: boolean;
  @Link compBindPopupTransitionOpacity: number;
  @Link enableCompBindPopupTransitionTranslateX: boolean
  @Link compBindPopupTransitionTranslateX: number;
  @Link enableCompBindPopupTransitionTranslateY: boolean;
  @Link compBindPopupTransitionTranslateY: number;
  @Link enableCompBindPopupTransitionTranslateZ: boolean;
  @Link compBindPopupTransitionTranslateZ: number;
  @Link enableCompBindPopupTransitionScaleX: boolean;
  @Link compBindPopupTransitionScaleX: number;
  @Link enableCompBindPopupTransitionScaleY: boolean;
  @Link compBindPopupTransitionScaleY: number;
  @Link enableCompBindPopupTransitionScaleZ: boolean;
  @Link compBindPopupTransitionScaleZ: number;
  @Link enableCompBindPopupTransitionScaleCenterX: boolean;
  @Link compBindPopupTransitionScaleCenterX: number;
  @Link enableCompBindPopupTransitionScaleCenterY: boolean;
  @Link compBindPopupTransitionScaleCenterY: number;
  @Link enableCompBindPopupTransitionRotateX: boolean;
  @Link compBindPopupTransitionRotateX: number;
  @Link enableCompBindPopupTransitionRotateY: boolean;
  @Link compBindPopupTransitionRotateY: number;
  @Link enableCompBindPopupTransitionRotateZ: boolean;
  @Link compBindPopupTransitionRotateZ: number;
  @Link enableCompBindPopupTransitionRotateAngle: boolean;
  @Link compBindPopupTransitionRotateAngle: number;
  @Link enableCompBindPopupTransitionRotateCenterX: boolean;
  @Link compBindPopupTransitionRotateCenterX: number;
  @Link enableCompBindPopupTransitionRotateCenterY: boolean;
  @Link compBindPopupTransitionRotateCenterY: number;
  @Link enableCompBindPopupTransitionRotateCenterZ: boolean;
  @Link compBindPopupTransitionRotateCenterZ: number;
  @Link enableCompBindPopupTransitionRotatePerspective: boolean;
  @Link compBindPopupTransitionRotatePerspective: number;
  @Link enableCompBindPopupTransitionMove: boolean;
  @Link compBindPopupTransitionMove: TransitionEdge;

  build() {
    Column() {

      RadioBlock({
        title: 'show.button',
        isEnabled: $enableCompPopupType,
        value: $compPopupType,
        dataSource: [
          { label: 'true', value: 0 },
          { label: 'false', value: 1 }
        ]
      })


      SliderBlock({
        title: 'bindPopup.arrowOffset',
        isEnabled: $enableCompBindPopupArrowOffset,
        value: $compBindPopupArrowOffset,
        min: 0,
        max: 50
      })

      RadioBlock({
        title: 'bindPopup.showInSubWindow',
        isEnabled: $enableCompBindPopupShowInSubWindow,
        value: $compBindPopupShowInSubWindow,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      RadioBlock({
        title: 'bindPopup.maskType',
        isEnabled: $enableCompBindPopupMaskType,
        value: $compBindPopupMaskType,
        dataSource: [
          { label: 'boolean', value: true },
          { label: 'color', value: false }
        ]
      })

      if (this.compBindPopupMaskType) {

        RadioBlock({
          title: 'bindPopup.mask.boolean',
          isEnabled: $enableCompBindPopupMaskBoolean,
          value: $compBindPopupMaskBoolean,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

      } else {

        ColorBlock({
          title: 'bindPopup.mask.color',
          isEnabled: $enableCompBindPopupMaskColor,
          color: $compBindPopupMaskColor
        })

      }

      ColorBlock({
        title: 'bindPopup.messageOptions.textColor',
        isEnabled: $enableCompBindPopupMessageOptionsTextColor,
        color: $compBindPopupMessageOptionsTextColor,
      })

      SliderBlock({
        title: 'bindPopup.messageOptions.font.size',
        isEnabled: $enableCompBindPopupMessageOptionsFontSize,
        value: $compBindPopupMessageOptionsFontSize,
        min: 0,
        max: 30
      })

      RadioBlock({
        title: 'bindPopup.messageOptions.font.weight',
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
        title: 'bindPopup.messageOptions.font.style',
        isEnabled: $enableCompBindPopupMessageOptionsFontStyle,
        value: $compBindPopupMessageOptionsFontStyle,
        dataSource: [
          { label: 'Normal', value: FontStyle.Normal },
          { label: 'Italic', value: FontStyle.Italic },
        ]
      })

      SliderBlock({
        title: 'bindPopup.targetSpace',
        isEnabled: $enableCompBindPopupTargetSpace,
        value: $compBindPopupTargetSpace,
        min: 0,
        max: 30
      })

      RadioBlock({
        title: 'bindPopup.placement',
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
        ]
      })

      SliderBlock({
        title: 'bindPopup.offsetX',
        isEnabled: $enableCompBindPopupOffsetX,
        value: $compBindPopupOffsetX,
        min: 0,
        max: 50
      })

      SliderBlock({
        title: 'bindPopup.offsetY',
        isEnabled: $enableCompBindPopupOffsetY,
        value: $compBindPopupOffsetY,
        min: 0,
        max: 50
      })

      RadioBlock({
        title: 'bindPopup.enableArrow',
        isEnabled: $enableCompBindPopupEnableArrow,
        value: $compBindPopupEnableArrow,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      ColorBlock({
        title: 'bindPopup.popupColor',
        isEnabled: $enableCompBindPopupPopupColor,
        color: $compBindPopupPopupColor,
      })

      RadioBlock({
        title: 'bindPopup.autoCancel',
        isEnabled: $enableCompBindPopupAutoCancel,
        value: $compBindPopupAutoCancel,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })

      SliderBlock({
        title: 'bindPopup.width',
        isEnabled: $enableCompBindPopupWidth,
        value: $compBindPopupWidth,
        min: 0,
        max: 400
      })

      RadioBlock({
        title: 'bindPopup.arrowPointPosition',
        isEnabled: $enableCompBindPopupArrowPointPosition,
        value: $compBindPopupArrowPointPosition,
        dataSource: [
          { label: 'CENTER', value: ArrowPointPosition.CENTER },
          { label: 'START', value: ArrowPointPosition.START },
          { label: 'END', value: ArrowPointPosition.END },
        ]
      })

      RadioBlock({
        title: 'bindPopup.shadowType',
        isEnabled: $enableCompBindPopupShadowType,
        value: $compBindPopupShadowType,
        dataSource: [
          { label: 'shadowStyle', value: true },
          { label: 'shadowOptions', value: false }
        ]
      })

      if (this.compBindPopupShadowType) {
        RadioBlock({
          title: 'bindPopup.shadowType.shadowStyle',
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
          title: 'bindPopup.shadowType.shadowOptions.radius',
          isEnabled: $enableCompBindPopupShadowOptionsRadius,
          value: $compBindPopupShadowOptionsRadius,
          min: 0,
          max: 30,
        })

        RadioBlock({
          title: 'bindPopup.shadowType.shadowOptions.type',
          isEnabled: $enableCompBindPopupShadowOptionsType,
          value: $compBindPopupShadowOptionsType,
          dataSource: [
            { label: 'COLOR', value: ShadowType.COLOR },
            { label: 'BLUR', value: ShadowType.BLUR },
          ]
        })

        ColorBlock({
          title: 'bindPopup.shadowType.shadowOptions.color',
          isEnabled: $enableCompBindPopupShadowOptionsColor,
          color: $compBindPopupShadowOptionsColor,
        })

        SliderBlock({
          title: 'bindPopup.shadowType.shadowOptions.offsetX',
          isEnabled: $enableCompBindPopupShadowOptionsOffsetX,
          value: $compBindPopupShadowOptionsOffsetX,
          min: 0,
          max: 40,
        })

        SliderBlock({
          title: 'bindPopup.shadowType.shadowOptions.offsetY',
          isEnabled: $enableCompBindPopupShadowOptionsOffsetY,
          value: $compBindPopupShadowOptionsOffsetY,
          min: 0,
          max: 40,
        })

        RadioBlock({
          title: 'bindPopup.shadowType.shadowOptions.fill',
          isEnabled: $enableCompBindPopupShadowOptionsFill,
          value: $compBindPopupShadowOptionsFill,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

      }

      RadioBlock({
        title: 'bindPopup.BackgroundBlurStyle',
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
        title: 'bindPopup.transition.opacity',
        isEnabled: $enableCompBindPopupTransitionOpacity,
        value: $compBindPopupTransitionOpacity,
        step: 0.1,
        min: 0,
        max: 1
      })


      SliderBlock({
        title: 'bindPopup.transition.translateX',
        isEnabled: $enableCompBindPopupTransitionTranslateX,
        value: $compBindPopupTransitionTranslateX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.translateY',
        isEnabled: $enableCompBindPopupTransitionTranslateY,
        value: $compBindPopupTransitionTranslateY,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.translateZ',
        isEnabled: $enableCompBindPopupTransitionTranslateZ,
        value: $compBindPopupTransitionTranslateZ,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.scaleX',
        isEnabled: $enableCompBindPopupTransitionScaleX,
        value: $compBindPopupTransitionScaleX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.scaleY',
        isEnabled: $enableCompBindPopupTransitionScaleY,
        value: $compBindPopupTransitionScaleY,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.scaleZ',
        isEnabled: $enableCompBindPopupTransitionScaleZ,
        value: $compBindPopupTransitionScaleZ,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.scale.centerX',
        isEnabled: $enableCompBindPopupTransitionScaleCenterX,
        value: $compBindPopupTransitionScaleCenterX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.scale.centerY',
        isEnabled: $enableCompBindPopupTransitionScaleCenterY,
        value: $compBindPopupTransitionScaleCenterY,
        min: 0,
        max: 100
      })


      SliderBlock({
        title: 'bindPopup.transition.RotateX',
        isEnabled: $enableCompBindPopupTransitionRotateX,
        value: $compBindPopupTransitionRotateX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.RotateY',
        isEnabled: $enableCompBindPopupTransitionRotateY,
        value: $compBindPopupTransitionRotateY,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.RotateY',
        isEnabled: $enableCompBindPopupTransitionRotateZ,
        value: $compBindPopupTransitionRotateZ,
        min: 0,
        max: 100
      })


      SliderBlock({
        title: 'bindPopup.transition.Rotate.CenterX',
        isEnabled: $enableCompBindPopupTransitionRotateCenterX,
        value: $compBindPopupTransitionRotateCenterX,
        min: 0,
        max: 100
      })

      SliderBlock({
        title: 'bindPopup.transition.Rotate.CenterY',
        isEnabled: $enableCompBindPopupTransitionRotateCenterY,
        value: $compBindPopupTransitionRotateCenterY,
        min: 0,
        max: 100
      })

      RadioBlock({
        title: 'bindPopup.transition.move',
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
    .width('100%')
  }
}