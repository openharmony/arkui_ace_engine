/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

/* If a new value is added, add it from the end. */
var Color;
(function (Color) {
  Color["White"] = "#ffffffff";
  Color["Black"] = "#ff000000";
  Color["Blue"] = "#ff0000ff";
  Color["Brown"] = "#ffa52a2a";
  Color["Gray"] = "#ff808080";
  Color["Green"] = "#ff008000";
  Color["Grey"] = "#ff808080";
  Color["Orange"] = "#ffffa500";
  Color["Pink"] = "#ffffc0cb";
  Color["Red"] = "#ffff0000";
  Color["Yellow"] = "#ffffff00";
  Color["Transparent"] = "#00000000";
})(Color || (Color = {}));

var ColoringStrategy;
(function (ColoringStrategy) {
  ColoringStrategy["INVERT"] = "invert";
  ColoringStrategy["AVERAGE"] = "average";
  ColoringStrategy["PRIMARY"] = "primary";
})(ColoringStrategy || (ColoringStrategy = {}));

var TextInputStyle;
(function (TextInputStyle) {
  TextInputStyle["Default"] = "Default";
  TextInputStyle["Inline"] = "Inline";
})(TextInputStyle || (TextInputStyle = {}));

var TextContentStyle;
(function (TextContentStyle) {
  TextContentStyle["DEFAULT"] = "Default";
  TextContentStyle["INLINE"] = "Inline";
})(TextContentStyle || (TextContentStyle = {}));

var TextAlign;
(function (TextAlign) {
  TextAlign[TextAlign["Start"] = 0] = "Start";
  TextAlign[TextAlign["Center"] = 1] = "Center";
  TextAlign[TextAlign["End"] = 2] = "End";
  TextAlign[TextAlign["Justify"] = 3] = "Justify";
  TextAlign[TextAlign["JUSTIFY"] = 3] = "JUSTIFY";
})(TextAlign || (TextAlign = {}));

var TextDataDetectorType;
(function (TextDataDetectorType) {
  TextDataDetectorType[TextDataDetectorType.PHONE_NUMBER = 0] = 'PHONE_NUMBER';
  TextDataDetectorType[TextDataDetectorType.URL = 1] = 'URL';
  TextDataDetectorType[TextDataDetectorType.EMAIL = 2] = 'EMAIL';
  TextDataDetectorType[TextDataDetectorType.ADDRESS = 3] = 'ADDRESS';
  TextDataDetectorType[TextDataDetectorType.DATE_TIME = 4] = 'DATE_TIME';
})(TextDataDetectorType || (TextDataDetectorType = {}));

var DataPanelType;
(function (DataPanelType) {
  DataPanelType[DataPanelType["Line"] = 0] = "Line";
  DataPanelType[DataPanelType["Circle"] = 4] = "Circle";
})(DataPanelType || (DataPanelType = {}));

var FontWeight;
(function (FontWeight) {
  FontWeight["Light"] = "light";
  FontWeight["Lighter"] = "lighter";
  FontWeight["Normal"] = "normal";
  FontWeight["Regular"] = "regular";
  FontWeight["Medium"] = "medium";
  FontWeight["Bold"] = "bold";
  FontWeight["Bolder"] = "bolder";
})(FontWeight || (FontWeight = {}));

var WordBreak;
(function (WordBreak) {
  WordBreak[WordBreak["NORMAL"] = 0] = "normal";
  WordBreak[WordBreak["BREAK_ALL"] = 1] = "break-all";
  WordBreak[WordBreak["BREAK_WORD"] = 2] = "break-word";
})(WordBreak || (WordBreak = {}));

var DpiFollowStrategy;
(function (DpiFollowStrategy) {
  DpiFollowStrategy[DpiFollowStrategy["FOLLOW_HOST_DPI"] = 0] = "follow-host-dpi";
  DpiFollowStrategy[DpiFollowStrategy["FOLLOW_UI_EXTENSION_ABILITY_DPI"] = 1] = "follow-ui-extension-ability-dpi";
})(DpiFollowStrategy || (DpiFollowStrategy = {}));

var SecurityDpiFollowStrategy;
(function (SecurityDpiFollowStrategy) {
  SecurityDpiFollowStrategy[SecurityDpiFollowStrategy["FOLLOW_HOST_DPI"] = 0] = "follow-host-dpi";
  SecurityDpiFollowStrategy[SecurityDpiFollowStrategy["FOLLOW_UI_EXTENSION_ABILITY_DPI"] = 1] = "follow-ui-extension-ability-dpi";
})(SecurityDpiFollowStrategy || (SecurityDpiFollowStrategy = {}));

var EllipsisMode;
(function (EllipsisMode) {
  EllipsisMode[EllipsisMode["START"] = 0] = "start";
  EllipsisMode[EllipsisMode["CENTER"] = 1] = "center";
  EllipsisMode[EllipsisMode["END"] = 2] = "end";
})(EllipsisMode || (EllipsisMode = {}));

var LineBreakStrategy;
(function (LineBreakStrategy) {
  LineBreakStrategy[LineBreakStrategy["GREEDY"] = 0] = "greedy";
  LineBreakStrategy[LineBreakStrategy["HIGH_QUALITY"] = 1] = "highquality";
  LineBreakStrategy[LineBreakStrategy["BALANCED"] = 2] = "balanced";
})(LineBreakStrategy || (LineBreakStrategy = {}));

var TextSelectableMode;
(function (TextSelectableMode) {
  TextSelectableMode[TextSelectableMode["SELECTABLE_UNFOCUSABLE"] = 0] = "selectable-unfocusable";
  TextSelectableMode[TextSelectableMode["SELECTABLE_FOCUSABLE"] = 1] = "selectable-focusable";
  TextSelectableMode[TextSelectableMode["UNSELECTABLE"] = 2] = "unselectable";
})(TextSelectableMode || (TextSelectableMode = {}));

var Curve;
(function (Curve) {
  Curve["Linear"] = "linear";
  Curve["Ease"] = "ease";
  Curve["EaseIn"] = "ease-in";
  Curve["EaseOut"] = "ease-out";
  Curve["EaseInOut"] = "ease-in-out";
  Curve["FastOutSlowIn"] = "fast-out-slow-in";
  Curve["LinearOutSlowIn"] = "linear-out-slow-in";
  Curve["FastOutLinearIn"] = "fast-out-linear-in";
  Curve["ExtremeDeceleration"] = "extreme-deceleration";
  Curve["Sharp"] = "sharp";
  Curve["Rhythm"] = "rhythm";
  Curve["Smooth"] = "smooth";
  Curve["Friction"] = "friction";
})(Curve || (Curve = {}));

var FillMode;
(function (FillMode) {
  FillMode[FillMode["None"] = 0] = "none";
  FillMode[FillMode["Forwards"] = 1] = "forwards";
  FillMode[FillMode["Backwards"] = 2] = "backwards";
  FillMode[FillMode["Both"] = 3] = "both";
})(FillMode || (FillMode = {}));

var PlayMode;
(function (PlayMode) {
  PlayMode["Normal"] = "normal";
  PlayMode["Alternate"] = "alternate";
  PlayMode["Reverse"] = "reverse";
  PlayMode["AlternateReverse"] = "alternate-reverse";
})(PlayMode || (PlayMode = {}));

var RepeatMode;
(function (RepeatMode) {
  RepeatMode["Repeat"] = "Repeat";
  RepeatMode["Stretch"] = "Stretch";
  RepeatMode["Round"] = "Round";
  RepeatMode["Space"] = "Space";
})(RepeatMode || (RepeatMode = {}));

var BorderStyle;
(function (BorderStyle) {
  BorderStyle[BorderStyle["Solid"] = 0] = "Solid";
  BorderStyle[BorderStyle["Dashed"] = 1] = "Dashed";
  BorderStyle[BorderStyle["Dotted"] = 2] = "Dotted";
})(BorderStyle || (BorderStyle = {}));

var LineCapStyle;
(function (LineCapStyle) {
  LineCapStyle[LineCapStyle["Butt"] = 0] = "Butt";
  LineCapStyle[LineCapStyle["Round"] = 1] = "Round";
  LineCapStyle[LineCapStyle["Square"] = 2] = "Square";
})(LineCapStyle || (LineCapStyle = {}));

var ButtonType;
(function (ButtonType) {
  ButtonType[ButtonType['Normal'] = 0] = 'Normal';
  ButtonType[ButtonType['Capsule'] = 1] = 'Capsule';
  ButtonType[ButtonType['Circle'] = 2] = 'Circle';
  ButtonType[ButtonType['Arc'] = 4] = 'Arc';
  ButtonType[ButtonType['ROUNDED_RECTANGLE'] = 8] = 'ROUNDED_RECTANGLE';
})(ButtonType || (ButtonType = {}));

var DevicePosition;
(function (DevicePosition) {
  DevicePosition[DevicePosition["Front"] = 0] = "Front";
  DevicePosition[DevicePosition["Back"] = 1] = "Back";
})(DevicePosition || (DevicePosition = {}));

var ImageFit;
(function (ImageFit) {
  ImageFit[ImageFit["Fill"] = 0] = "Fill";
  ImageFit[ImageFit["Contain"] = 1] = "Contain";
  ImageFit[ImageFit["Cover"] = 2] = "Cover";
  ImageFit[ImageFit["Auto"] = 3] = "Auto";
  ImageFit[ImageFit["None"] = 5] = "None";
  ImageFit[ImageFit["ScaleDown"] = 6] = "ScaleDown";
  ImageFit[ImageFit["TOP_START"] = 7] = "TOP_START";
  ImageFit[ImageFit["TOP"] = 8] = "TOP";
  ImageFit[ImageFit["TOP_END"] = 9] = "TOP_END";
  ImageFit[ImageFit["START"] = 10] = "START";
  ImageFit[ImageFit["CENTER"] = 11] = "CENTER";
  ImageFit[ImageFit["END"] = 12] = "END";
  ImageFit[ImageFit["BOTTOM_START"] = 13] = "BOTTOM_START";
  ImageFit[ImageFit["BOTTOM"] = 14] = "BOTTOM";
  ImageFit[ImageFit["BOTTOM_END"] = 15] = "BOTTOM_END";
})(ImageFit || (ImageFit = {}));

var DynamicRangeMode ;
(function (DynamicRangeMode ) {
  DynamicRangeMode [DynamicRangeMode ["HIGH"] = 0] = "HIGH";
  DynamicRangeMode [DynamicRangeMode ["CONSTRAINT"] = 1] = "CONSTRAINT";
  DynamicRangeMode [DynamicRangeMode ["STANDARD"] = 2] = "STANDARD";
})(DynamicRangeMode  || (DynamicRangeMode  = {}));

var ImageContent;
(function (ImageContent) {
  ImageContent[ImageContent["EMPTY"] = 0] = "EMPTY";
})(ImageContent || (ImageContent = {}));

var ImageRepeat;
(function (ImageRepeat) {
  ImageRepeat[ImageRepeat["NoRepeat"] = 0] = "NoRepeat";
  ImageRepeat[ImageRepeat["X"] = 1] = "X";
  ImageRepeat[ImageRepeat["Y"] = 2] = "Y";
  ImageRepeat[ImageRepeat["XY"] = 3] = "XY";
})(ImageRepeat || (ImageRepeat = {}));

var ImageSize;
(function (ImageSize) {
  ImageSize[ImageSize["Contain"] = 0] = "Contain";
  ImageSize[ImageSize["Cover"] = 1] = "Cover";
  ImageSize[ImageSize["Auto"] = 2] = "Auto";
  ImageSize[ImageSize["FILL"] = 3] = "FILL";
})(ImageSize || (ImageSize = {}));

var ImageRenderMode;
(function (ImageRenderMode) {
  ImageRenderMode[ImageRenderMode["Original"] = 0] = "Original";
  ImageRenderMode[ImageRenderMode["Template"] = 1] = "Template";
})(ImageRenderMode || (ImageRenderMode = {}));

var ImageInterpolation;
(function (ImageInterpolation) {
  ImageInterpolation[ImageInterpolation["None"] = 0] = "None";
  ImageInterpolation[ImageInterpolation["Low"] = 1] = "Low";
  ImageInterpolation[ImageInterpolation["Medium"] = 2] = "Medium";
  ImageInterpolation[ImageInterpolation["High"] = 3] = "High";
})(ImageInterpolation || (ImageInterpolation = {}));

var FontStyle;
(function (FontStyle) {
  FontStyle[FontStyle["Normal"] = 0] = "Normal";
  FontStyle[FontStyle["Italic"] = 1] = "Italic";
})(FontStyle || (FontStyle = {}));

var FlexAlign;
(function (FlexAlign) {
  FlexAlign[FlexAlign["Start"] = 1] = "Start";
  FlexAlign[FlexAlign["Center"] = 2] = "Center";
  FlexAlign[FlexAlign["End"] = 3] = "End";
  FlexAlign[FlexAlign["Stretch"] = 4] = "Stretch";
  FlexAlign[FlexAlign["Baseline"] = 5] = "Baseline";
  FlexAlign[FlexAlign["SpaceBetween"] = 6] = "SpaceBetween";
  FlexAlign[FlexAlign["SpaceAround"] = 7] = "SpaceAround";
  FlexAlign[FlexAlign["SpaceEvenly"] = 8] = "SpaceEvenly";
})(FlexAlign || (FlexAlign = {}));

var PixelRoundCalcPolicy;
(function (PixelRoundCalcPolicy) {
  PixelRoundCalcPolicy[PixelRoundCalcPolicy["NO_FORCE_ROUND"] = 0] = "NO_FORCE_ROUND";
  PixelRoundCalcPolicy[PixelRoundCalcPolicy["FORCE_CEIL"] = 1] = "FORCE_CEIL";
  PixelRoundCalcPolicy[PixelRoundCalcPolicy["FORCE_FLOOR"] = 2] = "FORCE_FLOOR";
})(PixelRoundCalcPolicy || (PixelRoundCalcPolicy = {}));

var VerticalAlign;
(function (VerticalAlign) {
  VerticalAlign[VerticalAlign["Top"] = 1] = "Top";
  VerticalAlign[VerticalAlign["Center"] = 2] = "Center";
  VerticalAlign[VerticalAlign["Bottom"] = 3] = "Bottom";
})(VerticalAlign || (VerticalAlign = {}));

var HorizontalAlign;
(function (HorizontalAlign) {
  HorizontalAlign[HorizontalAlign["Start"] = 1] = "Start";
  HorizontalAlign[HorizontalAlign["Center"] = 2] = "Center";
  HorizontalAlign[HorizontalAlign["End"] = 3] = "End";
})(HorizontalAlign || (HorizontalAlign = {}));

var ItemAlign;
(function (ItemAlign) {
  ItemAlign[ItemAlign["Auto"] = 0] = "Auto";
  ItemAlign[ItemAlign["Start"] = 1] = "Start";
  ItemAlign[ItemAlign["Center"] = 2] = "Center";
  ItemAlign[ItemAlign["End"] = 3] = "End";
  ItemAlign[ItemAlign["Stretch"] = 4] = "Stretch";
  ItemAlign[ItemAlign["Baseline"] = 5] = "Baseline";
})(ItemAlign || (ItemAlign = {}));

var Align;
(function (Align) {
  Align[Align["Start"] = 4] = "Start";
  Align[Align["Center"] = 2] = "Center";
  Align[Align["End"] = 5] = "End";
})(Align || (Align = {}));

var Alignment;
(function (Alignment) {
  Alignment[Alignment["TopStart"] = 0] = "TopStart";
  Alignment[Alignment["Top"] = 1] = "Top";
  Alignment[Alignment["TopEnd"] = 2] = "TopEnd";
  Alignment[Alignment["Start"] = 3] = "Start";
  Alignment[Alignment["Center"] = 4] = "Center";
  Alignment[Alignment["End"] = 5] = "End";
  Alignment[Alignment["BottomStart"] = 6] = "BottomStart";
  Alignment[Alignment["Bottom"] = 7] = "Bottom";
  Alignment[Alignment["BottomEnd"] = 8] = "BottomEnd";
})(Alignment || (Alignment = {}));

var ChainStyle;
(function (ChainStyle) {
  ChainStyle[ChainStyle["SPREAD"] = 0] = "SPREAD";
  ChainStyle[ChainStyle["SPREAD_INSIDE"] = 1] = "SPREAD_INSIDE";
  ChainStyle[ChainStyle["PACKED"] = 2] = "PACKED";
})(ChainStyle || (ChainStyle = {}));

var BarrierDirection;
(function (BarrierDirection) {
  BarrierDirection[BarrierDirection["LEFT"] = 0] = "LEFT";
  BarrierDirection[BarrierDirection["RIGHT"] = 1] = "RIGHT";
  BarrierDirection[BarrierDirection["TOP"] = 2] = "TOP";
  BarrierDirection[BarrierDirection["BOTTOM"] = 3] = "BOTTOM";
})(BarrierDirection || (BarrierDirection = {}));

var LocalizedBarrierDirection;
(function (LocalizedBarrierDirection) {
  LocalizedBarrierDirection[LocalizedBarrierDirection["START"] = 0] = "START";
  LocalizedBarrierDirection[LocalizedBarrierDirection["END"] = 1] = "END";
  LocalizedBarrierDirection[LocalizedBarrierDirection["TOP"] = 2] = "TOP";
  LocalizedBarrierDirection[LocalizedBarrierDirection["BOTTOM"] = 3] = "BOTTOM";
})(LocalizedBarrierDirection || (LocalizedBarrierDirection = {}));

var BlendMode;
(function (BlendMode) {
  BlendMode[BlendMode["NORMAL"] = 0] = "NORMAL";
  BlendMode[BlendMode["DESTINATION_IN"] = 7] = "DESTINATION_IN";
  BlendMode[BlendMode["SOURCE_IN"] = 5000] = "SOURCE_IN";
  BlendMode[BlendMode["NONE"] = 0] = "NONE";
  BlendMode[BlendMode["CLEAR"] = 1] = "CLEAR";
  BlendMode[BlendMode["SRC"] = 2] = "SRC";
  BlendMode[BlendMode["DST"] = 3] = "DST";
  BlendMode[BlendMode["SRC_OVER"] = 4] = "SRC_OVER";
  BlendMode[BlendMode["DST_OVER"] = 5] = "DST_OVER";
  BlendMode[BlendMode["SRC_IN"] = 6] = "SRC_IN";
  BlendMode[BlendMode["DST_IN"] = 7] = "DST_IN";
  BlendMode[BlendMode["SRC_OUT"] = 8] = "SRC_OUT";
  BlendMode[BlendMode["DST_OUT"] = 9] = "DST_OUT";
  BlendMode[BlendMode["SRC_ATOP"] = 10] = "SRC_ATOP";
  BlendMode[BlendMode["DST_ATOP"] = 11] = "DST_ATOP";
  BlendMode[BlendMode["XOR"] = 12] = "XOR";
  BlendMode[BlendMode["PLUS"] = 13] = "PLUS";
  BlendMode[BlendMode["MODULATE"] = 14] = "MODULATE";
  BlendMode[BlendMode["SCREEN"] = 15] = "SCREEN";
  BlendMode[BlendMode["OVERLAY"] = 16] = "OVERLAY";
  BlendMode[BlendMode["DARKEN"] = 17] = "DARKEN";
  BlendMode[BlendMode["LIGHTEN"] = 18] = "LIGHTEN";
  BlendMode[BlendMode["COLOR_DODGE"] = 19] = "COLOR_DODGE";
  BlendMode[BlendMode["COLOR_BURN"] = 20] = "COLOR_BURN";
  BlendMode[BlendMode["HARD_LIGHT"] = 21] = "HARD_LIGHT";
  BlendMode[BlendMode["SOFT_LIGHT"] = 22] = "SOFT_LIGHT";
  BlendMode[BlendMode["DIFFERENCE"] = 23] = "DIFFERENCE";
  BlendMode[BlendMode["EXCLUSION"] = 24] = "EXCLUSION";
  BlendMode[BlendMode["MULTIPLY"] = 25] = "MULTIPLY";
  BlendMode[BlendMode["HUE"] = 26] = "HUE";
  BlendMode[BlendMode["SATURATION"] = 27] = "SATURATION";
  BlendMode[BlendMode["COLOR"] = 28] = "COLOR";
  BlendMode[BlendMode["LUMINOSITY"] = 29] = "LUMINOSITY";
})(BlendMode || (BlendMode = {}));

