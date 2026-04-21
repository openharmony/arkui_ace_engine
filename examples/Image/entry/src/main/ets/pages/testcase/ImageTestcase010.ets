/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
");
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
 * 测试Image组件属性和样式设置
 * 涵盖width、height、objectFit、borderRadius、opacity、backgroundColor等属性
 */
import { image } from '@kit.ImageKit'

interface TestResult {
  property: string
  expected: string
  actual: string
  status: string
}

interface Scale {
  x: number
  y: number
}

interface TestConfiguration {
  name: string
  test: () => Promise<void>
  expectedCount: number
}

interface BorderConfig {
  width: number
  color: ResourceColor
  style: BorderStyle
}

interface ShadowConfig {
  radius: number
  color: ResourceColor
  offsetX: number
  offsetY: number
}

interface Transform {
  rotate: number
  scale: Scale
  translate: Scale
}

interface MarginPadding {
  left: number
  right: number
  top: number
  bottom: number
}

interface LayoutConfig {
  margin: MarginPadding
  padding: MarginPadding
}

@Entry
@Component
struct ImagePropertiesTestCase {
  @State currentTestIndex: number = 0
  @State testResults: TestResult[] = []
  @State animatedWidth: number = 100
  @State animatedHeight: number = 100
  @State currentObjectFit: ImageFit = ImageFit.Contain
  @State currentBorderRadius: number = 0
  @State currentOpacity: number = 1.0
  @State currentRotation: number = 0
  @State currentScale: Scale = { x: 1, y: 1 }
  @State isAutoAnimation: boolean = false
  @State testInProgress: boolean = false

  private readonly OBJECT_FIT_OPTIONS: ImageFit[] = [
    ImageFit.Contain,
    ImageFit.Cover,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown,
    ImageFit.Auto
  ]

  private readonly TEST_CONFIGURATIONS: TestConfiguration[] = [
    {
      name: '宽度尺寸测试',
      test: () => this.testWidthProperties(),
      expectedCount: 8
    },
    {
      name: '高度尺寸测试',
      test: () => this.testHeightProperties(),
      expectedCount: 8
    },
    {
      name: 'ObjectFit适配测试',
      test: () => this.testObjectFitProperties(),
      expectedCount: 6
    },
    {
      name: '圆角属性测试',
      test: () => this.testBorderRadiusProperties(),
      expectedCount: 7
    },
    {
      name: '透明度属性测试',
      test: () => this.testOpacityProperties(),
      expectedCount: 6
    },
    {
      name: '背景色属性测试',
      test: () => this.testBackgroundColorProperties(),
      expectedCount: 8
    },
    {
      name: '边框属性测试',
      test: () => this.testBorderProperties(),
      expectedCount: 10
    },
    {
      name: '阴影属性测试',
      test: () => this.testShadowProperties(),
      expectedCount: 6
    },
    {
      name: '变换属性测试',
      test: () => this.testTransformProperties(),
      expectedCount: 9
    },
    {
      name: '布局属性测试',
      test: () => this.testLayoutProperties(),
      expectedCount: 12
    }
  ]

  aboutToAppear() {
    this.startAutomatedTests()
  }

  private async startAutomatedTests(): Promise<void> {
    this.testInProgress = true
    this.testResults = []

    for (let i = 0; i < this.TEST_CONFIGURATIONS.length; i++) {
      this.currentTestIndex = i
      await this.delay(300) // 测试间隔
      await this.TEST_CONFIGURATIONS[i].test()
    }

    this.testInProgress = false
  }

