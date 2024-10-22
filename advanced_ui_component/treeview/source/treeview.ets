/**
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
import hilog from '@ohos.hilog';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';
import { common } from '@kit.AbilityKit';
import resourceManager from '@ohos.resourceManager';

const IMAGE_NODE_HEIGHT: number = 24;
const IMAGE_NODE_WIDTH: number = 24;
const ITEM_WIDTH: number = 0;
const ITEM_HEIGHT: number = 48;
const ITEM_HEIGHT_INPUT: number = 32;
const BORDER_WIDTH_HAS: number = 2;
const BORDER_WIDTH_NONE: number = 0;
const NODE_HEIGHT: number = 48;
const LIST_ITEM_HEIGHT_NONE: number = 0;
const LIST_ITEM_HEIGHT: number = 48;
const SHADOW_OFFSETY: number = 10;
const FLAG_NUMBER: number = 2;
const DRAG_OPACITY: number = 0.4;
const DRAG_OPACITY_NONE: number = 1;
const MIN_FONT_SCALE: number = 1;
const MAX_FONT_SCALE: number = 2;
const FLAG_LINE_HEIGHT: string = '1.0vp';
const X_OFF_SET: string = '0vp';
const Y_OFF_SET: string = '2.75vp';
const Y_BOTTOM_OFF_SET: string = '-1.25vp';
const Y_BASE_PLATE_OFF_SET: string = '1.5vp';
const COLOR_IMAGE_EDIT: string = '#FFFFFF';
const COLOR_IMAGE_ROW: string = '#00000000';
const COLOR_SELECT: string = '#1A0A59F7';
const SHADOW_COLOR: string = '#00001E';
const GRAG_POP_UP_HEIGHT: string = '48';
const FLOOR_MIN_WIDTH: string = '128vp';
const FLOOR_MAX_WIDTH: string = '208vp';
const TEXT_MIN_WIDTH: string = '80vp';
const TEXT_MAX_WIDTH: string = '160vp';
const MIN_WIDTH: string = '112vp';
const MAX_WIDTH: string = '192vp';
const TRANS_COLOR: string = '#00FFFFFF';
const DELAY_TIME: number = 100;
const LEVEL_MARGIN: number = 12;
const MARGIN_OFFSET: number = 8;
const TAG: string = 'TreeView';
const LOG_CODE: number = 0x3900;

const ARROW_DOWN: Resource | string = $r('sys.media.ohos_ic_public_arrow_down');

const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAAC' +
  'AhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAl' +
  'wSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E' +
  '4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMP' +
  'xBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg=='

const ARROW_RIGHT: Resource | string = $r('sys.media.ohos_ic_public_arrow_right');

const ARROW_RIGHT_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAA' +
  'CAhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAA' +
  'lwSFlzAAAOxAAADsQBlSsOGwAAAKFJREFUeNpjYBgFowAE/v//bwHEPOToZSJS3XIg3k6OJcRaUALEFuRYwkyMosbGxusNDQ3XgMwCIHYAsl' +
  'cDxX5RzQJKLGEmxbvkWMJEaqQxMjKuBVI5QGwDxOnUimR08AFK81DdAmAqArl8DhDfAOKpVLUAavh2IH4CxI7A4HpDMEgpMPwFUXFGS8NJCa' +
  'L55BgOAixEqqsB4oOkGj4KRggAAN4STB9zyhGzAAAAAElFTkSuQmCC'

enum Event {
  TOUCH_DOWN = 0,
  TOUCH_UP = 1,
  HOVER = 3,
  HOVER_OVER = 4,
  FOCUS = 5,
  BLUR = 6,
  MOUSE_BUTTON_RIGHT = 7,
  DRAG = 8,
}

enum MenuOperation {
  ADD_NODE = 0,
  REMOVE_NODE = 1,
  MODIFY_NODE = 2,
  COMMIT_NODE = 3,
}

enum PopUpType {
  HINTS = 0,
  WARNINGS = 1,
}

enum InputError {
  INVALID_ERROR = 0,
  LENGTH_ERROR = 1,
  NONE = 2,
}

enum Flag {
  DOWN_FLAG = 0,
  UP_FLAG = 1,
  NONE = 2,
}

export enum NodeStatus {
  EXPAND = 0,
  COLLAPSE,
}

export enum InteractionStatus {
  NORMAL = 0,
  SELECTED,
  EDIT,
  FINISH_EDIT,
  DRAG_INSERT,
  FINISH_DRAG_INSERT,
}

enum CollapseImageType {
  ARROW_DOWN = 0,
  ARROW_RIGHT,
  ARROW_DOWN_WHITE,
  ARROW_RIGHT_WHITE,
}

interface ChildNodeInfo {
  isHasChildNode: boolean;
  childNum: number;
  allChildNum: number;
}

interface NodeItemView {
  imageNode?: ImageNode;
  inputText: InputText;
  mainTitleNode: MainTitleNode;
  imageCollapse?: CollapseImageNode;
  fontColor?: ResourceColor;
}

interface Status {
  normal: ResourceColor;
  hover: ResourceColor;
  press: ResourceColor;
  selected: ResourceColor;
  highLight?: ResourceColor;
}

interface NodeBorder {
  borderWidth: Resource | number;
  borderColor: ResourceColor;
  borderRadius: Resource;
}

interface PopUpInfo {
  popUpIsShow: boolean;
  popUpEnableArrow: boolean;
  popUpColor?: ResourceColor;
  popUpText?: string | Resource;
  popUpTextColor?: ResourceColor;
}

interface BorderWidth {
  has: Resource | number;
  none: Resource | number;
}

interface TextSetting {
  fontColor: ResourceColor;
  fontSize: Resource;
  fontWeight: FontWeight;
}

interface NodeInfoView {
  itemId?: number;
  itemIcon?: Resource | string;
  itemTitle?: ResourceStr;
  isFolder?: boolean;
}

interface FloorConstraintSize {
  minWidth: string;
  maxWidth: string;
}

interface TextConstraintSize {
  minWidth1: string;
  maxWidth1: string;
  minWidth2: string;
  maxWidth2: string;
}

interface Padding {
  left: Resource;
  right: Resource;
}

interface ItemPadding {
  left: Resource;
  right: Resource;
  top: Resource;
  bottom: Resource;
}

interface Shadow {
  radius: Resource;
  color: string;
  offsetX?: number;
  offsetY?: number;
}

interface DragPopup {
  floorConstraintSize: FloorConstraintSize;
  textConstraintSize: TextConstraintSize;
  padding: Padding;
  backgroundColor: ResourceColor;
  height: string;
  shadow: Shadow;
  borderRadius: Resource;
  fontColor: ResourceColor;
  fontSize: Resource;
  fontWeight: FontWeight;
  imageOpacity: Resource;
}

interface DragNodeParam {
  parentId: number,
  currentId: number,
  data: NodeParam,
}

interface FlagLine {
  flagLineHeight: string;
  flagLineColor: Resource;
  xOffset: string;
  yTopOffset: string;
  yBottomOffset: string;
  yBasePlateOffset: string;
}

interface SubTitleStyle {
  normalFontColor: ResourceColor;
  highLightFontColor: ResourceColor;
  fontSize: Resource;
  fontWeight: FontWeight;
  margin: Padding;
}

interface NodeItemViewFactory {
  createNode: () => NodeItemView;
  createNodeByNodeParam: (nodeParam: NodeParam) => NodeItemView;
}

class TreeViewNodeItemFactory implements NodeItemViewFactory {
  private static instance: TreeViewNodeItemFactory;

  private constructor() {
  }

  /**
   * TreeViewNodeItemFactory singleton function
   *
   * @returns TreeViewNodeItemFactory
   */
  public static getInstance(): TreeViewNodeItemFactory {
    if (!TreeViewNodeItemFactory.instance) {
      TreeViewNodeItemFactory.instance = new TreeViewNodeItemFactory();
    }
    return TreeViewNodeItemFactory.instance;
  }

  /**
   * TreeViewNodeItemFactory create default node
   *
   * @returns NodeItemView
   */
  public createNode(): NodeItemView {
    return {
      imageNode: undefined,
      inputText: new InputText(),
      mainTitleNode: new MainTitleNode(''),
      imageCollapse: undefined,
      fontColor: undefined,
    };
  }

   /**
   * TreeViewNodeItemFactory create node by node parameter
   *
   * @param nodeParam node parameter
   * @returns NodeItemView
   */
  public createNodeByNodeParam(nodeParam: NodeParam): NodeItemView {
    let nodeItemView: NodeItemView = this.createNode();
    if (nodeParam.icon) {
      nodeItemView.imageNode = new ImageNode(
        nodeParam.icon,
        $r('sys.float.ohos_id_alpha_content_fourth'),
        IMAGE_NODE_HEIGHT,
        IMAGE_NODE_WIDTH,
        nodeParam.selectedIcon,
        nodeParam.editIcon,
      );
    }
    if (nodeParam.primaryTitle) {
      nodeItemView.mainTitleNode = new MainTitleNode(nodeParam.primaryTitle);
    }
    return nodeItemView;
  }
}

let emptyNodeInfo: NodeParam = {
  isFolder: true,
  icon: '',
  selectedIcon: '',
  editIcon: '',
  container: () => {
  },
  secondaryTitle: '',
  primaryTitle: '',
  parentNodeId: -1,
  currentNodeId: -1,
}

class TreeViewTheme {
  private static instance: TreeViewTheme;
  public itemSelectedBgColor: ResourceColor = '#1A0A59F7';
  public primaryTitleFontColor: ResourceColor = $r('sys.color.ohos_id_color_primary');
  public secondaryTitleFontColor: ResourceColor = $r('sys.color.ohos_id_color_secondary');
  public primaryTitleActiveFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_activated');
  public itemPressedBgColor: ResourceColor = $r('sys.color.ohos_id_color_click_effect');
  public itemHoverBgColor: ResourceColor = $r('sys.color.ohos_id_color_hover');
  public borderFocusedColor: ResourceColor = $r('sys.color.ohos_id_color_focused_outline');
  public leftIconColor: ResourceColor = $r('sys.color.icon_secondary');
  public leftIconActiveColor: ResourceColor = $r('sys.color.icon_secondary');
  public arrowIconColor: ResourceColor = $r('sys.color.icon_tertiary');

  private constructor() {

  }

  /**
   * TreeViewTheme singleton function
   *
   * @returns TreeViewNodeItemFactory
   */
  public static getInstance(): TreeViewTheme {
    if (!TreeViewTheme.instance) {
      TreeViewTheme.instance = new TreeViewTheme();
    }
    return TreeViewTheme.instance;
  }
}

@Observed
export class NodeInfo {
  public imageSource: Resource | string | undefined = '';
  private nodeHeight: Resource | number;
  private nodeItemView: NodeItemView;
  private nodeLeftPadding: number;
  private nodeColor: ResourceColor;
  private nodeIsShow: boolean;
  private status: Status;
  private nodeBorder: NodeBorder;
  private popUpInfo: PopUpInfo;
  private listItemHeight: number;
  private isShowTitle: boolean;
  private isShowInputText: boolean;
  private isSelected: boolean;
  public readonly borderWidth: BorderWidth =
    { has: BORDER_WIDTH_HAS/* 2vp */, none: BORDER_WIDTH_NONE/* 0vp */ }
  /* parameter of the drag event.*/
  private nodeParam: NodeParam;
  private node: NodeItem;
  private canShowFlagLine: boolean = false;
  private isOverBorder: boolean = false;
  private canShowBottomFlagLine: boolean = false;
  private isHighLight: boolean = false;
  private flagLineLeftMargin: number;
  private isModify: boolean = false;
  private treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();
  public fontColor: ResourceColor = '';

  constructor(node: NodeItem, nodeParam: NodeParam) {
    this.node = node;
    this.nodeParam = nodeParam;
    this.nodeItemView = TreeViewNodeItemFactory.getInstance().createNodeByNodeParam(nodeParam);
    this.popUpInfo = {
      popUpIsShow: false,
      popUpEnableArrow: false,
      popUpColor: undefined,
      popUpText: '',
      popUpTextColor: undefined,
    };
    this.nodeHeight = NODE_HEIGHT;
    this.nodeLeftPadding = node.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET; // calculate left padding
    this.nodeColor = $r('sys.color.ohos_id_color_background');
    this.nodeIsShow = (this.node.nodeLevel > 0) ? false : true;
    this.listItemHeight = (this.node.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
    this.isShowTitle = true;
    this.isShowInputText = false;
    this.isSelected = false;
    this.status = {
      normal: $r('sys.color.ohos_id_color_background_transparent'),
      hover: this.treeViewTheme.itemHoverBgColor,
      press: this.treeViewTheme.itemPressedBgColor,
      selected: this.treeViewTheme.itemSelectedBgColor,
      highLight: $r('sys.color.ohos_id_color_activated')
    };
    this.nodeBorder = {
      borderWidth: BORDER_WIDTH_NONE,
      borderColor: this.treeViewTheme.borderFocusedColor,
      borderRadius: $r('sys.float.ohos_id_corner_radius_clicked')
    };
    this.flagLineLeftMargin = node.nodeLevel * LEVEL_MARGIN + MARGIN_OFFSET;
  }

  /**
   * NodeInfo add collapse image
   *
   * @param isHasChildNode whether node has child node
   */
  addImageCollapse(isHasChildNode: boolean): void {
    if (isHasChildNode) {
      this.nodeItemView.imageCollapse =
        CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_RIGHT);
    } else {
      this.nodeItemView.imageCollapse = undefined;
    }
  }

  setFontColor(color: ResourceColor): void {
    this.fontColor = color
  }

  getFontColor(): ResourceColor {
    return this.fontColor;
  }

  getPopUpInfo(): PopUpInfo {
    return this.popUpInfo;
  }

  setPopUpIsShow(isShow: boolean): void {
    this.popUpInfo.popUpIsShow = isShow;
  }

  setPopUpEnableArrow(popUpEnableArrow: boolean): void {
    this.popUpInfo.popUpEnableArrow = popUpEnableArrow;
  }

  setPopUpColor(color: ResourceColor): void {
    this.popUpInfo.popUpColor = color;
  }

  setPopUpText(text: string | Resource | undefined): void {
    this.popUpInfo.popUpText = text;
  }

  setPopUpTextColor(popUpTextColor: ResourceColor): void {
    this.popUpInfo.popUpTextColor = popUpTextColor;
  }

  getIsShowTitle(): boolean {
    return this.isShowTitle;
  }

  getIsShowInputText(): boolean {
    return this.isShowInputText;
  }

  setTitleAndInputTextStatus(isModify: boolean): void {
    if (isModify) {
      this.isShowTitle = false;
      this.isShowInputText = true;
    } else {
      this.isShowTitle = true;
      this.isShowInputText = false;
    }
  }

  handleImageCollapseAfterAddNode(isAddImageCollapse: boolean): void {
    // listTree this node already has ImageCollapse.
    if (isAddImageCollapse) {
      this.nodeItemView.imageCollapse =
        CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(CollapseImageType.ARROW_DOWN);
    } else {
      this.nodeItemView.imageCollapse = undefined;
    }
  }

  setNodeColor(nodeColor: ResourceColor | undefined): void {
    if (nodeColor === undefined) {
      return;
    }
    this.nodeColor = nodeColor;
  }

  getNodeColor(): ResourceColor {
    return this.nodeColor;
  }

  setListItemHeight(listItemHeight: number): void {
    this.listItemHeight = listItemHeight;
  }

  getListItemHeight(): number {
    return this.listItemHeight;
  }

  getNodeCurrentNodeId(): number {
    return this.node.currentNodeId;
  }

  getNodeParentNodeId(): number {
    return this.node.parentNodeId;
  }

  getNodeLeftPadding(): number {
    return this.nodeLeftPadding;
  }

  getNodeHeight(): Resource | number {
    return this.nodeHeight;
  }

  setNodeIsShow(nodeIsShow: boolean): void {
    this.nodeIsShow = nodeIsShow;
  }

  getNodeIsShow(): boolean {
    return this.nodeIsShow;
  }

  getNodeItem(): NodeItemView {
    return this.nodeItemView;
  }

  getNodeStatus(): Status {
    return this.status;
  }

  getNodeBorder(): NodeBorder {
    return this.nodeBorder;
  }

  setNodeBorder(isClearFocusStatus: boolean): void {
    this.nodeBorder.borderWidth = isClearFocusStatus ? this.borderWidth.has : this.borderWidth.none;
  }

  getChildNodeInfo(): ChildNodeInfo {
    return this.node.childNodeInfo;
  }

  getMenu(): () => void {
    return this.nodeParam.container as () => void;
  }

  setIsSelected(isSelected: boolean): void {
    this.isSelected = isSelected;
  }

  getIsSelected(): boolean {
    return this.isSelected;
  }

  /* To gain the information while to alter node. */
  getNodeInfoData(): NodeParam {
    return this.nodeParam;
  }

  /* To gain the tree Node(NodeItem) while to alter node. */
  public getNodeInfoNode(): NodeItem {
    return this.node;
  }

  public getIsFolder(): boolean | undefined {
    return this.nodeParam.isFolder;
  }

  public setCanShowFlagLine(canShowFlagLine: boolean): void {
    this.canShowFlagLine = canShowFlagLine;
  }

  public getCanShowFlagLine(): boolean {
    return this.canShowFlagLine;
  }

  public setFlagLineLeftMargin(currentNodeLevel: number | undefined): void {
    if (currentNodeLevel === undefined) {
      return;
    }
    this.flagLineLeftMargin = currentNodeLevel * LEVEL_MARGIN + MARGIN_OFFSET; // calculate
  }

  public getFlagLineLeftMargin(): number {
    return this.flagLineLeftMargin;
  }

  public getNodeLevel(): number {
    return this.node.nodeLevel;
  }

  public setIsOverBorder(isOverBorder: boolean): void {
    this.isOverBorder = isOverBorder;
  }

  public getIsOverBorder(): boolean {
    return this.isOverBorder;
  }

  public setCanShowBottomFlagLine(canShowBottomFlagLine: boolean): void {
    this.canShowBottomFlagLine = canShowBottomFlagLine;
  }

  public getCanShowBottomFlagLine(): boolean {
    return this.canShowBottomFlagLine;
  }

  public setIsHighLight(isHighLight: boolean): void {
    this.isHighLight = isHighLight;
  }

  public getIsHighLight(): boolean {
    return this.isHighLight;
  }

  public setIsModify(isModify: boolean): void {
    this.isModify = isModify;
  }

  public getIsModify(): boolean {
    return this.isModify;
  }
}

