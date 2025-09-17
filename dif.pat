diff --git a/frameworks/core/interfaces/native/node/node_span_modifier.cpp b/frameworks/core/interfaces/native/node/node_span_modifier.cpp
index b7c838e1e6c..967d98c2305 100644
--- a/frameworks/core/interfaces/native/node/node_span_modifier.cpp
+++ b/frameworks/core/interfaces/native/node/node_span_modifier.cpp
@@ -272,10 +272,23 @@ void ResetSpanDecoration(ArkUINodeHandle node)
 
 void SetSpanFontColor(ArkUINodeHandle node, uint32_t textColor, void* fontColorRawPtr)
 {
-    auto* uiNode = reinterpret_cast<UINode*>(node);
+    auto *uiNode = reinterpret_cast<UINode *>(node);
     CHECK_NULL_VOID(uiNode);
-    SpanModelNG::SetTextColor(uiNode, Color(textColor));
-    NodeModifier::ProcessResourceObj<Color>(uiNode, "fontColor", Color(textColor), fontColorRawPtr);
+    Color result = Color(textColor);
+    SpanModelNG::SetTextColor(uiNode, result);
+    if (SystemProperties::ConfigChangePerform()) {
+        auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
+        CHECK_NULL_VOID(spanNode);
+        RefPtr<ResourceObject> resObj;
+        if (!fontColorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, uiNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(fontColorRawPtr));
+        }
+        if (resObj) {
+            spanNode->RegisterResource<Color>("fontColor", resObj, result);
+        }
+    }
 }
 
 uint32_t GetSpanFontColor(ArkUINodeHandle node)
diff --git a/frameworks/core/interfaces/native/node/node_text_area_modifier.cpp b/frameworks/core/interfaces/native/node/node_text_area_modifier.cpp
index 4b6f8dc60e0..3ba1924137e 100644
--- a/frameworks/core/interfaces/native/node/node_text_area_modifier.cpp
+++ b/frameworks/core/interfaces/native/node/node_text_area_modifier.cpp
@@ -20,6 +20,7 @@
 #include "core/components_ng/pattern/text_field/text_field_model_ng.h"
 #include "core/components/common/properties/text_style_parser.h"
 #include "interfaces/native/node/node_model.h"
