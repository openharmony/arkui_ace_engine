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

export default async function sliderStepColorTest() {
  /*
   * Slider组件 StepColor属性
   * 找到画面id为sliderStepColor1，sliderStepColor2，sliderStepColor3的Slider组件
   * 找到画面文本为SliderStepColor的Button组件
   * 获取sliderStepColor1的StepColor属性与期待值'#80FF64FF'比对
   * 获取sliderStepColor2的StepColor属性与期待值'#FFFFFFEE'比对
   * 获取sliderStepColor3的StepColor属性与期待值Color.Red比对
   * 点击button，变更sliderStepColor3的StepColor属性值为$r('sys.color.ohos_fa_activated')
   * 获取sliderStepColor3的StepColor属性与期待值$r('sys.color.ohos_fa_activated')比对
   */
  defineTest('sliderStepColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderStepColorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderStepColor1: Component = await driver.findComponent(Matcher.create().id('sliderStepColor1').enabled(true))
    let sliderStepColor2: Component = await driver.findComponent(Matcher.create().id('sliderStepColor2').enabled(true))
    let sliderStepColor3: Component = await driver.findComponent(Matcher.create().id('sliderStepColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderStepColor').enabled(true))

    let stepColor1: string = await sliderStepColor1.getInspectorInfo()
    assertEqual(JSON.parse(stepColor1).$attrs.stepColor, '#80FF64FF')

    let stepColor2: string = await sliderStepColor2.getInspectorInfo()
    assertEqual(JSON.parse(stepColor2).$attrs.stepColor, '#FFFFFFEE')

    let stepColor3: string = await sliderStepColor3.getInspectorInfo()
    assertEqual(JSON.parse(stepColor3).$attrs.stepColor.toLowerCase(), Color.Red)

    await button.tap()
    let stepColor4: string = await sliderStepColor3.getInspectorInfo()
    assertEqual(JSON.parse(stepColor4).$attrs.stepColor, $r('sys.color.ohos_fa_activated'))
  }, 0)
}