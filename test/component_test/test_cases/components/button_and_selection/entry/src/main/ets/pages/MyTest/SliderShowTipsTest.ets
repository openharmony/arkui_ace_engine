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

import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function sliderShowTipsTest() {
  /*
   * Slider组件 ShowTips属性
   * 找到画面id为sliderShowTips1，sliderShowTips2，sliderShowTips3的Slider组件
   * 找到画面文本为SliderShowTips1的Button组件
   * 获取sliderShowTips1的ShowTips属性与期待值false比对
   * 获取sliderShowTips2的ShowTips属性与期待值true比对
   * 获取sliderShowTips2的ShowTips属性与期待值'hello'比对
   * 获取sliderShowTips3的ShowTips属性与期待值true比对
   * 获取slider3的ShowTips属性与期待值$r('app.string.app_name')比对
   * 点击button，变更slider1的ShowTips属性值为true
   * 获取slider1的ShowTips属性与期待值true比对
   */
  defineTest('sliderShowTipsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderShowTipsTestDemo running')
    let driver: Tester = Tester.create()
    let sliderShowTips1: Component = await driver.findComponent(Matcher.create().id('sliderShowTips1').enabled(true))
    let sliderShowTips2: Component = await driver.findComponent(Matcher.create().id('sliderShowTips2').enabled(true))
    let sliderShowTips3: Component = await driver.findComponent(Matcher.create().id('sliderShowTips3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderShowTips1').enabled(true))

    let showTips1: string = await sliderShowTips1.getInspectorInfo()
    assertFalse(JSON.parse(showTips1).$attrs.showTips)

    let showTips2: string = await sliderShowTips2.getInspectorInfo()
    assertTrue(JSON.parse(showTips2).$attrs.showTips)
    assertEqual(JSON.parse(showTips2).$attrs.showTips.content, 'hello')

    let showTips3: string = await sliderShowTips3.getInspectorInfo()
    assertTrue(JSON.parse(showTips3).$attrs.showTips)
    assertEqual(JSON.parse(showTips3).$attrs.showTips.content, $r('app.string.app_name'))

    await button.tap()
    let showTips4: string = await sliderShowTips1.getInspectorInfo()
    assertTrue(JSON.parse(showTips4).$attrs.showTips)
  })
}