+#include "core/common/resource/resource_parse_utils.h"
 
 namespace OHOS::Ace::NG {
 namespace {
@@ -195,14 +196,20 @@ void SetTextAreaPlaceholderColor(ArkUINodeHandle node, ArkUI_Uint32 color, void*
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetPlaceholderColor(frameNode, result);
     auto pattern = frameNode->GetPattern();
     CHECK_NULL_VOID(pattern);
-    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
-        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
-        pattern->RegisterResource<Color>("placeholderColor", resObj, Color(color));
-    } else {
-        pattern->UnRegisterResource("placeholderColor");
+    if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
+        if (resObj) {
+            pattern->RegisterResource<Color>("placeholderColor", resObj, result);
+        }
     }
 }
 
@@ -441,15 +448,19 @@ void SetTextAreaCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* color
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetCaretColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetCaretColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!colorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(colorRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (colorRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
-            pattern->RegisterResource<Color>("caretColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("caretColor");
+        if (resObj) {
+            pattern->RegisterResource<Color>("caretColor", resObj, result);
         }
     }
 }
@@ -484,15 +495,19 @@ void SetTextAreaFontColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRaw
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetTextColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetTextColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (resRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
-            pattern->RegisterResource<Color>("fontColor", resObj, Color(color));
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
         } else {
-            pattern->UnRegisterResource("fontColor");
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
+        if (resObj) {
+            pattern->RegisterResource<Color>("fontColor", resObj, result);
         }
     }
 }
@@ -704,17 +719,21 @@ ArkUI_Bool GetTextAreaEditing(ArkUINodeHandle node)
 
 void SetTextAreaBackgroundColor(ArkUINodeHandle node, uint32_t color, void* resRawPtr)
 {
-    auto* frameNode = reinterpret_cast<FrameNode*>(node);
+    auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetBackgroundColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetBackgroundColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (resRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
-            pattern->RegisterResource<Color>("backgroundColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("backgroundColor");
+        if (resObj) {
+            pattern->RegisterResource<Color>("backgroundColor", resObj, result);
         }
     }
 }
diff --git a/frameworks/core/interfaces/native/node/node_text_input_modifier.cpp b/frameworks/core/interfaces/native/node/node_text_input_modifier.cpp
index 775d36566b7..c1bb7803149 100644
--- a/frameworks/core/interfaces/native/node/node_text_input_modifier.cpp
+++ b/frameworks/core/interfaces/native/node/node_text_input_modifier.cpp
@@ -22,6 +22,7 @@
 #include "core/components/common/properties/text_style_parser.h"
 #include "core/interfaces/arkoala/arkoala_api.h"
 #include "interfaces/native/node/node_model.h"
+#include "core/common/resource/resource_parse_utils.h"
 
 namespace OHOS::Ace::NG {
 namespace {
@@ -67,15 +68,19 @@ void SetTextInputCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* colo
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetCaretColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetCaretColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!colorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(colorRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (colorRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
-            pattern->RegisterResource<Color>("caretColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("caretColor");
+        if (resObj) {
+            pattern->RegisterResource<Color>("caretColor", resObj, result);
         }
     }
 }
@@ -131,15 +136,19 @@ void SetTextInputPlaceholderColor(ArkUINodeHandle node, ArkUI_Uint32 color, void
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetPlaceholderColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetPlaceholderColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!colorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(colorRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (colorRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
-            pattern->RegisterResource<Color>("placeholderColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("placeholderColor");
+        if (resObj) {
+            pattern->RegisterResource<Color>("placeholderColor", resObj, result);
         }
     }
 }
@@ -718,15 +727,19 @@ void SetTextInputSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 colo
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (resRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
-            pattern->RegisterResource<Color>("selectedBackgroundColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("selectedBackgroundColor");
+        if (resObj) {
+            pattern->RegisterResource<Color>("selectedBackgroundColor", resObj, result);
         }
     }
 }
@@ -858,15 +871,19 @@ void SetTextInputFontColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRa
 {
     auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetTextColor(frameNode, Color(color));
+    Color result = Color(color);
+    TextFieldModelNG::SetTextColor(frameNode, result);
     if (SystemProperties::ConfigChangePerform()) {
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (resRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
-            pattern->RegisterResource<Color>("fontColor", resObj, Color(color));
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
         } else {
-            pattern->UnRegisterResource("fontColor");
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
+        if (resObj) {
+            pattern->RegisterResource<Color>("fontColor", resObj, result);
         }
     }
 }
@@ -1245,19 +1262,23 @@ ArkUI_Float32 GetTextInputFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
 
 void SetTextInputBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* resRawPtr)
 {
-    auto* frameNode = reinterpret_cast<FrameNode*>(node);
+    auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
-    TextFieldModelNG::SetBackgroundColor(frameNode, Color(color));
+    Color result = Color(color);
     if (SystemProperties::ConfigChangePerform()) {
+        RefPtr<ResourceObject> resObj;
+        if (!resRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(resRawPtr));
+        }
         auto pattern = frameNode->GetPattern();
         CHECK_NULL_VOID(pattern);
-        if (resRawPtr) {
-            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
+        if (resObj) {
             pattern->RegisterResource<Color>("backgroundColor", resObj, Color(color));
-        } else {
-            pattern->UnRegisterResource("backgroundColor");
         }
     }
+    TextFieldModelNG::SetBackgroundColor(frameNode, result);
 }
 
 void SetTextInputBackgroundColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 color,
@@ -1584,46 +1605,62 @@ void SetTextInputUserUnderlineColor(ArkUINodeHandle node, const ArkUI_Uint32* va
         return;
     }
     if (hasValues[CALL_ARG_0]) {
-        userColor.typing = Color(values[CALL_ARG_0]);
+        Color result = Color(values[CALL_ARG_0]);
+        userColor.typing = result;
         if (SystemProperties::ConfigChangePerform()) {
+            RefPtr<ResourceObject> resObj;
             if (underlineColorObj && underlineColorObj->typingColorObj) {
-                auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(underlineColorObj->typingColorObj));
-                pattern->RegisterResource<Color>("underlineColorTyping", resObj, Color(values[CALL_ARG_0]));
+                resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(underlineColorObj->typingColorObj));
             } else {
-                pattern->UnRegisterResource("underlineColorTyping");
+                ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+            }
+            if (resObj) {
+                pattern->RegisterResource<Color>("underlineColorTyping", resObj, Color(values[CALL_ARG_0]));
             }
         }
     }
     if (hasValues[CALL_ARG_1]) {
-        userColor.normal = Color(values[CALL_ARG_1]);
+        Color result = Color(values[CALL_ARG_1]);
+        userColor.normal = result;
         if (SystemProperties::ConfigChangePerform()) {
+            RefPtr<ResourceObject> resObj;
             if (underlineColorObj && underlineColorObj->normalColorObj) {
-                auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(underlineColorObj->normalColorObj));
-                pattern->RegisterResource<Color>("underlineColorNormal", resObj, Color(values[CALL_ARG_1]));
+                resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(underlineColorObj->normalColorObj));
             } else {
-                pattern->UnRegisterResource("underlineColorNormal");
+                ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+            }
+            if (resObj) {
+                pattern->RegisterResource<Color>("underlineColorNormal", resObj, Color(values[CALL_ARG_1]));
             }
         }
     }
     if (hasValues[CALL_ARG_2]) {
-        userColor.error = Color(values[CALL_ARG_2]);
+        Color result = Color(values[CALL_ARG_0]);
+        userColor.error = result;
         if (SystemProperties::ConfigChangePerform()) {
+            RefPtr<ResourceObject> resObj;
             if (underlineColorObj && underlineColorObj->errorColorObj) {
-                auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(underlineColorObj->errorColorObj));
-                pattern->RegisterResource<Color>("underlineColorError", resObj, Color(values[CALL_ARG_2]));
+                resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(underlineColorObj->errorColorObj));
             } else {
-                pattern->UnRegisterResource("underlineColorError");
+                ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+            }
+            if (resObj) {
+                pattern->RegisterResource<Color>("underlineColorError", resObj, Color(values[CALL_ARG_2]));
             }
         }
     }
     if (hasValues[CALL_ARG_3]) {
-        userColor.disable = Color(values[CALL_ARG_3]);
+        Color result = Color(values[CALL_ARG_3]);
+        userColor.disable = result;
         if (SystemProperties::ConfigChangePerform()) {
+            RefPtr<ResourceObject> resObj;
             if (underlineColorObj && underlineColorObj->disableColorObj) {
-                auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(underlineColorObj->disableColorObj));
-                pattern->RegisterResource<Color>("underlineColorDisable", resObj, Color(values[CALL_ARG_3]));
+                resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(underlineColorObj->disableColorObj));
             } else {
-                pattern->UnRegisterResource("underlineColorDisable");
+                ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+            }
+            if (resObj) {
+                pattern->RegisterResource<Color>("underlineColorDisable", resObj, Color(values[CALL_ARG_3]));
             }
         }
     }
