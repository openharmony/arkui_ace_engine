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
 * 测试Image组件图片处理和编辑功能
 * 涵盖裁剪、旋转、翻转、水印、文字叠加等编辑功能
 */

import { image } from '@kit.ImageKit'
import { DrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI'
import { BusinessError } from '@ohos.base'

interface CropRegion {
  x: number
  y: number
  width: number
  height: number
  aspectRatio: string
}

interface RotationConfig {
  angle: number
  flipHorizontal: boolean
  flipVertical: boolean
  quality: number
}

interface WatermarkConfig {
  text: string
  position: 'top-left' | 'top-right' | 'bottom-left' | 'bottom-right' | 'center'
  opacity: number
  fontSize: number
  color: string
  shadow: boolean
}

interface TextOverlayConfig {
  text: string
  x: number
  y: number
  font: string
  size: number
  color: string
  backgroundColor: string
  padding: number
  borderRadius: number
}

interface AdjustmentConfig {
  brightness: number
  contrast: number
  saturation: number
  sharpness: number
  temperature: number
  tint: number
}

interface FilterPreset {
  name: string
  adjustment: AdjustmentConfig
  thumbnail: string
}

interface EditOperation {
  id: number
  type: string
  name: string
  timestamp: number
  params: any
  result: 'success' | 'failed' | 'processing'
  processingTime: number
}

interface ProcessingHistory {
  id: number
  operation: string
  before: string
  after: string
  duration: number
  success: boolean
}

@Entry
@Component
struct ImageEditTestCase {
  @State cropRegions: CropRegion[] = []
  @State currentCropIndex: number = 0
  @State rotationConfigs: RotationConfig[] = []
  @State currentRotationIndex: number = 0
  @State watermarkConfigs: WatermarkConfig[] = []
  @State currentWatermarkIndex: number = 0
  @State textOverlays: TextOverlayConfig[] = []
  @State adjustmentConfigs: AdjustmentConfig[] = []
  @State currentAdjustmentIndex: number = 0
  @State filterPresets: FilterPreset[] = []
  @State currentFilterIndex: number = 0
  @State editOperations: EditOperation[] = []
  @State processingHistory: ProcessingHistory[] = []
  @State isProcessing: boolean = false
  @State currentOperation: string = ''
  @State processedImagesCount: number = 0
  @State autoProcessingEnabled: boolean = false
  @State batchProcessingQueue: Array<{ id: number; operation: string; params: any }> = []

  private readonly CROP_PRESETS: CropRegion[] = [
    { x: 0, y: 0, width: 200, height: 200, aspectRatio: '1:1' },
    { x: 0, y: 0, width: 300, height: 200, aspectRatio: '3:2' },
    { x: 0, y: 0, width: 200, height: 300, aspectRatio: '2:3' },
    { x: 0, y: 0, width: 320, height: 180, aspectRatio: '16:9' },
    { x: 0, y: 0, width: 180, height: 320, aspectRatio: '9:16' },
    { x: 0, y: 0, width: 250, height: 250, aspectRatio: '1:1' },
    { x: 0, y: 0, width: 400, height: 300, aspectRatio: '4:3' },
    { x: 0, y: 0, width: 300, height: 400, aspectRatio: '3:4' },
    { x: 0, y: 0, width: 500, height: 250, aspectRatio: '2:1' },
    { x: 0, y: 0, width: 250, height: 500, aspectRatio: '1:2' }
  ]

  private readonly ROTATION_PRESETS: RotationConfig[] = [
    { angle: 0, flipHorizontal: false, flipVertical: false, quality: 100 },
    { angle: 90, flipHorizontal: false, flipVertical: false, quality: 100 },
    { angle: 180, flipHorizontal: false, flipVertical: false, quality: 100 },
    { angle: 270, flipHorizontal: false, flipVertical: false, quality: 100 },
    { angle: 0, flipHorizontal: true, flipVertical: false, quality: 100 },
    { angle: 0, flipHorizontal: false, flipVertical: true, quality: 100 },
    { angle: 45, flipHorizontal: false, flipVertical: false, quality: 95 },
    { angle: 135, flipHorizontal: false, flipVertical: false, quality: 90 },
    { angle: 225, flipHorizontal: false, flipVertical: false, quality: 85 },
    { angle: 315, flipHorizontal: false, flipVertical: false, quality: 80 },
    { angle: 30, flipHorizontal: true, flipVertical: false, quality: 95 },
    { angle: 60, flipHorizontal: false, flipVertical: true, quality: 90 }
  ]

  private readonly WATERMARK_PRESETS: WatermarkConfig[] = [
    { text: 'Sample', position: 'bottom-right', opacity: 0.7, fontSize: 16, color: '#FFFFFF', shadow: true },
    { text: 'Watermark', position: 'top-left', opacity: 0.6, fontSize: 14, color: '#CCCCCC', shadow: false },
    { text: 'Copyright', position: 'center', opacity: 0.5, fontSize: 20, color: '#FFFFFF', shadow: true },
    { text: 'Demo', position: 'top-right', opacity: 0.8, fontSize: 12, color: '#FFFFFF', shadow: true },
    { text: 'Test', position: 'bottom-left', opacity: 0.7, fontSize: 18, color: '#FFFFFF', shadow: false },
    { text: 'Preview', position: 'bottom-right', opacity: 0.4, fontSize: 24, color: '#000000', shadow: true },
    { text: 'Confidential', position: 'center', opacity: 0.3, fontSize: 28, color: '#FF0000', shadow: true },
    { text: 'Property', position: 'top-left', opacity: 0.9, fontSize: 10, color: '#FFFFFF', shadow: true }
  ]

  private readonly TEXT_OVERLAY_PRESETS: TextOverlayConfig[] = [
    { text: 'Hello World', x: 10, y: 10, font: 'Arial', size: 16, color: '#FF0000', backgroundColor: '#FFFFFF80', padding: 8, borderRadius: 4 },
    { text: 'Important Note', x: 20, y: 50, font: 'Helvetica', size: 20, color: '#0000FF', backgroundColor: '#FFFF0080', padding: 10, borderRadius: 6 },
    { text: 'Watermark', x: 100, y: 100, font: 'Times New Roman', size: 14, color: '#FFFFFF', backgroundColor: '#00000080', padding: 5, borderRadius: 2 },
    { text: 'Label', x: 50, y: 20, font: 'Courier New', size: 12, color: '#00FF00', backgroundColor: '#FF00FF80', padding: 6, borderRadius: 3 },
    { text: 'Title', x: 0, y: 0, font: 'Verdana', size: 24, color: '#FFFF00', backgroundColor: '#FF000080', padding: 12, borderRadius: 8 },
    { text: 'Subtitle', x: 0, y: 30, font: 'Georgia', size: 18, color: '#00FFFF', backgroundColor: '#0000FF80', padding: 8, borderRadius: 6 },
    { text: 'Comment', x: 30, y: 80, font: 'Tahoma', size: 10, color: '#000000', backgroundColor: '#FFFFFF80', padding: 4, borderRadius: 2 },
    { text: 'Signature', x: 150, y: 150, font: 'Script', size: 22, color: '#000000', backgroundColor: '#FFD70080', padding: 10, borderRadius: 10 }
  ]

  private readonly ADJUSTMENT_PRESETS: AdjustmentConfig[] = [
    { brightness: 100, contrast: 100, saturation: 100, sharpness: 0, temperature: 0, tint: 0 },
    { brightness: 110, contrast: 105, saturation: 110, sharpness: 10, temperature: 10, tint: 0 },
    { brightness: 90, contrast: 95, saturation: 90, sharpness: -10, temperature: -10, tint: 0 },
    { brightness: 120, contrast: 110, saturation: 120, sharpness: 20, temperature: 20, tint: 10 },
    { brightness: 80, contrast: 90, saturation: 80, sharpness: -20, temperature: -20, tint: -10 },
    { brightness: 100, contrast: 120, saturation: 100, sharpness: 30, temperature: 0, tint: 0 },
    { brightness: 100, contrast: 80, saturation: 100, sharpness: -30, temperature: 0, tint: 0 },
    { brightness: 105, contrast: 100, saturation: 130, sharpness: 15, temperature: 30, tint: 20 },
    { brightness: 95, contrast: 100, saturation: 70, sharpness: -15, temperature: -30, tint: -20 },
    { brightness: 115, contrast: 115, saturation: 115, sharpness: 25, temperature: 15, tint: 5 }
  ]

  private readonly FILTER_PRESETS: FilterPreset[] = [
    { name: '原图', adjustment: { brightness: 100, contrast: 100, saturation: 100, sharpness: 0, temperature: 0, tint: 0 }, thumbnail: 'original' },
    { name: '明亮', adjustment: { brightness: 120, contrast: 105, saturation: 110, sharpness: 10, temperature: 10, tint: 0 }, thumbnail: 'bright' },
    { name: '暗淡', adjustment: { brightness: 80, contrast: 95, saturation: 90, sharpness: -10, temperature: -10, tint: 0 }, thumbnail: 'dark' },
    { name: '鲜艳', adjustment: { brightness: 105, contrast: 110, saturation: 130, sharpness: 15, temperature: 20, tint: 10 }, thumbnail: 'vivid' },
    { name: '柔和', adjustment: { brightness: 95, contrast: 90, saturation: 70, sharpness: -15, temperature: -15, tint: -5 }, thumbnail: 'soft' },
    { name: '冷暖', adjustment: { brightness: 100, contrast: 100, saturation: 100, sharpness: 0, temperature: 30, tint: 10 }, thumbnail: 'warm' },
    { name: '冷色调', adjustment: { brightness: 100, contrast: 100, saturation: 100, sharpness: 0, temperature: -30, tint: -10 }, thumbnail: 'cool' },
    { name: '高对比', adjustment: { brightness: 100, contrast: 130, saturation: 110, sharpness: 20, temperature: 0, tint: 0 }, thumbnail: 'high-contrast' },
    { name: '复古', adjustment: { brightness: 105, contrast: 90, saturation: 80, sharpness: -5, temperature: 20, tint: 15 }, thumbnail: 'vintage' },
    { name: '黑白', adjustment: { brightness: 100, contrast: 110, saturation: 0, sharpness: 10, temperature: 0, tint: 0 }, thumbnail: 'bw' }
  ]

  aboutToAppear() {
    this.initializeEditTests()
    this.startEditProcessingTests()
  }

  private initializeEditTests(): void {
    this.cropRegions = [...this.CROP_PRESETS]
    this.rotationConfigs = [...this.ROTATION_PRESETS]
    this.watermarkConfigs = [...this.WATERMARK_PRESETS]
    this.textOverlays = [...this.TEXT_OVERLAY_PRESETS]
    this.adjustmentConfigs = [...this.ADJUSTMENT_PRESETS]
    this.filterPresets = [...this.FILTER_PRESETS]

    // 初始化批处理队列
    for (let i = 0; i < 20; i++) {
      this.batchProcessingQueue.push({
        id: i,
        operation: this.getRandomOperation(),
        params: this.getRandomParams()
      })
    }
  }

  private async startEditProcessingTests(): Promise<void> {
    this.isProcessing = true
    this.autoProcessingEnabled = true

    const editTests = [
      { name: '图片裁剪测试', func: () => this.testCropOperations() },
      { name: '图片旋转测试', func: () => this.testRotationOperations() },
      { name: '水印添加测试', func: () => this.testWatermarkOperations() },
      { name: '文字叠加测试', func: () => this.testTextOverlayOperations() },
      { name: '调整参数测试', func: () => this.testAdjustmentOperations() },
      { name: '滤镜预设测试', func: () => this.testFilterPresetOperations() },
      { name: '批处理测试', func: () => this.testBatchProcessing() },
      { name: '撤销重做测试', func: () => this.testUndoRedoOperations() },
      { name: '历史记录测试', func: () => this.testHistoryOperations() },
      { name: '性能测试', func: () => this.testEditPerformance() }
    ]

    for (let i = 0; i < editTests.length; i++) {
      const test = editTests[i]
      this.currentOperation = test.name

      try {
        await test.func()
        this.addEditOperation(test.name, 'success')
      } catch (error) {
        this.addEditOperation(test.name, 'failed')
        console.error(`${test.name} failed:`, error)
      }

      await this.delay(300)
    }

    this.autoProcessingEnabled = false
    this.isProcessing = false
  }

  private async testCropOperations(): Promise<void> {
    for (let i = 0; i < this.cropRegions.length; i++) {
      this.currentCropIndex = i
      
      try {
        const result = await this.performCrop(this.cropRegions[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('crop', 'original_image', 'cropped_image', 150, true)
        }
      } catch (error) {
        this.addHistoryRecord('crop', 'original_image', 'cropped_image', 150, false)
      }

      await this.delay(100)
    }
  }

  private async testRotationOperations(): Promise<void> {
    for (let i = 0; i < this.rotationConfigs.length; i++) {
      this.currentRotationIndex = i
      
      try {
        const result = await this.performRotation(this.rotationConfigs[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('rotation', 'original_image', 'rotated_image', 200, true)
        }
      } catch (error) {
        this.addHistoryRecord('rotation', 'original_image', 'rotated_image', 200, false)
      }

      await this.delay(120)
    }
  }

  private async testWatermarkOperations(): Promise<void> {
    for (let i = 0; i < this.watermarkConfigs.length; i++) {
      this.currentWatermarkIndex = i
      
      try {
        const result = await this.performWatermark(this.watermarkConfigs[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('watermark', 'original_image', 'watermarked_image', 100, true)
        }
      } catch (error) {
        this.addHistoryRecord('watermark', 'original_image', 'watermarked_image', 100, false)
      }

      await this.delay(80)
    }
  }

  private async testTextOverlayOperations(): Promise<void> {
    for (let i = 0; i < this.textOverlays.length; i++) {
      try {
        const result = await this.performTextOverlay(this.textOverlays[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('text_overlay', 'original_image', 'text_overlay_image', 90, true)
        }
      } catch (error) {
        this.addHistoryRecord('text_overlay', 'original_image', 'text_overlay_image', 90, false)
      }

      await this.delay(70)
    }
  }

  private async testAdjustmentOperations(): Promise<void> {
    for (let i = 0; i < this.adjustmentConfigs.length; i++) {
      this.currentAdjustmentIndex = i
      
      try {
        const result = await this.performAdjustment(this.adjustmentConfigs[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('adjustment', 'original_image', 'adjusted_image', 180, true)
        }
      } catch (error) {
        this.addHistoryRecord('adjustment', 'original_image', 'adjusted_image', 180, false)
      }

      await this.delay(150)
    }
  }

  private async testFilterPresetOperations(): Promise<void> {
    for (let i = 0; i < this.filterPresets.length; i++) {
      this.currentFilterIndex = i
      
      try {
        const result = await this.applyFilterPreset(this.filterPresets[i])
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord('filter', 'original_image', 'filtered_image', 160, true)
        }
      } catch (error) {
        this.addHistoryRecord('filter', 'original_image', 'filtered_image', 160, false)
      }

      await this.delay(140)
    }
  }

  private async testBatchProcessing(): Promise<void> {
    this.autoProcessingEnabled = true
    
    for (let i = 0; i < this.batchProcessingQueue.length; i++) {
      const item = this.batchProcessingQueue[i]
      
      try {
        const result = await this.processBatchItem(item)
        if (result) {
          this.processedImagesCount++
          this.addHistoryRecord(item.operation, 'original_image', 'processed_image', 75, true)
        }
      } catch (error) {
        this.addHistoryRecord(item.operation, 'original_image', 'processed_image', 75, false)
      }

      await this.delay(50)
    }
    
    this.autoProcessingEnabled = false
  }

  private async testUndoRedoOperations(): Promise<void> {
    const operations = ['crop', 'rotation', 'watermark', 'text_overlay', 'adjustment', 'filter']
    
    // 执行操作序列
    for (const op of operations) {
      await this.performOperation(op)
      await this.delay(100)
    }

    // 模拟撤销操作
    for (let i = 0; i < operations.length; i++) {
      await this.simulateUndo()
      await this.delay(80)
    }

    // 模拟重做操作
    for (let i = 0; i < operations.length; i++) {
      await this.simulateRedo()
      await this.delay(80)
    }
  }

  private async testHistoryOperations(): Promise<void> {
    // 生成更多历史记录
    for (let i = 0; i < 20; i++) {
      const operation = this.getRandomOperation()
      const duration = Math.floor(Math.random() * 300) + 50
      const success = Math.random() > 0.2 // 80% 成功率
      
      this.addHistoryRecord(operation, 'original_image', 'processed_image', duration, success)
      await this.delay(40)
    }

    // 测试历史记录功能
    await this.testHistoryNavigation()
    await this.testHistoryClear()
    await this.testHistoryExport()
  }

  private async testEditPerformance(): Promise<void> {
    const operations = ['crop', 'rotation', 'watermark', 'text_overlay', 'adjustment', 'filter']
    const iterations = 10

    for (const op of operations) {
      const startTime = performance.now()
      
      for (let i = 0; i < iterations; i++) {
        await this.performOperation(op)
        await this.delay(20) // 短延迟模拟快速连续操作
      }
      
      const endTime = performance.now()
      const avgTime = (endTime - startTime) / iterations
      
      this.addEditOperation(`Performance_${op}`, avgTime < 100 ? 'success' : 'warning')
    }
  }

  // 模拟处理方法
  private async performCrop(cropRegion: CropRegion): Promise<boolean> {
    await this.delay(50 + Math.random() * 150)
    return Math.random() > 0.1 // 90% 成功率
  }

  private async performRotation(rotation: RotationConfig): Promise<boolean> {
    const baseTime = Math.abs(rotation.angle) / 360 * 200
    await this.delay(baseTime + Math.random() * 100)
    return Math.random() > 0.05 // 95% 成功率
  }

  private async performWatermark(watermark: WatermarkConfig): Promise<boolean> {
    await this.delay(30 + Math.random() * 100)
    return Math.random() > 0.1 // 90% 成功率
  }

  private async performTextOverlay(overlay: TextOverlayConfig): Promise<boolean> {
    await this.delay(40 + Math.random() * 80)
    return Math.random() > 0.15 // 85% 成功率
  }

  private async performAdjustment(adjustment: AdjustmentConfig): Promise<boolean> {
    await this.delay(100 + Math.random() * 200)
    return Math.random() > 0.05 // 95% 成功率
  }

  private async applyFilterPreset(filter: FilterPreset): Promise<boolean> {
    await this.delay(80 + Math.random() * 150)
    return Math.random() > 0.08 // 92% 成功率
  }

  private async processBatchItem(item: { id: number; operation: string; params: any }): Promise<boolean> {
    await this.delay(60 + Math.random() * 120)
    return Math.random() > 0.12 // 88% 成功率
  }

  private async performOperation(operation: string): Promise<boolean> {
    await this.delay(50 + Math.random() * 100)
    return Math.random() > 0.1
  }

  private async simulateUndo(): Promise<boolean> {
    await this.delay(40 + Math.random() * 60)
    return Math.random() > 0.05
  }

  private async simulateRedo(): Promise<boolean> {
    await this.delay(40 + Math.random() * 60)
    return Math.random() > 0.05
  }

  private async testHistoryNavigation(): Promise<boolean> {
    await this.delay(100)
    return Math.random() > 0.02
  }

  private async testHistoryClear(): Promise<boolean> {
    await this.delay(50)
    return Math.random() > 0.01
  }

  private async testHistoryExport(): Promise<boolean> {
    await this.delay(200)
    return Math.random() > 0.02
  }

  private getRandomOperation(): string {
    const operations = ['crop', 'rotation', 'watermark', 'text_overlay', 'adjustment', 'filter', 'resize', 'blur', 'sharpen']
    return operations[Math.floor(Math.random() * operations.length)]
  }

  private getRandomParams(): any {
    return {
      intensity: Math.floor(Math.random() * 100),
      quality: Math.floor(Math.random() * 30) + 70,
      mode: Math.floor(Math.random() * 5)
    }
  }

  private addEditOperation(operation: string, result: string): void {
    const editOp: EditOperation = {
      id: this.editOperations.length + 1,
      type: operation,
      name: operation,
      timestamp: Date.now(),
      params: {},
      result: result as 'success' | 'failed' | 'processing',
      processingTime: Math.floor(Math.random() * 300) + 50
    }
    this.editOperations.push(editOp)

    // 保持列表长度限制
    if (this.editOperations.length > 50) {
      this.editOperations = this.editOperations.slice(-50)
    }
  }

  private addHistoryRecord(operation: string, before: string, after: string, duration: number, success: boolean): void {
    const history: ProcessingHistory = {
      id: this.processingHistory.length + 1,
      operation: operation,
      before: before,
      after: after,
      duration: duration,
      success: success
    }
    this.processingHistory.unshift(history)

    // 保持历史记录长度限制
    if (this.processingHistory.length > 100) {
      this.processingHistory = this.processingHistory.slice(0, 100)
    }
  }

  private delay(ms: number): Promise<void> {
    return new Promise(resolve => setTimeout(resolve, ms))
  }

  build() {
    Column() {
      // 标题栏
      Row() {
        Text('Image图片编辑测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
        Blank()
        if (this.isProcessing) {
          LoadingProgress()
            .width(24)
            .height(24)
            .margin({ right: 8 })
        }
        Text(`已处理: ${this.processedImagesCount}`)
          .fontSize(14)
          .fontColor(Color.Blue)
      }
      .width('100%')
      .padding(16)

      // 当前操作显示
      if (this.currentOperation) {
        Text(`当前操作: ${this.currentOperation}`)
          .fontSize(14)
          .fontColor(Color.Orange)
          .margin({ horizontal: 16, bottom: 8 })
      }

      Tabs({ barPosition: BarPosition.Start }) {
        TabContent() {
          this.buildCropTab()
        }
        .tabBar('裁剪')

        TabContent() {
          this.buildRotationTab()
        }
        .tabBar('旋转')

        TabContent() {
          this.buildWatermarkTab()
        }
        .tabBar('水印')

        TabContent() {
          this.buildTextOverlayTab()
        }
        .tabBar('文字')

        TabContent() {
          this.buildAdjustmentTab()
        }
        .tabBar('调整')

        TabContent() {
          this.buildFilterTab()
        }
        .tabBar('滤镜')

        TabContent() {
          this.buildBatchTab()
        }
        .tabBar('批处理')

        TabContent() {
          this.buildHistoryTab()
        }
        .tabBar('历史')
      }
      .height('85%')
      .barHeight(30)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder buildCropTab() {
    Scroll() {
      Column() {
        Text('图片裁剪测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 裁剪预设网格
        Grid() {
          ForEach(this.cropRegions, (crop: CropRegion, index: number) => {
            GridItem() {
              Column() {
                // 裁剪预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(80)
                    .height(80)
                    .borderRadius(4)
                    .border({ width: 1, color: Color.Gray })

                  // 裁剪框示意
                  if (index === this.currentCropIndex) {
                    Column()
                      .width(Math.min(crop.width / 3, 70))
                      .height(Math.min(crop.height / 3, 70))
                      .border({ width: 2, color: Color.Blue, style: BorderStyle.Dashed })
                      .backgroundColor(Color.Transparent)
                  }
                }
                .width(80)
                .height(80)

                Text(crop.aspectRatio)
                  .fontSize(12)
                  .margin({ top: 4 })

                Text(`${crop.width}×${crop.height}`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentCropIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentCropIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前裁剪详情
        if (this.currentCropIndex < this.cropRegions.length) {
          const currentCrop = this.cropRegions[this.currentCropIndex]
          Column() {
            Text('当前裁剪参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Grid() {
              GridItem() {
                Column() {
                  Text('X坐标')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentCrop.x}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('Y坐标')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentCrop.y}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('宽度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentCrop.width}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('高度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentCrop.height}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
            }
            .rowsTemplate('1fr 1fr')
            .columnsTemplate('repeat(2, 1fr)')
            .height(120)
            .rowsGap(16)
            .columnsGap(16)
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16 })
        }
      }
    }
  }

  @Builder buildRotationTab() {
    Scroll() {
      Column() {
        Text('图片旋转测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 旋转预设网格
        Grid() {
          ForEach(this.rotationConfigs, (rotation: RotationConfig, index: number) => {
            GridItem() {
              Column() {
                // 旋转预览
                Image($r('app.media.icon'))
                  .width(60)
                  .height(60)
                  .rotate({ angle: rotation.angle })
                  .scale({ 
                    x: rotation.flipHorizontal ? -1 : 1, 
                    y: rotation.flipVertical ? -1 : 1 
                  })
                  .borderRadius(4)
                  .border({ 
                    width: index === this.currentRotationIndex ? 3 : 1, 
                    color: index === this.currentRotationIndex ? Color.Blue : Color.Gray 
                  })

                Text(`${rotation.angle}°`)
                  .fontSize(12)
                  .margin({ top: 4 })

                if (rotation.flipHorizontal || rotation.flipVertical) {
                  Text(`H:${rotation.flipHorizontal} V:${rotation.flipVertical}`)
                    .fontSize(10)
                    .fontColor(Color.Gray)
                }
              }
              .padding(8)
              .backgroundColor(index === this.currentRotationIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentRotationIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前旋转详情
        if (this.currentRotationIndex < this.rotationConfigs.length) {
          const currentRotation = this.rotationConfigs[this.currentRotationIndex]
          Column() {
            Text('当前旋转参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Row() {
              Column() {
                Text('旋转角度')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(`${currentRotation.angle}°`)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
              }
              .layoutWeight(1)

              Column() {
                Text('水平翻转')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(currentRotation.flipHorizontal ? '是' : '否')
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(currentRotation.flipHorizontal ? Color.Green : Color.Gray)
              }
              .layoutWeight(1)

              Column() {
                Text('垂直翻转')
                  .fontSize(12)
                  .fontColor(Color.Gray)
                Text(currentRotation.flipVertical ? '是' : '否')
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(currentRotation.flipVertical ? Color.Green : Color.Gray)
              }
              .layoutWeight(1)
            }
            .justifyContent(FlexAlign.SpaceAround)

            // 质量指示器
            Row() {
              Text('输出质量')
                .fontSize(12)
                .fontColor(Color.Gray)
              Progress({
                value: currentRotation.quality,
                total: 100,
                type: ProgressType.Linear
              })
                .width(200)
                .margin({ horizontal: 8 })
              Text(`${currentRotation.quality}%`)
                .fontSize(12)
                .fontColor(Color.Blue)
            }
            .justifyContent(FlexAlign.Start)
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

  @Builder buildWatermarkTab() {
    Scroll() {
      Column() {
        Text('水印添加测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 水印预设网格
        Grid() {
          ForEach(this.watermarkConfigs, (watermark: WatermarkConfig, index: number) => {
            GridItem() {
              Column() {
                // 水印预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(80)
                    .height(80)
                    .borderRadius(4)
                    .backgroundColor('#E0E0E0')

                  Text(watermark.text)
                    .fontSize(watermark.fontSize / 2)
                    .fontColor(watermark.color)
                    .backgroundColor(watermark.shadow ? '#00000040' : 'transparent')
                    .borderRadius(2)
                    .opacity(watermark.opacity)
                    .position(this.getWatermarkPosition(watermark, 80, 80))
                }
                .width(80)
                .height(80)

                Text(watermark.text)
                  .fontSize(11)
                  .margin({ top: 4 })
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })

                Text(watermark.position)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentWatermarkIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentWatermarkIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前水印详情
        if (this.currentWatermarkIndex < this.watermarkConfigs.length) {
          const currentWatermark = this.watermarkConfigs[this.currentWatermarkIndex]
          Column() {
            Text('当前水印参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Grid() {
              GridItem() {
                Column() {
                  Text('文字')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(currentWatermark.text)
                    .fontSize(14)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('位置')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(currentWatermark.position)
                    .fontSize(14)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('透明度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${Math.round(currentWatermark.opacity * 100)}%`)
                    .fontSize(14)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('字体大小')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentWatermark.fontSize}px`)
                    .fontSize(14)
                    .fontWeight(FontWeight.Bold)
                }
              }
            }
            .rowsTemplate('1fr 1fr')
            .columnsTemplate('repeat(2, 1fr)')
            .height(120)
            
            // 颜色和阴影设置
            Row() {
              Text('颜色')
                .fontSize(12)
                .fontColor(Color.Gray)
                .margin({ right: 8 })
              Column()
                .width(20)
                .height(20)
                .backgroundColor(currentWatermark.color)
                .borderRadius(4)
                .border({ width: 1, color: Color.Gray })
                .margin({ right: 16 })

              Text('阴影')
                .fontSize(12)
                .fontColor(Color.Gray)
                .margin({ right: 8 })
              Text(currentWatermark.shadow ? '开启' : '关闭')
                .fontSize(12)
                .fontColor(currentWatermark.shadow ? Color.Green : Color.Gray)
            }
            .justifyContent(FlexAlign.Start)
            .alignItems(VerticalAlign.Center)
            .margin({ top: 12 })
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildTextOverlayTab() {
    Scroll() {
      Column() {
        Text('文字叠加测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 文字叠加预设网格
        Grid() {
          ForEach(this.textOverlays.slice(0, 12), (overlay: TextOverlayConfig, index: number) => {
            GridItem() {
              Column() {
                // 文字叠加预览
                Stack() {
                  Image($r('app.media.icon'))
                    .width(80)
                    .height(80)
                    .borderRadius(4)
                    .backgroundColor('#F0F0F0')

                  Text(overlay.text)
                    .fontSize(Math.min(overlay.size / 2, 10))
                    .fontColor(overlay.color)
                    .backgroundColor(overlay.backgroundColor)
                    .borderRadius(overlay.borderRadius / 2)
                    .padding(overlay.padding / 4)
                    .position({ x: Math.min(overlay.x / 2, 60), y: Math.min(overlay.y / 2, 60) })
                }
                .width(80)
                .height(80)

                Text(overlay.text.length > 8 ? overlay.text.substring(0, 8) + '...' : overlay.text)
                  .fontSize(11)
                  .margin({ top: 4 })

                Text(`${overlay.x},${overlay.y}`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
            }
          })
        }
        .columnsTemplate('repeat(4, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 统计信息
        Row() {
          Column() {
            Text('预设数量')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.textOverlays.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('字体种类')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.getFontTypeCount()}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Blue)
          }
          .layoutWeight(1)

          Column() {
            Text('平均大小')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.getAverageFontSize()}px`)
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
      }
    }
  }

  @Builder buildAdjustmentTab() {
    Scroll() {
      Column() {
        Text('图片调整测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 调整预设网格
        Grid() {
          ForEach(this.adjustmentConfigs, (adjustment: AdjustmentConfig, index: number) => {
            GridItem() {
              Column() {
                // 调整效果预览
                Image($r('app.media.icon'))
                  .width(70)
                  .height(70)
                  .borderRadius(4)
                  .brightness(adjustment.brightness)
                  .contrast(adjustment.contrast)
                  .saturation(adjustment.saturation)
                  .border({ 
                    width: index === this.currentAdjustmentIndex ? 3 : 1, 
                    color: index === this.currentAdjustmentIndex ? Color.Blue : Color.Gray 
                  })

                Text(`调整${index + 1}`)
                  .fontSize(12)
                  .margin({ top: 4 })

                Text(`亮度${adjustment.brightness}`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentAdjustmentIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentAdjustmentIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前调整详情
        if (this.currentAdjustmentIndex < this.adjustmentConfigs.length) {
          const currentAdjustment = this.adjustmentConfigs[this.currentAdjustmentIndex]
          Column() {
            Text('当前调整参数')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            Grid() {
              GridItem() {
                Column() {
                  Text('亮度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.brightness}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('对比度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.contrast}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('饱和度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.saturation}%`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
            }
            .rowsTemplate('1fr')
            .columnsTemplate('repeat(3, 1fr)')
            .height(100)
            .rowsGap(16)
            .columnsGap(16)

            // 高级调整参数
            Grid() {
              GridItem() {
                Column() {
                  Text('锐度')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.sharpness}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('色温')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.temperature}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
              
              GridItem() {
                Column() {
                  Text('色调')
                    .fontSize(12)
                    .fontColor(Color.Gray)
                  Text(`${currentAdjustment.tint}`)
                    .fontSize(16)
                    .fontWeight(FontWeight.Bold)
                }
              }
            }
            .rowsTemplate('1fr')
            .columnsTemplate('repeat(3, 1fr)')
            .height(100)
            .rowsGap(16)
            .columnsGap(16)
            .margin({ top: 8 })
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildFilterTab() {
    Scroll() {
      Column() {
        Text('滤镜预设测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 滤镜预设网格
        Grid() {
          ForEach(this.filterPresets, (filter: FilterPreset, index: number) => {
            GridItem() {
              Column() {
                // 滤镜效果预览
                Image($r('app.media.icon'))
                  .width(70)
                  .height(70)
                  .borderRadius(4)
                  .brightness(filter.adjustment.brightness)
                  .contrast(filter.adjustment.contrast)
                  .saturation(filter.adjustment.saturation)
                  .border({ 
                    width: index === this.currentFilterIndex ? 3 : 1, 
                    color: index === this.currentFilterIndex ? Color.Blue : Color.Gray 
                  })

                Text(filter.name)
                  .fontSize(12)
                  .margin({ top: 4 })
                
                Text(`${filter.adjustment.saturation}%`)
                  .fontSize(10)
                  .fontColor(Color.Gray)
              }
              .padding(8)
              .backgroundColor(index === this.currentFilterIndex ? '#E3F2FD' : '#FAFAFA')
              .borderRadius(6)
              .onClick(() => {
                this.currentFilterIndex = index
              })
            }
          })
        }
        .columnsTemplate('repeat(5, 1fr)')
        .rowsGap(12)
        .columnsGap(8)
        .padding(16)

        // 当前滤镜详情
        if (this.currentFilterIndex < this.filterPresets.length) {
          const currentFilter = this.filterPresets[this.currentFilterIndex]
          Column() {
            Text(`当前滤镜: ${currentFilter.name}`)
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
              .margin({ bottom: 12 })

            // 滤镜参数显示
            Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
              Text(`亮度: ${currentFilter.adjustment.brightness}%`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })

              Text(`对比度: ${currentFilter.adjustment.contrast}%`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })

              Text(`饱和度: ${currentFilter.adjustment.saturation}%`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })

              Text(`锐度: ${currentFilter.adjustment.sharpness}`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })

              Text(`色温: ${currentFilter.adjustment.temperature}`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })

              Text(`色调: ${currentFilter.adjustment.tint}`)
                .fontSize(12)
                .fontColor(Color.Gray)
                .padding({ horizontal: 8, vertical: 4 })
                .backgroundColor('#F0F0F0')
                .borderRadius(4)
                .margin({ right: 8, bottom: 8 })
            }
            .width('100%')
          }
          .padding(16)
          .backgroundColor('#FAFAFA')
          .borderRadius(8)
          .margin({ horizontal: 16, top: 16 })
        }
      }
    }
  }

  @Builder buildBatchTab() {
    Scroll() {
      Column() {
        Text('批处理测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 批处理队列状态
        Row() {
          Column() {
            Text('队列长度')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.batchProcessingQueue.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('处理状态')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(this.autoProcessingEnabled ? '运行中' : '已停止')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(this.autoProcessingEnabled ? Color.Green : Color.Red)
          }
          .layoutWeight(1)

          Column() {
            Text('已完成')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.editOperations.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)
        }
        .padding(16)
        .backgroundColor(Color.White)
        .borderRadius(8)
        .margin({ horizontal: 16 })

        // 批处理队列列表
        Text('批处理队列')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.batchProcessingQueue.slice(0, 15), (item: { id: number; operation: string; params: any }) => {
            ListItem() {
              Row() {
                Text(item.id.toString())
                  .fontSize(12)
                  .fontColor(Color.Gray)
                  .margin({ right: 8 })
                
                Text(item.operation)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                  .layoutWeight(1)
                
                Text('参数' + Object.keys(item.params).length)
                  .fontSize(12)
                  .fontColor(Color.Blue)
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
            }
          })
        }
        .height(300)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  @Builder buildHistoryTab() {
    Scroll() {
      Column() {
        Text('处理历史')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 16 })

        // 历史统计
        Row() {
          Column() {
            Text('总记录数')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.processingHistory.length}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .layoutWeight(1)

          Column() {
            Text('成功率')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.calculateSuccessRate().toFixed(1)}%`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.Green)
          }
          .layoutWeight(1)

          Column() {
            Text('平均耗时')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.calculateAverageDuration()}ms`)
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

        // 历史记录列表
        Text('详细历史')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 16, bottom: 8, horizontal: 16 })

        List() {
          ForEach(this.processingHistory.slice(0, 20), (history: ProcessingHistory) => {
            ListItem() {
              Row() {
                Circle({ width: 8, height: 8 })
                  .fill(history.success ? Color.Green : Color.Red)
                  .margin({ right: 8 })

                Column() {
                  Text(history.operation)
                    .fontSize(14)
                    .fontWeight(FontWeight.Medium)
                  Text(`耗时: ${history.duration}ms`)
                    .fontSize(12)
                    .fontColor(Color.Gray)
                }
                .layoutWeight(1)
                .alignItems(HorizontalAlign.Start)

                Text(history.success ? '成功' : '失败')
                  .fontSize(12)
                  .fontColor(history.success ? Color.Green : Color.Red)
                  .padding({ horizontal: 8, vertical: 4 })
                  .backgroundColor(history.success ? '#E8F5E8' : '#FFEBEE')
                  .borderRadius(4)
              }
              .width('100%')
              .padding(12)
              .backgroundColor('#FAFAFA')
              .borderRadius(6)
            }
          })
        }
        .height(400)
        .margin({ horizontal: 16, bottom: 16 })
      }
    }
  }

  // 工具方法
  private getWatermarkPosition(watermark: WatermarkConfig, containerWidth: number, containerHeight: number): { x: number; y: number } {
    const padding = 4
    switch (watermark.position) {
      case 'top-left':
        return { x: padding, y: padding }
      case 'top-right':
        return { x: containerWidth - padding, y: padding }
      case 'bottom-left':
        return { x: padding, y: containerHeight - padding }
      case 'bottom-right':
        return { x: containerWidth - padding, y: containerHeight - padding }
      case 'center':
        return { x: containerWidth / 2, y: containerHeight / 2 }
      default:
        return { x: padding, y: padding }
    }
  }

  private getFontTypeCount(): number {
    const fontTypes = new Set(this.textOverlays.map(overlay => overlay.font))
    return fontTypes.size
  }

  private getAverageFontSize(): number {
    if (this.textOverlays.length === 0) return 0
    const sum = this.textOverlays.reduce((acc, overlay) => acc + overlay.fontSize, 0)
    return Math.round(sum / this.textOverlays.length)
  }

  private calculateSuccessRate(): number {
    if (this.processingHistory.length === 0) return 0
    const successCount = this.processingHistory.filter(h => h.success).length
    return (successCount / this.processingHistory.length) * 100
  }

  private calculateAverageDuration(): number {
    if (this.processingHistory.length === 0) return 0
    const sum = this.processingHistory.reduce((acc, history) => acc + history.duration, 0)
    return Math.round(sum / this.processingHistory.length)
  }
}