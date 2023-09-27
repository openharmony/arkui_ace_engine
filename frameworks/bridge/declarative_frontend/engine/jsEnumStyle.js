/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
  ColoringStrategy["INVERT"] = "Invert";
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
  ButtonType[ButtonType["Normal"] = 0] = "Normal";
  ButtonType[ButtonType["Capsule"] = 1] = "Capsule";
  ButtonType[ButtonType["Circle"] = 2] = "Circle";
  ButtonType[ButtonType["Arc"] = 4] = "Arc";
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
})(ImageFit || (ImageFit = {}));

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
})(TextDecorationStyle || (TextDecorationStyle= {}));

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
  GesturePriority[GesturePriority["High"] = 1] = "High";
  GesturePriority[GesturePriority["Parallel"] = 2] = "Parallel";
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
})(FormDimension || (FormDimension = {}));

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

var DisplayedComponentType;
(function (DisplayedComponentType) {
  DisplayedComponentType[DisplayedComponentType["HOUR_MINUTE"] = 0] = "HOUR_MINUTE";
  DisplayedComponentType[DisplayedComponentType["HOUR_MINUTE_SECOND"] = 1] = "HOUR_MINUTE_SECOND";
})(DisplayedComponentType || (DisplayedComponentType = {}));

var InputType;
(function (InputType) {
  InputType[InputType["Normal"] = 0] = "Normal";
  InputType[InputType["Number"] = 2] = "Number";
  InputType[InputType["PhoneNumber"] = 3] = "PhoneNumber";
  InputType[InputType["Email"] = 5] = "Email";
  InputType[InputType["Password"] = 7] = "Password";
})(InputType || (InputType = {}));

var EnterKeyType;
(function (EnterKeyType) {
  EnterKeyType[EnterKeyType["Go"] = 2] = "Go";
  EnterKeyType[EnterKeyType["Search"] = 3] = "Search";
  EnterKeyType[EnterKeyType["Send"] = 4] = "Send";
  EnterKeyType[EnterKeyType["Next"] = 5] = "Next";
  EnterKeyType[EnterKeyType["Done"] = 6] = "Done";
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

var ResponseType;
(function (ResponseType) {
  ResponseType[ResponseType["RightClick"] = 0] = "RightClick";
  ResponseType[ResponseType["LongPress"] = 1] = "LongPress";
})(ResponseType || (ResponseType = {}));

var MenuPreviewMode;
(function (MenuPreviewMode) {
  MenuPreviewMode[MenuPreviewMode["NONE"] = 0] = "NONE";
  MenuPreviewMode[MenuPreviewMode["IMAGE"] = 1] = "IMAGE";
})(MenuPreviewMode || (MenuPreviewMode = {}));

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
  MixedMode[MixedMode["ALL"] = 0] = "All";
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

var RenderExitReason;
(function (RenderExitReason) {
  RenderExitReason[RenderExitReason["ProcessAbnormalTermination"] = 0] = "ProcessAbnormalTermination";
  RenderExitReason[RenderExitReason["ProcessWasKilled"] = 1] = "ProcessWasKilled";
  RenderExitReason[RenderExitReason["ProcessCrashed"] = 2] = "ProcessCrashed";
  RenderExitReason[RenderExitReason["ProcessOom"] = 3] = "ProcessOom";
  RenderExitReason[RenderExitReason["ProcessExitUnknown"] = 4] = "ProcessExitUnknown";
})(RenderExitReason || (RenderExitReason = {}));

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
  CopyOptions[CopyOptions["CrossDevice"] = 3] = "CrossDevice";
})(CopyOptions || (CopyOptions = {}));

var RichEditorSpanType;
(function (RichEditorSpanType) {
  RichEditorSpanType[RichEditorSpanType["TEXT"] = 0] = "TEXT";
  RichEditorSpanType[RichEditorSpanType["IMAGE"] = 1] = "IMAGE";
  RichEditorSpanType[RichEditorSpanType["MIXED"] = 2] = "MIXED";
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
  BlurStyle[BlurStyle["NONE"] = 0] = "NONE";
})(BlurStyle || (BlurStyle = {}));

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
})(SheetSize || (SheetSize = {}));

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
})(FunctionKey || (FunctionKey = {}));

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

