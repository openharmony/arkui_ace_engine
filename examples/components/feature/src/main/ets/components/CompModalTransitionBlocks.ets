import { RadioBlock, SliderBlock } from 'common';


@Component
export struct CompModalTransitionBlocks {
  @Link enableCompBindContentCoverIsShow: boolean;
  @Link compBindContentCoverIsShow: boolean;
  @Link enableCompBindContentCoverOptionsModalTransition: boolean;
  @Link compBindContentCoverOptionsModalTransition: ModalTransition;
  @Link enableCompBindContentCoverOptionsTransitionOpacity: boolean;
  @Link compBindContentCoverOptionsTransitionOpacity: number;
  @Link enableCompBindContentCoverOptionsTransitionTranslateX: boolean;
  @Link compBindContentCoverOptionsTransitionTranslateX: number;
  @Link enableCompBindContentCoverOptionsTransitionTranslateY: boolean;
  @Link compBindContentCoverOptionsTransitionTranslateY: number;
  @Link enableCompBindContentCoverOptionsTransitionTranslateZ: boolean;
  @Link compBindContentCoverOptionsTransitionTranslateZ: number;
  @Link enableCompBindContentCoverOptionsTransitionScaleX: boolean;
  @Link compBindContentCoverOptionsTransitionScaleX: number;
  @Link enableCompBindContentCoverOptionsTransitionScaleY: boolean;
  @Link compBindContentCoverOptionsTransitionScaleY: number;
  @Link enableCompBindContentCoverOptionsTransitionScaleZ: boolean;
  @Link compBindContentCoverOptionsTransitionScaleZ: number;
  @Link enableCompBindContentCoverOptionsTransitionScaleCenterX: boolean;
  @Link compBindContentCoverOptionsTransitionScaleCenterX: number;
  @Link enableCompBindContentCoverOptionsTransitionScaleCenterY: boolean;
  @Link compBindContentCoverOptionsTransitionScaleCenterY: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateX: boolean;
  @Link compBindContentCoverOptionsTransitionRotateX: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateY: boolean;
  @Link compBindContentCoverOptionsTransitionRotateY: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateZ: boolean;
  @Link compBindContentCoverOptionsTransitionRotateZ: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateAngle: boolean;
  @Link compBindContentCoverOptionsTransitionRotateAngle: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateCenterX: boolean;
  @Link compBindContentCoverOptionsTransitionRotateCenterX: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateCenterY: boolean;
  @Link compBindContentCoverOptionsTransitionRotateCenterY: number;
  @Link enableCompBindContentCoverOptionsTransitionRotateCenterZ: boolean;
  @Link compBindContentCoverOptionsTransitionRotateCenterZ: number;
  @Link enableCompBindContentCoverOptionsTransitionRotatePerspective: boolean;
  @Link compBindContentCoverOptionsTransitionRotatePerspective: number;
  @Link enableCompBindContentCoverOptionsTransitionMove: boolean;
  @Link compBindContentCoverOptionsTransitionMove: TransitionEdge;
  @Link enableCompBindContentCoverOptionsTransitionAnimationDuration: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationDuration: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationTempo: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationTempo: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationCurve: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationCurve: Curve;
  @Link enableCompBindContentCoverOptionsTransitionAnimationDelay: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationDelay: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationIterations: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationIterations: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationPlayMode: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationPlayMode: PlayMode;
  @Link enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax: number;
  @Link enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected: boolean;
  @Link compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected: number;

