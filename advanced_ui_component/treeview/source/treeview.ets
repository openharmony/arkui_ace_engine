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

const IMAGE_NODE_HEIGHT: number = 24
const IMAGE_NODE_WIDTH: number = 24
const ITEM_WIDTH: number = 0
const ITEM_HEIGHT: number = 48
const ITEM_HEIGHT_INPUT: number = 32
const BORDER_WIDTH_HAS: number = 2
const BORDER_WIDTH_NONE: number = 0
const NODE_HEIGHT: number = 48
const LIST_ITEM_HEIGHT_NONE: number = 0
const LIST_ITEM_HEIGHT: number = 48
const SHADOW_OFFSETY: number = 10
const FLAG_NUMBER: number = 2
const DRAG_OPACITY: number = 0.4
const DRAG_OPACITY_NONE: number = 1
const FLAG_LINE_HEIGHT: string = '1.0vp'
const X_OFF_SET: string = '0vp'
const Y_OFF_SET: string = '2.75vp'
const Y_BOTTOM_OFF_SET: string = '-1.25vp'
const Y_BASE_PLATE_OFF_SET: string = '1.5vp'
const COLOR_SELECT: string = '#1A0A59F7'
const COLOR_IMAGE_ROW: string = '#00000000'
const COLOR_IMAGE_EDIT: string = '#FFFFFF'
const SHADOW_COLOR: string = '#00001E'
const GRAG_POP_UP_HEIGHT: string = '48'
const LEFT_PADDING: string = '8vp'
const RIGHT_PADDING: string = '8vp'
const FLOOR_MIN_WIDTH: string = '128vp'
const FLOOR_MAX_WIDTH: string = '208vp'
const TEXT_MIN_WIDTH: string = '80vp'
const TEXT_MAX_WIDTH: string = '160vp'
const MIN_WIDTH: string = '112vp'
const MAX_WIDTH: string = '192vp'
const TRANS_COLOR: string = '#00FFFFFF'

const ARROW_DOWN = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA+' +
  'gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzA' +
  'AAOxAAADsQBlSsOGwAAAq9JREFUeNrt2j9rFEEYx/FJziIECwsLCwsJIVhYiISgaIhiioiIlpaCjZ1/qhNUIkHE0negpZggEnwHFgoWFiJic' +
  'VyRQsQXIHKIvyGzIJKbmTW7M7P6/cCvyR3c7fPsPLO7F2MAAAAAAAAAAAAAAAAAAAAAAAAAAF01keAz9ihrymVln/JEua18L7w2V5TrykHlt' +
  'XJTGTb9Ib0EB/JYueWKP6Ucd3mh/Ci0+Hfc9z6gTCuHlUvK06ZPnMkEB3Nth78tK89dQ0os/toOfz+kHG36w1I0YNwZs6JsFtaEccVvTYoGr' +
  'HteW3ajaKoDxbfz/10X94BXyoIyO+b1Wbcn2JE0ylT8VeW+5/UtZUn52sUG/FQ23PycG/OeGWXevW+U4cwPFf+MMmjjw3uJDnLkRo2vCTlWQ' +
  'l954Hn9i3Je+djWF+glPNNimlCthJcJLlH7buZPemb+ovKpzS/RS7zcqybMB/aEhZZXwmqg+NXMH7ZdkNQNqJrwLLAxz7Q4jkIzf5iq+LkaU' +
  'GdjbroJoUvNb674g1SFyNWAOntCU48tYq7zzyqfUxYhZwPqNOHYLi9RQ8XfylH8EhpQZ2P+23EUU/zFlGOntAbU2Zjr3qyF7nCrsTPIdeClN' +
  'CB2Y66zEvoRG26WsVNqA+rerPlWwg3lYeAmayl38UtsQBOPLezMfxRxkzUo4WBLbEDsxmxXwinlrRsn+5W7yr1SbrJiTJiy2d+T7Y82K4H32' +
  'QbsNf7fFeyDtRMlFb/kFVBnY7amXbN8l5oXTYtPNf/VBsTuCSZQfPs8/0OJB9eFBuymCXbsnCxlw+1yA2I35j+Lf860/Dz/f2rA73fMdhUc8' +
  'bzvjXKhxJnftasgH3sJelU5bbb/Z8ee8e/N9j9PrZt8P/ADAAAAAAAAAAAAAAAAAAAAAAAgpV9KuZwVm6MIDQAAAABJRU5ErkJggg=='

const ARROW_DOWN_WITHE = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAIGNIUk0AAHomAAC' +
  'AhAAA+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAl' +
  'wSFlzAAAOxAAADsQBlSsOGwAAAKVJREFUeNpjYBgFo2AU0Bww4pL4////diC1hZGRcSo+A4DqWIDUZCB+AVTbiC7PhEfvByCeAjQgn4Dhy4E' +
  '4BYgvYFODz4JYIF4DxBOwWYJkeAAQRwBdvxGbIcy4TG9sbPzX0NCwHsjUAuIiIPsDUOwkDsPXkhwHWFwaAsQlQAwyrJsYw4myAIslIPCHGMP' +
  'xBhGO4PoGxF+AOA9o+NbRTDgKRgFxAAAzj0Grm3RjyAAAAABJRU5ErkJggg=='

const ARROW_RIGHT = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA' +
  '+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlz' +
  'AAAOxAAADsQBlSsOGwAAAjVJREFUeNrtnCtvG1EQRq+9BlVUEBAYYFBgYGBYaBBoFUVVfkCtyqDAIL8jtI8EBruVIgU4UvMD0iKDPmirtlJg' +
  'lJZUyqzsSFXlxwZsPPPtOdJHbDKac+/cXXvtlAAAAAAAAAAAAAAAAAAAAAAUyZzW1bMMLbuWv5YvqgJqTps/sjT+eW1geckOuB+OLdtzpHy3' +
  'fFQTUHdY06MFr7+xPGMHlE93iYQnajvBo4APlj3LRhUkeBRwaRnProDkJXi9DP1ZFQmZ49oqISFzXl9RCb8sFwhYn4Sw9wlZkDplx1EWqFZJ' +
  'CVmwHSsnIZoAuYM5ogCpgzmqAJlxFFmAxDiKLiD8OFIQEHocqQgIK0FJwF0kfLZMELA+CTuWI8s1AtYj4YHlt+UcAeVK+JqmX2/OY9Pyat1F' +
  '1pM2J2n6Fec8mh4KVBdwO27m8RAB5dNb0uhPCCiXTpo+zLWItwgoj/bsKmhrwft/PBzAOQ3RlT9a0vycF5ZvHoqtCTZ/vKL5fcuhl4KVRlA7' +
  'WvOVBOQP875f0fyBt+arnAH52DmNtvJVzoBwM19pBBVp/r7n5kceQa0CYyfE78pqoiu/733lRxUg1fxoZ0BbrfmRzoAiHy+Ea36UEdRRXPlR' +
  'RlCR5g+iNt/7CGoqr3zvAuRXvucR1CrQ/GES+fMOjzvgQH3seN8B3ao036uASVWan+Pxybgflqf/LY78wH2dBPF6I/bY8txyZXlnOUsAAAAA' +
  'AAAAAAAAAAAAAAAAEIgb8WKMjSFbuAQAAAAASUVORK5CYII='

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
  Expand = 0,
  Collapse,
}

export enum InteractionStatus {
  Normal = 0,
  Selected,
  Edit,
  FinishEdit,
  DragInsert,
  FinishDragInsert,
}

interface childNodeInfo {
  isHasChildNode: boolean;
  childNum: number;
  allChildNum: number;
}

interface nodeItem {
  imageNode?: ImageNode;
  inputText: InputText;
  mainTitleNode: MainTitleNode;
  imageCollapse?: ImageNode;
  fontColor?: Resource;
}

interface status {
  normal: Resource;
  hover: Resource;
  press: Resource;
  selected: string;
  highLight?: Resource;
}

interface nodeBorder {
  borderWidth: Resource | number;
  borderColor: Resource;
  borderRadius: Resource;
}

interface popUpInfo {
  popUpIsShow: boolean;
  popUpEnableArrow: boolean;
  popUpColor?: Resource;
  popUpText?: string | Resource;
  popUpTextColor?: Resource;
}

interface borderWidth {
  has: Resource | number;
  none: Resource | number;
}

interface textSetting {
  fontColor: Resource;
  fontSize: Resource;
  fontWeight: FontWeight;
}

interface nodeInfo {
  itemId?: number;
  itemIcon?: Resource | string;
  itemTitle?: ResourceStr;
  isFolder?: boolean;
}

interface floorConstraintSize {
  minWidth: string;
  maxWidth: string;
}

interface textConstraintSize {
  minWidth1: string;
  maxWidth1: string;
  minWidth2: string;
  maxWidth2: string;
}

interface padding {
  left: string;
  right: string;
}

interface itemPadding {
  left: string | Resource;
  right: string | Resource;
  top: string | Resource;
  bottom: string | Resource;
}

interface shadow {
  radius: Resource;
  color: string;
  offsetX?: number;
  offsetY?: number;
}

interface dragPopup {
  floorConstraintSize: floorConstraintSize;
  textConstraintSize: textConstraintSize;
  padding: padding;
  backgroundColor: ResourceColor;
  height: string;
  shadow: shadow;
  borderRadius: Resource;
  fontColor: Resource;
  fontSize: Resource;
  fontWeight: FontWeight;
  imageOpacity: Resource;
}

interface DragNodeParam {
  parentId: number,
  currentId: number,
  data: NodeParam,
}

interface flagLine {
  flagLineHeight: string;
  flagLineColor: Resource;
  xOffset: string;
  yTopOffset: string;
  yBottomOffset: string;
  yBasePlateOffset: string;
}

interface subTitleStyle {
  normalFontColor: Resource;
  highLightFontColor: Resource;
  fontSize: Resource;
  fontWeight: FontWeight;
  margin: padding;
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

@Observed
export class NodeInfo {
  private childNodeInfo: childNodeInfo;
  imageSource: Resource | string | undefined = '';
  private parentNodeId: number;
  private currentNodeId: number;
  fontColor: string | Resource = '';
  private nodeHeight: Resource | number;
  private nodeLevel: number;
  private nodeItem: nodeItem;
  private nodeLeftPadding: number;
  private nodeColor: Resource | string;
  private nodeIsShow: boolean;
  private status: status;
  private nodeBorder: nodeBorder;
  private popUpInfo: popUpInfo;
  private listItemHeight: number;
  private container: () => void;
  private isShowTitle: boolean;
  private isShowInputText: boolean;
  private isSelected: boolean;
  readonly borderWidth: borderWidth =
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

