import { describe, beforeAll, afterEach, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'GridBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function GridBootcampTest() {

  describe('GridBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'GridBootcampTest' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('滚动与滑动'));
        await atomDisplays.click();
        await driver.delayMs(5000);

        let scrollSearch: Component = await driver.findComponent(ON.text('网格/Grid'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    /**
     * 测试组件rowsTemplate且获取属性正确
     */
    it('ArkUI_Grid_0001', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr'
      })

      done();
    })

    it('ArkUI_Grid_0002', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0003', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0004', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 2fr'
      })

      done();
    })

    it('ArkUI_Grid_0005', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0006', 0, async (done: Function) => {

      await Search('参数列表', 'rowsTemplate')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'rowsTemplate',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rowsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr 1fr 1fr'
      })

      done();
    })
    /**
     * 测试组件columnsGap
     */
    it('ArkUI_Grid_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'columnsGap')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'columnsGap',
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'columnsGap',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件columnsTemplate且获取属性正确
     */
    it('ArkUI_Grid_0008', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(3000);
      await Search('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr'
      })

      done();
    })

    it('ArkUI_Grid_0009', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'columnsTemplate')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0010', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'columnsTemplate')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0011', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'columnsTemplate')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 2fr'
      })

      done();
    })

    it('ArkUI_Grid_0012', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'columnsTemplate')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr 1fr'
      })

      done();
    })

    it('ArkUI_Grid_0013', 0, async (done: Function) => {
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'columnsTemplate')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'columnsTemplate',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsTemplate', JsonType.value),
        ],
        assertEqual: '1fr 1fr 1fr 1fr 1fr'
      })

      done();
    })
    /**
     * 测试组件columnsGap
     */
    it('ArkUI_Grid_0014', 0, async (done: Function) => {
      //无法取到子组件状态
      let scrollSearch: Component = await driver.findComponent(ON.text('竖直布局'))
      await scrollSearch.click()
      await driver.delayMs(1000);
      await Search('参数列表', 'rowsGap')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'rowsGap',
          toggleClickType: ToggleClick.Open
        },
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'rowsGap',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件scrollBar且获取属性正确
     */
    it('ArkUI_Grid_0015', 0, async (done: Function) => {

      await Search('参数列表', 'scrollBar')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'scrollBar',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value),
        ],
        assertEqual: 'BarState.Off'
      })

      done();
    })

    it('ArkUI_Grid_0016', 0, async (done: Function) => {

      await Search('参数列表', 'scrollBar')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'scrollBar',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value),
        ],
        assertEqual: 'BarState.On'
      })

      done();
    })

    it('ArkUI_Grid_0017', 0, async (done: Function) => {

      await Search('参数列表', 'scrollBar')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'scrollBar',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value),
        ],
        assertEqual: 'BarState.Auto'
      })

      done();
    })
    /**
     * 测试组件scrollBarColor获取属性正确
     */
    it('ArkUI_Grid_0018', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Grid_0019', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Grid_0020', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Grid_0021', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Grid_0022', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Grid_0023', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'scrollBarColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件scrollBarWidth且获取属性正确
     */
    it('ArkUI_Grid_0024', 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'scrollBarWidth',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarWidth', JsonType.value),
        ],
        assertEqual: '8.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'scrollBarWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarWidth', JsonType.value),
        ],
        assertEqual: '1.00vp'
      })

      done();
    })
    /**
     * 测试组件cachedCount且获取属性正确
     */
    it('ArkUI_Grid_0025', 0, async (done: Function) => {
      await Search('参数列表', 'cachedCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'cachedCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 30
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'cachedCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件editMode
     */
    it('ArkUI_Grid_0026', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'editMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'editMode',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Grid_0027', 0, async (done: Function) => {
      await Search('参数列表', 'editMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'editMode',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
  })
}