var BlendApplyType;
(function (BlendApplyType) {
  BlendApplyType[BlendApplyType["FAST"] = 0] = "FAST";
  BlendApplyType[BlendApplyType["OFFSCREEN"] = 1] = "OFFSCREEN";
})(BlendApplyType || (BlendApplyType = {}));

var TextOverflow;
(function (TextOverflow) {
  TextOverflow[TextOverflow["None"] = 0] = "None";
  TextOverflow[TextOverflow["Clip"] = 1] = "Clip";
  TextOverflow[TextOverflow["Ellipsis"] = 2] = "Ellipsis";
  TextOverflow[TextOverflow["Marquee"] = 3] = "Marquee";
  TextOverflow[TextOverflow["MARQUEE"] = 3] = "MARQUEE";
})(TextOverflow || (TextOverflow = {}));

var TextDecorationStyle;
(function (TextDecorationStyle) {
  TextDecorationStyle[TextDecorationStyle["SOLID"] = 0] = "SOLID";
  TextDecorationStyle[TextDecorationStyle["DOUBLE"] = 1] = "DOUBLE";
  TextDecorationStyle[TextDecorationStyle["DOTTED"] = 2] = "DOTTED";
  TextDecorationStyle[TextDecorationStyle["DASHED"] = 3] = "DASHED";
  TextDecorationStyle[TextDecorationStyle["WAVY"] = 4] = "WAVY";
})(TextDecorationStyle || (TextDecorationStyle = {}));

var TextDecorationType;
(function (TextDecorationType) {
  TextDecorationType[TextDecorationType["None"] = 0] = "None";
  TextDecorationType[TextDecorationType["Underline"] = 1] = "Underline";
  TextDecorationType[TextDecorationType["Overline"] = 2] = "Overline";
  TextDecorationType[TextDecorationType["LineThrough"] = 3] = "LineThrough";
})(TextDecorationType || (TextDecorationType = {}));

var ClickEffectLevel;
(function (ClickEffectLevel) {
  ClickEffectLevel[ClickEffectLevel["LIGHT"] = 0] = "LIGHT";
  ClickEffectLevel[ClickEffectLevel["MIDDLE"] = 1] = "MIDDLE";
  ClickEffectLevel[ClickEffectLevel["HEAVY"] = 2] = "HEAVY";
})(ClickEffectLevel || (ClickEffectLevel = {}));

var TextCase;
(function (TextCase) {
  TextCase[TextCase["Normal"] = 0] = "Normal";
  TextCase[TextCase["LowerCase"] = 1] = "LowerCase";
  TextCase[TextCase["UpperCase"] = 2] = "UpperCase";
})(TextCase || (TextCase = {}));

var NavigationType;
(function (NavigationType) {
  NavigationType[NavigationType["Push"] = 1] = "Push";
  NavigationType[NavigationType["Replace"] = 2] = "Replace";
  NavigationType[NavigationType["Back"] = 3] = "Back";
})(NavigationType || (NavigationType = {}));

var PanelType;
(function (PanelType) {
  PanelType[PanelType["Minibar"] = 0] = "Minibar";
  PanelType[PanelType["Foldable"] = 1] = "Foldable";
  PanelType[PanelType["Temporary"] = 2] = "Temporary";
  PanelType[PanelType["CUSTOM"] = 3] = "CUSTOM";
})(PanelType || (PanelType = {}));

var PanelHeight;
(function (PanelHeight) {
  PanelHeight[PanelHeight["WRAP_CONTENT"] = "wrapContent"] = "WRAP_CONTENT";
})(PanelHeight || (PanelHeight = {}));

var PanelMode;
(function (PanelMode) {
  PanelMode[PanelMode["Mini"] = 0] = "Mini";
  PanelMode[PanelMode["Half"] = 1] = "Half";
  PanelMode[PanelMode["Full"] = 2] = "Full";
})(PanelMode || (PanelMode = {}));

var Axis;
(function (Axis) {
  Axis[Axis["Vertical"] = 0] = "Vertical";
  Axis[Axis["Horizontal"] = 1] = "Horizontal";
})(Axis || (Axis = {}));

var BarState;
(function (BarState) {
  BarState[BarState["Off"] = 0] = "Off";
  BarState[BarState["Auto"] = 1] = "Auto";
  BarState[BarState["On"] = 2] = "On";
})(BarState || (BarState = {}));

var EdgeEffect;
(function (EdgeEffect) {
  EdgeEffect[EdgeEffect["Spring"] = 0] = "Spring";
  EdgeEffect[EdgeEffect["Fade"] = 1] = "Fade";
  EdgeEffect[EdgeEffect["None"] = 2] = "None";
})(EdgeEffect || (EdgeEffect = {}));

var SwipeEdgeEffect;
(function (SwipeEdgeEffect) {
  SwipeEdgeEffect[SwipeEdgeEffect["Spring"] = 0] = "Spring";
  SwipeEdgeEffect[SwipeEdgeEffect["None"] = 1] = "None";
})(SwipeEdgeEffect || (SwipeEdgeEffect = {}));

var ScrollState;
(function (ScrollState) {
  ScrollState[ScrollState["Idle"] = 0] = "Idle";
  ScrollState[ScrollState["Scroll"] = 1] = "Scroll";
  ScrollState[ScrollState["Fling"] = 2] = "Fling";
})(ScrollState || (ScrollState = {}));

var ScrollSource;
(function (ScrollSource) {
  ScrollSource[ScrollSource["DRAG"] = 0] = "DRAG";
  ScrollSource[ScrollSource["FLING"] = 1] = "FLING";
  ScrollSource[ScrollSource["EDGE_EFFECT"] = 2] = "EDGE_EFFECT";
  ScrollSource[ScrollSource["OTHER_USER_INPUT"] = 3] = "OTHER_USER_INPUT";
  ScrollSource[ScrollSource["SCROLL_BAR"] = 4] = "SCROLL_BAR";
  ScrollSource[ScrollSource["SCROLL_BAR_FLING"] = 5] = "SCROLL_BAR_FLING";
  ScrollSource[ScrollSource["SCROLLER"] = 6] = "SCROLLER";
  ScrollSource[ScrollSource["SCROLLER_ANIMATION"] = 7] = "SCROLLER_ANIMATION";
})(ScrollSource || (ScrollSource = {}));

var TouchType;
(function (TouchType) {
  TouchType[TouchType["Down"] = 0] = "Down";
  TouchType[TouchType["Up"] = 1] = "Up";
  TouchType[TouchType["Move"] = 2] = "Move";
  TouchType[TouchType["Cancel"] = 3] = "Cancel";
})(TouchType || (TouchType = {}));

var MouseButton;
(function (MouseButton) {
  MouseButton[MouseButton["None"] = 0] = "None";
  MouseButton[MouseButton["Left"] = 1] = "Left";
  MouseButton[MouseButton["Right"] = 2] = "Right";
  MouseButton[MouseButton["Middle"] = 4] = "Middle";
  MouseButton[MouseButton["Back"] = 8] = "Back";
  MouseButton[MouseButton["Forward"] = 16] = "Forward";
})(MouseButton || (MouseButton = {}));

var MouseAction;
(function (MouseAction) {
  MouseAction[MouseAction["None"] = 0] = "None";
  MouseAction[MouseAction["Press"] = 1] = "Press";
  MouseAction[MouseAction["Release"] = 2] = "Release";
  MouseAction[MouseAction["Move"] = 3] = "Move";
  MouseAction[MouseAction["Hover"] = 4] = "Hover";
})(MouseAction || (MouseAction = {}));

var KeyType;
(function (KeyType) {
  KeyType[KeyType["Down"] = 0] = "Down";
  KeyType[KeyType["Up"] = 1] = "Up";
  KeyType[KeyType["LongPress"] = 2] = "LongPress";
})(KeyType || (KeyType = {}));

var GestureMode;
(function (GestureMode) {
  GestureMode[GestureMode["Sequence"] = 0] = "Sequence";
  GestureMode[GestureMode["Parallel"] = 1] = "Parallel";
  GestureMode[GestureMode["Exclusive"] = 2] = "Exclusive";
})(GestureMode || (GestureMode = {}));

var PanDirection;
(function (PanDirection) {
  PanDirection[PanDirection["None"] = 0] = "None";
  PanDirection[PanDirection["Left"] = 1] = "Left";
  PanDirection[PanDirection["Right"] = 2] = "Right";
  PanDirection[PanDirection["Horizontal"] = 3] = "Horizontal";
  PanDirection[PanDirection["Up"] = 4] = "Up";
  PanDirection[PanDirection["Down"] = 8] = "Down";
  PanDirection[PanDirection["Vertical"] = 12] = "Vertical";
  PanDirection[PanDirection["All"] = 15] = "All";
})(PanDirection || (PanDirection = {}));

var SwipeDirection;
(function (SwipeDirection) {
  SwipeDirection[SwipeDirection["None"] = 0] = "None";
  SwipeDirection[SwipeDirection["Horizontal"] = 1] = "Horizontal";
  SwipeDirection[SwipeDirection["Vertical"] = 2] = "Vertical";
  SwipeDirection[SwipeDirection["All"] = 3] = "All";
})(SwipeDirection || (SwipeDirection = {}));

var GestureDirection;
(function (GestureDirection) {
  GestureDirection[GestureDirection["All"] = 0] = "All";
  GestureDirection[GestureDirection["Horizontal"] = 1] = "Horizontal";
  GestureDirection[GestureDirection["Vertical"] = 2] = "Vertical";
})(GestureDirection || (GestureDirection = {}));

var GestureMask;
(function (GestureMask) {
  GestureMask[GestureMask["Normal"] = 0] = "Normal";
  GestureMask[GestureMask["IgnoreInternal"] = 1] = "IgnoreInternal";
})(GestureMask || (GestureMask = {}));

var GesturePriority;
(function (GesturePriority) {
  GesturePriority[GesturePriority["Low"] = 0] = "Low";
  GesturePriority[GesturePriority["NORMAL"] = 0] = "NORMAL";
  GesturePriority[GesturePriority["High"] = 1] = "High";
  GesturePriority[GesturePriority["PRIORITY"] = 1] = "PRIORITY";
  GesturePriority[GesturePriority["Parallel"] = 2] = "Parallel";
  GesturePriority[GesturePriority["PARALLEL"] = 2] = "PARALLEL";
})(GesturePriority || (GesturePriority = {}));

var Visibility;
(function (Visibility) {
  Visibility[Visibility["Visible"] = 0] = "Visible";
  Visibility[Visibility["Hidden"] = 1] = "Hidden";
  Visibility[Visibility["None"] = 2] = "None";
})(Visibility || (Visibility = {}));

var RelateType;
(function (RelateType) {
  RelateType[RelateType["FILL"] = 0] = "FILL";
  RelateType[RelateType["FIT"] = 1] = "FIT";
})(RelateType || (RelateType = {}));

var FlexDirection;
(function (FlexDirection) {
  FlexDirection[FlexDirection["Row"] = 0] = "Row";
  FlexDirection[FlexDirection["Column"] = 1] = "Column";
  FlexDirection[FlexDirection["RowReverse"] = 2] = "RowReverse";
  FlexDirection[FlexDirection["ColumnReverse"] = 3] = "ColumnReverse";
})(FlexDirection || (FlexDirection = {}));

var FlexWrap;
(function (FlexWrap) {
  FlexWrap[FlexWrap["NoWrap"] = 0] = "NoWrap";
  FlexWrap[FlexWrap["Wrap"] = 1] = "Wrap";
  FlexWrap[FlexWrap["WrapReverse"] = 2] = "WrapReverse";
})(FlexWrap || (FlexWrap = {}));

var BlurStyle;
(function (BlurStyle) {
  BlurStyle[BlurStyle["SmallLight"] = 100] = "SmallLight";
  BlurStyle[BlurStyle["MediumLight"] = 101] = "MediumLight";
  BlurStyle[BlurStyle["LargeLight"] = 102] = "LargeLight";
  BlurStyle[BlurStyle["XlargeLight"] = 103] = "XlargeLight";
  BlurStyle[BlurStyle["SmallDark"] = 104] = "SmallDark";
  BlurStyle[BlurStyle["MediumDark"] = 105] = "MediumDark";
  BlurStyle[BlurStyle["LargeDark"] = 106] = "LargeDark";
  BlurStyle[BlurStyle["XlargeDark"] = 107] = "XlargeDark";
})(BlurStyle || (BlurStyle = {}));

var Edge;
(function (Edge) {
  Edge[Edge["Top"] = 0] = "Top";
  Edge[Edge["Center"] = 1] = "Center";
  Edge[Edge["Bottom"] = 2] = "Bottom";
  Edge[Edge["Baseline"] = 3] = "Baseline";
  Edge[Edge["Start"] = 4] = "Start";
  Edge[Edge["Middle"] = 5] = "Middle";
  Edge[Edge["End"] = 6] = "End";
})(Edge || (Edge = {}));

var LineJoinStyle;
(function (LineJoinStyle) {
  LineJoinStyle[LineJoinStyle["Miter"] = 0] = "Miter";
  LineJoinStyle[LineJoinStyle["Round"] = 1] = "Round";
  LineJoinStyle[LineJoinStyle["Bevel"] = 2] = "Bevel";
})(LineJoinStyle || (LineJoinStyle = {}));

var AnimationStatus;
(function (AnimationStatus) {
  AnimationStatus[AnimationStatus["Initial"] = 0] = "Initial";
  AnimationStatus[AnimationStatus["Running"] = 1] = "Running";
  AnimationStatus[AnimationStatus["Paused"] = 2] = "Paused";
  AnimationStatus[AnimationStatus["Stopped"] = 3] = "Stopped";
})(AnimationStatus || (AnimationStatus = {}));

var Motion;
(function (Motion) {
  Motion[Motion["SpringMotion"] = 0] = "SpringMotion";
  Motion[Motion["FrictionMotion"] = 1] = "FrictionMotion";
  Motion[Motion["ScrollMotion"] = 2] = "ScrollMotion";
})(Motion || (Motion = {}));

var ScrollDirection;
(function (ScrollDirection) {
  ScrollDirection[ScrollDirection["Vertical"] = 0] = "Vertical";
  ScrollDirection[ScrollDirection["Horizontal"] = 1] = "Horizontal";
  ScrollDirection[ScrollDirection["Free"] = 2] = "Free";
  ScrollDirection[ScrollDirection["None"] = 3] = "None";
})(ScrollDirection || (ScrollDirection = {}));

var Sticky;
(function (Sticky) {
  Sticky[Sticky["None"] = 0] = "None";
  Sticky[Sticky["Normal"] = 1] = "Normal";
  Sticky[Sticky["Opacity"] = 2] = "Opacity";
})(Sticky || (Sticky = {}));

var StickyStyle;
(function (StickyStyle) {
  StickyStyle[StickyStyle["None"] = 0] = "None";
  StickyStyle[StickyStyle["Header"] = 1] = "Header";
  StickyStyle[StickyStyle["Footer"] = 2] = "Footer";
})(StickyStyle || (StickyStyle = {}));

var ScrollSnapAlign;
(function (ScrollSnapAlign) {
  ScrollSnapAlign[ScrollSnapAlign["NONE"] = 0] = "NONE";
  ScrollSnapAlign[ScrollSnapAlign["START"] = 1] = "START";
  ScrollSnapAlign[ScrollSnapAlign["CENTER"] = 2] = "CENTER";
  ScrollSnapAlign[ScrollSnapAlign["END"] = 3] = "END";
})(ScrollSnapAlign || (ScrollSnapAlign = {}));

var ChainEdgeEffect;
(function (ChainEdgeEffect) {
  ChainEdgeEffect[ChainEdgeEffect["DEFAULT"] = 0] = "DEFAULT";
  ChainEdgeEffect[ChainEdgeEffect["STRETCH"] = 1] = "STRETCH";
})(ChainEdgeEffect || (ChainEdgeEffect = {}));

var Week;
(function (Week) {
  Week["Mon"] = 0b0000001;
  Week["Tue"] = 0b0000010;
  Week["Wed"] = 0b0000100;
  Week["Thur"] = 0b0001000;
  Week["Fri"] = 0b0010000;
  Week["Sat"] = 0b0100000;
  Week["Sun"] = 0b1000000;
})(Week || (Week = {}));

var FormDimension;
(function (FormDimension) {
  FormDimension["Dimension_1_2"] = 1;
  FormDimension["Dimension_2_2"] = 2;
  FormDimension["Dimension_2_4"] = 3;
  FormDimension["Dimension_4_4"] = 4;
  FormDimension["Dimension_2_1"] = 5;
  FormDimension["DIMENSION_1_1"] = 6;
  FormDimension["DIMENSION_6_4"] = 7;
})(FormDimension || (FormDimension = {}));

let FormShape;
(function (FormShape) {
  FormShape.RECT = 1;
  FormShape.CIRCLE = 2;
})(FormShape || (FormShape = {}));

let FormRenderingMode;
(function (FormRenderingMode) {
  FormRenderingMode.FULL_COLOR = 0;
  FormRenderingMode.SINGLE_COLOR = 1;
})(FormRenderingMode || (FormRenderingMode = {}));

var TransitionType;
(function (TransitionType) {
  TransitionType["All"] = "All";
  TransitionType["Insert"] = "Insert";
  TransitionType["Delete"] = "Delete";
})(TransitionType || (TransitionType = {}));

var Direction;
(function (Direction) {
  Direction["Ltr"] = "Ltr";
  Direction["Rtl"] = "Rtl";
  Direction["Auto"] = "Auto";
})(Direction || (Direction = {}));

var RouteType;
(function (RouteType) {
  RouteType[RouteType["None"] = 0] = "None";
  RouteType[RouteType["Push"] = 1] = "Push";
  RouteType[RouteType["Pop"] = 2] = "Pop";
})(RouteType || (RouteType = {}));

var FocusDirection;
(function (FocusDirection) {
  FocusDirection[FocusDirection["Up"] = 19] = "Up";
  FocusDirection[FocusDirection["Down"] = 20] = "Down";
  FocusDirection[FocusDirection["Left"] = 21] = "Left";
  FocusDirection[FocusDirection["Right"] = 22] = "Right";
  FocusDirection[FocusDirection["Tab"] = 61] = "Tab";
  FocusDirection[FocusDirection["ShiftTab"] = 200] = "ShiftTab";
})(FocusDirection || (FocusDirection = {}));

var SlideEffect;
(function (SlideEffect) {
  SlideEffect[SlideEffect["None"] = 0] = "None";
  SlideEffect[SlideEffect["Left"] = 1] = "Left";
  SlideEffect[SlideEffect["Right"] = 2] = "Right";
  SlideEffect[SlideEffect["Top"] = 3] = "Top";
  SlideEffect[SlideEffect["Bottom"] = 4] = "Bottom";
  SlideEffect[SlideEffect["START"] = 5] = "START";
  SlideEffect[SlideEffect["END"] = 6] = "END";
})(SlideEffect || (SlideEffect = {}));

var GradientDirection;
(function (GradientDirection) {
  GradientDirection[GradientDirection["Left"] = 0] = "Left";
  GradientDirection[GradientDirection["Top"] = 1] = "Top";
  GradientDirection[GradientDirection["Right"] = 2] = "Right";
  GradientDirection[GradientDirection["Bottom"] = 3] = "Bottom";
  GradientDirection[GradientDirection["LeftTop"] = 4] = "Bottom";
  GradientDirection[GradientDirection["LeftBottom"] = 5] = "Bottom";
  GradientDirection[GradientDirection["RightTop"] = 6] = "Bottom";
  GradientDirection[GradientDirection["RightBottom"] = 7] = "Bottom";
  GradientDirection[GradientDirection["None"] = 8] = "None";
})(GradientDirection || (GradientDirection = {}));

