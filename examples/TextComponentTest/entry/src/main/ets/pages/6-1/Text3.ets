/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct TextSpanExample3 {
  @State widthCon: number = 60
  @State heightCon: number = 60
  @State widthSpan: number = 200
  @State heightSpan: number = 60
  @State backgroundColorAll: (string | number | Color | Resource)[] = [Color.Blue, "#fc0303", 0xFF0000, 'rgb(2, 184, 17)', $r('app.color.color_yellow')]
  @State backgroundColorStr: string[] = ['Blue', "#fc0303", "0xFF0000", 'rgb(2, 184, 17)', "$r('yellow')"]
  @State backgroundColorIndex: number = 0
  @State radiusSpan: Dimension[] = ['10px', '20vp', '30fp', '50lpx', '10%', $r('app.string.radius')]
  @State radiusIndex: number = 0
  @State fontSize: number = 16

  build() {
    Column({ space: 8 }) {
      Text() {
        ContainerSpan() {
          Span('Span').fontSize('16fp').fontColor(Color.White).width(this.widthSpan).height(this.heightSpan).fontSize(this.fontSize)
            .textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex], radius: this.radiusSpan[this.radiusIndex] })
          ImageSpan($r('app.media.app_icon')).textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex], radius: this.radiusSpan[this.radiusIndex] })
            .borderWidth(1).width(this.widthCon).height(this.heightCon)
        }.textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex], radius: this.radiusSpan[this.radiusIndex] })
      }.borderWidth(1)

      Row() {
        Button('背景颜色:' + this.backgroundColorStr[this.backgroundColorIndex]).onClick(() => {
          this.backgroundColorIndex ++
          if (this.backgroundColorIndex > (this.backgroundColorAll.length - 1)) {
            this.backgroundColorIndex = 0
          }
        }).width('100%')
      }.width('80%')

      Row() {
        Button('radius:' + this.radiusSpan[this.radiusIndex]).onClick(() => {
          this.radiusIndex ++
          if (this.radiusIndex > (this.radiusSpan.length - 1)) {
            this.radiusIndex = 0
          }
        }).width('100%')
      }.width('80%')

      Row() {
        Button('Image width+,' + this.widthCon).onClick((event: ClickEvent) => {
          this.widthCon += 10
        }).width('50%')
        Button('Image width-,' + this.widthCon).onClick((event: ClickEvent) => {
          this.widthCon -= 10
        }).width('50%')
      }.width('80%')

      Row() {
        Button('Image height+,' + this.heightCon).onClick((event: ClickEvent) => {
          this.heightCon += 10
        }).width('50%')
        Button('Image height-,' + this.heightCon).onClick((event: ClickEvent) => {
          this.heightCon -= 10
        }).width('50%')
      }.width('80%')

      Row() {
        Button('Span width+,' + this.widthSpan).onClick((event: ClickEvent) => {
          this.widthSpan += 10
        }).width('50%')
        Button('Span width-,' + this.widthSpan).onClick((event: ClickEvent) => {
          this.widthSpan -= 10
        }).width('50%')
      }.width('80%')

      Row() {
        Button('Span height+,' + this.heightSpan).onClick((event: ClickEvent) => {
          this.heightSpan += 10
        }).width('50%')
        Button('Span height-,' + this.heightSpan).onClick((event: ClickEvent) => {
          this.heightSpan -= 10
        }).width('50%')
      }.width('80%')

      Row() {
        Button('Span fontSize+,' + this.fontSize).onClick((event: ClickEvent) => {
          this.fontSize += 10
        }).width('50%')
        Button('Span fontSize-,' + this.fontSize).onClick((event: ClickEvent) => {
          this.fontSize -= 10
        }).width('50%')
      }.width('80%')

    }
  }
}