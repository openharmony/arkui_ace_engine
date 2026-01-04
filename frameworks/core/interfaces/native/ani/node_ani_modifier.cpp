/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "animation_ani_modifier.h"
#include "canvas_ani_modifier.h"
#include "common_ani_modifier.h"
#include "common_node_ani_modifier.h"
#include "component3d_ani_modifier.h"
#include "component_content_ani_modifier.h"
#include "component_snapshot_ani_modifier.h"
#include "condition_scope_ani_modifier.h"
#include "content_slot_ani_modifier.h"
#include "custom_node_ani_modifier.h"
#include "detached_free_root_ani_modifier.h"
#include "keyboard_avoid_mode_ani_modifier.h"
#include "drag_ani_modifier.h"
#include "drag_controller_ani_modifier.h"
#include "image_ani_modifier.h"
#include "image_span_ani_modifier.h"
#include "interop_ani_modifier.h"
#include "lazy_for_each_node_ani_modifier.h"
#include "list_ani_modifier.h"
#include "node_adapter_ani_modifier.h"
#include "parallelize_ui_ani_modifier.h"
#include "rich_editor_ani_modifier.h"
#include "text_based_ani_modifier.h"
#include "paste_button_ani_modifier.h"
#include "save_button_ani_modifier.h"
#include "shape_ani_modifier.h"
#include "stateMgmt_ani_modifier.h"
#include "styled_string_ani_modifier.h"
#include "trace_ani_modifier.h"
#include "video_ani_modifier.h"
#include "visual_effect_ani_modifier.h"
#include "waterflow_ani_modifier.h"
#include "web_ani_modifier.h"
#include "xcomponent_ani_modifier.h"
#include "syntax_item_ani_modifier.h"
#include "for_each_node_ani_modifier.h"
#include "uinode_ani_modifier.h"
#include "xbar_ani_modifier.h"
extern "C" {
const ArkUIAniModifiers* GetArkUIAniModifiers()
{
    static const ArkUIAniModifiers impl = {
        .version = ARKUI_ANI_API_VERSION,
        .getImageAniModifier = OHOS::Ace::NG::GetImageAniModifier,
        .getWebAniModifier = OHOS::Ace::NG::GetWebAniModifier,
        .getDragAniModifier = OHOS::Ace::NG::GetDragAniModifier,
        .getCommonAniModifier = OHOS::Ace::NG::GetCommonAniModifier,
        .getCustomNodeAniModifier = OHOS::Ace::NG::GetCustomNodeAniModifier,
        .getKeyboardAvoidModeAniModifier = OHOS::Ace::NG::GetKeyboardAvoidModeAniModifier,
        .getLazyForEachNodeAniModifier = OHOS::Ace::NG::GetLazyForEachNodeAniModifier,
        .getContentSlotAniModifier = OHOS::Ace::NG::GetContentSlotAniModifier,
        .getArkUIAniDrawModifier = OHOS::Ace::NG::GetArkUIAniDrawModifier,
        .getArkUIAniWaterFlowModifier = OHOS::Ace::NG::GetArkUIAniWaterFlowModifier,
        .getArkUIAniListModifier = OHOS::Ace::NG::GetArkUIAniListModifier,
        .getComponentSnapshotAniModifier = OHOS::Ace::NG::GetComponentSnapshotAniModifier,
        .getAnimationAniModifier = OHOS::Ace::NG::GetAnimationAniModifier,
        .getVisualEffectAniModifier = OHOS::Ace::NG::GetVisualEffectAniModifier,
        .getInteropAniModifier = OHOS::Ace::NG::GetInteropAniModifier,
        .getDragControllerAniModifier = OHOS::Ace::NG::GetDragControllerAniModifier,
        .getStyledStringAniModifier = OHOS::Ace::NG::GetStyledStringAniModifier,
        .getTextBasedAniModifier = OHOS::Ace::NG::GetTextBasedAniModifier,
        .getImageSpanAniModifier = OHOS::Ace::NG::GetImageSpanAniModifier,
        .getArkUIAniVideoModifier = OHOS::Ace::NG::GetVideoAniModifier,
        .getArkUIAniShapeModifier = OHOS::Ace::NG::GetShapeAniModifier,
        .getRichEditorAniModifier = OHOS::Ace::NG::GetRichEditorAniModifier,
        .getStateMgmtAniModifier = OHOS::Ace::NG::GetStateMgmtAniModifier,
        .getArkUIAniXComponentModifier = OHOS::Ace::NG::GetXComponentAniModifier,
        .getArkUIAniConditionScopeModifier = OHOS::Ace::NG::GetConditionScopeAniModifier,
        .getArkUIAniComponentConentModifier = OHOS::Ace::NG::GetArkUIAniComponentConentModifier,
        .getCanvasAniModifier = OHOS::Ace::NG::GetCanvasAniModifier,
        .getTraceAniModifier = OHOS::Ace::NG::GetTraceAniModifier,
        .getUINodeOnUpdateDoneAniModifier = OHOS::Ace::NG::GetUINodeOnUpdateDoneAniModifier,
        .getNodeAdapterAniModifier = OHOS::Ace::NG::GetNodeAdapterAniModifier,
        .getSyntaxItemAniModifier = OHOS::Ace::NG::GetSyntaxItemAniModifier,
        .getForEachNodeAniModifier = OHOS::Ace::NG::GetForEachNodeAniModifier,
        .getComponent3DModifier = OHOS::Ace::NG::GetComponent3DModifier,
        .getXBarAniModifier = OHOS::Ace::NG::GetXBarAniModifier,
        .getCommonNodeAniModifier = OHOS::Ace::NG::GetCommonNodeAniModifier,
        .getParallelizeUIModifier = OHOS::Ace::NG::GetParallelizeUIAniModifier,
        .getSaveButtonAniModifier = OHOS::Ace::NG::GetSaveButtonAniModifier,
        .getPasteButtonAniModifier = OHOS::Ace::NG::GetPasteButtonAniModifier,
        .getArkUIAniDetachedFreeRootModifier = OHOS::Ace::NG::GetDetachedFreeRootModifier,
    };
    return &impl;
}
}