var BarMode;
(function (BarMode) {
  BarMode["Fixed"] = "Fixed";
  BarMode["Scrollable"] = "Scrollable";
})(BarMode || (BarMode = {}));

var AnimationMode;
(function (AnimationMode) {
  AnimationMode[AnimationMode["CONTENT_FIRST"] = 0] = "CONTENT_FIRST";
  AnimationMode[AnimationMode["ACTION_FIRST"] = 1] = "ACTION_FIRST";
  AnimationMode[AnimationMode["NO_ANIMATION"] = 2] = "NO_ANIMATION";
})(AnimationMode || (AnimationMode = {}));

var SelectedMode;
(function (SelectedMode) {
  SelectedMode[SelectedMode["INDICATOR"] = 0] = "INDICATOR";
  SelectedMode[SelectedMode["BOARD"] = 1] = "BOARD";
})(SelectedMode || (SelectedMode = {}));

var LayoutMode;
(function (LayoutMode) {
  LayoutMode[LayoutMode["AUTO"] = 0] = "AUTO";
  LayoutMode[LayoutMode["VERTICAL"] = 1] = "VERTICAL";
  LayoutMode[LayoutMode["HORIZONTAL"] = 2] = "HORIZONTAL";
})(LayoutMode || (LayoutMode = {}));

var LayoutStyle;
(function (LayoutStyle) {
  LayoutStyle[LayoutStyle["ALWAYS_CENTER"] = 0] = "ALWAYS_CENTER";
  LayoutStyle[LayoutStyle["ALWAYS_AVERAGE_SPLIT"] = 1] = "ALWAYS_AVERAGE_SPLIT";
  LayoutStyle[LayoutStyle["SPACE_BETWEEN_OR_CENTER"] = 2] = "SPACE_BETWEEN_OR_CENTER";
})(LayoutStyle || (LayoutStyle = {}));

var SizeType;
(function (SizeType) {
  SizeType[SizeType["Auto"] = 0] = "Auto";
  SizeType[SizeType["XS"] = 1] = "XS";
  SizeType[SizeType["SM"] = 2] = "SM";
  SizeType[SizeType["MD"] = 3] = "MD";
  SizeType[SizeType["LG"] = 4] = "LG";
})(SizeType || (SizeType = {}));

var CancelButtonStyle;
(function (CancelButtonStyle) {
  CancelButtonStyle["CONSTANT"] = "CONSTANT";
  CancelButtonStyle["INVISIBLE"] = "INVISIBLE";
  CancelButtonStyle["INPUT"] = "INPUT";
})(CancelButtonStyle || (CancelButtonStyle = {}));

var ColorMode;
(function (ColorMode) {
  ColorMode[ColorMode["LIGHT"] = 0] = "LIGHT";
  ColorMode[ColorMode["DARK"] = 1] = "DARK";
})(ColorMode || (ColorMode = {}));
var LayoutDirection;
(function (LayoutDirection) {
  LayoutDirection[LayoutDirection["RTL"] = 0] = "RTL";
  LayoutDirection[LayoutDirection["LTR"] = 1] = "LTR";
})(LayoutDirection || (LayoutDirection = {}));

function isSystemplugin(shortName, moduleType) {
  const plugin = moduleType === 'ohos' ? globalThis.ohosplugin : globalThis.systemplugin;
  if (typeof (plugin) !== 'undefined') {
    var target = plugin;
    for (let key of shortName.split('.')) {
      target = target[key];
      if (!target) {
        break;
      }
    }
    return typeof (target) !== 'undefined';
  }
}

var BarPosition;
(function (BarPosition) {
  BarPosition[BarPosition["Start"] = 0] = "Start";
  BarPosition[BarPosition["End"] = 1] = "End";
})(BarPosition || (BarPosition = {}));

var SharedTransitionEffectType;
(function (SharedTransitionEffectType) {
  SharedTransitionEffectType[SharedTransitionEffectType["Static"] = 0] = "Static";
  SharedTransitionEffectType[SharedTransitionEffectType["Exchange"] = 1] = "Exchange";
})(SharedTransitionEffectType || (SharedTransitionEffectType = {}));

function $r(id, type, ...params) {
  return { "id": id, "type": type, "params": params };
}

function $rawfile(fileName) {
  return { "id": 0, "type": 30000, "params": [fileName] };
}

var IndexerAlign;
(function (IndexerAlign) {
  IndexerAlign[IndexerAlign["Left"] = 0] = "Left";
  IndexerAlign[IndexerAlign["Right"] = 1] = "Right";
  IndexerAlign[IndexerAlign["START"] = 2] = "START";
  IndexerAlign[IndexerAlign["END"] = 3] = "END";
})(IndexerAlign || (IndexerAlign = {}));

var DialogAlignment;
(function (DialogAlignment) {
  DialogAlignment[DialogAlignment["Top"] = 0] = "Top";
  DialogAlignment[DialogAlignment["Center"] = 1] = "Center";
  DialogAlignment[DialogAlignment["Bottom"] = 2] = "Bottom";
  DialogAlignment[DialogAlignment["Default"] = 3] = "Default";
  DialogAlignment[DialogAlignment["TopStart"] = 4] = "TopStart";
  DialogAlignment[DialogAlignment["TopEnd"] = 5] = "TopEnd";
  DialogAlignment[DialogAlignment["CenterStart"] = 6] = "CenterStart";
  DialogAlignment[DialogAlignment["CenterEnd"] = 7] = "CenterEnd";
  DialogAlignment[DialogAlignment["BottomStart"] = 8] = "BottomStart";
  DialogAlignment[DialogAlignment["BottomEnd"] = 9] = "BottomEnd";
})(DialogAlignment || (DialogAlignment = {}));

let HoverModeAreaType;
(function (HoverModeAreaType) {
  HoverModeAreaType.TOP_SCREEN = 0;
  HoverModeAreaType.BOTTOM_SCREEN = 1;
})(HoverModeAreaType || (HoverModeAreaType = {}));

var DialogButtonStyle;
(function (DialogButtonStyle) {
  DialogButtonStyle[DialogButtonStyle["DEFAULT"] = 0] = "DEFAULT";
  DialogButtonStyle[DialogButtonStyle["HIGHLIGHT"] = 1] = "HIGHLIGHT";
})(DialogButtonStyle || (DialogButtonStyle = {}));

var EditMode;
(function (EditMode) {
  EditMode[EditMode["None"] = 0] = "None";
  EditMode[EditMode["Deletable"] = 1] = "Deletable";
  EditMode[EditMode["Movable"] = 2] = "Movable";
})(EditMode || (EditMode = {}));

var SwiperDisplayMode;
(function (SwiperDisplayMode) {
  SwiperDisplayMode[SwiperDisplayMode["Stretch"] = 0] = "Stretch";
  SwiperDisplayMode[SwiperDisplayMode["AutoLinear"] = 1] = "AutoLinear";
  SwiperDisplayMode[SwiperDisplayMode["STRETCH"] = 0] = "STRETCH";
  SwiperDisplayMode[SwiperDisplayMode["AUTO_LINEAR"] = 1] = "AUTO_LINEAR";
})(SwiperDisplayMode || (SwiperDisplayMode = {}));

var EdgeEffect;
(function (EdgeEffect) {
  EdgeEffect[EdgeEffect["Spring"] = 0] = "Spring";
  EdgeEffect[EdgeEffect["Fade"] = 1] = "Fade";
  EdgeEffect[EdgeEffect["None"] = 2] = "None";
})(EdgeEffect || (EdgeEffect = {}));

var DatePickerType;
(function (DatePickerType) {
  DatePickerType[DatePickerType["Time"] = 0] = "Time";
  DatePickerType[DatePickerType["Date"] = 1] = "Date";
})(DatePickerType || (DatePickerType = {}));

var TimePickerFormat;
(function (TimePickerFormat) {
  TimePickerFormat[TimePickerFormat["HOUR_MINUTE"] = 0] = "HOUR_MINUTE";
  TimePickerFormat[TimePickerFormat["HOUR_MINUTE_SECOND"] = 1] = "HOUR_MINUTE_SECOND";
})(TimePickerFormat || (TimePickerFormat = {}));

var InputType;
(function (InputType) {
  InputType[InputType["Normal"] = 0] = "Normal";
  InputType[InputType["Number"] = 2] = "Number";
  InputType[InputType["PhoneNumber"] = 3] = "PhoneNumber";
  InputType[InputType["Email"] = 5] = "Email";
  InputType[InputType["Password"] = 7] = "Password";
  InputType[InputType["NUMBER_PASSWORD"] = 8] = "NUMBER_PASSWORD";
  InputType[InputType["SCREEN_LOCK_PASSWORD"] = 9] = "SCREEN_LOCK_PASSWORD";
  InputType[InputType["USER_NAME"] = 10] = "USER_NAME";
  InputType[InputType["NEW_PASSWORD"] = 11] = "NEW_PASSWORD";
  InputType[InputType["NUMBER_DECIMAL"] = 12] = "NUMBER_DECIMAL";
  InputType[InputType["URL"] = 13] = "URL";
})(InputType || (InputType = {}));

var SearchType;
(function (SearchType) {
  SearchType[SearchType["NORMAL"] = 0] = "NORMAL";
  SearchType[SearchType["NUMBER"] = 2] = "NUMBER";
  SearchType[SearchType["PHONE_NUMBER"] = 3] = "PHONE_NUMBER";
  SearchType[SearchType["EMAIL"] = 5] = "EMAIL";
  SearchType[SearchType["NUMBER_DECIMAL"] = 12] = "NUMBER_DECIMAL";
  SearchType[SearchType["URL"] = 13] = "URL";
})(SearchType || (SearchType = {}));

var TextAreaType;
(function (TextAreaType) {
  TextAreaType[TextAreaType["NORMAL"] = 0] = "NORMAL";
  TextAreaType[TextAreaType["NUMBER"] = 2] = "NUMBER";
  TextAreaType[TextAreaType["PHONE_NUMBER"] = 3] = "PHONE_NUMBER";
  TextAreaType[TextAreaType["EMAIL"] = 5] = "EMAIL";
  TextAreaType[TextAreaType["NUMBER_DECIMAL"] = 12] = "NUMBER_DECIMAL";
  TextAreaType[TextAreaType["URL"] = 13] = "URL";
})(TextAreaType || (TextAreaType = {}));

var EnterKeyType;
(function (EnterKeyType) {
  EnterKeyType[EnterKeyType["Go"] = 2] = "Go";
  EnterKeyType[EnterKeyType["Search"] = 3] = "Search";
  EnterKeyType[EnterKeyType["Send"] = 4] = "Send";
  EnterKeyType[EnterKeyType["Next"] = 5] = "Next";
  EnterKeyType[EnterKeyType["Done"] = 6] = "Done";
  EnterKeyType[EnterKeyType["PREVIOUS"] = 7] = "PREVIOUS";
  EnterKeyType[EnterKeyType["NEW_LINE"] = 8] = "NEW_LINE";
})(EnterKeyType || (EnterKeyType = {}));

var ItemState
(function (ItemState) {
  ItemState[ItemState["Normal"] = 0] = "Normal";
  ItemState[ItemState["Disabled"] = 1] = "Disabled";
  ItemState[ItemState["Waiting"] = 2] = "Waiting";
  ItemState[ItemState["Skip"] = 3] = "Skip";
})(ItemState || (ItemState = {}));

var NavigationTitleMode;
(function (NavigationTitleMode) {
  NavigationTitleMode[NavigationTitleMode["Free"] = 0] = "Free";
  NavigationTitleMode[NavigationTitleMode["Full"] = 1] = "Full";
  NavigationTitleMode[NavigationTitleMode["Mini"] = 2] = "Mini";
})(NavigationTitleMode || (NavigationTitleMode = {}));

let BarStyle;
(function (BarStyle) {
  BarStyle[BarStyle.STANDARD = 0] = 'STANDARD';
  BarStyle[BarStyle.STACK = 1] = 'STACK';
  BarStyle[BarStyle.SAFE_AREA_PADDING = 2] = 'SAFE_AREA_PADDING';
})(BarStyle || (BarStyle = {}));
var NavigationMode;
(function (NavigationMode) {
  NavigationMode[NavigationMode["Stack"] = 0] = "Stack";
  NavigationMode[NavigationMode["Split"] = 1] = "Split";
  NavigationMode[NavigationMode["Auto"] = 2] = "Auto";
})(NavigationMode || (NavigationMode = {}));

var NavRouteMode;
(function (NavRouteMode) {
  NavRouteMode[NavRouteMode["PUSH_WITH_RECREATE"] = 0] = "PUSH_WITH_RECREATE";
  NavRouteMode[NavRouteMode["PUSH"] = 1] = "PUSH";
  NavRouteMode[NavRouteMode["REPLACE"] = 2] = "REPLACE";
})(NavRouteMode || (NavRouteMode = {}));

var NavBarPosition;
(function (NavBarPosition) {
  NavBarPosition[NavBarPosition["Start"] = 0] = "Start";
  NavBarPosition[NavBarPosition["End"] = 1] = "End";
})(NavBarPosition || (NavBarPosition = {}));

var TitleHeight;
(function (TitleHeight) {
  TitleHeight["MainOnly"] = "MainOnly";
  TitleHeight["MainWithSub"] = "MainWithSub";
})(TitleHeight || (TitleHeight = {}));

var NavDestinationMode;
(function (NavDestinationMode) {
  NavDestinationMode[NavDestinationMode["STANDARD"] = 0] = "STANDARD";
  NavDestinationMode[NavDestinationMode["DIALOG"] = 1] = "DIALOG";
}(NavDestinationMode || (NavDestinationMode = {})));

let NavigationOperation;
(function (NavigationOperation) {
  NavigationOperation[NavigationOperation.PUSH = 1] = "PUSH";
  NavigationOperation[NavigationOperation.POP = 2] = "POP";
  NavigationOperation[NavigationOperation.REPLACE = 3] = "REPLACE";
}(NavigationOperation || (NavigationOperation = {})));

var ResponseType;
(function (ResponseType) {
  ResponseType[ResponseType["RightClick"] = 0] = "RightClick";
  ResponseType[ResponseType["LongPress"] = 1] = "LongPress";
})(ResponseType || (ResponseType = {}));

var RichEditorResponseType;
(function (RichEditorResponseType) {
  RichEditorResponseType[RichEditorResponseType["RIGHT_CLICK"] = 0] = "RIGHT_CLICK";
  RichEditorResponseType[RichEditorResponseType["LONG_PRESS"] = 1] = "LONG_PRESS";
  RichEditorResponseType[RichEditorResponseType["SELECT"] = 2] = "SELECT";
})(RichEditorResponseType || (RichEditorResponseType = {}));

let MenuType;
(function (MenuType) {
  MenuType[MenuType.SELECTION_MENU = 0] = "SELECTION_MENU";
  MenuType[MenuType.PREVIEW_MENU = 1] = "PREVIEW_MENU";
})(MenuType || (MenuType = {}));

var MenuPreviewMode;
(function (MenuPreviewMode) {
  MenuPreviewMode[MenuPreviewMode["NONE"] = 0] = "NONE";
  MenuPreviewMode[MenuPreviewMode["IMAGE"] = 1] = "IMAGE";
})(MenuPreviewMode || (MenuPreviewMode = {}));

let DismissReason;
(function (DismissReason) {
  DismissReason[DismissReason.PRESS_BACK = 0] = "PRESS_BACK";
  DismissReason[DismissReason.TOUCH_OUTSIDE = 1] = "TOUCH_OUTSIDE";
  DismissReason[DismissReason.CLOSE_BUTTON = 2] = "CLOSE_BUTTON";
  DismissReason[DismissReason.SLIDE_DOWN = 3] = "SLIDE_DOWN";
})(DismissReason || (DismissReason = {}));

var HoverEffect;
(function (HoverEffect) {
  HoverEffect[HoverEffect["Auto"] = 4] = "Auto";
  HoverEffect[HoverEffect["Scale"] = 2] = "Scale";
  HoverEffect[HoverEffect["Board"] = 3] = "Board";
  HoverEffect[HoverEffect["Highlight"] = 3] = "Highlight";
  HoverEffect[HoverEffect["None"] = 0] = "None";
})(HoverEffect || (HoverEffect = {}));

var ScrollBarDirection;
(function (ScrollBarDirection) {
  ScrollBarDirection[ScrollBarDirection["Vertical"] = 0] = "Vertical";
  ScrollBarDirection[ScrollBarDirection["Horizontal"] = 1] = "Horizontal";
  ScrollBarDirection[ScrollBarDirection["None"] = 2] = "None";
})(ScrollBarDirection || (ScrollBarDirection = {}));

var Placement;
(function (Placement) {
  Placement[Placement["Left"] = 0] = "Left";
  Placement[Placement["Right"] = 1] = "Right";
  Placement[Placement["Top"] = 2] = "Top";
  Placement[Placement["Bottom"] = 3] = "Bottom";
  Placement[Placement["TopLeft"] = 4] = "TopLeft";
  Placement[Placement["TopRight"] = 5] = "TopRight";
  Placement[Placement["BottomLeft"] = 6] = "BottomLeft";
  Placement[Placement["BottomRight"] = 7] = "BottomRight";
  Placement[Placement["LeftTop"] = 8] = "LeftTop";
  Placement[Placement["LeftBottom"] = 9] = "LeftBottom";
  Placement[Placement["RightTop"] = 10] = "RightTop";
  Placement[Placement["RightBottom"] = 11] = "RightBottom";
})(Placement || (Placement = {}));

var DialogStatus;
(function (DialogStatus) {
  DialogStatus[DialogStatus["Accept"] = 0] = "Accept";
  DialogStatus[DialogStatus["Cancel"] = 1] = "Cancel";
  DialogStatus[DialogStatus["Update"] = 2] = "Update";
})(DialogStatus || (DialogStatus = {}));

var SourceType;
(function (SourceType) {
  SourceType[SourceType["Unknown"] = 0] = "Unknown";
  SourceType[SourceType["Mouse"] = 1] = "Mouse";
  SourceType[SourceType["TouchScreen"] = 2] = "TouchScreen";
  SourceType[SourceType["Keyboard"] = 4] = "Keyboard";
})(SourceType || (SourceType = {}));

var SourceTool;
(function (SourceTool) {
  SourceTool[SourceTool["Unknown"] = 0] = "Unknown";
  SourceTool[SourceTool["FINGER"] = 1] = "FINGER";
  SourceTool[SourceTool["PEN"] = 2] = "PEN";
  SourceTool[SourceTool["MOUSE"] = 7] = "MOUSE";
  SourceTool[SourceTool["TOUCHPAD"] = 9] = "TOUCHPAD";
  SourceTool[SourceTool["JOYSTICK"] = 10] = "JOYSTICK";
})(SourceTool || (SourceTool = {}));

var KeySource;
(function (KeySource) {
  KeySource[KeySource["Unknown"] = 0] = "Unknown";
  KeySource[KeySource["Keyboard"] = 4] = "Keyboard";
})(KeySource || (KeySource = {}));

var SeekMode;
(function (SeekMode) {
  SeekMode[SeekMode["PreviousKeyframe"] = 0] = "PreviousKeyframe";
  SeekMode[SeekMode["NextKeyframe"] = 1] = "NextKeyframe";
  SeekMode[SeekMode["ClosestKeyframe"] = 2] = "ClosestKeyframe";
  SeekMode[SeekMode["Accurate"] = 3] = "Accurate";
})(SeekMode || (SeekMode = {}));

var SideBarContainerType;
(function (SideBarContainerType) {
  SideBarContainerType[SideBarContainerType["AUTO"] = 2] = "AUTO";
  SideBarContainerType[SideBarContainerType["Overlay"] = 1] = "Overlay";
  SideBarContainerType[SideBarContainerType["Embed"] = 0] = "Embed";
})(SideBarContainerType || (SideBarContainerType = {}));