diff --git a/frameworks/core/interfaces/native/node/node_text_modifier.cpp b/frameworks/core/interfaces/native/node/node_text_modifier.cpp
index cd5e98334c7..de75ad6f662 100644
--- a/frameworks/core/interfaces/native/node/node_text_modifier.cpp
+++ b/frameworks/core/interfaces/native/node/node_text_modifier.cpp
@@ -28,6 +28,7 @@
 #include "frameworks/core/components/common/layout/constants.h"
 #include "frameworks/core/components/common/properties/text_style.h"
 #include "frameworks/core/components_ng/pattern/text/text_model_ng.h"
+#include "core/common/resource/resource_parse_utils.h"
 
 namespace OHOS::Ace::NG {
 constexpr int DEFAULT_SELECTION = -1;
@@ -272,10 +273,23 @@ void ResetTextContentAlign(ArkUINodeHandle node)
 
 void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* fontColorRawPtr)
 {
-    auto* frameNode = reinterpret_cast<FrameNode*>(node);
+    auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
+    Color result = Color(color);
     TextModelNG::SetTextColor(frameNode, Color(color));
-    NodeModifier::ProcessResourceObj<Color>(frameNode, "TextColor", Color(color), fontColorRawPtr);
+    if (SystemProperties::ConfigChangePerform()) {
+        auto pattern = frameNode->GetPattern();
+        CHECK_NULL_VOID(pattern);
+        RefPtr<ResourceObject> resObj;
+        if (!fontColorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(fontColorRawPtr));
+        }
+        if (resObj) {
+            pattern->RegisterResource<Color>("TextColor", resObj, result);
+        }
+    }
 }
 
 void ResetFontColor(ArkUINodeHandle node)
