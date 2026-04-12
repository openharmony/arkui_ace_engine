/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct ImageTestPage {
  @State message: string = 'Image Component Test'
  @State counter: number = 0
  @State imageWidth: number = 200
  @State imageHeight: number = 200
  @State opacity: number = 1.0
  @State borderRadius: number = 0
  @State borderWidth: number = 0
  @State scale: number = 1.0

  build() {
    Column() {
      Text(this.message)
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 20 })

      Image($r('app.media.icon'))
        .width(this.imageWidth)
        .height(this.imageHeight)
        .opacity(this.opacity)
        .borderRadius(this.borderRadius)
        .border({ width: this.borderWidth, color: Color.Blue })
        .scale({ x: this.scale, y: this.scale })
        .margin({ bottom: 20 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.imageWidth = Math.min(this.imageWidth + 20, 400)
          })

        Button('Width -')
          .onClick(() => {
            this.imageWidth = Math.max(this.imageWidth - 20, 50)
          })

        Button('Height +')
          .onClick(() => {
            this.imageHeight = Math.min(this.imageHeight + 20, 400)
          })

        Button('Height -')
          .onClick(() => {
            this.imageHeight = Math.max(this.imageHeight - 20, 50)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Opacity +')
          .onClick(() => {
            this.opacity = Math.min(this.opacity + 0.1, 1.0)
          })

        Button('Opacity -')
          .onClick(() => {
            this.opacity = Math.max(this.opacity - 0.1, 0.0)
          })

        Button('Radius +')
          .onClick(() => {
            this.borderRadius = Math.min(this.borderRadius + 10, 100)
          })

        Button('Radius -')
          .onClick(() => {
            this.borderRadius = Math.max(this.borderRadius - 10, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Border +')
          .onClick(() => {
            this.borderWidth = Math.min(this.borderWidth + 1, 10)
          })

        Button('Border -')
          .onClick(() => {
            this.borderWidth = Math.max(this.borderWidth - 1, 0)
          })

        Button('Scale +')
          .onClick(() => {
            this.scale = Math.min(this.scale + 0.1, 2.0)
          })

        Button('Scale -')
          .onClick(() => {
            this.scale = Math.max(this.scale - 0.1, 0.5)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}

@Component
struct ImageFitTest {
  @State fitMode: ImageFit = ImageFit.Cover
  private fitModes: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown
  ]
  private fitModeNames: string[] = ['Cover', 'Contain', 'Fill', 'None', 'ScaleDown']
  @State currentIndex: number = 0

  build() {
    Column() {
      Text('Image Fit Mode Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height(200)
        .objectFit(this.fitMode)
        .margin({ bottom: 20 })

      Text('Current Fit Mode: ' + this.fitModeNames[this.currentIndex])
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.fitModes.length) % this.fitModes.length
            this.fitMode = this.fitModes[this.currentIndex]
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.fitModes.length
            this.fitMode = this.fitModes[this.currentIndex]
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageInterpolationTest {
  @State interpolation: ImageInterpolation = ImageInterpolation.High
  private interpolations: ImageInterpolation[] = [
    ImageInterpolation.None,
    ImageInterpolation.Low,
    ImageInterpolation.Medium,
    ImageInterpolation.High
  ]
  private interpolationNames: string[] = ['None', 'Low', 'Medium', 'High']
  @State currentIndex: number = 3

  build() {
    Column() {
      Text('Image Interpolation Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width(400)
        .height('300vp')
        .renderMode(ImageRenderMode.Original)
        .interpolation(this.interpolation)
        .margin({ bottom: 20 })

      Text('Current Interpolation: ' + this.interpolationNames[this.currentIndex])
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.interpolations.length) % this.interpolations.length
            this.interpolation = this.interpolations[this.currentIndex]
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.interpolations.length
            this.interpolation = this.interpolations[this.currentIndex]
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageSyncLoadTest {
  @State loadStatus: string = 'Ready'
  @State imageLoaded: boolean = false

  build() {
    Column() {
      Text('Image Sync Load Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.imageLoaded) {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .margin({ bottom: 20 })
      } else {
        Text('Image not loaded')
          .fontSize(16)
          .margin({ bottom: 20 })
      }

      Text('Status: ' + this.loadStatus)
        .fontSize(16)
        .margin({ bottom: 10 })

      Button('Load Image')
        .onClick(() => {
          this.loadStatus = 'Loading...'
          setTimeout(() => {
            this.imageLoaded = true
            this.loadStatus = 'Loaded'
          }, 1000)
        })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageAsyncLoadTest {
  @State loadStatus: string = 'Ready'

  build() {
    Column() {
      Text('Image Async Load Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .onComplete(() => {
          this.loadStatus = 'Complete'
        })
        .onError(() => {
          this.loadStatus = 'Error'
        })
        .margin({ bottom: 20 })

      Text('Status: ' + this.loadStatus)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageBorderTest {
  @State borderWidth: number = 2
  @State borderColor: string = '#000000'
  @State borderRadius: number = 0

  build() {
    Column() {
      Text('Image Border Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .border({
          width: this.borderWidth,
          color: this.borderColor,
          radius: this.borderRadius
        })
        .margin({ bottom: 20 })

      Row() {
        Button('Border Width +')
          .onClick(() => {
            this.borderWidth = Math.min(this.borderWidth + 1, 10)
          })

        Button('Border Width -')
          .onClick(() => {
            this.borderWidth = Math.max(this.borderWidth - 1, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Border Radius +')
          .onClick(() => {
            this.borderRadius = Math.min(this.borderRadius + 10, 150)
          })

        Button('Border Radius -')
          .onClick(() => {
            this.borderRadius = Math.max(this.borderRadius - 10, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageShadowTest {
  @State shadowRadius: number = 10
  @State shadowColor: string = '#000000'
  @State shadowOffsetX: number = 5
  @State shadowOffsetY: number = 5

  build() {
    Column() {
      Text('Image Shadow Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .shadow({
          radius: this.shadowRadius,
          color: this.shadowColor,
          offsetX: this.shadowOffsetX,
          offsetY: this.shadowOffsetY
        })
        .margin({ bottom: 20 })

      Row() {
        Button('Shadow Radius +')
          .onClick(() => {
            this.shadowRadius = Math.min(this.shadowRadius + 5, 50)
          })

        Button('Shadow Radius -')
          .onClick(() => {
            this.shadowRadius = Math.max(this.shadowRadius - 5, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Offset X +')
          .onClick(() => {
            this.shadowOffsetX = Math.min(this.shadowOffsetX + 5, 50)
          })

        Button('Offset X -')
          .onClick(() => {
            this.shadowOffsetX = Math.max(this.shadowOffsetX - 5, -50)
          })

        Button('Offset Y +')
          .onClick(() => {
            this.shadowOffsetY = Math.min(this.shadowOffsetY + 5, 50)
          })

        Button('Offset Y -')
          .onClick(() => {
            this.shadowOffsetY = Math.max(this.shadowOffsetY - 5, -50)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageTransformTest {
  @State rotateAngle: number = 0
  @State scaleX: number = 1.0
  @State scaleY: number = 1.0
  @State translateX: number = 0
  @State translateY: number = 0

  build() {
    Column() {
      Text('Image Transform Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .rotate({ angle: this.rotateAngle })
        .scale({ x: this.scaleX, y: this.scaleY })
        .translate({ x: this.translateX, y: this.translateY })
        .margin({ bottom: 20 })

      Row() {
        Button('Rotate +')
          .onClick(() => {
            this.rotateAngle = (this.rotateAngle + 15) % 360
          })

        Button('Rotate -')
          .onClick(() => {
            this.rotateAngle = (this.rotateAngle - 15 + 360) % 360
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Scale X +')
          .onClick(() => {
            this.scaleX = Math.min(this.scaleX + 0.1, 2.0)
          })

        Button('Scale X -')
          .onClick(() => {
            this.scaleX = Math.max(this.scaleX - 0.1, 0.5)
          })

        Button('Scale Y +')
          .onClick(() => {
            this.scaleY = Math.min(this.scaleY + 0.1, 2.0)
          })

        Button('Scale Y -')
          .onClick(() => {
            this.scaleY = Math.max(this.scaleY - 0.1, 0.5)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageClipTest {
  @State clipRadius: number = 0
  @State clipWidth: number = 300
  @State clipHeight: number = 300

  build() {
    Column() {
      Text('Image Clip Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .clip(new Circle({ width: this.clipWidth, height: this.clipHeight }))
        .margin({ bottom: 20 })

      Row() {
        Button('Clip Size +')
          .onClick(() => {
            this.clipWidth = Math.min(this.clipWidth + 20, 300)
            this.clipHeight = Math.min(this.clipHeight + 20, 300)
          })

        Button('Clip Size -')
          .onClick(() => {
            this.clipWidth = Math.max(this.clipWidth - 20, 50)
            this.clipHeight = Math.max(this.clipHeight - 20, 50)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageColorFilterTest {
  @State brightness: number = 1.0
  @State contrast: number = 1.0
  @State saturation: number = 1.0

  build() {
    Column() {
      Text('Image Color Filter Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .brightness(this.brightness)
        .contrast(this.contrast)
        .saturate(this.saturation)
        .margin({ bottom: 20 })

      Row() {
        Button('Brightness +')
          .onClick(() => {
            this.brightness = Math.min(this.brightness + 0.1, 2.0)
          })

        Button('Brightness -')
          .onClick(() => {
            this.brightness = Math.max(this.brightness - 0.1, 0.0)
          })

        Button('Contrast +')
          .onClick(() => {
            this.contrast = Math.min(this.contrast + 0.1, 2.0)
          })

        Button('Contrast -')
          .onClick(() => {
            this.contrast = Math.max(this.contrast - 0.1, 0.0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })

      Row() {
        Button('Saturation +')
          .onClick(() => {
            this.saturation = Math.min(this.saturation + 0.1, 2.0)
          })

        Button('Saturation -')
          .onClick(() => {
            this.saturation = Math.max(this.saturation - 0.1, 0.0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageBlendModeTest {
  @State blendMode: BlendMode = BlendMode.SrcOver
  private blendModes: BlendMode[] = [
    BlendMode.SrcOver,
    BlendMode.DstOver,
    BlendMode.SrcIn,
    BlendMode.DstIn,
    BlendMode.SrcOut,
    BlendMode.DstOut,
    BlendMode.SrcATop,
    BlendMode.DstATop,
    BlendMode.Xor,
    BlendMode.Plus,
    BlendMode.Modulate,
    BlendMode.Screen,
    BlendMode.Overlay,
    BlendMode.Darken,
    BlendMode.Lighten,
    BlendMode.ColorDodge,
    BlendMode.ColorBurn,
    BlendMode.HardLight,
    BlendMode.SoftLight,
    BlendMode.Difference,
    BlendMode.Exclusion,
    BlendMode.Multiply,
    BlendMode.Hue,
    BlendMode.Saturation,
    BlendMode.Color,
    BlendMode.Luminosity
  ]
  private blendModeNames: string[] = [
    'SrcOver', 'DstOver', 'SrcIn', 'DstIn', 'SrcOut', 'DstOut',
    'SrcATop', 'DstATop', 'Xor', 'Plus', 'Modulate', 'Screen',
    'Overlay', 'Darken', 'Lighten', 'ColorDodge', 'ColorBurn',
    'HardLight', 'SoftLight', 'Difference', 'Exclusion', 'Multiply',
    'Hue', 'Saturation', 'Color', 'Luminosity'
  ]
  @State currentIndex: number = 0

  build() {
    Column() {
      Text('Image Blend Mode Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack() {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .objectFit(ImageFit.Cover)

        Image($r('app.media.icon'))
          .width(200)
          .height(200)
          .objectFit(ImageFit.Cover)
          .blendMode(this.blendMode)
      }
      .width('300vp')
      .height('300vp')
      .margin({ bottom: 20 })

      Text('Current Blend Mode: ' + this.blendModeNames[this.currentIndex])
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.blendModes.length) % this.blendModes.length
            this.blendMode = this.blendModes[this.currentIndex]
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.blendModes.length
            this.blendMode = this.blendModes[this.currentIndex]
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageMemoryTest {
  @State imageCount: number = 1
  @State memoryUsage: string = 'Low'

  build() {
    Column() {
      Text('Image Memory Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Column() {
        ForEach(Array.from({ length: this.imageCount }, (_, i) => i), (index: number) => {
          Image($r('app.media.icon'))
            .width('150vp')
            .height('150vp')
            .margin(5)
        })
      }
      .margin({ bottom: 20 })

      Text('Image Count: ' + this.imageCount)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text('Memory Usage: ' + this.memoryUsage)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Add Image')
          .onClick(() => {
            this.imageCount = Math.min(this.imageCount + 1, 10)
            this.updateMemoryUsage()
          })

        Button('Remove Image')
          .onClick(() => {
            this.imageCount = Math.max(this.imageCount - 1, 1)
            this.updateMemoryUsage()
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }

  private updateMemoryUsage(): void {
    if (this.imageCount <= 3) {
      this.memoryUsage = 'Low'
    } else if (this.imageCount <= 6) {
      this.memoryUsage = 'Medium'
    } else {
      this.memoryUsage = 'High'
    }
  }
}

@Component
struct ImageAnimationTest {
  @State isAnimating: boolean = false
  @State rotation: number = 0
  @State scale: number = 1.0
  private animationInterval: number = -1

  build() {
    Column() {
      Text('Image Animation Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .rotate({ angle: this.rotation })
        .scale({ x: this.scale, y: this.scale })
        .margin({ bottom: 20 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageAspectRatioTest {
  @State aspectRatio: number = 1.0
  @State imageWidth: number = 300

  build() {
    Column() {
      Text('Image Aspect Ratio Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width(this.imageWidth)
        .aspectRatio(this.aspectRatio)
        .objectFit(ImageFit.Cover)
        .margin({ bottom: 20 })

      Text('Aspect Ratio: ' + this.aspectRatio.toFixed(2))
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Ratio +')
          .onClick(() => {
            this.aspectRatio = Math.min(this.aspectRatio + 0.1, 3.0)
          })

        Button('Ratio -')
          .onClick(() => {
            this.aspectRatio = Math.max(this.aspectRatio - 0.1, 0.3)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageFillModeTest {
  @State fillMode: ImageFill = ImageFill.Cover
  private fillModes: ImageFill[] = [
    ImageFill.Cover,
    ImageFill.Contain,
    ImageFill.Fill,
    ImageFill.None
  ]
  private fillModeNames: string[] = ['Cover', 'Contain', 'Fill', 'None']
  @State currentIndex: number = 0

  build() {
    Column() {
      Text('Image Fill Mode Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height(200)
        .fillMode(this.fillMode)
        .margin({ bottom: 20 })

      Text('Current Fill Mode: ' + this.fillModeNames[this.currentIndex])
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.fillModes.length) % this.fillModes.length
            this.fillMode = this.fillModes[this.currentIndex]
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.fillModes.length
            this.fillMode = this.fillModes[this.currentIndex]
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageRepeatTest {
  @State repeatX: number = 1
  @State repeatY: number = 1

  build() {
    Column() {
      Text('Image Repeat Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .margin({ bottom: 20 })
        .repeatX(this.repeatX)
        .repeatY(this.repeatY)

      Text('Repeat X: ' + this.repeatX + ', Repeat Y: ' + this.repeatY)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Repeat X +')
          .onClick(() => {
            this.repeatX = Math.min(this.repeatX + 1, 5)
          })

        Button('Repeat X -')
          .onClick(() => {
            this.repeatX = Math.max(this.repeatX - 1, 1)
          })

        Button('Repeat Y +')
          .onClick(() => {
            this.repeatY = Math.min(this.repeatY + 1, 5)
          })

        Button('Repeat Y -')
          .onClick(() => {
            this.repeatY = Math.max(this.repeatY - 1, 1)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImagePositionTest {
  @State positionX: number = 0
  @State positionY: number = 0

  build() {
    Column() {
      Text('Image Position Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .position({ x: this.positionX, y: this.positionY })
        .margin({ bottom: 20 })

      Text('Position X: ' + this.positionX + ', Position Y: ' + this.positionY)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('X +')
          .onClick(() => {
            this.positionX = Math.min(this.positionX + 10, 100)
          })

        Button('X -')
          .onClick(() => {
            this.positionX = Math.max(this.positionX - 10, -100)
          })

        Button('Y +')
          .onClick(() => {
            this.positionY = Math.min(this.positionY + 10, 100)
          })

        Button('Y -')
          .onClick(() => {
            this.positionY = Math.max(this.positionY - 10, -100)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageMarginTest {
  @State marginTop: number = 0
  @State marginBottom: number = 0
  @State marginLeft: number = 0
  @State marginRight: number = 0

  build() {
    Column() {
      Text('Image Margin Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .margin({
          top: this.marginTop,
          bottom: this.marginBottom,
          left: this.marginLeft,
          right: this.marginRight
        })
        .margin({ bottom: 20 })

      Text('Margins: T:' + this.marginTop + ' B:' + this.marginBottom + ' L:' + this.marginLeft + ' R:' + this.marginRight)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Top +')
          .onClick(() => {
            this.marginTop = Math.min(this.marginTop + 5, 50)
          })

        Button('Top -')
          .onClick(() => {
            this.marginTop = Math.max(this.marginTop - 5, 0)
          })

        Button('Bottom +')
          .onClick(() => {
            this.marginBottom = Math.min(this.marginBottom + 5, 50)
          })

        Button('Bottom -')
          .onClick(() => {
            this.marginBottom = Math.max(this.marginBottom - 5, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImagePaddingTest {
  @State paddingTop: number = 0
  @State paddingBottom: number = 0
  @State paddingLeft: number = 0
  @State paddingRight: number = 0

  build() {
    Column() {
      Text('Image Padding Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .padding({
          top: this.paddingTop,
          bottom: this.paddingBottom,
          left: this.paddingLeft,
          right: this.paddingRight
        })
        .margin({ bottom: 20 })

      Text('Paddings: T:' + this.paddingTop + ' B:' + this.paddingBottom + ' L:' + this.paddingLeft + ' R:' + this.paddingRight)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Top +')
          .onClick(() => {
            this.paddingTop = Math.min(this.paddingTop + 5, 50)
          })

        Button('Top -')
          .onClick(() => {
            this.paddingTop = Math.max(this.paddingTop - 5, 0)
          })

        Button('Bottom +')
          .onClick(() => {
            this.paddingBottom = Math.min(this.paddingBottom + 5, 50)
          })

        Button('Bottom -')
          .onClick(() => {
            this.paddingBottom = Math.max(this.paddingBottom - 5, 0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageConstraintTest {
  @State minWidth: number = 100
  @State maxWidth: number = 400
  @State minHeight: number = 100
  @State maxHeight: number = 400

  build() {
    Column() {
      Text('Image Constraint Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .constraintSize({
          minWidth: this.minWidth,
          maxWidth: this.maxWidth,
          minHeight: this.minHeight,
          maxHeight: this.maxHeight
        })
        .margin({ bottom: 20 })

      Text('Min: ' + this.minWidth + 'x' + this.minHeight + ', Max: ' + this.maxWidth + 'x' + this.maxHeight)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Min +')
          .onClick(() => {
            this.minWidth = Math.min(this.minWidth + 20, 300)
            this.minHeight = Math.min(this.minHeight + 20, 300)
          })

        Button('Min -')
          .onClick(() => {
            this.minWidth = Math.max(this.minWidth - 20, 50)
            this.minHeight = Math.max(this.minHeight - 20, 50)
          })

        Button('Max +')
          .onClick(() => {
            this.maxWidth = Math.min(this.maxWidth + 20, 500)
            this.maxHeight = Math.min(this.maxHeight + 20, 500)
          })

        Button('Max -')
          .onClick(() => {
            this.maxWidth = Math.max(this.maxWidth - 20, 100)
            this.maxHeight = Math.max(this.maxHeight - 20, 100)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageLayoutTest {
  @State layoutWeight: number = 1
  @State align: Alignment = Alignment.Center

  build() {
    Column() {
      Text('Image Layout Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        Image($r('app.media.icon'))
          .width(100)
          .height(100)
          .layoutWeight(this.layoutWeight)
          .align(this.align)

        Image($r('app.media.icon'))
          .width(100)
          .height(100)
          .layoutWeight(this.layoutWeight)
          .align(this.align)
      }
      .width('100%')
      .height(200)
      .margin({ bottom: 20 })

      Text('Layout Weight: ' + this.layoutWeight)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Weight +')
          .onClick(() => {
            this.layoutWeight = Math.min(this.layoutWeight + 0.5, 3.0)
          })

        Button('Weight -')
          .onClick(() => {
            this.layoutWeight = Math.max(this.layoutWeight - 0.5, 0.5)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageVisibilityTest {
  @State visible: boolean = true
  @State opacity: number = 1.0

  build() {
    Column() {
      Text('Image Visibility Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.visible) {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .opacity(this.opacity)
          .margin({ bottom: 20 })
      }

      Text('Visible: ' + this.visible + ', Opacity: ' + this.opacity.toFixed(2))
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Toggle Visibility')
          .onClick(() => {
            this.visible = !this.visible
          })

        Button('Opacity +')
          .onClick(() => {
            this.opacity = Math.min(this.opacity + 0.1, 1.0)
          })

        Button('Opacity -')
          .onClick(() => {
            this.opacity = Math.max(this.opacity - 0.1, 0.0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageZIndexTest {
  @State zIndex1: number = 1
  @State zIndex2: number = 2

  build() {
    Column() {
      Text('Image Z-Index Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack() {
        Image($r('app.media.icon'))
          .width(200)
          .height(200)
          .zIndex(this.zIndex1)
          .backgroundColor(Color.Red)

        Image($r('app.media.icon'))
          .width('150vp')
          .height('150vp')
          .zIndex(this.zIndex2)
          .backgroundColor(Color.Blue)
      }
      .width('300vp')
      .height('300vp')
      .margin({ bottom: 20 })

      Text('Z-Index 1: ' + this.zIndex1 + ', Z-Index 2: ' + this.zIndex2)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Swap Z-Index')
          .onClick(() => {
            const temp = this.zIndex1
            this.zIndex1 = this.zIndex2
            this.zIndex2 = temp
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageAccessibilityTest {
  @State accessibilityText: string = 'Sample Image'
  @State accessibilityDescription: string = 'This is a sample image for testing'

  build() {
    Column() {
      Text('Image Accessibility Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .accessibilityText(this.accessibilityText)
        .accessibilityDescription(this.accessibilityDescription)
        .margin({ bottom: 20 })

      Text('Accessibility Text: ' + this.accessibilityText)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text('Description: ' + this.accessibilityDescription)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageGestureTest {
  @State scale: number = 1.0
  @State rotation: number = 0
  @State offsetX: number = 0
  @State offsetY: number = 0

  build() {
    Column() {
      Text('Image Gesture Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .scale({ x: this.scale, y: this.scale })
        .rotate({ angle: this.rotation })
        .translate({ x: this.offsetX, y: this.offsetY })
        .gesture(
          PinchGesture({ fingers: 2 })
            .onActionStart(() => {
              console.log('Pinch start')
            })
            .onActionUpdate((event: PinchGestureEvent) => {
              this.scale = event.scale
            })
            .onActionEnd(() => {
              console.log('Pinch end')
            })
        )
        .margin({ bottom: 20 })

      Text('Scale: ' + this.scale.toFixed(2))
        .fontSize(16)
        .margin({ bottom: 10 })

      Button('Reset')
        .onClick(() => {
          this.scale = 1.0
          this.rotation = 0
          this.offsetX = 0
          this.offsetY = 0
        })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageStateTest {
  @State loading: boolean = false
  @State loaded: boolean = false
  @State error: boolean = false

  build() {
    Column() {
      Text('Image State Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.loading) {
        Text('Loading...')
          .fontSize(16)
          .margin({ bottom: 20 })
      } else if (this.loaded) {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .margin({ bottom: 20 })
      } else if (this.error) {
        Text('Error loading image')
          .fontSize(16)
          .margin({ bottom: 20 })
      } else {
        Text('Ready to load')
          .fontSize(16)
          .margin({ bottom: 20 })
      }

      Row() {
        Button('Load')
          .onClick(() => {
            this.loading = true
            this.loaded = false
            this.error = false

            setTimeout(() => {
              this.loading = false
              this.loaded = true
            }, 1000)
          })

        Button('Error')
          .onClick(() => {
            this.loading = false
            this.loaded = false
            this.error = true
          })

        Button('Reset')
          .onClick(() => {
            this.loading = false
            this.loaded = false
            this.error = false
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageEventTest {
  @State clickCount: number = 0
  @State hoverState: string = 'None'

  build() {
    Column() {
      Text('Image Event Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .onClick(() => {
          this.clickCount++
        })
        .onHover((isHover: boolean) => {
          this.hoverState = isHover ? 'Hovering' : 'None'
        })
        .margin({ bottom: 20 })

      Text('Click Count: ' + this.clickCount)
        .fontSize(16)
        .margin({ bottom: 10 })

      Text('Hover State: ' + this.hoverState)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImagePerformanceTest {
  @State renderTime: number = 0
  @State frameRate: number = 60
  private startTime: number = 0

  build() {
    Column() {
      Text('Image Performance Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .onAppear(() => {
          this.startTime = Date.now()
        })
        .margin({ bottom: 20 })

      Text('Render Time: ' + this.renderTime + 'ms')
        .fontSize(16)
        .margin({ bottom: 10 })

      Text('Frame Rate: ' + this.frameRate + ' FPS')
        .fontSize(16)
        .margin({ bottom: 10 })

      Button('Measure Performance')
        .onClick(() => {
          this.measurePerformance()
        })
    }
    .width('100%')
    .padding(20)
  }

  private measurePerformance(): void {
    const start = Date.now()
    
    setTimeout(() => {
      const end = Date.now()
      this.renderTime = end - start
    }, 100)
  }
}

@Component
struct ImageQualityTest {
  @State quality: number = 100

  build() {
    Column() {
      Text('Image Quality Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .margin({ bottom: 20 })

      Text('Quality: ' + this.quality + '%')
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Quality +')
          .onClick(() => {
            this.quality = Math.min(this.quality + 10, 100)
          })

        Button('Quality -')
          .onClick(() => {
            this.quality = Math.max(this.quality - 10, 10)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageFormatTest {
  @State format: string = 'PNG'
  private formats: string[] = ['PNG', 'JPEG', 'GIF', 'BMP', 'WEBP']
  @State currentIndex: number = 0

  build() {
    Column() {
      Text('Image Format Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .margin({ bottom: 20 })

      Text('Current Format: ' + this.format)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.formats.length) % this.formats.length
            this.format = this.formats[this.currentIndex]
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.formats.length
            this.format = this.formats[this.currentIndex]
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageSizeTest {
  @State width: number = 300
  @State height: number = 300

  build() {
    Column() {
      Text('Image Size Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.icon'))
        .width(this.width)
        .height(this.height)
        .margin({ bottom: 20 })

      Text('Size: ' + this.width + 'x' + this.height)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Width +')
          .onClick(() => {
            this.width = Math.min(this.width + 20, 500)
          })

        Button('Width -')
          .onClick(() => {
            this.width = Math.max(this.width - 20, 50)
          })

        Button('Height +')
          .onClick(() => {
            this.height = Math.min(this.height + 20, 500)
          })

        Button('Height -')
          .onClick(() => {
            this.height = Math.max(this.height - 20, 50)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageBackgroundTest {
  @State backgroundColor: string = '#FFFFFF'

  build() {
    Column() {
      Text('Image Background Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })
      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .backgroundColor(this.backgroundColor)
        .margin({ bottom: 20 })
      Text('Background Color: ' + this.backgroundColor)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageOverlayTest {
  @State showOverlay: boolean = false

  build() {
    Column() {
      Text('Image Overlay Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })
      Stack() {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
        if (this.showOverlay) {
          Text('Overlay')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.White)
            .backgroundColor(Color.Black)
            .opacity(0.7)
            .padding(10)
        }
      }
      .width('300vp')
      .height('300vp')
      .margin({ bottom: 20 })
      Button('Toggle Overlay')
        .onClick(() => {
          this.showOverlay = !this.showOverlay
        })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageFilterTest {
  @State blurRadius: number = 0
  @State grayscale: number = 0

  build() {
    Column() {
      Text('Image Filter Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })
      Image($r('app.media.icon'))
        .width('300vp')
        .height('300vp')
        .blur(this.blurRadius)
        .grayscale(this.grayscale)
        .margin({ bottom: 20 })
      Text('Blur: ' + this.blurRadius + ', Grayscale: ' + this.grayscale)
        .fontSize(16)
        .margin({ bottom: 10 })
      Row() {
        Button('Blur +')
          .onClick(() => {
            this.blurRadius = Math.min(this.blurRadius + 5, 50)
          })
        Button('Blur -')
          .onClick(() => {
            this.blurRadius = Math.max(this.blurRadius - 5, 0)
          })
        Button('Grayscale +')
          .onClick(() => {
            this.grayscale = Math.min(this.grayscale + 0.1, 1.0)
          })
        Button('Grayscale -')
          .onClick(() => {
            this.grayscale = Math.max(this.grayscale - 0.1, 0.0)
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
      .margin({ top: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageGradientTest {
  @State showGradient: boolean = false

  build() {
    Column() {
      Text('Image Gradient Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.showGradient) {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .linearGradient({
            angle: 45,
            colors: [[0xFF0000, 0.0], [0x00FF00, 0.5], [0x0000FF, 1.0]]
          })
          .margin({ bottom: 20 })
      } else {
        Image($r('app.media.icon'))
          .width('300vp')
          .height('300vp')
          .margin({ bottom: 20 })
      }
      Button('Toggle Gradient')
        .onClick(() => {
          this.showGradient = !this.showGradient
        })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageGalleryTest {
  @State currentIndex: number = 0
  private images: Resource[] = [
    $r('app.media.icon'),
    $r('app.media.icon'),
    $r('app.media.icon')
  ]

  build() {
    Column() {
      Text('Image Gallery Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image(this.images[this.currentIndex])
        .width('300vp')
        .height('300vp')
        .margin({ bottom: 20 })

      Text('Image ' + (this.currentIndex + 1) + ' of ' + this.images.length)
        .fontSize(16)
        .margin({ bottom: 10 })

      Row() {
        Button('Previous')
          .onClick(() => {
            this.currentIndex = (this.currentIndex - 1 + this.images.length) % this.images.length
          })

        Button('Next')
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % this.images.length
          })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .width('100%')
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageSliderTest {
  @State currentIndex: number = 0
  private images: Resource[] = [
    $r('app.media.icon'),
    $r('app.media.icon'),
    $r('app.media.icon'),
    $r('app.media.icon'),
    $r('app.media.icon')
  ]

  build() {
    Column() {
      Text('Image Slider Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })
      Swiper() {
        ForEach(this.images, (image: Resource, index: number) => {
          Image(image)
            .width('300vp')
            .height('300vp')
        })
      }
      .width('300vp')
      .height('300vp')
      .index(this.currentIndex)
      .onChange((index: number) => {
        this.currentIndex = index
      })
      .margin({ bottom: 20 })
      Text('Slide ' + (this.currentIndex + 1) + ' of ' + this.images.length)
        .fontSize(16)
        .margin({ bottom: 10 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageGridTest {
  private images: Resource[] = Array.from({ length: 9 }, () => $r('app.media.icon'))

  build() {
    Column() {
      {
        Text('Image Grid Test')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 20 })
        Grid() {
          ForEach(this.images, (image: Resource, index: number) => {
            GridItem() {
              Image(image)
                .width('100%')
                .height('100%')
                .objectFit(ImageFit.Cover)
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr')
        .rowsTemplate('1fr 1fr 1fr')
        .width('300vp')
        .height('300vp')
        .margin({ bottom: 20 })
      }
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct ImageListTest {
  private images: Resource[] = Array.from({ length: 10 }, () => $r('app.media.icon'))
  build() {
    Column() {
      Text('Image List Test')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })
      List() {
        ForEach(this.images, (image: Resource, index: number) => {
          ListItem() {
            Row() {
              Image(image)
                .width(50)
                .height(50)
                .margin({ right: 10 })
              Text('Image ' + (index + 1))
                .fontSize(16)
            }
            .width('100%')
            .padding(10)
          }
        })
      }
      .width('100%')
      .height(400)
      .margin({ bottom: 20 })
    }
    .width('100%')
    .padding(20)
  }
}

@Component
struct TransitionAnimationDemo {
  @State showElement: boolean = true

  build() {
    Column() {
      Text('Transition Animation Demo')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
      if (this.showElement) {
        Text('Transition Element')
          .width(200)
          .height(50)
          .fontSize(16)
          .textAlign(TextAlign.Center)
          .backgroundColor('#4ECDC4')
          .transition({ type: TransitionType.All, opacity: 0.5, duration: 300 })
          .margin({ bottom: 15 })
      }
      Button('Toggle Element')
        .onClick(() => {
          this.showElement = !this.showElement
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#F5F5F5')
    .borderRadius(10)
    .margin({ bottom: 20 })
  }
}