var SideBarPosition;
(function (SideBarPosition) {
  SideBarPosition[SideBarPosition["Start"] = 0] = "Start";
  SideBarPosition[SideBarPosition["End"] = 1] = "End";
})(SideBarPosition || (SideBarPosition = {}));

var PlaybackSpeed;
(function (PlaybackSpeed) {
  PlaybackSpeed["Speed_Forward_0_75_X"] = "0.75";
  PlaybackSpeed["Speed_Forward_1_00_X"] = "1.00";
  PlaybackSpeed["Speed_Forward_1_25_X"] = "1.25";
  PlaybackSpeed["Speed_Forward_1_75_X"] = "1.75";
  PlaybackSpeed["Speed_Forward_2_00_X"] = "2.00";
})(PlaybackSpeed || (PlaybackSpeed = {}));

var MixedMode;
(function (MixedMode) {
  MixedMode[MixedMode["All"] = 0] = "All";
  MixedMode[MixedMode["Compatible"] = 1] = "Compatible";
  MixedMode[MixedMode["None"] = 2] = "None";
})(MixedMode || (MixedMode = {}));

var HitTestType;
(function (HitTestType) {
  HitTestType[HitTestType["EditText"] = 0] = "EditText";
  HitTestType[HitTestType["Email"] = 1] = "Email";
  HitTestType[HitTestType["HttpAnchor"] = 2] = "HttpAnchor";
  HitTestType[HitTestType["HttpAnchorImg"] = 3] = "HttpAnchorImg";
  HitTestType[HitTestType["Img"] = 4] = "Img";
  HitTestType[HitTestType["Map"] = 5] = "Map";
  HitTestType[HitTestType["Phone"] = 6] = "Phone";
  HitTestType[HitTestType["Unknown"] = 7] = "Unknown";
})(HitTestType || (HitTestType = {}));

var CacheMode;
(function (CacheMode) {
  CacheMode[CacheMode["Default"] = 0] = "Default";
  CacheMode[CacheMode["None"] = 1] = "None";
  CacheMode[CacheMode["Online"] = 2] = "Online";
  CacheMode[CacheMode["Only"] = 3] = "Only";
})(CacheMode || (CacheMode = {}));

var WebDarkMode;
(function (WebDarkMode) {
  WebDarkMode[WebDarkMode["Off"] = 0] = "Off";
  WebDarkMode[WebDarkMode["On"] = 1] = "On";
  WebDarkMode[WebDarkMode["Auto"] = 2] = "Auto";
})(WebDarkMode || (WebDarkMode = {}));

var OverScrollMode;
(function (OverScrollMode) {
  OverScrollMode[OverScrollMode["NEVER"] = 0] = "NEVER";
  OverScrollMode[OverScrollMode["ALWAYS"] = 1] = "ALWAYS";
})(OverScrollMode || (OverScrollMode = {}));

var RenderExitReason;
(function (RenderExitReason) {
  RenderExitReason[RenderExitReason["ProcessAbnormalTermination"] = 0] = "ProcessAbnormalTermination";
  RenderExitReason[RenderExitReason["ProcessWasKilled"] = 1] = "ProcessWasKilled";
  RenderExitReason[RenderExitReason["ProcessCrashed"] = 2] = "ProcessCrashed";
  RenderExitReason[RenderExitReason["ProcessOom"] = 3] = "ProcessOom";
  RenderExitReason[RenderExitReason["ProcessExitUnknown"] = 4] = "ProcessExitUnknown";
})(RenderExitReason || (RenderExitReason = {}));

var RenderProcessNotRespondingReason;
(function (RenderProcessNotRespondingReason) {
  RenderProcessNotRespondingReason[RenderProcessNotRespondingReason["INPUT_TIMEOUT"] = 0] = "INPUT_TIMEOUT";
  RenderProcessNotRespondingReason[RenderProcessNotRespondingReason["NAVIGATION_COMMIT_TIMEOUT"] = 1] = "NAVIGATION_COMMIT_TIMEOUT";
})(RenderProcessNotRespondingReason || (RenderProcessNotRespondingReason = {}));

var SslError;
(function (SslError) {
  SslError[SslError["Invalid"] = 0] = "Invalid";
  SslError[SslError["HostMismatch"] = 1] = "HostMismatch";
  SslError[SslError["DateInvalid"] = 2] = "DateInvalid";
  SslError[SslError["Untrusted"] = 3] = "Untrusted";
})(SslError || (SslError = {}));

var FileSelectorMode;
(function (FileSelectorMode) {
  FileSelectorMode[FileSelectorMode["FileOpenMode"] = 0] = "FileOpenMode";
  FileSelectorMode[FileSelectorMode["FileOpenMultipleMode"] = 1] = "FileOpenMultipleMode";
  FileSelectorMode[FileSelectorMode["FileOpenFolderMode"] = 2] = "FileOpenFolderMode";
  FileSelectorMode[FileSelectorMode["FileSaveMode"] = 3] = "FileSaveMode";
})(FileSelectorMode || (FileSelectorMode = {}));

var ProtectedResourceType;
(function (ProtectedResourceType) {
  ProtectedResourceType["MidiSysex"] = "TYPE_MIDI_SYSEX";
  ProtectedResourceType["VIDEO_CAPTURE"] = "TYPE_VIDEO_CAPTURE";
  ProtectedResourceType["AUDIO_CAPTURE"] = "TYPE_AUDIO_CAPTURE";
  ProtectedResourceType["SENSOR"] = "TYPE_SENSOR";
})(ProtectedResourceType || (ProtectedResourceType = {}));

var ProgressType;
(function (ProgressType) {
  ProgressType[ProgressType["Linear"] = 0] = "Linear";
  ProgressType[ProgressType["Ring"] = 1] = "Ring";
  ProgressType[ProgressType["Eclipse"] = 2] = "Eclipse";
  ProgressType[ProgressType["ScaleRing"] = 3] = "ScaleRing";
  ProgressType[ProgressType["Capsule"] = 4] = "Capsule";
})(ProgressType || (ProgressType = {}));

var ProgressStatus;
(function (ProgressStatus) {
  ProgressStatus["LOADING"] = "LOADING";
  ProgressStatus["PROGRESSING"] = "PROGRESSING";
})(ProgressStatus || (ProgressStatus = {}));

var MessageLevel
(function (MessageLevel) {
  MessageLevel[MessageLevel["Debug"] = 1] = "Debug";
  MessageLevel[MessageLevel["Info"] = 2] = "Info";
  MessageLevel[MessageLevel["Warn"] = 3] = "Warn";
  MessageLevel[MessageLevel["Error"] = 4] = "Error";
  MessageLevel[MessageLevel["Log"] = 5] = "Log";
})(MessageLevel || (MessageLevel = {}));

var CopyOptions;
(function (CopyOptions) {
  CopyOptions[CopyOptions["None"] = 0] = "None";
  CopyOptions[CopyOptions["InApp"] = 1] = "InApp";
  CopyOptions[CopyOptions["LocalDevice"] = 2] = "LocalDevice";
  CopyOptions[CopyOptions["CROSS_DEVICE"] = 3] = "CrossDevice";
})(CopyOptions || (CopyOptions = {}));

var SymbolRenderingStrategy;
(function (SymbolRenderingStrategy) {
  SymbolRenderingStrategy[SymbolRenderingStrategy["SINGLE"] = 0] = "SINGLE";
  SymbolRenderingStrategy[SymbolRenderingStrategy["MULTIPLE_COLOR"] = 1] = "MULTIPLE_COLOR";
  SymbolRenderingStrategy[SymbolRenderingStrategy["MULTIPLE_OPACITY"] = 2] = "MULTIPLE_OPACITY";
})(SymbolRenderingStrategy || (SymbolRenderingStrategy = {}));

var SymbolEffectStrategy;
(function (SymbolEffectStrategy) {
  SymbolEffectStrategy[SymbolEffectStrategy["NONE"] = 0] = "NONE";
  SymbolEffectStrategy[SymbolEffectStrategy["SCALE"] = 1] = "SCALE";
  SymbolEffectStrategy[SymbolEffectStrategy["HIERARCHICAL"] = 2] = "HIERARCHICAL";
})(SymbolEffectStrategy || (SymbolEffectStrategy = {}));

var EffectDirection;
(function (EffectDirection) {
  EffectDirection[EffectDirection["DOWN"] = 0] = "DOWN";
  EffectDirection[EffectDirection["UP"] = 1] = "UP";
})(EffectDirection || (EffectDirection = {}));

var EffectScope;
(function (EffectScope) {
  EffectScope[EffectScope["LAYER"] = 0] = "LAYER";
  EffectScope[EffectScope["WHOLE"] = 1] = "WHOLE";
})(EffectScope || (EffectScope = {}));

var EffectFillStyle;
(function (EffectFillStyle) {
  EffectFillStyle[EffectFillStyle["CUMULATIVE"] = 0] = "CUMULATIVE";
  EffectFillStyle[EffectFillStyle["ITERATIVE"] = 1] = "ITERATIVE";
})(EffectFillStyle || (EffectFillStyle = {}));

let WebKeyboardAvoidMode;
(function (WebKeyboardAvoidMode) {
  WebKeyboardAvoidMode[WebKeyboardAvoidMode.RESIZE_VISUAL = 0] = 'RESIZE_VISUAL';
  WebKeyboardAvoidMode[WebKeyboardAvoidMode.RESIZE_CONTENT = 1] = 'RESIZE_CONTENT';
  WebKeyboardAvoidMode[WebKeyboardAvoidMode.OVERLAYS_CONTENT = 2] = 'OVERLAYS_CONTENT';
})(WebKeyboardAvoidMode || (WebKeyboardAvoidMode = {}));

class SymbolEffect {
}

class ScaleSymbolEffect extends SymbolEffect {
  constructor(scope, direction) {
    super();
    this.type = "ScaleSymbolEffect";
    this.scope = scope;
    this.direction = direction;
  }
  scope(value) {
    this.scope = value;
    return this;
  }
  direction(value) {
    this.direction = value;
    return this;
  }
}

class HierarchicalSymbolEffect extends SymbolEffect {
  constructor(fillStyle) {
    super();
    this.type = "HierarchicalSymbolEffect";
    this.fillStyle = fillStyle;
  }
}

class AppearSymbolEffect extends SymbolEffect {
  constructor(scope) {
    super();
    this.type = "AppearSymbolEffect";
    this.scope = scope;
  }
  scope(value) {
    this.scope = value;
    return this;
  }
}
class DisappearSymbolEffect extends SymbolEffect {
  constructor(scope) {
    super();
    this.type = "DisappearSymbolEffect";
    this.scope = scope;
  }
  scope(value) {
    this.scope = value;
    return this;
  }
}

class BounceSymbolEffect extends SymbolEffect {
  constructor(scope, direction) {
    super();
    this.type = "BounceSymbolEffect";
    this.scope = scope;
    this.direction = direction;
  }
  scope(value) {
    this.scope = value;
    return this;
  }
  direction(value) {
    this.direction = value;
    return this;
  }
}

class ReplaceSymbolEffect extends SymbolEffect {
  constructor(scope) {
    super();
    this.type = "ReplaceSymbolEffect";
    this.scope = scope;
  }
  scope(value) {
    this.scope = value;
    return this;
  }
}

class PulseSymbolEffect extends SymbolEffect {
  constructor() {
    super();
    this.type = "PulseSymbolEffect";
  }
}

var RichEditorSpanType;
(function (RichEditorSpanType) {
  RichEditorSpanType[RichEditorSpanType["TEXT"] = 0] = "TEXT";
  RichEditorSpanType[RichEditorSpanType["IMAGE"] = 1] = "IMAGE";
  RichEditorSpanType[RichEditorSpanType["MIXED"] = 2] = "MIXED";
  RichEditorSpanType[RichEditorSpanType["BUILDER"] = 3] = "BUILDER";
})(RichEditorSpanType || (RichEditorSpanType = {}));

var ListItemAlign;
(function (ListItemAlign) {
  ListItemAlign[ListItemAlign["Start"] = 0] = "Start";
  ListItemAlign[ListItemAlign["Center"] = 1] = "Center";
  ListItemAlign[ListItemAlign["End"] = 2] = "End";
})(ListItemAlign || (ListItemAlign = {}));

var BlurStyle;
(function (BlurStyle) {
  BlurStyle[BlurStyle["NoMaterial"] = 0] = "NoMaterial";
  BlurStyle[BlurStyle["Thin"] = 1] = "Thin";
  BlurStyle[BlurStyle["Regular"] = 2] = "Regular";
  BlurStyle[BlurStyle["Thick"] = 3] = "Thick";
  BlurStyle[BlurStyle["BackgroundThin"] = 4] = "BackgroundThin";
  BlurStyle[BlurStyle["BackgroundRegular"] = 5] = "BackgroundRegular";
  BlurStyle[BlurStyle["BackgroundThick"] = 6] = "BackgroundThick";
  BlurStyle[BlurStyle["BackgroundUltraThick"] = 7] = "BackgroundUltraThick";
  BlurStyle[BlurStyle["BACKGROUND_THIN"] = 4] = "BACKGROUND_THIN";
  BlurStyle[BlurStyle["BACKGROUND_REGULAR"] = 5] = "BACKGROUND_REGULAR";
  BlurStyle[BlurStyle["BACKGROUND_THICK"] = 6] = "BACKGROUND_THICK";
  BlurStyle[BlurStyle["BACKGROUND_ULTRA_THICK"] = 7] = "BACKGROUND_ULTRA_THICK";
  BlurStyle[BlurStyle["COMPONENT_ULTRA_THIN"] = 8] = "COMPONENT_ULTRA_THIN";
  BlurStyle[BlurStyle["COMPONENT_THIN"] = 9] = "COMPONENT_THIN";
  BlurStyle[BlurStyle["COMPONENT_REGULAR"] = 10] = "COMPONENT_REGULAR";
  BlurStyle[BlurStyle["COMPONENT_THICK"] = 11] = "COMPONENT_THICK";
  BlurStyle[BlurStyle["COMPONENT_ULTRA_THICK"] = 12] = "COMPONENT_ULTRA_THICK";
  BlurStyle[BlurStyle["NONE"] = 0] = "NONE";
})(BlurStyle || (BlurStyle = {}));

var BlurStyleActivePolicy;
(function (BlurStyleActivePolicy) {
  BlurStyleActivePolicy[BlurStyleActivePolicy["FOLLOWS_WINDOW_ACTIVE_STATE"] = 0] = "FOLLOWS_WINDOW_ACTIVE_STATE";
  BlurStyleActivePolicy[BlurStyleActivePolicy["ALWAYS_ACTIVE"] = 1] = "ALWAYS_ACTIVE";
  BlurStyleActivePolicy[BlurStyleActivePolicy["ALWAYS_INACTIVE"] = 2] = "ALWAYS_INACTIVE";
})(BlurStyleActivePolicy || (BlurStyleActivePolicy = {}));

var BlurType;
(function (BlurType) {
  BlurType[BlurType["WITHIN_WINDOW"] = 0] = "WITHIN_WINDOW";
  BlurType[BlurType["BEHIND_WINDOW"] = 1] = "BEHIND_WINDOW";
})(BlurType || (BlurType = {}));

var ThemeColorMode;
(function (ThemeColorMode) {
  ThemeColorMode[ThemeColorMode["System"] = 0] = "System";
  ThemeColorMode[ThemeColorMode["Light"] = 1] = "Light";
  ThemeColorMode[ThemeColorMode["Dark"] = 2] = "Dark";
  ThemeColorMode[ThemeColorMode["SYSTEM"] = 0] = "SYSTEM";
  ThemeColorMode[ThemeColorMode["LIGHT"] = 1] = "LIGHT";
  ThemeColorMode[ThemeColorMode["DARK"] = 2] = "DARK";
})(ThemeColorMode || (ThemeColorMode = {}));

var AdaptiveColor;
(function (AdaptiveColor) {
  AdaptiveColor[AdaptiveColor["Default"] = 0] = "Default";
  AdaptiveColor[AdaptiveColor["Average"] = 1] = "Average";
  AdaptiveColor[AdaptiveColor["DEFAULT"] = 0] = "DEFAULT";
  AdaptiveColor[AdaptiveColor["AVERAGE"] = 1] = "AVERAGE";
})(AdaptiveColor || (AdaptiveColor = {}));

var ShadowStyle;
(function (ShadowStyle) {
  ShadowStyle[ShadowStyle["OuterDefaultXS"] = 0] = "OuterDefaultXS";
  ShadowStyle[ShadowStyle["OuterDefaultSM"] = 1] = "OuterDefaultSM";
  ShadowStyle[ShadowStyle["OuterDefaultMD"] = 2] = "OuterDefaultMD";
  ShadowStyle[ShadowStyle["OuterDefaultLG"] = 3] = "OuterDefaultLG";
  ShadowStyle[ShadowStyle["OuterFloatingSM"] = 4] = "OuterFloatingSM";
  ShadowStyle[ShadowStyle["OuterFloatingMD"] = 5] = "OuterFloatingMD";
  ShadowStyle[ShadowStyle["OUTER_DEFAULT_XS"] = 0] = "OUTER_DEFAULT_XS";
  ShadowStyle[ShadowStyle["OUTER_DEFAULT_SM"] = 1] = "OUTER_DEFAULT_SM";
  ShadowStyle[ShadowStyle["OUTER_DEFAULT_MD"] = 2] = "OUTER_DEFAULT_MD";
  ShadowStyle[ShadowStyle["OUTER_DEFAULT_LG"] = 3] = "OUTER_DEFAULT_LG";
  ShadowStyle[ShadowStyle["OUTER_FLOATING_SM"] = 4] = "OUTER_FLOATING_SM";
  ShadowStyle[ShadowStyle["OUTER_FLOATING_MD"] = 5] = "OUTER_FLOATING_MD";
})(ShadowStyle || (ShadowStyle = {}));

var ShadowType;
(function (ShadowType) {
  ShadowType[ShadowType["COLOR"] = 0] = "COLOR";
  ShadowType[ShadowType["BLUR"] = 1] = "BLUR";
})(ShadowType || (ShadowType = {}));

var BreakpointsReference;
(function (BreakpointsReference) {
  BreakpointsReference[BreakpointsReference["WindowSize"] = 0] = "WindowSize";
  BreakpointsReference[BreakpointsReference["ComponentSize"] = 1] = "ComponentSize";
})(BreakpointsReference || (BreakpointsReference = {}));

var GridRowDirection;
(function (GridRowDirection) {
  GridRowDirection[GridRowDirection["Row"] = 0] = "Row";
  GridRowDirection[GridRowDirection["RowReverse"] = 1] = "RowReverse";
})(GridRowDirection || (GridRowDirection = {}));

var HitTestMode;
(function (HitTestMode) {
  HitTestMode[HitTestMode["Default"] = 0] = "Default";
  HitTestMode[HitTestMode["Block"] = 1] = "Block";
  HitTestMode[HitTestMode["Transparent"] = 2] = "Transparent";
  HitTestMode[HitTestMode["None"] = 3] = "None";
})(HitTestMode || (HitTestMode = {}));

var GridDirection;
(function (GridDirection) {
  GridDirection[GridDirection["Row"] = 0] = "Row";
  GridDirection[GridDirection["Column"] = 1] = "Column";
  GridDirection[GridDirection["RowReverse"] = 2] = "RowReverse";
  GridDirection[GridDirection["ColumnReverse"] = 3] = "ColumnReverse";
})(GridDirection || (GridDirection = {}));

var SelectStatus;
(function (SelectStatus) {
  SelectStatus[SelectStatus["All"] = 0] = "All";
  SelectStatus[SelectStatus["Part"] = 1] = "Part";
  SelectStatus[SelectStatus["None"] = 2] = "None";
})(SelectStatus || (SelectStatus = {}));

