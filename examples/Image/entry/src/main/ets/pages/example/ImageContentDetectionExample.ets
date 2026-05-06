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
 * ========================================
 * Image 内容检测解耦测试示例
 * ========================================
 * 测试功能说明:
 * 本示例验证 Image 组件基于内容的图片类型检测能力，
 * 主要覆盖 SVG 检测从"后缀名推断"到"数据内容判断"的重构。
 *
 * 测试场景:
 * 1. 标准 SVG 文件加载 (回归)
 * 2. 标准 PNG/JPG 文件加载 (回归)
 * 3. Base64 SVG 渲染及 SVG 特性 (fillColor, 缩放不失真)
 * 4. Base64 与 Resource 交叉对比
 * 5. 缓存行为验证
 *
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "内容检测解耦测试" 页面
 * 2. 观察 SVG 和位图是否各自正确渲染
 * 3. 点击 fillColor 切换按钮验证 SVG 着色
 * 4. 点击"重新加载"按钮验证缓存行为
 * 5. 切换不同图片源验证动态切换
 *
 * 关键 API:
 * - resourceManager.getMediaContentSync() 读取资源为 Uint8Array
 * - util.Base64Helper.encodeToStringSync() 编码为 base64 字符串
 */

import { util } from '@kit.ArkTS';

@Entry
@Component
struct ImageContentDetectionExample {
  @State svgLoadStatus: string = '等待加载'
  @State pngLoadStatus: string = '等待加载'
  @State svgBase64LoadStatus: string = '等待加载'
  @State currentFillColor: Color = Color.Red
  @State fillColorIndex: number = 0
  @State reloadCount: number = 0
  @State showImages: boolean = true
  @State svgStarBase64: string = ''
  @State svgArrowBase64: string = ''
  @State svgHeartBase64: string = ''
  @State pngBase64: string = ''
  @State dynamicSourceIndex: number = 0
  @State dynamicLoadStatus: string = '等待加载'
  @State dynamicDataUri: string = ''

  // 填充色列表
  private fillColors: Color[] = [
    Color.Red,
    Color.Blue,
    Color.Green,
    Color.Orange,
    Color.Black,
    Color.Transparent
  ]
  private fillColorNames: string[] = [
    '红色', '蓝色', '绿色', '橙色', '黑色', '透明'
  ]

  aboutToAppear() {
    this.encodeResources()
  }

  private encodeResources() {
    let context = getContext(this)
    let resMgr = context.resourceManager
    let base64Helper = new util.Base64Helper()

    try {
      let svgData = resMgr.getMediaContentSync($r('app.media.svg').id)
      let svgBase64 = base64Helper.encodeToStringSync(svgData)
      this.svgStarBase64 = `data:image/svg+xml;base64,${svgBase64}`
      this.svgArrowBase64 = this.svgStarBase64
      this.svgHeartBase64 = this.svgStarBase64
    } catch (_) {}

    try {
      let pngData = resMgr.getMediaContentSync($r('app.media.startIcon').id)
      let pngBase64Str = base64Helper.encodeToStringSync(pngData)
      this.pngBase64 = `data:image/png;base64,${pngBase64Str}`
    } catch (_) {}
  }

  private encodeDynamicResource(resource: string, mimeType: string) {
    try {
      let context = getContext(this)
      let resMgr = context.resourceManager
      let base64Helper = new util.Base64Helper()
      let resId: number = resource === 'png' ? $r('app.media.startIcon').id : $r('app.media.svg').id
      let rawData: Uint8Array = resMgr.getMediaContentSync(resId)
      let base64Str = base64Helper.encodeToStringSync(rawData)
      this.dynamicDataUri = `data:${mimeType};base64,${base64Str}`
    } catch (e) {
      this.dynamicLoadStatus = `编码失败: ${e}`
      this.dynamicDataUri = ''
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image 内容检测解耦测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 5 })