  constructor(node: NodeItem) {
    this.childNodeInfo = node.getChildNodeInfo();
    this.nodeItem = {
      imageNode: undefined,
      inputText: new InputText(),
      mainTitleNode: node.getNodeItem().mainTitleNode,
      imageCollapse: undefined,
      fontColor: undefined,
    };
    this.popUpInfo = {
      popUpIsShow: false,
      popUpEnableArrow: false,
      popUpColor: undefined,
      popUpText: '',
      popUpTextColor: undefined,
    };
    this.nodeItem.imageNode = node.getNodeItem().imageNode;
    this.nodeItem.imageCollapse = node.getNodeItem().imageCollapse;
    this.container = node.container;
    this.parentNodeId = node.parentNodeId;
    this.currentNodeId = node.currentNodeId;
    this.nodeHeight = NODE_HEIGHT;
    this.nodeLevel = node.nodeLevel;
    this.nodeLeftPadding = node.nodeLevel * 12 + 8; // calculate left padding
    this.nodeColor = $r('sys.color.ohos_id_color_background');
    this.nodeIsShow = (this.nodeLevel > 0) ? false : true;
    this.listItemHeight = (this.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
    this.isShowTitle = true;
    this.isShowInputText = false;
    this.isSelected = false;
    this.status = {
      normal: $r('sys.color.ohos_id_color_background_transparent'),
      hover: $r('sys.color.ohos_id_color_hover'),
      press: $r('sys.color.ohos_id_color_click_effect'),
      selected: COLOR_SELECT,
      highLight: $r('sys.color.ohos_id_color_activated')
    };
    this.nodeBorder = { borderWidth: BORDER_WIDTH_NONE,
      borderColor: $r('sys.color.ohos_id_color_focused_outline'),
      borderRadius: $r('sys.float.ohos_id_corner_radius_clicked')
    };
    this.flagLineLeftMargin = node.nodeLevel * 12 + 8;
    this.node = node;
    this.nodeParam = node.data;
  }

  setFontColor(color: string | Resource) {
    this.fontColor = color
  }

  getFontColor() {
    return this.fontColor;
  }

  getPopUpInfo() {
    return this.popUpInfo;
  }

  setPopUpIsShow(isShow: boolean) {
    this.popUpInfo.popUpIsShow = isShow;
  }

  setPopUpEnableArrow(popUpEnableArrow: boolean) {
    this.popUpInfo.popUpEnableArrow = popUpEnableArrow;
  }

  setPopUpColor(color: Resource) {
    this.popUpInfo.popUpColor = color;
  }

  setPopUpText(text: string | Resource | undefined) {
    this.popUpInfo.popUpText = text;
  }

  setPopUpTextColor(popUpTextColor: Resource) {
    this.popUpInfo.popUpTextColor = popUpTextColor;
  }

  getIsShowTitle() {
    return this.isShowTitle;
  }

  getIsShowInputText() {
    return this.isShowInputText;
  }

  setTitleAndInputTextStatus(isModify: boolean) {
    if (isModify) {
      this.isShowTitle = false;
      this.isShowInputText = true;
    } else {
      this.isShowTitle = true;
      this.isShowInputText = false;
    }
  }

  handleImageCollapseAfterAddNode(isAddImageCollapse: boolean) {
    // listTree this node already has ImageCollapse.
    if (isAddImageCollapse) {
      this.nodeItem.imageCollapse = new ImageNode(
        ARROW_DOWN,
        $r('sys.float.ohos_id_alpha_content_tertiary'),
        IMAGE_NODE_HEIGHT,
        IMAGE_NODE_WIDTH,
        undefined,
        undefined
      );
      this.nodeItem.imageCollapse.itemRightMargin = ($r('sys.float.ohos_id_text_paragraph_margin_xs'));
    } else {
      this.nodeItem.imageCollapse = undefined;
    }
  }

  setNodeColor(nodeColor: Resource | string | undefined): void {
    if (nodeColor === undefined) {
      return;
    }
    this.nodeColor = nodeColor;
  }

  getNodeColor(): Resource | string {
    return this.nodeColor;
  }

  setListItemHeight(listItemHeight: number): void {
    this.listItemHeight = listItemHeight;
  }

  getListItemHeight(): number {
    return this.listItemHeight;
  }

  getNodeCurrentNodeId(): number {
    return this.currentNodeId;
  }

  getNodeParentNodeId(): number {
    return this.parentNodeId;
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

  getNodeItem() {
    return this.nodeItem;
  }

  getNodeStatus() {
    return this.status;
  }

  getNodeBorder() {
    return this.nodeBorder;
  }

  setNodeBorder(isClearFocusStatus: boolean): void {
    this.nodeBorder.borderWidth = isClearFocusStatus ? this.borderWidth.has : this.borderWidth.none;
  }

  getChildNodeInfo() {
    return this.childNodeInfo;
  }

  getCurrentNodeId(): number {
    return this.currentNodeId;
  }

  getMenu() {
    return this.container;
  }

  setIsSelected(isSelected: boolean) {
    this.isSelected = isSelected;
  }

  getIsSelected() {
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

  public getIsFolder() {
    return this.nodeParam.isFolder;
  }

  public setCanShowFlagLine(canShowFlagLine: boolean) {
    this.canShowFlagLine = canShowFlagLine;
  }

  public getCanShowFlagLine(): boolean {
    return this.canShowFlagLine;
  }

  public setFlagLineLeftMargin(currentNodeLevel: number | undefined) {
    if (currentNodeLevel === undefined) {
      return;
    }
    this.flagLineLeftMargin = currentNodeLevel * 12 + 8; // calculate
  }

  public getFlagLineLeftMargin(): number {
    return this.flagLineLeftMargin;
  }

  public getNodeLevel(): number {
    return this.nodeLevel;
  }

  public setIsOverBorder(isOverBorder: boolean) {
    this.isOverBorder = isOverBorder;
  }

  public getIsOverBorder() {
    return this.isOverBorder;
  }

  public setCanShowBottomFlagLine(canShowBottomFlagLine: boolean) {
    this.canShowBottomFlagLine = canShowBottomFlagLine;
  }

  public getCanShowBottomFlagLine() {
    return this.canShowBottomFlagLine;
  }

  public setIsHighLight(isHighLight: boolean) {
    this.isHighLight = isHighLight;
  }

  public getIsHighLight(): boolean {
    return this.isHighLight;
  }

  public setIsModify(isModify: boolean) {
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
  _events: [(callbackParam: CallbackParam) => void] | [] = [];
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
        this.on((type as Array<TreeListenType>)[i], callback);
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
        this.off((type as Array<TreeListenType>)[i], callback);
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
      let cbs_once: Array<(callbackParam: CallbackParam) => void> = Array.from<(callbackParam: CallbackParam) => void>(this._once_events[event]);
      if (cbs_once) {
        for (let i: number = 0, l: number = cbs_once.length; i < l; i++) {
          try {
            cbs_once[i](argument);
          } catch (e) {
            new Error(e);
          }
        }
        this._once_events[event] = null;
      }
    } else if (this._events[event]) {
      let cbs_on: Array<(callbackParam: CallbackParam) => void> = Array.from<(callbackParam: CallbackParam) => void>(this._events[event]);
      if (cbs_on) {
        for (let i: number = 0, l: number = cbs_on.length; i < l; i++) {
          try {
            cbs_on[i](argument);
          } catch (e) {
            new Error(e);
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
  static readonly APP_KEY_EVENT_BUS = 'app_key_event_bus';
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
  @State listItemBgColor: Resource = $r('sys.color.ohos_id_color_background_transparent');

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
  private readonly itemPadding: itemPadding = {
    left: $r('sys.float.ohos_id_card_margin_start'),
    right: $r('sys.float.ohos_id_card_margin_end'),
    top: $r('sys.float.ohos_id_text_margin_vertical'),
    bottom: $r('sys.float.ohos_id_text_margin_vertical'),
  };
  private readonly textInputPadding: itemPadding =
    { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' }

  aboutToAppear(): void {
    if (this.treeController !== null) {
      this.listNodeDataSource = this.treeController.getListNodeDataSource();
      this.nodeList = this.treeController.getListNodeDataSource().listNode;
      this.item = this.treeController.getListNodeDataSource().listNode;
    }
  }

  @Builder
  popupForShowTitle(text: string | Resource, backgroundColor: Resource, fontColor: Resource) {
    Row() {
      Text(text).fontSize($r('sys.float.ohos_id_text_size_body2')).fontWeight('regular').fontColor(fontColor)
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
        }
        .backgroundColor(COLOR_IMAGE_ROW)
        .margin({ right: item.getNodeItem().imageNode?.itemRightMargin })
        .height(item.getNodeItem().imageNode?.itemHeight)
        .width(item.getNodeItem().imageNode?.itemWidth)
      }

      Row() {
        if (item.getNodeItem().mainTitleNode && item.getIsShowTitle()) {
          Text(item.getNodeItem().mainTitleNode?.title)
            .maxLines(1)
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
        this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2 })
    }
    .constraintSize({ minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
      maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth })
    .height(this.listNodeDataSource.getDragPopupPara().height)
    .backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor)
    .padding({ left: this.listNodeDataSource.getDragPopupPara().padding.left,
      right: this.listNodeDataSource.getDragPopupPara().padding.right })
    .shadow({ radius: $r('sys.float.ohos_id_corner_radius_default_m'),
      color: SHADOW_COLOR,
      offsetY: 0 })
    .borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius) // need to doubleCheck.
  }

  clearLastIndexColor() {
    if (this.viewLastIndex === -1 || this.viewLastIndex >= this.nodeList.length) {
      return;
    }
    this.setImageSources(this.viewLastIndex, InteractionStatus.Normal);

    this.nodeList[this.viewLastIndex].setNodeColor($r('sys.color.ohos_id_color_background_transparent'))
    this.nodeList[this.viewLastIndex].fontColor = $r('sys.color.ohos_id_color_primary');
    this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor($r('sys.color.ohos_id_color_background_transparent'));
    this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = $r('sys.color.ohos_id_color_primary');
    this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(false);
    this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.Normal);
  }

  setImageSources(index: number, interactionStatus: InteractionStatus) {
    let nodeInfo: NodeInfo = this.nodeList[index];
    nodeInfo.setIsSelected(interactionStatus === InteractionStatus.Selected ||
      interactionStatus === InteractionStatus.Edit || interactionStatus === InteractionStatus.FinishEdit);
    if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DragInsert &&
      interactionStatus !== InteractionStatus.FinishDragInsert) {
      nodeInfo.getNodeItem().mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.Selected ||
        interactionStatus === InteractionStatus.FinishEdit);
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
              this.listNodeDataSource.setImageSource(index, InteractionStatus.Selected);
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
              this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
              this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
            }
          })
        }
        .width('100%')
        .height(itemInner.getListItemHeight())
        .padding({ left: this.itemPadding.left, right: this.itemPadding.right })
        .align(Alignment.Start)
        .onDragStart((event: DragEvent, extraParams: string) => {
          if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
            console.error('drag error, a item has been dragged');
            return;
          }
          this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
          let currentNodeIndex: number = JSON.parse(extraParams).selectedIndex;
          let currentNodeInfo: NodeInfo = this.listNodeDataSource.getData(currentNodeIndex) as NodeInfo;
          let currentItemNodeId: number = itemInner.getNodeCurrentNodeId();
          /* handle the situation of drag error, currentNodeIndex is not found in onDragStart. */
          if (currentNodeIndex >= this.listNodeDataSource.totalCount() || currentNodeIndex === undefined) {
            console.error('drag error, currentNodeIndex is not found in onDragStart');
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
            console.error('drag is too fast,it attribute a fault to OH');
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
        console.error('drag error, a item has been dragged');
        return;
      }
      let nodeHeight: number = LIST_ITEM_HEIGHT;

      /* flag the position of the focus on the node. */
      let flag: Flag = Math.floor(event.getY() / (nodeHeight / FLAG_NUMBER)) % FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;

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
      let currentNodeId: number | undefined = currentNodeInfo?.getCurrentNodeId();

      /**
       * handle a situation that "draggingCurrentNodeId" is parent of "insertNodeCurrentNodeId";
       * do not perform some functions.
       */
      if (index !== this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
        let isParentNodeOfInsertNode: boolean = this.listNodeDataSource.getIsParentOfInsertNode(currentNodeId);
        if (isParentNodeOfInsertNode) {
          this.listNodeDataSource.setPassIndex(index);
          if (currentNodeId !== undefined) {
            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex(this.listNodeDataSource,
              currentNodeId));
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
        this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex(this.listNodeDataSource, currentNodeId),
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
        console.error('drag error, currentNodeIndex is not found');
        this.listNodeDataSource.setIsDrag(false);
        return;
      }

      if (insertNodeIndex === this.listNodeDataSource.totalCount()) {
        console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
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
        let currentFocusIndex: number = findCurrentNodeIndex(this.listNodeDataSource, draggingCurrentNodeId);
        this.listNodeDataSource.setClickIndex(currentFocusIndex);
        this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);
        return;
      }

      /* Collapse drag node. */
      if (this.listNodeDataSource.getExpandAndCollapseInfo(draggingCurrentNodeId) === NodeStatus.Expand) {
        this.listNodeDataSource.expandAndCollapseNode(
          findCurrentNodeIndex(this.listNodeDataSource, draggingCurrentNodeId));
      }

      let flag: boolean = false;

      /* Expand insert node. */
      if (this.listNodeDataSource.getExpandAndCollapseInfo(insertNodeCurrentNodeId) === NodeStatus.Collapse) {
        let currentIndex: number = findCurrentNodeIndex(this.listNodeDataSource, insertNodeCurrentNodeId);
        if (this.listNodeDataSource.ListNode[currentIndex].getIsHighLight()) {
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
      let lastDelayHighLightIndex: number = findCurrentNodeIndex(this.listNodeDataSource,
        this.listNodeDataSource.getLastDelayHighLightId());
      this.listNodeDataSource.setLastDelayHighLightIndex(lastDelayHighLightIndex);
      this.listNodeDataSource.clearLastTimeoutHighLight();
      this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
      this.listNodeDataSource.setIsDrag(false);

      /* set the position of focus. */
      let currentFocusIndex: number = findCurrentNodeIndex(this.listNodeDataSource, draggingCurrentNodeId);
      this.listNodeDataSource.setClickIndex(currentFocusIndex);
      this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);

      /* innerDrag is over. */
      this.listNodeDataSource.setIsInnerDrag(false);
      this.listNodeDataSource.notifyDataReload();

      this.listNodeDataSource.listNode[currentFocusIndex].fontColor = $r('sys.color.ohos_id_color_text_primary_activated');
      if (this.viewLastIndex !== -1 && currentNodeIndex !== this.viewLastIndex) {
        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .mainTitleNode?.setMainTitleSelected(false);
        this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .mainTitleNode?.setMainTitleHighLight(false);
      }

      if (this.listNodeDataSource.listNode[this.viewLastIndex] !== null) {
        this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = $r('sys.color.ohos_id_color_text_primary');
      }

      this.listNodeDataSource.lastIndex = this.viewLastIndex;
      if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
        if (this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
          .imageNode !== null) {

          this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
            .imageNode?.setImageSource(InteractionStatus.Normal);
          this.listNodeDataSource.listNode[this.viewLastIndex].imageSource = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
            .imageNode?.source;
        }
      }

      if (this.listNodeDataSource.listNode[this.viewLastIndex]) {
        this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor($r('sys.color.ohos_id_color_background_transparent'));
      }

      this.viewLastIndex = currentFocusIndex;
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

/* nodeId to find index */
function findCurrentNodeIndex(listNodeDataSource: ListNodeDataSource, currentNodeId: number): number {
  let thisIndex: number = 0;
  listNodeDataSource.ListNode.forEach((value, index) => {
    if (value.getNodeCurrentNodeId() === currentNodeId) {
      thisIndex = index;
    }
  })
  return thisIndex;
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
  readonly ROOT_NODE_ID: number = -1;
  private nodeIdList: number[] = [];
  private listNodeUtils: ListNodeUtils = new ListNodeUtils();
  private listNodeDataSource: ListNodeDataSource = new ListNodeDataSource();
  private initBuild: boolean = true;

  public getListNodeDataSource(): ListNodeDataSource {
    return this.listNodeDataSource;
  }

  public getClickNodeChildrenInfo(): Array<nodeInfo> {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    return this.listNodeUtils.getClickNodeChildrenInfo(clickNodeId);
  }

  public getChildrenId(): Array<number> {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    return this.listNodeUtils.getClickChildId(clickNodeId);
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
    let parentNodeId: number = this.listNodeUtils.findParentNodeId(clickNodeId);
    let removeNodeIdList: number[] = this.listNodeUtils.removeNode(clickNodeId, parentNodeId);
    this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, parentNodeId, removeNodeIdList);
    this.nodeIdList.splice(this.nodeIdList.indexOf(clickNodeId), 1);
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

  public add(): void {
    let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
    if (clickNodeId === this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(clickNodeId)) {
      return;
    }
    let newNodeInfo: NodeParam = this.listNodeUtils.getNewNodeInfo(clickNodeId);
    this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
    let newNodeId: number = this.nodeIdList[this.nodeIdList.length - 1];
    this.listNodeUtils.addNewNodeId = newNodeId;
    this.listNodeUtils.addNode(clickNodeId, newNodeId,
      {
        isFolder: newNodeInfo.isFolder,
        icon: newNodeInfo.icon,
        selectedIcon: newNodeInfo.selectedIcon,
        editIcon: newNodeInfo.editIcon,
        primaryTitle: '新建文件夹',
        container: newNodeInfo.container,
        secondaryTitle: newNodeInfo.secondaryTitle as ResourceStr,
      });
    this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, clickNodeId, [newNodeId]);

    this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
    this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
    this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()].setFontColor($r('sys.color.ohos_id_color_text_primary'));

    let newNodeIndex: number = findCurrentNodeIndex(this.listNodeDataSource, newNodeId);
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
      this.add();
      return this;
    } else {
      if (nodeParam.primaryTitle !== undefined &&
        !this.listNodeUtils.checkMainTitleIsValid(nodeParam.primaryTitle.toString())) {
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
          this.listNodeUtils.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam);
        }
      }
      if (!this.initBuild && nodeParam.parentNodeId !== undefined) {
        let newNodeId: number = this.nodeIdList[this.nodeIdList.length - 1];
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, nodeParam.parentNodeId, [newNodeId]);
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
    this.listNodeDataSource.init(this.listNodeUtils);
    this.nodeIdList.sort((a, b) => a - b);
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

