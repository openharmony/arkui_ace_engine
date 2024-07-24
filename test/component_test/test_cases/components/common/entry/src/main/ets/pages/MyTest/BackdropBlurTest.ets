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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function backdropBlurTest() {
  /*
  * button组件 backdropBlur属性
  * 找到画面id为buttonBackdropBlur1的button组件
  * 找到画面文本为ButtonBackdropBlur2的Button组件
  * 获取buttonBackdropBlur1的backdropBlur属性与期待值0比对
  * 点击button1，变更buttonBackdropBlur1的backdropBlur属性值为255
  * 获取buttonBackdropBlur1的backdropBlur属性与期待值255比对
  */
  defineTest('backdropBlurTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("backdropBlurTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().id('buttonBackdropBlur1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBackdropBlur2').enabled(true))
    let backdropBlur1: string = await button1.getInspectorInfo()
    assertEqual(JSON.parse(backdropBlur1).$attrs.backdropBlur, 0)

    await button2.tap()
    let backdropBlur2: string = await button1.getInspectorInfo()
    assertEqual(JSON.parse(backdropBlur2).$attrs.backdropBlur, 255)
  }, 0)
}