var SliderBlockType;
(function (SliderBlockType) {
  SliderBlockType[SliderBlockType["DEFAULT"] = 0] = "DEFAULT";
  SliderBlockType[SliderBlockType["IMAGE"] = 1] = "IMAGE";
  SliderBlockType[SliderBlockType["SHAPE"] = 2] = "SHAPE";
})(SliderBlockType || (SliderBlockType = {}));

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

class NavPathInfo {
  constructor(name, param) {
    this.name = name;
    this.param = param;
  }
}

class NavPathStack {
  constructor() {
    this.pathArray = [];
    // indicate class has changed.
    this.changeFlag = 0;
    this.type = this.constructor.name;
  }
  pushName(name, param) {
    this.pathArray.push(new NavPathInfo(name, param));
    this.changeFlag = this.changeFlag + 1;
  }
  push(info) {
    this.pathArray.push(info);
    this.changeFlag = this.changeFlag + 1;
  }
  pushPathByName(name, param) {
    this.pathArray.push(new NavPathInfo(name, param));
    this.changeFlag = this.changeFlag + 1;
  }
  pushPath(info) {
    this.pathArray.push(info);
    this.changeFlag = this.changeFlag + 1;
  }
  pop() {
    if (this.pathArray.length === 0) {
      return undefined;
    }
    let pathInfo = this.pathArray.pop();
    this.changeFlag = this.changeFlag + 1;
    return pathInfo;
  }
  popTo(name) {
    let index = this.pathArray.findIndex(element => element.name === name);
    if (index === -1) {
      return -1;
    }
    this.pathArray.splice(index + 1);
    this.changeFlag = this.changeFlag + 1;
    return index;
  }
  popToName(name) {
    let index = this.pathArray.findIndex(element => element.name === name);
    if (index === -1) {
      return -1;
    }
    this.pathArray.splice(index + 1);
    this.changeFlag = this.changeFlag + 1;
    return index;
  }
  popToIndex(index) {
    if (index >= this.pathArray.length) {
      return;
    }
    this.pathArray.splice(index + 1);
    this.changeFlag = this.changeFlag + 1;
  }
  moveToTop(name) {
    let index = this.pathArray.findIndex(element => element.name === name);
    if (index === -1) {
      return -1;
    }
    let info = this.pathArray.splice(index, 1);
    this.pathArray.push(info[0]);
    this.changeFlag = this.changeFlag + 1;
    return index;
  }
  moveIndexToTop(index) {
    if (index >= this.pathArray.length) {
      return;
    }
    let info = this.pathArray.splice(index, 1);
    this.pathArray.push(info[0]);
    this.changeFlag = this.changeFlag + 1;
  }
  clear() {
    this.pathArray.splice(0);
    this.changeFlag = this.changeFlag + 1;
  }
  removeName(name) {
    var removed = false;
    for (var i = 0; i < this.pathArray.length; i++) {
      if (this.pathArray[i].name === name) {
        this.pathArray.splice(i, 1);
        removed = true;
      }
    }
    if (removed) {
      this.changeFlag = this.changeFlag + 1;
    }
  }
  removeIndex(index) {
    if (index >= this.pathArray.length) {
      return;
    }
    this.pathArray.splice(index, 1);
    this.changeFlag = this.changeFlag + 1;
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
  size() {
    return this.pathArray.length;
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
})(XComponentType || (XComponentType = {}));

var NestedScrollMode;
(function (NestedScrollMode) {
  NestedScrollMode[NestedScrollMode["SELF_ONLY"] = 0] = "SELF_ONLY";
  NestedScrollMode[NestedScrollMode["SELF_FIRST"] = 1] = "SELF_FIRST";
  NestedScrollMode[NestedScrollMode["PARENT_FIRST"] = 2] = "PARENT_FIRST";
  NestedScrollMode[NestedScrollMode["PARALLEL"] = 3] = "PARALLEL";
})(NestedScrollMode || (NestedScrollMode = {}));

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

var ParticleUpdater;
(function (ParticleUpdater) {
  ParticleUpdater[ParticleUpdater["NONE"] = 0] = "NONE";
  ParticleUpdater[ParticleUpdater["RANDOM"] = 1] = "RANDOM";
  ParticleUpdater[ParticleUpdater["CURVE"] = 2] = "CURVE";
})(ParticleUpdater || (ParticleUpdater = {}));
