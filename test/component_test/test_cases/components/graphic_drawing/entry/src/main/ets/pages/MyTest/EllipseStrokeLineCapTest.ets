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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function ellipseStrokeLineCapTest() {
  /*
   * Ellipse组件 strokeLineCapt属性
   * 找到画面id为ellipseStrokeLineCapt1,ellipseStrokeLineCapt2的Ellipse组件
   * 找到画面文本为EllipseStrokeLineCapt的Button组件
   * 获取ellipse1的strokeLineCapt属性与期待值LineCapStyle.Butt比对
   * 获取ellipse2的strokeLineCapt属性与期待值LineCapStyle.Round比对
   * 点击button，变更ellipse2的strokeLineCapt属性值为LineCapStyle.Square
   * 获取ellipse2的strokeLineCapt属性与期待值LineCapStyle.Square比对
   */
  defineTest('ellipseStrokeLineCapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ellipseStrokeLineCapTestDemo running")

    let driver: Tester = Tester.create()
    let ellipse1: Component = await driver.findComponent(Matcher.create().id('ellipseStrokeLineCapt1').enabled(true))
    let ellipse2: Component = await driver.findComponent(Matcher.create().id('ellipseStrokeLineCapt2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('EllipseStrokeLineCapt').enabled(true))

    let strokeLineCap1: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap1).$attrs.strokeLineCap, 'LineCapStyle.Butt')

    let strokeLineCap2: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap2).$attrs.strokeLineCap, 'LineCapStyle.Round')

    await button.tap()
    let strokeLineCap3: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(strokeLineCap3).$attrs.strokeLineCap, 'LineCapStyle.Square')
  }, 0)
}