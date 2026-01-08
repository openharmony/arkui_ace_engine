/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/declaration/common/declaration_creator_manager.h"

#include "compatible/components/image-animator/image_animator_declaration.h"
#include "compatible/components/svg/svg_animate_declaration.h"
#include "compatible/components/svg/svg_circle_declaration.h"
#include "compatible/components/svg/svg_ellipse_declaration.h"
#include "compatible/components/svg/svg_fe_colormatrix_declaration.h"
#include "compatible/components/svg/svg_fe_composite_declaration.h"
#include "compatible/components/svg/svg_fe_gaussianblur_declaration.h"
#include "compatible/components/svg/svg_fe_offset_declaration.h"
#include "compatible/components/svg/svg_filter_declaration.h"
#include "compatible/components/svg/svg_gradient_declaration.h"
#include "compatible/components/svg/svg_line_declaration.h"
#include "compatible/components/svg/svg_mask_declaration.h"
#include "compatible/components/svg/svg_path_declaration.h"
#include "compatible/components/svg/svg_polygon_declaration.h"
#include "compatible/components/svg/svg_rect_declaration.h"
#include "compatible/components/svg/svg_stop_declaration.h"
#include "compatible/components/svg/svg_text_declaration.h"
#include "compatible/components/svg/svg_text_path_declaration.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components/declaration/button/button_declaration.h"
#include "core/components/declaration/canvas/canvas_declaration.h"
#include "core/components/declaration/piece/piece_declaration.h"
#include "core/components/declaration/richtext/rich_text_declaration.h"
#include "core/components/declaration/span/span_declaration.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/declaration/text/text_declaration.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/components/declaration/xcomponent/xcomponent_declaration.h"

namespace OHOS::Ace {

SINGLETON_INSTANCE_IMPL(DeclarationCreatorManager);

DeclarationCreatorManager::DeclarationCreatorManager() = default;
DeclarationCreatorManager::~DeclarationCreatorManager() = default;

template<class T>
RefPtr<Declaration> DeclarationCreator(const std::string& tag)
{
    return AceType::MakeRefPtr<T>();
}

const RefPtr<Declaration> DeclarationCreatorManager::CreateDeclaration(const std::string& tag)
{
    static const LinearMapNode<std::function<RefPtr<Declaration>(const std::string&)>> declarationCreators[] = {
        { DOM_NODE_TAG_BUTTON, DeclarationCreator<ButtonDeclaration> },
        { DOM_NODE_TAG_CANVAS, DeclarationCreator<CanvasDeclaration> },
        { DOM_NODE_TAG_PIECE, DeclarationCreator<PieceDeclaration> },
        { DOM_NODE_TAG_RICH_TEXT, DeclarationCreator<RichTextDeclaration> },
        { DOM_NODE_TAG_SPAN, DeclarationCreator<SpanDeclaration> },
        { DOM_NODE_TAG_SWIPER, DeclarationCreator<SwiperDeclaration> },
        { DOM_NODE_TAG_TEXT, DeclarationCreator<TextDeclaration> },
        { DOM_NODE_TAG_WEB, DeclarationCreator<WebDeclaration> },
        { DOM_NODE_TAG_XCOMPONENT, DeclarationCreator<XComponentDeclaration> },
    };
    int64_t creatorIndex = BinarySearchFindIndex(declarationCreators, ArraySize(declarationCreators), tag.c_str());
    RefPtr<Declaration> declaration = AceType::MakeRefPtr<Declaration>();
    if (creatorIndex >= 0) {
        declaration = declarationCreators[creatorIndex].value(tag);
    } else {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName(tag.c_str());
        if (!loader) {
            declaration->Init();
            return declaration;
        }
        auto newDeclaration = loader->CreateDeclaration();
        if (newDeclaration) {
            declaration = newDeclaration;
        }
    }
    declaration->Init();
    return declaration;
}

} // namespace OHOS::Ace
