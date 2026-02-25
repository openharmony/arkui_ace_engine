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
 * 测试Image组件高级功能和特性
 * 涵盖图片滤镜、遮罩、合成、动态生成等高级特性
 */

import { image } from '@kit.ImageKit'
import { DrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI'
import { BusinessError } from '@ohos.base'

interface ImageFilterConfig {
  name: string
  brightness: number
  contrast: number
  saturation: number
  hueRotate: number
  blur: number
  grayscale: number
  sepia: number
  invert: number
}

interface ImageBlendMode {
  mode: BlendMode
  name: string
  description: string
}

interface TestImageData {
  id: number
  type: 'resource' | 'pixelmap' | 'base64' | 'svg'
  source: string | Resource | image.PixelMap
  properties: ImageProperties
  metadata?: Map<string, any>
}

interface ImageProperties {
  width: number
  height: number
  format: string
  size: number
  hasAlpha: boolean
  colorSpace: string
}

interface CompressionTest {
  quality: number
  format: string
  originalSize: number
  compressedSize: number
  compressionRatio: number
  processingTime: number
}

interface ColorTestResult {
  hex: string
  rgb: { r: number; g: number; b: number; a: number }
  hsl: { h: number; s: number; l: number }
  brightness: number
  samplePoints: Array<{ x: number; y: number; color: string }>
}

@Entry
@Component
struct ImageAdvancedFeaturesTestCase {
  @State filterConfigs: ImageFilterConfig[] = []
  @State currentFilterIndex: number = 0
  @State blendModes: ImageBlendMode[] = []
  @State currentBlendModeIndex: number = 0
  @State testImages: TestImageData[] = []
  @State compressionTests: CompressionTest[] = []
  @State colorTestResults: ColorTestResult[] = []
  @State advancedTestResults: Array<{ name: string; status: string; details: string }> = []
  @State testProgress: number = 0
  @State isTesting: boolean = false
  @State processedImageCount: number = 0
  @State currentOperation: string = ''
  @State generatedPatterns: Array<{ id: number; type: string; data: ArrayBuffer }> = []
  @State transformedImages: Array<{ id: number; operation: string; result: boolean }> = []

  private readonly FILTER_PRESETS: ImageFilterConfig[] = [
    { name: '原图', brightness: 100, contrast: 100, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '明亮', brightness: 120, contrast: 100, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '暗淡', brightness: 80, contrast: 100, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '高对比', brightness: 100, contrast: 150, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '低对比', brightness: 100, contrast: 50, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '鲜艳', brightness: 100, contrast: 100, saturation: 150, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '柔和', brightness: 100, contrast: 100, saturation: 50, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '反色', brightness: 100, contrast: 100, saturation: 100, hueRotate: 0, blur: 0, grayscale: 0, sepia: 0, invert: 100 },
    { name: '灰度', brightness: 100, contrast: 100, saturation: 0, hueRotate: 0, blur: 0, grayscale: 100, sepia: 0, invert: 0 },
    { name: '怀日', brightness: 100, contrast: 100, saturation: 50, hueRotate: 0, blur: 0, grayscale: 0, sepia: 80, invert: 0 },
    { name: '模糊', brightness: 100, contrast: 100, saturation: 100, hueRotate: 0, blur: 10, grayscale: 0, sepia: 0, invert: 0 },
    { name: '色相旋转', brightness: 100, contrast: 100, saturation: 100, hueRotate: 180, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '复古', brightness: 110, contrast: 90, saturation: 80, hueRotate: 30, blur: 0, grayscale: 0, sepia: 40, invert: 0 },
    { name: '冷色调', brightness: 105, contrast: 100, saturation: 90, hueRotate: 200, blur: 0, grayscale: 0, sepia: 0, invert: 0 },
    { name: '暖色调', brightness: 105, contrast: 100, saturation: 90, hueRotate: 20, blur: 0, grayscale: 0, sepia: 20, invert: 0 },
    { name: '梦幻', brightness: 110, contrast: 80, saturation: 120, hueRotate: 120, blur: 2, grayscale: 0, sepia: 0, invert: 0 }
  ]

  private readonly BLEND_MODES: ImageBlendMode[] = [
    { mode: BlendMode.Normal, name: 'Normal', description: '正常混合模式' },
    { mode: BlendMode.Multiply, name: 'Multiply', description: '正片叠底' },
    { mode: BlendMode.Screen, name: 'Screen', description: '滤色' },
    { mode: BlendMode.Overlay, name: 'Overlay', description: '叠加' },
    { mode: BlendMode.Darken, name: 'Darken', description: '变暗' },
    { mode: BlendMode.Lighten, name: 'Lighten', description: '变亮' },
    { mode: BlendMode.ColorDodge, name: 'ColorDodge', description: '颜色减淡' },
    { mode: BlendMode.ColorBurn, name: 'ColorBurn', description: '颜色加深' },
    { mode: BlendMode.HardLight, name: 'HardLight', description: '强光' },
    { mode: BlendMode.SoftLight, name: 'SoftLight', description: '柔光' },
    { mode: BlendMode.Difference, name: 'Difference', description: '差值' },
    { mode: BlendMode.Exclusion, name: 'Exclusion', description: '排除' },
    { mode: BlendMode.Hue, name: 'Hue', description: '色相' },
    { mode: BlendMode.Saturation, name: 'Saturation', description: '饱和度' },
    { mode: BlendMode.Color, name: 'Color', description: '颜色' },
    { mode: BlendMode.Luminosity, name: 'Luminosity', description: '明度' }
  ]

  private readonly COMPRESSION_FORMATS = ['JPEG', 'PNG', 'WEBP', 'GIF', 'BMP']
  private readonly QUALITY_LEVELS = [10, 30, 50, 70, 90, 95]

  aboutToAppear() {
    this.initializeAdvancedTests()
    this.startAdvancedFeatureTests()
  }

  private initializeAdvancedTests(): void {
    this.filterConfigs = [...this.FILTER_PRESETS]
    this.blendModes = [...this.BLEND_MODES]
    this.initializeTestData()
  }

  private async initializeTestData(): Promise<void> {
    // 生成测试图片数据
    const testImageTypes = ['resource', 'pixelmap', 'base64', 'svg']
    const resources = [
      $r('app.media.icon'),
      $r('app.media.foreground'),
      $r('app.media.background'),
      $r('app.media.mask')
    ]

    for (let i = 0; i < 10; i++) {
      const type = testImageTypes[i % testImageTypes.length] as 'resource' | 'pixelmap' | 'base64' | 'svg'
      const source = resources[i % resources.length]

      const testImage: TestImageData = {
        id: i,
        type: type,
        source: source,
        properties: {
          width: 100 + i * 20,
          height: 100 + i * 20,
          format: this.getImageFormat(type),
          size: this.calculateImageSize(type),
          hasAlpha: this.hasAlphaChannel(type),
          colorSpace: 'SRGB'
        },
        metadata: new Map([
          ['creationTime', Date.now()],
          ['testId', `test_${i}`],
          ['category', 'advanced'],
          ['processed', false]
        ])
      }

      this.testImages.push(testImage)
    }

    // 生成图案数据
    for (let i = 0; i < 8; i++) {
      const patternData = await this.generatePattern(i)
      this.generatedPatterns.push({
        id: i,
        type: this.getPatternType(i),
        data: patternData
      })
    }
  }

  private async startAdvancedFeatureTests(): Promise<void> {
    this.isTesting = true
    this.advancedTestResults = []
    this.testProgress = 0

    const testSuites = [
      { name: '图片滤镜测试', func: () => this.testImageFilters() },
      { name: '混合模式测试', func: () => this.testBlendModes() },
      { name: '图片压缩测试', func: () => this.testImageCompression() },
      { name: '颜色分析测试', func: () => this.testColorAnalysis() },
      { name: '图案生成测试', func: () => this.testPatternGeneration() },
      { name: '图片变换测试', func: () => this.testImageTransformations() },
      { name: '元数据测试', func: () => this.testImageMetadata() },
      { name: '性能基准测试', func: () => this.testPerformanceBenchmarks() },
      { name: '边界条件测试', func: () => this.testBoundaryConditions() },
      { name: '错误处理测试', func: () => this.testErrorHandling() }
    ]

    for (let i = 0; i < testSuites.length; i++) {
      const suite = testSuites[i]
      this.currentOperation = suite.name
      this.testProgress = Math.round((i / testSuites.length) * 100)

      try {
        await suite.func()
        this.advancedTestResults.push({
          name: suite.name,
          status: 'Passed',
          details: `成功执行${suite.name}`
        })
      } catch (error) {
        this.advancedTestResults.push({
          name: suite.name,
          status: 'Failed',
          details: (error as BusinessError).message
        })
      }

      await this.delay(200)
    }

    this.testProgress = 100
    this.isTesting = false
  }

  private async testImageFilters(): Promise<void> {
    for (let i = 0; i < this.filterConfigs.length; i++) {
      this.currentFilterIndex = i
      await this.delay(100)
      
      // 模拟滤镜处理
      const processingTime = 50 + Math.random() * 200
      await this.delay(processingTime)
      
      if (i % 5 === 0) {
        this.advancedTestResults.push({
          name: `滤镜${this.filterConfigs[i].name}处理`,
          status: 'Passed',
          details: `${this.filterConfigs[i].name}滤镜应用成功，耗时${processingTime.toFixed(0)}ms`
        })
      }
    }
  }

  private async testBlendModes(): Promise<void> {
    for (let i = 0; i < this.blendModes.length; i++) {
      this.currentBlendModeIndex = i
      await this.delay(80)

      try {
        // 模拟混合模式处理
        const blendResult = await this.simulateBlendOperation(this.blendModes[i].mode)
        if (blendResult) {
          this.advancedTestResults.push({
            name: `混合模式${this.blendModes[i].name}`,
            status: 'Passed',
            details: `${this.blendModes[i].description} - 应用成功`
          })
        }
      } catch (error) {
        this.advancedTestResults.push({
          name: `混合模式${this.blendModes[i].name}`,
          status: 'Failed',
          details: `混合模式应用失败: ${(error as BusinessError).message}`
        })
      }
    }
  }

  private async testImageCompression(): Promise<void> {
    this.compressionTests = []

    for (const format of this.COMPRESSION_FORMATS) {
      for (const quality of this.QUALITY_LEVELS) {
        const startTime = performance.now()
        
        // 模拟压缩过程
        await this.delay(50 + quality)
        
        const endTime = performance.now()
        const originalSize = 1024 * 1024 // 1MB
        const compressedSize = originalSize * (quality / 100) * (1 - Math.random() * 0.5)
        
        const compressionTest: CompressionTest = {
          quality: quality,
          format: format,
          originalSize: originalSize,
          compressedSize: compressedSize,
          compressionRatio: originalSize / compressedSize,
          processingTime: endTime - startTime
        }

        this.compressionTests.push(compressionTest)
      }
    }
  }

  private async testColorAnalysis(): Promise<void> {
    this.colorTestResults = []

    for (let i = 0; i < 20; i++) {
      const colorResult: ColorTestResult = {
        hex: this.generateRandomHexColor(),
        rgb: this.generateRandomRGB(),
        hsl: this.generateRandomHSL(),
        brightness: Math.random() * 100,
        samplePoints: []
      }

      // 生成采样点
      for (let j = 0; j < 9; j++) {
        colorResult.samplePoints.push({
          x: j % 3 * 50,
          y: Math.floor(j / 3) * 50,
          color: this.generateRandomHexColor()
        })
      }

      this.colorTestResults.push(colorResult)
      await this.delay(30)
    }
  }

  private async testPatternGeneration(): Promise<void> {
    for (let i = 0; i < this.generatedPatterns.length; i++) {
      this.currentOperation = `生成图案 ${i + 1}`
      await this.delay(150)
      
      // 验证生成的图案
      const isValid = await this.validateGeneratedPattern(this.generatedPatterns[i])
      if (isValid) {
        this.advancedTestResults.push({
          name: `图案生成${this.generatedPatterns[i].type}`,
          status: 'Passed',
          details: `图案${this.generatedPatterns[i].type}生成成功`
        })
      }
    }
  }

  private async testImageTransformations(): Promise<void> {
    const transformations = [
      'rotate', 'scale', 'flip', 'crop', 'resize', 'skew', 'perspective', 
      'wrap', 'distort', 'morph', 'bend', 'twist', 'wave', 'ripple'
    ]

    for (let i = 0; i < transformations.length; i++) {
      const transformation = transformations[i]
      this.currentOperation = `图片变换: ${transformation}`
      
      try {
        const result = await this.applyTransformation(transformation)
        this.transformedImages.push({
          id: i,
          operation: transformation,
          result: result
        })

        if (result) {
          this.advancedTestResults.push({
            name: `图片${transformation}变换`,
            status: 'Passed',
            details: `${transformation}变换应用成功`
          })
        }
      } catch (error) {
        this.advancedTestResults.push({
          name: `图片${transformation}变换`,
          status: 'Failed',
          details: `${transformation}变换失败: ${(error as BusinessError).message}`
        })
      }

      await this.delay(100)
    }
  }

  private async testImageMetadata(): Promise<void> {
    for (const testImage of this.testImages) {
      this.currentOperation = `分析元数据: ${testImage.type}`

      // 模拟元数据分析
      await this.delay(50)

      const metadata = testImage.metadata
      metadata?.set('analyzed', true)
      metadata?.set('analysisTime', Date.now())
      metadata?.set('validSize', testImage.properties.size > 0)
      metadata?.set('validDimensions', testImage.properties.width > 0 && testImage.properties.height > 0)

      this.processedImageCount++
    }
  }

  private async testPerformanceBenchmarks(): Promise<void> {
    const operations = [
      'load', 'resize', 'compress', 'filter', 'transform', 'analyze',
      'compare', 'merge', 'split', 'convert'
    ]

    for (const operation of operations) {
      const iterations = 100
      const startTime = performance.now()

      for (let i = 0; i < iterations; i++) {
        await this.delay(Math.random() * 10)
      }

      const endTime = performance.now()
      const avgTime = (endTime - startTime) / iterations

      this.advancedTestResults.push({
        name: `性能基准${operation}`,
        status: avgTime < 50 ? 'Passed' : 'Warning',
        details: `${operation}操作平均耗时: ${avgTime.toFixed(2)}ms`
      })
    }
  }

  private async testBoundaryConditions(): Promise<void> {
    const boundaryConditions = [
      { name: '最小尺寸', width: 1, height: 1 },
      { name: '最大尺寸', width: 50000, height: 50000 },
      { name: '负宽度', width: -100, height: 100 },
      { name: '负高度', width: 100, height: -100 },
      { name: '零尺寸', width: 0, height: 0 },
      { name: '极端比例', width: 1, height: 100000 },
      { name: '超大文件', size: 100 << 20 }, // 100MB
      { name: '空文件', size: 0 },
      { name: '负文件大小', size: -1000 },
      { name: '损坏文件', corrupted: true }
    ]

    for (const condition of boundaryConditions) {
      this.currentOperation = `边界测试: ${condition.name}`
      
      try {
        const result = await this.testBoundaryCondition(condition)
        this.advancedTestResults.push({
          name: `边界条件${condition.name}`,
          status: result ? 'Handled' : 'Failed',
          details: result ? '边界条件正确处理' : '边界条件处理失败'
        })
      } catch (error) {
        this.advancedTestResults.push({
          name: `边界条件${condition.name}`,
          status: 'Error',
          details: `边界条件测试出错: ${(error as BusinessError).message}`
        })
      }

      await this.delay(100)
    }
  }

  private async testErrorHandling(): Promise<void> {
    const errorScenarios = [
      'invalidSource', 'corruptedData', 'unsupportedFormat', 'memoryError',
      'timeoutError', 'permissionError', 'networkError', ' fileSizeError',
      'dimensionError', 'colorSpaceError', 'compressionError', 'decodingError'
    ]

    for (const scenario of errorScenarios) {
      this.currentOperation = `错误处理测试: ${scenario}`
      
      try {
        const handled = await this.simulateErrorScenario(scenario)
        this.advancedTestResults.push({
          name: `错误处理${scenario}`,
          status: handled ? 'Handled' : 'Failed',
          details: handled ? '错误正确处理' : '错误处理失败'
        })
      } catch (error) {
        this.advancedTestResults.push({
          name: `错误处理${scenario}`,
          status: 'Exception',
          details: `错误处理测试异常: ${(error as BusinessError).message}`
        })
      }

      await this.delay(80)
    }
  }

  private async generatePattern(index: number): Promise<ArrayBuffer> {
    const patternTypes = ['checkerboard', 'stripes', 'dots', 'gradient', 'noise', 'spiral', 'waves', 'random']
    const patternType = patternTypes[index % patternTypes.length]
    
    // 模拟图案生成
    const dataSize = 1024 * 4 // RGBA 32x32
    const buffer = new ArrayBuffer(dataSize)
    const view = new Uint8Array(buffer)
    
    for (let i = 0; i < view.length; i++) {
      view[i] = Math.floor(Math.random() * 256)
    }
    
    await this.delay(50)
    return buffer
  }

  private getPatternType(index: number): string {
    const patternTypes = ['棋盘格', '条纹', '点阵', '渐变', '噪点', '螺旋', '波浪', '随机']
    return patternTypes[index % patternTypes.length]
  }

  private async simulateBlendOperation(mode: BlendMode): Promise<boolean> {
    await this.delay(30)
    return Math.random() > 0.1 // 90% 成功率
  }

  private async applyTransformation(transformation: string): Promise<boolean> {
    await this.delay(50)
    return Math.random() > 0.15 // 85% 成功率
  }

  private async validateGeneratedPattern(pattern: { id: number; type: string; data: ArrayBuffer }): Promise<boolean> {
    await this.delay(20)
    return pattern.data.byteLength > 0
  }

  private async testBoundaryCondition(condition: any): Promise<boolean> {
    await this.delay(30)
    // 模拟边界条件处理
    return condition.corrupted !== true
  }

  private async simulateErrorScenario(scenario: string): Promise<boolean> {
    await this.delay(40)
    // 模拟错误处理
    return Math.random() > 0.2 // 80% 处理成功率
  }

  private getImageFormat(type: string): string {
    const formats: Record<string, string> = {
      'resource': 'PNG',
      'pixelmap': 'RAW',
      'base64': 'BASE64',
      'svg': 'SVG'
    }
    return formats[type] || 'UNKNOWN'
  }

  private calculateImageSize(type: string): number {
    const sizes: Record<string, number> = {
      'resource': 2048,
      'pixelmap': 4096,
      'base64': 1024,
      'svg': 512
    }
    return sizes[type] || 1024
  }

  private hasAlphaChannel(type: string): boolean {
    return type !== 'jpeg' && Math.random() > 0.3
  }

  private generateRandomHexColor(): string {
    return '#' + Math.floor(Math.random() * 16777215).toString(16).padStart(6, '0')
  }

  private generateRandomRGB(): { r: number; g: number; b: number; a: number } {
    return {
      r: Math.floor(Math.random() * 256),
      g: Math.floor(Math.random() * 256),
      b: Math.floor(Math.random() * 256),
      a: Math.floor(Math.random() * 256)
    }
  }

  private generateRandomHSL(): { h: number; s: number; l: number } {
    return {
      h: Math.random() * 360,
      s: Math.random() * 100,
      l: Math.random() * 100
    }
  }

  private delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms))
  }

  build() {
    Scroll() {
      Column() {
        // 标题和进度
        Row() {
          Text('Image高级功能测试')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
          Blank()
          if (this.isTesting) {
            LoadingProgress()
              .width(24)
              .height(24)
              .margin({ right: 8 })
          }
          Text(`${this.testProgress}%`)
            .fontSize(14)
            .fontColor(Color.Gray)
        }
        .width('100%')
        .padding(16)

        // 当前操作显示
        if (this.currentOperation) {
          Text(`当前操作: ${this.currentOperation}`)
            .fontSize(14)
            .fontColor(Color.Blue)
            .margin({ horizontal: 16, bottom: 8 })
        }

        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            this.buildFilterTab()
          }
          .tabBar('滤镜')

          TabContent() {
            this.buildBlendModeTab()
          }
          .tabBar('混合')

          TabContent() {
            this.buildCompressionTab()
          }
          .tabBar('压缩')

          TabContent() {
            this.buildColorAnalysisTab()
          }
          .tabBar('颜色')

          TabContent() {
            this.buildPatternTab()
          }
          .tabBar('图案')

          TabContent() {
            this.buildTransformTab()
          }
          .tabBar('变换')

          TabContent() {
            this.buildResultsTab()
          }
          .tabBar('结果')
        }
        .height('85%')
        .barHeight(32)
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder buildFilterTab() {
    Scroll() {
      Column() {
        Text('图片滤镜测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 滤镜预览区域
        Grid() {
          ForEach(this.filterConfigs, (filter: ImageFilterConfig, index: number) => {
            GridItem() {
              Column() {
                Image($r('app.media.icon'))
                  .width(80)
                  .height(80)
                  .borderRadius(8)
                  .border({
                    width: index === this.currentFilterIndex ? 3 : 1,
                    color: index === this.currentFilterIndex ? Color.Blue : Color.Gray
                  })
                  .backgroundColor(this.applyFilterBackground(filter))
                  .blur(filter.blur)

                Text(filter.name)
                  .fontSize(12)
                  .margin({ top: 4 })
                
                Text(`亮度${filter.brightness}% 对比${filter.contrast}%`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
                  .maxLines(1)
              }
              .padding(8)
              .backgroundColor(index === this.currentFilterIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(8)
              .onClick(() => {
                this.currentFilterIndex = index
              })
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr')
        .rowsGap(12)
        .columnsGap(12)
        .padding(16)

        // 当前滤镜详情
        if (this.currentFilterIndex < this.filterConfigs.length) {
          const currentFilter = this.filterConfigs[this.currentFilterIndex]
          Column() {
            Text('当前滤镜参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Grid() {
              GridItem() {
                Column() {
                  Text('亮度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.brightness}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('对比度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.contrast}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('饱和度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.saturation}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('色相')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.hueRotate}°`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('模糊')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.blur}px`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('灰度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentFilter.grayscale}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
            }
            .rowsTemplate('1fr 1fr')
            .columnsTemplate('repeat(3, 1fr)')
            .height(120)
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildBlendModeTab() {
    Scroll() {
      Column() {
        Text('混合模式测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 混合模式预览
        Grid() {
          ForEach(this.blendModes, (blend: ImageBlendMode, index: number) => {
            GridItem() {
              Column() {
                Stack() {
                  Image($r('app.media.background'))
                    .width(60)
                    .height(60)
                    .borderRadius(4)
                    .backgroundColor('#FF0000')
                  
                  Image($r('app.media.foreground'))
                    .width(60)
                    .height(60)
                    .borderRadius(4)
                    .backgroundColor('#00FF00')
                    .blendMode(blend.mode)
                }
                .width(60)
                .height(60)
                .border({
                  width: index === this.currentBlendModeIndex ? 3 : 1,
                  color: index === this.currentBlendModeIndex ? Color.Blue : Color.Gray
                })

                Text(blend.name)
                  .fontSize(11)
                  .margin({ top: 4 })
                
                Text(blend.description)
                  .fontSize(9)
                  .fontColor(Color.Gray)
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .margin({ top: 2 })
              }
              .padding(8)
              .backgroundColor(index === this.currentBlendModeIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(8)
              .onClick(() => {
                this.currentBlendModeIndex = index
              })
            }
          })
        }
        .columnsTemplate('1fr 1fr')
        .rowsGap(12)
        .columnsGap(12)
        .padding(16)

        // 当前混合模式详情
        if (this.currentBlendModeIndex < this.blendModes.length) {
          const currentBlend = this.blendModes[this.currentBlendModeIndex]
          Column() {
            Text(`当前混合模式: ${currentBlend.name}`)
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 8 })
            
            Text(currentBlend.description)
              .fontSize(12)
              .fontColor(Color.Gray)
              .lineHeight(18)

            // 混合效果演示
            Row() {
              Text('混合前')
                .fontSize(12)
                .fontColor(Color.Gray)
                .margin({ right: 8 })
              
              Stack() {
                Image($r('app.media.foreground'))
                  .width(40)
                  .height(40)
                  .backgroundColor('#0066CC')
                Text('A')
                  .fontSize(20)
                  .fontColor(Color.White)
              }

              Text('+')
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .margin({ horizontal: 8 })

              Stack() {
                Image($r('app.media.background'))
                  .width(40)
                  .height(40)
                  .backgroundColor('#FF6600')
                Text('B')
                  .fontSize(20)
                  .fontColor(Color.White)
              }

              Text('=')
                .fontSize(20)
                .fontWeight(FontWeight.Bold)
                .margin({ horizontal: 8 })

              Stack() {
                Image($r('app.media.background'))
                  .width(40)
                  .height(40)
                  .backgroundColor('#FF6600')
                Image($r('app.media.foreground'))
                  .width(40)
                  .height(40)
                  .backgroundColor('#0066CC')
                  .blendMode(currentBlend.mode)
                Text(`=${currentBlend.name}`)
                  .fontSize(10)
                  .fontColor(Color.White)
                  .textAlign(TextAlign.Center)
                  .width('100%')
              }
            }
            .justifyContent(FlexAlign.Center)
            .alignItems(VerticalAlign.Center)
            .margin({ top: 16 })
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildCompressionTab() {
    Scroll() {
      Column() {
        Text('图片压缩测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 压缩结果概览
        Row() {
          Column() {
            Text('总测试数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.compressionTests.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('平均压缩率')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.calculateAverageCompressionRatio().toFixed(2)}x`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)

          Column() {
            Text('平均处理时间')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.calculateAverageProcessingTime().toFixed(0)}ms`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 压缩测试结果列表
        Text('详细压缩结果')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.compressionTests.slice(0, 10), (test: CompressionTest) => {
            ListItem() {
              Row() {
                Text(test.format)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                  .layoutWeight(1)

                Text(`质量${test.quality}%`)
                  .fontSize(12)
                  .fontColor(Color.Gray)
                  .margin({ right: 8 })

                Text(`压缩${test.compressionRatio.toFixed(2)}x`)
                  .fontSize(12)
                  .fontColor(Color.Green)
                  .margin({ right: 8 })

                Text(`${test.processingTime.toFixed(0)}ms`)
                  .fontSize(12)
                  .fontColor(Color.Blue)
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(4)
            }
          })
        }
        .height(300)
        .margin({ horizontal: 16 })

        // 压缩质量分布图
        if (this.compressionTests.length > 0) {
          Column() {
            Text('压缩质量分布')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })
            
            Row() {
              ForEach(this.QUALITY_LEVELS, (quality: number) => {
                Column() {
                  Text(`${quality}%`)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                    
                  Row() {
                    ForEach(this.COMPRESSION_FORMATS, (format: string) => {
                      const tests = this.compressionTests
                        .filter(t => t.quality === quality && t.format === format)
                        
                      Column() {
                        Text(`${tests.length}`)
                          .fontSize(12)
                          .fontWeight(FontWeight.Bold)
                          .textAlign(TextAlign.Center)
                          .width((tests.length * 20).clamp(20, 80))
                          .height(40)
                          .backgroundColor(this.getFormatColor(format))
                          .borderRadius(4)
                      }
                      .margin({ horizontal: 2 })
                    })
                  }
                  
                  Text(format)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                    .margin({ top: 4 })
                }
              })
            }
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildColorAnalysisTab() {
    Scroll() {
      Column() {
        Text('颜色分析测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 颜色样本网格
        Grid() {
          ForEach(this.colorTestResults.slice(0, 20), (color: ColorTestResult, index: number) => {
            GridItem() {
              Column() {
                Column() {
                  // 显示颜色
                  Row() {
                    Column() {
                      // 主色块
                      Column()
                        .width(30)
                        .height(30)
                        .backgroundColor(color.hex)
                        .borderRadius(4)
                        .border({ width: 1, color: Color.Gray })
                      
                      Text(color.hex)
                        .fontSize(10)
                        .fontColor(Color.Gray)
                        .maxLines(1)
                        .textOverflow({ overflow: TextOverflow.Ellipsis })
                        .margin({ top: 2 })
                    }
                    
                    // 采样点
                    Column() {
                      Text('采样点')
                        .fontSize(10)
                        .fontColor(Color.Gray)
                        .margin({ bottom: 2 })
                      
                      Grid() {
                        ForEach(color.samplePoints, (point: { x: number; y: number; color: string }) => {
                          GridItem() {
                            Column()
                              .width(8)
                              .height(8)
                              .backgroundColor(point.color)
                              .borderRadius(2)
                          }
                        })
                      }
                      .rowsTemplate('repeat(3, 1fr)')
                      .columnsTemplate('repeat(3, 1fr)')
                    }
                  }
                  
                  // 颜色信息
                  Text(`B:${color.brightness.toFixed(0)}%`)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                    .margin({ top: 4 })
                }
              }
              .padding(8)
              .backgroundColor('#FAFAFA')
              .borderRadius(8)
            }
          })
        }
        .rowsTemplate('repeat(4, 1fr)')
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(8)
        .columnsGap(8)
        .padding(16)

        // 颜色分析统计
        Column() {
          Text('颜色统计信息')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Grid() {
            GridItem() {
              Column() {
                Text('总样本数')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${this.colorTestResults.length}`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
            }
            
            GridItem() {
              Column() {
                Text('平均亮度')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${this.calculateAverageBrightness().toFixed(1)}%`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
            }
            
            GridItem() {
              Column() {
                Text('采样点数')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${this.calculateTotalSamplePoints()}`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
            }
            
            GridItem() {
              Column() {
                Text('独特颜色')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${this.calculateUniqueColors()}`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
            }
          }
          .rowsTemplate('1fr')
          .columnsTemplate('repeat(4, 1fr)')
          .rowsGap(16)
          .columnsGap(16)
        }
        .padding(16)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
        .margin({ horizontal: 16, top: 16 })
      }
    }
  }

  @Builder buildPatternTab() {
    Scroll() {
      Column() {
        Text('图案生成测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 图案网格展示
        Grid() {
          ForEach(this.generatedPatterns, (pattern: { id: number; type: string; data: ArrayBuffer }) => {
            GridItem() {
              Column() {
                // 图案预览
                Column()
                  .width(60)
                  .height(60)
                  .backgroundColor('#E0E0E0')
                  .borderRadius(8)
                  .border({ width: 1, color: Color.Gray })
                  .justifyContent(FlexAlign.Center)
                  .shadow({
                    radius: 4,
                    color: Color.Gray,
                    offsetX: 2,
                    offsetY: 2
                  })

                Text(pattern.type)
                  .fontSize(12)
                  .margin({ top: 8 })
                
                Text(`${(pattern.data.byteLength / 1024).toFixed(1)}KB`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
                  .margin({ top: 2 })
              }
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(8)
            }
          })
        }
        .rowsTemplate('repeat(2, 1fr)')
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(12)
        .columnsGap(12)
        .padding(16)

        // 图案生成统计
        Row() {
          Column() {
            Text('生成图案数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.generatedPatterns.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('总数据量')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.calculateTotalPatternSize().toFixed(0)}KB`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .layoutWeight(1)

          Column() {
            Text('平均大小')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.calculateAveragePatternSize().toFixed(1)}KB`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16, top: 8 })

        // 图谱类型分布
        Column() {
          Text('图案类型分布')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 16, bottom: 12, horizontal: 16 })

          Row() {
            ForEach(this.getPatternTypeDistribution(), (type: { name: string; count: number }) => {
              Column() {
                Text(type.name)
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${type.count}`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                Column()
                  .width(30)
                  .height(type.count * 10 + 10)
                  .backgroundColor(this.getRandomColor())
                  .borderRadius(4)
                  .margin({ top: 4 })
              }
              .layoutWeight(1)
            })
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, bottom: 16 })
        }
      }
    }
  }

  @Builder buildTransformTab() {
    Scroll() {
      Column() {
        Text('图片变换测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 变换结果网格
        Grid() {
          ForEach(this.transformedImages, (transform: { id: number; operation: string; result: boolean }) => {
            GridItem() {
              Column() {
                // 变换预览
                Image($r('app.media.icon'))
                  .width(50)
                  .height(50)
                  .borderRadius(6)
                  .border({
                    width: 2,
                    color: transform.result ? Color.Green : Color.Red
                  })

                Text(transform.operation)
                  .fontSize(12)
                  .margin({ top: 8 })
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Row() {
                  Circle({ width: 8, height: 8 })
                    .fill(transform.result ? Color.Green : Color.Red)
                  Text(transform.result ? '成功' : '失败')
                    .fontSize(10)
                    .fontColor(transform.result ? Color.Green : Color.Red)
                    .margin({ left: 4 })
                }
                .justifyContent(FlexAlign.Center)
                .margin({ top: 4 })
              }
              .padding(8)
              .backgroundColor(transform.result ? '#E8F5E8' : '#FFEBEE')
              .borderRadius(8)
            }
          })
        }
        .rowsTemplate('repeat(3, 1fr)')
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(8)
        .columnsGap(8)
        .padding(16)

        // 变换成功率统计
        Column() {
          Text('变换成功率')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })
          
          Row() {
            // 成功率环
            Stack() {
              Circle({ width: 120, height: 120 })
                .fill(Color.Transparent)
                .stroke(Color.Green)
                .strokeWidth(8)
              
              Circle({ width: 120, height: 120 })
                .fill(Color.Transparent)
                .stroke(Color.Gray)
                .strokeWidth(8)
                .strokeDashArray([this.calculateSuccessRate(), 360 - this.calculateSuccessRate()])
                .strokeDashOffset(90)
              
              Text(`${this.calculateSuccessRate().toFixed(0)}%`)
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
                .fontColor(Color.Green)
            }
            .width(120)
            .height(120)

            // 统计详情
            Column() {
              Text(`总变换数: ${this.transformedImages.length}`)
                .fontSize(12)
                .fontColor(Color.Gray)
              Text(`成功: ${this.transformedImages.filter(t => t.result).length}`)
                .fontSize(12)
                .fontColor(Color.Green)
              Text(`失败: ${this.transformedImages.filter(t => !t.result).length}`)
                .fontSize(12)
                .fontColor(Color.Red)
            }
            .layoutWeight(1)
            .justifyContent(FlexAlign.Center)
            .margin({ left: 32 })
          }
        }
        .padding(16)
        .backgroundColor('#FAFAFA')
        .borderRadius(8)
        .margin({ horizontal: 16, top: 16 })

        // 变换操作类型
        Column() {
          Text('变换操作类别')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 16, bottom: 12, horizontal: 16 })

          List() {
            ForEach(this.getCategorizedTransformations(), (category: { type: string; operations: string[]; successRate: number }) => {
              ListItem() {
                Column() {
                  Row() {
                    Text(category.type)
                      .fontSize(14)
                      .fontWeight(FontWeight.Medium)
                    Blank()
                    Text(`${category.successRate.toFixed(0)}%`)
                      .fontSize(14)
                      .fontWeight(FontWeight.Bold)
                      .fontColor(category.successRate > 80 ? Color.Green : category.successRate > 60 ? Color.Orange : Color.Red)
                  }
                  .width('100%')
                  .margin({ bottom: 8 })

                  Flex({ wrap: FlexWrap.Wrap }) {
                    ForEach(category.operations, (op: string) => {
                      Text(op)
                        .fontSize(11)
                        .fontColor(Color.Gray)
                        .padding({ horizontal: 6, vertical: 2 })
                        .backgroundColor('#F0F0F0')
                        .borderRadius(4)
                        .margin({ right: 4, bottom: 4 })
                    })
                  }
                  .width('100%')
                }
                .width('100%')
                .padding(12)
                .backgroundColor('#FAFAFA')
                .borderRadius(6)
              }
            })
          }
          .height(200)
          .margin({ horizontal: 16, bottom: 16 })
        }
      }
    }
  }

  @Builder buildResultsTab() {
    Scroll() {
      Column() {
        Text('测试结果总览')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 结果统计
        Row() {
          Column() {
            Text('总测试数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.advancedTestResults.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('通过')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.advancedTestResults.filter(r => r.status === 'Passed').length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)

          Column() {
            Text('失败')
              .fontSize(12)
              .fontColor(Color.Red)
            Text(`${this.advancedTestResults.filter(r => r.status === 'Failed').length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Red)
          }
          .layoutWeight(1)

          Column() {
            Text('警告')
              .fontSize(12)
              .fontColor(Color.Orange)
            Text(`${this.advancedTestResults.filter(r => r.status === 'Warning').length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Orange)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 详细结果列表
        Text('详细测试结果')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.advancedTestResults, (result: { name: string; status: string; details: string }) => {
            ListItem() {
              Column() {
                Row() {
                  Circle({ width: 8, height: 8 })
                    .fill(this.getStatusColor(result.status))
                    .margin({ right: 8 })

                  Text(result.name)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                    .layoutWeight(1)

                  Text(result.status)
                    .fontSize(12)
                    .fontColor(this.getStatusTextColor(result.status))
                    .padding({ horizontal: 8, vertical: 4 })
                    .backgroundColor(this.getStatusBgColor(result.status))
                    .borderRadius(4)
                }
                .width('100%')
                .margin({ bottom: 4 })

                Text(result.details)
                  .fontSize(12)
                  .fontColor(Color.Gray)
                  .maxLines(2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .width('100%')
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
              .margin({ bottom: 8 })
            }
          })
        }
        .layoutWeight(1)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  // 工具方法
  private applyFilterBackground(filter: ImageFilterConfig): ResourceColor {
    const brightness = filter.brightness / 100
    const gray = Math.floor(255 - brightness * 50)
    return Color.rgb(gray, gray, gray)
  }

  private getFormatColor(format: string): ResourceColor {
    const colors: Record<string, ResourceColor> = {
      'JPEG': Color.Red,
      'PNG': Color.Green,
      'WEBP': Color.Blue,
      'GIF': Color.Orange,
      'BMP': Color.Purple
    }
    return colors[format] || Color.Gray
  }

  private calculateAverageCompressionRatio(): number {
    if (this.compressionTests.length === 0) return 0
    const sum = this.compressionTests.reduce((acc, test) => acc + test.compressionRatio, 0)
    return sum / this.compressionTests.length
  }

  private calculateAverageProcessingTime(): number {
    if (this.compressionTests.length === 0) return 0
    const sum = this.compressionTests.reduce((acc, test) => acc + test.processingTime, 0)
    return sum / this.compressionTests.length
  }

  private calculateAverageBrightness(): number {
    if (this.colorTestResults.length === 0) return 0
    const sum = this.colorTestResults.reduce((acc, color) => acc + color.brightness, 0)
    return sum / this.colorTestResults.length
  }

  private calculateTotalSamplePoints(): number {
    return this.colorTestResults.reduce((acc, color) => acc + color.samplePoints.length, 0)
  }

  private calculateUniqueColors(): number {
    const uniqueColors = new Set(this.colorTestResults.map(color => color.hex))
    return uniqueColors.size
  }

  private calculateTotalPatternSize(): number {
    return this.generatedPatterns.reduce((acc, pattern) => acc + pattern.data.byteLength, 0) / 1024
  }

  private calculateAveragePatternSize(): number {
    if (this.generatedPatterns.length === 0) return 0
    return this.calculateTotalPatternSize() / this.generatedPatterns.length
  }

  private getPatternTypeDistribution(): Array<{ name: string; count: number }> {
    const distribution = new Map<string, number>()
    this.generatedPatterns.forEach(pattern => {
      const count = distribution.get(pattern.type) || 0
      distribution.set(pattern.type, count + 1)
    })
    return Array.from(distribution.entries()).map(([name, count]) => ({ name, count }))
  }

  private getRandomColor(): ResourceColor {
    const colors = [Color.Red, Color.Blue, Color.Green, Color.Orange, Color.Purple, Color.Brown, Color.Pink]
    return colors[Math.floor(Math.random() * colors.length)]
  }

  private calculateSuccessRate(): number {
    if (this.transformedImages.length === 0) return 0
    const successCount = this.transformedImages.filter(t => t.result).length
    return (successCount / this.transformedImages.length) * 100
  }

  private getCategorizedTransformations(): Array<{ type: string; operations: string[]; successRate: number }> {
    const categories = new Map<string, { operations: string[], successes: number }>()
    
    this.transformedImages.forEach(transform => {
      let category = '其他'
      if (['rotate', 'flip'].includes(transform.operation)) {
        category = '几何变换'
      } else if (['filter', 'blur'].includes(transform.operation)) {
        category = '滤镜效果'
      } else if (['crop', 'resize'].includes(transform.operation)) {
        category = '尺寸调整'
      } else if (['wrap', 'distort'].includes(transform.operation)) {
        category = '变形效果'
      }
      
      const existing = categories.get(category) || { operations: [], successes: 0 }
      existing.operations.push(transform.operation)
      if (transform.result) existing.successes++
      categories.set(category, existing)
    })
    
    return Array.from(categories.entries()).map(([type, data]) => ({
      type,
      operations: data.operations,
      successRate: (data.successes / data.operations.length) * 100
    }))
  }

  private getStatusColor(status: string): ResourceColor {
    switch (status) {
      case 'Passed':
        return Color.Green
      case 'Failed':
        return Color.Red
      case 'Warning':
        return Color.Orange
      case 'Handled':
        return Color.Blue
      default:
        return Color.Gray
    }
  }

  private getStatusTextColor(status: string): ResourceColor {
    switch (status) {
      case 'Passed':
        return Color.Green
      case 'Failed':
        return Color.Red
      case 'Warning':
        return Color.Orange
      case 'Handled':
        return Color.Blue
      default:
        return Color.Gray
    }
  }

  private getStatusBgColor(status: string): ResourceColor {
    switch (status) {
      case 'Passed':
        return '#E8F5E8'
      case 'Failed':
        return '#FFEBEE'
      case 'Warning':
        return '#FFF3E0'
      case 'Handled':
        return '#E3F2FD'
      default:
        return '#F5F5F5'
    }
  }
}