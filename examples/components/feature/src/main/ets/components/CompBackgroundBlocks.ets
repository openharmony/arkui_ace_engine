import { RadioBlock, ColorBlock, SliderBlock } from 'common';
import { common2D } from '@kit.ArkGraphics2D';

@Component
export struct CompBackgroundBlocks {
  @Link enableCompBackgroundAlign: boolean;
  @Link compBackgroundAlign: Alignment;
  @Link enableCompBackgroundColor: boolean;
  @Link compBackgroundColor: ResourceColor;
  @Link enableCompBackgroundImageSrc: boolean;
  @Link enableCompBackgroundImageRepeat: boolean;
  @Link compBackgroundImageRepeat: ImageRepeat;
  @Link enableCompBackgroundImageSize: boolean;
  @Link compBackgroundImageSize: ImageSize;
  @Link enableCompBackgroundImagePositionX: boolean;
  @Link compBackgroundImagePositionX: Length;
  @Link enableCompBackgroundImagePositionY: boolean;
  @Link compBackgroundImagePositionY: Length;
  @Link enableCompBackgroundBlurStyle: boolean;
  @Link compBackgroundBlurStyle: BlurStyle;
  @Link enableCompBackgroundBlurStyleParams: boolean;
  @Link enableCompBackgroundBlurStyleParamsColorMode: boolean;
  @Link compBackgroundBlurStyleParamsColorMode: ThemeColorMode;
  @Link enableCompBackgroundBlurStyleParamsAdaptiveColor: boolean;
  @Link compBackgroundBlurStyleParamsAdaptiveColor: AdaptiveColor
  @Link enableCompBackgroundBlurStyleParamsBlurOptionsLeft: boolean;
  @Link compBackgroundBlurStyleParamsBlurOptionsLeft: number;
  @Link enableCompBackgroundBlurStyleParamsBlurOptionsRight: boolean;
  @Link compBackgroundBlurStyleParamsBlurOptionsRight: number;
  @Link enableCompBackgroundBlurStyleParamsScale: boolean;
  @Link compBackgroundBlurStyleParamsScale: number;
  @Link enableCompBackdropBlur: boolean;
  @Link compBackdropBlur: number;
  @Link enableCompBackdropBlurGrayscale: boolean;
  @Link enableCompBackdropBlurGrayscaleLeft: boolean;
  @Link compBackdropBlurGrayscaleLeft: number;
  @Link enableCompBackdropBlurGrayscaleRight: boolean;
  @Link compBackdropBlurGrayscaleRight: number;
  @Link enableCompBackgroundEffect: boolean;
  @Link enableCompBackgroundEffectRadius: boolean;
  @Link compBackgroundEffectRadius: number;
  @Link enableCompBackgroundEffectSaturation: boolean;
  @Link compBackgroundEffectSaturation: number;
  @Link enableCompBackgroundEffectBrightness: boolean;
  @Link compBackgroundEffectBrightness: number;
  @Link enableCompBackgroundEffectColor: boolean;
  @Link compBackgroundEffectColor: ResourceColor;
  @Link enableCompBackgroundEffectAdaptiveColor: boolean;
  @Link compBackgroundEffectAdaptiveColor: AdaptiveColor;
  @Link enableCompBackgroundEffectBlurOptionsGrayscaleLeft: boolean;
  @Link compBackgroundEffectBlurOptionsGrayscaleLeft: number;
  @Link enableCompBackgroundEffectBlurOptionsGrayscaleRight: boolean;
  @Link compBackgroundEffectBlurOptionsGrayscaleRight: number;
  @Link enableCompBackgroundImageResizable: boolean;
  @Link enableCompBackgroundImageResizableSliceTop: boolean;
  @Link compBackgroundImageResizableSliceTop: Length;
  @Link enableCompBackgroundImageResizableSliceBottom: boolean;
  @Link compBackgroundImageResizableSliceBottom: Length;
  @Link enableCompBackgroundImageResizableSliceLeft: boolean;
  @Link compBackgroundImageResizableSliceLeft: Length;
  @Link enableCompBackgroundImageResizableSliceRight: boolean;
  @Link compBackgroundImageResizableSliceRight: Length;
  @Link enableCompBackgroundImageResizableLattice: boolean;
  @Link enableCompBackgroundImageResizableLatticeXDivs: boolean;
  @Link compBackgroundImageResizableLatticeXDivs: Array<number>;
  @Link enableCompBackgroundImageResizableLatticeYDivs: boolean;
  @Link compBackgroundImageResizableLatticeYDivs: Array<number>;
  @Link enableCompBackgroundImageResizableLatticeFXCount: boolean;
  @Link compBackgroundImageResizableLatticeFXCount: number;
  @Link enableCompBackgroundImageResizableLatticeFYCount: boolean;
  @Link compBackgroundImageResizableLatticeFYCount: number;
  @Link enableCompBackgroundImageResizableLatticeFBounds: boolean;
  @Link enableCompBackgroundImageResizableLatticeFBoundsLeft: boolean;
  @Link compBackgroundImageResizableLatticeFBoundsLeft: number;
  @Link enableCompBackgroundImageResizableLatticeFBoundsTop: boolean;
  @Link compBackgroundImageResizableLatticeFBoundsTop: number;
  @Link enableCompBackgroundImageResizableLatticeFBoundsRight: boolean;
  @Link compBackgroundImageResizableLatticeFBoundsRight: number;
  @Link enableCompBackgroundImageResizableLatticeFBoundsBottom: boolean;
  @Link compBackgroundImageResizableLatticeFBoundsBottom: number;
  @Link enableCompBackgroundImageResizableLatticeFColors: boolean;
  @Link compBackgroundImageResizableLatticeFColors: Array<common2D.Color> | null;
  @Link enableCompBackgroundBrightnessRate: boolean;
  @Link compBackgroundBrightnessRate: number;
  @Link enableCompBackgroundBrightnessLightUpDegree: boolean;
  @Link compBackgroundBrightnessLightUpDegree: number;

