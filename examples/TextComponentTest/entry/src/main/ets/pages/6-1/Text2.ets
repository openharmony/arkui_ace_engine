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
struct TextSpanExample2 {
  @State widthCon: number = 200
  @State heightCon: number = 60
  @State backgroundColorAll: (string | number | Color | Resource)[] = [Color.Blue, "#fc0303", 0xFF0000, 'rgb(2, 184, 17)', $r('app.color.color_yellow')]
  @State backgroundColorStr: string[] = ['Blue', "#fc0303", "0xFF0000", 'rgb(2, 184, 17)', "$r('yellow')"]
  @State backgroundColorIndex: number = 0
  @State topLeft: number = 10
  @State topRight: number = 10
  @State bottomLeft: number = 10
  @State bottomRight: number = 10

  build() {
    Column({ space: 8 }) {

      Text('不设置color')
      Text() {
        Span('Span').textBackgroundStyle({ radius: { topLeft: this.topLeft, topRight: this.topRight, bottomLeft: this.bottomLeft, bottomRight: this.bottomRight} }).borderWidth(1)
        ImageSpan($r('app.media.app_icon')).width(60).height(60)
          .textBackgroundStyle({ radius: { topLeft: this.topLeft, topRight: this.topRight, bottomLeft: this.bottomLeft, bottomRight: this.bottomRight} }).borderWidth(1)
        ContainerSpan() {
          Span('ContainerSpan').fontSize('16fp').fontColor(Color.White)
        }.textBackgroundStyle({ radius: { topLeft: this.topLeft, topRight: this.topRight, bottomLeft: this.bottomLeft, bottomRight: this.bottomRight} })
      }.borderWidth(1)

      Row() {
        Button('topLeft+,' + this.topLeft).onClick((event: ClickEvent) => {
          this.topLeft += 5
        }).width('50%')
        Button('topLeft-,' + this.topLeft).onClick((event: ClickEvent) => {
          this.topLeft -= 5
        }).width('50%')
      }.width('80%')

      Row() {
        Button('topRight+,' + this.topRight).onClick((event: ClickEvent) => {
          this.topRight += 5
        }).width('50%')
        Button('topRight-,' + this.topRight).onClick((event: ClickEvent) => {
          this.topRight -= 5
        }).width('50%')
      }.width('80%')

      Row() {
        Button('bottomLeft+,' + this.bottomLeft).onClick((event: ClickEvent) => {
          this.bottomLeft += 5
        }).width('50%')
        Button('bottomLeft-,' + this.bottomLeft).onClick((event: ClickEvent) => {
          this.bottomLeft -= 5
        }).width('50%')
      }.width('80%')

      Row() {
        Button('bottomRight+,' + this.bottomRight).onClick((event: ClickEvent) => {
          this.bottomRight += 5
        }).width('50%')
        Button('bottomRight-,' + this.bottomRight).onClick((event: ClickEvent) => {
          this.bottomRight -= 5
        }).width('50%')
      }.width('80%')

      Text('不设置radius')
      Text() {
        Span('Span').textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex]}).borderWidth(1)
        ImageSpan($r('app.media.app_icon')).textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex]}).borderWidth(1)
        ContainerSpan()  {
          Span('ContainerSpan').fontSize('16fp').fontColor(Color.White)
        }.textBackgroundStyle({ color: this.backgroundColorAll[this.backgroundColorIndex] })
      }.borderWidth(1)

      Row() {
        Button('背景颜色:' + this.backgroundColorStr[this.backgroundColorIndex]).onClick(() => {
          this.backgroundColorIndex ++
          if (this.backgroundColorIndex > (this.backgroundColorAll.length - 1)) {
            this.backgroundColorIndex = 0
          }
        }).width('100%')
      }.width('80%')

    }
  }
}