/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PIECE_PIECE_MODIFIER_COMPATIBLE_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PIECE_PIECE_MODIFIER_COMPATIBLE_H

#include <string>
namespace OHOS::Ace {

template<typename T>
class RefPtr;

class Component;
class PieceComponent;
class PieceTheme;
class Border;
class TextStyle;
class EventMarker;

struct ArkUIPieceModifierCompatible {
    RefPtr<PieceComponent> (*createPieceComponent)();
    void (*setContent)(const RefPtr<Component>& pieceComponent, const std::string& content);
    void (*setIcon)(const RefPtr<Component>& pieceComponent, const std::string& icon);
    void (*initializeStyle)(const RefPtr<Component>& pieceComponent, RefPtr<PieceTheme>& theme);
    void (*setBorder)(const RefPtr<Component>& pieceComponent, const Border& border);
    void (*setShowDelete)(const RefPtr<Component>& pieceComponent, bool showDelete);
    TextStyle (*getTextStyle)(const RefPtr<Component>& pieceComponent);
    void (*setTextStyle)(const RefPtr<Component>& pieceComponent, const TextStyle& textStyle);
    void (*setOnDelete)(const RefPtr<Component>& pieceComponent, const EventMarker& onDelete);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PIECE_PIECE_MODIFIER_COMPATIBLE_H