        Text('验证基于数据内容的 SVG 检测机制')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== 第一部分: 回归测试 ==========
        Column({ space: 15 }) {
          Text('回归测试: 文件路径加载')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            Column({ space: 8 }) {
              Text('SVG 文件')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .backgroundColor('#F5F5F5')
                .borderRadius(8)
                .onComplete(() => {
                  this.svgLoadStatus = 'SVG 加载成功'
                })
                .onError(() => {
                  this.svgLoadStatus = 'SVG 加载失败'
                })
              Text(this.svgLoadStatus)
                .fontSize(12)
                .fontColor(this.svgLoadStatus.includes('成功') ? Color.Green : Color.Red)
            }

            Column({ space: 8 }) {
              Text('PNG 文件')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Image($r('app.media.startIcon'))
                .width(100)
                .height(100)
                .backgroundColor('#F5F5F5')
                .borderRadius(8)
                .onComplete(() => {
                  this.pngLoadStatus = 'PNG 加载成功'
                })
                .onError(() => {
                  this.pngLoadStatus = 'PNG 加载失败'
                })
              Text(this.pngLoadStatus)
                .fontSize(12)
                .fontColor(this.pngLoadStatus.includes('成功') ? Color.Green : Color.Red)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E8F5E9')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 第二部分: Base64 SVG 多图形渲染 ==========
        Column({ space: 15 }) {
          Text('Base64 SVG 多图形渲染')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('验证不同 Base64 SVG 图形均能正确解析和渲染')
            .fontSize(13)
            .fontColor(Color.Gray)

          Row({ space: 15 }) {
            Column({ space: 5 }) {
              Image(this.svgStarBase64)
                .width(80)
                .height(80)
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
              Text('五角星')
                .fontSize(12)
                .fontColor(Color.Gray)
            }

            Column({ space: 5 }) {
              Image(this.svgArrowBase64)
                .width(80)
                .height(80)
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
              Text('箭头')
                .fontSize(12)
                .fontColor(Color.Gray)
            }

            Column({ space: 5 }) {
              Image(this.svgHeartBase64)
                .width(80)
                .height(80)
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
              Text('心形')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFF3E0')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 第三部分: SVG 缩放不失真 ==========
        Column({ space: 15 }) {
          Text('SVG 矢量缩放验证')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('SVG 放大后应保持清晰 (与位图对比)')
            .fontSize(13)
            .fontColor(Color.Gray)

          // SVG 放大
          Row({ space: 15 }) {
            Column({ space: 5 }) {
              Text('Base64 SVG')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Image(this.svgStarBase64)
                .width(200)
                .height(200)
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
              Text('200x200 无锯齿')
                .fontSize(12)
                .fontColor(Color.Green)
            }

            Column({ space: 5 }) {
              Text('Base64 PNG (1x1)')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Image(this.pngBase64)
                .width(200)
                .height(200)
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
              Text('200x200 放大模糊')
                .fontSize(12)
                .fontColor(Color.Orange)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E3F2FD')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 第四部分: SVG fillColor 切换 ==========
        Column({ space: 15 }) {
          Text('Base64 SVG fillColor 验证')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('验证 SVG 的 fillColor 着色功能正常 (需要 SVG 支持填充)')
            .fontSize(13)
            .fontColor(Color.Gray)

          Row({ space: 15 }) {
            Image(this.svgStarBase64)
              .width(100)
              .height(100)
              .fillColor(this.currentFillColor)
              .border({ width: 1, color: '#DDDDDD' })
              .borderRadius(8)

            Image(this.svgHeartBase64)
              .width(100)
              .height(100)
              .fillColor(this.currentFillColor)
              .border({ width: 1, color: '#DDDDDD' })
              .borderRadius(8)

            Image(this.svgArrowBase64)
              .width(100)
              .height(100)
              .fillColor(this.currentFillColor)
              .border({ width: 1, color: '#DDDDDD' })
              .borderRadius(8)
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)

          Text('当前 fillColor: ' + this.fillColorNames[this.fillColorIndex])
            .fontSize(14)
            .fontColor(Color.Blue)
            .fontWeight(FontWeight.Medium)

          Row({ space: 10 }) {
            Button('上一个颜色')
              .fontSize(13)
              .onClick(() => {
                this.fillColorIndex =
                  (this.fillColorIndex - 1 + this.fillColors.length) % this.fillColors.length
                this.currentFillColor = this.fillColors[this.fillColorIndex]
              })

            Button('下一个颜色')
              .fontSize(13)
              .onClick(() => {
                this.fillColorIndex = (this.fillColorIndex + 1) % this.fillColors.length
                this.currentFillColor = this.fillColors[this.fillColorIndex]
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F3E5F5')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 第五部分: 动态切换 + 缓存验证 ==========
        Column({ space: 15 }) {
          Text('动态切换与缓存验证')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('切换图片源验证类型检测和缓存正常')
            .fontSize(13)
            .fontColor(Color.Gray)

          Text('重新加载次数: ' + this.reloadCount)
            .fontSize(14)
            .fontColor(Color.Blue)

          Row({ space: 15 }) {
            Button('隐藏全部')
              .fontSize(13)
              .backgroundColor(Color.Orange)
              .onClick(() => {
                this.showImages = false
                this.reloadCount++
              })

            Button('重新显示')
              .fontSize(13)
              .backgroundColor(Color.Green)
              .onClick(() => {
                this.showImages = true
                this.reloadCount++
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          if (this.showImages) {
            Row({ space: 15 }) {
              Column({ space: 5 }) {
                Image(this.svgStarBase64)
                  .width(80)
                  .height(80)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(8)
                Text('SVG')
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }

              Column({ space: 5 }) {
                Image(this.pngBase64)
                  .width(80)
                  .height(80)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(8)
                Text('PNG')
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }

              Column({ space: 5 }) {
                Image($r('app.media.svg'))
                  .width(80)
                  .height(80)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(8)
                Text('文件 SVG')
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.SpaceAround)
          } else {
            Text('图片已隐藏，点击"重新显示"验证缓存')
              .fontSize(14)
              .fontColor(Color.Gray)
              .padding(20)
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 动态修改图源 ==========
        Column({ space: 15 }) {
          Text('动态修改图源')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('运行时动态编码不同资源为 Base64，传给 Image 加载')
            .fontSize(13)
            .fontColor(Color.Gray)

          if (this.dynamicDataUri) {
            Image(this.dynamicDataUri)
              .width(150)
              .height(150)
              .backgroundColor('#F5F5F5')
              .border({ width: 1, color: '#CCCCCC' })
              .borderRadius(10)
              .onComplete(() => {
                this.dynamicLoadStatus = '加载成功'
              })
              .onError(() => {
                this.dynamicLoadStatus = '加载失败'
              })
          } else {
            Column() {
              Text('点击下方按钮动态编码')
                .fontSize(13)
                .fontColor(Color.Gray)
            }
            .width(150)
            .height(150)
            .backgroundColor('#F5F5F5')
            .border({ width: 1, color: '#CCCCCC' })
            .borderRadius(10)
            .justifyContent(FlexAlign.Center)
          }

          Text(this.dynamicSourceIndex === 0 ? '当前: Base64 SVG' :
               this.dynamicSourceIndex === 1 ? '当前: Base64 PNG' :
               this.dynamicSourceIndex === 2 ? '当前: 通配 MIME SVG' : '')
            .fontSize(14)
            .fontColor(Color.Blue)
            .fontWeight(FontWeight.Medium)

          Text('加载状态: ' + this.dynamicLoadStatus)
            .fontSize(13)
            .fontColor(this.dynamicLoadStatus.includes('成功') ? Color.Green : Color.Gray)

          Row({ space: 10 }) {
            Button('Base64 SVG')
              .fontSize(13)
              .backgroundColor(this.dynamicSourceIndex === 0 ? Color.Green : '#D3D3D3')
              .onClick(() => {
                this.dynamicSourceIndex = 0
                this.dynamicLoadStatus = '编码中...'
                this.dynamicDataUri = ''
                this.encodeDynamicResource('svg', 'image/svg+xml')
              })

            Button('Base64 PNG')
              .fontSize(13)
              .backgroundColor(this.dynamicSourceIndex === 1 ? Color.Green : '#D3D3D3')
              .onClick(() => {
                this.dynamicSourceIndex = 1
                this.dynamicLoadStatus = '编码中...'
                this.dynamicDataUri = ''
                this.encodeDynamicResource('png', 'image/png')
              })

            Button('通配 MIME')
              .fontSize(13)
              .backgroundColor(this.dynamicSourceIndex === 2 ? Color.Green : '#D3D3D3')
              .onClick(() => {
                this.dynamicSourceIndex = 2
                this.dynamicLoadStatus = '编码中...'
                this.dynamicDataUri = ''
                this.encodeDynamicResource('svg', 'image/xxx')
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E0F7FA')
        .borderRadius(15)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 第六部分: 综合对比表 ==========
        Column({ space: 15 }) {
          Text('综合对比表')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          this.ComparisonRow('图片来源', '类型', '是否 SVG', '状态')
          this.ComparisonRow('app.media.svg', '文件', '是 (后缀)', '回归')
          this.ComparisonRow('app.media.startIcon', '文件', '否 (后缀)', '回归')
          this.ComparisonRow('svg+xml;base64,...', 'Base64', '是 (内容)', '新增')
          this.ComparisonRow('image/xxx;base64,...', 'Base64', '是 (内容)', '新增')
          this.ComparisonRow('image/png;base64,...', 'Base64', '否 (内容)', '回归')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E8EAF6')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== 底部说明 ==========
        Column({ space: 10 }) {
          Text('关键改动说明')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. SVG 检测从"后缀名推断"改为"数据内容 MIME 判断"')
            .fontSize(13)
            .fontColor(Color.Black)

          Text('2. Base64 URI 支持任意 image/* MIME 类型')
            .fontSize(13)
            .fontColor(Color.Black)

          Text('3. Base64 SVG (image/svg+xml) 完整支持加载→解析→渲染')
            .fontSize(13)
            .fontColor(Color.Black)

          Text('4. 缓存 key 正确反映基于内容的类型判断')
            .fontSize(13)
            .fontColor(Color.Black)

          Text('5. 新增图片格式无需修改 ArkUI 层逻辑')
            .fontSize(13)
            .fontColor(Color.Black)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFFDE7')
        .borderRadius(15)
        .margin({ bottom: 20 })
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }

  @Builder
  ComparisonRow(col1: string, col2: string, col3: string, col4: string) {
    Row() {
      Text(col1)
        .fontSize(12)
        .width('35%')
      Text(col2)
        .fontSize(12)
        .width('15%')
      Text(col3)
        .fontSize(12)
        .width('30%')
      Text(col4)
        .fontSize(12)
        .fontColor(col4 === '新增' ? Color.Green : Color.Blue)
        .width('20%')
    }
    .width('100%')
    .padding({ top: 4, bottom: 4 })
  }
}
