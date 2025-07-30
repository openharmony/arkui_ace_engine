/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#pragma once

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "interop-types.h"

using std::string;

const int UndefinedDimensionUnit = -1;

struct Dimension
{
    float value = 0;
    int32_t unit = UndefinedDimensionUnit;
};

struct TreeNode {
  private:
    static int _globalId;
    static string _noAttribute;
    string _name;
    int _customIntData;
    std::unique_ptr<void, std::function<void(const void *)>> _customVoidData;
    int _peerId;
    int _flags;
    // Id of our peer.
    int _id;
    // Id of updater callback.
    int _updaterId;
    // Id of indexer callback.
    int _indexerId;
    // Id of custom callback.
    int _customId;
    std::vector<TreeNode*> _children;
    std::unordered_map<string, string> _attributes;
    TreeNode* _parent;
    float _width;
    float _height;
    float _x;
    float _y;

    std::function<void(Ark_ClickEvent event)> _clickCallback;


  public:
    TreeNode(const string& name, int peerId, int flags) :
        _name(name), _customIntData(0), _peerId(peerId), _flags(flags), _id(_globalId++), _updaterId(0), _indexerId(0), _parent(nullptr) {}

    ~TreeNode() {}

    string name() const { return _name; }

    void setCustomIntData(int intData) {
        _customIntData = intData;
    }

    template<class T>
    void setCustomVoidData(T *const ptr) {
        _customVoidData = {ptr, [ptr](const void *) { delete ptr; }};
    }

    void *customVoidData() const {
        return _customVoidData.get();
    }
    const char* namePtr() const { return _name.c_str(); }

    int peerId() const { return _peerId; }

    int id() const { return _id; }

    int updaterId() const { return _updaterId; }
    int indexerId() const { return _indexerId; }
    int customId() const { return _customId; }

    void setUpdaterId(int updaterId) { _updaterId = updaterId; }
    void setIndexerId(int indexerId) { _indexerId = indexerId; }
    void setCustomId(int customId) { _customId = customId; }
    void setClickEvent(std::function<void(Ark_ClickEvent event)> event) {
        _clickCallback = event;
    }
    void callClickEvent(Ark_ClickEvent event) {
        if (_clickCallback) {
            _clickCallback(event);
        } else {
            fprintf(stderr, "#### Callback is nullptr, peerId = %d\n", _peerId);
        }
    }

    const std::vector<TreeNode*>* children() { return &_children; }

    void dispose() {
        fprintf(stderr, "Dispose node %p\n", this);
        delete this;
    }

    void setParent(TreeNode* parent) {
        this->_parent = parent;
    }

    TreeNode* parent() const {
        return this->_parent;
    }

    int addChild(TreeNode* node) {
        _children.push_back(node);
        node->setParent(this);
        return 0;
    }

    float measure(Ark_VMContext vmContext, float* data);
    float layout(Ark_VMContext vmContext, float* data);
    float draw(Ark_VMContext vmContext, float* data);

    void setMeasureWidthValue(float value);
    float getMeasureWidthValue();
    void setMeasureHeightValue(float value);
    float getMeasureHeightValue();
    void setXValue(float value);
    float getXValue();
    void setYValue(float value);
    float getYValue();

    void removeChild(TreeNode* node) {
        auto it = std::find(_children.begin(), _children.end(), node);
        if (it != _children.end()) {
            _children.erase(it);
            node->setParent(nullptr);
        }
    }

    int insertChildAfter(TreeNode* node, TreeNode* sibling) {

        if (sibling == (TreeNode*)1 || sibling == nullptr) {
            node->setParent(this);
            _children.push_back(node);
            return 0;
        }

        if (_children.empty()) {
            _children.push_back(node);
            return 0;
        }
        auto it = std::find(_children.begin(), _children.end(), sibling);
        if (it == _children.end()) {
            fprintf(stderr, "insertChildAfter: sibling node %p not found among children\n", sibling);
            INTEROP_FATAL("Error");
        }
        auto next = std::next(it);
        _children.insert(next, node);
        node->setParent(this);
        return 0;
    }

    int insertChildBefore(TreeNode* node, TreeNode* sibling) {

        if (sibling == (TreeNode*)1 || sibling == nullptr) {
            _children.insert(_children.begin(), node);
            return 0;
        }

        if (_children.empty()) {
            _children.push_back(node);
            return 0;
        }
        auto it = std::find(_children.begin(), _children.end(), sibling);
        if (it == _children.end()) {
            fprintf(stderr, "insertChildBefore: sibling node %p not found among children\n", sibling);
            INTEROP_FATAL("Error");
        }
        _children.insert(it, node);
        node->setParent(this);
        return 0;
    }

    int insertChildAt(TreeNode* node, int position) {
        _children.insert(_children.begin(), position, node);
        node->setParent(this);
        return 0;
    }

    void* needMoreElements(void* mark, int32_t direction) {
        fprintf(stderr, "needMoreElements %p %d\n", mark, direction);
        if (_children.size() == 0)
            return (void*)0x1;
        if (_children.size() > 5)
            return nullptr;
        return direction == 0 ? _children.front() : _children.back();
    }

    const string& getAttribute(const std::string& key) const {
        auto it = _attributes.find(key);
        if (it != _attributes.end())
            return it->second;
        else
            return _noAttribute;
    }

    void setAttribute(const string& key, const string& value) {
        _attributes[key] = value;
    }

    void resetAttribute(const string& key) {
        _attributes.erase(key);
    }

    Dimension dimensionWidth;
    Dimension dimensionHeight;
    int32_t alignment = 0;
    float* measureResult = nullptr;
    float* layoutResult = nullptr;
};