/**
 * Control style of operation element.
 * @enum { TreeListenType }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Control style of operation element.
 * @enum { TreeListenType }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export enum TreeListenType {
  /**
   * register listener after a node is clicked.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * register listener after a node is clicked.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  NODE_CLICK = 'NodeClick',

  /**
   * register listener after a node is add.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * register listener after a node is add.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  NODE_ADD = 'NodeAdd',

  /**
   * register listener after a node is deleted.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * register listener after a node is deleted.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  NODE_DELETE = 'NodeDelete',

  /**
   * register listener after a node is modified.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * register listener after a node is modified.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  NODE_MODIFY = 'NodeModify',

  /**
   * register listener after a node is moved.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * register listener after a node is moved.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  NODE_MOVE = 'NodeMove',
}

/**
 * Declare class TreeListener.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Declare class TreeListener.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export class TreeListener {
  public _events: [(callbackParam: CallbackParam) => void] | [] = [];
  _once_events: [(callbackParam: CallbackParam) => void] | [] = [];

  constructor() {
  }

  /**
   * Event registration and processing.
   *
   * The event will not be destroyed after being processed.
   *
   * @param { type } event Registered Events.
   * @param callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Event registration and processing.
   *
   * The event will not be destroyed after being processed.
   *
   * @param { type } event Registered Events.
   * @param callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public on(type: TreeListenType, callback: (callbackParam: CallbackParam) => void): void {
    if (Array.isArray(type)) {
      for (let i = 0, l = type.length; i < l; i++) {
        this.on((type as TreeListenType[])[i], callback);
      }
    } else {
      (this._events[type] || (this._events[type] = [])).push(callback);
    }
  }

  /**
   * Event registration and processing.
   *
   * After the event is processed once, it will be destroyed.
   *
   * @param { type } event Registered Events.
   * @param callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Event registration and processing.
   *
   * After the event is processed once, it will be destroyed.
   *
   * @param { type } event Registered Events.
   * @param callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public once(type: TreeListenType, callback?: (callbackParam: CallbackParam) => void): void {
    if (Array.isArray(type)) {
      this.off(type, callback);
    } else {
      (this._once_events[type] || (this._once_events[type] = [])).push(callback);
    }
  }

  /**
   * Destroy event.
   *
   * @param type Registered Events.
   * @param callback Event callback.
   * @since 10
   */
  public off(type: TreeListenType, callback?: (callbackParam: CallbackParam) => void): void {
    if (type === null) {
      this._events = [];
    }
    if (Array.isArray(type)) {
      for (let i: number = 0, l: number = type.length; i < l; i++) {
        this.off((type as TreeListenType[])[i], callback);
      }
    }
    let cbs: [(callbackParam: CallbackParam) => void] = this._events[type];
    if (!cbs) {
      return;
    }
    if (callback === null) {
      this._events[type] = null;
    }
    let i: number = cbs.length;
    while (i--) {
      let cb: (callbackParam: CallbackParam) => void = cbs[i];
      if (cb === callback) {
        cbs.splice(i, 1);
        break;
      }
    }
  }

  /**
   * Triggers all callbacks of an event with parameters.
   *
   * @param event Registered Events.
   * @param argument Parameters returned by the callback event.
   * @since 10
   */
  public emit(event: TreeListenType, argument: CallbackParam) {
    if (this._once_events[event]) {
      let cbsOnce: ((callbackParam: CallbackParam) => void)[] =
        Array.from<(callbackParam: CallbackParam) => void>(this._once_events[event]);
      if (cbsOnce) {
        for (let i: number = 0, l: number = cbsOnce.length; i < l; i++) {
          try {
            cbsOnce[i](argument);
          } catch (e) {
            throw new Error('once function callbacks error.');
          }
        }
        this._once_events[event] = null;
      }
    } else if (this._events[event]) {
      let cbsOn: ((callbackParam: CallbackParam) => void)[] =
        Array.from<(callbackParam: CallbackParam) => void>(this._events[event]);
      if (cbsOn) {
        for (let i: number = 0, l: number = cbsOn.length; i < l; i++) {
          try {
            cbsOn[i](argument);
          } catch (e) {
            throw new Error('on function callbacks error.');
          }
        }
      }
    }
  }
}

/**
 * Declare class TreeListenerManager.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Declare class TreeListenerManager.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export class TreeListenerManager {
  public static readonly APP_KEY_EVENT_BUS = 'app_key_event_bus';
  private appEventBus: TreeListener;

  private constructor() {
    this.appEventBus = new TreeListener();
  }

  /**
   * Get instance of treeListenerManager.
   * @return treeListenerManager instance.
   * @static
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Get instance of treeListenerManager.
   * @return treeListenerManager instance.
   * @static
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  static getInstance(): TreeListenerManager {
    if (AppStorage.Get('app_key_event_bus') === undefined) {
      AppStorage.SetOrCreate('app_key_event_bus', new TreeListenerManager())
    }
    return AppStorage.Get('app_key_event_bus') as TreeListenerManager;
  }

  /**
   * Get treeListener.
   * @return treeListener object
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Get treeListener.
   * @return treeListener object
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public getTreeListener(): TreeListener {
    return this.appEventBus;
  }
}

/**
 * Declare TreeView Component
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
@Component
export struct TreeView {
  /**
   * Node data source of TreeView
   * @type TreeController
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Node data source of TreeView
   * @type TreeController
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  treeController: TreeController = new TreeController();
  @State nodeList: NodeInfo[] = [];
  listNodeDataSource: ListNodeDataSource = new ListNodeDataSource();
  @State item: NodeInfo[] | null = null;
  @State touchCount: number = 0;
  @State dropSelectedIndex: number = 0;
  @State viewLastIndex: number = -1;
  @State followingSystemFontScale: boolean = false;
  @State maxAppFontScale: number = 1;
  @State listItemBgColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @Provide treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();

  @Builder
  NullBuilder() {
  };

  @BuilderParam private listTreeViewMenu: () => void = this.NullBuilder;
  private readonly MAX_CN_LENGTH: number = 254;
  private readonly MAX_EN_LENGTH: number = 255;
  private readonly INITIAL_INVALID_VALUE = -1;
  private readonly MAX_TOUCH_DOWN_COUNT = 0;
  private isMultiPress: boolean = false;
  private touchDownCount: number = this.INITIAL_INVALID_VALUE;
  private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
  private readonly itemPadding: ItemPadding = {
    left: $r('sys.float.ohos_id_card_margin_start'),
    right: $r('sys.float.ohos_id_card_margin_end'),
    top: $r('sys.float.ohos_id_text_margin_vertical'),
    bottom: $r('sys.float.ohos_id_text_margin_vertical'),
  };
  private readonly textInputPadding: ItemPadding =
    { left: $r('sys.float.padding_level0'), right: $r('sys.float.padding_level0'),
      top: $r('sys.float.padding_level0'), bottom: $r('sys.float.padding_level0') }

  onWillApplyTheme(theme: Theme) {
    this.treeViewTheme.itemSelectedBgColor = theme.colors.interactiveSelect;
    this.treeViewTheme.itemPressedBgColor = theme.colors.interactivePressed;
    this.treeViewTheme.itemHoverBgColor = theme.colors.interactiveHover;
    this.treeViewTheme.primaryTitleFontColor = theme.colors.fontPrimary;
    this.treeViewTheme.secondaryTitleFontColor = theme.colors.fontSecondary;
    this.treeViewTheme.primaryTitleActiveFontColor = theme.colors.interactiveActive;
    this.treeViewTheme.borderFocusedColor = theme.colors.interactiveFocus;
    this.treeViewTheme.leftIconColor = theme.colors.iconSecondary;
    this.treeViewTheme.leftIconActiveColor = theme.colors.interactiveActive;
    this.treeViewTheme.arrowIconColor = theme.colors.iconPrimary;
    this.treeController.treeViewTheme = this.treeViewTheme;
  }

  aboutToAppear(): void {
    if (this.treeController !== null) {
      this.listNodeDataSource = this.treeController.getListNodeDataSource();
      this.nodeList = this.treeController.getListNodeDataSource().listNode;
      this.item = this.treeController.getListNodeDataSource().listNode;
    }
    let uiContent: UIContext = this.getUIContext();
    this.followingSystemFontScale = uiContent.isFollowingSystemFontScale();
    this.maxAppFontScale = uiContent.getMaxFontScale();
  }

  decideFontScale() {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.followingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale, MAX_FONT_SCALE)
  }

  @Builder
  popupForShowTitle(text: string | Resource, backgroundColor: Resource, fontColor: Resource) {
    Row() {
      Text(text)
        .fontSize($r('sys.float.ohos_id_text_size_body2'))
        .fontWeight('regular').fontColor(fontColor)
        .minFontScale(MIN_FONT_SCALE)
        .maxFontScale(this.decideFontScale())
    }.backgroundColor(backgroundColor)
    .border({ radius: $r('sys.float.ohos_id_elements_margin_horizontal_l') })
    .padding({
      left: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
      right: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
      top: $r('sys.float.ohos_id_card_margin_middle'),
      bottom: $r('sys.float.ohos_id_card_margin_middle'),
    })
  }

  @Builder
  builder() {
    this.listTreeViewMenu()
  }

  /* Set the popup of dragging node. */
  @Builder
  draggingPopup(item: NodeInfo) {
    Row() {
      if (item.getNodeItem().imageNode) {
        Row() {
          Image(item.getNodeItem().imageNode?.normalSource)
            .objectFit(ImageFit.Contain)
            .height(item.getNodeItem().imageNode?.itemHeight)
            .width(item.getNodeItem().imageNode?.itemWidth)
            .opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity)
            .matchTextDirection((item.getNodeItem().imageCollapse?.collapseSource === ARROW_RIGHT || item.getNodeItem()
              .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false)
        }
        .backgroundColor(COLOR_IMAGE_ROW)
        .margin({ end: getLengthMetricsByResourceOrNumber(item.getNodeItem().imageNode?.itemRightMargin) })
        .height(item.getNodeItem().imageNode?.itemHeight)
        .width(item.getNodeItem().imageNode?.itemWidth)
      }

      Row() {
        if (item.getNodeItem().mainTitleNode && item.getIsShowTitle()) {
          Text(item.getNodeItem().mainTitleNode?.title)
            .maxLines(1)
            .minFontScale(MIN_FONT_SCALE)
            .maxFontScale(this.decideFontScale())
            .fontSize(item.getNodeItem().mainTitleNode?.size)
            .fontColor(this.listNodeDataSource.getDragPopupPara().fontColor)
            .fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
        }
      }
      .constraintSize({
        minWidth: item.getNodeItem().imageNode ?
        this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth1 :
        this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
        maxWidth: item.getNodeItem().imageNode ?
        this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth1 :
        this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2,
      })
    }
    .constraintSize({
      minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
      maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth,
    })
    .height(this.listNodeDataSource.getDragPopupPara().height)
    .backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor)
    .padding({
      start: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.left),
      end: LengthMetrics.resource(this.listNodeDataSource.getDragPopupPara().padding.right),
    })
    .shadow({
      radius: $r('sys.float.ohos_id_corner_radius_default_m'),
      color: SHADOW_COLOR,
      offsetY: 0,
    })
    .borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius) // need to doubleCheck.
  }

  clearLastIndexColor(): void {
    if (this.viewLastIndex === -1 || this.viewLastIndex >= this.nodeList.length) {
      return;
    }
    this.setImageSources(this.viewLastIndex, InteractionStatus.NORMAL);
    this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.NORMAL);
    this.nodeList[this.viewLastIndex].setNodeColor($r('sys.color.ohos_id_color_background_transparent'))
    this.nodeList[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
    this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor($r('sys.color.ohos_id_color_background_transparent'));
    this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
    this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(false);
    this.listNodeDataSource.listNode[this.viewLastIndex].imageSource =
      this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem().imageNode?.source;
  }

  setImageSources(index: number, interactionStatus: InteractionStatus): void {
    let nodeInfo: NodeInfo = this.nodeList[index];
    nodeInfo.setIsSelected(interactionStatus === InteractionStatus.SELECTED ||
      interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.FINISH_EDIT);
    if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DRAG_INSERT &&
      interactionStatus !== InteractionStatus.FINISH_DRAG_INSERT) {
      nodeInfo.getNodeItem().mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.SELECTED ||
        interactionStatus === InteractionStatus.FINISH_EDIT);
    }
    if (nodeInfo.getNodeItem().imageNode !== null) {
      nodeInfo.getNodeItem().imageNode?.setImageSource(interactionStatus);
    }
  }

  build() {
    List({}) {
      LazyForEach(this.listNodeDataSource, (itemInner: NodeInfo) => {
        ListItem() {
          Row() {
            TreeViewInner({
              item: itemInner,
              listNodeDataSource: this.listNodeDataSource,
              index: this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId()),
              listTreeViewMenu: this.listTreeViewMenu,
            })
          }
          .onTouch((event: TouchEvent) => {
            this.viewLastIndex = this.listNodeDataSource.getLastIndex();
            let index: number = this.listNodeDataSource.findIndex(itemInner.getNodeCurrentNodeId());

            if (event.type === TouchType.Down) {
              if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.setClickIndex(index);
              }
            }
            if (event.type === TouchType.Up) {
              this.listNodeDataSource.listNode[index].setIsSelected(true);
              this.listNodeDataSource.setImageSource(index, InteractionStatus.SELECTED);
              if (this.listNodeDataSource.listNode[index].getNodeItem().imageNode !== null) {
                this.listNodeDataSource.listNode[index].imageSource = this.listNodeDataSource.listNode[index]
                  .getNodeItem().imageNode?.source;
              }

              if (index !== this.viewLastIndex) {
                this.clearLastIndexColor();
                this.listNodeDataSource.lastIndex = index;
                this.listNodeDataSource.setClickIndex(index);
              }
              this.viewLastIndex = index;
            }

            if (this.listNodeDataSource.getLastIndex() !== -1 && index !== this.listNodeDataSource.getLastIndex()) {
              this.listNodeDataSource.setPopUpInfo(
                PopUpType.WARNINGS,
                InputError.NONE,
                false,
                this.listNodeDataSource.getLastIndex()
              );
              this.listNodeDataSource.setItemVisibilityOnEdit(
                this.listNodeDataSource.getLastIndex(),
                MenuOperation.COMMIT_NODE
              );
            }
          })
        }
        .width('100%')
        .height(itemInner.getListItemHeight())
        .padding({
          start: LengthMetrics.resource(this.itemPadding.left),
          end: LengthMetrics.resource(this.itemPadding.right)
        })
        .align(Alignment.Start)
        .onDragStart((event: DragEvent, extraParams: string) => {
          if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
            hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
            return;
          }
          this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
          let currentNodeIndex: number = JSON.parse(extraParams).selectedIndex;
          let currentNodeInfo: NodeInfo = this.listNodeDataSource.getData(currentNodeIndex) as NodeInfo;
          let currentItemNodeId: number = itemInner.getNodeCurrentNodeId();
          /* handle the situation of drag error, currentNodeIndex is not found in onDragStart. */
          if (currentNodeIndex >= this.listNodeDataSource.totalCount() || currentNodeIndex === undefined) {
            hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found in onDragStart');
            return;
          }

          this.listNodeDataSource.setIsInnerDrag(true);
          this.listNodeDataSource.setIsDrag(true);
          this.listNodeDataSource.setCurrentNodeInfo(currentNodeInfo);
          this.listNodeDataSource.setDraggingCurrentNodeId(currentNodeInfo?.getNodeCurrentNodeId());
          this.listNodeDataSource.setDraggingParentNodeId(currentNodeInfo?.getNodeParentNodeId());

          /* set the opacity of the dragging node. */
          let draggingNodeOpacity: number = DRAG_OPACITY;
          this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
          this.listNodeDataSource.notifyDataChange(currentNodeIndex);

          /**
           * handle the situation of drag is too fast,it attribute a fault to OH.
           * OH has Solved on real machine.
           */
          if (currentItemNodeId !== currentNodeInfo?.getNodeCurrentNodeId()) {
            hilog.error(LOG_CODE, TAG, 'drag is too fast, it attribute a fault to OH');
            this.listNodeDataSource.setIsDrag(false);
            return;
          }

          return this.draggingPopup(currentNodeInfo);
        })
      }, (item: NodeInfo) => JSON.stringify(item))
    }

    /* Move the dragged node. */
    .onDragMove((event: DragEvent, extraParams: string) => {
      if (this.isMultiPress) {
        hilog.error(LOG_CODE, TAG, 'drag error, a item has been dragged');
        return;
      }
      let nodeHeight: number = LIST_ITEM_HEIGHT;

      /* flag the position of the focus on the node. */
      let flag: Flag = Math.floor(
        event.getY() /
          (nodeHeight / FLAG_NUMBER)) %
        FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;

      /* Record the node position to which the dragged node moves. */
      let index: number = JSON.parse(extraParams).insertIndex;

      /* Handle the situation where the focus(index) exceeds the list area. */
      let isOverBorder: boolean = false;
      if (index >= this.listNodeDataSource.totalCount()) {
        flag = Flag.DOWN_FLAG;
        index = this.listNodeDataSource.totalCount() - 1;
        this.listNodeDataSource.getData(index)?.setIsOverBorder(true);
        isOverBorder = true;
      } else {
        this.listNodeDataSource.getData(index)?.setIsOverBorder(false);
      }

      let currentNodeInfo: NodeInfo | undefined = this.listNodeDataSource.getData(index);
      let currentNodeId: number | undefined = currentNodeInfo?.getNodeCurrentNodeId();

      /**
       * handle a situation that "draggingCurrentNodeId" is parent of "insertNodeCurrentNodeId";
       * do not perform some functions.
       */
      if (index !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
        let isParentNodeOfInsertNode: boolean = this.listNodeDataSource.getIsParentOfInsertNode(currentNodeId);
        if (isParentNodeOfInsertNode) {
          this.listNodeDataSource.setPassIndex(index);
          if (currentNodeId !== undefined) {
            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(
              this.listNodeDataSource.findIndex(currentNodeId));
          }
          this.listNodeDataSource.setFlag(Flag.NONE);
          return;
        }
      }
      this.listNodeDataSource.setLastPassIndex(index);

      /* Set the visibility of the flag line. */
      this.listNodeDataSource.setVisibility(flag, index - 1, isOverBorder);

      /* Automatically HighLight one second delay and expand after two second delay. */
      if (currentNodeId !== undefined && currentNodeId !== this.listNodeDataSource.getDraggingCurrentNodeId()) {
        this.listNodeDataSource.delayHighLightAndExpandNode(this.listNodeDataSource.findIndex(currentNodeId),
          currentNodeId, index);
      }
    })

    /* DragEvent Enter. */
    .onDragEnter((event: DragEvent, extraParams: string) => {
      if (this.listNodeDataSource.getIsInnerDrag()) {
        this.listNodeDataSource.setIsDrag(true);

        /* set the opacity of the dragging node. */
        let draggingNodeOpacity: number = DRAG_OPACITY;
        this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
      }
    })

    /* DragEvent Leave. */
    .onDragLeave((event: DragEvent, extraParams: string) => {
      this.listNodeDataSource.hideLastLine();
      this.listNodeDataSource.clearLastTimeoutHighLight();
      this.listNodeDataSource.clearLastTimeoutExpand();
      let draggingNodeOpacity: number = DRAG_OPACITY_NONE;
      this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
      this.listNodeDataSource.setIsDrag(false);
      this.listNodeDataSource.notifyDataReload();
    })

    /* DragEvent Drop. */
    .onDrop((event: DragEvent, extraParams: string) => {
      this.listNodeDataSource.clearLastTimeoutExpand();
      let draggingNodeOpacity: number = DRAG_OPACITY_NONE;
      this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
      let insertNodeIndex: number = JSON.parse(extraParams).insertIndex;
      let currentNodeIndex: number = this.dropSelectedIndex;

      if (currentNodeIndex - 1 > this.listNodeDataSource.totalCount() || currentNodeIndex === undefined) {
        hilog.error(LOG_CODE, TAG, 'drag error, currentNodeIndex is not found');
        this.listNodeDataSource.setIsDrag(false);
        return;
      }

      if (insertNodeIndex === this.listNodeDataSource.totalCount()) {
        hilog.info(LOG_CODE, TAG, 'need to insert into the position of the last line');
        insertNodeIndex -= 1;
      }

      let insertNodeInfo: NodeInfo | undefined = this.listNodeDataSource.getData(insertNodeIndex);
      if (insertNodeInfo === undefined) {
        return;
      }
      let insertNodeCurrentNodeId: number = insertNodeInfo.getNodeCurrentNodeId();

      /* outer node is move in. */
      if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
        this.listNodeDataSource.clearLastTimeoutHighLight();
        this.listNodeDataSource.setIsInnerDrag(false);
        this.listNodeDataSource.hideLastLine();
        this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
        this.listNodeDataSource.refreshSubtitle(insertNodeCurrentNodeId);
        this.listNodeDataSource.notifyDataReload();
        return;
      }

      let currentNodeInfo: NodeInfo | null = this.listNodeDataSource.getCurrentNodeInfo();
      let insertNodeParentNodeId: number = insertNodeInfo.getNodeParentNodeId();
      let draggingCurrentNodeId: number = this.listNodeDataSource.getDraggingCurrentNodeId();
      let draggingParentNodeId: number = this.listNodeDataSource.getDraggingParentNodeId();

      /**
       * handle a situation that "draggingCurrentNodeId" is parent of "insertNodeCurrentNodeId".
       * drag is fail.
       */
      let isParentNodeOfInsertNode: boolean = this.listNodeDataSource.getIsParentOfInsertNode(insertNodeCurrentNodeId);
      if (isParentNodeOfInsertNode) {
        this.listNodeDataSource.clearLastTimeoutHighLight();
        this.listNodeDataSource.setIsInnerDrag(false);
        this.listNodeDataSource.hideLastLine();
        this.listNodeDataSource.notifyDataChange(insertNodeIndex);
        this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
        this.listNodeDataSource.setIsDrag(false);

        /* set the position of focus. */
        let currentFocusIndex: number = this.listNodeDataSource.findIndex(draggingCurrentNodeId);
        this.listNodeDataSource.setClickIndex(currentFocusIndex);
        this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);
        return;
      }

      /* Collapse drag node. */
      if (this.listNodeDataSource.getExpandAndCollapseInfo(draggingCurrentNodeId) === NodeStatus.EXPAND) {
        this.listNodeDataSource.expandAndCollapseNode(
          this.listNodeDataSource.findIndex(draggingCurrentNodeId));
      }

      let flag: boolean = false;

      /* Expand insert node. */
      if (this.listNodeDataSource.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === NodeStatus.COLLAPSE) {
        let currentIndex: number = this.listNodeDataSource.findIndex(insertNodeCurrentNodeId);
        if (this.listNodeDataSource.listNode[currentIndex].getIsHighLight()) {
          this.listNodeDataSource.expandAndCollapseNode(currentIndex);
        }
        flag = true;
      }

      /* alter dragNode. */
      this.listNodeDataSource.setLastDelayHighLightId();
      if (currentNodeInfo !== null && draggingCurrentNodeId !== insertNodeCurrentNodeId) {
        this.listNodeDataSource.alterDragNode(insertNodeParentNodeId, insertNodeCurrentNodeId,
          draggingParentNodeId, draggingCurrentNodeId, currentNodeInfo);
        this.listNodeDataSource.hideLastLine();
      } else {
        /*the position of dragNode is equal with the position of insertNode. */
        this.listNodeDataSource.hideLastLine();
        this.listNodeDataSource.setLastPassId(draggingCurrentNodeId);
        this.listNodeDataSource.hideLastLine();
      }
      let lastDelayHighLightIndex: number =
        this.listNodeDataSource.findIndex(this.listNodeDataSource.getLastDelayHighLightId());
      this.listNodeDataSource.setLastDelayHighLightIndex(lastDelayHighLightIndex);
      this.listNodeDataSource.clearLastTimeoutHighLight();
      this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
      this.listNodeDataSource.setIsDrag(false);

      /* set the position of focus. */
      let currentFocusIndex: number = this.listNodeDataSource.findIndex(draggingCurrentNodeId);
      this.listNodeDataSource.setClickIndex(currentFocusIndex);
      this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);

      /* innerDrag is over. */
      this.listNodeDataSource.setIsInnerDrag(false);
      this.listNodeDataSource.notifyDataReload();

      this.listNodeDataSource.listNode[currentFocusIndex].fontColor = this.treeViewTheme.primaryTitleActiveFontColor;
      if (this.viewLastIndex !== -1 && currentNodeIndex !== this.viewLastIndex) {
        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .mainTitleNode?.setMainTitleSelected(false);
        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .mainTitleNode?.setMainTitleHighLight(false);
      }

      if (this.listNodeDataSource.listNode[this.viewLastIndex] !== null) {
        this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = this.treeViewTheme.primaryTitleFontColor;
      }

      this.listNodeDataSource.lastIndex = this.viewLastIndex;
      if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
        if (this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .imageNode !== null) {

          this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
            .imageNode?.setImageSource(InteractionStatus.NORMAL);
          this.listNodeDataSource.listNode[this.viewLastIndex].imageSource =
            this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
              .imageNode?.source;
        }
      }

      if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
        this.listNodeDataSource.listNode[this.viewLastIndex]
          .setNodeColor($r('sys.color.ohos_id_color_background_transparent'));
      }

      this.listNodeDataSource.lastIndex = currentFocusIndex;
    })
  }
}

