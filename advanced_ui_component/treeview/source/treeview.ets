/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

export namespace TreeView {
  const IMAGE_NODE_HEIGHT: number = 24
  const IMAGE_NODE_WIDTH: number = 24
  const ITEM_WIDTH: number = 0
  const ITEM_HEIGHT: number = 44
  const ITEM_HEIGHT_INPUT: number = 32
  const BORDER_WIDTH_HAS: number = 2
  const BORDER_WIDTH_NONE: number = 0
  const NODE_HEIGHT: number = 44
  const LIST_ITEM_HEIGHT_NONE: number = 0
  const LIST_ITEM_HEIGHT: number = 48
  const SHADOW_OFFSETY: number = 10
  const FLAG_NUMBER: number = 2
  const DRAG_OPACITY: number = 0.4
  const DRAG_OPACITY_NONE: number = 1
  const FLAG_LINE_HEIGHT: string = '1.5vp'
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

  export class TreeListener {
    _events = []

    constructor() {
    }

    /*
   * Event registration and processing.
   *
   * The event will not be destroyed after being processed.
   *
   * @param type Registered Events.
   * @param callback Event callback.
   * @since 10
   */
    public on(type: TreeListenType, callback: (callbackParam: CallbackParam) => void) {
      if (Array.isArray(type)) {
        for (let i = 0, l = type.length; i < l; i++) {
          this.on(type[i], callback)
        }
      } else {
        (this._events[type] || (this._events[type] = [])).push(callback)
      }
    }

    /*
   * Event registration and processing.
   *
   * After the event is processed once, it will be destroyed.
   *
   * @param type Registered Events.
   * @param callback Event callback.
   * @since 10
   */
    public once(type: TreeListenType, callback: (callbackParam: CallbackParam) => void) {
      let _self = this;
      function handler() {
        _self.off(type, handler);
        callback.apply(null, [type, callback]);
      }

      handler.callback = callback;
      this.on(type, handler);
    }

    /*
   * Destroy event.
   *
   * @param type Registered Events.
   * @param callback Event callback.
   * @since 10
   */
    public off(type: TreeListenType, callback: (callbackParam: CallbackParam) => void) {
      if (type == null) {
        this._events = [];
      }
      if (Array.isArray(type)) {
        for (let i = 0, l = type.length; i < l; i++) {
          this.off(type[i], callback)
        }
      }
      const cbs = this._events[type];
      if (!cbs) {
        return;
      }
      if (callback == null) {
        this._events[type] = null
      }
      let cb, i = cbs.length
      while (i--) {
        cb = cbs[i]
        if (cb === callback || cb.callback === callback) {
          cbs.splice(i, 1)
          break
        }
      }
    }

    /*
   * Triggers all callbacks of an event with parameters.
   *
   * @param event Registered Events.
   * @param argument Parameters returned by the callback event.
   * @since 10
   */
    public emit(event, argument: any[]) {
      let _self = this
      if (!this._events[event]) {
        return
      }
      let cbs = [...this._events[event]];
      if (cbs) {
        for (let i = 0, l = cbs.length; i < l; i++) {
          try {
            cbs[i].apply(_self,argument)
          } catch (e) {
            new Error(e)
          }
        }
      }
    }
  }

  /*
 * TreeListenType listen type.
 *
 * @since 10
 */
  export enum TreeListenType {
    NODE_ADD = "NodeAdd",
    NODE_DELETE = "NodeDelete",
    NODE_MODIFY = "NodeModify",
    NODE_MOVE = "NodeMove",
    NODE_CLICK = 'NodeClick',
  }

  /*
 * TreeListenerManager.
 *
 * @since 10
 */
  export class TreeListenerManager {
    static readonly APP_KEY_EVENT_BUS = "app_key_event_bus";
    private appEventBus: TreeListener;
    private constructor() {
      this.appEventBus = new TreeListener();
    }

    /*
   * Obtains the EventBusManager object.
   *
   * @since 10
   */
    public static getInstance(): TreeListenerManager {
      if (AppStorage.Get(this.APP_KEY_EVENT_BUS) == null) {
        AppStorage.SetOrCreate(this.APP_KEY_EVENT_BUS, new TreeListenerManager())
      }
      return AppStorage.Get(this.APP_KEY_EVENT_BUS);
    }

    /*
   * Obtains the EventBus object.
   *
   * @since 10
   */
    public getTreeListener(): TreeListener {
      return this.appEventBus;
    }
  }

  class BasicDataSource implements IDataSource {
    private listeners: DataChangeListener[] = []

    public totalCount(): number {
      return 0
    }
    public getData(index: number): any {
      return undefined
    }

    registerDataChangeListener(listener: DataChangeListener): void {
      if (this.listeners.indexOf(listener) < 0) {
        this.listeners.push(listener)
      }
    }
    unregisterDataChangeListener(listener: DataChangeListener): void {
      const pos = this.listeners.indexOf(listener);
      if (pos >= 0) {
        this.listeners.splice(pos, 1)
      }
    }

    notifyDataReload(): void {
      this.listeners.forEach(listener => {
        listener.onDataReloaded()
      })
    }
    notifyDataAdd(index: number): void {
      this.listeners.forEach(listener => {
        listener.onDataAdd(index)
      })
    }
    notifyDataChange(index: number): void {
      this.listeners.forEach(listener => {
        listener.onDataChange(index)
      })
    }
    notifyDataDelete(index: number): void {
      this.listeners.forEach(listener => {
        listener.onDataDelete(index)
      })
    }
    notifyDataMove(from: number, to: number): void {
      this.listeners.forEach(listener => {
        listener.onDataMove(from, to)
      })
    }
  }

  export enum Event {
    TOUCH_DOWN = 0,
    TOUCH_UP = 1,
    HOVER = 3,
    HOVER_OVER = 4,
    FOCUS = 5,
    BLUR = 6,
    MOUSE_BUTTON_RIGHT = 7,
    DRAG = 8
  }

  export enum MenuOperation {
    ADD_NODE = 0,
    REMOVE_NODE = 1,
    MODIFY_NODE = 2,
    COMMIT_NODE = 3
  }

  export enum PopUpType {
    HINTS = 0,
    WARNINGS = 1
  }

  export enum InputError {
    INVALID_ERROR = 0,
    LENGTH_ERROR = 1,
    NONE = 2
  }

  export enum Flag {
    DOWN_FLAG = 0,
    UP_FLAG = 1,
    NONE = 2
  }

  export class NodeItem {
    private nodeItem: { imageNode?: ImageNode,
    mainTitleNode?: MainTitleNode,
    imageCollapse?: ImageNode};
    private childNodeInfo: { isHasChildNode: boolean, childNum: number, allChildNum: number };
    menu: () => void;
    nodeLevel: number;
    parentNodeId: number;
    currentNodeId: number;
    children: Array<NodeItem>;
    data: { isFolder?: boolean,
    icon?: Resource,
    selectedIcon?: Resource,
    editIcon?: Resource,
    primaryTitle?: string,
    menu?: () => void,
    objectCount?: number | string }

    constructor(data: { isFolder?: boolean,
    icon?: Resource,
    selectedIcon?: Resource,
    editIcon?: Resource,
    primaryTitle?: string,
    menu?: () => void,
    objectCount?: number | string }) {
      this.data = data;
      this.nodeLevel = -1;
      this.parentNodeId = -1;
      this.nodeItem = { imageNode: null, mainTitleNode: null, imageCollapse: null };
      this.childNodeInfo = { isHasChildNode: false, childNum: 0, allChildNum: 0 };
      this.menu = data.menu;
      if (data.icon) {
        this.nodeItem.imageNode = new ImageNode(data.icon, data.selectedIcon, data.editIcon,
          $r('sys.float.ohos_id_alpha_content_fourth'),
          IMAGE_NODE_HEIGHT,
          IMAGE_NODE_WIDTH);
      }
      if (data.primaryTitle) {
        this.nodeItem.mainTitleNode = new MainTitleNode(data.primaryTitle);
      }
      this.children = [];
    }

    addImageCollapse(isHasChildNode: boolean) {
      if (isHasChildNode) {
        this.nodeItem.imageCollapse = new ImageNode($r('sys.media.ohos_ic_public_arrow_right'), null, null,
          $r('sys.float.ohos_id_alpha_content_tertiary'),
          IMAGE_NODE_HEIGHT,
          IMAGE_NODE_WIDTH);
        this.nodeItem.imageCollapse.itemRightMargin = ($r('sys.float.ohos_id_text_paragraph_margin_xs'));
      } else {
        this.nodeItem.imageCollapse = null;
      }
    }

    getNodeItem() {
      return this.nodeItem;
    }

    getChildNodeInfo() {
      return this.childNodeInfo;
    }

    getMenu(): () => void {
      return this.menu;
    }

    getCurrentNodeId() {
      return this.currentNodeId;
    }

    getIsFolder() {
      return this.data.isFolder;
    }
  }

  class NodeBaseInfo {
    public rightMargin: Resource | number;
    private width: number;
    private height: number;
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

  export enum NodeStatus {
    Expand = 0,
    Collapse
  }

  export enum InteractionStatus {
    Normal = 0,
    Selected,
    Edit,
    FinishEdit,
    DragInsert,
    FinishDragInsert
  }

  export class ImageNode extends NodeBaseInfo {
    private imageSource: Resource;
    private imageNormalSource: Resource;
    private imageSelectedSource: Resource;
    private imageEditSource: Resource;
    private imageOpacity: Resource;
    private currentInteractionStatus: InteractionStatus;
    private imageCollapseSource: Resource;
    private imageCollapseDownSource: Resource;
    private isImageCollapse: boolean;
    private imageCollapseRightSource: Resource;
    constructor(imageSource: Resource, itemSelectedIcon: Resource, itemEditIcon: Resource,
                imageOpacity: Resource, itemWidth: number, itemHeight: number) {
      super();
      this.rightMargin = $r('sys.float.ohos_id_elements_margin_horizontal_m');
      this.imageSource = imageSource;
      this.imageNormalSource = imageSource;
      if (itemSelectedIcon != null) {
        this.imageSelectedSource = itemSelectedIcon;
      } else {
        this.imageSelectedSource = this.imageNormalSource;
      }
      if (itemEditIcon != null) {
        this.imageEditSource = itemEditIcon;
      } else {
        this.imageEditSource = this.imageNormalSource;
      }
      this.imageOpacity = imageOpacity;
      this.itemWidth = itemWidth;
      this.itemHeight = itemHeight;
      this.imageCollapseSource = imageSource;
      this.imageCollapseDownSource = $r('sys.media.ohos_ic_public_arrow_down');
      this.imageCollapseRightSource = $r('sys.media.ohos_ic_public_arrow_right');
      this.isImageCollapse = true;
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
      if (nodeStatus == NodeStatus.Expand) {
        this.imageCollapseSource = this.imageCollapseDownSource;
      } else if (nodeStatus == NodeStatus.Collapse) {
        this.imageCollapseSource = this.imageCollapseRightSource;
      }
    }

