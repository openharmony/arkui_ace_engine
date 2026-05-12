/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

interface ParticleInfo {
  x: number
  y: number
  size: number
  color: Color
  angle: number
  speed: number
}

/**
 * SVG Advanced Effects Example - Demonstrates comprehensive SVG advanced effects
 * Including: filters, masks, clipping, gradients, transforms, animations, particles
 */
@Entry
@Component
struct svgExample018 {
  @State blurRadius: number = 0
  @State shadowRadius: number = 0
  @State shadowColor: Color = Color.Black
  @State gradientAngle: number = 0
  @State rotateAngle: number = 0
  @State scaleValue: number = 1.0
  @State translateX: number = 0
  @State translateY: number = 0
  @State animationDuration: number = 1000
  @State isAnimating: boolean = false
  @State brightnessValue: number = 1.0
  @State contrastValue: number = 1.0
  @State saturateValue: number = 1.0
  @State invertValue: number = 0
  @State sepiaValue: number = 0
  @State hueRotateValue: number = 0
  @State glowIntensity: number = 0.5
  @State embossStrength: number = 0
  @State sharpenAmount: number = 0
  @State animAngle: number = 0
  @State animScale: number = 1.0
  @State animOpacity: number = 1.0
  @State animX: number = 0
  @State progress: number = 0
  @State interactScale: number = 1.0
  @State interactOpacity: number = 1.0
  @State interactRotation: number = 0
  @State interactColor: Color = Color.Blue
  @State pressCount: number = 0
  @State dragX: number = 0
  @State dragY: number = 0
  @State loadAngle1: number = 0
  @State loadAngle2: number = 0
  @State loadAngle3: number = 0
  @State loadOpacity1: number = 1.0
  @State loadOpacity2: number = 1.0
  @State loadOpacity3: number = 1.0
  @State loadScale1: number = 1.0
  @State loadScale2: number = 1.0
  @State loadScale3: number = 1.0
  @State transitionIndex: number = 0
  @State particles: ParticleInfo[] = []
  private colors: Color[] = [
    Color.Red, Color.Orange, Color.Yellow, Color.Green,
    Color.Black, Color.Blue, Color.Transparent, Color.Pink,
    Color.Brown, Color.Gray
  ]
  private gradientColors: Array<[ResourceColor, number]> = [
    [Color.Red, 0.0],
    [Color.Orange, 0.25],
    [Color.Yellow, 0.5],
    [Color.Green, 0.75],
    [Color.Blue, 1.0]
  ]

  aboutToAppear(): void {
    this.initParticles()
  }