/**
 * Declare CallbackParam
 * @type CallbackParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Declare CallbackParam
 * @type CallbackParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export interface CallbackParam {
  /**
   * Get the currentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Get the currentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  currentNodeId: number,

  /**
   * Get the parentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Get the parentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  parentNodeId?: number,

  /**
   * Get the childIndex.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Get the childIndex.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  childIndex?: number,
}

/**
 * Declare NodeParam
 * @typedef NodeParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Declare NodeParam
 * @typedef NodeParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export interface NodeParam {
  /**
   * Set the parentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set the parentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  parentNodeId?: number,

  /**
   * Set currentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set currentNodeId.
   * @type { number }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  currentNodeId?: number,

  /**
   * Set catalog whether is floder.
   * @type { boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set catalog whether is floder.
   * @type { boolean }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  isFolder?: boolean,

  /**
   * Set the icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set the icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  icon?: ResourceStr,

  /**
   * Set selected icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set selected icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  selectedIcon?: ResourceStr,

  /**
   * Set edit icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set edit icon resource.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  editIcon?: ResourceStr,

  /**
   * Set primary title content.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set primary title content.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  primaryTitle?: ResourceStr,

  /**
   * Set secondary title content.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set secondary title content.
   * @type { ResourceStr }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  secondaryTitle?: ResourceStr,

  /**
   * Set subcomponent binded on tree item.
   * @type { () => void }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Set subcomponent binded on tree item.
   * @type { () => void }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  container?: () => void,
}

/**
 * Declare TreeController.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 10
 */
/**
 * Declare TreeController.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @atomicservice
 * @since 11
 */
export class TreeController {
  public readonly ROOT_NODE_ID: number = -1;
  private nodeIdList: number[] = [];
  private listNodeDataSource: ListNodeDataSource = new ListNodeDataSource();
  private initBuild: boolean = true;
  public treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();

  public getListNodeDataSource(): ListNodeDataSource {
    return this.listNodeDataSource;
  }

  public getClickNodeChildrenInfo(): NodeInfoView[] {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    return this.listNodeDataSource.getClickNodeChildrenInfo(clickNodeId);
  }

  public getChildrenId(): number[] {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    return this.listNodeDataSource.getClickChildId(clickNodeId);
  }

  /**
   * Delete a node.
   * Register an ON_ITEM_DELETE callback through the EventBus mechanism to obtain the IDs of all deleted nodes.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Delete a node.
   * Register an ON_ITEM_DELETE callback through the EventBus mechanism to obtain the IDs of all deleted nodes.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public removeNode(): void {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    if (clickNodeId < 0) {
      return;
    }
    let parentNodeId: number = this.listNodeDataSource.findParentNodeId(clickNodeId);
    let removeNodeIdList: number[] = this.listNodeDataSource.removeNode(clickNodeId, parentNodeId);
    this.listNodeDataSource.refreshData(
      MenuOperation.REMOVE_NODE,
      parentNodeId,
      removeNodeIdList
    );
    this.nodeIdList.splice(this.nodeIdList.indexOf(clickNodeId), 1);
    this.listNodeDataSource.lastIndex = -1;
  }

  /**
   * Modify the node name.
   * Register an ON_ITEM_MODIFY callback to obtain the ID, parent node ID, and node name of the modified node.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Modify the node name.
   * Register an ON_ITEM_MODIFY callback to obtain the ID, parent node ID, and node name of the modified node.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public modifyNode(): void {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    this.listNodeDataSource.setItemVisibilityOnEdit(clickNodeId, MenuOperation.MODIFY_NODE);
  }

  /**
   * add new node
   *
   * @param initBuild whether is in initialization process
   */
  public add(initBuild: boolean): void {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    if (clickNodeId === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(clickNodeId)) {
      return;
    }
    let newNodeParam: NodeParam = this.listNodeDataSource.getNewNodeParam(clickNodeId);
    this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
    let newNodeId: number = this.nodeIdList[this.nodeIdList.length - 1];
    let addNodeResult: boolean = this.listNodeDataSource.addNode(clickNodeId, newNodeId,
      {
        isFolder: newNodeParam.isFolder,
        icon: newNodeParam.icon,
        selectedIcon: newNodeParam.selectedIcon,
        editIcon: newNodeParam.editIcon,
        primaryTitle: '新建文件夹',
        container: newNodeParam.container,
        secondaryTitle: newNodeParam.secondaryTitle as ResourceStr,
      }, initBuild);
    if (!addNodeResult) {
      return;
    }
    this.listNodeDataSource.refreshData(MenuOperation.ADD_NODE, clickNodeId, [newNodeId]);

    this.listNodeDataSource.setPopUpInfo(
      PopUpType.WARNINGS,
      InputError.NONE,
      false,
      this.listNodeDataSource.getLastIndex()
    );
    this.listNodeDataSource.setItemVisibilityOnEdit(
      this.listNodeDataSource.getLastIndex(),
      MenuOperation.COMMIT_NODE
    );
    this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()]
      .setFontColor(this.treeViewTheme.primaryTitleFontColor);
    let newNodeIndex: number = this.listNodeDataSource.findIndex(newNodeId);
    this.listNodeDataSource.setClickIndex(newNodeIndex);
    this.listNodeDataSource.handleEvent(Event.TOUCH_UP, newNodeIndex);
  }

  /**
   * Initialize the interface of the tree view. This interface is used to generate ListNodeDataSource data.
   * addNode is only designed for initialization. It can only be invoked during initialization.
   *
   * A maximum of 50 directory levels can be added.
   *
   * @param nodeParam Configuration information of the newly added node.
   *
   * For details, see the comment description of NodeParam.
   * @return ListTreeNode Tree view component proxy class.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * Initialize the interface of the tree view. This interface is used to generate ListNodeDataSource data.
   * addNode is only designed for initialization. It can only be invoked during initialization.
   *
   * A maximum of 50 directory levels can be added.
   *
   * @param nodeParam Configuration information of the newly added node.
   *
   * For details, see the comment description of NodeParam.
   * @return ListTreeNode Tree view component proxy class.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public addNode(nodeParam?: NodeParam): TreeController {
    if (nodeParam === undefined) {
      this.add(this.initBuild);
      return this;
    } else {
      let addNodeResult: boolean = false;
      if (nodeParam.primaryTitle !== undefined &&
        !this.listNodeDataSource.checkMainTitleIsValid(nodeParam.primaryTitle.toString())) {
        throw new Error('ListTreeNode[addNode]: ' +
          'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
        return this;
      }
      if (nodeParam.primaryTitle === null && nodeParam.icon === null) {
        throw new Error('ListTreeNode[addNode]: ' +
          'The icon and directory name cannot be empty at the same time.');
        return this;
      }
      if (nodeParam.currentNodeId === this.ROOT_NODE_ID || nodeParam.currentNodeId === null) {
        throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
        return this;
      }
      if (nodeParam.currentNodeId !== undefined) {
        this.nodeIdList.push(nodeParam.currentNodeId);
      }
      if (nodeParam.parentNodeId !== undefined) {
        if (nodeParam.currentNodeId !== undefined) {
          addNodeResult =
            this.listNodeDataSource.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam, this.initBuild);
        }
      }
      if (!addNodeResult) {
        return this;
      }
      if (!this.initBuild && nodeParam.parentNodeId !== undefined) {
        let newNodeId: number = this.nodeIdList[this.nodeIdList.length - 1];
        this.listNodeDataSource.refreshData(
          MenuOperation.ADD_NODE,
          nodeParam.parentNodeId,
          [newNodeId]
        );
      }
      return this;
    }
  }

  /**
   * this interface is called when a secondaryTitle needs to be updated.
   *
   * @Param parentId ID of the parent node.
   * @Param parentSubTitle secondaryTitle of parent node.
   * @Param currentSubTitle secondaryTitle of current node.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * this interface is called when a secondaryTitle needs to be updated.
   *
   * @Param parentId ID of the parent node.
   * @Param parentSubTitle secondaryTitle of parent node.
   * @Param currentSubTitle secondaryTitle of current node.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public refreshNode(parentId: number, parentSubTitle: ResourceStr, CurrentSubtitle: ResourceStr): void {
    this.listNodeDataSource.setNodeSubtitlePara(parentId, parentSubTitle, CurrentSubtitle);
  }

  /**
   * After the initialization is complete by calling the addNode interface,
   * call this interface to complete initialization.
   *
   * This interface must be called when you finish initializing the ListTreeView by addNode.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 10
   */
  /**
   * After the initialization is complete by calling the addNode interface,
   * call this interface to complete initialization.
   *
   * This interface must be called when you finish initializing the ListTreeView by addNode.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @atomicservice
   * @since 11
   */
  public buildDone(): void {
    this.listNodeDataSource.initSection();
    this.listNodeDataSource.delayInit();
    this.listNodeDataSource.updateAllChildNum();
    delaySortNodeIdList(this.nodeIdList);
    this.initBuild = false;
  }
}

class BasicDataSource implements IDataSource {
  private listeners: DataChangeListener[] = []

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): NodeInfo | undefined {
    return undefined;
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataChange(index: number | undefined): void {
    if (index === undefined) {
      return;
    }
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }

  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }
}

/**
 * delay update all parentnodes childNum
 *
 * @param isAdd whether addNode or delete node
 * @param count node count
 * @param nodeIdNodeItemMap nodeId and nodeItem relation map
 * @param updateNodeIdList nodeId list whose childNum need update
 */
function delayUpdateParentChildNum(isAdd: boolean, count: number,
  nodeIdNodeItemMap: Map<number, NodeItem>, updateNodeIdList: Array<number>): void {
  let taskId: number = setTimeout(() => {
    updateNodeIdList.forEach((parentNodeId) => {
      updateParentChildNumHandler(parentNodeId, nodeIdNodeItemMap, isAdd, count);
    });
    clearTimeout(taskId);
  }, DELAY_TIME);
}

/**
 * delay update all parentnodes child number handler
 * 
 * @param parentNodeId parent node id
 * @param nodeIdNodeItemMap nodeId and nodeItem relation map
 * @param isAdd whether addNode or delete node
 * @param count node count
 */
function updateParentChildNumHandler(parentNodeId: number, nodeIdNodeItemMap: Map<number, NodeItem>,
  isAdd: boolean, count: number) {
  let tmpParentNodeId: number = parentNodeId;
  while (tmpParentNodeId >= 0) {
    if (nodeIdNodeItemMap.has(tmpParentNodeId)) {
      let parent: NodeItem = nodeIdNodeItemMap.get(tmpParentNodeId) as NodeItem;
      parent.getChildNodeInfo().allChildNum =
        isAdd ? parent.getChildNodeInfo().allChildNum + count : parent.getChildNodeInfo().allChildNum - count;
      tmpParentNodeId = parent.parentNodeId;
    } else {
      hilog.error(LOG_CODE, TAG, 'updateParentChildNumHandler: parent node not found');
      break;
    }
  }
}

/**
 * delay sort nodeId list
 *
 * @param nodeIdList nodeId list
 */
function delaySortNodeIdList(nodeIdList: Array<number>): void {
  let taskId: number = setTimeout(() => {
    nodeIdList.sort((a, b) => a - b);
    clearTimeout(taskId);
  }, DELAY_TIME);
}

class ListNodeDataSource extends BasicDataSource {
  public readonly ROOT_NODE_ID = -1;
  public _root: NodeItem = new NodeItem(emptyNodeInfo);
  private readonly maxNodeLevel: number = 50;
  private readonly MAX_CN_LENGTH: number = 254;
  private readonly MAX_EN_LENGTH: number = 255;
  private readonly INITIAL_INVALID_VALUE = -1;
  public listNode: NodeInfo[] = [];
  public loadedListNode: NodeInfo[] = [];
  public nodeIdNodeItemMap: Map<number, NodeItem> = new Map<number, NodeItem>();
  public nodeIdNodeParamMap: Map<number, NodeParam> = new Map<number, NodeParam>();
  public lastIndex: number = -1; // record the last focused node.
  public thisIndex: number = -1; // records clicked nodes in the current period.
  private modifyNodeIndex: number = -1; // records the nodes edited in the current period.
  public modifyNodeId: number = -1;
  private currentOperation?: MenuOperation;
  private expandAndCollapseInfo: Map<number, NodeStatus> = new Map<number, NodeStatus>();
  public loadedNodeIdAndIndexMap: Map<number, number> = new Map<number, number>();
  public nodeIdAndNodeIndexMap: Map<number, number> = new Map<number, number>();
  private isTouchDown: boolean = false;
  private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
  /* parameter of the drag event. */
  private isInnerDrag: boolean = false; // Judge whether it is an internal drag event.
  // It is used to handle events(For example, prevent press events) during global drag.
  private isDrag: boolean = false;
  private draggingCurrentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the current ID of the dragged node.
  private draggingParentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the parent ID of the dragged node.
  private currentNodeInfo: NodeInfo | null = null; // To solve the problem of currentIndex missed in onDrop event.
  private listItemOpacity: number = 1; // It is used to set the opacity of the node when dragged.
  private lastPassIndex: number = this.INITIAL_INVALID_VALUE; // record the last passing node index in drag.
  private lastPassId?: number = this.INITIAL_INVALID_VALUE; // record the last passing node Id in drag.
  private thisPassIndex: number = this.INITIAL_INVALID_VALUE; // record the current passing node in drag.
  // record last passing node in delay expand event.
  private lastDelayExpandIndex: number = this.INITIAL_INVALID_VALUE;
  private timeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private lastTimeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private clearTimeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private timeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  private lastTimeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  private clearTimeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  // record last passing node in HighLight event.
  private lastDelayHighLightIndex: number = this.INITIAL_INVALID_VALUE;
  //record last passing node Id in HighLight event.
  private lastDelayHighLightId: number = this.INITIAL_INVALID_VALUE;
  private nodeIdAndSubtitleMap: Map<number, ResourceStr> = new Map<number, ResourceStr>();
  private flag: Flag = Flag.NONE;
  private selectedParentNodeId: number = this.INITIAL_INVALID_VALUE;
  private selectedParentNodeSubtitle: ResourceStr = '';
  private insertNodeSubtitle: ResourceStr = '';
  private currentFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  private lastFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  private addFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  private treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();
  public updateNodeIdList: number[] = [];
  public readonly FLAG_LINE: FlagLine = {
    flagLineHeight: FLAG_LINE_HEIGHT,
    flagLineColor: $r('sys.color.ohos_id_color_emphasize'),
    xOffset: X_OFF_SET,
    yTopOffset: Y_OFF_SET,
    yBottomOffset: Y_BOTTOM_OFF_SET,
    yBasePlateOffset: Y_BASE_PLATE_OFF_SET,
  }
  private readonly DRAG_POPUP: DragPopup = {
    floorConstraintSize: { minWidth: FLOOR_MIN_WIDTH, maxWidth: FLOOR_MAX_WIDTH },
    textConstraintSize: {
      minWidth1: TEXT_MIN_WIDTH,
      maxWidth1: TEXT_MAX_WIDTH,
      minWidth2: MIN_WIDTH,
      maxWidth2: MAX_WIDTH,
    },
    padding: { left: $r('sys.float.padding_level4'), right: $r('sys.float.padding_level4') },
    backgroundColor: COLOR_IMAGE_EDIT,
    height: GRAG_POP_UP_HEIGHT,
    shadow: {
      radius: $r('sys.float.ohos_id_corner_radius_default_m'),
      color: SHADOW_COLOR,
      offsetX: 0,
      offsetY: SHADOW_OFFSETY,
    },
    borderRadius: $r('sys.float.ohos_id_corner_radius_clicked'),
    fontColor: this.treeViewTheme.primaryTitleFontColor,
    fontSize: $r('sys.float.ohos_id_text_size_body1'),
    fontWeight: FontWeight.Regular,
    imageOpacity: $r('sys.float.ohos_id_alpha_content_fourth')
  };
  private readonly subTitle: SubTitleStyle = {
    normalFontColor: this.treeViewTheme.secondaryTitleFontColor,
    highLightFontColor: $r('sys.color.ohos_id_color_primary_contrary'),
    fontSize: $r('sys.float.ohos_id_text_size_body2'),
    fontWeight: FontWeight.Regular,
    margin: { left: $r('sys.float.padding_level2'), right: $r('sys.float.padding_level12') }
  }

