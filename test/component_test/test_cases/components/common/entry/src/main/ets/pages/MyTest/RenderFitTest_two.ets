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

export default async function renderFitTest_two() {
  /*
 * ellipse组件 renderFit属性
 * 找到画面id为ellipseRenderFit1，ellipseRenderFit2,ellipseRenderFit3,ellipseRenderFit4的ellipse组件
 * 找到画面文本为EllipseRenderFit1、EllipseRenderFit2的Button组件
 * 获取ellipseRenderFit1的renderFit属性与期待值RenderFit.TOP_RIGHT比对
 * 获取ellipseRenderFit2的renderFit属性与期待值RenderFit.BOTTOM_LEFT比对
 * 获取ellipseRenderFit3的renderFit属性与期待值RenderFit.BOTTOM_RIGHT比对
 * 获取ellipseRenderFit4的renderFit属性与期待值RenderFit.RESIZE_FILL比对
 * 点击button1，变更ellipseRenderFit3的renderFit属性值为RenderFit.RESIZE_CONTAIN
 * 获取ellipseRenderFit3的renderFit属性与期待值RenderFit.RESIZE_CONTAIN比对
 * 点击button2，变更ellipseRenderFit4的renderFit属性值为RenderFit.RESIZE_CONTAIN_TOP_LEFT
 * 获取ellipseRenderFit4的renderFit属性与期待值RenderFit.RESIZE_CONTAIN_TOP_LEFT比对
 */
  defineTest('renderFitTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("renderFitTest_twoDemo running")
    let driver: Tester = Tester.create()
    let ellipseRenderFit1: Component =
      await driver.findComponent(Matcher.create().id('ellipseRenderFit1').enabled(true))
    let ellipseRenderFit2: Component =
      await driver.findComponent(Matcher.create().id('ellipseRenderFit2').enabled(true))
    let ellipseRenderFit3: Component =
      await driver.findComponent(Matcher.create().id('ellipseRenderFit3').enabled(true))
    let ellipseRenderFit4: Component =
      await driver.findComponent(Matcher.create().id('ellipseRenderFit4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonEllipseRenderFit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonEllipseRenderFit2').enabled(true))
    let renderFit1: string = await ellipseRenderFit1.getInspectorInfo()
    assertEqual(JSON.parse(renderFit1).$attrs.renderFit, 'RenderFit.TOP_RIGHT')
    let renderFit2: string = await ellipseRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit2).$attrs.renderFit, 'RenderFit.BOTTOM_LEFT')
    let renderFit3: string = await ellipseRenderFit3.getInspectorInfo()
    assertEqual(JSON.parse(renderFit3).$attrs.renderFit, 'RenderFit.BOTTOM_RIGHT')
    let renderFit4: string = await ellipseRenderFit4.getInspectorInfo()
    assertEqual(JSON.parse(renderFit4).$attrs.renderFit, 'RenderFit.RESIZE_FILL')
    await button1.tap()
    let renderFit5: string = await ellipseRenderFit3.getInspectorInfo()
    assertEqual(JSON.parse(renderFit5).$attrs.renderFit, 'RenderFit.RESIZE_CONTAIN')
    await button2.tap()
    let renderFit6: string = await ellipseRenderFit4.getInspectorInfo()
    assertEqual(JSON.parse(renderFit6).$attrs.renderFit, 'RenderFit.RESIZE_CONTAIN_TOP_LEFT')
  }, 0)
}