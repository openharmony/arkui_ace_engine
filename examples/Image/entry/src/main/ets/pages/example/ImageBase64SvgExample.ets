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
 * Image Base64 解耦测试示例
 * ========================================
 * 测试功能说明:
 * 本示例通过 ResourceManager 读取媒体资源原始字节，
 * 使用 util.Base64Helper 编码为 base64 字符串，
 * 拼接 data URI 后传给 Image 组件加载，验证：
 * 1. Base64 SVG 加载（data:image/svg+xml;base64,...）
 * 2. Base64 PNG 回归测试
 * 3. 通配 MIME 类型（image/xxx）基于内容的检测
 *
 * 关键 API:
 * - resourceManager.getMediaContentSync() 读取资源为 Uint8Array
 * - util.Base64Helper.encodeToStringSync() 编码为 base64 字符串
 */

import { util } from '@kit.ArkTS';

/**
 * SVG Base64 测试项：读取 SVG 资源编码为 Base64 后加载
 */
@Component
struct SvgBase64TestItem {
  @State dataUri: string = ''
  @State encodeStatus: string = '编码中...'
  @State loadStatus: string = '等待加载'

  aboutToAppear() {
    this.encodeResource()
  }

  private encodeResource() {
    try {
      let context = getContext(this)
      let resMgr = context.resourceManager
      let rawData: Uint8Array = resMgr.getMediaContentSync($r('app.media.svg').id)
      let base64Helper = new util.Base64Helper()
      let base64Str = base64Helper.encodeToStringSync(rawData)
      this.dataUri = `data:image/svg+xml;base64,${base64Str}`
      this.encodeStatus = `编码成功 (${rawData.byteLength} 字节)`
    } catch (e) {
      this.encodeStatus = `编码失败: ${e}`
    }
  }