class ListNodeDataSource extends BasicDataSource {
  readonly ROOT_NODE_ID = -1;
  public listNodeUtils: ListNodeUtils = new ListNodeUtils();
  listNode: NodeInfo[] = [];
  private readonly INITIAL_INVALID_VALUE = -1;
  public lastIndex: number = -1; // record the last focused node.
  thisIndex: number = -1; // records clicked nodes in the current period.
  private modifyNodeIndex: number = -1; // records the nodes edited in the current period.
  modifyNodeId: number = -1;
  private currentOperation?: MenuOperation;
  private expandAndCollapseInfo: Map<number, NodeStatus> = new Map<number, NodeStatus>();
  loadedNodeIdAndIndexMap: Map<number, number> = new Map<number, number>(); // [currentNodeId, index]
  private isTouchDown: boolean = false;
  private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
  /* parameter of the drag event. */
  private isInnerDrag: boolean = false; // Judge whether it is an internal drag event.
  private isDrag: boolean = false; // It is used to handle events(For example, prevent press events) during global drag.
  private draggingCurrentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the current ID of the dragged node.
  private draggingParentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the parent ID of the dragged node.
  private currentNodeInfo: NodeInfo | null = null; // To solve the problem of currentIndex missed in onDrop event.
  private listItemOpacity: number = 1; // It is used to set the opacity of the node when dragged.
  private lastPassIndex: number = this.INITIAL_INVALID_VALUE; // record the last passing node index in drag.
  private lastPassId?: number = this.INITIAL_INVALID_VALUE; // record the last passing node Id in drag.
  private thisPassIndex: number = this.INITIAL_INVALID_VALUE; // record the current passing node in drag.
  private lastDelayExpandIndex: number = this.INITIAL_INVALID_VALUE; // record last passing node in delay expand event.
  private timeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private lastTimeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private clearTimeoutExpandId: number = this.INITIAL_INVALID_VALUE;
  private timeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  private lastTimeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  private clearTimeoutHighLightId: number = this.INITIAL_INVALID_VALUE;
  private lastDelayHighLightIndex: number = this.INITIAL_INVALID_VALUE; // record last passing node in HighLight event.
  private lastDelayHighLightId: number = this.INITIAL_INVALID_VALUE; //record last passing node Id in HighLight event.
  private nodeIdAndSubtitleMap: Map<number, ResourceStr> = new Map<number, ResourceStr>(); // [currentNodeId, subtitle]
  private flag: Flag = Flag.NONE;
  private selectedParentNodeId: number = this.INITIAL_INVALID_VALUE;
  private selectedParentNodeSubtitle: ResourceStr = '';
  private insertNodeSubtitle: ResourceStr = '';
  private currentFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  private lastFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  private addFocusNodeId: number = this.INITIAL_INVALID_VALUE;
  readonly FLAG_LINE: flagLine = {
    flagLineHeight: FLAG_LINE_HEIGHT,
    flagLineColor: $r('sys.color.ohos_id_color_emphasize'),
    xOffset: X_OFF_SET,
    yTopOffset: Y_OFF_SET,
    yBottomOffset: Y_BOTTOM_OFF_SET,
    yBasePlateOffset: Y_BASE_PLATE_OFF_SET,
  }
  private readonly DRAG_POPUP: dragPopup = {
    floorConstraintSize: { minWidth: FLOOR_MIN_WIDTH, maxWidth: FLOOR_MAX_WIDTH },
    textConstraintSize: {
      minWidth1: TEXT_MIN_WIDTH,
      maxWidth1: TEXT_MAX_WIDTH,
      minWidth2: MIN_WIDTH,
      maxWidth2: MAX_WIDTH,
    },
    padding: { left: LEFT_PADDING, right: RIGHT_PADDING },
    backgroundColor: COLOR_IMAGE_EDIT,
    height: GRAG_POP_UP_HEIGHT,
    shadow: {
      radius: $r('sys.float.ohos_id_corner_radius_default_m'),
      color: SHADOW_COLOR,
      offsetX: 0,
      offsetY: SHADOW_OFFSETY,
    },
    borderRadius: $r('sys.float.ohos_id_corner_radius_clicked'),
    fontColor: $r('sys.color.ohos_id_color_primary'),
    fontSize: $r('sys.float.ohos_id_text_size_body1'),
    fontWeight: FontWeight.Regular,
    imageOpacity: $r('sys.float.ohos_id_alpha_content_fourth')
  };
  private readonly subTitle: subTitleStyle = {
    normalFontColor: $r('sys.color.ohos_id_color_secondary'),
    highLightFontColor: $r('sys.color.ohos_id_color_primary_contrary'),
    fontSize: $r('sys.float.ohos_id_text_size_body2'),
    fontWeight: FontWeight.Regular,
    margin: { left: '4vp', right: '24' }
  }

  public changeNodeColor(index: number, color: Resource | string | undefined): void {
    this.listNode[index].setNodeColor(color);
    this.listNode[index].setNodeBorder(false);
  }

  private getNodeColor(index: number) {
    return this.listNode[index].getNodeColor();
  }

  private handleFocusEffect(index: number, isClearFocusStatus: boolean) {
    if (this.listNode[index].getNodeIsShow()) {
      this.listNode[index].setNodeBorder(isClearFocusStatus);
    }
  }

