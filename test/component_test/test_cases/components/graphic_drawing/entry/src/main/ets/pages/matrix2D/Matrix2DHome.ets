/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { CommonButton } from '../../util/CommonButton'

@Entry
@Component
struct Matrix2DHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'Matrix2DScaleX', buttonUrl: 'pages/matrix2D/Matrix2DScaleXSample' })
        CommonButton({ buttonName: 'Matrix2DScaleY', buttonUrl: 'pages/matrix2D/Matrix2DScaleYSample' })
        CommonButton({ buttonName: 'Matrix2DRotateX', buttonUrl: 'pages/matrix2D/Matrix2DRotateXSample' })
        CommonButton({ buttonName: 'Matrix2DRotateY', buttonUrl: 'pages/matrix2D/Matrix2DRotateYSample' })
        CommonButton({ buttonName: 'Matrix2DTranslateX', buttonUrl: 'pages/matrix2D/Matrix2DTranslateXSample' })
        CommonButton({ buttonName: 'Matrix2DTranslateY', buttonUrl: 'pages/matrix2D/Matrix2DTranslateYSample' })
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}