  private initParticles(): void {
    const tempParticles: ParticleInfo[] = []
    for (let i = 0; i < 20; i++) {
      const particle: ParticleInfo = {
        x: Math.random() * 280,
        y: Math.random() * 280,
        size: 10 + Math.random() * 30,
        color: this.colors[Math.floor(Math.random() * 6)],
        angle: Math.random() * 360,
        speed: 1 + Math.random() * 3
      }
      tempParticles.push(particle)
    }
    this.particles = tempParticles
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Advanced Effects Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        this.BlurEffectSection()
        this.ShadowEffectSection()
        this.GradientEffectSection()
        this.TransformEffectSection()
        this.AnimationEffectSection()
        this.MaskEffectSection()
        this.ClipEffectSection()
        this.FilterEffectSection()
        this.ParticleEffectSection()
        this.ProgressEffectSection()
        this.GlowEffectSection()
        this.EmbossEffectSection()
        this.SharpenEffectSection()
        this.ColorMatrixEffectSection()
        this.MixedEffectSection()
        this.InteractiveEffectSection()
        this.LoadingEffectSection()
        this.TransitionEffectSection()
      }
      .width('100%')
      .padding(15)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  BlurEffectSection() {
    Column({ space: 15 }) {
      Text('Blur Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .blur(this.blurRadius)
            .border({ width: 1, color: Color.Gray })
          Text('Blur: ' + this.blurRadius.toFixed(0))
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .blur(this.blurRadius * 0.5)
            .border({ width: 1, color: Color.Gray })
          Text('Half Blur')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .blur(this.blurRadius * 1.5)
            .border({ width: 1, color: Color.Gray })
          Text('1.5x Blur')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Slider({
        value: this.blurRadius,
        min: 0,
        max: 20,
        step: 1
      })
        .width('90%')
        .onChange((value: number) => {
          this.blurRadius = value
        })

      Text('Adjust blur radius')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  ShadowEffectSection() {
    Column({ space: 15 }) {
      Text('Shadow Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .shadow({
              radius: this.shadowRadius,
              color: this.shadowColor,
              offsetX: 5,
              offsetY: 5
            })
            .border({ width: 1, color: Color.Gray })
          Text('Shadow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .shadow({
              radius: this.shadowRadius,
              color: Color.Red,
              offsetX: -5,
              offsetY: -5
            })
            .border({ width: 1, color: Color.Gray })
          Text('Red Shadow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .shadow({
              radius: this.shadowRadius,
              color: Color.Blue,
              offsetX: 0,
              offsetY: 10
            })
            .border({ width: 1, color: Color.Gray })
          Text('Blue Shadow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(70)
            .height(70)
            .shadow({
              radius: this.shadowRadius,
              color: Color.Green,
              offsetX: 10,
              offsetY: 0
            })
            .border({ width: 1, color: Color.Gray })
          Text('Green Shadow')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Slider({
        value: this.shadowRadius,
        min: 0,
        max: 30,
        step: 1
      })
        .width('90%')
        .onChange((value: number) => {
          this.shadowRadius = value
        })

      Row({ space: 10 }) {
        ForEach([Color.Black, Color.Red, Color.Blue, Color.Green], (color: Color) => {
          Button('')
            .width(30)
            .height(30)
            .backgroundColor(color)
            .borderRadius(15)
            .onClick(() => {
              this.shadowColor = color
            })
        })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  GradientEffectSection() {
    Column({ space: 15 }) {
      Text('Gradient Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .linearGradient({
              angle: this.gradientAngle,
              colors: this.gradientColors
            })
            .border({ width: 1, color: Color.Gray })
          Text('Linear')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .linearGradient({
              direction: GradientDirection.Right,
              colors: [[0xFF0000, 0.0], [0x00FF00, 0.5], [0x0000FF, 1.0]]
            })
            .border({ width: 1, color: Color.Gray })
          Text('RGB Gradient')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .linearGradient({
              direction: GradientDirection.Bottom,
              colors: [[0xFFFFFF, 0.0], [0x000000, 1.0]]
            })
            .border({ width: 1, color: Color.Gray })
          Text('Grayscale')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Slider({
        value: this.gradientAngle,
        min: 0,
        max: 360,
        step: 15
      })
        .width('90%')
        .onChange((value: number) => {
          this.gradientAngle = value
        })

      Text('Angle: ' + this.gradientAngle.toFixed(0) + '°')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  TransformEffectSection() {
    Column({ space: 15 }) {
      Text('Transform Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(60)
            .height(60)
            .rotate({ angle: this.rotateAngle })
            .border({ width: 1, color: Color.Gray })
          Text('Rotate')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(60)
            .height(60)
            .scale({ x: this.scaleValue, y: this.scaleValue })
            .border({ width: 1, color: Color.Gray })
          Text('Scale')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(60)
            .height(60)
            .translate({ x: this.translateX, y: this.translateY })
            .border({ width: 1, color: Color.Gray })
          Text('Translate')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(60)
            .height(60)
            .rotate({ angle: this.rotateAngle })
            .scale({ x: this.scaleValue, y: this.scaleValue })
            .border({ width: 1, color: Color.Gray })
          Text('Combined')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Column({ space: 10 }) {
        Row({ space: 10 }) {
          Text('Rotate:')
            .width(70)
            .fontSize(12)
          Slider({
            value: this.rotateAngle,
            min: 0,
            max: 360,
            step: 1
          })
            .width('60%')
            .onChange((value: number) => {
              this.rotateAngle = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('Scale:')
            .width(70)
            .fontSize(12)
          Slider({
            value: this.scaleValue,
            min: 0.5,
            max: 2.0,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.scaleValue = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('TranslateX:')
            .width(70)
            .fontSize(12)
          Slider({
            value: this.translateX,
            min: -50,
            max: 50,
            step: 1
          })
            .width('60%')
            .onChange((value: number) => {
              this.translateX = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('TranslateY:')
            .width(70)
            .fontSize(12)
          Slider({
            value: this.translateY,
            min: -50,
            max: 50,
            step: 1
          })
            .width('60%')
            .onChange((value: number) => {
              this.translateY = value
            })
        }
        .width('100%')
      }
      .width('100%')
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  AnimationEffectSection() {
    Column({ space: 15 }) {
      Text('Animation Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .rotate({ angle: this.animAngle })
            .animation({
              duration: this.animationDuration,
              curve: Curve.Linear,
              iterations: -1
            })
            .border({ width: 1, color: Color.Gray })
          Text('Rotate')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .scale({ x: this.animScale, y: this.animScale })
            .animation({
              duration: this.animationDuration,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
            .border({ width: 1, color: Color.Gray })
          Text('Scale')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .opacity(this.animOpacity)
            .animation({
              duration: this.animationDuration,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
            .border({ width: 1, color: Color.Gray })
          Text('Opacity')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(70)
            .height(70)
            .translate({ x: this.animX })
            .animation({
              duration: this.animationDuration,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
            .border({ width: 1, color: Color.Gray })
          Text('Translate')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('Start')
          .onClick(() => {
            this.isAnimating = true
            this.animAngle = 360
            this.animScale = 1.5
            this.animOpacity = 0.3
            this.animX = 30
          })

        Button('Stop')
          .onClick(() => {
            this.isAnimating = false
            this.animAngle = 0
            this.animScale = 1.0
            this.animOpacity = 1.0
            this.animX = 0
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Row({ space: 10 }) {
        Text('Duration:')
          .fontSize(12)
        Slider({
          value: this.animationDuration,
          min: 500,
          max: 5000,
          step: 100
        })
          .width('70%')
          .onChange((value: number) => {
            this.animationDuration = value
          })
      }
      .width('100%')

      Text('Duration: ' + this.animationDuration + 'ms')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  MaskEffectSection() {
    Column({ space: 15 }) {
      Text('Mask Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.testSvg'))
              .width(80)
              .height(80)
          }
          .width(80)
          .height(80)
          .mask(new Circle({ width: 80, height: 80 }))
          .border({ width: 1, color: Color.Gray })

          Text('Circle Mask')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
          }
          .width(80)
          .height(80)
          .mask(new Rect({ width: 80, height: 80 }))
          .border({ width: 1, color: Color.Gray })

          Text('Rect Mask')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.icon'))
              .width(80)
              .height(80)
          }
          .width(80)
          .height(80)
          .mask(new Ellipse({ width: 80, height: 60 }))
          .border({ width: 1, color: Color.Gray })

          Text('Ellipse Mask')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.star'))
              .width(80)
              .height(80)
              .fillColor(Color.Red)
          }
          .width(80)
          .height(80)
          .mask(new Path({ width: 80, height: 80, commands: 'M40 0 L80 80 L0 80 Z' }))
          .border({ width: 1, color: Color.Gray })

          Text('Triangle Mask')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.heart'))
              .width(80)
              .height(80)
              .fillColor(Color.Pink)
          }
          .width(80)
          .height(80)
          .borderRadius(20)
          .clip(true)
          .border({ width: 1, color: Color.Gray })

          Text('RoundRect Mask')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  ClipEffectSection() {
    Column({ space: 15 }) {
      Text('Clip Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .clip(new Circle({ width: 80, height: 80 }))
            .border({ width: 1, color: Color.Gray })
          Text('Circle Clip')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .clip(new Rect({ width: 80, height: 80 }))
            .border({ width: 1, color: Color.Gray })
          Text('Rect Clip')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .clip(new Ellipse({ width: 80, height: 60 }))
            .border({ width: 1, color: Color.Gray })
          Text('Ellipse Clip')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(80)
            .height(80)
            .fillColor(Color.Orange)
            .clip(new Path({ width: 80, height: 80, commands: 'M40 0 L80 80 L0 80 Z' }))
            .border({ width: 1, color: Color.Gray })
          Text('Triangle Clip')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.heart'))
            .width(80)
            .height(80)
            .fillColor(Color.Red)
            .borderRadius(15)
            .clip(true)
            .border({ width: 1, color: Color.Gray })
          Text('RoundRect Clip')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .borderRadius(40)
            .clip(true)
            .border({ width: 1, color: Color.Gray })
          Text('BorderRadius')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  FilterEffectSection() {
    Column({ space: 15 }) {
      Text('Filter Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .brightness(this.brightnessValue)
            .border({ width: 1, color: Color.Gray })
          Text('Brightness')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .contrast(this.contrastValue)
            .border({ width: 1, color: Color.Gray })
          Text('Contrast')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .saturate(this.saturateValue)
            .border({ width: 1, color: Color.Gray })
          Text('Saturate')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(70)
            .height(70)
            .invert(this.invertValue)
            .border({ width: 1, color: Color.Gray })
          Text('Invert')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Column({ space: 8 }) {
        Row({ space: 10 }) {
          Text('Brightness:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.brightnessValue,
            min: 0,
            max: 2,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.brightnessValue = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('Contrast:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.contrastValue,
            min: 0,
            max: 2,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.contrastValue = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('Saturate:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.saturateValue,
            min: 0,
            max: 2,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.saturateValue = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('Invert:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.invertValue,
            min: 0,
            max: 1,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.invertValue = value
            })
        }
        .width('100%')
      }
      .width('100%')
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  ParticleEffectSection() {
    Column({ space: 15 }) {
      Text('Particle Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Stack() {
        ForEach(this.particles, (particle: ParticleInfo, index: number) => {
          Image($r('app.media.testSvg'))
            .width(particle.size)
            .height(particle.size)
            .fillColor(particle.color)
            .position({ x: particle.x, y: particle.y })
            .opacity(0.7)
            .rotate({ angle: particle.angle })
            .animation({
              duration: 2000 + particle.speed * 500,
              curve: Curve.Linear,
              iterations: -1
            })
        })
      }
      .width(280)
      .height(280)
      .backgroundColor('#E8E8E8')
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('Refresh')
          .onClick(() => {
            this.initParticles()
          })

        Button('Add')
          .onClick(() => {
            const newParticle: ParticleInfo = {
              x: Math.random() * 280,
              y: Math.random() * 280,
              size: 10 + Math.random() * 30,
              color: this.colors[Math.floor(Math.random() * 6)],
              angle: Math.random() * 360,
              speed: 1 + Math.random() * 3
            }
            this.particles.push(newParticle)
          })

        Button('Clear')
          .onClick(() => {
            this.particles = []
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('Particles: ' + this.particles.length)
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  ProgressEffectSection() {
    Column({ space: 15 }) {
      Text('Progress Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Stack() {
        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .fillColor(Color.Gray)

        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .fillColor(Color.Blue)
          .clip(new Rect({ width: 150 * this.progress / 100, height: 150 }))
      }
      .width(150)
      .height(150)
      .border({ width: 2, color: Color.Gray })

      Row({ space: 10 }) {
        Text('Progress:')
          .fontSize(12)
        Slider({
          value: this.progress,
          min: 0,
          max: 100,
          step: 1
        })
          .width('70%')
          .onChange((value: number) => {
            this.progress = value
          })
      }
      .width('100%')

      Text('Progress: ' + this.progress.toFixed(0) + '%')
        .fontSize(12)
        .fontColor(Color.Gray)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
              .fillColor(Color.Gray)

            Image($r('app.media.svg'))
              .width(80)
              .height(80)
              .fillColor(Color.Green)
              .clip(new Circle({ width: 80 * this.progress / 100, height: 80 * this.progress / 100 }))
          }
          .width(80)
          .height(80)
          .border({ width: 1, color: Color.Gray })

          Text('Circle')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.icon'))
              .width(80)
              .height(80)
              .fillColor(Color.Gray)

            Image($r('app.media.icon'))
              .width(80)
              .height(80)
              .fillColor(Color.Orange)
              .clip(new Rect({ width: 80, height: 80 * this.progress / 100 }))
          }
          .width(80)
          .height(80)
          .border({ width: 1, color: Color.Gray })

          Text('Vertical')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.star'))
              .width(80)
              .height(80)
              .fillColor(Color.Gray)

            Image($r('app.media.star'))
              .width(80)
              .height(80)
              .fillColor(Color.Red)
              .clip(new Ellipse({ width: 80 * this.progress / 100, height: 80 * this.progress / 100 }))
          }
          .width(80)
          .height(80)
          .border({ width: 1, color: Color.Gray })

          Text('Ellipse')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  GlowEffectSection() {
    Column({ space: 15 }) {
      Text('Glow Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(Color.Blue)
            .shadow({
              radius: 20 * this.glowIntensity,
              color: Color.Blue,
              offsetX: 0,
              offsetY: 0
            })
            .border({ width: 1, color: Color.Gray })
          Text('Blue Glow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .fillColor(Color.Red)
            .shadow({
              radius: 20 * this.glowIntensity,
              color: Color.Red,
              offsetX: 0,
              offsetY: 0
            })
            .border({ width: 1, color: Color.Gray })
          Text('Red Glow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .fillColor(Color.Green)
            .shadow({
              radius: 20 * this.glowIntensity,
              color: Color.Green,
              offsetX: 0,
              offsetY: 0
            })
            .border({ width: 1, color: Color.Gray })
          Text('Green Glow')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Text('Intensity:')
          .width(80)
          .fontSize(12)
        Slider({
          value: this.glowIntensity,
          min: 0,
          max: 2,
          step: 0.1
        })
          .width('60%')
          .onChange((value: number) => {
            this.glowIntensity = value
          })
      }
      .width('100%')

      Text('Glow Intensity: ' + this.glowIntensity.toFixed(1))
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  EmbossEffectSection() {
    Column({ space: 15 }) {
      Text('Emboss Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .shadow({
              radius: 10,
              color: Color.White,
              offsetX: -2,
              offsetY: -2
            })
            .shadow({
              radius: 10,
              color: Color.Black,
              offsetX: 2,
              offsetY: 2
            })
            .border({ width: 1, color: Color.Gray })
          Text('Emboss')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .shadow({
              radius: 10 * this.embossStrength,
              color: Color.White,
              offsetX: -3,
              offsetY: -3
            })
            .shadow({
              radius: 10 * this.embossStrength,
              color: Color.Black,
              offsetX: 3,
              offsetY: 3
            })
            .border({ width: 1, color: Color.Gray })
          Text('Dynamic')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .shadow({
              radius: 15,
              color: '#FFFFFFFF',
              offsetX: -4,
              offsetY: -4
            })
            .shadow({
              radius: 15,
              color: '#FF000000',
              offsetX: 4,
              offsetY: 4
            })
            .border({ width: 1, color: Color.Gray })
          Text('Strong')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Text('Strength:')
          .width(80)
          .fontSize(12)
        Slider({
          value: this.embossStrength,
          min: 0,
          max: 3,
          step: 0.1
        })
          .width('60%')
          .onChange((value: number) => {
            this.embossStrength = value
          })
      }
      .width('100%')

      Text('Emboss Strength: ' + this.embossStrength.toFixed(1))
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  SharpenEffectSection() {
    Column({ space: 15 }) {
      Text('Sharpen Effect (Simulated)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .contrast(1 + this.sharpenAmount * 0.2)
            .brightness(1 + this.sharpenAmount * 0.05)
            .border({ width: 1, color: Color.Gray })
          Text('Sharpened')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .contrast(1)
            .border({ width: 1, color: Color.Gray })
          Text('Original')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .contrast(1 + this.sharpenAmount * 0.3)
            .saturate(1 + this.sharpenAmount * 0.1)
            .border({ width: 1, color: Color.Gray })
          Text('Enhanced')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Text('Amount:')
          .width(80)
          .fontSize(12)
        Slider({
          value: this.sharpenAmount,
          min: 0,
          max: 2,
          step: 0.1
        })
          .width('60%')
          .onChange((value: number) => {
            this.sharpenAmount = value
          })
      }
      .width('100%')

      Text('Sharpen Amount: ' + this.sharpenAmount.toFixed(1))
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  ColorMatrixEffectSection() {
    Column({ space: 15 }) {
      Text('Color Matrix Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .sepia(1)
            .border({ width: 1, color: Color.Gray })
          Text('Sepia')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .sepia(this.sepiaValue)
            .border({ width: 1, color: Color.Gray })
          Text('Sepia')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .hueRotate(this.hueRotateValue)
            .border({ width: 1, color: Color.Gray })
          Text('Hue Rotate')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(70)
            .height(70)
            .saturate(2)
            .border({ width: 1, color: Color.Gray })
          Text('Saturate')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Column({ space: 8 }) {
        Row({ space: 10 }) {
          Text('Sepia:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.sepiaValue,
            min: 0,
            max: 1,
            step: 0.1
          })
            .width('60%')
            .onChange((value: number) => {
              this.sepiaValue = value
            })
        }
        .width('100%')

        Row({ space: 10 }) {
          Text('Hue Rotate:')
            .width(80)
            .fontSize(12)
          Slider({
            value: this.hueRotateValue,
            min: 0,
            max: 360,
            step: 15
          })
            .width('60%')
            .onChange((value: number) => {
              this.hueRotateValue = value
            })
        }
        .width('100%')
      }
      .width('100%')
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  MixedEffectSection() {
    Column({ space: 15 }) {
      Text('Mixed Effects')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .fillColor(Color.Blue)
            .blur(3)
            .shadow({
              radius: 10,
              color: Color.Blue,
              offsetX: 0,
              offsetY: 5
            })
            .border({ width: 1, color: Color.Gray })
          Text('Blur+Shadow')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .fillColor(Color.Red)
            .rotate({ angle: 45 })
            .scale({ x: 0.8, y: 0.8 })
            .border({ width: 1, color: Color.Gray })
          Text('Rotate+Scale')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .fillColor(Color.Green)
            .brightness(1.2)
            .contrast(1.1)
            .border({ width: 1, color: Color.Gray })
          Text('Bright+Contrast')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.star'))
            .width(70)
            .height(70)
            .fillColor(Color.Orange)
            .opacity(0.7)
            .blur(2)
            .border({ width: 1, color: Color.Gray })
          Text('Opacity+Blur')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.heart'))
            .width(70)
            .height(70)
            .fillColor(Color.Pink)
            .shadow({
              radius: 15,
              color: Color.Pink,
              offsetX: 0,
              offsetY: 0
            })
            .scale({ x: 1.2, y: 1.2 })
            .border({ width: 1, color: Color.Gray })
          Text('Glow+Scale')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(70)
            .height(70)
            .fillColor(Color.Pink)
            .hueRotate(180)
            .saturate(1.5)
            .border({ width: 1, color: Color.Gray })
          Text('Hue+Sat')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(70)
            .height(70)
            .fillColor(Color.Black)
            .translate({ x: 10, y: 10 })
            .opacity(0.8)
            .border({ width: 1, color: Color.Gray })
          Text('Translate+Op')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(70)
            .height(70)
            .fillColor(Color.Yellow)
            .invert(0.3)
            .brightness(1.1)
            .border({ width: 1, color: Color.Gray })
          Text('Invert+Bright')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  InteractiveEffectSection() {
    Column({ space: 15 }) {
      Text('Interactive Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.interactColor)
            .scale({ x: this.interactScale, y: this.interactScale })
            .opacity(this.interactOpacity)
            .rotate({ angle: this.interactRotation })
            .border({ width: 1, color: Color.Gray })
            .animation({
              duration: 300,
              curve: Curve.EaseInOut
            })
        }

        Column({ space: 10 }) {
          Button('Press')
            .width(80)
            .onClick(() => {
              this.pressCount++
              this.interactScale = 1.2
              this.interactOpacity = 0.7
              this.interactRotation += 45
              this.interactColor = this.colors[this.pressCount % this.colors.length]
            })

          Button('Reset')
            .width(80)
            .onClick(() => {
              this.interactScale = 1.0
              this.interactOpacity = 1.0
              this.interactRotation = 0
              this.interactColor = Color.Blue
            })
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('Press Count: ' + this.pressCount)
        .fontSize(12)
        .fontColor(Color.Gray)

      Stack() {
        Image($r('app.media.svg'))
          .width(60)
          .height(60)
          .fillColor(Color.Red)
          .translate({ x: this.dragX, y: this.dragY })
          .gesture(
            PanGesture({ direction: PanDirection.All })
              .onActionUpdate((event: GestureEvent) => {
                if (event.offsetX) {
                  this.dragX = event.offsetX
                }
                if (event.offsetY) {
                  this.dragY = event.offsetY
                }
              })
              .onActionEnd(() => {
                this.dragX = 0
                this.dragY = 0
              })
          )
      }
      .width(200)
      .height(100)
      .backgroundColor('#E8E8E8')
      .borderRadius(10)

      Text('Drag the icon')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  LoadingEffectSection() {
    Column({ space: 15 }) {
      Text('Loading Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(50)
            .height(50)
            .fillColor(Color.Blue)
            .rotate({ angle: this.loadAngle1 })
            .animation({
              duration: 1000,
              curve: Curve.Linear,
              iterations: -1
            })
          Text('Spin')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.svg'))
            .width(50)
            .height(50)
            .fillColor(Color.Green)
            .opacity(this.loadOpacity2)
            .animation({
              duration: 800,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
          Text('Pulse')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.icon'))
            .width(50)
            .height(50)
            .fillColor(Color.Red)
            .scale({ x: this.loadScale3, y: this.loadScale3 })
            .animation({
              duration: 600,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
          Text('Scale')
            .fontSize(12)
        }

        Column({ space: 5 }) {
          Stack() {
            Image($r('app.media.star'))
              .width(50)
              .height(50)
              .fillColor(Color.Orange)
              .opacity(0.3)
            Image($r('app.media.star'))
              .width(50)
              .height(50)
              .fillColor(Color.Orange)
              .rotate({ angle: this.loadAngle1 })
              .clip(true)
              .animation({
                duration: 1000,
                curve: Curve.Linear,
                iterations: -1
              })
          }
          .width(50)
          .height(50)

          Text('Progress')
            .fontSize(12)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('Start')
          .onClick(() => {
            this.loadAngle1 = 360
            this.loadAngle2 = 360
            this.loadAngle3 = 360
            this.loadOpacity1 = 0.3
            this.loadOpacity2 = 0.3
            this.loadOpacity3 = 0.3
            this.loadScale1 = 0.5
            this.loadScale2 = 0.5
            this.loadScale3 = 0.5
          })

        Button('Stop')
          .onClick(() => {
            this.loadAngle1 = 0
            this.loadAngle2 = 0
            this.loadAngle3 = 0
            this.loadOpacity1 = 1.0
            this.loadOpacity2 = 1.0
            this.loadOpacity3 = 1.0
            this.loadScale1 = 1.0
            this.loadScale2 = 1.0
            this.loadScale3 = 1.0
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
  }

  @Builder
  TransitionEffectSection() {
    Column({ space: 15 }) {
      Text('Transition Effect')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Stack() {
        if (this.transitionIndex === 0) {
          Image($r('app.media.testSvg'))
            .width(120)
            .height(120)
            .fillColor(Color.Blue)
        } else if (this.transitionIndex === 1) {
          Image($r('app.media.svg'))
            .width(120)
            .height(120)
            .fillColor(Color.Green)
        } else if (this.transitionIndex === 2) {
          Image($r('app.media.icon'))
            .width(120)
            .height(120)
            .fillColor(Color.Red)
        } else {
          Image($r('app.media.star'))
            .width(120)
            .height(120)
            .fillColor(Color.Orange)
        }
      }
      .width(120)
      .height(120)
      .border({ width: 2, color: Color.Gray })

      Row({ space: 10 }) {
        Button('Fade')
          .onClick(() => {
            this.transitionIndex = (this.transitionIndex + 1) % 4
          })

        Button('Slide')
          .onClick(() => {
            this.transitionIndex = (this.transitionIndex + 1) % 4
          })

        Button('Rotate')
          .onClick(() => {
            this.transitionIndex = (this.transitionIndex + 1) % 4
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('Current: ' + (this.transitionIndex + 1) + ' / 4')
        .fontSize(12)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(10)
    .backgroundColor(Color.White)
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}