  public setImageSource(index: number, interactionStatus: InteractionStatus) {
    let nodeInfo: NodeInfo = this.listNode[index];
    nodeInfo.setIsSelected(interactionStatus === InteractionStatus.Selected ||
      interactionStatus === InteractionStatus.Edit || interactionStatus === InteractionStatus.FinishEdit);
    if (nodeInfo.getNodeItem().mainTitleNode !== null && interactionStatus !== InteractionStatus.DragInsert &&
      interactionStatus !== InteractionStatus.FinishDragInsert) {
      nodeInfo.getNodeItem().mainTitleNode?.setMainTitleSelected(interactionStatus === InteractionStatus.Selected ||
        interactionStatus === InteractionStatus.FinishEdit);
    }
    if (nodeInfo.getNodeItem().imageNode !== null) {
      nodeInfo.getNodeItem().imageNode?.setImageSource(interactionStatus);
    }
  }

  private setImageCollapseSource(index: number, interactionStatus: InteractionStatus) {
    let nodeInfo: NodeInfo = this.listNode[index];
    if (nodeInfo.getNodeItem().imageCollapse !== undefined) {
      nodeInfo.getNodeItem().imageCollapse?.setImageCollapseSource(interactionStatus,
        this.expandAndCollapseInfo.get(nodeInfo.getCurrentNodeId()));
    }
  }

