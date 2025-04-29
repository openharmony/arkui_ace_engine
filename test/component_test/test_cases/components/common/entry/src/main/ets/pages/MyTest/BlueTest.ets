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

import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function blurTest() {
  /*
  * image组件 blur属性
  * 找到画面id为imageBlur1，imageBlur1的image组件
  * 找到画面文本为ButtonBlur的Button组件
  * 获取mageBlur1的blur属性与期待值5比对
  * 获取mageBlur2的blur属性下的value参数与期待值5比对
  * 获取mageBlur2的blur属性下的option参数与期待值{ grayscale: [0, 0] }比对
  * 点击button1，变更mageBlur2的blur属性的option参数值为{ grayscale: [20, 80] }
  * 获取mageBlur2的blur属性下的option参数与期待值{ grayscale: [20, 80] }比对
  */
  defineTest('blurTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("blurTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageBlur1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageBlur2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBlur').enabled(true))
    let blur1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(blur1).$attrs.blur, 5)
    let blur2: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(blur2).$attrs.blur, 10)
    assertEqual(JSON.parse(blur2).$attrs.blur.options, {
      grayscale: [0, 0]
    })
    await button.tap()
    let blur3: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(blur3).$attrs.blur.options, {
      grayscale: [20, 80]
    })
  }, 0)
}