import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';

const TAG = 'SelectionMenuBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SelectionMenuBootcampTest() {
  describe('SelectionMenuBootcampTest', () => {
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(6000);
        console.info(TAG + 'SelectionMenuBootcamp001' + ' begin');

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[3].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(4000);

        let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems1: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[0].getBoundsCenter()
        let width4: Point = await ListItems1[5].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('文本选择菜单/SelectionMenu'))
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
     * 测试组件selectionMenuOptions
     */
    it('ArkUI_SelectionMenu_0001', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'selectionMenuOptions')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectionMenuOptions',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'selectionMenuOptions')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'selectionMenuOptions',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件editorMenuOptions
     */
    it('ArkUI_SelectionMenu_0003', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'editorMenuOptions')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'editorMenuOptions',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'editorMenuOptions')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'editorMenuOptions',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件expandedMenuOptions
     */
    it('ArkUI_SelectionMenu_0005', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'expandedMenuOptions')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'expandedMenuOptions',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'expandedMenuOptions')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'expandedMenuOptions',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件onCut
     */
    it('ArkUI_SelectionMenu_0007', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'onCut')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'onCut',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'onCut')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'onCut',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件onPaste
     */
    it('ArkUI_SelectionMenu_0009', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'onPaste')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'onPaste',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'onPaste')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'onPaste',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件onCopy
     */
    it('ArkUI_SelectionMenu_0011', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'onCopy')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'onCopy',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'onCopy')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'onCopy',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件onSelectAll
     */
    it('ArkUI_SelectionMenu_0013', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'onSelectAll')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'onSelectAll',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_SelectionMenu_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'onSelectAll')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'onSelectAll',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })

  })
}