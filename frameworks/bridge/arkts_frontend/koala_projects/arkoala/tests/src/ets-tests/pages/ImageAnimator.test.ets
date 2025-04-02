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
struct ImageAnimatorTest {
    build() {
        ImageAnimator()
        .images([
            {
              src: "/common/img1.png",
              width: 100,
              height: 100,
              top: 2,
              left: 2,
              duration: 1000
            },
            {
              src: "/common/img2.png"
            }
          ])
        .state(AnimationStatus.Initial)
        .duration(2000)
        .reverse(false)
        .fixedSize(false)
        //TODO: .fillMode(FillMode.Forwards) error: 'FillMode' only refers to a type, but is being used as a value here.
        .iterations(17)
        .width(100)
        .height(100)

    }
}
