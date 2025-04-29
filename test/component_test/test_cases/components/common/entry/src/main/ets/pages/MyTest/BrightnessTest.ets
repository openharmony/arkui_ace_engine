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

export default async function brightnessTest() {
  /*
  * canvas组件 brightness属性
  * 找到画面id为canvasBrightness1的canvas组件
  * 找到画面文本为ButtonBrightness1的Button组件
  * 获取canvas1的brightness属性与期待值2比对
  * 点击button1，变更canvas1的brightness属性与期待值-1比对
  */
  defineTest('brightnessTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("brightnessTestDemo running")
    let driver: Tester = Tester.create()
    let canvas1: Component = await driver.findComponent(Matcher.create().id('canvasBrightness1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBrightness1').enabled(true))
    let brightness1: string = await canvas1.getInspectorInfo()
    assertEqual(JSON.parse(brightness1).$attrs.brightness, 2)
    await button1.tap()
    let brightness2: string = await canvas1.getInspectorInfo()
    assertEqual(JSON.parse(brightness2).$attrs.brightness, -1)
  }, 0)
}