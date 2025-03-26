import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { buttonClick,
  getToggle,
  JsonType, KeyStruct, radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide, sliderDrag,
  titleSearch,
  ToggleClick } from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'CheckboxGroupBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function CheckboxGroupBootcampTest() {

  describe('CheckboxGroupBootcampTest', () => {

    beforeAll(async (done: Function) => {
      console.info('beforeAll begin');
      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'CheckboxGroupBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[1].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('勾选文本/CheckboxGroup'))
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

    // selectAll
    it('ArkUI_CheckboxGroup_001', 0, async (done: Function) => {
      // 无法获取属性值
      await Search('参数列表', 'selectAll')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectAll'
        },
      })

      done();
    })

    it('ArkUI_CheckboxGroup_002', 0, async (done: Function) => {

      await Search('参数列表', 'selectAll')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    // selectedColor
    it('ArkUI_CheckboxGroup_003', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'selectedColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_004', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_005', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_006', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_007', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_008', 0, async (done: Function) => {

      await Search('参数列表', 'selectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // unselectedColor
    it('ArkUI_CheckboxGroup_009', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'unselectedColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_010', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_011', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_012', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_013', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_014', 0, async (done: Function) => {

      await Search('参数列表', 'unselectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('unselectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // mark.value.strokeColor
    it('ArkUI_CheckboxGroup_015', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF0A59F7","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_016', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF646AFD","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_017', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFE7062","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_018', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFE9E8ED","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_019', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FF1C1C1C","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_020', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeColor',
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"2.00vp"}'
      })

      done();
    })

    // mark.value.size
    it('ArkUI_CheckboxGroup_021', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.size')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'mark.value.size'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"20.00vp","strokeWidth":"2.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'mark.value.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"0.00vp","strokeWidth":"2.00vp"}'
      })

      done();
    })

    // mark.value.strokeWidth
    it('ArkUI_CheckboxGroup_022', 0, async (done: Function) => {

      await Search('参数列表', 'mark.value.strokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeWidth'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"20.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'mark.value.strokeWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mark', JsonType.obj),
        ],
        assertEqual: '{"strokeColor":"#FFFFFFFF","size":"-1.00px","strokeWidth":"0.00vp"}'
      })

      done();
    })

    // checkboxShape
    it('ArkUI_CheckboxGroup_023', 0, async (done: Function) => {

      await Search('参数列表', 'checkboxShape')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'checkboxShape'
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('checkboxShape', JsonType.value),
        ],
        assertEqual: '1'
      })

      done();
    })

    it('ArkUI_CheckboxGroup_024', 0, async (done: Function) => {

      await Search('参数列表', 'checkboxShape')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'checkboxShape',
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('checkboxShape', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_CheckboxGroup_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_CheckboxGroup_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'CheckboxGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_CheckboxGroup_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
  })
}