  public clearLastIndexStatus() {
    if (this.lastIndex === -1 || this.lastIndex >= this.listNode.length) {
      return;
    }
    this.setImageSource(this.lastIndex, InteractionStatus.Normal);
    this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
    this.handleFocusEffect(this.lastIndex, false);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getCurrentNodeId()));
  }

  private changeNodeStatus(clickIndex: number): void {
    let thisIndex: number = clickIndex;
    let tmp: NodeInfo[] = this.ListNode;
    let nodeId: number = tmp[clickIndex].getCurrentNodeId();
    if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.Expand) {
      this.expandAndCollapseInfo.set(nodeId, NodeStatus.Collapse);
      tmp[thisIndex].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
    } else if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.Collapse) {
      this.expandAndCollapseInfo.set(nodeId, NodeStatus.Expand);
      tmp[thisIndex].getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
    }
  }

  private handleExpandAndCollapse(clickIndex: number) {
    let thisIndex: number = clickIndex;
    let tmp: NodeInfo[] = this.ListNode;
    let nodeId: number = tmp[thisIndex].getCurrentNodeId();
    if (!this.expandAndCollapseInfo.has(nodeId)) {
      return;
    }

    let rootNodeStatus: NodeStatus | undefined = this.expandAndCollapseInfo.get(nodeId);
    if (tmp[thisIndex].getChildNodeInfo().isHasChildNode && rootNodeStatus === NodeStatus.Collapse) {
      for (let i: number = 0; i < tmp[thisIndex].getChildNodeInfo().allChildNum; i++) {
        tmp[thisIndex + 1 + i].setNodeIsShow(false);
        tmp[thisIndex + 1 + i].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
      }
      this.notifyDataReload();
      return;
    }

    let childNum: number[] | null = new Array(tmp[thisIndex].getChildNodeInfo().childNum);
    childNum[0] = thisIndex + 1;
    let index: number = 1;
    while (index < tmp[thisIndex].getChildNodeInfo().childNum) {
      childNum[index] = childNum[index -1] + tmp[childNum[index - 1]].getChildNodeInfo().allChildNum + 1;
      index++;
    }
    if (rootNodeStatus === NodeStatus.Expand) {
      for (let i: number = 0; i < childNum.length; i++) {
        tmp[childNum[i]].setNodeIsShow(true);
        tmp[childNum[i]].setListItemHeight(LIST_ITEM_HEIGHT);
        let nodeId: number = tmp[childNum[i]].getCurrentNodeId();
        if (this.expandAndCollapseInfo.get(nodeId) === NodeStatus.Expand) {
          this.handleExpandAndCollapse(childNum[i]);
        }
      }
    }
    childNum = null;
    this.notifyDataReload();
  }

  public init(listNodeUtils: ListNodeUtils) {
    let index: number = 0;
    this.listNode = [];
    this.listNodeUtils = listNodeUtils;
    this.loadedNodeIdAndIndexMap.clear();
    this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
      if (node.currentNodeId >= 0) {
        let nodeInfo: NodeInfo = new NodeInfo(node);
        this.listNode.push(nodeInfo);
        if (nodeInfo.getChildNodeInfo().isHasChildNode) {
          this.expandAndCollapseInfo.set(nodeInfo.getCurrentNodeId(), NodeStatus.Collapse);
        }
        if (nodeInfo.getNodeIsShow()) {
          this.loadedNodeIdAndIndexMap.set(nodeInfo.getCurrentNodeId(), index++);
        }
        if (nodeInfo.getIsFolder()) {
          if (nodeInfo.getNodeInfoData().secondaryTitle !== undefined) {
            this.nodeIdAndSubtitleMap.set(
              nodeInfo.getCurrentNodeId(),
              nodeInfo.getNodeInfoData().secondaryTitle as ResourceStr,
            );
          } else {
            this.nodeIdAndSubtitleMap.set(nodeInfo.getCurrentNodeId(), '');
          }
        }
      }
      return false;
    });
  }

  private refreshRemoveNodeData(removeNodeIdList: number[], parentNodeInfo: NodeInfo) {
    let deleteIndexList: number[] = [];
    for (let i: number = 0; i < removeNodeIdList.length; i++) {
      for (let j: number = 0; j < this.listNode.length; j++) {
        if (this.listNode[j].getNodeCurrentNodeId() === removeNodeIdList[i]) {
          let currentNodeId: number = this.listNode[j].getNodeCurrentNodeId();
          if (this.loadedNodeIdAndIndexMap.has(currentNodeId)) {
            // this.listNode index to lazyForEach index.
            deleteIndexList.push(this.loadedNodeIdAndIndexMap.get(currentNodeId) as number);
          }
          let deleteNode: NodeInfo[] | null = this.listNode.splice(j, 1);
          deleteNode = null; // free memory
          if (this.expandAndCollapseInfo.has(removeNodeIdList[i])) {
            this.expandAndCollapseInfo.delete(removeNodeIdList[i]); // delete deleteNode expandAndCollapseInfo.
          }
          break;
        }
      }
    }
    deleteIndexList.forEach((value) => {
      this.notifyDataDelete(value); // notifyDataDelete do not  update data.
      this.notifyDataChange(value); // call notifyDataChange to update data.
    })
    let index: number = 0;
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeCurrentNodeId() === parentNodeInfo.getNodeCurrentNodeId()) {
        if (parentNodeInfo.getNodeItem().imageCollapse === null) {
          this.listNode[i].handleImageCollapseAfterAddNode(false);
          // delete deleteNode parentNode expandAndCollapseInfo.
          this.expandAndCollapseInfo.delete(parentNodeInfo.getNodeCurrentNodeId());
          this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[i].getNodeCurrentNodeId()));
        }
        break;
      }
    }
    let callbackParam: CallbackParam = {
      currentNodeId: parentNodeInfo.getNodeCurrentNodeId(),
      parentNodeId: parentNodeInfo.getNodeParentNodeId(),
    };
    this.appEventBus.emit(TreeListenType.NODE_DELETE, callbackParam);
  }

  private refreshAddNodeData(addNodeIdList: number[]) {
    let addNodeInfo: NodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo));
    this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
      if (node.currentNodeId === addNodeIdList[0]) {
        addNodeInfo = new NodeInfo(node);
        return true;
      }
      return false;
    });
    addNodeInfo.setIsModify(true);

    let index: number = 0;
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeCurrentNodeId() === addNodeInfo.getNodeParentNodeId()) {
        index = i;
        if (this.listNode[i].getNodeItem().imageCollapse === null) {
          this.listNode[i].handleImageCollapseAfterAddNode(true);
          this.notifyDataChange(index);
        } else if (this.expandAndCollapseInfo.get(this.listNode[i].getNodeCurrentNodeId()) === NodeStatus.Collapse) {
          this.changeNodeStatus(index);
        }
        this.listNode.splice(i + 1, 0, addNodeInfo);
        this.listNode[i + 1].setTitleAndInputTextStatus(true); // false->true: realize inner Interaction.
        this.listNode[i + 1].setNodeIsShow(true);
        this.listNode[i + 1].setListItemHeight(LIST_ITEM_HEIGHT);
        this.setImageSource(i + 1, InteractionStatus.Edit); // Normal->Edit : realize inner Interaction.
        this.currentOperation = MenuOperation.ADD_NODE;
        this.notifyDataAdd(i + 1);
        this.notificationNodeInfo(i + 1, this.currentOperation);
        break;
      }
    }
    this.modifyNodeIndex = index + 1;
    this.setClickIndex(index);
    this.lastIndex = index;
    this.expandAndCollapseInfo.set(addNodeInfo.getNodeParentNodeId(), NodeStatus.Expand);
    this.handleExpandAndCollapse(index);
  }

  public refreshData(listNodeUtils: ListNodeUtils, operation: MenuOperation,
                     parentNodeId: number, changeNodeIdList: number[]) {
    let parentNodeInfo: NodeInfo = new NodeInfo(new NodeItem(emptyNodeInfo));
    this.listNodeUtils = listNodeUtils;
    this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
      if (node.currentNodeId === parentNodeId) {
        parentNodeInfo = new NodeInfo(node);
        return true;
      }
      return false;
    });

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

  public setClickIndex(index: number) {
    this.thisIndex = index;
  }

  public getClickNodeId(): number {
    if (this.thisIndex < 0 || this.thisIndex >= this.ListNode.length) {
      return -1;
    }
    return this.ListNode[this.thisIndex].getCurrentNodeId();
  }

  public expandAndCollapseNode(clickIndex: number) {
    this.changeNodeStatus(clickIndex);
    this.handleExpandAndCollapse(clickIndex);
  }

  public getIsTouchDown(): boolean {
    return this.isTouchDown;
  }

  public getLastIndex(): number {
    return this.lastIndex;
  }

  public findIndex(currentNodeId: number): number {
    let thisIndex: number = -1;
    this.ListNode.forEach((value, index) => {
      if (value.getNodeCurrentNodeId() === currentNodeId) {
        thisIndex = index;
      }
    })
    return thisIndex;
  }

  public handleEventDrag(index: number) {
    this.setImageSource(index, InteractionStatus.Normal);
    this.changeNodeColor(index, this.listNode[index].getNodeStatus().normal);
    this.handleFocusEffect(index, false);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId()));
  }

  public handleEvent(event: Event, index: number) {
    /* Return while the event is dragging event. */
    if (this.isDrag) {
      return;
    }

    if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
      if (index !== this.lastIndex) {
        this.clearLastIndexStatus();
      }
    }

    let lazyForEachIndex: number = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId()) as number;
    switch (event) {
      case Event.TOUCH_DOWN:
        this.isTouchDown = true;
        this.changeNodeColor(index, this.listNode[index].getNodeStatus().press);
        this.notifyDataChange(lazyForEachIndex);
        break;
      case Event.TOUCH_UP: {
        if (this.isInnerDrag) {
          this.isInnerDrag = false;
        }
        this.isTouchDown = false;
        let nodeInfo: NodeInfo = this.listNode[index];
        this.setImageSource(index, InteractionStatus.Selected);
        nodeInfo.setFontColor($r('sys.color.ohos_id_color_primary'));
        this.lastIndex = index;
        this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
        this.notifyDataChange(lazyForEachIndex);
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
        this.setImageSource(index, InteractionStatus.Selected);
        this.lastIndex = index;
        this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
        this.notifyDataChange(lazyForEachIndex);
        break;
      default:
        break;
    }
  }

  private notificationNodeInfo(addNodeId: number, operation: MenuOperation | undefined) {
    if (operation === MenuOperation.MODIFY_NODE) {
      let modifyNodeInfo: NodeInfo = this.listNode[this.modifyNodeIndex];
      let backParamModify: CallbackParam = { currentNodeId: modifyNodeInfo.getNodeCurrentNodeId(),
        parentNodeId: modifyNodeInfo.getNodeParentNodeId() }
      this.appEventBus.emit(TreeListenType.NODE_MODIFY, backParamModify);
    } else if (operation === MenuOperation.ADD_NODE) {
      let addNodeInfo: NodeInfo = this.listNode[addNodeId];
      let icon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.source : undefined;
      let selectedIcon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.selectedSource : undefined;
      let editIcon: Resource | string | undefined = (addNodeInfo.getNodeItem().imageNode !== undefined) ?
        addNodeInfo.getNodeItem().imageNode?.editSource : undefined;
      let callbackParam: CallbackParam = { currentNodeId: addNodeInfo.getNodeCurrentNodeId(),
        parentNodeId: addNodeInfo.getNodeParentNodeId() }
      this.appEventBus.emit(TreeListenType.NODE_ADD, callbackParam);
    }
  }

  public finishEditing() {
    if (this.modifyNodeIndex !== -1) {
      this.setImageSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
      this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
      this.listNode[this.modifyNodeIndex].setIsModify(false);
      this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(false);
      this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
      this.notifyDataChange(this.modifyNodeIndex);
    }
  }

  public setItemVisibilityOnEdit(nodeId: number, operation: MenuOperation) {
    let index: number = -1;
    if (nodeId === -1) {
      return;
    }
    if (operation === MenuOperation.MODIFY_NODE) {
      for (let i: number = 0; i < this.listNode.length; i++) { // nodeId to find index
        if (this.listNode[i].getCurrentNodeId() === nodeId) {
          index = i;
          break;
        }
      }
      let nodeInfo: NodeInfo = this.listNode[index];
      nodeInfo.setIsModify(true);
      if (nodeInfo.getNodeItem().mainTitleNode === null) {
        return; // no title
      }

      this.currentOperation = MenuOperation.MODIFY_NODE;
      nodeInfo.setTitleAndInputTextStatus(true);
      this.setImageSource(index, InteractionStatus.Edit);
      this.setImageCollapseSource(index, InteractionStatus.Edit);
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
      nodeInfo.setTitleAndInputTextStatus(false);
      nodeInfo.setIsModify(false);
      this.setImageSource(index, InteractionStatus.FinishEdit);
      this.setImageCollapseSource(index, InteractionStatus.FinishEdit);
      this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
      this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(nodeInfo.getCurrentNodeId()));
    }
  }

  public setPopUpInfo(popUpType: PopUpType, inputError: InputError, isShow: boolean, index: number) {
    let nodeInfo: NodeInfo = this.listNode[index];
    nodeInfo.setPopUpIsShow(isShow);
    // this.listNode index to lazyForEach index.
    let lazyForEachIndex: number = this.loadedNodeIdAndIndexMap.get(nodeInfo.getCurrentNodeId()) as number;
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
      nodeInfo.setPopUpTextColor($r('sys.color.ohos_id_color_text_secondary'));
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

  public setShowPopUpTimeout(timeout: number, index: number) {
    if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
      this.listNode[index].getNodeItem().mainTitleNode.popUpTimeout = timeout;
    }
    let lazyForEachIndex: number = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId()) as number;
    this.notifyDataChange(lazyForEachIndex);
  }

  public setMainTitleNameOnEdit(index: number, text: string) {
    this.modifyNodeIndex = index;
    if (this.listNode[index].getNodeItem().mainTitleNode !== null) {
      this.listNode[index].getNodeItem().mainTitleNode.title = text;
    }
  }

  public get ListNode(): NodeInfo[] {
    return this.listNode;
  }

  public totalCount(): number {
    let count: number = 0;
    let index: number = 0;
    this.loadedNodeIdAndIndexMap.clear();
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeIsShow()) {
        this.loadedNodeIdAndIndexMap.set(this.listNode[i].getCurrentNodeId(), index++);
        count++;
      }
    }
    return count;
  }

  public getData(index: number): NodeInfo | undefined {
    let count: number = 0;
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getNodeIsShow()) {
        if (index === count) {
          return this.listNode[i];
        }
        count++;
      }
    }
    return undefined;
  }

  public addData(index: number, data: NodeInfo): void {
    this.listNode.splice(index, 0, data);
    this.notifyDataAdd(index);
  }

  public pushData(data: NodeInfo): void {
    this.listNode.push(data);
    this.notifyDataAdd(this.listNode.length - 1);
  }

  public setIsInnerDrag(isInnerDrag: boolean) {
    this.isInnerDrag = isInnerDrag;
  }

  public getIsInnerDrag(): boolean {
    return this.isInnerDrag;
  }

  public setIsDrag(isDrag: boolean) {
    this.isDrag = isDrag;
  }

  public getIsDrag(): boolean {
    return this.isDrag;
  }

  public setCurrentNodeInfo(currentNodeInfo: NodeInfo | undefined) {
    if (currentNodeInfo === undefined) {
      return;
    }
    this.currentNodeInfo = currentNodeInfo;
  }

  public getCurrentNodeInfo(): NodeInfo | null {
    return this.currentNodeInfo;
  }

  public setDraggingParentNodeId(draggingParentNodeId: number | undefined) {
    if (draggingParentNodeId === undefined) {
      return;
    }
    this.draggingParentNodeId = draggingParentNodeId;
  }

  public getDraggingParentNodeId() {
    return this.draggingParentNodeId;
  }

  public getDraggingCurrentNodeId() {
    return this.draggingCurrentNodeId;
  }

  public setDraggingCurrentNodeId(draggingCurrentNodeId: number | undefined) {
    if (draggingCurrentNodeId === undefined) {
      return;
    }
    this.draggingCurrentNodeId = draggingCurrentNodeId;
  }

  public setListItemOpacity(listItemOpacity: number) {
    this.listItemOpacity = listItemOpacity;
  }

  public getListItemOpacity(item: NodeInfo) {
    return item.getCurrentNodeId() === this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
  }

  public getDragPopupPara() {
    return this.DRAG_POPUP;
  }

  public setLastPassIndex(lastPassIndex: number) {
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
    let isParentNodeOfInsertNode: boolean = false;
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === insertNodeId) {
        isParentNodeOfInsertNode = true;
        return true;
      }
      return false;
    };
    this.listNodeUtils.traverseNodeDF(callback, selectedNodeItem);
    return isParentNodeOfInsertNode;
  }

  public setPassIndex(thisPassIndex: number) {
    this.thisPassIndex = thisPassIndex;
  }

  public getPassIndex(): number {
    return this.thisPassIndex;
  }

  public clearTimeOutAboutDelayHighLightAndExpand(currentIndex: number) {
    if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
      let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
      this.ListNode.forEach((value) => {
        if (value.getNodeCurrentNodeId() === this.lastPassId) {
          value.setCanShowFlagLine(false);
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
          .get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId()) as number;
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

  public clearHighLight(currentIndex: number) {
    this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().normal);
    this.changeNodeHighLightColor(currentIndex, false);
    this.setImageSource(currentIndex, InteractionStatus.FinishDragInsert);
    this.setImageCollapseSource(currentIndex, InteractionStatus.FinishDragInsert);
    this.listNode[currentIndex].setIsHighLight(false);
  }

  private changeNodeHighLightColor(index: number, isHighLight: boolean): void {
    if (this.listNode[index].getNodeItem().mainTitleNode && this.listNode[index].getIsShowTitle()) {
      this.listNode[index].getNodeItem().mainTitleNode?.setMainTitleHighLight(isHighLight);
    }
  }

  public setVisibility(flag: Flag, index: number, isOverBorder: boolean) {
    let isChanged: boolean = (this.thisPassIndex !== index || this.flag !== flag) ? true : false;
    this.thisPassIndex = index;
    if ((isChanged || isOverBorder) && this.isInnerDrag) {
      this.flag = flag;
      let currentNodeId: number | undefined = this.getData(index)?.getCurrentNodeId();
      let currentNodeLevel: number | undefined = this.getData(index)?.getNodeLevel();
      if (currentNodeId !== undefined) {
        currentNodeLevel = (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.Expand &&
          this.flag === Flag.DOWN_FLAG) ? (currentNodeLevel ? currentNodeLevel + 1 : undefined) : currentNodeLevel;
        if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
          let lastIndex: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
          this.ListNode.forEach((value) => {
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

  public delayHighLightAndExpandNode(currentIndex: number, currentNodeId: number, showIndex: number) {
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
        (this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.Collapse && this.isInnerDrag) ||
        (!this.expandAndCollapseInfo.has(currentNodeId) && this.listNode[currentIndex].getIsFolder()));
      if (canDelayHighLight) {
        /* set hoverState color before highLight. */
        this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().hover);
        this.notifyDataChange(showIndex);

        let delayHighLightTime: number = this.isInnerDrag ? 1000 : 0; // ms
        this.timeoutHighLightId = setTimeout(() => {
          this.delayHighLight(currentIndex);
        }, delayHighLightTime)
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
      if (!isOverBorder && this.expandAndCollapseInfo.get(currentNodeId) === NodeStatus.Collapse) {
        let firstChildNodeId: number | undefined = this.getData(showIndex)?.getNodeInfoNode().children[0].currentNodeId;
        let delayAlterFlagLineAndExpandNodeTime: number = 2000; // ms
        this.timeoutExpandId = setTimeout(() => {
          this.clearHighLight(this.lastDelayHighLightIndex);
          if (firstChildNodeId !== undefined) {
            this.alterFlagLineAndExpandNode(currentIndex, firstChildNodeId);
          }
        }, delayAlterFlagLineAndExpandNodeTime)
      }
      if (isOverBorder || (this.lastTimeoutExpandId !== this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutExpandId !== this.lastTimeoutExpandId)) {
        clearTimeout(this.lastTimeoutExpandId);
        this.clearTimeoutExpandId = this.lastTimeoutExpandId;
      }
      this.lastTimeoutExpandId = this.timeoutExpandId;
    }
  }

  public delayHighLight(currentIndex: number) {
    this.ListNode.forEach((value) => {
      if (value.getNodeCurrentNodeId() === this.lastPassId) {
        value.setCanShowFlagLine(false);
        value.setCanShowBottomFlagLine(false);
      }
    })
    this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().highLight);
    this.listNode[currentIndex].setIsHighLight(true);
    this.changeNodeHighLightColor(currentIndex, true);
    this.setImageSource(currentIndex, InteractionStatus.DragInsert);
    this.setImageCollapseSource(currentIndex, InteractionStatus.DragInsert);
    this.notifyDataReload();
  }

  public alterFlagLineAndExpandNode(currentIndex: number, firstChildNodeId: number) {
    this.ListNode.forEach((value) => {
      if (value.getNodeCurrentNodeId() === this.lastPassId) {
        value.setCanShowFlagLine(false);
        value.setCanShowBottomFlagLine(false);
      }
    })
    this.ListNode.forEach((value) => {
      if (this.isInnerDrag && value.getNodeCurrentNodeId() === firstChildNodeId) {
        value.setCanShowFlagLine(true);
      }
    })
    this.changeNodeStatus(currentIndex);
    this.handleExpandAndCollapse(currentIndex);
    this.lastPassId = firstChildNodeId;
  }

  public hideLastLine() {
    if (this.lastPassId !== this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId as number)) {
      this.ListNode.forEach((value) => {
        if (value.getNodeCurrentNodeId() === this.lastPassId) {
          value.setCanShowFlagLine(false);
          value.setCanShowBottomFlagLine(false);
        }
      })
      let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId as number) as number;
      this.notifyDataChange(index);
    }
  }

  public clearLastTimeoutHighLight() {
    if (this.lastTimeoutHighLightId !== this.INITIAL_INVALID_VALUE &&
      this.clearTimeoutHighLightId !== this.lastTimeoutHighLightId) {
      clearTimeout(this.lastTimeoutHighLightId);
      if (this.lastDelayHighLightIndex !== this.INITIAL_INVALID_VALUE) {
        this.clearHighLight(this.lastDelayHighLightIndex);
      }
    }
  }

  public clearLastTimeoutExpand() {
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

  public hasSubtitle(currentNodeId: number) {
    return this.nodeIdAndSubtitleMap.has(currentNodeId);
  }

  public initialParameterAboutDelayHighLightAndExpandIndex() {
    this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
    this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
    this.lastPassIndex = this.INITIAL_INVALID_VALUE;
    this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
    this.flag = Flag.NONE;
  }

  public refreshSubtitle(insertNodeCurrentNodeId: number) {
    this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
    this.nodeIdAndSubtitleMap.set(insertNodeCurrentNodeId, this.insertNodeSubtitle);
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
    this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(insertNodeCurrentNodeId));
  }

  public setNodeSubtitlePara(
    selectedParentNodeId: number,
    selectedParentNodeSubtitle: ResourceStr,
    insertNodeSubtitle: ResourceStr
  ) {
    this.selectedParentNodeId = selectedParentNodeId;
    this.selectedParentNodeSubtitle = selectedParentNodeSubtitle;
    this.insertNodeSubtitle = insertNodeSubtitle;
  }

  public getInsertNodeSubtitle() {
    return this.insertNodeSubtitle;
  }

  public getExpandAndCollapseInfo(currentNodeId: number) {
    return this.expandAndCollapseInfo.get(currentNodeId);
  }

  public getLastDelayHighLightId() {
    return this.lastDelayHighLightId;
  }

  public setLastDelayHighLightId() {
    this.ListNode.forEach((value, index) => {
      if (index === this.lastDelayHighLightIndex) {
        this.lastDelayHighLightId = value.getCurrentNodeId();
      }
    })
  }

  public setLastPassId(lastPassId: number) {
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
                       dragParentNodeId: number, dragCurrentNodeId: number, frontNodeInfoItem: NodeInfo) {
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
      if (this.listNode[i].getCurrentNodeId() === rearCurrentNodeId) {
        isHighLight = this.listNode[i].getIsHighLight();
        if (this.flag === Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.Expand) {
          parentNodeId = rearCurrentNodeId;
          insertChildIndex = 0;
        } else if (this.flag === Flag.UP_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.Expand
          && this.listNode[i].getCanShowFlagLine() === false) {
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

    let oneself: NodeItem | null = null;
    let callback: (node: NodeItem, listNode: NodeInfo[]) => boolean = (node: NodeItem, listNode: NodeInfo[]): boolean => {
      if (node) {
        oneself = node;
        parentNodeId = oneself.parentNodeId;
        currentNodeId = oneself.currentNodeId;
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
    this.listNodeUtils.dragTraverseNodeDF(callback, nodeInfoNode, this.listNode);

    /* Delete the dragging node from the tree. */
    this.listNodeUtils.removeNode(dragCurrentNodeId, dragParentNodeId);

    /**
     * Add the dragging node to the tree
     * 1.The first dragging node is added singly, because it needs to distinguish the position to insert
     *
     * Add first node.
     */
    let insertCurrentNodeId: number = rearCurrentNodeId;
    let isAfter: boolean = isDownFlag;
    if (this.expandAndCollapseInfo.get(rearCurrentNodeId) === NodeStatus.Expand) {
      isAfter = false;
      this.listNode.forEach((value) => {
        if (value.getCurrentNodeId() === rearCurrentNodeId && value.getCanShowFlagLine() === false) {
          if (value.getNodeInfoNode().children.length) {
            insertCurrentNodeId = value.getNodeInfoNode().children[0].currentNodeId;
          } else {
            insertCurrentNodeId = this.INITIAL_INVALID_VALUE;
          }
        }
      })
    } else if (!this.expandAndCollapseInfo.get(rearCurrentNodeId) && isHighLight) {
      this.expandAndCollapseInfo.set(rearCurrentNodeId, NodeStatus.Expand);
    }

    this.listNodeUtils.addDragNode(dragNodeParam[0].parentId, dragNodeParam[0].currentId, insertCurrentNodeId,
      isAfter, dragNodeParam[0].data);

    /* Add remaining node. */
    for (let j: number = 1; j < dragNodeParam.length; j++) {
      this.listNodeUtils.addNode(dragNodeParam[j].parentId, dragNodeParam[j].currentId, dragNodeParam[j].data);
    }

    /* Update node data and reload the array named 'listNode'. */
    for (let i: number = 0; i < this.listNode.length; i++) {
      if (this.listNode[i].getCurrentNodeId() === dragParentNodeId) {
        if (this.listNode[i].getNodeInfoNode().getNodeItem().imageCollapse === null) {
          this.listNode[i].handleImageCollapseAfterAddNode(false);
          this.expandAndCollapseInfo.delete(dragParentNodeId);
          break;
        }
      }
    }
    let tmp: NodeInfo[] = [...this.listNode];
    this.reloadListNode(this.listNodeUtils, tmp);

  }

  /**
   * Reload the array named 'listNode'
   * @param listNodeUtils
   * @param tmp
   */
  public reloadListNode(listNodeUtils: ListNodeUtils, tmp: NodeInfo[]) {
    let index: number = 0;
    this.listNode = [];
    this.listNodeUtils = listNodeUtils;
    this.loadedNodeIdAndIndexMap.clear();
    this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
      if (node.currentNodeId >= 0) {
        let nodeInfo: NodeInfo = new NodeInfo(node);
        this.listNode.push(nodeInfo);

        if (this.expandAndCollapseInfo.get(node.currentNodeId) === NodeStatus.Expand) {
          nodeInfo.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Expand);
        } else if (this.expandAndCollapseInfo.get(node.currentNodeId) === NodeStatus.Collapse) {
          nodeInfo.getNodeItem().imageCollapse?.changeImageCollapseSource(NodeStatus.Collapse);
        }

        for (let i: number = 0; i < tmp.length; i++) {
          if (tmp[i].getCurrentNodeId() === nodeInfo.getCurrentNodeId()) {
            nodeInfo.setNodeIsShow(tmp[i].getNodeIsShow());
            nodeInfo.setListItemHeight(tmp[i].getListItemHeight());
            if (nodeInfo.getNodeItem().mainTitleNode && nodeInfo.getIsShowTitle()) {
              nodeInfo.getNodeItem().mainTitleNode.title = tmp[i].getNodeItem().mainTitleNode?.title as string;
            }
            break;
          }
        }
        if (nodeInfo.getNodeIsShow()) {
          this.loadedNodeIdAndIndexMap.set(nodeInfo.getCurrentNodeId(), index++);
        }
      }
      return false;
    });
  }

  public getFlagLine() {
    return this.FLAG_LINE;
  }

  public getVisibility(nodeInfo: NodeInfo): Visibility {
    let lastShowIndex: number = this.loadedNodeIdAndIndexMap.get(nodeInfo.getCurrentNodeId()) as number - 1;
    if (lastShowIndex > this.INITIAL_INVALID_VALUE) {
      let lastNodeInfo: NodeInfo | undefined = this.getData(lastShowIndex);
      return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight() && !lastNodeInfo?.getIsHighLight()) ?
      Visibility.Visible : Visibility.Hidden;
    } else {
      return (nodeInfo.getCanShowFlagLine() === true && !nodeInfo.getIsHighLight()) ?
      Visibility.Visible : Visibility.Hidden;
    }
  }

  public getSubTitlePara() {
    return this.subTitle;
  }

  public getIsFolder(nodeId: number): boolean | undefined {
    if (this.loadedNodeIdAndIndexMap.has(nodeId)) {
      return this.getData(this.loadedNodeIdAndIndexMap.get(nodeId) as number)?.getIsFolder();
    }
    return false;
  }

  public getSubTitleFontColor(isHighLight: boolean) {
    return isHighLight ? this.subTitle.highLightFontColor : this.subTitle.normalFontColor;
  }

  private getChildIndex(rearParentNodeId: number, rearCurrentNodeId: number) {
    let insertChildIndex: number = this.INITIAL_INVALID_VALUE;
    this.listNodeUtils.traverseNodeBF((node): boolean => {
      if (node.getCurrentNodeId() === rearParentNodeId) {
        node.children.forEach((value, index) => {
          if (value.getCurrentNodeId() === rearCurrentNodeId) {
            insertChildIndex = index;
          }
        })
        return true;
      }
      return false;
    });
    return insertChildIndex;
  }

  public setCurrentFocusNodeId(focusNodeId: number) {
    this.currentFocusNodeId = focusNodeId;
  }

  public getCurrentFocusNodeId(): number {
    return this.currentFocusNodeId;
  }

  public setLastFocusNodeId(focusNodeId: number) {
    this.lastFocusNodeId = focusNodeId;
  }

  public getLastFocusNodeId(): number {
    return this.lastFocusNodeId;
  }

  public getAddFocusNodeId(): number {
    return this.addFocusNodeId;
  }

  public setFlag(flag: Flag) {
    this.flag = flag;
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
  @BuilderParam private listTreeViewMenu: () => void;
  private readonly MAX_CN_LENGTH: number = 254;
  private readonly MAX_EN_LENGTH: number = 255;
  private readonly INITIAL_INVALID_VALUE = -1;
  private readonly MAX_TOUCH_DOWN_COUNT = 0;
  private isMultiPress: boolean = false;
  private touchDownCount: number = this.INITIAL_INVALID_VALUE;
  private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
  private readonly itemPadding: itemPadding = {
    left: $r('sys.float.ohos_id_card_margin_start'),
    right: $r('sys.float.ohos_id_card_margin_end'),
    top: $r('sys.float.ohos_id_text_margin_vertical'),
    bottom: '0vp',
  };
  private readonly textInputPadding: itemPadding =
    { left: '0vp', right: '0vp', top: '0vp', bottom: '0vp' }

  aboutToAppear(): void {
    if (this.item.getNodeItem().imageNode) {
      this.item.imageSource = this.item.getNodeItem().imageNode?.source;
    }
  }

  private checkInvalidPattern(title: string): boolean {
    return new RegExp('/[\\\/:*?"<>|]/').test(title);
  }

  private checkIsAllCN(title: string): boolean {
    return new RegExp('/^[\u4e00-\u9fa5]+$/').test(title);
  }

  @Builder
  popupForShowTitle(text: string | Resource | undefined, backgroundColor: Resource, fontColor: Resource) {
    Row() {
      Text(text).fontSize($r('sys.float.ohos_id_text_size_body2')).fontWeight('regular').fontColor(fontColor)
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
              .margin({ left: this.item.getFlagLineLeftMargin() })
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
                }
                .focusable(true)
                .backgroundColor(COLOR_IMAGE_ROW)
                .margin({ right: this.item.getNodeItem().imageNode?.itemRightMargin })
                .height(this.item.getNodeItem().imageNode?.itemHeight)
                .width(this.item.getNodeItem().imageNode?.itemWidth)
              }
              Row() {
                if (this.item.getNodeItem().mainTitleNode && this.item.getIsShowTitle()) {
                  Text(this.item.getNodeItem().mainTitleNode?.title)
                    .maxLines(1)// max line
                    .fontSize(this.item.getNodeItem().mainTitleNode?.size)
                    .fontColor(this.item.fontColor)
                    .margin({ right: this.item.getNodeItem().mainTitleNode?.itemRightMargin })
                    .textOverflow({ overflow: TextOverflow.Ellipsis })
                    .fontWeight(this.item.getNodeItem().mainTitleNode?.weight)
                    .focusable(true)
                }
                if (this.item.getNodeItem().mainTitleNode && this.item.getNodeItem().inputText &&
                this.item.getIsShowInputText()) {
                  Row() {
                    TextInput({ text: this.item.getNodeItem().mainTitleNode?.title })
                      .height(this.item.getNodeItem().inputText?.itemHeight)
                      .fontSize(this.item.getNodeItem().inputText?.size)
                      .fontColor(this.item.getNodeItem().inputText?.color)
                      .borderRadius(this.item.getNodeItem().inputText?.borderRadius)
                      .backgroundColor(this.item.getNodeItem().inputText?.backgroundColor)
                      .enterKeyType(EnterKeyType.Done)
                      .focusable(true)
                      .padding({ left: this.textInputPadding.left, right: this.textInputPadding.right,
                        top: this.textInputPadding.top, bottom: this.textInputPadding.bottom })
                      .onChange((value: string) => {
                        let thisIndex: number = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
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
                        }
                        else {
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
                        }
                        else {
                          isLengthError = false;
                        }
                        if (!isLengthError && !isInvalidError) {
                          this.listNodeDataSource.setMainTitleNameOnEdit(thisIndex, res);
                        }
                      })
                      .onSubmit((enterKey: EnterKeyType) => {
                        let thisIndex: number = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
                        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, thisIndex);
                        this.listNodeDataSource.setItemVisibilityOnEdit(thisIndex, MenuOperation.COMMIT_NODE);
                      })
                  }.backgroundColor(this.item.getNodeItem().inputText?.backgroundColor)
                  .borderRadius(this.item.getNodeItem().inputText?.borderRadius)
                  .margin({ right: this.item.getNodeItem().inputText?.itemRightMargin })
                }
                Blank()
              }
              .layoutWeight(1)
              .focusable(true)

              if (this.listNodeDataSource.hasSubtitle(this.item.getCurrentNodeId())) {
                Row() {
                  Text(this.listNodeDataSource.getSubtitle(this.item.getCurrentNodeId()))
                    .fontSize(this.listNodeDataSource.getSubTitlePara().fontSize)
                    .fontColor(this.listNodeDataSource.getSubTitleFontColor(this.item.getIsHighLight() || this.item.getIsModify()))
                    .fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight)
                }
                .focusable(true)
                .margin({ left: this.listNodeDataSource.getSubTitlePara().margin.left,
                  right: this.item.getNodeItem().imageCollapse ?
                    0 : this.listNodeDataSource.getSubTitlePara().margin.right })
              }

              if (this.item.getNodeItem().imageCollapse) {
                Row() {
                  Image(this.item.getNodeItem().imageCollapse?.collapseSource)
                    .fillColor(this.item.getNodeItem().imageCollapse?.isCollapse ? COLOR_IMAGE_ROW : COLOR_IMAGE_EDIT)
                    .align(Alignment.End)
                    .objectFit(ImageFit.Contain)
                    .height(this.item.getNodeItem().imageCollapse?.itemHeight)
                    .width(this.item.getNodeItem().imageCollapse?.itemWidth)
                    .opacity(!this.item.getIsHighLight() ?
                      this.item.getNodeItem().imageCollapse?.opacity : this.item.getNodeItem().imageCollapse?.noOpacity)
                    .onTouch((event: TouchEvent) => {
                      if (event.type === TouchType.Down) {
                        this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                        this.listNodeDataSource.setCurrentFocusNodeId(this.item.getCurrentNodeId());
                      }
                      event.stopPropagation();
                    })
                    .focusable(true)
                }
                .focusable(true)
                .height(this.item.getNodeItem().imageCollapse?.itemHeight)
                .width(this.item.getNodeItem().imageCollapse?.itemWidth)
              }
            }
            .focusable(true)
            .width('100%')
            .gesture(
              TapGesture({ count: 2 })// doubleClick
                .onAction((event: GestureEvent) => {
                  this.listNodeDataSource.expandAndCollapseNode(
                    findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
                })
            )
            .height(this.item.getNodeHeight())
            .padding({ left: this.item.getNodeLeftPadding() })
            .bindContextMenu(this.builder, ResponseType.RightClick)

          }.focusable(true)
        }
        .opacity(this.listNodeDataSource.getListItemOpacity(this.item))
        .onHover((isHover: boolean) => {
          if (isHover) {
            this.item.setNodeColor($r('sys.color.ohos_id_color_hover'))
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

          this.listNodeDataSource.setClickIndex(this.index);
          let currentId: number = this.item.getNodeCurrentNodeId();

          if (event.type === TouchType.Down) {
            this.item.setNodeColor($r('sys.color.ohos_id_color_click_effect'));
          }

          else if (event.type === TouchType.Up) {
            this.item.setNodeColor(COLOR_SELECT);
            this.item.fontColor = $r('sys.color.ohos_id_color_text_primary_activated');
            if (this.item.getNodeItem().imageNode !== null) {
              this.item.getNodeItem().imageNode?.setImageSource(InteractionStatus.Selected);
              this.listNodeDataSource.setImageSource(this.index, InteractionStatus.Selected);
              this.item.imageSource = this.item.getNodeItem().imageNode?.source;
            }

            this.item.getNodeItem().mainTitleNode?.setMainTitleSelected(true)
            this.lastIndex = this.index;
            let callParam: CallbackParam = { currentNodeId: currentId };
            this.appEventBus.emit(TreeListenType.NODE_CLICK, callParam);
          }

          if (this.listNodeDataSource.getLastIndex() !== -1 && this.index !== this.listNodeDataSource.getLastIndex()) {
            this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, this.listNodeDataSource.getLastIndex());
            this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
          }
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
          let thisIndex: number = findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId());
          if (event.button === MouseButton.Right) {
            this.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
              findCurrentNodeIndex(this.listNodeDataSource, this.item.getNodeCurrentNodeId()));
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
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0 })
        }
      })
    }
  }
}

