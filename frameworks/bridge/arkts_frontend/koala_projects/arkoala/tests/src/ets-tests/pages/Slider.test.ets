/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
@Entry
@Component
struct SliderTest {
  Value1: number = 0
  Value2: number = 60
  Value3: number = 20
  Value4: number = 5

  build() {
    Column() {
      Slider({ value: this.Value1 })
      Slider({ value: this.Value2, min: 50, max: 80, step: 3, style: SliderStyle.InSet })
      Slider({ value: this.Value3, min: 10, max: 200, step: 10, style: SliderStyle.OutSet, reverse: true }).showTips(true, 'First Tip')
      .trackThickness(10).blockColor(Color.Black).trackColor(Color.Red).selectedColor(Color.Green)
      Slider({ value: this.Value4, max: 10, style: SliderStyle.InSet, reverse: true })
      .trackThickness(50).showSteps(false).showTips(false).blockColor(Color.Black).trackColor(Color.Red).selectedColor(Color.Green)
      Slider({ value: this.Value1, direction: Axis.Horizontal })
      .borderColor(Color.Black).borderWidth(2).borderRadius(5)
      .blockSize({ width: '15%', height: '33%' }).stepSize(13)
      .blockBorderColor(Color.Yellow).blockBorderWidth(4).stepColor(Color.Red).trackBorderRadius('2%')
      Slider({ value: this.Value2, min: 50, max: 80, step: 3, style: SliderStyle.InSet, direction: Axis.Vertical })
      Slider({ value: this.Value3, min: 10, max: 200, step: 10, style: SliderStyle.OutSet, reverse: false, direction: Axis.Horizontal })
      .trackThickness(10).blockColor(Color.Black).trackColor(Color.Red).selectedColor(Color.Green)
      Slider({ value: this.Value4, max: 10, style: SliderStyle.InSet, reverse: true, direction: Axis.Vertical })
      .trackThickness(50).showSteps(true).showTips(true, 'Second Tip').blockColor(Color.Black).trackColor(Color.Red).selectedColor(Color.Green)
    }
  }
}
