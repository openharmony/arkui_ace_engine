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
 * 测试Image组件transform属性
 * 验证rotate/scale/translate变换在不同参数组合下的效果
 */

@Entry
@Component
struct ImageTransformTestCase031 {
  @State rotateAngle: number = 0
  @State scaleX: number = 1
  @State scaleY: number = 1
  @State translateX: number = 0
  @State translateY: number = 0

  private readonly TRANSFORM_PRESETS: Array<{ name: string; angle: number; sx: number; sy: number; tx: number; ty: number }> = [
    { name: '原图', angle: 0, sx: 1, sy: 1, tx: 0, ty: 0 },
    { name: '旋转45', angle: 45, sx: 1, sy: 1, tx: 0, ty: 0 },
    { name: '旋转90', angle: 90, sx: 1, sy: 1, tx: 0, ty: 0 },
    { name: '旋转180', angle: 180, sx: 1, sy: 1, tx: 0, ty: 0 },
    { name: '放大1.5x', angle: 0, sx: 1.5, sy: 1.5, tx: 0, ty: 0 },
    { name: '缩小0.5x', angle: 0, sx: 0.5, sy: 0.5, tx: 0, ty: 0 },
    { name: '水平拉伸', angle: 0, sx: 2, sy: 1, tx: 0, ty: 0 },
    { name: '垂直拉伸', angle: 0, sx: 1, sy: 2, tx: 0, ty: 0 },
    { name: '水平偏移', angle: 0, sx: 1, sy: 1, tx: 30, ty: 0 },
    { name: '垂直偏移', angle: 0, sx: 1, sy: 1, tx: 0, ty: 30 },
    { name: '旋转+缩放', angle: 45, sx: 1.2, sy: 1.2, tx: 0, ty: 0 },
    { name: '全部组合', angle: 30, sx: 1.1, sy: 1.1, tx: 10, ty: 10 }
  ]

  build() {
    Column() {
      Text('Image transform属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image($r('app.media.startIcon'))
        .width(120)
        .height(120)
        .rotate({ angle: this.rotateAngle })
        .scale({ x: this.scaleX, y: this.scaleY })
        .translate({ x: this.translateX, y: this.translateY })
        .border({ width: 2, color: Color.Blue })
        .borderRadius(8)
        .margin({ bottom: 16 })

      Text(`旋转:${this.rotateAngle}° 缩放:${this.scaleX}x${this.scaleY} 偏移:${this.translateX},${this.translateY}`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.TRANSFORM_PRESETS, (preset: { name: string; angle: number; sx: number; sy: number; tx: number; ty: number }) => {
          GridItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width(40)
                .height(40)
                .rotate({ angle: preset.angle })
                .scale({ x: preset.sx, y: preset.sy })
                .borderRadius(4)

              Text(preset.name)
                .fontSize(10)
                .margin({ top: 4 })
            }
            .padding(8)
            .backgroundColor('#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.rotateAngle = preset.angle
              this.scaleX = preset.sx
              this.scaleY = preset.sy
              this.translateX = preset.tx
              this.translateY = preset.ty
            })
          }
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
