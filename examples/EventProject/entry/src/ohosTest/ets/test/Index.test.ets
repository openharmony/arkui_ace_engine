/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { describe, it, expect, beforeAll, Level } from '@ohos/hypium';
// 导入测试依赖kit
import { abilityDelegatorRegistry, Driver, ON, MouseButton, Component, MatchPattern, Point, On } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';
import resource from '../../../main/ets/common/resource';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { KeyCode } from '@kit.InputKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

const TAG = '[Sample_Eventproject]';
const DOMAIN = 0xF811;
const BUNDLE = 'Eventproject_';
// $r('app.string.xxx')需要替换为开发者所需的资源文件

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      let driver = Driver.create();
      await driver.delayMs(1000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      console.info('get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    /**
     * @tc.number UiTest_001
     * @tc.name testSingleGestureTap
     * @tc.desc 测试点击手势示例
     */
    it('testSingleGestureTap', 0, async (done: Function) => {
      console.info('uitest: testSingleGestureTap begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('gesture', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      // 请将$r('app.string.singlegesture_Index_TapGesture_title')替换为实际资源文件，在本示例中该资源文件的value值为"点击手势"
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.singlegesture_Index_TapGesture_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let button2 = await driver.findComponent(ON.text('twice', MatchPattern.CONTAINS));
      await button2.doubleClick();
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testSingleGestureTap end');
      done();
    })

    /**
     * @tc.number UiTest_002
     * @tc.name testSingleGestureLong
     * @tc.desc 测试长按手势示例
     */
    it('testSingleGestureLong', 0, async (done: Function) => {
      console.info('uitest: testSingleGestureLong begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('gesture', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      // 请将$r('app.string.singlegesture_Index_LongPress_title')替换为实际资源文件，在本示例中该资源文件的value值为"长按手势"
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.singlegesture_Index_LongPress_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let button2 = await driver.findComponent(ON.text('Long', MatchPattern.CONTAINS));
      await button2.longClick();
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testSingleGestureLong end');
      done();
    })

    /**
     * @tc.number UiTest_003
     * @tc.name testSingleGestureJudge
     * @tc.desc 测试手势拦截示例
     */
    it('testSingleGestureJudge', 0, async (done: Function) => {
      console.info('uitest: testSingleGestureJudge begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('GestureJudge', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      // 请将$r('app.string.gesture_Index_GestureJudge_title')替换为实际资源文件，在本示例中该资源文件的value值为"手势拦截"
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.gesture_Index_GestureJudge_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.delayMs(1000);
      await driver.pressBack();
      console.info('uitest: testSingleGestureJudge end');
      done();
    })

    /**
     * @tc.number UiTest_004
     * @tc.name testSingleGestureTouch
     * @tc.desc 测试点击事件示例
     */
    it('testSingleGestureTouch', 0, async (done: Function) => {
      console.info('uitest: testSingleGestureTouch begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('TouchEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      // 请将$r('app.string.Touch_Index_ClickEvent_title')替换为实际资源文件，在本示例中该资源文件的value值为"点击事件"
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Touch_Index_ClickEvent_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let button = await driver.findComponent(ON.text('show', MatchPattern.CONTAINS));
      await button.click();
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testSingleGestureTouch end');
      done();
    })

    /**
     * @tc.number UiTest_005
     * @tc.name testOnClickGesture
     * @tc.desc 测试点击事件示例
     */
    it('testOnClickGesture', 0, async (done: Function) => {
      console.info('uitest: testOnClickGesture begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('gesture', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      // 请将$r('app.string.singlegesture_Index_Click_title')替换为实际资源文件，在本示例中该资源文件的value值为"点击事件"
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.singlegesture_Index_Click_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testOnClickGesture end');
      done();
    })

    /**
     * @tc.number UiTest_006
     * @tc.name testFocusActive
     * @tc.desc 测试聚焦示例
     */
    it('testFocusActive', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.waitForComponent(ON.text('FocusEvent', MatchPattern.CONTAINS), 1000);
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Pages_Index_Focus_Active_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2054);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_007
     * @tc.name testDeviceOnKey_1
     * @tc.desc 测试支持键盘输入事件
     */
    it('testDeviceOnKey_1', Level.LEVEL1, async (done: Function) => {
      console.info('uitest: testDeviceOnKey_1 begin');
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_1 begin");
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('DeviceEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.delayMs(1000);
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_index_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_OnKey_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(KeyCode.KEYCODE_SEARCH);
      await driver.triggerKey(KeyCode.KEYCODE_ENTER);
      await driver.triggerKey(KeyCode.KEYCODE_CTRL_LEFT);
      await driver.triggerKey(KeyCode.KEYCODE_CTRL_RIGHT);
      await driver.triggerKey(KeyCode.KEYCODE_SHIFT_LEFT);
      await driver.triggerKey(KeyCode.KEYCODE_A);
      await driver.triggerKey(KeyCode.KEYCODE_Z);
      let button = await driver.findComponent(ON.text('onKeyEvent', MatchPattern.CONTAINS));
      await button.click();

      await driver.delayMs(2000);
      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_1 end");
      done();
    })

    /**
     * @tc.number UiTest_008
     * @tc.name testDeviceOnKey_2
     * @tc.desc 测试支持键盘输入事件
     */
    it('testDeviceOnKey_2', Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_2 begin");
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('DeviceEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.delayMs(1000);
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_index_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Key_Event')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(KeyCode.KEYCODE_SEARCH);
      await driver.triggerKey(KeyCode.KEYCODE_ENTER);
      await driver.triggerKey(KeyCode.KEYCODE_CTRL_LEFT);
      await driver.triggerKey(KeyCode.KEYCODE_CTRL_RIGHT);
      await driver.triggerKey(KeyCode.KEYCODE_SHIFT_LEFT);
      await driver.triggerKey(KeyCode.KEYCODE_A);
      await driver.triggerKey(KeyCode.KEYCODE_Z);
      let button = await driver.findComponent(ON.text('onKeyEvent', MatchPattern.CONTAINS));
      await button.click();

      await driver.delayMs(2000);
      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_2 end");
      done();
    })

    /**
     * @tc.number UiTest_009
     * @tc.name testDeviceOnKey_3
     * @tc.desc 测试支持键盘输入事件
     */
    it('testDeviceOnKey_3', Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_3 begin");
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('DeviceEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.delayMs(1000);
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_index_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Key_PreIme')), MatchPattern.CONTAINS));
      await button_list1.click();

      //已进入测试界面
      let textArea = await driver.findComponent(ON.type('Search'));
      expect(textArea === null).assertFalse();
      await textArea.inputText('this is content');
      await driver.triggerKey(KeyCode.KEYCODE_DPAD_LEFT);

      await driver.pressBack();
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_3 end");
      done();
    })

    /**
     * @tc.number UiTest_010
     * @tc.name testDeviceOnKey_4
     * @tc.desc 测试支持键盘输入事件
     */
    it('testDeviceOnKey_4', Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_4 begin");
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('DeviceEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.delayMs(1000);
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_index_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.OnKeyDistributeEvent_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      button_list1 = await driver.findComponent(ON.id('button1'));
      expect(button_list1 === null).assertFalse();
      await button_list1.click();
      await driver.triggerKey(KeyCode.KEYCODE_SEARCH);

      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_4 end");
      done();
    })

    /**
     * @tc.number UiTest_011
     * @tc.name testDeviceOnKey_5
     * @tc.desc 测试支持键盘输入事件
     */
    it('testDeviceOnKey_5', Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_5 begin");
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('DeviceEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.delayMs(1000);
      let button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.Device_index_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      button_list1 = await driver.findComponent(ON.text(resource.resourceToString($r('app.string.OnKeyPreImeCommit_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let textArea = await driver.findComponent(ON.type('TextArea'));
      expect(textArea === null).assertFalse();
      await textArea.inputText('this is content');
      await driver.triggerKey(KeyCode.KEYCODE_ENTER);

      await driver.pressBack();
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + "ProgressTest: testDeviceOnKey_5 end");
      done();
    })

    /**
     * @tc.number UiTest_012
     * @tc.name testPanCombination
     * @tc.desc 测试滑动事件示例
     */
    it('testPanCombination', 0, async (done: Function) => {
      console.info('uitest: testPanCombination begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('gesture', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      // 请将$r('app.string.singlegesture_Index_Pancom_title')替换为实际资源文件，在本示例中该资源文件的value值为"滑动手势"
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.singlegesture_Index_Pancom_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.delayMs(1000);
      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testPanCombination end');
      done();
    })

    /**
     * @tc.number UiTest_013
     * @tc.name FocusOnClick
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFocusOnClick', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FocusOnClick_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let button = await driver.findComponent(ON.text('Button', MatchPattern.CONTAINS));
      await button.click();
      let button1 = await driver.findComponent(ON.text('count is odd number', MatchPattern.CONTAINS));
      await button1.click();
      let button2 = await driver.findComponent(ON.text('count is even number', MatchPattern.CONTAINS));
      await button2.click();
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_014
     * @tc.name FocusScopeId
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFocusScopeId', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FocusScopeId_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2049);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_015
     * @tc.name FocusScopePriorityPrevious
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFocusScopePriorityPrevious', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FocusScopePriorityPrevious_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_016
     * @tc.name FocusTransfer
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFocusTransfer', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FocusTransfer_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      let button = await driver.findComponent(ON.text('Button 1', MatchPattern.CONTAINS));
      await button.click();
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_017
     * @tc.name FocusTraversalGuidelines
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFocusTraversalGuidelines', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FocusTraversalGuidelines_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2014);
      await driver.triggerKey(2012);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_018
     * @tc.name FrojectAreaFocusFlex
     * @tc.desc 测试焦点传递事件示例
     */
    it('testFrojectAreaFocusFlex', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_FrojectAreaFocusFlex_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_019
     * @tc.name NextFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testNextFocus', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_NextFocus_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_020
     * @tc.name OnFocusOnBlurEvents
     * @tc.desc 测试焦点传递事件示例
     */
    it('testOnFocusOnBlurEvents', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_OnFocusOnBlurEvents_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_021
     * @tc.name ProjectionBasedFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testProjectionBasedFocus', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_ProjectionBasedFocus_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_022
     * @tc.name ProjectionBasedFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testRequestFocus', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_RequestFocus_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_023
     * @tc.name ScopeFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testScopeFocus', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Focus_Index_ScopeFocus_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      let button = await driver.findComponent(ON.text('Button1', MatchPattern.CONTAINS));
      await button.click();
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_024
     * @tc.name TabIndex
     * @tc.desc 测试焦点传递事件示例
     */
    it('testTabIndex', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Tab_Index_TabIndex_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_025
     * @tc.name TabIndexFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testTabIndexFocus', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Tab_Index_TabIndexFocus_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2013);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })

    /**
     * @tc.number UiTest_026
     * @tc.name TabIndexFocus
     * @tc.desc 测试焦点传递事件示例
     */
    it('testTabStop', 0, async (done: Function) => {
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('FocusEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      let scrollBar: Component = await driver.findComponent(ON.type('Scroll'));
      let button_list1 = await scrollBar.scrollSearch(ON.text(resource.resourceToString($r('app.string.Tab_Index_TabStop_title')), MatchPattern.CONTAINS));
      await button_list1.click();
      //已进入测试界面
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2016);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.triggerKey(2049);
      await driver.pressBack();
      await driver.pressBack();
      done();
    })
  })
}