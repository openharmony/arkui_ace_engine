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
struct ShapeExample {
  scroller: Scroller = new Scroller();
  build() {
    Column({ space: 10 }) {
      Scroll(this.scroller) {
        Column({ space: 10 }) {
          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: '-2',
            y: '-2',
            width: '304',
            height: '130'
          })

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: $r('app.float.x'),
            y: $r('app.float.y'),
            width: $r('app.float.width'),
            height: $r('app.float.height')
          })

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: undefined,
            y: undefined,
            width: undefined,
            height: undefined
          })

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fill(0x317AF7)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fill('rgb(255, 100, 255)')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fill(Color.Blue)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fill($r('app.color.Gray'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fillOpacity(0.8)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fillOpacity('0.8')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .fillOpacity($r('app.float.fillOpacity'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke('rgb(255, 100, 255)')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(Color.Blue)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke($r('app.color.Gray'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeDashArray([20])

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeDashOffset(10)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeDashOffset('10')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeDashOffset($r('app.float.strokeDashOffset'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeLineCap(LineCapStyle.Round)
          .strokeWidth(4)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeLineJoin(LineJoinStyle.Miter)
          .strokeMiterLimit(10)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeLineJoin(LineJoinStyle.Miter)
          .strokeMiterLimit('10')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeLineJoin(LineJoinStyle.Miter)
          .strokeMiterLimit($r('app.float.strokeDashOffset'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth('4')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth($r('app.float.strokeDashOffset'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth('4')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth($r('app.float.strokeDashOffset'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth(4)
          .strokeOpacity(0.8)

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth(4)
          .strokeOpacity('0.8')

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .strokeWidth(4)
          .strokeOpacity($r('app.float.fillOpacity'))

          Shape() {
            Rect().width(300).height(50)
            Ellipse().width(300).height(50).offset({ x: 0, y: 60 })
            Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
          }
          .width(350)
          .height(140)
          .viewPort({
            x: -2,
            y: -2,
            width: 304,
            height: 130
          })
          .stroke(0x317AF7)
          .antiAlias(false)
          
        }
      }
    }.width('100%').margin({ top: 15 })
  }
}