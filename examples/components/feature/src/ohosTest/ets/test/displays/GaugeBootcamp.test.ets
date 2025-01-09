import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  swipeColumn,
  ToggleClick
} from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'GaugeBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function GaugeBootcampTest() {

  describe('GaugeBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);
        console.info(TAG + 'GaugeBootcamp001' + ' begin');

        let atomDisplays:Component = await driver.findComponent(ON.text('展示类'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems:Component[] = await driver.findComponents(ON.type('ListItem'))
        let width:Point = await ListItems[0].getBoundsCenter()
        let width2:Point = await ListItems[7].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch:Component = await driver.findComponent(ON.text('数据量规图/gauge'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons:Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    /**
     * 每条用例结束向下滑动
     */
    afterEach(async () => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
      let radio:Component[] = await driver.findComponents(ON.type('Radio').within(ON.type('Scroll')).clickable())
      let slider:Component= await driver.findComponent(ON.type('Slider').within(ON.type('Scroll')).scrollable())
      let Button:Component[] = await driver.findComponents(ON.type('Button').within(ON.type('Scroll')).clickable())

      if (!radio && !slider && !Button) {
        await swipeColumn()
      }

    })

    /**
     * 测试组件show.ChildComponents支持设置包含单个子组件为true且获取属性正确
     */
    it('ArkUI_Gauge_001 ', 0, async (done: Function) => {
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
      })

      done();

    })

    /**
     * 测试组件show.ChildComponents支持设置包含单个子组件为false且获取属性正确
     */
    it('ArkUI_Gauge_002 ', 0, async (done: Function) => {
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
      })

      done();

    })

    /**
     * 测试组件value支持设置量规图的数据值且获取属性正确
     */
    it('ArkUI_Gauge_003 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件min支持设置当前数据段最小值且获取属性正确
     */
    it('ArkUI_Gauge_004 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('min', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('min', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件max支持设置当前数据段最大值且获取属性正确
     */
    it('ArkUI_Gauge_005 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('max', JsonType.value),
        ],
        assertEqual: '400.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('max', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      done();

    })

    /**
     * 测试组件startAngle支持设置起始角度位置且获取属性正确
     */
    it('ArkUI_Gauge_006 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('startAngle', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('startAngle', JsonType.value),
        ],
        assertEqual: '0.00'
      })

      done();

    })

    /**
     * 测试组件endAngle支持设置终止角度位置且获取属性正确
     */
    it('ArkUI_Gauge_007 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('endAngle', JsonType.value),
        ],
        assertEqual: '100.00'
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('endAngle', JsonType.value),
        ],
        assertEqual: '360.00'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Gauge_008 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Gauge_009 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Gauge_010 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Gauge_011 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Gauge_012 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    /**
     * 测试组件colors支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Gauge_013 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colors', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    /**
     * 测试组件strokeWidth支持设置环形量规图的环形厚度且获取属性正确
     */
    it('ArkUI_Gauge_014 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '4.00vp'
      })

      done();

    })

    /**
     * 测试组件description支持设置说明内容为true且获取属性正确
     */
    it('ArkUI_Gauge_015 ', 0, async (done: Function) => {
      // 取不到 description值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
      })

      done();

    })

    /**
     * 测试组件description支持设置说明内容为false且获取属性正确
     */
    it('ArkUI_Gauge_016 ', 0, async (done: Function) => {
      // 取不到 description值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
      })

      done();

    })

    /**
     * 测试组件trackShadow.radius支持设置投影模糊半径且获取属性正确
     */
    it('ArkUI_Gauge_017 ', 0, async (done: Function) => {


      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '50.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '20.000000'
      })

      done();

    })

    /**
     * 测试组件trackShadow.OffsetX支持设置X轴的偏移量且获取属性正确
     */
    it('ArkUI_Gauge_018 ', 0, async (done: Function) => {


      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '15.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '5.000000'
      })

      done();

    })

    /**
     * 测试组件trackShadow.OffsetY支持设置Y轴的偏移量且获取属性正确
     */
    it('ArkUI_Gauge_019 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '15.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '5.000000'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为手机图标显示且获取属性正确
     */
    it('ArkUI_Gauge_020 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830212.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为平板图标显示且获取属性正确
     */
    it('ArkUI_Gauge_021 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830209.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为屏幕图标显示且获取属性正确
     */
    it('ArkUI_Gauge_022 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830210.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为电脑图标显示且获取属性正确
     */
    it('ArkUI_Gauge_023 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830208.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为手表图标显示且获取属性正确
     */
    it('ArkUI_Gauge_024 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125830211.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.icon支持设置指针样式为鼠标图标显示且获取属性正确
     */
    it('ArkUI_Gauge_025 ', 0, async (done: Function) => {

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('icon', JsonType.value),
        ],
        assertEqual: 'resource:///125831214.svg'
      })

      done();

    })

    /**
     * 测试组件indicator.space支持设置指针距离圆环外边的间距且获取属性正确
     */
    it('ArkUI_Gauge_026 ', 0, async (done: Function) => {

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 0
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '8.00vp'
      })

      done();

    })

  })
}