export class NodeItem {
  private nodeItem: nodeItem;
  private childNodeInfo: childNodeInfo;
  container: () => void;
  nodeLevel: number;
  parentNodeId: number;
  currentNodeId: number;
  children: Array<NodeItem>;
  data: NodeParam;

  constructor(data: NodeParam) {
    this.data = data;
    this.nodeLevel = -1;
    this.parentNodeId = -1;
    this.currentNodeId = -1;
    this.nodeItem = {
      imageNode: undefined,
      inputText: new InputText(),
      mainTitleNode: new MainTitleNode(''),
      imageCollapse: undefined,
      fontColor: undefined,
    };
    this.childNodeInfo = { isHasChildNode: false, childNum: 0, allChildNum: 0 };
    this.container = data.container as () => void;
    if (data.icon) {
      this.nodeItem.imageNode = new ImageNode(
        data.icon,
        $r('sys.float.ohos_id_alpha_content_fourth'),
        IMAGE_NODE_HEIGHT,
        IMAGE_NODE_WIDTH,
        data.selectedIcon,
        data.editIcon,
      );
    }
    if (data.primaryTitle) {
      this.nodeItem.mainTitleNode = new MainTitleNode(data.primaryTitle);
    }
    this.children = [];
  }

  addImageCollapse(isHasChildNode: boolean) {
    if (isHasChildNode) {
      this.nodeItem.imageCollapse = new ImageNode(
        ARROW_RIGHT,
        $r('sys.float.ohos_id_alpha_content_tertiary'),
        IMAGE_NODE_HEIGHT,
        IMAGE_NODE_WIDTH,
        undefined,
        undefined,
      );
      this.nodeItem.imageCollapse.itemRightMargin = ($r('sys.float.ohos_id_text_paragraph_margin_xs'));
    } else {
      this.nodeItem.imageCollapse = undefined;
    }
  }

