/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { EllipseShape, matrix4 } from '@kit.ArkUI';

@Entry
@Component
struct BinderImageMatrixDemo {
  // 定义矩阵1：初始为单位矩阵，先缩放到0.5倍，再以(10,10)为中心旋转-10度
  private matrix1 = matrix4.identity()
    .scale({ x: 0.5, y: 0.5 })
    .rotate({
      x: 2,
      y: 0.5,
      z: 3,
      centerX: 10,
      centerY: 10,
      angle: -10
    })
  // 图片资源数组
  @State imageResource: Resource[] = [
    $r("app.media.startIcon"),
    $r("app.media.cat01"),
    $r("app.media.cloud")
  ]
  @State imgIdx: number = 0   // 当前显示图片的索引
  // 图片重复模式数组
  @State repeatModes: ImageRepeat[] = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY
  ]
  @State repeatIdx: number = 0  // 当前重复模式的索引

  // 图片切片调整参数
  @State resizeMode: ResizableOptions = {
    slice: {
      top: 30,
      bottom: 30,
      left: 30,
      right: 30
    }
  }

  build() {
    Column({ space: 20 }) {
      // 应用矩阵变换的图片
      Image(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .borderWidth(2)
        .objectFit(ImageFit.MATRIX) // 按矩阵方式适配图片
        .imageMatrix(this.matrix1)  // 绑定矩阵变换
        .contentTransition(ContentTransitionEffect.OPACITY) // 切换时淡入淡出
        .onClick(() => {
          // 点击循环切换图片
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })

      // 使用alt属性显示图片（src为空时生效）
      Image("")
        .alt(this.imageResource[this.imgIdx])
        .width(300)
        .height(300)
        .objectFit(ImageFit.Contain)
        .borderWidth(2)
        .contentTransition(ContentTransitionEffect.OPACITY)
        .onClick(() => {
          // 点击循环切换图片
          this.imgIdx = (this.imgIdx + 1) % this.imageResource.length
        })
    }
    .width("100%")
    .height("100%")
    .justifyContent(FlexAlign.Center) 
    .alignItems(HorizontalAlign.Center) 
  }
}