import { ColorBlock, Drawer, RadioBlock, SliderBlock, useEnabled } from 'common'
import { BlockTag } from 'common/src/main/ets/model/BlockTag';
import { formatDate } from 'common/src/main/ets/utils/timeUtil';


@Component
export struct BindContentCoverBootcamp {
  @Require @Prop title: ResourceStr
  @State showParameters: boolean = false;
  @State isShowBindContentCover: boolean = false;
  @State enableModalTransition: boolean = false;
  @State modalTransition: ModalTransition = ModalTransition.DEFAULT;
  @State enableBackgroundColorColor: boolean = false;
  @State backgroundColorColor: ResourceColor = Color.Orange;
  @State enableTransitionOpacity: boolean = false;
  @State transitionOpacity: number = 1;
  @State enableTransitionTranslateX: boolean = false;
  @State transitionTranslateX: number = 0;
  @State enableTransitionTranslateY: boolean = false;
  @State transitionTranslateY: number = 0;
  @State enableTransitionTranslateZ: boolean = false;
  @State transitionTranslateZ: number = 0;
  @State enableTransitionScaleX: boolean = false;
  @State transitionScaleX: number = 0;
  @State enableTransitionScaleY: boolean = false;
  @State transitionScaleY: number = 0;
  @State enableTransitionScaleZ: boolean = false;
  @State transitionScaleZ: number = 0;
  @State enableTransitionScaleCenterX: boolean = false;
  @State transitionScaleCenterX: number = 50;
  @State enableTransitionScaleCenterY: boolean = false;
  @State transitionScaleCenterY: number = 50;
  @State enableTransitionRotateX: boolean = false;
  @State transitionRotateX: number = 0;
  @State enableTransitionRotateY: boolean = false;
  @State transitionRotateY: number = 0;
  @State enableTransitionRotateZ: boolean = false;
  @State transitionRotateZ: number = 0;
  @State enableTransitionRotateAngle: boolean = false;
  @State transitionRotateAngle: number = 0;
  @State enableTransitionRotateCenterX: boolean = false;
  @State transitionRotateCenterX: number = 50;
  @State enableTransitionRotateCenterY: boolean = false;
  @State transitionRotateCenterY: number = 50;
  @State enableTransitionRotateCenterZ: boolean = false;
  @State transitionRotateCenterZ: number = 0;
  @State enableTransitionRotatePerspective: boolean = false;
  @State transitionRotatePerspective: number = 0;
  @State enableTransitionMove: boolean = false;
  @State transitionMove: TransitionEdge = TransitionEdge.TOP;
  @State enableTransitionAnimationDuration: boolean = false;
  @State transitionAnimationDuration: number = 1000;
  @State enableTransitionAnimationTempo: boolean = false;
  @State transitionAnimationTempo: number = 1.0;
  @State enableTransitionAnimationCurve: boolean = false;
  @State transitionAnimationCurve: Curve = Curve.EaseInOut;
  @State enableTransitionAnimationDelay: boolean = false;
  @State transitionAnimationDelay: number = 0;
  @State enableTransitionAnimationIterations: boolean = false;
  @State transitionAnimationIterations: number = 1;
  @State enableTransitionAnimationPlayMode: boolean = false;
  @State transitionAnimationPlayMode: PlayMode = PlayMode.Normal;
  @State enableTransitionAnimationExpectedFrameRateRangeMin: boolean = false;
  @State transitionAnimationExpectedFrameRateRangeMin: number = 60;
  @State enableTransitionAnimationExpectedFrameRateRangeMax: boolean = false;
  @State transitionAnimationExpectedFrameRateRangeMax: number = 60;
  @State enableTransitionAnimationExpectedFrameRateRangeExpected: boolean = false;
  @State transitionAnimationExpectedFrameRateRangeExpected: number = 60;
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
      Button('点击唤出全模态界面')
        .onClick(() => {
          this.isShowBindContentCover = true;
        })
        .bindContentCover($$this.isShowBindContentCover, this.SheetBuilder(), {
          modalTransition: useEnabled(this.enableModalTransition, this.modalTransition),
          backgroundColor: useEnabled(this.enableBackgroundColorColor, this.backgroundColorColor),
          onWillDismiss: (dismissContentCoverAction: DismissContentCoverAction) => {
            if (dismissContentCoverAction.reason == DismissReason.PRESS_BACK) {
              this.compEventTriggeredLog('BindContentCover: onWillDismiss()')
            }
            dismissContentCoverAction.dismiss()
          },
          onWillAppear: () => {
            this.compEventTriggeredLog('BindContentCover:onWillAppear()')
          },
          onAppear: () => {
            this.compEventTriggeredLog('BindContentCover:onAppear()')
          },
          onWillDisappear: () => {
            this.compEventTriggeredLog('BindContentCover:onWillDisappear()')
          },
          onDisappear: () => {
            this.compEventTriggeredLog('BindContentCover:onDisappear()')
          },
          transition: TransitionEffect.opacity(useEnabled(this.enableTransitionOpacity,
            this.transitionOpacity))
            .combine(TransitionEffect.translate({
              x: useEnabled(this.enableTransitionTranslateX,
                this.transitionTranslateX),
              y: useEnabled(this.enableTransitionTranslateY,
                this.transitionTranslateY),
              z: useEnabled(this.enableTransitionTranslateZ,
                this.transitionTranslateZ),
            }))
            .combine(TransitionEffect.scale({
              x: useEnabled(this.enableTransitionScaleX,
                this.transitionScaleX),
              y: useEnabled(this.enableTransitionScaleY,
                this.transitionScaleY),
              z: useEnabled(this.enableTransitionScaleZ,
                this.transitionScaleZ),
              centerX: useEnabled(this.enableTransitionScaleCenterX,
                this.transitionScaleCenterX) + '%',
              centerY: useEnabled(this.enableTransitionScaleCenterY,
                this.transitionScaleCenterY) + '%',
            }))
            .combine(TransitionEffect.rotate({
              x: useEnabled(this.enableTransitionRotateX,
                this.transitionRotateX),
              y: useEnabled(this.enableTransitionRotateY,
                this.transitionRotateY),
              z: useEnabled(this.enableTransitionRotateZ,
                this.transitionRotateZ),
              angle:
              useEnabled(this.enableTransitionRotateAngle,
                this.transitionRotateAngle),
              centerX:
              useEnabled(this.enableTransitionRotateCenterX,
                this.transitionRotateCenterX) + '%',
              centerY:
              useEnabled(this.enableTransitionRotateCenterY,
                this.transitionRotateCenterY) + '%',
              centerZ:
              useEnabled(this.enableTransitionRotateCenterZ,
                this.transitionRotateCenterZ),
              perspective:
              useEnabled(this.enableTransitionRotatePerspective,
                this.transitionRotatePerspective)
            }))
            .combine(TransitionEffect.move(
              useEnabled(this.enableTransitionMove,
                this.transitionMove)))
            .animation({
              duration:
              useEnabled(this.enableTransitionAnimationDuration,
                this.transitionAnimationDuration),
              tempo:
              useEnabled(this.enableTransitionAnimationTempo,
                this.transitionAnimationTempo),
              curve:
              useEnabled(this.enableTransitionAnimationCurve,
                this.transitionAnimationCurve),
              delay:
              useEnabled(this.enableTransitionAnimationDelay,
                this.transitionAnimationDelay),
              iterations:
              useEnabled(this.enableTransitionAnimationIterations,
                this.transitionAnimationIterations),
              playMode:
              useEnabled(this.enableTransitionAnimationPlayMode,
                this.transitionAnimationPlayMode),
              expectedFrameRateRange: {
                max:
                useEnabled(this.enableTransitionAnimationExpectedFrameRateRangeMax,
                  this.transitionAnimationExpectedFrameRateRangeMax),
                min:
                useEnabled(this.enableTransitionAnimationExpectedFrameRateRangeMin,
                  this.transitionAnimationExpectedFrameRateRangeMin),
                expected:
                useEnabled(this.enableTransitionAnimationExpectedFrameRateRangeExpected,
                  this.transitionAnimationExpectedFrameRateRangeExpected),
              }
            })
        })
    }
  }

  @Builder
  SheetBuilder() {
    Column() {
      Text(this.title)
      Button('close')
        .onClick((event: ClickEvent) => {
          this.isShowBindContentCover = false
        })
    }.width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'bindContentCover.options.modalTransition',
          isEnabled: $enableModalTransition,
          value: $modalTransition,
          dataSource: [
            { label: 'DEFAULT', value: ModalTransition.DEFAULT },
            { label: 'NONE', value: ModalTransition.NONE },
            { label: 'ALPHA', value: ModalTransition.ALPHA },
          ]
        })

        ColorBlock({
          title: 'backGroundColor',
          isEnabled: this.enableBackgroundColorColor,
          color: this.backgroundColorColor,
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.opacity',
          isEnabled: $enableTransitionOpacity,
          value: $transitionOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.x',
          isEnabled: $enableTransitionTranslateX,
          value: $transitionTranslateX,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.y',
          isEnabled: $enableTransitionTranslateY,
          value: $transitionTranslateY,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.translate.z',
          isEnabled: $enableTransitionTranslateZ,
          value: $transitionTranslateZ,
          min: -200,
          max: 200
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.x',
          isEnabled: $enableTransitionScaleX,
          value: $transitionScaleX,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.y',
          isEnabled: $enableTransitionScaleY,
          value: $transitionScaleY,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.z',
          isEnabled: $enableTransitionScaleZ,
          value: $transitionScaleZ,
          min: -10,
          max: 10
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.centerX',
          isEnabled: $enableTransitionScaleCenterX,
          value: $transitionScaleCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.scale.centerY',
          isEnabled: $enableTransitionScaleCenterY,
          value: $transitionScaleCenterY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.x',
          isEnabled: $enableTransitionRotateX,
          value: $transitionRotateX,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.y',
          isEnabled: $enableTransitionRotateY,
          value: $transitionRotateY,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.z',
          isEnabled: $enableTransitionRotateZ,
          value: $transitionRotateZ,
          min: -180,
          max: 180
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerX',
          isEnabled: $enableTransitionRotateCenterX,
          value: $transitionRotateCenterX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerY',
          isEnabled: $enableTransitionRotateCenterY,
          value: $transitionRotateCenterY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.centerZ',
          isEnabled: $enableTransitionRotateCenterZ,
          value: $transitionRotateCenterZ,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.rotate.perspective',
          isEnabled: $enableTransitionRotatePerspective,
          value: $transitionRotatePerspective,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.move',
          isEnabled: $enableTransitionMove,
          value: $transitionMove,
          dataSource: [
            { label: 'TOP', value: TransitionEdge.TOP },
            { label: 'BOTTOM', value: TransitionEdge.BOTTOM },
            { label: 'START', value: TransitionEdge.START },
            { label: 'END', value: TransitionEdge.END },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.duration',
          isEnabled: $enableTransitionAnimationDuration,
          value: $transitionAnimationDuration,
          min: 0,
          max: 5000
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.tempo',
          isEnabled: $enableTransitionAnimationTempo,
          value: $transitionAnimationTempo,
          min: 0,
          max: 3.0,
          step: 0.1
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.animation.curve',
          isEnabled: $enableTransitionAnimationCurve,
          value: $transitionAnimationCurve,
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
          isEnabled: $enableTransitionAnimationDelay,
          value: $transitionAnimationDelay,
          min: -5000,
          max: 5000,
          step: 100
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.iterations',
          isEnabled: $enableTransitionAnimationIterations,
          value: $transitionAnimationIterations,
          min: -1,
          max: 20
        })

        RadioBlock({
          title: 'bindContentCover.options.transition.animation.playMode',
          isEnabled: $enableTransitionAnimationPlayMode,
          value: $transitionAnimationPlayMode,
          dataSource: [
            { label: 'Normal', value: PlayMode.Normal },
            { label: 'Reverse', value: PlayMode.Reverse },
            { label: 'Alternate', value: PlayMode.Alternate },
            { label: 'AlternateReverse', value: PlayMode.AlternateReverse },
          ]
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.max',
          isEnabled: $enableTransitionAnimationExpectedFrameRateRangeMax,
          value: $transitionAnimationExpectedFrameRateRangeMax,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.min',
          isEnabled: $enableTransitionAnimationExpectedFrameRateRangeMin,
          value: $transitionAnimationExpectedFrameRateRangeMin,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected',
          isEnabled: $enableTransitionAnimationExpectedFrameRateRangeExpected,
          value: $transitionAnimationExpectedFrameRateRangeExpected,
          min: 0,
          max: 300
        })

      }
    }.height('50%').id('scroll')

  }

  @Builder
  Generic() {

  }
}

@Preview
@Component
struct BindContentCoverBootcampPreviewer {
  build() {
    BindContentCoverBootcamp({
      title: '全模态/BindContentCover'
    })
  }
}