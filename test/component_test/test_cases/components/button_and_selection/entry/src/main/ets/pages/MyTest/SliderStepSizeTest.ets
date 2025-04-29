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

export default async function sliderStepSizeTest() {
  /*
  * Slider组件 StepSize属性
  * 找到画面id为sliderStepSize1，sliderStepSize2，sliderStepSize3的Slider组件
  * 找到画面文本为SliderStepSize的Button组件
  * 获取sliderStepSize1的StepSize属性与期待值'0.00vp'比对
  * 获取sliderStepSize2的StepSize属性与期待值'4.00vp'比对
  * 获取sliderStepSize3的StepSize属性与期待值'5.00px'比对
  * 点击button，变更sliderStepSize3的StepSize属性值为$r('app.string.slider_stepSize')
  * 获取sliderStepSize3的StepSize属性与期待值$r('app.string.slider_stepSize')比对
  */
  defineTest('sliderStepSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderStepSizeTestDemo running')
    let driver: Tester = Tester.create()
    let sliderStepSize1: Component = await driver.findComponent(Matcher.create().id('sliderStepSize1').enabled(true))
    let sliderStepSize2: Component = await driver.findComponent(Matcher.create().id('sliderStepSize2').enabled(true))
    let sliderStepSize3: Component = await driver.findComponent(Matcher.create().id('sliderStepSize3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderStepSize').enabled(true))

    let stepSize1: string = await sliderStepSize1.getInspectorInfo()
    assertEqual(JSON.parse(stepSize1).$attrs.stepSize, '0.00vp')

    let stepSize2: string = await sliderStepSize2.getInspectorInfo()
    assertEqual(JSON.parse(stepSize2).$attrs.stepSize, '4.00vp')

    let stepSize3: string = await sliderStepSize3.getInspectorInfo()
    assertEqual(JSON.parse(stepSize3).$attrs.stepSize, '5.00px')

    await button.tap()
    let stepSize4: string = await sliderStepSize3.getInspectorInfo()
    assertEqual(JSON.parse(stepSize4).$attrs.stepSize, $r('app.string.slider_stepSize'))
  }, 0)
}