  build() {
    Column() {
      RadioBlock({
        title: 'background.align',
        isEnabled: $enableCompBackgroundAlign,
        value: $compBackgroundAlign,
        dataSource: [
          { label: 'TopStart', value: Alignment.TopStart },
          { label: 'Top', value: Alignment.Top },
          { label: 'TopEnd', value: Alignment.TopEnd },
          { label: 'Start', value: Alignment.Start },
          { label: 'Center', value: Alignment.Center },
          { label: 'End', value: Alignment.End },
          { label: 'BottomStart', value: Alignment.BottomStart },
          { label: 'Bottom', value: Alignment.Bottom },
          { label: 'BottomEnd', value: Alignment.BottomEnd }
        ]
      })
      ColorBlock({
        title: 'backgroundColor',
        isEnabled: $enableCompBackgroundColor,
        color: $compBackgroundColor
      })
      RadioBlock({
        title: 'backgroundImage.src',
        isEnabled: $enableCompBackgroundImageSrc,
        value: $enableCompBackgroundImageSrc,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      RadioBlock({
        title: 'backgroundImage.repeat',
        isEnabled: $enableCompBackgroundImageRepeat,
        value: $compBackgroundImageRepeat,
        dataSource: [
          { label: 'TopStart', value: ImageRepeat.NoRepeat },
          { label: 'TopStart', value: ImageRepeat.X },
          { label: 'TopStart', value: ImageRepeat.Y },
          { label: 'TopStart', value: ImageRepeat.XY },
        ]
      })
      RadioBlock({
        title: 'backgroundImageSize',
        isEnabled: $enableCompBackgroundImageSize,
        value: $compBackgroundImageSize,
        dataSource: [
          { label: 'Auto', value: ImageSize.Auto },
          { label: 'Cover', value: ImageSize.Cover },
          { label: 'Contain', value: ImageSize.Contain },
          { label: 'FILL', value: ImageSize.FILL }
        ]
      })
      SliderBlock({
        title: 'backgroundImagePosition.x',
        isEnabled: $enableCompBackgroundImagePositionX,
        value: $compBackgroundImagePositionX,
        min: 0,
        max: 300
      })
      SliderBlock({
        title: 'backgroundImagePosition.y',
        isEnabled: $enableCompBackgroundImagePositionY,
        value: $compBackgroundImagePositionY,
        min: 0,
        max: 300
      })
      RadioBlock({
        title: 'backgroundBlurStyle',
        isEnabled: $enableCompBackgroundBlurStyle,
        value: $compBackgroundBlurStyle,
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
          { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
          { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
          { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
          { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK }
        ]
      })
      RadioBlock({
        title: 'backgroundBlurStyleParams.options.params',
        isEnabled: $enableCompBackgroundBlurStyleParams,
        value: $enableCompBackgroundBlurStyleParams,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      if (this.enableCompBackgroundBlurStyleParams) {
        RadioBlock({
          title: 'backgroundBlurStyleParams.options.params.colorMode',
          isEnabled: $enableCompBackgroundBlurStyleParamsColorMode,
          value: $compBackgroundBlurStyleParamsColorMode,
          dataSource: [
            { label: 'SYSTEM', value: ThemeColorMode.SYSTEM },
            { label: 'LIGHT', value: ThemeColorMode.LIGHT },
            { label: 'DARK', value: ThemeColorMode.DARK }
          ]
        })
        RadioBlock({
          title: 'backgroundBlurStyleParams.options.params.adaptiveColor',
          isEnabled: $enableCompBackgroundBlurStyleParamsAdaptiveColor,
          value: $compBackgroundBlurStyleParamsAdaptiveColor,
          dataSource: [
            { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
            { label: 'AVERAGE', value: AdaptiveColor.AVERAGE }
          ]
        })
        SliderBlock({
          title: 'backgroundBlurStyleParams.options.params.blurOptions.left',
          isEnabled: $enableCompBackgroundBlurStyleParamsBlurOptionsLeft,
          value: $compBackgroundBlurStyleParamsBlurOptionsLeft,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'backgroundBlurStyleParams.options.params.blurOptions.right',
          isEnabled: $enableCompBackgroundBlurStyleParamsBlurOptionsRight,
          value: $compBackgroundBlurStyleParamsBlurOptionsRight,
          min: 0,
          max: 100
        })
        //666
        SliderBlock({
          title: 'backgroundBlurStyleParams.options.params.scale',
          isEnabled: $enableCompBackgroundBlurStyleParamsScale,
          value: $compBackgroundBlurStyleParamsScale,
          step: 0.1,
          min: 0,
          max: 1
        })
      }
      SliderBlock({
        title: 'backdropBlur',
        isEnabled: $enableCompBackdropBlur,
        value: $compBackdropBlur,
        min: 0,
        max: 300
      })
      RadioBlock({
        title: 'backdropBlur.options.grayscale',
        isEnabled: $enableCompBackdropBlurGrayscale,
        value: $enableCompBackdropBlurGrayscale,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      if (this.enableCompBackdropBlurGrayscale) {
        SliderBlock({
          title: 'backdropBlur.options.grayscale.left',
          isEnabled: $enableCompBackdropBlurGrayscaleLeft,
          value: $compBackdropBlurGrayscaleLeft,
          min: 0,
          max: 127
        })
        SliderBlock({
          title: 'backdropBlur.options.grayscale.right',
          isEnabled: $enableCompBackdropBlurGrayscaleRight,
          value: $compBackdropBlurGrayscaleRight,
          min: 0,
          max: 127
        })
      }
      RadioBlock({
        title: 'backgroundEffect',
        isEnabled: $enableCompBackgroundEffect,
        value: $enableCompBackgroundEffect,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      if (this.enableCompBackgroundEffect) {
        SliderBlock({
          title: 'backgroundEffect.radius',
          isEnabled: $enableCompBackgroundEffectRadius,
          value: $compBackgroundEffectRadius,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'backgroundEffect.saturation',
          isEnabled: $enableCompBackgroundEffectSaturation,
          value: $compBackgroundEffectSaturation,
          min: 0,
          max: 50
        })
        SliderBlock({
          title: 'backgroundEffect.brightness',
          isEnabled: $enableCompBackgroundEffectBrightness,
          value: $compBackgroundEffectBrightness,
          min: 0,
          max: 2
        })
        ColorBlock({
          title: 'backgroundEffect.color',
          isEnabled: $enableCompBackgroundEffectColor,
          color: $compBackgroundEffectColor,
        })
        RadioBlock({
          title: 'backgroundEffect.adaptiveColor',
          isEnabled: $enableCompBackgroundEffectAdaptiveColor,
          value: $compBackgroundEffectAdaptiveColor,
          dataSource: [
            { label: 'DEFAULT', value: AdaptiveColor.DEFAULT },
            { label: 'AVERAGE', value: AdaptiveColor.AVERAGE }
          ]
        })
        SliderBlock({
          title: 'backgroundEffect.blurOptions.grayscale.left',
          isEnabled: $enableCompBackgroundEffectBlurOptionsGrayscaleLeft,
          value: $compBackgroundEffectBlurOptionsGrayscaleLeft,
          min: 0,
          max: 127
        })
        SliderBlock({
          title: 'backgroundEffect.blurOptions.grayscale.right',
          isEnabled: $enableCompBackgroundEffectBlurOptionsGrayscaleRight,
          value: $compBackgroundEffectBlurOptionsGrayscaleRight,
          min: 0,
          max: 127
        })
      }
      RadioBlock({
        title: 'backgroundImageResizable',
        isEnabled: $enableCompBackgroundImageResizable,
        value: $enableCompBackgroundImageResizable,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      if (this.enableCompBackgroundImageResizable) {
        SliderBlock({
          title: 'backgroundImageResizable.slice.top',
          isEnabled: $enableCompBackgroundImageResizableSliceTop,
          value: $compBackgroundImageResizableSliceTop,
          min: 0,
          max: 300
        })
        SliderBlock({
          title: 'backgroundImageResizable.slice.bottom',
          isEnabled: $enableCompBackgroundImageResizableSliceBottom,
          value: $compBackgroundImageResizableSliceBottom,
          min: 0,
          max: 300
        })
        SliderBlock({
          title: 'backgroundImageResizable.slice.left',
          isEnabled: $enableCompBackgroundImageResizableSliceLeft,
          value: $compBackgroundImageResizableSliceLeft,
          min: 0,
          max: 300
        })
        SliderBlock({
          title: 'backgroundImageResizable.slice.right',
          isEnabled: $enableCompBackgroundImageResizableSliceRight,
          value: $compBackgroundImageResizableSliceRight,
          min: 0,
          max: 300
        })
        RadioBlock({
          title: 'backgroundImageResizable.lattice',
          isEnabled: $enableCompBackgroundImageResizableLattice,
          value: $enableCompBackgroundImageResizableLattice,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        if (this.enableCompBackgroundImageResizableLattice) {
          RadioBlock({
            title: 'backgroundImageResizable.lattice.xDivs',
            isEnabled: $enableCompBackgroundImageResizableLatticeXDivs,
            value: $compBackgroundImageResizableLatticeXDivs,
            dataSource: [
              { label: '[1, 2, 3]', value: [1, 2, 3] },
              { label: '[3, 4, 5]', value: [3, 4, 5] },
              { label: '[5, 6, 3]', value: [5, 6, 3] },
            ]
          })
          //666
          RadioBlock({
            title: 'backgroundImageResizable.lattice.yDivs',
            isEnabled: $enableCompBackgroundImageResizableLatticeYDivs,
            value: $compBackgroundImageResizableLatticeYDivs,
            dataSource: [
              { label: '[1, 2, 3]', value: [1, 2, 3] },
              { label: '[3, 4, 5]', value: [3, 4, 5] },
              { label: '[5, 6, 3]', value: [5, 6, 3] },
            ]
          })
          SliderBlock({
            title: 'backgroundImageResizable.lattice.fXCount',
            isEnabled: $enableCompBackgroundImageResizableLatticeFXCount,
            value: $compBackgroundImageResizableLatticeFXCount,
            min: 0,
            max: 5
          })
          SliderBlock({
            title: 'backgroundImageResizable.lattice.fYCount',
            isEnabled: $enableCompBackgroundImageResizableLatticeFYCount,
            value: $compBackgroundImageResizableLatticeFYCount,
            min: 0,
            max: 5
          })
          RadioBlock({
            title: 'backgroundImageResizable.lattice.fBounds',
            isEnabled: $enableCompBackgroundImageResizableLatticeFBounds,
            value: $enableCompBackgroundImageResizableLatticeFBounds,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
          if (this.enableCompBackgroundImageResizableLatticeFBounds) {
            SliderBlock({
              title: 'backgroundImageResizable.lattice.fBounds.left',
              isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsLeft,
              value: $compBackgroundImageResizableLatticeFBoundsLeft,
              min: 0,
              max: 100
            })
            SliderBlock({
              title: 'backgroundImageResizable.lattice.fBounds.top',
              isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsTop,
              value: $compBackgroundImageResizableLatticeFBoundsTop,
              min: 0,
              max: 100
            })
            SliderBlock({
              title: 'backgroundImageResizable.lattice.fBounds.right',
              isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsRight,
              value: $compBackgroundImageResizableLatticeFBoundsRight,
              min: 0,
              max: 100
            })
            SliderBlock({
              title: 'backgroundImageResizable.lattice.fBounds.bottom',
              isEnabled: $enableCompBackgroundImageResizableLatticeFBoundsBottom,
              value: $compBackgroundImageResizableLatticeFBoundsBottom,
              min: 0,
              max: 100
            })
          }
          RadioBlock({
            title: 'backgroundImageResizable.lattice.fColors',
            isEnabled: $enableCompBackgroundImageResizableLatticeFColors,
            value: $compBackgroundImageResizableLatticeFColors,
            dataSource: [
              { label: '[{alpha:0,red:0,green:0,blue:0}]', value: ['#00000000'] },
              { label: '[{alpha:100,red:100,green:100,blue:100}]', value: ['#64646464'] },
              { label: '[{alpha:255,red:255,green:255,blue:255}]', value: ['#ffffffff'] }
            ]
          })
        }
      }

      SliderBlock({
        title: 'backgroundBrightness.rate',
        isEnabled: $enableCompBackgroundBrightnessRate,
        value: $compBackgroundBrightnessRate,
        step: 0.1,
        min: 0,
        max: 5
      })

      SliderBlock({
        title: 'backgroundBrightness.lightUpDegree',
        isEnabled: $enableCompBackgroundBrightnessLightUpDegree,
        value: $compBackgroundBrightnessLightUpDegree,
        step: 0.1,
        min: -1,
        max: 1
      })
    }
  }
}