  constructor() {
    super();
    this._root.nodeLevel = -1;
    this.nodeIdNodeItemMap.set(-1, this._root);
    this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
  }

  private checkIndex(index: number): boolean {
    if (index < 0 || index >= this.listNode.length) {
      hilog.error(LOG_CODE, TAG, 'check index fail');
      return false;
    }
    return true;
  }

  public changeNodeColor(index: number, color: ResourceColor | undefined): void {
    if (!this.checkIndex(index)) {
      return;
    }
    this.listNode[index].setNodeColor(color);
    this.listNode[index].setNodeBorder(false);
  }

  private getNodeColor(index: number): ResourceColor {
    return this.listNode[index].getNodeColor();
  }

  private handleFocusEffect(index: number, isClearFocusStatus: boolean): void {
    if (this.listNode[index].getNodeIsShow()) {
      this.listNode[index].setNodeBorder(isClearFocusStatus);
    }
  }

  public setImageSource(index: number, interactionStatus: InteractionStatus): void {
    if (!this.checkIndex(index)) {
      return;
    }
    let nodeInfo: NodeInfo = this.listNode[index];
    nodeInfo.setIsSelected(interactionStatus === InteractionStatus.SELECTED ||
      interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.FINISH_EDIT);
    if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DRAG_INSERT &&
      interactionStatus !== InteractionStatus.FINISH_DRAG_INSERT) {
      nodeInfo.getNodeItem().mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.SELECTED ||
        interactionStatus === InteractionStatus.FINISH_EDIT);
    }
    if (nodeInfo.getNodeItem().imageNode !== null) {
      nodeInfo.getNodeItem().imageNode?.setImageSource(interactionStatus);
    }
  }

  private setImageCollapseSource(index: number, interactionStatus: InteractionStatus): void {
    let nodeInfo: NodeInfo = this.listNode[index];
    if (nodeInfo.getNodeItem().imageCollapse !== undefined) {
      nodeInfo.getNodeItem().imageCollapse = CollapseImageNodeFlyweightFactory.getCollapseImageNode(interactionStatus,
        this.expandAndCollapseInfo.get(nodeInfo.getNodeCurrentNodeId()), nodeInfo.getNodeItem().imageCollapse?.type);
    }
  }

  public clearLastIndexStatus(): void {
    if (!this.checkIndex(this.lastIndex)) {
      return;
    }
    this.setImageSource(this.lastIndex, InteractionStatus.NORMAL);
    this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
    this.handleFocusEffect(this.lastIndex, false);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getNodeCurrentNodeId()));
  }

  private loadedListNodeFunction(): void {
    let index: number = 0;
    this.loadedNodeIdAndIndexMap.clear();
    this.nodeIdAndNodeIndexMap.clear();
    this.loadedListNode.splice(0, this.loadedListNode.length);
    for (let i: number = 0; i < this.listNode.length; i++) {
      this.nodeIdAndNodeIndexMap.set(this.listNode[i].getNodeCurrentNodeId(), i);
      if (this.listNode[i].getNodeIsShow()) {
        this.loadedNodeIdAndIndexMap.set(this.listNode[i].getNodeCurrentNodeId(), index++);
        this.loadedListNode.push(this.listNode[i]);
      }
    }
  }

  private changeNodeStatus(clickIndex: number): void {
    if (clickIndex >= this.listNode.length) {
      hilog.error(LOG_CODE, TAG, 'changeNodeStatus clickIndex error.');
      return;
    }
    let thisIndex: number = clickIndex;
    let nodeId: number = this.listNode[clickIndex].getNodeCurrentNodeId();
    if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.EXPAND) {
      this.expandAndCollapseInfo.set(nodeId, NodeStatus.COLLAPSE);
      this.listNode[thisIndex].getNodeItem()
        .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
          this.listNode[thisIndex].getNodeItem().imageCollapse?.isCollapse);
    } else if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.COLLAPSE) {
      this.expandAndCollapseInfo.set(nodeId, NodeStatus.EXPAND);
      this.listNode[thisIndex].getNodeItem()
        .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
        this.listNode[thisIndex].getNodeItem().imageCollapse?.isCollapse);
    }
  }

  private handleExpandAndCollapse(clickIndex: number, isRefreshList: boolean): void {
    if (clickIndex >= this.listNode.length) {
      hilog.error(LOG_CODE, TAG, 'handleExpandAndCollapse clickIndex error.');
      return;
    }
    let thisIndex: number = clickIndex;
    let nodeId: number = this.listNode[thisIndex].getNodeCurrentNodeId();
    if (!this.expandAndCollapseInfo.has(nodeId)) {
      return;
    }

    let rootNodeStatus: NodeStatus | undefined = this.expandAndCollapseInfo.get(nodeId);
    if (this.listNode[thisIndex].getChildNodeInfo().isHasChildNode && rootNodeStatus === NodeStatus.COLLAPSE) {
      for (let i: number = 0; i < this.listNode[thisIndex].getChildNodeInfo().allChildNum; i++) {
        if (this.listNode[thisIndex + 1 + i] === undefined) {
          return;
        }
        this.listNode[thisIndex + 1 + i].setNodeIsShow(false);
        this.listNode[thisIndex + 1 + i].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
      }
      this.loadedListNodeFunction();
      this.notifyDataReload();
      return;
    }

    let childNum: number[] | null = new Array(this.listNode[thisIndex].getChildNodeInfo().childNum);
    childNum[0] = thisIndex + 1;
    let index: number = 1;
    while (index < this.listNode[thisIndex].getChildNodeInfo().childNum) {
      childNum[index] = childNum[index - 1] + this.listNode[childNum[index - 1]].getChildNodeInfo().allChildNum + 1;
      index++;
    }
    if (rootNodeStatus === NodeStatus.EXPAND) {
      for (let i: number = 0; i < childNum.length; i++) {
        if (this.listNode[childNum[i]] === undefined) {
          return;
        }
        this.listNode[childNum[i]].setNodeIsShow(true);
        this.listNode[childNum[i]].setListItemHeight(LIST_ITEM_HEIGHT);
        let nodeId: number = this.listNode[childNum[i]].getNodeCurrentNodeId();
        if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.EXPAND) {
          this.handleExpandAndCollapse(childNum[i], false);
        }
      }
    }
    childNum = null;
    if (isRefreshList) {
      this.loadedListNodeFunction();
      this.notifyDataReload();
    }
  }

  /**
   * update all parentNodes childNum
   */
  public updateAllChildNum(): void {
    delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, this.updateNodeIdList);
  }

  private resetData(listNode: Array<NodeInfo>): void {
    listNode.splice(0, listNode.length);
    this.loadedNodeIdAndIndexMap.clear();
    this.loadedListNode.splice(0, this.loadedListNode.length);
    this.nodeIdAndNodeIndexMap.clear();
    this.nodeIdAndSubtitleMap.clear();
  }

  private initHandler(listNode: Array<NodeInfo>, startLevel: number, endLevel?: number): void {
    let index: number = 0;
    let listIndex: number = 0;
    this.resetData(listNode);
    try {
      this.traverseSectionNodeDF((node: NodeItem): boolean => {
        if (node.getCurrentNodeId() >= 0 && this.nodeIdNodeParamMap.has(node.getCurrentNodeId())) {
          let nodeInfo: NodeInfo =
            new NodeInfo(node, this.nodeIdNodeParamMap.get(node.getCurrentNodeId()) as NodeParam);
          nodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
          listNode.push(nodeInfo);
          this.nodeIdAndNodeIndexMap.set(nodeInfo.getNodeCurrentNodeId(), listIndex++);
          index = this.nodeDFHandler(nodeInfo, index);
        }
        return false;
      }, this._root, startLevel, endLevel);
    } catch (err) {
      hilog.error(LOG_CODE, TAG, 'traverseSectionNodeDF function callbacks error.');
      this.resetData(listNode);
    }
  }

  private nodeDFHandler(nodeInfo: NodeInfo, index: number): number {
    if (nodeInfo.getChildNodeInfo().isHasChildNode) {
      this.expandAndCollapseInfo.set(nodeInfo.getNodeCurrentNodeId(), NodeStatus.COLLAPSE);
    }
    if (nodeInfo.getNodeIsShow()) {
      this.loadedNodeIdAndIndexMap.set(nodeInfo.getNodeCurrentNodeId(), index++);
      this.loadedListNode.push(nodeInfo);
    }
    if (nodeInfo.getIsFolder()) {
      if (nodeInfo.getNodeInfoData().secondaryTitle !== undefined) {
        this.nodeIdAndSubtitleMap.set(
          nodeInfo.getNodeCurrentNodeId(),
          nodeInfo.getNodeInfoData().secondaryTitle as ResourceStr
        );
      } else {
        this.nodeIdAndSubtitleMap.set(nodeInfo.getNodeCurrentNodeId(), '');
      }
    }
    return index;
  }

  /**
   * update delay init all nodes
   */
  public delayInit(): void {
    let timeId: number = setTimeout(() => {
      let listNode: NodeInfo[] = [];
      this.initHandler(listNode, 0);
      this.listNode.splice(0, this.listNode.length);
      this.listNode.push(...listNode);
      this.listNode.forEach((value: NodeInfo, index: number) => {
        this.notifyDataDelete(index);
        this.notifyDataAdd(index);
      });
      clearTimeout(timeId);
    }, DELAY_TIME);
  }

  /**
   * update delay init some nodes
   */
  public initSection(): void {
    this.initHandler(this.listNode, 0, 1);
  }

  private refreshRemoveNodeData(removeNodeIdList: number[], parentNodeInfo: NodeInfo): void {
    let deleteIndexList: number[] = [];
    if (removeNodeIdList.length === 0) {
      return;
    }
    let startIndex: number | undefined = undefined;
    for (let i: number = 0; i < removeNodeIdList.length; i++) {
      if (this.loadedNodeIdAndIndexMap.has(removeNodeIdList[i])) {
        let loadedIndex: number = this.loadedNodeIdAndIndexMap.get(removeNodeIdList[i]) as number;
        deleteIndexList.push(loadedIndex);
      }
      if (startIndex === undefined && this.nodeIdAndNodeIndexMap.has(removeNodeIdList[i])) {
        startIndex = this.nodeIdAndNodeIndexMap.get(removeNodeIdList[i]);
      }
      if (startIndex !== undefined) {
        let deleteNode: NodeInfo[] | null = this.listNode.splice(startIndex, 1);
        deleteNode = null;
      }
      if (this.expandAndCollapseInfo.has(removeNodeIdList[i])) {
        this.expandAndCollapseInfo.delete(removeNodeIdList[i]); // delete deleteNode expandAndCollapseInfo.
      }
    }
    deleteIndexList.forEach((value) => {
      this.notifyDataDelete(value); // notifyDataDelete do not  update data.
      this.notifyDataChange(value); // call notifyDataChange to update data.
    })
    if (parentNodeInfo.getNodeItem().imageCollapse === null) {
      if (this.nodeIdAndNodeIndexMap.has(parentNodeInfo.getNodeCurrentNodeId())) {
        let parentIndex: number = this.nodeIdAndNodeIndexMap.get(parentNodeInfo.getNodeCurrentNodeId()) as number;
        this.listNode[parentIndex]?.handleImageCollapseAfterAddNode(false);
      }
      // delete deleteNode parentNode expandAndCollapseInfo.
      this.expandAndCollapseInfo.delete(parentNodeInfo.getNodeCurrentNodeId());
      this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(parentNodeInfo.getNodeCurrentNodeId()));
    }
    let callbackParam: CallbackParam = {
      currentNodeId: parentNodeInfo.getNodeCurrentNodeId(),
      parentNodeId: parentNodeInfo.getNodeParentNodeId(),
    };
    this.loadedListNodeFunction();
    this.appEventBus.emit(TreeListenType.NODE_DELETE, callbackParam);
  }

  private refreshAddNodeData(addNodeIdList: number[]): void {
    let addNodeInfo: NodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(addNodeIdList[0])) {
      let node: NodeItem = this.nodeIdNodeItemMap.get(addNodeIdList[0]) as NodeItem;
      addNodeInfo = new NodeInfo(node, this.nodeIdNodeParamMap.get(addNodeIdList[0]) as NodeParam);
      addNodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
    }
    addNodeInfo.setIsModify(true);

    let index: number = 0;
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeCurrentNodeId() === addNodeInfo.getNodeParentNodeId()) {
        index = i;
        if (this.listNode[i].getNodeItem().imageCollapse === null) {
          this.listNode[i].handleImageCollapseAfterAddNode(true);
          this.notifyDataChange(index);
        } else if (this.expandAndCollapseInfo.get(this.listNode[i].getNodeCurrentNodeId()) === NodeStatus.COLLAPSE) {
          this.changeNodeStatus(index);
        }
        this.listNode.splice(i + 1, 0, addNodeInfo);
        this.listNode[i + 1].setTitleAndInputTextStatus(true);
        this.listNode[i + 1].setNodeIsShow(true);
        this.listNode[i + 1].setListItemHeight(LIST_ITEM_HEIGHT);
        this.nodeIdAndNodeIndexMap.set(addNodeIdList[0], i + 1);
        this.setImageSource(i + 1, InteractionStatus.EDIT);
        this.currentOperation = MenuOperation.ADD_NODE;
        this.notifyDataAdd(i + 1);
        this.notificationNodeInfo(i + 1, this.currentOperation);
        break;
      }
    }
    this.modifyNodeIndex = index + 1;
    this.setClickIndex(index);
    this.lastIndex = index;
    this.expandAndCollapseInfo.set(addNodeInfo.getNodeParentNodeId(), NodeStatus.EXPAND);
    this.handleExpandAndCollapse(index, true);
  }

  public refreshData(operation: MenuOperation,
    parentNodeId: number, changeNodeIdList: number[]): void {
    let parentNodeInfo: NodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(parentNodeId)) {
      let parentNode: NodeItem = this.nodeIdNodeItemMap.get(parentNodeId) as NodeItem;
      parentNodeInfo = new NodeInfo(parentNode, this.nodeIdNodeParamMap.get(parentNodeId) as NodeParam);
      parentNodeInfo.addImageCollapse(parentNode.getChildNodeInfo().isHasChildNode);
    }

    if (operation === MenuOperation.REMOVE_NODE) {
      this.nodeIdAndSubtitleMap.set(parentNodeId, this.selectedParentNodeSubtitle);
      this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(parentNodeId));
      this.refreshRemoveNodeData(changeNodeIdList, parentNodeInfo);
    }

    if (operation === MenuOperation.ADD_NODE) {
      this.addFocusNodeId = changeNodeIdList[0];
      this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
      this.nodeIdAndSubtitleMap.set(changeNodeIdList[0], this.insertNodeSubtitle);
      this.refreshAddNodeData(changeNodeIdList);
    }
  }

  public setClickIndex(index: number): void {
    this.thisIndex = index;
  }

  public getClickNodeId(): number {
    if (!this.checkIndex(this.thisIndex)) {
      return -1;
    }
    return this.listNode[this.thisIndex].getNodeCurrentNodeId();
  }

  public expandAndCollapseNode(clickIndex: number): void {
    this.changeNodeStatus(clickIndex);
    this.handleExpandAndCollapse(clickIndex, true);
  }

  public getIsTouchDown(): boolean {
    return this.isTouchDown;
  }

  public getLastIndex(): number {
    return this.lastIndex;
  }

  public findIndex(currentNodeId: number): number {
    let thisIndex: number = -1;
    if (this.nodeIdAndNodeIndexMap.has(currentNodeId)) {
      thisIndex = this.nodeIdAndNodeIndexMap.get(currentNodeId) as number;
    }
    return thisIndex;
  }

  public handleEventDrag(index: number): void {
    if (!this.checkIndex(index)) {
      return;
    }
    this.setImageSource(index, InteractionStatus.NORMAL);
    this.changeNodeColor(index, this.listNode[index].getNodeStatus().normal);
    this.handleFocusEffect(index, false);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId()));
  }

  public handleEvent(event: Event, index: number): void {
    /* Return while the event is dragging event. */
    if (this.isDrag) {
      return;
    }
    if (!this.checkIndex(index)) {
      return;
    }

    if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
      if (index !== this.lastIndex) {
        this.clearLastIndexStatus();
      }
    }

    this.eventHandler(index, event);
  }

  private eventHandler(index: number, event: Event): void {
    let lazyForEachIndex: number =
      this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId()) as number;
    switch (event) {
      case Event.TOUCH_DOWN:
        this.isTouchDown = true;
        this.changeNodeColor(index, this.listNode[index].getNodeStatus().press);
        this.notifyDataChange(lazyForEachIndex);
        break;
      case Event.TOUCH_UP: {
        this.touchUpHandler(index, lazyForEachIndex);
        break;
      }
      case Event.HOVER:
        if (this.getNodeColor(index) !== this.listNode[index].getNodeStatus().selected) {
          this.changeNodeColor(index, this.listNode[index].getNodeStatus().hover);
          this.notifyDataChange(lazyForEachIndex);
        }
        break;
      case Event.HOVER_OVER:
        if (this.getNodeColor(index) !== this.listNode[index].getNodeStatus().selected) {
          this.changeNodeColor(index, this.listNode[index].getNodeStatus().normal);
          this.notifyDataChange(lazyForEachIndex);
        }
        break;
      case Event.FOCUS:
        this.handleFocusEffect(index, true);
        this.notifyDataChange(lazyForEachIndex);
        break;
      case Event.BLUR:
        this.handleFocusEffect(index, false);
        this.notifyDataChange(lazyForEachIndex);
        break;
      case Event.MOUSE_BUTTON_RIGHT:
        this.lastIndex = index;
        this.finishEditing();
        break;
      case Event.DRAG:
        this.isTouchDown = false;
        let nodeInfo: NodeInfo = this.listNode[index];
        this.setImageSource(index, InteractionStatus.SELECTED);
        this.lastIndex = index;
        this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
        this.notifyDataChange(lazyForEachIndex);
        break;
      default:
        break;
    }
  }

  private touchUpHandler(index: number, lazyForEachIndex: number): void {
    if (this.isInnerDrag) {
      this.isInnerDrag = false;
    }
    this.isTouchDown = false;
    let nodeInfo: NodeInfo = this.listNode[index];
    this.setImageSource(index, InteractionStatus.SELECTED);
    nodeInfo.setFontColor(this.treeViewTheme.primaryTitleFontColor);
    this.lastIndex = index;
    this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
    this.notifyDataChange(lazyForEachIndex);
  }

  private notificationNodeInfo(addNodeId: number, operation: MenuOperation | undefined): void {
    if (operation === MenuOperation.MODIFY_NODE) {
      let modifyNodeInfo: NodeInfo = this.listNode[this.modifyNodeIndex];
      let backParamModify: CallbackParam = {
        currentNodeId: modifyNodeInfo?.getNodeCurrentNodeId(),
        parentNodeId: modifyNodeInfo?.getNodeParentNodeId(),
      };
      this.appEventBus.emit(TreeListenType.NODE_MODIFY, backParamModify);
    } else if (operation === MenuOperation.ADD_NODE) {
      let addNodeInfo: NodeInfo = this.listNode[addNodeId];
      if (addNodeInfo === undefined) {
        return;
      }
      let icon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.source : undefined;
      let selectedIcon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.selectedSource : undefined;
      let editIcon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.editSource : undefined;
      let callbackParam: CallbackParam = {
        currentNodeId: addNodeInfo?.getNodeCurrentNodeId(),
        parentNodeId: addNodeInfo?.getNodeParentNodeId(),
      };
      this.appEventBus.emit(TreeListenType.NODE_ADD, callbackParam);
    }
  }

  public finishEditing(): void {
    if (this.modifyNodeIndex !== -1) {
      this.setImageSource(this.modifyNodeIndex, InteractionStatus.FINISH_EDIT);
      this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FINISH_EDIT);
      this.listNode[this.modifyNodeIndex].setIsModify(false);
      this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(false);
      this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
      this.notifyDataChange(this.modifyNodeIndex);
    }
  }

  public setItemVisibilityOnEdit(nodeId: number, operation: MenuOperation): void {
    let index: number = -1;
    if (nodeId === -1) {
      return;
    }
    if (operation === MenuOperation.MODIFY_NODE) {
      for (let i: number = 0; i < this.listNode.length; i++) { // nodeId to find index
        if (this.listNode[i]?.getNodeCurrentNodeId() === nodeId) {
          index = i;
          break;
        }
      }
      let nodeInfo: NodeInfo = this.listNode[index];
      if (nodeInfo === undefined) {
        return;
      }
      nodeInfo.setIsModify(true);
      if (nodeInfo.getNodeItem().mainTitleNode === null) {
        return; // no title
      }

      this.currentOperation = MenuOperation.MODIFY_NODE;
      nodeInfo.setTitleAndInputTextStatus(true);
      this.setImageSource(index, InteractionStatus.EDIT);
      this.setImageCollapseSource(index, InteractionStatus.EDIT);
      this.modifyNodeIndex = index;
      if (nodeInfo.getNodeItem().inputText) {
        if (nodeInfo.getNodeItem().imageCollapse !== null) {
          nodeInfo.getNodeItem().inputText.rightMargin =
            $r('sys.float.ohos_id_text_paragraph_margin_xs');
        } else {
          nodeInfo.getNodeItem().inputText.rightMargin =
            $r('sys.float.ohos_id_elements_margin_horizontal_m');
        }
      }
      this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(nodeId));
    }
    index = nodeId;
    if (operation === MenuOperation.COMMIT_NODE) {
      let nodeInfo: NodeInfo = this.listNode[index];
      if (nodeInfo === undefined) {
        return;
      }
      nodeInfo.setTitleAndInputTextStatus(false);
      nodeInfo.setIsModify(false);
      this.setImageSource(index, InteractionStatus.FINISH_EDIT);
      this.setImageCollapseSource(index, InteractionStatus.FINISH_EDIT);
      this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
      this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(nodeInfo?.getNodeCurrentNodeId()));
    }
  }

  public setPopUpInfo(popUpType: PopUpType, inputError: InputError, isShow: boolean, index: number): void {
    if (!this.checkIndex(index)) {
      return;
    }
    let nodeInfo: NodeInfo = this.listNode[index];
    if (nodeInfo === undefined) {
      return;
    }
    nodeInfo.setPopUpIsShow(isShow);
    // this.listNode index to lazyForEach index.
    let lazyForEachIndex: number = this.loadedNodeIdAndIndexMap.get(nodeInfo.getNodeCurrentNodeId()) as number;
    if (!isShow) {
      this.notifyDataChange(lazyForEachIndex);
      return;
    }
    if (popUpType === PopUpType.HINTS) {
      if (nodeInfo.getNodeItem().mainTitleNode !== null) {
        nodeInfo.setPopUpText(nodeInfo.getNodeItem().mainTitleNode?.title);
      } else {
        nodeInfo.setPopUpText('');
        nodeInfo.setPopUpIsShow(false);
      }
      nodeInfo.setPopUpEnableArrow(false);
      nodeInfo.setPopUpColor($r('sys.color.ohos_id_color_background'));
      nodeInfo.setPopUpTextColor(this.treeViewTheme.secondaryTitleFontColor);
    } else if (popUpType === PopUpType.WARNINGS) {
      if (nodeInfo.getNodeItem().inputText !== null) {
        if (inputError === InputError.INVALID_ERROR) {
          nodeInfo.setPopUpText('invalid error');
        } else if (inputError === InputError.LENGTH_ERROR) {
          nodeInfo.setPopUpText('length error');
        }
        nodeInfo.setPopUpEnableArrow(true);
        nodeInfo.setPopUpColor($r('sys.color.ohos_id_color_help_tip_bg'));
        nodeInfo.setPopUpTextColor($r('sys.color.ohos_id_color_text_hint_contrary'));
      }
    }
    this.notifyDataChange(lazyForEachIndex);
  }

  public setShowPopUpTimeout(timeout: number, index: number): void {
    if (!this.checkIndex(index)) {
      return;
    }
    if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
      this.listNode[index].getNodeItem().mainTitleNode.popUpTimeout = timeout;
    }
    let lazyForEachIndex: number =
      this.loadedNodeIdAndIndexMap.get(this.listNode[index].getNodeCurrentNodeId()) as number;
    this.notifyDataChange(lazyForEachIndex);
  }

  public setMainTitleNameOnEdit(index: number, text: string): void {
    this.modifyNodeIndex = index;
    if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
      this.listNode[index].getNodeItem().mainTitleNode.title = text;
    }
  }

  public totalCount(): number {
    return this.loadedNodeIdAndIndexMap.size;
  }

  public getData(index: number): NodeInfo | undefined {
    if (index < 0 || index >= this.loadedListNode.length) {
      return undefined;
    }
    return this.loadedListNode[index];
  }

  public addData(index: number, data: NodeInfo): void {
    if (!this.checkIndex(index)) {
      return;
    }
    this.listNode.splice(index, 0, data);
    this.nodeIdAndNodeIndexMap.set(data.getNodeCurrentNodeId(), index);
    this.loadedListNodeFunction();
    this.notifyDataAdd(index);
  }

  public pushData(data: NodeInfo): void {
    this.listNode.push(data);
    this.nodeIdAndNodeIndexMap.set(data.getNodeCurrentNodeId(), this.listNode.length);
    this.loadedListNodeFunction();
    this.notifyDataAdd(this.listNode.length - 1);
  }

  public setIsInnerDrag(isInnerDrag: boolean): void {
    this.isInnerDrag = isInnerDrag;
  }

  public getIsInnerDrag(): boolean {
    return this.isInnerDrag;
  }

  public setIsDrag(isDrag: boolean): void {
    this.isDrag = isDrag;
  }

  public getIsDrag(): boolean {
    return this.isDrag;
  }

  public setCurrentNodeInfo(currentNodeInfo: NodeInfo | undefined): void {
    if (currentNodeInfo === undefined) {
      return;
    }
    this.currentNodeInfo = currentNodeInfo;
  }

  public getCurrentNodeInfo(): NodeInfo | null {
    return this.currentNodeInfo;
  }

  public setDraggingParentNodeId(draggingParentNodeId: number | undefined): void {
    if (draggingParentNodeId === undefined) {
      return;
    }
    this.draggingParentNodeId = draggingParentNodeId;
  }

  public getDraggingParentNodeId(): number {
    return this.draggingParentNodeId;
  }

  public getDraggingCurrentNodeId(): number {
    return this.draggingCurrentNodeId;
  }

  public setDraggingCurrentNodeId(draggingCurrentNodeId: number | undefined): void {
    if (draggingCurrentNodeId === undefined) {
      return;
    }
    this.draggingCurrentNodeId = draggingCurrentNodeId;
  }

  public setListItemOpacity(listItemOpacity: number): void {
    this.listItemOpacity = listItemOpacity;
  }

  public getListItemOpacity(item: NodeInfo): number {
    return item.getNodeCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
  }

  public getDragPopupPara(): DragPopup {
    return this.DRAG_POPUP;
  }

  public setLastPassIndex(lastPassIndex: number): void {
    this.lastPassIndex = lastPassIndex;
  }

  public getLastPassIndex(): number {
    return this.lastPassIndex;
  }

  public getIsParentOfInsertNode(insertNodeId: number | undefined): boolean {
    if (this.currentNodeInfo === null || insertNodeId === undefined) {
      return false;
    }
    let selectedNodeItem: NodeItem = this.currentNodeInfo.getNodeInfoNode();
    let parentId: number = selectedNodeItem.currentNodeId;
    let insertParentId: number | undefined = this.nodeIdNodeItemMap.get(insertNodeId as number)?.parentNodeId;
    while (insertParentId !== undefined && insertParentId !== -1) {
      if (parentId === insertParentId) {
        return true;
      } else {
        insertParentId = this.nodeIdNodeItemMap.get(insertParentId as number)?.parentNodeId;
      }
    }
    return false;
  }

  public setPassIndex(thisPassIndex: number): void {
    this.thisPassIndex = thisPassIndex;
  }

  public getPassIndex(): number {
    return this.thisPassIndex;
  }

  public clearTimeOutAboutDelayHighLightAndExpand(currentIndex: number): void {
    if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
      let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
      this.listNode.forEach((value) => {
        if (value.getNodeCurrentNodeId() === this.lastPassId) {
          value.setCanShowFlagLine(false);
          return;
        }
      })
      this.notifyDataChange(index);
    }

    if ((this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
      this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
      clearTimeout(this.lastTimeoutHighLightId);
      if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
        this.clearHighLight(this.lastDelayHighLightIndex);
        let index: number = this.loadedNodeIdAndIndexMap
          .get(this.listNode[this.lastDelayHighLightIndex].getNodeCurrentNodeId()) as number;
        this.notifyDataChange(index);
      }
      this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
    }
    this.lastTimeoutHighLightId = this.timeoutHighLightId;
    this.lastDelayHighLightIndex = currentIndex;

    if ((this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
      this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
      clearTimeout(this.lastTimeoutExpandId);
      this.clearTimeoutExpandId = this.lastTimeoutExpandId;
    }
    this.lastTimeoutExpandId = this.timeoutExpandId;
    this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
  }

  public clearHighLight(currentIndex: number): void {
    if (!this.checkIndex(currentIndex)) {
      return;
    }
    this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().normal);
    this.changeNodeHighLightColor(currentIndex, false);
    this.setImageSource(currentIndex, InteractionStatus.FINISH_DRAG_INSERT);
    this.setImageCollapseSource(currentIndex, InteractionStatus.FINISH_DRAG_INSERT);
    this.listNode[currentIndex].setIsHighLight(false);
  }

  private changeNodeHighLightColor(index: number, isHighLight: boolean): void {
    if (this.listNode[index].getNodeItem().mainTitleNode && this.listNode[index].getIsShowTitle()) {
      this.listNode[index].getNodeItem().mainTitleNode?.setMainTitleHighLight(isHighLight);
    }
  }

  public setVisibility(flag: Flag, index: number, isOverBorder: boolean): void {
    let isChanged: boolean = (this.thisPassIndex !== index || this.flag !== flag) ? true : false;
    this.thisPassIndex = index;
    if ((isChanged || isOverBorder) && this.isInnerDrag) {
      this.flag = flag;
      let currentNodeId: number | undefined = this.getData(index)?.getNodeCurrentNodeId();
      let currentNodeLevel: number | undefined = this.getData(index)?.getNodeLevel();
      if (currentNodeId !== undefined) {
        currentNodeLevel = (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.EXPAND &&
          this.flag === Flag.DOWN_FLAG) ? (currentNodeLevel ? currentNodeLevel + 1 : undefined) : currentNodeLevel;
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
          let lastIndex: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
          this.listNode.forEach((value) => {
            if (value.getNodeCurrentNodeId() === this.lastPassId) {
              value.setCanShowFlagLine(false);
            }
          })
          this.notifyDataChange(lastIndex);
        }
        if (this.flag === Flag.DOWN_FLAG && index < this.totalCount() - 1) {
          this.getData(index)?.setCanShowFlagLine(false);
          this.getData(index + 1)?.setCanShowFlagLine(true);
          this.getData(index)?.setCanShowBottomFlagLine(false);
          this.getData(index + 1)?.setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.notifyDataChange(index + 1);
          this.lastPassId = this.getData(index + 1)?.getNodeCurrentNodeId();
        } else if (this.flag === Flag.UP_FLAG && index < this.totalCount() - 1) {
          this.getData(index)?.setCanShowFlagLine(true);
          this.getData(index + 1)?.setCanShowFlagLine(false);
          this.getData(index)?.setCanShowBottomFlagLine(false);
          this.getData(index)?.setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.notifyDataChange(index + 1);
          this.lastPassId = this.getData(index)?.getNodeCurrentNodeId();
        } else if (index >= this.totalCount() - 1) {
          if (this.flag === Flag.DOWN_FLAG) {
            this.getData(index)?.setCanShowFlagLine(false);
            this.getData(index)?.setCanShowBottomFlagLine(true);
          } else {
            this.getData(index)?.setCanShowFlagLine(true);
            this.getData(index)?.setCanShowBottomFlagLine(false);
          }
          this.getData(index)?.setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.lastPassId = this.getData(index)?.getNodeCurrentNodeId();
        }
      }
    }
  }

  public delayHighLightAndExpandNode(currentIndex: number, currentNodeId: number, showIndex: number): void {
    let isChangIndex: boolean = currentIndex !== this.lastDelayExpandIndex ? true : false;
    let isOverBorder: boolean | undefined = this.getData(showIndex)?.getIsOverBorder();
    if (isOverBorder) {
      this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    } else {
      this.lastDelayExpandIndex = currentIndex;
    }
    if (isOverBorder || isChangIndex) {

      /* highLight node time-out. */
      let canDelayHighLight: boolean | undefined = !isOverBorder && (!this.isInnerDrag ||
        (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE && this.isInnerDrag) ||
        (!this.expandAndCollapseInfo.has(currentNodeId) && this.listNode[currentIndex].getIsFolder()));
      if (canDelayHighLight) {
        /* set hoverState color before highLight. */
        this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().hover);
        this.notifyDataChange(showIndex);

        let delayHighLightTime: number = this.isInnerDrag ? 1000 : 0; // ms
        this.timeoutHighLightId = setTimeout(() => {
          this.delayHighLight(currentIndex);
        }, delayHighLightTime);
      }
      if (isOverBorder || (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId)) {
        clearTimeout(this.lastTimeoutHighLightId);
        if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
          this.clearHighLight(this.lastDelayHighLightIndex);
          this.notifyDataReload();
        }
        this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
      }
      this.lastTimeoutHighLightId = this.timeoutHighLightId;
      this.lastDelayHighLightIndex = currentIndex;

      /* alter flagLine and expand node time-out. */
      if (!isOverBorder && this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE) {
        let firstChildNodeId: number | undefined =
          this.getData(showIndex)?.getNodeInfoNode().children[0]?.currentNodeId;
        let delayAlterFlagLineAndExpandNodeTime: number = 2000; // ms
        this.timeoutExpandId = setTimeout(() => {
          this.clearHighLight(this.lastDelayHighLightIndex);
          if (firstChildNodeId !== undefined) {
            this.alterFlagLineAndExpandNode(currentIndex, firstChildNodeId);
          }
        }, delayAlterFlagLineAndExpandNodeTime);
      }
      if (isOverBorder || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
        clearTimeout(this.lastTimeoutExpandId);
        this.clearTimeoutExpandId = this.lastTimeoutExpandId;
      }
      this.lastTimeoutExpandId = this.timeoutExpandId;
    }
  }

  public delayHighLight(currentIndex: number): void {
    this.listNode.forEach((value) => {
      if (value.getNodeCurrentNodeId() === this.lastPassId) {
        value.setCanShowFlagLine(false);
        value.setCanShowBottomFlagLine(false);
        return;
      }
    })
    this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().highLight);
    this.listNode[currentIndex].setIsHighLight(true);
    this.changeNodeHighLightColor(currentIndex, true);
    this.setImageSource(currentIndex, InteractionStatus.DRAG_INSERT);
    this.setImageCollapseSource(currentIndex, InteractionStatus.DRAG_INSERT);
    this.notifyDataReload();
  }

  public alterFlagLineAndExpandNode(currentIndex: number, firstChildNodeId: number): void {
    this.listNode.forEach((value) => {
      if (value.getNodeCurrentNodeId() === this.lastPassId) {
        value.setCanShowFlagLine(false);
        value.setCanShowBottomFlagLine(false);
      }
    })
    this.listNode.forEach((value) => {
      if (this.isInnerDrag && value.getNodeCurrentNodeId() === firstChildNodeId) {
        value.setCanShowFlagLine(true);
      }
    })
    this.changeNodeStatus(currentIndex);
    this.handleExpandAndCollapse(currentIndex, true);
    this.lastPassId = firstChildNodeId;
  }

  public hideLastLine(): void {
    if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
      this.listNode.forEach((value) => {
        if (value.getNodeCurrentNodeId() === this.lastPassId) {
          value.setCanShowFlagLine(false);
          value.setCanShowBottomFlagLine(false);
          return;
        }
      })
      let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
      this.notifyDataChange(index);
    }
  }

  public clearLastTimeoutHighLight(): void {
    if (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
      this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
      clearTimeout(this.lastTimeoutHighLightId);
      if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
        this.clearHighLight(this.lastDelayHighLightIndex);
      }
    }
  }

  public clearLastTimeoutExpand(): void {
    if (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
      this.clearTimeoutExpandId !== this.lastTimeoutExpandId) {
      clearTimeout(this.lastTimeoutExpandId);
    }
  }

  public getSubtitle(currentNodeId: number): string | undefined {
    if (this.nodeIdAndSubtitleMap.has(currentNodeId)) {
      if (typeof this.nodeIdAndSubtitleMap.get(currentNodeId) === 'number') {
        return this.nodeIdAndSubtitleMap.get(currentNodeId)?.toString();
      } else {
        return this.nodeIdAndSubtitleMap.get(currentNodeId) as string;
      }
    } else {
      return '';
    }
  }

  public hasSubtitle(currentNodeId: number): boolean {
    return this.nodeIdAndSubtitleMap.has(currentNodeId);
  }

  public initialParameterAboutDelayHighLightAndExpandIndex(): void {
    this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
    this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    this.lastPassIndex = this.INITIAL_INVALID_VALUE;
    this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
    this.flag = Flag.NONE;
  }

  public refreshSubtitle(insertNodeCurrentNodeId: number): void {
    this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
    this.nodeIdAndSubtitleMap.set(insertNodeCurrentNodeId, this.insertNodeSubtitle);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(insertNodeCurrentNodeId));
  }

  public setNodeSubtitlePara(
    selectedParentNodeId: number,
    selectedParentNodeSubtitle: ResourceStr,
    insertNodeSubtitle: ResourceStr): void {
    this.selectedParentNodeId = selectedParentNodeId;
    this.selectedParentNodeSubtitle = selectedParentNodeSubtitle;
    this.insertNodeSubtitle = insertNodeSubtitle;
  }

  public getInsertNodeSubtitle(): ResourceStr {
    return this.insertNodeSubtitle;
  }

  public getExpandAndCollapseInfo(currentNodeId: number): NodeStatus | undefined {
    return this.expandAndCollapseInfo.get(currentNodeId);
  }

  public getLastDelayHighLightId(): number {
    return this.lastDelayHighLightId;
  }

  public setLastDelayHighLightId(): void {
    this.listNode.forEach((value, index) => {
      if (index === this.lastDelayHighLightIndex) {
        this.lastDelayHighLightId = value.getNodeCurrentNodeId();
      }
    })
  }

  public setLastPassId(lastPassId: number): void {
    this.lastPassId = lastPassId;
  }

  public setLastDelayHighLightIndex(lastDelayHighLightIndex: number): void {
    this.lastDelayHighLightIndex = lastDelayHighLightIndex;
  }

  /**
   * Alter the current node location to a needful position.
   * 1.Create an array named 'dragNodeParam' to store dragging node information.
   * 2.Delete the dragging node from the tree.
   * 3.Add the dragging node to the tree.
   */
  public alterDragNode(rearParentNodeId: number, rearCurrentNodeId: number,
    dragParentNodeId: number, dragCurrentNodeId: number, frontNodeInfoItem: NodeInfo): void {
    let dragNodeParam: DragNodeParam[] = [];
    let parentNodeId: number = rearParentNodeId;
    let currentNodeId: number = dragCurrentNodeId;
    let nodeParam: NodeParam = frontNodeInfoItem.getNodeInfoData();
    let nodeInfo: NodeInfo | null = null;
    let nodeInfoNode: NodeItem = frontNodeInfoItem.getNodeInfoNode();
    let isHighLight: boolean = false;
    let insertChildIndex: number = this.INITIAL_INVALID_VALUE;
    let currentChildIndex: number = this.INITIAL_INVALID_VALUE;
    let isDownFlag: boolean = this.flag === Flag.DOWN_FLAG ? true : false;

    currentChildIndex = this.getChildIndex(dragParentNodeId, dragCurrentNodeId);

    insertChildIndex = this.getChildIndex(rearParentNodeId, rearCurrentNodeId) + 1;

    if (rearParentNodeId !== dragParentNodeId) {
      insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
    } else {
      if (insertChildIndex > currentChildIndex) {
        insertChildIndex = isDownFlag ? insertChildIndex : insertChildIndex - 1;
      } else {
        insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
      }
    }

    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeCurrentNodeId() === rearCurrentNodeId) {
        isHighLight = this.listNode[i].getIsHighLight();
        if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.EXPAND) {
          parentNodeId = rearCurrentNodeId;
          insertChildIndex = 0;
        } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) ===
        NodeStatus.EXPAND &&
          this.listNode[i].getCanShowFlagLine() === false) {
          parentNodeId = rearCurrentNodeId;
          insertChildIndex = 0;
        } else if (isHighLight) {
          parentNodeId = rearCurrentNodeId;
          insertChildIndex = 0;
        }
        break;
      }
    }

    let callbackParam: CallbackParam = {
      currentNodeId: currentNodeId,
      parentNodeId: parentNodeId,
      childIndex: insertChildIndex,
    }

    /* export inner drag node Id. */
    this.appEventBus.emit(TreeListenType.NODE_MOVE, callbackParam);

    /* To store dragging node information by the array named 'dragNodeParam'. */
    dragNodeParam.push({ parentId: parentNodeId, currentId: currentNodeId, data: nodeParam });

    let callback: (node: NodeItem, listNode: NodeInfo[]) => boolean = (node: NodeItem, listNode: NodeInfo[]): boolean => {
      if (node) {
        parentNodeId = node.parentNodeId;
        currentNodeId = node.currentNodeId;
        for (let i: number = 0; i < listNode.length; i++) {
          if (listNode[i].getNodeCurrentNodeId() === currentNodeId) {
            nodeInfo = listNode[i];
            break;
          }
        }
        if (nodeInfo === null) {
          return false;
        }
        let nodeParam: NodeParam = nodeInfo.getNodeInfoData();
        if (parentNodeId !== dragParentNodeId) {
          dragNodeParam.push({ parentId: parentNodeId, currentId: currentNodeId, data: nodeParam });
        }
        return false;
      }
      return false;
    }
    this.dragTraverseNodeDF(callback, nodeInfoNode, this.listNode);

    /* Delete the dragging node from the tree. */
    let removeNodeIdList: number[] = this.removeNode(dragCurrentNodeId, dragParentNodeId);
    if (removeNodeIdList.length === 0) {
      return;
    }

    /**
     * Add the dragging node to the tree
     * 1.The first dragging node is added singly, because it needs to distinguish the position to insert
     *
     * Add first node.
     */
    let insertCurrentNodeId: number = rearCurrentNodeId;
    let isAfter: boolean = isDownFlag;
    if (this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.EXPAND) {
      isAfter = false;
      this.listNode.forEach((value) => {
        if (value.getNodeCurrentNodeId() === rearCurrentNodeId && value.getCanShowFlagLine() === false) {
          if (value.getNodeInfoNode().children.length) {
            insertCurrentNodeId = value.getNodeInfoNode().children[0].currentNodeId;
          } else {
            insertCurrentNodeId = this.INITIAL_INVALID_VALUE;
          }
        }
      })
    } else if (!this.expandAndCollapseInfo.get(rearCurrentNodeId) && isHighLight) {
      this.expandAndCollapseInfo.set(rearCurrentNodeId, NodeStatus.EXPAND);
    }

    let addDragNodeResult: boolean =
      this.addDragNode(dragNodeParam[0].parentId, dragNodeParam[0].currentId, insertCurrentNodeId,
        isAfter, dragNodeParam[0].data);

    if (!addDragNodeResult) {
      return;
    }
    /* Add remaining node. */
    for (let j: number = 1; j < dragNodeParam.length; j++) {
      let addNodeResult: boolean =
        this.addNode(dragNodeParam[j].parentId, dragNodeParam[j].currentId, dragNodeParam[j].data, false);
      if (!addNodeResult) {
        return;
      }
    }

    /* Update node data and reload the array named 'listNode'. */
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeCurrentNodeId() === dragParentNodeId) {
        if (this.listNode[i].getNodeItem().imageCollapse === null) {
          this.listNode[i].handleImageCollapseAfterAddNode(false);
          this.expandAndCollapseInfo.delete(dragParentNodeId);
          break;
        }
      }
    }
    let tmp: NodeInfo[] = [...this.listNode];
    this.reloadListNode(tmp);
  }

  /**
   * Reload the array named 'listNode'
   * @param tmp
   */
  public reloadListNode(tmp: NodeInfo[]): void {
    let index: number = 0;
    let listIndex: number = 0;
    this.listNode.splice(0, this.listNode.length);
    this.loadedNodeIdAndIndexMap.clear();
    this.loadedListNode.splice(0, this.loadedListNode.length);
    this.traverseNodeDF((node: NodeItem): boolean => {
      let currentNodeId: number = node.currentNodeId;
      if (currentNodeId >= 0) {
        if (this.nodeIdNodeParamMap.has(currentNodeId)) {
          let nodeInfo: NodeInfo = new NodeInfo(node, this.nodeIdNodeParamMap.get(currentNodeId) as NodeParam);
          nodeInfo.addImageCollapse(node.getChildNodeInfo().isHasChildNode);
          this.listNode.push(nodeInfo);
          this.nodeIdAndNodeIndexMap.set(nodeInfo.getNodeCurrentNodeId(), listIndex++);
          if (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.EXPAND) {
            nodeInfo.getNodeItem()
              .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.EXPAND,
              nodeInfo.getNodeItem().imageCollapse?.isCollapse);
          } else if (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.COLLAPSE) {
            nodeInfo.getNodeItem()
              .imageCollapse = CollapseImageNodeFlyweightFactory.changeImageCollapseSource(NodeStatus.COLLAPSE,
              nodeInfo.getNodeItem().imageCollapse?.isCollapse);
          }

          for (let i: number = 0; i < tmp.length; i++) {
            if (tmp[i].getNodeCurrentNodeId() === nodeInfo.getNodeCurrentNodeId()) {
              nodeInfo.setNodeIsShow(tmp[i].getNodeIsShow());
              nodeInfo.setListItemHeight(tmp[i].getListItemHeight());
              if (nodeInfo.getNodeItem().mainTitleNode && nodeInfo.getIsShowTitle()) {
                nodeInfo.getNodeItem().mainTitleNode.title = tmp[i].getNodeItem().mainTitleNode?.title as string;
              }
              break;
            }
          }
          if (nodeInfo.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(nodeInfo.getNodeCurrentNodeId(), index++);
            this.loadedListNode.push(nodeInfo);
          }
        }
      }
      return false;
    });
  }

  public getFlagLine(): FlagLine {
    return this.FLAG_LINE;
  }

  public getVisibility(nodeInfo: NodeInfo): Visibility {
    let lastShowIndex: number = this.loadedNodeIdAndIndexMap.get(nodeInfo.getNodeCurrentNodeId()) as number - 1;
    if (lastShowIndex > this.INITIAL_INVALID_VALUE) {
      let lastNodeInfo: NodeInfo | undefined = this.getData(lastShowIndex);
      return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight() && !lastNodeInfo?.getIsHighLight()) ?
      Visibility.Visible : Visibility.Hidden;
    } else {
      return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight()) ?
      Visibility.Visible : Visibility.Hidden;
    }
  }

  public getSubTitlePara(): SubTitleStyle {
    return this.subTitle;
  }

  public getIsFolder(nodeId: number): boolean | undefined {
    if (this.loadedNodeIdAndIndexMap.has(nodeId)) {
      return this.getData(this.loadedNodeIdAndIndexMap.get(nodeId) as number)?.getIsFolder();
    }
    return false;
  }

  public getSubTitleFontColor(isHighLight: boolean): ResourceColor {
    return isHighLight ? this.subTitle.highLightFontColor : this.treeViewTheme.secondaryTitleFontColor;
  }

  private getChildIndex(rearParentNodeId: number, rearCurrentNodeId: number): number {
    let insertChildIndex: number = this.INITIAL_INVALID_VALUE;
    if (this.nodeIdNodeItemMap.has(rearParentNodeId)) {
      let node: NodeItem = this.nodeIdNodeItemMap.get(rearParentNodeId) as NodeItem;
      if (node.getCurrentNodeId() === rearParentNodeId) {
        node.children.forEach((value, index) => {
          if (value.getCurrentNodeId() === rearCurrentNodeId) {
            insertChildIndex = index;
            return;
          }
        })
      }
    }
    return insertChildIndex;
  }

  public setCurrentFocusNodeId(focusNodeId: number): void {
    this.currentFocusNodeId = focusNodeId;
  }

  public getCurrentFocusNodeId(): number {
    return this.currentFocusNodeId;
  }

  public setLastFocusNodeId(focusNodeId: number): void {
    this.lastFocusNodeId = focusNodeId;
  }

  public getLastFocusNodeId(): number {
    return this.lastFocusNodeId;
  }

  public getAddFocusNodeId(): number {
    return this.addFocusNodeId;
  }

  public setFlag(flag: Flag): void {
    this.flag = flag;
  }

  private traverseNodeDF(callback: (currentNode: NodeItem) => boolean, root: NodeItem = this._root): void {
    let stack: NodeItem[] = [];
    let found: boolean = false;
    stack.unshift(root);
    let currentNode: NodeItem = stack.shift() as NodeItem;
    while (!found && currentNode) {
      found = callback(currentNode) === true;
      if (!found) {
        stack.unshift(...currentNode.children);
        currentNode = stack.shift() as NodeItem;
      }
    }
  }

  private traverseSectionNodeDF(callback: (currentNode: NodeItem) => boolean, root: NodeItem = this._root,
    startLevel?: number, endLevel?: number): void {
    let stack: NodeItem[] = [];
    let found: boolean = false;
    let isPassNode: boolean = false;
    stack.unshift(root);
    let currentNode: NodeItem = stack.shift() as NodeItem;
    while (!found && currentNode) {
      try {
        if (startLevel !== undefined && currentNode.nodeLevel < startLevel) {
          isPassNode = true;
        }
        if (endLevel !== undefined && currentNode.nodeLevel > endLevel) {
          isPassNode = true;
        }
        if (!isPassNode) {
          found = callback(currentNode);
        }
      } catch (err) {
        throw new Error('traverseSectionNodeDF function callbacks error');
      }
      if (!found) {
        stack.unshift(...currentNode.children);
        currentNode = stack.shift() as NodeItem;
        isPassNode = false;
      }
    }
  }

  private updateParentChildNum(parentNode: NodeItem, isAdd: boolean, count: number): void {
    let parentNodeId: number = parentNode.parentNodeId;
    while (parentNodeId >= 0) {
      if (this.nodeIdNodeItemMap.has(parentNodeId)) {
        let parent: NodeItem = this.nodeIdNodeItemMap.get(parentNodeId) as NodeItem;
        parent.getChildNodeInfo().allChildNum =
          isAdd ? parent.getChildNodeInfo().allChildNum + count : parent.getChildNodeInfo().allChildNum - count;
        parentNodeId = parent.parentNodeId;
      } else {
        hilog.error(LOG_CODE, TAG, 'updateParentChildNum: parent node not found.');
        break;
      }
    }
  }

  /**
   * find parent node id
   *
   * @param currentNodeId current node id
   * @returns parent node id
   */
  public findParentNodeId(currentNodeId: number): number {
    let current: NodeItem = new NodeItem(emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(currentNodeId)) {
      current = this.nodeIdNodeItemMap.get(currentNodeId) as NodeItem;
    }
    return current.parentNodeId;
  }

  /**
   * add nodeItem in params
   *
   * @param parentNodeId parent node id
   * @param currentNodeId current node id
   * @param data  node param
   * @param initBuild whether in initialization process
   */
  public addNode(parentNodeId: number,
    currentNodeId: number,
    data: NodeParam, initBuild: boolean): boolean {
    if (this._root === null) {
      this._root = new NodeItem(emptyNodeInfo);
      this._root.nodeLevel = -1;
      this.nodeIdNodeItemMap.set(-1, this._root);
      this.nodeIdNodeParamMap.set(-1, emptyNodeInfo);
    }
    if (this.nodeIdNodeItemMap.has(parentNodeId)) {
      let parent: NodeItem = this.nodeIdNodeItemMap.get(parentNodeId) as NodeItem;
      let currentNode: NodeItem = new NodeItem(data);
      if (parent.nodeLevel > this.maxNodeLevel) {
        hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: The level of the tree view cannot exceed 50.');
        return false;
      }
      currentNode.nodeLevel = parent.nodeLevel + 1;
      currentNode.parentNodeId = parentNodeId;
      currentNode.currentNodeId = currentNodeId;
      currentNode.indexOfParent = parent.children.length;
      data.parentNodeId = parentNodeId;
      data.currentNodeId = currentNodeId;
      parent.children.push(currentNode);
      parent.getChildNodeInfo().isHasChildNode = true;
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum += 1;
      if (initBuild) {
        this.updateNodeIdList.push(parent.parentNodeId);
      } else {
        let updateNodeIdList: number[] = [];
        updateNodeIdList.push(parent.parentNodeId);
        delayUpdateParentChildNum(true, 1, this.nodeIdNodeItemMap, updateNodeIdList);
      }
      this.nodeIdNodeParamMap.set(currentNodeId, data);
      this.nodeIdNodeItemMap.set(currentNodeId, currentNode);
      return true;
    } else {
      hilog.error(LOG_CODE, TAG, 'ListDataSource[addNode]: Parent node not found.');
      return false;
    }
  }

  private freeNodeMemory(rootNode: NodeItem, removeNodeIdList: number[]): void {
    let deleteNode: NodeItem[] = [];
    let callback = (node: NodeItem): boolean => {
      deleteNode.push(node);
      return false;
    };
    this.traverseNodeDF(callback, rootNode);
    deleteNode.forEach((value: NodeItem) => {
      removeNodeIdList.push(value.getCurrentNodeId());
      this.nodeIdNodeItemMap.delete(value.getCurrentNodeId());
      this.nodeIdNodeParamMap.delete(value.getCurrentNodeId());
      value = new NodeItem(emptyNodeInfo);
    })
  }

   /**
   * remove node
   *
   * @param currentNodeId current node id
   * @param parentNodeId  parent node id
   * @returns node id list which is removed
   */
  public removeNode(currentNodeId: number, parentNodeId: number): number[] {
    if (this.nodeIdNodeItemMap.has(parentNodeId) && this.nodeIdNodeItemMap.has(currentNodeId)) {
      let parent: NodeItem = this.nodeIdNodeItemMap.get(parentNodeId) as NodeItem;
      let current: NodeItem = this.nodeIdNodeItemMap.get(currentNodeId) as NodeItem;
      let removeNodeIdList: number[] = [];
      let index: number = current.indexOfParent;
      let deleteNodeAllChildNum: number = 0;
      if (index < 0) {
        hilog.error(LOG_CODE, TAG, 'node does not exist.');
        return [];
      } else {
        deleteNodeAllChildNum = parent.children[index].getChildNodeInfo().allChildNum + 1;
        this.freeNodeMemory(parent.children[index], removeNodeIdList);
        for (let i: number = index; i < parent.children.length; i++) {
          parent.children[i].indexOfParent -= 1;
        }
        let node: NodeItem[] | null = parent.children.splice(index, 1);
        node = null;
        if (parent.children.length === 0) {
          if (this.nodeIdAndNodeIndexMap.has(parentNodeId)) {
            let parentIndex: number = this.nodeIdAndNodeIndexMap.get(parentNodeId) as number;
            this.listNode[parentIndex]?.addImageCollapse(false);
          }
        }
      }
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum -= (deleteNodeAllChildNum);
      let updateNodeIdList: number[] = [];
      updateNodeIdList.push(parent.parentNodeId);
      delayUpdateParentChildNum(false, deleteNodeAllChildNum, this.nodeIdNodeItemMap, updateNodeIdList);
      return removeNodeIdList;
    } else {
      hilog.error(LOG_CODE, TAG, 'parent does not exist.');
      return [];
    }
  }

  private getNodeInfoByNodeItem(nodeItem: NodeItem): NodeInfo {
    if (nodeItem?.currentNodeId === undefined) {
      hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: currentId is undefined');
      return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
    }
    if (!this.nodeIdAndNodeIndexMap.has(nodeItem.currentNodeId)) {
      hilog.error(LOG_CODE, TAG, 'getNodeInfoByNodeItem: not has nodeItem.');
      return new NodeInfo(new NodeItem(emptyNodeInfo), emptyNodeInfo);
    }
    let index: number = this.nodeIdAndNodeIndexMap.get(nodeItem.currentNodeId) as number;
    return this.listNode[index];
  }

  /**
   * get node param by node id
   * @param nodeId node id
   * @returns node param
   */
  public getNewNodeParam(nodeId: number): NodeParam {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(nodeId)) {
      parent = this.nodeIdNodeItemMap.get(nodeId) as NodeItem;
    }
    let newNodeParam: NodeParam = emptyNodeInfo;
    if (parent) {
      let nodeInfo: NodeInfo = this.getNodeInfoByNodeItem(parent);
      if (parent.children.length === 0) {
        if (nodeInfo.getNodeItem().imageNode !== undefined) {
          newNodeParam.icon = nodeInfo.getNodeItem().imageNode?.normalSource;
          newNodeParam.selectedIcon = nodeInfo.getNodeItem().imageNode?.selectedSource;
          newNodeParam.editIcon = nodeInfo.getNodeItem().imageNode?.editSource;
          newNodeParam.container = nodeInfo.getMenu();
        } else {
          newNodeParam.icon = undefined;
          newNodeParam.selectedIcon = undefined;
          newNodeParam.editIcon = undefined;
          newNodeParam.container = nodeInfo.getMenu();
        }
      } else if (parent.children.length > 0) {
        let childNodeInfo: NodeInfo = this.getNodeInfoByNodeItem(parent.children[0]);
        if (nodeInfo.getNodeItem().imageNode !== null) {
          newNodeParam.icon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
            childNodeInfo.getNodeItem().imageNode?.normalSource : undefined;
          newNodeParam.selectedIcon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
            childNodeInfo.getNodeItem().imageNode?.selectedSource : undefined;
          newNodeParam.editIcon = (childNodeInfo.getNodeItem().imageNode !== undefined) ?
            childNodeInfo.getNodeItem().imageNode?.editSource : undefined;
          newNodeParam.container = childNodeInfo.getMenu();
        } else {
          newNodeParam.icon = undefined;
          newNodeParam.selectedIcon = undefined;
          newNodeParam.editIcon = undefined;
          newNodeParam.container = childNodeInfo.getMenu();
        }
      }
    }
    return newNodeParam;
  }

  /**
   * get child node ids by node id
   *
   * @param nodeId node id
   * @returns child node ids
   */
  public getClickChildId(nodeId: number): number[] {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(nodeId)) {
      parent = this.nodeIdNodeItemMap.get(nodeId) as NodeItem;
    }
    if (parent) {
      if (parent.children.length === 0) {
        return [];
      } else if (parent.children.length > 0) {
        let childrenNodeInfo: number[] = new Array(parent.children.length);
        for (let i: number = 0; i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i] = 0;
        }
        for (let i: number = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i] = parent.children[i].currentNodeId;
        }
        return childrenNodeInfo;
      }
    }
    return [];
  }

  /**
   * get child nodeInfo views by node id
   *
   * @param nodeId node id
   * @returns child nodeInfo views
   */
  public getClickNodeChildrenInfo(nodeId: number): NodeInfoView[] {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    if (this.nodeIdNodeItemMap.has(nodeId)) {
      parent = this.nodeIdNodeItemMap.get(nodeId) as NodeItem;
    }
    if (parent) {
      if (parent.children.length === 0) {
        return [];
      } else if (parent.children.length > 0) {
        let childrenNodeInfo: NodeInfoView[] = new Array(parent.children.length);
        for (let i: number = 0; i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i] = {};
        }
        for (let i: number = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i].itemId = parent.children[i].currentNodeId;
          let nodeInfo: NodeInfo = this.getNodeInfoByNodeItem(parent.children[i]);
          if (nodeInfo.getNodeItem().imageNode) {
            childrenNodeInfo[i].itemIcon = nodeInfo.getNodeItem().imageNode?.source;
          }
          if (nodeInfo.getNodeItem().mainTitleNode) {
            childrenNodeInfo[i].itemTitle = nodeInfo.getNodeItem().mainTitleNode?.title;
          }
          childrenNodeInfo[i].isFolder = nodeInfo.getIsFolder();
        }
        return childrenNodeInfo;
      }
    }
    return [];
  }

  /**
   * check main title is valid
   *
   * @param title main title
   * @returns check result
   */
  public checkMainTitleIsValid(title: string): boolean {
    if (new RegExp('/[\\\/:*?"<>|]/').test(title)) {
      return false;
    }
    if ((new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_CN_LENGTH) ||
      (!new RegExp('/^[\u4e00-\u9fa5]+$/').test(title) && title.length > this.MAX_EN_LENGTH)) {
      return false;
    }
    return true;
  }

  /**
   * DFS: Depth first traversal in drag event.
   *
   * @param callback dfs callback fuction
   */
  dragTraverseNodeDF(callback: (node: NodeItem, listNode: NodeInfo[]) => boolean,
    root: NodeItem = this._root, listNode: NodeInfo[]): void {
    let stack: NodeItem[] = [];
    let found: boolean = false;
    stack.unshift(root);
    let currentNode: NodeItem = stack.shift() as NodeItem;
    while (!found && currentNode) {
      found = callback(currentNode, listNode) === true;
      if (!found) {
        stack.unshift(...currentNode.children);
        currentNode = stack.shift() as NodeItem;
      }
    }
  }

  private updateChildIndexOfParent(insertIndex: number, parent: NodeItem): void {
    for (let i: number = insertIndex; i < parent.children.length; i++) {
      parent.children[i].indexOfParent += 1;
    }
  }

  /**
   * Add the first dragging node in dragging nodes
   * 1.the first dragging node needs to distinguish the position to insert
   */
  private addDragNode(parentNodeId: number,
    currentNodeId: number,
    insertCurrentNodeId: number,
    isAfter: boolean,
    data: NodeParam): boolean {

    if (this._root === null) {
      this._root = new NodeItem(emptyNodeInfo);
      this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
    }

    if (this.nodeIdNodeItemMap.has(parentNodeId)) {
      let parent: NodeItem = this.nodeIdNodeItemMap.get(parentNodeId) as NodeItem;
      let currentNode: NodeItem = new NodeItem(data);
      if (parent.nodeLevel > this.maxNodeLevel) {
        hilog.error(LOG_CODE, TAG, 'addDragNode: The level of the tree view cannot exceed 50.');
        return false;
      }
      currentNode.nodeLevel = parent.nodeLevel + 1;
      currentNode.parentNodeId = parentNodeId;
      currentNode.currentNodeId = currentNodeId;
      data.parentNodeId = parentNodeId;
      data.currentNodeId = currentNodeId;
      let insertIndex: number = this.INITIAL_INVALID_VALUE;
      if (parent.children.length) {
        for (let i: number = 0; i < parent.children.length; i++) {
          if (parent.children[i].getCurrentNodeId() === insertCurrentNodeId) {
            insertIndex = i;
            break;
          }
        }
        if (isAfter) {
          currentNode.indexOfParent = insertIndex + 1;
          this.updateChildIndexOfParent(currentNode.indexOfParent, parent);
          parent.children.splice(insertIndex + 1, 0, currentNode);
        } else {
          currentNode.indexOfParent = insertIndex < 0 ? parent.children.length + insertIndex : insertIndex;
          this.updateChildIndexOfParent(currentNode.indexOfParent, parent);
          parent.children.splice(insertIndex, 0, currentNode);
        }
      } else {
        currentNode.indexOfParent = parent.children.length;
        parent.children.push(currentNode);
      }
      parent.getChildNodeInfo().isHasChildNode = true;
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum += 1;
      this.updateParentChildNum(parent, true, 1);
      this.nodeIdNodeItemMap.set(currentNodeId, currentNode);
      this.nodeIdNodeParamMap.set(currentNodeId, data);
      return true;
    } else {
      hilog.error(LOG_CODE, TAG, 'addDragNode: Parent node not found.');
      return false;
    }
  }
}

