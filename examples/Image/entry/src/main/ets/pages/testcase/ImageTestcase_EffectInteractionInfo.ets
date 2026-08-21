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

/**
 * Image 效果·交互·信息综合合集
 * 合并自: ImageTestcaseEffectsInteraction / ImageTestcaseDragAccessibility / ImageTestcaseImageInfoDecode
 */

/**
 * Image 动效与交互合集（由原 038/045/046/050 合并）
 * 覆盖：宽高动画过渡 / clip·mask 裁剪遮罩 / 视觉效果叠加 / 手势交互
 */

/** 原 038：宽高动画过渡 */
@Component
struct ImageSizeAnimationTestCase038 {
  @State imageWidth: number = 100
  @State imageHeight: number = 100
  @State animDuration: number = 500
  @State animCurve: Curve = Curve.EaseInOut

  private readonly SIZE_ANIMATIONS: Array<{
    name: string; width: number; height: number; duration: number; curve: Curve
  }> = [
    { name: '放大', width: 200, height: 200, duration: 500, curve: Curve.EaseInOut },
    { name: '缩小', width: 50, height: 50, duration: 500, curve: Curve.EaseInOut },
    { name: '横向展开', width: 300, height: 100, duration: 400, curve: Curve.EaseOut },
    { name: '纵向展开', width: 100, height: 300, duration: 400, curve: Curve.EaseOut },
    { name: '弹跳放大', width: 180, height: 180, duration: 800, curve: Curve.EaseInOut },
    { name: '快速缩小', width: 30, height: 30, duration: 200, curve: Curve.Linear },
    { name: '恢复原始', width: 100, height: 100, duration: 500, curve: Curve.EaseInOut }
  ]