@@ -1185,11 +1199,23 @@ void ResetTextCaretColor(ArkUINodeHandle node)
 
 void SetTextSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color, void* selectedBackgroundColorRawPtr)
 {
-    auto* frameNode = reinterpret_cast<FrameNode*>(node);
+    auto *frameNode = reinterpret_cast<FrameNode *>(node);
     CHECK_NULL_VOID(frameNode);
+    Color result = Color(color);
     TextModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
-    NodeModifier::ProcessResourceObj<Color>(
-        frameNode, "SelectedBackgroundColor", Color(color), selectedBackgroundColorRawPtr);
+    if (SystemProperties::ConfigChangePerform()) {
+        auto pattern = frameNode->GetPattern();
+        CHECK_NULL_VOID(pattern);
+        RefPtr<ResourceObject> resObj;
+        if (!selectedBackgroundColorRawPtr) {
+            ResourceParseUtils::CompleteResourceObjectFromColor(resObj, result, frameNode->GetTag());
+        } else {
+            resObj = AceType::Claim(reinterpret_cast<ResourceObject *>(selectedBackgroundColorRawPtr));
+        }
+        if (resObj) {
+            pattern->RegisterResource<Color>("SelectedBackgroundColor", resObj, result);
+        }
+    }
 }
 
 ArkUI_Uint32 GetTextSelectedBackgroundColor(ArkUINodeHandle node)
diff --git a/interfaces/native/node/style_modifier.cpp b/interfaces/native/node/style_modifier.cpp
index de23f7a456f..2ad7e69d942 100644
--- a/interfaces/native/node/style_modifier.cpp
+++ b/interfaces/native/node/style_modifier.cpp
@@ -919,7 +919,7 @@ int32_t SetBackgroundColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* ite
     auto* fullImpl = GetFullImpl();
     if (node->type == ARKUI_NODE_BUTTON) {
         fullImpl->getNodeModifiers()->getButtonModifier()->setButtonBackgroundColor(
-            node->uiNodeHandle, item->value[NUM_0].u32);
+            node->uiNodeHandle, item->value[NUM_0].u32, nullptr);
     } else if (node->type == ARKUI_NODE_TEXT_INPUT) {
         fullImpl->getNodeModifiers()->getTextInputModifier()->setTextInputBackgroundColor(
             node->uiNodeHandle, item->value[NUM_0].u32, nullptr);
@@ -2156,7 +2156,7 @@ int32_t SetBorderColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
     }
     if (node->type == ARKUI_NODE_TEXT_INPUT || node->type == ARKUI_NODE_TEXT_AREA) {
         fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaBorderColor(
-            node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]);
+            node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3]， nullptr);
     } else {
         fullImpl->getNodeModifiers()->getCommonModifier()->setBorderColor(
             node->uiNodeHandle, colors[NUM_0], colors[NUM_1], colors[NUM_2], colors[NUM_3], nullptr);
@@ -4377,7 +4377,7 @@ int32_t SetFontColor(ArkUI_NodeHandle node, const ArkUI_AttributeItem* item)
             break;
         case ARKUI_NODE_BUTTON:
             fullImpl->getNodeModifiers()->getButtonModifier()->setButtonFontColor(
-                node->uiNodeHandle, item->value[0].u32);
+                node->uiNodeHandle, item->value[0].u32, nullptr);
             break;
         case ARKUI_NODE_TEXT_AREA:
             fullImpl->getNodeModifiers()->getTextAreaModifier()->setTextAreaFontColor(