@Component
export struct TreeViewInner {
  @ObjectLink item: NodeInfo;
  listNodeDataSource: ListNodeDataSource = new ListNodeDataSource();
  @State columnWidth: number = 0;
  @State isFocused: boolean = false;
  @State index: number = -1;
  @State lastIndex: number = -1;
  @State count: number = 0;
  @State followingSystemFontScale: boolean = false;
  @State maxAppFontScale: number = 1;
  @Consume treeViewTheme: TreeViewTheme;
  @BuilderParam private listTreeViewMenu: () => void;
  private readonly MAX_CN_LENGTH: number = 254;
  private readonly MAX_EN_LENGTH: number = 255;
  private readonly INITIAL_INVALID_VALUE = -1;
  private readonly MAX_TOUCH_DOWN_COUNT = 0;
  private isMultiPress: boolean = false;
  private touchDownCount: number = this.INITIAL_INVALID_VALUE;
  private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
  private readonly itemPadding: ItemPadding = {
    left: $r('sys.float.ohos_id_card_margin_start'),
    right: $r('sys.float.ohos_id_card_margin_end'),
    top: $r('sys.float.ohos_id_text_margin_vertical'),
    bottom: $r('sys.float.padding_level0'),
  };
  private readonly textInputPadding: ItemPadding = {
    left: $r('sys.float.padding_level0'),
    right: $r('sys.float.padding_level0'),
    top: $r('sys.float.padding_level0'),
    bottom: $r('sys.float.padding_level0') };
    private inputFontSize: number = resourceManager.getSystemResourceManager().getNumberByName('ohos_id_text_size_body1');

