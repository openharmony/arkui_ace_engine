import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompBorderImageBlocks {
  @Link enableCompBorderImage: boolean;
  @Link enableCompBorderImageSource: boolean;
  @Link enableCompBorderImageSlice: boolean;
  @Link enableCompBorderImageSliceTop: boolean;
  @Link compBorderImageSliceTop: Length;
  @Link enableCompBorderImageSliceBottom: boolean;
  @Link compBorderImageSliceBottom: Length;
  @Link enableCompBorderImageSliceLeft: boolean;
  @Link compBorderImageSliceLeft: Length;
  @Link enableCompBorderImageSliceRight: boolean;
  @Link compBorderImageSliceRight: Length;
  @Link enableCompBorderImageWidth: boolean;
  @Link enableCompBorderImageWidthTop: boolean;
  @Link compBorderImageWidthTop: Length;
  @Link enableCompBorderImageWidthBottom: boolean;
  @Link compBorderImageWidthBottom: Length;
  @Link enableCompBorderImageWidthLeft: boolean;
  @Link compBorderImageWidthLeft: Length;
  @Link enableCompBorderImageWidthRight: boolean;
  @Link compBorderImageWidthRight: Length;
  @Link enableCompBorderImageOutset: boolean;
  @Link enableCompBorderImageOutsetTop: boolean;
  @Link compBorderImageOutsetTop: Length;
  @Link enableCompBorderImageOutsetBottom: boolean;
  @Link compBorderImageOutsetBottom: Length;
  @Link enableCompBorderImageOutsetLeft: boolean;
  @Link compBorderImageOutsetLeft: Length;
  @Link enableCompBorderImageOutsetRight: boolean;
  @Link compBorderImageOutsetRight: Length;
  @Link enableCompBorderImageRepeat: boolean;
  @Link compBorderImageRepeat: RepeatMode;
  @Link enableCompBorderImageFill: boolean;
  @Link compBorderImageFill: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'borderImage',
        isEnabled: $enableCompBorderImage,
        value: $enableCompBorderImage,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompBorderImage) {
        RadioBlock({
          title: 'borderImage.source',
          isEnabled: $enableCompBorderImageSource,
          value: $enableCompBorderImageSource,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'borderImage.slice',
          isEnabled: $enableCompBorderImageSlice,
          value: $enableCompBorderImageSlice,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBorderImageSlice) {
          SliderBlock({
            title: 'borderImage.slice.top',
            isEnabled: $enableCompBorderImageSliceTop,
            value: $compBorderImageSliceTop,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.slice.bottom',
            isEnabled: $enableCompBorderImageSliceBottom,
            value: $compBorderImageSliceBottom,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.slice.left',
            isEnabled: $enableCompBorderImageSliceLeft,
            value: $compBorderImageSliceLeft,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.slice.right',
            isEnabled: $enableCompBorderImageSliceRight,
            value: $compBorderImageSliceRight,
            min: 0,
            max: 300
          })
        }

        RadioBlock({
          title: 'borderImage.width',
          isEnabled: $enableCompBorderImageWidth,
          value: $enableCompBorderImageWidth,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBorderImageWidth) {
          SliderBlock({
            title: 'borderImage.width.top',
            isEnabled: $enableCompBorderImageWidthTop,
            value: $compBorderImageWidthTop,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.width.bottom',
            isEnabled: $enableCompBorderImageWidthBottom,
            value: $compBorderImageWidthBottom,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.width.left',
            isEnabled: $enableCompBorderImageWidthLeft,
            value: $compBorderImageWidthLeft,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.width.right',
            isEnabled: $enableCompBorderImageWidthRight,
            value: $compBorderImageWidthRight,
            min: 0,
            max: 300
          })
        }

        RadioBlock({
          title: 'borderImage.outset',
          isEnabled: $enableCompBorderImageOutset,
          value: $enableCompBorderImageOutset,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        if (this.enableCompBorderImageOutset) {
          SliderBlock({
            title: 'borderImage.outset.top',
            isEnabled: $enableCompBorderImageOutsetTop,
            value: $compBorderImageOutsetTop,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.outset.bottom',
            isEnabled: $enableCompBorderImageOutsetBottom,
            value: $compBorderImageOutsetBottom,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.outset.left',
            isEnabled: $enableCompBorderImageOutsetLeft,
            value: $compBorderImageOutsetLeft,
            min: 0,
            max: 300
          })

          SliderBlock({
            title: 'borderImage.outset.right',
            isEnabled: $enableCompBorderImageOutsetRight,
            value: $compBorderImageOutsetRight,
            min: 0,
            max: 300
          })
        }

        RadioBlock({
          title: 'borderImage.repeat',
          isEnabled: $enableCompBorderImageRepeat,
          value: $compBorderImageRepeat,
          dataSource: [
            { label: 'Repeat', value: RepeatMode.Repeat },
            { label: 'Stretch', value: RepeatMode.Stretch },
            { label: 'Round', value: RepeatMode.Round },
            { label: 'Space', value: RepeatMode.Space }
          ]
        })

        RadioBlock({
          title: 'borderImage.fill',
          isEnabled: $enableCompBorderImageFill,
          value: $enableCompBorderImageFill,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
    }
  }
}