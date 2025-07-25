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
struct MarqueeTest {
    @State start: boolean = false
    private fromStart: boolean = true
    private step: number = 50
    private loop: number = Number.POSITIVE_INFINITY
    private src: string = "Running Marquee starts rolling"

    build() {
        Marquee({
            start: this.start,
            step: this.step,
            loop: this.loop,
            fromStart: this.fromStart,
            src: this.src
          })
        .fontColor(Color.White)
        .fontSize("18fp")
        .allowScale(false)
        .fontWeight(17)
        .fontFamily("testString")
        //TODO .onStart(() => {})
        //TODO .onBounce(() => {})
        //TODO .onFinish(() => {})
        Marquee({
            start: this.start,
            step: this.step,
            loop: 100,
            fromStart: this.fromStart,
            src: this.src
          })
        .fontColor('#FF00AA')
        .fontSize(20)
        .allowScale(true)
        .fontWeight(FontWeight.Bolder)
        .fontFamily("testString")

    }
}
