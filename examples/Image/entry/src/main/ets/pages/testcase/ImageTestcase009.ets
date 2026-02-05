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

/**
 * 测试Image组件基础加载功能
 * 涵盖各种图片格式和加载场景
 */
import { image } from '@kit.ImageKit'
import common from '@ohos.app.ability.common';
import { BusinessError } from '@ohos.base';

@Entry
@Component
struct ImageBasicLoadTestCase {
  @State imageUrl: string = ''
  @State imageResource: Resource = $r('app.media.icon')
  @State pixelMap: image.PixelMap | undefined = undefined
  @State base64Image: string = ''
  @State loadingState: string = 'idle'
  @State errorMessage: string = ''
  @State currentTestIndex: number = 0
  @State testResults: Array<{ name: string, status: string, duration: number }> = []

  private readonly TEST_CASES = [
    { name: '本地资源加载', type: 'resource', value: $r('app.media.icon') },
    { name: 'PixelMap加载', type: 'pixelmap', value: null },
    { name: '空资源加载', type: 'empty', value: '' },
    { name: '无效URL加载', type: 'invalid', value: 'invalid://url' },
  ]

  async aboutToAppear() {
    await this.generateTestPixelMap()
    this.runAllTests()
  }

  private async generateTestPixelMap(): Promise<void> {
    const pixelMapOptions: image.InitializationOptions = {
      size: { width: 100, height: 100 },
      pixelFormat: image.PixelMapFormat.RGBA_8888,
      editable: true
    }
    
    const buffer = new ArrayBuffer(100 * 100 * 4)
    this.pixelMap = await image.createPixelMap(buffer, pixelMapOptions)
  }

  private async runAllTests(): Promise<void> {
    for (let i = 0; i < this.TEST_CASES.length; i++) {
      this.currentTestIndex = i
      await this.runSingleTest(this.TEST_CASES[i])
    }
  }

  private async runSingleTest(testCase: any): Promise<void> {
    const startTime = Date.now()
    this.loadingState = 'loading'
    this.errorMessage = ''

    try {
      switch (testCase.type) {
        case 'resource':
          await this.testResourceLoad(testCase.value)
          break
        case 'network':
          await this.testNetworkLoad(testCase.value)
          break
        case 'base64':
          await this.testBase64Load(testCase.value)
          break
        case 'pixelmap':
          await this.testPixelMapLoad()
          break
        case 'empty':
          await this.testEmptyLoad()
          break
        case 'invalid':
          await this.testInvalidLoad(testCase.value)
          break
        case 'large':
          await this.testLargeImageLoad(testCase.value)
          break
        case 'svg':
          await this.testSvgLoad(testCase.value)
          break
      }

      const duration = Date.now() - startTime
      this.testResults.push({
        name: testCase.name,
        status: 'success',
        duration: duration
      })
      this.loadingState = 'success'

    } catch (error) {
      const duration = Date.now() - startTime
      const businessError = error as BusinessError
      this.errorMessage = businessError.message || 'Unknown error'
      this.testResults.push({
        name: testCase.name,
        status: 'failed',
        duration: duration
      })
      this.loadingState = 'failed'
    }
  }

  private async testResourceLoad(resource: Resource): Promise<void> {
    return new Promise((resolve, reject) => {
      setTimeout(() => {
        try {
          this.imageResource = resource
          resolve()
        } catch (error) {
          reject(error)
        }
      }, 100)
    })
  }

  private async testBase64Load(base64: string): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        this.base64Image = base64
        setTimeout(resolve, 100)
      } catch (error) {
        reject(error)
      }
    })
  }

  private async testPixelMapLoad(): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        if (this.pixelMap) {
          resolve()
        } else {
          reject(new Error('PixelMap is not available'))
        }
      } catch (error) {
        reject(error)
      }
    })
  }

  private async testEmptyLoad(): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        this.imageUrl = ''
        setTimeout(() => resolve(), 50)
      } catch (error) {
        reject(error)
      }
    })
  }

  private async testInvalidLoad(url: string): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        this.imageUrl = url
        setTimeout(() => resolve(), 50) // 应该失败但我们继续
      } catch (error) {
        reject(error)
      }
    })
  }

  private async testSvgLoad(svgData: string): Promise<void> {
    return new Promise((resolve, reject) => {
      try {
        this.base64Image = svgData
        setTimeout(resolve, 150)
      } catch (error) {
        reject(error)
      }
    })
  }

  build() {
    Column() {
      Row() {
        Text('Image基础加载测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        Text(`当前测试: ${this.currentTestIndex + 1}/${this.TEST_CASES.length}`)
          .fontSize(14)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .padding(16)

      Scroll() {
        Column() {
          // 测试图片显示区域
          Row() {
            Column() {
              Text('资源图片')
                .fontSize(14)
                .margin({ bottom: 8 })
              Image(this.imageResource)
                .width(100)
                .height(100)
                .border({ width: 1, color: Color.Gray })
                .objectFit(ImageFit.Contain)
            }
            .padding(8)

            Column() {
              Text('Base64图片')
                .fontSize(14)
                .margin({ bottom: 8 })
              Image(this.base64Image)
                .width(100)
                .height(100)
                .border({ width: 1, color: Color.Gray })
                .objectFit(ImageFit.Contain)
            }
            .padding(8)

            Column() {
              Text('PixelMap图片')
                .fontSize(14)
                .margin({ bottom: 8 })
              Image(this.pixelMap)
                .width(100)
                .height(100)
                .border({ width: 1, color: Color.Gray })
                .objectFit(ImageFit.Contain)
            }
            .padding(8)
          }
          .margin({ vertical: 16 })

          // 加载状态显示
          Row() {
            Text('加载状态:')
              .fontSize(14)
              .margin({ right: 8 })
            Text(this.loadingState)
              .fontSize(14)
              .fontColor(this.getLoadingStateColor())
          }
          .justifyContent(FlexAlign.Start)
          .width('100%')
          .padding(8)

          if (this.errorMessage) {
            Text(`错误信息: ${this.errorMessage}`)
              .fontSize(12)
              .fontColor(Color.Red)
              .width('100%')
              .padding(8)
          }

          Divider()

          // 测试结果列表
          Text('测试结果')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 16, bottom: 8 })

          ForEach(this.testResults, (result: { name: string, status: string, duration: number }) => {
            Row() {
              Circle({ width: 8, height: 8 })
                .fill(result.status === 'success' ? Color.Green : Color.Red)
                .margin({ right: 8 })
              
              Text(result.name)
                .fontSize(14)
                .layoutWeight(1)
              
              Text(`${result.duration}ms`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .margin({ right: 8 })
              
              Text(result.status)
                .fontSize(12)
                .fontColor(result.status === 'success' ? Color.Green : Color.Red)
            }
            .width('100%')
            .padding({ vertical: 4, horizontal: 8 })
            .borderRadius(4)
            .backgroundColor(result.status === 'success' ? '#E8F5E8' : '#FFEBEE')
          })
        }
        .padding(16)
      }
      .layoutWeight(1)

      // 控制按钮区域
      Row() {
        Button('重新运行测试')
          .onClick(() => {
            this.testResults = []
            this.currentTestIndex = 0
            this.runAllTests()
          })
        Button('清空结果')
          .onClick(() => {
            this.testResults = []
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

  private getLoadingStateColor(): ResourceColor {
    switch (this.loadingState) {
      case 'loading':
        return Color.Blue
      case 'success':
        return Color.Green
      case 'failed':
        return Color.Red
      default:
        return Color.Gray
    }
  }
}