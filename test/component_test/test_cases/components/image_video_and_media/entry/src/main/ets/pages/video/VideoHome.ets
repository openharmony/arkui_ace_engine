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
import { CommonButton } from '../../util/CommonButton';

@Entry
@Component
struct VideoHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('VideoHome')
          .padding('10vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'VideoAutoPlay', buttonUrl: 'pages/video/VideoAutoPlaySample' });
        CommonButton({ buttonName: 'VideoControls', buttonUrl: 'pages/video/VideoControlsSample' });
        CommonButton({ buttonName: 'VideoLoop', buttonUrl: 'pages/video/VideoLoopSample' });
        CommonButton({ buttonName: 'VideoMuted', buttonUrl: 'pages/video/VideoMutedSample' });
        CommonButton({ buttonName: 'VideoObjectFit_one', buttonUrl: 'pages/video/VideoObjectFitSample_one' });
        CommonButton({ buttonName: 'VideoObjectFit_three', buttonUrl: 'pages/video/VideoObjectFitSample_three' });
        CommonButton({ buttonName: 'VideoObjectFit_two', buttonUrl: 'pages/video/VideoObjectFitSample_two' });
      }
      .padding('10vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}