    setImageCollapseSource(interactionStatus: InteractionStatus, nodeStatus: NodeStatus) {
      if (interactionStatus === InteractionStatus.Edit || interactionStatus === InteractionStatus.DragInsert) {
        this.imageCollapseDownSource = $r('sys.media.ohos_ic_public_arrow_down');
        this.imageCollapseRightSource = $r('sys.media.ohos_ic_public_arrow_right');
        this.isImageCollapse = false;
      } else if (interactionStatus === InteractionStatus.FinishEdit ||
        interactionStatus === InteractionStatus.FinishDragInsert) {
        this.imageCollapseDownSource = $r('sys.media.ohos_ic_public_arrow_down');
        this.imageCollapseRightSource = $r('sys.media.ohos_ic_public_arrow_right');
        this.isImageCollapse = true;
      }
      this.imageCollapseSource = (nodeStatus == NodeStatus.Collapse) ?
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

  export class MainTitleNode extends NodeBaseInfo {
    private mainTitleName: string;
    private mainTitleSetting: { fontColor: Resource, fontSize: Resource, fontWeight: FontWeight }
    private showPopUpTimeout: number;
    constructor(mainTitleName: string) {
      super();
      this.mainTitleName = mainTitleName;
      this.itemWidth = ITEM_WIDTH;
      this.itemHeight = ITEM_HEIGHT;
      this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
      this.mainTitleSetting = { fontColor: $r('sys.color.ohos_id_color_primary'),
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Normal };
      this.showPopUpTimeout = 0;
    }
    setMainTitleSelected(isSelected: boolean): void {
      if (isSelected) {
        this.mainTitleSetting = { fontColor: $r('sys.color.ohos_id_color_text_primary_activated'),
          fontSize: $r('sys.float.ohos_id_text_size_body1'),
          fontWeight: FontWeight.Regular };
      } else {
        this.mainTitleSetting = { fontColor: $r('sys.color.ohos_id_color_primary'),
          fontSize: $r('sys.float.ohos_id_text_size_body1'),
          fontWeight: FontWeight.Normal };
      }
    }
    set title(text: string) {
      this.mainTitleName = text;
    }
    get title(): string {
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
    private inputTextSetting: { fontColor: Resource, fontSize: Resource, fontWeight: FontWeight }
    private status: { normal: Resource, hover: Resource, press: Resource };
    private statusColor: Resource = $r('sys.color.ohos_id_color_background');
    private editItemColor: Resource = $r('sys.color.ohos_id_color_emphasize');
    private radius: Resource = $r('sys.float.ohos_id_corner_radius_default_xs')
    constructor() {
      super();
      this.itemWidth = ITEM_WIDTH;
      this.itemHeight = ITEM_HEIGHT_INPUT;
      this.rightMargin = $r('sys.float.ohos_id_text_paragraph_margin_xs');
      this.inputTextSetting = {
        fontColor: $r('sys.color.ohos_id_color_text_primary'),
        fontSize: $r('sys.float.ohos_id_text_size_body1'),
        fontWeight: FontWeight.Normal };
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

  export class NodeInfo {
    private childNodeInfo: { isHasChildNode: boolean, childNum: number, allChildNum: number };
    private parentNodeId: number;
    private currentNodeId: number;
    private nodeHeight: Resource | number;
    private nodeLevel: number;
    private nodeItem: { imageNode?: ImageNode,
    inputText: InputText,
    mainTitleNode?: MainTitleNode,
    imageCollapse?: ImageNode };
    private nodeLeftPadding: number;
    private nodeColor: Resource | string;
    private nodeIsShow: boolean;
    private status: { normal: Resource, hover: Resource, press: Resource, selected: string, highLight: Resource };
    private nodeBorder: { borderWidth: Resource | number, borderColor: Resource, borderRadius: Resource };
    private popUpInfo: { popUpIsShow: boolean,
    popUpEnableArrow: boolean,
    popUpColor: Resource,
    popUpText: string | Resource,
    popUpTextColor: Resource};
    private listItemHeight: number;
    private menu: () => void;
    private isShowTitle: boolean;
    private isShowInputText: boolean;
    private isSelected: boolean;
    readonly borderWidth: {has: Resource | number, none: Resource | number } =
      {has: BORDER_WIDTH_HAS/* 2vp */, none: BORDER_WIDTH_NONE/* 0vp */}

    /* parameter of the drag event.*/
    private nodeParam: {
      isFolder?: boolean,
      icon?: Resource,
      selectedIcon?: Resource,
      editIcon?: Resource,
      primaryTitle?: string,
      menu?: () => void,
      secondaryTitle?: number | string
    };
    private node: NodeItem;
    private canShowFlagLine: boolean = false;
    private isOverBorder: boolean = false;
    private canShowBottomFlagLine: boolean = false;
    private isHighLight: boolean = false;
    private flagLineLeftMargin: number;
    private isModify: boolean = false;

    constructor(node: NodeItem) {
      this.childNodeInfo = node.getChildNodeInfo();
      this.nodeItem = { imageNode: null, inputText: null, mainTitleNode: null, imageCollapse: null };
      this.popUpInfo = { popUpIsShow: false,
        popUpEnableArrow: false,
        popUpColor: null,
        popUpText: '',
        popUpTextColor: null };
      this.nodeItem.imageNode = node.getNodeItem().imageNode;
      this.nodeItem.inputText = new InputText();
      this.nodeItem.mainTitleNode = node.getNodeItem().mainTitleNode;
      this.nodeItem.imageCollapse = node.getNodeItem().imageCollapse;
      this.menu = node.menu;
      this.parentNodeId = node.parentNodeId;
      this.currentNodeId = node.currentNodeId;
      this.nodeHeight = NODE_HEIGHT;
      this.nodeLevel = node.nodeLevel;
      this.nodeLeftPadding = node.nodeLevel * 12 + 8; // calculate left padding
      this.nodeColor = $r('sys.color.ohos_id_color_background');
      this.nodeIsShow = (this.nodeLevel > 0) ? false : true;
      this.listItemHeight =  (this.nodeLevel > 0) ? LIST_ITEM_HEIGHT_NONE : LIST_ITEM_HEIGHT;
      this.isShowTitle = true;
      this.isShowInputText = false;
      this.isSelected = false;
      this.status = { normal: $r('sys.color.ohos_id_color_background_transparent'),
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

    setPopUpText(text: string | Resource) {
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
        this.nodeItem.imageCollapse = new ImageNode($r('sys.media.ohos_ic_public_arrow_down'), null, null,
          $r('sys.float.ohos_id_alpha_content_tertiary'),
          IMAGE_NODE_HEIGHT,
          IMAGE_NODE_WIDTH);
        this.nodeItem.imageCollapse.itemRightMargin = ($r('sys.float.ohos_id_text_paragraph_margin_xs'));
      } else {
        this.nodeItem.imageCollapse = null;
      }
    }

    setNodeColor(nodeColor: Resource | string): void {
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

    getNodeItem()  {
      return this.nodeItem;
    }

    getNodeStatus() {
      return this.status;
    }

    getNodeBorder() {
      return this.nodeBorder;
    }

    setNodeBorder(isClearFocusStatus: boolean): void {
      this.nodeBorder.borderWidth = isClearFocusStatus ?  this.borderWidth.has : this.borderWidth.none;
    }

    getChildNodeInfo() {
      return this.childNodeInfo;
    }

    getCurrentNodeId() {
      return this.currentNodeId;
    }

    getMenu() {
      return this.menu;
    }

    setIsSelected(isSelected: boolean) {
      this.isSelected = isSelected;
    }

    getIsSelected() {
      return this.isSelected;
    }

    /* To gain the information while to alter node. */
    getNodeInfoData() {
      return this.nodeParam;
    }

    /* To gain the tree Node(NodeItem) while to alter node. */
    public getNodeInfoNode() {
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

    public setFlagLineLeftMargin(currentNodeLevel: number) {
      this.flagLineLeftMargin = currentNodeLevel * 12 + 8;  // calculate
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


  export class ListNodeUtils {
    private _root: NodeItem;
    public addNewNodeId: number;
    private readonly MaxNodeLevel = 50;
    private readonly MAX_CN_LENGTH: number = 254;
    private readonly MAX_EN_LENGTH: number = 255;
    private readonly INITIAL_INVALID_VALUE = -1;
    constructor() {
      this._root = new NodeItem({});
      this._root.nodeLevel = -1;
      this._root.parentNodeId = -1;
      this._root.currentNodeId = -1;
    }

    getNewNodeId() {
      return this.addNewNodeId;
    }

    traverseNodeDF(callback, root: NodeItem = this._root) {
      let stack = [], found = false;
      stack.unshift(root);
      let currentNode = stack.shift();
      while(!found && currentNode) {
        found = callback(currentNode) === true;
        if (!found) {
          stack.unshift(...currentNode.children);
          currentNode = stack.shift();
        }
      }
    }

    traverseNodeBF(callback) {
      let queue = [];
      let found: boolean = false;
      queue.push(this._root);
      let currentNode: NodeItem = queue.shift();
      while(!found && currentNode) {
        try {
          found = callback(currentNode);
        } catch(err) {
          var e = err.name + " == " + err.message;
        }
        if (!found) {
          queue.push(...currentNode.children)
          currentNode = queue.shift();
        }
      }
    }

    private contains(callback, traversal) {
      traversal.call(this, callback, true);
    }

    private updateParentChildNum(parentNode: NodeItem, isAdd: boolean, count: number) {
      let parentNodeId: number = parentNode.parentNodeId;
      while(parentNodeId >= 0) {
        this.traverseNodeDF((node: NodeItem): boolean => {
          if (node.currentNodeId == parentNodeId) {
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
      let current = null,
        callback = function(node): boolean {
          if (node.currentNodeId == currentNodeId ) {
            current = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
      return current.parentNodeId;
    }

    addNode(parentNodeId: number,
            currentNodeId: number,
            data: { isFolder?: boolean,
            icon?: Resource,
            selectedIcon?: Resource,
            editIcon?: Resource,
            primaryTitle?: string,
            secondaryTitle?: number | string,
            menu?: () => void,
            }): ListNodeUtils {
      if (this._root === null) {
        this._root = new NodeItem({});
        this._root.nodeLevel = -1;
        this._root.parentNodeId = -1;
        this._root.currentNodeId = -1;
      }

      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == parentNodeId ) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
      if (parent) {
        let currentNode: NodeItem = new NodeItem(data);
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

    findNodeIndex(children, currentNodeId: number) {
      let index = this.INITIAL_INVALID_VALUE;
      for (let i = 0, len = children.length; i < len; i++) {
        if (children[i].currentNodeId === currentNodeId) {
          index = i;
          break;
        }
      }
      return index;
    }

    private freeNodeMemory(rootNode: NodeItem, removeNodeIdList: number[]) {
      let deleteNode: NodeItem[] = [];
      let callback = function(node): boolean {
        deleteNode.push(node);
        return false;
      };
      this.traverseNodeDF(callback, rootNode);
      deleteNode.forEach((value)=>{
        removeNodeIdList.push(value.currentNodeId);
        value = null;
      })
    }

    removeNode(currentNodeId: number, parentNodeId: number, traversal: any) {
      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == parentNodeId) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, traversal);

      if (parent) {
        let removeNodeIdList: number[] = [];
        let index = this.findNodeIndex(parent.children, currentNodeId);
        if (index < 0) {
          throw new Error('Node does not exist.');
        } else {
          var deleteNodeAllChildNum = parent.children[index].getChildNodeInfo().allChildNum + 1;
          this.freeNodeMemory(parent.children[index], removeNodeIdList);
          let node = parent.children.splice(index, 1);
          node = null;
          if (parent.children.length == 0) {
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

    getNewNodeInfo(nodeId: number) {
      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == nodeId) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
      let newNodeInfo: { isFolder: boolean, icon: Resource, selectedIcon: Resource, editIcon: Resource, menu: () => any, secondaryTitle: number | string } =
        { isFolder: true, icon: null, selectedIcon: null, editIcon: null, menu: null, secondaryTitle: '' };
      if (parent) {
        if (parent.children.length === 0) {
          if (parent.getNodeItem().imageNode != null) {
            newNodeInfo.icon = parent.getNodeItem().imageNode.normalSource;
            newNodeInfo.selectedIcon = parent.getNodeItem().imageNode.selectedSource;
            newNodeInfo.editIcon = parent.getNodeItem().imageNode.editSource;
            newNodeInfo.menu = parent.getMenu();
          } else {
            newNodeInfo.icon = null;
            newNodeInfo.selectedIcon = null;
            newNodeInfo.editIcon = null;
            newNodeInfo.menu = parent.getMenu();
          }
        } else if (parent.children.length > 0) {
          if (parent.getNodeItem().imageNode != null) {
            newNodeInfo.icon = (parent.children[0].getNodeItem().imageNode != null) ?
            parent.children[0].getNodeItem().imageNode.normalSource : null;
            newNodeInfo.selectedIcon = (parent.children[0].getNodeItem().imageNode != null) ?
            parent.children[0].getNodeItem().imageNode.selectedSource : null;
            newNodeInfo.editIcon = (parent.children[0].getNodeItem().imageNode != null) ?
            parent.children[0].getNodeItem().imageNode.editSource : null;
            newNodeInfo.menu = parent.children[0].getMenu();
          } else {
            newNodeInfo.icon = null;
            newNodeInfo.selectedIcon = null;
            newNodeInfo.editIcon = null;
            newNodeInfo.menu = parent.children[0].getMenu();
          }
        }
      }
      return newNodeInfo;
    }

    getClickChildId(nodeId: number) {
      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == nodeId) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
      if (parent) {
        if (parent.children.length === 0) {
          return [];
        } else if (parent.children.length > 0) {
          var nodeInfo: { itemId: number, itemIcon: Resource, itemTitle: string } =
            { itemId: null, itemIcon: null, itemTitle: null }
          var childrenNodeInfo: Array<number> = new Array(parent.children.length);
          for (let i = 0; i < childrenNodeInfo.length; i++) {
            childrenNodeInfo[i] = 0;
          }
          for (let i = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
            childrenNodeInfo[i] = parent.children[i].currentNodeId;
          }
          return childrenNodeInfo;
        }
      }
      return [];
    }

    getClickNodeChildrenInfo(nodeId: number) {
      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == nodeId) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
      if (parent) {
        if (parent.children.length === 0) {
          return [];
        } else if (parent.children.length > 0) {
          var nodeInfo: { itemId: number, itemIcon: Resource, itemTitle: string } =
            { itemId: null, itemIcon: null, itemTitle: null }
          var childrenNodeInfo: Array<{ itemId: number, itemIcon: Resource, itemTitle: string, isFolder: boolean }> = new Array(parent.children.length);
          for (let i = 0; i < childrenNodeInfo.length; i++) {
            childrenNodeInfo[i] = { itemId: null, itemIcon: null, itemTitle: null, isFolder: null };
          }
          for (let i = 0; i < parent.children.length && i < childrenNodeInfo.length; i++) {
            childrenNodeInfo[i].itemId = parent.children[i].currentNodeId;
            if (parent.children[i].getNodeItem().imageNode) {
              childrenNodeInfo[i].itemIcon = parent.children[i].getNodeItem().imageNode.source;
            }
            if (parent.children[i].getNodeItem().mainTitleNode) {
              childrenNodeInfo[i].itemTitle = parent.children[i].getNodeItem().mainTitleNode.title;
            }
            childrenNodeInfo[i].isFolder =  parent.children[i].getIsFolder();
          }
          return childrenNodeInfo;
        }
      }
      return [];
    }

    public checkMainTitleIsValid(title: string) : boolean {
      let invalid = /[\\\/:*?"<>|]/;
      let invalidLength = /^[\u4e00-\u9fa5]+$/;
      if (invalid.test(title)) {
        return false;
      }
      if ((invalidLength.test(title) && title.length > this.MAX_CN_LENGTH) ||
        (!invalidLength.test(title) && title.length > this.MAX_EN_LENGTH)) {
        return false;
      }
      return true;
    }

    /*
   * DFS: Depth first traversal in drag event.
   * @param callback
   */
    dragTraverseNodeDF(callback, root: NodeItem = this._root, listNode) {
      let stack = [], found = false;
      stack.unshift(root);
      let currentNode = stack.shift();
      while(!found && currentNode) {
        found = callback(currentNode, listNode) === true;
        if (!found) {
          stack.unshift(...currentNode.children);
          currentNode = stack.shift();
        }
      }
    }

    /*
   * Add the first dragging node in dragging nodes
   * 1.the first dragging node needs to distinguish the position to insert
   */
    addDragNode(parentNodeId: number,
                currentNodeId: number,
                insertCurrentNodeId: number,
                isAfter: boolean,
                data: { isFolder?: boolean,
                icon?: Resource,
                selectedIcon?: Resource,
                editIcon?: Resource,
                primaryTitle?: string,
                menu?: () => any,
                objectCount?: number }): ListNodeUtils {

      if (this._root === null) {
        this._root = new NodeItem({});
        this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
        this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
        this._root.currentNodeId = this.INITIAL_INVALID_VALUE;
      }

      let parent = null,
        callback = function(node): boolean {
          if (node.currentNodeId == parentNodeId ) {
            parent = node;
            return true;
          }
          return false;
        };
      this.contains(callback, this.traverseNodeBF);
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
          for (let i = 0; i < parent.children.length; i++) {
            if ( parent.children[i].getCurrentNodeId() == insertCurrentNodeId) {
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


  export class ListNodeDataSource extends BasicDataSource {
    readonly ROOT_NODE_ID = -1;
    private listNodeUtils: ListNodeUtils = new ListNodeUtils();
    private listNode: NodeInfo[] = [];
    private readonly INITIAL_INVALID_VALUE = -1;
    private lastIndex: number = -1; // record the last focused node.
    thisIndex: number = -1; // records clicked nodes in the current period.
    private modifyNodeIndex: number = -1; // records the nodes edited in the current period.
    modifyNodeId: number = -1
    private currentOperation: MenuOperation;
    private expandAndCollapseInfo = new Map();
    private loadedNodeIdAndIndexMap = new Map(); // [currentNodeId, index]
    private isTouchDown: boolean = false;
    private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();

    /* parameter of the drag event. */
    private isInnerDrag: boolean = false; // Judge whether it is an internal drag event.
    private isDrag: boolean = false; // It is used to handle events(For example, prevent press events) during global drag.
    private draggingCurrentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the current ID of the dragged node.
    private draggingParentNodeId: number = this.INITIAL_INVALID_VALUE; // Record the parent ID of the dragged node.
    private currentNodeInfo: NodeInfo = null; // To solve the problem of currentIndex missed in onDrop event.
    private listItemOpacity : number = 1; // It is used to set the opacity of the node when dragged.
    private lastPassIndex: number = this.INITIAL_INVALID_VALUE; // record the last passing node index in drag.
    private lastPassId: number = this.INITIAL_INVALID_VALUE; // record the last passing node Id in drag.
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
    private nodeIdAndSubtitleMap = new Map(); // [currentNodeId, subtitle]
    private flag: Flag = Flag.NONE;
    private selectedParentNodeId: number = this.INITIAL_INVALID_VALUE;
    private selectedParentNodeSubtitle: any = '';
    private insertNodeSubtitle: any = '';
    private currentFocusNodeId: number = this.INITIAL_INVALID_VALUE;
    private lastFocusNodeId: number = this.INITIAL_INVALID_VALUE;
    private addFocusNodeId: number = this.INITIAL_INVALID_VALUE;

    readonly FLAG_LINE: { flagLineHeight: string,
    flagLineColor: Resource,
    xOffset: string,
    yTopOffset: string,
    yBottomOffset: string,
    yBasePlateOffset: string } = {
      flagLineHeight: FLAG_LINE_HEIGHT,
      flagLineColor: $r('sys.color.ohos_id_color_activated'),
      xOffset: X_OFF_SET,
      yTopOffset: Y_OFF_SET,
      yBottomOffset: Y_BOTTOM_OFF_SET,
      yBasePlateOffset: Y_BASE_PLATE_OFF_SET
    }

    private readonly DRAG_POPUP: { floorConstraintSize: { minWidth: string, maxWidth: string },
    textConstraintSize: { minWidth1: string, maxWidth1: string,
    minWidth2: string, maxWidth2: string },
    padding: { left: string, right: string },
    backgroundColor: ResourceColor,
    height: string,
    shadow: { radius: Resource, color: ResourceColor, offsetX?: number, offsetY?: number },
    borderRadius : Resource,
    fontColor: Resource,
    fontSize: Resource,
    fontWeight: FontWeight
    imageOpacity: Resource } = {
      floorConstraintSize: { minWidth: FLOOR_MIN_WIDTH, maxWidth: FLOOR_MAX_WIDTH },
      textConstraintSize: { minWidth1: TEXT_MIN_WIDTH, maxWidth1: TEXT_MAX_WIDTH, minWidth2: MIN_WIDTH, maxWidth2: MAX_WIDTH },
      padding: { left: LEFT_PADDING, right: RIGHT_PADDING },
      backgroundColor: COLOR_IMAGE_EDIT,
      height: GRAG_POP_UP_HEIGHT,
      shadow: { radius: $r('sys.float.ohos_id_corner_radius_default_m'), color: SHADOW_COLOR, offsetX: 0, offsetY: SHADOW_OFFSETY },
      borderRadius: $r('sys.float.ohos_id_corner_radius_clicked'),
      fontColor: $r('sys.color.ohos_id_color_primary'),
      fontSize: $r('sys.float.ohos_id_text_size_body1'),
      fontWeight: FontWeight.Regular,
      imageOpacity: $r('sys.float.ohos_id_alpha_content_fourth')
    }

    private readonly subTitle: { normalFontColor: Resource,
    highLightFontColor: Resource,
    fontSize: Resource,
    fontWeight: FontWeight,
    margin: { left: string, right: string } } = {
      normalFontColor: $r('sys.color.ohos_id_color_secondary'),
      highLightFontColor: $r('sys.color.ohos_id_color_primary_contrary'),
      fontSize: $r('sys.float.ohos_id_text_size_body2'),
      fontWeight: FontWeight.Regular,
      margin: { left: '4vp', right: '24' }
    }

    private changeNodeColor(index: number, color: Resource | string): void {
      this.listNode[index].setNodeColor(color);
    }

    private getNodeColor(index) {
      return this.listNode[index].getNodeColor();
    }

    private handleFocusEffect(index: number, isClearFocusStatus: boolean) {
      if (this.listNode[index].getNodeIsShow()) {
        this.listNode[index].setNodeBorder(isClearFocusStatus);
      }
    }

    private setImageSource(index: number, interactionStatus: InteractionStatus) {
      let nodeInfo: NodeInfo = this.listNode[index];
      nodeInfo.setIsSelected(interactionStatus === InteractionStatus.Selected ||
        interactionStatus === InteractionStatus.Edit || interactionStatus === InteractionStatus.FinishEdit);
      if (nodeInfo.getNodeItem().mainTitleNode != null && interactionStatus != InteractionStatus.DragInsert &&
        interactionStatus != InteractionStatus.FinishDragInsert) {
        nodeInfo.getNodeItem().mainTitleNode.setMainTitleSelected(interactionStatus === InteractionStatus.Selected ||
          interactionStatus === InteractionStatus.FinishEdit);
      }
      if (nodeInfo.getNodeItem().imageNode != null) {
        nodeInfo.getNodeItem().imageNode.setImageSource(interactionStatus);
      }
    }

    private setImageCollapseSource(index: number, interactionStatus: InteractionStatus) {
      let nodeInfo: NodeInfo = this.listNode[index];
      if (nodeInfo.getNodeItem().imageCollapse != null) {
        nodeInfo.getNodeItem().imageCollapse.setImageCollapseSource(interactionStatus,
          this.expandAndCollapseInfo.get(nodeInfo.getCurrentNodeId()));
      }
    }

    public clearLastIndexStatus() {
      if (this.lastIndex == -1 || this.lastIndex >= this.listNode.length) {
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
      let nodeId =  tmp[clickIndex].getCurrentNodeId();
      if (this.expandAndCollapseInfo.get(nodeId) == NodeStatus.Expand) {
        this.expandAndCollapseInfo.set(nodeId, NodeStatus.Collapse);
        tmp[thisIndex].getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Collapse);
      } else if (this.expandAndCollapseInfo.get(nodeId) == NodeStatus.Collapse) {
        this.expandAndCollapseInfo.set(nodeId, NodeStatus.Expand);
        tmp[thisIndex].getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Expand);
      }
    }

    private handleExpandAndCollapse(clickIndex: number) {
      let thisIndex: number = clickIndex;
      let tmp: NodeInfo[] = this.ListNode;
      let nodeId = tmp[thisIndex].getCurrentNodeId();
      if (!this.expandAndCollapseInfo.has(nodeId)) {
        return;
      }

      let rootNodeStatus: NodeStatus = this.expandAndCollapseInfo.get(nodeId);
      if (tmp[thisIndex].getChildNodeInfo().isHasChildNode && rootNodeStatus == NodeStatus.Collapse) {
        for(var i = 0; i < tmp[thisIndex].getChildNodeInfo().allChildNum; i++) {
          tmp[thisIndex + 1 + i].setNodeIsShow(false);
          tmp[thisIndex + 1 + i].setListItemHeight(LIST_ITEM_HEIGHT_NONE);
        }
        this.notifyDataReload();
        return;
      }

      let childNum: number[] = new Array(tmp[thisIndex].getChildNodeInfo().childNum);
      childNum[0] = thisIndex + 1;
      let index = 1;
      while(index < tmp[thisIndex].getChildNodeInfo().childNum) {
        childNum[index] = childNum[index -1] + tmp[childNum[index - 1]].getChildNodeInfo().allChildNum + 1;
        index++;
      }
      if (rootNodeStatus == NodeStatus.Expand) {
        for(var i = 0; i < childNum.length; i++) {
          tmp[childNum[i]].setNodeIsShow(true);
          tmp[childNum[i]].setListItemHeight(LIST_ITEM_HEIGHT);
          let nodeId =  tmp[childNum[i]].getCurrentNodeId();
          if(this.expandAndCollapseInfo.get(nodeId) == NodeStatus.Expand) {
            this.handleExpandAndCollapse(childNum[i]);
          }
        }
      }
      childNum = null;
      this.notifyDataReload();
    }

    public init(listNodeUtils: ListNodeUtils) {
      let index = 0;
      this.listNode = [];
      this.listNodeUtils = listNodeUtils;
      this.loadedNodeIdAndIndexMap.clear();
      this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
        if (node.currentNodeId >= 0) {
          var nodeInfo: NodeInfo = new NodeInfo(node);
          this.listNode.push(nodeInfo);
          if (nodeInfo.getChildNodeInfo().isHasChildNode) {
            this.expandAndCollapseInfo.set(nodeInfo.getCurrentNodeId(), NodeStatus.Collapse);
          }
          if (nodeInfo.getNodeIsShow()) {
            this.loadedNodeIdAndIndexMap.set(nodeInfo.getCurrentNodeId(), index++);
          }
          if (nodeInfo.getIsFolder()) {
            this.nodeIdAndSubtitleMap.set(nodeInfo.getCurrentNodeId(),
              nodeInfo.getNodeInfoData().secondaryTitle || nodeInfo.getNodeInfoData().secondaryTitle == 0 ?
              nodeInfo.getNodeInfoData().secondaryTitle : '');
          }
        }
        return false;
      });
    }

    private refreshRemoveNodeData(removeNodeIdList: number[], parentNodeInfo: NodeInfo) {
      let deleteIndexList: number[] = [];
      for (let i = 0; i < removeNodeIdList.length; i++) {
        for (let j = 0; j < this.listNode.length; j++) {
          if (this.listNode[j].getNodeCurrentNodeId() == removeNodeIdList[i]) {
            let currentNodeId = this.listNode[j].getNodeCurrentNodeId();
            if (this.loadedNodeIdAndIndexMap.has(currentNodeId)) {
              // this.listNode index to lazyForEach index.
              deleteIndexList.push(this.loadedNodeIdAndIndexMap.get(currentNodeId));
            }
            let deleteNode = this.listNode.splice(j, 1);
            deleteNode = null; // free memory
            if (this.expandAndCollapseInfo.has(removeNodeIdList[i])) {
              this.expandAndCollapseInfo.delete(removeNodeIdList[i]); // delete deleteNode expandAndCollapseInfo.
            }
            break;
          }
        }
      }
      deleteIndexList.forEach((value)=>{
        this.notifyDataDelete(value); // notifyDataDelete do not  update data.
        this.notifyDataChange(value); // call notifyDataChange to update data.
      })
      let index: number = 0;
      for (let i = 0; i < this.listNode.length; i++) {
        if (this.listNode[i].getNodeCurrentNodeId() == parentNodeInfo.getNodeCurrentNodeId()) {
          if (parentNodeInfo.getNodeItem().imageCollapse == null) {
            this.listNode[i].handleImageCollapseAfterAddNode(false);
            // delete deleteNode parentNode expandAndCollapseInfo.
            this.expandAndCollapseInfo.delete(parentNodeInfo.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[i].getNodeCurrentNodeId()));
          }
          break;
        }
      }
      let callbackParam: CallbackParam = {currentNodeId: parentNodeInfo.getNodeCurrentNodeId(), parentNodeId: parentNodeInfo.getNodeParentNodeId()};
      this.appEventBus.emit(TreeListenType.NODE_DELETE, [callbackParam]);
    }

    private refreshAddNodeData(addNodeIdList: number[]) {
      var addNodeInfo: NodeInfo;
      this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
        if (node.currentNodeId === addNodeIdList[0]) {
          addNodeInfo = new NodeInfo(node);
          return true;
        }
        return false;
      });
      addNodeInfo.setIsModify(true);

      let index: number = 0;
      for (let i = 0; i < this.listNode.length; i++) {
        if (this.listNode[i].getNodeCurrentNodeId() == addNodeInfo.getNodeParentNodeId()) {
          index = i;
          if (this.listNode[i].getNodeItem().imageCollapse == null) {
            this.listNode[i].handleImageCollapseAfterAddNode(true);
            this.notifyDataChange(index);
          } else if (this.expandAndCollapseInfo.get(this.listNode[i].getNodeCurrentNodeId()) == NodeStatus.Collapse) {
            this.changeNodeStatus(index);
          }
          this.listNode.splice(i + 1, 0, addNodeInfo);
          this.listNode[i + 1].setTitleAndInputTextStatus(true); // false->true: realize inner Interaction.
          this.listNode[i + 1].setNodeIsShow(true);
          this.listNode[i + 1].setListItemHeight(LIST_ITEM_HEIGHT);
          this.setImageSource(i + 1, InteractionStatus.Edit); // Normal->Edit : realize inner Interaction.
          this.currentOperation = MenuOperation.ADD_NODE;
          this.notifyDataAdd(i + 1);
          this.notificationNodeInfo(i+1, this.currentOperation);
          break;
        }
      }
      this.modifyNodeIndex = index + 1;
      this.expandAndCollapseInfo.set(addNodeInfo.getNodeParentNodeId(), NodeStatus.Expand);
      this.handleExpandAndCollapse(index);
    }

    public refreshData(listNodeUtils: ListNodeUtils, operation: MenuOperation,
                       parentNodeId: number, changeNodeIdList: number[]) {
      let parentNodeInfo: NodeInfo;
      this.listNodeUtils = listNodeUtils;
      this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
        if (node.currentNodeId == parentNodeId) {
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
        return  -1;
      }
      return this.ListNode[this.thisIndex].getCurrentNodeId();
    }

    public expandAndCollapseNode(clickIndex: number) {
      this.changeNodeStatus(clickIndex);
      this.handleExpandAndCollapse(clickIndex)
    }

    public getIsTouchDown(): boolean {
      return this.isTouchDown;
    }

    public getLastIndex(): number {
      return this.lastIndex;
    }

    public handleEvent(event: Event, index: number) {
      /* Return while the event is dragging event. */
      if (this.isDrag) {
        return;
      }

      if (event === Event.TOUCH_DOWN || event === Event.TOUCH_UP || event === Event.MOUSE_BUTTON_RIGHT) {
        if (index != this.lastIndex) {
          this.clearLastIndexStatus();
        }
      }
      let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId());
      switch(event) {
        case Event.TOUCH_DOWN:
          this.isTouchDown = true;
          this.changeNodeColor(index, this.listNode[index].getNodeStatus().press);
          break;
        case Event.TOUCH_UP: {
          if (this.isInnerDrag) {
            this.isInnerDrag = false;
          }
          this.isTouchDown = false;
          let nodeInfo: NodeInfo = this.listNode[index];
          this.setImageSource(index, InteractionStatus.Selected);
          this.lastIndex = index;
          this.changeNodeColor(index, nodeInfo.getNodeStatus().selected);
          this.notifyDataChange(lazyForEachIndex);
          break;
        }
        case Event.HOVER:
          if (this.getNodeColor(index) != this.listNode[index].getNodeStatus().selected) {
            this.changeNodeColor(index, this.listNode[index].getNodeStatus().hover);
            this.notifyDataChange(lazyForEachIndex);
          }
          break;
        case Event.HOVER_OVER:
          if (this.getNodeColor(index) != this.listNode[index].getNodeStatus().selected) {
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

    private notificationNodeInfo(addNodeId: number, operation: MenuOperation) {
      if (operation === MenuOperation.MODIFY_NODE) {
        let modifyNodeInfo: NodeInfo = this.listNode[this.modifyNodeIndex];
        let backParamModify: CallbackParam = { currentNodeId: modifyNodeInfo.getNodeCurrentNodeId(),
          parentNodeId: modifyNodeInfo.getNodeParentNodeId() }
        this.appEventBus.emit(TreeListenType.NODE_MODIFY,
          [backParamModify]);
      } else if (operation === MenuOperation.ADD_NODE)  {
        let addNodeInfo: NodeInfo = this.listNode[addNodeId];
        let icon: Resource = (addNodeInfo.getNodeItem().imageNode != null) ?
        addNodeInfo.getNodeItem().imageNode.source : null;
        let selectedIcon: Resource = (addNodeInfo.getNodeItem().imageNode != null) ?
        addNodeInfo.getNodeItem().imageNode.selectedSource : null;
        let editIcon: Resource = (addNodeInfo.getNodeItem().imageNode != null) ?
        addNodeInfo.getNodeItem().imageNode.editSource : null;
        let callbackParam: CallbackParam = { currentNodeId: addNodeInfo.getNodeCurrentNodeId(),
          parentNodeId: addNodeInfo.getNodeParentNodeId() }
        this.appEventBus.emit(TreeListenType.NODE_ADD,
          [callbackParam]);
      }
    }

    public finishEditing() {
      if (this.modifyNodeIndex!= -1) {
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
      if (nodeId == -1) {
        return;
      }
      if (operation === MenuOperation.MODIFY_NODE) {
        for (let i = 0; i < this.listNode.length; i++) { // nodeId to find index
          if (this.listNode[i].getCurrentNodeId() == nodeId) {
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
          if (nodeInfo.getNodeItem().imageCollapse != null) {
            nodeInfo.getNodeItem().inputText.rightMargin =
            $r('sys.float.ohos_id_text_paragraph_margin_xs')
          } else {
            nodeInfo.getNodeItem().inputText.rightMargin =
            $r('sys.float.ohos_id_elements_margin_horizontal_m')
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
      let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(nodeInfo.getCurrentNodeId());
      if (!isShow) {
        this.notifyDataChange(lazyForEachIndex);
        return;
      }
      if (popUpType === PopUpType.HINTS) {
        if (nodeInfo.getNodeItem().mainTitleNode != null) {
          nodeInfo.setPopUpText(nodeInfo.getNodeItem().mainTitleNode.title);
        } else {
          nodeInfo.setPopUpText('');
          nodeInfo.setPopUpIsShow(false);
        }
        nodeInfo.setPopUpEnableArrow(false);
        nodeInfo.setPopUpColor($r('sys.color.ohos_id_color_background'));
        nodeInfo.setPopUpTextColor($r('sys.color.ohos_id_color_text_secondary'));
      } else if (popUpType === PopUpType.WARNINGS) {
        if (nodeInfo.getNodeItem().inputText != null) {
          if (inputError === InputError.INVALID_ERROR) {
            nodeInfo.setPopUpText("invalid error");
          } else if (inputError === InputError.LENGTH_ERROR) {
            nodeInfo.setPopUpText("length error");
          }
          nodeInfo.setPopUpEnableArrow(true);
          nodeInfo.setPopUpColor($r('sys.color.ohos_id_color_help_tip_bg'));
          nodeInfo.setPopUpTextColor($r('sys.color.ohos_id_color_text_hint_contrary'));
        }
      }
      this.notifyDataChange(lazyForEachIndex);
    }

    public setShowPopUpTimeout(timeout: number, index: number) {
      if (this.listNode[index].getNodeItem().mainTitleNode != null) {
        this.listNode[index].getNodeItem().mainTitleNode.popUpTimeout = timeout;
      }
      // this.notifyDataChange(index)  lazyForEachIndex;
      let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId());
      this.notifyDataChange(lazyForEachIndex);
    }

    public setMainTitleNameOnEdit(index: number, text: string) {
      this.modifyNodeIndex = index;
      if (this.listNode[index].getNodeItem().mainTitleNode != null) {
        this.listNode[index].getNodeItem().mainTitleNode.title = text;
        // this.listNode index to lazyForEach index.
        let lazyForEachIndex = this.loadedNodeIdAndIndexMap.get(this.listNode[index].getCurrentNodeId());
        this.notifyDataChange(lazyForEachIndex);
      }
    }

    public get ListNode(): NodeInfo[] {
      return this.listNode;
    }

    public totalCount(): number {
      let count: number = 0;
      let index: number = 0;
      this.loadedNodeIdAndIndexMap.clear();
      for (let i =0 ; i < this.listNode.length; i++) {
        if (this.listNode[i].getNodeIsShow()) {
          this.loadedNodeIdAndIndexMap.set(this.listNode[i].getCurrentNodeId(), index++);
          count++;
        }
      }
      return count;
    }

    public getData(index: number): any {
      let count = 0;
      for (let i = 0; i < this.listNode.length; i++) {
        if (this.listNode[i].getNodeIsShow()) {
          if (index == count) {
            return this.listNode[i];
          }
          count++;
        }
      }
      return null;
    }

    public addData(index: number, data: NodeInfo): void {
      this.listNode.splice(index, 0, data)
      this.notifyDataAdd(index)
    }

    public pushData(data: NodeInfo): void {
      this.listNode.push(data)
      this.notifyDataAdd(this.listNode.length - 1)
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

    public setCurrentNodeInfo(currentNodeInfo: NodeInfo) {
      this.currentNodeInfo = currentNodeInfo;
    }

    public getCurrentNodeInfo() {
      return this.currentNodeInfo;
    }

    public setDraggingParentNodeId(draggingParentNodeId: number) {
      this.draggingParentNodeId = draggingParentNodeId;
    }

    public getDraggingParentNodeId() {
      return this.draggingParentNodeId;
    }

    public getDraggingCurrentNodeId() {
      return this.draggingCurrentNodeId;
    }

    public setDraggingCurrentNodeId(draggingCurrentNodeId: number) {
      this.draggingCurrentNodeId = draggingCurrentNodeId;
    }

    public setListItemOpacity(listItemOpacity: number) {
      this.listItemOpacity = listItemOpacity;
    }

    public getListItemOpacity(item: NodeInfo) {
      return item.getCurrentNodeId() == this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1;
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

    public getIsParentOfInsertNode(insertNodeId: number): boolean {
      let selectedNodeItem: NodeItem = this.currentNodeInfo.getNodeInfoNode();
      let isParentNodeOfInsertNode = false,
        callback = function(node): boolean {
          if (node.currentNodeId == insertNodeId ) {
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
      if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
        let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
        let that =this;
        this.ListNode.forEach(function(value) {
          if (value.getNodeCurrentNodeId() == that.lastPassId) {
            value.setCanShowFlagLine(false);
          }
        })
        this.notifyDataChange(index);
      }

      if ((this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutHighLightId != this.lastTimeoutHighLightId)) {
        clearTimeout(this.lastTimeoutHighLightId);
        if (this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE) {
          this.clearHighLight(this.lastDelayHighLightIndex);
          let index: number = this.loadedNodeIdAndIndexMap
            .get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId());
          this.notifyDataChange(index);
        }
        this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
      }
      this.lastTimeoutHighLightId = this.timeoutHighLightId;
      this.lastDelayHighLightIndex = currentIndex;

      if ((this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutExpandId != this.lastTimeoutExpandId)) {
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
        this.listNode[index].getNodeItem().mainTitleNode.setMainTitleHighLight(isHighLight);
      }
    }

    public setVisibility(flag: Flag, index: number, isOverBorder: boolean) {
      let isChanged: boolean = (this.thisPassIndex != index || this.flag != flag) ? true : false;
      this.thisPassIndex = index;
      if ((isChanged || isOverBorder) && this.isInnerDrag) {
        this.flag = flag;
        let currentNodeId: number = this.getData(index).getCurrentNodeId();
        let currentNodeLevel: number = this.expandAndCollapseInfo.get(currentNodeId) == NodeStatus.Expand &&
                                         this.flag == Flag.DOWN_FLAG ? this.getData(index).getNodeLevel() + 1 : this.getData(index).getNodeLevel();
        if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
          let lastIndex: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
          let that = this;
          this.ListNode.forEach(function (value) {
            if (value.getNodeCurrentNodeId() == that.lastPassId) {
              value.setCanShowFlagLine(false);
            }
          })
          this.notifyDataChange(lastIndex);
        }
        if (this.flag == Flag.DOWN_FLAG && index < this.totalCount() - 1) {
          this.getData(index).setCanShowFlagLine(false);
          this.getData(index+1).setCanShowFlagLine(true);
          this.getData(index).setCanShowBottomFlagLine(false);
          this.getData(index+1).setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.notifyDataChange(index + 1);
          this.lastPassId = this.getData(index + 1).getNodeCurrentNodeId();
        } else if (this.flag == Flag.UP_FLAG && index < this.totalCount() - 1) {
          this.getData(index).setCanShowFlagLine(true);
          this.getData(index+1).setCanShowFlagLine(false);
          this.getData(index).setCanShowBottomFlagLine(false);
          this.getData(index).setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.notifyDataChange(index + 1);
          this.lastPassId = this.getData(index).getNodeCurrentNodeId();
        } else if (index >= this.totalCount() - 1) {
          if (this.flag == Flag.DOWN_FLAG) {
            this.getData(index).setCanShowFlagLine(false);
            this.getData(index).setCanShowBottomFlagLine(true);
          } else {
            this.getData(index).setCanShowFlagLine(true);
            this.getData(index).setCanShowBottomFlagLine(false);
          }
          this.getData(index).setFlagLineLeftMargin(currentNodeLevel);
          this.notifyDataChange(index);
          this.lastPassId = this.getData(index).getNodeCurrentNodeId();
        }
      }
    }

    public delayHighLightAndExpandNode(currentIndex: number, currentNodeId: number, showIndex: number) {
      let isChangIndex: boolean = currentIndex != this.lastDelayExpandIndex ? true : false;
      let isOverBorder: boolean = this.getData(showIndex).getIsOverBorder();
      if (isOverBorder) {
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
      } else {
        this.lastDelayExpandIndex = currentIndex;
      }
      if (isOverBorder || isChangIndex) {
        let that = this;

        /* highLight node time-out. */
        let canDelayHighLight: boolean = !isOverBorder && (!this.isInnerDrag ||
          (this.expandAndCollapseInfo.get(currentNodeId) == NodeStatus.Collapse && this.isInnerDrag) ||
          (!this.expandAndCollapseInfo.has(currentNodeId) && this.listNode[currentIndex].getIsFolder()));
        if (canDelayHighLight) {
          /* set hoverState color before highLight. */
          this.changeNodeColor(currentIndex, this.listNode[currentIndex].getNodeStatus().hover);
          this.notifyDataChange(showIndex);

          let delayHighLightTime: number = this.isInnerDrag ? 1000 : 0; // ms
          this.timeoutHighLightId = setTimeout(function() {
            that.delayHighLight(currentIndex);
          }, delayHighLightTime)
        }
        if (isOverBorder || (this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE &&
          this.clearTimeoutHighLightId != this.lastTimeoutHighLightId)) {
          clearTimeout(this.lastTimeoutHighLightId);
          if (this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE) {
            this.clearHighLight(this.lastDelayHighLightIndex);
            this.notifyDataReload();
          }
          this.clearTimeoutHighLightId = this.lastTimeoutHighLightId;
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = currentIndex;

        /* alter flagLine and expand node time-out. */
        if (!isOverBorder && this.expandAndCollapseInfo.get(currentNodeId) == NodeStatus.Collapse) {
          let firstChildNodeId: number = this.getData(showIndex).getNodeInfoNode().children[0].currentNodeId;
          let delayAlterFlagLineAndExpandNodeTime: number = 2000; // ms
          this.timeoutExpandId = setTimeout(function() {
            that.clearHighLight(that.lastDelayHighLightIndex);
            that.alterFlagLineAndExpandNode(currentIndex, firstChildNodeId);
          }, delayAlterFlagLineAndExpandNodeTime)
        }
        if (isOverBorder || (this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE &&
          this.clearTimeoutExpandId != this.lastTimeoutExpandId)) {
          clearTimeout(this.lastTimeoutExpandId);
          this.clearTimeoutExpandId = this.lastTimeoutExpandId;
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
      }
    }

    public delayHighLight(currentIndex: number) {
      let that =this;
      this.ListNode.forEach(function (value) {
        if (value.getNodeCurrentNodeId() == that.lastPassId) {
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
      let that =this;
      this.ListNode.forEach(function (value) {
        if (value.getNodeCurrentNodeId() == that.lastPassId) {
          value.setCanShowFlagLine(false);
          value.setCanShowBottomFlagLine(false);
        }
      })
      this.ListNode.forEach(function (value) {
        if (that.isInnerDrag && value.getNodeCurrentNodeId() == firstChildNodeId) {
          value.setCanShowFlagLine(true);
        }
      })
      this.changeNodeStatus(currentIndex);
      this.handleExpandAndCollapse(currentIndex);
      this.lastPassId = firstChildNodeId;
    }

    public hideLastLine() {
      if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
        let that = this;
        this.ListNode.forEach(function (value) {
          if (value.getNodeCurrentNodeId() == that.lastPassId) {
            value.setCanShowFlagLine(false);
            value.setCanShowBottomFlagLine(false);
          }
        })
        let index: number = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
        this.notifyDataChange(index);
      }
    }

    public clearLastTimeoutHighLight() {
      if (this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutHighLightId != this.lastTimeoutHighLightId) {
        clearTimeout(this.lastTimeoutHighLightId);
        if (this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE) {
          this.clearHighLight(this.lastDelayHighLightIndex);
        }
      }
    }

    public clearLastTimeoutExpand() {
      if (this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE &&
        this.clearTimeoutExpandId != this.lastTimeoutExpandId) {
        clearTimeout(this.lastTimeoutExpandId);
      }
    }

    public getSubtitle(currentNodeId: number): string {
      if (this.nodeIdAndSubtitleMap.has(currentNodeId)) {
        if (typeof this.nodeIdAndSubtitleMap.get(currentNodeId) == "number") {
          return this.nodeIdAndSubtitleMap.get(currentNodeId).toString();
        } else {
          return this.nodeIdAndSubtitleMap.get(currentNodeId)
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
        if (index == this.lastDelayHighLightIndex) {
          this.lastDelayHighLightId = value.getCurrentNodeId();
        }
      })
    }

    public setLastPassId(lastPassId: number) {
      this.lastPassId = lastPassId;
    }

    public setLastDelayHighLightIndex(lastDelayHighLightIndex) {
      this.lastDelayHighLightIndex = lastDelayHighLightIndex;
    }

    /*
   * Alter the current node location to a needful position.
   * 1.Create an array named 'dragNodeParam' to store dragging node information.
   * 2.Delete the dragging node from the tree.
   * 3.Add the dragging node to the tree.
   */
    public alterDragNode(rearParentNodeId: number, rearCurrentNodeId: number, insertNodeInfo: NodeInfo,
                         dragParentNodeId: number, dragCurrentNodeId: number, frontNodeInfoItem: NodeInfo) {
      let dragNodeParam: { parentId: number, currentId: number, data: any }[] = [];
      let parentNodeId: number = rearParentNodeId;
      let currentNodeId: number = dragCurrentNodeId;
      let nodeParam = frontNodeInfoItem.getNodeInfoData();
      let nodeInfo: NodeInfo = null;
      let nodeInfoNode: NodeItem = frontNodeInfoItem.getNodeInfoNode();
      let isHighLight : boolean = false;
      let insertChildIndex: number = this.INITIAL_INVALID_VALUE;
      let currentChildIndex: number = this.INITIAL_INVALID_VALUE;
      let isDownFlag: boolean = this.flag == Flag.DOWN_FLAG ? true : false;

      currentChildIndex = this.getChildIndex(dragParentNodeId, dragCurrentNodeId);
      insertChildIndex = this.getChildIndex(rearParentNodeId, rearCurrentNodeId);

      if (rearParentNodeId != dragParentNodeId) {
        insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
      } else {
        if (insertChildIndex > currentChildIndex) {
          insertChildIndex = isDownFlag ? insertChildIndex : insertChildIndex - 1;
        } else {
          insertChildIndex = isDownFlag ? insertChildIndex + 1 : insertChildIndex;
        }
      }

      for (let i = 0; i < this.listNode.length; i++) {
        if (this.listNode[i].getCurrentNodeId() == rearCurrentNodeId) {
          isHighLight = this.listNode[i].getIsHighLight();
          if (this.flag == Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) == NodeStatus.Expand) {
            parentNodeId = rearCurrentNodeId;
            insertChildIndex = 0;
          } else if (this.flag == Flag.UP_FLAG && this.expandAndCollapseInfo.get(rearCurrentNodeId) == NodeStatus.Expand
            && this.listNode[i].getCanShowFlagLine() == false) {
            parentNodeId = rearCurrentNodeId;
            insertChildIndex = 0;
          } else if (isHighLight) {
            parentNodeId = rearCurrentNodeId;
            insertChildIndex = 0;
          }
          break;
        }
      }

      let callbackParam: CallbackParam = { currentNodeId: currentNodeId, parentNodeId: parentNodeId, childIndex: insertChildIndex }

      /* export inner drag node Id. */
      this.appEventBus.emit(TreeListenType.NODE_MOVE, [callbackParam]);

      /* To store dragging node information by the array named 'dragNodeParam'. */
      dragNodeParam.push({parentId: parentNodeId, currentId: currentNodeId, data: nodeParam});

      let oneself = null,
        callback = function(node, listNode): boolean {
          if (node) {
            oneself = node;
            parentNodeId = oneself.parentNodeId;
            currentNodeId = oneself.currentNodeId;
            for (let i = 0; i < listNode.length; i++) {
              if (listNode[i].getNodeCurrentNodeId() == currentNodeId) {
                nodeInfo = listNode[i];
                break;
              }
            }
            nodeParam = nodeInfo.getNodeInfoData();
            if (parentNodeId != dragParentNodeId) {
              dragNodeParam.push({parentId: parentNodeId, currentId: currentNodeId, data: nodeParam});
            }
            return false;
          }
          return false;
        }
      this.listNodeUtils.dragTraverseNodeDF(callback, nodeInfoNode, this.listNode);

      /* Delete the dragging node from the tree. */
      this.listNodeUtils.removeNode(dragCurrentNodeId, dragParentNodeId, this.listNodeUtils.traverseNodeBF);

      /*
     * Add the dragging node to the tree
     * 1.The first dragging node is added singly, because it needs to distinguish the position to insert
     *
     * Add first node.
     */
      let insertCurrentNodeId: number = rearCurrentNodeId;
      let isAfter: boolean = isDownFlag;
      if (this.expandAndCollapseInfo.get(rearCurrentNodeId) == NodeStatus.Expand) {
        isAfter = false;
        this.listNode.forEach((value) => {
          if (value.getCurrentNodeId() == rearCurrentNodeId && value.getCanShowFlagLine() == false) {
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
      for (let j = 1; j < dragNodeParam.length; j++) {
        this.listNodeUtils.addNode(dragNodeParam[j].parentId, dragNodeParam[j].currentId, dragNodeParam[j].data);
      }

      /* Update node data and reload the array named 'listNode'. */
      for (let i = 0; i < this.listNode.length; i++) {
        if (this.listNode[i].getCurrentNodeId() == dragParentNodeId) {
          if (this.listNode[i].getNodeInfoNode().getNodeItem().imageCollapse == null) {
            this.listNode[i].handleImageCollapseAfterAddNode(false);
            this.expandAndCollapseInfo.delete(dragParentNodeId);
            break;
          }
        }
      }
      let tmp: NodeInfo[] = [...this.listNode];
      this.reloadListNode(this.listNodeUtils, tmp);

    }

    /*
   * Reload the array named 'listNode'
   * @param listNodeUtils
   * @param tmp
   */
    public reloadListNode(listNodeUtils: ListNodeUtils, tmp: NodeInfo[]) {
      let index = 0;
      this.listNode = [];
      this.listNodeUtils = listNodeUtils;
      this.loadedNodeIdAndIndexMap.clear();
      this.listNodeUtils.traverseNodeDF((node: NodeItem): boolean => {
        if (node.currentNodeId >= 0) {
          var nodeInfo: NodeInfo = new NodeInfo(node);
          this.listNode.push(nodeInfo);

          if (this.expandAndCollapseInfo.get(node.currentNodeId) == NodeStatus.Expand) {
            nodeInfo.getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Expand);
          } else if (this.expandAndCollapseInfo.get(node.currentNodeId) == NodeStatus.Collapse) {
            nodeInfo.getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Collapse);
          }

          for (let i = 0; i < tmp.length; i++){
            if (tmp[i].getCurrentNodeId() == nodeInfo.getCurrentNodeId()) {
              nodeInfo.setNodeIsShow(tmp[i].getNodeIsShow());
              nodeInfo.setListItemHeight(tmp[i].getListItemHeight());
              if (nodeInfo.getNodeItem().mainTitleNode && nodeInfo.getIsShowTitle()) {
                nodeInfo.getNodeItem().mainTitleNode.title = tmp[i].getNodeItem().mainTitleNode.title;
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

    public getVisibility(nodeInfo: NodeInfo): any {
      let lastShowIndex: number = this.loadedNodeIdAndIndexMap.get(nodeInfo.getCurrentNodeId()) - 1;
      if (lastShowIndex > this.INITIAL_INVALID_VALUE) {
        let lastNodeInfo: NodeInfo = this.getData(lastShowIndex);
        return (nodeInfo.getCanShowFlagLine() == true && !nodeInfo.getIsHighLight() && !lastNodeInfo.getIsHighLight()) ?
        Visibility.Visible : Visibility.Hidden;
      } else {
        return (nodeInfo.getCanShowFlagLine() == true && !nodeInfo.getIsHighLight()) ?
        Visibility.Visible : Visibility.Hidden;
      }
    }

    public getSubTitlePara() {
      return this.subTitle;
    }

    public getIsFolder(nodeId: number) {
      if (this.loadedNodeIdAndIndexMap.has(nodeId)) {
        return this.getData(this.loadedNodeIdAndIndexMap.get(nodeId)).getIsFolder();
      }
      return false;
    }

    public getSubTitleFontColor(isHighLight: boolean) {
      return isHighLight ? this.subTitle.highLightFontColor : this.subTitle.normalFontColor;
    }

    private getChildIndex(rearParentNodeId: number, rearCurrentNodeId: number) {
      let insertChildIndex: number = this.INITIAL_INVALID_VALUE;
      this.listNodeUtils.traverseNodeBF(function(node): boolean {
        if (node.getCurrentNodeId() == rearParentNodeId) {
          node.children.forEach((value, index) => {
            if (value.getCurrentNodeId() == rearCurrentNodeId) {
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

  /* nodeId to find index */
  function findCurrentNodeIndex(this, currentNodeId: number): number {
    let thisIndex: number = 0;
    this.listNodeDataSource.ListNode.forEach(function (value, index) {
      if (value.getNodeCurrentNodeId() == currentNodeId) {
        thisIndex = index;
      }
    })
    return thisIndex;
  }

  /**
   * Tree view control, which is created by using the TreeController class.
   *
   * When you create this component, you must initialize the listNodeDataSource.
   * You can run the listTreeViewWidth command to set the width of the component.
   * The default width is 200vp.
   *
   * @since 10
   */
  @Component
  export struct TreeView {
    listNodeDataSource: ListNodeDataSource;
    treeController: TreeController;
    @State dropSelectedIndex: number = 0;
    @BuilderParam private listTreeViewMenu: () => void  = null;
    @Prop listTreeViewWidth: string | number;
    @Prop listTreeViewHeight: number | string;
    private readonly MAX_CN_LENGTH: number = 254;
    private readonly MAX_EN_LENGTH: number = 255;
    private readonly INITIAL_INVALID_VALUE = -1;
    private readonly MAX_TOUCH_DOWN_COUNT = 0;
    private isMultiPress: boolean = false;
    private touchDownCount: number = this.INITIAL_INVALID_VALUE;
    private appEventBus: TreeListener = TreeListenerManager.getInstance().getTreeListener();
    private readonly itemPadding: { left: Resource, right: Resource, top: Resource, bottom: Resource } =
      { left: $r('sys.float.ohos_id_card_margin_middle'),
        right: $r('sys.float.ohos_id_card_margin_middle'),
        top: $r('sys.float.ohos_id_text_margin_vertical'),
        bottom: $r('sys.float.ohos_id_text_margin_vertical')};
    /* { left: '12vp', right: '12vp', top: '2vp', bottom: '2vp' } */
    private readonly textInputPadding:  { left : string, right: string, top: string, bottom: string } =
      { left : '0vp', right: '0vp', top: '0vp', bottom: '0vp'}
    aboutToAppear(): void  {
      this.listTreeViewWidth = (this.listTreeViewWidth === undefined) ? 200 : this.listTreeViewWidth;
      this.listNodeDataSource = this.treeController.getListNodeDataSource();
    }

    private checkInvalidPattern(title: string): boolean {
      let pattern = /[\\\/:*?"<>|]/;
      return pattern.test(title)
    }

    private checkIsAllCN(title: string): boolean {
      let pattern = /^[\u4e00-\u9fa5]+$/;
      return pattern.test(title)
    }

    @Builder popupForShowTitle(text: string | Resource, backgroundColor: Resource, fontColor: Resource ) {
      Row() {
        Text(text).fontSize($r('sys.float.ohos_id_text_size_body2')).fontWeight('regular').fontColor(fontColor)
      }.backgroundColor(backgroundColor)
      .border({radius: $r('sys.float.ohos_id_elements_margin_horizontal_l')})
      .padding({left: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
        right: $r('sys.float.ohos_id_elements_margin_horizontal_l'),
        top: $r('sys.float.ohos_id_card_margin_middle'),
        bottom: $r('sys.float.ohos_id_card_margin_middle')})
    }

    @Builder builder() {
      this.listTreeViewMenu()
    }

    /* Set the popup of dragging node. */
    @Builder draggingPopup(item: NodeInfo) {
      Row() {
        if (item.getNodeItem().imageNode) {
          Row() {
            Image(item.getNodeItem().imageNode.normalSource)
              .objectFit(ImageFit.Contain)
              .height(item.getNodeItem().imageNode.itemHeight)
              .width(item.getNodeItem().imageNode.itemWidth)
              .opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity)
          }
          .backgroundColor(COLOR_IMAGE_ROW)
          .margin({ right: item.getNodeItem().imageNode.itemRightMargin })
          .height(item.getNodeItem().imageNode.itemHeight)
          .width(item.getNodeItem().imageNode.itemWidth)
        }
        Row() {
          if (item.getNodeItem().mainTitleNode && item.getIsShowTitle()) {
            Text(item.getNodeItem().mainTitleNode.title)
              .maxLines(1)
              .fontSize(item.getNodeItem().mainTitleNode.size)
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
      .shadow({ radius: this.listNodeDataSource.getDragPopupPara().shadow.radius,
        color: this.listNodeDataSource.getDragPopupPara().shadow.color,
        offsetY: this.listNodeDataSource.getDragPopupPara().shadow.offsetY })
      .borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius) // need to doubleCheck.
    }

    build() {
      List({ }) {
        LazyForEach(this.listNodeDataSource, (item: NodeInfo) => {
          ListItem() {
            if (item.getNodeIsShow()) {
              Column() {
                Divider()
                  .height(this.listNodeDataSource.getFlagLine().flagLineHeight)
                  .color(this.listNodeDataSource.getFlagLine().flagLineColor)
                  .visibility(this.listNodeDataSource.getVisibility(item))
                  .lineCap(LineCapStyle.Round)
                  .margin({ left: item.getFlagLineLeftMargin() })
                  .markAnchor({ x: this.listNodeDataSource.getFlagLine().xOffset,
                    y: this.listNodeDataSource.getFlagLine().yTopOffset })
                Row({}) {
                  Row({}) {
                    if (item.getNodeItem().imageNode) {
                      Row() {
                        Image(item.getNodeItem().imageNode.source)
                          .objectFit(ImageFit.Contain)
                          .height(item.getNodeItem().imageNode.itemHeight)
                          .width(item.getNodeItem().imageNode.itemWidth)
                          .opacity(!item.getIsSelected() && !item.getIsHighLight() ?
                          item.getNodeItem().imageNode.opacity : item.getNodeItem().imageNode.noOpacity)
                          .focusable(item.getNodeItem().mainTitleNode != null ? false : true)
                          .onFocus(() => {
                            let that = this;
                            that.listNodeDataSource.handleEvent(Event.FOCUS,
                              findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                          })
                          .onBlur(() => {
                            let that = this;
                            that.listNodeDataSource.handleEvent(Event.BLUR,
                              findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                          })
                      }
                      .backgroundColor(COLOR_IMAGE_ROW)
                      .margin({ right: item.getNodeItem().imageNode.itemRightMargin })
                      .height(item.getNodeItem().imageNode.itemHeight)
                      .width(item.getNodeItem().imageNode.itemWidth)
                    }
                    Row() {
                      if (item.getNodeItem().mainTitleNode && item.getIsShowTitle()) {
                        Text(item.getNodeItem().mainTitleNode.title)
                          .maxLines(1) // max line
                          .fontSize(item.getNodeItem().mainTitleNode.size)
                          .fontColor(item.getNodeItem().mainTitleNode.color)
                          .margin({ right: item.getNodeItem().mainTitleNode.itemRightMargin })
                          .textOverflow({ overflow: TextOverflow.Ellipsis })
                          .fontWeight(item.getNodeItem().mainTitleNode.weight)
                          .focusable(true)
                          .onFocus(() => {
                            let that = this;
                            this.listNodeDataSource.handleEvent(Event.FOCUS,
                              findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                          })
                          .onBlur(() => {
                            let that = this;
                            that.listNodeDataSource.handleEvent(Event.BLUR,
                              findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                          })
                      }
                      if (item.getNodeItem().mainTitleNode &&
                      item.getNodeItem().inputText &&
                      item.getIsShowInputText()) {
                        Row() {
                          TextInput({ text: item.getNodeItem().mainTitleNode.title })
                            .height(item.getNodeItem().inputText.itemHeight)
                            .fontSize(item.getNodeItem().inputText.size)
                            .fontColor(item.getNodeItem().inputText.color)
                            .borderRadius(item.getNodeItem().inputText.borderRadius)
                            .backgroundColor(item.getNodeItem().inputText.backgroundColor)
                            .enterKeyType(EnterKeyType.Done)
                            .padding({ left: this.textInputPadding.left, right: this.textInputPadding.right,
                              top: this.textInputPadding.top, bottom: this.textInputPadding.bottom })
                            .onChange((value: string) => {
                              let that = this;
                              var thisIndex = findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId());
                              let res: string = '';
                              let isInvalidError: boolean = false;
                              let isLengthError: boolean = false;
                              if (that.checkInvalidPattern(value)) {
                                for (let i = 0; i < value.length; i++) {
                                  if (!that.checkInvalidPattern(value[i])) {
                                    res += value[i];
                                  }
                                }
                                isInvalidError = true;
                                that.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                  InputError.INVALID_ERROR, true, thisIndex);
                              } else {
                                res = value;
                                isInvalidError = false;
                                that.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                  InputError.INVALID_ERROR, false, thisIndex);
                              }
                              if ((that.checkIsAllCN(res) && res.length > this.MAX_CN_LENGTH) ||
                                (!that.checkIsAllCN(res) && res.length > this.MAX_EN_LENGTH)) {
                                res = that.checkIsAllCN(res) ?
                                res.substr(0, this.MAX_CN_LENGTH) : res.substr(0, this.MAX_EN_LENGTH);
                                isLengthError = true;
                                that.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                  InputError.LENGTH_ERROR, true, thisIndex);
                              } else {
                                isLengthError = false;
                              }
                              if (!isLengthError && !isInvalidError) {
                                that.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS,
                                  InputError.LENGTH_ERROR, false, thisIndex);
                                that.listNodeDataSource.setMainTitleNameOnEdit(thisIndex, res);
                              }

                            })
                            .onSubmit((enterKey: EnterKeyType) => {
                              let that = this;
                              var thisIndex = findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId());
                              that.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE, false, thisIndex);
                              that.listNodeDataSource.setItemVisibilityOnEdit(thisIndex, MenuOperation.COMMIT_NODE);
                            })
                        }.backgroundColor(item.getNodeItem().inputText.backgroundColor)
                        .borderRadius(item.getNodeItem().inputText.borderRadius)
                        .margin({ right: item.getNodeItem().inputText.itemRightMargin })
                      }
                      Blank()
                    }.layoutWeight(1)

                    if (this.listNodeDataSource.hasSubtitle(item.getCurrentNodeId())) {
                      Row() {
                        Text(this.listNodeDataSource.getSubtitle(item.getCurrentNodeId()))
                          .fontSize(this.listNodeDataSource.getSubTitlePara().fontSize)
                          .fontColor(this.listNodeDataSource.getSubTitleFontColor(item.getIsHighLight() || item.getIsModify()))
                          .fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight)
                      }
                      .margin({ left: this.listNodeDataSource.getSubTitlePara().margin.left,
                        right: item.getNodeItem().imageCollapse ?
                          0 : this.listNodeDataSource.getSubTitlePara().margin.right })
                    }

                    if (item.getNodeItem().imageCollapse) {
                      Row() {
                        Image(item.getNodeItem().imageCollapse.collapseSource)
                          .fillColor(item.getNodeItem().imageCollapse.isCollapse ? COLOR_IMAGE_ROW : COLOR_IMAGE_EDIT)
                          .align(Alignment.End)
                          .objectFit(ImageFit.Contain)
                          .height(item.getNodeItem().imageCollapse.itemHeight)
                          .width(item.getNodeItem().imageCollapse.itemWidth)
                          .opacity(!item.getIsHighLight() ?
                          item.getNodeItem().imageCollapse.opacity : item.getNodeItem().imageCollapse.noOpacity)
                          .onTouch((event: TouchEvent) => {
                            if (event.type === TouchType.Down) {
                              let that = this;
                              that.listNodeDataSource.expandAndCollapseNode(
                                findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                              this.listNodeDataSource.setCurrentFocusNodeId(item.getCurrentNodeId());
                            }
                            event.stopPropagation();
                          })
                      }
                      .backgroundColor(COLOR_IMAGE_ROW)
                      .height(item.getNodeItem().imageCollapse.itemHeight)
                      .width(item.getNodeItem().imageCollapse.itemWidth)
                    }
                  }
                  .width('100%')
                  .onTouch((event: TouchEvent) => {
                    let that = this;
                    let index = findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId());
                    let currentId = item.getNodeCurrentNodeId();
                    that.listNodeDataSource.setClickIndex(index);
                    if (event.type === TouchType.Down) {
                      this.touchDownCount ++;
                      this.isMultiPress = this.touchDownCount > this.MAX_TOUCH_DOWN_COUNT ? true : false;
                      if (!this.listNodeDataSource.getIsTouchDown()) {
                        that.listNodeDataSource.handleEvent(Event.TOUCH_DOWN, index);
                      }
                    }
                    if (event.type === TouchType.Up) {
                      this.touchDownCount--;
                      if (this.touchDownCount < this.MAX_TOUCH_DOWN_COUNT) {
                        this.isMultiPress = false;
                      }
                      let callbackParam = { currentNodeId: currentId }
                      this.appEventBus.emit(TreeListenType.NODE_CLICK, [callbackParam]);
                      that.listNodeDataSource.handleEvent(Event.TOUCH_UP, index);
                    }
                  })
                  .onHover((isHover: boolean) => {
                    let that = this;
                    let index = findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId())
                    if (isHover) {
                      that.listNodeDataSource.handleEvent(Event.HOVER, index);
                    } else {
                      if (!that.listNodeDataSource.getIsTouchDown()) {
                        that.listNodeDataSource.handleEvent(Event.HOVER_OVER, index);
                      }
                    }
                  })
                  .gesture(
                    TapGesture({ count: 2 }) // doubleClick
                      .onAction((event: GestureEvent) => {
                        let that = this;
                        that.listNodeDataSource.expandAndCollapseNode(
                          findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                      })
                  )
                  .height(item.getNodeHeight())
                  .padding({ left: item.getNodeLeftPadding() })
                  /* backgroundColor when editing and in other states. */
                  .backgroundColor((item.getNodeItem().mainTitleNode && item.getNodeItem().inputText &&
                  item.getIsShowInputText()) ? item.getNodeItem().inputText.editColor : item.getNodeColor())
                  .border({
                    width: item.getNodeBorder().borderWidth,
                    color: item.getNodeBorder().borderColor,
                    radius: item.getNodeBorder().borderRadius
                  })
                  .bindContextMenu(this.builder, ResponseType.RightClick)
                }
                .opacity(this.listNodeDataSource.getListItemOpacity(item))
                .markAnchor({ x: this.listNodeDataSource.getFlagLine().xOffset,
                  y: this.listNodeDataSource.getFlagLine().yBasePlateOffset })
                if (item.getCanShowBottomFlagLine()) {
                  if (this.listNodeDataSource.getPassIndex() == this.listNodeDataSource.totalCount() - 1 &&
                    !item.getIsHighLight()) {
                    Divider()
                      .height(this.listNodeDataSource.getFlagLine().flagLineHeight)
                      .color(this.listNodeDataSource.getFlagLine().flagLineColor)
                      .visibility(Visibility.Visible)
                      .lineCap(LineCapStyle.Round)
                      .margin({ left: item.getFlagLineLeftMargin() })
                      .markAnchor({ x: this.listNodeDataSource.getFlagLine().xOffset,
                        y: this.listNodeDataSource.getFlagLine().yBottomOffset })
                  }
                }
              }
              .focusable(true)
              .onMouse((event: MouseEvent) => {
                let that = this;
                let thisIndex = findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId());
                if (event.button == MouseButton.Right) {
                  that.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT,
                    findCurrentNodeIndex.call(that, item.getNodeCurrentNodeId()));
                  this.listTreeViewMenu = item.getMenu();
                  that.listNodeDataSource.setClickIndex(thisIndex);
                  that.listNodeDataSource.setPopUpInfo(PopUpType.HINTS, InputError.NONE, false, thisIndex);
                  clearTimeout(item.getNodeItem().mainTitleNode.popUpTimeout);
                }
                event.stopPropagation();
              })
              .padding({ top: this.itemPadding.top, bottom: this.itemPadding.bottom })
              .bindPopup(item.getPopUpInfo().popUpIsShow, {
                builder: this.popupForShowTitle(item.getPopUpInfo().popUpText, item.getPopUpInfo().popUpColor,
                  item.getPopUpInfo().popUpTextColor),
                placement: Placement.BottomLeft,
                placementOnTop: false,
                popupColor: item.getPopUpInfo().popUpColor,
                autoCancel: true,
                enableArrow: item.getPopUpInfo().popUpEnableArrow
              })
            }

          }
          .width('100%').height(item.getListItemHeight())
          .padding({ left: this.itemPadding.left, right: this.itemPadding.right})
          .align(Alignment.Start)
          .onDragStart((event: DragEvent, extraParams: string) => {
            if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
              console.error('drag error, a item has been dragged');
              return;
            }
            this.dropSelectedIndex = JSON.parse(extraParams).selectedIndex;
            let currentNodeIndex = JSON.parse(extraParams).selectedIndex;
            let currentNodeInfo = this.listNodeDataSource.getData(currentNodeIndex);
            let currentItemNodeId = item.getNodeCurrentNodeId();

            /* handle the situation of drag error, currentNodeIndex is not found in onDragStart. */
            if (currentNodeIndex >= this.listNodeDataSource.totalCount() || currentNodeIndex == undefined) {
              console.error('drag error, currentNodeIndex is not found in onDragStart');
              return;
            }

            this.listNodeDataSource.setIsInnerDrag(true);
            this.listNodeDataSource.setIsDrag(true);
            this.listNodeDataSource.setCurrentNodeInfo(currentNodeInfo);
            this.listNodeDataSource.setDraggingCurrentNodeId(currentNodeInfo.getNodeCurrentNodeId());
            this.listNodeDataSource.setDraggingParentNodeId(currentNodeInfo.getNodeParentNodeId());

            /* set the opacity of the dragging node. */
            let draggingNodeOpacity: number = DRAG_OPACITY;
            this.listNodeDataSource.setListItemOpacity(draggingNodeOpacity);
            this.listNodeDataSource.notifyDataChange(currentNodeIndex);

            /*
           * handle the situation of drag is too fast,it attribute a fault to OH.
           * OH has Solved on real machine.
           */
            if (currentItemNodeId != currentNodeInfo.getNodeCurrentNodeId()) {
              console.error('drag is too fast,it attribute a fault to OH');
              this.listNodeDataSource.setIsDrag(false);
              return;
            }
            return this.draggingPopup(currentNodeInfo);
          })
        }, item => JSON.stringify(item))
      }.width(this.listTreeViewWidth).height(this.listTreeViewHeight)

      /* Move the dragged node. */
      .onDragMove((event: DragEvent) => {
        if (this.isMultiPress) {
          console.error('drag error, a item has been dragged');
          return;
        }
        let nodeHeight: number = LIST_ITEM_HEIGHT;

        /* flag the position of the focus on the node. */
        let flag: Flag = Math.floor(event.getY() / (nodeHeight / FLAG_NUMBER)) % FLAG_NUMBER ? Flag.DOWN_FLAG : Flag.UP_FLAG;

        /* Record the node position to which the dragged node moves. */
        let index: number = Math.floor(event.getY() / nodeHeight);

        /* Handle the situation where the focus(index) exceeds the list area. */
        let isOverBorder: boolean = false;
        if (index >= this.listNodeDataSource.totalCount()) {
          flag = Flag.DOWN_FLAG;
          index = this.listNodeDataSource.totalCount() - 1;
          this.listNodeDataSource.getData(index).setIsOverBorder(true);
          isOverBorder = true;
        } else {
          this.listNodeDataSource.getData(index).setIsOverBorder(false);
        }

        let currentNodeInfo: NodeInfo = this.listNodeDataSource.getData(index);
        let currentNodeId: number = currentNodeInfo.getCurrentNodeId();

        /*
       * handle a situation that "draggingCurrentNodeId" is parent of "insertNodeCurrentNodeId";
       * do not perform some functions.
       */
        if (index != this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
          let isParentNodeOfInsertNode: boolean = this.listNodeDataSource.getIsParentOfInsertNode(currentNodeId);
          if (isParentNodeOfInsertNode) {
            this.listNodeDataSource.setPassIndex(index);
            let that = this;
            this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex.call(that,
              currentNodeId));
            this.listNodeDataSource.setFlag(Flag.NONE);
            return;
          }
        }
        this.listNodeDataSource.setLastPassIndex(index);

        /* Set the visibility of the flag line. */
        this.listNodeDataSource.setVisibility(flag, index, isOverBorder);

        /* Automatically HighLight one second delay and expand after two second delay. */
        if (currentNodeId != this.listNodeDataSource.getDraggingCurrentNodeId()) {
          let that = this;
          this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex.call(that, currentNodeId),
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
        let insertNodeIndex: number = this.listNodeDataSource.getPassIndex();
        let currentNodeIndex: number = this.dropSelectedIndex;

        if (currentNodeIndex - 1 > this.listNodeDataSource.totalCount() || currentNodeIndex == undefined) {
          console.error('drag error, currentNodeIndex is not found');
          this.listNodeDataSource.setIsDrag(false);
          return;
        }

        if (insertNodeIndex == this.listNodeDataSource.totalCount()) {
          console.log('need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1');
          insertNodeIndex -= 1;
        }

        let insertNodeInfo: NodeInfo = this.listNodeDataSource.getData(insertNodeIndex);
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

        let currentNodeInfo: NodeInfo = this.listNodeDataSource.getCurrentNodeInfo();
        let insertNodeParentNodeId: number = insertNodeInfo.getNodeParentNodeId();
        let draggingCurrentNodeId: number = this.listNodeDataSource.getDraggingCurrentNodeId();
        let draggingParentNodeId: number = this.listNodeDataSource.getDraggingParentNodeId();

        /*
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
          let that = this;
          let currentFocusIndex: number = findCurrentNodeIndex.call(that, draggingCurrentNodeId);
          this.listNodeDataSource.setClickIndex(currentFocusIndex);
          this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);
          return;
        }

        /* Collapse drag node. */
        if (this.listNodeDataSource.getExpandAndCollapseInfo(draggingCurrentNodeId) == NodeStatus.Expand) {
          let that = this;
          this.listNodeDataSource.expandAndCollapseNode(
            findCurrentNodeIndex.call(that, draggingCurrentNodeId));
        }

        /* Expand insert node. */
        if (this.listNodeDataSource.getExpandAndCollapseInfo(insertNodeCurrentNodeId) == NodeStatus.Collapse) {
          let that = this;
          let currentIndex: number = findCurrentNodeIndex.call(that, insertNodeCurrentNodeId);
          if (this.listNodeDataSource.ListNode[currentIndex].getIsHighLight()) {
            this.listNodeDataSource.expandAndCollapseNode(currentIndex);
          }
        }

        /* alter dragNode. */
        this.listNodeDataSource.setLastDelayHighLightId();
        if (draggingCurrentNodeId != insertNodeCurrentNodeId) {
          this.listNodeDataSource.alterDragNode(insertNodeParentNodeId, insertNodeCurrentNodeId, insertNodeInfo,
            draggingParentNodeId, draggingCurrentNodeId, currentNodeInfo);
          this.listNodeDataSource.hideLastLine();
        } else {
          /*the position of dragNode is equal with the position of insertNode. */
          this.listNodeDataSource.hideLastLine();
          this.listNodeDataSource.setLastPassId(draggingCurrentNodeId);
          this.listNodeDataSource.hideLastLine();
        }

        let that = this;
        let lastDelayHighLightIndex: number = findCurrentNodeIndex.call(that,
          this.listNodeDataSource.getLastDelayHighLightId());
        this.listNodeDataSource.setLastDelayHighLightIndex(lastDelayHighLightIndex);
        this.listNodeDataSource.clearLastTimeoutHighLight();
        this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
        this.listNodeDataSource.setIsDrag(false);

        /* set the position of focus. */
        let currentFocusIndex: number = findCurrentNodeIndex.call(that, draggingCurrentNodeId);
        this.listNodeDataSource.setClickIndex(currentFocusIndex);
        this.listNodeDataSource.handleEvent(Event.DRAG, currentFocusIndex);

        /* innerDrag is over. */
        this.listNodeDataSource.setIsInnerDrag(false);
        this.listNodeDataSource.notifyDataReload();
      })
    }
  }

  // Declare NodeParam
  export interface NodeParam {
    parentNodeId?: number,
    currentNodeId?: number,
    isFolder?: boolean,
    icon?: Resource,
    selectedIcon?: Resource,
    editIcon? : Resource,
    primaryTitle?: string,
    secondaryTitle?: number | string,
    menu?: () => void,
  }


  // Declare CallbackParam
  export interface CallbackParam {
    currentNodeId: number,
    parentNodeId?: number,
    childIndex?: number,
  }

  /**
   * Create a tree view control proxy class to generate a tree view.
   *
   * @since 10
   */
  export class TreeController {
    readonly ROOT_NODE_ID: number = -1;
    private nodeIdList: number[] = [];
    private listNodeUtils : ListNodeUtils = new ListNodeUtils();
    private listNodeDataSource : ListNodeDataSource = new ListNodeDataSource();

    /**
     * After the addNode interface is invoked,
     * this interface is used to obtain the initialization data of
     * the tree view component for creating a tree view component.
     *
     * @return ListNodeDataSource Obtains the initialization data of the tree view component.
     *
     * @since 10
     */
    public getListNodeDataSource(): ListNodeDataSource {
      return this.listNodeDataSource;
    }

    /**
     * Obtains the subNode information of the currently clicked node.
     *
     * @return Array Returns an array that stores the configuration information of each node.
     * If there is no child node, an empty array is returned.
     *
     * @since 10
     */
    public getClickNodeChildrenInfo(): Array<{ itemId: number, itemIcon: Resource, itemTitle: string,
    isFolder: boolean }> {
      let clickNodeId = this.listNodeDataSource.getClickNodeId();
      return this.listNodeUtils.getClickNodeChildrenInfo(clickNodeId);
    }

    public getChildrenId(): Array<number> {
      let clickNodeId = this.listNodeDataSource.getClickNodeId();
      return this.listNodeUtils.getClickChildId(clickNodeId);
    }

    /**
     * Delete a node.
     *
     * Register an ON_ITEM_DELETE callback through the EventBus mechanism to obtain the IDs of all deleted nodes.
     *
     * @since 10
     */
    public removeNode(): void {
      let clickNodeId = this.listNodeDataSource.getClickNodeId();
      let parentNodeId = this.listNodeUtils.findParentNodeId(clickNodeId);
      let removeNodeIdList: number[] = this.listNodeUtils.removeNode(clickNodeId,
        parentNodeId, this.listNodeUtils.traverseNodeBF);
      this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, parentNodeId, removeNodeIdList);
      this.nodeIdList.splice(this.nodeIdList.indexOf(clickNodeId), 1);
    }

    /**
     * Modify the node name.
     *
     * Register an ON_ITEM_MODIFY callback to obtain the ID, parent node ID, and node name of the modified node.
     *
     * @since 10
     */
    public modifyNode(): void {
      let clickNodeId = this.listNodeDataSource.getClickNodeId();
      this.listNodeDataSource.setItemVisibilityOnEdit(clickNodeId, MenuOperation.MODIFY_NODE);
    }

    /**
     * Add a node.
     *
     * Icon of a new node, which is generated by the system by default.
     * If there is a same-level node, the icon of the first node of the same-level node is used.
     * If no icon is set for the first node of the same-level node, the new node does not have an icon.
     * If there is no peer node, the icon of the parent node is used.
     * If no icon is set for the parent node, the new node does not have an icon.
     * The system generates an ID for the new node and registers an ON_ITEM_ADD callback through
     * the EventBus mechanism to obtain the ID, parent node ID, node name, normal icon, selected icon,
     * edit icon of the new node.
     *
     * @since 10
     */
    public add(): void {
      let clickNodeId: number = this.listNodeDataSource.getClickNodeId();
      if (clickNodeId == this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(clickNodeId)) {
        return;
      }
      let newNodeInfo: { isFolder: boolean, icon: Resource, selectedIcon: Resource, editIcon: Resource,
      menu: () =>any, secondaryTitle: number | string } =
        { isFolder: true, icon: null, selectedIcon: null, editIcon: null, menu: null, secondaryTitle: '' };
      newNodeInfo = this.listNodeUtils.getNewNodeInfo(clickNodeId);
      this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length - 1] + 1);
      let newNodeId: number = this.nodeIdList[this.nodeIdList.length - 1];
      this.listNodeUtils.addNewNodeId = newNodeId;
      this.listNodeUtils.addNode(clickNodeId, newNodeId,
        { isFolder: newNodeInfo.isFolder, icon: newNodeInfo.icon, selectedIcon: newNodeInfo.selectedIcon,
          editIcon: newNodeInfo.editIcon, primaryTitle: '新建文件夹', menu: newNodeInfo.menu,
          secondaryTitle: newNodeInfo.secondaryTitle });
      this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, clickNodeId, [newNodeId]);
    }

    public addNodeParam(nodeParam: NodeParam): TreeController {
      if (nodeParam.primaryTitle != null &&
        !this.listNodeUtils.checkMainTitleIsValid(nodeParam.primaryTitle)) {
        throw new Error('ListTreeNode[addNode]: ' +
          'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
        return null;
      }
      if (nodeParam.primaryTitle == null && nodeParam.icon == null) {
        throw new Error('ListTreeNode[addNode]: ' +
          'The icon and directory name cannot be empty at the same time.');
        return null;
      }
      if (nodeParam.currentNodeId === this.ROOT_NODE_ID || nodeParam.currentNodeId === null) {
        throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
        return null;
      }
      this.nodeIdList.push(nodeParam.currentNodeId);
      this.listNodeUtils.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam);
      return this;
    }

    /**
     * Initialize the interface of the tree view. This interface is used to generate ListNodeDataSource data.
     * addNode is only designed for initialization. It can only be invoked during initialization.
     *
     * A maximum of 50 directory levels can be added.
     *
     * @param parentNodeId ID of the parent node.
     * @param currentNodeId ID of the new node. The value cannot be -1 or null.
     * @param nodeParam Configuration information of the newly added node.
     *                  For details, see the comment description of NodeParam.
     * @return ListTreeNode Tree view component proxy class.
     *
     * @since 10
     */
    public addNode(nodeParam?: NodeParam): TreeController {
      if (nodeParam == null) {
        this.add();
      } else {
        if (nodeParam.primaryTitle != null &&
          !this.listNodeUtils.checkMainTitleIsValid(nodeParam.primaryTitle)) {
          throw new Error('ListTreeNode[addNode]: ' +
            'The directory name cannot contain the following characters\ /: *? "< > | or exceeds the maximum length.');
          return null;
        }
        if (nodeParam.primaryTitle == null && nodeParam.icon == null) {
          throw new Error('ListTreeNode[addNode]: ' +
            'The icon and directory name cannot be empty at the same time.');
          return null;
        }
        if (nodeParam.currentNodeId === this.ROOT_NODE_ID || nodeParam.currentNodeId === null) {
          throw new Error('ListTreeNode[addNode]: currentNodeId can not be -1 or null.');
          return null;
        }
        this.nodeIdList.push(nodeParam.currentNodeId);
        this.listNodeUtils.addNode(nodeParam.parentNodeId, nodeParam.currentNodeId, nodeParam);
        return this;
      }
    }

    /**
     * After the initialization is complete by calling the addNode interface,
     * call this interface to complete initialization.
     *
     * This interface must be called when you finish initializing the ListTreeView by addNode.
     * @since 10
     */
    public buildDone() {
      this.listNodeDataSource.init(this.listNodeUtils);
      this.nodeIdList.sort((a, b) => a - b);
    }

    public refreshNode(parentId: number, parentSubTitle: ResourceStr = '',
                       currentSubtitle: ResourceStr = '') {
      this.listNodeDataSource.setNodeSubtitlePara(parentId, parentSubTitle, currentSubtitle);
    }
  }
}