var ContextMenuSourceType;
(function (ContextMenuSourceType) {
  ContextMenuSourceType[ContextMenuSourceType["None"] = 0] = "None";
  ContextMenuSourceType[ContextMenuSourceType["Mouse"] = 1] = "Mouse";
  ContextMenuSourceType[ContextMenuSourceType["LongPress"] = 2] = "LongPress";
})(ContextMenuSourceType || (ContextMenuSourceType = {}));

var ContextMenuMediaType;
(function (ContextMenuMediaType) {
  ContextMenuMediaType[ContextMenuMediaType["None"] = 0] = "None";
  ContextMenuMediaType[ContextMenuMediaType["Image"] = 1] = "Image";
})(ContextMenuMediaType || (ContextMenuMediaType = {}));

var ContextMenuInputFieldType;
(function (ContextMenuInputFieldType) {
  ContextMenuInputFieldType[ContextMenuInputFieldType["None"] = 0] = "None";
  ContextMenuInputFieldType[ContextMenuInputFieldType["PlainText"] = 1] = "PlainText";
  ContextMenuInputFieldType[ContextMenuInputFieldType["Password"] = 2] = "Password";
  ContextMenuInputFieldType[ContextMenuInputFieldType["Number"] = 3] = "Number";
  ContextMenuInputFieldType[ContextMenuInputFieldType["Telephone"] = 4] = "Telephone";
  ContextMenuInputFieldType[ContextMenuInputFieldType["Other"] = 5] = "Other";
})(ContextMenuInputFieldType || (ContextMenuInputFieldType = {}));

var ContextMenuEditStateFlags;
(function (ContextMenuEditStateFlags) {
  ContextMenuEditStateFlags[ContextMenuEditStateFlags["NONE"] = 0] = "None";
  ContextMenuEditStateFlags[ContextMenuEditStateFlags["CAN_CUT"] = 1] = "CAN_CUT";
  ContextMenuEditStateFlags[ContextMenuEditStateFlags["CAN_COPY"] = 2] = "CAN_COPY";
  ContextMenuEditStateFlags[ContextMenuEditStateFlags["CAN_PASTE"] = 4] = "CAN_PASTE";
  ContextMenuEditStateFlags[ContextMenuEditStateFlags["CAN_SELECT_ALL"] = 8] = "CAN_SELECT_ALL";
})(ContextMenuEditStateFlags || (ContextMenuEditStateFlags = {}));

var TransitionEdge;
(function (TransitionEdge) {
  TransitionEdge['TOP'] = 0;
  TransitionEdge['BOTTOM'] = 1;
  TransitionEdge['START'] = 2;
  TransitionEdge['END'] = 3;
})(TransitionEdge || (TransitionEdge = {}));

var TouchTestStrategy;
(function (TouchTestStrategy) {
  TouchTestStrategy['DEFAULT'] = 0;
  TouchTestStrategy['FORWARD_COMPETITION'] = 1;
  TouchTestStrategy['FORWARD'] = 2;
})(TouchTestStrategy || (TouchTestStrategy = {}));

var ModalTransition;
(function (ModalTransition) {
  ModalTransition[ModalTransition["Default"] = 0] = "Default";
  ModalTransition[ModalTransition["None"] = 1] = "None";
  ModalTransition[ModalTransition["Alpha"] = 2] = "Alpha";
  ModalTransition[ModalTransition["DEFAULT"] = 0] = "DEFAULT";
  ModalTransition[ModalTransition["NONE"] = 1] = "NONE";
  ModalTransition[ModalTransition["ALPHA"] = 2] = "ALPHA";
})(ModalTransition || (ModalTransition = {}));

var ModifierKey;
(function (ModifierKey) {
  ModifierKey[ModifierKey["CTRL"] = 0] = "CTRL";
  ModifierKey[ModifierKey["SHIFT"] = 1] = "SHIFT";
  ModifierKey[ModifierKey["ALT"] = 2] = "ALT";
})(ModifierKey || (ModifierKey = {}));

var SheetSize;
(function (SheetSize) {
  SheetSize['MEDIUM'] = "MEDIUM";
  SheetSize['LARGE'] = "LARGE";
  SheetSize['FIT_CONTENT'] = "FIT_CONTENT";
})(SheetSize || (SheetSize = {}));

var SheetType;
(function (SheetType) {
  SheetType[SheetType["BOTTOM"] = 0] = "BOTTOM";
  SheetType[SheetType["CENTER"] = 1] = "CENTER";
  SheetType[SheetType["POPUP"] = 2] = "POPUP";
})(SheetType || (SheetType = {}));

var SheetMode;
(function (SheetMode) {
  SheetMode[SheetMode["OVERLAY"] = 0] = "OVERLAY";
  SheetMode[SheetMode["EMBEDDED"] = 1] = "EMBEDDED";
})(SheetMode || (SheetMode = {}));

var ScrollSizeMode ;
(function (ScrollSizeMode ) {
  ScrollSizeMode[ScrollSizeMode["FOLLOW_DETENT"] = 0] = "FOLLOW_DETENT";
  ScrollSizeMode[ScrollSizeMode["CONTINUOUS"] = 1] = "CONTINUOUS";
})(ScrollSizeMode || (ScrollSizeMode = {}));

var SheetKeyboardAvoidMode;
(function (SheetKeyboardAvoidMode) {
  SheetKeyboardAvoidMode[SheetKeyboardAvoidMode['NONE'] = 0] = 'NONE';
  SheetKeyboardAvoidMode[SheetKeyboardAvoidMode['TRANSLATE_AND_RESIZE'] = 1] = 'TRANSLATE_AND_RESIZE';
  SheetKeyboardAvoidMode[SheetKeyboardAvoidMode['RESIZE_ONLY'] = 2] = 'RESIZE_ONLY';
  SheetKeyboardAvoidMode[SheetKeyboardAvoidMode['TRANSLATE_AND_SCROLL'] = 3] = 'TRANSLATE_AND_SCROLL';
})(SheetKeyboardAvoidMode || (SheetKeyboardAvoidMode = {}));

var FunctionKey;
(function (FunctionKey) {
  FunctionKey[FunctionKey["ESC"] = 0] = "ESC";
  FunctionKey[FunctionKey["F1"] = 1] = "F1";
  FunctionKey[FunctionKey["F2"] = 2] = "F2";
  FunctionKey[FunctionKey["F3"] = 3] = "F3";
  FunctionKey[FunctionKey["F4"] = 4] = "F4";
  FunctionKey[FunctionKey["F5"] = 5] = "F5";
  FunctionKey[FunctionKey["F6"] = 6] = "F6";
  FunctionKey[FunctionKey["F7"] = 7] = "F7";
  FunctionKey[FunctionKey["F8"] = 8] = "F8";
  FunctionKey[FunctionKey["F9"] = 9] = "F9";
  FunctionKey[FunctionKey["F10"] = 10] = "F10";
  FunctionKey[FunctionKey["F11"] = 11] = "F11";
  FunctionKey[FunctionKey["F12"] = 12] = "F12";
  FunctionKey[FunctionKey["TAB"] = 13] = "TAB";
  FunctionKey[FunctionKey["DPAD_UP"] = 14] = "DPAD_UP";
  FunctionKey[FunctionKey["DPAD_DOWN"] = 15] = "DPAD_DOWN";
  FunctionKey[FunctionKey["DPAD_LEFT"] = 16] = "DPAD_LEFT";
  FunctionKey[FunctionKey["DPAD_RIGHT"] = 17] = "DPAD_RIGHT";
})(FunctionKey || (FunctionKey = {}));

var ContentType;
(function (ContentType) {
  ContentType[ContentType['USER_NAME'] = 0] = 'USER_NAME';
  ContentType[ContentType['PASSWORD'] = 1] = 'PASSWORD';
  ContentType[ContentType['NEW_PASSWORD'] = 2] = 'NEW_PASSWORD';
  ContentType[ContentType['FULL_STREET_ADDRESS'] = 3] = 'FULL_STREET_ADDRESS';
  ContentType[ContentType['HOUSE_NUMBER'] = 4] = 'HOUSE_NUMBER';
  ContentType[ContentType['DISTRICT_ADDRESS'] = 5] = 'DISTRICT_ADDRESS';
  ContentType[ContentType['CITY_ADDRESS'] = 6] = 'CITY_ADDRESS';
  ContentType[ContentType['PROVINCE_ADDRESS'] = 7] = 'PROVINCE_ADDRESS';
  ContentType[ContentType['COUNTRY_ADDRESS'] = 8] = 'COUNTRY_ADDRESS';
  ContentType[ContentType['PERSON_FULL_NAME'] = 9] = 'PERSON_FULL_NAME';
  ContentType[ContentType['PERSON_LAST_NAME'] = 10] = 'PERSON_LAST_NAME';
  ContentType[ContentType['PERSON_FIRST_NAME'] = 11] = 'PERSON_FIRST_NAME';
  ContentType[ContentType['PHONE_NUMBER'] = 12] = 'PHONE_NUMBER';
  ContentType[ContentType['PHONE_COUNTRY_CODE'] = 13] = 'PHONE_COUNTRY_CODE';
  ContentType[ContentType['FULL_PHONE_NUMBER'] = 14] = 'FULL_PHONE_NUMBER';
  ContentType[ContentType['EMAIL_ADDRESS'] = 15] = 'EMAIL_ADDRESS';
  ContentType[ContentType['BANK_CARD_NUMBER'] = 16] = 'BANK_CARD_NUMBER';
  ContentType[ContentType['ID_CARD_NUMBER'] = 17] = 'ID_CARD_NUMBER';
  ContentType[ContentType['PRECISE_TIME'] = 18] = 'PRECISE_TIME';
  ContentType[ContentType['HOUR_AND_MINUTE'] = 19] = 'HOUR_AND_MINUTE';
  ContentType[ContentType['DATE'] = 20] = 'DATE';
  ContentType[ContentType['MONTH'] = 21] = 'MONTH';
  ContentType[ContentType['YEAR'] = 22] = 'YEAR';
  ContentType[ContentType['NICKNAME'] = 23] = 'NICKNAME';
  ContentType[ContentType['DETAIL_INFO_WITHOUT_STREET'] = 24] = 'DETAIL_INFO_WITHOUT_STREET';
  ContentType[ContentType['FORMAT_ADDRESS'] = 25] = 'FORMAT_ADDRESS';
})(ContentType || (ContentType = {}));

var GestureJudgeResult;
(function (GestureJudgeResult) {
  GestureJudgeResult[GestureJudgeResult["CONTINUE"] = 0] = "CONTINUE";
  GestureJudgeResult[GestureJudgeResult["REJECT"] = 1] = "REJECT";
})(GestureJudgeResult || (GestureJudgeResult = {}));

var GestureControl;
(function (GestureControl) {
  let GestureType;
  (function (GestureType) {
    GestureType[GestureType["TAP_GESTURE"] = 0] = "TAP_GESTURE";
    GestureType[GestureType["LONG_PRESS_GESTURE"] = 1] = "LONG_PRESS_GESTURE";
    GestureType[GestureType["PAN_GESTURE"] = 2] = "PAN_GESTURE";
    GestureType[GestureType["PINCH_GESTURE"] = 3] = "PINCH_GESTURE";
    GestureType[GestureType["SWIPE_GESTURE"] = 4] = "SWIPE_GESTURE";
    GestureType[GestureType["ROTATION_GESTURE"] = 5] = "ROTATION_GESTURE";
    GestureType[GestureType["DRAG"] = 6] = "DRAG";
    GestureType[GestureType["CLICK"] = 7] = "CLICK";
  })(GestureType = GestureControl.GestureType || (GestureControl.GestureType = {}));
})(GestureControl || (GestureControl = {}));

var TransitionHierarchyStrategy;
(function (TransitionHierarchyStrategy) {
  TransitionHierarchyStrategy[TransitionHierarchyStrategy["NONE"] = 0] = "NONE";
  TransitionHierarchyStrategy[TransitionHierarchyStrategy["ADAPTIVE"] = 1] = "ADAPTIVE";
})(TransitionHierarchyStrategy || (TransitionHierarchyStrategy = {}));

var KeyboardAvoidMode;
(function (KeyboardAvoidMode) {
    KeyboardAvoidMode[KeyboardAvoidMode["DEFAULT"] = 0] = "DEFAULT";
    KeyboardAvoidMode[KeyboardAvoidMode["NONE"] = 1] = "NONE";
})(KeyboardAvoidMode || (KeyboardAvoidMode = {}));

class SubTabBarStyle {
  constructor(content) {
    this.type = 'SubTabBarStyle';
    this.content = content;
  }
  static of(content) {
    return new SubTabBarStyle(content);
  }
  indicator(arg) {
    this.indicator = arg;
    return this;
  }
  selectedMode(arg) {
    this.selectedMode = arg;
    return this;
  }
  board(arg) {
    this.board = arg;
    return this;
  }
  labelStyle(arg) {
    this.labelStyle = arg;
    return this;
  }
  padding(arg) {
    this.padding = arg;
    return this;
  }
  id(arg) {
    this.id = arg;
    return this;
  }
}

class DrawModifier {
  invalidate() { }
}

class ProgressMask {
  constructor(value, total, color) {
    this.type = 'ProgressMask';
    this.value = value;
    this.total = total;
    this.color = color;
  }

  updateProgress(arg) {
    this.value = arg;
    return this;
  }

  updateColor(arg) {
    this.color = arg;
    return this;
  }

  enableBreathingAnimation(arg) {
    this.breathe = arg;
    return this;
  }
}

class BottomTabBarStyle {
  constructor(icon, text) {
    this.type = 'BottomTabBarStyle';
    this.icon = icon;
    this.text = text;
  }
  static of(icon, text) {
    return new BottomTabBarStyle(icon, text);
  }
  padding(arg) {
    this.padding = arg;
    return this;
  }
  layoutMode(arg) {
    this.layoutMode = arg;
    return this;
  }
  verticalAlign(arg) {
    this.verticalAlign = arg;
    return this;
  }
  symmetricExtensible(arg) {
    this.symmetricExtensible = arg;
    return this;
  }
  labelStyle(arg) {
    this.labelStyle = arg;
    return this;
  }
  id(arg) {
    this.id = arg;
    return this;
  }
  iconStyle(arg) {
    this.iconStyle = arg;
    return this;
  }
}

class Indicator {
  top(value) {
    this.topValue = value;
    return this;
  }
  left(value) {
    this.leftValue = value;
    return this;
  }
  right(value) {
    this.rightValue = value;
    return this;
  }
  bottom(value) {
    this.bottomValue = value;
    return this;
  }
  start(value) {
    this.startValue = value;
    return this;
  }
  end(value) {
    this.endValue = value;
    return this;
  }
  static dot() {
    return new DotIndicator();
  }
  static digit() {
    return new DigitIndicator();
  }
}

class DotIndicator extends Indicator {
  constructor() {
    super();
    this.type = 'DotIndicator';
  }
  itemWidth(value) {
    this.itemWidthValue = value;
    return this;
  }
  itemHeight(value) {
    this.itemHeightValue = value;
    return this;
  }
  selectedItemWidth(value) {
    this.selectedItemWidthValue = value;
    return this;
  }
  selectedItemHeight(value) {
    this.selectedItemHeightValue = value;
    return this;
  }
  mask(value) {
    this.maskValue = value;
    return this;
  }
  color(value) {
    this.colorValue = value;
    return this;
  }
  selectedColor(value) {
    this.selectedColorValue = value;
    return this;
  }
  maxDisplayCount(value) {
    this.maxDisplayCountValue = value;
    return this;
  }
}

class DigitIndicator extends Indicator {
  constructor() {
    super();
    this.type = 'DigitIndicator';
  }
  fontColor(value) {
    this.fontColorValue = value;
    return this;
  }
  selectedFontColor(value) {
    this.selectedFontColorValue = value;
    return this;
  }
  digitFont(value) {
    this.digitFontValue = value;
    return this;
  }
  selectedDigitFont(value) {
    this.selectedDigitFontValue = value;
    return this;
  }
}

var TextHeightAdaptivePolicy;
(function (TextHeightAdaptivePolicy) {
  TextHeightAdaptivePolicy[TextHeightAdaptivePolicy["MAX_LINES_FIRST"] = 0] = "MAX_LINES_FIRST";
  TextHeightAdaptivePolicy[TextHeightAdaptivePolicy["MIN_FONT_SIZE_FIRST"] = 1] = "MIN_FONT_SIZE_FIRST";
  TextHeightAdaptivePolicy[TextHeightAdaptivePolicy["LAYOUT_CONSTRAINT_FIRST"] = 2] = "LAYOUT_CONSTRAINT_FIRST";
})(TextHeightAdaptivePolicy || (TextHeightAdaptivePolicy = {}));

var ArrowPosition;
(function (ArrowPosition) {
  ArrowPosition[ArrowPosition["END"] = 0] = "END";
  ArrowPosition[ArrowPosition["START"] = 1] = "START";
})(ArrowPosition || (ArrowPosition = {}));

class TransitionEffect {
  type_ = '';
  effect_ = undefined;
  animation_ = undefined;
  // use successor_ to mark whether this is an instance of TransitionEffect
  successor_ = null;

  constructor(type, effect) {
    this.type_ = type;
    this.effect_ = effect;
  }

  static get IDENTITY() {
    return new TransitionEffect('identity', undefined);
  }
  static get OPACITY() {
    return new TransitionEffect('opacity', 0);
  }
  static get SLIDE() {
    return new TransitionEffect('asymmetric', {
      appear: new TransitionEffect('move', TransitionEdge.START),
      disappear: new TransitionEffect('move', TransitionEdge.END)
    });
  }
  static get SLIDE_SWITCH() {
    return new TransitionEffect('slideSwitch', undefined);
  }
  static translate(option) {
    return new TransitionEffect('translate', option);
  }
  static rotate(option) {
    return new TransitionEffect('rotate', option);
  }
  static scale(option) {
    return new TransitionEffect('scale', option);
  }
  static opacity(value) {
    return new TransitionEffect('opacity', value);
  }
  static move(edge) {
    return new TransitionEffect('move', edge);
  }
  static asymmetric(appearEffect, disappearEffect) {
    return new TransitionEffect('asymmetric', {
      appear: appearEffect,
      disappear: disappearEffect
    });
  }

  animation(option) {
    this.animation_ = option;
    return this;
  }
  combine(nextEffect) {
    if (nextEffect == null || nextEffect == undefined) {
      return this;
    }
    var lastEffect = this;
    while (lastEffect.successor_ != null) {
      lastEffect = lastEffect.successor_;
    }
    lastEffect.successor_ = nextEffect;
    return this;
  }
}

class TextMenuItemId {
  id_ = '';

  constructor(id) {
    this.id_ = id;
  }

  static of(id) {
    return new TextMenuItemId(id);
  }

  equals(id) {
    return id.id_ === this.id_;
  }

  static get CUT() {
    return new TextMenuItemId('OH_DEFAULT_CUT');
  }
  
  static get COPY() {
    return new TextMenuItemId('OH_DEFAULT_COPY');
  }

  static get PASTE() {
    return new TextMenuItemId('OH_DEFAULT_PASTE');
  }

  static get SELECT_ALL() {
    return new TextMenuItemId('OH_DEFAULT_SELECT_ALL');
  }

  static get COLLABORATION_SERVICE() {
    return new TextMenuItemId('OH_DEFAULT_COLLABORATION_SERVICE');
  }

  static get CAMERA_INPUT() {
    return new TextMenuItemId('OH_DEFAULT_CAMERA_INPUT');
  }

  static get AI_WRITER() {
    return new TextMenuItemId('OH_DEFAULT_AI_WRITE');
  }
}

globalThis.TextMenuItemId = TextMenuItemId;

var SliderBlockType;
(function (SliderBlockType) {
  SliderBlockType[SliderBlockType["DEFAULT"] = 0] = "DEFAULT";
  SliderBlockType[SliderBlockType["IMAGE"] = 1] = "IMAGE";
  SliderBlockType[SliderBlockType["SHAPE"] = 2] = "SHAPE";
})(SliderBlockType || (SliderBlockType = {}));