  build() {
    Column() {
      RadioBlock({
        title: 'bindContentCover.isShow',
        isEnabled: $enableCompBindContentCoverIsShow,
        value: $compBindContentCoverIsShow,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false },
        ]
      })
      if (this.enableCompBindContentCoverIsShow) {
        RadioBlock({
          title: 'bindContentCover.options.modalTransition',
          isEnabled: $enableCompBindContentCoverOptionsModalTransition,
          value: $compBindContentCoverOptionsModalTransition,
          dataSource: [
            { label: 'DEFAULT', value: ModalTransition.DEFAULT },
            { label: 'NONE', value: ModalTransition.NONE },
            { label: 'ALPHA', value: ModalTransition.ALPHA },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.opacity',
          isEnabled: $enableCompBindContentCoverOptionsTransitionOpacity,
          value: $compBindContentCoverOptionsTransitionOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.x',
          isEnabled: $enableCompBindContentCoverOptionsTransitionTranslateX,
          value: $compBindContentCoverOptionsTransitionTranslateX,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.y',
          isEnabled: $enableCompBindContentCoverOptionsTransitionTranslateY,
          value: $compBindContentCoverOptionsTransitionTranslateY,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.z',
          isEnabled: $enableCompBindContentCoverOptionsTransitionTranslateZ,
          value: $compBindContentCoverOptionsTransitionTranslateZ,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.x',
          isEnabled: $enableCompBindContentCoverOptionsTransitionScaleX,
          value: $compBindContentCoverOptionsTransitionScaleX,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.y',
          isEnabled: $enableCompBindContentCoverOptionsTransitionScaleY,
          value: $compBindContentCoverOptionsTransitionScaleY,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.z',
          isEnabled: $enableCompBindContentCoverOptionsTransitionScaleZ,
          value: $compBindContentCoverOptionsTransitionScaleZ,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.centerX',
          isEnabled: $enableCompBindContentCoverOptionsTransitionScaleCenterX,
          value: $compBindContentCoverOptionsTransitionScaleCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.centerY',
          isEnabled: $enableCompBindContentCoverOptionsTransitionScaleCenterY,
          value: $compBindContentCoverOptionsTransitionScaleCenterY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.x',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateX,
          value: $compBindContentCoverOptionsTransitionRotateX,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.y',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateY,
          value: $compBindContentCoverOptionsTransitionRotateY,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.z',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateZ,
          value: $compBindContentCoverOptionsTransitionRotateZ,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerX',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateCenterX,
          value: $compBindContentCoverOptionsTransitionRotateCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerY',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateCenterY,
          value: $compBindContentCoverOptionsTransitionRotateCenterY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerZ',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotateCenterZ,
          value: $compBindContentCoverOptionsTransitionRotateCenterZ,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.perspective',
          isEnabled: $enableCompBindContentCoverOptionsTransitionRotatePerspective,
          value: $compBindContentCoverOptionsTransitionRotatePerspective,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.move',
          isEnabled: $enableCompBindContentCoverOptionsTransitionMove,
          value: $compBindContentCoverOptionsTransitionMove,
          dataSource: [
            { label: 'TOP', value: TransitionEdge.TOP },
            { label: 'BOTTOM', value: TransitionEdge.BOTTOM },
            { label: 'START', value: TransitionEdge.START },
            { label: 'END', value: TransitionEdge.END },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.duration',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationDuration,
          value: $compBindContentCoverOptionsTransitionAnimationDuration,
          min: 0,
          max: 5000
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.tempo',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationTempo,
          value: $compBindContentCoverOptionsTransitionAnimationTempo,
          min: 0,
          max: 3.0,
          step: 0.1
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.animation.curve',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationCurve,
          value: $compBindContentCoverOptionsTransitionAnimationCurve,
          dataSource: [
            { label: 'Linear', value: Curve.Linear },
            { label: 'Ease', value: Curve.Ease },
            { label: 'EaseIn', value: Curve.EaseIn },
            { label: 'EaseOut', value: Curve.EaseOut },
            { label: 'EaseInOut', value: Curve.EaseInOut },
            { label: 'FastOutSlowIn', value: Curve.FastOutSlowIn },
            { label: 'LinearOutSlowIn', value: Curve.LinearOutSlowIn },
            { label: 'FastOutLinearIn', value: Curve.FastOutLinearIn },
            { label: 'ExtremeDeceleration', value: Curve.ExtremeDeceleration },
            { label: 'Sharp', value: Curve.Sharp },
            { label: 'Rhythm', value: Curve.Rhythm },
            { label: 'Smooth', value: Curve.Smooth },
            { label: 'Friction', value: Curve.Friction },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.delay',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationDelay,
          value: $compBindContentCoverOptionsTransitionAnimationDelay,
          min: -5000,
          max: 5000,
          step: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.iterations',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationIterations,
          value: $compBindContentCoverOptionsTransitionAnimationIterations,
          min: -1,
          max: 20
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.animation.playMode',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationPlayMode,
          value: $compBindContentCoverOptionsTransitionAnimationPlayMode,
          dataSource: [
            { label: 'Normal', value: PlayMode.Normal },
            { label: 'Reverse', value: PlayMode.Reverse },
            { label: 'Alternate', value: PlayMode.Alternate },
            { label: 'AlternateReverse', value: PlayMode.AlternateReverse },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.max',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax,
          value: $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMax,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.min',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin,
          value: $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeMin,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected',
          isEnabled: $enableCompBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected,
          value: $compBindContentCoverOptionsTransitionAnimationExpectedFrameRateRangeExpected,
          min: 0,
          max: 300
        })
      }
    }
  }
}