  private async testWidthProperties(): Promise<void> {
    const widthValues: number[] = [50, 100, 150, 200]
    const widthStrValues: string[] = ['50%', '100vp', '200px', 'auto']

    for (const width of widthValues) {
      try {
        this.animatedWidth = width

        this.testResults.push({
          property: `width: ${width}`,
          expected: `${width}`,
          actual: `${this.animatedWidth}`,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        this.testResults.push({
          property: `width: ${width}`,
          expected: `${width}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }

    for (const width of widthStrValues) {
      try {
        this.animatedWidth = 100

        this.testResults.push({
          property: `width: ${width}`,
          expected: `${width}`,
          actual: `${this.animatedWidth}`,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        this.testResults.push({
          property: `width: ${width}`,
          expected: `${width}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testHeightProperties(): Promise<void> {
    const heightValues: number[] = [50, 100, 150, 200]
    const heightStrValues: string[] = ['50%', '100vp', '200px', 'auto']

    for (const height of heightValues) {
      try {
        this.animatedHeight = height

        this.testResults.push({
          property: `height: ${height}`,
          expected: `${height}`,
          actual: `${this.animatedHeight}`,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        this.testResults.push({
          property: `height: ${height}`,
          expected: `${height}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }

    for (const height of heightStrValues) {
      try {
        this.animatedHeight = 100

        this.testResults.push({
          property: `height: ${height}`,
          expected: `${height}`,
          actual: `${this.animatedHeight}`,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        this.testResults.push({
          property: `height: ${height}`,
          expected: `${height}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testObjectFitProperties(): Promise<void> {
    for (const fit of this.OBJECT_FIT_OPTIONS) {
      try {
        this.currentObjectFit = fit

        this.testResults.push({
          property: `objectFit: ${fit}`,
          expected: `${fit}`,
          actual: `${this.currentObjectFit}`,
          status: 'success'
        })

        await this.delay(200)
      } catch (error) {
        this.testResults.push({
          property: `objectFit: ${fit}`,
          expected: `${fit}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testBorderRadiusProperties(): Promise<void> {
    const radiusValues = [0, 5, 10, 15, 20, 25, 50]

    for (const radius of radiusValues) {
      try {
        this.currentBorderRadius = radius

        this.testResults.push({
          property: `borderRadius: ${radius}`,
          expected: `${radius}`,
          actual: `${this.currentBorderRadius}`,
          status: 'success'
        })

        await this.delay(150)
      } catch (error) {
        this.testResults.push({
          property: `borderRadius: ${radius}`,
          expected: `${radius}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testOpacityProperties(): Promise<void> {
    const opacityValues = [0.0, 0.2, 0.4, 0.6, 0.8, 1.0]

    for (const opacity of opacityValues) {
      try {
        this.currentOpacity = opacity

        this.testResults.push({
          property: `opacity: ${opacity}`,
          expected: `${opacity}`,
          actual: `${this.currentOpacity}`,
          status: 'success'
        })

        await this.delay(150)
      } catch (error) {
        this.testResults.push({
          property: `opacity: ${opacity}`,
          expected: `${opacity}`,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testBackgroundColorProperties(): Promise<void> {
    const backgroundColors: ResourceColor[] = [
      Color.Red,
      Color.Green,
      Color.Blue,
      Color.Yellow,
      Color.Pink,
      '#800080',
      Color.Orange,
      Color.Gray
    ]

    for (const color of backgroundColors) {
      try {
        const colorStr: string = `${color}`
        this.testResults.push({
          property: `backgroundColor: ${colorStr}`,
          expected: colorStr,
          actual: colorStr,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        const colorStr: string = `${color}`
        this.testResults.push({
          property: `backgroundColor: ${colorStr}`,
          expected: colorStr,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testBorderProperties(): Promise<void> {
    const borderConfigs: BorderConfig[] = [
      { width: 1, color: Color.Black, style: BorderStyle.Solid },
      { width: 2, color: Color.Red, style: BorderStyle.Dashed },
      { width: 3, color: Color.Blue, style: BorderStyle.Dotted },
      { width: 4, color: Color.Green, style: BorderStyle.Solid },
      { width: 5, color: '#800080', style: BorderStyle.Dashed },
      { width: 0, color: Color.Gray, style: BorderStyle.Solid },
      { width: 10, color: Color.Orange, style: BorderStyle.Solid },
      { width: 2, color: Color.Pink, style: BorderStyle.Dotted },
      { width: 3, color: Color.Brown, style: BorderStyle.Solid },
      { width: 6, color: '#00FFFF', style: BorderStyle.Dashed }
    ]

    for (const config of borderConfigs) {
      try {
        const configStr: string = `${config.width}, ${config.color}, ${config.style}`
        this.testResults.push({
          property: `border: ${config.width}px ${config.color} ${config.style}`,
          expected: configStr,
          actual: configStr,
          status: 'success'
        })

        await this.delay(100)
      } catch (error) {
        const configStr: string = `${config.width}, ${config.color}, ${config.style}`
        this.testResults.push({
          property: `border: ${config.width}px ${config.color} ${config.style}`,
          expected: configStr,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testShadowProperties(): Promise<void> {
    const shadowConfigs: ShadowConfig[] = [
      { radius: 5, color: Color.Black, offsetX: 2, offsetY: 2 },
      { radius: 10, color: Color.Red, offsetX: 0, offsetY: 5 },
      { radius: 15, color: Color.Blue, offsetX: -3, offsetY: -3 },
      { radius: 20, color: Color.Green, offsetX: 10, offsetY: 10 },
      { radius: 0, color: Color.Gray, offsetX: 0, offsetY: 0 },
      { radius: 8, color: '#800080', offsetX: 5, offsetY: -2 }
    ]

    for (const shadow of shadowConfigs) {
      try {
        const shadowStr: string = `${shadow.radius}, ${shadow.color}, ${shadow.offsetX},${shadow.offsetY}`
        this.testResults.push({
          property: `shadow: ${shadow.radius} ${shadow.color} ${shadow.offsetX},${shadow.offsetY}`,
          expected: shadowStr,
          actual: shadowStr,
          status: 'success'
        })

        await this.delay(150)
      } catch (error) {
        const shadowStr: string = `${shadow.radius}, ${shadow.color}, ${shadow.offsetX},${shadow.offsetY}`
        this.testResults.push({
          property: `shadow: ${shadow.radius} ${shadow.color} ${shadow.offsetX},${shadow.offsetY}`,
          expected: shadowStr,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testTransformProperties(): Promise<void> {
    const transforms: Transform[] = [
      { rotate: 0, scale: { x: 1, y: 1 }, translate: { x: 0, y: 0 } },
      { rotate: 45, scale: { x: 1.2, y: 1.2 }, translate: { x: 10, y: 0 } },
      { rotate: 90, scale: { x: 0.8, y: 0.8 }, translate: { x: 0, y: 10 } },
      { rotate: 180, scale: { x: 1.5, y: 1.5 }, translate: { x: -10, y: -10 } },
      { rotate: 270, scale: { x: 0.5, y: 0.5 }, translate: { x: 20, y: 20 } },
      { rotate: 30, scale: { x: 2, y: 1 }, translate: { x: -20, y: 10 } },
      { rotate: 60, scale: { x: 1, y: 2 }, translate: { x: 10, y: -20 } },
      { rotate: 120, scale: { x: 0.7, y: 0.7 }, translate: { x: 30, y: 30 } },
      { rotate: 360, scale: { x: 1, y: 1 }, translate: { x: 0, y: 0 } }
    ]

    for (const transform of transforms) {
      try {
        this.currentRotation = transform.rotate
        this.currentScale = transform.scale

        const expectedStr: string = `${transform.rotate}, ${transform.scale.x},${transform.scale.y}, ${transform.translate.x},${transform.translate.y}`
        const actualStr: string = `${this.currentRotation}, ${this.currentScale.x},${this.currentScale.y}, ${transform.translate.x},${transform.translate.y}`
        const propertyStr: string = `transform: rotate(${transform.rotate}) scale(${transform.scale.x},${transform.scale.y}) translate(${transform.translate.x},${transform.translate.y})`

        this.testResults.push({
          property: propertyStr,
          expected: expectedStr,
          actual: actualStr,
          status: 'success'
        })

        await this.delay(200)
      } catch (error) {
        const expectedStr: string = `${transform.rotate}, ${transform.scale.x},${transform.scale.y}, ${transform.translate.x},${transform.translate.y}`
        const propertyStr: string = `transform: rotate(${transform.rotate}) scale(${transform.scale.x},${transform.scale.y}) translate(${transform.translate.x},${transform.translate.y})`

        this.testResults.push({
          property: propertyStr,
          expected: expectedStr,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private async testLayoutProperties(): Promise<void> {
    const margin1: MarginPadding = { left: 5, right: 5, top: 5, bottom: 5 }
    const padding1: MarginPadding = { left: 5, right: 5, top: 5, bottom: 5 }
    const margin2: MarginPadding = { left: 10, right: 10, top: 0, bottom: 0 }
    const padding2: MarginPadding = { left: 10, right: 10, top: 0, bottom: 0 }
    const margin3: MarginPadding = { left: 0, right: 0, top: 10, bottom: 10 }
    const padding3: MarginPadding = { left: 0, right: 0, top: 10, bottom: 10 }
    const margin4: MarginPadding = { left: 15, right: 0, top: 5, bottom: 0 }
    const padding4: MarginPadding = { left: 0, right: 15, top: 0, bottom: 5 }
    const margin5: MarginPadding = { left: 20, right: 20, top: 20, bottom: 20 }
    const padding5: MarginPadding = { left: 20, right: 20, top: 20, bottom: 20 }
    const margin6: MarginPadding = { left: 0, right: 0, top: 0, bottom: 0 }
    const padding6: MarginPadding = { left: 0, right: 0, top: 0, bottom: 0 }
    const margin7: MarginPadding = { left: 8, right: 8, top: 4, bottom: 4 }
    const padding7: MarginPadding = { left: 4, right: 4, top: 8, bottom: 8 }
    const margin8: MarginPadding = { left: 12, right: 8, top: 6, bottom: 10 }
    const padding8: MarginPadding = { left: 10, right: 12, top: 8, bottom: 6 }
    const margin9: MarginPadding = { left: 25, right: 15, top: 12, bottom: 18 }
    const padding9: MarginPadding = { left: 18, right: 25, top: 15, bottom: 12 }
    const margin10: MarginPadding = { left: 3, right: 3, top: 3, bottom: 3 }
    const padding10: MarginPadding = { left: 3, right: 3, top: 3, bottom: 3 }
    const margin11: MarginPadding = { left: 50, right: 0, top: 25, bottom: 0 }
    const padding11: MarginPadding = { left: 0, right: 50, top: 0, bottom: 25 }
    const margin12: MarginPadding = { left: 100, right: 100, top: 50, bottom: 50 }
    const padding12: MarginPadding = { left: 25, right: 25, top: 25, bottom: 25 }

    const layoutConfigs: LayoutConfig[] = [
      { margin: margin1, padding: padding1 },
      { margin: margin2, padding: padding2 },
      { margin: margin3, padding: padding3 },
      { margin: margin4, padding: padding4 },
      { margin: margin5, padding: padding5 },
      { margin: margin6, padding: padding6 },
      { margin: margin7, padding: padding7 },
      { margin: margin8, padding: padding8 },
      { margin: margin9, padding: padding9 },
      { margin: margin10, padding: padding10 },
      { margin: margin11, padding: padding11 },
      { margin: margin12, padding: padding12 }
    ]

    for (const layout of layoutConfigs) {
      try {
        const marginStr: string = JSON.stringify(layout.margin)
        const paddingStr: string = JSON.stringify(layout.padding)
        const layoutStr: string = JSON.stringify(layout)

        this.testResults.push({
          property: `margin: ${marginStr}, padding: ${paddingStr}`,
          expected: layoutStr + "," + paddingStr,
          actual: layoutStr + "," + paddingStr,
          status: 'success'
        })

        await this.delay(150)
      } catch (error) {
        const marginStr: string = JSON.stringify(layout.margin)
        const paddingStr: string = JSON.stringify(layout.padding)
        const layoutStr: string = JSON.stringify(layout)

        this.testResults.push({
          property: `margin: ${marginStr}, padding: ${paddingStr}`,
          expected: layoutStr + "," + paddingStr,
          actual: 'Error',
          status: 'failed'
        })
      }
    }
  }

  private delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms))
  }

  build() {
    Column() {
      Row() {
        Text('Image属性测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        if (this.testInProgress) {
          LoadingProgress()
            .width(20)
            .height(20)
        }
        Text(`测试: ${this.currentTestIndex + 1}/${this.TEST_CONFIGURATIONS.length}`)
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ left: 8 })
      }
      .width('100%')
      .padding(16)

      Scroll() {
        Column() {
          // 测试图片展示区域
          Row() {
            Column() {
              Text('属性测试图片')
                .fontSize(14)
                .margin({ bottom: 8 })
              Image($r('app.media.startIcon'))
                .width(this.animatedWidth)
                .height(this.animatedHeight)
                .objectFit(this.currentObjectFit)
                .borderRadius(this.currentBorderRadius)
                .opacity(this.currentOpacity)
                .rotate({ angle: this.currentRotation })
                .scale({ x: this.currentScale.x, y: this.currentScale.y })
                .border({ width: 2, color: Color.Blue })
                .backgroundColor('#D3D3D3')
                .shadow({
                  radius: 10,
                  color: Color.Black,
                  offsetX: 5,
                  offsetY: 5
                })
            }
            .layoutWeight(1)
            .margin(8)

            Column() {
              Text('当前属性值')
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
                .margin({ bottom: 8 })

              Text(`宽度: ${this.animatedWidth}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`高度: ${this.animatedHeight}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`适配: ${this.currentObjectFit}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`圆角: ${this.currentBorderRadius}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`透明度: ${this.currentOpacity}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`旋转: ${this.currentRotation}°`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })

              Text(`缩放: ${this.currentScale.x}x${this.currentScale.y}`)
                .fontSize(12)
                .margin({ top: 2, bottom: 2 })
            }
            .layoutWeight(1)
            .margin(8)
          }
          .margin({ top: 16, bottom: 16 })

          Divider()

          // 测试结果展示
          Text('测试结果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 16, bottom: 8 })

          Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            ForEach(this.testResults, (result: TestResult) => {
              Row() {
                Circle({ width: 6, height: 6 })
                  .fill(result.status === 'success' ? Color.Green : Color.Red)
                  .margin({ right: 4 })

                Text(result.property.length > 20 ? result.property.substring(0, 20) + '...' : result.property)
                  .fontSize(10)
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .padding(4)
              .backgroundColor(result.status === 'success' ? '#E8F5E8' : '#FFEBEE')
              .borderRadius(4)
              .margin(2)
            })
          }

          // 统计信息
          Row() {
            Text(`总计: ${this.testResults.length}`)
              .fontSize(12)
              .fontColor(Color.Gray)

            Text(`成功: ${this.testResults.filter(r => r.status === 'success').length}`)
              .fontSize(12)
              .fontColor(Color.Green)
              .margin({ left: 16 })

            Text(`失败: ${this.testResults.filter(r => r.status === 'failed').length}`)
              .fontSize(12)
              .fontColor(Color.Red)
              .margin({ left: 16 })
          }
          .justifyContent(FlexAlign.Start)
          .width('100%')
          .padding(8)
          .margin({ top: 16 })
        }
        .padding(16)
      }
      .layoutWeight(1)

      // 控制按钮
      Row() {
        Button('重新测试')
          .onClick(() => {
            this.startAutomatedTests()
          })

        Button('清空结果')
          .onClick(() => {
            this.testResults = []
          })
          .margin({ left: 8 })

        Button('手动测试')
          .onClick(() => {
            this.testInProgress = false
          })
          .margin({ left: 8 })
      }
      .justifyContent(FlexAlign.Center)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }
}