var SliderInteraction;
(function (SliderInteraction) {
  SliderInteraction[SliderInteraction["SLIDE_AND_CLICK"] = 0] = "SLIDE_AND_CLICK";
  SliderInteraction[SliderInteraction["SLIDE_ONLY"] = 1] = "SLIDE_ONLY";
  SliderInteraction[SliderInteraction["SLIDE_AND_CLICK_UP"] = 2] = "SLIDE_AND_CLICK_UP";
})(SliderInteraction || (SliderInteraction = {}));

var TitleStyle;
(function (TitleStyle) {
  TitleStyle[TitleStyle["ListMode"] = 0] = "ListMode";
  TitleStyle[TitleStyle["ContentMode"] = 1] = "ContentMode";
})(TitleStyle || (TitleStyle = {}));

var OperationStyle;
(function (OperationStyle) {
  OperationStyle[OperationStyle["TextArrow"] = 0] = "TextArrow";
  OperationStyle[OperationStyle["Button"] = 1] = "Button";
  OperationStyle[OperationStyle["IconGroup"] = 2] = "IconGroup";
})(OperationStyle || (OperationStyle = {}));

var TabItemType;
(function (TabItemType) {
  TabItemType[TabItemType["Text"] = 0] = "Text";
  TabItemType[TabItemType["Icon"] = 1] = "Icon";
})(TabItemType || (TabItemType = {}));

var EditableLeftIconType;
(function (EditableLeftIconType) {
  EditableLeftIconType[EditableLeftIconType["Back"] = 0] = "Back";
  EditableLeftIconType[EditableLeftIconType["Cancel"] = 1] = "Cancel";
})(EditableLeftIconType || (EditableLeftIconType = {}));

var ContentIconPosition;
(function (ContentIconPosition) {
  ContentIconPosition[ContentIconPosition["Top"] = 0] = "Top";
  ContentIconPosition[ContentIconPosition["Center"] = 1] = "Center";
})(ContentIconPosition || (ContentIconPosition = {}));

var ContentTextStyle;
(function (ContentTextStyle) {
  ContentTextStyle[ContentTextStyle["SingleLine"] = 0] = "SingleLine";
  ContentTextStyle[ContentTextStyle["DoubleLine"] = 1] = "DoubleLine";
  ContentTextStyle[ContentTextStyle["ThreeLines"] = 2] = "ThreeLines";
})(ContentTextStyle || (ContentTextStyle = {}));

var MarqueeUpdateStrategy;
(function (MarqueeUpdateStrategy) {
  MarqueeUpdateStrategy["DEFAULT"] = "default";
  MarqueeUpdateStrategy["PRESERVE_POSITION"] = "preserve_position";
})(MarqueeUpdateStrategy || (MarqueeUpdateStrategy = {}));

var LaunchMode;
(function (LaunchMode) {
  LaunchMode[LaunchMode.STANDARD = 0] = 'STANDARD';
  LaunchMode[LaunchMode.MOVE_TO_TOP_SINGLETON = 1] = 'MOVE_TO_TOP_SINGLETON';
  LaunchMode[LaunchMode.POP_TO_SINGLETON = 2] = 'POP_TO_SINGLETON';
  LaunchMode[LaunchMode.NEW_INSTANCE = 3] = 'NEW_INSTANCE';
})(LaunchMode || (LaunchMode = {}));

class NavPathInfo {
  constructor(name, param, onPop, isEntry) {
    this.name = name;
    this.param = param;
    this.onPop = onPop;
    this.index = -1;
    this.needUpdate = false;
    this.needBuildNewInstance = false;
    this.navDestinationId = undefined;
    this.promise = undefined;
    this.replacedDestinationInfo = undefined;
    this.recoveryFromReplaceDestination = undefined;
    this.isEntry = isEntry;
    this.fromRecovery = false;
    this.mode = undefined;
  }
}

class NavPathStack {
  constructor() {
    this.pathArray = [];
    // replace value 0: don't do anything;
    // 1: replace value and do replace animation;
    // 2: don't replace value but do replace animation
    this.isReplace = 0;
    this.type = this.constructor.name;
    // control all navigation transition animations.
    this.disableAllAnimation = false;
    // control a single navigation transition animation.
    this.animated = true;
    // native nav path stack, implement in cpp
    this.nativeStack = undefined;
    // parent stack
    this.parentStack = undefined;
    this.popArray = [];
    this.interception = undefined;
  }
  getJsIndexFromNativeIndex(index) {
    for (let i = 0; i < this.pathArray.length; i++) {
      if (this.pathArray[i].index === index) {
        return i;
      }
    }
    return -1;
  }
  initNavPathIndex(pathName) {
    this.popArray = [];
    for (let i = 0; i < this.pathArray.length && i < pathName.length; i++) {
      if (pathName[i] === this.pathArray[i].name && this.isReplace !== 1) {
        this.pathArray[i].index = i;
      }
    }
  }
  getAllPathIndex() {
    let array = this.pathArray.flatMap(element => element.index);
    return array;
  }
  findInPopArray(name) {
    for (let i = this.popArray.length - 1; i >= 0; i--) {
      if (name === this.popArray[i].name) {
        let info = this.popArray.splice(i, 1);
        return [info[0].index, info[0].navDestinationId];
      }
    }
    return [-1, undefined]; // add new navdestination
  }
  setNativeStack(stack) {
    this.nativeStack = stack;
  }
  getNativeStack() {
    return this.nativeStack;
  }
  setParent(parent) {
    this.parentStack = parent;
  }
  getParent() {
    return this.parentStack;
  }
  pushName(name, param) {
    let info = new NavPathInfo(name, param);
    [info.index, info.navDestinationId] = this.findInPopArray(name);
    this.pathArray.push(info);
    this.isReplace = 0;
    this.nativeStack?.onStateChanged();
  }
  push(info, animated) {
    this.pushPath(info, animated);
  }
  pushPathByName(name, param, onPop, animated) {
    let info = undefined;
    if (onPop === undefined || typeof onPop === 'boolean') {
      info = new NavPathInfo(name, param);
    } else {
      info = new NavPathInfo(name, param, onPop);
    }
    [info.index, info.navDestinationId] = this.findInPopArray(name);
    this.pathArray.push(info);
    this.isReplace = 0;
    if (typeof onPop === 'boolean') {
      this.animated = onPop;
    } else if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
  }
  pushDestinationByName(name, param, onPop, animated) {
    let info = undefined;
    if (onPop === undefined || typeof onPop === 'boolean') {
      info = new NavPathInfo(name, param);
    } else {
      info = new NavPathInfo(name, param, onPop);
    }
    this.isReplace = 0;
    if (typeof onPop === 'boolean') {
      this.animated = onPop;
    } else if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    [info.index, info.navDestinationId] = this.findInPopArray(name);
    this.pathArray.push(info);
    this.nativeStack?.onStateChanged();
    return new Promise((resolve, reject) => {
      info.promise = (errorCode, errorMessage) => {
        if (errorCode === 0) {
          resolve(0);
          return;
        }
        reject({code: errorCode, message: errorMessage});
      };
    });
  }
  parseNavigationOptions(param) {
    let launchMode = LaunchMode.STANDARD;
    let animated = true;
    if (typeof param === 'boolean') {
      animated = param;
    } else if (param !== undefined) {
      if (typeof param.animated === 'boolean') {
        animated = param.animated;
      }
      if (param.launchMode !== undefined) {
        launchMode = param.launchMode;
      }
    }
    return [launchMode, animated];
  }
  pushWithLaunchModeAndAnimated(info, launchMode, animated, createPromise) {
    if (launchMode === LaunchMode.MOVE_TO_TOP_SINGLETON || launchMode === LaunchMode.POP_TO_SINGLETON) {
      let index = this.pathArray.findIndex(element => element.name === info.name);
      if (index !== -1) {
        this.pathArray[index].param = info.param;
        this.pathArray[index].onPop = info.onPop;
        this.pathArray[index].needUpdate = true;
        this.pathArray[index].isEntry = info.isEntry;
        if (launchMode === LaunchMode.MOVE_TO_TOP_SINGLETON) {
          this.moveIndexToTop(index, animated);
        } else {
          this.popToIndex(index, undefined, animated);
        }
        let promise = null;
        if (createPromise) {
          promise = new Promise((resolve, reject) => {
            resolve();
          });
        }
        return [true, promise];
      }
    }
    return [false, null];
  }
  pushPath(info, optionParam) {
    let [launchMode, animated] = this.parseNavigationOptions(optionParam);
    let [ret, _] = this.pushWithLaunchModeAndAnimated(info, launchMode, animated, false);
    if (ret) {
      return;
    }
    [info.index, info.navDestinationId] = this.findInPopArray(info.name);
    if (launchMode === LaunchMode.NEW_INSTANCE) {
      info.needBuildNewInstance = true;
    }
    this.pathArray.push(info);
    this.isReplace = 0;
    this.animated = animated;
    this.nativeStack?.onStateChanged();
  }
  pushDestination(info, optionParam) {
    let [launchMode, animated] = this.parseNavigationOptions(optionParam);
    let [ret, promiseRet] = this.pushWithLaunchModeAndAnimated(info, launchMode, animated, true);
    if (ret) {
      return promiseRet;
    }
    this.isReplace = 0;
    this.animated = animated;
    [info.index, info.navDestinationId] = this.findInPopArray(info.name);
    if (launchMode === LaunchMode.NEW_INSTANCE) {
      info.needBuildNewInstance = true;
    }
    this.pathArray.push(info);
    this.nativeStack?.onStateChanged();
    return new Promise((resolve, reject) => {
      info.promise = (errorCode, errorMessage) => {
        if (errorCode === 0) {
          resolve(0);
          return;
        }
        reject({code: errorCode, message: errorMessage});
      };
    });
  }
  doReplaceInner(info, optionParam, isReplaceDestination) {
    let [launchMode, animated] = this.parseNavigationOptions(optionParam);
    let index = -1;
    let needCreatePromiseWithLaunchMode = false;
    if (launchMode === LaunchMode.MOVE_TO_TOP_SINGLETON || launchMode === LaunchMode.POP_TO_SINGLETON) {
      index = this.pathArray.findIndex(element => element.name === info.name);
      if (index !== -1) {
        this.pathArray[index].param = info.param;
        this.pathArray[index].onPop = info.onPop;
        this.pathArray[index].index = -1;
        if (index !== this.pathArray.length - 1) {
          let targetInfo = this.pathArray.splice(index, 1);
          if (launchMode === LaunchMode.MOVE_TO_TOP_SINGLETON) {
            this.pathArray.pop();
          } else {
            this.pathArray.splice(index);
          }
          this.pathArray.push(targetInfo[0]);
        }
        if (isReplaceDestination) {
          needCreatePromiseWithLaunchMode = true;
        }
      }
    }
    if (index === -1) {
      if (this.pathArray.length !== 0) {
        let popInfo = this.pathArray.pop();
        if (isReplaceDestination) {
          info.replacedDestinationInfo = popInfo;
        }
      }
      this.pathArray.push(info);
      this.pathArray[this.pathArray.length - 1].index = -1;
    }
    this.isReplace = 1;
    this.animated = animated;
    this.nativeStack?.onStateChanged();
    if (needCreatePromiseWithLaunchMode) {
      return new Promise((resolve, reject) => {
        resolve();
      });
    }
    return undefined;
  }
  replacePath(info, optionParam) {
    this.doReplaceInner(info, optionParam);
  }
  replaceDestination(info, navigationOptions) {
    let promiseWithLaunchMode = this.doReplaceInner(info, navigationOptions, true);
    if (promiseWithLaunchMode !== undefined) {
      return promiseWithLaunchMode;
    }
    return new Promise((resolve, reject) => {
      info.promise = (errorCode, errorMessage) => {
        if (errorCode === 0) {
          resolve(0);
          return;
        }
        reject({code: errorCode, message: errorMessage});
      };
    });
  }
  replacePathByName(name, param, animated) {
    if (this.pathArray.length !== 0) {
      this.pathArray.pop();
    }
    this.isReplace = 1;
    this.pathArray.push(new NavPathInfo(name, param));
    this.pathArray[this.pathArray.length - 1].index = -1;
    if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
  }
  setIsReplace(value) {
    this.isReplace = value;
  }
  setAnimated(value) {
    this.animated = value;
  }
  pop(result, animated) {
    if (this.pathArray.length === 0) {
      return undefined;
    }
    let currentPathInfo = this.pathArray[this.pathArray.length - 1];
    let pathInfo = this.pathArray.pop();
    this.popArray.push(pathInfo);
    this.isReplace = 0;
    if (result !== undefined && typeof result !== 'boolean' && currentPathInfo.onPop !== undefined) {
      let popInfo = {
        info: currentPathInfo,
        result: result,
      };
      currentPathInfo.onPop(popInfo);
    }
    if (typeof result === 'boolean') {
      this.animated = result;
    } else if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
    return pathInfo;
  }
  popTo(name, animated) {
    popToName(name, animated);
  }
  popToName(name, result, animated) {
    let index = this.pathArray.findIndex(element => element.name === name);
    if (index === -1) {
      return -1;
    }
    let currentPathInfo = this.pathArray[this.pathArray.length - 1];
    this.pathArray.splice(index + 1);
    this.isReplace = 0;
    if (result !== undefined && typeof result !== 'boolean' && currentPathInfo.onPop !== undefined) {
      let popInfo = {
        info: currentPathInfo,
        result: result,
      };
      currentPathInfo.onPop(popInfo);
    }
    if (typeof result === 'boolean') {
      this.animated = result;
    } else if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
    return index;
  }
  popToIndex(index, result, animated) {
    if (index >= this.pathArray.length) {
      return;
    }
    let currentPathInfo = this.pathArray[this.pathArray.length - 1];
    this.pathArray.splice(index + 1);
    this.isReplace = 0;
    if (result !== undefined && typeof result !== 'boolean' && currentPathInfo.onPop !== undefined) {
      let popInfo = {
        info: currentPathInfo,
        result: result,
      };
      currentPathInfo.onPop(popInfo);
    }
    if (typeof result === 'boolean') {
      this.animated = result;
    } else if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
  }
  moveToTop(name, animated) {
    let index = this.pathArray.findIndex(element => element.name === name);
    if (index === -1) {
      return -1;
    }
    let info = this.pathArray.splice(index, 1);
    this.pathArray.push(info[0]);
    this.isReplace = 0;
    if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
    return index;
  }
  moveIndexToTop(index, animated) {
    if (index >= this.pathArray.length) {
      return;
    }
    let info = this.pathArray.splice(index, 1);
    this.pathArray.push(info[0]);
    this.isReplace = 0;
    if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
  }
  clear(animated) {
    if (this.pathArray.length == 0) {
      return;
    }
    this.pathArray.splice(0);
    this.isReplace = 0;
    if (animated === undefined) {
      this.animated = true;
    } else {
      this.animated = animated;
    }
    this.nativeStack?.onStateChanged();
  }
  removeByIndexes(indexes) {
    if (!Array.isArray(indexes) || indexes.length === 0) {
      return 0;
    }
    let originLength = this.pathArray.length;
    this.pathArray = this.pathArray.filter((item, index) => {
      return item && !indexes.includes(index)
    });
    let cnt = originLength - this.pathArray.length;
    if (cnt > 0) {
      this.isReplace = 0;
      this.nativeStack?.onStateChanged();
    }
    return cnt;
  }
  removeByName(name) {
    let originLength = this.pathArray.length;
    this.pathArray = this.pathArray.filter(item => { return name !== item.name });
    let cnt = originLength - this.pathArray.length;
    if (cnt > 0) {
      this.isReplace = 0;
      this.nativeStack?.onStateChanged();
    }
    return cnt;
  }
  removeByNavDestinationId(navDestinationId) {
    let index = this.pathArray.findIndex(element => element.navDestinationId === navDestinationId);
    if (index === -1) {
      return false;
    }
    this.pathArray.splice(index, 1);
    this.isReplace = 0;
    this.nativeStack?.onStateChanged();
    return true;
  }
  removeIndex(index) {
    if (index >= this.pathArray.length) {
      return;
    }
    this.pathArray.splice(index, 1);
    this.isReplace = 0;
    this.nativeStack?.onStateChanged();
  }
  removeInvalidPage(index) {
    if (index >= this.pathArray.length || index < 0) {
      return;
    }
    if (this.pathArray[index].replacedDestinationInfo !== undefined) {
      this.pathArray[index] = this.pathArray[index].replacedDestinationInfo;
      this.pathArray[index].recoveryFromReplaceDestination = true;
      return;
    }
    this.pathArray.splice(index, 1);
  }
  getAllPathName() {
    let array = this.pathArray.flatMap(element => element.name);
    return array;
  }
  getParamByIndex(index) {
    let item = this.pathArray[index];
    if (item === undefined) {
      return undefined;
    }
    return item.param;
  }
  getParamByName(name) {
    let array = new Array();
    this.pathArray.forEach((element) => {
      if (element.name === name) {
        array.push(element.param);
      }
    });
    return array;
  }
  getIndexByName(name) {
    let array = new Array();
    this.pathArray.forEach((element, index) => {
      if (element.name === name) {
        array.push(index);
      }
    });
    return array;
  }
  getNameByIndex(index) {
    let item = this.pathArray[index];
    if (item === undefined) {
      return undefined;
    }
    return item.name;
  }
  getOnPopByIndex(index) {
    let item = this.pathArray[index];
    if (item === undefined) {
      return undefined;
    }
    return item.onPop;
  }
  size() {
    return this.pathArray.length;
  }
  disableAnimation(disableAnimation) {
    this.disableAllAnimation = disableAnimation;
  }
  setInterception(interception) {
    this.interception = interception;
  }
  getIsEntryByIndex(index) {
    let item = this.pathArray[index];
    if (item === undefined) {
      return false;
    }
    return item.isEntry;
  }
  setIsEntryByIndex(index, isEntry) {
    let item = this.pathArray[index];
    if (item === undefined) {
      return;
    }
    item.isEntry = isEntry;
  }
}

globalThis.NavPathStack = NavPathStack;

class WaterFlowSections {
  constructor() {
    this.sectionArray = [];
    // indicate class has changed.
    this.changeFlag = true;
    this.changeArray = [];
  }

  isNonNegativeInt32(input) {
    return Number.isSafeInteger(input) && input >= 0 && input <= 2147483647;
  }

  toArrayIndex(origin, limit) {
    // origin is truncated to an integer
    let result = Math.trunc(origin);
    if (result < 0) {
      // Negative index counts back from the end of the sectionArray.
      result += limit;
      // If origin < -sectionArray.length, 0 is used.
      if (result < 0) {
        result = 0;
      }
    } else if (result > limit) {
      result = limit;
    }
    return result;
  }

  // splice(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean;
  splice(start, deleteCount, sections) {
    let oldLength = this.sectionArray.length;
    let paramCount = arguments.length;
    if (paramCount === 1) {
      this.sectionArray.splice(start);
    } else if (paramCount === 2) {
      this.sectionArray.splice(start, deleteCount);
    } else {
      const iterator = sections.values();
      for (const section of iterator) {
        if (!this.isNonNegativeInt32(section.itemsCount)) {
          return false;
        }
      }
      this.sectionArray.splice(start, deleteCount, ...sections);
    }

    let intStart = this.toArrayIndex(start, oldLength);
    let intDeleteCount = 0;
    if (paramCount === 1) {
      // If deleteCount is omitted, then all the sections from start to the end of the sectionArray will be deleted.
      intDeleteCount = oldLength - intStart;
    } else {
      intDeleteCount = Math.trunc(deleteCount);
      if (intDeleteCount > oldLength - intStart) {
        intDeleteCount = oldLength - intStart;
      }
    }
    intDeleteCount = intDeleteCount < 0 ? 0 : intDeleteCount;

    this.changeArray.push({ start: intStart, deleteCount: intDeleteCount, sections: sections ? sections : [] });
    this.changeFlag = !this.changeFlag;
    return true;
  }

