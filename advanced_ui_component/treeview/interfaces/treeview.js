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

var __decorate = this && this.__decorate || function (e, t, i, o) {
  var s, a = arguments.length, d = a < 3 ? t : null === o ? o = Object.getOwnPropertyDescriptor(t, i) : o;
  if ("object" == typeof Reflect && "function" == typeof Reflect.decorate) d = Reflect.decorate(e, t, i, o); else for (var r = e.length - 1;r >= 0; r--) (s = e[r]) && (d = (a < 3 ? s(d) : a > 3 ? s(t, i, d) : s(t, i)) || d);
  return a > 3 && d && Object.defineProperty(t, i, d), d
};
const IMAGE_NODE_HEIGHT = 24;
const IMAGE_NODE_WIDTH = 24;
const ITEM_WIDTH = 0;
const ITEM_HEIGHT = 48;
const ITEM_HEIGHT_INPUT = 32;
const BORDER_WIDTH_HAS = 2;
const BORDER_WIDTH_NONE = 0;
const NODE_HEIGHT = 48;
const LIST_ITEM_HEIGHT_NONE = 0;
const LIST_ITEM_HEIGHT = 48;
const SHADOW_OFFSETY = 10;
const FLAG_NUMBER = 2;
const DRAG_OPACITY = .4;
const DRAG_OPACITY_NONE = 1;
const FLAG_LINE_HEIGHT = "1.0vp";
const X_OFF_SET = "0vp";
const Y_OFF_SET = "2.75vp";
const Y_BOTTOM_OFF_SET = "-1.25vp";
const Y_BASE_PLATE_OFF_SET = "1.5vp";
const COLOR_SELECT = "#1A0A59F7";
const COLOR_IMAGE_ROW = "#00000000";
const COLOR_IMAGE_EDIT = "#FFFFFF";
const SHADOW_COLOR = "#00001E";
const GRAG_POP_UP_HEIGHT = "48";
const LEFT_PADDING = "8vp";
const RIGHT_PADDING = "8vp";
const FLOOR_MIN_WIDTH = "128vp";
const FLOOR_MAX_WIDTH = "208vp";
const TEXT_MIN_WIDTH = "80vp";
const TEXT_MAX_WIDTH = "160vp";
const MIN_WIDTH = "112vp";
const MAX_WIDTH = "192vp";
const TRANS_COLOR = "#00FFFFFF";

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

  var Event;
  !function(e){
    e[e.TOUCH_DOWN=0] = "TOUCH_DOWN";
    e[e.TOUCH_UP=1] = "TOUCH_UP";
    e[e.HOVER=3] = "HOVER";
    e[e.HOVER_OVER=4] = "HOVER_OVER";
    e[e.FOCUS=5] = "FOCUS";
    e[e.BLUR=6] = "BLUR";
    e[e.MOUSE_BUTTON_RIGHT=7] = "MOUSE_BUTTON_RIGHT";
    e[e.DRAG=8] = "DRAG"
  }(Event || (Event = {}));
  var MenuOperation;
  !function(e){
    e[e.ADD_NODE=0] = "ADD_NODE";
    e[e.REMOVE_NODE=1] = "REMOVE_NODE";
    e[e.MODIFY_NODE=2] = "MODIFY_NODE";
    e[e.COMMIT_NODE=3] = "COMMIT_NODE"
  }(MenuOperation || (MenuOperation = {}));
  var PopUpType;
  !function(e){
    e[e.HINTS=0] = "HINTS";
    e[e.WARNINGS=1] = "WARNINGS"
  }(PopUpType || (PopUpType = {}));
  var InputError;
  !function(e){
    e[e.INVALID_ERROR=0] = "INVALID_ERROR";
    e[e.LENGTH_ERROR=1] = "LENGTH_ERROR";
    e[e.NONE=2] = "NONE"
  }(InputError || (InputError = {}));
  var Flag;
  !function(e){
    e[e.DOWN_FLAG=0] = "DOWN_FLAG";
    e[e.UP_FLAG=1] = "UP_FLAG";
    e[e.NONE=2] = "NONE"
  }(Flag || (Flag = {}));
  
  export var NodeStatus;
  !function(e){
    e[e.Expand=0] = "Expand";
    e[e.Collapse=1] = "Collapse"
  }(NodeStatus || (NodeStatus = {}));
  
  export var InteractionStatus;
  !function(e){
    e[e.Normal=0] = "Normal";
    e[e.Selected=1] = "Selected";
    e[e.Edit=2] = "Edit";
    e[e.FinishEdit=3] = "FinishEdit";
    e[e.DragInsert=4] = "DragInsert";
    e[e.FinishDragInsert=5] = "FinishDragInsert"
  }(InteractionStatus || (InteractionStatus = {}));
  
  function findCurrentNodeIndex(e) {
    let t = 0;
    this.listNodeDataSource.ListNode.forEach((function (i, o) {
      i.getNodeCurrentNodeId() == e && (t = o)
    }));
    return t
  }
  
  let NodeInfo = class {
    constructor(e) {
      this.borderWidth = { has: 2, none: 0 };
      this.canShowFlagLine = !1;
      this.isOverBorder = !1;
      this.canShowBottomFlagLine = !1;
      this.isHighLight = !1;
      this.isModify = !1;
      this.childNodeInfo = e.getChildNodeInfo();
      this.nodeItem = { imageNode: null, inputText: null, mainTitleNode: null, imageCollapse: null };
      this.popUpInfo = {
        popUpIsShow: !1,
        popUpEnableArrow: !1,
        popUpColor: null,
        popUpText: "",
        popUpTextColor: null
      };
      this.nodeItem.imageNode = e.getNodeItem().imageNode;
      this.nodeItem.inputText = new TreeView.InputText;
      this.nodeItem.mainTitleNode = e.getNodeItem().mainTitleNode;
      this.nodeItem.imageCollapse = e.getNodeItem().imageCollapse;
      this.menu = e.menu;
      this.parentNodeId = e.parentNodeId;
      this.currentNodeId = e.currentNodeId;
      this.nodeHeight = 48;
      this.nodeLevel = e.nodeLevel;
      this.nodeLeftPadding = 12 * e.nodeLevel + 8;
      this.nodeColor = {
        id: -1,
        type: 10001,
        params: ["sys.color.ohos_id_color_background"],
        bundleName: "",
        moduleName: ""
      };
      this.nodeIsShow = !(this.nodeLevel > 0);
      this.listItemHeight = this.nodeLevel > 0 ? 0 : 48;
      this.isShowTitle = !0;
      this.isShowInputText = !1;
      this.isSelected = !1;
      this.status = {
        normal: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_background_transparent"],
          bundleName: "",
          moduleName: ""
        },
        hover: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_hover"],
          bundleName: "",
          moduleName: ""
        },
        press: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_click_effect"],
          bundleName: "",
          moduleName: ""
        },
        selected: "#1A0A59F7",
        highLight: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_activated"],
          bundleName: "",
          moduleName: ""
        }
      };
      this.nodeBorder = {
        borderWidth: 0,
        borderColor: {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_focused_outline"],
          bundleName: "",
          moduleName: ""
        },
        borderRadius: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_clicked"],
          bundleName: "",
          moduleName: ""
        }
      };
      this.flagLineLeftMargin = 12 * e.nodeLevel + 8;
      this.node = e;
      this.nodeParam = e.data
    }
  
    setFontColor(e) {
      this.fontColor = e
    }
  
    getFontColor() {
      return this.fontColor
    }
  
    getPopUpInfo() {
      return this.popUpInfo
    }
  
    setPopUpIsShow(e) {
      this.popUpInfo.popUpIsShow = e
    }
  
    setPopUpEnableArrow(e) {
      this.popUpInfo.popUpEnableArrow = e
    }
  
    setPopUpColor(e) {
      this.popUpInfo.popUpColor = e
    }
  
    setPopUpText(e) {
      this.popUpInfo.popUpText = e
    }
  
    setPopUpTextColor(e) {
      this.popUpInfo.popUpTextColor = e
    }
  
    getIsShowTitle() {
      return this.isShowTitle
    }
  
    getIsShowInputText() {
      return this.isShowInputText
    }
  
    setTitleAndInputTextStatus(e) {
      if (e) {
        this.isShowTitle = !1;
        this.isShowInputText = !0
      } else {
        this.isShowTitle = !0;
        this.isShowInputText = !1
      }
    }
  
    handleImageCollapseAfterAddNode(e) {
      if (e) {
        this.nodeItem.imageCollapse = new TreeView.ImageNode({
          id: -1,
          type: 2e4,
          params: ["app.media.ic_public_arrow_down_0"],
          bundleName: "",
          moduleName: ""
        }, null, null, {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_alpha_content_tertiary"],
          bundleName: "",
          moduleName: ""
        }, 24, 24);
        this.nodeItem.imageCollapse.itemRightMargin = {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_paragraph_margin_xs"],
          bundleName: "",
          moduleName: ""
        }
      } else this.nodeItem.imageCollapse = null
    }
  
    setNodeColor(e) {
      this.nodeColor = e
    }
  
    getNodeColor() {
      return this.nodeColor
    }
  
    setListItemHeight(e) {
      this.listItemHeight = e
    }
  
    getListItemHeight() {
      return this.listItemHeight
    }
  
    getNodeCurrentNodeId() {
      return this.currentNodeId
    }
  
    getNodeParentNodeId() {
      return this.parentNodeId
    }
  
    getNodeLeftPadding() {
      return this.nodeLeftPadding
    }
  
    getNodeHeight() {
      return this.nodeHeight
    }
  
    setNodeIsShow(e) {
      this.nodeIsShow = e
    }
  
    getNodeIsShow() {
      return this.nodeIsShow
    }
  
    getNodeItem() {
      return this.nodeItem
    }
  
    getNodeStatus() {
      return this.status
    }
  
    getNodeBorder() {
      return this.nodeBorder
    }
  
    setNodeBorder(e) {
      this.nodeBorder.borderWidth = e ? this.borderWidth.has : this.borderWidth.none
    }
  
    getChildNodeInfo() {
      return this.childNodeInfo
    }
  
    getCurrentNodeId() {
      return this.currentNodeId
    }
  
    getMenu() {
      return this.menu
    }
  
    setIsSelected(e) {
      this.isSelected = e
    }
  
    getIsSelected() {
      return this.isSelected
    }
  
    getNodeInfoData() {
      return this.nodeParam
    }
  
    getNodeInfoNode() {
      return this.node
    }
  
    getIsFolder() {
      return this.nodeParam.isFolder
    }
  
    setCanShowFlagLine(e) {
      this.canShowFlagLine = e
    }
  
    getCanShowFlagLine() {
      return this.canShowFlagLine
    }
  
    setFlagLineLeftMargin(e) {
      this.flagLineLeftMargin = 12 * e + 8
    }
  
    getFlagLineLeftMargin() {
      return this.flagLineLeftMargin
    }
  
    getNodeLevel() {
      return this.nodeLevel
    }
  
    setIsOverBorder(e) {
      this.isOverBorder = e
    }
  
    getIsOverBorder() {
      return this.isOverBorder
    }
  
    setCanShowBottomFlagLine(e) {
      this.canShowBottomFlagLine = e
    }
  
    getCanShowBottomFlagLine() {
      return this.canShowBottomFlagLine
    }
  
    setIsHighLight(e) {
      this.isHighLight = e
    }
  
    getIsHighLight() {
      return this.isHighLight
    }
  
    setIsModify(e) {
      this.isModify = e
    }
  
    getIsModify() {
      return this.isModify
    }
  };
  NodeInfo = __decorate([Observed], NodeInfo);
  
  export { NodeInfo };
  
  export var TreeView;
  !function(e){
    let t;
    !function(e){
      e.NODE_ADD = "NodeAdd";
      e.NODE_DELETE = "NodeDelete";
      e.NODE_MODIFY = "NodeModify";
      e.NODE_MOVE = "NodeMove";
      e.NODE_CLICK = "NodeClick"
    }(t = e.TreeListenType || (e.TreeListenType = {}));
  
    class i {
      constructor() {
        this._events = []
      }
  
      on(e, t) {
        if (Array.isArray(e)) for (let i = 0,
          o = e.length;i < o; i++) this.on(e[i], t); else (this._events[e] || (this._events[e] = [])).push(t)
      }
  
      once(e, t) {
        let i = this;
  
        function o() {
          i.off(e, o);
          t.apply(null, [e, t])
        }
  
        o.callback = t;
        this.on(e, o)
      }
  
      off(e, t) {
        null == e && (this._events = []);
        if (Array.isArray(e)) for (let i = 0, o = e.length;i < o; i++) this.off(e[i], t);
        const i = this._events[e];
        if (!i) return;
        null == t && (this._events[e] = null);
        let o, s = i.length;
        for (; s--; ) {
          o = i[s];
          if (o === t || o.callback === t) {
            i.splice(s, 1);
            break
          }
        }
      }
  
      emit(e, t) {
        let i = this;
        if (!this._events[e]) return;
        let o = [...this._events[e]];
        if (o) for (let e = 0, s = o.length;e < s; e++) try {
          o[e].apply(i, t)
        } catch (e) {
          new Error(e)
        }
      }
    }
  
    e.TreeListener = i;
  
    class o {
      constructor() {
        this.appEventBus = new i
      }
  
      static getInstance() {
        null == AppStorage.Get(this.APP_KEY_EVENT_BUS) && AppStorage.SetOrCreate(this.APP_KEY_EVENT_BUS, new o);
        return AppStorage.Get(this.APP_KEY_EVENT_BUS)
      }
  
      getTreeListener() {
        return this.appEventBus
      }
    }
  
    o.APP_KEY_EVENT_BUS = "app_key_event_bus";
    e.TreeListenerManager = o;
  
    class s {
      constructor() {
        this.listeners = []
      }
  
      totalCount() {
        return 0
      }
  
      getData(e) {
      }
  
      registerDataChangeListener(e) {
        this.listeners.indexOf(e) < 0 && this.listeners.push(e)
      }
  
      unregisterDataChangeListener(e) {
        const t = this.listeners.indexOf(e);
        t >= 0 && this.listeners.splice(t, 1)
      }
  
      notifyDataReload() {
        this.listeners.forEach((e => {
          e.onDataReloaded()
        }))
      }
  
      notifyDataAdd(e) {
        this.listeners.forEach((t => {
          t.onDataAdd(e)
        }))
      }
  
      notifyDataChange(e) {
        this.listeners.forEach((t => {
          t.onDataChange(e)
        }))
      }
  
      notifyDataDelete(e) {
        this.listeners.forEach((t => {
          t.onDataDelete(e)
        }))
      }
  
      notifyDataMove(e, t) {
        this.listeners.forEach((i => {
          i.onDataMove(e, t)
        }))
      }
    }
  
    class a {
      constructor(e) {
        this.data = e;
        this.nodeLevel = -1;
        this.parentNodeId = -1;
        this.nodeItem = { imageNode: null, mainTitleNode: null, imageCollapse: null };
        this.childNodeInfo = { isHasChildNode: !1, childNum: 0, allChildNum: 0 };
        this.menu = e.menu;
        e.icon && (this.nodeItem.imageNode = new r(e.icon, e.selectedIcon, e.editIcon, {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_alpha_content_fourth"],
          bundleName: "",
          moduleName: ""
        }, 24, 24));
        e.primaryTitle && (this.nodeItem.mainTitleNode = new n(e.primaryTitle));
        this.children = []
      }
  
      addImageCollapse(e) {
        if (e) {
          this.nodeItem.imageCollapse = new r({
            id: -1,
            type: 2e4,
            params: ["app.media.ic_public_arrow_right"],
            bundleName: "",
            moduleName: ""
          }, null, null, {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_alpha_content_tertiary"],
            bundleName: "",
            moduleName: ""
          }, 24, 24);
          this.nodeItem.imageCollapse.itemRightMargin = {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_paragraph_margin_xs"],
            bundleName: "",
            moduleName: ""
          }
        } else this.nodeItem.imageCollapse = null
      }
  
      getNodeItem() {
        return this.nodeItem
      }
  
      getChildNodeInfo() {
        return this.childNodeInfo
      }
  
      getMenu() {
        return this.menu
      }
  
      getCurrentNodeId() {
        return this.currentNodeId
      }
  
      getIsFolder() {
        return this.data.isFolder
      }
    }
  
    e.NodeItem = a;
  
    class d {
      constructor() {
      }
  
      set itemWidth(e) {
        this.width = e
      }
  
      get itemWidth() {
        return this.width
      }
  
      set itemHeight(e) {
        this.height = e
      }
  
      get itemHeight() {
        return this.height
      }
  
      set itemRightMargin(e) {
        this.rightMargin = e
      }
  
      get itemRightMargin() {
        return this.rightMargin
      }
    }
  
    class r extends d {
      constructor(e, t, i, o, s, a) {
        super();
        this.rightMargin = {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_elements_margin_horizontal_m"],
          bundleName: "",
          moduleName: ""
        };
        this.imageSource = e;
        this.imageNormalSource = e;
        this.imageSelectedSource = null != t ? t : this.imageNormalSource;
        this.imageEditSource = null != i ? i : this.imageNormalSource;
        this.imageOpacity = o;
        this.itemWidth = s;
        this.itemHeight = a;
        this.imageCollapseSource = e;
        this.imageCollapseDownSource = {
          id: -1,
          type: 2e4,
          params: ["app.media.ic_public_arrow_down_0"],
          bundleName: "",
          moduleName: ""
        };
        this.imageCollapseRightSource = {
          id: -1,
          type: 2e4,
          params: ["app.media.ic_public_arrow_right"],
          bundleName: "",
          moduleName: ""
        };
        this.isImageCollapse = !0
      }
  
      get source() {
        return this.imageSource
      }
  
      get normalSource() {
        return this.imageNormalSource
      }
  
      get selectedSource() {
        return this.imageSelectedSource
      }
  
      get editSource() {
        return this.imageEditSource
      }
  
      get opacity() {
        return this.imageOpacity
      }
  
      get noOpacity() {
        return 1
      }
  
      get collapseSource() {
        return this.imageCollapseSource
      }
  
      get isCollapse() {
        return this.isImageCollapse
      }
  
      changeImageCollapseSource(e) {
        e == NodeStatus.Expand ? this.imageCollapseSource = this.imageCollapseDownSource : e == NodeStatus.Collapse && (this.imageCollapseSource = this.imageCollapseRightSource)
      }
  
      setImageCollapseSource(e, t) {
        if (e === InteractionStatus.Edit || e === InteractionStatus.DragInsert) {
          this.imageCollapseDownSource = ARROW_DOWN_WITHE;
          this.imageCollapseRightSource = ARROW_RIGHT_WITHE;
          this.isImageCollapse = !1
        } else if (e === InteractionStatus.FinishEdit || e === InteractionStatus.FinishDragInsert) {
          this.imageCollapseDownSource = ARROW_DOWN;
          this.imageCollapseRightSource = ARROW_RIGHT;
          this.isImageCollapse = !0
        }
        this.imageCollapseSource = t == NodeStatus.Collapse ? this.imageCollapseRightSource : this.imageCollapseDownSource
      }
  
      setImageSource(e) {
        switch (e) {
          case InteractionStatus.Normal:
            this.imageSource = this.imageNormalSource;
            this.currentInteractionStatus = e;
            break;
          case InteractionStatus.Selected:
            if (this.currentInteractionStatus !== InteractionStatus.Edit) {
              this.imageSource = this.imageSelectedSource;
              this.currentInteractionStatus = e
            }
            break;
          case InteractionStatus.Edit:
            this.imageSource = this.imageEditSource;
            this.currentInteractionStatus = e;
            break;
          case InteractionStatus.FinishEdit:
            this.imageSource = this.imageSelectedSource;
            this.currentInteractionStatus = e;
            break;
          case InteractionStatus.DragInsert:
            this.imageSource = this.imageEditSource;
            this.currentInteractionStatus = e;
            break;
          case InteractionStatus.FinishDragInsert:
            this.imageSource = this.imageNormalSource;
            this.currentInteractionStatus = e
        }
      }
    }
  
    e.ImageNode = r;
  
    class n extends d {
      constructor(e) {
        super();
        this.mainTitleName = e;
        this.itemWidth = 0;
        this.itemHeight = 48;
        this.rightMargin = {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_paragraph_margin_xs"],
          bundleName: "",
          moduleName: ""
        };
        this.mainTitleSetting = {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Normal
        };
        this.showPopUpTimeout = 0
      }
  
      setMainTitleSelected(e) {
        this.mainTitleSetting = e ? {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary_activated"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Regular
        } : {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Normal
        }
      }
  
      set title(e) {
        this.mainTitleName = e
      }
  
      get title() {
        return this.mainTitleName
      }
  
      set popUpTimeout(e) {
        this.showPopUpTimeout = e
      }
  
      get popUpTimeout() {
        return this.showPopUpTimeout
      }
  
      get color() {
        return this.mainTitleSetting.fontColor
      }
  
      get size() {
        return this.mainTitleSetting.fontSize
      }
  
      get weight() {
        return this.mainTitleSetting.fontWeight
      }
  
      setMainTitleHighLight(e) {
        this.mainTitleSetting = e ? {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary_contrary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Regular
        } : {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Normal
        }
      }
    }
  
    e.MainTitleNode = n;
    e.InputText = class extends d {
      constructor() {
        super();
        this.statusColor = {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_background"],
          bundleName: "",
          moduleName: ""
        };
        this.editItemColor = {
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_emphasize"],
          bundleName: "",
          moduleName: ""
        };
        this.radius = {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_corner_radius_default_xs"],
          bundleName: "",
          moduleName: ""
        };
        this.itemWidth = 0;
        this.itemHeight = 32;
        this.rightMargin = {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_paragraph_margin_xs"],
          bundleName: "",
          moduleName: ""
        };
        this.inputTextSetting = {
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_text_primary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Normal
        }
      }
  
      get color() {
        return this.inputTextSetting.fontColor
      }
  
      get size() {
        return this.inputTextSetting.fontSize
      }
  
      get weight() {
        return this.inputTextSetting.fontWeight
      }
  
      get borderRadius() {
        return this.radius
      }
  
      get backgroundColor() {
        return this.statusColor
      }
  
      get editColor() {
        return this.editItemColor
      }
  
      get textInputStatusColor() {
        return this.status
      }
    };
  
    class l {
      constructor() {
        this.MaxNodeLevel = 50;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this._root = new a({});
        this._root.nodeLevel = -1;
        this._root.parentNodeId = -1;
        this._root.currentNodeId = -1
      }
  
      getNewNodeId() {
        return this.addNewNodeId
      }
  
      traverseNodeDF(e, t = this._root) {
        let i = [], o = !1;
        i.unshift(t);
        let s = i.shift();
        for (;!o && s; ) {
          o = !0 === e(s);
          if (!o) {
            i.unshift(...s.children);
            s = i.shift()
          }
        }
      }
  
      traverseNodeBF(e) {
        let t = [];
        let i = !1;
        t.push(this._root);
        let o = t.shift();
        for (;!i && o; ) {
          try {
            i = e(o)
          } catch (e) {
            e.name, e.message
          }
          if (!i) {
            t.push(...o.children);
            o = t.shift()
          }
        }
      }
  
      contains(e, t) {
        t.call(this, e,!0)
      }
  
      updateParentChildNum(e, t, i) {
        let o = e.parentNodeId;
        for (; o >= 0; ) this.traverseNodeDF((e => {
          if (e.currentNodeId == o) {
            e.getChildNodeInfo().allChildNum = t ? e.getChildNodeInfo().allChildNum + i : e.getChildNodeInfo()
              .allChildNum - i;
            o = e.parentNodeId;
            return !1
          }
          return !1
        }))
      }
  
      findParentNodeId(e) {
        let t = null;
        this.contains((function (i) {
          if (i.currentNodeId == e) {
            t = i;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        return t.parentNodeId
      }
  
      addNode(e, t, i) {
        if (null === this._root) {
          this._root = new a({});
          this._root.nodeLevel = -1;
          this._root.parentNodeId = -1;
          this._root.currentNodeId = -1
        }
        let o = null;
        this.contains((function (t) {
          if (t.currentNodeId == e) {
            o = t;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        if (o) {
          let s = new a(i);
          if (o.nodeLevel > this.MaxNodeLevel) throw new Error("ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.");
          s.nodeLevel = o.nodeLevel + 1;
          s.parentNodeId = e;
          s.currentNodeId = t;
          o.children.push(s);
          o.getChildNodeInfo().isHasChildNode = !0;
          o.getChildNodeInfo().childNum = o.children.length;
          o.getChildNodeInfo().allChildNum += 1;
          o.addImageCollapse(o.getChildNodeInfo().isHasChildNode);
          this.updateParentChildNum(o,!0, 1);
          return this
        }
        throw new Error("ListNodeUtils[addNode]: Parent node not found.")
      }
  
      findNodeIndex(e, t) {
        let i = this.INITIAL_INVALID_VALUE;
        for (let o = 0, s = e.length;o < s; o++) if (e[o].currentNodeId === t) {
          i = o;
          break
        }
        return i
      }
  
      freeNodeMemory(e, t) {
        let i = [];
        this.traverseNodeDF((function (e) {
          i.push(e);
          return !1
        }), e);
        i.forEach((e => {
          t.push(e.currentNodeId);
          e = null
        }))
      }
  
      removeNode(e, t, i) {
        let o = null;
        this.contains((function (e) {
          if (e.currentNodeId == t) {
            o = e;
            return !0
          }
          return !1
        }), i);
        if (o) {
          let t = [];
          let i = this.findNodeIndex(o.children, e);
          if (i < 0) throw new Error("Node does not exist.");
          {
            var s = o.children[i].getChildNodeInfo().allChildNum + 1;
            this.freeNodeMemory(o.children[i], t);
            let e = o.children.splice(i, 1);
            e = null;
            0 == o.children.length && o.addImageCollapse(!1)
          }
          o.getChildNodeInfo().childNum = o.children.length;
          o.getChildNodeInfo().allChildNum -= s;
          this.updateParentChildNum(o,!1, s);
          return t
        }
        throw new Error("Parent does not exist.")
      }
  
      getNewNodeInfo(e) {
        let t = null;
        this.contains((function (i) {
          if (i.currentNodeId == e) {
            t = i;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        let i = {
          isFolder: !0,
          icon: null,
          selectedIcon: null,
          editIcon: null,
          menu: null,
          secondaryTitle: ""
        };
        if (t) if (0 === t.children.length) if (null != t.getNodeItem().imageNode) {
          i.icon = t.getNodeItem().imageNode.normalSource;
          i.selectedIcon = t.getNodeItem().imageNode.selectedSource;
          i.editIcon = t.getNodeItem().imageNode.editSource;
          i.menu = t.getMenu()
        } else {
          i.icon = null;
          i.selectedIcon = null;
          i.editIcon = null;
          i.menu = t.getMenu()
        } else if (t.children.length > 0) if (null != t.getNodeItem().imageNode) {
          i.icon = null != t.children[0].getNodeItem().imageNode ? t.children[0].getNodeItem()
            .imageNode
            .normalSource : null;
          i.selectedIcon = null != t.children[0].getNodeItem().imageNode ? t.children[0].getNodeItem()
            .imageNode
            .selectedSource : null;
          i.editIcon = null != t.children[0].getNodeItem().imageNode ? t.children[0].getNodeItem()
            .imageNode
            .editSource : null;
          i.menu = t.children[0].getMenu()
        } else {
          i.icon = null;
          i.selectedIcon = null;
          i.editIcon = null;
          i.menu = t.children[0].getMenu()
        }
        return i
      }
  
      getClickChildId(e) {
        let t = null;
        this.contains((function (i) {
          if (i.currentNodeId == e) {
            t = i;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        if (t) {
          if (0 === t.children.length) return [];
          if (t.children.length > 0) {
            var i = new Array(t.children.length);
            for (let e = 0;e < i.length; e++) i[e] = 0;
            for (let e = 0;e < t.children.length && e < i.length; e++) i[e] = t.children[e].currentNodeId;
            return i
          }
        }
        return []
      }
  
      getClickNodeChildrenInfo(e) {
        let t = null;
        this.contains((function (i) {
          if (i.currentNodeId == e) {
            t = i;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        if (t) {
          if (0 === t.children.length) return [];
          if (t.children.length > 0) {
            var i = new Array(t.children.length);
            for (let e = 0;e < i.length; e++) i[e] = { itemId: null, itemIcon: null, itemTitle: null, isFolder: null };
            for (let e = 0;e < t.children.length && e < i.length; e++) {
              i[e].itemId = t.children[e].currentNodeId;
              t.children[e].getNodeItem().imageNode && (i[e].itemIcon = t.children[e].getNodeItem().imageNode.source);
              t.children[e].getNodeItem().mainTitleNode && (i[e].itemTitle = t.children[e].getNodeItem()
                .mainTitleNode
                .title);
              i[e].isFolder = t.children[e].getIsFolder()
            }
            return i
          }
        }
        return []
      }
  
      checkMainTitleIsValid(e) {
        let t = /^[\u4e00-\u9fa5]+$/;
        return!/[\\\/:*?"<>|]/.test(e) && !(t.test(e) && e.length > this.MAX_CN_LENGTH || !t.test(e) && e.length > this.MAX_EN_LENGTH)
      }
  
      dragTraverseNodeDF(e, t = this._root, i) {
        let o = [], s = !1;
        o.unshift(t);
        let a = o.shift();
        for (;!s && a; ) {
          s = !0 === e(a, i);
          if (!s) {
            o.unshift(...a.children);
            a = o.shift()
          }
        }
      }
  
      addDragNode(e, t, i, o, s) {
        if (null === this._root) {
          this._root = new a({});
          this._root.nodeLevel = this.INITIAL_INVALID_VALUE;
          this._root.parentNodeId = this.INITIAL_INVALID_VALUE;
          this._root.currentNodeId = this.INITIAL_INVALID_VALUE
        }
        let d = null;
        this.contains((function (t) {
          if (t.currentNodeId == e) {
            d = t;
            return !0
          }
          return !1
        }), this.traverseNodeBF);
        if (d) {
          let r = new a(s);
          if (d.nodeLevel > this.MaxNodeLevel) throw new Error("ListNodeUtils[addNode]: The level of the tree view cannot exceed 50.");
          r.nodeLevel = d.nodeLevel + 1;
          r.parentNodeId = e;
          r.currentNodeId = t;
          let n = this.INITIAL_INVALID_VALUE;
          if (d.children.length) {
            for (let e = 0;e < d.children.length; e++) if (d.children[e].getCurrentNodeId() == i) {
              n = e;
              break
            }
            o ? d.children.splice(n + 1, 0, r) : d.children.splice(n, 0, r)
          } else d.children.push(r);
          d.getChildNodeInfo().isHasChildNode = !0;
          d.getChildNodeInfo().childNum = d.children.length;
          d.getChildNodeInfo().allChildNum += 1;
          d.addImageCollapse(d.getChildNodeInfo().isHasChildNode);
          this.updateParentChildNum(d,!0, 1);
          return this
        }
        throw new Error("ListNodeUtils[addNode]: Parent node not found.")
      }
    }
  
    e.ListNodeUtils = l;
  
    class h extends s {
      constructor() {
        super(...arguments);
        this.ROOT_NODE_ID = -1;
        this.listNodeUtils = new l;
        this.listNode = [];
        this.INITIAL_INVALID_VALUE = -1;
        this.lastIndex = -1;
        this.thisIndex = -1;
        this.modifyNodeIndex = -1;
        this.modifyNodeId = -1;
        this.expandAndCollapseInfo = new Map;
        this.loadedNodeIdAndIndexMap = new Map;
        this.isTouchDown = !1;
        this.appEventBus = o.getInstance().getTreeListener();
        this.isInnerDrag = !1;
        this.isDrag = !1;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.draggingParentNodeId = this.INITIAL_INVALID_VALUE;
        this.currentNodeInfo = null;
        this.listItemOpacity = 1;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassId = this.INITIAL_INVALID_VALUE;
        this.thisPassIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.timeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutExpandId = this.INITIAL_INVALID_VALUE;
        this.timeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.lastTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.clearTimeoutHighLightId = this.INITIAL_INVALID_VALUE;
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayHighLightId = this.INITIAL_INVALID_VALUE;
        this.nodeIdAndSubtitleMap = new Map;
        this.flag = Flag.NONE;
        this.selectedParentNodeId = this.INITIAL_INVALID_VALUE;
        this.selectedParentNodeSubtitle = "";
        this.insertNodeSubtitle = "";
        this.currentFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.lastFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.addFocusNodeId = this.INITIAL_INVALID_VALUE;
        this.FLAG_LINE = {
          flagLineHeight: "1.0vp",
          flagLineColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_emphasize"],
            bundleName: "",
            moduleName: ""
          },
          xOffset: "0vp",
          yTopOffset: "2.75vp",
          yBottomOffset: "-1.25vp",
          yBasePlateOffset: "1.5vp"
        };
        this.DRAG_POPUP = {
          floorConstraintSize: { minWidth: "128vp", maxWidth: "208vp" },
          textConstraintSize: { minWidth1: "80vp", maxWidth1: "160vp", minWidth2: "112vp", maxWidth2: "192vp" },
          padding: { left: "8vp", right: "8vp" },
          backgroundColor: "#FFFFFF",
          height: "48",
          shadow: {
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_corner_radius_default_m"],
              bundleName: "",
              moduleName: ""
            },
            color: "#00001E",
            offsetX: 0,
            offsetY: 10
          },
          borderRadius: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_corner_radius_clicked"],
            bundleName: "",
            moduleName: ""
          },
          fontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body1"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Regular,
          imageOpacity: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_alpha_content_fourth"],
            bundleName: "",
            moduleName: ""
          }
        };
        this.subTitle = {
          normalFontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_secondary"],
            bundleName: "",
            moduleName: ""
          },
          highLightFontColor: {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary_contrary"],
            bundleName: "",
            moduleName: ""
          },
          fontSize: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          },
          fontWeight: FontWeight.Regular,
          margin: { left: "4vp", right: "24" }
        }
      }
  
      changeNodeColor(e, t) {
        this.listNode[e].setNodeColor(t);
        this.listNode[e].setNodeBorder(!1)
      }
  
      getNodeColor(e) {
        return this.listNode[e].getNodeColor()
      }
  
      handleFocusEffect(e, t) {
        this.listNode[e].getNodeIsShow() && this.listNode[e].setNodeBorder(t)
      }
  
      setImageSource(e, t) {
        let i = this.listNode[e];
        i.setIsSelected(t === InteractionStatus.Selected || t === InteractionStatus.Edit || t === InteractionStatus.FinishEdit);
        null != i.getNodeItem()
          .mainTitleNode && t != InteractionStatus.DragInsert && t != InteractionStatus.FinishDragInsert && i.getNodeItem()
          .mainTitleNode
          .setMainTitleSelected(t === InteractionStatus.Selected || t === InteractionStatus.FinishEdit);
        null != i.getNodeItem().imageNode && i.getNodeItem().imageNode.setImageSource(t)
      }
  
      setImageCollapseSource(e, t) {
        let i = this.listNode[e];
        null != i.getNodeItem().imageCollapse && i.getNodeItem()
          .imageCollapse
          .setImageCollapseSource(t, this.expandAndCollapseInfo.get(i.getCurrentNodeId()))
      }
  
      clearLastIndexStatus() {
        if (!(-1 == this.lastIndex || this.lastIndex >= this.listNode.length)) {
          this.setImageSource(this.lastIndex, InteractionStatus.Normal);
          this.changeNodeColor(this.lastIndex, this.listNode[this.lastIndex].getNodeStatus().normal);
          this.handleFocusEffect(this.lastIndex,!1);
          this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastIndex].getCurrentNodeId()))
        }
      }
  
      changeNodeStatus(e) {
        let t = e;
        let i = this.ListNode;
        let o = i[e].getCurrentNodeId();
        if (this.expandAndCollapseInfo.get(o) == NodeStatus.Expand) {
          this.expandAndCollapseInfo.set(o, NodeStatus.Collapse);
          i[t].getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Collapse)
        } else if (this.expandAndCollapseInfo.get(o) == NodeStatus.Collapse) {
          this.expandAndCollapseInfo.set(o, NodeStatus.Expand);
          i[t].getNodeItem().imageCollapse.changeImageCollapseSource(NodeStatus.Expand)
        }
      }
  
      handleExpandAndCollapse(e) {
        let t = e;
        let i = this.ListNode;
        let o = i[t].getCurrentNodeId();
        if (!this.expandAndCollapseInfo.has(o)) return;
        let s = this.expandAndCollapseInfo.get(o);
        if (i[t].getChildNodeInfo().isHasChildNode && s == NodeStatus.Collapse) {
          for (var a = 0;a < i[t].getChildNodeInfo().allChildNum; a++) {
            i[t + 1+a].setNodeIsShow(!1);
            i[t + 1+a].setListItemHeight(0)
          }
          this.notifyDataReload();
          return
        }
        let d = new Array(i[t].getChildNodeInfo().childNum);
        d[0] = t + 1;
        let r = 1;
        for (; r < i[t].getChildNodeInfo().childNum; ) {
          d[r] = d[r-1] + i[d[r-1]].getChildNodeInfo().allChildNum + 1;
          r++
        }
        if (s == NodeStatus.Expand) for (a = 0; a < d.length; a++) {
          i[d[a]].setNodeIsShow(!0);
          i[d[a]].setListItemHeight(48);
          let e = i[d[a]].getCurrentNodeId();
          this.expandAndCollapseInfo.get(e) == NodeStatus.Expand && this.handleExpandAndCollapse(d[a])
        }
        d = null;
        this.notifyDataReload()
      }
  
      init(e) {
        let t = 0;
        this.listNode = [];
        this.listNodeUtils = e;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((e => {
          if (e.currentNodeId >= 0) {
            var i = new NodeInfo(e);
            this.listNode.push(i);
            i.getChildNodeInfo()
              .isHasChildNode && this.expandAndCollapseInfo.set(i.getCurrentNodeId(), NodeStatus.Collapse);
            i.getNodeIsShow() && this.loadedNodeIdAndIndexMap.set(i.getCurrentNodeId(), t++);
            i.getIsFolder() && this.nodeIdAndSubtitleMap.set(i.getCurrentNodeId(), i.getNodeInfoData()
              .secondaryTitle || 0 == i.getNodeInfoData().secondaryTitle ? i.getNodeInfoData().secondaryTitle : "")
          }
          return !1
        }))
      }
  
      refreshRemoveNodeData(e, i) {
        let o = [];
        for (let t = 0;t < e.length; t++) for (let i = 0;i < this.listNode.length; i++) if (this.listNode[i].getNodeCurrentNodeId() == e[t]) {
          let s = this.listNode[i].getNodeCurrentNodeId();
          this.loadedNodeIdAndIndexMap.has(s) && o.push(this.loadedNodeIdAndIndexMap.get(s));
          let a = this.listNode.splice(i, 1);
          a = null;
          this.expandAndCollapseInfo.has(e[t]) && this.expandAndCollapseInfo.delete(e[t]);
          break
        }
        o.forEach((e => {
          this.notifyDataDelete(e);
          this.notifyDataChange(e)
        }));
        for (let e = 0;e < this.listNode.length; e++) if (this.listNode[e].getNodeCurrentNodeId() == i.getNodeCurrentNodeId()) {
          if (null == i.getNodeItem().imageCollapse) {
            this.listNode[e].handleImageCollapseAfterAddNode(!1);
            this.expandAndCollapseInfo.delete(i.getNodeCurrentNodeId());
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[e].getNodeCurrentNodeId()))
          }
          break
        }
        let s = { currentNodeId: i.getNodeCurrentNodeId(), parentNodeId: i.getNodeParentNodeId() };
        this.appEventBus.emit(t.NODE_DELETE, [s])
      }
  
      refreshAddNodeData(e) {
        var t;
        this.listNodeUtils.traverseNodeDF((i => {
          if (i.currentNodeId === e[0]) {
            t = new NodeInfo(i);
            return !0
          }
          return !1
        }));
        t.setIsModify(!0);
        let i = 0;
        for (let e = 0;e < this.listNode.length; e++) if (this.listNode[e].getNodeCurrentNodeId() == t.getNodeParentNodeId()) {
          i = e;
          if (null == this.listNode[e].getNodeItem().imageCollapse) {
            this.listNode[e].handleImageCollapseAfterAddNode(!0);
            this.notifyDataChange(i)
          } else this.expandAndCollapseInfo.get(this.listNode[e].getNodeCurrentNodeId()) == NodeStatus.Collapse && this.changeNodeStatus(i);
          this.listNode.splice(e + 1, 0, t);
          this.listNode[e+1].setTitleAndInputTextStatus(!0);
          this.listNode[e+1].setNodeIsShow(!0);
          this.listNode[e+1].setListItemHeight(48);
          this.setImageSource(e + 1, InteractionStatus.Edit);
          this.currentOperation = MenuOperation.ADD_NODE;
          this.notifyDataAdd(e + 1);
          this.notificationNodeInfo(e + 1, this.currentOperation);
          break
        }
        this.modifyNodeIndex = i + 1;
        this.expandAndCollapseInfo.set(t.getNodeParentNodeId(), NodeStatus.Expand);
        this.handleExpandAndCollapse(i)
      }
  
      refreshData(e, t, i, o) {
        let s;
        this.listNodeUtils = e;
        this.listNodeUtils.traverseNodeDF((e => {
          if (e.currentNodeId == i) {
            s = new NodeInfo(e);
            return !0
          }
          return !1
        }));
        if (t === MenuOperation.REMOVE_NODE) {
          this.nodeIdAndSubtitleMap.set(i, this.selectedParentNodeSubtitle);
          this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(i));
          this.refreshRemoveNodeData(o, s)
        }
        if (t === MenuOperation.ADD_NODE) {
          this.addFocusNodeId = o[0];
          this.nodeIdAndSubtitleMap.set(this.getClickNodeId(), this.selectedParentNodeSubtitle);
          this.nodeIdAndSubtitleMap.set(o[0], this.insertNodeSubtitle);
          this.refreshAddNodeData(o)
        }
      }
  
      setClickIndex(e) {
        this.thisIndex = e
      }
  
      getClickNodeId() {
        return this.thisIndex < 0 || this.thisIndex >= this.ListNode.length ? -1 : this.ListNode[this.thisIndex].getCurrentNodeId()
      }
  
      expandAndCollapseNode(e) {
        this.changeNodeStatus(e);
        this.handleExpandAndCollapse(e)
      }
  
      getIsTouchDown() {
        return this.isTouchDown
      }
  
      getLastIndex() {
        return this.lastIndex
      }
  
      handleEventDrag(e) {
        this.setImageSource(e, InteractionStatus.Normal);
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().normal);
        this.handleFocusEffect(e,!1);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.listNode[e].getCurrentNodeId()))
      }
  
      handleEvent(e, t) {
        if (this.isDrag) return;
        e !== Event.TOUCH_DOWN && e !== Event.TOUCH_UP && e !== Event.MOUSE_BUTTON_RIGHT || t != this.lastIndex && this.clearLastIndexStatus();
        let i = this.loadedNodeIdAndIndexMap.get(this.listNode[t].getCurrentNodeId());
        switch (e) {
          case Event.TOUCH_DOWN:
            this.isTouchDown = !0;
            this.changeNodeColor(t, this.listNode[t].getNodeStatus().press);
            this.notifyDataChange(i);
            break;
          case Event.TOUCH_UP: {
            this.isInnerDrag && (this.isInnerDrag = !1);
            this.isTouchDown = !1;
            let e = this.listNode[t];
            this.setImageSource(t, InteractionStatus.Selected);
            e.setFontColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_primary"],
              bundleName: "",
              moduleName: ""
            });
            this.lastIndex = t;
            this.changeNodeColor(t, e.getNodeStatus().selected);
            this.notifyDataChange(i);
            break
          }
          case Event.HOVER:
            if (this.getNodeColor(t) != this.listNode[t].getNodeStatus().selected) {
              this.changeNodeColor(t, this.listNode[t].getNodeStatus().hover);
              this.notifyDataChange(i)
            }
            break;
          case Event.HOVER_OVER:
            if (this.getNodeColor(t) != this.listNode[t].getNodeStatus().selected) {
              this.changeNodeColor(t, this.listNode[t].getNodeStatus().normal);
              this.notifyDataChange(i)
            }
            break;
          case Event.FOCUS:
            this.handleFocusEffect(t,!0);
            this.notifyDataChange(i);
            break;
          case Event.BLUR:
            this.handleFocusEffect(t,!1);
            this.notifyDataChange(i);
            break;
          case Event.MOUSE_BUTTON_RIGHT:
            this.lastIndex = t;
            this.finishEditing();
            break;
          case Event.DRAG:
            this.isTouchDown = !1;
            let e = this.listNode[t];
            this.setImageSource(t, InteractionStatus.Selected);
            this.lastIndex = t;
            this.changeNodeColor(t, e.getNodeStatus().selected);
            this.notifyDataChange(i)
        }
      }
  
      notificationNodeInfo(e, i) {
        if (i === MenuOperation.MODIFY_NODE) {
          let e = this.listNode[this.modifyNodeIndex];
          let i = { currentNodeId: e.getNodeCurrentNodeId(), parentNodeId: e.getNodeParentNodeId() };
          this.appEventBus.emit(t.NODE_MODIFY, [i])
        } else if (i === MenuOperation.ADD_NODE) {
          let i = this.listNode[e];
          null != i.getNodeItem().imageNode && i.getNodeItem().imageNode.source;
          null != i.getNodeItem().imageNode && i.getNodeItem().imageNode.selectedSource;
          null != i.getNodeItem().imageNode && i.getNodeItem().imageNode.editSource;
          let o = { currentNodeId: i.getNodeCurrentNodeId(), parentNodeId: i.getNodeParentNodeId() };
          this.appEventBus.emit(t.NODE_ADD, [o])
        }
      }
  
      finishEditing() {
        if (-1 != this.modifyNodeIndex) {
          this.setImageSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
          this.setImageCollapseSource(this.modifyNodeIndex, InteractionStatus.FinishEdit);
          this.listNode[this.modifyNodeIndex].setIsModify(!1);
          this.listNode[this.modifyNodeIndex].setTitleAndInputTextStatus(!1);
          this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
          this.notifyDataChange(this.modifyNodeIndex)
        }
      }
  
      setItemVisibilityOnEdit(e, t) {
        let i = -1;
        if (-1 != e) {
          if (t === MenuOperation.MODIFY_NODE) {
            for (let t = 0;t < this.listNode.length; t++) if (this.listNode[t].getCurrentNodeId() == e) {
              i = t;
              break
            }
            let t = this.listNode[i];
            t.setIsModify(!0);
            if (null === t.getNodeItem().mainTitleNode) return;
            this.currentOperation = MenuOperation.MODIFY_NODE;
            t.setTitleAndInputTextStatus(!0);
            this.setImageSource(i, InteractionStatus.Edit);
            this.setImageCollapseSource(i, InteractionStatus.Edit);
            this.modifyNodeIndex = i;
            t.getNodeItem().inputText && (null != t.getNodeItem().imageCollapse ? t.getNodeItem()
              .inputText
              .rightMargin = {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_text_paragraph_margin_xs"],
              bundleName: "",
              moduleName: ""
            } : t.getNodeItem().inputText.rightMargin = {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_elements_margin_horizontal_m"],
              bundleName: "",
              moduleName: ""
            });
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e))
          }
          i = e;
          if (t === MenuOperation.COMMIT_NODE) {
            let e = this.listNode[i];
            e.setTitleAndInputTextStatus(!1);
            e.setIsModify(!1);
            this.setImageSource(i, InteractionStatus.FinishEdit);
            this.setImageCollapseSource(i, InteractionStatus.FinishEdit);
            this.notificationNodeInfo(this.modifyNodeIndex, this.currentOperation);
            this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e.getCurrentNodeId()))
          }
        }
      }
  
      setPopUpInfo(e, t, i, o) {
        let s = this.listNode[o];
        s.setPopUpIsShow(i);
        let a = this.loadedNodeIdAndIndexMap.get(s.getCurrentNodeId());
        if (i) {
          if (e === PopUpType.HINTS) {
            if (null != s.getNodeItem().mainTitleNode) s.setPopUpText(s.getNodeItem().mainTitleNode.title); else {
              s.setPopUpText("");
              s.setPopUpIsShow(!1)
            }
            s.setPopUpEnableArrow(!1);
            s.setPopUpColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_background"],
              bundleName: "",
              moduleName: ""
            });
            s.setPopUpTextColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_secondary"],
              bundleName: "",
              moduleName: ""
            })
          } else if (e === PopUpType.WARNINGS && null != s.getNodeItem().inputText) {
            t === InputError.INVALID_ERROR ? s.setPopUpText("invalid error") : t === InputError.LENGTH_ERROR && s.setPopUpText("length error");
            s.setPopUpEnableArrow(!0);
            s.setPopUpColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_help_tip_bg"],
              bundleName: "",
              moduleName: ""
            });
            s.setPopUpTextColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_hint_contrary"],
              bundleName: "",
              moduleName: ""
            })
          }
          this.notifyDataChange(a)
        } else this.notifyDataChange(a)
      }
  
      setShowPopUpTimeout(e, t) {
        null != this.listNode[t].getNodeItem().mainTitleNode && (this.listNode[t].getNodeItem()
          .mainTitleNode
          .popUpTimeout = e);
        let i = this.loadedNodeIdAndIndexMap.get(this.listNode[t].getCurrentNodeId());
        this.notifyDataChange(i)
      }
  
      setMainTitleNameOnEdit(e, t) {
        this.modifyNodeIndex = e;
        if (null != this.listNode[e].getNodeItem().mainTitleNode) {
          this.listNode[e].getNodeItem().mainTitleNode.title = t;
          let i = this.loadedNodeIdAndIndexMap.get(this.listNode[e].getCurrentNodeId());
          this.notifyDataChange(i)
        }
      }
  
      get ListNode() {
        return this.listNode
      }
  
      totalCount() {
        let e = 0;
        let t = 0;
        this.loadedNodeIdAndIndexMap.clear();
        for (let i = 0;i < this.listNode.length; i++) if (this.listNode[i].getNodeIsShow()) {
          this.loadedNodeIdAndIndexMap.set(this.listNode[i].getCurrentNodeId(), t++);
          e++
        }
        return e
      }
  
      getData(e) {
        let t = 0;
        for (let i = 0;i < this.listNode.length; i++) if (this.listNode[i].getNodeIsShow()) {
          if (e == t) return this.listNode[i];
          t++
        }
        return null
      }
  
      addData(e, t) {
        this.listNode.splice(e, 0, t);
        this.notifyDataAdd(e)
      }
  
      pushData(e) {
        this.listNode.push(e);
        this.notifyDataAdd(this.listNode.length - 1)
      }
  
      setIsInnerDrag(e) {
        this.isInnerDrag = e
      }
  
      getIsInnerDrag() {
        return this.isInnerDrag
      }
  
      setIsDrag(e) {
        this.isDrag = e
      }
  
      getIsDrag() {
        return this.isDrag
      }
  
      setCurrentNodeInfo(e) {
        this.currentNodeInfo = e
      }
  
      getCurrentNodeInfo() {
        return this.currentNodeInfo
      }
  
      setDraggingParentNodeId(e) {
        this.draggingParentNodeId = e
      }
  
      getDraggingParentNodeId() {
        return this.draggingParentNodeId
      }
  
      getDraggingCurrentNodeId() {
        return this.draggingCurrentNodeId
      }
  
      setDraggingCurrentNodeId(e) {
        this.draggingCurrentNodeId = e
      }
  
      setListItemOpacity(e) {
        this.listItemOpacity = e
      }
  
      getListItemOpacity(e) {
        return e.getCurrentNodeId() == this.getDraggingCurrentNodeId() ? this.listItemOpacity : 1
      }
  
      getDragPopupPara() {
        return this.DRAG_POPUP
      }
  
      setLastPassIndex(e) {
        this.lastPassIndex = e
      }
  
      getLastPassIndex() {
        return this.lastPassIndex
      }
  
      getIsParentOfInsertNode(e) {
        let t = this.currentNodeInfo.getNodeInfoNode();
        let i = !1;
        this.listNodeUtils.traverseNodeDF((function (t) {
          if (t.currentNodeId == e) {
            i = !0;
            return !0
          }
          return !1
        }), t);
        return i
      }
  
      setPassIndex(e) {
        this.thisPassIndex = e
      }
  
      getPassIndex() {
        return this.thisPassIndex
      }
  
      clearTimeOutAboutDelayHighLightAndExpand(e) {
        if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
          let e = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
          let t = this;
          this.ListNode.forEach((function (e) {
            e.getNodeCurrentNodeId() == t.lastPassId && e.setCanShowFlagLine(!1)
          }));
          this.notifyDataChange(e)
        }
        if (this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId != this.lastTimeoutHighLightId) {
          clearTimeout(this.lastTimeoutHighLightId);
          if (this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE) {
            this.clearHighLight(this.lastDelayHighLightIndex);
            let e = this.loadedNodeIdAndIndexMap.get(this.listNode[this.lastDelayHighLightIndex].getCurrentNodeId());
            this.notifyDataChange(e)
          }
          this.clearTimeoutHighLightId = this.lastTimeoutHighLightId
        }
        this.lastTimeoutHighLightId = this.timeoutHighLightId;
        this.lastDelayHighLightIndex = e;
        if (this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId != this.lastTimeoutExpandId) {
          clearTimeout(this.lastTimeoutExpandId);
          this.clearTimeoutExpandId = this.lastTimeoutExpandId
        }
        this.lastTimeoutExpandId = this.timeoutExpandId;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE
      }
  
      clearHighLight(e) {
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().normal);
        this.changeNodeHighLightColor(e,!1);
        this.setImageSource(e, InteractionStatus.FinishDragInsert);
        this.setImageCollapseSource(e, InteractionStatus.FinishDragInsert);
        this.listNode[e].setIsHighLight(!1)
      }
  
      changeNodeHighLightColor(e, t) {
        this.listNode[e].getNodeItem()
          .mainTitleNode && this.listNode[e].getIsShowTitle() && this.listNode[e].getNodeItem()
          .mainTitleNode
          .setMainTitleHighLight(t)
      }
  
      setVisibility(e, t, i) {
        let o = this.thisPassIndex != t || this.flag != e;
        this.thisPassIndex = t;
        if ((o || i) && this.isInnerDrag) {
          this.flag = e;
          let i = this.getData(t).getCurrentNodeId();
          let o = this.expandAndCollapseInfo.get(i) == NodeStatus.Expand && this.flag == Flag.DOWN_FLAG ? this.getData(t)
            .getNodeLevel() + 1 : this.getData(t).getNodeLevel();
          if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
            let e = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
            let t = this;
            this.ListNode.forEach((function (e) {
              e.getNodeCurrentNodeId() == t.lastPassId && e.setCanShowFlagLine(!1)
            }));
            this.notifyDataChange(e)
          }
          if (this.flag == Flag.DOWN_FLAG && t < this.totalCount() - 1) {
            this.getData(t).setCanShowFlagLine(!1);
            this.getData(t + 1).setCanShowFlagLine(!0);
            this.getData(t).setCanShowBottomFlagLine(!1);
            this.getData(t + 1).setFlagLineLeftMargin(o);
            this.notifyDataChange(t);
            this.notifyDataChange(t + 1);
            this.lastPassId = this.getData(t + 1).getNodeCurrentNodeId()
          } else if (this.flag == Flag.UP_FLAG && t < this.totalCount() - 1) {
            this.getData(t).setCanShowFlagLine(!0);
            this.getData(t + 1).setCanShowFlagLine(!1);
            this.getData(t).setCanShowBottomFlagLine(!1);
            this.getData(t).setFlagLineLeftMargin(o);
            this.notifyDataChange(t);
            this.notifyDataChange(t + 1);
            this.lastPassId = this.getData(t).getNodeCurrentNodeId()
          } else if (t >= this.totalCount() - 1) {
            if (this.flag == Flag.DOWN_FLAG) {
              this.getData(t).setCanShowFlagLine(!1);
              this.getData(t).setCanShowBottomFlagLine(!0)
            } else {
              this.getData(t).setCanShowFlagLine(!0);
              this.getData(t).setCanShowBottomFlagLine(!1)
            }
            this.getData(t).setFlagLineLeftMargin(o);
            this.notifyDataChange(t);
            this.lastPassId = this.getData(t).getNodeCurrentNodeId()
          }
        }
      }
  
      delayHighLightAndExpandNode(e, t, i) {
        let o = e != this.lastDelayExpandIndex;
        let s = this.getData(i).getIsOverBorder();
        this.lastDelayExpandIndex = s ? this.INITIAL_INVALID_VALUE : e;
        if (s || o) {
          let o = this;
          if (!s && (!this.isInnerDrag || this.expandAndCollapseInfo.get(t) == NodeStatus.Collapse && this.isInnerDrag || !this.expandAndCollapseInfo.has(t) && this.listNode[e].getIsFolder())) {
            this.changeNodeColor(e, this.listNode[e].getNodeStatus().hover);
            this.notifyDataChange(i);
            let t = this.isInnerDrag ? 1e3 : 0;
            this.timeoutHighLightId = setTimeout((function () {
              o.delayHighLight(e)
            }), t)
          }
          if (s || this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId != this.lastTimeoutHighLightId) {
            clearTimeout(this.lastTimeoutHighLightId);
            if (this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE) {
              this.clearHighLight(this.lastDelayHighLightIndex);
              this.notifyDataReload()
            }
            this.clearTimeoutHighLightId = this.lastTimeoutHighLightId
          }
          this.lastTimeoutHighLightId = this.timeoutHighLightId;
          this.lastDelayHighLightIndex = e;
          if (!s && this.expandAndCollapseInfo.get(t) == NodeStatus.Collapse) {
            let t = this.getData(i).getNodeInfoNode().children[0].currentNodeId;
            let s = 2e3;
            this.timeoutExpandId = setTimeout((function () {
              o.clearHighLight(o.lastDelayHighLightIndex);
              o.alterFlagLineAndExpandNode(e, t)
            }), s)
          }
          if (s || this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId != this.lastTimeoutExpandId) {
            clearTimeout(this.lastTimeoutExpandId);
            this.clearTimeoutExpandId = this.lastTimeoutExpandId
          }
          this.lastTimeoutExpandId = this.timeoutExpandId
        }
      }
  
      delayHighLight(e) {
        let t = this;
        this.ListNode.forEach((function (e) {
          if (e.getNodeCurrentNodeId() == t.lastPassId) {
            e.setCanShowFlagLine(!1);
            e.setCanShowBottomFlagLine(!1)
          }
        }));
        this.changeNodeColor(e, this.listNode[e].getNodeStatus().highLight);
        this.listNode[e].setIsHighLight(!0);
        this.changeNodeHighLightColor(e,!0);
        this.setImageSource(e, InteractionStatus.DragInsert);
        this.setImageCollapseSource(e, InteractionStatus.DragInsert);
        this.notifyDataReload()
      }
  
      alterFlagLineAndExpandNode(e, t) {
        let i = this;
        this.ListNode.forEach((function (e) {
          if (e.getNodeCurrentNodeId() == i.lastPassId) {
            e.setCanShowFlagLine(!1);
            e.setCanShowBottomFlagLine(!1)
          }
        }));
        this.ListNode.forEach((function (e) {
          i.isInnerDrag && e.getNodeCurrentNodeId() == t && e.setCanShowFlagLine(!0)
        }));
        this.changeNodeStatus(e);
        this.handleExpandAndCollapse(e);
        this.lastPassId = t
      }
  
      hideLastLine() {
        if (this.lastPassId != this.INITIAL_INVALID_VALUE && this.loadedNodeIdAndIndexMap.has(this.lastPassId)) {
          let e = this;
          this.ListNode.forEach((function (t) {
            if (t.getNodeCurrentNodeId() == e.lastPassId) {
              t.setCanShowFlagLine(!1);
              t.setCanShowBottomFlagLine(!1)
            }
          }));
          let t = this.loadedNodeIdAndIndexMap.get(this.lastPassId);
          this.notifyDataChange(t)
        }
      }
  
      clearLastTimeoutHighLight() {
        if (this.lastTimeoutHighLightId != this.INITIAL_INVALID_VALUE && this.clearTimeoutHighLightId != this.lastTimeoutHighLightId) {
          clearTimeout(this.lastTimeoutHighLightId);
          this.lastDelayHighLightIndex != this.INITIAL_INVALID_VALUE && this.clearHighLight(this.lastDelayHighLightIndex)
        }
      }
  
      clearLastTimeoutExpand() {
        this.lastTimeoutExpandId != this.INITIAL_INVALID_VALUE && this.clearTimeoutExpandId != this.lastTimeoutExpandId && clearTimeout(this.lastTimeoutExpandId)
      }
  
      getSubtitle(e) {
        return this.nodeIdAndSubtitleMap.has(e) ? "number" == typeof this.nodeIdAndSubtitleMap.get(e) ? this.nodeIdAndSubtitleMap.get(e)
          .toString() : this.nodeIdAndSubtitleMap.get(e) : ""
      }
  
      hasSubtitle(e) {
        return this.nodeIdAndSubtitleMap.has(e)
      }
  
      initialParameterAboutDelayHighLightAndExpandIndex() {
        this.lastDelayHighLightIndex = this.INITIAL_INVALID_VALUE;
        this.lastDelayExpandIndex = this.INITIAL_INVALID_VALUE;
        this.lastPassIndex = this.INITIAL_INVALID_VALUE;
        this.draggingCurrentNodeId = this.INITIAL_INVALID_VALUE;
        this.flag = Flag.NONE
      }
  
      refreshSubtitle(e) {
        this.nodeIdAndSubtitleMap.set(this.selectedParentNodeId, this.selectedParentNodeSubtitle);
        this.nodeIdAndSubtitleMap.set(e, this.insertNodeSubtitle);
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(this.selectedParentNodeId));
        this.notifyDataChange(this.loadedNodeIdAndIndexMap.get(e))
      }
  
      setNodeSubtitlePara(e, t, i) {
        this.selectedParentNodeId = e;
        this.selectedParentNodeSubtitle = t;
        this.insertNodeSubtitle = i
      }
  
      getInsertNodeSubtitle() {
        return this.insertNodeSubtitle
      }
  
      getExpandAndCollapseInfo(e) {
        return this.expandAndCollapseInfo.get(e)
      }
  
      getLastDelayHighLightId() {
        return this.lastDelayHighLightId
      }
  
      setLastDelayHighLightId() {
        this.ListNode.forEach(((e, t) => {
          t == this.lastDelayHighLightIndex && (this.lastDelayHighLightId = e.getCurrentNodeId())
        }))
      }
  
      setLastPassId(e) {
        this.lastPassId = e
      }
  
      setLastDelayHighLightIndex(e) {
        this.lastDelayHighLightIndex = e
      }
  
      alterDragNode(e, i, o, s, a, d) {
        let r = [];
        let n = e;
        let l = a;
        let h = d.getNodeInfoData();
        let N = null;
        let c = d.getNodeInfoNode();
        let u = !1;
        let I = this.INITIAL_INVALID_VALUE;
        let g = this.INITIAL_INVALID_VALUE;
        let p = this.flag == Flag.DOWN_FLAG;
        g = this.getChildIndex(s, a);
        I = this.getChildIndex(e, i);
        I = e != s ? p ? I + 1 : I : I > g ? p ? I : I - 1 : p ? I + 1 : I;
        for (let e = 0;e < this.listNode.length; e++) if (this.listNode[e].getCurrentNodeId() == i) {
          u = this.listNode[e].getIsHighLight();
          if (this.flag == Flag.DOWN_FLAG && this.expandAndCollapseInfo.get(i) == NodeStatus.Expand) {
            n = i;
            I = 0
          } else if (this.flag == Flag.UP_FLAG && this.expandAndCollapseInfo.get(i) == NodeStatus.Expand && 0 == this.listNode[e].getCanShowFlagLine()) {
            n = i;
            I = 0
          } else if (u) {
            n = i;
            I = 0
          }
          break
        }
        let m = { currentNodeId: l, parentNodeId: n, childIndex: I };
        this.appEventBus.emit(t.NODE_MOVE, [m]);
        r.push({ parentId: n, currentId: l, data: h });
        let A = null;
        this.listNodeUtils.dragTraverseNodeDF((function (e, t) {
          if (e) {
            A = e;
            n = A.parentNodeId;
            l = A.currentNodeId;
            for (let e = 0;e < t.length; e++) if (t[e].getNodeCurrentNodeId() == l) {
              N = t[e];
              break
            }
            h = N.getNodeInfoData();
            n != s && r.push({ parentId: n, currentId: l, data: h });
            return !1
          }
          return !1
        }), c, this.listNode);
        this.listNodeUtils.removeNode(a, s, this.listNodeUtils.traverseNodeBF);
        let S = i;
        let _ = p;
        if (this.expandAndCollapseInfo.get(i) == NodeStatus.Expand) {
          _ = !1;
          this.listNode.forEach((e => {
            e.getCurrentNodeId() == i && 0 == e.getCanShowFlagLine() && (S = e.getNodeInfoNode()
              .children
              .length ? e.getNodeInfoNode().children[0].currentNodeId : this.INITIAL_INVALID_VALUE)
          }))
        } else !this.expandAndCollapseInfo.get(i) && u && this.expandAndCollapseInfo.set(i, NodeStatus.Expand);
        this.listNodeUtils.addDragNode(r[0].parentId, r[0].currentId, S, _, r[0].data);
        for (let e = 1;e < r.length; e++) this.listNodeUtils.addNode(r[e].parentId, r[e].currentId, r[e].data);
        for (let e = 0;e < this.listNode.length; e++) if (this.listNode[e].getCurrentNodeId() == s && null == this.listNode[e].getNodeInfoNode()
          .getNodeItem()
          .imageCollapse) {
          this.listNode[e].handleImageCollapseAfterAddNode(!1);
          this.expandAndCollapseInfo.delete(s);
          break
        }
        let f = [...this.listNode];
        this.reloadListNode(this.listNodeUtils, f)
      }
  
      reloadListNode(e, t) {
        let i = 0;
        this.listNode = [];
        this.listNodeUtils = e;
        this.loadedNodeIdAndIndexMap.clear();
        this.listNodeUtils.traverseNodeDF((e => {
          if (e.currentNodeId >= 0) {
            var o = new NodeInfo(e);
            this.listNode.push(o);
            this.expandAndCollapseInfo.get(e.currentNodeId) == NodeStatus.Expand ? o.getNodeItem()
              .imageCollapse
              .changeImageCollapseSource(NodeStatus.Expand) : this.expandAndCollapseInfo.get(e.currentNodeId) == NodeStatus.Collapse && o.getNodeItem()
              .imageCollapse
              .changeImageCollapseSource(NodeStatus.Collapse);
            for (let e = 0;e < t.length; e++) if (t[e].getCurrentNodeId() == o.getCurrentNodeId()) {
              o.setNodeIsShow(t[e].getNodeIsShow());
              o.setListItemHeight(t[e].getListItemHeight());
              o.getNodeItem().mainTitleNode && o.getIsShowTitle() && (o.getNodeItem()
                .mainTitleNode
                .title = t[e].getNodeItem().mainTitleNode.title);
              break
            }
            o.getNodeIsShow() && this.loadedNodeIdAndIndexMap.set(o.getCurrentNodeId(), i++)
          }
          return !1
        }))
      }
  
      getFlagLine() {
        return this.FLAG_LINE
      }
  
      getVisibility(e) {
        let t = this.loadedNodeIdAndIndexMap.get(e.getCurrentNodeId()) - 1;
        if (t > this.INITIAL_INVALID_VALUE) {
          let i = this.getData(t);
          return 1 != e.getCanShowFlagLine() || e.getIsHighLight() || i.getIsHighLight() ? Visibility.Hidden : Visibility.Visible
        }
        return 1 != e.getCanShowFlagLine() || e.getIsHighLight() ? Visibility.Hidden : Visibility.Visible
      }
  
      getSubTitlePara() {
        return this.subTitle
      }
  
      getIsFolder(e) {
        return!!this.loadedNodeIdAndIndexMap.has(e) && this.getData(this.loadedNodeIdAndIndexMap.get(e)).getIsFolder()
      }
  
      getSubTitleFontColor(e) {
        return e ? this.subTitle.highLightFontColor : this.subTitle.normalFontColor
      }
  
      getChildIndex(e, t) {
        let i = this.INITIAL_INVALID_VALUE;
        this.listNodeUtils.traverseNodeBF((function (o) {
          if (o.getCurrentNodeId() == e) {
            o.children.forEach(((e, o) => {
              e.getCurrentNodeId() == t && (i = o)
            }));
            return !0
          }
          return !1
        }));
        return i
      }
  
      setCurrentFocusNodeId(e) {
        this.currentFocusNodeId = e
      }
  
      getCurrentFocusNodeId() {
        return this.currentFocusNodeId
      }
  
      setLastFocusNodeId(e) {
        this.lastFocusNodeId = e
      }
  
      getLastFocusNodeId() {
        return this.lastFocusNodeId
      }
  
      getAddFocusNodeId() {
        return this.addFocusNodeId
      }
  
      setFlag(e) {
        this.flag = e
      }
    }
  
    e.ListNodeDataSource = h;
  
    class N extends ViewPU {
      constructor(e, t, i, s = -1) {
        super(e, i, s);
        this.__nodeList = new ObservedPropertyObjectPU([], this, "nodeList");
        this.listNodeDataSource = void 0;
        this.__item = new ObservedPropertyObjectPU(null, this, "item");
        this.treeController = void 0;
        this.__touchCount = new ObservedPropertySimplePU(0, this, "touchCount");
        this.__dropSelectedIndex = new ObservedPropertySimplePU(0, this, "dropSelectedIndex");
        this.__viewLastIndex = new ObservedPropertySimplePU(-1, this, "viewLastIndex");
        this.__listItemBgColor = new ObservedPropertyObjectPU({
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_background_transparent"],
          bundleName: "",
          moduleName: ""
        }, this, "listItemBgColor");
        this.listTreeViewMenu = null;
        this.MAX_CN_LENGTH = 254;
        this.MAX_EN_LENGTH = 255;
        this.INITIAL_INVALID_VALUE = -1;
        this.MAX_TOUCH_DOWN_COUNT = 0;
        this.isMultiPress = !1;
        this.touchDownCount = this.INITIAL_INVALID_VALUE;
        this.appEventBus = o.getInstance().getTreeListener();
        this.itemPadding = {
          left: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_card_margin_start"],
            bundleName: "",
            moduleName: ""
          },
          right: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_card_margin_end"],
            bundleName: "",
            moduleName: ""
          },
          top: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_margin_vertical"],
            bundleName: "",
            moduleName: ""
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_margin_vertical"],
            bundleName: "",
            moduleName: ""
          }
        };
        this.textInputPadding = { left: "0vp", right: "0vp", top: "0vp", bottom: "0vp" };
        this.setInitiallyProvidedValue(t)
      }
  
      setInitiallyProvidedValue(e) {
        void 0 !== e.nodeList && (this.nodeList = e.nodeList);
        void 0 !== e.listNodeDataSource && (this.listNodeDataSource = e.listNodeDataSource);
        void 0 !== e.item && (this.item = e.item);
        void 0 !== e.treeController && (this.treeController = e.treeController);
        void 0 !== e.touchCount && (this.touchCount = e.touchCount);
        void 0 !== e.dropSelectedIndex && (this.dropSelectedIndex = e.dropSelectedIndex);
        void 0 !== e.viewLastIndex && (this.viewLastIndex = e.viewLastIndex);
        void 0 !== e.listItemBgColor && (this.listItemBgColor = e.listItemBgColor);
        void 0 !== e.listTreeViewMenu && (this.listTreeViewMenu = e.listTreeViewMenu);
        void 0 !== e.MAX_CN_LENGTH && (this.MAX_CN_LENGTH = e.MAX_CN_LENGTH);
        void 0 !== e.MAX_EN_LENGTH && (this.MAX_EN_LENGTH = e.MAX_EN_LENGTH);
        void 0 !== e.INITIAL_INVALID_VALUE && (this.INITIAL_INVALID_VALUE = e.INITIAL_INVALID_VALUE);
        void 0 !== e.MAX_TOUCH_DOWN_COUNT && (this.MAX_TOUCH_DOWN_COUNT = e.MAX_TOUCH_DOWN_COUNT);
        void 0 !== e.isMultiPress && (this.isMultiPress = e.isMultiPress);
        void 0 !== e.touchDownCount && (this.touchDownCount = e.touchDownCount);
        void 0 !== e.appEventBus && (this.appEventBus = e.appEventBus);
        void 0 !== e.itemPadding && (this.itemPadding = e.itemPadding);
        void 0 !== e.textInputPadding && (this.textInputPadding = e.textInputPadding)
      }
  
      updateStateVars(e) {
      }
  
      purgeVariableDependenciesOnElmtId(e) {
        this.__nodeList.purgeDependencyOnElmtId(e);
        this.__item.purgeDependencyOnElmtId(e);
        this.__touchCount.purgeDependencyOnElmtId(e);
        this.__dropSelectedIndex.purgeDependencyOnElmtId(e);
        this.__viewLastIndex.purgeDependencyOnElmtId(e);
        this.__listItemBgColor.purgeDependencyOnElmtId(e)
      }
  
      aboutToBeDeleted() {
        this.__nodeList.aboutToBeDeleted();
        this.__item.aboutToBeDeleted();
        this.__touchCount.aboutToBeDeleted();
        this.__dropSelectedIndex.aboutToBeDeleted();
        this.__viewLastIndex.aboutToBeDeleted();
        this.__listItemBgColor.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal()
      }
  
      get nodeList() {
        return this.__nodeList.get()
      }
  
      set nodeList(e) {
        this.__nodeList.set(e)
      }
  
      get item() {
        return this.__item.get()
      }
  
      set item(e) {
        this.__item.set(e)
      }
  
      get touchCount() {
        return this.__touchCount.get()
      }
  
      set touchCount(e) {
        this.__touchCount.set(e)
      }
  
      get dropSelectedIndex() {
        return this.__dropSelectedIndex.get()
      }
  
      set dropSelectedIndex(e) {
        this.__dropSelectedIndex.set(e)
      }
  
      get viewLastIndex() {
        return this.__viewLastIndex.get()
      }
  
      set viewLastIndex(e) {
        this.__viewLastIndex.set(e)
      }
  
      get listItemBgColor() {
        return this.__listItemBgColor.get()
      }
  
      set listItemBgColor(e) {
        this.__listItemBgColor.set(e)
      }
  
      aboutToAppear() {
        this.listNodeDataSource = this.treeController.getListNodeDataSource();
        this.nodeList = this.treeController.getListNodeDataSource().listNode;
        this.item = this.treeController.getListNodeDataSource().listNode
      }
  
      checkInvalidPattern(e) {
        return /[\\\/:*?"<>|]/.test(e)
      }
  
      checkIsAllCN(e) {
        return /^[\u4e00-\u9fa5]+$/.test(e)
      }
  
      popupForShowTitle(e, t, i, o = null) {
        this.observeComponentCreation(((e, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.backgroundColor(t);
          Row.border({
            radius: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
              bundleName: "",
              moduleName: ""
            }
          });
          Row.padding({
            left: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
              bundleName: "",
              moduleName: ""
            },
            right: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
              bundleName: "",
              moduleName: ""
            },
            top: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_card_margin_middle"],
              bundleName: "",
              moduleName: ""
            },
            bottom: {
              id: -1,
              type: 10002,
              params: ["sys.float.ohos_id_card_margin_middle"],
              bundleName: "",
              moduleName: ""
            }
          });
          i || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, o) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          Text.create(e);
          Text.fontSize({
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_text_size_body2"],
            bundleName: "",
            moduleName: ""
          });
          Text.fontWeight("regular");
          Text.fontColor(i);
          o || Text.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        Text.pop();
        Row.pop()
      }
  
      builder(e = null) {
        this.listTreeViewMenu.bind(this)()
      }
  
      draggingPopup(e, t = null) {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          Row.create();
          Row.constraintSize({
            minWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.minWidth,
            maxWidth: this.listNodeDataSource.getDragPopupPara().floorConstraintSize.maxWidth
          });
          Row.height(this.listNodeDataSource.getDragPopupPara().height);
          Row.backgroundColor(this.listNodeDataSource.getDragPopupPara().backgroundColor);
          Row.padding({
            left: this.listNodeDataSource.getDragPopupPara().padding.left,
            right: this.listNodeDataSource.getDragPopupPara().padding.right
          });
          Row.shadow({
            radius: this.listNodeDataSource.getDragPopupPara().shadow.radius,
            color: this.listNodeDataSource.getDragPopupPara().shadow.color,
            offsetY: this.listNodeDataSource.getDragPopupPara().shadow.offsetY
          });
          Row.borderRadius(this.listNodeDataSource.getDragPopupPara().borderRadius);
          t || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          If.create();
          e.getNodeItem().imageNode ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((t, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(t);
              Row.create();
              Row.backgroundColor("#00000000");
              Row.margin({ right: e.getNodeItem().imageNode.itemRightMargin });
              Row.height(e.getNodeItem().imageNode.itemHeight);
              Row.width(e.getNodeItem().imageNode.itemWidth);
              i || Row.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            this.observeComponentCreation(((t, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(t);
              Image.create(e.getNodeItem().imageNode.normalSource);
              Image.objectFit(ImageFit.Contain);
              Image.height(e.getNodeItem().imageNode.itemHeight);
              Image.width(e.getNodeItem().imageNode.itemWidth);
              Image.opacity(this.listNodeDataSource.getDragPopupPara().imageOpacity);
              i || Image.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Row.pop()
          })) : If.branchId(1);
          i || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        this.observeComponentCreation(((t, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          Row.create();
          Row.constraintSize({
            minWidth: e.getNodeItem().imageNode ? this.listNodeDataSource.getDragPopupPara()
              .textConstraintSize
              .minWidth1 : this.listNodeDataSource.getDragPopupPara().textConstraintSize.minWidth2,
            maxWidth: e.getNodeItem().imageNode ? this.listNodeDataSource.getDragPopupPara()
              .textConstraintSize
              .maxWidth1 : this.listNodeDataSource.getDragPopupPara().textConstraintSize.maxWidth2
          });
          i || Row.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        this.observeComponentCreation(((t, i) => {
          ViewStackProcessor.StartGetAccessRecordingFor(t);
          If.create();
          e.getNodeItem().mainTitleNode && e.getIsShowTitle() ? this.ifElseBranchUpdateFunction(0, (() => {
            this.observeComponentCreation(((t, i) => {
              ViewStackProcessor.StartGetAccessRecordingFor(t);
              Text.create(e.getNodeItem().mainTitleNode.title);
              Text.maxLines(1);
              Text.fontSize(e.getNodeItem().mainTitleNode.size);
              Text.fontColor(this.listNodeDataSource.getDragPopupPara().fontColor);
              Text.fontWeight(this.listNodeDataSource.getDragPopupPara().fontWeight);
              Text.textOverflow({ overflow: TextOverflow.Ellipsis });
              i || Text.pop();
              ViewStackProcessor.StopGetAccessRecording()
            }));
            Text.pop()
          })) : If.branchId(1);
          i || If.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        If.pop();
        Row.pop();
        Row.pop()
      }
  
      clearLastIndexColor() {
        if (!(-1 == this.viewLastIndex || this.viewLastIndex >= this.nodeList.length)) {
          this.setImageSources(this.viewLastIndex, InteractionStatus.Normal);
          this.nodeList[this.viewLastIndex].setNodeColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_background_transparent"],
            bundleName: "",
            moduleName: ""
          });
          this.nodeList[this.viewLastIndex].fontColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          };
          this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_background_transparent"],
            bundleName: "",
            moduleName: ""
          });
          this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = {
            id: -1,
            type: 10001,
            params: ["sys.color.ohos_id_color_primary"],
            bundleName: "",
            moduleName: ""
          };
          this.listNodeDataSource.listNode[this.viewLastIndex].setIsSelected(!1);
          this.listNodeDataSource.setImageSource(this.viewLastIndex, InteractionStatus.Normal)
        }
      }
  
      setImageSources(e, t) {
        let i = this.nodeList[e];
        i.setIsSelected(t === InteractionStatus.Selected || t === InteractionStatus.Edit || t === InteractionStatus.FinishEdit);
        null != i.getNodeItem()
          .mainTitleNode && t != InteractionStatus.DragInsert && t != InteractionStatus.FinishDragInsert && i.getNodeItem()
          .mainTitleNode
          .setMainTitleSelected(t === InteractionStatus.Selected || t === InteractionStatus.FinishEdit);
        null != i.getNodeItem().imageNode && i.getNodeItem().imageNode.setImageSource(t)
      }
  
      findIndex(e) {
        let t = 0;
        this.listNodeDataSource.ListNode.forEach((function (i, o) {
          i.getNodeCurrentNodeId() == e && (t = o)
        }));
        return t
      }
  
      initialRender() {
        this.observeComponentCreation(((e, t) => {
          ViewStackProcessor.StartGetAccessRecordingFor(e);
          List.create({});
          List.onDragMove((e => {
            if (this.isMultiPress) {
              console.error("drag error, a item has been dragged");
              return
            }
            let t = Math.floor(e.getY() / 24) % 2 ? Flag.DOWN_FLAG : Flag.UP_FLAG;
            let i = Math.floor(e.getY() / 48);
            let o = !1;
            if (i >= this.listNodeDataSource.totalCount()) {
              t = Flag.DOWN_FLAG;
              i = this.listNodeDataSource.totalCount() - 1;
              this.listNodeDataSource.getData(i).setIsOverBorder(!0);
              o = !0
            } else this.listNodeDataSource.getData(i).setIsOverBorder(!1);
            let s = this.listNodeDataSource.getData(i).getCurrentNodeId();
            if (i != this.listNodeDataSource.getLastPassIndex() && this.listNodeDataSource.getIsInnerDrag()) {
              if (this.listNodeDataSource.getIsParentOfInsertNode(s)) {
                this.listNodeDataSource.setPassIndex(i);
                let e = this;
                this.listNodeDataSource.clearTimeOutAboutDelayHighLightAndExpand(findCurrentNodeIndex.call(e, s));
                this.listNodeDataSource.setFlag(Flag.NONE);
                return
              }
            }
            this.listNodeDataSource.setLastPassIndex(i);
            this.listNodeDataSource.setVisibility(t, i, o);
            if (s != this.listNodeDataSource.getDraggingCurrentNodeId()) {
              let e = this;
              this.listNodeDataSource.delayHighLightAndExpandNode(findCurrentNodeIndex.call(e, s), s, i)
            }
          }));
          List.onDragEnter(((e, t) => {
            if (this.listNodeDataSource.getIsInnerDrag()) {
              this.listNodeDataSource.setIsDrag(!0);
              let e = .4;
              this.listNodeDataSource.setListItemOpacity(e)
            }
          }));
          List.onDragLeave(((e, t) => {
            this.listNodeDataSource.hideLastLine();
            this.listNodeDataSource.clearLastTimeoutHighLight();
            this.listNodeDataSource.clearLastTimeoutExpand();
            this.listNodeDataSource.setListItemOpacity(1);
            this.listNodeDataSource.setIsDrag(!1);
            this.listNodeDataSource.notifyDataReload()
          }));
          List.onDrop(((e, t) => {
            this.listNodeDataSource.clearLastTimeoutExpand();
            this.listNodeDataSource.setListItemOpacity(1);
            let i = this.listNodeDataSource.getPassIndex();
            let o = this.dropSelectedIndex;
            if (o - 1 > this.listNodeDataSource.totalCount() || null == o) {
              console.error("drag error, currentNodeIndex is not found");
              this.listNodeDataSource.setIsDrag(!1);
              return
            }
            if (i == this.listNodeDataSource.totalCount()) {
              console.log("need to insert into the position of the last line, now insertNodeIndex = insertNodeIndex - 1");
              i -= 1
            }
            let s = this.listNodeDataSource.getData(i);
            let a = s.getNodeCurrentNodeId();
            if (!this.listNodeDataSource.getIsDrag() || !this.listNodeDataSource.getIsInnerDrag()) {
              this.listNodeDataSource.clearLastTimeoutHighLight();
              this.listNodeDataSource.setIsInnerDrag(!1);
              this.listNodeDataSource.hideLastLine();
              this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
              this.listNodeDataSource.refreshSubtitle(a);
              this.listNodeDataSource.notifyDataReload();
              return
            }
            let d = this.listNodeDataSource.getCurrentNodeInfo();
            let r = s.getNodeParentNodeId();
            let n = this.listNodeDataSource.getDraggingCurrentNodeId();
            let l = this.listNodeDataSource.getDraggingParentNodeId();
            if (this.listNodeDataSource.getIsParentOfInsertNode(a)) {
              this.listNodeDataSource.clearLastTimeoutHighLight();
              this.listNodeDataSource.setIsInnerDrag(!1);
              this.listNodeDataSource.hideLastLine();
              this.listNodeDataSource.notifyDataChange(i);
              this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
              this.listNodeDataSource.setIsDrag(!1);
              let e = this;
              let t = findCurrentNodeIndex.call(e, n);
              this.listNodeDataSource.setClickIndex(t);
              this.listNodeDataSource.handleEvent(Event.DRAG, t);
              return
            }
            if (this.listNodeDataSource.getExpandAndCollapseInfo(n) == NodeStatus.Expand) {
              let e = this;
              this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex.call(e, n))
            }
            if (this.listNodeDataSource.getExpandAndCollapseInfo(a) == NodeStatus.Collapse) {
              let e = this;
              let t = findCurrentNodeIndex.call(e, a);
              this.listNodeDataSource.ListNode[t].getIsHighLight() && this.listNodeDataSource.expandAndCollapseNode(t)
            }
            this.listNodeDataSource.setLastDelayHighLightId();
            if (n != a) {
              this.listNodeDataSource.alterDragNode(r, a, s, l, n, d);
              this.listNodeDataSource.hideLastLine()
            } else {
              this.listNodeDataSource.hideLastLine();
              this.listNodeDataSource.setLastPassId(n);
              this.listNodeDataSource.hideLastLine()
            }
            let h = findCurrentNodeIndex.call(this, this.listNodeDataSource.getLastDelayHighLightId());
            this.listNodeDataSource.setLastDelayHighLightIndex(h);
            this.listNodeDataSource.clearLastTimeoutHighLight();
            this.listNodeDataSource.initialParameterAboutDelayHighLightAndExpandIndex();
            this.listNodeDataSource.setIsDrag(!1);
            let N = findCurrentNodeIndex.call(this, n);
            this.listNodeDataSource.setClickIndex(N);
            this.listNodeDataSource.handleEvent(Event.DRAG, N);
            this.listNodeDataSource.setIsInnerDrag(!1);
            this.listNodeDataSource.notifyDataReload();
            this.listNodeDataSource.listNode[N].fontColor = {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary_activated"],
              bundleName: "",
              moduleName: ""
            };
            if (-1 !== this.viewLastIndex && o != this.viewLastIndex) {
              this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .mainTitleNode
                .setMainTitleSelected(!1);
              this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .mainTitleNode
                .setMainTitleHighLight(!1)
            }
            null != this.listNodeDataSource.listNode[this.viewLastIndex] && (this.listNodeDataSource.listNode[this.viewLastIndex].fontColor = {
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_text_primary"],
              bundleName: "",
              moduleName: ""
            });
            this.listNodeDataSource.lastIndex = this.viewLastIndex;
            if (this.listNodeDataSource.listNode[this.viewLastIndex] && null != this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
              .imageNode) {
              this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .imageNode
                .setImageSource(InteractionStatus.Normal);
              this.listNodeDataSource.listNode[this.viewLastIndex].imageSource = this.listNodeDataSource.listNode[this.viewLastIndex].getNodeItem()
                .imageNode
                .source
            }
            this.listNodeDataSource.listNode[this.viewLastIndex] && this.listNodeDataSource.listNode[this.viewLastIndex].setNodeColor({
              id: -1,
              type: 10001,
              params: ["sys.color.ohos_id_color_background_transparent"],
              bundleName: "",
              moduleName: ""
            })
          }));
          t || List.pop();
          ViewStackProcessor.StopGetAccessRecording()
        }));
        {
          const e = e => {
            const t = e;
            {
              const e = void 0 !== globalThis.__lazyForEachItemGenFunction && !0;
              const i = (i, o) => {
                ViewStackProcessor.StartGetAccessRecordingFor(i);
                ListItem.create(s, e);
                ListItem.width("100%");
                ListItem.height(t.getListItemHeight());
                ListItem.padding({ left: this.itemPadding.left, right: this.itemPadding.right });
                ListItem.align(Alignment.Start);
                ListItem.onDragStart(((e, i) => {
                  if (this.listNodeDataSource.getIsDrag() || this.listNodeDataSource.getIsInnerDrag() || this.isMultiPress) {
                    console.error("drag error, a item has been dragged");
                    return
                  }
                  this.dropSelectedIndex = JSON.parse(i).selectedIndex;
                  let o = JSON.parse(i).selectedIndex;
                  let s = this.listNodeDataSource.getData(o);
                  let a = t.getNodeCurrentNodeId();
                  if (o >= this.listNodeDataSource.totalCount() || null == o) {
                    console.error("drag error, currentNodeIndex is not found in onDragStart");
                    return
                  }
                  this.listNodeDataSource.setIsInnerDrag(!0);
                  this.listNodeDataSource.setIsDrag(!0);
                  this.listNodeDataSource.setCurrentNodeInfo(s);
                  this.listNodeDataSource.setDraggingCurrentNodeId(s.getNodeCurrentNodeId());
                  this.listNodeDataSource.setDraggingParentNodeId(s.getNodeParentNodeId());
                  this.listNodeDataSource.setListItemOpacity(.4);
                  this.listNodeDataSource.notifyDataChange(o);
                  if (a == s.getNodeCurrentNodeId()) ; else {
                    console.error("drag is too fast,it attribute a fault to OH");
                    this.listNodeDataSource.setIsDrag(!1)
                  }
                }));
                o || ListItem.pop();
                ViewStackProcessor.StopGetAccessRecording()
              };
              const o = () => {
                this.observeComponentCreation(i);
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Row.create();
                  Row.onTouch((e => {
                    this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                    let i = this.findIndex(t.getNodeCurrentNodeId());
                    if (e.type == TouchType.Down && i != this.viewLastIndex) {
                      this.clearLastIndexColor();
                      this.listNodeDataSource.lastIndex = i;
                      this.listNodeDataSource.setClickIndex(i)
                    }
                    if (e.type == TouchType.Up) {
                      this.listNodeDataSource.listNode[i].setIsSelected(!0);
                      this.listNodeDataSource.setImageSource(i, InteractionStatus.Selected);
                      null != this.listNodeDataSource.listNode[i].getNodeItem()
                        .imageNode && (this.listNodeDataSource.listNode[i].imageSource = this.listNodeDataSource.listNode[i].getNodeItem()
                        .imageNode
                        .source);
                      if (i != this.viewLastIndex) {
                        this.clearLastIndexColor();
                        this.listNodeDataSource.lastIndex = i;
                        this.listNodeDataSource.setClickIndex(i)
                      }
                      this.viewLastIndex = i
                    }
                    if (-1 !== this.listNodeDataSource.getLastIndex() && i !== this.listNodeDataSource.getLastIndex()) {
                      this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                      this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
                    }
                  }));
                  i || Row.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  i ? ViewPU.create(new TreeViewInner(this, {
                    item: t,
                    listNodeDataSource: this.listNodeDataSource,
                    index: this.findIndex(t.getNodeCurrentNodeId())
                  }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, { item: t });
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                ListItem.pop()
              };
              const s = (e, o) => {
                i(e, o);
                this.updateFuncByElmtId.set(e, i);
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  Row.create();
                  Row.onTouch((e => {
                    this.viewLastIndex = this.listNodeDataSource.getLastIndex();
                    let i = this.findIndex(t.getNodeCurrentNodeId());
                    if (e.type == TouchType.Down && i != this.viewLastIndex) {
                      this.clearLastIndexColor();
                      this.listNodeDataSource.lastIndex = i;
                      this.listNodeDataSource.setClickIndex(i)
                    }
                    if (e.type == TouchType.Up) {
                      this.listNodeDataSource.listNode[i].setIsSelected(!0);
                      this.listNodeDataSource.setImageSource(i, InteractionStatus.Selected);
                      null != this.listNodeDataSource.listNode[i].getNodeItem()
                        .imageNode && (this.listNodeDataSource.listNode[i].imageSource = this.listNodeDataSource.listNode[i].getNodeItem()
                        .imageNode
                        .source);
                      if (i != this.viewLastIndex) {
                        this.clearLastIndexColor();
                        this.listNodeDataSource.lastIndex = i;
                        this.listNodeDataSource.setClickIndex(i)
                      }
                      this.viewLastIndex = i
                    }
                    if (-1 !== this.listNodeDataSource.getLastIndex() && i !== this.listNodeDataSource.getLastIndex()) {
                      this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                      this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
                    }
                  }));
                  i || Row.pop();
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                this.observeComponentCreation(((e, i) => {
                  ViewStackProcessor.StartGetAccessRecordingFor(e);
                  i ? ViewPU.create(new TreeViewInner(this, {
                    item: t,
                    listNodeDataSource: this.listNodeDataSource,
                    index: this.findIndex(t.getNodeCurrentNodeId())
                  }, void 0, e)) : this.updateStateVarsOfChildByElmtId(e, { item: t });
                  ViewStackProcessor.StopGetAccessRecording()
                }));
                Row.pop();
                ListItem.pop()
              };
              e ? (() => {
                this.observeComponentCreation(i);
                ListItem.pop()
              })() : o()
            }
          };
          const t = e => JSON.stringify(e);
          LazyForEach.create("1", this, this.listNodeDataSource, e, t);
          LazyForEach.pop()
        }
        List.pop()
      }
  
      rerender() {
        this.updateDirtyElements()
      }
    }
  
    __decorate([], N.prototype, "popupForShowTitle", null);
    __decorate([], N.prototype, "builder", null);
    __decorate([], N.prototype, "draggingPopup", null);
    e.TreeView = N;
    e.TreeController = class {
      constructor() {
        this.ROOT_NODE_ID = -1;
        this.nodeIdList = [];
        this.listNodeUtils = new l;
        this.listNodeDataSource = new h
      }
  
      getListNodeDataSource() {
        return this.listNodeDataSource
      }
  
      getClickNodeChildrenInfo() {
        let e = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickNodeChildrenInfo(e)
      }
  
      getChildrenId() {
        let e = this.listNodeDataSource.getClickNodeId();
        return this.listNodeUtils.getClickChildId(e)
      }
  
      removeNode() {
        let e = this.listNodeDataSource.getClickNodeId();
        let t = this.listNodeUtils.findParentNodeId(e);
        let i = this.listNodeUtils.removeNode(e, t, this.listNodeUtils.traverseNodeBF);
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.REMOVE_NODE, t, i);
        this.nodeIdList.splice(this.nodeIdList.indexOf(e), 1)
      }
  
      modifyNode() {
        let e = this.listNodeDataSource.getClickNodeId();
        this.listNodeDataSource.setItemVisibilityOnEdit(e, MenuOperation.MODIFY_NODE)
      }
  
      add() {
        let e = this.listNodeDataSource.getClickNodeId();
        if (e == this.listNodeDataSource.ROOT_NODE_ID || !this.listNodeDataSource.getIsFolder(e)) return;
        let t = {
          isFolder: !0,
          icon: null,
          selectedIcon: null,
          editIcon: null,
          menu: null,
          secondaryTitle: ""
        };
        t = this.listNodeUtils.getNewNodeInfo(e);
        this.nodeIdList.push(this.nodeIdList[this.nodeIdList.length-1] + 1);
        let i = this.nodeIdList[this.nodeIdList.length-1];
        this.listNodeUtils.addNewNodeId = i;
        this.listNodeUtils.addNode(e, i, {
          isFolder: t.isFolder,
          icon: t.icon,
          selectedIcon: t.selectedIcon,
          editIcon: t.editIcon,
          primaryTitle: "新建文件夹",
          menu: t.menu,
          secondaryTitle: t.secondaryTitle
        });
        this.listNodeDataSource.refreshData(this.listNodeUtils, MenuOperation.ADD_NODE, e, [i]);
        this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
        this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE);
        this.listNodeDataSource.listNode[this.listNodeDataSource.getLastIndex()].setFontColor({
          id: -1,
          type: 10001,
          params: ["sys.color.ohos_id_color_text_primary"],
          bundleName: "",
          moduleName: ""
        });
        let o = findCurrentNodeIndex.call(this, i);
        this.listNodeDataSource.setClickIndex(o);
        this.listNodeDataSource.handleEvent(Event.TOUCH_UP, o)
      }
  
      addNodeParam(e) {
        if (null != e.primaryTitle && !this.listNodeUtils.checkMainTitleIsValid(e.primaryTitle)) throw new Error('ListTreeNode[addNode]: The directory name cannot contain the following characters /: *? "< > | or exceeds the maximum length.');
        if (null == e.primaryTitle && null == e.icon) throw new Error("ListTreeNode[addNode]: The icon and directory name cannot be empty at the same time.");
        if (e.currentNodeId === this.ROOT_NODE_ID || null === e.currentNodeId) throw new Error("ListTreeNode[addNode]: currentNodeId can not be -1 or null.");
        this.nodeIdList.push(e.currentNodeId);
        this.listNodeUtils.addNode(e.parentNodeId, e.currentNodeId, e);
        return this
      }
  
      addNode(e) {
        if (null != e) {
          if (null != e.primaryTitle && !this.listNodeUtils.checkMainTitleIsValid(e.primaryTitle)) throw new Error('ListTreeNode[addNode]: The directory name cannot contain the following characters /: *? "< > | or exceeds the maximum length.');
          if (null == e.primaryTitle && null == e.icon) throw new Error("ListTreeNode[addNode]: The icon and directory name cannot be empty at the same time.");
          if (e.currentNodeId === this.ROOT_NODE_ID || null === e.currentNodeId) throw new Error("ListTreeNode[addNode]: currentNodeId can not be -1 or null.");
          this.nodeIdList.push(e.currentNodeId);
          this.listNodeUtils.addNode(e.parentNodeId, e.currentNodeId, e);
          return this
        }
        this.add()
      }
  
      buildDone() {
        this.listNodeDataSource.init(this.listNodeUtils);
        this.nodeIdList.sort(((e, t) => e - t))
      }
  
      refreshNode(e, t = "", i = "") {
        this.listNodeDataSource.setNodeSubtitlePara(e, t, i)
      }
    }
  }(TreeView || (TreeView = {}));
  
  export class TreeViewInner extends ViewPU {
    constructor(e, t, i, o = -1) {
      super(e, i, o);
      this.__item = new SynchedPropertyNesedObjectPU(t.item, this, "item");
      this.listNodeDataSource = void 0;
      this.__index = new ObservedPropertySimplePU(-1, this, "index");
      this.__lastIndex = new ObservedPropertySimplePU(-1, this, "lastIndex");
      this.__count = new ObservedPropertySimplePU(0, this, "count");
      this.listTreeViewMenu = null;
      this.MAX_CN_LENGTH = 254;
      this.MAX_EN_LENGTH = 255;
      this.INITIAL_INVALID_VALUE = -1;
      this.MAX_TOUCH_DOWN_COUNT = 0;
      this.isMultiPress = !1;
      this.touchDownCount = this.INITIAL_INVALID_VALUE;
      this.appEventBus = TreeView.TreeListenerManager.getInstance().getTreeListener();
      this.itemPadding = {
        left: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_card_margin_start"],
          bundleName: "",
          moduleName: ""
        },
        right: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_card_margin_end"],
          bundleName: "",
          moduleName: ""
        },
        top: {
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_margin_vertical"],
          bundleName: "",
          moduleName: ""
        },
        bottom: "0vp"
      };
      this.textInputPadding = { left: "0vp", right: "0vp", top: "0vp", bottom: "0vp" };
      this.setInitiallyProvidedValue(t)
    }
  
    setInitiallyProvidedValue(e) {
      this.__item.set(e.item);
      void 0 !== e.listNodeDataSource && (this.listNodeDataSource = e.listNodeDataSource);
      void 0 !== e.index && (this.index = e.index);
      void 0 !== e.lastIndex && (this.lastIndex = e.lastIndex);
      void 0 !== e.count && (this.count = e.count);
      void 0 !== e.listTreeViewMenu && (this.listTreeViewMenu = e.listTreeViewMenu);
      void 0 !== e.MAX_CN_LENGTH && (this.MAX_CN_LENGTH = e.MAX_CN_LENGTH);
      void 0 !== e.MAX_EN_LENGTH && (this.MAX_EN_LENGTH = e.MAX_EN_LENGTH);
      void 0 !== e.INITIAL_INVALID_VALUE && (this.INITIAL_INVALID_VALUE = e.INITIAL_INVALID_VALUE);
      void 0 !== e.MAX_TOUCH_DOWN_COUNT && (this.MAX_TOUCH_DOWN_COUNT = e.MAX_TOUCH_DOWN_COUNT);
      void 0 !== e.isMultiPress && (this.isMultiPress = e.isMultiPress);
      void 0 !== e.touchDownCount && (this.touchDownCount = e.touchDownCount);
      void 0 !== e.appEventBus && (this.appEventBus = e.appEventBus);
      void 0 !== e.itemPadding && (this.itemPadding = e.itemPadding);
      void 0 !== e.textInputPadding && (this.textInputPadding = e.textInputPadding)
    }
  
    updateStateVars(e) {
      this.__item.set(e.item)
    }
  
    purgeVariableDependenciesOnElmtId(e) {
      this.__item.purgeDependencyOnElmtId(e);
      this.__index.purgeDependencyOnElmtId(e);
      this.__lastIndex.purgeDependencyOnElmtId(e);
      this.__count.purgeDependencyOnElmtId(e)
    }
  
    aboutToBeDeleted() {
      this.__item.aboutToBeDeleted();
      this.__index.aboutToBeDeleted();
      this.__lastIndex.aboutToBeDeleted();
      this.__count.aboutToBeDeleted();
      SubscriberManager.Get().delete(this.id__());
      this.aboutToBeDeletedInternal()
    }
  
    get item() {
      return this.__item.get()
    }
  
    get index() {
      return this.__index.get()
    }
  
    set index(e) {
      this.__index.set(e)
    }
  
    get lastIndex() {
      return this.__lastIndex.get()
    }
  
    set lastIndex(e) {
      this.__lastIndex.set(e)
    }
  
    get count() {
      return this.__count.get()
    }
  
    set count(e) {
      this.__count.set(e)
    }
  
    aboutToAppear() {
      this.item.getNodeItem().imageNode && (this.item.imageSource = this.item.getNodeItem().imageNode.source)
    }
  
    checkInvalidPattern(e) {
      return /[\\\/:*?"<>|]/.test(e)
    }
  
    checkIsAllCN(e) {
      return /^[\u4e00-\u9fa5]+$/.test(e)
    }
  
    popupForShowTitle(e, t, i, o = null) {
      this.observeComponentCreation(((e, i) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        Row.create();
        Row.backgroundColor(t);
        Row.border({
          radius: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
            bundleName: "",
            moduleName: ""
          }
        });
        Row.padding({
          left: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
            bundleName: "",
            moduleName: ""
          },
          right: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_elements_margin_horizontal_l"],
            bundleName: "",
            moduleName: ""
          },
          top: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_card_margin_middle"],
            bundleName: "",
            moduleName: ""
          },
          bottom: {
            id: -1,
            type: 10002,
            params: ["sys.float.ohos_id_card_margin_middle"],
            bundleName: "",
            moduleName: ""
          }
        });
        i || Row.pop();
        ViewStackProcessor.StopGetAccessRecording()
      }));
      this.observeComponentCreation(((t, o) => {
        ViewStackProcessor.StartGetAccessRecordingFor(t);
        Text.create(e);
        Text.fontSize({
          id: -1,
          type: 10002,
          params: ["sys.float.ohos_id_text_size_body2"],
          bundleName: "",
          moduleName: ""
        });
        Text.fontWeight("regular");
        Text.fontColor(i);
        o || Text.pop();
        ViewStackProcessor.StopGetAccessRecording()
      }));
      Text.pop();
      Row.pop()
    }
  
    builder(e = null) {
      this.listTreeViewMenu.bind(this)()
    }
  
    initialRender() {
      this.observeComponentCreation(((e, t) => {
        ViewStackProcessor.StartGetAccessRecordingFor(e);
        If.create();
        this.item.getNodeIsShow() ? this.ifElseBranchUpdateFunction(0, (() => {
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Column.create();
            Column.opacity(this.listNodeDataSource.getListItemOpacity(ObservedObject.GetRawObject(this.item)));
            Column.onHover((e => {
              e ? this.item.setNodeColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_hover"],
                bundleName: "",
                moduleName: ""
              }) : this.item.setNodeColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_background_transparent"],
                bundleName: "",
                moduleName: ""
              })
            }));
            Column.onTouch((e => {
              this.count++;
              if (this.count > 1) {
                this.count--;
                return
              }
              this.listNodeDataSource.setClickIndex(this.index);
              let t = this.item.getNodeCurrentNodeId();
              if (e.type === TouchType.Down) this.item.setNodeColor({
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_click_effect"],
                bundleName: "",
                moduleName: ""
              }); else if (e.type === TouchType.Up) {
                this.item.setNodeColor("#1A0A59F7");
                this.item.fontColor = {
                  id: -1,
                  type: 10001,
                  params: ["sys.color.ohos_id_color_text_primary_activated"],
                  bundleName: "",
                  moduleName: ""
                };
                if (null != this.item.getNodeItem().imageNode) {
                  this.item.getNodeItem().imageNode.setImageSource(InteractionStatus.Selected);
                  this.listNodeDataSource.setImageSource(this.index, InteractionStatus.Selected);
                  this.item.imageSource = this.item.getNodeItem().imageNode.source
                }
                this.item.getNodeItem().mainTitleNode.setMainTitleSelected(!0);
                this.lastIndex = this.index;
                let e = { currentNodeId: t };
                this.appEventBus.emit(TreeView.TreeListenType.NODE_CLICK, [e])
              }
              if (-1 !== this.listNodeDataSource.getLastIndex() && this.index !== this.listNodeDataSource.getLastIndex()) {
                this.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, this.listNodeDataSource.getLastIndex());
                this.listNodeDataSource.setItemVisibilityOnEdit(this.listNodeDataSource.getLastIndex(), MenuOperation.COMMIT_NODE)
              }
              this.count--
            }));
            ViewStackProcessor.visualState("focused");
            Column.border({
              radius: {
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              },
              width: 2,
              color: {
                id: -1,
                type: 10001,
                params: ["sys.color.ohos_id_color_focused_outline"],
                bundleName: "",
                moduleName: ""
              },
              style: BorderStyle.Solid
            });
            ViewStackProcessor.visualState("normal");
            Column.border({
              radius: {
                id: -1,
                type: 10002,
                params: ["sys.float.ohos_id_corner_radius_clicked"],
                bundleName: "",
                moduleName: ""
              },
              width: 0
            });
            ViewStackProcessor.visualState();
            Column.backgroundColor(this.item.getNodeItem().mainTitleNode && this.item.getNodeItem()
              .inputText && this.item.getIsShowInputText() ? this.item.getNodeItem()
              .inputText
              .editColor : this.item.getNodeColor());
            Column.border({
              width: this.item.getNodeBorder().borderWidth,
              color: this.item.getNodeBorder().borderColor,
              radius: this.item.getNodeBorder().borderRadius
            });
            Column.height(48);
            Column.focusable(!0);
            Column.onMouse((e => {
              let t = this;
              let i = findCurrentNodeIndex.call(t, this.item.getNodeCurrentNodeId());
              if (e.button == MouseButton.Right) {
                t.listNodeDataSource.handleEvent(Event.MOUSE_BUTTON_RIGHT, findCurrentNodeIndex.call(t, this.item.getNodeCurrentNodeId()));
                this.listTreeViewMenu = this.item.getMenu();
                t.listNodeDataSource.setClickIndex(i);
                t.listNodeDataSource.setPopUpInfo(PopUpType.HINTS, InputError.NONE,!1, i);
                clearTimeout(this.item.getNodeItem().mainTitleNode.popUpTimeout)
              }
              e.stopPropagation()
            }));
            Column.padding({ top: 0, bottom: 0 });
            Column.bindPopup(this.item.getPopUpInfo().popUpIsShow, {
              builder: { builder: () => {
                this.popupForShowTitle.call(this, this.item.getPopUpInfo().popUpText, this.item.getPopUpInfo()
                  .popUpColor, this.item.getPopUpInfo().popUpTextColor)
              } },
              placement: Placement.BottomLeft,
              placementOnTop: !1,
              popupColor: this.item.getPopUpInfo().popUpColor,
              autoCancel: !0,
              enableArrow: this.item.getPopUpInfo().popUpEnableArrow
            });
            t || Column.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Stack.create({ alignContent: Alignment.Bottom });
            t || Stack.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Divider.create();
            Divider.height(this.listNodeDataSource.getFlagLine().flagLineHeight);
            Divider.color(this.listNodeDataSource.getFlagLine().flagLineColor);
            Divider.visibility(this.listNodeDataSource.getVisibility(ObservedObject.GetRawObject(this.item)));
            Divider.lineCap(LineCapStyle.Round);
            Divider.margin({ left: this.item.getFlagLineLeftMargin() });
            t || Divider.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create({});
            t || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create({});
            Row.width("100%");
            Gesture.create(GesturePriority.Low);
            TapGesture.create({ count: 2 });
            TapGesture.onAction((e => {
              this.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex.call(this, this.item.getNodeCurrentNodeId()))
            }));
            TapGesture.pop();
            Gesture.pop();
            Row.height(this.item.getNodeHeight());
            Row.padding({ left: this.item.getNodeLeftPadding() });
            Row.bindContextMenu({ builder: this.builder.bind(this) }, ResponseType.RightClick);
            t || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.item.getNodeItem().imageNode ? this.ifElseBranchUpdateFunction(0, (() => {
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Row.create();
                Row.backgroundColor("#00000000");
                Row.margin({ right: this.item.getNodeItem().imageNode.itemRightMargin });
                Row.height(this.item.getNodeItem().imageNode.itemHeight);
                Row.width(this.item.getNodeItem().imageNode.itemWidth);
                t || Row.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Image.create(this.item.imageSource);
                Image.objectFit(ImageFit.Contain);
                Image.height(this.item.getNodeItem().imageNode.itemHeight);
                Image.width(this.item.getNodeItem().imageNode.itemWidth);
                Image.opacity(this.item.getIsSelected() || this.item.getIsHighLight() ? this.item.getNodeItem()
                  .imageNode
                  .noOpacity : this.item.getNodeItem().imageNode.opacity);
                Image.focusable(null == this.item.getNodeItem().mainTitleNode);
                t || Image.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              Row.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          If.pop();
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Row.create();
            Row.layoutWeight(1);
            t || Row.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.item.getNodeItem()
              .mainTitleNode && this.item.getIsShowTitle() ? this.ifElseBranchUpdateFunction(0, (() => {
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Text.create(this.item.getNodeItem().mainTitleNode.title);
                Text.maxLines(1);
                Text.fontSize(this.item.getNodeItem().mainTitleNode.size);
                Text.fontColor(this.item.fontColor);
                Text.margin({ right: this.item.getNodeItem().mainTitleNode.itemRightMargin });
                Text.textOverflow({ overflow: TextOverflow.Ellipsis });
                Text.fontWeight(this.item.getNodeItem().mainTitleNode.weight);
                Text.focusable(!0);
                t || Text.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              Text.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          If.pop();
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.item.getNodeItem().mainTitleNode && this.item.getNodeItem()
              .inputText && this.item.getIsShowInputText() ? this.ifElseBranchUpdateFunction(0, (() => {
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Row.create();
                Row.backgroundColor(this.item.getNodeItem().inputText.backgroundColor);
                Row.borderRadius(this.item.getNodeItem().inputText.borderRadius);
                Row.margin({ right: this.item.getNodeItem().inputText.itemRightMargin });
                t || Row.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                TextInput.create({ text: this.item.getNodeItem().mainTitleNode.title });
                TextInput.height(this.item.getNodeItem().inputText.itemHeight);
                TextInput.fontSize(this.item.getNodeItem().inputText.size);
                TextInput.fontColor(this.item.getNodeItem().inputText.color);
                TextInput.borderRadius(this.item.getNodeItem().inputText.borderRadius);
                TextInput.backgroundColor(this.item.getNodeItem().inputText.backgroundColor);
                TextInput.enterKeyType(EnterKeyType.Done);
                TextInput.padding({
                  left: this.textInputPadding.left,
                  right: this.textInputPadding.right,
                  top: this.textInputPadding.top,
                  bottom: this.textInputPadding.bottom
                });
                TextInput.onChange((e => {
                  let t = this;
                  var i = findCurrentNodeIndex.call(t, this.item.getNodeCurrentNodeId());
                  let o = "";
                  let s = !1;
                  let a = !1;
                  if (t.checkInvalidPattern(e)) {
                    for (let i = 0;i < e.length; i++) t.checkInvalidPattern(e[i]) || (o += e[i]);
                    s = !0;
                    t.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR,!0, i)
                  } else {
                    o = e;
                    s = !1;
                    t.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.INVALID_ERROR,!1, i)
                  }
                  if (t.checkIsAllCN(o) && o.length > this.MAX_CN_LENGTH || !t.checkIsAllCN(o) && o.length > this.MAX_EN_LENGTH) {
                    o = t.checkIsAllCN(o) ? o.substr(0, this.MAX_CN_LENGTH) : o.substr(0, this.MAX_EN_LENGTH);
                    a = !0;
                    t.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR,!0, i)
                  } else a = !1;
                  if (!a && !s) {
                    t.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.LENGTH_ERROR,!1, i);
                    t.listNodeDataSource.setMainTitleNameOnEdit(i, o)
                  }
                }));
                TextInput.onSubmit((e => {
                  let t = this;
                  var i = findCurrentNodeIndex.call(t, this.item.getNodeCurrentNodeId());
                  t.listNodeDataSource.setPopUpInfo(PopUpType.WARNINGS, InputError.NONE,!1, i);
                  t.listNodeDataSource.setItemVisibilityOnEdit(i, MenuOperation.COMMIT_NODE)
                }));
                t || TextInput.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              Row.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          If.pop();
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            Blank.create();
            t || Blank.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          Blank.pop();
          Row.pop();
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.listNodeDataSource.hasSubtitle(this.item.getCurrentNodeId()) ? this.ifElseBranchUpdateFunction(0, (() => {
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Row.create();
                Row.margin({
                  left: this.listNodeDataSource.getSubTitlePara().margin.left,
                  right: this.item.getNodeItem().imageCollapse ? 0 : this.listNodeDataSource.getSubTitlePara()
                    .margin
                    .right
                });
                t || Row.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Text.create(this.listNodeDataSource.getSubtitle(this.item.getCurrentNodeId()));
                Text.fontSize(this.listNodeDataSource.getSubTitlePara().fontSize);
                Text.fontColor(this.listNodeDataSource.getSubTitleFontColor(this.item.getIsHighLight() || this.item.getIsModify()));
                Text.fontWeight(this.listNodeDataSource.getSubTitlePara().fontWeight);
                t || Text.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              Text.pop();
              Row.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          If.pop();
          this.observeComponentCreation(((e, t) => {
            ViewStackProcessor.StartGetAccessRecordingFor(e);
            If.create();
            this.item.getNodeItem().imageCollapse ? this.ifElseBranchUpdateFunction(0, (() => {
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Row.create();
                Row.height(this.item.getNodeItem().imageCollapse.itemHeight);
                Row.width(this.item.getNodeItem().imageCollapse.itemWidth);
                t || Row.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              this.observeComponentCreation(((e, t) => {
                ViewStackProcessor.StartGetAccessRecordingFor(e);
                Image.create(this.item.getNodeItem().imageCollapse.collapseSource);
                Image.borderWidth(1);
                Image.fillColor(this.item.getNodeItem().imageCollapse.isCollapse ? "#00000000" : "#FFFFFF");
                Image.align(Alignment.End);
                Image.objectFit(ImageFit.Contain);
                Image.height(this.item.getNodeItem().imageCollapse.itemHeight);
                Image.width(this.item.getNodeItem().imageCollapse.itemWidth);
                Image.opacity(this.item.getIsHighLight() ? this.item.getNodeItem()
                  .imageCollapse
                  .noOpacity : this.item.getNodeItem().imageCollapse.opacity);
                Image.onTouch((e => {
                  if (e.type === TouchType.Down) {
                    let e = this;
                    e.listNodeDataSource.expandAndCollapseNode(findCurrentNodeIndex.call(e, this.item.getNodeCurrentNodeId()));
                    this.listNodeDataSource.setCurrentFocusNodeId(this.item.getCurrentNodeId())
                  }
                  e.stopPropagation()
                }));
                t || Image.pop();
                ViewStackProcessor.StopGetAccessRecording()
              }));
              Row.pop()
            })) : If.branchId(1);
            t || If.pop();
            ViewStackProcessor.StopGetAccessRecording()
          }));
          If.pop();
          Row.pop();
          Row.pop();
          Stack.pop();
          Column.pop()
        })) : If.branchId(1);
        t || If.pop();
        ViewStackProcessor.StopGetAccessRecording()
      }));
      If.pop()
    }
  
    rerender() {
      this.updateDirtyElements()
    }
  }

export default TreeView