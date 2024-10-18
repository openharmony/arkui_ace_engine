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

export default async function renderFitTest_one() {
  /*
  * text,circle组件 renderFit属性
  * 找到画面id为textRenderFit1，textRenderFit2,circleRenderFit1,circleRenderFit2的text和circle组件
  * 找到画面文本为CircleRenderFit1、CircleRenderFit2的Button组件
  * 获取textRenderFit1的renderFit属性与期待值RenderFit.CENTER比对
  * 获取textRenderFit2的renderFit属性与期待值RenderFit.TOP比对
  * 获取circleRenderFit1的renderFit属性与期待值RenderFit.BOTTOM比对
  * 获取circleRenderFit2的renderFit属性与期待值RenderFit.LEFT比对
  * 点击button1，变更circleRenderFit1的renderFit属性值为RenderFit.RIGHT
  * 获取circleRenderFit1的renderFit属性与期待值RenderFit.TOP_LEFT比对
  * 点击button2，变更circleRenderFit2的renderFit属性值为RenderFit.TOP_LEFT
  * 获取circleRenderFit2的renderFit属性与期待值RenderFit.TOP_LEFT比对
  */
  defineTest('renderFitTest_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("renderFitTest_one running")
    let driver: Tester = Tester.create()
    let textRenderFit1: Component = await driver.findComponent(Matcher.create().id('textRenderFit1').enabled(true))
    let textRenderFit2: Component = await driver.findComponent(Matcher.create().id('textRenderFit2').enabled(true))
    let circleRenderFit1: Component = await driver.findComponent(Matcher.create().id('circleRenderFit1').enabled(true))
    let circleRenderFit2: Component = await driver.findComponent(Matcher.create().id('circleRenderFit2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonCircleRenderFit1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonCircleRenderFit2').enabled(true))
    let renderFit1: string = await textRenderFit1.getInspectorInfo()
    assertEqual(JSON.parse(renderFit1).$attrs.renderFit, 'RenderFit.CENTER')
    let renderFit2: string = await textRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit2).$attrs.renderFit, 'RenderFit.TOP')
    let renderFit3: string = await circleRenderFit1.getInspectorInfo()
    assertEqual(JSON.parse(renderFit3).$attrs.renderFit, 'RenderFit.BOTTOM')
    let renderFit4: string = await circleRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit4).$attrs.renderFit, 'RenderFit.LEFT')
    await button1.tap()
    let renderFit5: string = await circleRenderFit1.getInspectorInfo()
    assertEqual(JSON.parse(renderFit5).$attrs.renderFit, 'RenderFit.RIGHT')
    await button2.tap()
    let renderFit6: string = await circleRenderFit2.getInspectorInfo()
    assertEqual(JSON.parse(renderFit6).$attrs.renderFit, 'RenderFit.TOP_LEFT')
  }, 0)
}