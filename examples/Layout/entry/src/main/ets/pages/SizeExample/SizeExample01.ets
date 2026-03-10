/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
struct SizeExample1 {
  @State widthList: (Length | undefined | null)[] = [80, 'auto', '80px', '80vp', '80fp', '80lpx' ,'40%' ,'80',
    undefined, $r('app.string.size'), null, $r('app.string.string')]
  @State widthIndex: number = 0
  @State heightList: (Length | undefined | null)[] = [80, 'auto', '80px', '80vp', '80fp', '80lpx' ,'40%' ,'80',
    undefined, $r('app.string.size'), null, $r('app.string.string')]
  @State heightIndex: number = 0

  build() {
    Column({ space: 8 }) {
      Row() {
        Button('width:' + this.widthList[this.widthIndex]).onClick(() => {
          this.widthIndex ++
          if (this.widthIndex > (this.widthList.length - 1)) {
            this.widthIndex = 0
          }
        }).width('100%')
      }.width('80%')

      Row() {
        Button('height:' + this.heightList[this.heightIndex]).onClick(() => {
          this.heightIndex ++
          if (this.heightIndex > (this.heightList.length - 1)) {
            this.heightIndex = 0
          }
        }).width('100%')
      }.width('80%')
      Row() {
        Row() {
          Row()
            .size({ width: '100%', height: '100%' })
            .backgroundColor(Color.Yellow)
        }
        .width(this.widthList[this.widthIndex])
        .height(this.heightList[this.heightIndex])
        .padding({
          top: 5,
          left: 10,
          bottom: 15,
          right: 20
        })
        .margin(20)
        .backgroundColor(Color.White)
      }.backgroundColor(Color.Blue)

    }
  }
}