  aboutToAppear(): void {
    if (this.item.getNodeItem().imageNode) {
      this.item.imageSource = this.item.getNodeItem().imageNode?.source;
    }
    let uiContent: UIContext = this.getUIContext();
    this.followingSystemFontScale = uiContent.isFollowingSystemFontScale();
    this.maxAppFontScale = uiContent.getMaxFontScale();
  }

  decideFontScale() {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.followingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale, MAX_FONT_SCALE)
  }

  getInputTextMaxFontSize() {
    let inputTextMaxFontSize = this.decideFontScale() * this.inputFontSize + 'vp';
    return inputTextMaxFontSize;
  }

  getLeftIconColor(): ResourceColor {
    if (this.item.getIsModify()) {
      return $r('sys.color.icon_on_primary');
    } else if (this.item.getIsSelected()) {
      return this.treeViewTheme.leftIconActiveColor;
    } else {
      return this.treeViewTheme.leftIconColor;
    }
  }

  private checkInvalidPattern(title: string): boolean {
    return new RegExp('/[\\\/:*?"<>|]/').test(title);
  }

  private checkIsAllCN(title: string): boolean {
    return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
  }

  @Builder
  popupForShowTitle(text: string | Resource | undefined, backgroundColor: ResourceColor, fontColor: ResourceColor) {
    Row() {
      Text(text)
        .fontSize($r('sys.float.ohos_id_text_size_body2'))
        .fontWeight('regular')
        .fontColor(fontColor)
        .minFontScale(MIN_FONT_SCALE)
        .maxFontScale(this.decideFontScale())
    }
    .backgroundColor(backgroundColor)
    .border({ radius: $r('sys.float.ohos_id_elements_margin_horizontal_l') })
    .padding({
      left: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
      right: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
      top: $r('sys.float.ohos_id_card_margin_middle'),
      bottom: $r('sys.float.ohos_id_card_margin_middle'),
    })
  }

  @Builder
  builder() {
    if (this.listTreeViewMenu) {
      this.listTreeViewMenu()
    }
  }

  build() {
    if (this.item.getNodeIsShow()) {
      Stack() {
        Column() {
          Stack({ alignContent: Alignment.Bottom }) {
            Divider()
              .height(this.listNodeDataSource.getFlagLine().flagLineHeight)
              .color(this.listNodeDataSource.getFlagLine().flagLineColor)
              .visibility(this.listNodeDataSource.getVisibility(this.item))
              .lineCap(LineCapStyle.Round)
              .margin({ start: LengthMetrics.vp(this.item.getFlagLineLeftMargin()) })
              .focusable(true)
            Row({}) {
              if (this.item.getNodeItem().imageNode) {
                Row() {
                  Image(this.item.imageSource)
                    .objectFit(ImageFit.Contain)
                    .height(this.item.getNodeItem().imageNode?.itemHeight)
                    .width(this.item.getNodeItem().imageNode?.itemWidth)
                    .opacity(!this.item.getIsSelected() && !this.item.getIsHighLight() ?
                      this.item.getNodeItem().imageNode?.opacity : this.item.getNodeItem().imageNode?.noOpacity)
                    .focusable(this.item.getNodeItem().mainTitleNode !== null ? false : true)
                    .fillColor(this.getLeftIconColor())
                    .matchTextDirection((this.item.getNodeItem()
                      .imageCollapse?.collapseSource === ARROW_RIGHT || this.item.getNodeItem()
                      .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false)
                }
                .focusable(true)
                .backgroundColor(COLOR_IMAGE_ROW)
                .margin({
                  end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem().imageNode?.itemRightMargin)
                })
                .height(this.item.getNodeItem().imageNode?.itemHeight)
                .width(this.item.getNodeItem().imageNode?.itemWidth)
              }
              Row() {
                if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                  Text(this.item.getNodeItem().mainTitleNode?.title)
                    .minFontScale(MIN_FONT_SCALE)
                    .maxFontScale(this.decideFontScale())
                    .maxLines(1)// max line
                    .fontSize(this.item.getNodeItem().mainTitleNode?.size)
                    .fontColor(this.item.getIsSelected() ?
                    this.treeViewTheme.primaryTitleActiveFontColor : this.treeViewTheme.primaryTitleFontColor)
                    .margin({
                      end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                        .mainTitleNode?.itemRightMargin)
                    })
                    .textOverflow({ overflow: TextOverflow.Ellipsis })
                    .fontWeight(this.item.getNodeItem().mainTitleNode?.weight)
                    .focusable(true)
                }
                if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                this.item.getIsShowInputText()) {
                  Row() {
                    TextInput({ text: this.item.getNodeItem().mainTitleNode?.title })
                      .height(this.item.getNodeItem().inputText?.itemHeight)
                      .fontSize(this.getInputTextMaxFontSize())
                      .fontColor(this.item.getNodeItem().inputText?.color)
                      .borderRadius(this.item.getNodeItem().inputText?.borderRadius)
                      .backgroundColor(this.item.getNodeItem().inputText?.backgroundColor)
                      .enterKeyType(EnterKeyType.Done)
                      .focusable(true)
                      .padding({
                        start: LengthMetrics.resource(this.textInputPadding.left),
                        end: LengthMetrics.resource(this.textInputPadding.right),
                        top: LengthMetrics.resource(this.textInputPadding.top),
                        bottom: LengthMetrics.resource(this.textInputPadding.bottom),
                      })
                      .onChange((value: string) => {
                        let thisIndex: number = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                        let res: string = '';
                        let isInvalidError: boolean = false;
                        let isLengthError: boolean = false;
                        if (this.checkInvalidPattern(value)) {
                          for (let i: number = 0; i < value.length; i++) {
                            if (!this.checkInvalidPattern(value[i])) {
                              res += value[i];
                            }
                          }
                          isInvalidError = true;
                          this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                            InputError.INVALID_ERROR, true, thisIndex);
                        } else {
                          res = value;
                          isInvalidError = false;
                        }
                        if ((this.checkIsAllCN(res) && res.length > this.MAX_CN_LENGTH) ||
                          (!this.checkIsAllCN(res) && res.length > this.MAX_EN_LENGTH)) {
                          res = this.checkIsAllCN(res) ?
                          res.substr(0, this.MAX_CN_LENGTH) : res.substr(0, this.MAX_EN_LENGTH);
                          isLengthError = true;
                          this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                            InputError.LENGTH_ERROR, true, thisIndex);
                        } else {
                          isLengthError = false;
                        }
                        if (!isLengthError && !isInvalidError) {
                          this.listNodeDataSource.setMainTitleNameOnEdit(thisIndex, res);
                        }
                      })
                      .onSubmit((enterKey: EnterKeyType) => {
                        let thisIndex: number = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
                        this.listNodeDataSource.setPopUpInfo(
                          PopUpType.WARNINGS,
                          InputError.NONE,
                          false,
                          thisIndex
                        );
                        this.listNodeDataSource.setItemVisibilityOnEdit(thisIndex, MenuOperation.COMMIT_NODE);
                      })
                  }.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor)
                  .borderRadius(this.item.getNodeItem().inputText?.borderRadius)
                  .margin({
                    end: getLengthMetricsByResourceOrNumber(this.item.getNodeItem()
                      .inputText?.itemRightMargin)
                  })
                }
                Blank()
              }
              .layoutWeight(1)
              .focusable(true)

              if (this.listNodeDataSource.hasSubtitle(this.item.getNodeCurrentNodeId())) {
                Row() {
                  Text(this.listNodeDataSource.getSubtitle(this.item.getNodeCurrentNodeId()))
                    .minFontScale(MIN_FONT_SCALE)
                    .maxFontScale(this.decideFontScale())
                    .fontSize(this.listNodeDataSource.getSubTitlePara().fontSize)
                    .fontColor(this.item.getIsHighLight() || this.item.getIsModify() ?
                    $r('sys.color.ohos_id_color_primary_contrary') : this.treeViewTheme.secondaryTitleFontColor)
                    .fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight)
                }
                .focusable(true)
                .margin({
                  start: LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin.left),
                  end: this.item.getNodeItem().imageCollapse ?
                  LengthMetrics.resource($r('sys.float.padding_level0')) : LengthMetrics.resource(this.listNodeDataSource.getSubTitlePara().margin.right)
                })
              }

              if (this.item.getNodeItem().imageCollapse) {
                Row() {
                  Image(this.item.getNodeItem().imageCollapse?.collapseSource)
                    .fillColor(this.item.getNodeItem().imageCollapse?.isCollapse ?
                    this.treeViewTheme.arrowIconColor : COLOR_IMAGE_EDIT)
                    .align(Alignment.End)
                    .objectFit(ImageFit.Contain)
                    .height(this.item.getNodeItem().imageCollapse?.itemHeight)
                    .width(this.item.getNodeItem().imageCollapse?.itemWidth)
                    .opacity(!this.item.getIsHighLight() ?
                      this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity)
                    .onTouch((event: TouchEvent) => {
                      if (event.type === TouchType.Down) {
                        this.listNodeDataSource.expandAndCollapseNode(
                          this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                        this.listNodeDataSource.setCurrentFocusNodeId(this.item.getNodeCurrentNodeId());
                      }
                      event.stopPropagation();
                    })
                    .focusable(true)
                    .matchTextDirection((this.item.getNodeItem()
                      .imageCollapse?.collapseSource === ARROW_RIGHT || this.item.getNodeItem()
                      .imageCollapse?.collapseSource === ARROW_RIGHT_WITHE) ? true : false)
                }
                .focusable(true)
                .height(this.item.getNodeItem().imageCollapse?.itemHeight)
                .width(this.item.getNodeItem().imageCollapse?.itemWidth)
              }
            }
            .focusable(true)
            .width('100%')
            .gesture(
              TapGesture({ count: 2 })
                .onAction((event: GestureEvent) => {
                  this.listNodeDataSource.expandAndCollapseNode(
                    this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
                })
            )
            .height(this.item.getNodeHeight())
            .padding({ start: LengthMetrics.vp(this.item.getNodeLeftPadding()) })
            .bindContextMenu(this.builder, ResponseType.RightClick)

          }.focusable(true)
        }
        .opacity(this.listNodeDataSource.getListItemOpacity(this.item))
        .onHover((isHover: boolean) => {
          if (isHover) {
            this.item.setNodeColor(this.treeViewTheme.itemHoverBgColor)
          } else {
            this.item.setNodeColor($r('sys.color.ohos_id_color_background_transparent'))
          }
        })
        .onTouch((event) => {
          this.count++;
          if (this.count > 1) {
            this.count--;
            return;
          }

          this.index = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId())
          this.listNodeDataSource.setClickIndex(this.index);
          let currentId: number = this.item.getNodeCurrentNodeId();

          if (event.type === TouchType.Down) {
            this.item.setNodeColor(this.treeViewTheme.itemPressedBgColor);
          }

          else if (event.type === TouchType.Up) {
            if (!(typeof this.treeViewTheme.itemSelectedBgColor === 'string')) {
              this.item.setNodeColor(COLOR_SELECT);
            } else {
              this.item.setNodeColor(this.treeViewTheme.itemSelectedBgColor);
            }
            if (this.item.getNodeItem().imageNode !== null) {
              this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.SELECTED);
              this.listNodeDataSource.setImageSource(this.index, InteractionStatus.SELECTED);
              this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            }

            this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true);
            let callParam: CallbackParam = { currentNodeId: currentId };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, callParam);
          }

          if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(
              PopUpType.WARNINGS,
              InputError.NONE,
              false,
              this.listNodeDataSource.getLastIndex()
            );
            this.listNodeDataSource.setItemVisibilityOnEdit(
              this.listNodeDataSource.getLastIndex(),
              MenuOperation.COMMIT_NODE
            );
          }
          this.lastIndex = this.index;
          this.count--;
        })
        /* backgroundColor when editing and in other states. */
        .backgroundColor((this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
        this.item.getIsShowInputText()) ? this.item.getNodeItem().inputText?.editColor : this.item.getNodeColor())
        .border({
          width: this.item.getNodeBorder().borderWidth,
          color: this.item.getNodeBorder().borderColor,
          radius: this.item.getNodeBorder().borderRadius,
        })
        .height(LIST_ITEM_HEIGHT)
        .focusable(true)
        .onMouse((event: MouseEvent) => {
          let thisIndex: number = this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId());
          if (event.button === MouseButton.Right) {
            this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
              this.listNodeDataSource.findIndex(this.item.getNodeCurrentNodeId()));
            this.listTreeViewMenu = this.item.getMenu();
            this.listNodeDataSource.setClickIndex(thisIndex);
            clearTimeout(this.item.getNodeItem().mainTitleNode?.popUpTimeout);
          }
          event.stopPropagation();
        })
        .padding({ top: 0, bottom: 0 })
        .bindPopup(this.item.getPopUpInfo().popUpIsShow, {
          builder: this.popupForShowTitle(this.item.getPopUpInfo().popUpText, this.item.getPopUpInfo().popUpColor,
            this.item.getPopUpInfo().popUpTextColor),
          placement: Placement.BottomLeft,
          placementOnTop: false,
          popupColor: this.item.getPopUpInfo().popUpColor,
          autoCancel: true,
          enableArrow: this.item.getPopUpInfo().popUpEnableArrow,
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          let columnWidthNum: number = Number.parseInt(newValue.width.toString());
          this.columnWidth = columnWidthNum;
        })
      }
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: FLAG_NUMBER,
            color: this.treeViewTheme.borderFocusedColor,
            style: BorderStyle.Solid,
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0,
          })
        }
      })
    }
  }
}

