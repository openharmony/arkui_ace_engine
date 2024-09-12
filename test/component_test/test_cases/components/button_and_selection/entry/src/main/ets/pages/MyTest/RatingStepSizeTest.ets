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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function ratingStepSizeTest() {
  /*
   * Rating组件 StepSize属性
   * 找到画面id为ratingStepSize1，ratingStepSize2的Rating组件
   * 找到画面文本为RatingStepSize的Button组件
   * 获取ratingStepSize1的StepSize属性与期待值'0.500000'比对
   * 获取ratingStepSize2的StepSize属性与期待值'0.200000'比对
   * 点击button，变更ratingStepSize2的StepSize属性值为'5.000000'
   * 获取ratingStepSize2的StepSize属性与期待值'5.000000'比对
   */
  defineTest('ratingStepSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('ratingStepSizeTestDemo running')
    let driver: Tester = Tester.create()
    let ratingStepSize1: Component = await driver.findComponent(Matcher.create().id('ratingStepSize1').enabled(true))
    let ratingStepSize2: Component = await driver.findComponent(Matcher.create().id('ratingStepSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RatingStepSize').enabled(true))

    let stepSize1: string = await ratingStepSize1.getInspectorInfo()
    assertEqual(JSON.parse(stepSize1).$attrs.stepSize, '0.500000')

    let stepSize2: string = await ratingStepSize2.getInspectorInfo()
    assertEqual(JSON.parse(stepSize2).$attrs.stepSize, '0.200000')

    await button.tap()
    let stepSize3: string = await ratingStepSize2.getInspectorInfo()
    assertEqual(JSON.parse(stepSize3).$attrs.stepSize, '5.000000')
  }, 0)
}