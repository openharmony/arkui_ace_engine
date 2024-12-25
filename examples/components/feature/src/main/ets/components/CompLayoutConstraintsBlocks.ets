import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompLayoutConstraintsBlocks {
  @Link enableCompAspectRatio: boolean;
  @Link compAspectRatio: number;
  @Link enableCompPixelRound: boolean;
  @Link enableCompPixelRoundStart: boolean;
  @Link compPixelRoundStart: PixelRoundCalcPolicy;
  @Link enableCompPixelRoundTop: boolean;
  @Link compPixelRoundTop: PixelRoundCalcPolicy;
  @Link enableCompPixelRoundEnd: boolean;
  @Link compPixelRoundEnd: PixelRoundCalcPolicy;
  @Link enableCompPixelRoundBottom: boolean;
  @Link compPixelRoundBottom: PixelRoundCalcPolicy;

  build() {
    Column() {
      SliderBlock({
        title: 'aspectRatio',
        isEnabled: $enableCompAspectRatio,
        value: $compAspectRatio,
        min: 0,
        max: 5
      })
      RadioBlock({
        title: 'pixelRound',
        isEnabled: $enableCompPixelRound,
        value: $enableCompPixelRound,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
      if (this.enableCompPixelRound) {
        RadioBlock({
          title: 'pixelRound.start',
          isEnabled: $enableCompPixelRoundStart,
          value: $compPixelRoundStart,
          dataSource: [
            { label: 'NO_FORCE_ROUND', value: PixelRoundCalcPolicy.NO_FORCE_ROUND },
            { label: 'FORCE_CEIL', value: PixelRoundCalcPolicy.FORCE_CEIL },
            { label: 'FORCE_FLOOR', value: PixelRoundCalcPolicy.FORCE_FLOOR }
          ]
        })

        RadioBlock({
          title: 'pixelRound.bottom',
          isEnabled: $enableCompPixelRoundBottom,
          value: $compPixelRoundBottom,
          dataSource: [
            { label: 'NO_FORCE_ROUND', value: PixelRoundCalcPolicy.NO_FORCE_ROUND },
            { label: 'FORCE_CEIL', value: PixelRoundCalcPolicy.FORCE_CEIL },
            { label: 'FORCE_FLOOR', value: PixelRoundCalcPolicy.FORCE_FLOOR }
          ]
        })

        RadioBlock({
          title: 'pixelRound.top',
          isEnabled: $enableCompPixelRoundTop,
          value: $compPixelRoundTop,
          dataSource: [
            { label: 'NO_FORCE_ROUND', value: PixelRoundCalcPolicy.NO_FORCE_ROUND },
            { label: 'FORCE_CEIL', value: PixelRoundCalcPolicy.FORCE_CEIL },
            { label: 'FORCE_FLOOR', value: PixelRoundCalcPolicy.FORCE_FLOOR }
          ]
        })

        RadioBlock({
          title: 'pixelRound.end',
          isEnabled: $enableCompPixelRoundEnd,
          value: $compPixelRoundEnd,
          dataSource: [
            { label: 'NO_FORCE_ROUND', value: PixelRoundCalcPolicy.NO_FORCE_ROUND },
            { label: 'FORCE_CEIL', value: PixelRoundCalcPolicy.FORCE_CEIL },
            { label: 'FORCE_FLOOR', value: PixelRoundCalcPolicy.FORCE_FLOOR }
          ]
        })
      }
    }
  }
}
