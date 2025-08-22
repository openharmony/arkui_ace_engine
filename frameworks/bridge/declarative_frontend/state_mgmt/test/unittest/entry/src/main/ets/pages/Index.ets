/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { TestStats } from '../../lib/testStats'
import { PageController } from '../../lib/pageController'
import router from '@system.router'

@Entry
@Component
struct Parent {
  @State finalResult: string = "Pending..."
  @State finalResultsString: string = ""

  reportFinal = (): void => {
    this.finalResult = TestStats.isAllPassed() ? "PASSED" : "FAILED";
    this.finalResultsString = TestStats.getFinalReport();
    if (TestStats.isAllPassed()) {
      console.log(TestStats.getFinalReport(true));
    } else {
      console.error(TestStats.getFinalReport(true));
    }
  }

  aboutToAppear() {
    // Start after 200 ms to allow UI to start.
    setTimeout(() => {
      PageController.registerPages([
        'pages/v1_tests',
        'pages/v2_tests',
        // Add more pages if needed
      ])
      PageController.start(this.reportFinal)
    }, 200)
  }

  build() {
    Column() {
      Column() {
        Text(`All: ${this.finalResult}`)
          .fontSize(50)
      }.height(60)

      Scroll() {
        Column() {
          Text(this.finalResultsString)
            .width(385)
            .fontSize(14)
            .lineHeight(20)
            .textAlign(TextAlign.Start)
            .maxLines(-1)
            .textOverflow({ overflow: TextOverflow.Clip })
        }
      }.height(700) // Set the visible scrollable area height
    }
  }
}