export class NodeItem {
  public childNodeInfo: ChildNodeInfo;
  public nodeLevel: number;
  public children: NodeItem[];
  public indexOfParent: number;
  public parentNodeId: number;
  public currentNodeId: number;
  public isFolder?: boolean;

  constructor(nodeParam: NodeParam) {
    this.currentNodeId = nodeParam.currentNodeId ?? -1;
    this.parentNodeId = nodeParam.parentNodeId ?? -1;
    this.isFolder = nodeParam.isFolder;
    this.nodeLevel = -1;
    this.indexOfParent = -1;
    this.childNodeInfo = { isHasChildNode: false, childNum: 0, allChildNum: 0 };
    this.children = [];
  }

  getChildNodeInfo(): ChildNodeInfo {
    return this.childNodeInfo;
  }

  getCurrentNodeId(): number {
    return this.currentNodeId;
  }

  getIsFolder(): boolean | undefined {
    return this.isFolder;
  }
}

class NodeBaseInfo {
  public rightMargin: Resource | number = -1;
  private width: number = -1;
  private height: number = -1;

  constructor() {
  }

  set itemWidth(width: number) {
    this.width = width;
  }

  get itemWidth(): number {
    return this.width;
  }

  set itemHeight(height: number) {
    this.height = height;
  }

