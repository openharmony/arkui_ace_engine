import { describe, beforeAll,it} from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import { Point, Component, ON } from '@ohos.UiTest';
import { buttonClick,
  JsonType, KeyStruct, radioClick, Search,
  Slide,
  sliderDrag,
  ToggleClick } from '../../utils/index';

const TAG = 'SpanBootcamp'
/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SpanBootcampTest() {
  describe('SpanBootcampTest', () => {
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
        console.info(TAG + 'SpanBootcamp001' + ' begin');

        let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        let width0: Point = await ListItemGroups[0].getBoundsCenter()
        let width1: Point = await ListItemGroups[4].getBoundsCenter()
        await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
        await driver.delayMs(2000);

        let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
        await atomDisplays.click();
        await driver.delayMs(2000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[4].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('Span'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })
    //decoration.type
    /*
     * 测试组件decoration.type支持设置None且获取属性正确
     */
    it('ArkUI_Span_001', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /*
     * 测试组件decoration.type支持设置Underline且获取属性正确
     */
    it('ArkUI_Span_002', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 1,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Underline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /*
     * 测试组件decoration.type支持设置Overline且获取属性正确
     */
    it('ArkUI_Span_003', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 2,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Overline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /*
     * 测试组件decoration.type支持设置LineThrough且获取属性正确
     */
    it('ArkUI_Span_004', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.LineThrough","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    //decoration.color
    /*
    *测试组件decoration.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Span_005', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF0A59F7","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Span_006', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF646AFD","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Span_007', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFFE7062","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Span_008', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFE9E8ED","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Span_009', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF1C1C1C","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Span_010', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFFFFFFF","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    //decoration.style
    /*
     * 测试组件decoration.style支持设置SOLID且获取属性正确
     */
    it('ArkUI_Span_011', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置DOUBLE且获取属性正确
     */
    it('ArkUI_Span_012', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 1,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOUBLE"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置DOTTED且获取属性正确
     */
    it('ArkUI_Span_013', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 2,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOTTED"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置DASHED且获取属性正确
     */
    it('ArkUI_Span_014', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 3,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DASHED"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置WAVY且获取属性正确
     */
    it('ArkUI_Span_015', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 4,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.WAVY"}'
      })
      done();
    })
    //letterSpacing
    it('ArkUI_Span_016', 0, async (done: Function) => {
      await Search('参数列表', 'letterSpacing')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '20.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //textCase
    /*
     * 测试组件textCase支持设置Normal且获取属性正确
     */
    it('ArkUI_Span_017', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.Normal'
      })
      done();
    })
    /*
     * 测试组件textCase支持设置LowerCase且获取属性正确
     */
    it('ArkUI_Span_018', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 1,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.LowerCase'
      })
      done();
    })
    /*
     * 测试组件textCase支持设置UpperCase且获取属性正确
     */
    it('ArkUI_Span_019', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.UpperCase'
      })
      done();
    })
    //fontColor
    /*
    *测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Span_020', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Span_021', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Span_022', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Span_023', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Span_024', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Span_025', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //fontSize  需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
    it('ArkUI_Span_026', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value)
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done()
    })
    //fontStyle 
    /*
     * 测试组件fontStyle支持设置Normal且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_027', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value)
        ],
        assertEqual: 'FontStyle.Normal'
      })
      done();
    })
    /*
     * 测试组件fontStyle支持设置Italic且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_028', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value)
        ],
        assertEqual: 'FontStyle.Italic'
      })
      done();
    })
    //fontWeight
    /*
     * 测试组件fontWeight支持设置100且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_029', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '100'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置200且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_030', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '200'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置300且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_031', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '300'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置400且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_032', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '400'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置500且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_033', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '500'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置600且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_034', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '600'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置700且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_035', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 6,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '700'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置800且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_036', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 7,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '800'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置900且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_037', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 8,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '900'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Lighter且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_038', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 9,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Lighter'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Normal且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_039', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 10,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Normal'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Regular且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_040', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 11,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Medium且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_041', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 12,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Bold且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_042', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 13,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bold'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Bolder且获取属性正确
     * 需要将该属性添加到Text组件，否则不生效，因此取Text组件id进行断言
     */
    it('ArkUI_Span_043', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bolder'
      })
      done();
    })
    //lineHeight
    it('ArkUI_Span_044', 0, async (done: Function) => {
      await Search('参数列表', 'lineHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineHeight', JsonType.value)
        ],
        assertEqual: '10.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineHeight', JsonType.obj)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //textShadow.radius
    it('ArkUI_Span_045', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.radius')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '360.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //textShadow.type
    /*
     * 测试组件textShadow.type支持设置COLOR且获取属性正确
     * */
    it('ArkUI_Span_046', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.type')
      await radioClick({
        radioClickObj: 0,
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    /*
     * 测试组件textShadow.type支持设置BLUR且获取属性正确
     * */
    it('ArkUI_Span_047', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Span',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done()
    })

  })
}