  build() {
    Column({ space: 12 }) {
      Text('1. SVG 资源 → Base64 (data:image/svg+xml)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('编码状态: ' + this.encodeStatus)
        .fontSize(13)
        .fontColor(this.encodeStatus.includes('成功') ? Color.Green : Color.Red)

      Row({ space: 20 }) {
        if (this.dataUri) {
          Image(this.dataUri)
            .width(100)
            .height(100)
            .backgroundColor('#F5F5F5')
            .border({ width: 1, color: '#CCCCCC' })
            .borderRadius(8)
            .onComplete(() => {
              this.loadStatus = '加载成功'
            })
            .onError(() => {
              this.loadStatus = '加载失败'
            })
        } else {
          Column() {
            Text('编码中...')
              .fontSize(13)
              .fontColor(Color.Gray)
          }
          .width(100)
          .height(100)
          .backgroundColor('#F5F5F5')
          .border({ width: 1, color: '#CCCCCC' })
          .borderRadius(8)
          .justifyContent(FlexAlign.Center)
        }

        Column({ space: 8 }) {
          Text('加载状态:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text(this.loadStatus)
            .fontSize(13)
            .fontColor(this.loadStatus.includes('成功') ? Color.Green :
                       this.loadStatus.includes('失败') ? Color.Red : Color.Gray)
        }
        .alignItems(HorizontalAlign.Start)
      }
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFEBEE')
    .borderRadius(15)
  }
}

/**
 * PNG Base64 测试项：读取 PNG 资源编码为 Base64 后加载
 */
@Component
struct PngBase64TestItem {
  @State dataUri: string = ''
  @State encodeStatus: string = '编码中...'
  @State loadStatus: string = '等待加载'

  aboutToAppear() {
    this.encodeResource()
  }

  private encodeResource() {
    try {
      let context = getContext(this)
      let resMgr = context.resourceManager
      let rawData: Uint8Array = resMgr.getMediaContentSync($r('app.media.startIcon').id)
      let base64Helper = new util.Base64Helper()
      let base64Str = base64Helper.encodeToStringSync(rawData)
      this.dataUri = `data:image/png;base64,${base64Str}`
      this.encodeStatus = `编码成功 (${rawData.byteLength} 字节)`
    } catch (e) {
      this.encodeStatus = `编码失败: ${e}`
    }
  }

  build() {
    Column({ space: 12 }) {
      Text('2. PNG 资源 → Base64 (data:image/png)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('编码状态: ' + this.encodeStatus)
        .fontSize(13)
        .fontColor(this.encodeStatus.includes('成功') ? Color.Green : Color.Red)

      Row({ space: 20 }) {
        if (this.dataUri) {
          Image(this.dataUri)
            .width(100)
            .height(100)
            .backgroundColor('#F5F5F5')
            .border({ width: 1, color: '#CCCCCC' })
            .borderRadius(8)
            .onComplete(() => {
              this.loadStatus = '加载成功'
            })
            .onError(() => {
              this.loadStatus = '加载失败'
            })
        } else {
          Column() {
            Text('编码中...')
              .fontSize(13)
              .fontColor(Color.Gray)
          }
          .width(100)
          .height(100)
          .backgroundColor('#F5F5F5')
          .border({ width: 1, color: '#CCCCCC' })
          .borderRadius(8)
          .justifyContent(FlexAlign.Center)
        }

        Column({ space: 8 }) {
          Text('加载状态:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text(this.loadStatus)
            .fontSize(13)
            .fontColor(this.loadStatus.includes('成功') ? Color.Green :
                       this.loadStatus.includes('失败') ? Color.Red : Color.Gray)
        }
        .alignItems(HorizontalAlign.Start)
      }
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#E8F5E9')
    .borderRadius(15)
  }
}

/**
 * 通配 MIME 测试项：读取 SVG 资源编码，MIME 声明为 image/xxx
 */
@Component
struct WildcardMimeTestItem {
  @State dataUri: string = ''
  @State encodeStatus: string = '编码中...'
  @State loadStatus: string = '等待加载'

  aboutToAppear() {
    this.encodeResource()
  }

  private encodeResource() {
    try {
      let context = getContext(this)
      let resMgr = context.resourceManager
      let rawData: Uint8Array = resMgr.getMediaContentSync($r('app.media.svg').id)
      let base64Helper = new util.Base64Helper()
      let base64Str = base64Helper.encodeToStringSync(rawData)
      // 故意使用非标准 MIME image/xxx，验证底层按内容检测
      this.dataUri = `data:image/xxx;base64,${base64Str}`
      this.encodeStatus = `编码成功 (MIME 声明为 image/xxx)`
    } catch (e) {
      this.encodeStatus = `编码失败: ${e}`
    }
  }

  build() {
    Column({ space: 12 }) {
      Text('3. 通配 MIME + 内容检测')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('MIME 声明为 image/xxx，实际数据为 SVG，底层应按内容识别')
        .fontSize(13)
        .fontColor(Color.Gray)

      Text('编码状态: ' + this.encodeStatus)
        .fontSize(13)
        .fontColor(this.encodeStatus.includes('成功') ? Color.Green : Color.Red)

      Row({ space: 20 }) {
        if (this.dataUri) {
          Image(this.dataUri)
            .width(100)
            .height(100)
            .backgroundColor('#F5F5F5')
            .border({ width: 1, color: '#CCCCCC' })
            .borderRadius(8)
            .onComplete(() => {
              this.loadStatus = '加载成功 (内容检测识别为 SVG)'
            })
            .onError(() => {
              this.loadStatus = '加载失败'
            })
        } else {
          Column() {
            Text('编码中...')
              .fontSize(13)
              .fontColor(Color.Gray)
          }
          .width(100)
          .height(100)
          .backgroundColor('#F5F5F5')
          .border({ width: 1, color: '#CCCCCC' })
          .borderRadius(8)
          .justifyContent(FlexAlign.Center)
        }

        Column({ space: 8 }) {
          Text('加载状态:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text(this.loadStatus)
            .fontSize(13)
            .fontColor(this.loadStatus.includes('成功') ? Color.Green : Color.Orange)
        }
        .alignItems(HorizontalAlign.Start)
      }
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor('#FFF8E1')
    .borderRadius(15)
  }
}

@Entry
@Component
struct ImageBase64SvgExample {
  @State currentTestIndex: number = 0
  @State svgDataUri: string = ''
  @State pngDataUri: string = ''
  @State switchLoadStatus: string = '等待加载'

  aboutToAppear() {
    this.encodeSwitchResources()
  }

  private encodeSwitchResources() {
    let context = getContext(this)
    let resMgr = context.resourceManager
    let base64Helper = new util.Base64Helper()

    try {
      let svgData = resMgr.getMediaContentSync($r('app.media.svg').id)
      let svgBase64 = base64Helper.encodeToStringSync(svgData)
      this.svgDataUri = `data:image/svg+xml;base64,${svgBase64}`
    } catch (_) {}

    try {
      let pngData = resMgr.getMediaContentSync($r('app.media.startIcon').id)
      let pngBase64 = base64Helper.encodeToStringSync(pngData)
      this.pngDataUri = `data:image/png;base64,${pngBase64}`
    } catch (_) {}
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image Base64 解耦测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 5 })

        Text('通过 getMediaContentSync 读取原始字节 → Base64Helper 编码 → Image 加载')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 10 })

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== 编码流程说明 ==========
        Column({ space: 8 }) {
          Text('编码流程')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. resMgr.getMediaContentSync($r(\'app.media.xxx\').id) → Uint8Array')
            .fontSize(12)
            .fontColor(Color.Black)
            .fontFamily('monospace')

          Text('2. new util.Base64Helper().encodeToStringSync(uint8Array) → base64 字符串')
            .fontSize(12)
            .fontColor(Color.Black)
            .fontFamily('monospace')

          Text('3. "data:image/xxx;base64," + base64Str → data URI')
            .fontSize(12)
            .fontColor(Color.Black)
            .fontFamily('monospace')

          Text('4. Image(dataUri) 加载显示')
            .fontSize(12)
            .fontColor(Color.Black)
            .fontFamily('monospace')
        }
        .width('100%')
        .padding(12)
        .backgroundColor('#FFFDE7')
        .borderRadius(10)

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 测试 1: SVG → Base64 → Image ==========
        SvgBase64TestItem()

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 测试 2: PNG → Base64 → Image ==========
        PngBase64TestItem()

        Divider().strokeWidth(1).color('#EEEEEE')

        // ========== 测试 3: 通配 MIME ==========
        WildcardMimeTestItem()

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== 对比: 原始资源 vs Base64 ==========
        Column({ space: 15 }) {
          Text('对比: 原始资源 vs Base64 编码')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('验证同一资源通过不同方式加载效果一致')
            .fontSize(13)
            .fontColor(Color.Gray)

          Row({ space: 15 }) {
            Column({ space: 5 }) {
              Text('原始资源')
                .fontSize(13)
                .fontWeight(FontWeight.Medium)
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .backgroundColor('#F5F5F5')
                .border({ width: 1, color: '#DDDDDD' })
                .borderRadius(8)
            }

            Column({ space: 5 }) {
              Text('Base64 编码')
                .fontSize(13)
                .fontWeight(FontWeight.Medium)
              if (this.svgDataUri) {
                Image(this.svgDataUri)
                  .width(100)
                  .height(100)
                  .backgroundColor('#F5F5F5')
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(8)
              } else {
                Text('编码中...')
                  .fontSize(12)
                  .fontColor(Color.Gray)
              }
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

        // ========== 动态切换: SVG ↔ PNG ==========
        Column({ space: 15 }) {
          Text('动态切换 Base64 图片源')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          if (this.svgDataUri && this.pngDataUri) {
            Image(this.currentTestIndex === 0 ? this.pngDataUri : this.svgDataUri)
              .width(150)
              .height(150)
              .backgroundColor('#F5F5F5')
              .border({ width: 1, color: '#CCCCCC' })
              .borderRadius(10)
              .onComplete(() => {
                this.switchLoadStatus = '加载成功'
              })
              .onError(() => {
                this.switchLoadStatus = '加载失败'
              })
          }

          Text(this.currentTestIndex === 0 ? '当前: Base64 PNG' : '当前: Base64 SVG')
            .fontSize(14)
            .fontColor(Color.Blue)
            .fontWeight(FontWeight.Medium)

          Text('加载状态: ' + this.switchLoadStatus)
            .fontSize(13)
            .fontColor(this.switchLoadStatus.includes('成功') ? Color.Green : Color.Gray)

          Row({ space: 15 }) {
            Button('切换 PNG')
              .fontSize(14)
              .backgroundColor(this.currentTestIndex === 0 ? Color.Green : '#D3D3D3')
              .onClick(() => {
                this.currentTestIndex = 0
                this.switchLoadStatus = '等待加载'
              })

            Button('切换 SVG')
              .fontSize(14)
              .backgroundColor(this.currentTestIndex === 1 ? Color.Green : '#D3D3D3')
              .onClick(() => {
                this.currentTestIndex = 1
                this.switchLoadStatus = '等待加载'
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== SVG 缩放验证 ==========
        Column({ space: 15 }) {
          Text('SVG Base64 缩放验证 (矢量不失真)')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 15 }) {
            Column({ space: 5 }) {
              if (this.svgDataUri) {
                Image(this.svgDataUri)
                  .width(50)
                  .height(50)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(4)
              }
              Text('50x50')
                .fontSize(11)
                .fontColor(Color.Gray)
            }

            Column({ space: 5 }) {
              if (this.svgDataUri) {
                Image(this.svgDataUri)
                  .width(100)
                  .height(100)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(4)
              }
              Text('100x100')
                .fontSize(11)
                .fontColor(Color.Gray)
            }

            Column({ space: 5 }) {
              if (this.svgDataUri) {
                Image(this.svgDataUri)
                  .width(150)
                  .height(150)
                  .border({ width: 1, color: '#DDDDDD' })
                  .borderRadius(4)
              }
              Text('150x150')
                .fontSize(11)
                .fontColor(Color.Gray)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceAround)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFFFFF')
        .borderRadius(15)
        .shadow({ radius: 5, color: '#20000000' })

        Divider().strokeWidth(2).color('#E0E0E0')

        // ========== 测试说明 ==========
        Column({ space: 10 }) {
          Text('测试说明')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Text('1. getMediaContentSync(resId) 读取资源原始字节 → Uint8Array')
            .fontSize(12)
            .fontColor(Color.Black)

          Text('2. Base64Helper.encodeToStringSync(uint8Array) → base64 字符串')
            .fontSize(12)
            .fontColor(Color.Black)

          Text('3. 手动拼接 "data:image/svg+xml;base64," + base64Str')
            .fontSize(12)
            .fontColor(Color.Black)

          Text('4. SVG 底层按内容自动识别，支持 fillColor 等矢量特性')
            .fontSize(12)
            .fontColor(Color.Black)

          Text('5. 通配 MIME (image/xxx) 同样能加载，框架按实际数据判断类型')
            .fontSize(12)
            .fontColor(Color.Black)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E8EAF6')
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
}