  get itemHeight(): number {
    return this.height;
  }

  set itemRightMargin(rightMargin: Resource | number) {
    this.rightMargin = rightMargin;
  }

  get itemRightMargin(): Resource | number {
    return this.rightMargin;
  }
}

export class CollapseImageNode extends NodeBaseInfo {
  private imageSource: Resource | string;
  private imageOpacity: Resource;
  private imageCollapseSource: Resource | string;
  private isImageCollapse: boolean;
  private collapseImageType: CollapseImageType;

  constructor(
    imageSource: Resource | string,
    imageOpacity: Resource,
    itemWidth: number,
    itemHeight: number,
    itemRightMargin: Resource | number,
    isImageCollapse: boolean,
    collapseImageType: CollapseImageType
  ) {
    super();
    this.rightMargin = $r('sys.float.ohos_id_elements_margin_horizontal_m');
    this.imageSource = imageSource;
    this.rightMargin = itemRightMargin;
    this.imageOpacity = imageOpacity;
    this.itemWidth = itemWidth;
    this.itemHeight = itemHeight;
    this.imageCollapseSource = imageSource;
    this.isImageCollapse = isImageCollapse;
    this.collapseImageType = collapseImageType;
  }

  get source(): Resource | string {
    return this.imageSource;
  }

  get opacity(): Resource {
    return this.imageOpacity;
  }

  get noOpacity(): number {
    return 1;
  }

  get collapseSource(): Resource | string {
    return this.imageCollapseSource;
  }

  get isCollapse(): boolean {
    return this.isImageCollapse;
  }

  get type(): CollapseImageType {
    return this.collapseImageType;
  }
}

class CollapseImageNodeFactory {
  private static instance: CollapseImageNodeFactory;

  private constructor() {
  }

  /**
   * CollapseImageNodeFactory singleton function
   *
   * @returns CollapseImageNodeFactory
   */
  public static getInstance(): CollapseImageNodeFactory {
    if (!CollapseImageNodeFactory.instance) {
      CollapseImageNodeFactory.instance = new CollapseImageNodeFactory();
    }
    return CollapseImageNodeFactory.instance;
  }

  /**
   * create collapse image node by type
   *
   * @param type collapse image type
   * @returns collapse image node
   */
  public createCollapseImageNodeByType(type: CollapseImageType): CollapseImageNode {
    let imageSource: Resource | string;
    switch (type) {
      case CollapseImageType.ARROW_RIGHT_WHITE:
        imageSource = ARROW_RIGHT_WITHE;
        break;
      case CollapseImageType.ARROW_RIGHT:
        imageSource = ARROW_RIGHT;
        break;
      case CollapseImageType.ARROW_DOWN_WHITE:
        imageSource = ARROW_DOWN_WITHE;
        break;
      default:
        imageSource = ARROW_DOWN;
    }
    return new CollapseImageNode(
      imageSource,
      $r('sys.float.ohos_id_alpha_content_tertiary'),
      IMAGE_NODE_HEIGHT,
      IMAGE_NODE_WIDTH,
      $r('sys.float.ohos_id_text_paragraph_margin_xs'),
      (type === CollapseImageType.ARROW_RIGHT_WHITE || type === CollapseImageType.ARROW_DOWN_WHITE) ? false : true,
      type
    );
  }
}

class CollapseImageNodeFlyweightFactory {
  private static nodeMap: Map<CollapseImageType, CollapseImageNode> = new Map<CollapseImageType, CollapseImageNode>();

  /**
   * get collapse image node by type
   *
   * @param type collapse image node type
   * @returns  collapse image node
   */
  static getCollapseImageNodeByType(type: CollapseImageType): CollapseImageNode {
    let node: CollapseImageNode | undefined = CollapseImageNodeFlyweightFactory.nodeMap.get(type);
    if (node === undefined) {
      node = CollapseImageNodeFactory.getInstance().createCollapseImageNodeByType(type);
      CollapseImageNodeFlyweightFactory.nodeMap.set(type, node);
    }
    return node;
  }

  /**
   * get collapse image node by interactionStatus and nodeStatus
   *
   * @param interactionStatus interaction status
   * @param nodeStatus node status
   * @param defaultType default collapse image type
   * @returns collapse image node
   */
  static getCollapseImageNode(interactionStatus: InteractionStatus, nodeStatus: NodeStatus | undefined,
    defaultType?: CollapseImageType): CollapseImageNode | undefined {
    if (defaultType === undefined) {
      return undefined;
    }
    let type: CollapseImageType = defaultType;
    if (interactionStatus == InteractionStatus.EDIT ||
      interactionStatus === InteractionStatus.DRAG_INSERT) {
      if (nodeStatus === NodeStatus.COLLAPSE) {
        type = CollapseImageType.ARROW_RIGHT_WHITE;
      } else {
        type = CollapseImageType.ARROW_DOWN_WHITE;
      }
    } else if (interactionStatus === InteractionStatus.FINISH_EDIT ||
      interactionStatus === InteractionStatus.FINISH_DRAG_INSERT) {
      if (nodeStatus === NodeStatus.COLLAPSE) {
        type = CollapseImageType.ARROW_RIGHT;
      } else {
        type = CollapseImageType.ARROW_DOWN;
      }
    }
    return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(type);
  }

  /**
   * change collapse image node source
   *
   * @param nodeStatus node status
   * @param isImageCollapse whether collapse image or white collapse image
   * @returns collapse image node
   */
  static changeImageCollapseSource(nodeStatus: NodeStatus, isImageCollapse?: boolean): CollapseImageNode | undefined {
    if (isImageCollapse === undefined) {
      return undefined;
    }
    let type: CollapseImageType;
    if (!isImageCollapse) {
      if (nodeStatus === NodeStatus.COLLAPSE) {
        type = CollapseImageType.ARROW_RIGHT_WHITE;
      } else {
        type = CollapseImageType.ARROW_DOWN_WHITE;
      }
    } else {
      if (nodeStatus === NodeStatus.COLLAPSE) {
        type = CollapseImageType.ARROW_RIGHT;
      } else {
        type = CollapseImageType.ARROW_DOWN;
      }
    }
    return CollapseImageNodeFlyweightFactory.getCollapseImageNodeByType(type);
  }
}

export class ImageNode extends NodeBaseInfo {
  private imageSource: Resource | string;
  private imageNormalSource: Resource | string;
  private imageSelectedSource: Resource | string;
  private imageEditSource: Resource | string;
  private imageOpacity: Resource;
  private currentInteractionStatus: InteractionStatus;
  private imageCollapseSource: Resource | string;
  private imageCollapseDownSource: Resource | string;
  private isImageCollapse: boolean;
  private imageCollapseRightSource: Resource | string;

  constructor(
    imageSource: Resource | string,
    imageOpacity: Resource,
    itemWidth: number,
    itemHeight: number,
    itemSelectedIcon?: Resource | string,
    itemEditIcon?: Resource | string,
  ) {
    super();
    this.rightMargin = $r('sys.float.ohos_id_elements_margin_horizontal_m');
    this.imageSource = imageSource;
    this.imageNormalSource = imageSource;
    if (itemSelectedIcon !== undefined) {
      this.imageSelectedSource = itemSelectedIcon;
    } else {
      this.imageSelectedSource = this.imageNormalSource;
    }
    if (itemEditIcon !== undefined) {
      this.imageEditSource = itemEditIcon;
    } else {
      this.imageEditSource = this.imageNormalSource;
    }
    this.imageOpacity = imageOpacity;
    this.itemWidth = itemWidth;
    this.itemHeight = itemHeight;
    this.imageCollapseSource = imageSource;
    this.imageCollapseDownSource = ARROW_DOWN;
    this.imageCollapseRightSource = ARROW_RIGHT;
    this.isImageCollapse = true;
    this.currentInteractionStatus = InteractionStatus.NORMAL;
  }

  get source(): Resource | string {
    return this.imageSource;
  }

  get normalSource(): Resource | string {
    return this.imageNormalSource;
  }

  get selectedSource(): Resource | string {
    return this.imageSelectedSource;
  }

  get editSource(): Resource | string {
    return this.imageEditSource;
  }

  get opacity(): Resource {
    return this.imageOpacity;
  }

  get noOpacity(): number {
    return 1;
  }

  get collapseSource(): Resource | string {
    return this.imageCollapseSource;
  }

  get isCollapse(): boolean {
    return this.isImageCollapse;
  }

  changeImageCollapseSource(nodeStatus: NodeStatus): void {
    if (nodeStatus === NodeStatus.EXPAND) {
      this.imageCollapseSource = this.imageCollapseDownSource;
    } else if (nodeStatus === NodeStatus.COLLAPSE) {
      this.imageCollapseSource = this.imageCollapseRightSource;
    }
  }

  setImageCollapseSource(interactionStatus: InteractionStatus, nodeStatus: NodeStatus | undefined): void {
    if (interactionStatus === InteractionStatus.EDIT || interactionStatus === InteractionStatus.DRAG_INSERT) {
      this.imageCollapseDownSource = ARROW_DOWN_WITHE;
      this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
      this.isImageCollapse = false;
    } else if (interactionStatus === InteractionStatus.FINISH_EDIT ||
      interactionStatus === InteractionStatus.FINISH_DRAG_INSERT) {
      this.imageCollapseDownSource = ARROW_DOWN
      this.imageCollapseRightSource = ARROW_RIGHT
      this.isImageCollapse = true;
    }
    this.imageCollapseSource = (nodeStatus === NodeStatus.COLLAPSE) ?
    this.imageCollapseRightSource : this.imageCollapseDownSource;
  }

  setImageSource(interactionStatus: InteractionStatus): void {
    switch (interactionStatus) {
      case InteractionStatus.NORMAL:
        this.imageSource = this.imageNormalSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.SELECTED:
        if (this.currentInteractionStatus !== InteractionStatus.EDIT) {
          this.imageSource = this.imageSelectedSource;
          this.currentInteractionStatus = interactionStatus;
        }
        break;
      case InteractionStatus.EDIT:
        this.imageSource = this.imageEditSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.FINISH_EDIT:
        this.imageSource = this.imageSelectedSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.DRAG_INSERT:
        this.imageSource = this.imageEditSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.FINISH_DRAG_INSERT:
        this.imageSource = this.imageNormalSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      default:
        break;
    }
  }
}

class MainTitleNode extends NodeBaseInfo {
  private mainTitleName: ResourceStr;
  public mainTitleSetting: TextSetting;
  private showPopUpTimeout: number;
  private treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();

  constructor(mainTitleName: ResourceStr) {
    super();
    this.mainTitleName = mainTitleName;
    this.itemWidth = ITEM_WIDTH;
    this.itemHeight = ITEM_HEIGHT;
    this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
    this.mainTitleSetting = {
      fontColor: this.treeViewTheme.primaryTitleFontColor,
      fontSize: $r('sys.float.ohos_id_text_size_body1'),
      fontWeight: FontWeight.Normal,
    };
    this.showPopUpTimeout = 0;
  }

  setMainTitleSelected(isSelected: boolean): void {
    if (isSelected) {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Regular,
      };
    } else {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleFontColor,
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Normal,
      };
    }
  }

  set title(text: ResourceStr) {
    this.mainTitleName = text;
  }

  get title(): ResourceStr {
    return this.mainTitleName;
  }

  set popUpTimeout(showPopUpTimeout: number) {
    this.showPopUpTimeout = showPopUpTimeout;
  }

  get popUpTimeout(): number {
    return this.showPopUpTimeout;
  }

  get color(): ResourceColor {
    return this.mainTitleSetting.fontColor;
  }

  get size(): Resource {
    return this.mainTitleSetting.fontSize;
  }

  get weight(): FontWeight {
    return this.mainTitleSetting.fontWeight;
  }

  setMainTitleHighLight(isHighLight: boolean): void {
    if (isHighLight) {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleActiveFontColor,
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Regular,
      };
    } else {
      this.mainTitleSetting = {
        fontColor: this.treeViewTheme.primaryTitleFontColor,
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Normal,
      };
    }
  }
}

export class InputText extends NodeBaseInfo {
  private inputTextSetting: TextSetting;
  private status?: Status = undefined;
  private statusColor: Resource = $r('sys.color.ohos_id_color_background');
  private editItemColor: Resource = $r('sys.color.ohos_id_color_emphasize');
  private radius: Resource = $r('sys.float.ohos_id_corner_radius_default_xs');
  private treeViewTheme: TreeViewTheme = TreeViewTheme.getInstance();

  constructor() {
    super();
    this.itemWidth = ITEM_WIDTH;
    this.itemHeight = ITEM_HEIGHT_INPUT;
    this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
    this.inputTextSetting = {
      fontColor: this.treeViewTheme.primaryTitleFontColor,
      fontSize: $r('sys.float.ohos_id_text_size_body1'),
      fontWeight: FontWeight.Normal,
    };
  }

  get color(): ResourceColor {
    return this.inputTextSetting.fontColor;
  }

  get size(): Resource {
    return this.inputTextSetting.fontSize;
  }

  get weight(): FontWeight {
    return this.inputTextSetting.fontWeight;
  }

  get borderRadius(): Resource {
    return this.radius;
  }

  get backgroundColor(): Resource {
    return this.statusColor;
  }

  get editColor(): Resource {
    return this.editItemColor;
  }

  get textInputStatusColor(): Status | undefined {
    return this.status;
  }
}

/**
 * get LengthMetrics
 *
 * @param Resource | number type
 * @returns LengthMetrics
 */
function getLengthMetricsByResourceOrNumber(resourceOrNumber: Resource | number): LengthMetrics {
  if (!resourceOrNumber) {
    return LengthMetrics.vp(0);
  } else if (typeof resourceOrNumber === 'number') {
    return LengthMetrics.vp(resourceOrNumber);
  } else {
    return LengthMetrics.resource(resourceOrNumber);
  }
}