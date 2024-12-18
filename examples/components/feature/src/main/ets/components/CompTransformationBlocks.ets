import { RadioBlock, SliderBlock } from 'common';

@Component
export struct CompTransformationBlocks {
  @Link enableCompRotate: boolean;
  @Link enableCompRotateX: boolean;
  @Link compRotateX: number;
  @Link enableCompRotateY: boolean;
  @Link compRotateY: number;
  @Link enableCompRotateZ: boolean;
  @Link compRotateZ: number;
  @Link enableCompRotateAngle: boolean;
  @Link compRotateAngle: number;
  @Link enableCompRotateCenterX: boolean;
  @Link compRotateCenterX: number;
  @Link enableCompRotateCenterY: boolean;
  @Link compRotateCenterY: number;
  @Link enableCompRotateCenterZ: boolean;
  @Link compRotateCenterZ: number;
  @Link enableCompRotatePerspective: boolean;
  @Link compRotatePerspective: number;
  @Link enableCompTranslate: boolean;
  @Link enableCompTranslateX: boolean;
  @Link compTranslateX: number;
  @Link enableCompTranslateY: boolean;
  @Link compTranslateY: number;
  @Link enableCompTranslateZ: boolean;
  @Link compTranslateZ: number;
  @Link enableCompScale: boolean;
  @Link enableCompScaleX: boolean;
  @Link compScaleX: number;
  @Link enableCompScaleY: boolean;
  @Link compScaleY: number;
  @Link enableCompScaleZ: boolean;
  @Link compScaleZ: number;
  @Link enableCompScaleCenterX: boolean;
  @Link compScaleCenterX: number;
  @Link enableCompScaleCenterY: boolean;
  @Link compScaleCenterY: number;
  @Link enableCompTransform: boolean;

  build() {
    Column() {
      RadioBlock({
        title: 'rotate',
        isEnabled: $enableCompRotate,
        value: $enableCompRotate,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompRotate) {
        SliderBlock({
          title: 'rotate.x',
          isEnabled: $enableCompRotateX,
          value: $compRotateX,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.y',
          isEnabled: $enableCompRotateY,
          value: $compRotateY,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.z',
          isEnabled: $enableCompRotateZ,
          value: $compRotateZ,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.angle',
          isEnabled: $enableCompRotateAngle,
          value: $compRotateAngle,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.centerX',
          isEnabled: $enableCompRotateCenterX,
          value: $compRotateCenterX,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.centerY',
          isEnabled: $enableCompRotateCenterY,
          value: $compRotateCenterY,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.centerZ',
          isEnabled: $enableCompRotateCenterZ,
          value: $compRotateCenterZ,
          min: 0,
          max: 360
        })

        SliderBlock({
          title: 'rotate.perspective',
          isEnabled: $enableCompRotatePerspective,
          value: $compRotatePerspective,
          min: 0,
          max: 360
        })
      }

      RadioBlock({
        title: 'translate',
        isEnabled: $enableCompTranslate,
        value: $enableCompTranslate,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompTranslate) {
        SliderBlock({
          title: 'translate.x',
          isEnabled: $enableCompTranslateX,
          value: $compTranslateX,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'translate.y',
          isEnabled: $enableCompTranslateY,
          value: $compTranslateY,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'translate.z',
          isEnabled: $enableCompTranslateZ,
          value: $compTranslateZ,
          min: 0,
          max: 300
        })
      }

      RadioBlock({
        title: 'scale',
        isEnabled: $enableCompScale,
        value: $enableCompScale,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })

      if (this.enableCompScale) {
        SliderBlock({
          title: 'scale.x',
          isEnabled: $enableCompScaleX,
          value: $compScaleX,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'scale.y',
          isEnabled: $enableCompScaleY,
          value: $compScaleY,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'scale.z',
          isEnabled: $enableCompScaleZ,
          value: $compScaleZ,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'scale.centerX',
          isEnabled: $enableCompScaleCenterX,
          value: $compScaleCenterX,
          min: 0,
          max: 300
        })

        SliderBlock({
          title: 'scale.centerY',
          isEnabled: $enableCompScaleCenterY,
          value: $compScaleCenterY,
          min: 0,
          max: 300
        })
      }

      RadioBlock({
        title: 'transform',
        isEnabled: $enableCompTransform,
        value: $enableCompTransform,
        dataSource: [
          { label: 'true', value: true },
          { label: 'false', value: false }
        ]
      })
    }
  }
}