  push(section) {
    if (!this.isNonNegativeInt32(section.itemsCount)) {
      return false;
    }
    let oldLength = this.sectionArray.length;
    this.sectionArray.push(section);
    this.changeArray.push({ start: oldLength, deleteCount: 0, sections: [section] });
    this.changeFlag = !this.changeFlag;
    return true;
  }

  update(sectionIndex, section) {
    if (!this.isNonNegativeInt32(section.itemsCount)) {
      return false;
    }
    let oldLength = this.sectionArray.length;
    this.sectionArray.splice(sectionIndex, 1, section);

    let intStart = this.toArrayIndex(sectionIndex, oldLength);
    this.changeArray.push({ start: intStart, deleteCount: 1, sections: [section] });
    this.changeFlag = !this.changeFlag;
    return true;
  }

  values() {
    return this.sectionArray;
  }

  length() {
    return this.sectionArray.length;
  }

  clearChanges() {
    this.changeArray.splice(0);
  }
}

var WaterFlowLayoutMode;
(function (WaterFlowLayoutMode) {
  WaterFlowLayoutMode[WaterFlowLayoutMode["ALWAYS_TOP_DOWN"] = 0] = "ALWAYS_TOP_DOWN";
  WaterFlowLayoutMode[WaterFlowLayoutMode["SLIDING_WINDOW"] = 1] = "SLIDING_WINDOW";
})(WaterFlowLayoutMode || (WaterFlowLayoutMode = {}));

class ChildrenMainSizeParamError extends Error {
  constructor(message, code) {
    super(message);
    this.code = code;
  }
}

class ChildrenMainSize {

  constructor(childDefaultSize) {
    if (this.isInvalid(childDefaultSize)) {
      throw new ChildrenMainSizeParamError('The parameter check failed.', '401');
    }
    this.defaultMainSize = childDefaultSize;
    this.sizeArray = [];
    this.changeFlag = true;
    // -1: represent newly created.
    this.changeArray = [ { start: -1 } ];
  }

  set childDefaultSize(value) {
    if (this.isInvalid(value)) {
      throw new ChildrenMainSizeParamError('The parameter check failed.', '401');
    }
    this.defaultMainSize = value;
  }

  get childDefaultSize() {
    return this.defaultMainSize;
  }

  // splice(start: number, deleteCount?: number, childrenSize?: Array<number>);
  splice(start, deleteCount, childrenSize) {
    let paramCount = arguments.length;
    if (this.isInvalid(start)) {
      throw new ChildrenMainSizeParamError('The parameter check failed.', '401');
    }
    let startValue = Math.trunc(start);
    let deleteCountValue = deleteCount && !(this.isInvalid(deleteCount)) ? Math.trunc(deleteCount) : 0;
    if (paramCount === 1) {
      this.sizeArray.splice(startValue);
      this.changeArray.push({ start: startValue });
    } else if (paramCount === 2) {
      this.sizeArray.splice(startValue, deleteCountValue);
      this.changeArray.push({ start: startValue, deleteCount: deleteCountValue });
    } else if (paramCount === 3) {
      let childrenSizeLength = childrenSize ? childrenSize.length : 0;
      if (childrenSizeLength === 0) {
        childrenSize = [];
      }
      for (let i = 0; i < childrenSizeLength; i++) {
        if (this.isInvalid(childrenSize[i])) {
          // -1: represent default size.
          childrenSize[i] = -1;
        }
      }
      while (startValue >= this.sizeArray.length) {
        this.sizeArray.push(-1);
      }
      this.sizeArray.splice(startValue, deleteCountValue, ...childrenSize);
      this.changeArray.push({ start: startValue, deleteCount: deleteCountValue, childrenSize: childrenSize });
    }
    this.changeFlag = !this.changeFlag;
  }

  update(index, childSize) {
    if (this.isInvalid(index)) {
      throw new ChildrenMainSizeParamError('The parameter check failed.', '401');
    } else if (this.isInvalid(childSize)) {
      // -1: represent default size.
      childSize = -1;
    }
    let startValue = Math.trunc(index);
    while (startValue >= this.sizeArray.length) {
      this.sizeArray.push(-1);
    }
    this.sizeArray.splice(startValue, 1, childSize);
    this.changeArray.push({ start: startValue, deleteCount: 1, childrenSize: [childSize] });
    this.changeFlag = !this.changeFlag;
  }

  isInvalid(input) {
    return !(Number.isFinite(input) && input >= 0);
  }

  clearChanges() {
    this.changeArray.splice(0);
  }
}

var ImageSpanAlignment;
(function (ImageSpanAlignment) {
  ImageSpanAlignment[ImageSpanAlignment["NONE"] = 0] = "NONE";
  ImageSpanAlignment[ImageSpanAlignment["TOP"] = 1] = "TOP";
  ImageSpanAlignment[ImageSpanAlignment["CENTER"] = 2] = "CENTER";
  ImageSpanAlignment[ImageSpanAlignment["BOTTOM"] = 3] = "BOTTOM";
  ImageSpanAlignment[ImageSpanAlignment["BASELINE"] = 4] = "BASELINE";
})(ImageSpanAlignment || (ImageSpanAlignment = {}));

var MenuAlignType;
(function (MenuAlignType) {
  MenuAlignType[MenuAlignType["START"] = 0] = "START";
  MenuAlignType[MenuAlignType["CENTER"] = 1] = "CENTER";
  MenuAlignType[MenuAlignType["END"] = 2] = "END";
})(MenuAlignType || (MenuAlignType = {}));

var ToolbarItemStatus;
(function (ToolbarItemStatus) {
  ToolbarItemStatus[ToolbarItemStatus["NORMAL"] = 0] = "NORMAL";
  ToolbarItemStatus[ToolbarItemStatus["DISABLED"] = 1] = "DISABLED";
  ToolbarItemStatus[ToolbarItemStatus["ACTIVE"] = 2] = "ACTIVE";
})(ToolbarItemStatus || (ToolbarItemStatus = {}));

var SecurityComponentLayoutDirection;
(function (SecurityComponentLayoutDirection) {
  SecurityComponentLayoutDirection[SecurityComponentLayoutDirection["HORIZONTAL"] = 0] = "HORIZONTAL";
  SecurityComponentLayoutDirection[SecurityComponentLayoutDirection["VERTICAL"] = 1] = "VERTICAL";
})(SecurityComponentLayoutDirection || (SecurityComponentLayoutDirection = {}));

var LocationIconStyle;
(function (LocationIconStyle) {
  LocationIconStyle[LocationIconStyle["FULL_FILLED"] = 0] = "FULL_FILLED";
  LocationIconStyle[LocationIconStyle["LINES"] = 1] = "LINES";
})(LocationIconStyle || (LocationIconStyle = {}));

var LocationDescription;
(function (LocationDescription) {
  LocationDescription[LocationDescription["CURRENT_LOCATION"] = 0] = "CURRENT_LOCATION";
  LocationDescription[LocationDescription["ADD_LOCATION"] = 1] = "ADD_LOCATION";
  LocationDescription[LocationDescription["SELECT_LOCATION"] = 2] = "SELECT_LOCATION";
  LocationDescription[LocationDescription["SHARE_LOCATION"] = 3] = "SHARE_LOCATION";
  LocationDescription[LocationDescription["SEND_LOCATION"] = 4] = "SEND_LOCATION";
  LocationDescription[LocationDescription["LOCATING"] = 5] = "LOCATING";
  LocationDescription[LocationDescription["LOCATION"] = 6] = "LOCATION";
  LocationDescription[LocationDescription["SEND_CURRENT_LOCATION"] = 7] = "SEND_CURRENT_LOCATION";
  LocationDescription[LocationDescription["RELOCATION"] = 8] = "RELOCATION";
  LocationDescription[LocationDescription["PUNCH_IN"] = 9] = "PUNCH_IN";
  LocationDescription[LocationDescription["CURRENT_POSITION"] = 10] = "CURRENT_POSITION";
})(LocationDescription || (LocationDescription = {}));

var LocationButtonOnClickResult;
(function (LocationButtonOnClickResult) {
  LocationButtonOnClickResult[LocationButtonOnClickResult["SUCCESS"] = 0] =
    "SUCCESS";
  LocationButtonOnClickResult[LocationButtonOnClickResult["TEMPORARY_AUTHORIZATION_FAILED"] = 1] =
    "TEMPORARY_AUTHORIZATION_FAILED ";
})(LocationButtonOnClickResult || (LocationButtonOnClickResult = {}));

var PasteIconStyle;
(function (PasteIconStyle) {
  PasteIconStyle[PasteIconStyle["LINES"] = 0] = "LINES";
})(PasteIconStyle || (PasteIconStyle = {}));

var PasteDescription;
(function (PasteDescription) {
  PasteDescription[PasteDescription["PASTE"] = 0] = "PASTE";
})(PasteDescription || (PasteDescription = {}));

var PasteButtonOnClickResult;
(function (PasteButtonOnClickResult) {
  PasteButtonOnClickResult[PasteButtonOnClickResult["SUCCESS"] = 0] =
    "SUCCESS";
  PasteButtonOnClickResult[PasteButtonOnClickResult["TEMPORARY_AUTHORIZATION_FAILED"] = 1] =
    "TEMPORARY_AUTHORIZATION_FAILED ";
})(PasteButtonOnClickResult || (PasteButtonOnClickResult = {}));

var SaveIconStyle;
(function (SaveIconStyle) {
  SaveIconStyle[SaveIconStyle["FULL_FILLED"] = 0] = "FULL_FILLED";
  SaveIconStyle[SaveIconStyle["LINES"] = 1] = "LINES";
  SaveIconStyle[SaveIconStyle["PICTURE"] = 2] = "PICTURE";
})(SaveIconStyle || (SaveIconStyle = {}));

var SaveDescription;
(function (SaveDescription) {
  SaveDescription[SaveDescription["DOWNLOAD"] = 0] = "DOWNLOAD";
  SaveDescription[SaveDescription["DOWNLOAD_FILE"] = 1] = "DOWNLOAD_FILE";
  SaveDescription[SaveDescription["SAVE"] = 2] = "SAVE";
  SaveDescription[SaveDescription["SAVE_IMAGE"] = 3] = "SAVE_IMAGE";
  SaveDescription[SaveDescription["SAVE_FILE"] = 4] = "SAVE_FILE";
  SaveDescription[SaveDescription["DOWNLOAD_AND_SHARE"] = 5] = "DOWNLOAD_AND_SHARE";
  SaveDescription[SaveDescription["RECEIVE"] = 6] = "RECEIVE";
  SaveDescription[SaveDescription["CONTINUE_TO_RECEIVE"] = 7] = "CONTINUE_TO_RECEIVE";
  SaveDescription[SaveDescription["SAVE_TO_GALLERY"] = 8] = "SAVE_TO_GALLERY";
  SaveDescription[SaveDescription["EXPORT_TO_GALLERY"] = 9] = "EXPORT_TO_GALLERY";
  SaveDescription[SaveDescription["QUICK_SAVE_TO_GALLERY"] = 10] = "QUICK_SAVE_TO_GALLERY";
  SaveDescription[SaveDescription["RESAVE_TO_GALLERY"] = 11] = "RESAVE_TO_GALLERY";
})(SaveDescription || (SaveDescription = {}));

var SaveButtonOnClickResult;
(function (SaveButtonOnClickResult) {
  SaveButtonOnClickResult[SaveButtonOnClickResult["SUCCESS"] = 0] =
    "SUCCESS";
  SaveButtonOnClickResult[SaveButtonOnClickResult["TEMPORARY_AUTHORIZATION_FAILED"] = 1] =
    "TEMPORARY_AUTHORIZATION_FAILED ";
})(SaveButtonOnClickResult || (SaveButtonOnClickResult = {}));

var ObscuredReasons;
(function (ObscuredReasons) {
  ObscuredReasons[ObscuredReasons["PLACEHOLDER"] = 0] = "PLACEHOLDER";
})(ObscuredReasons || (ObscuredReasons = {}));

var ListItemStyle;
(function (ListItemStyle) {
  ListItemStyle[ListItemStyle["NONE"] = 0] = "NONE";
  ListItemStyle[ListItemStyle["CARD"] = 1] = "CARD";
})(ListItemStyle || (ListItemStyle = {}));

var GridItemStyle;
(function (GridItemStyle) {
  GridItemStyle[GridItemStyle["NONE"] = 0] = "NONE";
  GridItemStyle[GridItemStyle["PLAIN"] = 1] = "PLAIN";
})(GridItemStyle || (GridItemStyle = {}));

var ListItemGroupStyle;
(function (ListItemGroupStyle) {
  ListItemGroupStyle[ListItemGroupStyle["NONE"] = 0] = "NONE";
  ListItemGroupStyle[ListItemGroupStyle["CARD"] = 1] = "CARD";
})(ListItemGroupStyle || (ListItemGroupStyle = {}));

var DragResult;
(function (DragResult) {
  DragResult[DragResult["DRAG_SUCCESSFUL"] = 0] = "DRAG_SUCCESSFUL";
  DragResult[DragResult["DRAG_FAILED"] = 1] = "DRAG_FAILED";
  DragResult[DragResult["DRAG_CANCELED"] = 2] = "DRAG_CANCELED";
  DragResult[DragResult["DROP_ENABLED"] = 3] = "DROP_ENABLED";
  DragResult[DragResult["DROP_DISABLED"] = 4] = "DROP_DISABLED";
})(DragResult || (DragResult = {}));

var XComponentType;
(function (XComponentType) {
  XComponentType[XComponentType["SURFACE"] = 0] = "SURFACE";
  XComponentType[XComponentType["COMPONENT"] = 1] = "COMPONENT";
  XComponentType[XComponentType["TEXTURE"] = 2] = "TEXTURE";
  XComponentType[XComponentType["NODE"] = 3] = "NODE";
})(XComponentType || (XComponentType = {}));

var NestedScrollMode;
(function (NestedScrollMode) {
  NestedScrollMode[NestedScrollMode["SELF_ONLY"] = 0] = "SELF_ONLY";
  NestedScrollMode[NestedScrollMode["SELF_FIRST"] = 1] = "SELF_FIRST";
  NestedScrollMode[NestedScrollMode["PARENT_FIRST"] = 2] = "PARENT_FIRST";
  NestedScrollMode[NestedScrollMode["PARALLEL"] = 3] = "PARALLEL";
})(NestedScrollMode || (NestedScrollMode = {}));

var IlluminatedType;
(function (IlluminatedType) {
  IlluminatedType[IlluminatedType["NONE"] = 0] = "NONE";
  IlluminatedType[IlluminatedType["BORDER"] = 1] = "BORDER";
  IlluminatedType[IlluminatedType["CONTENT"] = 2] = "CONTENT";
  IlluminatedType[IlluminatedType["BORDER_CONTENT"] = 3] = "BORDER_CONTENT";
  IlluminatedType[IlluminatedType["BLOOM_BORDER"] = 4] = "BLOOM_BORDER";
  IlluminatedType[IlluminatedType["BLOOM_BORDER_CONTENT"] = 5] = "BLOOM_BORDER_CONTENT";
})(IlluminatedType || (IlluminatedType = {}));

var ScrollAlign;
(function (ScrollAlign) {
  ScrollAlign[ScrollAlign["START"] = 0] = "START";
  ScrollAlign[ScrollAlign["CENTER"] = 1] = "CENTER";
  ScrollAlign[ScrollAlign["END"] = 2] = "END";
  ScrollAlign[ScrollAlign["AUTO"] = 3] = "AUTO";
})(ScrollAlign || (ScrollAlign = {}));

var SafeAreaType;
(function (SafeAreaType) {
  SafeAreaType[SafeAreaType["SYSTEM"] = 0] = "SYSTEM";
  SafeAreaType[SafeAreaType["CUTOUT"] = 1] = "CUTOUT";
  SafeAreaType[SafeAreaType["KEYBOARD"] = 2] = "KEYBOARD";
})(SafeAreaType || (SafeAreaType = {}));

var SafeAreaEdge;
(function (SafeAreaEdge) {
  SafeAreaEdge[SafeAreaEdge["TOP"] = 0] = "TOP";
  SafeAreaEdge[SafeAreaEdge["BOTTOM"] = 1] = "BOTTOM";
  SafeAreaEdge[SafeAreaEdge["START"] = 2] = "START";
  SafeAreaEdge[SafeAreaEdge["END"] = 3] = "END";
})(SafeAreaEdge || (SafeAreaEdge = {}));

let LayoutSafeAreaType;
(function (LayoutSafeAreaType) {
  LayoutSafeAreaType[LayoutSafeAreaType.SYSTEM = 0] = "SYSTEM";
})(LayoutSafeAreaType || (LayoutSafeAreaType = {}));

let LayoutSafeAreaEdge;
(function (LayoutSafeAreaEdge) {
  LayoutSafeAreaEdge[LayoutSafeAreaEdge.TOP = 0] = "TOP";
  LayoutSafeAreaEdge[LayoutSafeAreaEdge.BOTTOM = 1] = "BOTTOM";
})(LayoutSafeAreaEdge || (LayoutSafeAreaEdge = {}));

var RenderFit;
(function (RenderFit) {
  RenderFit[RenderFit["CENTER"] = 0] = "CENTER";
  RenderFit[RenderFit["TOP"] = 1] = "TOP";
  RenderFit[RenderFit["BOTTOM"] = 2] = "BOTTOM";
  RenderFit[RenderFit["LEFT"] = 3] = "LEFT";
  RenderFit[RenderFit["RIGHT"] = 4] = "RIGHT";
  RenderFit[RenderFit["TOP_LEFT"] = 5] = "TOP_LEFT";
  RenderFit[RenderFit["TOP_RIGHT"] = 6] = "TOP_RIGHT";
  RenderFit[RenderFit["BOTTOM_LEFT"] = 7] = "BOTTOM_LEFT";
  RenderFit[RenderFit["BOTTOM_RIGHT"] = 8] = "BOTTOM_RIGHT";
  RenderFit[RenderFit["RESIZE_FILL"] = 9] = "RESIZE_FILL";
  RenderFit[RenderFit["RESIZE_CONTAIN"] = 10] = "RESIZE_CONTAIN";
  RenderFit[RenderFit["RESIZE_CONTAIN_TOP_LEFT"] = 11] = "RESIZE_CONTAIN_TOP_LEFT";
  RenderFit[RenderFit["RESIZE_CONTAIN_BOTTOM_RIGHT"] = 12] = "RESIZE_CONTAIN_BOTTOM_RIGHT";
  RenderFit[RenderFit["RESIZE_COVER"] = 13] = "RESIZE_COVER";
  RenderFit[RenderFit["RESIZE_COVER_TOP_LEFT"] = 14] = "RESIZE_COVER_TOP_LEFT";
  RenderFit[RenderFit["RESIZE_COVER_BOTTOM_RIGHT"] = 15] = "RESIZE_COVER_BOTTOM_RIGHT";
})(RenderFit || (RenderFit = {}));

var WebCaptureMode;
(function (WebCaptureMode) {
  WebCaptureMode[WebCaptureMode["HOME_SCREEN"] = 0] = "HOME_SCREEN";
})(WebCaptureMode || (WebCaptureMode = {}));

var CalendarAlign;
(function (CalendarAlign) {
  CalendarAlign[CalendarAlign["START"] = 0] = "START";
  CalendarAlign[CalendarAlign["CENTER"] = 1] = "CENTER";
  CalendarAlign[CalendarAlign["END"] = 2] = "END";
})(CalendarAlign || (CalendarAlign = {}));

var DragBehavior;
(function (DragBehavior) {
  DragBehavior[DragBehavior["COPY"] = 0] = "COPY";
  DragBehavior[DragBehavior["MOVE"] = 1] = "MOVE";
})(DragBehavior || (DragBehavior = {}));