  getNodeItem() {
    return this.nodeItem;
  }

  getChildNodeInfo() {
    return this.childNodeInfo;
  }

  getMenu(): () => void {
    return this.container;
  }

  getCurrentNodeId() {
    return this.currentNodeId;
  }

  getIsFolder() {
    return this.data.isFolder;
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

  get itemRightMargin() {
    return this.rightMargin;
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
    this.currentInteractionStatus = InteractionStatus.Normal;
  }

  get source() {
    return this.imageSource;
  }

  get normalSource() {
    return this.imageNormalSource;
  }

  get selectedSource() {
    return this.imageSelectedSource;
  }

  get editSource() {
    return this.imageEditSource;
  }

  get opacity() {
    return this.imageOpacity;
  }

  get noOpacity() {
    return 1;
  }

  get collapseSource() {
    return this.imageCollapseSource;
  }

  get isCollapse() {
    return this.isImageCollapse;
  }

  changeImageCollapseSource(nodeStatus: NodeStatus) {
    if (nodeStatus === NodeStatus.Expand) {
      this.imageCollapseSource = this.imageCollapseDownSource;
    } else if (nodeStatus === NodeStatus.Collapse) {
      this.imageCollapseSource = this.imageCollapseRightSource;
    }
  }

  setImageCollapseSource(interactionStatus: InteractionStatus, nodeStatus: NodeStatus | undefined) {
    if (interactionStatus === InteractionStatus.Edit || interactionStatus === InteractionStatus.DragInsert) {
      this.imageCollapseDownSource = ARROW_DOWN_WITHE;
      this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
      this.isImageCollapse = false;
    } else if (interactionStatus === InteractionStatus.FinishEdit ||
      interactionStatus === InteractionStatus.FinishDragInsert) {
      this.imageCollapseDownSource = ARROW_DOWN
      this.imageCollapseRightSource = ARROW_RIGHT
      this.isImageCollapse = true;
    }
    this.imageCollapseSource = (nodeStatus === NodeStatus.Collapse) ?
    this.imageCollapseRightSource : this.imageCollapseDownSource;
  }

  setImageSource(interactionStatus: InteractionStatus) {
    switch (interactionStatus) {
      case InteractionStatus.Normal:
        this.imageSource = this.imageNormalSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.Selected:
        if (this.currentInteractionStatus !== InteractionStatus.Edit) {
          this.imageSource = this.imageSelectedSource;
          this.currentInteractionStatus = interactionStatus;
        }
        break;
      case InteractionStatus.Edit:
        this.imageSource = this.imageEditSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.FinishEdit:
        this.imageSource = this.imageSelectedSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.DragInsert:
        this.imageSource = this.imageEditSource;
        this.currentInteractionStatus = interactionStatus;
        break;
      case InteractionStatus.FinishDragInsert:
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
  mainTitleSetting: textSetting;
  private showPopUpTimeout: number;

  constructor(mainTitleName: ResourceStr) {
    super();
    this.mainTitleName = mainTitleName;
    this.itemWidth = ITEM_WIDTH;
    this.itemHeight = ITEM_HEIGHT;
    this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
    this.mainTitleSetting = {
      fontColor: $r('sys.color.ohos_id_color_primary'),
      fontSize: $r('sys.float.ohos_id_text_size_body1'),
      fontWeight: FontWeight.Normal,
    };
    this.showPopUpTimeout = 0;
  }

  setMainTitleSelected(isSelected: boolean): void {
    if (isSelected) {
      this.mainTitleSetting = {
        fontColor: $r('sys.color.ohos_id_color_text_primary_activated'),
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Regular,
      };
    } else {
      this.mainTitleSetting = {
        fontColor: $r('sys.color.ohos_id_color_primary'),
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

  get popUpTimeout() {
    return this.showPopUpTimeout;
  }

  get color(): Resource {
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
      this.mainTitleSetting = { fontColor: $r('sys.color.ohos_id_color_primary_contrary'),
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Regular };
    } else {
      this.mainTitleSetting = { fontColor: $r('sys.color.ohos_id_color_primary'),
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Normal };
    }
  }
}

export class InputText extends NodeBaseInfo {
  private inputTextSetting: textSetting;
  private status?: status = undefined;
  private statusColor: Resource = $r('sys.color.ohos_id_color_background');
  private editItemColor: Resource = $r('sys.color.ohos_id_color_emphasize');
  private radius: Resource = $r('sys.float.ohos_id_corner_radius_default_xs');

  constructor() {
    super();
    this.itemWidth = ITEM_WIDTH;
    this.itemHeight = ITEM_HEIGHT_INPUT;
    this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
    this.inputTextSetting = {
      fontColor: $r('sys.color.ohos_id_color_text_primary'),
      fontSize: $r('sys.float.ohos_id_text_size_body1'),
      fontWeight: FontWeight.Normal,
    };
  }

  get color(): Resource {
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

  get backgroundColor() {
    return this.statusColor;
  }

  get editColor() {
    return this.editItemColor;
  }

  get textInputStatusColor() {
    return this.status;
  }
}

export class ListNodeUtils {
  private _root: NodeItem;
  public addNewNodeId: number;
  private readonly MaxNodeLevel = 50;
  private readonly MAX_CN_LENGTH: number = 254;
  private readonly MAX_EN_LENGTH: number = 255;
  private readonly INITIAL_INVALID_VALUE = -1;

  constructor() {
    this._root = new NodeItem(emptyNodeInfo);
    this._root.nodeLevel = -1;
    this._root.parentNodeId = -1;
    this._root.currentNodeId = -1;
    this.addNewNodeId = -1;
  }

  getNewNodeId() {
    return this.addNewNodeId;
  }

  traverseNodeDF(callback: (currentNode: NodeItem) => boolean, root: NodeItem = this._root) {
    let stack: Array<NodeItem> = [], found: boolean = false;
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

  traverseNodeBF(callback: (currentNode: NodeItem) => boolean) {
    let queue: Array<NodeItem> = [];
    let found: boolean = false;
    queue.push(this._root);
    let currentNode: NodeItem = queue.shift() as NodeItem;
    while (!found && currentNode) {
      try {
        found = callback(currentNode);
      } catch (err) {
        throw new Error('traverseNodeBF function callbacks error.');
      }
      if (!found) {
        queue.push(...currentNode.children)
        currentNode = queue.shift() as NodeItem;
      }
    }
  }

  private contains(callback: (currentNode: NodeItem) => boolean, traversal: (callback: (currentNode: NodeItem) => boolean) => void) {
    traversal(callback);
  }

  private updateParentChildNum(parentNode: NodeItem, isAdd: boolean, count: number) {
    let parentNodeId: number = parentNode.parentNodeId;
    while (parentNodeId >= 0) {
      this.traverseNodeDF((node: NodeItem): boolean => {
        if (node.currentNodeId === parentNodeId) {
          node.getChildNodeInfo().allChildNum =
            isAdd ? node.getChildNodeInfo().allChildNum + count : node.getChildNodeInfo().allChildNum - count;
          parentNodeId = node.parentNodeId;
          return false;
        }
        return false;
      })
    }
  }

  findParentNodeId(currentNodeId: number): number {
    let current: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem) => {
      if (node.currentNodeId === currentNodeId) {
        current = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    return current.parentNodeId;
  }

  addNode(parentNodeId: number,
          currentNodeId: number,
          data: NodeParam): ListNodeUtils {
    if (this._root === null) {
      this._root = new NodeItem(emptyNodeInfo);
      this._root.nodeLevel = -1;
      this._root.parentNodeId = -1;
      this._root.currentNodeId = -1;
    }

    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem) => {
      if (node.currentNodeId === parentNodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    if (parent) {
      let currentNode: NodeItem = new NodeItem(data as NodeParam);
      if (parent.nodeLevel > this.MaxNodeLevel) {
        throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
      }
      currentNode.nodeLevel = parent.nodeLevel + 1; // nodeLevel
      currentNode.parentNodeId = parentNodeId;
      currentNode.currentNodeId = currentNodeId;
      parent.children.push(currentNode);
      parent.getChildNodeInfo().isHasChildNode = true;
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum += 1; // childNum
      parent.addImageCollapse(parent.getChildNodeInfo().isHasChildNode);
      this.updateParentChildNum(parent, true, 1);
      return this;
    } else {
      throw new Error('ListNodeUtils[addNode]: Parent node not found.');
    }
  }

  findNodeIndex(children: Array<NodeItem>, currentNodeId: number) {
    let index: number = this.INITIAL_INVALID_VALUE;
    for (let i: number = 0, len: number = children.length; i < len; i++) {
      if (children[i].currentNodeId === currentNodeId) {
        index = i;
        break;
      }
    }
    return index;
  }

  private freeNodeMemory(rootNode: NodeItem, removeNodeIdList: number[]) {
    let deleteNode: NodeItem[] = [];
    let callback = (node: NodeItem): boolean => {
      deleteNode.push(node);
      return false;
    };
    this.traverseNodeDF(callback, rootNode);
    deleteNode.forEach((value: NodeItem) => {
      removeNodeIdList.push(value.currentNodeId);
      value = new NodeItem(emptyNodeInfo);
    })
  }

  removeNode(currentNodeId: number, parentNodeId: number) {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === parentNodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);

    if (parent) {
      let removeNodeIdList: number[] = [];
      let index: number = this.findNodeIndex(parent.children, currentNodeId);
      let deleteNodeAllChildNum: number = 0;
      if (index < 0) {
        throw new Error('Node does not exist.');
      } else {
        deleteNodeAllChildNum = parent.children[index].getChildNodeInfo().allChildNum + 1;
        this.freeNodeMemory(parent.children[index], removeNodeIdList);
        let node: NodeItem[] | null = parent.children.splice(index, 1);
        node = null;
        if (parent.children.length === 0) {
          parent.addImageCollapse(false);
        }
      }
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum -= (deleteNodeAllChildNum);
      this.updateParentChildNum(parent, false, deleteNodeAllChildNum);
      return removeNodeIdList;
    } else {
      throw new Error('Parent does not exist.');
    }
  }

  getNewNodeInfo(nodeId: number): NodeParam {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === nodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    let newNodeInfo: NodeParam = emptyNodeInfo;
    if (parent) {
      if (parent.children.length === 0) {
        if (parent.getNodeItem().imageNode !== undefined) {
          newNodeInfo.icon = parent.getNodeItem().imageNode?.normalSource;
          newNodeInfo.selectedIcon = parent.getNodeItem().imageNode?.selectedSource;
          newNodeInfo.editIcon = parent.getNodeItem().imageNode?.editSource;
          newNodeInfo.container = parent.getMenu();
        } else {
          newNodeInfo.icon = undefined;
          newNodeInfo.selectedIcon = undefined;
          newNodeInfo.editIcon = undefined;
          newNodeInfo.container = parent.getMenu();
        }
      } else if (parent.children.length > 0) {
        if (parent.getNodeItem().imageNode !== null) {
          newNodeInfo.icon = (parent.children[0].getNodeItem().imageNode !== undefined) ?
            parent.children[0].getNodeItem().imageNode?.normalSource : undefined;
          newNodeInfo.selectedIcon = (parent.children[0].getNodeItem().imageNode !== undefined) ?
            parent.children[0].getNodeItem().imageNode?.selectedSource : undefined;
          newNodeInfo.editIcon = (parent.children[0].getNodeItem().imageNode !== undefined) ?
            parent.children[0].getNodeItem().imageNode?.editSource : undefined;
          newNodeInfo.container = parent.children[0].getMenu();
        } else {
          newNodeInfo.icon = undefined;
          newNodeInfo.selectedIcon = undefined;
          newNodeInfo.editIcon = undefined;
          newNodeInfo.container = parent.children[0].getMenu();
        }
      }
    }
    return newNodeInfo;
  }

  getClickChildId(nodeId: number) {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === nodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    if (parent) {
      if (parent.children.length === 0) {
        return [];
      } else if (parent.children.length > 0) {
        let nodeInfo: nodeInfo = { itemId: undefined, itemIcon: undefined, itemTitle: undefined }
        let childrenNodeInfo: Array<number> = new Array(parent.children.length);
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

  getClickNodeChildrenInfo(nodeId: number) {
    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === nodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    if (parent) {
      if (parent.children.length === 0) {
        return [];
      } else if (parent.children.length > 0) {
        let childrenNodeInfo: Array<nodeInfo> = new Array(parent.children.length);
        for (let i: number = 0; i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i] = {};
        }
        for (let i: number = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
          childrenNodeInfo[i].itemId = parent.children[i].currentNodeId;
          if (parent.children[i].getNodeItem().imageNode) {
            childrenNodeInfo[i].itemIcon = parent.children[i].getNodeItem().imageNode?.source;
          }
          if (parent.children[i].getNodeItem().mainTitleNode) {
            childrenNodeInfo[i].itemTitle = parent.children[i].getNodeItem().mainTitleNode?.title;
          }
          childrenNodeInfo[i].isFolder = parent.children[i].getIsFolder();
        }
        return childrenNodeInfo;
      }
    }
    return [];
  }

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
   * @param callback
   */
  dragTraverseNodeDF(callback: (node: NodeItem, listNode: NodeInfo[]) => boolean,
                     root: NodeItem = this._root, listNode: NodeInfo[]) {
    let stack: Array<NodeItem> = [], found: boolean = false;
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

  /**
   * Add the first dragging node in dragging nodes
   * 1.the first dragging node needs to distinguish the position to insert
   */
  addDragNode(parentNodeId: number,
              currentNodeId: number,
              insertCurrentNodeId: number,
              isAfter: boolean,
              data: NodeParam): ListNodeUtils {

    if (this._root === null) {
      this._root = new NodeItem(emptyNodeInfo);
      this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
      this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
      this._root.currentNodeId = this.INITIAL_INVALID_VALUE;
    }

    let parent: NodeItem = new NodeItem(emptyNodeInfo);
    let callback: (node: NodeItem) => boolean = (node: NodeItem): boolean => {
      if (node.currentNodeId === parentNodeId) {
        parent = node;
        return true;
      }
      return false;
    };
    this.traverseNodeBF(callback);
    if (parent) {
      let currentNode: NodeItem = new NodeItem(data);
      if (parent.nodeLevel > this.MaxNodeLevel) {
        throw new Error('ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.');
      }
      currentNode.nodeLevel = parent.nodeLevel + 1;
      currentNode.parentNodeId = parentNodeId;
      currentNode.currentNodeId = currentNodeId;
      let insertIndex: number = this.INITIAL_INVALID_VALUE;
      if (parent.children.length) {
        for (let i: number = 0; i < parent.children.length; i++) {
          if (parent.children[i].getCurrentNodeId() === insertCurrentNodeId) {
            insertIndex = i;
            break;
          }
        }
        if (isAfter) {
          parent.children.splice(insertIndex + 1, 0, currentNode);
        } else {
          parent.children.splice(insertIndex, 0, currentNode);
        }
      } else {
        parent.children.push(currentNode);
      }
      parent.getChildNodeInfo().isHasChildNode = true;
      parent.getChildNodeInfo().childNum = parent.children.length;
      parent.getChildNodeInfo().allChildNum += 1;
      parent.addImageCollapse(parent.getChildNodeInfo().isHasChildNode);
      this.updateParentChildNum(parent, true, 1);
      return this;
    } else {
      throw new Error('ListNodeUtils[addNode]: Parent node not found.');
    }
  }
}