  build() {
    Column() {
      Text('Image宽高动画过渡测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Column() {
        Image($r('app.media.startIcon'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .animation({
            duration: this.animDuration,
            curve: this.animCurve
          })

        Text(`${this.imageWidth} x ${this.imageHeight}`)
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ top: 8 })
      }
      .margin({ bottom: 16 })

      Grid() {
        ForEach(this.SIZE_ANIMATIONS, (anim: {
          name: string; width: number; height: number; duration: number; curve: Curve
        }) => {
          GridItem() {
            Column() {
              Text(anim.name)
                .fontSize(12)
                .fontWeight(FontWeight.Medium)
            }
            .padding(10)
            .backgroundColor('#E3F2FD')
            .borderRadius(4)
            .onClick(() => {
              this.imageWidth = anim.width
              this.imageHeight = anim.height
              this.animDuration = anim.duration
              this.animCurve = anim.curve
            })
          }
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)

      Divider()

      Text('手动调节')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row({ space: 12 }) {
        Button('宽度+20')
          .onClick(() => { this.imageWidth += 20 })
        Button('宽度-20')
          .onClick(() => { this.imageWidth = Math.max(10, this.imageWidth - 20) })
        Button('高度+20')
          .onClick(() => { this.imageHeight += 20 })
        Button('高度-20')
          .onClick(() => { this.imageHeight = Math.max(10, this.imageHeight - 20) })
        Button('重置')
          .onClick(() => { this.imageWidth = 100; this.imageHeight = 100 })
          .backgroundColor('#FF6666')
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 045：clip 和 mask 裁剪遮罩 */
@Component
struct ImageClipMaskTestCase045 {
  @State currentClipIndex: number = 0
  @State maskEnabled: boolean = false

  private readonly CLIP_CONFIGS: Array<{ clip: ShapeClip; label: string }> = [
    { clip: new Circle({ width: 150, height: 150 }), label: '圆形裁剪' },
    { clip: new Rect({ width: 150, height: 150 }), label: '矩形裁剪' },
    { clip: new Ellipse({ width: 150, height: 150 }), label: '椭圆裁剪' },
    { clip: new Path().commands('M0 150 L75 0 L150 150 Z'), label: '三角形裁剪' }
  ]

  build() {
    Column() {
      Text('Image clip/mask属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('clip裁剪效果')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(150)
            .height(150)
            .clip(this.CLIP_CONFIGS[this.currentClipIndex].clip)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Blue })
        }
        .margin({ right: 16 })

        Column() {
          Text('原始图片')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(150)
            .height(150)
            .objectFit(ImageFit.Cover)
            .border({ width: 1, color: Color.Gray })
        }
      }
      .margin({ bottom: 16 })

      Text(`当前裁剪: ${this.CLIP_CONFIGS[this.currentClipIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Row({ space: 12 }) {
        ForEach(this.CLIP_CONFIGS, (config: { clip: ShapeClip; label: string }, index: number) => {
          Button(config.label)
            .fontSize(11)
            .onClick(() => {
              this.currentClipIndex = index
            })
            .backgroundColor(index === this.currentClipIndex ? '#2196F3' : '#EEEEEE')
        })
      }
      .margin({ bottom: 16 })

      Divider()

      Text('clip + borderRadius对比')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(80)
          .height(80)
          .clip(new Circle({ width: 80, height: 80 }))
          .margin({ right: 16 })

        Image($r('app.media.startIcon'))
          .width(80)
          .height(80)
          .borderRadius(40)
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 046：视觉效果叠加 */
@Component
struct ImageVisualEffectsTestCase046 {
  @State brightnessValue: number = 1.0
  @State contrastValue: number = 1.0
  @State saturateValue: number = 1.0
  @State blurValue: number = 0
  @State grayscaleValue: number = 0
  @State sepiaValue: number = 0
  @State invertValue: number = 0
  @State hueRotateValue: number = 0
  @State currentPresetIndex: number = 0

  private readonly PRESETS: Array<{
    name: string; brightness: number; contrast: number; saturate: number;
    blur: number; grayscale: number; sepia: number; invert: number; hueRotate: number
  }> = [
    { name: '原图', brightness: 1, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '高亮', brightness: 1.3, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '暗淡', brightness: 0.7, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '高对比', brightness: 1, contrast: 1.5, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '鲜艳', brightness: 1, contrast: 1, saturate: 2,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '灰度', brightness: 1, contrast: 1, saturate: 1,
      blur: 0, grayscale: 1, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '模糊', brightness: 1, contrast: 1, saturate: 1,
      blur: 5, grayscale: 0, sepia: 0, invert: 0, hueRotate: 0 },
    { name: '怀旧', brightness: 1, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 1, invert: 0, hueRotate: 0 },
    { name: '反色', brightness: 1, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 1, hueRotate: 0 },
    { name: '色相旋转', brightness: 1, contrast: 1, saturate: 1,
      blur: 0, grayscale: 0, sepia: 0, invert: 0, hueRotate: 180 },
    { name: '梦幻', brightness: 1.1, contrast: 0.8, saturate: 1.2,
      blur: 2, grayscale: 0, sepia: 0, invert: 0, hueRotate: 120 },
    { name: '复古', brightness: 1.05, contrast: 0.9, saturate: 0.8,
      blur: 0, grayscale: 0, sepia: 0.4, invert: 0, hueRotate: 30 }
  ]

  build() {
    Column() {
      Text('Image视觉效果叠加测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image($r('app.media.startIcon'))
        .width(150)
        .height(150)
        .brightness(this.brightnessValue)
        .contrast(this.contrastValue)
        .saturate(this.saturateValue)
        .blur(this.blurValue)
        .grayscale(this.grayscaleValue)
        .sepia(this.sepiaValue)
        .invert(this.invertValue)
        .hueRotate(this.hueRotateValue)
        .objectFit(ImageFit.Cover)
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)
        .margin({ bottom: 16 })

      Text('效果预设')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.PRESETS, (preset: {
          name: string; brightness: number; contrast: number; saturate: number;
          blur: number; grayscale: number; sepia: number; invert: number; hueRotate: number
        }, index: number) => {
          GridItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width(50)
                .height(50)
                .brightness(preset.brightness)
                .contrast(preset.contrast)
                .saturate(preset.saturate)
                .blur(preset.blur)
                .grayscale(preset.grayscale)
                .sepia(preset.sepia)
                .invert(preset.invert)
                .hueRotate(preset.hueRotate)
                .borderRadius(4)
                .border({
                  width: index === this.currentPresetIndex ? 2 : 1,
                  color: index === this.currentPresetIndex ? Color.Blue : Color.Gray
                })

              Text(preset.name)
                .fontSize(10)
                .margin({ top: 2 })
            }
            .padding(6)
            .onClick(() => {
              this.currentPresetIndex = index
              this.brightnessValue = preset.brightness
              this.contrastValue = preset.contrast
              this.saturateValue = preset.saturate
              this.blurValue = preset.blur
              this.grayscaleValue = preset.grayscale
              this.sepiaValue = preset.sepia
              this.invertValue = preset.invert
              this.hueRotateValue = preset.hueRotate
            })
          }
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)

      Button('重置')
        .onClick(() => {
          this.brightnessValue = 1; this.contrastValue = 1; this.saturateValue = 1
          this.blurValue = 0; this.grayscaleValue = 0; this.sepiaValue = 0
          this.invertValue = 0; this.hueRotateValue = 0; this.currentPresetIndex = 0
        })
        .backgroundColor('#FF6666')
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 原 050：手势交互 */
@Component
struct ImageGestureTestCase050 {
  @State scaleValue: number = 1.0
  @State rotateAngle: number = 0
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State gestureLog: string = ''
  @State tapCount: number = 0
  @State longPressCount: number = 0

  build() {
    Column() {
      Text('Image手势交互测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Stack() {
        Image($r('app.media.startIcon'))
          .width(150)
          .height(150)
          .objectFit(ImageFit.Cover)
          .scale({ x: this.scaleValue, y: this.scaleValue })
          .rotate({ angle: this.rotateAngle })
          .translate({ x: this.offsetX, y: this.offsetY })
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .gesture(
            GestureGroup(GestureMode.Exclusive,
              TapGesture({ count: 1 })
                .onAction(() => {
                  this.tapCount++
                  this.gestureLog = `单击(${this.tapCount}次)`
                }),
              TapGesture({ count: 2 })
                .onAction(() => {
                  this.gestureLog = `双击 - 放大1.5x`
                  this.scaleValue = 1.5
                }),
              LongPressGesture({ repeatInterval: 500 })
                .onAction(() => {
                  this.longPressCount++
                  this.gestureLog = `长按(${this.longPressCount}次) - 旋转90`
                  this.rotateAngle += 90
                }),
              PinchGesture({ fingers: 2 })
                .onActionEnd((event: GestureEvent) => {
                  this.scaleValue = Math.max(0.5, Math.min(3, this.scaleValue * event.scale))
                  this.gestureLog = `捏合缩放: ${this.scaleValue.toFixed(2)}x`
                }),
              PanGesture({ fingers: 1 })
                .onActionUpdate((event: GestureEvent) => {
                  this.offsetX += event.offsetX
                  this.offsetY += event.offsetY
                  this.gestureLog = `拖动: (${this.offsetX.toFixed(0)}, ${this.offsetY.toFixed(0)})`
                })
            )
          )
      }
      .width('100%')
      .height(200)
      .margin({ bottom: 16 })

      Text(this.gestureLog || '请对图片进行手势操作')
        .fontSize(14)
        .fontColor(this.gestureLog ? Color.Orange : Color.Gray)
        .margin({ bottom: 8 })

      Text(`缩放:${this.scaleValue.toFixed(2)} 旋转:${this.rotateAngle}° 偏移:(${this.offsetX},${this.offsetY})`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Row({ space: 8 }) {
        Button('放大')
          .onClick(() => { this.scaleValue = Math.min(3, this.scaleValue + 0.3) })
          .fontSize(11)
        Button('缩小')
          .onClick(() => { this.scaleValue = Math.max(0.3, this.scaleValue - 0.3) })
          .fontSize(11)
        Button('旋转+45')
          .onClick(() => { this.rotateAngle += 45 })
          .fontSize(11)
        Button('旋转-45')
          .onClick(() => { this.rotateAngle -= 45 })
          .fontSize(11)
        Button('重置')
          .onClick(() => {
            this.scaleValue = 1; this.rotateAngle = 0; this.offsetX = 0; this.offsetY = 0
            this.gestureLog = ''; this.tapCount = 0; this.longPressCount = 0
          })
          .backgroundColor('#FF6666')
          .fontSize(11)
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseEffectsInteraction {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageSizeAnimationTestCase038() }
          .tabBar('宽高动画')
        TabContent() { ImageClipMaskTestCase045() }
          .tabBar('clip·mask')
        TabContent() { ImageVisualEffectsTestCase046() }
          .tabBar('视觉效果')
        TabContent() { ImageGestureTestCase050() }
          .tabBar('手势交互')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

/**
 * Image 拖拽与无障碍合集
 * 覆盖：draggable 拖拽行为 / 无障碍属性 / 焦点与可见性
 */

/** 拖拽行为 */
@Component
struct ImageDraggableScene {
  @State draggable: boolean = true
  @State dragBehavior: DragBehavior = DragBehavior.Copy
  @State log: string = '拖拽图片到外部应用以观察效果'

  build() {
    Column({ space: 12 }) {
      Text('Image 拖拽行为测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image($r('app.media.startIcon'))
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .draggable(this.draggable)
        .dragBehavior(this.dragBehavior)
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)

      Text(this.log)
        .fontSize(12)
        .fontColor(Color.Gray)

      Row({ space: 8 }) {
        Button(this.draggable ? '可拖拽:开' : '可拖拽:关')
          .fontSize(11)
          .onClick(() => { this.draggable = !this.draggable })
        Button('复制模式')
          .fontSize(11)
          .backgroundColor(this.dragBehavior === DragBehavior.Copy ? '#007DFF' : '#E0E0E0')
          .onClick(() => { this.dragBehavior = DragBehavior.Copy })
        Button('移动模式')
          .fontSize(11)
          .backgroundColor(this.dragBehavior === DragBehavior.Move ? '#007DFF' : '#E0E0E0')
          .onClick(() => { this.dragBehavior = DragBehavior.Move })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
    .justifyContent(FlexAlign.Center)
  }
}

/** 无障碍属性 */
@Component
struct ImageAccessibilityScene {
  @State groupEnabled: boolean = true
  @State level: AccessibilityLevel = AccessibilityLevel.YES
  @State important: AccessibilityImportant = AccessibilityImportant.Yes
  @State announce: string = ''

  private readonly LEVELS: Array<{ label: string; value: AccessibilityLevel }> = [
    { label: 'YES', value: AccessibilityLevel.YES },
    { label: 'NO', value: AccessibilityLevel.NO },
    { label: 'AUTO', value: AccessibilityLevel.AUTO }
  ]

  build() {
    Column({ space: 12 }) {
      Text('Image 无障碍属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image($r('app.media.startIcon'))
        .width(120)
        .height(120)
        .objectFit(ImageFit.Cover)
        .borderRadius(8)
        .accessibilityText('演示图片')
        .accessibilityDescription('一张用于无障碍测试的图标')
        .accessibilityGroup(this.groupEnabled)
        .accessibilityLevel(this.level)
        .accessibilityImportant(this.important)

      Text(`group:${this.groupEnabled} level:${this.level} important:${this.important}`)
        .fontSize(12)
        .fontColor(Color.Gray)

      Text(this.announce || '使用屏幕朗读功能查看无障碍文案')
        .fontSize(12)
        .fontColor(this.announce ? Color.Orange : Color.Gray)

      Row({ space: 8 }) {
        Button(this.groupEnabled ? '组合:开' : '组合:关')
          .fontSize(11)
          .onClick(() => { this.groupEnabled = !this.groupEnabled })
        Button('朗读一次')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .onClick(() => {
            this.announce = `已触发朗读: 演示图片 (level=${this.level})`
          })
      }

      Row({ space: 8 }) {
        ForEach(this.LEVELS, (item: { label: string; value: AccessibilityLevel }) => {
          Button(item.label)
            .fontSize(11)
            .backgroundColor(this.level === item.value ? '#007DFF' : '#E0E0E0')
            .onClick(() => { this.level = item.value })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** 焦点与可见性 */
@Component
struct ImageFocusScene {
  @State focused: boolean = false
  @State focusCount: number = 0
  @State blurCount: number = 0
  @State visibleRatio: number = 0

  build() {
    Column({ space: 12 }) {
      Text('Image 焦点与可见性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image($r('app.media.startIcon'))
        .width(140)
        .height(140)
        .objectFit(ImageFit.Cover)
        .focusable(true)
        .tabIndex(1)
        .border({
          width: this.focused ? 4 : 2,
          color: this.focused ? Color.Red : Color.Gray
        })
        .borderRadius(8)
        .onFocus(() => {
          this.focused = true
          this.focusCount++
        })
        .onBlur(() => {
          this.focused = false
          this.blurCount++
        })
        .onVisibleAreaChange([0, 0.5, 1], (isVisible: boolean, ratio: number) => {
          this.visibleRatio = ratio
        })

      Text(`聚焦:${this.focused ? '是' : '否'} 聚焦次数:${this.focusCount} 失焦次数:${this.blurCount}`)
        .fontSize(12)
        .fontColor(Color.Gray)
      Text(`可见区域比例:${(this.visibleRatio * 100).toFixed(0)}%`)
        .fontSize(12)
        .fontColor(Color.Gray)

      Text('使用 Tab 键或方向键在图片上聚焦以观察边框变化')
        .fontSize(11)
        .fontColor(Color.Orange)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseDragAccessibility {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageDraggableScene() }
          .tabBar('拖拽')
        TabContent() { ImageAccessibilityScene() }
          .tabBar('无障碍')
        TabContent() { ImageFocusScene() }
          .tabBar('焦点·可见')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

/**
 * Image 图片信息与解码合集
 * 覆盖：onComplete 尺寸回填 / sourceSize 解码尺寸 / onError 错误诊断
 */

/** onComplete 尺寸回填 */
@Component
struct ImageOnCompleteScene {
  @State imgWidth: number = 0
  @State imgHeight: number = 0
  @State compWidth: number = 0
  @State compHeight: number = 0
  @State loadStatus: number = -1
  @State completeCount: number = 0

  build() {
    Column({ space: 12 }) {
      Text('Image onComplete 尺寸回填测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image($r('app.media.startIcon'))
        .width(160)
        .height(160)
        .objectFit(ImageFit.Cover)
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)
        .onComplete((event) => {
          if (event) {
            this.imgWidth = event.width
            this.imgHeight = event.height
            this.compWidth = event.componentWidth
            this.compHeight = event.componentHeight
            this.loadStatus = event.loadingStatus
          }
          this.completeCount++
        })

      Text(`解码尺寸: ${this.imgWidth} x ${this.imgHeight}`)
        .fontSize(13)
        .fontColor(Color.Gray)
      Text(`组件尺寸: ${this.compWidth} x ${this.compHeight}`)
        .fontSize(13)
        .fontColor(Color.Gray)
      Text(`loadingStatus: ${this.loadStatus}  onComplete 次数: ${this.completeCount}`)
        .fontSize(12)
        .fontColor(Color.Orange)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** sourceSize 解码尺寸对比 */
@Component
struct ImageSourceSizeScene {
  @State sizes: Array<{ label: string; w: number; h: number }> = [
    { label: '原始', w: 0, h: 0 },
    { label: '32x32', w: 32, h: 32 },
    { label: '96x96', w: 96, h: 96 }
  ]
  @State decoded: Array<string> = ['', '', '']

  build() {
    Column({ space: 12 }) {
      Text('Image sourceSize 解码尺寸对比')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Row({ space: 8 }) {
        ForEach(this.sizes, (s: { label: string; w: number; h: number }, idx: number) => {
          Column({ space: 4 }) {
            Image($r('app.media.startIcon'))
              .width(80)
              .height(80)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
              .border({ width: 1, color: Color.Gray })
              .sourceSize(s.w === 0 ? undefined : { width: s.w, height: s.h })
              .onComplete((event) => {
                if (event) {
                  this.decoded[idx] = `${event.width}x${event.height}`
                }
              })

            Text(s.label)
              .fontSize(11)
              .fontColor(Color.Gray)
            Text(this.decoded[idx] || '-')
              .fontSize(10)
              .fontColor(Color.Blue)
          }
        }, (s: { label: string; w: number; h: number }) => s.label)
      }

      Text('sourceSize 控制图片解码后的像素尺寸,越小内存占用越低')
        .fontSize(11)
        .fontColor(Color.Orange)
        .margin({ top: 8 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

/** onError 错误诊断 */
@Component
struct ImageErrorDiagnoseScene {
  @State source: ResourceStr = $r('app.media.startIcon')
  @State errMsg: string = ''
  @State errCompW: number = 0
  @State errCompH: number = 0
  @State errorCount: number = 0
  @State sourceLabel: string = '正常资源'

  build() {
    Column({ space: 12 }) {
      Text('Image onError 错误诊断测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Image(this.source)
        .width(160)
        .height(160)
        .objectFit(ImageFit.Cover)
        .alt($r('app.media.startIcon'))
        .border({ width: 2, color: Color.Red })
        .borderRadius(8)
        .onError((error) => {
          this.errMsg = error.message
          this.errCompW = error.componentWidth
          this.errCompH = error.componentHeight
          this.errorCount++
        })

      Text(`当前源: ${this.sourceLabel}`)
        .fontSize(13)
        .fontColor(Color.Gray)
      Text(`错误信息: ${this.errMsg || '无'}`)
        .fontSize(12)
        .fontColor(this.errMsg ? Color.Red : Color.Gray)
      Text(`错误组件尺寸: ${this.errCompW} x ${this.errCompH}  错误次数: ${this.errorCount}`)
        .fontSize(12)
        .fontColor(Color.Orange)

      Row({ space: 8 }) {
        Button('正常资源')
          .fontSize(11)
          .onClick(() => {
            this.source = $r('app.media.startIcon')
            this.sourceLabel = '正常资源'
            this.errMsg = ''
          })
        Button('无效URL')
          .fontSize(11)
          .onClick(() => {
            this.source = 'invalid://nonexistent.jpg'
            this.sourceLabel = '无效URL'
          })
        Button('空字符串')
          .fontSize(11)
          .backgroundColor('#FF6666')
          .onClick(() => {
            this.source = ''
            this.sourceLabel = '空字符串'
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}

@Component
struct ImageTestcaseImageInfoDecode {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageOnCompleteScene() }
          .tabBar('onComplete')
        TabContent() { ImageSourceSizeScene() }
          .tabBar('sourceSize')
        TabContent() { ImageErrorDiagnoseScene() }
          .tabBar('onError诊断')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}

@Entry
@Component
struct ImageTestCategoryEffectInteraction {
  @State currentIndex: number = 0

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.Start, index: this.currentIndex }) {
        TabContent() { ImageTestcaseEffectsInteraction() }
          .tabBar('动效交互')
        TabContent() { ImageTestcaseDragAccessibility() }
          .tabBar('拖拽无障碍')
        TabContent() { ImageTestcaseImageInfoDecode() }
          .tabBar('信息解码')
      }
      .barMode(BarMode.Scrollable)
      .scrollable(true)
      .onChange((index: number) => { this.currentIndex = index })
    }
    .width('100%')
    .height('100%')
  }
}