var PatternLockChallengeResult;
(function (PatternLockChallengeResult) {
  PatternLockChallengeResult[PatternLockChallengeResult["CORRECT"] = 1] = "CORRECT";
  PatternLockChallengeResult[PatternLockChallengeResult["WRONG"] = 2] = "WRONG";
})(PatternLockChallengeResult || (PatternLockChallengeResult = {}));

var DialogButtonDirection;
(function (DialogButtonDirection) {
  DialogButtonDirection[DialogButtonDirection["AUTO"] = 0] = "AUTO";
  DialogButtonDirection[DialogButtonDirection["HORIZONTAL"] = 1] = "HORIZONTAL";
  DialogButtonDirection[DialogButtonDirection["VERTICAL"] = 2] = "VERTICAL";
})(DialogButtonDirection || (DialogButtonDirection = {}));

var ParticleType;
(function (ParticleType) {
  ParticleType[ParticleType["POINT"] = 0] = "POINT";
  ParticleType[ParticleType["IMAGE"] = 1] = "IMAGE";
})(ParticleType || (ParticleType = {}));

var ParticleEmitterShape;
(function (ParticleEmitterShape) {
  ParticleEmitterShape[ParticleEmitterShape["RECTANGLE"] = 0] = "RECTANGLE";
  ParticleEmitterShape[ParticleEmitterShape["CIRCLE"] = 1] = "CIRCLE";
  ParticleEmitterShape[ParticleEmitterShape["ELLIPSE"] = 2] = "ELLIPSE";
})(ParticleEmitterShape || (ParticleEmitterShape = {}));

var DistributionType;
(function (DistributionType) {
  DistributionType[DistributionType["UNIFORM"] = 0] = "UNIFORM";
  DistributionType[DistributionType["GAUSSIAN"] = 1] = "GAUSSIAN";
})(DistributionType || (DistributionType = {}));

var ParticleUpdater;
(function (ParticleUpdater) {
  ParticleUpdater[ParticleUpdater["NONE"] = 0] = "NONE";
  ParticleUpdater[ParticleUpdater["RANDOM"] = 1] = "RANDOM";
  ParticleUpdater[ParticleUpdater["CURVE"] = 2] = "CURVE";
})(ParticleUpdater || (ParticleUpdater = {}));

var DisturbanceFieldShape;
(function (DisturbanceFieldShape) {
  DisturbanceFieldShape[DisturbanceFieldShape["RECT"] = 0] = "RECT";
  DisturbanceFieldShape[DisturbanceFieldShape["CIRCLE"] = 1] = "CIRCLE";
  DisturbanceFieldShape[DisturbanceFieldShape["ELLIPSE"] = 2] = "ELLIPSE";
})(DisturbanceFieldShape || (DisturbanceFieldShape = {}));

var SwiperNestedScrollMode;
(function (SwiperNestedScrollMode) {
  SwiperNestedScrollMode[SwiperNestedScrollMode["SELF_ONLY"] = 0] = "SELF_ONLY";
  SwiperNestedScrollMode[SwiperNestedScrollMode["SELF_FIRST"] = 1] = "SELF_FIRST";
})(SwiperNestedScrollMode || (SwiperNestedScrollMode = {}));

var CheckBoxStyle;
(function (CheckBoxStyle) {
  CheckBoxStyle["CIRCULAR_STYLE"] = 0;
  CheckBoxStyle["SQUARE_STYLE"] = 1;
})(CheckBoxStyle || (CheckBoxStyle = {}));

var ModelType;
(function (ModelType) {
  ModelType[ModelType["TEXTURE"] = 0] = "TEXTURE";
  ModelType[ModelType["SURFACE"] = 1] = "SURFACE";
})(ModelType || (ModelType = {}));

var ModelLightType;
(function (ModelLightType) {
  ModelLightType[ModelLightType["INVALID"] = 0] = "INVALID";
  ModelLightType[ModelLightType["DIRECTIONAL"] = 1] = "DIRECTIONAL";
  ModelLightType[ModelLightType["POINT"] = 2] = "POINT";
  ModelLightType[ModelLightType["SPOT"] = 3] = "SPOT";
})(ModelLightType || (ModelLightType = {}));

var ModelAnimationStates;
(function (ModelAnimationStates) {
  ModelAnimationStates[ModelAnimationStates["PLAY"] = 0] = "PLAY";
  ModelAnimationStates[ModelAnimationStates["PAUSE"] = 1] = "PAUSE";
  ModelAnimationStates[ModelAnimationStates["STOP"] = 2] = "STOP";
})(ModelAnimationStates || (ModelAnimationStates = {}));

var SwipeActionState;
(function (SwipeActionState) {
  SwipeActionState[SwipeActionState["COLLAPSED"] = 0] = "COLLAPSED";
  SwipeActionState[SwipeActionState["EXPANDED"] = 1] = "EXPANDED";
  SwipeActionState[SwipeActionState["ACTIONING"] = 2] = "ACTIONING";
})(SwipeActionState || (SwipeActionState = {}));

var CheckBoxShape;
(function (CheckBoxShape) {
  CheckBoxShape["CIRCLE"] = 0;
  CheckBoxShape["ROUNDED_SQUARE"] = 1;
})(CheckBoxShape || (CheckBoxShape = {}));

var FinishCallbackType;
(function (FinishCallbackType) {
  FinishCallbackType["REMOVED"] = 0;
  FinishCallbackType["LOGICALLY"] = 1;
})(FinishCallbackType || (FinishCallbackType = {}));

var WebLayoutMode;
(function (WebLayoutMode) {
  WebLayoutMode[WebLayoutMode["NONE"] = 0] = "NONE";
  WebLayoutMode[WebLayoutMode["FIT_CONTENT"] = 1] = "FIT_CONTENT";
})(WebLayoutMode || (WebLayoutMode = {}));

var OptionWidthMode;
(function (OptionWidthMode) {
  OptionWidthMode["FIT_CONTENT"] = "fit_content";
  OptionWidthMode["FIT_TRIGGER"] = "fit_trigger";
})(OptionWidthMode || (OptionWidthMode = {}));

var ArrowPointPosition;
(function (ArrowPointPosition) {
  ArrowPointPosition["START"] = "Start";
  ArrowPointPosition["CENTER"] = "Center";
  ArrowPointPosition["END"] = "End";
})(ArrowPointPosition || (ArrowPointPosition = {}));

var DragPreviewMode;
(function (DragPreviewMode) {
  DragPreviewMode["AUTO"] = 1;
  DragPreviewMode["DISABLE_SCALE"] = 2;
  DragPreviewMode["ENABLE_DEFAULT_SHADOW"] = 3;
  DragPreviewMode["ENABLE_DEFAULT_RADIUS"] = 4;
})(DragPreviewMode || (DragPreviewMode = {}));

var FoldStatus;
(function (FoldStatus) {
  FoldStatus[FoldStatus["FOLD_STATUS_UNKNOWN"] = 0] = "FOLD_STATUS_UNKNOWN";
  FoldStatus[FoldStatus["FOLD_STATUS_EXPANDED"] = 1] = "FOLD_STATUS_EXPANDED";
  FoldStatus[FoldStatus["FOLD_STATUS_FOLDED"] = 2] = "FOLD_STATUS_FOLDED";
  FoldStatus[FoldStatus["FOLD_STATUS_HALF_FOLDED"] = 3] = "FOLD_STATUS_HALF_FOLDED";
})(FoldStatus || (FoldStatus = {}));

var EmbeddedType;
(function (EmbeddedType) {
  EmbeddedType[EmbeddedType["EMBEDDED_UI_EXTENSION"] = 0] = "EMBEDDED_UI_EXTENSION";
})(EmbeddedType || (EmbeddedType = {}));

var OutlineStyle;
(function (OutlineStyle) {
  OutlineStyle[OutlineStyle["SOLID"] = 0] = "SOLID";
  OutlineStyle[OutlineStyle["DASHED"] = 1] = "DASHED";
  OutlineStyle[OutlineStyle["DOTTED"] = 2] = "DOTTED";
})(OutlineStyle || (OutlineStyle = {}));

var ButtonStyleMode;
(function (ButtonStyleMode) {
  ButtonStyleMode["NORMAL"] = 0;
  ButtonStyleMode["EMPHASIZED"] = 1;
  ButtonStyleMode["TEXTUAL"] = 2;
})(ButtonStyleMode || (ButtonStyleMode = {}));

let RadioIndicatorType;
(function (RadioIndicatorType) {
  RadioIndicatorType[RadioIndicatorType.TICK = 0] = "TICK";
  RadioIndicatorType[RadioIndicatorType.DOT = 1] = "DOT";
  RadioIndicatorType[RadioIndicatorType.CUSTOM = 2] = "CUSTOM";
})(RadioIndicatorType  || (RadioIndicatorType  = {}));

var ControlSize;
(function (ControlSize) {
  ControlSize[ControlSize["SMALL"] = 0] = "SMALL";
  ControlSize[ControlSize["NORMAL"] = 1] = "NORMAL";
})(ControlSize || (ControlSize = {}));

var ImageAnalyzerType;
(function (ImageAnalyzerType) {
  ImageAnalyzerType[ImageAnalyzerType["SUBJECT"] = 0] = "SUBJECT";
  ImageAnalyzerType[ImageAnalyzerType["TEXT"] = 1] = "TEXT";
  ImageAnalyzerType[ImageAnalyzerType["OBJECT_LOOKUP"] = 2] = "OBJECT_LOOKUP";
})(ImageAnalyzerType || (ImageAnalyzerType = {}));

function wrapBuilder(builder) {
  return new WrappedBuilder(builder);
}
class WrappedBuilder {
  constructor(builder) {
    this.builder = builder;
  }
}

let TextSpanType;
(function (TextSpanType) {
  TextSpanType[TextSpanType['TEXT'] = 0] = 'TEXT';
  TextSpanType[TextSpanType['IMAGE'] = 1] = 'IMAGE';
  TextSpanType[TextSpanType['MIXED'] = 2] = 'MIXED';
})(TextSpanType || (TextSpanType = {}));

let TextResponseType;
(function (TextResponseType) {
  TextResponseType[TextResponseType['RIGHT_CLICK'] = 0] = 'RIGHT_CLICK';
  TextResponseType[TextResponseType['LONG_PRESS'] = 1] = 'LONG_PRESS';
  TextResponseType[TextResponseType['SELECT'] = 2] = 'SELECT';
})(TextResponseType || (TextResponseType = {}));

let NativeEmbedStatus;
(function (NativeEmbedStatus) {
  NativeEmbedStatus['CREATE'] = 0;
  NativeEmbedStatus['UPDATE'] = 1;
  NativeEmbedStatus['DESTROY'] = 2;
  NativeEmbedStatus['ENTER_BFCACHE'] = 3;
  NativeEmbedStatus['LEAVE_BFCACHE'] = 4;
  NativeEmbedStatus['VISIBLE'] = 5;
  NativeEmbedStatus['HIDDEN'] = 6;
})(NativeEmbedStatus || (NativeEmbedStatus = {}));

let RenderMode;
(function (RenderMode) {
  RenderMode['ASYNC_RENDER'] = 0;
  RenderMode['SYNC_RENDER'] = 1;
})(RenderMode || (RenderMode = {}));

let ButtonRole;
(function (ButtonRole) {
  ButtonRole['NORMAL'] = 0;
  ButtonRole['ERROR'] = 1;
})(ButtonRole || (ButtonRole = {}));

let MenuPolicy;
(function (MenuPolicy) {
  MenuPolicy['DEFAULT'] = 0;
  MenuPolicy['HIDE'] = 1;
  MenuPolicy['SHOW'] = 2;
})(MenuPolicy || (MenuPolicy = {}));

let PreDragStatus;
(function (PreDragStatus) {
  PreDragStatus['ACTION_DETECTING_STATUS'] = 0;
  PreDragStatus['READY_TO_TRIGGER_DRAG_ACTION'] = 1;
  PreDragStatus['PREVIEW_LIFT_STARTED'] = 2;
  PreDragStatus['PREVIEW_LIFT_FINISHED'] = 3;
  PreDragStatus['PREVIEW_LANDING_STARTED'] = 4;
  PreDragStatus['PREVIEW_LANDING_FINISHED'] = 5;
  PreDragStatus['ACTION_CANCELED_BEFORE_DRAG'] = 6;
})(PreDragStatus || (PreDragStatus = {}));

let DataOperationType;
(function (DataOperationType) {
  DataOperationType['ADD'] = "add";
  DataOperationType['DELETE'] = "delete";
  DataOperationType['CHANGE'] = "change";
  DataOperationType['MOVE'] = "move";
  DataOperationType['EXCHANGE'] = "exchange";
  DataOperationType['RELOAD'] = "reload";
})(DataOperationType || (DataOperationType = {}));

var StyledStringKey;
(function (StyledStringKey) {
  StyledStringKey[StyledStringKey['FONT'] = 0] = 'FONT';
  StyledStringKey[StyledStringKey['DECORATION'] = 1] = 'DECORATION';
  StyledStringKey[StyledStringKey['BASELINE_OFFSET'] = 2] = 'BASELINE_OFFSET';
  StyledStringKey[StyledStringKey['LETTER_SPACING'] = 3] = 'LETTER_SPACING';
  StyledStringKey[StyledStringKey['TEXT_SHADOW'] = 4] = 'TEXT_SHADOW';
  StyledStringKey[StyledStringKey['LINE_HEIGHT'] = 5] = 'LINE_HEIGHT';
  StyledStringKey[StyledStringKey['PARAGRAPH_STYLE'] = 200] = 'PARAGRAPH_STYLE';
  StyledStringKey[StyledStringKey['BACKGROUND_COLOR'] = 6] = 'BACKGROUND_COLOR';
  StyledStringKey[StyledStringKey['URL'] = 7] = 'URL';
  StyledStringKey[StyledStringKey['GESTURE'] = 100] = 'GESTURE';
  StyledStringKey[StyledStringKey['IMAGE'] = 300] = 'IMAGE';
  StyledStringKey[StyledStringKey['CUSTOM_SPAN'] = 400] = 'CUSTOM_SPAN';
  StyledStringKey[StyledStringKey['USER_DATA'] = 500] = 'USER_DATA';
})(StyledStringKey || (StyledStringKey = {}));

class CustomSpan extends NativeCustomSpan {
  type_ = 'CustomSpan';
}

class UserDataSpan {
  type_ = 'ExtSpan';
}

let FocusPriority;
(function (FocusPriority) {
  FocusPriority[FocusPriority["AUTO"] = 0] = "AUTO";
  FocusPriority[FocusPriority["PRIOR"] = 2000] = "PRIOR";
  FocusPriority[FocusPriority["PREVIOUS"] = 3000] = "PREVIOUS";
})(FocusPriority || (FocusPriority = {}));
var SubMenuExpandingMode;
(function (SubMenuExpandingMode) {
  SubMenuExpandingMode[SubMenuExpandingMode["SIDE_EXPAND"] = 0] = "SIDE";
  SubMenuExpandingMode[SubMenuExpandingMode["EMBEDDED_EXPAND"] = 1] = "EMBEDDED";
  SubMenuExpandingMode[SubMenuExpandingMode["STACK_EXPAND"] = 2] = "STACK";
})(SubMenuExpandingMode || (SubMenuExpandingMode = {}));

var ViewportFit;
(function (ViewportFit) {
  ViewportFit[ViewportFit["AUTO"] = 0] = "AUTO";
  ViewportFit[ViewportFit["CONTAINS"] = 1] = "CONTAINS";
  ViewportFit[ViewportFit["COVER"] = 2] = "COVER";
})(ViewportFit || (ViewportFit = {}));

var TextDeleteDirection;
(function (TextDeleteDirection) {
    TextDeleteDirection[TextDeleteDirection["BACKWARD"] = 0] = "BACKWARD";
    TextDeleteDirection[TextDeleteDirection["FORWARD"] = 1] = "FORWARD";
})(TextDeleteDirection || (TextDeleteDirection = {}));

var GestureRecognizerState;
(function (GestureRecognizerState) {
  GestureRecognizerState[GestureRecognizerState["READY"] = 0] = "READY";
  GestureRecognizerState[GestureRecognizerState["DETECTING"] = 1] = "DETECTING";
  GestureRecognizerState[GestureRecognizerState["PENDING"] = 2] = "PENDING";
  GestureRecognizerState[GestureRecognizerState["BLOCKED"] = 3] = "BLOCKED";
  GestureRecognizerState[GestureRecognizerState["SUCCESSFUL"] = 4] = "SUCCESSFUL";
  GestureRecognizerState[GestureRecognizerState["FAILED"] = 5] = "FAILED";
})(GestureRecognizerState || (GestureRecognizerState = {}));

let GridItemAlignment;
(function (GridItemAlignment) {
  GridItemAlignment[GridItemAlignment['DEFAULT'] = 0] = 'DEFAULT';
  GridItemAlignment[GridItemAlignment['STRETCH'] = 1] = 'STRETCH';
})(GridItemAlignment || (GridItemAlignment = {}));

let ContentClipMode;
(function (ContentClipMode) {
  ContentClipMode[ContentClipMode['CONTENT_ONLY'] = 0] = 'CONTENT_ONLY';
  ContentClipMode[ContentClipMode['BOUNDARY'] = 1] = 'BOUNDARY';
  ContentClipMode[ContentClipMode['SAFE_AREA'] = 2] = 'SAFE_AREA';
})(ContentClipMode || (ContentClipMode = {}));

var AccessibilityHoverType;
(function (AccessibilityHoverType) {
  AccessibilityHoverType[AccessibilityHoverType["HOVER_ENTER"] = 0] = "HOVER_ENTER";
  AccessibilityHoverType[AccessibilityHoverType["HOVER_MOVE"] = 1] = "HOVER_MOVE";
  AccessibilityHoverType[AccessibilityHoverType["HOVER_EXIT"] = 2] = "HOVER_EXIT";
  AccessibilityHoverType[AccessibilityHoverType["HOVER_CANCEL"] = 3] = "HOVER_CANCEL";
})(AccessibilityHoverType || (AccessibilityHoverType = {}));

let WidthBreakpoint;
(function (WidthBreakpoint) {
  WidthBreakpoint[WidthBreakpoint['WIDTH_XS'] = 0] = 'WIDTH_XS';
  WidthBreakpoint[WidthBreakpoint['WIDTH_SM'] = 1] = 'WIDTH_SM';
  WidthBreakpoint[WidthBreakpoint['WIDTH_MD'] = 2] = 'WIDTH_MD';
  WidthBreakpoint[WidthBreakpoint['WIDTH_LG'] = 3] = 'WIDTH_LG';
  WidthBreakpoint[WidthBreakpoint['WIDTH_XL'] = 4] = 'WIDTH_XL';
})(WidthBreakpoint || (WidthBreakpoint = {}));

let HeightBreakpoint;
(function (HeightBreakpoint) {
  HeightBreakpoint[HeightBreakpoint['HEIGHT_SM'] = 0] = 'HEIGHT_SM';
  HeightBreakpoint[HeightBreakpoint['HEIGHT_MD'] = 1] = 'HEIGHT_MD';
  HeightBreakpoint[HeightBreakpoint['HEIGHT_LG'] = 2] = 'HEIGHT_LG';
})(HeightBreakpoint || (HeightBreakpoint = {}));

var WebElementType;
(function (WebElementType) {
  WebElementType[WebElementType['IMAGE'] = 1] = 'IMAGE';
})(WebElementType || (WebElementType = {}));

var WebResponseType;
(function (WebResponseType) {
  WebResponseType[WebResponseType['LONG_PRESS'] = 1] = 'LONG_PRESS';
})(WebResponseType || (WebResponseType = {}));

class ImageAnalyzerController {
  constructor() {
  }

  registerSupportTypesAction(getSupportTypesAction) {
    this.getSupportTypesAction = getSupportTypesAction;
  }

  unRegisterSupportTypesAction() {
    this.getSupportTypesAction = null;
  }

  getImageAnalyzerSupportTypes() {
    if (this.getSupportTypesAction === null || this.getSupportTypesAction === undefined) {
      return null;
    }
    return this.getSupportTypesAction();
  }
}
